#ifndef RVL_SDK_MEM_ALLOCATOR_H
#define RVL_SDK_MEM_ALLOCATOR_H

#include <RVL_SDK/mem/heapCommon.h>

#ifdef __cplusplus
extern "C"
{
#endif

// TODO: This belongs elsewhere
typedef int OSHeapHandle;

typedef struct MEMAllocator MEMAllocator;

typedef struct MEMAllocatorFunc
{
    void *( *pfAlloc )( MEMAllocator *pAllocator, u32 size );
    void ( *pfFree )( MEMAllocator *pAllocator, void *memBlock );
} MEMAllocatorFunc;

struct MEMAllocator
{
    const MEMAllocatorFunc *pFunc;
    void *pHeap;
    u32 heapParam1;
    u32 heapParam2;
};

void *MEMAllocFromAllocator( MEMAllocator *pAllocator, u32 size );
void MEMFreeToAllocator( MEMAllocator *pAllocator, void *memBlock );
void MEMInitAllocatorForExpHeap( MEMAllocator *pAllocator, MEMiHeapHead *pHeap, int alignment );
void MEMInitAllocatorForFrmHeap( MEMAllocator *pAllocator, MEMiHeapHead *pHeap, int alignment );
void MEMInitAllocatorForUnitHeap( MEMAllocator *pAllocator, MEMiHeapHead *pHeap );
void MEMInitAllocatorForOSHeap( MEMAllocator *pAllocator, OSHeapHandle heap );

#ifdef __cplusplus
}
#endif

#endif
