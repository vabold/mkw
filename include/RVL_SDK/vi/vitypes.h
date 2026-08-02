#ifndef RVL_SDK_VI_TYPES_H
#define RVL_SDK_VI_TYPES_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    VI_TVMODE_NTSC_INT = 0,
    VI_TVMODE_NTSC_DS = 1,
    VI_TVMODE_NTSC_PROG = 2,
    VI_TVMODE_PAL_INT = 4,
    VI_TVMODE_PAL_DS = 5,
    VI_TVMODE_MPAL_INT = 8,
    VI_TVMODE_MPAL_DS = 9,
    VI_TVMODE_DEBUG_INT = 12,
} VITVMode;

typedef enum
{
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF = 1,
} VIXFBMode;

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_VI_TYPES_H
