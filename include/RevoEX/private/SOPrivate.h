/// \file RevoEX/private/SOPrivate.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [RDCE78] Deadly Creatures
///     [R3RE8P] Sonic & SEGA All-Stars Racing
///
/// Header path: /RevoEX/include/private/SOPrivate.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef REVOEX_SOPRIVATE_H
#define REVOEX_SOPRIVATE_H

#include <RVL_SDK/types.h>
#include <RevoEX/so.h>

#include <RevoEX/private/SOInet6.h>

EXTERN_C_BEGIN

// [RDCE78]/DeadlyCreatures_Debug.elf DWARF
typedef struct SOSysWork
{
    SOAllocFunc alloc;
    SOFreeFunc free;
    s32 rmState;
    s32 rmFd;
    SOResolver *pResolver;
    s32 allocCount;
} SOSysWork;

// SOCommon.c

SOSysWork *SOiGetSysWork( void );                                          // [R3RE8P]
BOOL SOiIsBufferAddrCheck( void );                                         // [RDCE78] DWARF
BOOL SOiIsInitialized( void );                                             // [R3RE8P]
void *SOiAlloc( u32 name, s32 size );                                      // [RDCE78] DWARF
void SOiFree( u32 name, void *ptr, s32 size );                             // [RDCE78] DWARF
int SOiPrepare( const char *funcName, s32 *pRmId );                        // [RDCE78] DWARF*
int SOiConclude( const char *funcName, int result );                       // [RDCE78] DWARF*
int SOiPrepareTempRm( const char *funcName, s32 *pRmId, BOOL *pIsTempRm ); // [RDCE78] DWARF
int SOiConcludeTempRm( const char *funcName, int result, BOOL isTempRm );  // [RDCE78] DWARF
// Not found: SOiWaitForDHCP
int SOiWaitForDHCPEx( int timeOut ); // [RDCE78] DWARF

// SOBasic.c

int __SOCreateSocket( int pf, int type, int protocol ); // [RDCE78] DWARF

EXTERN_C_END

#endif
