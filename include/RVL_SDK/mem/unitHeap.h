#ifndef RVL_SDK_MEM_UNIT_HEAP_H
#define RVL_SDK_MEM_UNIT_HEAP_H

#include <RVL_SDK/mem/heapCommon.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct MEMiUnitHeapExt
{
    u8 _0[ 0x4 - 0x0 ];
    u32 memBlockSize;
} MEMiUnitHeapExt;

typedef struct MEMiUnitHeapHead
{
    MEMiHeapHead base;
    MEMiUnitHeapExt ext;
} MEMiUnitHeapHead;

MEMiHeapHead *
MEMCreateUnitHeapEx( void *startAddress, u32 heapSize, u32 memBlockSize, s32 alignment, u16 opt );
MEMiHeapHead *MEMDestroyUnitHeap( MEMiHeapHead *heap );
void *MEMAllocFromUnitHeap( MEMiHeapHead *heap );
void MEMFreeToUnitHeap( MEMiHeapHead *heap, void *memBlock );
u32 MEMCountFreeBlockForUnitHeap( MEMiHeapHead *heap );
u32 MEMCalcHeapSizeForUnitHeap( u32 memBlockSize, u32 memBlockCount, s32 alignment );

static inline MEMiHeapHead *MEMCreateUnitHeap( void *startAddress, u32 heapSize, u32 memBlockSize )
{
    return MEMCreateUnitHeapEx( startAddress, heapSize, memBlockSize, 4, 0 );
}

static inline u32 MEMGetMemBlockSizeForUnitHeap( MEMiHeapHead *heap )
{
    return ( (MEMiUnitHeapHead *)heap )->ext.memBlockSize;
}

#ifdef __cplusplus
}
#endif

#endif
