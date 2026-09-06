#ifndef EGG_HEAP_H
#define EGG_HEAP_H

#include <egg/core/eggDisposer.h>

#include <egg/prim/eggBitFlag.h>

#include <RVL_SDK/mem.h>
#include <RVL_SDK/os.h>

namespace EGG
{

struct HeapAllocArg
{
    // RevoYawarakaD.MAP: size 0x24 (-O0 -inline off)
    HeapAllocArg( void ) : arg( NULL ), size( 0 ), align( 0 ), heap( NULL ) { }

    void *arg;
    u32 size;
    int align;
    Heap *heap;
};

struct HeapErrorArg
{
    // RevoYawarakaD.MAP: size 0x14 (-O0 -inline off)
    HeapErrorArg( void ) : name( NULL ), arg( NULL ) { }

    const char *name;
    void *arg;
};

class Allocator;
class ExpHeap;

class Heap : Disposer
{
public:
    enum EHeapKind
    {
        HEAP_KIND_NONE,
        HEAP_KIND_EXPANDED,
        HEAP_KIND_FRAME,
        HEAP_KIND_UNIT,
        HEAP_KIND_ASSERT,
    };

    typedef void ( *AllocCallback )( const EGG::HeapAllocArg & );
    typedef void ( *ErrorCallback )( const EGG::HeapErrorArg & );

    Heap( MEMiHeapHead *handle );
    virtual ~Heap( void );
    virtual EHeapKind getHeapKind( void ) const = 0;
    virtual void initAllocator( Allocator *pAllocator, s32 align = 4 ) = 0;
    virtual void *alloc( u32 size, s32 align = 4 ) = 0;
    virtual void free( void *block ) = 0;
    virtual void destroy( void ) = 0;
    virtual u32 resizeForMBlock( void *block, u32 size ) = 0;
    virtual u32 getAllocatableSize( s32 align = 4 ) = 0;
    virtual u32 adjust( void ) = 0;

    Heap *findParentHeap( void );
    void dispose( void );
    void dump( void );
    // u32 getAllocatableSum( int align = 4 );
    u32 setFillVal( s32 type, u32 val );
    u32 getFillVal( s32 type );
    bool isOptDebugFill( void ) const;
    Heap *becomeCurrentHeap( void );
    // TODO: Needs DCStoreRange for implementation
    // Heap *_becomeCurrentHeapWithoutLock( void );

    static void initialize( void );
    static void *alloc( u32 size, int align, Heap *pHeap );
    static Heap *findHeap( MEMiHeapHead *handle );
    static Heap *findContainHeap( const void *memBlock );
    static void free( void *memBlock, Heap *pHeap );
    static void dumpAll( void );
    static void fillAllocMemory( void *memBlock, u32 size );

    /******************************************************************************
     *
     * Header-defined functions
     *
     ******************************************************************************/

    // RevoYawarakaD.MAP: size 0x8 (-O0 -inline off)
    static void *addOffset( void *start, u32 offset )
    {
        return reinterpret_cast< void * >( reinterpret_cast< u32 >( start ) + offset );
    }

    // RevoYawarakaD.MAP: size 0x34 (-O0 -inline off)
    // Must call nw4r::ut::List_Append
    void appendDisposer( Disposer *disposer )
    {
        nw4r::ut::List_Append( &mDisposerList, disposer );
    }

    // RevoYawarakaD.MAP: size 0x8 (-O0 -inline off)
    static void disableAllocationAllBut( Heap *pHeap )
    {
        sAllocatableHeap = pHeap;
    }

    // RevoYawarakaD.MAP: size 0x34 (-O0 -inline off)
    // Must call TBitFlag< u16 >::setBit
    void disableAllocation( void )
    {
        mFlags.setBit( 0 );
    }

    // RevoYawarakaD.MAP: size 0x50 (-O0 -inline off)
    static ExpHeap *dynamicCastToExp( Heap *pHeap )
    {
        if( pHeap->getHeapKind( ) == HEAP_KIND_EXPANDED )
        {
            return reinterpret_cast< ExpHeap * >( pHeap );
        }

        return NULL;
    }

    // RevoYawarakaD.MAP: size 0x34 (-O0 -inline off)
    // Must call TBitFlag< u16 >::resetBit
    void enableAllocation( void )
    {
        mFlags.resetBit( 0 );
    }

    // RevoYawarakaD.MAP: size 0x8 (-O0 -inline off)
    static Heap *getCurrentHeap( void )
    {
        return sCurrentHeap;
    }

    // RevoYawarakaD.MAP: size 0x30 (-O0 -inline off)
    // Must call MEMGetHeapEndAddress
    void *getEndAddress( void )
    {
        return MEMGetHeapEndAddress( mHeapHandle );
    }

    // RevoYawarakaD.MAP: size 0xc (-O0 -inline off)
    static const nw4r::ut::List *getHeapList( void )
    {
        return &sHeapList;
    }

    // RevoYawarakaD.MAP: size 0x8 (-O0 -inline off)
    const char *getName( void )
    {
        return mName;
    }

    // RevoYawarakaD.MAP: size 0x4 (-O0 -inline off)
    void *getStartAddress( void )
    {
        return this;
    }

    // RevoYawarakaD.MAP: size 0x48 (-O0 -inline off)
    s32 getTotalSize( void )
    {
        return reinterpret_cast< u32 >( getEndAddress( ) ) -
                reinterpret_cast< u32 >( getStartAddress( ) );
    }

    // static bool isHeapPointer( void *ptr );

    // RevoYawarakaD.MAP: size 0x8 (-O0 -inline off)
    void registerHeapBuffer( void *buffer )
    {
        mHeapBuffer = buffer;
    }

    // RevoYawarakaD.MAP: size 0x34 (-O0 -inline off)
    // Must call nw4r::ut::List_Remove
    void removeDisposer( Disposer *disposer )
    {
        nw4r::ut::List_Remove( &mDisposerList, disposer );
    }

    // RevoYawarakaD.MAP: size 0xc (-O0 -inline off)
    void setAllocCallback( AllocCallback callback, void *arg )
    {
        sAllocCallback = callback;
        sAllocCallbackArg = arg;
    }

    // RevoYawarakaD.MAP: size 0x8 (-O0 -inline off)
    void setAllocatableThread( OSThread *pThread )
    {
        sAllocatableThread = pThread;
    }

    // RevoYawarakaD.MAP: size 0xc (-O0 -inline off)
    void setErrorCallback( ErrorCallback callback, void *arg )
    {
        sErrorCallback = callback;
        sErrorCallbackArg = arg;
    }

    // RevoYawarakaD.MAP: size 0x8 (-O0 -inline off)
    void setName( const char *name )
    {
        mName = name;
    }

    // RevoYawarakaD.MAP: size 0x34 (-O0 -inline off)
    // Must call TBitFlag< u16 >::onBit
    bool tstDisableAllocation( void )
    {
        return mFlags.onBit( 0 );
    }

private:
    MEMiHeapHead *mHeapHandle;
    void *mHeapBuffer;
    Heap *mParentHeap;
    TBitFlag< u16 > mFlags;
    nw4r::ut::Link mHeapLink;
    nw4r::ut::List mDisposerList;
    const char *mName;

    static Heap *sCurrentHeap;
    static BOOL sIsHeapListInitialized;
    static Heap *sAllocatableHeap;
    static ErrorCallback sErrorCallback;
    static AllocCallback sAllocCallback;
    static void *sErrorCallbackArg;
    static void *sAllocCallbackArg;
    static OSThread *sAllocatableThread;

    static nw4r::ut::List sHeapList;
    static OSMutex sRootMutex;
};

} // namespace EGG

void *operator new( size_t size );
void *operator new( size_t size, int align );
void *operator new( size_t size, EGG::Heap *pHeap, int align = 4 );
void *operator new[]( size_t size );
void *operator new[]( size_t size, int align );
void *operator new[]( size_t size, EGG::Heap *pHeap, int align = 4 );
void operator delete( void *memBlock );
void operator delete[]( void *memBlock );

#endif
