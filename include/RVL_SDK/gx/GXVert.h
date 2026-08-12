#ifndef RVL_SDK_GX_VERT_H
#define RVL_SDK_GX_VERT_H

#include <RVL_SDK/gx/GXEnum.h>

#include <RVL_SDK/base/PPCWGPipe.h>

#ifdef __cplusplus
extern "C"
{
#endif

volatile PPCWGPipe GXWGFifo : 0xcc008000;

static inline void GXCmd1u8( const u8 x )
{
    GXWGFifo.u8 = x;
}

static inline void GXCmd1u16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXCmd1u32( const u32 x )
{
    GXWGFifo.u32 = x;
}

static inline void GXParam1u8( const u8 x )
{
    GXWGFifo.u8 = x;
}

static inline void GXParam1u16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXParam1u32( const u32 x )
{
    GXWGFifo.u32 = x;
}

static inline void GXParam1s8( const s8 x )
{
    GXWGFifo.s8 = x;
}

static inline void GXParam1s16( const s16 x )
{
    GXWGFifo.s16 = x;
}

static inline void GXParam1s32( const s32 x )
{
    GXWGFifo.s32 = x;
}

static inline void GXParam1f32( const f32 x )
{
    GXWGFifo.f32 = x;
}

static inline void GXParam3f32( const f32 x, const f32 y, const f32 z )
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXParam4f32( const f32 x, const f32 y, const f32 z, const f32 w )
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
    GXWGFifo.f32 = w;
}

static inline void GXPosition3f32( const f32 x, const f32 y, const f32 z )
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXPosition3u8( const u8 x, const u8 y, const u8 z )
{
    GXWGFifo.u8 = x;
    GXWGFifo.u8 = y;
    GXWGFifo.u8 = z;
}

static inline void GXPosition3s8( const s8 x, const s8 y, const s8 z )
{
    GXWGFifo.s8 = x;
    GXWGFifo.s8 = y;
    GXWGFifo.s8 = z;
}

static inline void GXPosition3u16( const u16 x, const u16 y, const u16 z )
{
    GXWGFifo.u16 = x;
    GXWGFifo.u16 = y;
    GXWGFifo.u16 = z;
}

static inline void GXPosition3s16( const s16 x, const s16 y, const s16 z )
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.s16 = z;
}

static inline void GXPosition2f32( const f32 x, const f32 y )
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
}

static inline void GXPosition2u8( const u8 x, const u8 y )
{
    GXWGFifo.u8 = x;
    GXWGFifo.u8 = y;
}

static inline void GXPosition2s8( const s8 x, const s8 y )
{
    GXWGFifo.s8 = x;
    GXWGFifo.s8 = y;
}

static inline void GXPosition2u16( const u16 x, const u16 y )
{
    GXWGFifo.u16 = x;
    GXWGFifo.u16 = y;
}

static inline void GXPosition2s16( const s16 x, const s16 y )
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
}

static inline void GXPosition1x16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXPosition1x8( const u8 x )
{
    GXWGFifo.u8 = x;
}

static inline void GXNormal3f32( const f32 x, const f32 y, const f32 z )
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXNormal3s16( const s16 x, const s16 y, const s16 z )
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXWGFifo.s16 = z;
}

static inline void GXNormal3s8( const s8 x, const s8 y, const s8 z )
{
    GXWGFifo.s8 = x;
    GXWGFifo.s8 = y;
    GXWGFifo.s8 = z;
}

static inline void GXNormal1x16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXNormal1x8( const u8 x )
{
    GXWGFifo.u8 = x;
}

static inline void GXColor4u8( const u8 x, const u8 y, const u8 z, const u8 w )
{
    GXWGFifo.u8 = x;
    GXWGFifo.u8 = y;
    GXWGFifo.u8 = z;
    GXWGFifo.u8 = w;
}

static inline void GXColor1u32( const u32 x )
{
    GXWGFifo.u32 = x;
}

static inline void GXColor3u8( const u8 x, const u8 y, const u8 z )
{
    GXWGFifo.u8 = x;
    GXWGFifo.u8 = y;
    GXWGFifo.u8 = z;
}

static inline void GXColor1u16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXColor1x16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXColor1x8( const u8 x )
{
    GXWGFifo.u8 = x;
}

static inline void GXTexCoord2f32( const f32 x, const f32 y )
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
}

static inline void GXTexCoord2s16( const s16 x, const s16 y )
{
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
}

static inline void GXTexCoord2u16( const u16 x, const u16 y )
{
    GXWGFifo.u16 = x;
    GXWGFifo.u16 = y;
}

static inline void GXTexCoord2s8( const s8 x, const s8 y )
{
    GXWGFifo.s8 = x;
    GXWGFifo.s8 = y;
}

static inline void GXTexCoord2u8( const u8 x, const u8 y )
{
    GXWGFifo.u8 = x;
    GXWGFifo.u8 = y;
}

static inline void GXTexCoord1f32( const f32 x )
{
    GXWGFifo.f32 = x;
}

static inline void GXTexCoord1s16( const s16 x )
{
    GXWGFifo.s16 = x;
}

static inline void GXTexCoord1u16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXTexCoord1s8( const s8 x )
{
    GXWGFifo.s8 = x;
}

static inline void GXTexCoord1u8( const u8 x )
{
    GXWGFifo.u8 = x;
}

static inline void GXTexCoord1x16( const u16 x )
{
    GXWGFifo.u16 = x;
}

static inline void GXTexCoord1x8( const u8 x )
{
    GXWGFifo.u8 = x;
}

static inline void GXMatrixIndex1u8( const u8 x )
{
    GXWGFifo.u8 = x;
}

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_VERT_H
