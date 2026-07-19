#ifndef RVL_SDK_MEM_FRAME_HEAP_H
#define RVL_SDK_MEM_FRAME_HEAP_H

#include <RVL_SDK/mem/heapCommon.h>

#ifdef __cplusplus
extern "C"
{
#endif

void *MEMiGetFreeStartForFrmHeap( MEMiHeapHead *heap );
void *MEMiGetFreeEndForFrmHeap( MEMiHeapHead *heap );
MEMiHeapHead *MEMCreateFrmHeapEx( void *startAddress, u32 size, u16 opt );
MEMiHeapHead *MEMDestroyFrmHeap( MEMiHeapHead *heap );
void *MEMAllocFromFrmHeapEx( MEMiHeapHead *heap, u32 size, s32 alignment );
void MEMFreeToFrmHeap( MEMiHeapHead *heap, u32 flags );
u32 MEMGetAllocatableSizeForFrmHeapEx( MEMiHeapHead *heap, s32 alignment );
BOOL MEMRecordStateForFrmHeap( MEMiHeapHead *heap, u32 tag );
BOOL MEMFreeByStateToFrmHeap( MEMiHeapHead *heap, u32 tag );
u32 MEMAdjustFrmHeap( MEMiHeapHead *heap );
void MEMResizeForMBlockFrmHeap( MEMiHeapHead *heap, void *memBlock, u32 size );

static inline MEMiHeapHead *MEMCreateFrmHeap( void *startAddress, u32 size )
{
    return MEMCreateFrmHeapEx( startAddress, size, 0 );
}

static inline void *MEMAllocFromFrmHeap( MEMiHeapHead *heap, u32 size )
{
    return MEMAllocFromFrmHeapEx( heap, size, 4 );
}

static inline u32 MEMGetAllocatableSizeForFrmHeap( MEMiHeapHead *heap )
{
    return MEMGetAllocatableSizeForFrmHeapEx( heap, 4 );
}

#ifdef __cplusplus
}
#endif

#endif
