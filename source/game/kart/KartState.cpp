#include "KartState.hpp"

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
extern UNKNOWN_FUNCTION(unk_80594594);
// PAL: 0x80594bd4
extern UNKNOWN_FUNCTION(PlayerSub1c_updateCollisions);
// PAL: 0x805959d4
extern UNKNOWN_FUNCTION(PlayerSub1c_computeStartBoost);
// PAL: 0x80595af8
extern UNKNOWN_FUNCTION(PlayerSub1c_applyStartBoost);
// PAL: 0x80599eac
extern UNKNOWN_FUNCTION(WheelPhysics_hasFloorCollision);
// PAL: 0x80599ec8
extern UNKNOWN_FUNCTION(WheelPhysics_getCollisionData);
// PAL: 0x80865138
extern UNKNOWN_FUNCTION(unk_80865138);// Extern data references.
// PAL: 0x802a4100
extern UNKNOWN_DATA(lbl_802a4100);
// PAL: 0x802a4130
extern UNKNOWN_DATA(lbl_802a4130);
// PAL: 0x80891ef0
extern UNKNOWN_DATA(lbl_80891ef0);
// PAL: 0x80891ef4
extern UNKNOWN_DATA(lbl_80891ef4);
// PAL: 0x80891ef8
extern UNKNOWN_DATA(lbl_80891ef8);
// PAL: 0x808b64e8
extern UNKNOWN_DATA(lbl_808b64e8);
// PAL: 0x808b64f8
extern UNKNOWN_DATA(lbl_808b64f8);
// PAL: 0x808b6528
extern UNKNOWN_DATA(lbl_808b6528);
// PAL: 0x808b6534
extern UNKNOWN_DATA(lbl_808b6534);
// PAL: 0x809bd728
extern UNKNOWN_DATA(spInstance__Q26System10RaceConfig);
// PAL: 0x809bd730
extern UNKNOWN_DATA(lbl_809bd730);
// PAL: 0x809c18f8
extern UNKNOWN_DATA(lbl_809c18f8);
// PAL: 0x809c1950
extern UNKNOWN_DATA(lbl_809c1950);
// PAL: 0x809c1951
extern UNKNOWN_DATA(lbl_809c1951);
}

// --- EXTERN DECLARATIONS END ---

// .rodata

// .data


// .bss


// Symbol: PlayerSub1c_construct
// PAL: 0x805943b4..0x8059455c
MARK_BINARY_BLOB(PlayerSub1c_construct, 0x805943b4, 0x8059455c);
asm UNKNOWN_FUNCTION(PlayerSub1c_construct) {
  #include "asm/805943b4.s"
}

// Symbol: unk_8059455c
// PAL: 0x8059455c..0x80594594
MARK_BINARY_BLOB(unk_8059455c, 0x8059455c, 0x80594594);
asm UNKNOWN_FUNCTION(unk_8059455c) {
  #include "asm/8059455c.s"
}

// Symbol: unk_80594594
// PAL: 0x80594594..0x80594634
MARK_BINARY_BLOB(unk_80594594, 0x80594594, 0x80594634);
asm UNKNOWN_FUNCTION(unk_80594594) {
  #include "asm/80594594.s"
}

// Symbol: unk_80594634
// PAL: 0x80594634..0x80594644
MARK_BINARY_BLOB(unk_80594634, 0x80594634, 0x80594644);
asm UNKNOWN_FUNCTION(unk_80594634) {
  #include "asm/80594634.s"
}

// Symbol: unk_80594644
// PAL: 0x80594644..0x805946f4
MARK_BINARY_BLOB(unk_80594644, 0x80594644, 0x805946f4);
asm UNKNOWN_FUNCTION(unk_80594644) {
  #include "asm/80594644.s"
}

// Symbol: PlayerSub1c_startOobWipe
// PAL: 0x805946f4..0x80594704
MARK_BINARY_BLOB(PlayerSub1c_startOobWipe, 0x805946f4, 0x80594704);
asm UNKNOWN_FUNCTION(PlayerSub1c_startOobWipe) {
  #include "asm/805946f4.s"
}

// Symbol: unk_80594704
// PAL: 0x80594704..0x8059474c
MARK_BINARY_BLOB(unk_80594704, 0x80594704, 0x8059474c);
asm UNKNOWN_FUNCTION(unk_80594704) {
  #include "asm/80594704.s"
}

// Symbol: PlayerSub1c_updateCollisionsAndMore
// PAL: 0x8059474c..0x8059487c
MARK_BINARY_BLOB(PlayerSub1c_updateCollisionsAndMore, 0x8059474c, 0x8059487c);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateCollisionsAndMore) {
  #include "asm/8059474c.s"
}

// Symbol: PlayerSub1c_updateFromInput
// PAL: 0x8059487c..0x80594bd4
MARK_BINARY_BLOB(PlayerSub1c_updateFromInput, 0x8059487c, 0x80594bd4);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateFromInput) {
  #include "asm/8059487c.s"
}

// Symbol: PlayerSub1c_updateCollisions
// PAL: 0x80594bd4..0x805958ec
MARK_BINARY_BLOB(PlayerSub1c_updateCollisions, 0x80594bd4, 0x805958ec);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateCollisions) {
  #include "asm/80594bd4.s"
}

// Symbol: unk_805958ec
// PAL: 0x805958ec..0x805958f0
MARK_BINARY_BLOB(unk_805958ec, 0x805958ec, 0x805958f0);
asm UNKNOWN_FUNCTION(unk_805958ec) {
  #include "asm/805958ec.s"
}

// Symbol: unk_805958f0
// PAL: 0x805958f0..0x80595918
MARK_BINARY_BLOB(unk_805958f0, 0x805958f0, 0x80595918);
asm UNKNOWN_FUNCTION(unk_805958f0) {
  #include "asm/805958f0.s"
}

// Symbol: PlayerSub1c_updateStartBoostCharge
// PAL: 0x80595918..0x805959d4
MARK_BINARY_BLOB(PlayerSub1c_updateStartBoostCharge, 0x80595918, 0x805959d4);
asm UNKNOWN_FUNCTION(PlayerSub1c_updateStartBoostCharge) {
  #include "asm/80595918.s"
}

// Symbol: PlayerSub1c_computeStartBoost
// PAL: 0x805959d4..0x80595af8
MARK_BINARY_BLOB(PlayerSub1c_computeStartBoost, 0x805959d4, 0x80595af8);
asm UNKNOWN_FUNCTION(PlayerSub1c_computeStartBoost) {
  #include "asm/805959d4.s"
}

// Symbol: PlayerSub1c_applyStartBoost
// PAL: 0x80595af8..0x80595c5c
MARK_BINARY_BLOB(PlayerSub1c_applyStartBoost, 0x80595af8, 0x80595c5c);
asm UNKNOWN_FUNCTION(PlayerSub1c_applyStartBoost) {
  #include "asm/80595af8.s"
}

// Symbol: unk_80595c5c
// PAL: 0x80595c5c..0x80595ca4
MARK_BINARY_BLOB(unk_80595c5c, 0x80595c5c, 0x80595ca4);
asm UNKNOWN_FUNCTION(unk_80595c5c) {
  #include "asm/80595c5c.s"
}

// Symbol: unk_80595ca4
// PAL: 0x80595ca4..0x80595cb4
MARK_BINARY_BLOB(unk_80595ca4, 0x80595ca4, 0x80595cb4);
asm UNKNOWN_FUNCTION(unk_80595ca4) {
  #include "asm/80595ca4.s"
}

// Symbol: unk_80595cb4
// PAL: 0x80595cb4..0x80595cc4
MARK_BINARY_BLOB(unk_80595cb4, 0x80595cb4, 0x80595cc4);
asm UNKNOWN_FUNCTION(unk_80595cb4) {
  #include "asm/80595cb4.s"
}

// Symbol: PlayerSub1c_destroy
// PAL: 0x80595cc4..0x80595d04
MARK_BINARY_BLOB(PlayerSub1c_destroy, 0x80595cc4, 0x80595d04);
asm UNKNOWN_FUNCTION(PlayerSub1c_destroy) {
  #include "asm/80595cc4.s"
}

