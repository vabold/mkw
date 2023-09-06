#pragma once

#include <rk_types.h>

#include <decomp.h>

#include <game/kart/KartObjectProxy.hpp>

#ifdef __cplusplus
extern "C" {
#endif

// PAL: 0x805943b4..0x8059455c
UNKNOWN_FUNCTION(PlayerSub1c_construct);
// PAL: 0x8059455c..0x80594594
UNKNOWN_FUNCTION(unk_8059455c);
// PAL: 0x80594594..0x80594634
UNKNOWN_FUNCTION(unk_80594594);
// PAL: 0x80594634..0x80594644
UNKNOWN_FUNCTION(unk_80594634);
// PAL: 0x80594644..0x805946f4
UNKNOWN_FUNCTION(unk_80594644);
// PAL: 0x805946f4..0x80594704
UNKNOWN_FUNCTION(PlayerSub1c_startOobWipe);
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
UNKNOWN_FUNCTION(unk_805958f0);
// PAL: 0x80595918..0x805959d4
UNKNOWN_FUNCTION(PlayerSub1c_updateStartBoostCharge);
// PAL: 0x805959d4..0x80595af8
UNKNOWN_FUNCTION(PlayerSub1c_computeStartBoost);
// PAL: 0x80595af8..0x80595c5c
UNKNOWN_FUNCTION(PlayerSub1c_applyStartBoost);
// PAL: 0x80595c5c..0x80595ca4
UNKNOWN_FUNCTION(unk_80595c5c);
// PAL: 0x80595ca4..0x80595cb4
UNKNOWN_FUNCTION(unk_80595ca4);
// PAL: 0x80595cb4..0x80595cc4
UNKNOWN_FUNCTION(unk_80595cb4);
// PAL: 0x80595cc4..0x80595d04
UNKNOWN_FUNCTION(PlayerSub1c_destroy);

#ifdef __cplusplus
}
#endif

namespace Kart {

namespace KartFlags {

// We never reference this enum directly, we only reference the values
enum _KartFlags {
  FLAG_ACCELERATE = (32 * 0) + 0,
  FLAG_BRAKE = (32 * 0) + 1,
  FLAG_DRIFT_INPUT = (32 * 0) + 2,
  FLAG_DRIFT_MANUAL = (32 * 0) + 3,
  FLAG_OFFROAD_INVINCIBILITY = (32 * 1) + 8
};

} // namespace KartFlags

class KartState {
private:
  u8 _00[0x04 - 0x00];
  // For now, we round up to 160 until we have a certain number
  RKBitField<160> mFlags;
  KartObjectProxy* mProxy;
  u8 _1c[0xc0 - 0x1c];
};
static_assert(sizeof(KartState) == 0xc0);

} // namespace Kart
