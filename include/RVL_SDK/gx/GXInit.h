// NOTE: This header name is wrong

#ifndef RVL_SDK_GX_INIT_H
#define RVL_SDK_GX_INIT_H

#include <RVL_SDK/gx/GXStruct.h>

#ifdef __cplusplus
extern "C"
{
#endif

BOOL IsWriteGatherBufferEmpty( void );
GXFifoObj *GXInit( void *base, u32 size );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_INIT_H
