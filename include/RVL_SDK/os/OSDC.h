/// \file RVL_SDK/os/OSDC.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// Header path: /RVL_SDK/include/revolution/os/OSDC.h [SSDDRV] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_DC_H
#define RVL_SDK_OS_DC_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

void DCInvalidateRange( void *addr, u32 nBytes );
void DCFlushRange( void *addr, u32 nBytes );
void DCStoreRange( void *addr, u32 nBytes );
void DCFlushRangeNoSync( void *addr, u32 nBytes );
void DCStoreRangeNoSync( void *addr, u32 nBytes );
void DCZeroRange( void *addr, u32 nBytes );
void DCTouchRange( void *addr, u32 nBytes );

#ifdef __cplusplus
}
#endif

#endif
