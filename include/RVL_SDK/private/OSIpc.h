/// \file RVL_SDK/private/OSIpc.h
///
/// Sources:
///     [RJTJ01] Minna no Joushiki Ryoku TV
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_OS_IPC_H
#define RVL_SDK_PRIVATE_OS_IPC_H

#ifdef __cplusplus
extern "C"
{
#endif

void *__OSGetIPCBufferHi( void );
void *__OSGetIPCBufferLo( void );
void __OSInitIPCBuffer( void );

#ifdef __cplusplus
}
#endif

#endif
