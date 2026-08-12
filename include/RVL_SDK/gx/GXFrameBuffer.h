#ifndef RVL_SDK_GX_FRAME_BUFFER_H
#define RVL_SDK_GX_FRAME_BUFFER_H

#include <RVL_SDK/gx/GXStruct.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXAdjustForOverscan( GXRenderModeObj *rmin, GXRenderModeObj *rmout, u16 hor, u16 ver );
void GXSetDispCopySrc( u16 left, u16 top, u16 wd, u16 ht );
void GXSetTexCopySrc( u16 left, u16 top, u16 wd, u16 ht );
void GXSetDispCopyDst( u16 wd );
// mipmap: Use GX_TRUE or GX_FALSE
void GXSetTexCopyDst( u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap );
void GXSetDispCopyFrame2Field( GXCopyMode mode );
void GXSetCopyClamp( GXFBClamp clamp );
u16 GXGetNumXfbLines( u16, f32 vscale );
f32 GXGetYScaleFactor( u16 efb_height, u16 xfb_height );
u32 GXSetDispCopyYScale( f32 vscale );
void GXSetCopyClear( GXColor clear_clr, u32 clear_z );
void GXSetCopyFilter( u8 aa, u8 sample_pattern[ 12 ][ 2 ], u8 vf, u8 *vfilter );
void GXSetDispCopyGamma( GXGamma gamma );
// clear: Use GX_TRUE or GX_FALSE
void GXCopyDisp( void *dest, GXBool clear );
// clear: Use GX_TRUE or GX_FALSE
void GXCopyTex( void *dest, GXBool clear );
void GXClearBoundingBox( void );
void GXReadBoundingBox( u16 *left, u16 *top, u16 *right, u16 *bottom );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_FRAME_BUFFER_H
