/// \file RVL_SDK/private/memory.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [SC5PGN] Challenge Me: Word Puzzles
///
/// Header path: /RVL_SDK/include/private/memory.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_MEMORY_H
#define RVL_SDK_PRIVATE_MEMORY_H

#include <RVL_SDK/private/iostypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum
{
    IOS_HEAP_MAX = 8,
};

IOSHeapId iosCreateHeap( void *base, u32 size );
IOSError iosDestroyHeap( IOSHeapId hid );
void *iosAlloc( IOSHeapId hid, s32 size );
void *iosAllocAligned( IOSHeapId hid, s32 size, u32 align );
IOSError iosFree( IOSHeapId hid, void *ptr );

#ifdef __cplusplus
}
#endif

#endif
