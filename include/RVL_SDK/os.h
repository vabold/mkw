#ifndef OS_H
#define OS_H

#include <RVL_SDK/types.h>

#include <RVL_SDK/os/OSCache.h>
#include <RVL_SDK/os/OSContext.h>
#include <RVL_SDK/os/OSFastCast.h>
#include <RVL_SDK/os/OSInterrupt.h>
#include <RVL_SDK/os/OSMutex.h>
#include <RVL_SDK/os/OSThread.h>

#ifdef __cplusplus
extern "C"
{
#endif

// TODO: This is likely defined elsewhere
__attribute__( ( weak ) ) void OSReport( const char *msg, ... );
__attribute__( ( weak ) ) void OSPanic( const char *file, int line, const char *msg, ... );

#ifdef DEBUG
#define OSAssertMessage( exp_, ... ) \
    (void)( ( exp_ ) || ( OSPanic( __FILE__, __LINE__, __VA_ARGS__ ), 0 ) )
#else
#define OSAssertMessage( exp_, ... ) ( (void)0 )
#endif
#define OSAssert( exp_ ) OSAssertMessage( exp_, "Failed assertion " #exp_ )
#define OSError( ... ) OSPanic( __FILE__, __LINE__, __VA_ARGS__ )

// Lingcod's separate PatchFunction templates suggest 3 different signatures here.
// OSCachedToPhysical and OSUncachedToPhysical match with DKCR functions with confirmed signatures
// like <32-bit integer type>(const <struct>*)

// Place the function names in parentheses to avoid macro expansion
u8 *(OSPhysicalToCached)( u32 address );
u8 *(OSPhysicalToUncached)( u32 address );
u32( OSCachedToPhysical )( const void *address );
u32( OSUncachedToPhysical )( const void *address );
u8 *(OSCachedToUncached)( const void *address );
u8 *(OSUncachedToCached)( const void *address );

#ifndef DEBUG
// These are seemingly defined as macros in release. Although the definitions still exist in
// OSAddress.c, they're left unused
#define OSPhysicalToCached( address_ ) ( ( (u8 *)( address_ ) ) + 0x80000000ul )
#define OSPhysicalToUncached( address_ ) ( ( (u8 *)( address_ ) ) + 0xC0000000ul )
#define OSCachedToPhysical( address_ ) ( ( (u32)( address_ ) ) - 0x80000000ul )
#define OSUncachedToPhysical( address_ ) ( ( (u32)( address_ ) ) - 0xC0000000ul )
#define OSCachedToUncached( address_ ) ( ( (u8 *)( address_ ) ) + 0x40000000ul )
#define OSUncachedToCached( address_ ) ( ( (u8 *)( address_ ) ) - 0x40000000ul )
#endif

#ifdef __cplusplus
}
#endif

#endif
