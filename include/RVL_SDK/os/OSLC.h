/// \file RVL_SDK/os/OSLC.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// Header path: /RVL_SDK/include/revolution/os/OSLC.h [SSDDRV] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_LC_H
#define RVL_SDK_OS_LC_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

void LCEnable( void );
void LCDisable( void );
void LCAllocOneTag( BOOL invalidate, void *tag );
void LCAllocTags( BOOL invalidate, void *startTag, u32 numBlocks );
void LCLoadBlocks( void *destTag, void *srcAddr, u32 numBlocks );
void LCStoreBlocks( void *destAddr, void *srcTag, u32 numBlocks );
void LCAlloc( void *addr, u32 nBytes );
void LCAllocNoInvalidate( void *addr, u32 nBytes );
u32 LCLoadData( void *destAddr, void *srcAddr, u32 nBytes );
u32 LCStoreData( void *destAddr, void *srcAddr, u32 nBytes );
u32 LCQueueLength( void );
void LCQueueWait( u32 len );
void LCFlushQueue( void );

#ifdef __cplusplus
}
#endif

#endif
