// NOTE: This header name is wrong

#ifndef RVL_SDK_GX_INIT_H
#define RVL_SDK_GX_INIT_H

#include <RVL_SDK/gx/GXStruct.h>
#include <RVL_SDK/types.h>

EXTERN_C_BEGIN

BOOL IsWriteGatherBufferEmpty( void );
GXFifoObj *GXInit( void *base, u32 size );

EXTERN_C_END

#endif // RVL_SDK_GX_INIT_H
