#ifndef RVL_SDK_GX_TEXTURE_H
#define RVL_SDK_GX_TEXTURE_H

#include <RVL_SDK/gx/GXStruct.h>

#ifdef __cplusplus
extern "C"
{
#endif

// mipmap: Use GX_TRUE or GX_FALSE
// max_lod: Use GX_TRUE or GX_FALSE
u32 GXGetTexBufferSize( u16 width, u16 height, u32 format, GXBool mipmap, GXBool max_lod );
// mipmap: Use GX_TRUE or GX_FALSE
void GXInitTexObj( GXTexObj *obj,
        void *image_ptr,
        u16 width,
        u16 height,
        GXTexFmt format,
        GXTexWrapMode wrap_s,
        GXTexWrapMode wrap_t,
        GXBool mipmap );
// mipmap: Use GX_TRUE or GX_FALSE
void GXInitTexObjCI( GXTexObj *obj,
        void *image_ptr,
        u16 width,
        u16 height,
        GXCITexFmt format,
        GXTexWrapMode wrap_s,
        GXTexWrapMode wrap_t,
        GXBool mipmap,
        u32 tlut_name );
// bias_clamp: Use GX_TRUE or GX_FALSE
// do_edge_lod: Use GX_TRUE or GX_FALSE
void GXInitTexObjLOD( GXTexObj *obj,
        GXTexFilter min_filt,
        GXTexFilter mag_filt,
        f32 min_lod,
        f32 max_lod,
        f32 lod_bias,
        GXBool bias_clamp,
        GXBool do_edge_lod,
        GXAnisotropy max_aniso );
void GXInitTexObjData( GXTexObj *obj, void *image_ptr );
void GXInitTexObjWrapMode( GXTexObj *obj, GXTexWrapMode sm, GXTexWrapMode tm );
void GXInitTexObjTlut( GXTexObj *obj, u32 tlut_name );
void GXInitTexObjFilter( GXTexObj *obj, GXTexFilter min_filt, GXTexFilter mag_filt );
void GXInitTexObjMaxLOD( GXTexObj *obj, f32 max_lod );
void GXInitTexObjMinLOD( GXTexObj *obj, f32 min_lod );
void GXInitTexObjLODBias( GXTexObj *obj, f32 lod_bias );
// bias_clamp: Use GX_TRUE or GX_FALSE
void GXInitTexObjBiasClamp( GXTexObj *obj, GXBool bias_clamp );
// do_edge_lod: Use GX_TRUE or GX_FALSE
void GXInitTexObjEdgeLOD( GXTexObj *obj, GXBool do_edge_lod );
void GXInitTexObjMaxAniso( GXTexObj *obj, GXAnisotropy max_aniso );
void GXInitTexObjUserData( GXTexObj *obj, void *user_data );
void *GXGetTexObjUserData( GXTexObj *obj );
void GXGetTexObjAll( GXTexObj *obj,
        void **image_ptr,
        u16 *width,
        u16 *height,
        GXTexFmt *format,
        GXTexWrapMode *wrap_s,
        GXTexWrapMode *wrap_t,
        GXBool *mipmap );
void *GXGetTexObjData( GXTexObj *to );
u16 GXGetTexObjWidth( GXTexObj *to );
u16 GXGetTexObjHeight( GXTexObj *to );
GXTexFmt GXGetTexObjFmt( GXTexObj *to );
GXTexWrapMode GXGetTexObjWrapS( GXTexObj *to );
GXTexWrapMode GXGetTexObjWrapT( GXTexObj *to );
GXBool GXGetTexObjMipMap( GXTexObj *to );
void GXGetTexObjLODAll( GXTexObj *tex_obj,
        GXTexFilter *min_filt,
        GXTexFilter *mag_filt,
        f32 *min_lod,
        f32 *max_lod,
        f32 *lod_bias,
        GXBool *bias_clamp,
        GXBool *do_edge_lod,
        GXAnisotropy *max_aniso );
GXTexFilter GXGetTexObjMinFilt( GXTexObj *tex_obj );
GXTexFilter GXGetTexObjMagFilt( GXTexObj *tex_obj );
f32 GXGetTexObjMinLOD( GXTexObj *tex_obj );
f32 GXGetTexObjMaxLOD( GXTexObj *tex_obj );
f32 GXGetTexObjLODBias( GXTexObj *tex_obj );
GXBool GXGetTexObjBiasClamp( GXTexObj *tex_obj );
GXBool GXGetTexObjEdgeLOD( GXTexObj *tex_obj );
GXAnisotropy GXGetTexObjMaxAniso( GXTexObj *tex_obj );
u32 GXGetTexObjTlut( GXTexObj *tex_obj );
void GXLoadTexObjPreLoaded( GXTexObj *obj, GXTexRegion *region, GXTexMapID id );
void GXLoadTexObj( GXTexObj *obj, GXTexMapID id );
void GXInitTlutObj( GXTlutObj *tlut_obj, void *lut, GXTlutFmt fmt, u16 n_entries );
void GXGetTlutObjAll( GXTlutObj *tlut_obj, void **data, GXTlutFmt *format, u16 *numEntries );
void *GXGetTlutObjData( GXTlutObj *tlut_obj );
GXTlutFmt GXGetTlutObjFmt( GXTlutObj *tlut_obj );
u16 GXGetTlutObjNumEntries( GXTlutObj *tlut_obj );
void GXLoadTlut( GXTlutObj *tlut_obj, u32 tlut_name );
// is_32b_mipmap: Use GX_TRUE or GX_FALSE
void GXInitTexCacheRegion( GXTexRegion *region,
        GXBool is_32b_mipmap,
        u32 tmem_even,
        GXTexCacheSize size_even,
        u32 tmem_odd,
        GXTexCacheSize size_odd );
void GXInitTexPreLoadRegion( GXTexRegion *region,
        u32 tmem_even,
        u32 size_even,
        u32 tmem_odd,
        u32 size_odd );
void GXGetTexRegionAll( GXTexRegion *region,
        GXBool *is_cached,
        GXBool *is_32b_mipmap,
        u32 *tmem_even,
        u32 *size_even,
        u32 *tmem_odd,
        u32 *size_odd );
void GXInitTlutRegion( GXTlutRegion *region, u32 tmem_addr, GXTlutSize tlut_size );
void GXGetTlutRegionAll( GXTlutRegion *region, u32 *tmem_addr, GXTlutSize *tlut_size );
void GXInvalidateTexRegion( GXTexRegion *region );
void GXInvalidateTexAll( void );
GXTexRegionCallback GXSetTexRegionCallback( GXTexRegionCallback f );
GXTlutRegionCallback GXSetTlutRegionCallback( GXTlutRegionCallback f );
void GXPreLoadEntireTexture( GXTexObj *tex_obj, GXTexRegion *region );
// enable: Use GX_ENABLE or GX_DISABLE
void GXSetTexCoordScaleManually( GXTexCoordID coord, GXBool enable, u16 ss, u16 ts );
// s_enable: Use GX_ENABLE or GX_DISABLE
// t_enable: Use GX_ENABLE or GX_DISABLE
void GXSetTexCoordCylWrap( GXTexCoordID coord, GXBool s_enable, GXBool t_enable );
// s_enable: Use GX_ENABLE or GX_DISABLE
// t_enable: Use GX_ENABLE or GX_DISABLE
void GXSetTexCoordBias( GXTexCoordID coord, GXBool s_enable, GXBool t_enable );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_TEXTURE_H
