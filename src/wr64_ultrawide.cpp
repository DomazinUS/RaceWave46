#include "wr64_ultrawide.hpp"
#include "../lib/rt64/src/common/rt64_wr64_ultrawide.h"
#include "../lib/rt64/src/common/rt64_wr64_dolphin_sun_sprite.h"

#include <algorithm>
#include <cmath>
#include <cstring>

// Reuse the existing Shindou host celestial boundary model (sdl_platform.cpp),
// adapted to the USA IPS baseline. SDL/window access stays on the host thread;
// native producers read the effective plane published by the RT64 workload.
extern "C" float wr64_sun_logical_width() {
    return RT64::wr64UltrawideLogicalWidth();
}

extern "C" float wr64_sun_half_extension() {
    return (wr64_sun_logical_width() - RT64::Wr64BaselineWidth) * 0.5f;
}

extern "C" uint32_t wr64_sun_logical_width_bits() {
    const float width = wr64_sun_logical_width();
    uint32_t bits = 0;
    static_assert(sizeof(bits) == sizeof(width));
    std::memcpy(&bits, &width, sizeof(bits));
    return bits;
}

extern "C" int32_t wr64_sun_logical_right_edge() {
    return std::max(423, static_cast<int32_t>(std::ceil(wr64_sun_logical_width())) - 1);
}

extern "C" int32_t wr64_sun_horizontal_cull_limit() {
    return static_cast<int32_t>(std::ceil(wr64_sun_logical_width() + 128.0f));
}

extern "C" float wr64_sun_record_window_limit() {
    return std::max(1024.0f, static_cast<float>(wr64_sun_horizontal_cull_limit() + 384));
}

// The USA projector rejects dot products below 0.5 before screen coordinates
// exist. At 21:9 that cuts Sunset Bay's disk/glow with about a third visible.
// Dolphin Park uses the same gate, but its native projection is symmetric.
// Defer only these main suns' forward-facing, formerly rejected candidates;
// the native projector still calculates the coordinates and depth normally.
extern "C" int32_t wr64_sun_right_exit_probe(uint32_t record_address, int32_t course, float facing) {
    return record_address == 0x801C4170U && (course == 0 || course == 2) &&
        wr64_sun_logical_width() > RT64::Wr64BaselineWidth && facing > 0.0f && facing < 0.5f;
}

extern "C" int32_t wr64_sun_right_exit_keep(uint32_t x_bits, uint32_t half_width_bits) {
    float x, half_width;
    std::memcpy(&x, &x_bits, sizeof(x));
    std::memcpy(&half_width, &half_width_bits, sizeof(half_width));
    // Match sun_draw's center calculation, not the record's x field alone.
    const float center = std::trunc(x + half_width);
    // Keep the existing offscreen tail allowance so interpolated output can
    // finish its exit. The consumer's cull and renderer scissor still apply.
    // Reject the left half exactly as the original angular gate did.
    return std::isfinite(center) && center > wr64_sun_logical_width() * 0.5f &&
        center < static_cast<float>(wr64_sun_horizontal_cull_limit());
}

extern "C" int32_t wr64_sun_dolphin_exit_keep(uint32_t x_bits, uint32_t half_width_bits) {
    float x, half_width;
    std::memcpy(&x, &x_bits, sizeof(x));
    std::memcpy(&half_width, &half_width_bits, sizeof(half_width));
    const float center = std::trunc(x + half_width);
    // Dolphin Park skips Sunset Bay's horizontal direction adjustment. Its
    // original angular gate can therefore cut either edge of a wider view.
    // Retain the existing 128-pixel offscreen allowance on both sides; native
    // UV clipping and the established vertical park/transit handling remain.
    return std::isfinite(center) && center > -128.0f &&
        center < static_cast<float>(wr64_sun_horizontal_cull_limit());
}

extern "C" float wr64_sun_wash_edge(int32_t course, float facing, double native_cutoff,
    uint32_t x_bits, uint32_t half_width_bits, int32_t sprite_radius) {
    const float width = wr64_sun_logical_width();
    // -1 leaves every previously enabled wash on its exact native path.
    // The record's facing value and the flares' separate intensity are never
    // changed. Only the newly visible horizontal portion is admitted here.
    if (width <= RT64::Wr64BaselineWidth || (course != 0 && course != 2) ||
        !std::isfinite(facing) || !(facing > 0.0f) ||
        !std::isfinite(native_cutoff) || facing > native_cutoff) return -1.0f;
    float x, half_width;
    std::memcpy(&x, &x_bits, sizeof(x));
    std::memcpy(&half_width, &half_width_bits, sizeof(half_width));
    const float center = x + half_width;
    if (!std::isfinite(center) || sprite_radius <= 0) return 0.0f;
    const float radius = static_cast<float>(sprite_radius);
    const float overlap = std::min(width, center + radius) - std::max(0.0f, center - radius);
    // The native facing^4 attenuation continues through the former cutoff.
    // Scale only its newly admitted edge tail by visible disk coverage so it
    // reaches zero at the actual image edge, without a second hard switch.
    return std::clamp(overlap / (2.0f * radius), 0.0f, 1.0f);
}

extern "C" float wr64_dolphin_sun_effects(uint8_t* ram, float native_factor) {
    // Apply normal sun effects during the native disk exit. Returning -1 preserves
    // the original effect producer without changing the disk geometry or opacity.
    static const bool enabled = [] {
        const char* value = std::getenv("WR64_DOLPHIN_SUN_VISIBLE_EFFECTS");
        // Exact 0 retains the previous effects for troubleshooting.
        return !value || !value[0] || (value[0] == '1' && value[1] == '\0');
    }();
    if (!enabled || !RT64::wr64DolphinSunNativeExitEnabled() || !ram ||
        !std::isfinite(native_factor) || native_factor < 0.0f || native_factor > 1.0f) return -1.0f;
    const auto word = [ram](uint32_t address) {
        return RT64::wr64DolphinSunReadWord(ram, address & 0x1fffffffu);
    };
    if (word(0x800d8170u) != 0 || word(0x800dab28u) != 1 ||
        word(0x801ce638u) != 1 || word(0x800d9944u) != 12) return -1.0f;
    const auto number = [&word](uint32_t address) {
        const uint32_t bits = word(address);
        float value;
        std::memcpy(&value, &bits, sizeof(value));
        return value;
    };
    const float center_x = number(0x801c4170u) + number(0x801c417cu);
    const float center_y = number(0x801c4174u) - number(0x801c4180u);
    const float depth = number(0x801c4178u);
    const float facing = number(0x801c4184u);
    if (!std::isfinite(center_x) || !std::isfinite(center_y) || !std::isfinite(depth) ||
        depth == -64.0f || !std::isfinite(facing) || facing < 0.0f || facing > 1.0f ||
        center_x < -128.0f || center_x > 4096.0f || center_y < -128.0f || center_y >= 240.0f) return -1.0f;
    constexpr float radius = 12.0f;
    const float overlap_x = std::clamp((std::min(wr64_sun_logical_width(), center_x + radius) -
        std::max(0.0f, center_x - radius)) / (radius * 2.0f), 0.0f, 1.0f);
    const float overlap_y = std::clamp((std::min(240.0f, center_y + radius) -
        std::max(0.0f, center_y - radius)) / (radius * 2.0f), 0.0f, 1.0f);
    // The original height factor reaches zero at camera Y <= 20 even with a
    // visible disk. Retain its stronger values, but give visible low-camera
    // sunlight a modest floor. Native facing^2/^4 still controls flare/wash
    // brightness. Coverage brings both effects to zero as the disk exits.
    constexpr float minimum_visible_strength = 0.35f;
    return std::max(native_factor, minimum_visible_strength) * overlap_x * overlap_y;
}
