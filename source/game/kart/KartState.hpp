#pragma once

#include <rk_types.h>

#include <decomp.h>

#include <game/kart/KartObjectProxy.hpp>
#include <game/kart/KartSettings.hpp>

#ifdef __cplusplus
extern "C" {
#endif

// PAL: 0x805943b4..0x8059455c
UNKNOWN_FUNCTION(__ct__Q24Kart9KartStateFPQ24Kart12KartSettings);
// PAL: 0x8059455c..0x80594594
UNKNOWN_FUNCTION(init__Q24Kart9KartStateFv);
// PAL: 0x80594594..0x80594634
UNKNOWN_FUNCTION(reset__Q24Kart9KartStateFv);
// PAL: 0x80594634..0x80594644
UNKNOWN_FUNCTION(resetOob__Q24Kart9KartStateFv);
// PAL: 0x80594644..0x805946f4
UNKNOWN_FUNCTION(unk_80594644);
// PAL: 0x805946f4..0x80594704
UNKNOWN_FUNCTION(startWipe__Q24Kart9KartStateFi);
// PAL: 0x80594704..0x8059474c
UNKNOWN_FUNCTION(unk_80594704);
// PAL: 0x8059474c..0x8059487c
UNKNOWN_FUNCTION(PlayerSub1c_updateCollisionsAndMore);
// PAL: 0x8059487c..0x80594bd4
UNKNOWN_FUNCTION(PlayerSub1c_updateFromInput);
// PAL: 0x80594bd4..0x805958ec
UNKNOWN_FUNCTION(PlayerSub1c_updateCollisions);
// PAL: 0x805958ec..0x805958f0
UNKNOWN_FUNCTION(unk_805958ec);
// PAL: 0x805958f0..0x80595918
UNKNOWN_FUNCTION(resetCollisionFlags__Q24Kart9KartStateFv);
// PAL: 0x80595918..0x805959d4
UNKNOWN_FUNCTION(PlayerSub1c_updateStartBoostCharge);
// PAL: 0x805959d4..0x80595af8
UNKNOWN_FUNCTION(PlayerSub1c_computeStartBoost);
// PAL: 0x80595af8..0x80595c5c
UNKNOWN_FUNCTION(PlayerSub1c_applyStartBoost);
// PAL: 0x80595c5c..0x80595ca4
UNKNOWN_FUNCTION(unk_80595c5c);
// PAL: 0x80595ca4..0x80595cb4
UNKNOWN_FUNCTION(setCameraFlag__Q24Kart9KartStateFv);
// PAL: 0x80595cb4..0x80595cc4
UNKNOWN_FUNCTION(resetCameraFlag__Q24Kart9KartStateFv);
// PAL: 0x80595cc4..0x80595d04
UNKNOWN_FUNCTION(PlayerSub1c_destroy);

#ifdef __cplusplus
}
#endif

namespace Kart {

namespace KartFlags {

// We never reference this enum directly, we only reference the values
enum _KartFlags {
  FLAG_CPU = (32 * 4) + 0,
  FLAG_LOCAL = (32 * 4) + 1,
  FLAG_ONLINE_LOCAL = (32 * 4) + 2,
  FLAG_ONLINE_REMOTE = (32 * 4) + 3,
  FLAG_AUTOMATIC_DRIFT = (32 * 4) + 4,
  FLAG_SOMETHING_CAMERA = (32 * 4) + 5,
  FLAG_GHOST = (32 * 4) + 6
};

} // namespace KartFlags

class KartState {
public:
  KartState(KartSettings* settings);
  virtual ~KartState();

  void init();
  void reset();
  void resetOob();
  void calcOob();
  void startWipe(int wipeState);
  void calcFlagsAndStick();

  void empty();
  void resetCollisionFlags();
  void setCameraFlag();
  void resetCameraFlag();

private:
  // For now, we round up to 160 until we have a certain number
  RKBitField<160> mFlags;
  KartObjectProxy* mProxy;
  u32 mAirtime;
  u8 _20[0x24 - 0x20];
  f32 _24;
  EGG::Vector3f mTop;
  u8 _34[0x40 - 0x34];
  EGG::Vector3f _40;
  EGG::Vector3f _4c;
  u32 _58;
  u32 _5c;
  u8 _60[0x6c - 0x60];
  u32 mHwgTimer;
  u32 _70;
  s32 mBoostRampType;
  s32 mJumpPadType;
  u8 _7c[0x80 - 0x7c];
  u32 mCnptId;
  u16 _84;
  EGG::Vector2f mStick;
  int mWipeState;
  s16 mWipeFrame;
  f32 mWipeDuration;
  f32 mStartBoostCharge;
  s32 mStartBoostIdx;
  u16 _a4;
  u16 _a6;
  EGG::Vector3f _a8;
  u8 _b4[0xc0 - 0xb4];
};
static_assert(sizeof(KartState) == 0xc0);

} // namespace Kart
