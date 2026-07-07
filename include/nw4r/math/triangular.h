#ifndef NW4R_MATH_TRIANGULAR_H
#define NW4R_MATH_TRIANGULAR_H

#include <nw4r/math/arithmetic.h>

#include <RVL_SDK/types.h>

#define DEG2RAD ( 6.2831853f / 360.0f )     // 2pi / 360
#define RAD2DEG ( 359.99998f / 6.2831845f ) // 360 / 2pi, slightly tweaked
#define DEG2FIDX ( 256.0f / 360.0f )        // 256 / 360
#define FIDX2DEG ( 360.0f / 256.0f )        // 360 / 256
#define RAD2FIDX ( 256.0f / 6.2831853f )    // 256 / 2pi
#define FIDX2RAD ( 6.2831853f / 256.0f )    // 2pi / 256

namespace nw4r
{
namespace math
{

namespace detail
{

struct SinCosSample
{
    f32 sin_val, cos_val, sin_delta, cos_delta;
};

extern const SinCosSample gSinCosTbl[ 257 ];

} // namespace detail

// WARN (vabold): Some functions are made up to complete an API, but some are missing
// MISSING functions are unconfirmed to exist or have other extenuating circumstances
// This is particularly noticeable with asin/acos implementations, which might be incomplete

f32 SinFIdx( f32 fidx );
f32 CosFIdx( f32 fidx );
void SinCosFIdx( f32 *pSin, f32 *pCos, f32 fidx );

inline f32 TanFIdx( f32 fidx )
{
    return tanf( FIDX2RAD * fidx );
}

// MISSING: AsinFIdx, AcosFIdx

f32 AtanFIdx( f32 x );
f32 Atan2FIdx( f32 y, f32 x );

inline f32 SinIdx( u16 idx )
{
    return SinFIdx( ( 1.0f / 256.0f ) * U16ToF32( idx ) );
}

inline f32 CosIdx( u16 idx )
{
    return CosFIdx( ( 1.0f / 256.0f ) * U16ToF32( idx ) );
}

inline void SinCosIdx( f32 *pSin, f32 *pCos, u16 idx )
{
    SinCosFIdx( pSin, pCos, ( 1.0f / 256.0f ) * U16ToF32( idx ) );
}

inline f32 TanIdx( u16 idx )
{
    return TanFIdx( ( 1.0f / 256.0f ) * U16ToF32( idx ) );
}

// MISSING: AsinIdx, AcosIdx, AtanIdx, Atan2Idx
// The latter two are defined in the source file, but it's not in nw4hbm and unused everywhere else

inline f32 SinRad( f32 rad )
{
    return SinFIdx( RAD2FIDX * rad );
}

inline f32 CosRad( f32 rad )
{
    return CosFIdx( RAD2FIDX * rad );
}

inline void SinCosRad( f32 *pSin, f32 *pCos, f32 rad )
{
    SinCosFIdx( pSin, pCos, RAD2FIDX * rad );
}

inline f32 TanRad( f32 rad )
{
    return TanFIdx( RAD2FIDX * rad );
}

inline f32 AsinRad( f32 x )
{
    return asinf( x );
}

inline f32 AcosRad( f32 x )
{
    return acosf( x );
}

inline f32 AtanRad( f32 x )
{
    return FIDX2RAD * AtanFIdx( x );
}

inline f32 Atan2Rad( f32 y, f32 x )
{
    return FIDX2RAD * Atan2FIdx( y, x );
}

inline f32 SinDeg( f32 deg )
{
    return SinFIdx( DEG2FIDX * deg );
}

inline f32 CosDeg( f32 deg )
{
    return CosFIdx( DEG2FIDX * deg );
}

inline void SinCosDeg( f32 *pSin, f32 *pCos, f32 deg )
{
    SinCosFIdx( pSin, pCos, DEG2FIDX * deg );
}

inline f32 TanDeg( f32 deg )
{
    return TanFIdx( DEG2FIDX * deg );
}

inline f32 AsinDeg( f32 x )
{
    return RAD2DEG * asinf( x );
}

inline f32 AcosDeg( f32 x )
{
    return RAD2DEG * acosf( x );
}

inline f32 AtanDeg( f32 x )
{
    return FIDX2DEG * AtanFIdx( x );
}

inline f32 Atan2Deg( f32 y, f32 x )
{
    return FIDX2DEG * Atan2FIdx( y, x );
}

} // namespace math
} // namespace nw4r

#endif
