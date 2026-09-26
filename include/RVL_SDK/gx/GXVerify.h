#ifndef RVL_SDK_GX_VERIFY_H
#define RVL_SDK_GX_VERIFY_H

#include <RVL_SDK/gx/GXStruct.h>
#include <RVL_SDK/types.h>

EXTERN_C_BEGIN

void GXSetVerifyLevel( u32 );
GXVerifyCallback GXSetVerifyCallback( GXVerifyCallback callback );

EXTERN_C_END

#endif // RVL_SDK_GX_VERIFY_H
