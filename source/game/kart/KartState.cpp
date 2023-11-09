#include "KartState.hpp"

#include <game/kart/KartObject.hpp>
#include <game/system/RaceConfig.hpp>
#include <game/system/RaceManager.hpp>

// --- EXTERN DECLARATIONS BEGIN ---

extern "C" {

// Extern function references.
// PAL: 0x80021580
extern UNKNOWN_FUNCTION(_savegpr_19);
// PAL: 0x800215cc
extern UNKNOWN_FUNCTION(_restgpr_19);
// PAL: 0x80229dcc
extern UNKNOWN_FUNCTION(__nw__FUl);
// PAL: 0x8022f80c
extern UNKNOWN_FUNCTION(sqrt__Q23EGG5MathfFf);
// PAL: 0x80243adc
extern UNKNOWN_FUNCTION(normalise__Q23EGG8Vector3fFv);
// PAL: 0x80533090
extern UNKNOWN_FUNCTION(RaceInfo_getCountdown);
// PAL: 0x80536230
extern UNKNOWN_FUNCTION(Raceinfo_isAtLeastStage);
// PAL: 0x8053db34
extern UNKNOWN_FUNCTION(unk_8053db34);
// PAL: 0x8056e70c
extern UNKNOWN_FUNCTION(unk_8056e70c);
// PAL: 0x80573ed4
extern UNKNOWN_FUNCTION(PlayerSub18_updateRespawn);
// PAL: 0x805758e4
extern UNKNOWN_FUNCTION(PlayerZipper_end);
// PAL: 0x805766b8
extern UNKNOWN_FUNCTION(PlayerTrick_end);
// PAL: 0x8057f7a8
extern UNKNOWN_FUNCTION(PlayerSub10_endTrick);
// PAL: 0x8058212c
extern UNKNOWN_FUNCTION(PlayerSub10_applyStartBoost);
// PAL: 0x805890b0
extern UNKNOWN_FUNCTION(unk_805890b0);
// PAL: 0x8059018c
extern UNKNOWN_FUNCTION(__ct__Q24Kart15KartObjectProxyFv);
// PAL: 0x8059020c
extern UNKNOWN_FUNCTION(PlayerPointers_getPlayerPosition);
// PAL: 0x805902ec
extern UNKNOWN_FUNCTION(PlayerPointers_getWheelCount1);
// PAL: 0x805903ac
extern UNKNOWN_FUNCTION(PlayerPointers_getPlayerPhysicsHolder);
// PAL: 0x805903cc
extern UNKNOWN_FUNCTION(PlayerPointers_getPlayerPhysics);
// PAL: 0x805903f4
extern UNKNOWN_FUNCTION(KartAccessor_getInput);
// PAL: 0x8059041c
extern UNKNOWN_FUNCTION(unk_8059041c);
// PAL: 0x80590664
extern UNKNOWN_FUNCTION(PlayerPointers_isCpu);
// PAL: 0x805906dc
extern UNKNOWN_FUNCTION(kartTire__Q24Kart15KartObjectProxyFl);
// PAL: 0x80590734
extern UNKNOWN_FUNCTION(PlayerPointers_getWheelPhysics);
// PAL: 0x8059077c
extern UNKNOWN_FUNCTION(kartMove__Q24Kart15KartObjectProxyFv);
// PAL: 0x805907a0
extern UNKNOWN_FUNCTION(unk_805907a0);
// PAL: 0x8059084c
extern UNKNOWN_FUNCTION(kartCollide__Q24Kart15KartObjectProxyFv);
// PAL: 0x80590a5c
extern UNKNOWN_FUNCTION(PlayerPointers_getPlayerIdx);
// PAL: 0x80590a6c
extern UNKNOWN_FUNCTION(PlayerPointers_isBike);
// PAL: 0x80590d08
extern UNKNOWN_FUNCTION(playerPointers_getSpeed);
// PAL: 0x80590d5c
extern UNKNOWN_FUNCTION(unk_80590d5c);
// PAL: 0x80591044
extern UNKNOWN_FUNCTION(unk_80591044);
// PAL: 0x805911a8
extern UNKNOWN_FUNCTION(unk_805911a8);
// PAL: 0x805911c0
extern UNKNOWN_FUNCTION(unk_805911c0);
// PAL: 0x80591440
extern UNKNOWN_FUNCTION(kartNetSender__Q24Kart15KartObjectProxyFv);
// PAL: 0x805917c0
extern UNKNOWN_FUNCTION(unk_805917c0);
// PAL: 0x80591904
extern UNKNOWN_FUNCTION(kartHalfPipe__Q24Kart15KartObjectProxyFv);
// PAL: 0x80591914
extern UNKNOWN_FUNCTION(kartJump__Q24Kart15KartObjectProxyFv);
// PAL: 0x80594594
extern UNKNOWN_FUNCTION(reset__Q24Kart9KartStateFv);
// PAL: 0x80594bd4
extern UNKNOWN_FUNCTION(PlayerSub1c_updateCollisions);
// PAL: 0x805959d4
extern UNKNOWN_FUNCTION(PlayerSub1c_computeStartBoost);
// PAL: 0x80595af8
extern UNKNOWN_FUNCTION(PlayerSub1c_applyStartBoost);
// PAL: 0x80595cc4
extern UNKNOWN_FUNCTION(PlayerSub1c_destroy);
// PAL: 0x80599eac
extern UNKNOWN_FUNCTION(WheelPhysics_hasFloorCollision);
// PAL: 0x80599ec8
extern UNKNOWN_FUNCTION(WheelPhysics_getCollisionData);
// PAL: 0x80865138
extern UNKNOWN_FUNCTION(unk_80865138); // Extern data references.
// PAL: 0x802a4130
extern UNKNOWN_DATA(RKSystem_ey);
// PAL: 0x808b6534
extern UNKNOWN_DATA(__vt__Q24Kart9KartState);
// PAL: 0x809bd728
extern UNKNOWN_DATA(spInstance__Q26System10RaceConfig);
// PAL: 0x809bd730
extern UNKNOWN_DATA(spInstance__Q26System11RaceManager);
// PAL: 0x809c18f8
extern UNKNOWN_DATA(lbl_809c18f8);
// PAL: 0x809c1950
extern UNKNOWN_DATA(sOnlineLocal__Q24Kart10KartObject);
// PAL: 0x809c1951
extern UNKNOWN_DATA(sOnlineRemote__Q24Kart10KartObject);
}

extern "C" EGG::Vector3f RKSystem_zero;

// --- EXTERN DECLARATIONS END ---

// .rodata
/*const u32 lbl_80891ef0[] = {0x00000000};
const u32 lbl_80891ef4[] = {0x3f800000};
const u32 lbl_80891ef8[] = {0x43300000, 0x80000000, 0x41200000, 0x3f4ccccd,
                            0x3f59999a, 0x3d4ccccd, 0xc1b00000, 0xc0e00000};*/

#ifndef SHIFTABLE
extern "C" f32 KART_STATE_ZERO_F__4Kart;
REL_SYMBOL_AT(KART_STATE_ZERO_F__4Kart, 0x80891ef0)
extern "C" f32 KART_STATE_ONE_F__4Kart;
REL_SYMBOL_AT(KART_STATE_ONE_F__4Kart, 0x80891ef4)
extern "C" f64 KART_STATE_DIVIDE_F__4Kart;
REL_SYMBOL_AT(KART_STATE_DIVIDE_F__4Kart, 0x80891ef8)

extern "C" u32 sFrameCount__Q24Kart9KartState;
REL_SYMBOL_AT(sFrameCount__Q24Kart9KartState, 0x808b6528)
#else
namespace Kart {

static const f32 KART_STATE_ZERO_F = 0.f;
static const f32 KART_STATE_ONE_F = 1.f;
static const f64 KART_STATE_DIVIDE_F =
    reinterpret_cast<f64>(0x4330000080000000ULL);

} // namespace Kart
#endif

// .data
#pragma explicit_zero_data on
u32 lbl_808b64e8[] = {0x3ca3d70a, 0x3b03126f, 0x3f75c28f, 0x3ca3d70a};
u32 lbl_808b64f8[] = {0x3f59999a, 0x00000000, 0x3f6147ae, 0x000a0000,
                      0x3f67ae14, 0x00140000, 0x3f6ccccd, 0x001e0000,
                      0x3f70a3d7, 0x002d0000, 0x3f733333, 0x00460000};
#pragma explicit_zero_data off
extern "C" u32 lbl_808b6528[];
// extern "C" u32 __vt__Q24Kart9KartState[];

// .bss

#ifndef EQUIVALENT
// https://decomp.me/scratch/BMILo - Equivalent
// Symbol: __ct__Q24Kart9KartStateFPQ24Kart12KartSettings
// PAL: 0x805943b4..0x8059455c
MARK_BINARY_BLOB(__ct__Q24Kart9KartStateFPQ24Kart12KartSettings, 0x805943b4,
                 0x8059455c);
asm UNKNOWN_FUNCTION(__ct__Q24Kart9KartStateFPQ24Kart12KartSettings) {
#include "asm/805943b4.s"
}
#else
namespace Kart {

MARK_FLOW_CHECK(0x805943b4);
KartState::KartState(KartSettings* settings) {
  mAirtime = 0;
  _24 = 0.0f;
  mCnptId = 0;
  mStartBoostIdx = 0;
  mTop.z = 0.0f;
  mTop.y = 0.0f;
  mTop.x = 0.0f;
  mProxy = new KartObjectProxy;

  switch (System::RaceConfig::spInstance->mRaceScenario
              .mPlayers[settings->mPlayerIdx]
              .mPlayerType) {
  case System::RaceConfig::Player::TYPE_REAL_LOCAL:
    mFlags.set(KartFlags::FLAG_LOCAL);
    break;
  case System::RaceConfig::Player::TYPE_CPU:
    mFlags.set(KartFlags::FLAG_CPU);
    break;
  case System::RaceConfig::Player::TYPE_GHOST:
    mFlags.set(KartFlags::FLAG_GHOST);
  default:
    break;
  }

  if (KartObject::sOnlineLocal) {
    mFlags.set(KartFlags::FLAG_ONLINE_LOCAL);
  } else {
    if (KartObject::sOnlineRemote) {
      mFlags.set(KartFlags::FLAG_ONLINE_REMOTE);
    }
  }

  System::KPadController* controller =
      System::RaceManager::spInstance->mPlayers[settings->mPlayerIdx]
          ->mPad->mController;
  bool isDriftAuto = controller ? controller->mDriftIsAuto : false;
  if (isDriftAuto) {
    mFlags.set(KartFlags::FLAG_AUTOMATIC_DRIFT);
  }

  if (System::RaceConfig::spInstance->mRaceScenario.mSettings.mGameMode ==
          System::RaceConfig::Settings::GAMEMODE_AWARDS &&
      System::RaceConfig::spInstance->mRaceScenario.mSettings.mCameraMode ==
          System::RaceConfig::Settings::CAMERA_MODE_LOSS) {
    mFlags.field(4) |= 0xa00;
  }
}

} // namespace Kart
#endif

namespace Kart {

void KartState::init() {
  reset();
  resetOob();
}

void KartState::reset() {
  mFlags.field(3) = 0;
  mFlags.field(2) = 0;
  mFlags.field(1) = 0;
  mFlags.field(0) = 0;
  mAirtime = 0;
  _24 = 0.0f;

  mTop.z = 0.0f;
  mTop.y = 0.0f;
  mTop.x = 0.0f;
  _40.z = 0.0f;
  _40.y = 0.0f;
  _40.x = 0.0f;

  _58 = 0;
  _5c = 0;
  mHwgTimer = 0;
  _70 = 0;
  mBoostRampType = -1;
  mJumpPadType = -1;
  _84 = 0;
  mStartBoostCharge = 0.0f;
  mStick.y = 0.0f;
  mStick.x = 0.0f;
  _a4 = 0;

  _4c = _a8 = RKSystem_zero;

  _a6 = 0;
}

void KartState::resetOob() {
  mWipeState = -1;
  mWipeFrame = -1;
}

void KartState::calcOob() {
  static s16 sFrameCount[1] = {180};

  if (mWipeState == -1) {
    return;
  }

  mWipeDuration = ++mWipeFrame / (f32)sFrameCount[mWipeState];
  if (1.0f < mWipeDuration) {
    mWipeDuration = 1.0f;
  }

  if (mWipeFrame > sFrameCount[mWipeState]) {
    mWipeState = -1;
  }
}

void KartState::startWipe(int wipeState) {
  mWipeState = wipeState;
  mWipeFrame = 0;
}

void KartState::calcFlagsAndStick() {
  mFlags.field(0) &= ~0x1806387;
  mFlags.field(1) &= ~0x1000;
  mFlags.field(2) &= ~0xc0401000;
  mStick.y = 0.0f;
  mStick.x = 0.0f;
}

} // namespace Kart

// Symbol: PlayerSub1c_updateCollisionsAndMore
// PAL: 0x8059474c..0x8059487c
MARK_BINARY_BLOB(PlayerSub1c_updateCollisionsAndMore, 0x8059474c, 0x8059487c);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateCollisionsAndMore){
#include "asm/8059474c.s"
}

// Symbol: PlayerSub1c_updateFromInput
// PAL: 0x8059487c..0x80594bd4
MARK_BINARY_BLOB(PlayerSub1c_updateFromInput, 0x8059487c, 0x80594bd4);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateFromInput){
#include "asm/8059487c.s"
}

// Symbol: PlayerSub1c_updateCollisions
// PAL: 0x80594bd4..0x805958ec
MARK_BINARY_BLOB(PlayerSub1c_updateCollisions, 0x80594bd4, 0x805958ec);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateCollisions) {
#include "asm/80594bd4.s"
}

namespace Kart {

void KartState::empty() {}

// TODO: better name
// TODO: all reset flags documented
void KartState::resetCollisionFlags() {
  mFlags.field(1) &= ~0x8080200;
  mFlags.field(2) &= ~0x408;
}

} // namespace Kart

#ifndef EQUIVALENT
// https://decomp.me/scratch/s5cyy - matching, needs implementing
// Symbol: PlayerSub1c_updateStartBoostCharge
// PAL: 0x80595918..0x805959d4
MARK_BINARY_BLOB(PlayerSub1c_updateStartBoostCharge, 0x80595918, 0x805959d4);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateStartBoostCharge) {
#include "asm/80595918.s"
}
#else
namespace Kart {

void KartState::calcStartBoost() {
  static f32 START_BOOST_DELTA_ONE = 0.02f;
  static f32 START_BOOST_DELTA_TWO = 0.002f;
  static f32 START_BOOST_FALLOFF = 0.96f;

  if (mFlags.on(KartFlags::FLAG_CHARGE_START_BOOST)) {
    f32 x = START_BOOST_DELTA_ONE - START_BOOST_DELTA_TWO;
    mStartBoostCharge += START_BOOST_DELTA_ONE - x * mStartBoostCharge;
  } else {
    mStartBoostCharge *= START_BOOST_FALLOFF;
  }

  if (0.0f > mStartBoostCharge) {
    mStartBoostCharge = 0.0f;
  } else if (1.0f < mStartBoostCharge) {
    mStartBoostCharge = 1.0f;
  }

  mProxy->kartMove()->setScaledStartBoostCharge(mStartBoostCharge * 10.0f);
}

} // namespace Kart
#endif

// Symbol: PlayerSub1c_computeStartBoost
// PAL: 0x805959d4..0x80595af8
MARK_BINARY_BLOB(PlayerSub1c_computeStartBoost, 0x805959d4, 0x80595af8);
asm UNKNOWN_FUNCTION(PlayerSub1c_computeStartBoost){
#include "asm/805959d4.s"
}

// Symbol: PlayerSub1c_applyStartBoost
// PAL: 0x80595af8..0x80595c5c
MARK_BINARY_BLOB(PlayerSub1c_applyStartBoost, 0x80595af8, 0x80595c5c);
asm UNKNOWN_FUNCTION(PlayerSub1c_applyStartBoost){
#include "asm/80595af8.s"
}

// Symbol: unk_80595c5c
// PAL: 0x80595c5c..0x80595ca4
MARK_BINARY_BLOB(unk_80595c5c, 0x80595c5c, 0x80595ca4);
asm UNKNOWN_FUNCTION(unk_80595c5c) {
#include "asm/80595c5c.s"
}

namespace Kart {

void KartState::setCameraFlag() {
  mFlags.set(KartFlags::FLAG_SOMETHING_CAMERA);
}

void KartState::resetCameraFlag() {
  mFlags.reset(KartFlags::FLAG_SOMETHING_CAMERA);
}

KartState::~KartState() {}

} // namespace Kart

#pragma explicit_zero_data on
u32 lbl_808b6528[] = {0x0000000a, 0x42200000};
#pragma explicit_zero_data off
