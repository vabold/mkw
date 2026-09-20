/// \file RVL_SDK/private/iosresclt.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [RJTJ01] Minna no Joushiki Ryoku TV
///
/// Header path: /RVL_SDK/include/private/iosresclt.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_IOSRESCLT_H
#define RVL_SDK_PRIVATE_IOSRESCLT_H

#include <RVL_SDK/private/iosrestypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Note: iosresclt means IOS Resource Client

typedef void ( *IOSIoCallbackFunc )( s32 result, void *userData );

IOSError IOS_OpenAsync( u8 *path, u32 flags, IOSIoCallbackFunc callback, void *userData );
IOSFd IOS_Open( u8 *path, u32 flags );
IOSError IOS_CloseAsync( IOSFd fd, IOSIoCallbackFunc callback, void *userData );
IOSError IOS_Close( IOSFd fd );
IOSError
IOS_ReadAsync( IOSFd fd, u8 *outPtr, s32 outLen, IOSIoCallbackFunc callback, void *userData );
IOSError IOS_Read( IOSFd fd, u8 *outPtr, u32 outLen );
IOSError
IOS_WriteAsync( IOSFd fd, u8 *inPtr, s32 inLen, IOSIoCallbackFunc callback, void *userData );
IOSError IOS_Write( IOSFd fd, u8 *inPtr, s32 inLen );
IOSError
IOS_SeekAsync( IOSFd fd, s32 offset, s32 whence, IOSIoCallbackFunc callback, void *userData );
IOSError IOS_Seek( IOSFd fd, s32 offset, s32 whence );
IOSError IOS_IoctlAsync( IOSFd fd,
        u32 cmd,
        u8 *inPtr,
        u32 inLen,
        u8 *outPtr,
        u32 outLen,
        IOSIoCallbackFunc callback,
        void *userData );
IOSError IOS_Ioctl( IOSFd fd, u32 cmd, u8 *inPtr, u32 inLen, u8 *outPtr, u32 outLen );
IOSError IOS_IoctlvAsync( IOSFd fd,
        u32 cmd,
        u32 readCount,
        u32 writeCount,
        IOSIoVector *vector,
        IOSIoCallbackFunc callback,
        void *userData );
IOSError IOS_Ioctlv( IOSFd fd, u32 cmd, u32 readCount, u32 writeCount, IOSIoVector *vector );
IOSError IOS_IoctlvReboot( IOSFd fd, u32 cmd, u32 readCount, u32 writeCount, IOSIoVector *vector );

#ifdef __cplusplus
}
#endif

#endif
