/// \file RevoEX/so/SOBasic.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [RDCE78] Deadly Creatures
///     [R3RE8P] Sonic & SEGA All-Stars Racing
///     [R89JEL] Tokyo Friend Park II: Ketteiban: Minna de Chousen! Taikan Attraction!
///
/// Header path: /RevoEX/include/so/SOBasic.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef REVOEX_SOBASIC_H
#define REVOEX_SOBASIC_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

// [RDCE78]/DeadlyCreatures_Debug.elf DWARF
typedef struct SOInAddr
{
    u32 addr;
} SOInAddr;

// [R89JEL]/mainD.elf DWARF
typedef struct SOSockAddr
{
    u8 len;
    u8 family;
    u8 data[ 6 ];
} SOSockAddr;

// [RDCE78]/DeadlyCreatures_Debug.elf DWARF
typedef struct SOSockAddrIn
{
    u8 len;
    u8 family;
    u16 port;
    SOInAddr addr;
} SOSockAddrIn;

// [RDCE78]/DeadlyCreatures_Debug.elf DWARF
typedef struct SOPollFD
{
    int fd;
    int events;
    int revents;
} SOPollFD;

int SOSocket( int pf, int type, int protocol );                         // [RDCE78] DWARF
int SOClose( int s );                                                   // [RDCE78] DWARF
int SOListen( int s, int backlog );                                     // [R3RE8P]
int SOAccept( int s, void *sockAddr );                                  // [R3RE8P]
int SOBind( int s, void *sockAddr );                                    // [R3RE8P]
int SOGetSockName( int s, void *sockAddr );                             // [R3RE8P]
int SOConnect( int s, void *sockAddr );                                 // [RDCE78] DWARF
int SORecvFrom( int s, void *buf, int len, int flags, void *sockFrom ); // [R3RE8P]
int SORecv( int s, void *buf, int len, int flags );                     // [RDCE78] DWARF
int SORead( int s, void *buf, int len );                                // [R3RE8P]
int SOSendTo( int s, void *buf, int len, int flags, void *sockTo );     // [R3RE8P]
int SOSend( int s, void *buf, int len, int flags );                     // [RDCE78] DWARF
int SOWrite( int s, void *buf, int len );                               // [R3RE8P]
int SOFcntl( int s, int cmd, ... );                                     // [RDCE78] DWARF
int SOShutdown( int s, int how );                                       // [RDCE78] DWARF
int SOPoll( SOPollFD *fds, int nfds, s64 timeOut );                     // [R3RE8P]
int SOInetAtoN( const char *cp, SOInAddr *inp );                        // [RDCE78] DWARF
const char *SOInetNtoA( SOInAddr *inp );                                // [R3RE8P]
u32 SONtoHl( u32 netlong );                                             // [R3RE8P]
u16 SONtoHs( u16 netshort );                                            // [R3RE8P]
u32 SOHtoNl( u32 hostlong );                                            // [R3RE8P]
u16 SOHtoNs( u16 hostshort );                                           // [RDCE78] DWARF

#ifdef __cplusplus
}
#endif

#endif
