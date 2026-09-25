/// \file RVL_SDK/private/iostypes.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [C2W] Wii U OSv0 Cafe2Wii/fw.img
///     [IOSU] Wii U OSv10-v15848/code/fw.img
///
/// Header path: /RVL_SDK/include/private/iostypes.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_IOSTYPES_H
#define RVL_SDK_PRIVATE_IOSTYPES_H

#include <RVL_SDK/types.h>

#include <RVL_SDK/private/ioserrno.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef s32 IOSError;
typedef u32 IOSIoctlCommand;

enum
{
    IOS_FD_INVALID = -1,
    IOS_HEAP_INVALID = -1,
};

typedef s32 IOSFd;
typedef s32 IOSHeapId;

// [C2W] DWARF
typedef u32 IOSTime;
typedef u64 IOSTime64;
typedef u32 IOSTicks;

// [IOSU] Strings referenced
enum // IOSCommand
{
    IOS_COMMAND_INVALID = 0,
    IOS_OPEN = 1,
    IOS_CLOSE = 2,
    IOS_READ = 3,
    IOS_WRITE = 4,
    IOS_SEEK = 5,
    IOS_IOCTL = 6,
    IOS_IOCTLV = 7,
    IOS_REPLY = 8,
    IOS_IPC_MSG = 9,
};
typedef s32 IOSCommand;

typedef u8 IOSPath[ 64 ];

#ifdef __cplusplus
}
#endif

#endif
