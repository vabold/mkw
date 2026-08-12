#ifndef RVL_SDK_GX_DISP_LIST_H
#define RVL_SDK_GX_DISP_LIST_H

#include <RVL_SDK/gx/GXVert.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXBeginDisplayList( void *list, u32 size );
u32 GXEndDisplayList( void );
void GXCallDisplayList( void *list, u32 nbytes );

static inline void GXFastCallDisplayList( void *list, u32 nbytes )
{
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u32 = (u32)list;
    GXWGFifo.u32 = nbytes;
}

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_DISP_LIST_H
