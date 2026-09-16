#pragma once

#include <atomic>
#include <cmath>
#include <cstdint>

namespace RT64 {
    struct Wr64RTSettings {
        bool reflections;
        bool shadows;
        uint32_t reflectionDistancePercent = 100u;
        uint32_t shadowSamples = 16u;
        bool skyReflections = false;
        bool rasterSky = true;
        uint32_t rasterSkyStrengthPercent = 100u;
        bool rasterShadows = false;
        bool rasterReflections = false;
        uint32_t rasterShadowDistanceMode = 0u;
    };

    // One snapshot is consumed at workload setup and startup preparation. UI
    // callbacks may run on another thread; never mutate the process environment
    // to publish live renderer settings.
    namespace Wr64RTSettingsDetail {
        inline constexpr uint32_t Reflections = 1u;
        inline constexpr uint32_t Shadows = 2u;
        inline constexpr uint32_t FrontendOwned = 4u;
        inline constexpr uint32_t SkyReflections = 8u;
        inline constexpr uint32_t RasterSky = 16u;
        inline constexpr uint32_t RasterShadows = 32u;
        inline constexpr uint32_t RasterReflections = 64u;
        inline constexpr uint32_t ReflectionDistanceShift = 8u;
        inline constexpr uint32_t ReflectionDistanceMask = 127u << ReflectionDistanceShift;
        inline constexpr uint32_t ShadowSamplesShift = 16u;
        inline constexpr uint32_t ShadowSamplesMask = 31u << ShadowSamplesShift;
        inline constexpr uint32_t RasterShadowDistanceShift = 21u;
        inline constexpr uint32_t RasterShadowDistanceMask = 3u << RasterShadowDistanceShift;
        inline constexpr uint32_t RasterSkyStrengthShift = 24u;
        inline constexpr uint32_t RasterSkyStrengthMask = 255u << RasterSkyStrengthShift;
        inline std::atomic_uint32_t value{Shadows | RasterSky | (100u << ReflectionDistanceShift) |
            (16u << ShadowSamplesShift) | (100u << RasterSkyStrengthShift)};

        inline void setField(uint32_t mask, uint32_t selected) {
            uint32_t previous = value.load(std::memory_order_relaxed);
            uint32_t next;
            do {
                next = (previous & ~mask) | (selected & mask) | FrontendOwned;
            } while (!value.compare_exchange_weak(previous, next, std::memory_order_relaxed));
        }

        inline void set(uint32_t bit, bool enabled) { setField(bit, enabled ? bit : 0u); }

        inline uint32_t quantize(double requested, uint32_t minimum, uint32_t maximum, uint32_t step) {
            if (!std::isfinite(requested)) return maximum;
            const double bounded = requested < minimum ? minimum : requested > maximum ? maximum : requested;
            return minimum + uint32_t(std::floor((bounded - minimum) / step + 0.5)) * step;
        }
    }

    inline void setWr64WaterReflections(uint32_t mode) {
        // Value 2 belongs to the retired RasterSky profile migration; the
        // independent raster object/scenery mode uses a new stable value.
        const uint32_t selected = mode == 1u ? Wr64RTSettingsDetail::Reflections :
            mode == 3u ? Wr64RTSettingsDetail::RasterReflections : 0u;
        Wr64RTSettingsDetail::setField(Wr64RTSettingsDetail::Reflections | Wr64RTSettingsDetail::RasterReflections, selected);
    }

    inline void setWr64ShadowMethod(uint32_t method) {
        const uint32_t selected = method == 0u ? 0u : method == 1u ?
            Wr64RTSettingsDetail::RasterShadows : Wr64RTSettingsDetail::Shadows;
        Wr64RTSettingsDetail::setField(Wr64RTSettingsDetail::Shadows | Wr64RTSettingsDetail::RasterShadows, selected);
    }

    inline void setWr64RayTracedShadows(bool enabled) {
        setWr64ShadowMethod(enabled ? 2u : 0u);
    }

    inline void setWr64SkyReflections(bool enabled) {
        Wr64RTSettingsDetail::set(Wr64RTSettingsDetail::SkyReflections, enabled);
    }

    inline void setWr64SkyReflectionMethod(uint32_t method) {
        Wr64RTSettingsDetail::set(Wr64RTSettingsDetail::RasterSky, method != 1u);
    }

    inline void setWr64ReflectionDistance(double percent) {
        Wr64RTSettingsDetail::setField(Wr64RTSettingsDetail::ReflectionDistanceMask,
            Wr64RTSettingsDetail::quantize(percent, 25u, 100u, 5u) << Wr64RTSettingsDetail::ReflectionDistanceShift);
    }

    inline void setWr64ShadowSamples(double samples) {
        Wr64RTSettingsDetail::setField(Wr64RTSettingsDetail::ShadowSamplesMask,
            Wr64RTSettingsDetail::quantize(samples, 4u, 16u, 4u) << Wr64RTSettingsDetail::ShadowSamplesShift);
    }

    inline void setWr64RasterShadowDistance(uint32_t mode) {
        Wr64RTSettingsDetail::setField(Wr64RTSettingsDetail::RasterShadowDistanceMask,
            (mode <= 3u ? mode : 0u) << Wr64RTSettingsDetail::RasterShadowDistanceShift);
    }

    inline void setWr64RasterSkyStrength(double percent) {
        const uint32_t selected = std::isfinite(percent) ? Wr64RTSettingsDetail::quantize(percent, 100u, 200u, 5u) : 100u;
        Wr64RTSettingsDetail::setField(Wr64RTSettingsDetail::RasterSkyStrengthMask,
            selected << Wr64RTSettingsDetail::RasterSkyStrengthShift);
    }

    inline Wr64RTSettings getWr64RTSettings() {
        const uint32_t selected = Wr64RTSettingsDetail::value.load(std::memory_order_relaxed);
        return { (selected & Wr64RTSettingsDetail::Reflections) != 0,
            (selected & Wr64RTSettingsDetail::Shadows) != 0,
            (selected & Wr64RTSettingsDetail::ReflectionDistanceMask) >> Wr64RTSettingsDetail::ReflectionDistanceShift,
            (selected & Wr64RTSettingsDetail::ShadowSamplesMask) >> Wr64RTSettingsDetail::ShadowSamplesShift,
            (selected & Wr64RTSettingsDetail::SkyReflections) != 0,
            (selected & Wr64RTSettingsDetail::RasterSky) != 0,
            (selected & Wr64RTSettingsDetail::RasterSkyStrengthMask) >> Wr64RTSettingsDetail::RasterSkyStrengthShift,
            (selected & Wr64RTSettingsDetail::RasterShadows) != 0,
            (selected & Wr64RTSettingsDetail::RasterReflections) != 0,
            (selected & Wr64RTSettingsDetail::RasterShadowDistanceMask) >> Wr64RTSettingsDetail::RasterShadowDistanceShift };
    }

    // Parked AO/blur prototypes remain available to isolated development
    // probes. They cannot be enabled by inherited flags after the frontend
    // takes ownership of the application's feature settings.
    inline bool wr64RTDevelopmentEffectsAllowed() {
        return (Wr64RTSettingsDetail::value.load(std::memory_order_relaxed) &
            Wr64RTSettingsDetail::FrontendOwned) == 0;
    }
}
