#ifndef EGG_BIT_FLAG_H
#define EGG_BIT_FLAG_H

#include <RVL_SDK/types.h>

namespace EGG
{

// This doesn't exist, but it's used to help validate TBitFlag to prevent improper usage
// The old method involved a union to avoid __static_assert, but this code only exists in MWCC v4
// TODO: gcc/clang/MW v2 support
template < typename T, typename U >
struct TIsSame
{
    static const bool value = false;
};

template < typename T >
struct TIsSame< T, T >
{
    static const bool value = true;
};

template < typename T >
class TBitFlag
{
public:
    // All: RevoYawarakaD.MAP size 0x34 (-O0 -inline off)
    // u16, u32: Must call makeAllZero
    TBitFlag( void )
    {
        makeAllZero( );
    }

    // u8, u32: RevoYawarakaD.MAP size 0x8 (-O0 -inline off)
    TBitFlag( T val ) : bits( val ) { }

    // Assume implicit copy constructor
    // Assume implicit destructor
    // Assume implicit assignment operator

    // u8: RevoYawarakaV.map size 0x8 (guessing -O4,p -inline on)
    operator T( void )
    {
        return bits;
    }

    // u8, u16: RevoYawarakaD.MAP size 0x50 (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x4C (-O0 -inline off)
    // u16, u32: Must call change
    void changeBit( u8 bit, bool enable )
    {
        change( makeMask( bit ), enable );
    }

    // u8: RevoYawarakaD.MAP size 0x48 (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x44 (-O0 -inline off)
    // u8: Must call makeMask, off
    bool offBit( u8 bit ) const
    {
        return off( makeMask( bit ) );
    }

    // u8, u16: RevoYawarakaD.MAP size 0x48 (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x44 (-O0 -inline off)
    // u16, u32: Must call makeMask, on
    bool onBit( u8 bit ) const
    {
        return on( makeMask( bit ) );
    }

    // u8, u16: RevoYawarakaD.MAP size 0x48 (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x44 (-O0 -inline off)
    // u16, u32: Must call reset
    void resetBit( u8 bit )
    {
        reset( makeMask( bit ) );
    }

    // u8, u16: RevoYawarakaD.MAP size 0x48 (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x44 (-O0 -inline off)
    void setBit( u8 bit )
    {
        set( makeMask( bit ) );
    }

    // u16: RevoYawarakaD.MAP size 0x54 (-O0 -inline off)
    // u16: Must call changeBit
    void toggleBit( u8 bit )
    {
        changeBit( bit, !onBit( bit ) );
    }

    // All: RevoYawarakaD.MAP size 0x60 (-O0 -inline off)
    // u8, u32: Must call set
    void change( T mask, bool enable )
    {
        if( enable )
        {
            set( mask );
        }
        else
        {
            reset( mask );
        }
    }

    // u8, u32: RevoYawarakaD.MAP size 0x38 (-O0 -inline off)
    bool off( T mask ) const
    {
        return !on( mask );
    }

    // u8, u16: RevoYawarakaD.MAP size 0x1c (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x18 (-O0 -inline off)
    bool on( T mask ) const
    {
        return ( bits & mask ) != static_cast< T >( 0 );
    }

    // u8, u16: RevoYawarakaD.MAP size 0x14 (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x10 (-O0 -inline off)
    void reset( T mask )
    {
        bits &= ~mask;
    }

    // All: RevoYawarakaD.MAP size 0x10 (-O0 -inline off)
    void set( T mask )
    {
        bits |= mask;
    }

    // u8: RevoYawarakaD.MAP size 0xc (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x8 (-O0 -inline off)
    T getDirect( void ) const
    {
        return bits;
    }

    // u8, u32: RevoYawarakaV.MAP size 0x10 (guessing -O4,p -inline on)
    bool isZero( void )
    {
        return bits == static_cast< T >( 0 );
    }

    // u8: RevoYawarakaV.MAP size 0xc (guessing -O4,p -inline on)
    void makeAllOne( void )
    {
        bits = ~static_cast< T >( 0 );
    }

    // All: RevoYawarakaD.MAP size 0xc (-O0 -inline off)
    void makeAllZero( void )
    {
        bits = static_cast< T >( 0 );
    }

    // u8, u32: RevoYawarakaD.MAP size 0x8 (-O0 -inline off)
    void setDirect( T val )
    {
        bits = val;
    }

private:
    // u8, u16: RevoYawarakaD.MAP size 0x14 (-O0 -inline off)
    // u32: RevoYawarakaD.MAP size 0x10 (-O0 -inline off)
    T makeMask( u8 bit ) const
    {
        return static_cast< T >( 1 ) << bit;
    }

    T bits;
    __static_assert( TIsSame< T, u8 >::value || TIsSame< T, u16 >::value ||
                    TIsSame< T, u32 >::value,
            "EGG::TBitFlag must be u8, u16, or u32!" );
};

} // namespace EGG

#endif // EGG_BIT_FLAG_H
