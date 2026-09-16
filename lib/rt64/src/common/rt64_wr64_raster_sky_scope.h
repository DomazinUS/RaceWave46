#pragma once

#include "rt64_wr64_rt_scope.h"
#include "rt64_wr64_rt_settings.h"

namespace RT64 {
    // Native race courses 1..8 share the established two-player scene guard.
    // Enhanced assets must already belong to the loaded race.
    inline constexpr bool wr64RasterTwoPlayerScope(bool selected, uint32_t course,
        uint32_t players, uint32_t phase, uint32_t mode, bool loadedEnhanced) {
        return wr64RTTwoPlayerReflectionScope(selected, course,
            players, phase, mode, loadedEnhanced);
    }

    // Reuse the established native scene domains, including the Dolphin Park
    // opening and per-player views with enhanced course assets loaded.
    inline constexpr bool wr64RasterSkyScope(bool selected, uint32_t course,
        uint32_t players, uint32_t phase, uint32_t mode, uint32_t menuLayout = 0,
        bool loadedEnhanced = false) {
        return wr64RTReflectionScope(selected, course, players, phase, mode) ||
            wr64RTMenuReflectionScope(selected, course, players, phase, mode, menuLayout) ||
            wr64RTTwoPlayerReflectionScope(selected, course, players, phase, mode, loadedEnhanced);
    }

    struct Wr64WaterEffectScopes {
        bool rayScene = false, objects = false, raySky = false, rasterSky = false;
        bool rasterScene = false;
        bool menu = false, twoPlayer = false;
    };

    inline constexpr Wr64WaterEffectScopes wr64WaterEffectScopes(const Wr64RTSettings &settings,
        bool startupAllowed, uint32_t course, uint32_t players, uint32_t phase,
        uint32_t mode, uint32_t menuLayout, bool loadedEnhanced) {
        Wr64WaterEffectScopes result;
        if (!startupAllowed) return result;
        result.rasterScene = wr64RTReflectionScope(settings.rasterReflections,
            course, players, phase, mode) || wr64RasterTwoPlayerScope(settings.rasterReflections,
                course, players, phase, mode, loadedEnhanced);
        const bool selected = settings.reflections || settings.skyReflections;
        const bool scene = wr64RTReflectionScope(selected, course, players, phase, mode);
        result.menu = wr64RTMenuReflectionScope(selected, course, players, phase, mode, menuLayout);
        const bool legacyTwoPlayer = wr64RTTwoPlayerReflectionScope(selected,
            course, players, phase, mode, loadedEnhanced);
        result.twoPlayer = legacyTwoPlayer || wr64RasterTwoPlayerScope(
            settings.rasterReflections || settings.rasterShadows,
            course, players, phase, mode, loadedEnhanced);
        const bool eligible = scene || result.menu || legacyTwoPlayer;
        result.objects = eligible && settings.reflections;
        result.raySky = eligible && settings.skyReflections && !settings.rasterSky;
        result.rasterSky = eligible && settings.skyReflections && settings.rasterSky;
        result.rayScene = result.objects || result.raySky;
        return result;
    }
}
