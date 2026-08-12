// NOTE: This header name is wrong

#ifndef RVL_SDK_GX_MISC_H
#define RVL_SDK_GX_MISC_H

#include <RVL_SDK/gx/GXStruct.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXSetMisc( GXMiscToken token, u32 val );
void GXFlush( void );
void GXResetWriteGatherPipe( void );
void GXAbortFrame( void );
void GXSetDrawSync( u16 token );
u16 GXReadDrawSync( void );
void GXSetDrawDone( void );
void GXWaitDrawDone( void );
void GXDrawDone( void );
void GXPixModeSync( void );
void GXTexModeSync( void );
void GXPokeAlphaMode( GXCompare func, u8 threshold );
void GXPokeAlphaRead( GXAlphaReadMode mode );
// update_enable: Use GX_ENABLE or GX_DISABLE
void GXPokeAlphaUpdate( GXBool update_enable );
void GXPokeBlendMode( GXBlendMode type,
        GXBlendFactor src_factor,
        GXBlendFactor dst_factor,
        GXLogicOp op );
// update_enable: Use GX_ENABLE or GX_DISABLE
void GXPokeColorUpdate( GXBool update_enable );
// enable: Use GX_ENABLE or GX_DISABLE
void GXPokeDstAlpha( GXBool enable, u8 alpha );
// dither: Use GX_ENABLE or GX_DISABLE
void GXPokeDither( GXBool dither );
// compare_enable: Use GX_ENABLE or GX_DISABLE
// update_enable: Use GX_ENABLE or GX_DISABLE
void GXPokeZMode( GXBool compare_enable, GXCompare func, GXBool update_enable );
void GXPeekARGB( u16 x, u16 y, u32 *color );
void GXPokeARGB( u16 x, u16 y, u32 color );
void GXPeekZ( u16 x, u16 y, u32 *z );
void GXPokeZ( u16 x, u16 y, u32 z );
GXDrawSyncCallback GXSetDrawSyncCallback( GXDrawSyncCallback cb );
GXDrawDoneCallback GXSetDrawDoneCallback( GXDrawDoneCallback cb );
u32 GXCompressZ16( u32 z24, GXZFmt16 zfmt );
u32 GXDecompressZ16( u32 z16, GXZFmt16 zfmt );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_MISC_H
