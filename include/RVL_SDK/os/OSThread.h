/// \file RVL_SDK/os/OSThread.h
///
/// Sources:
///     [SSDDRV] Schlag den Raab
///     [GSDEAF] Smashing Drive
///     [GR6E78] Bratz - Rock Angelz
///
/// SPDX-License-Identifier: CC0-1.0

#ifndef RVL_SDK_OS_THREAD_H
#define RVL_SDK_OS_THREAD_H

#include <RVL_SDK/os/OSContext.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// [GSDEAF]/smash.elf:.debug_info
typedef s32 OSPriority;
typedef struct OSMutex OSMutex;
typedef struct OSThread OSThread;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001939
typedef struct OSThreadQueue
{
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001C34
typedef struct OSThreadLink
{
    OSThread *next;
    OSThread *prev;
} OSThreadLink;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001C6C
/// \note This must be here, otherwise it creates a circular dependency.
typedef struct OSMutexQueue
{
    OSMutex *head;
    OSMutex *tail;
} OSMutexQueue;

/// [SSDDRV]/SdRGameD.elf:.debug_info::0x00001972
typedef struct OSThread
{
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
    OSMutex *mutex;
    OSMutexQueue queueMutex;
    OSThreadLink linkActive;

    u8 *stackBase;
    u32 *stackEnd;

    s32 error;
    void *specific[ 2 ];
} OSThread;

/// [GR6E78]/Bratz_NGC_M.elf:.debug_info::0x00187322
typedef void ( *OSIdleFunction )( void * );

/// [GR6E78]/Bratz_NGC_M.elf:.debug_info::0x00187382
typedef void ( *OSSwitchThreadCallback )( OSThread *, OSThread * );

OSSwitchThreadCallback OSSetSwitchThreadCallback( OSSwitchThreadCallback callback );
void __OSThreadInit( void );
void OSInitThreadQueue( OSThreadQueue *queue );
OSThread *OSGetCurrentThread( void );
BOOL OSIsThreadSuspended( OSThread *thread );
BOOL OSIsThreadTerminated( OSThread *thread );
s32 OSDisableScheduler( void );
s32 OSEnableScheduler( void );
OSPriority __OSGetEffectivePriority( OSThread *thread );
void __OSPromoteThread( OSThread *thread, OSPriority priority );
void __OSReschedule( void );
void OSYieldThread( void );
BOOL OSCreateThread( OSThread *thread,
        void *( *func )(void *),
        void *param,
        void *stack,
        u32 stackSize,
        OSPriority priority,
        u16 attr );
void OSExitThread( void *val );
void OSCancelThread( OSThread *thread );
BOOL OSJoinThread( OSThread *thread, void *val );
void OSDetachThread( OSThread *thread );
s32 OSResumeThread( OSThread *thread );
s32 OSSuspendThread( OSThread *thread );
void OSSleepThread( OSThreadQueue *queue );
void OSWakeupThread( OSThreadQueue *queue );
BOOL OSSetThreadPriority( OSThread *thread, OSPriority priority );
OSPriority OSGetThreadPriority( OSThread *thread );
OSThread *OSSetIdleFunction( OSIdleFunction idleFunction, void *param, void *stack, u32 stackSize );
OSThread *OSGetIdleFunction( void );
s32 OSCheckActiveThreads( void );
void OSClearStack( u8 val );
void OSSetThreadSpecific( s32 index, void *specific );
void *OSGetThreadSpecific( s32 index );

// Wii-specific, no DWARF
void OSSleepTicks( s64 ticks );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_OS_THREAD_H
