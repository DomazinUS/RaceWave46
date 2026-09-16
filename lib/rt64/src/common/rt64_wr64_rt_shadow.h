#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "rt64_wr64_rt_scope.h"

namespace RT64 {
    struct Wr64RTShadowLight {
        // Unit world-space direction from the receiver towards the light.
        std::array<float, 3> toLight{};
        std::array<float, 3> diffuse{};
        std::array<float, 3> ambient{};
        bool valid = false;
    };

    constexpr bool wr64RTShadowScope(bool selected, bool reflectionScope, uint32_t course,
        uint32_t players, uint32_t phase, uint32_t mode) {
        // Reuse the proven course-scene scope, including Dolphin Park's
        // opening/title sequence. The separate rider-preview world stays out.
        return reflectionScope && wr64RTReflectionScope(selected, course, players, phase, mode);
    }

    constexpr bool wr64RTTwoPlayerShadowScope(bool selected, bool twoPlayerReflectionScope,
        uint32_t course, uint32_t players, uint32_t phase, uint32_t mode) {
        return wr64RTTwoPlayerReflectionScope(selected, course, players, phase, mode,
            twoPlayerReflectionScope);
    }

    // Hold lighting fixed in world space. Dolphin Park follows its native sun
    // bearing; Sunset Bay has a native fixed sunlight branch. Other courses retain their original
    // world-light preset. Mutable Crs_color is unsuitable as a general source:
    // ordinary courses rotate them with camera heading (8008F95C..8008FA78),
    // and other courses have additional special lighting behavior.
    // This does not claim that the native game had a fixed physical sun light.
    // Read on the producer thread and copy the value into the owning workload.
    inline Wr64RTShadowLight wr64RTShadowReadLight(const uint8_t *ram, size_t size,
        uint32_t course, uint32_t players, bool endingScope = false) {
        Wr64RTShadowLight result;
        if (ram == nullptr || size < 0x800000 || course > 8 || players != 1 ||
            (endingScope && course != 7)) {
            return result;
        }
        // Native US Rev1 Crs_color table, 0x110 bytes per course. init_world
        // (8008E4B0) copies this into the two mutable camera-light records.
        // init_world's phase21 branch (8008E564..8008E5B0) overwrites the
        // first light bank from the dedicated award preset at800DA404 (index10).
        // Retain that authored lighting instead of the course7 race colors.
        const uint32_t preset = 0x000D9964 + (endingScope ? 10U : course) * 0x110;
        auto word = [&](uint32_t offset) {
            uint32_t value = 0;
            std::memcpy(&value, ram + preset + offset, sizeof(value));
            return value;
        };
        double lengthSquared = 0.0;
        bool hasDiffuse = false;
        for (uint32_t i = 0; i < 3; i++) {
            const uint32_t diffuse = word(i * 4), ambient = word(0x0c + i * 4);
            const uint32_t bits = word(0xac + i * 4);
            float direction = 0.0f;
            std::memcpy(&direction, &bits, sizeof(direction));
            // Native signed-byte directional lights; reject corrupt or
            // uninitialized data before it can enter a ray direction.
            if (diffuse > 255 || ambient > 255 || !std::isfinite(direction) ||
                direction < -127.0f || direction > 127.0f) {
                return {};
            }
            result.diffuse[i] = float(diffuse) / 255.0f;
            result.ambient[i] = float(ambient) / 255.0f;
            result.toLight[i] = direction;
            lengthSquared += double(direction) * direction;
            hasDiffuse |= diffuse != 0;
        }
        if (!hasDiffuse || lengthSquared < 1.0 || result.toLight[1] <= 0.0f) {
            return {};
        }
        if (course == 0 || course == 2) {
            // Dolphin's visible sun (80089E24 -> 8008962C) uses angle 5 degrees,
            // truncated to native sine-table index 56: X=cos, Z=sin. Its old
            // preset points along -X, almost opposite the actual sun. Keep the
            // authored 45-degree light elevation: the sun's table height 120
            // is a camera-up pixel offset, not a physical world-space Y.
            // move_world's Sunset branch (8008F31C..8008F37C) uses these
            // fixed sine-table entries for world/rider X/Z, independent of
            // camera or reverse-course heading. 8008FA50..8008FA78 normalizes
            // X/Z to length 64 and sets Y64: native azimuth315, elevation45.
            // The original preset (0,85,85) is overwritten by that branch.
            const uint32_t sunIndex = course == 0 ? 56U : 3584U;
            float x = 0.0f, z = 0.0f;
            std::memcpy(&x, ram + 0x00154350 + ((sunIndex + 1024U) & 4095U) * 4U, sizeof(x));
            std::memcpy(&z, ram + 0x00154350 + sunIndex * 4U, sizeof(z));
            const double horizontalSquared = double(x) * x + double(z) * z;
            if (!std::isfinite(horizontalSquared) || horizontalSquared < 0.99 || horizontalSquared > 1.01) {
                return {};
            }
            const float inverseHorizontal = float(1.0 / std::sqrt(horizontalSquared));
            result.toLight = { x * inverseHorizontal, 1.0f, z * inverseHorizontal };
            lengthSquared = 0.0;
            for (float value : result.toLight) { lengthSquared += double(value) * value; }
        }
        const float inverseLength = float(1.0 / std::sqrt(lengthSquared));
        for (float &value : result.toLight) { value *= inverseLength; }
        result.valid = true;
        return result;
    }

    inline Wr64RTShadowLight wr64RTTwoPlayerShadowReadLight(const uint8_t *ram, size_t size,
        uint32_t course, uint32_t players, bool twoPlayerScope) {
        if (!twoPlayerScope || course > 8 || players != 2) return {};
        // Reuse each course's established one-player world-light policy,
        // including Sunset's native sun branch and the authored night/fog
        // colors. Neither camera's mutable light can rotate the shared sun.
        // Keep the original public reader's one-player eligibility unchanged.
        return wr64RTShadowReadLight(ram, size, course, 1);
    }
}
