/// \file RVL_SDK/os/OSMutex.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_MUTEX_H
#define RVL_SDK_OS_MUTEX_H

#include <RVL_SDK/os/OSThread.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001CB9
typedef struct OSMutexLink
{
    OSMutex *next;
    OSMutex *prev;
} OSMutexLink;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x000018EA
typedef struct OSMutex
{
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutexLink link;
} OSMutex;

/// TODO: Properly attribute Smashing Drive
typedef struct OSCond
{
    OSThreadQueue queue;
} OSCond;

void OSInitMutex( OSMutex *mutex );
void OSLockMutex( OSMutex *mutex );
void OSUnlockMutex( OSMutex *mutex );
void __OSUnlockAllMutex( OSThread *thread );
BOOL OSTryLockMutex( OSMutex *mutex );

void OSInitCond( OSCond *cond );
void OSWaitCond( OSCond *cond, OSMutex *mutex );
void OSSignalCond( OSCond *cond );

BOOL __OSCheckMutex( OSMutex *mutex );
BOOL __OSCheckDeadLock( OSThread *thread );
BOOL __OSCheckMutexes( OSThread *thread );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_OS_MUTEX_H
