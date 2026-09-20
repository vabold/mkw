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

enum
{
    IPCREG_PPCMSG = 0,
    IPCREG_PPCCTRL = 1,
    IPCREG_IOPMSG = 2,
    IPCREG_IOPCTRL = 3,
};

/******************************************************************************
 *
 * ipcMain.c
 *
 ******************************************************************************/

void IPCInit( void );
void IPCReInit( void );
u32 IPCReadReg( u32 ipcReg );
void IPCWriteReg( u32 ipcReg, u32 regVal );
void *IPCGetBufferHi( void );
void *IPCGetBufferLo( void );
void IPCSetBufferHi( void *newHi );
void IPCSetBufferLo( void *newLo );

/******************************************************************************
 *
 * ipcclt.c
 *
 ******************************************************************************/

IOSError IPCCltInit( void );
IOSError IPCCltReInit( void );

/******************************************************************************
 *
 * ipcProfile.c
 *
 ******************************************************************************/

u32 IPCGetNumPendingReqs( void );
u32 IPCGetNumUnIssuedReqs( void );
IOSError IPCGetQueueStatus( u32 );

#ifdef __cplusplus
}
#endif

#endif
