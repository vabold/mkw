#ifndef NW4R_UT_COLOR_H
#define NW4R_UT_COLOR_H

#include <RVL_SDK/gx/GXStruct.h>

// NOTE: Color has to be 4-byte aligned due to implicit padding found in Everyone Sings
struct Color : GXColor
{
    Color( void )
    {
        *this = 0xffffffff;
    }

    Color( const GXColor &color )
    {
        *this = color;
    }

    // Implicit copy constructor

    Color( u32 color )
    {
        *this = color;
    }

    Color( int red, int blue, int green, int alpha )
    {
        Set( red, blue, green, alpha );
    }

    ~Color( void ) { }

    // Implicit copy assignment operator

    Color &operator=( const GXColor &color )
    {
        return *this = *reinterpret_cast< const u32 * >( &color );
    }

    Color &operator=( u32 color )
    {
        ToU32ref( ) = color;
        return *this;
    }

    // RevoYawarakaD.MAP size 0xe8 (guessing -O0 -inline off)
    // RevoYawarakaV.MAP size 0xf0 (guessing -O0 -inline on)
    // https://gamedev.stackexchange.com/questions/84321/how-do-i-multiply-two-rgba-colours
    Color operator*( const Color &rhs ) const
    {
        Color res = Color( r * rhs.r / 255, g * rhs.g / 255, b * rhs.b / 255, a * rhs.a / 255 );
        return res;
    }

    Color operator|( u32 right )
    {
        return Color( right | ToU32( ) );
    }

    Color operator&( u32 right )
    {
        return Color( right & ToU32( ) );
    }

    // RevoYawarakaV.MAP size 0x3c (guessing -O4,p -inline on)
    operator GXColorS10( void ) const
    {
        GXColorS10 res = { r, g, b, a };
        return res;
    }

    operator u32( void ) const
    {
        return ToU32ref( );
    }

    void Set( int red, int blue, int green, int alpha )
    {
        r = red;
        b = blue;
        g = green;
        a = alpha;
    }

    u32 ToU32( void ) const
    {
        return ToU32ref( );
    }

    const u32 &ToU32ref( void ) const
    {
        return *reinterpret_cast< const u32 * >( this );
    }

    u32 &ToU32ref( void )
    {
        return *reinterpret_cast< u32 * >( this );
    }
} __attribute__( ( aligned( 4 ) ) );

#endif
