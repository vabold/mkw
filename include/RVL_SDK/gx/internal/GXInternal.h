#ifndef RVL_SDK_GX_INTERNAL_H
#define RVL_SDK_GX_INTERNAL_H

#include <RVL_SDK/gx/GXStruct.h>

#ifdef __cplusplus
extern "C"
{
#endif

// TODO: Cross-reference Big Brain Academy: Wii Degree to see which functions are weak
// Functions like __GXReadMEMCounterU32 are likely header-defined

/******************************************************************************
 *
 * GXAttr.c
 *
 ******************************************************************************/

void __GXSetVCD( void );
void __GXCalculateVLim( void );
void __GXSetVAT( void );

/******************************************************************************
 *
 * GXBump.c
 *
 ******************************************************************************/

void __GXUpdateBPMask( void );
void __GXSetIndirectMask( u32 mask );
void __GXFlushTextureState( void );

/******************************************************************************
 *
 * GXFifo.c
 *
 ******************************************************************************/

void __GXSaveFifo( void );
GXBool __GXIsGPFifoReady( void );
void __GXFifoInit( void );
void __GXCleanGPFifo( void );

/******************************************************************************
 *
 * GXGeometry.c
 *
 ******************************************************************************/

void __GXSetDirtyState( void );
void __GXSetTexGen( u32 );
void __GXSetLightChan( u32 );
void __GXSetAmbMat( u32 );
void __GXSendFlushPrim( void );
void __GXSetGenMode( void );

/******************************************************************************
 *
 * GXInit.c
 *
 ******************************************************************************/

u32 __GXReadMEMCounterU32( u32, u32 );
void __GXInitRevisionBits( void );
void __GXInitGX( void );

/******************************************************************************
 *
 * GXMisc.c
 *
 ******************************************************************************/

u32 __GXReadMEMCounterU32( u32, u32 );
void __GXAbort( void );
void __GXBypass( u32 );
u16 __GXReadPEReg( u32 );
void __GXPEInit( void );

/******************************************************************************
 *
 * GXPerf.c
 *
 ******************************************************************************/

u32 __GXReadCPCounterU32( u32, u32 );
u32 __GXReadMEMCounterU32( u32, u32 );
u32 __GXReadPECounterU32( u32, u32 );
void __GXSetBWDials( u16, u16, u16, u16, u16 );

/******************************************************************************
 *
 * GXSave.c
 *
 ******************************************************************************/

void DPF( ... );
void __GXShadowDispList( void *list, u32 size );
void __GXShadowIndexState( u32, u32 );
void __GXPrintShadowState( void );

/******************************************************************************
 *
 * GXTexture.c
 *
 ******************************************************************************/

void __GetImageTileCount( GXTexFmt fmt,
        u16 wd,
        u16 ht,
        u32 *rowTiles,
        u32 *colTiles,
        u32 *cmpTiles );
void __GXSetSUTexRegs( void );
void __GXGetSUTexSize( GXTexCoordID coord, u16 *width, u16 *height );
void __GXSetTmemConfig( u32 config );

/******************************************************************************
 *
 * GXTransform.c
 *
 ******************************************************************************/

void __GXSetProjection( void );
void __GXSetViewport( void );
void __GXSetMatrixIndex( void );

/******************************************************************************
 *
 * GXVerifRAS.c
 *
 ******************************************************************************/

void __GXVerifySU( void );
void __GXVerifyBUMP( void );
void __GXVerifyTEX( void );
void __GXVerifyTEV( void );
void __GXVerifyPE( void );

/******************************************************************************
 *
 * GXVerifXF.c
 *
 ******************************************************************************/

void __GXVerifyXF( void );

/******************************************************************************
 *
 * GXVerify.c
 *
 ******************************************************************************/

void __GXVerifyState( u32 );
void __GXVerifyVATImm( u32, u32, u32, u32 );

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_INTERNAL_H
