#ifndef NW4R_MATH_ARITHMETIC_H
#define NW4R_MATH_ARITHMETIC_H

#include <RVL_SDK/os/OSFastCast.h>

namespace nw4r
{
namespace math
{

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

inline f32 U16ToF32( u16 x )
{
    f32 rval;
    OSu16tof32( &x, &rval );
    return rval;
}

inline u16 F32ToU16( f32 x )
{
    u16 rval;
    OSf32tou16( &x, &rval );
    return rval;
}

} // namespace math
} // namespace nw4r

#endif
