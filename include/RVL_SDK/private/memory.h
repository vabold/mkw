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
#include <RVL_SDK/types.h>

EXTERN_C_BEGIN

s32 iosCreateHeap( void *base, u32 size );
s32 iosDestroyHeap( s32 hid );
void *iosAlloc( s32 hid, s32 size );
void *iosAllocAligned( s32 hid, s32 size, u32 align );
s32 iosFree( s32 hid, void *ptr );

EXTERN_C_END

#endif
