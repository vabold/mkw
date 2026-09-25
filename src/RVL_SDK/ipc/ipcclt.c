/// \file RVL_SDK/ipc/ipcclt.c
///
/// Sources:
///     [RJTJ01] Minna no Joushiki Ryoku TV
///     [RDCE78] Deadly Creatures
///     [SC5PGN] Challenge Me: Word Puzzles
///
/// SPDX-License-Identifier: CC0-1.0

#include <RVL_SDK/os.h>
#include <RVL_SDK/private/OSIpc.h>
#include <RVL_SDK/private/acr.h>
#include <RVL_SDK/private/ipc.h>
#include <RVL_SDK/private/ipcProfile.h>
#include <RVL_SDK/private/memory.h>

#define PPC_TO_IOP_ADDR( addr_ ) \
    ( ( addr_ ) ? (u8 *)OSCachedToPhysical( (void *)( addr_ ) ) : NULL )
#define IOP_TO_PPC_ADDR( addr_ ) ( ( addr_ ) ? (u8 *)OSPhysicalToCached( (u32)( addr_ ) ) : NULL )

#define IPCCTRL_SET( flag_ ) \
    IPCWriteReg( IPCREG_PPCCTRL, \
            IPCReadReg( IPCREG_PPCCTRL ) & ( ACRIPCCTRL_RECVMSGINTEN | ACRIPCCTRL_RECVACKINTEN ) | \
                    ( flag_ ) )

#define IPCCTRL_TEST( flag_ ) ( IPCReadReg( IPCREG_PPCCTRL ) & ( flag_ ) ) == ( flag_ )

enum
{
    IPC_MAX_REQUESTS = 16,        /// Maximum number of requests to be queued
    IPC_HEAP_SIZE = 0x1000,       /// IPC heap size
    IPC_REINIT_HEAP_SIZE = 0x800, /// IPC heap size after relaunch
};

typedef struct
{
    IOSIoRequest req;           /// Raw IPC request struct
    IOSIoCallbackFunc callback; /// User callback
    void *userData;             /// User callback argument
    BOOL relnchFl;              /// Relaunch flag set by IOS_IoctlvReboot
    OSThreadQueue threadQueue;  /// Thread queue for waiting upon reply
    u8 pad[ 0x40 - 0x34 ];
} IOSRequestRpc;

typedef struct
{
    u32 totalNumSent;
    u32 totalNumQueued;
    u32 nextToSend;
    u32 nextQueued;
    IOSRequestRpc *queue[ IPC_MAX_REQUESTS ];
} IOSResponseQueue;

static s32 __mailboxAck = 1;                  /// Decremented on PPC send and incremented on IOP ack
static IOSHeapId hid = -1;                    /// IPC heap
static BOOL __relnchFl = FALSE;               /// IOS_IoctlvReboot (relaunch) flag
static IOSRequestRpc *__relnchRpc = NULL;     /// Save of static IOSRequestRpc for relaunch
static IOSRequestRpc *__relnchRpcSave = NULL; /// Save of allocated IOSRequestRpc for relaunch
static IOSResponseQueue __responses;          /// Queue of requests to send and relaunch
static IOSRequestRpc __rpcBuf;                /// Static IOSRequestRPC buffer for relaunch

/// Count number of characters up until the null terminator or the designated maximum length
size_t strnlen( const u8 *str, size_t maxlen )
{
    const u8 *cur = str;
    while( *cur && maxlen-- )
    {
        cur++;
    }
    return cur - str;
}

/// Allocate IOSRequestRpc buffer
static IOSRequestRpc *ipcAllocReq( void )
{
    return (IOSRequestRpc *)iosAllocAligned( hid, sizeof( IOSRequestRpc ), 0x20 );
}

/// Free IOSRequestRpc buffer
static IOSError ipcFree( IOSRequestRpc *rpc )
{
    iosFree( hid, rpc );
    return IOS_ERROR_OK;
}

/// Enqueue the IPC request to be sent later
static IOSError __ipcQueueRequest( IOSRequestRpc *rpc )
{
    IOSError rv = IOS_ERROR_OK;

    // FIXME: This doesn't match in IOS_IoctlvReboot
    if( !!( __responses.totalNumQueued < __responses.totalNumSent ?
                        __responses.totalNumQueued + -__responses.totalNumSent :
                        __responses.totalNumQueued - __responses.totalNumSent >=
                                IPC_MAX_REQUESTS ) )
    {
        rv = IOS_ERROR_QFULL;
    }
    else
    {
        __responses.queue[ __responses.nextQueued ] = rpc;
        __responses.nextQueued = ( __responses.nextQueued + 1 ) % IPC_MAX_REQUESTS;
        __responses.totalNumQueued++;
        IPCiProfQueueReq( &rpc->req, rpc->req.handle );
    }

    return rv;
}

/// Send the IPC request now
static inline void __ipcSendRequest( void )
{
    IOSRequestRpc *rpc;

    // FIXME: This doesn't match in IOS_IoctlvReboot
    if( __responses.totalNumQueued < __responses.totalNumSent ?
                    __responses.totalNumQueued + -__responses.totalNumSent :
                    __responses.totalNumQueued - __responses.totalNumSent - 0 == 0 )
    {
        return;
    }

    rpc = __responses.queue[ __responses.nextToSend ];

    if( rpc != NULL )
    {
        if( rpc->relnchFl )
        {
            __mailboxAck--;
        }

        // Set PPCMSG register to the request block
        IPCWriteReg( IPCREG_PPCMSG, OSCachedToPhysical( (u32)&rpc->req ) );
        __responses.nextToSend = ( __responses.nextToSend + 1 ) % IPC_MAX_REQUESTS;
        __responses.totalNumSent++;
        __mailboxAck--;
        // Notify IOP with MSG
        IPCCTRL_SET( ACRIPCCTRL_SENDMSG );
    }
}

/// Handle resource reply from IOS
static void IpcReplyHandler( s32 interrupt, OSContext *context )
{
    IOSIoRequest *req;
    IOSRequestRpc *rpc;
    u32 iopMsg, i;

    iopMsg = IPCReadReg( IPCREG_IOPMSG );
    if( !iopMsg )
    {
        return;
    }

    rpc = (IOSRequestRpc *)OSPhysicalToCached( iopMsg );
    // Clear receive message flag
    IPCCTRL_SET( ACRIPCCTRL_RECVMSGSTS );
    // Clear IPC IRQ flag
    ACRWriteReg( ACRPPCIRQSTS, ACRIRQFL_IPCPPC );

    req = &rpc->req;
    DCInvalidateRange( req, sizeof( IOSIoRequest ) );

    // IOS replaces the cmd with IOS_REPLY, but prior to that the IPC handler backs up the command
    // into the already-read handle field
    switch( req->handle )
    {
    case IOS_READ:
        req->args.read.outPtr = IOP_TO_PPC_ADDR( req->args.read.outPtr );
        if( req->status > 0 )
        {
            DCInvalidateRange( req->args.read.outPtr, req->status );
        }
        break;

    case IOS_IOCTL:
        req->args.ioctl.outPtr = IOP_TO_PPC_ADDR( req->args.ioctl.outPtr );
        DCInvalidateRange( req->args.ioctl.inPtr, req->args.ioctl.inLen );
        DCInvalidateRange( req->args.ioctl.outPtr, req->args.ioctl.outLen );
        break;

    case IOS_IOCTLV:
    {
        IOSIoRequestIoctlv *ioctlv = &req->args.ioctlv;
        req->args.ioctlv.vector = (IOSIoVector *)IOP_TO_PPC_ADDR( req->args.ioctlv.vector );
        DCInvalidateRange( ioctlv->vector,
                ( req->args.ioctlv.readCount + req->args.ioctlv.writeCount ) *
                        sizeof( IOSIoVector ) );

        for( i = 0; i < req->args.ioctlv.readCount + req->args.ioctlv.writeCount; i++ )
        {
            // FIXME: Matches debug but not release
            ioctlv->vector[ i ].base = IOP_TO_PPC_ADDR( ioctlv->vector[ i ].base );
            DCInvalidateRange( ioctlv->vector[ i ].base, ioctlv->vector[ i ].length );
        }

        if( __relnchFl && __relnchRpcSave == rpc )
        {
            __relnchFl = FALSE;
            if( __mailboxAck < 1 )
            {
                __mailboxAck++;
            }
        }
        break;
    }
    }

    if( rpc->callback != NULL )
    {
        struct
        {
            OSContext context;
            // TODO: Figure out what this actually is. This is just to push the stack size
            u8 extra[ 0x100 ];
        } cbCtx;
        OSClearContext( &cbCtx.context );
        OSSetCurrentContext( &cbCtx.context );
        rpc->callback( req->status, rpc->userData );
        OSClearContext( &cbCtx.context );
        OSSetCurrentContext( context );
        ipcFree( rpc );
    }
    else
    {
        OSWakeupThread( &rpc->threadQueue );
    }

    // Acknowledge we received the message
    IPCCTRL_SET( ACRIPCCTRL_SENDACK );
    IPCiProfReply( req, rpc->req.handle );
}

/// Handle request acknowledge from IOS
static void IpcAckHandler( s32 interrupt, OSContext *context )
{
    // Clear receive acknowledge flag
    IPCCTRL_SET( ACRIPCCTRL_RECVACKSTS );
    // Clear IPC IRQ flag
    ACRWriteReg( ACRPPCIRQSTS, ACRIRQFL_IPCPPC );

    if( __mailboxAck < 1 )
    {
        __mailboxAck++;
        IPCiProfAck( );
    }
    if( __mailboxAck > 0 )
    {
        if( __relnchFl )
        {
            __relnchRpc->req.status = 0;
            __relnchFl = FALSE;
            OSWakeupThread( &__relnchRpc->threadQueue );
            // Send acknowledge for relaunch
            IPCCTRL_SET( ACRIPCCTRL_SENDACK );
        }
        __ipcSendRequest( );
    }
}

/// Handle IPC interrupt request
static void IPCInterruptHandler( s16 interrupt, OSContext *context )
{
    // Check for reply (RECVMSG)
    if( IPCCTRL_TEST( ACRIPCCTRL_RECVMSGSTS | ACRIPCCTRL_RECVMSGINTEN ) )
    {
        IpcReplyHandler( interrupt, context );
    }

    // Check for acknowledge (RECVACK)
    if( IPCCTRL_TEST( ACRIPCCTRL_RECVACKSTS | ACRIPCCTRL_RECVACKINTEN ) )
    {
        IpcAckHandler( interrupt, context );
    }
}

/// Iniitalize the IPC client
IOSError IPCCltInit( void )
{
    static BOOL initialized = FALSE;
    u8 *end;
    IOSError rv = IOS_ERROR_OK;
    u8 *base;

    if( initialized )
    {
        goto out;
    }

    initialized = TRUE;
    IPCInit( );

    base = (u8 *)IPCGetBufferLo( );
    end = base + IPC_HEAP_SIZE;
    if( end > (u8 *)IPCGetBufferHi( ) )
    {
        rv = IOS_ERROR_FAIL_ALLOC;
        goto out;
    }

    hid = iosCreateHeap( base, IPC_HEAP_SIZE );
    IPCSetBufferLo( end );
    // TODO: Name these values
    __OSSetInterruptHandler( 27, IPCInterruptHandler );
    __OSUnmaskInterrupts( 0x10 );
    // Enable interrupts and send acknowledge for relaunch
    IPCWriteReg( IPCREG_PPCCTRL,
            ACRIPCCTRL_RECVMSGINTEN | ACRIPCCTRL_RECVACKINTEN | ACRIPCCTRL_SENDACK );
    IPCiProfInit( );

out:
    return rv;
}

/// Reinitialize the IPC client after relaunch
IOSError IPCCltReInit( void )
{
    u8 *end;
    IOSError rv = IOS_ERROR_OK;
    u8 *base;

    // Use a different heap size after relaunch
    base = (u8 *)IPCGetBufferLo( );
    end = base + IPC_REINIT_HEAP_SIZE;
    if( end > (u8 *)IPCGetBufferHi( ) )
    {
        rv = IOS_ERROR_FAIL_ALLOC;
        goto out;
    }

    hid = iosCreateHeap( base, IPC_REINIT_HEAP_SIZE );
    IPCSetBufferLo( end );

out:
    return rv;
}

/// Allocate and initialize IPC request command block
static IOSError
__ios_Ipc1( IOSFd fd, u32 cmd, IOSIoCallbackFunc callback, void *userData, IOSRequestRpc **rpc )
{
    IOSError rv = IOS_ERROR_OK;
    IOSIoRequest *req;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    *rpc = ipcAllocReq( );
    if( *rpc == NULL )
    {
        rv = IOS_ERROR_FAIL_ALLOC;
        goto out;
    }

    req = &( *rpc )->req;
    ( *rpc )->callback = callback;
    ( *rpc )->userData = userData;
    ( *rpc )->relnchFl = FALSE;
    req->cmd = cmd;
    req->handle = fd;

out:
    return rv;
}

/// Queue an IPC request to be sent
static IOSError __ios_Ipc2( IOSRequestRpc *rpc, IOSIoCallbackFunc callback )
{
    IOSError rv = IOS_ERROR_OK;
    int enabled;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    if( callback == NULL )
    {
        OSInitThreadQueue( &rpc->threadQueue );
    }
    DCFlushRange( &rpc->req, sizeof( IOSIoRequest ) );

    enabled = OSDisableInterrupts( );
    rv = __ipcQueueRequest( rpc );
    if( rv != IOS_ERROR_OK )
    {
        OSRestoreInterrupts( enabled );
        if( callback != NULL )
        {
            ipcFree( rpc );
        }
        goto out;
    }

    if( __mailboxAck > 0 )
    {
        __ipcSendRequest( );
    }
    if( callback == NULL )
    {
        OSSleepThread( &rpc->threadQueue );
    }
    OSRestoreInterrupts( enabled );
    if( callback == NULL )
    {
        rv = rpc->req.status;
    }

out:
    if( rpc != NULL && callback == NULL )
    {
        ipcFree( rpc );
    }

    return rv;
}

/// Setup an IOS_OPEN request
static IOSError __ios_Open( IOSRequestRpc *rpc, u8 *path, u32 flags )
{
    IOSError rv = IOS_ERROR_OK;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
    }
    else
    {
        DCFlushRange( path, strnlen( path, sizeof( IOSPath ) ) + 1 );
        rpc->req.args.open.path = (u8 *)OSCachedToPhysical( (u32)path );
        rpc->req.args.open.flags = flags;
    }

    return rv;
}

IOSError IOS_OpenAsync( u8 *path, u32 flags, IOSIoCallbackFunc callback, void *userData )
{
    IOSRequestRpc *rpc;

    s32 rv = __ios_Ipc1( 0, IOS_OPEN, callback, userData, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Open( rpc, path, flags );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, callback );
        }
    }

    return rv;
}

IOSFd IOS_Open( u8 *path, u32 flags )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( 0, IOS_OPEN, NULL, NULL, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Open( rpc, path, flags );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, NULL );
        }
    }

    return rv;
}

IOSError IOS_CloseAsync( IOSFd fd, IOSIoCallbackFunc callback, void *userData )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_CLOSE, callback, userData, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Ipc2( rpc, callback );
    }

    return rv;
}

IOSError IOS_Close( IOSFd fd )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_CLOSE, NULL, NULL, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Ipc2( rpc, NULL );
    }

    return rv;
}

/// Setup an IOS_READ request
static IOSError __ios_Read( IOSRequestRpc *rpc, u8 *outPtr, s32 outLen )
{
    IOSError rv = IOS_ERROR_OK;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
    }
    else
    {
        DCInvalidateRange( outPtr, outLen );
        rpc->req.args.read.outPtr = PPC_TO_IOP_ADDR( outPtr );
        rpc->req.args.read.outLen = outLen;
    }

    return rv;
}

IOSError
IOS_ReadAsync( IOSFd fd, u8 *outPtr, s32 outLen, IOSIoCallbackFunc callback, void *userData )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_READ, callback, userData, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Read( rpc, outPtr, outLen );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, callback );
        }
    }

    return rv;
}

IOSError IOS_Read( IOSFd fd, u8 *outPtr, u32 outLen )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_READ, NULL, NULL, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Read( rpc, outPtr, outLen );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, NULL );
        }
    }

    return rv;
}

/// Setup an IOS_WRITE request
static IOSError __ios_Write( IOSRequestRpc *rpc, u8 *inPtr, s32 inLen )
{
    IOSError rv = IOS_ERROR_OK;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
    }
    else
    {
        rpc->req.args.write.inPtr = PPC_TO_IOP_ADDR( inPtr );
        rpc->req.args.write.inLen = inLen;
        DCFlushRange( inPtr, inLen );
    }

    return rv;
}

IOSError
IOS_WriteAsync( IOSFd fd, u8 *inPtr, s32 inLen, IOSIoCallbackFunc callback, void *userData )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_WRITE, callback, userData, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Write( rpc, inPtr, inLen );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, callback );
        }
    }

    return rv;
}

IOSError IOS_Write( IOSFd fd, u8 *inPtr, s32 inLen )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_WRITE, NULL, NULL, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Write( rpc, inPtr, inLen );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, NULL );
        }
    }

    return rv;
}

/// Setup an IOS_SEEK request
static IOSError __ios_Seek( IOSRequestRpc *rpc, s32 offset, s32 whence )
{
    IOSError rv = IOS_ERROR_OK;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
    }
    else
    {
        rpc->req.args.seek.offset = offset;
        rpc->req.args.seek.whence = whence;
    }

    return rv;
}

IOSError
IOS_SeekAsync( IOSFd fd, s32 offset, s32 whence, IOSIoCallbackFunc callback, void *userData )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_SEEK, callback, userData, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Seek( rpc, offset, whence );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, callback );
        }
    }

    return rv;
}

IOSError IOS_Seek( IOSFd fd, s32 offset, s32 whence )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_SEEK, NULL, NULL, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Seek( rpc, offset, whence );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, NULL );
        }
    }

    return rv;
}

/// Setup an IOS_IOCTL request
static IOSError
__ios_Ioctl( IOSRequestRpc *rpc, u32 cmd, u8 *inPtr, u32 inLen, u8 *outPtr, u32 outLen )
{
    IOSError rv = IOS_ERROR_OK;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
    }
    else
    {
        rpc->req.args.ioctl.cmd = cmd;
        rpc->req.args.ioctl.outPtr = PPC_TO_IOP_ADDR( outPtr );
        rpc->req.args.ioctl.outLen = outLen;
        rpc->req.args.ioctl.inPtr = PPC_TO_IOP_ADDR( inPtr );
        rpc->req.args.ioctl.inLen = inLen;

        DCFlushRange( inPtr, inLen );
        DCFlushRange( outPtr, outLen );
    }

    return rv;
}

IOSError IOS_IoctlAsync( IOSFd fd,
        u32 cmd,
        u8 *inPtr,
        u32 inLen,
        u8 *outPtr,
        u32 outLen,
        IOSIoCallbackFunc callback,
        void *userData )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_IOCTL, callback, userData, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Ioctl( rpc, cmd, inPtr, inLen, outPtr, outLen );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, callback );
        }
    }

    return rv;
}

IOSError IOS_Ioctl( IOSFd fd, u32 cmd, u8 *inPtr, u32 inLen, u8 *outPtr, u32 outLen )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_IOCTL, NULL, NULL, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Ioctl( rpc, cmd, inPtr, inLen, outPtr, outLen );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, NULL );
        }
    }

    return rv;
}

/// Setup an IOS_IOCTLV request
static IOSError
__ios_Ioctlv( IOSRequestRpc *rpc, u32 cmd, u32 readCount, u32 writeCount, IOSIoVector *vector )
{
    IOSError rv = IOS_ERROR_OK;
    u32 i;
    u32 vecOffset;

    if( rpc == NULL )
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    rpc->req.args.ioctlv.cmd = cmd;
    rpc->req.args.ioctlv.readCount = readCount;
    rpc->req.args.ioctlv.writeCount = writeCount;
    rpc->req.args.ioctlv.vector = vector;

    vecOffset = rpc->req.args.ioctlv.readCount;
    for( i = 0; i < rpc->req.args.ioctlv.writeCount; i++ )
    {
        DCFlushRange( rpc->req.args.ioctlv.vector[ vecOffset + i ].base,
                rpc->req.args.ioctlv.vector[ vecOffset + i ].length );

        rpc->req.args.ioctlv.vector[ vecOffset + i ].base =
                PPC_TO_IOP_ADDR( rpc->req.args.ioctlv.vector[ vecOffset + i ].base );
    }

    for( i = 0; i < rpc->req.args.ioctlv.readCount; i++ )
    {
        DCFlushRange( rpc->req.args.ioctlv.vector[ i ].base,
                rpc->req.args.ioctlv.vector[ i ].length );

        rpc->req.args.ioctlv.vector[ i ].base =
                PPC_TO_IOP_ADDR( rpc->req.args.ioctlv.vector[ i ].base );
    }

    DCFlushRange( rpc->req.args.ioctlv.vector,
            ( rpc->req.args.ioctlv.readCount + rpc->req.args.ioctlv.writeCount ) *
                    sizeof( IOSIoVector ) );

    rpc->req.args.ioctlv.vector = (IOSIoVector *)PPC_TO_IOP_ADDR( vector );

out:
    return rv;
}

IOSError IOS_IoctlvAsync( IOSFd fd,
        u32 cmd,
        u32 readCount,
        u32 writeCount,
        IOSIoVector *vector,
        IOSIoCallbackFunc callback,
        void *userData )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_IOCTLV, callback, userData, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Ioctlv( rpc, cmd, readCount, writeCount, vector );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, callback );
        }
    }

    return rv;
}

IOSError IOS_Ioctlv( IOSFd fd, u32 cmd, u32 readCount, u32 writeCount, IOSIoVector *vector )
{
    IOSRequestRpc *rpc;

    IOSError rv = __ios_Ipc1( fd, IOS_IOCTLV, NULL, NULL, &rpc );
    if( rv == IOS_ERROR_OK )
    {
        rv = __ios_Ioctlv( rpc, cmd, readCount, writeCount, vector );
        if( rv == IOS_ERROR_OK )
        {
            rv = __ios_Ipc2( rpc, NULL );
        }
    }

    return rv;
}

// FIXME: Non-matching
IOSError IOS_IoctlvReboot( IOSFd fd, u32 cmd, u32 readCount, u32 writeCount, IOSIoVector *vector )
{
    IOSError rv = IOS_ERROR_OK;
    IOSRequestRpc *rpc;
    int enabled;

    enabled = OSDisableInterrupts( );
    if( __relnchFl )
    {
        OSRestoreInterrupts( enabled );
        rv = IOS_ERROR_NOTREADY;
        goto out;
    }

    __relnchFl = TRUE;
    OSRestoreInterrupts( enabled );

    rv = __ios_Ipc1( fd, IOS_IOCTLV, NULL, NULL, &rpc );
    if( rv != IOS_ERROR_OK )
    {
        goto cleanup;
    }

    __relnchRpcSave = rpc;
    rpc->relnchFl = TRUE;

    rv = __ios_Ioctlv( rpc, cmd, readCount, writeCount, vector );
    if( rv == IOS_ERROR_OK )
    {
        int enabled;
        IOSRequestRpc *rpcSave;

        memcpy( &__rpcBuf, rpc, sizeof( IOSRequestRpc ) );
        __relnchRpc = &__rpcBuf;
        rpcSave = rpc;
        OSInitThreadQueue( &__relnchRpc->threadQueue );
        DCFlushRange( &rpcSave->req, sizeof( IOSIoRequest ) );

        enabled = OSDisableInterrupts( );
        rv = __ipcQueueRequest( rpcSave );
        if( rv != IOS_ERROR_OK )
        {
            OSRestoreInterrupts( enabled );
            goto cleanup;
        }

        if( __mailboxAck > 0 )
        {
            __ipcSendRequest( );
        }
        OSSleepThread( &__relnchRpc->threadQueue );
        OSRestoreInterrupts( enabled );
        rv = __relnchRpc->req.status;
    }

cleanup:
    __relnchFl = FALSE;
    __relnchRpcSave = NULL;
    if( rpc != NULL && rv != IOS_ERROR_OK )
    {
        ipcFree( rpc );
    }

out:
    return rv;
}
