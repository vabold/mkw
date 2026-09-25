/// \file RVL_SDK/private/acr.h
///
/// Sources:
///     [RDCE78] Deadly Creatures
///     [IOS36] IOS36.15.24 firmware.64.1109301041
///     [IOSU] Wii U OSv10-v15848/code/fw.img
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_ACR_H
#define RVL_SDK_PRIVATE_ACR_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __MWERKS__
extern u32 __ACRReg[ 0x100 ] : 0xCD000000;
#else
#define __ACRReg ( (u32 *)0xCD000000 )
#endif

// [IOS36]:STM "ACRPLLSYS = %08X\n"
// [IOS36]:STM "ACRPLLSYSEXT = %08X\n"
// [IOSU] "WDGINTSTS=0x%08x.\n"
/// ACR registers
enum
{
    ACRIPCPPCMSG = 0x000,
    ACRIPCPPCCTRL = 0x004,
    ACRIPCIOPMSG = 0x008,
    ACRIPCIOPCTRL = 0x00c,

    ACRPPCIRQSTS = 0x030,
    ACRPPCIRQEN = 0x034,

    ACRWDGINTSTS = 0x048,

    ACRPLLSYS = 0x1b0,
    ACRPLLSYSEXT = 0x1b4,
};

/// ACRIPCxxxCTRL bits
enum
{
    ACRIPCCTRL_SENDMSG = 0x1,
    ACRIPCCTRL_RECVACKSTS = 0x2,
    ACRIPCCTRL_RECVMSGSTS = 0x4,
    ACRIPCCTRL_SENDACK = 0x8,
    ACRIPCCTRL_RECVMSGINTEN = 0x10,
    ACRIPCCTRL_RECVACKINTEN = 0x20,
};

/// ACR IRQ flags
enum
{
    ACRIRQFL_IPCPPC = 0x40000000,
};

// [RDCE78]
static void ACRWriteReg( u32 reg, u32 value )
{
    __ACRReg[ reg >> 2 ] = value;
}

#ifdef __cplusplus
}
#endif

#endif
