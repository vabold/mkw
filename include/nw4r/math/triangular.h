#ifndef NW4R_MATH_TRIANGULAR_H
#define NW4R_MATH_TRIANGULAR_H

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

} // namespace math
} // namespace nw4r

#endif
