/// \file RVL_SDK/os/OSL2.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// Header path: /RVL_SDK/include/revolution/os/OSL2.h [SSDDRV] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_L2_H
#define RVL_SDK_OS_L2_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

void L2Enable( void );
void L2Disable( void );
void L2GlobalInvalidate( void );
void L2SetDataOnly( BOOL dataOnly );
void L2SetWriteThrough( BOOL writeThrough );

#ifdef __cplusplus
}
#endif

#endif
