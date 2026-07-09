#ifndef RVL_SDK_OS_FAST_CAST_H
#define RVL_SDK_OS_FAST_CAST_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

static inline f32 __OSu16tof32( register u16 *in )
{
    register f32 r;
    ASM
    (
        psq_l r, 0x0( in ), 1, 3;
    );
    return r;
}

static inline void OSu16tof32( u16 *in, vf32 *out )
{
    *out = __OSu16tof32( in );
}

static inline f32 __OSs16tof32( register s16 *in )
{
    register f32 r;
    ASM
    (
        psq_l r, 0x0( in ), 1, 5;
    );
    return r;
}

static inline void OSs16tof32( s16 *in, vf32 *out )
{
    *out = __OSs16tof32( in );
}

static inline u16 __OSf32tou16( register f32 in )
{
    f32 a;
    register f32 *ptr = &a;
    register u16 r;
    ASM
    (
        psq_st in, 0x0( ptr ), 1, 3;
        lhz r, 0x0( ptr );
    );
    return r;
}

static inline void OSf32tou16( f32 *in, vu16 *out )
{
    *out = __OSf32tou16( *in );
}

static inline s16 __OSf32tos16( register f32 in )
{
    f32 a;
    register f32 *ptr = &a;
    register s16 r;
    ASM
    (
        psq_st in, 0x0( ptr ), 1, 5;
        lha r, 0x0( ptr );
    );
    return r;
}

static inline void OSf32tos16( f32 *in, vs16 *out )
{
    *out = __OSf32tos16( *in );
}

#ifdef __cplusplus
}
#endif

#endif
