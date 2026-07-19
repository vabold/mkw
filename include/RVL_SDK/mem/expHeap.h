#ifndef RVL_SDK_MEM_EXP_HEAP_H
#define RVL_SDK_MEM_EXP_HEAP_H

#include <RVL_SDK/mem/heapCommon.h>

#ifdef __cplusplus
extern "C"
{
#endif

MEMiHeapHead *MEMCreateExpHeapEx( void *startAddress, u32 size, u16 opt );
MEMiHeapHead *MEMDestroyExpHeap( MEMiHeapHead *heap );
void *MEMAllocFromExpHeapEx( MEMiHeapHead *heap, u32 size, s32 alignment );
void MEMResizeForMBlockExpHeap( MEMiHeapHead *heap, void *memBlock, u32 size );
void MEMFreeToExpHeap( MEMiHeapHead *heap, void *memBlock );
u32 MEMGetTotalFreeSizeForExpHeap( MEMiHeapHead *heap );
u32 MEMGetAllocatableSizeForExpHeapEx( MEMiHeapHead *heap, s32 alignment );
BOOL MEMiIsEmptyExpHeap( MEMiHeapHead *heap );
u16 MEMSetAllocModeForExpHeap( MEMiHeapHead *heap, u16 allocMode );
u16 MEMGetAllocModeForExpHeap( MEMiHeapHead *heap );
BOOL MEMUseMarginOfAlignmentForExpHeap( MEMiHeapHead *heap, BOOL useMargin );
u16 MEMSetGroupIDForExpHeap( MEMiHeapHead *heap, u16 groupID );
u16 MEMGetGroupIDForExpHeap( MEMiHeapHead *heap );
void MEMVisitAllocatedForExpHeap( MEMiHeapHead *heap,
        void ( *visitor )( void *memBlock, MEMiHeapHead *heap, u32 param ),
        u32 param );
u32 MEMGetSizeForMBlockExpHeap( const void *memBlock );
u16 MEMGetGroupIDForMBlockExpHeap( const void *memBlock );
u16 MEMGetAllocDirForMBlockExpHeap( const void *memBlock );
u32 MEMAdjustExpHeap( MEMiHeapHead *heap );

static inline MEMiHeapHead *MEMCreateExpHeap( void *startAddress, u32 size )
{
    return MEMCreateExpHeapEx( startAddress, size, 0 );
}

static inline void *MEMAllocFromExpHeap( MEMiHeapHead *heap, u32 size )
{
    return MEMAllocFromExpHeapEx( heap, size, 4 );
}

static inline u32 MEMGetAllocatableSizeForExpHeap( MEMiHeapHead *heap )
{
    return MEMGetAllocatableSizeForExpHeapEx( heap, 4 );
}

#ifdef __cplusplus
}
#endif

#endif
