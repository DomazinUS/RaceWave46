#include "common/rt64_wr64_rt_scope.h"
#include "common/rt64_wr64_rt_shadow.h"
#include "common/rt64_wr64_rt_two_player_assets.h"
#include "../rt_shadows/native_light_presets.h"

#include <bit>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

namespace {
unsigned checks = 0;
void require(bool value, const char *message) {
    ++checks;
    if (!value) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
}

int main() {
    using namespace RT64;
    // The eight native VS tracks share race states 40..45 / phase 1. Adjacent
    // menus, introductions, Dolphin Park and one-player scope stay excluded.
    for (uint32_t course = 0; course <= 10; ++course)
    for (uint32_t players : {0u, 1u, 2u, 3u, UINT32_MAX})
    for (uint32_t phase = 0; phase <= 17; ++phase)
    for (uint32_t mode = 0; mode <= 64; ++mode)
    for (bool selected : {false, true}) for (bool loaded : {false, true}) {
        const bool expected = course >= 1 && course <= 8 && players == 2 &&
            phase == 1 && mode >= 40 && mode <= 45 && selected && loaded;
        const bool scope = wr64RTTwoPlayerReflectionScope(selected, course, players, phase, mode, loaded);
        require(scope == expected, "two-player scope admitted an unsupported native state");
        require(wr64RTTwoPlayerShadowScope(true, scope, course, players, phase, mode) == scope,
            "two-player shadow scope diverged from reflections");
        require(!wr64RTTwoPlayerShadowScope(false, scope, course, players, phase, mode), "shadow setting ignored");
        require(wr64RTSkyReflectionScope(scope, true) == scope, "sky failed to follow eligible reflections");
        require(!wr64RTSkyReflectionScope(scope, false), "sky selection ignored");
        if (players == 2) {
            require(!wr64RTReflectionScope(true, course, players, phase, mode), "original one-player scope broadened");
            require(!wr64RTShadowScope(true, scope, course, players, phase, mode),
                "one-player-only AO scope enabled in two-player play");
        }
    }
    require(!wr64RTTwoPlayerReflectionScope(true, UINT32_MAX, 2, 1, 40, true), "overflowing course accepted");
    require(!wr64RTTwoPlayerReflectionScope(true, 1, 2, UINT32_MAX, 40, true), "overflowing phase accepted");
    require(!wr64RTTwoPlayerReflectionScope(true, 1, 2, 1, UINT32_MAX, true), "overflowing mode accepted");

    std::vector<uint8_t> ram(0x800000), other(0x800000);
    for (uint32_t course = 1; course <= 8; ++course) {
        require(!wr64RTTwoPlayerAssetsReady(ram.data(), course), "initial resident latch set");
    }
    for (uint32_t course = 1; course <= 8; ++course) {
        wr64RTPublishTwoPlayerAssets(ram.data(), course);
        for (uint32_t candidate = 0; candidate <= 10; ++candidate) {
            require(wr64RTTwoPlayerAssetsReady(ram.data(), candidate) == (candidate == course),
                "resident assets leaked between courses on the same RAM instance");
            require(!wr64RTTwoPlayerAssetsReady(other.data(), candidate), "another RAM instance inherited assets");
            require(!wr64RTTwoPlayerAssetsReady(nullptr, candidate), "null RAM inherited assets");
        }
        const bool savedScope = wr64RTTwoPlayerReflectionScope(true, course, 2, 1, 41,
            wr64RTTwoPlayerAssetsReady(ram.data(), course));
        wr64RTPublishTwoPlayerAssets(nullptr, 0);
        require(!wr64RTTwoPlayerAssetsReady(ram.data(), course), "new course load retained previous assets");
        require(savedScope, "published workload snapshot followed a later course load");
        wr64RTPublishTwoPlayerAssets(other.data(), course);
        require(!wr64RTTwoPlayerAssetsReady(ram.data(), course) && wr64RTTwoPlayerAssetsReady(other.data(), course),
            "RAM ownership was not replaced");
    }
    for (uint32_t invalid : {0u, 9u, UINT32_MAX}) {
        wr64RTPublishTwoPlayerAssets(ram.data(), 1);
        wr64RTPublishTwoPlayerAssets(ram.data(), invalid);
        require(!wr64RTTwoPlayerAssetsReady(ram.data(), invalid), "invalid resident course accepted");
        for (uint32_t course = 1; course <= 8; ++course)
            require(!wr64RTTwoPlayerAssetsReady(ram.data(), course), "invalid publication retained older owner");
    }
    wr64RTPublishTwoPlayerAssets(nullptr, 0);

    auto word = [&](uint32_t address, uint32_t value) { std::memcpy(ram.data() + address, &value, 4); };
    auto resetPreset = [&](uint32_t course) {
        const auto &native = NativeLightPresets[course];
        const uint32_t preset = 0xD9964 + course * 0x110;
        for (unsigned i = 0; i < 3; ++i) {
            word(preset + i * 4, native.diffuse[i]);
            word(preset + 0xC + i * 4, native.ambient[i]);
            word(preset + 0xAC + i * 4, std::bit_cast<uint32_t>(native.direction[i]));
        }
        word(0x154B50, std::bit_cast<uint32_t>(0.7071067690849304f));
        word(0x157B50, std::bit_cast<uint32_t>(-0.7071067690849304f));
    };
    for (uint32_t course = 1; course <= 8; ++course) {
        resetPreset(course);
        const auto original = wr64RTShadowReadLight(ram.data(), ram.size(), course, 1);
        const auto beforeRead = ram;
        const auto twoPlayer = wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), course, 2, true);
        require(ram == beforeRead, "reading authored two-player light mutated native memory");
        require(original.valid && twoPlayer.valid && original.toLight == twoPlayer.toLight &&
            original.diffuse == twoPlayer.diffuse && original.ambient == twoPlayer.ambient,
            "two-player lighting differs from the established one-player authored policy");
        const auto &native = NativeLightPresets[course];
        for (unsigned i = 0; i < 3; ++i) {
            require(twoPlayer.diffuse[i] == float(native.diffuse[i]) / 255.0f &&
                twoPlayer.ambient[i] == float(native.ambient[i]) / 255.0f,
                "authored night/fog course lighting colors lost");
        }
        if (course == 2) {
            require(std::fabs(twoPlayer.toLight[0] - 0.5f) < 1e-6f &&
                std::fabs(twoPlayer.toLight[1] - std::sqrt(0.5f)) < 1e-6f &&
                std::fabs(twoPlayer.toLight[2] + 0.5f) < 1e-6f,
                "Sunset lost its native fixed sun azimuth/elevation");
        }
        for (unsigned sample = 0; sample < 16; ++sample) {
            // Camera movement, reverse heading and mutable per-camera light
            // must never rotate a course's world-fixed authored shadow light.
            for (uint32_t i = 0; i < 0x220; ++i) ram[0x1CB058 + i] = uint8_t(i + sample * 17);
            for (uint32_t i = 0; i < 0x218; ++i) ram[0x227C80 + i] = uint8_t(i + sample * 31);
            ram[0xDAB68 ^ 3] = uint8_t(sample & 1);
            const auto moved = wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), course, 2, true);
            require(moved.valid && moved.toLight == original.toLight && moved.diffuse == original.diffuse &&
                moved.ambient == original.ambient, "camera or live light changed the authored course light");
        }
        for (uint32_t players : {0u, 1u, 3u, UINT32_MAX})
            require(!wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), course, players, true).valid,
                "invalid player count accepted by two-player light reader");
        require(!wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), course, 2, false).valid, "unscoped light accepted");
        require(!wr64RTTwoPlayerShadowReadLight(nullptr, ram.size(), course, 2, true).valid, "null light data accepted");
        require(!wr64RTTwoPlayerShadowReadLight(ram.data(), 0x7FFFFF, course, 2, true).valid, "undersized RAM accepted");
        require(!wr64RTShadowReadLight(ram.data(), ram.size(), course, 2).valid, "original light reader broadened");
        const uint32_t preset = 0xD9964 + course * 0x110;
        for (float invalid : {0.0f, -1.0f, 128.0f, std::numeric_limits<float>::quiet_NaN()}) {
            word(preset + 0xB0, std::bit_cast<uint32_t>(invalid));
            require(!wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), course, 2, true).valid,
                "invalid native direction accepted");
            resetPreset(course);
        }
        word(preset, 256);
        require(!wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), course, 2, true).valid,
            "invalid native light color accepted");
        resetPreset(course);
    }
    for (uint32_t course : {0u, 9u, 10u, UINT32_MAX})
        require(!wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), course, 2, true).valid,
            "unsupported two-player course light accepted");
    word(0x154B50, std::bit_cast<uint32_t>(std::numeric_limits<float>::quiet_NaN()));
    require(!wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), 2, 2, true).valid,
        "invalid native sun table accepted in two-player Sunset");
    std::cout << "PASS " << checks << " all-course two-player scope, resident owner and authored-light checks\n";
}
