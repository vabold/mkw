/// \file RVL_SDK/ipc/ipcMain.c
///
/// Sources:
///     [RJTJ01] Minna no Joushiki Ryoku TV
///     [RDCE78] Deadly Creatures
///     [SC5PGN] Challenge Me: Word Puzzles
///
/// SPDX-License-Identifier: CC0-1.0

#include <RVL_SDK/os.h>
#include <RVL_SDK/private/OSIpc.h>
#include <RVL_SDK/private/acr.h>
#include <RVL_SDK/private/ipc.h>

static void *IPCBufferHi;
static void *IPCBufferLo;
static void *IPCCurrentBufferHi;
static void *IPCCurrentBufferLo;
static u8 Initialized;

void IPCInit( void )
{
    if( Initialized == FALSE )
    {
        IPCBufferHi = __OSGetIPCBufferHi( );
        IPCBufferLo = __OSGetIPCBufferLo( );
        IPCCurrentBufferHi = IPCBufferHi;
        IPCCurrentBufferLo = IPCBufferLo;
        Initialized = TRUE;
    }
}

void IPCReInit( void )
{
    Initialized = FALSE;
    IPCInit( );
}

u32 IPCReadReg( u32 ipcReg )
{
    return __ACRReg[ ipcReg ];
}

void IPCWriteReg( u32 ipcReg, u32 regVal )
{
    __ACRReg[ ipcReg ] = regVal;
}

void *IPCGetBufferHi( void )
{
    return IPCCurrentBufferHi;
}

void *IPCGetBufferLo( void )
{
    return IPCCurrentBufferLo;
}

void IPCSetBufferHi( void *newHi )
{
    OSAssert( newHi <= IPCBufferHi );
    IPCCurrentBufferHi = newHi;
}

void IPCSetBufferLo( void *newLo )
{
    OSAssert( IPCBufferLo <= newLo );
    IPCCurrentBufferLo = newLo;
}
