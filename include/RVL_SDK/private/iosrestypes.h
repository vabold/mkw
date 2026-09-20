/// \file RVL_SDK/private/iosrestypes.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [IOS9A] IOS9.0.1 from "Insert Startup Disc" Wii
///             (Boot Content SHA-1: 9dce75d14e01f6efc8d56821c139490792b8b3f9)
///     [IOS21] IOS21.5.15 firmware.64.1109301023
///     [IOSU] Wii U OSv10-v15848/code/fw.img
///
/// Header path: /RVL_SDK/include/private/iosrestypes.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_IOSRESTYPES_H
#define RVL_SDK_PRIVATE_IOSRESTYPES_H

#include <RVL_SDK/private/iostypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

// [SDLE78]/DtoL_Debug_Wii.elf DWARF (typedef name confirmed)
typedef struct
{
    u8 *base;
    u32 length;
} IOSIoVector;

// Notable strings:
// [IOS21] "IPC: failed open path check: path=%s len=%d\n"
// [IOS21] "IOS_OPEN(flags = 0x%08x): Invalid flags."
// [IOS21] "(%s) (diIoctl) ioctlMesg->cmd is DI_READ_CMD\n"
// [IOS21] "Invalid whence parameter (%d)"
// [IOS21] "Dispatch switch ERROR: %d cmd: %d\n"
// [IOS9A] "IOS_IsValidIob((IOSIobuf *)args->inPtr) == IOS_ERROR_OK"
// [IOSU] "IOS_READ   outLen:%08x outPtr:%08x"
// [IOSU] "IOS_WRITE  inLen:%08x inPtr:%08x"
// [IOSU] "IOS_IOCTL  cmd:%08x inLen:%08x inPtr:%08x outLen:%08x outPtr:%08x"
// [IOSU] "IOS_IOCTLV cmd:%08x readCount:%08x writeCount:%08x vector:%08x"
// [IOSU] "Failed at %s(%d): p_b->rm_request.handle == p_t->client_handle"
// [IOSU] "Failed at %s(%d): p_b->rm_request.args.ioctl.inPtr == (void*)p_t"
// [IOSU] "ISFS: %s(%d)Invalid offset %d, whence %d with file size %d"

typedef struct
{
    u8 *path;
    u32 flags;

    // IPC server-side only
    u32 uid;
    u16 gid;
} IOSIoRequestOpen;

typedef struct
{
    u8 *outPtr;
    u32 outLen;
} IOSIoRequestRead;

typedef struct
{
    u8 *inPtr;
    u32 inLen;
} IOSIoRequestWrite;

typedef struct
{
    s32 offset;
    s32 whence;
} IOSIoRequestSeek;

typedef struct
{
    u32 cmd;
    u8 *inPtr;
    u32 inLen;
    u8 *outPtr;
    u32 outLen;
} IOSIoRequestIoctl;

typedef struct
{
    u32 cmd;
    u32 readCount;
    u32 writeCount;
    IOSIoVector *vector;
} IOSIoRequestIoctlv;

typedef union
{
    IOSIoRequestOpen open;
    IOSIoRequestRead read;
    IOSIoRequestWrite write;
    IOSIoRequestSeek seek;
    IOSIoRequestIoctl ioctl;
    IOSIoRequestIoctlv ioctlv;
} IOSIoRequestArgs;

typedef struct
{
    u32 cmd;
    s32 status;
    IOSFd handle;
    IOSIoRequestArgs args;
} IOSIoRequest;

#ifdef __cplusplus
}
#endif

#endif
