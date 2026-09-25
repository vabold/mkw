/// \file RVL_SDK/private/ioserrno.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [IOS9A] IOS9.0.1 from "Insert Startup Disc" Wii
///             (Boot Content SHA-1: 9dce75d14e01f6efc8d56821c139490792b8b3f9)
///     [IOSU] Wii U OSv10-v15848/code/fw.img
///
/// Header path: /RVL_SDK/include/private/ioserrno.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_IOSERRNO_H
#define RVL_SDK_PRIVATE_IOSERRNO_H

#ifdef __cplusplus
extern "C"
{
#endif

// [IOS9A]:segment_19(NCD.data):0x0 (0x13d6a000)
enum
{
    IOS_ERROR_OK = 0,
    IOS_ERROR_ACCESS = -1,
    IOS_ERROR_EXISTS = -2,
    IOS_ERROR_INTR = -3,
    IOS_ERROR_INVALID = -4,
    IOS_ERROR_MAX = -5,
    IOS_ERROR_NOEXISTS = -6,
    IOS_ERROR_QEMPTY = -7,
    IOS_ERROR_QFULL = -8,
    IOS_ERROR_UNKNOWN = -9,
    IOS_ERROR_NOTREADY = -10,
    IOS_ERROR_ECC = -11,
    IOS_ERROR_ECC_CRIT = -12,
    IOS_ERROR_BADBLOCK = -13,
    IOS_ERROR_INVALID_OBJTYPE = -14,
    IOS_ERROR_INVALID_RNG = -15,
    IOS_ERROR_INVALID_FLAG = -16,
    IOS_ERROR_INVALID_FORMAT = -17,
    IOS_ERROR_INVALID_VERSION = -18,
    IOS_ERROR_INVALID_SIGNER = -19,
    IOS_ERROR_FAIL_CHECKVALUE = -20,
    IOS_ERROR_FAIL_INTERNAL = -21,
    IOS_ERROR_FAIL_ALLOC = -22,
    IOS_ERROR_INVALID_SIZE = -23,
};

#ifdef __cplusplus
}
#endif

#endif
