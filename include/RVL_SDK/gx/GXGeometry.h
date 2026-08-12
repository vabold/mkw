#ifndef RVL_SDK_GX_GEOMETRY_H
#define RVL_SDK_GX_GEOMETRY_H

#include <RVL_SDK/gx/GXAttr.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXBegin( GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts );
void GXSetLineWidth( u8 width, GXTexOffset texOffsets );
void GXGetLineWidth( u8 *width, GXTexOffset *texOffsets );
void GXSetPointSize( u8 pointSize, GXTexOffset texOffsets );
void GXGetPointSize( u8 *pointSize, GXTexOffset *texOffsets );
// line_enable: Use GX_ENABLE or GX_DISABLE
// point_enable: Use GX_ENABLE or GX_DISABLE
void GXEnableTexOffsets( GXTexCoordID coord, GXBool line_enable, GXBool point_enable );
void GXSetCullMode( GXCullMode mode );
void GXGetCullMode( GXCullMode *mode );
// enable: Use GX_ENABLE or GX_DISABLE
void GXSetCoPlanar( GXBool enable );

static inline void GXEnd( void ) { }

// TODO: Why is this defined here and not in GXAttr?
// mtx: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
static inline void
GXSetTexCoordGen( GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx )
{
    GXSetTexCoordGen2( dst_coord, func, src_param, mtx, GX_FALSE, GX_PTIDENTITY );
}

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_GEOMETRY_H
