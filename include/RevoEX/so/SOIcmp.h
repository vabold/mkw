/// \file RevoEX/so/SOIcmp.h
///
/// Sources:
///     [SDLE78] Dood's Big Adventure
///     [IOS58] $IOSVersion:  SO: 01/09/09 15:45:00 64M Release/builder/HEAD $
///
/// Header path: /RevoEX/include/so/SOIcmp.h [SDLE78] DWARF
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef REVOEX_SOICMP_H
#define REVOEX_SOICMP_H

#include <RVL_SDK/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

// TODO: These are identical to POSIX and the rest can be inferred
// See also: https://www.iana.org/protocols

// [IOS] "assert local->family == SO_PF_INET || local->family == SO_PF_INET6"
// [IOS: "assert len < SO_INET6_ADDRSTRLEN"
// [IOS] "assert next && *next == SO_IPPROTO_FRAGMENT"
// [IOS] "assert info->info.proto == SO_IPPROTO_ICMPV6"
// TODO: Anonymous enum or preprocessor defines?

enum
{
    SO_PF_INET = 2,
    SO_PF_INET6 = 23,
};

enum
{
    SO_INET_ADDRSTRLEN = 16,  // sizeof "255.255.255.255"
    SO_INET6_ADDRSTRLEN = 46, // sizeof "0000:0000:0000:0000:0000:ffff:255.255.255.255"
};

enum
{
    SO_IPPROTO_FRAGMENT = 44,
    SO_IPPROTO_ICMPV6 = 58,
};

#ifdef __cplusplus
}
#endif

#endif
