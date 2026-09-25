/// \file RVL_SDK/os/OSIC.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// Header path: /RVL_SDK/include/revolution/os/OSIC.h [SSDDRV] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_IC_H
#define RVL_SDK_OS_IC_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

void ICInvalidateRange( void *addr, u32 nBytes );
void ICFlashInvalidate( void );
void ICEnable( void );
void ICDisable( void );
void ICFreeze( void );
void ICUnfreeze( void );
void ICBlockInvalidate( void *addr );
void ICSync( void );

#ifdef __cplusplus
}
#endif

#endif
