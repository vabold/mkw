#ifndef RVL_SDK_GX_DRAW_H
#define RVL_SDK_GX_DRAW_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXDrawCylinder( u32 edges );
void GXDrawTorus( f32 thickness, u32, u32 );
void GXDrawSphere( u32, u32 );
void GXDrawCube( void );
void GXDrawDodeca( void );
void GXDrawOctahedron( void );
void GXDrawIcosahedron( void );
void GXDrawSphere1( u8 );
void GXGenNormalTable( u8, void * );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_DRAW_H
