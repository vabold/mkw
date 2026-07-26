/// \file RVL_SDK/os/OSContext.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///     [GZ2E01] The Legend of Zelda: Twilight Princess
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_CONTEXT_H
#define RVL_SDK_OS_CONTEXT_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001ABC
typedef struct OSContext
{
    u32 gpr[ 32 ];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;

    f64 fpr[ 32 ];
    u32 fpscr_pad;
    u32 fpscr;

    u32 ssr0;
    u32 ssr1;
    u16 mode;
    u16 state;

    u32 gqr[ 8 ];
    u32 psf_pad;
    f64 psf[ 32 ];
} OSContext;

void OSLoadFPUContext( OSContext *fpucontext );
void OSSaveFPUContext( OSContext *fpucontext );
void OSSetCurrentContext( OSContext *context );
OSContext *OSGetCurrentContext( void );
u32 OSSaveContext( OSContext *context );
void OSLoadContext( OSContext *context );
u32 OSGetStackPointer( void );
u32 OSSwitchStack( u32 newsp );

/// TODO: int? BOOL? Other typedef?
int OSSwitchFiber( u32 pc, u32 newsp );
/// [GZ2E01]/frameworkF.map
/// NOTE: Expecting same return type as OSSwitchFiber
int OSSwitchFiberEx( u32, u32, u32, u32, u32 pc, u32 newsp );

void OSClearContext( OSContext *context );
void OSInitContext( OSContext *context, u32 pc, u32 newsp );
void OSDumpContext( OSContext *context );
void __OSContextInit( void );
void OSFillFPUContext( OSContext *context );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_OS_CONTEXT_H
