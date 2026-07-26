/// \file RVL_SDK/os/OSThread.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_THREAD_H
#define RVL_SDK_OS_THREAD_H

#include <RVL_SDK/types.h>
#include <RVL_SDK/os/OSContext.h>

#ifdef __cplusplus
extern "C" {
#endif

/// [GSDEAF]/smash.elf:.debug_info
typedef s32 OSPriority;
typedef struct OSMutex OSMutex;
typedef struct OSThread OSThread;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001939
typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001C34
typedef struct OSThreadLink {
    struct OSThread *next;
    struct OSThread *prev;
} OSThreadLink;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001C6C
/// \note This must be here otherwise it creates a circular dependency.
typedef struct OSMutexQueue {
    struct OSMutex *head;
    struct OSMutex *tail;
} OSMutexQueue;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001972
typedef struct OSThread {
    OSContext context;
    u16 state;
    u16 attr;
    s32 suspend;
    OSPriority priority;
    s32 base;
    void *val;

    OSThreadQueue *queue;
    OSThreadLink link;
    OSThreadQueue queueJoin;
    struct OSMutex *mutex;
    OSMutexQueue queueMutex;
    OSThreadLink linkActive;

    u8 *stackBase;
    u32 *stackEnd;

    s32 error;
    void *specific[2];
} OSThread;

void OSInitThreadQueue(OSThreadQueue *queue);
void OSSleepThread(OSThreadQueue *queue);
void OSWakeupThread(OSThreadQueue *queue);

OSThread *OSGetCurrentThread(void);
BOOL OSIsThreadSuspended(OSThread *thread);
BOOL OSIsThreadTerminated(OSThread *thread);

BOOL OSCreateThread(
    OSThread *thread,
    void (*func)(void *),
    void *param,
    void *stack,
    u32 stackSize,
    u16 attr
)
;
void OSExitThread(void *val);
void OSCancelThread(OSThread *thread);
BOOL OSJoinThread(OSThread *thread, void *val);
void OSDetachThread(OSThread *thread);
s32 OSResumeThread(OSThread *thread);
s32 OSSuspendThread(OSThread *thread);

BOOL OSSetThreadPriority(OSThread *thread, OSPriority priority);
OSPriority OSGetThreadPriority(OSThread *thread);

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_OS_THREAD_H
