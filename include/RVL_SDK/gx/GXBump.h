#ifndef RVL_SDK_GX_BUMP_H
#define RVL_SDK_GX_BUMP_H

#include <RVL_SDK/gx/GXEnum.h>

#ifdef __cplusplus
extern "C"
{
#endif

// add_prev: Use GX_TRUE or GX_FALSE
// utc_lod: Use GX_TRUE or GX_FALSE
void GXSetTevIndirect( GXTevStageID tev_stage,
        GXIndTexStageID ind_stage,
        GXIndTexFormat format,
        GXIndTexBiasSel bias_sel,
        GXIndTexMtxID matrix_sel,
        GXIndTexWrap wrap_s,
        GXIndTexWrap wrap_t,
        GXBool add_prev,
        GXBool utc_lod,
        GXIndTexAlphaSel alpha_sel );
// TODO: offset typedef?
void GXSetIndTexMtx( GXIndTexMtxID mtx_id, f32 offset[ 2 ][ 3 ], s8 scale_exp );
void GXSetIndTexCoordScale( GXIndTexStageID ind_state,
        GXIndTexScale scale_s,
        GXIndTexScale scale_t );
void GXSetIndTexOrder( GXIndTexStageID ind_stage, GXTexCoordID tex_coord, GXTexMapID tex_map );
void GXSetNumIndStages( u8 nIndStages );
void GXSetTevDirect( GXTevStageID tev_stage );
// signed_offset: Use GX_TRUE or GX_FALSE
// replace_mode: Use GX_TRUE or GX_FALSE
void GXSetTevIndWarp( GXTevStageID tev_stage,
        GXIndTexStageID ind_stage,
        GXBool signed_offset,
        GXBool replace_mode,
        GXIndTexMtxID matrix_sel );
void GXSetTevIndTile( GXTevStageID tev_stage,
        GXIndTexStageID ind_stage,
        u16 tilesize_s,
        u16 tilesize_t,
        u16 tilespacing_s,
        u16 tilespacing_t,
        GXIndTexFormat format,
        GXIndTexMtxID matrix_sel,
        GXIndTexBiasSel bias_sel,
        GXIndTexAlphaSel alpha_sel );
void GXSetTevIndBumpST( GXTevStageID tev_stage,
        GXIndTexStageID ind_stage,
        GXIndTexMtxID matrix_sel );
void GXSetTevIndBumpXYZ( GXTevStageID tev_stage,
        GXIndTexStageID ind_stage,
        GXIndTexMtxID matrix_sel );
void GXSetTevIndRepeat( GXTevStageID tev_stage );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_BUMP_H
