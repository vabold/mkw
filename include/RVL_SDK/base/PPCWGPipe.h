#ifndef RVL_SDK_BASE_PPCWGPIPE_H
#define RVL_SDK_BASE_PPCWGPIPE_H

#include <RVL_SDK/types.h>

EXTERN_C_BEGIN

typedef union uPPCWGPipe
{
    u8 u8;
    u16 u16;
    u32 u32;
    u64 u64;
    s8 s8;
    s16 s16;
    s32 s32;
    s64 s64;
    f32 f32;
    f64 f64;
} PPCWGPipe;

EXTERN_C_END

#endif // RVL_SDK_BASE_PPCWGPIPE_H
