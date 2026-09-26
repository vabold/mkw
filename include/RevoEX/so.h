/// \file RevoEX/so.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [RDCE78] Deadly Creatures
///     [R3RE8P] Sonic & SEGA All-Stars Racing
///
/// Header path: /RevoEX/include/so.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef REVOEX_SO_H
#define REVOEX_SO_H

#include <RVL_SDK/types.h>
#include <RevoEX/so/SOIcmp.h>

#include <RevoEX/so/SOBasic.h>
#include <RevoEX/so/SOOption.h>

EXTERN_C_BEGIN

// TODO: Could these be in SOBasic.h?

// [R3RE8P]/SSR_Wii.elf::SmoScriptVMDebugSocketGetSOErrorDescription
// TODO: Anonymous enum or preprocessor defines?
enum
{
    SO_EFATAL = 0x80000000, // [SBAJGD]::0x806b85e0
    SO_E2BIG = -1,
    SO_EACCES = -2,
    SO_EADDRINUSE = -3, // Address is already in use
    SO_EADDRNOTAVAIL = -4,
    SO_EAFNOSUPPORT = -5, // Non-supported address family
    SO_EAGAIN = -6,       // aka EWOULDBLOCK
    SO_EALREADY = -7,     // Already in progress
    SO_EBADF = -8,        // Bad socket descriptor
    SO_EBADMSG = -9,
    SO_EBUSY = -10, // Busy
    SO_ECANCELED = -11,
    SO_ECHILD = -12,
    SO_ECONNABORTED = -13, // Connection aborted
    SO_ECONNREFUSED = -14, // Connection refused
    SO_ECONNRESET = -15,   // Connection reset
    SO_EDEADLK = -16,
    SO_EDESTADDRREQ = -17, // Not bound to a local address
    SO_EDOM = -18,
    SO_EDQUOT = -19,
    SO_EEXIST = -20,
    SO_EFAULT = -21,
    SO_EFBIG = -22,
    SO_EHOSTUNREACH = -23,
    SO_EIDRM = -24,
    SO_EILSEQ = -25,
    SO_EINPROGRESS = -26, // Still in progress
    SO_EINTR = -27,       // Canceled
    SO_EINVAL = -28,      // Invalid operation
    SO_EIO = -29,         // I/O error
    SO_EISCONN = -30,     // Socket is already connected
    SO_EISDIR = -31,
    SO_ELOOP = -32,
    SO_EMFILE = -33, // No more socket descriptors
    SO_EMLINK = -34,
    SO_EMSGSIZE = -35, // Too large to be sent
    SO_EMULTIHOP = -36,
    SO_ENAMETOOLONG = -37,
    SO_ENETDOWN = -38,
    SO_ENETRESET = -39,
    SO_ENETUNREACH = -40, // Unreachable
    SO_ENFILE = -41,
    SO_ENOBUFS = -42, // Insufficient resources
    SO_ENODATA = -43,
    SO_ENODEV = -44,
    SO_ENOENT = -45,
    SO_ENOEXEC = -46,
    SO_ENOLCK = -47,
    SO_ENOLINK = -48, // Network interface is unavailable
    SO_ENOMEM = -49,  // Insufficient memory
    SO_ENOMSG = -50,
    SO_ENOPROTOOPT = -51, // Non-supported option
    SO_ENOSPC = -52,
    SO_ENOSR = -53,
    SO_ENOSTR = -54,
    SO_ENOSYS = -55,
    SO_ENOTCONN = -56, // Not connected
    SO_ENOTDIR = -57,
    SO_ENOTEMPTY = -58,
    SO_ENOTSOCK = -59, // Not a socket
    SO_ENOTSUP = -60,
    SO_ENOTTY = -61,
    SO_ENXIO = -62,      // Network interface device doesn't exist
    SO_EOPNOTSUPP = -63, // Non-supported operation
    SO_EOVERFLOW = -64,
    SO_EPERM = -65,
    SO_EPIPE = -66,
    SO_EPROTO = -67,
    SO_EPROTONOSUPPORT = -68, // Non-supported protocol
    SO_EPROTOTYPE = -69,      // Non-supported socket type
    SO_ERANGE = -70,
    SO_EROFS = -71,
    SO_ESPIPE = -72,
    SO_ESRCH = -73,
    SO_ESTALE = -74,
    SO_ETIME = -75,
    SO_ETIMEDOUT = -76, // Timed out
    SO_ETXTBSY = -77,
    SO_EXDEV = -78,
    SO_SUCCESS = 0,
};

// [R3RE8P]/SSR_Wii.elf::SmoScriptVMDebugSocketGetSOErrorDescription
// TODO: Anonymous enum or preprocessor defines?
enum
{
    SO_ERR_NETRM_NOTAVAIL = 0x80000000,
    SO_ERR_DHCP_TIMEOUT = -100, // Could not find any DHCP server.
    SO_ERR_DHCP_EXPIRED = -101,
    SO_ERR_DHCP_NAK = -102,
    SO_ERR_LCP = -107,             // LCP negotiation error
    SO_ERR_AUTH = -108,            // Authentication error
    SO_ERR_IPCP = -109,            // IPCP negotiation error
    SO_ERR_ADDR_COLLISION = -111,  // Duplicate IP address
    SO_ERR_LINK_DOWN = -112,       // Link down
    SO_ERR_LINK_UP_TIMEOUT = -121, // Link-up timeout
};

// [R3RE8P]/SSR_Wii.elf::SmoScriptVMDebugSocketGetSOErrorDescription
// TODO: Anonymous enum or preprocessor defines?
enum
{
    SO_EAI_AGAIN = -300,
    SO_EAI_BADFLAGS = -301,
    SO_EAI_FAIL = -302,
    SO_EAI_FAMILY = -303,
    SO_EAI_MEMORY = -304,
    SO_EAI_NONAME = -305,
    SO_EAI_SERVICE = -306,
    SO_EAI_SOCKTYPE = -307,
    SO_EAI_SYSTEM = -308,
    SO_EAI_OVERFLOW = -309,
};

// Name assumed
typedef void *( *SOAllocFunc )( u32 name, s32 size );
typedef void ( *SOFreeFunc )( u32 name, void *ptr, s32 size );

// [RDCE78]/DeadlyCreatures_Debug.elf:.debug
typedef struct SOLibraryConfig
{
    SOAllocFunc alloc;
    SOFreeFunc free;
} SOLibraryConfig;

// [RDCE78]/DeadlyCreatures_Debug.elf:.debug
typedef struct SOHostEnt
{
    char *name;
    char **aliases;
    s16 addrType;
    s16 length;
    u8 **addrList;
} SOHostEnt;

// [RDCE78]/DeadlyCreatures_Debug.elf:.debug
typedef struct SOResolver
{
    SOHostEnt ent;
    char name[ 256 ];
    u8 addrList[ 560 ];
    u8 *ptrList[ 72 ];
} SOResolver;

typedef struct SOAddrInfo SOAddrInfo;

typedef struct SOAddrInfo
{
    int flags;
    int family;
    u8 _08[ 0x18 - 0x08 ];
    void *addr;
    SOAddrInfo *next;
} SOAddrInfo;

/******************************************************************************
 *
 * SOCommon.c
 *
 ******************************************************************************/

int SOInit( SOLibraryConfig *config ); // [RDCE78] DWARF
int SOFinish( void );                  // [RDCE78] DWARF
int SOStartup( void );                 // [RDCE78] DWARF
int SOStartupEx( int timeOut );        // [RDCE78] DWARF
int SOCleanup( void );                 // [RDCE78] DWARF
int SOGetLastError( void );            // [RDCE78] DWARF
// Not found: SOSwitchBufferAddrCheck

/******************************************************************************
 *
 * SOInformation.c
 *
 ******************************************************************************/

s32 SOGetHostID( void );                             // [RDCE78] DWARF
SOResolver *SOGetHostByName( const char *hostName ); // [R3RE8P]
int SOGetAddrInfo( const char *node,
        const char *service,
        const SOAddrInfo *hints,
        SOAddrInfo **res );                  // [R3RE8P]
void SOFreeAddrInfo( SOAddrInfo *addrInfo ); // [R3RE8P]

EXTERN_C_END

#endif
