#pragma once

#include <rk_types.h>

namespace Kart {

struct KartSettings {
  u8 _00[0x10 - 0x00];
  u8 mPlayerIdx;
};

} // namespace Kart
