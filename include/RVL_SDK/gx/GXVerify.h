#ifndef RVL_SDK_GX_VERIFY_H
#define RVL_SDK_GX_VERIFY_H

#include <RVL_SDK/gx/GXStruct.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXSetVerifyLevel( u32 );
GXVerifyCallback GXSetVerifyCallback( GXVerifyCallback callback );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_VERIFY_H
