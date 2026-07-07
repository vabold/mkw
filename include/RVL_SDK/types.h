#ifndef TYPES_H
#define TYPES_H

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
// NOT typedef volatile s8 vs8, per Smashing Drive
typedef volatile signed char vs8;
typedef volatile signed short vs16;
typedef volatile signed long vs32;
typedef volatile signed long long vs64;
typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;
typedef volatile unsigned long long vu64;

typedef float f32;
typedef float f64;
typedef volatile float vf32;
typedef volatile double vf64;

typedef u32 size_t;
typedef u32 uintptr_t;
typedef s32 ptrdiff_t;

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#ifndef NULL
#ifdef __cplusplus // We need NULL to be (void *)0 in C contexts, but this is illegal in C++
#define NULL 0
#else
#define NULL (void *)0
#endif
#endif

#define ASM asm

#ifdef __cplusplus
extern "C"
{
#endif

// Any external functions can temporary live here until sorted into their correct header

// ctype.h

typedef struct _loc_ctype_cmpt
{
    unsigned char _00[ 0x10 - 0x00 ];
    const unsigned char *lower_map_ptr;
} _loc_ctype_cmpt;

typedef struct __locale
{
    unsigned char _00[ 0x38 - 0x00 ];
    _loc_ctype_cmpt *ctype_cmpt_ptr;
} __locale;

extern __locale _current_locale;

inline int tolower( int c )
{
    return c < 0 || c >= 0x100 ? c : _current_locale.ctype_cmpt_ptr->lower_map_ptr[ c ];
}

// math.h

double sqrt( double x );
double sin( double x );
double cos( double x );
double tan( double x );
double asin( double x );
double acos( double x );

inline float sqrtf( float x )
{
    return sqrt( x );
}

inline float sinf( float x )
{
    return sin( x );
}

inline float cosf( float x )
{
    return cos( x );
}

inline float tanf( float x )
{
    return tan( x );
}

inline float asinf( float x )
{
    return asin( x );
}

inline float acosf( float x )
{
    return acos( x );
}

#ifdef __cplusplus
}
#endif

#endif
