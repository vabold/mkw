#ifndef RVL_SDK_MEM_HEAP_COMMON_H
#define RVL_SDK_MEM_HEAP_COMMON_H

#include <RVL_SDK/mem/list.h>

#include <RVL_SDK/os/OSMutex.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum MEMHeapType
{
    MEM_HEAP_TYPE_EXP,
    MEM_HEAP_TYPE_FRM,
    MEM_HEAP_TYPE_UNIT,
    MEM_HEAP_TYPE_UNKNOWN,
} MEMHeapType;

typedef struct MEMiHeapHead
{
    u32 signature;
    MEMLink link;
    MEMList childList;
    void *heapStart;
    void *heapEnd;
    OSMutex mutex;
    union
    {
        u32 val;
        struct
        {
            u32 _reserved : 24;
            u32 optFlag : 8;
        } fields;
    } attribute;
} MEMiHeapHead;

void MEMiInitHeapHead( MEMiHeapHead *heap,
        u32 signature,
        void *startAddress,
        void *endAddress,
        u16 opt );
void MEMiFinalizeHeap( MEMiHeapHead *heap );
void MEMiDumpHeapHead( MEMiHeapHead *heap );
MEMiHeapHead *MEMFindContainHeap( const void *block );
MEMiHeapHead *MEMFindParentHeap( MEMiHeapHead *heap );

static inline s32 MEMGetHeapTotalSize( MEMiHeapHead *heap )
{
    return (u32)heap->heapEnd - (u32)heap;
}

static inline s32 MEMGetHeapTotalUsableSize( MEMiHeapHead *heap )
{
    return (u32)heap->heapEnd - (u32)heap->heapStart;
}

static inline MEMHeapType MEMGetHeapType( MEMiHeapHead *heap )
{
    switch( heap->signature )
    {
    case 'EXPH':
        return MEM_HEAP_TYPE_EXP;
    case 'FRMH':
        return MEM_HEAP_TYPE_FRM;
    case 'UNTH':
        return MEM_HEAP_TYPE_UNIT;
    default:
        return MEM_HEAP_TYPE_UNKNOWN;
    }
}

#ifdef __cplusplus
}
#endif

#endif
