/// \file RVL_SDK/private/ipc.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [RJTJ01] Minna no Joushiki Ryoku TV
///     [SC5PGN] Challenge Me: Word Puzzles
///
/// Header path: /RVL_SDK/include/private/ipc.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_IPC_H
#define RVL_SDK_PRIVATE_IPC_H

#include <RVL_SDK/private/iosresclt.h>
#include <RVL_SDK/private/iostypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 *
 * ipcMain.c
 *
 ******************************************************************************/

s32 IPCInit( void );
s32 IPCReInit( void );
u32 IPCReadReg( u32 reg );
void IPCWriteReg( u32 reg, u32 value );
void *IPCGetBufferHi( void );
void *IPCGetBufferLo( void );
void IPCSetBufferHi( void *newHi );
void IPCSetBufferLo( void *newLo );

/******************************************************************************
 *
 * ipcclt.c
 *
 ******************************************************************************/

s32 IPCCltInit( void );
s32 IPCCltReInit( void );

/******************************************************************************
 *
 * ipcProfile.c
 *
 ******************************************************************************/

u32 IPCGetNumPendingReqs( void );
u32 IPCGetNumUnIssuedReqs( void );
s32 IPCGetQueueStatus( u32 );

#ifdef __cplusplus
}
#endif

#endif
