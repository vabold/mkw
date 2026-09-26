/// \file RevoEX/so/SOOption.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [RDCE78] Deadly Creatures
///     [R3RE8P] Sonic & SEGA All-Stars Racing
///     [RSBE01] Super Smash Bros. Brawl
///
/// Header path: /RevoEX/include/so/SOOption.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef REVOEX_SOOPTION_H
#define REVOEX_SOOPTION_H

#include <RVL_SDK/types.h>

EXTERN_C_BEGIN

int SOGetSockOpt( int s, int level, int optname, void *optval, int *optlen ); // [RSBE01]
int SOSetSockOpt( int s, int level, int optname, void *optval, int optlen );  // [R3RE8P]
int SOGetInterfaceOpt( int level, int optname, void *optval, int *optlen );   // [RDCE78] DWARF

EXTERN_C_END

#endif
