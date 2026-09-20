/// \file RVL_SDK/ipc/ipcProfile.c
///
/// Sources:
///     [RJTJ01] Minna no Joushiki Ryoku TV
///     [RDCE78] Deadly Creatures
///     [SC5PGN] Challenge Me: Word Puzzles
///
/// SPDX-License-Identifier: CC0-1.0

#include <RVL_SDK/os.h>
#include <RVL_SDK/private/ipc.h>
#include <RVL_SDK/private/ipcProfile.h>

enum
{
    IPC_PROFILE_REQUEST_NUM = 32,
};

static IOSFd IpcFdArray[ IPC_PROFILE_REQUEST_NUM ] = { };
static IOSIoRequest *IpcReqPtrArray[ 32 ] = { };

static u32 IpcNumPendingReqs = 0;
static u32 IpcNumUnIssuedReqs = 0;

static void AddReqInfo( IOSIoRequest *req, IOSFd fd );
static void DelReqInfo( IOSIoRequest *req, IOSFd fd );

u32 IPCGetNumPendingReqs( void )
{
    return IpcNumPendingReqs;
}

u32 IPCGetNumUnIssuedReqs( void )
{
    return IpcNumUnIssuedReqs;
}

s32 IPCGetQueueStatus( u32 id )
{
    if( id >= IPC_PROFILE_REQUEST_NUM )
    {
        return -1;
    }
    if( IpcReqPtrArray[ id ] == NULL )
    {
        return -1;
    }
    return IpcReqPtrArray[ id ]->status;
}

void IPCiProfInit( void )
{
    u32 id;
    IpcNumPendingReqs = 0;
    IpcNumUnIssuedReqs = 0;
    for( id = 0; id < IPC_PROFILE_REQUEST_NUM; id++ )
    {
        IpcReqPtrArray[ id ] = NULL;
        IpcFdArray[ id ] = IOS_FD_INVALID;
    }
}

void IPCiProfQueueReq( IOSIoRequest *req, IOSFd fd )
{
    IpcNumPendingReqs++;
    IpcNumUnIssuedReqs++;
    AddReqInfo( req, fd );
}

void IPCiProfAck( void )
{
    IpcNumUnIssuedReqs--;
}

void IPCiProfReply( IOSIoRequest *req, IOSFd fd )
{
    IpcNumPendingReqs--;
    DelReqInfo( req, fd );
}

static void AddReqInfo( IOSIoRequest *req, IOSFd fd )
{
    u32 id;
    for( id = 0; id < IPC_PROFILE_REQUEST_NUM; id++ )
    {
        if( IpcReqPtrArray[ id ] == NULL && IpcFdArray[ id ] == IOS_FD_INVALID )
        {
            IpcReqPtrArray[ id ] = req;
            IpcFdArray[ id ] = fd;
            return;
        }
    }
}

static void DelReqInfo( IOSIoRequest *req, IOSFd fd )
{
    u32 id;
    for( id = 0; id < IPC_PROFILE_REQUEST_NUM; id++ )
    {
        if( req == IpcReqPtrArray[ id ] && fd == IpcFdArray[ id ] )
        {
            IpcReqPtrArray[ id ] = NULL;
            IpcFdArray[ id ] = IOS_FD_INVALID;
            return;
        }
    }
}
