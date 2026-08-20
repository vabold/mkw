#ifndef NW4R_UT_RECT_H
#define NW4R_UT_RECT_H

#include <nw4r/math/arithmetic.h>

namespace nw4r
{
namespace ut
{

struct Rect
{
    Rect( void ) : left( 0.0f ), top( 0.0f ), right( 0.0f ), bottom( 0.0f ) { }

    Rect( f32 l, f32 t, f32 r, f32 b ) : left( l ), top( t ), right( r ), bottom( b ) { }

    // Implicit copy constructor

    ~Rect( void ) { }

    // Implicit assignment operator

    f32 GetHeight( void ) const
    {
        return bottom - top;
    }

    f32 GetWidth( void ) const
    {
        return right - left;
    }

    // donut.MAP (Kirby's Dream Collection) size 0x34 (guessing -O4,p -inline on)
    // Relative move
    void Move( f32 x, f32 y )
    {
        left += x;
        right += x;
        top += y;
        bottom += y;
    }

    // Absolute move
    void MoveTo( f32 x, f32 y )
    {
        right = x + GetWidth( );
        left = x;
        bottom = y + GetHeight( );
        top = y;
    }

    void Normalize( void )
    {
        f32 l = left;
        f32 t = top;
        f32 r = right;
        f32 b = bottom;

        left = math::FSelect( r - l, l, r );
        right = math::FSelect( r - l, r, l );
        top = math::FSelect( b - t, t, b );
        bottom = math::FSelect( b - t, b, t );
    }

    void SetHeight( f32 height )
    {
        bottom = top + height;
    }

    void SetWidth( f32 width )
    {
        right = left + width;
    }

    f32 left;
    f32 top;
    f32 right;
    f32 bottom;
};

} // namespace ut
} // namespace nw4r

#endif // NW4R_UT_RECT_H
