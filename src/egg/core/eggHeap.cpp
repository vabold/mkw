#include <egg/core/eggHeap.h>

#include <egg/core/eggThread.h>

namespace EGG
{

void Heap::initialize( void )
{
    // offsetof( Heap, mHeapLink )
    nw4r::ut::List_Init( &sHeapList, 0x20 );
    OSInitMutex( &sRootMutex );
    sIsHeapListInitialized = 1;
}

Heap::Heap( MEMiHeapHead *handle )
    : mHeapHandle( handle ), mHeapBuffer( NULL ), mParentHeap( NULL ), mName( "NoName" )
{
    // Normally an implicit part of the TBitFlag constructor
    // We need this here to initialize mName first
    mFlags.makeAllZero( );

    // offsetof( Disposer, mLink )
    nw4r::ut::List_Init( &mDisposerList, 8 );

    OSLockMutex( &sRootMutex );
    nw4r::ut::List_Append( &sHeapList, this );
    OSUnlockMutex( &sRootMutex );
}

Heap::~Heap( void )
{
    OSLockMutex( &sRootMutex );
    nw4r::ut::List_Remove( &sHeapList, this );
    OSUnlockMutex( &sRootMutex );
}

void *Heap::alloc( u32 size, int align, Heap *pHeap )
{
    Heap *pCurrentHeap = sCurrentHeap;
    Thread *pCurrentThread = Thread::findThread( OSGetCurrentThread( ) );
    if( sAllocatableThread )
    {
        // This is probably an assert to make sure allocating in other threads is disabled
        OSThread *pCurrentOSThread = OSGetCurrentThread( );
        // pCurrentOSThread == sAllocatableThread
    }

    if( pCurrentThread && pCurrentThread->getNewHeap( ) )
    {
        pHeap = pCurrentHeap = pCurrentThread->getNewHeap( );
    }

    if( sAllocatableHeap )
    {
        if( pCurrentHeap && !pHeap )
        {
            pHeap = pCurrentHeap;
        }

        if( pHeap != sAllocatableHeap )
        {
            OSReport( "cannot allocate from heap %x(%s) : allocatable heap is %x(%s)\n", pHeap,
                    pHeap->getName( ), sAllocatableHeap, sAllocatableHeap->getName( ) );
            OSReport( "\tthread heap=%x\n", pCurrentThread ? pCurrentThread->getNewHeap( ) : NULL );
            OSReport( "\tthread heap=%s\n",
                    pCurrentThread ? pCurrentThread->getNewHeap( ) ?
                                     pCurrentThread->getNewHeap( )->getName( ) :
                                     "none" :
                                     "none" );
            if( sErrorCallback )
            {
                HeapErrorArg arg;
                arg.name = "disable_but";
                arg.arg = sErrorCallbackArg;
                ( *sErrorCallback )( arg );
            }

            dumpAll( );
            return NULL;
        }
    }

    if( sAllocCallback )
    {
        HeapAllocArg arg;
        arg.heap = pHeap ? pHeap : pCurrentHeap;
        arg.size = size;
        arg.align = align;
        arg.arg = sAllocCallbackArg;
        ( *sAllocCallback )( arg );
    }

    if( pHeap )
    {
        return pHeap->alloc( size, align );
    }

    if( pCurrentHeap )
    {
        void *memBlock = pCurrentHeap->alloc( size, align );
        if( !memBlock )
        {
            OSReport( "heap (%p):(%.1fMBytes free %d)->alloc(size(%d:%.1fMBytes),%d align)\n",
                    pCurrentHeap, pCurrentHeap->getTotalSize( ) / ( 1024.0f * 1024.0f ),
                    pCurrentHeap->getAllocatableSize( ), size, size / ( 1024.0f * 1024.0f ),
                    align );
            dumpAll( );
        }
        return memBlock;
    }

    OSReport( "cannot allocate %d from heap %x\n", size, pHeap );
    dumpAll( );
    return NULL;
}

// RevoYawarakaR.MAP: size 0x98 (-O4,p -inline on)
Heap *Heap::findHeap( MEMiHeapHead *handle )
{
    Heap *pHeap = NULL;
    OSLockMutex( &sRootMutex );

    if( sIsHeapListInitialized )
    {
        Heap *pNode = NULL;
        while( pNode = reinterpret_cast< Heap * >( nw4r::ut::List_GetNext( &sHeapList, pNode ) ) )
        {
            if( pNode->mHeapHandle == handle )
            {
                pHeap = pNode;
                break;
            }
        }
    }

    OSUnlockMutex( &sRootMutex );
    return pHeap;
}

Heap *Heap::findParentHeap( void )
{
    return mParentHeap;
}

Heap *Heap::findContainHeap( const void *memBlock )
{
    Heap *pHeap = NULL;

    if( MEMiHeapHead *handle = MEMFindContainHeap( memBlock ) )
    {
        pHeap = findHeap( handle );
    }

    return pHeap;
}

void Heap::free( void *memBlock, Heap *pHeap )
{
    if( !pHeap )
    {
        MEMiHeapHead *handle = MEMFindContainHeap( memBlock );
        if( !handle )
        {
            return;
        }

        pHeap = findHeap( handle );
        if( !pHeap )
        {
            return;
        }
    }

    pHeap->free( memBlock );
}

void Heap::dispose( void )
{
    Disposer *pDisposer = NULL;
    while( pDisposer = reinterpret_cast< Disposer * >( nw4r::ut::List_GetFirst( &mDisposerList ) ) )
    {
        pDisposer->~Disposer( );
    }
}

// RevoYawarakaD.MAP: size 0x30 (-O0 -inline off)
// RevoYawarakaR.MAP: size 0x4 (-O4,p -inline on)
// Must call MEMDumpHeap in debug, not in release
void Heap::dump( void )
{
    // This function doesn't exist on release
    // MEMDumpHeap( mHeapHandle );
}

void Heap::dumpAll( void )
{
    Heap *pHeap = NULL;
    u32 mem[ 2 ] = { 0, 0 };

    while( pHeap = reinterpret_cast< Heap * >( nw4r::ut::List_GetNext( &sHeapList, pHeap ) ) )
    {
        Heap *pParent = NULL;
        if( reinterpret_cast< u32 >( pHeap->getStartAddress( ) ) < 0x90000000 )
        {
            mem[ 0 ] += pHeap->getAllocatableSize( );
        }
        else
        {
            mem[ 1 ] += pHeap->getAllocatableSize( );
        }

        while( pParent = reinterpret_cast< Heap * >(
                       nw4r::ut::List_GetNext( &sHeapList, pParent ) ) )
        {
            if( pHeap->findParentHeap( ) == pParent )
            {
                break;
            }
        }
    }

    // Needed to prevent dumpAll from inlining in alloc
    static_cast< void >( mem );
    static_cast< void >( mem );
}

// RevoYawarakaD.MAP: size 0x30 (-O0 -inline off)
// RevoYawarakaR.MAP: size 0x8 (-O4,p -inline on)
// Must call MEMSetFillValForHeap in debug, not in release
u32 Heap::setFillVal( s32 type, u32 val )
{
    // This function doesn't exist on release
    // return MEMSetFillValForHeap( type, val );
    return 0;
}

// RevoYawarakaD.MAP: size 0x28 (-O0 -inline off)
// RevoYawarakaR.MAP: size 0x8 (-O4,p -inline on)
u32 Heap::getFillVal( s32 type )
{
    // This function doesn't exist on release
    // return MEMGetFillValForHeap( type );
    return 0;
}

// RevoYawarakaD.MAP: size 0x24 (-O0 -inline off)
// RevoYawarakaR.MAP: size 0x10 (-O4,p -inline on)
bool Heap::isOptDebugFill( void ) const
{
    // GetOptForHeap casts to u16 as well, and it's required for -O0
    return static_cast< u16 >( mHeapHandle->attribute.fields.optFlag ) & 2;
}

// RevoYawarakaD.MAP: size 0x38 (-O0 -inline off)
// RevoYawarakaR.MAP: size 0x10 (-O4,p -inline on)
void Heap::fillAllocMemory( void *memBlock, u32 size )
{
    // The function is too small to call getFillVal or MEMGetFillValForHeap
    // Assume the value is hardcoded to a number > 0xffff
    // The value provided is the default fill value from MEMGetFillValForHeap
    memset( memBlock, 0xf3f3f3f3, size );
}

Heap *Heap::becomeCurrentHeap( void )
{
    OSLockMutex( &sRootMutex );
    Heap *pOldHeap = sCurrentHeap;
    sCurrentHeap = this;
    OSUnlockMutex( &sRootMutex );
    return pOldHeap;
}

} // namespace EGG

void *operator new( size_t size )
{
    return EGG::Heap::alloc( size, 4, NULL );
}

void *operator new( size_t size, int align )
{
    return EGG::Heap::alloc( size, align, NULL );
}

void *operator new( size_t size, EGG::Heap *pHeap, int align )
{
    return EGG::Heap::alloc( size, align, pHeap );
}

void *operator new[]( size_t size )
{
    return EGG::Heap::alloc( size, 4, NULL );
}

void *operator new[]( size_t size, int align )
{
    return EGG::Heap::alloc( size, align, NULL );
}

void *operator new[]( size_t size, EGG::Heap *pHeap, int align )
{
    return EGG::Heap::alloc( size, align, pHeap );
}

void operator delete( void *memBlock )
{
    EGG::Heap::free( memBlock, NULL );
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
    (void)memBlock;
}

void operator delete[]( void *memBlock )
{
    EGG::Heap::free( memBlock, NULL );
}

namespace EGG
{

Heap *Heap::sCurrentHeap = NULL;
BOOL Heap::sIsHeapListInitialized = FALSE;
Heap *Heap::sAllocatableHeap = NULL;
Heap::ErrorCallback Heap::sErrorCallback = NULL;
Heap::AllocCallback Heap::sAllocCallback = NULL;
void *Heap::sErrorCallbackArg = NULL;
void *Heap::sAllocCallbackArg = NULL;
OSThread *Heap::sAllocatableThread = NULL;

nw4r::ut::List Heap::sHeapList;
OSMutex Heap::sRootMutex;

} // namespace EGG
