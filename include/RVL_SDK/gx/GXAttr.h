#ifndef RVL_SDK_GX_ATTR_H
#define RVL_SDK_GX_ATTR_H

#include <RVL_SDK/gx/GXStruct.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXSetVtxDesc( GXAttr attr, GXAttrType type );
void GXSetVtxDescv( GXVtxDescList *attrPtr );
void GXGetVtxDesc( GXAttr attr, GXAttrType *type );
void GXGetVtxDescv( GXVtxDescList *vcd );
void GXClearVtxDesc( void );
// attr is GX_VA_POS - cnt: GX_POS_x, type: prim
// attr is GX_VA_NRM - cnt: GX_NRM_x, type: prim
// attr is GX_VA_CLRx - cnt: GX_CLR_x, type: RGB
// attr is GX_VA_TEXx - cnt: GX_TEX_x, type: prim
void GXSetVtxAttrFmt( GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac );
void GXSetVtxAttrFmtv( GXVtxFmt vtxfmt, GXVtxAttrFmtList *list );
// attr is GX_VA_POS - cnt: GX_POS_x, type: prim
// attr is GX_VA_NRM - cnt: GX_NRM_x, type: prim
// attr is GX_VA_CLRx - cnt: GX_CLR_x, type: RGB
// attr is GX_VA_TEXx - cnt: GX_TEX_x, type: prim
void GXGetVtxAttrFmt( GXVtxFmt fmt, GXAttr attr, GXCompCnt *cnt, GXCompType *type, u8 *frac );
void GXGetVtxAttrFmtv( GXVtxFmt fmt, GXVtxAttrFmtList *vat );
void GXSetArray( GXAttr attr, void *base_ptr, u8 stride );
void GXInvalidateVtxCache( void );
// mtx: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
// normalize: Use GX_TRUE or GX_FALSE
// pt_texmtx: Use GXPosNrmMtx, GXTexMtx, or GXPTTexMtx
void GXSetTexCoordGen2( GXTexCoordID dst_coord,
        GXTexGenType func,
        GXTexGenSrc src_param,
        u32 mtx,
        GXBool normalize,
        u32 pt_texmtx );
void GXSetNumTexGens( u8 nTexGens );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_ATTR_H
