#include "wr64_sunny_water.hpp"
#include "wr64_sunny_detail.hpp"
#include "recomp.h"

namespace {
bool enabled(uint8_t* rdram) {
    return rdram && wr64_sunny_detail_water_active(rdram) &&
        uint32_t(MEM_W(0, S32(0x800DAB2C))) < 2;
}
}

extern "C" uint32_t wr64_sunny_water_material_players(uint8_t* rdram, uint32_t original) {
    // The enhanced course load installs the matching native RGBA32 wave texture.
    // Select only its translucent material branch. The later player-count read
    // still chooses the two independent native wave meshes and viewports.
    return enabled(rdram) ? 1u : original;
}

extern "C" uint32_t wr64_sunny_water_environment(uint8_t* rdram, uint32_t original) {
    // The native single-player material reads its luminance from player zero's
    // environment record. Its two call sites use a fixed 801D0000 load base;
    // select the current view's existing record without updating either one.
    if (!enabled(rdram) || original != 0x801D0000) return original;
    return original + uint32_t(MEM_W(0, S32(0x800DAB2C))) * 0x110;
}
