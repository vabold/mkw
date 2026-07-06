#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H

#include <nw4r/math/triangular.h>

#include <RVL_SDK/mtx.h>

namespace nw4r
{
namespace math
{

struct VEC2;
struct VEC3;
struct VEC4;
struct QUAT;
struct MTX33;
struct MTX34;
struct MTX44;

/******************************************************************************
 *
 * VEC2
 *
 ******************************************************************************/

VEC2 *VEC2Maximize( VEC2 *pOut, const VEC2 *p1, const VEC2 *p2 );
VEC2 *VEC2Minimize( VEC2 *pOut, const VEC2 *p1, const VEC2 *p2 );
VEC2 *VEC2Normalize( VEC2 *pOut, const VEC2 *p );

struct _VEC2
{
    f32 x, y;
};

struct VEC2 : _VEC2
{
    VEC2( void ) { }
    VEC2( f32 fx, f32 fy )
    {
        x = fx;
        y = fy;
    }

    VEC2( const _VEC2 &v )
    {
        x = v.x;
        y = v.y;
    }

    VEC2( const f32 *p )
    {
        x = p[ 0 ];
        y = p[ 1 ];
    }

    VEC2 operator+( const VEC2 &rhs ) const
    {
        return VEC2( x + rhs.x, y + rhs.y );
    }

    VEC2 &operator+=( const VEC2 &rhs )
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    VEC2 operator-( void ) const
    {
        return VEC2( -x, -y );
    }

    VEC2 operator-( const VEC2 &rhs ) const
    {
        return VEC2( x - rhs.x, y - rhs.y );
    }

    VEC2 &operator-=( const VEC2 &rhs )
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    VEC2 operator*( f32 f ) const
    {
        return VEC2( x * f, y * f );
    }

    friend VEC2 operator*( f32 f, const VEC2 &v )
    {
        return VEC2( v.x * f, v.y * f );
    }

    VEC2 &operator*=( f32 f )
    {
        x *= f;
        y *= f;
        return *this;
    }

    // NOTE (vabold): This is close to the debug size in Winter Sports 2012 but not quite
    VEC2 operator/( f32 f ) const
    {
        f32 r = 1.0f / f;
        return VEC2( x * r, y * r );
    }

    // NOTE (vabold): Implementation is inferred from the other operator patterns
    VEC2 &operator/=( f32 f )
    {
        f32 r = 1.0f / f;
        x *= r;
        y *= r;
        return *this;
    }

    bool operator==( const VEC2 &rhs ) const
    {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=( const VEC2 &rhs ) const
    {
        return x != rhs.x || y != rhs.y;
    }

    operator f32 *( void )
    {
        return reinterpret_cast< f32 * >( this );
    }

    operator const f32 *( void ) const
    {
        return reinterpret_cast< const f32 * >( this );
    }

    void Report( bool bNewline, const char *name ) const;
};

/******************************************************************************
 *
 * VEC3
 *
 ******************************************************************************/

struct VEC3;

VEC3 *VEC3Add( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 );
VEC3 *VEC3Sub( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 );
VEC3 *VEC3Scale( VEC3 *pOut, const VEC3 *p, f32 scale );
VEC3 *VEC3Lerp( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2, f32 t );
f32 VEC3Dot( const VEC3 *p1, const VEC3 *p2 );
VEC3 *VEC3Cross( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 );
f32 VEC3LenSq( const VEC3 *p );
f32 VEC3Len( const VEC3 *p );
VEC3 *VEC3Normalize( VEC3 *pOut, const VEC3 *p );
f32 VEC3DistSq( const VEC3 *p1, const VEC3 *p2 );
VEC3 *VEC3Maximize( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 );
VEC3 *VEC3Minimize( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 );

VEC3 *VEC3TransformNormal( VEC3 *pOut, const MTX34 *pM, const VEC3 *pV );
VEC3 *VEC3TransformNormalArray( VEC3 *pOut, const MTX34 *pM, const VEC3 *pV, u32 count );
VEC4 *VEC3Transform( VEC4 *pOut, const MTX44 *pM, const VEC3 *pV );
VEC3 *VEC3TransformCoord( VEC3 *pOut, const MTX44 *pM, const VEC3 *pV );
VEC4 *VEC3TransformArray( VEC4 *pOut, const MTX44 *pM, const VEC3 *pV, u32 count );
VEC3 *VEC3TransformCoordArray( VEC3 *pOut, const MTX44 *pM, const VEC3 *pV, u32 count );

struct _VEC3
{
    f32 x, y, z;
};

struct VEC3 : _VEC3
{
    VEC3( void ) { }
    VEC3( f32 fx, f32 fy, f32 fz )
    {
        x = fx;
        y = fy;
        z = fz;
    }

    VEC3( const _VEC3 &v )
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    VEC3( const Vec &v )
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    VEC3( const f32 *p )
    {
        x = p[ 0 ];
        y = p[ 1 ];
        z = p[ 2 ];
    }

    VEC3 operator+( const VEC3 &rhs ) const
    {
        VEC3 tmp;
        VEC3Add( &tmp, this, &rhs );
        return tmp;
    }

    VEC3 &operator+=( const VEC3 &rhs )
    {
        VEC3Add( this, this, &rhs );
        return *this;
    }

    VEC3 operator-( void ) const
    {
        return VEC3( -x, -y, -z );
    }

    VEC3 operator-( const VEC3 &rhs ) const
    {
        VEC3 tmp;
        VEC3Sub( &tmp, this, &rhs );
        return tmp;
    }

    VEC3 &operator-=( const VEC3 &rhs )
    {
        VEC3Sub( this, this, &rhs );
        return *this;
    }

    VEC3 operator*( f32 f ) const
    {
        VEC3 tmp;
        VEC3Scale( &tmp, this, f );
        return tmp;
    }

    friend VEC3 operator*( f32 f, const VEC3 &v )
    {
        VEC3 tmp;
        VEC3Scale( &tmp, &v, f );
        return tmp;
    }

    VEC3 &operator*=( f32 f )
    {
        VEC3Scale( this, this, f );
        return *this;
    }

    VEC3 operator/( f32 f ) const
    {
        f32 r = 1.0f / f;
        return *this * r;
    }

    VEC3 &operator/=( f32 f )
    {
        return *this *= ( 1.0f / f );
    }

    bool operator==( const VEC3 &rhs ) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!=( const VEC3 &rhs ) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    operator VecPtr( void )
    {
        return reinterpret_cast< VecPtr >( this );
    }

    operator CVecPtr( void ) const
    {
        return reinterpret_cast< CVecPtr >( this );
    }

    operator f32 *( void )
    {
        return reinterpret_cast< f32 * >( this );
    }

    operator const f32 *( void ) const
    {
        return reinterpret_cast< const f32 * >( this );
    }

    f32 LenSq( void ) const
    {
        return x * x + y * y + z * z;
    }

    void Report( bool bNewline, const char *name ) const;
};

inline VEC3 *VEC3Add( register VEC3 *pOut, register const VEC3 *p1, register const VEC3 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, VEC3.x( p1 ), 0, 0;
        psq_l b, VEC3.x( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, VEC3.x( pOut ), 0, 0;
        psq_l a, VEC3.z( p1 ), 1, 0;
        psq_l b, VEC3.z( p2 ), 1, 0;
        ps_add c, a, b;
        psq_st c, VEC3.z( pOut ), 1, 0;
    );
    return pOut;
}

inline VEC3 *VEC3Sub( register VEC3 *pOut, register const VEC3 *p1, register const VEC3 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, VEC3.x( p1 ), 0, 0;
        psq_l b, VEC3.x( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, VEC3.x( pOut ), 0, 0;
        psq_l a, VEC3.z( p1 ), 1, 0;
        psq_l b, VEC3.z( p2 ), 1, 0;
        ps_sub c, a, b;
        psq_st c, VEC3.z( pOut ), 1, 0;
    );
    return pOut;
}

inline VEC3 *VEC3Scale( register VEC3 *pOut, register const VEC3 *p, register f32 scale )
{
    register f32 a, b;
    ASM
    (
        psq_l a, VEC3.x( p ), 0, 0;
        ps_muls0 b, a, scale
        psq_st b, VEC3.x( pOut ), 0, 0;
        psq_l a, VEC3.z( p ), 1, 0;
        ps_muls0 b, a, scale
        psq_st b, VEC3.z( pOut ), 1, 0;
    );
    return pOut;
}

inline VEC3 *
VEC3Lerp( register VEC3 *pOut, register const VEC3 *p1, register const VEC3 *p2, register f32 t )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, VEC3.x( p1 ), 0, 0;
        psq_l b, VEC3.x( p2 ), 0, 0;
        ps_sub c, b, a;
        ps_madds0 c, c, t, a;
        psq_st c, VEC3.x( pOut ), 0, 0;
        psq_l a, VEC3.z( p1 ), 1, 0;
        psq_l b, VEC3.z( p2 ), 1, 0;
        ps_sub c, b, a;
        ps_madds0 c, c, t, a;
        psq_st c, VEC3.z( pOut ), 1, 0;
    );
    return pOut;
}

inline f32 VEC3Dot( register const VEC3 *p1, register const VEC3 *p2 )
{
    register f32 _v1, _v2, _v3, _v4, _v5;
    ASM
    (
        psq_l _v2, VEC3.y( p1 ), 0, 0;
        psq_l _v3, VEC3.y( p2 ), 0, 0;
        ps_mul _v2, _v2, _v3;
        psq_l _v5, VEC3.x( p1 ), 1, 0;
        psq_l _v4, VEC3.x( p2 ), 1, 0;
        ps_madd _v3, _v5, _v4, _v2;
        ps_sum0 _v1, _v3, _v2, _v2;
    );
    return _v1;
}

inline VEC3 *VEC3Cross( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 )
{
    VECCrossProduct( *p1, *p2, *pOut );
    return pOut;
}

inline f32 VEC3LenSq( register const VEC3 *p )
{
    register f32 vxy, vzz, sqmag;
    ASM
    (
        psq_l vxy, VEC3.x( p ), 0, 0;
        ps_mul vxy, vxy, vxy;
        lfs vzz, VEC3.z( p );
        ps_madd sqmag, vzz, vzz, vxy;
        ps_sum0 sqmag, sqmag, vxy, vxy;
    );
    return sqmag;
}

inline f32 VEC3Len( register const VEC3 *p )
{
    return VECMag( *p );
}

inline VEC3 *VEC3Normalize( VEC3 *pOut, const VEC3 *p )
{
    VECNormalize( *p, *pOut );
    return pOut;
}

inline f32 VEC3DistSq( const VEC3 *p1, const VEC3 *p2 )
{
    return VECSquareDistance( *p1, *p2 );
}

/******************************************************************************
 *
 * VEC4
 *
 ******************************************************************************/

VEC4 *VEC4Add( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2 );
VEC4 *VEC4Sub( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2 );
VEC4 *VEC4Scale( VEC4 *pOut, const VEC4 *p, f32 scale );
VEC4 *VEC4Lerp( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2, f32 t );
f32 VEC4Dot( const VEC4 *p1, const VEC4 *p2 );
f32 VEC4LenSq( const VEC4 *p );
f32 VEC4Len( const VEC4 *p );
VEC4 *VEC4Normalize( VEC4 *pOut, const VEC4 *p );
f32 VEC4DistSq( const VEC4 *p1, const VEC4 *p2 );
VEC4 *VEC4Maximize( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2 );
VEC4 *VEC4Minimize( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2 );

VEC4 *VEC4Transform( VEC4 *pOut, const MTX44 *pM, const VEC4 *pV );
VEC4 *VEC4TransformArray( VEC4 *pOut, const MTX44 *pM, const VEC4 *pV, u32 count );

struct _VEC4
{
    f32 x, y, z, w;
};

struct VEC4 : _VEC4
{
    VEC4( void ) { }
    VEC4( f32 fx, f32 fy, f32 fz, f32 fw )
    {
        x = fx;
        y = fy;
        z = fz;
        w = fw;
    }

    VEC4( const _VEC4 &v )
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }

    VEC4( const f32 *p )
    {
        x = p[ 0 ];
        y = p[ 1 ];
        z = p[ 2 ];
        w = p[ 3 ];
    }

    VEC4 operator+( const VEC4 &rhs ) const
    {
        VEC4 tmp;
        VEC4Add( &tmp, this, &rhs );
        return tmp;
    }

    VEC4 &operator+=( const VEC4 &rhs )
    {
        VEC4Add( this, this, &rhs );
        return *this;
    }

    VEC4 operator-( void ) const
    {
        return VEC4( -x, -y, -z, -w );
    }

    VEC4 operator-( const VEC4 &rhs ) const
    {
        VEC4 tmp;
        VEC4Sub( &tmp, this, &rhs );
        return tmp;
    }

    VEC4 &operator-=( const VEC4 &rhs )
    {
        VEC4Sub( this, this, &rhs );
        return *this;
    }

    VEC4 operator*( f32 f ) const
    {
        VEC4 tmp;
        VEC4Scale( &tmp, this, f );
        return tmp;
    }

    friend VEC4 operator*( f32 f, const VEC4 &v )
    {
        VEC4 tmp;
        VEC4Scale( &tmp, &v, f );
        return tmp;
    }

    VEC4 &operator*=( f32 f )
    {
        VEC4Scale( this, this, f );
        return *this;
    }

    VEC4 operator/( f32 f ) const
    {
        f32 r = 1.0f / f;
        return *this * r;
    }

    VEC4 &operator/=( f32 f )
    {
        return *this *= ( 1.0f / f );
    }

    bool operator==( const VEC4 &rhs ) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }

    bool operator!=( const VEC4 &rhs ) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
    }

    operator f32 *( void )
    {
        return reinterpret_cast< f32 * >( this );
    }

    operator const f32 *( void ) const
    {
        return reinterpret_cast< const f32 * >( this );
    }

    void Report( bool bNewline, const char *name ) const;
};

/******************************************************************************
 *
 * QUAT
 *
 ******************************************************************************/

QUAT *QUATMult( QUAT *pOut, const QUAT *q1, const QUAT *q2 );
QUAT *QUATNormalize( QUAT *pOut, const QUAT *q );
QUAT *QUATSlerp( QUAT *pOut, const QUAT *q1, const QUAT *q2, f32 t );

struct _QUAT
{
    f32 x, y, z, w;
};

struct QUAT : _QUAT
{
    QUAT( void ) { }
    QUAT( f32 fx, f32 fy, f32 fz, f32 fw )
    {
        x = fx;
        y = fy;
        z = fz;
        w = fw;
    }

    QUAT( const _QUAT &q )
    {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
    }

    QUAT( const f32 *p )
    {
        x = p[ 0 ];
        y = p[ 1 ];
        z = p[ 2 ];
        w = p[ 3 ];
    }

    operator f32 *( void )
    {
        return reinterpret_cast< f32 * >( this );
    }

    operator const f32 *( void ) const
    {
        return reinterpret_cast< const f32 * >( this );
    }

    void Report( bool bNewline, const char *name ) const;
};

inline QUAT *QUATMult( QUAT *pOut, const QUAT *q1, const QUAT *q2 )
{
    QUATMultiply( reinterpret_cast< CQuaternionPtr >( q1 ),
            reinterpret_cast< CQuaternionPtr >( q2 ), reinterpret_cast< QuaternionPtr >( pOut ) );
    return pOut;
}

inline QUAT *QUATNormalize( QUAT *pOut, const QUAT *q )
{
    QUATNormalize( reinterpret_cast< CQuaternionPtr >( q ),
            reinterpret_cast< QuaternionPtr >( pOut ) );
    return pOut;
}

inline QUAT *QUATSlerp( QUAT *pOut, const QUAT *q1, const QUAT *q2, f32 t )
{
    QUATSlerp( reinterpret_cast< CQuaternionPtr >( q1 ), reinterpret_cast< CQuaternionPtr >( q2 ),
            reinterpret_cast< QuaternionPtr >( pOut ), t );
    return pOut;
}

/******************************************************************************
 *
 * MTX33
 *
 ******************************************************************************/

MTX33 *MTX33Copy( MTX33 *pOut, const MTX33 *p );
MTX33 *MTX33Zero( MTX33 *pOut );
MTX33 *MTX33Identity( MTX33 *pOut );
MTX33 *MTX34ToMTX33( MTX33 *pOut, const MTX34 *pM );
MTX33 *MTX33MAdd( MTX33 *pOut, f32 t, const MTX33 *p1, const MTX33 *p2 );

struct _MTX33
{
    union
    {
        struct
        {
            f32 _00, _01, _02, _10, _11, _12, _20, _21, _22;
        };
        f32 m[ 3 ][ 3 ];
        f32 a[ 9 ];
    };
};

struct MTX33 : _MTX33
{
    MTX33( void ) { }
    MTX33( const MTX34 &m )
    {
        MTX34ToMTX33( this, &m );
    }

    MTX33( f32 x00, f32 x01, f32 x02, f32 x10, f32 x11, f32 x12, f32 x20, f32 x21, f32 x22 )
    {
        _00 = x00;
        _01 = x01;
        _02 = x02;
        _10 = x10;
        _11 = x11;
        _12 = x12;
        _20 = x20;
        _21 = x21;
        _22 = x22;
    }

    MTX33( const _MTX33 &m )
    {
        _00 = m._00;
        _01 = m._01;
        _02 = m._02;
        _10 = m._10;
        _11 = m._11;
        _12 = m._12;
        _20 = m._20;
        _21 = m._21;
        _22 = m._22;
    }

    MTX33( const f32 *p )
    {
        a[ 0 ] = p[ 0 ];
        a[ 1 ] = p[ 1 ];
        a[ 2 ] = p[ 2 ];
        a[ 3 ] = p[ 3 ];
        a[ 4 ] = p[ 4 ];
        a[ 5 ] = p[ 5 ];
        a[ 6 ] = p[ 6 ];
        a[ 7 ] = p[ 7 ];
        a[ 8 ] = p[ 8 ];
    }

    operator f32 *( void )
    {
        return reinterpret_cast< f32 * >( this );
    }

    operator const f32 *( void ) const
    {
        return reinterpret_cast< const f32 * >( this );
    }

    void Report( bool bNewline, const char *name ) const;
};

/******************************************************************************
 *
 * MTX34
 *
 ******************************************************************************/

u32 MTX34InvTranspose( MTX33 *inv, const MTX34 *src );
MTX34 *MTX34Zero( MTX34 *pOut );
bool MTX34IsIdentity( const MTX34 *p );
MTX34 *MTX34Add( MTX34 *pOut, const MTX34 *p1, const MTX34 *p2 );
MTX34 *MTX34Sub( MTX34 *pOut, const MTX34 *p1, const MTX34 *p2 );
MTX34 *MTX34Mult( MTX34 *pOut, const MTX34 *p, f32 f );
MTX34 *MTX34Scale( MTX34 *pOut, const MTX34 *pM, const VEC3 *pS );
MTX34 *MTX34Trans( MTX34 *pOut, const MTX34 *pM, const VEC3 *pT );
MTX34 *MTX34MAdd( MTX34 *pOut, f32 t, const MTX34 *p1, const MTX34 *p2 );
MTX34 *MTX34RotAxisFIdx( MTX34 *pOut, const VEC3 *pAxis, f32 fIdx );
MTX34 *MTX34RotXYZFIdx( MTX34 *pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ );
MTX34 *MTX34RotXYZTransFIdx( MTX34 *pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, const VEC3 *pT );

MTX34 *MTX34Identity( MTX34 *pOut );
MTX34 *MTX34Copy( MTX34 *pOut, const MTX34 *p );
MTX34 *MTX34Mult( MTX34 *pOut, const MTX34 *p1, const MTX34 *p2 );
MTX34 *MTX34MultArray( MTX34 *pOut, const MTX34 *p1, const MTX34 *pSrc, u32 count );
u32 MTX34Inv( MTX34 *pOut, const MTX34 *p );
MTX34 *MTX34Scale( MTX34 *pOut, const VEC3 *pS, const MTX34 *pM );
MTX34 *MTX34Trans( MTX34 *pOut, const VEC3 *pT, const MTX34 *pM );
MTX34 *MTX34RotAxisRad( MTX34 *pOut, const VEC3 *pAxis, f32 fRad );
MTX34 *MTX34RotAxisDeg( MTX34 *pOut, const VEC3 *pAxis, f32 fDeg );
MTX34 *MTX34RotXYZRad( MTX34 *pOut, f32 fRadX, f32 fRadY, f32 fRadZ );
MTX34 *MTX34RotXYZDeg( MTX34 *pOut, f32 fDegX, f32 fDegY, f32 fDegZ );
MTX34 *MTX34LookAt( MTX34 *pOut, const VEC3 *pCamPos, const VEC3 *pCamUp, const VEC3 *pTarget );

struct _MTX34
{
    union
    {
        struct
        {
            f32 _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23;
        };
        f32 m[ 3 ][ 4 ];
        f32 a[ 12 ];
        Mtx mtx;
    };
};

struct MTX34 : _MTX34
{
    MTX34( void ) { }
    MTX34( f32 x00,
            f32 x01,
            f32 x02,
            f32 x03,
            f32 x10,
            f32 x11,
            f32 x12,
            f32 x13,
            f32 x20,
            f32 x21,
            f32 x22,
            f32 x23 )
    {
        _00 = x00;
        _01 = x01;
        _02 = x02;
        _03 = x03;
        _10 = x10;
        _11 = x11;
        _12 = x12;
        _13 = x13;
        _20 = x20;
        _21 = x21;
        _22 = x22;
        _23 = x23;
    }

    MTX34( const _MTX34 &m )
    {
        _00 = m._00;
        _01 = m._01;
        _02 = m._02;
        _03 = m._03;
        _10 = m._10;
        _11 = m._11;
        _12 = m._12;
        _13 = m._13;
        _20 = m._20;
        _21 = m._21;
        _22 = m._22;
        _23 = m._23;
    }

    MTX34( const f32 *p )
    {
        a[ 0 ] = p[ 0 ];
        a[ 1 ] = p[ 1 ];
        a[ 2 ] = p[ 2 ];
        a[ 3 ] = p[ 3 ];
        a[ 4 ] = p[ 4 ];
        a[ 5 ] = p[ 5 ];
        a[ 6 ] = p[ 6 ];
        a[ 7 ] = p[ 7 ];
        a[ 8 ] = p[ 8 ];
        a[ 9 ] = p[ 9 ];
        a[ 10 ] = p[ 10 ];
        a[ 11 ] = p[ 11 ];
    }

    operator MtxPtr( void )
    {
        return reinterpret_cast< MtxPtr >( this );
    }

    operator CMtxPtr( void ) const
    {
        return reinterpret_cast< CMtxPtr >( this );
    }

    operator f32 *( void )
    {
        return reinterpret_cast< f32 * >( this );
    }

    operator const f32 *( void ) const
    {
        return reinterpret_cast< const f32 * >( this );
    }

    void Report( bool bNewline, const char *name ) const;
};

inline MTX34 *MTX34Identity( MTX34 *pOut )
{
    MTXIdentity( *pOut );
    return pOut;
}

inline MTX34 *MTX34Copy( MTX34 *pOut, const MTX34 *p )
{
    MTXCopy( *p, *pOut );
    return pOut;
}

inline MTX34 *MTX34Mult( MTX34 *pOut, const MTX34 *p1, const MTX34 *p2 )
{
    MTXConcat( *p1, *p2, *pOut );
    return pOut;
}

inline MTX34 *MTX34MultArray( MTX34 *pOut, const MTX34 *p1, const MTX34 *pSrc, u32 count )
{
    MTXConcatArray( *p1, reinterpret_cast< CMtxPtr >( pSrc ), reinterpret_cast< MtxPtr >( pOut ),
            count );
    return pOut;
}

inline u32 MTX34Inv( MTX34 *pOut, const MTX34 *p )
{
    return MTXInverse( *p, *pOut );
}

inline MTX34 *MTX34Scale( MTX34 *pOut, const VEC3 *pS, const MTX34 *pM )
{
    MTXScaleApply( *pM, *pOut, pS->x, pS->y, pS->z );
    return pOut;
}

inline MTX34 *MTX34Trans( MTX34 *pOut, const VEC3 *pT, const MTX34 *pM )
{
    MTXTransApply( *pM, *pOut, pT->x, pT->y, pT->z );
    return pOut;
}

inline MTX34 *MTX34RotAxisRad( MTX34 *pOut, const VEC3 *pAxis, f32 fRad )
{
    return MTX34RotAxisFIdx( pOut, pAxis, RAD2FIDX * fRad );
}

inline MTX34 *MTX34RotAxisDeg( MTX34 *pOut, const VEC3 *pAxis, f32 fDeg )
{
    return MTX34RotAxisFIdx( pOut, pAxis, DEG2FIDX * fDeg );
}

inline MTX34 *MTX34RotXYZRad( MTX34 *pOut, f32 fRadX, f32 fRadY, f32 fRadZ )
{
    return MTX34RotXYZFIdx( pOut, RAD2FIDX * fRadX, RAD2FIDX * fRadY, RAD2FIDX * fRadZ );
}

inline MTX34 *MTX34RotXYZDeg( MTX34 *pOut, f32 fDegX, f32 fDegY, f32 fDegZ )
{
    return MTX34RotXYZFIdx( pOut, DEG2FIDX * fDegX, DEG2FIDX * fDegY, DEG2FIDX * fDegZ );
}

inline MTX34 *
MTX34LookAt( MTX34 *pOut, const VEC3 *pCamPos, const VEC3 *pCamUp, const VEC3 *pTarget )
{
    MTXLookAt( *pOut, *pCamPos, *pCamUp, *pTarget );
    return pOut;
}

/******************************************************************************
 *
 * MTX44
 *
 ******************************************************************************/

#undef MTX44Identity
#undef MTX44Copy

MTX44 *MTX44Zero( MTX44 *pOut );
MTX44 *MTX44Identity( MTX44 *pOut );
MTX44 *MTX44Copy( MTX44 *pOut, const MTX44 *p );
bool MTX44IsIdentity( const MTX44 *p );

struct _MTX44
{
    union
    {
        struct
        {
            f32 _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33;
        };
        f32 m[ 4 ][ 4 ];
        f32 a[ 16 ];
        Mtx44 mtx;
    };
};

struct MTX44 : _MTX44
{
    MTX44( void ) { }
    MTX44( f32 x00,
            f32 x01,
            f32 x02,
            f32 x03,
            f32 x10,
            f32 x11,
            f32 x12,
            f32 x13,
            f32 x20,
            f32 x21,
            f32 x22,
            f32 x23,
            f32 x30,
            f32 x31,
            f32 x32,
            f32 x33 )
    {
        _00 = x00;
        _01 = x01;
        _02 = x02;
        _03 = x03;
        _10 = x10;
        _11 = x11;
        _12 = x12;
        _13 = x13;
        _20 = x20;
        _21 = x21;
        _22 = x22;
        _23 = x23;
        _30 = x30;
        _31 = x31;
        _32 = x32;
        _33 = x33;
    }

    MTX44( const _MTX44 &m )
    {
        _00 = m._00;
        _01 = m._01;
        _02 = m._02;
        _03 = m._03;
        _10 = m._10;
        _11 = m._11;
        _12 = m._12;
        _13 = m._13;
        _20 = m._20;
        _21 = m._21;
        _22 = m._22;
        _23 = m._23;
        _30 = m._30;
        _31 = m._31;
        _32 = m._32;
        _33 = m._33;
    }

    MTX44( const f32 *p )
    {
        a[ 0 ] = p[ 0 ];
        a[ 1 ] = p[ 1 ];
        a[ 2 ] = p[ 2 ];
        a[ 3 ] = p[ 3 ];
        a[ 4 ] = p[ 4 ];
        a[ 5 ] = p[ 5 ];
        a[ 6 ] = p[ 6 ];
        a[ 7 ] = p[ 7 ];
        a[ 8 ] = p[ 8 ];
        a[ 9 ] = p[ 9 ];
        a[ 10 ] = p[ 10 ];
        a[ 11 ] = p[ 11 ];
        a[ 12 ] = p[ 12 ];
        a[ 13 ] = p[ 13 ];
        a[ 14 ] = p[ 14 ];
        a[ 15 ] = p[ 15 ];
    }

    operator Mtx44Ptr( void )
    {
        return reinterpret_cast< Mtx44Ptr >( this );
    }

    operator CMtx44Ptr( void ) const
    {
        return reinterpret_cast< CMtx44Ptr >( this );
    }

    operator f32 *( void )
    {
        return reinterpret_cast< f32 * >( this );
    }

    operator const f32 *( void ) const
    {
        return reinterpret_cast< const f32 * >( this );
    }

    void Report( bool bNewline, const char *name ) const;
};

/******************************************************************************
 *
 * Misc
 *
 ******************************************************************************/

inline MTX34 *QUATToMTX34( MTX34 *pOut, const QUAT *p )
{
    MTXQuat( *pOut, reinterpret_cast< CQuaternionPtr >( p ) );
    return pOut;
}

inline QUAT *MTX34ToQUAT( QUAT *pOut, const MTX34 *pM )
{
    QUATMtx( reinterpret_cast< QuaternionPtr >( pOut ), *pM );
    return pOut;
}

} // namespace math
} // namespace nw4r

#endif
