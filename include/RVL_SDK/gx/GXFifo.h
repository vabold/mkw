#ifndef RVL_SDK_GX_FIFO_H
#define RVL_SDK_GX_FIFO_H

#include <RVL_SDK/gx/GXStruct.h>

#include <RVL_SDK/os/OSThread.h>

#ifdef __cplusplus
extern "C"
{
#endif

void GXInitFifoBase( GXFifoObj *fifo, void *base, u32 size );
void GXInitFifoPtrs( GXFifoObj *fifo, void *readPtr, void *writePtr );
void GXInitFifoLimits( GXFifoObj *fifo, u32 hiWatermark, u32 loWatermark );
void GXSetCPUFifo( GXFifoObj *fifo );
void GXSetGPFifo( GXFifoObj *fifo );
GXBool GXIsCPUGPFifoLinked( void );
void GXGetGPStatus( GXBool *overhi,
        GXBool *underlow,
        GXBool *readIdle,
        GXBool *cmdIdle,
        GXBool *brkpt );
GXBool GXGetCPUFifo( GXFifoObj *fifo );
GXBool GXGetGPFifo( GXFifoObj *fifo );
void GXGetFifoPtrs( GXFifoObj *fifo, void **readPtr, void **writePtr );
void *GXGetFifoBase( GXFifoObj *fifo );
u32 GXGetFifoSize( GXFifoObj *fifo );
void GXGetFifoLimits( GXFifoObj *fifo, u32 *hi, u32 *lo );
s32 GXGetFifoCount( GXFifoObj *fifo );
GXBool GXGetFifoWrap( GXFifoObj *fifo );
GXBreakPtCallback GXSetBreakPtCallback( GXBreakPtCallback cb );
void GXEnableBreakPt( void *break_pt );
void GXDisableBreakPt( void );
OSThread *GXSetCurrentGXThread( void );
OSThread *GXGetCurrentGXThread( void );
u32 GXGetOverflowCount( void );
u32 GXResetOverflowCount( void );
void *GXRedirectWriteGatherPipe( void *ptr );
void GXRestoreWriteGatherPipe( void );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_FIFO_H
