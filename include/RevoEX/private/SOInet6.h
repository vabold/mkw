/// \file RevoEX/private/SOInet6.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [IOS58] $IOSVersion:  SO: 01/09/09 15:45:00 64M Release/builder/HEAD $
///
/// Header path: /RevoEX/include/private/SOInet6.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef REVOEX_SOINET6_H
#define REVOEX_SOINET6_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Assumed from [IOS] "assert !SO_IN6_ARE_ADDR_EQUAL(&ip6->dst, &SOIn6AddrAny)"
typedef struct SOIn6Addr
{
    u8 addr[ 16 ];
} SOIn6Addr;

// [IOS] "assert local->family != SO_PF_INET6 || sizeof(SOSockAddrIn6) <=
// local->len"
typedef struct SOSockAddrIn6
{
    u8 len;
    u8 family;
    u16 port;
    u32 flowinfo;
    SOIn6Addr addr;
    u32 scopeid;
} SOSockAddrIn6;

// [IOS] "assert !SO_IN6_ARE_ADDR_EQUAL(&ip6->dst, &SOIn6AddrAny)"
// TODO: Verify if actually const
extern const SOIn6Addr SOIn6AddrAny;

// [IOS] "assert SO_IN6_ARE_ADDR_EQUAL(&header->src, &frag->src)"
#define SO_IN6_ARE_ADDR_EQUAL( a, b ) ( memcmp( a, b, sizeof( SOSockAddr ) ) == 0 )

// TODO: SO_IN6_IS_ADDR_UNSPECIFIED
// TODO: SO_IN6_IS_ADDR_LOOPBACK

// [IOS] "assert !SO_IN6_IS_ADDR_MULTICAST(addr)"
#define SO_IN6_IS_ADDR_MULTICAST( a ) ( *(u8 *)( a ) == 0xff )

// [IOS] "assert !SO_IN6_IS_ADDR_LINKLOCAL(prefix)"
#define SO_IN6_IS_ADDR_LINKLOCAL( a ) \
    ( *(u8 *)( a ) == 0xfe && ( ( (u8 *)( a ) )[ 1 ] & 0xc0 ) == 0x80 )

// TODO: SO_IN6_IS_ADDR_SITELOCAL

// [IOS] "assert SO_IN6_IS_ADDR_V4MAPPED(&twInfo->localAddr)"
#define SO_IN6_IS_ADDR_V4MAPPED( a ) \
    ( memcmp( a, &SOIn6AddrAny, 10 ) == 0 && ( (u16 *)( a ) )[ 5 ] == 0xffff )

// TODO: SO_IN6_IS_ADDR_V4COMPAT
// TODO: SO_IN6_IS_ADDR_MC_NODELOCAL
// TODO: SO_IN6_IS_ADDR_MC_LINKLOCAL
// TODO: SO_IN6_IS_ADDR_MC_SITELOCAL
// TODO: SO_IN6_IS_ADDR_MC_ORGLOCAL
// TODO: SO_IN6_IS_ADDR_MC_GLOBAL

#ifdef __cplusplus
}
#endif

#endif
