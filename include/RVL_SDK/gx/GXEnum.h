#ifndef RVL_SDK_GX_ENUM_H
#define RVL_SDK_GX_ENUM_H

#include <RVL_SDK/vi/vitypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

// All of the enums have been reordered alphabetically for ease of searching

typedef enum _GXAlphaOp
{
    GX_AOP_AND = 0,
    GX_AOP_OR = 1,
    GX_AOP_XOR = 2,
    GX_AOP_XNOR = 3,
    GX_MAX_ALPHAOP = 4,
} GXAlphaOp;

typedef enum _GXAlphaReadMode
{
    GX_READ_00 = 0,
    GX_READ_FF = 1,
    GX_READ_NONE = 2,
} GXAlphaReadMode;

typedef enum _GXAnisotropy
{
    GX_ANISO_1 = 0,
    GX_ANISO_2 = 1,
    GX_ANISO_4 = 2,
    GX_MAX_ANISOTROPY = 3,
} GXAnisotropy;

typedef enum _GXAttnFn
{
    GX_AF_SPEC = 0,
    GX_AF_SPOT = 1,
    GX_AF_NONE = 2,
} GXAttnFn;

typedef enum _GXAttr
{
    GX_VA_PNMTXIDX = 0,
    GX_VA_TEX0MTXIDX = 1,
    GX_VA_TEX1MTXIDX = 2,
    GX_VA_TEX2MTXIDX = 3,
    GX_VA_TEX3MTXIDX = 4,
    GX_VA_TEX4MTXIDX = 5,
    GX_VA_TEX5MTXIDX = 6,
    GX_VA_TEX6MTXIDX = 7,
    GX_VA_TEX7MTXIDX = 8,
    GX_VA_POS = 9,
    GX_VA_NRM = 10,
    GX_VA_CLR0 = 11,
    GX_VA_CLR1 = 12,
    GX_VA_TEX0 = 13,
    GX_VA_TEX1 = 14,
    GX_VA_TEX2 = 15,
    GX_VA_TEX3 = 16,
    GX_VA_TEX4 = 17,
    GX_VA_TEX5 = 18,
    GX_VA_TEX6 = 19,
    GX_VA_TEX7 = 20,
    GX_POS_MTX_ARRAY = 21,
    GX_NRM_MTX_ARRAY = 22,
    GX_TEX_MTX_ARRAY = 23,
    GX_LIGHT_ARRAY = 24,
    GX_VA_NBT = 25,
    GX_VA_MAX_ATTR = 26,
    GX_VA_NULL = 255,
} GXAttr;

typedef enum _GXAttrType
{
    GX_NONE = 0,
    GX_DIRECT = 1,
    GX_INDEX8 = 2,
    GX_INDEX16 = 3,
} GXAttrType;

// WARN: Multiple enumerators map to a single value. Choose carefully!
typedef enum _GXBlendFactor
{
    GX_BL_ZERO = 0,
    GX_BL_ONE = 1,
    GX_BL_SRCCLR = 2,
    GX_BL_INVSRCCLR = 3,
    GX_BL_SRCALPHA = 4,
    GX_BL_INVSRCALPHA = 5,
    GX_BL_DSTALPHA = 6,
    GX_BL_INVDSTALPHA = 7,
    GX_BL_DSTCLR = 2,
    GX_BL_INVDSTCLR = 3,
} GXBlendFactor;

typedef enum _GXBlendMode
{
    GX_BM_NONE = 0,
    GX_BM_BLEND = 1,
    GX_BM_LOGIC = 2,
    GX_BM_SUBTRACT = 3,
    GX_MAX_BLENDMODE = 4,
} GXBlendMode;

// https://patents.google.com/patent/US7034828B1/en
// While GXBool is known from DWARF, the exact nature of its interface is unknown
// We know GX_TRUE, GX_FALSE, GX_ENABLE, and GX_DISABLE are defined from the above patent
// However, ProDG DWARF does not emit fully anonymous enums or (obviously) preprocessor macros
// There are also no obvious code generation patterns to delineate which is used
// Use defines for now but move to fully anonymous enum if there are matching problems
typedef u8 GXBool;
#define GX_TRUE 1
#define GX_FALSE 0
#define GX_ENABLE 1
#define GX_DISABLE 0

typedef enum _GXChannelID
{
    GX_COLOR0 = 0,
    GX_COLOR1 = 1,
    GX_ALPHA0 = 2,
    GX_ALPHA1 = 3,
    GX_COLOR0A0 = 4,
    GX_COLOR1A1 = 5,
    GX_COLOR_ZERO = 6,
    GX_ALPHA_BUMP = 7,
    GX_ALPHA_BUMPN = 8,
    GX_COLOR_NULL = 255,
} GXChannelID;

typedef enum _GXCITexFmt
{
    GX_TF_C4 = 8,
    GX_TF_C8 = 9,
    GX_TF_C14X2 = 10,
} GXCITexFmt;

typedef enum _GXClipMode
{
    GX_CLIP_ENABLE = 0,
    GX_CLIP_DISABLE = 1,
} GXClipMode;

typedef enum _GXColorSrc
{
    GX_SRC_REG = 0,
    GX_SRC_VTX = 1,
} GXColorSrc;

// WARN: Multiple enumerators map to a single value. Choose carefully!
typedef enum _GXCompCnt
{
    GX_POS_XY = 0,
    GX_POS_XYZ = 1,
    GX_NRM_XYZ = 0,
    GX_NRM_NBT = 1,
    GX_NRM_NBT3 = 2,
    GX_CLR_RGB = 0,
    GX_CLR_RGBA = 1,
    GX_TEX_S = 0,
    GX_TEX_ST = 1,
} GXCompCnt;

// WARN: Multiple enumerators map to a single value. Choose carefully!
typedef enum _GXCompType
{
    GX_U8 = 0,
    GX_S8 = 1,
    GX_U16 = 2,
    GX_S16 = 3,
    GX_F32 = 4,
    GX_RGB565 = 0,
    GX_RGB8 = 1,
    GX_RGBX8 = 2,
    GX_RGBA4 = 3,
    GX_RGBA6 = 4,
    GX_RGBA8 = 5,
} GXCompType;

typedef enum _GXCompare
{
    GX_NEVER = 0,
    GX_LESS = 1,
    GX_EQUAL = 2,
    GX_LEQUAL = 3,
    GX_GREATER = 4,
    GX_NEQUAL = 5,
    GX_GEQUAL = 6,
    GX_ALWAYS = 7,
} GXCompare;

typedef enum _GXCopyMode
{
    GX_COPY_PROGRESSIVE = 0,
    GX_COPY_INTLC_EVEN = 2,
    GX_COPY_INTLC_ODD = 3,
} GXCopyMode;

typedef enum _GXCullMode
{
    GX_CULL_NONE = 0,
    GX_CULL_FRONT = 1,
    GX_CULL_BACK = 2,
    GX_CULL_ALL = 3,
} GXCullMode;

typedef enum _GXDiffuseFn
{
    GX_DF_NONE = 0,
    GX_DF_SIGN = 1,
    GX_DF_CLAMP = 2,
} GXDiffuseFn;

typedef enum _GXDistAttnFn
{
    GX_DA_OFF = 0,
    GX_DA_GENTLE = 1,
    GX_DA_MEDIUM = 2,
    GX_DA_STEEP = 3,
} GXDistAttnFn;

typedef enum _GXEvent
{
    GX_VCACHE_MISS_ALL = 0,
    GX_VCACHE_MISS_POS = 1,
    GX_VCACHE_MISS_NRM = 2,
} GXEvent;

typedef enum _GXFBClamp
{
    GX_CLAMP_NONE = 0,
    GX_CLAMP_TOP = 1,
    GX_CLAMP_BOTTOM = 2,
} GXFBClamp;

typedef enum _GXFogType
{
    GX_FOG_NONE = 0,
    GX_FOG_LIN = 2,
    GX_FOG_EXP = 4,
    GX_FOG_EXP2 = 5,
    GX_FOG_REVEXP = 6,
    GX_FOG_REVEXP2 = 7,
} GXFogType;

typedef enum _GXGamma
{
    GX_GM_1_0 = 0,
    GX_GM_1_7 = 1,
    GX_GM_2_2 = 2,
} GXGamma;

typedef enum _GXIndTexAlphaSel
{
    GX_ITBA_OFF = 0,
    GX_ITBA_S = 1,
    GX_ITBA_T = 2,
    GX_ITBA_U = 3,
    GX_MAX_ITBALPHA = 4,
} GXIndTexAlphaSel;

typedef enum _GXIndTexBiasSel
{
    GX_ITB_NONE = 0,
    GX_ITB_S = 1,
    GX_ITB_T = 2,
    GX_ITB_ST = 3,
    GX_ITB_U = 4,
    GX_ITB_SU = 5,
    GX_ITB_TU = 6,
    GX_ITB_STU = 7,
    GX_MAX_ITBIAS = 8,
} GXIndTexBiasSel;

typedef enum _GXIndTexFormat
{
    GX_ITF_8 = 0,
    GX_ITF_5 = 1,
    GX_ITF_4 = 2,
    GX_ITF_3 = 3,
    GX_MAX_ITFORMAT = 4,
} GXIndTexFormat;

typedef enum _GXIndTexMtxID
{
    GX_ITM_OFF = 0,
    GX_ITM_0 = 1,
    GX_ITM_1 = 2,
    GX_ITM_2 = 3,
    GX_ITM_S0 = 5,
    GX_ITM_S1 = 6,
    GX_ITM_S2 = 7,
    GX_ITM_T0 = 9,
    GX_ITM_T1 = 10,
    GX_ITM_T2 = 11,
} GXIndTexMtxID;

typedef enum _GXIndTexScale
{
    GX_ITS_1 = 0,
    GX_ITS_2 = 1,
    GX_ITS_4 = 2,
    GX_ITS_8 = 3,
    GX_ITS_16 = 4,
    GX_ITS_32 = 5,
    GX_ITS_64 = 6,
    GX_ITS_128 = 7,
    GX_ITS_256 = 8,
    GX_MAX_ITSCALE = 9,
} GXIndTexScale;

typedef enum _GXIndTexStageID
{
    GX_INDTEXSTAGE0 = 0,
    GX_INDTEXSTAGE1 = 1,
    GX_INDTEXSTAGE2 = 2,
    GX_INDTEXSTAGE3 = 3,
    GX_MAX_INDTEXSTAGE = 4,
} GXIndTexStageID;

typedef enum _GXIndTexWrap
{
    GX_ITW_OFF = 0,
    GX_ITW_256 = 1,
    GX_ITW_128 = 2,
    GX_ITW_64 = 3,
    GX_ITW_32 = 4,
    GX_ITW_16 = 5,
    GX_ITW_0 = 6,
    GX_MAX_ITWRAP = 7,
} GXIndTexWrap;

typedef enum _GXLightID
{
    GX_LIGHT0 = 1,
    GX_LIGHT1 = 2,
    GX_LIGHT2 = 4,
    GX_LIGHT3 = 8,
    GX_LIGHT4 = 16,
    GX_LIGHT5 = 32,
    GX_LIGHT6 = 64,
    GX_LIGHT7 = 128,
    GX_MAX_LIGHT = 256,
    GX_LIGHT_NULL = 0,
} GXLightID;

typedef enum _GXLogicOp
{
    GX_LO_CLEAR = 0,
    GX_LO_AND = 1,
    GX_LO_REVAND = 2,
    GX_LO_COPY = 3,
    GX_LO_INVAND = 4,
    GX_LO_NOOP = 5,
    GX_LO_XOR = 6,
    GX_LO_OR = 7,
    GX_LO_NOR = 8,
    GX_LO_EQUIV = 9,
    GX_LO_INV = 10,
    GX_LO_REVOR = 11,
    GX_LO_INVCOPY = 12,
    GX_LO_INVOR = 13,
    GX_LO_NAND = 14,
    GX_LO_SET = 15,
} GXLogicOp;

typedef enum _GXMiscToken
{
    GX_MT_XF_FLUSH = 1,
    GX_MT_DL_SAVE_CONTEXT = 2,
    GX_MT_NULL = 0,
} GXMiscToken;

typedef enum _GXPTTexMtx
{
    GX_PTTEXMTX0 = 64,
    GX_PTTEXMTX1 = 67,
    GX_PTTEXMTX2 = 70,
    GX_PTTEXMTX3 = 73,
    GX_PTTEXMTX4 = 76,
    GX_PTTEXMTX5 = 79,
    GX_PTTEXMTX6 = 82,
    GX_PTTEXMTX7 = 85,
    GX_PTTEXMTX8 = 88,
    GX_PTTEXMTX9 = 91,
    GX_PTTEXMTX10 = 94,
    GX_PTTEXMTX11 = 97,
    GX_PTTEXMTX12 = 100,
    GX_PTTEXMTX13 = 103,
    GX_PTTEXMTX14 = 106,
    GX_PTTEXMTX15 = 109,
    GX_PTTEXMTX16 = 112,
    GX_PTTEXMTX17 = 115,
    GX_PTTEXMTX18 = 118,
    GX_PTTEXMTX19 = 121,
    GX_PTIDENTITY = 125,
} GXPTTexMtx;

typedef enum _GXPerf0
{
    GX_PERF0_VERTICES = 0,
    GX_PERF0_CLIP_VTX = 1,
    GX_PERF0_CLIP_CLKS = 2,
    GX_PERF0_XF_WAIT_IN = 3,
    GX_PERF0_XF_WAIT_OUT = 4,
    GX_PERF0_XF_XFRM_CLKS = 5,
    GX_PERF0_XF_LIT_CLKS = 6,
    GX_PERF0_XF_BOT_CLKS = 7,
    GX_PERF0_XF_REGLD_CLKS = 8,
    GX_PERF0_XF_REGRD_CLKS = 9,
    GX_PERF0_CLIP_RATIO = 10,
    GX_PERF0_TRIANGLES = 11,
    GX_PERF0_TRIANGLES_CULLED = 12,
    GX_PERF0_TRIANGLES_PASSED = 13,
    GX_PERF0_TRIANGLES_SCISSORED = 14,
    GX_PERF0_TRIANGLES_0TEX = 15,
    GX_PERF0_TRIANGLES_1TEX = 16,
    GX_PERF0_TRIANGLES_2TEX = 17,
    GX_PERF0_TRIANGLES_3TEX = 18,
    GX_PERF0_TRIANGLES_4TEX = 19,
    GX_PERF0_TRIANGLES_5TEX = 20,
    GX_PERF0_TRIANGLES_6TEX = 21,
    GX_PERF0_TRIANGLES_7TEX = 22,
    GX_PERF0_TRIANGLES_8TEX = 23,
    GX_PERF0_TRIANGLES_0CLR = 24,
    GX_PERF0_TRIANGLES_1CLR = 25,
    GX_PERF0_TRIANGLES_2CLR = 26,
    GX_PERF0_QUAD_0CVG = 27,
    GX_PERF0_QUAD_NON0CVG = 28,
    GX_PERF0_QUAD_1CVG = 29,
    GX_PERF0_QUAD_2CVG = 30,
    GX_PERF0_QUAD_3CVG = 31,
    GX_PERF0_QUAD_4CVG = 32,
    GX_PERF0_AVG_QUAD_CNT = 33,
    GX_PERF0_CLOCKS = 34,
    GX_PERF0_NONE = 35,
} GXPerf0;

typedef enum _GXPerf1
{
    GX_PERF1_TEXELS = 0,
    GX_PERF1_TX_IDLE = 1,
    GX_PERF1_TX_REGS = 2,
    GX_PERF1_TX_MEMSTALL = 3,
    GX_PERF1_TC_CHECK1_2 = 4,
    GX_PERF1_TC_CHECK3_4 = 5,
    GX_PERF1_TC_CHECK5_6 = 6,
    GX_PERF1_TC_CHECK7_8 = 7,
    GX_PERF1_TC_MISS = 8,
    GX_PERF1_VC_ELEMQ_FULL = 9,
    GX_PERF1_VC_MISSQ_FULL = 10,
    GX_PERF1_VC_MEMREQ_FULL = 11,
    GX_PERF1_VC_STATUS7 = 12,
    GX_PERF1_VC_MISSREP_FULL = 13,
    GX_PERF1_VC_STREAMBUF_LOW = 14,
    GX_PERF1_VC_ALL_STALLS = 15,
    GX_PERF1_VERTICES = 16,
    GX_PERF1_FIFO_REQ = 17,
    GX_PERF1_CALL_REQ = 18,
    GX_PERF1_VC_MISS_REQ = 19,
    GX_PERF1_CP_ALL_REQ = 20,
    GX_PERF1_CLOCKS = 21,
    GX_PERF1_NONE = 22,
} GXPerf1;

typedef enum _GXPixelFmt
{
    GX_PF_RGB8_Z24 = 0,
    GX_PF_RGBA6_Z24 = 1,
    GX_PF_RGB565_Z16 = 2,
    GX_PF_Z24 = 3,
    GX_PF_Y8 = 4,
    GX_PF_U8 = 5,
    GX_PF_V8 = 6,
    GX_PF_YUV420 = 7,
} GXPixelFmt;

typedef enum _GXPosNrmMtx
{
    GX_PNMTX0 = 0,
    GX_PNMTX1 = 3,
    GX_PNMTX2 = 6,
    GX_PNMTX3 = 9,
    GX_PNMTX4 = 12,
    GX_PNMTX5 = 15,
    GX_PNMTX6 = 18,
    GX_PNMTX7 = 21,
    GX_PNMTX8 = 24,
    GX_PNMTX9 = 27,
} GXPosNrmMtx;

typedef enum _GXPrimitive
{
    GX_POINTS = 184,
    GX_LINES = 168,
    GX_LINESTRIP = 176,
    GX_TRIANGLES = 144,
    GX_TRIANGLESTRIP = 152,
    GX_TRIANGLEFAN = 160,
    GX_QUADS = 128,
} GXPrimitive;

typedef enum _GXProjectionType
{
    GX_PERSPECTIVE = 0,
    GX_ORTHOGRAPHIC = 1,
} GXProjectionType;

typedef enum _GXSpotFn
{
    GX_SP_OFF = 0,
    GX_SP_FLAT = 1,
    GX_SP_COS = 2,
    GX_SP_COS2 = 3,
    GX_SP_SHARP = 4,
    GX_SP_RING1 = 5,
    GX_SP_RING2 = 6,
} GXSpotFn;

// WARN: Multiple enumerators map to a single value. Choose carefully!
typedef enum _GXTevAlphaArg
{
    GX_CA_APREV = 0,
    GX_CA_A0 = 1,
    GX_CA_A1 = 2,
    GX_CA_A2 = 3,
    GX_CA_TEXA = 4,
    GX_CA_RASA = 5,
    GX_CA_KONST = 6,
    GX_CA_ZERO = 7,
    GX_CA_ONE = 6,
} GXTevAlphaArg;

typedef enum _GXTevBias
{
    GX_TB_ZERO = 0,
    GX_TB_ADDHALF = 1,
    GX_TB_SUBHALF = 2,
    GX_MAX_TEVBIAS = 3,
} GXTevBias;

typedef enum _GXTevClampMode
{
    GX_TC_LINEAR = 0,
    GX_TC_GE = 1,
    GX_TC_EQ = 2,
    GX_TC_LE = 3,
    GX_MAX_TEVCLAMPMODE = 4,
} GXTevClampMode;

// WARN: Multiple enumerators map to a single value. Choose carefully!
typedef enum _GXTevColorArg
{
    GX_CC_CPREV = 0,
    GX_CC_APREV = 1,
    GX_CC_C0 = 2,
    GX_CC_A0 = 3,
    GX_CC_C1 = 4,
    GX_CC_A1 = 5,
    GX_CC_C2 = 6,
    GX_CC_A2 = 7,
    GX_CC_TEXC = 8,
    GX_CC_TEXA = 9,
    GX_CC_RASC = 10,
    GX_CC_RASA = 11,
    GX_CC_ONE = 12,
    GX_CC_HALF = 13,
    GX_CC_KONST = 14,
    GX_CC_ZERO = 15,
    GX_CC_TEXRRR = 16,
    GX_CC_TEXGGG = 17,
    GX_CC_TEXBBB = 18,
    GX_CC_QUARTER = 14,
} GXTevColorArg;

typedef enum _GXTevColorChan
{
    GX_CH_RED = 0,
    GX_CH_GREEN = 1,
    GX_CH_BLUE = 2,
    GX_CH_ALPHA = 3,
} GXTevColorChan;

typedef enum _GXTevKAlphaSel
{
    GX_TEV_KASEL_1 = 0,
    GX_TEV_KASEL_7_8 = 1,
    GX_TEV_KASEL_3_4 = 2,
    GX_TEV_KASEL_5_8 = 3,
    GX_TEV_KASEL_1_2 = 4,
    GX_TEV_KASEL_3_8 = 5,
    GX_TEV_KASEL_1_4 = 6,
    GX_TEV_KASEL_1_8 = 7,
    GX_TEV_KASEL_K0_R = 16,
    GX_TEV_KASEL_K1_R = 17,
    GX_TEV_KASEL_K2_R = 18,
    GX_TEV_KASEL_K3_R = 19,
    GX_TEV_KASEL_K0_G = 20,
    GX_TEV_KASEL_K1_G = 21,
    GX_TEV_KASEL_K2_G = 22,
    GX_TEV_KASEL_K3_G = 23,
    GX_TEV_KASEL_K0_B = 24,
    GX_TEV_KASEL_K1_B = 25,
    GX_TEV_KASEL_K2_B = 26,
    GX_TEV_KASEL_K3_B = 27,
    GX_TEV_KASEL_K0_A = 28,
    GX_TEV_KASEL_K1_A = 29,
    GX_TEV_KASEL_K2_A = 30,
    GX_TEV_KASEL_K3_A = 31,
} GXTevKAlphaSel;

typedef enum _GXTevKColorID
{
    GX_KCOLOR0 = 0,
    GX_KCOLOR1 = 1,
    GX_KCOLOR2 = 2,
    GX_KCOLOR3 = 3,
    GX_MAX_KCOLOR = 4,
} GXTevKColorID;

typedef enum _GXTevKColorSel
{
    GX_TEV_KCSEL_1 = 0,
    GX_TEV_KCSEL_7_8 = 1,
    GX_TEV_KCSEL_3_4 = 2,
    GX_TEV_KCSEL_5_8 = 3,
    GX_TEV_KCSEL_1_2 = 4,
    GX_TEV_KCSEL_3_8 = 5,
    GX_TEV_KCSEL_1_4 = 6,
    GX_TEV_KCSEL_1_8 = 7,
    GX_TEV_KCSEL_K0 = 12,
    GX_TEV_KCSEL_K1 = 13,
    GX_TEV_KCSEL_K2 = 14,
    GX_TEV_KCSEL_K3 = 15,
    GX_TEV_KCSEL_K0_R = 16,
    GX_TEV_KCSEL_K1_R = 17,
    GX_TEV_KCSEL_K2_R = 18,
    GX_TEV_KCSEL_K3_R = 19,
    GX_TEV_KCSEL_K0_G = 20,
    GX_TEV_KCSEL_K1_G = 21,
    GX_TEV_KCSEL_K2_G = 22,
    GX_TEV_KCSEL_K3_G = 23,
    GX_TEV_KCSEL_K0_B = 24,
    GX_TEV_KCSEL_K1_B = 25,
    GX_TEV_KCSEL_K2_B = 26,
    GX_TEV_KCSEL_K3_B = 27,
    GX_TEV_KCSEL_K0_A = 28,
    GX_TEV_KCSEL_K1_A = 29,
    GX_TEV_KCSEL_K2_A = 30,
    GX_TEV_KCSEL_K3_A = 31,
} GXTevKColorSel;

typedef enum _GXTevMode
{
    GX_MODULATE = 0,
    GX_DECAL = 1,
    GX_BLEND = 2,
    GX_REPLACE = 3,
    GX_PASSCLR = 4,
} GXTevMode;

// WARN: Multiple enumerators map to a single value. Choose carefully!
typedef enum _GXTevOp
{
    GX_TEV_ADD = 0,
    GX_TEV_SUB = 1,
    GX_TEV_COMP_R8_GT = 8,
    GX_TEV_COMP_R8_EQ = 9,
    GX_TEV_COMP_GR16_GT = 10,
    GX_TEV_COMP_GR16_EQ = 11,
    GX_TEV_COMP_BGR24_GT = 12,
    GX_TEV_COMP_BGR24_EQ = 13,
    GX_TEV_COMP_RGB8_GT = 14,
    GX_TEV_COMP_RGB8_EQ = 15,
    GX_TEV_COMP_A8_GT = 14,
    GX_TEV_COMP_A8_EQ = 15,
} GXTevOp;

typedef enum _GXTevRegID
{
    GX_TEVPREV = 0,
    GX_TEVREG0 = 1,
    GX_TEVREG1 = 2,
    GX_TEVREG2 = 3,
    GX_MAX_TEVREG = 4,
} GXTevRegID;

typedef enum _GXTevScale
{
    GX_CS_SCALE_1 = 0,
    GX_CS_SCALE_2 = 1,
    GX_CS_SCALE_4 = 2,
    GX_CS_DIVIDE_2 = 3,
    GX_MAX_TEVSCALE = 4,
} GXTevScale;

typedef enum _GXTevStageID
{
    GX_TEVSTAGE0 = 0,
    GX_TEVSTAGE1 = 1,
    GX_TEVSTAGE2 = 2,
    GX_TEVSTAGE3 = 3,
    GX_TEVSTAGE4 = 4,
    GX_TEVSTAGE5 = 5,
    GX_TEVSTAGE6 = 6,
    GX_TEVSTAGE7 = 7,
    GX_TEVSTAGE8 = 8,
    GX_TEVSTAGE9 = 9,
    GX_TEVSTAGE10 = 10,
    GX_TEVSTAGE11 = 11,
    GX_TEVSTAGE12 = 12,
    GX_TEVSTAGE13 = 13,
    GX_TEVSTAGE14 = 14,
    GX_TEVSTAGE15 = 15,
    GX_MAX_TEVSTAGE = 16,
} GXTevStageID;

typedef enum _GXTevSwapSel
{
    GX_TEV_SWAP0 = 0,
    GX_TEV_SWAP1 = 1,
    GX_TEV_SWAP2 = 2,
    GX_TEV_SWAP3 = 3,
    GX_MAX_TEVSWAP = 4,
} GXTevSwapSel;

typedef enum _GXTexCacheSize
{
    GX_TEXCACHE_32K = 0,
    GX_TEXCACHE_128K = 1,
    GX_TEXCACHE_512K = 2,
    GX_TEXCACHE_NONE = 3,
} GXTexCacheSize;

typedef enum _GXTexCoordID
{
    GX_TEXCOORD0 = 0,
    GX_TEXCOORD1 = 1,
    GX_TEXCOORD2 = 2,
    GX_TEXCOORD3 = 3,
    GX_TEXCOORD4 = 4,
    GX_TEXCOORD5 = 5,
    GX_TEXCOORD6 = 6,
    GX_TEXCOORD7 = 7,
    GX_MAX_TEXCOORD = 8,
    GX_TEXCOORD_NULL = 255,
} GXTexCoordID;

typedef enum _GXTexFilter
{
    GX_NEAR = 0,
    GX_LINEAR = 1,
    GX_NEAR_MIP_NEAR = 2,
    GX_LIN_MIP_NEAR = 3,
    GX_NEAR_MIP_LIN = 4,
    GX_LIN_MIP_LIN = 5,
} GXTexFilter;

// WARN: Multiple enumerators map to a single value. Choose carefully!
typedef enum _GXTexFmt
{
    GX_TF_I4 = 0,
    GX_TF_I8 = 1,
    GX_TF_IA4 = 2,
    GX_TF_IA8 = 3,
    GX_TF_RGB565 = 4,
    GX_TF_RGB5A3 = 5,
    GX_TF_RGBA8 = 6,
    GX_TF_CMPR = 14,
    GX_CTF_R4 = 32,
    GX_CTF_RA4 = 34,
    GX_CTF_RA8 = 35,
    GX_CTF_YUVA8 = 38,
    GX_CTF_A8 = 39,
    GX_CTF_R8 = 40,
    GX_CTF_G8 = 41,
    GX_CTF_B8 = 42,
    GX_CTF_RG8 = 43,
    GX_CTF_GB8 = 44,
    GX_TF_Z8 = 17,
    GX_TF_Z16 = 19,
    GX_TF_Z24X8 = 22,
    GX_CTF_Z4 = 48,
    GX_CTF_Z8M = 57,
    GX_CTF_Z8L = 58,
    GX_CTF_Z16L = 60,
    GX_TF_A8 = 39,
} GXTexFmt;

typedef enum _GXTexGenSrc
{
    GX_TG_POS = 0,
    GX_TG_NRM = 1,
    GX_TG_BINRM = 2,
    GX_TG_TANGENT = 3,
    GX_TG_TEX0 = 4,
    GX_TG_TEX1 = 5,
    GX_TG_TEX2 = 6,
    GX_TG_TEX3 = 7,
    GX_TG_TEX4 = 8,
    GX_TG_TEX5 = 9,
    GX_TG_TEX6 = 10,
    GX_TG_TEX7 = 11,
    GX_TG_TEXCOORD0 = 12,
    GX_TG_TEXCOORD1 = 13,
    GX_TG_TEXCOORD2 = 14,
    GX_TG_TEXCOORD3 = 15,
    GX_TG_TEXCOORD4 = 16,
    GX_TG_TEXCOORD5 = 17,
    GX_TG_TEXCOORD6 = 18,
    GX_TG_COLOR0 = 19,
    GX_TG_COLOR1 = 20,
} GXTexGenSrc;

typedef enum _GXTexGenType
{
    GX_TG_MTX3x4 = 0,
    GX_TG_MTX2x4 = 1,
    GX_TG_BUMP0 = 2,
    GX_TG_BUMP1 = 3,
    GX_TG_BUMP2 = 4,
    GX_TG_BUMP3 = 5,
    GX_TG_BUMP4 = 6,
    GX_TG_BUMP5 = 7,
    GX_TG_BUMP6 = 8,
    GX_TG_BUMP7 = 9,
    GX_TG_SRTG = 10,
} GXTexGenType;

typedef enum _GXTexMapID
{
    GX_TEXMAP0 = 0,
    GX_TEXMAP1 = 1,
    GX_TEXMAP2 = 2,
    GX_TEXMAP3 = 3,
    GX_TEXMAP4 = 4,
    GX_TEXMAP5 = 5,
    GX_TEXMAP6 = 6,
    GX_TEXMAP7 = 7,
    GX_MAX_TEXMAP = 8,
    GX_TEXMAP_NULL = 255,
    GX_TEX_DISABLE = 256,
} GXTexMapID;

typedef enum _GXTexMtx
{
    GX_TEXMTX0 = 30,
    GX_TEXMTX1 = 33,
    GX_TEXMTX2 = 36,
    GX_TEXMTX3 = 39,
    GX_TEXMTX4 = 42,
    GX_TEXMTX5 = 45,
    GX_TEXMTX6 = 48,
    GX_TEXMTX7 = 51,
    GX_TEXMTX8 = 54,
    GX_TEXMTX9 = 57,
    GX_IDENTITY = 60,
} GXTexMtx;

typedef enum _GXTexMtxType
{
    GX_MTX3x4 = 0,
    GX_MTX2x4 = 1,
} GXTexMtxType;

typedef enum _GXTexOffset
{
    GX_TO_ZERO = 0,
    GX_TO_SIXTEENTH = 1,
    GX_TO_EIGHTH = 2,
    GX_TO_FOURTH = 3,
    GX_TO_HALF = 4,
    GX_TO_ONE = 5,
    GX_MAX_TEXOFFSET = 6,
} GXTexOffset;

typedef enum _GXTexWrapMode
{
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
} GXTexWrapMode;

typedef enum _GXTlut
{
    GX_TLUT0 = 0,
    GX_TLUT1 = 1,
    GX_TLUT2 = 2,
    GX_TLUT3 = 3,
    GX_TLUT4 = 4,
    GX_TLUT5 = 5,
    GX_TLUT6 = 6,
    GX_TLUT7 = 7,
    GX_TLUT8 = 8,
    GX_TLUT9 = 9,
    GX_TLUT10 = 10,
    GX_TLUT11 = 11,
    GX_TLUT12 = 12,
    GX_TLUT13 = 13,
    GX_TLUT14 = 14,
    GX_TLUT15 = 15,
    GX_BIGTLUT0 = 16,
    GX_BIGTLUT1 = 17,
    GX_BIGTLUT2 = 18,
    GX_BIGTLUT3 = 19,
} GXTlut;

typedef enum _GXTlutFmt
{
    GX_TL_IA8 = 0,
    GX_TL_RGB565 = 1,
    GX_TL_RGB5A3 = 2,
    GX_MAX_TLUTFMT = 3,
} GXTlutFmt;

typedef enum _GXTlutSize
{
    GX_TLUT_16 = 1,
    GX_TLUT_32 = 2,
    GX_TLUT_64 = 4,
    GX_TLUT_128 = 8,
    GX_TLUT_256 = 16,
    GX_TLUT_512 = 32,
    GX_TLUT_1K = 64,
    GX_TLUT_2K = 128,
    GX_TLUT_4K = 256,
    GX_TLUT_8K = 512,
    GX_TLUT_16K = 1024,
} GXTlutSize;

typedef enum _GXVCachePerf
{
    GX_VC_POS = 0,
    GX_VC_NRM = 1,
    GX_VC_CLR0 = 2,
    GX_VC_CLR1 = 3,
    GX_VC_TEX0 = 4,
    GX_VC_TEX1 = 5,
    GX_VC_TEX2 = 6,
    GX_VC_TEX3 = 7,
    GX_VC_TEX4 = 8,
    GX_VC_TEX5 = 9,
    GX_VC_TEX6 = 10,
    GX_VC_TEX7 = 11,
    GX_VC_ALL = 15,
} GXVCachePerf;

typedef enum _GXVtxFmt
{
    GX_VTXFMT0 = 0,
    GX_VTXFMT1 = 1,
    GX_VTXFMT2 = 2,
    GX_VTXFMT3 = 3,
    GX_VTXFMT4 = 4,
    GX_VTXFMT5 = 5,
    GX_VTXFMT6 = 6,
    GX_VTXFMT7 = 7,
    GX_MAX_VTXFMT = 8,
} GXVtxFmt;

typedef enum _GXXFFlushVal
{
    GX_XF_FLUSH_NONE = 0,
    GX_XF_FLUSH_SAFE = 8,
} GXXFFlushVal;

typedef enum _GXZFmt16
{
    GX_ZC_LINEAR = 0,
    GX_ZC_NEAR = 1,
    GX_ZC_MID = 2,
    GX_ZC_FAR = 3,
} GXZFmt16;

typedef enum _GXZTexOp
{
    GX_ZT_DISABLE = 0,
    GX_ZT_ADD = 1,
    GX_ZT_REPLACE = 2,
    GX_MAX_ZTEXOP = 3,
} GXZTexOp;

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_GX_ENUM_H
