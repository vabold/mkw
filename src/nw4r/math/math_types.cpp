#include <nw4r/math/types.h>

#include <RVL_SDK/os.h>

#define MAXIMIZE( lhs, rhs ) \
    ( { \
        a = ( lhs ); \
        b = ( rhs ); \
        c = a - b; \
        ASM( fsel d, c, a, b; ); \
        d; \
    } )

#define MINIMIZE( lhs, rhs ) \
    ( { \
        a = ( lhs ); \
        b = ( rhs ); \
        c = b - a; \
        ASM( fsel d, c, a, b; ); \
        d; \
    } )

namespace nw4r
{
namespace math
{

VEC2 *VEC2Maximize( VEC2 *pOut, const VEC2 *p1, const VEC3 *p2 )
{
    // Required for macros
    register f32 a, b, c, d;
    pOut->x = MAXIMIZE( p1->x, p2->x );
    pOut->y = MAXIMIZE( p1->y, p2->y );
    return pOut;
}

VEC2 *VEC2Minimize( VEC2 *pOut, const VEC2 *p1, const VEC3 *p2 )
{
    // Required for macros
    register f32 a, b, c, d;
    pOut->x = MINIMIZE( p1->x, p2->x );
    pOut->y = MINIMIZE( p1->y, p2->y );
    return pOut;
}

VEC2 *VEC2Normalize( register VEC2 *pOut, register const VEC2 *p )
{
    register f32 c_half = 0.5f;
    register f32 c_three = 3.0f;
    register f32 v1_xy;
    register f32 xx_yy;
    register f32 sqsum;
    register f32 rsqrt;
    register f32 nwork0, nwork1;

    ASM
    (
        psq_l v1_xy, VEC2.x( p ), 0, 0;
        ps_mul xx_yy, v1_xy, v1_xy;
        ps_sum0 sqsum, xx_yy, xx_yy, xx_yy;
        frsqrte rsqrt, sqsum;
        fmuls nwork0, rsqrt, rsqrt;
        fmuls nwork1, rsqrt, c_half;
        fnmsubs nwork0, nwork0, sqsum, c_three;
        fmuls rsqrt, nwork0, nwork1;
        ps_muls0 v1_xy, v1_xy, rsqrt;
        psq_st v1_xy, VEC2.x( pOut ), 0, 0;
    );
    return pOut;
}

VEC3 *VEC3Maximize( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 )
{
    // Required for macros
    register f32 a, b, c, d;
    pOut->x = MAXIMIZE( p1->x, p2->x );
    pOut->y = MAXIMIZE( p1->y, p2->y );
    pOut->z = MAXIMIZE( p1->z, p2->z );
    return pOut;
}

VEC3 *VEC3Minimize( VEC3 *pOut, const VEC3 *p1, const VEC3 *p2 )
{
    // Required for macros
    register f32 a, b, c, d;
    pOut->x = MINIMIZE( p1->x, p2->x );
    pOut->y = MINIMIZE( p1->y, p2->y );
    pOut->z = MINIMIZE( p1->z, p2->z );
    return pOut;
}

VEC4 *VEC4Add( register VEC4 *pOut, register const VEC4 *p1, register const VEC4 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, VEC4.x( p1 ), 0, 0;
        psq_l b, VEC4.x( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, VEC4.x( pOut ), 0, 0;
        psq_l a, VEC4.z( p1 ), 0, 0;
        psq_l b, VEC4.z( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, VEC4.z( pOut ), 0, 0;
    );
    return pOut;
}

VEC4 *VEC4Sub( register VEC4 *pOut, register const VEC4 *p1, register const VEC4 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, VEC4.x( p1 ), 0, 0;
        psq_l b, VEC4.x( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, VEC4.x( pOut ), 0, 0;
        psq_l a, VEC4.z( p1 ), 0, 0;
        psq_l b, VEC4.z( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, VEC4.z( pOut ), 0, 0;
    );
    return pOut;
}

VEC4 *VEC4Scale( register VEC4 *pOut, register const VEC4 *p, register f32 scale )
{
    register f32 a, b;
    ASM
    (
        psq_l a, VEC4.x( p ), 0, 0;
        ps_muls0 b, a, scale;
        psq_st b, VEC4.x( pOut ), 0, 0;
        psq_l a, VEC4.z( p ), 0, 0;
        ps_muls0 b, a, scale;
        psq_st b, VEC4.z( pOut ), 0, 0;
    );
    return pOut;
}

VEC4 *VEC4Lerp( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2, f32 t )
{
    pOut->x = p1->x + t * ( p2->x - p1->x );
    pOut->y = p1->y + t * ( p2->y - p1->y );
    pOut->z = p1->z + t * ( p2->z - p1->z );
    pOut->w = p1->w + t * ( p2->w - p1->w );
    return pOut;
}

f32 VEC4Dot( register const VEC4 *p1, register const VEC4 *p2 )
{
    register f32 _v1, _v2, _v3, _v4, _v5;
    ASM
    (
        psq_l _v2, VEC4.x( p1 ), 0, 0;
        psq_l _v3, VEC4.x( p2 ), 0, 0;
        ps_mul _v2, _v2, _v3;
        psq_l _v5, VEC4.z( p1 ), 0, 0;
        psq_l _v4, VEC4.z( p2 ), 0, 0;
        ps_mul _v5, _v5, _v4;
        ps_add _v1, _v2, _v5;
        ps_sum0 _v1, _v1, _v1, _v1;
    );
    return _v1;
}

f32 VEC4LenSq( register const VEC4 *p )
{
    register f32 vxy, vzw, sqmag;
    ASM
    (
        psq_l vxy, VEC4.x( p ), 0, 0;
        ps_mul vxy, vxy, vxy;
        psq_l vzw, VEC4.z( p ), 0, 0;
        ps_madd sqmag, vzw, vzw, vxy;
        ps_sum0 sqmag, sqmag, sqmag, sqmag;
    );
    return sqmag;
}

f32 VEC4Len( register const VEC4 *p )
{
    register f32 vxy, vzw, sqmag;
    register f32 rmag, nwork0, nwork1;
    register f32 c_three, c_half, c_zero;

    c_half = 0.5f;

    ASM
    (
        psq_l vxy, VEC4.x( p ), 0, 0;
        ps_mul vxy, vxy, vxy;
        psq_l vzw, VEC4.z( p ), 0, 0;
        fsubs c_zero, c_half, c_half;
        ps_madd sqmag, vzw, vzw, vxy;
        ps_sum0 sqmag, sqmag, sqmag, sqmag;
        fcmpu cr0, sqmag, c_zero;
        beq end;
        frsqrte rmag, sqmag;
    );
    c_three = 3.0f;

    ASM
    (
        fmuls nwork0, rmag, rmag;
        fmuls nwork1, rmag, c_half;
        fnmsubs nwork0, nwork0, sqmag, c_three;
        fmuls rmag, nwork0, nwork1;
        fmuls sqmag, sqmag, rmag;
    end:
    );

    return sqmag;
}

VEC4 *VEC4Normalize( register VEC4 *pOut, register const VEC4 *p )
{
    register f32 c_half = 0.5f;
    register f32 c_three = 3.0f;
    register f32 v1_xy, v1_zw;
    register f32 xx_zz_yy_ww, xx_yy;
    register f32 sqsum;
    register f32 rsqrt;
    register f32 nwork0, nwork1;

    ASM
    (
        psq_l v1_xy, VEC4.x( p ), 0, 0;
        ps_mul xx_yy, v1_xy, v1_xy;
        psq_l v1_zw, VEC4.z( p ), 0, 0;
        ps_madd xx_zz_yy_ww, v1_zw, v1_zw, xx_yy;
        ps_sum0 sqsum, xx_zz_yy_ww, xx_zz_yy_ww, xx_zz_yy_ww;
        frsqrte rsqrt, sqsum;
        fmuls nwork0, rsqrt, rsqrt;
        fmuls nwork1, rsqrt, c_half;
        fnmsubs nwork0, nwork0, sqsum, c_three;
        fmuls rsqrt, nwork0, nwork1;
        ps_muls0 v1_xy, v1_xy, rsqrt;
        psq_st v1_xy, VEC4.x( pOut ), 0, 0;
        ps_muls0 v1_zw, v1_zw, rsqrt;
        psq_st v1_zw, VEC4.z( pOut ), 0, 0;
    );

    return pOut;
}

f32 VEC4DistSq( register const VEC4 *p1, register const VEC4 *p2 )
{
    register f32 _v1, _v2, vxy, vzw, sqmag;

    ASM
    (
        psq_l _v1, VEC4.x( p1 ), 0, 0;
        psq_l _v2, VEC4.x( p2 ), 0, 0;
        ps_sub vxy, _v1, _v2;
        ps_mul vxy, vxy, vxy;
        psq_l _v1, VEC4.z( p1 ), 0, 0;
        psq_l _v2, VEC4.z( p2 ), 0, 0;
        ps_sub vzw, _v1, _v2;
        ps_madd sqmag, vzw, vzw, vxy;
        ps_sum0 sqmag, sqmag, sqmag, sqmag;
    );

    return sqmag;
}

VEC4 *VEC4Maximize( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2 )
{
    // Required for macros
    register f32 a, b, c, d;
    pOut->x = MAXIMIZE( p1->x, p2->x );
    pOut->y = MAXIMIZE( p1->y, p2->y );
    pOut->z = MAXIMIZE( p1->z, p2->z );
    pOut->w = MAXIMIZE( p1->w, p2->w );
    return pOut;
}

VEC4 *VEC4Minimize( VEC4 *pOut, const VEC4 *p1, const VEC4 *p2 )
{
    // Required for macros
    register f32 a, b, c, d;
    pOut->x = MINIMIZE( p1->x, p2->x );
    pOut->y = MINIMIZE( p1->y, p2->y );
    pOut->z = MINIMIZE( p1->z, p2->z );
    pOut->w = MINIMIZE( p1->w, p2->w );
    return pOut;
}

MTX33 *MTX33Copy( register MTX33 *pOut, register const MTX33 *p )
{
    register f32 _fp0, _fp1, _fp2, _fp3, _fp4;
    ASM
    (
        psq_l _fp0, MTX33._00( p ), 0, 0;
        psq_st _fp0, MTX33._00( pOut ), 0, 0;
        psq_l _fp1, MTX33._02( p ), 0, 0;
        psq_st _fp1, MTX33._02( pOut ), 0, 0;
        psq_l _fp2, MTX33._11( p ), 0, 0;
        psq_st _fp2, MTX33._11( pOut ), 0, 0;
        psq_l _fp3, MTX33._20( p ), 0, 0;
        psq_st _fp3, MTX33._20( pOut ), 0, 0;
        psq_l _fp4, MTX33._22( p ), 1, 0;
        psq_st _fp4, MTX33._22( pOut ), 1, 0;
    );
    return pOut;
}

MTX33 *MTX33Zero( register MTX33 *pOut )
{
    register f32 zero = 0.0f;
    ASM
    (
        psq_st zero, MTX33._00( pOut ), 0, 0;
        psq_st zero, MTX33._02( pOut ), 0, 0;
        psq_st zero, MTX33._11( pOut ), 0, 0;
        psq_st zero, MTX33._20( pOut ), 0, 0;
        psq_st zero, MTX33._22( pOut ), 1, 0;
    );
    return pOut;
}

MTX33 *MTX33Identity( register MTX33 *pOut )
{
    register f32 c_00 = 0.0f;
    register f32 c_11 = 1.0f;
    register f32 c_10;
    ASM
    (
        ps_merge00 c_10, c_11, c_00;
        psq_st c_10, MTX33._00( pOut ), 0, 0;
        psq_st c_00, MTX33._02( pOut ), 0, 0;
        psq_st c_10, MTX33._11( pOut ), 0, 0;
        psq_st c_00, MTX33._20( pOut ), 0, 0;
        stfs c_11, MTX33._22( pOut );
    );
    return pOut;
}

MTX33 *MTX34ToMTX33( register MTX33 *pOut, register const MTX34 *pM )
{
    register f32 _fp0, _fp1, _fp2, _fp3, _fp4, _fp5;
    ASM
    (
        psq_l _fp0, MTX34._00( pM ), 0, 0;
        psq_st _fp0, MTX33._00( pOut ), 0, 0;
        psq_l _fp1, MTX34._02( pM ), 0, 0;
        psq_st _fp1, MTX33._02( pOut ), 1, 0;
        psq_l _fp2, MTX34._10( pM ), 0, 0;
        psq_st _fp2, MTX33._10( pOut ), 0, 0;
        psq_l _fp3, MTX34._12( pM ), 0, 0;
        psq_st _fp3, MTX33._12( pOut ), 1, 0;
        psq_l _fp4, MTX34._20( pM ), 0, 0;
        psq_st _fp4, MTX33._20( pOut ), 0, 0;
        psq_l _fp5, MTX34._22( pM ), 0, 0;
        psq_st _fp5, MTX33._22( pOut ), 1, 0;
    );
    return pOut;
}

MTX33 *MTX33MAdd( register MTX33 *pOut,
        register f32 t,
        register const MTX33 *p1,
        register const MTX33 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, MTX33._00( p1 ), 0, 0;
        psq_l b, MTX33._00( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX33._00( pOut ), 0, 0;
        psq_l a, MTX33._02( p1 ), 0, 0;
        psq_l b, MTX33._02( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX33._02( pOut ), 0, 0;
        psq_l a, MTX33._11( p1 ), 0, 0;
        psq_l b, MTX33._11( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX33._11( pOut ), 0, 0;
        psq_l a, MTX33._20( p1 ), 0, 0;
        psq_l b, MTX33._20( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX33._20( pOut ), 0, 0;
        psq_l a, MTX33._22( p1 ), 1, 0;
        psq_l b, MTX33._22( p2 ), 1, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX33._22( pOut ), 1, 0;
    );
    return pOut;
}

asm u32 MTX34InvTranspose( register MTX33 *inv, register const MTX34 *src )
{
    psq_l f0, MTX34._00( src ), 1, 0;
    psq_l f1, MTX34._01( src ), 0, 0;
    psq_l f2, MTX34._10( src ), 1, 0;
    ps_merge10 f6, f1, f0;
    psq_l f3, MTX34._11( src ), 0, 0;
    psq_l f4, MTX34._20( src ), 1, 0;
    ps_merge10 f7, f3, f2;
    psq_l f5, MTX34._21( src ), 0, 0;
    ps_mul f11, f3, f6;
    ps_merge10 f8, f5, f4;
    ps_mul f13, f5, f7;
    ps_msub f11, f1, f7, f11;
    ps_mul f12, f1, f8;
    ps_msub f13, f3, f8, f13;
    ps_msub f12, f5, f6, f12;
    ps_mul f10, f3, f4;
    ps_mul f9, f0, f5;
    ps_mul f8, f1, f2;
    ps_msub f10, f2, f5, f10;
    ps_msub f9, f1, f4, f9;
    ps_msub f8, f0, f3, f8;
    ps_mul f7, f0, f13;
    ps_sub f1, f1, f1;
    ps_madd f7, f2, f12, f7;
    ps_madd f7, f4, f11, f7;
    ps_cmpo0 cr0, f7, f1;
    bne nonsingular;

    li r3, 0x0;
    blr;

nonsingular:
    fres f0, f7;
    ps_add f6, f0, f0;
    ps_mul f5, f0, f0;
    ps_nmsub f0, f7, f5, f6;
    ps_add f6, f0, f0;
    ps_mul f5, f0, f0;
    ps_nmsub f0, f7, f5, f6;
    ps_muls0 f13, f13, f0;
    ps_muls0 f12, f12, f0;
    psq_st f13, MTX33._00( inv ), 0, 0;
    ps_muls0 f11, f11, f0;
    psq_st f12, MTX33._10( inv ), 0, 0;
    ps_muls0 f10, f10, f0;
    psq_st f11, MTX33._20( inv ), 0, 0;
    ps_muls0 f9, f9, f0;
    psq_st f10, MTX33._02( inv ), 1, 0;
    ps_muls0 f8, f8, f0;
    psq_st f9, MTX33._12( inv ), 1, 0;
    psq_st f8, MTX33._22( inv ), 1, 0;

    li r3, 0x1;
    blr;
}

MTX34 *MTX34Zero( register MTX34 *pOut )
{
    register f32 zero = 0.0f;
    ASM
    (
        psq_st zero, MTX34._00( pOut ), 0, 0;
        psq_st zero, MTX34._02( pOut ), 0, 0;
        psq_st zero, MTX34._10( pOut ), 0, 0;
        psq_st zero, MTX34._12( pOut ), 0, 0;
        psq_st zero, MTX34._20( pOut ), 0, 0;
        psq_st zero, MTX34._22( pOut ), 0, 0;
    );
    return pOut;
}

bool MTX34IsIdentity( const MTX34 *p )
{
    return p->_00 == 1.0f && p->_01 == 0.0f && p->_02 == 0.0f && p->_03 == 0.0f && p->_10 == 0.0f &&
            p->_11 == 1.0f && p->_12 == 0.0f && p->_13 == 0.0f && p->_20 == 0.0f &&
            p->_21 == 0.0f && p->_22 == 1.0f && p->_23 == 0.0f;
}

MTX34 *MTX34Add( register MTX34 *pOut, register const MTX34 *p1, register const MTX34 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, MTX34._00( p1 ), 0, 0;
        psq_l b, MTX34._00( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, MTX34._00( pOut ), 0, 0;
        psq_l a, MTX34._02( p1 ), 0, 0;
        psq_l b, MTX34._02( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, MTX34._02( pOut ), 0, 0;
        psq_l a, MTX34._10( p1 ), 0, 0;
        psq_l b, MTX34._10( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, MTX34._10( pOut ), 0, 0;
        psq_l a, MTX34._12( p1 ), 0, 0;
        psq_l b, MTX34._12( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, MTX34._12( pOut ), 0, 0;
        psq_l a, MTX34._20( p1 ), 0, 0;
        psq_l b, MTX34._20( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, MTX34._20( pOut ), 0, 0;
        psq_l a, MTX34._22( p1 ), 0, 0;
        psq_l b, MTX34._22( p2 ), 0, 0;
        ps_add c, a, b;
        psq_st c, MTX34._22( pOut ), 0, 0;
    );
    return pOut;
}

MTX34 *MTX34Sub( register MTX34 *pOut, register const MTX34 *p1, register const MTX34 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, MTX34._00( p1 ), 0, 0;
        psq_l b, MTX34._00( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, MTX34._00( pOut ), 0, 0;
        psq_l a, MTX34._02( p1 ), 0, 0;
        psq_l b, MTX34._02( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, MTX34._02( pOut ), 0, 0;
        psq_l a, MTX34._10( p1 ), 0, 0;
        psq_l b, MTX34._10( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, MTX34._10( pOut ), 0, 0;
        psq_l a, MTX34._12( p1 ), 0, 0;
        psq_l b, MTX34._12( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, MTX34._12( pOut ), 0, 0;
        psq_l a, MTX34._20( p1 ), 0, 0;
        psq_l b, MTX34._20( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, MTX34._20( pOut ), 0, 0;
        psq_l a, MTX34._22( p1 ), 0, 0;
        psq_l b, MTX34._22( p2 ), 0, 0;
        ps_sub c, a, b;
        psq_st c, MTX34._22( pOut ), 0, 0;
    );
    return pOut;
}

MTX34 *MTX34Mult( register MTX34 *pOut, register const MTX34 *p, register f32 f )
{
    register f32 a, b;
    ASM
    (
        psq_l a, MTX34._00( p ), 0, 0;
        ps_muls0 b, a, f;
        psq_st b, MTX34._00( pOut ), 0, 0;
        psq_l a, MTX34._02( p ), 0, 0;
        ps_muls0 b, a, f;
        psq_st b, MTX34._02( pOut ), 0, 0;
        psq_l a, MTX34._10( p ), 0, 0;
        ps_muls0 b, a, f;
        psq_st b, MTX34._10( pOut ), 0, 0;
        psq_l a, MTX34._12( p ), 0, 0;
        ps_muls0 b, a, f;
        psq_st b, MTX34._12( pOut ), 0, 0;
        psq_l a, MTX34._20( p ), 0, 0;
        ps_muls0 b, a, f;
        psq_st b, MTX34._20( pOut ), 0, 0;
        psq_l a, MTX34._22( p ), 0, 0;
        ps_muls0 b, a, f;
        psq_st b, MTX34._22( pOut ), 0, 0;
    );
    return pOut;
}

MTX34 *MTX34Scale( register MTX34 *pOut, register const MTX34 *pM, register const VEC3 *pS )
{
    register f32 xy, z1;
    register f32 row0a, row0b;
    register f32 row1a, row1b;
    register f32 row2a, row2b;
    ASM
    (
        psq_l xy, VEC3.x( pS ), 0, 0;
        psq_l z1, VEC3.z( pS ), 1, 0;
        psq_l row0a, MTX34._00( pM ), 0, 0;
        psq_l row0b, MTX34._02( pM ), 0, 0;
        psq_l row1a, MTX34._10( pM ), 0, 0;
        psq_l row1b, MTX34._12( pM ), 0, 0;
        psq_l row2a, MTX34._20( pM ), 0, 0;
        psq_l row2b, MTX34._22( pM ), 0, 0;
        ps_mul row0a, row0a, xy;
        ps_mul row1a, row1a, xy;
        ps_mul row2a, row2a, xy;
        ps_mul row0b, row0b, z1;
        ps_mul row1b, row1b, z1;
        ps_mul row2b, row2b, z1;
        psq_st row0a, MTX34._00( pOut ), 0, 0;
        psq_st row0b, MTX34._02( pOut ), 0, 0;
        psq_st row1a, MTX34._10( pOut ), 0, 0;
        psq_st row1b, MTX34._12( pOut ), 0, 0;
        psq_st row2a, MTX34._20( pOut ), 0, 0;
        psq_st row2b, MTX34._22( pOut ), 0, 0;
    );
    return pOut;
}

MTX34 *MTX34Trans( register MTX34 *pOut, register const MTX34 *pM, register const VEC3 *pT )
{
    register f32 xy, z1;
    register f32 vv0, vv1, vv2, vv3, vv4, vv5;
    register f32 tmp0, tmp1, tmp2;
    ASM
    (
        psq_l vv0, MTX34._00( pM ), 0, 0;
        psq_st vv0, MTX34._00( pOut ), 0, 0;
        psq_l vv1, MTX34._02( pM ), 0, 0;
        psq_st vv1, MTX34._02( pOut ), 0, 0;
        psq_l vv2, MTX34._10( pM ), 0, 0;
        psq_st vv2, MTX34._10( pOut ), 0, 0;
        psq_l vv3, MTX34._12( pM ), 0, 0;
        psq_st vv3, MTX34._12( pOut ), 0, 0;
        psq_l vv4, MTX34._20( pM ), 0, 0;
        psq_st vv4, MTX34._20( pOut ), 0, 0;
        psq_l vv5, MTX34._22( pM ), 0, 0;
        psq_st vv5, MTX34._22( pOut ), 0, 0;
        psq_l xy, VEC3.x( pT ), 0, 0;
        psq_l z1, VEC3.z( pT ), 1, 0;
        ps_mul tmp0, vv0, xy;
        ps_madd tmp1, vv1, z1, tmp0;
        ps_sum0 tmp2, tmp1, tmp2, tmp1;
        psq_st tmp2, MTX34._03( pOut ), 1, 0;
        ps_mul tmp0, vv2, xy;
        ps_madd tmp1, vv3, z1, tmp0;
        ps_sum0 tmp2, tmp1, tmp2, tmp1;
        psq_st tmp2, MTX34._13( pOut ), 1, 0;
        ps_mul tmp0, vv4, xy;
        ps_madd tmp1, vv5, z1, tmp0;
        ps_sum0 tmp2, tmp1, tmp2, tmp1;
        psq_st tmp2, MTX34._23( pOut ), 1, 0;
    );
    return pOut;
}

MTX34 *MTX34MAdd( register MTX34 *pOut,
        register f32 t,
        register const MTX34 *p1,
        register const MTX34 *p2 )
{
    register f32 a, b, c;
    ASM
    (
        psq_l a, MTX34._00( p1 ), 0, 0;
        psq_l b, MTX34._00( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX34._00( pOut ), 0, 0;
        psq_l a, MTX34._02( p1 ), 0, 0;
        psq_l b, MTX34._02( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX34._02( pOut ), 0, 0;
        psq_l a, MTX34._10( p1 ), 0, 0;
        psq_l b, MTX34._10( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX34._10( pOut ), 0, 0;
        psq_l a, MTX34._12( p1 ), 0, 0;
        psq_l b, MTX34._12( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX34._12( pOut ), 0, 0;
        psq_l a, MTX34._20( p1 ), 0, 0;
        psq_l b, MTX34._20( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX34._20( pOut ), 0, 0;
        psq_l a, MTX34._22( p1 ), 0, 0;
        psq_l b, MTX34._22( p2 ), 0, 0;
        ps_muls0 a, a, t;
        ps_add c, a, b;
        psq_st c, MTX34._22( pOut ), 0, 0;
    );
    return pOut;
}

MTX34 *MTX34RotAxisFIdx( MTX34 *pOut, const VEC3 *pAxis, f32 fIdx )
{
    MTXRotAxisRad( *pOut, *pAxis, fIdx * FIDX2RAD );
    return pOut;
}

// SinCosSample processing

#define SIN_VAL 0x0
#define COS_VAL 0x4
#define SIN_DELTA 0x8
#define COS_DELTA 0xc

MTX34 *
MTX34RotXYZFIdx( register MTX34 *pOut, register f32 fIdxX, register f32 fIdxY, register f32 fIdxZ )
{
    register __vec2x32float__ sincosx, sincosy, sincosz;
    register __vec2x32float__ sincosxneg, mcosxsinx;
    register __vec2x32float__ scx_sinz, scz_cosy;
    register __vec2x32float__ res;
    register f32 c_zero;
    register __vec2x32float__ mf11f21, f22mf12;

    {
        // Sincos variable loading
        register u32 idxXY, idxZ;
        register const f32 *pTblBase = reinterpret_cast< const f32 * >( &detail::gSinCosTbl );
        register f32 *pTbl, *pTblY;
        register __vec2x32float__ c_idxmax = 65536.0f;
        register __vec2x32float__ c_idxmaxneg;
        register __vec2x32float__ c_zero;
        register __vec2x32float__ abs_fidxXY;
        register f32 abs_fidxZ;
        register __vec2x32float__ fidxXY;
        // r is a holdover from SinCosFIdx
        register __vec2x32float__ r, scval, scdel;
        register f32 work;
        register f32 *pTmp;
        register f32 tmp;
        pTmp = &tmp;

        ASM
        (
            // NOTE: Nintendo must have thought the float would only load into ps0
            ps_merge00 c_idxmax, c_idxmax, c_idxmax;
            ps_neg c_idxmaxneg, c_idxmax;
            ps_sub c_zero, c_idxmax, c_idxmax;
            ps_merge00 fidxXY, fIdxX, fIdxY;
            ps_abs abs_fidxXY, fidxXY;
            ps_cmpu0 cr0, abs_fidxXY, c_idxmax;
            ble x_in_domain;

        x_loop:
            ps_sum0 abs_fidxXY, abs_fidxXY, abs_fidxXY, c_idxmaxneg;
            ps_cmpu0 cr0, abs_fidxXY, c_idxmax;
            bgt x_loop;

        x_in_domain:
            ps_cmpu1 cr0, abs_fidxXY, c_idxmax;
            ble y_in_domain;
            ps_merge10 abs_fidxXY, abs_fidxXY, abs_fidxXY; // Process ps0 instead of ps1

        y_loop:
            ps_sum0 abs_fidxXY, abs_fidxXY, abs_fidxXY, c_idxmaxneg;
            ps_cmpu0 cr0, abs_fidxXY, c_idxmax;
            bgt y_loop;
            ps_merge10 abs_fidxXY, abs_fidxXY, abs_fidxXY; // Swap ps0 and ps1 back to normal

        y_in_domain:
            // Paired u16s with idxX in high bytes and idxY in low bytes
            psq_st abs_fidxXY, 0x0( pTmp ), 0, 3;
            psq_l r, 0x0( pTmp ), 0, 3;
            fabs abs_fidxZ, fIdxZ;
            fcmpu cr0, abs_fidxZ, c_idxmax;
            lwz idxXY, 0x0( pTmp );
            ble z_in_domain;

        z_loop:
            fsubs abs_fidxZ, abs_fidxZ, c_idxmax;
            fcmpu cr0, abs_fidxZ, c_idxmax;
            bgt z_loop;

        z_in_domain:
            // Single u16 with idxZ in high bytes
            psq_st abs_fidxZ, 0x0( pTmp ), 1, 3;
            ps_sub r, abs_fidxXY, r;
            // ps0 - ( idxX & 0xff ) * sizeof( SinCosSample )
            rlwinm pTbl, idxXY, 0x14, 0x14, 0x1b;
            add pTbl, pTblBase, pTbl;
            psq_l scval, SIN_VAL( pTbl ), 0, 0;
            // ps1 - ( idxY & 0xff ) * sizeof( SinCosSample )
            rlwinm pTblY, idxXY, 0x4, 0x14, 0x1b;
            psq_l scdel, SIN_DELTA( pTbl ), 0, 0;
            add pTblY, pTblBase, pTblY;
            ps_madds0 sincosx, scdel, r, scval;
            psq_l scval, SIN_VAL( pTblY ), 0, 0;
            ps_cmpu0 cr0, fidxXY, c_zero;
            psq_l scdel, SIN_DELTA( pTblY ), 0, 0;
            lhz idxZ, 0x0( pTmp );
            bge x_fixed;
            ps_neg work, sincosx;
            ps_merge01 sincosx, work, sincosx;

        x_fixed:
            ps_madds1 sincosy, scdel, r, scval;
            psq_l r, 0x0( pTmp ), 1, 3;
            // ( idxZ & 0xff ) * sizeof( SinCosSample )
            rlwinm idxZ, idxZ, 0x4, 0x14, 0x1b;
            ps_cmpu1 cr0, fidxXY, c_zero;
            add pTbl, pTblBase, idxZ;
            psq_l scval, SIN_VAL( pTbl ), 0, 0;
            fsubs r, abs_fidxZ, r;
            psq_l scdel, SIN_DELTA( pTbl ), 0, 0;
            bge y_fixed;
            ps_neg work, sincosy;
            ps_merge01 sincosy, work, sincosy;

        y_fixed:
            ps_madds0 sincosz, scdel, r, scval;
            fcmpu cr0, fIdxZ, c_zero;
            bge z_fixed;
            ps_neg work, sincosz;
            ps_merge01 sincosz, work, sincosz;

        z_fixed:
        );
    }

    ASM
    (
        ps_sub c_zero, sincosx, sincosx;
        psq_st c_zero, MTX34._23( pOut ), 1, 0;
        ps_neg sincosxneg, sincosx;
        ps_merge10 mcosxsinx, sincosxneg, sincosx;
        ps_muls0 scx_sinz, sincosx, sincosz;
        ps_muls1 scz_cosy, sincosz, sincosy;
        ps_merge10 res, scz_cosy, scz_cosy;
        psq_st res, MTX34._00( pOut ), 1, 0;
        ps_muls1 res, sincosx, sincosz;
        ps_muls0 mf11f21, mcosxsinx, sincosz;
        ps_madds0 res, res, sincosy, mf11f21;
        psq_st res, MTX34._01( pOut ), 0, 0;
        ps_merge00 res, c_zero, scz_cosy;
        psq_st res, MTX34._03( pOut ), 0, 0;
        ps_muls1 f22mf12, mcosxsinx, sincosz;
        ps_neg f22mf12, f22mf12;
        ps_madds0 res, scx_sinz, sincosy, f22mf12;
        psq_st res, MTX34._11( pOut ), 0, 0;
        ps_neg res, sincosy;
        ps_merge00 res, c_zero, res;
        psq_st res, MTX34._13( pOut ), 0, 0;
        ps_muls1 res, sincosx, sincosy;
        psq_st res, MTX34._21( pOut ), 0, 0;
    );

    return pOut;
}

MTX34 *MTX34RotXYZTransFIdx( MTX34 *pOut, f32 fIdxX, f32 fIdxY, f32 fIdxZ, const VEC3 *pT )
{
    MTX34RotXYZFIdx( pOut, fIdxX, fIdxY, fIdxZ );
    pOut->_03 = pT->x;
    pOut->_13 = pT->y;
    pOut->_23 = pT->z;
    return pOut;
}

VEC3 *VEC3TransformNormal( VEC3 *pOut, const MTX34 *pM, const VEC3 *pV )
{
    VEC3 tmp;
    tmp.x = pM->_00 * pV->x + pM->_01 * pV->y + pM->_02 * pV->z;
    tmp.y = pM->_10 * pV->x + pM->_11 * pV->y + pM->_12 * pV->z;
    tmp.z = pM->_20 * pV->x + pM->_21 * pV->y + pM->_22 * pV->z;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    return pOut;
}

VEC3 *VEC3TransformNormalArray( VEC3 *pOut, const MTX34 *pM, const VEC3 *pV, u32 count )
{
    u32 i;
    VEC3 tmp;
    VEC3 *pDst = pOut;

    for( i = 0; i < count; ++i )
    {
        tmp.x = pM->_00 * pV->x + pM->_01 * pV->y + pM->_02 * pV->z;
        tmp.y = pM->_10 * pV->x + pM->_11 * pV->y + pM->_12 * pV->z;
        tmp.z = pM->_20 * pV->x + pM->_21 * pV->y + pM->_22 * pV->z;

        pDst->x = tmp.x;
        pDst->y = tmp.y;
        pDst->z = tmp.z;
        ++pV;
        ++pDst;
    }

    return pOut;
}

MTX44 *MTX44Zero( register MTX44 *pOut )
{
    register f32 zero = 0.0f;
    ASM
    (
        psq_st zero, MTX44._00( pOut ), 0, 0;
        psq_st zero, MTX44._02( pOut ), 0, 0;
        psq_st zero, MTX44._10( pOut ), 0, 0;
        psq_st zero, MTX44._12( pOut ), 0, 0;
        psq_st zero, MTX44._20( pOut ), 0, 0;
        psq_st zero, MTX44._22( pOut ), 0, 0;
        psq_st zero, MTX44._30( pOut ), 0, 0;
        psq_st zero, MTX44._32( pOut ), 0, 0;
    );
    return pOut;
}

MTX44 *MTX44Identity( register MTX44 *pOut )
{
    register f32 c_zero = 0.0f;
    register f32 c_one = 1.0f;
    register f32 c_01;
    register f32 c_10;
    ASM
    (
        psq_st c_zero, MTX44._02( pOut ), 0, 0;
        ps_merge01 c_01, c_zero, c_one;
        psq_st c_zero, MTX44._12( pOut ), 0, 0;
        ps_merge10 c_10, c_one, c_zero;
        psq_st c_zero, MTX44._20( pOut ), 0, 0;
        psq_st c_01, MTX44._10( pOut ), 0, 0;
        psq_st c_10, MTX44._00( pOut ), 0, 0;
        psq_st c_10, MTX44._22( pOut ), 0, 0;
        psq_st c_zero, MTX44._30( pOut ), 0, 0;
        psq_st c_01, MTX44._32( pOut ), 0, 0;
    );
    return pOut;
}

MTX44 *MTX44Copy( register MTX44 *pOut, register const MTX44 *p )
{
    register f32 _0, _1, _2, _3, _4, _5, _6, _7;
    ASM
    (
        psq_l _0, MTX44._00( p ), 0, 0;
        psq_st _0, MTX44._00( pOut ), 0, 0;
        psq_l _1, MTX44._02( p ), 0, 0;
        psq_st _1, MTX44._02( pOut ), 0, 0;
        psq_l _2, MTX44._10( p ), 0, 0;
        psq_st _2, MTX44._10( pOut ), 0, 0;
        psq_l _3, MTX44._12( p ), 0, 0;
        psq_st _3, MTX44._12( pOut ), 0, 0;
        psq_l _4, MTX44._20( p ), 0, 0;
        psq_st _4, MTX44._20( pOut ), 0, 0;
        psq_l _5, MTX44._22( p ), 0, 0;
        psq_st _5, MTX44._22( pOut ), 0, 0;
        psq_l _6, MTX44._30( p ), 0, 0;
        psq_st _6, MTX44._30( pOut ), 0, 0;
        psq_l _7, MTX44._32( p ), 0, 0;
        psq_st _7, MTX44._32( pOut ), 0, 0;
    );
    return pOut;
}

bool MTX44IsIdentity( const MTX44 *p )
{
    return p->_00 == 1.0f && p->_01 == 0.0f && p->_02 == 0.0f && p->_03 == 0.0f && p->_10 == 0.0f &&
            p->_11 == 1.0f && p->_12 == 0.0f && p->_13 == 0.0f && p->_20 == 0.0f &&
            p->_21 == 0.0f && p->_22 == 1.0f && p->_23 == 0.0f && p->_30 == 0.0f &&
            p->_31 == 0.0f && p->_32 == 0.0f && p->_33 == 1.0f;
}

VEC4 *VEC3Transform( VEC4 *pOut, const MTX44 *pM, const VEC3 *pV )
{
    VEC4 tmp;
    tmp.x = pM->_00 * pV->x + pM->_01 * pV->y + pM->_02 * pV->z + pM->_03;
    tmp.y = pM->_10 * pV->x + pM->_11 * pV->y + pM->_12 * pV->z + pM->_13;
    tmp.z = pM->_20 * pV->x + pM->_21 * pV->y + pM->_22 * pV->z + pM->_23;
    tmp.w = pM->_30 * pV->x + pM->_31 * pV->y + pM->_32 * pV->z + pM->_33;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    pOut->w = tmp.w;
    return pOut;
}

VEC3 *VEC3TransformCoord( VEC3 *pOut, const MTX44 *pM, const VEC3 *pV )
{
    VEC3 tmp;
    tmp.x = pM->_00 * pV->x + pM->_01 * pV->y + pM->_02 * pV->z + pM->_03;
    tmp.y = pM->_10 * pV->x + pM->_11 * pV->y + pM->_12 * pV->z + pM->_13;
    tmp.z = pM->_20 * pV->x + pM->_21 * pV->y + pM->_22 * pV->z + pM->_23;
    f32 rw = 1.0f / ( pM->_30 * pV->x + pM->_31 * pV->y + pM->_32 * pV->z + pM->_33 );

    pOut->x = rw * tmp.x;
    pOut->y = rw * tmp.y;
    pOut->z = rw * tmp.z;
    return pOut;
}

VEC4 *VEC3TransformArray( VEC4 *pOut, const MTX44 *pM, const VEC3 *pV, u32 count )
{
    u32 i;
    VEC4 *pDst = pOut;

    for( i = 0; i < count; ++i )
    {
        VEC3Transform( pDst, pM, pV );
        ++pDst;
        ++pV;
    }

    return pOut;
}

VEC3 *VEC3TransformCoordArray( VEC3 *pOut, const MTX44 *pM, const VEC3 *pV, u32 count )
{
    u32 i;
    VEC3 *pDst = pOut;

    for( i = 0; i < count; ++i )
    {
        VEC3TransformCoord( pDst, pM, pV );
        ++pDst;
        ++pV;
    }

    return pOut;
}

VEC4 *VEC4Transform( VEC4 *pOut, const MTX44 *pM, const VEC4 *pV )
{
    VEC4 tmp;
    tmp.x = pM->_00 * pV->x + pM->_01 * pV->y + pM->_02 * pV->z + pM->_03 * pV->w;
    tmp.y = pM->_10 * pV->x + pM->_11 * pV->y + pM->_12 * pV->z + pM->_13 * pV->w;
    tmp.z = pM->_20 * pV->x + pM->_21 * pV->y + pM->_22 * pV->z + pM->_23 * pV->w;
    tmp.w = pM->_30 * pV->x + pM->_31 * pV->y + pM->_32 * pV->z + pM->_33 * pV->w;

    pOut->x = tmp.x;
    pOut->y = tmp.y;
    pOut->z = tmp.z;
    pOut->w = tmp.w;
    return pOut;
}

VEC4 *VEC4TransformArray( VEC4 *pOut, const MTX44 *pM, const VEC4 *pV, u32 count )
{
    u32 i;
    VEC4 *pDst = pOut;

    for( i = 0; i < count; ++i )
    {
        VEC4Transform( pDst, pM, pV );
        ++pDst;
        ++pV;
    }

    return pOut;
}

void VEC2::Report( bool bNewline, const char *name ) const
{
    if( name )
    {
        OSReport( "%s", name );
    }
    else
    {
        OSReport( "VEC2" );
    }

    OSReport( "<%f, %f>", x, y );

    if( bNewline )
    {
        OSReport( "\n" );
    }
}

void VEC3::Report( bool bNewline, const char *name ) const
{
    if( name )
    {
        OSReport( "%s", name );
    }
    else
    {
        OSReport( "VEC3" );
    }

    OSReport( "<%f, %f, %f>", x, y, z );

    if( bNewline )
    {
        OSReport( "\n" );
    }
}

void VEC4::Report( bool bNewline, const char *name ) const
{
    if( name )
    {
        OSReport( "%s", name );
    }
    else
    {
        OSReport( "VEC4" );
    }

    OSReport( "<%f, %f, %f, %f>", x, y, z, w );

    if( bNewline )
    {
        OSReport( "\n" );
    }
}

void QUAT::Report( bool bNewline, const char *name ) const
{
    if( name )
    {
        OSReport( "%s", name );
    }
    else
    {
        OSReport( "QUAT" );
    }

    OSReport( "<%f, %f, %f, %f>", x, y, z, w );

    if( bNewline )
    {
        OSReport( "\n" );
    }
}

void MTX33::Report( bool bNewline, const char *name ) const
{
    if( name )
    {
        OSReport( "%s", name );
    }
    else
    {
        OSReport( "MTX33" );
    }

    OSReport( "<%f, %f, %f\n", _00, _01, _02 );
    OSReport( "      %f, %f, %f\n", _10, _11, _12 );
    OSReport( "      %f, %f, %f>\n", _20, _21, _22 );

    if( bNewline )
    {
        OSReport( "\n" );
    }
}

void MTX34::Report( bool bNewline, const char *name ) const
{
    if( name )
    {
        OSReport( "%s", name );
    }
    else
    {
        OSReport( "MTX34" );
    }

    OSReport( "<%f, %f, %f, %f\n", _00, _01, _02, _03 );
    OSReport( "      %f, %f, %f, %f\n", _10, _11, _12, _13 );
    OSReport( "      %f, %f, %f, %f>\n", _20, _21, _22, _23 );

    if( bNewline )
    {
        OSReport( "\n" );
    }
}

void MTX44::Report( bool bNewline, const char *name ) const
{
    if( name )
    {
        OSReport( "%s", name );
    }
    else
    {
        OSReport( "MTX44" );
    }

    OSReport( "<%f, %f, %f, %f\n", _00, _01, _02, _03 );
    OSReport( "      %f, %f, %f, %f\n", _10, _11, _12, _13 );
    OSReport( "      %f, %f, %f, %f\n", _20, _21, _22, _23 );
    OSReport( "      %f, %f, %f, %f>\n", _30, _31, _32, _33 );

    if( bNewline )
    {
        OSReport( "\n" );
    }
}

} // namespace math
} // namespace nw4r
