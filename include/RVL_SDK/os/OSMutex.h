/// \file RVL_SDK/os/OSMutex.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_MUTEX_H
#define RVL_SDK_OS_MUTEX_H

#include <RVL_SDK/types.h>
#include <RVL_SDK/os/OSThread.h>

#ifdef __cplusplus
extern "C" {
#endif

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001CB9
typedef struct OSMutexLink {
    struct OSMutex *next;
    struct OSMutex *prev;
} OSMutexLink;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x0x000018EA
typedef struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutexLink link;
} OSMutex;

void OSInitMutex(OSMutex *mutex);
void OSLockMutex(OSMutex *mutex);
void OSUnlockMutex(OSMutex *mutex);
BOOL OSTryLockMutex(OSMutex *mutex);

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_OS_MUTEX_H
