/// \file RVL_SDK/os/OSInterrupt.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// Header path: /RVL_SDK/include/revolution/os/OSInterrupt.h [SSDDRV] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_INTERRUPT_H
#define RVL_SDK_OS_INTERRUPT_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct OSContext OSContext;

typedef void ( *__OSInterruptHandler )( s16 interrupt, OSContext *context );

BOOL OSDisableInterrupts( );
BOOL OSEnableInterrupts( );
BOOL OSRestoreInterrupts( BOOL level );
u32 OSGetInterruptMask( void );
u32 OSSetInterruptMask( u32 local );

__OSInterruptHandler __OSSetInterruptHandler( s16 interrupt, __OSInterruptHandler handler );
__OSInterruptHandler __OSGetInterruptHandler( s16 interrupt );
void __OSInterruptInit( void );
u32 __OSMaskInterrupts( u32 global );
u32 __OSUnmaskInterrupts( u32 global );
void __OSDispatchInterrupt( OSContext *context );

#ifdef __cplusplus
}
#endif

#endif
