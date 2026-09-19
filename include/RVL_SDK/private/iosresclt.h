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

s32 IOS_OpenAsync( const char *path, u32 flags, IOSIoCallbackFunc callback, void *userData );
s32 IOS_Open( const char *path, u32 flags );
s32 IOS_CloseAsync( s32 fd, IOSIoCallbackFunc callback, void *userData );
s32 IOS_Close( s32 fd );
s32 IOS_ReadAsync( s32 fd, u8 *outPtr, s32 outLen, IOSIoCallbackFunc callback, void *userData );
s32 IOS_Read( s32 fd, u8 *outPtr, u32 outLen );
s32 IOS_WriteAsync( s32 fd, u8 *inPtr, s32 inLen, IOSIoCallbackFunc callback, void *userData );
s32 IOS_Write( s32 fd, u8 *inPtr, s32 inLen );
s32 IOS_SeekAsync( s32 fd, s32 offset, s32 whence, IOSIoCallbackFunc callback, void *userData );
s32 IOS_Seek( s32 fd, s32 offset, s32 whence );
s32 IOS_IoctlAsync( s32 fd,
        u32 cmd,
        u8 *inPtr,
        u32 inLen,
        u8 *outPtr,
        u32 outLen,
        IOSIoCallbackFunc callback,
        void *userData );
s32 IOS_Ioctl( s32 fd, u32 cmd, u8 *inPtr, u32 inLen, u8 *outPtr, u32 outLen );
s32 IOS_IoctlvAsync( s32 fd,
        u32 cmd,
        u32 readCount,
        u32 writeCount,
        IOSIoVector *vector,
        IOSIoCallbackFunc callback,
        void *userData );
s32 IOS_Ioctlv( s32 fd, u32 cmd, u32 readCount, u32 writeCount, IOSIoVector *vector );
s32 IOS_IoctlvReboot( s32 fd, u32 cmd, u32 readCount, u32 writeCount, IOSIoVector *vector );

#ifdef __cplusplus
}
#endif

#endif
