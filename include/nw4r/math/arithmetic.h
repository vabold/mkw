#ifndef NW4R_MATH_ARITHMETIC_H
#define NW4R_MATH_ARITHMETIC_H

#include <RVL_SDK/os/OSFastCast.h>

namespace nw4r
{
namespace math
{

inline f32 U16ToF32( u16 x )
{
    f32 rval;
    OSu16tof32( &x, &rval );
    return rval;
}

inline f32 S16ToF32( s16 x )
{
    f32 rval;
    OSs16tof32( &x, &rval );
    return rval;
}

inline f32 U32AsF32( u32 x )
{
    return *reinterpret_cast< f32 * >( &x );
}

inline u16 F32ToU16( f32 x )
{
    u16 rval;
    OSf32tou16( &x, &rval );
    return rval;
}

inline s16 F32ToS16( f32 x )
{
    s16 rval;
    OSf32tos16( &x, &rval );
    return rval;
}

inline u32 F32AsU32( f32 x )
{
    return *reinterpret_cast< u32 * >( &x );
}

inline s32 FGetExpPart( f32 x )
{
    s32 s = ( F32AsU32( x ) >> 0x17 & 0xff );
    return s - 0x7f;
}

inline f32 FGetMantPart( f32 x )
{
    u32 u = F32AsU32( x ) & 0x807fffff | 0x3f800000;
    return U32AsF32( u );
}

inline f32 FAbs( register f32 x )
{
    register f32 ret;
    ASM
    (
        // __fabs returns a double and there's no fabsf call so we need ASM here
        fabs ret, x;
    );
    return ret;
}

inline f32 FCeil( f32 x )
{
    return ceilf( x );
}

inline f32 FFloor( f32 x )
{
    return floorf( x );
}

inline f32 FModf( f32 x, f32 *y )
{
    return modff( x, y );
}

inline f32 FInv( register f32 x )
{
    register f32 ix;
    register f32 rx = x;
    register f32 x2;
    register f32 xx;

    ASM
    (
        fres ix, rx;
        ps_add x2, ix, ix;
        ps_mul xx, ix, ix;
        ps_nmsub ix, rx, xx, x2;
    );
    return ix;
}

inline f32 FMod( f32 x, f32 y )
{
    return fmodf( x, y );
}

inline f32 FSelect( register f32 cond, register f32 ifPos, register f32 ifNeg )
{
    register f32 ret;
    ASM
    (
        fsel ret, cond, ifPos, ifNeg;
    );
    return ret;
}

namespace detail
{

f32 FExp( f32 x );
f32 FLog( f32 x );
u32 CntLz_( u32 x );

} // namespace detail

inline f32 FExp( f32 x )
{
    return detail::FExp( x );
}

inline f32 FLog( f32 x )
{
    return x > 0.0f ? detail::FLog( x ) : NAN;
}

f32 FrSqrt( f32 x );
f32 Hermite( f32 p1, f32 t1, f32 p2, f32 t2, f32 s );
f32 Bezier( f32 p1, f32 p2, f32 p3, f32 p4, f32 s );
f32 CatmullRom( f32 p0, f32 p1, f32 p2, f32 p3, f32 s );
u32 CntBit1( u32 x );
u32 CntBit1( const u32 *first, const u32 *last );
u32 DistBit( const u32 *first1, const u32 *last1, const u32 *first2 );
u32 RevBit( u32 x );
int IExp( int x, u32 n );
u32 ILog10( u32 x );

inline f32 FSqrt( f32 x )
{
    return x <= 0.0f ? 0.0f : x * FrSqrt( x );
}

inline u32 CntLz( register u32 x )
{
    register u32 result;
    ASM
    (
        cntlzw result, x;
    );
    return result;
}

} // namespace math
} // namespace nw4r

#endif
