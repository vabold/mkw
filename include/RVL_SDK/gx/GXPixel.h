#ifndef RVL_SDK_GX_PIXEL_H
#define RVL_SDK_GX_PIXEL_H

#include <RVL_SDK/gx/GXStruct.h>

#include <RVL_SDK/mtx.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXSetFog( GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color );
void GXSetFogColor( GXColor color );
void GXInitFogAdjTable( GXFogAdjTable *table, u16 width, Mtx44Ptr projmtx );
// enable: Use GX_ENABLE or GX_DISABLE
void GXSetFogRangeAdj( GXBool enable, u16 center, GXFogAdjTable *table );
void GXSetBlendMode( GXBlendMode type,
        GXBlendFactor src_factor,
        GXBlendFactor dst_factor,
        GXLogicOp op );
// update_enable: Use GX_ENABLE or GX_DISABLE
void GXSetColorUpdate( GXBool update_enable );
void GXGetColorUpdate( GXBool *update_enable );
// update_enable: Use GX_ENABLE or GX_DISABLE
void GXSetAlphaUpdate( GXBool update_enable );
void GXGetAlphaUpdate( GXBool *update_enable );
// compare_enable: Use GX_ENABLE or GX_DISABLE
// update_enable: Use GX_ENABLE or GX_DISABLE
void GXSetZMode( GXBool compare_enable, GXCompare func, GXBool update_enable );
// before_tex: Use GX_TRUE or GX_FALSE
void GXSetZCompLoc( GXBool before_tex );
void GXSetPixelFmt( GXPixelFmt pix_fmt, GXZFmt16 z_fmt );
void GXGetPixelFmt( GXPixelFmt *pix_fmt, GXZFmt16 *z_fmt );
// dither: Use GX_TRUE or GX_FALSE
void GXSetDither( GXBool dither );
void GXGetDither( GXBool *dither );
// enable: Use GX_ENABLE or GX_DISABLE
void GXSetDstAlpha( GXBool enable, u8 alpha );
// odd_mask: Use GX_TRUE or GX_FALSE
// even_mask: Use GX_TRUE or GX_FALSE
void GXSetFieldMask( GXBool odd_mask, GXBool even_mask );
// field_mode: Use GX_TRUE or GX_FALSE
// half_aspect_ratio: Use GX_TRUE or GX_FALSE
void GXSetFieldMode( GXBool field_mode, GXBool half_aspect_ratio );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_PIXEL_H
