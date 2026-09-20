#include "wr64_camera_fov.hpp"
#include "../lib/rt64/src/common/rt64_wr64_rt_two_player_assets.h"

#include <algorithm>
#include <atomic>
#include <bit>
#include <cmath>
#include <cstring>

namespace {
std::atomic<float> extraDegrees{0.0f};
uint32_t word(const uint8_t* rdram, uint32_t address) {
    uint32_t value;
    std::memcpy(&value, rdram + (address & 0x7FFFFFU), sizeof(value));
    return value;
}
}

namespace wr64::camera_fov {
void set_extra_degrees(double degrees) {
    extraDegrees.store(std::isfinite(degrees) ? float(std::clamp(degrees, 0.0, 10.0)) : 0.0f,
        std::memory_order_relaxed);
}
double extra_degrees() { return extraDegrees.load(std::memory_order_relaxed); }
}

extern "C" uint32_t wr64_camera_fov_lens(const uint8_t* rdram, uint32_t camera,
    uint32_t pool, uint32_t original_bits) {
    const float extra = extraDegrees.load(std::memory_order_relaxed);
    // Original is bit-identical, including exceptional inputs; no RAM reads.
    if (extra == 0.0f || !rdram) return original_bits;
    const uint32_t players = word(rdram, 0x800DAB28);
    const uint32_t mode = word(rdram, 0x800DAB24);
    const uint32_t course = word(rdram, 0x800D8170);
    if ((players != 1 && players != 2) || word(rdram, 0x801CE638) != 1 ||
        mode < 40 || mode > 44 || course > 8 ||
        (players == 2 && course == 0 && !RT64::wr64RTTwoPlayerAssetsReady(rdram, course)))
        return original_bits;

    // The native course cameras occupy exactly these two 0x10C-byte slots.
    // Type 3 initializes the normal follow camera and becomes type 4 at
    // 801DDC8C. Scripted introductions, finish cameras and menu previews keep
    // their authored lens. E8 is the matrix slot, not the viewport number.
    if (camera != 0x80227C80 && camera != 0x80227D8C) return original_bits;
    const uint32_t index = (camera - 0x80227C80) / 0x10C;
    if (word(rdram, camera) != 4 || word(rdram, camera + 0xE8) != index ||
        word(rdram, camera + 0x88) != original_bits) return original_bits;
    const uint32_t first = word(rdram, 0x80223930);
    if (first > 1) return original_bits;
    if (players == 1) {
        if (first != index) return original_bits;
    }
    else {
        const uint32_t second = word(rdram, 0x80223934);
        if (second > 1 || first == second) return original_bits;
    }

    // Limit the hook to the live native graphics pool. Initialization builds
    // both alternating pools; later native updates rebuild the active pool.
    if (pool != word(rdram, 0x801518B8) || (pool & 7) ||
        pool < 0x80000000 || pool > 0x80800000 - 0xE108) return original_bits;
    const float original = std::bit_cast<float>(original_bits);
    if (!std::isfinite(original) || original < 1.0f || original > 120.0f)
        return original_bits;

    // The original native builder uses degrees/720 for its half-angle sine
    // table lookup. Changing its argument therefore reaches the world, sky,
    // CPU celestial projectors and RT consumers through one native matrix.
    // A defensive ceiling avoids approaching a singular perspective lens.
    return std::bit_cast<uint32_t>(std::min(original + extra, 120.0f));
}
