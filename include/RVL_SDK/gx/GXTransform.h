#ifndef RVL_SDK_GX_TRANSFORM_H
#define RVL_SDK_GX_TRANSFORM_H

#include <RVL_SDK/gx/GXEnum.h>

#include <RVL_SDK/mtx.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXProject( f32 x, f32 y, f32 z, MtxPtr mtx, f32 *pm, f32 *vp, f32 *sx, f32 *sy, f32 *sz );
void GXSetProjection( Mtx44Ptr mtx, GXProjectionType type );
void GXSetProjectionv( f32 *ptr );
void GXGetProjectionv( f32 *ptr );
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXLoadPosMtxImm( MtxPtr mtx, u32 id );
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXLoadPosMtxIndx( u16 mtx_indx, u32 id );
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXLoadNrmMtxImm( MtxPtr mtx, u32 id );
// TODO: mtx typedef?
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXLoadNrmMtxImm3x3( f32 mtx[ 3 ][ 3 ], u32 id );
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXLoadNrmMtxIndx3x3( u16 mtx_indx, u32 id );
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXSetCurrentMtx( u32 id );
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXLoadTexMtxImm( MtxPtr mtx, u32 id, GXTexMtxType type );
// id: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXLoadTexMtxIndx( u16 mtx_indx, u32 id, GXTexMtxType type );
void GXSetViewportJitter( f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field );
void GXSetViewport( f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz );

static inline void GXSetViewportv( const f32 *vp )
{
    GXSetViewport( vp[ 0 ], vp[ 1 ], vp[ 2 ], vp[ 3 ], vp[ 4 ], vp[ 5 ] );
}

f32 GXGetViewportv( f32 *vp );
void GXSetZScaleOffset( f32, f32 );
void GXSetScissor( u32 left, u32 top, u32 wd, u32 ht );
void GXGetScissor( u32 *left, u32 *top, u32 *wd, u32 *ht );
void GXSetScissorBoxOffset( s32 x_off, s32 y_off );
void GXSetClipMode( GXClipMode mode );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_TRANSFORM_H
