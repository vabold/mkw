/// \file RVL_SDK/private/acr.h
///
/// Sources:
///     [RJTJ01] Minna no Joushiki Ryoku TV
///
/// Temporarily placed here until we find a better place for it
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_PRIVATE_IPC_PROFILE_H
#define RVL_SDK_PRIVATE_IPC_PROFILE_H

#include <RVL_SDK/private/iosrestypes.h>
#include <RVL_SDK/private/iostypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

void IPCiProfInit( void );
void IPCiProfQueueReq( IOSIoRequest *req, IOSFd fd );
void IPCiProfAck( void );
void IPCiProfReply( IOSIoRequest *req, IOSFd fd );

#ifdef __cplusplus
}
#endif

#endif
