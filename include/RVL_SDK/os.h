#ifndef OS_H
#define OS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <RVL_SDK/types.h>

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

#ifdef __cplusplus
}
#endif

#endif
