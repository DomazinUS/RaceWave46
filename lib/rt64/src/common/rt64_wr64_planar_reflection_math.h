#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace RT64 {
    struct Wr64PlanarClipProjection {
        bool valid = false;
        float rows[4][4] = {};
    };

    // Convert the N64 presentation VP (already expressed as row-dot rows) to
    // the same clip coordinates emitted by RSPProcessCS followed by RasterVS.
    // Framebuffer size is the native FbParams.resolution, not capture size.
    inline Wr64PlanarClipProjection wr64BuildPlanarD3DClipProjection(
        const float nativeRows[4][4], const float viewportScale[3],
        const float viewportTranslate[3], const float framebufferSize[2],
        const float screenScale[2], const float screenOffset[2]) {
        Wr64PlanarClipProjection result;
        if (!nativeRows || !viewportScale || !viewportTranslate ||
            !framebufferSize || !screenScale || !screenOffset) return result;
        for (size_t i = 0; i < 3; ++i)
            if (!std::isfinite(viewportScale[i]) || !std::isfinite(viewportTranslate[i])) return {};
        for (size_t i = 0; i < 2; ++i)
            if (!std::isfinite(framebufferSize[i]) || framebufferSize[i] <= 0 ||
                !std::isfinite(screenScale[i]) || !std::isfinite(screenOffset[i])) return {};
        const double scaleX = 2.0 * viewportScale[0] / framebufferSize[0] * screenScale[0];
        const double scaleY = 2.0 * viewportScale[1] / framebufferSize[1] * screenScale[1];
        const double offsetX = (2.0 * viewportTranslate[0] / framebufferSize[0] - 1) * screenScale[0] + screenOffset[0];
        const double offsetY = (1.0 - 2.0 * viewportTranslate[1] / framebufferSize[1]) * screenScale[1] + screenOffset[1];
        for (size_t col = 0; col < 4; ++col) {
            for (size_t row = 0; row < 4; ++row) if (!std::isfinite(nativeRows[row][col])) return {};
            result.rows[0][col] = float(scaleX*nativeRows[0][col] + offsetX*nativeRows[3][col]);
            result.rows[1][col] = float(scaleY*nativeRows[1][col] + offsetY*nativeRows[3][col]);
            result.rows[2][col] = float(double(viewportScale[2])*nativeRows[2][col] + double(viewportTranslate[2])*nativeRows[3][col]);
            result.rows[3][col] = nativeRows[3][col];
            for (size_t row = 0; row < 4; ++row) if (!std::isfinite(result.rows[row][col])) return {};
        }
        result.valid = true;
        return result;
    }

    struct Wr64PlanarWaterDatum {
        bool valid = false;
        float height = 0.0f;
    };

    // Read on the native producer thread and retain with the owning workload.
    // USA sea_offset is the signed integer at 80192458. vertex_sea adds it to
    // wave samples and writes it directly to the flat perimeter; move_sea
    // lowers it for Southern Island. The local wave median is not this datum.
    // RAM follows the recomp's host-native 32-bit word storage convention.
    inline Wr64PlanarWaterDatum wr64ReadPlanarWaterDatum(const uint8_t *ram,
        size_t size, uint32_t course, uint32_t players, bool validatedTwoPlayerScope = false) {
        // Both race views share this world datum, including Southern's tide.
        // The producer supplies the validated Enhanced race scope rather than
        // a live menu preference.
        const bool twoPlayer = course <= 8 && players == 2 && validatedTwoPlayerScope;
        if (!ram || size < 0x800000 || course > 8 || (players != 1 && !twoPlayer)) return {};
        int32_t nativeHeight = 0;
        std::memcpy(&nativeHeight, ram + 0x00192458, sizeof(nativeHeight));
        // The native vertex writer stores the common height in signed VTX Y.
        if (nativeHeight < -32768 || nativeHeight > 32767) return {};
        return {true, float(nativeHeight)};
    }

    struct Wr64PlanarReflectionProjection {
        bool valid = false;
        float rows[4][4] = {};
        // Positive signed distance retains real geometry above the water.
        // The capture shader may subtract a small explicit clipping bias.
        float clipPlane[4] = {};
    };

    // Input is the final presentation world-to-D3D-clip mapping, expressed as
    // clip[i] = dot(worldToClipRows[i], float4(world, 1)). Include the native
    // viewport/depth conversion before calling: a raw N64 view-projection has
    // different Z conventions. No hlslpp memory-layout assumptions live here.
    // Reflecting the scene about Y=planeY is exactly the mirrored-camera view.
    // It reverses winding, so capture culling must account for that separately.
    inline Wr64PlanarReflectionProjection wr64BuildPlanarReflectionProjection(
        const float worldToClipRows[4][4], float planeY) {
        Wr64PlanarReflectionProjection result;
        if (!worldToClipRows || !std::isfinite(planeY)) return result;
        double wMagnitude = 0;
        for (size_t row = 0; row < 4; ++row) {
            for (size_t col = 0; col < 4; ++col) {
                if (!std::isfinite(worldToClipRows[row][col])) return {};
                result.rows[row][col] = worldToClipRows[row][col];
            }
            result.rows[row][1] = -worldToClipRows[row][1];
            result.rows[row][3] = float(double(worldToClipRows[row][3]) +
                2.0 * double(planeY) * double(worldToClipRows[row][1]));
            if (!std::isfinite(result.rows[row][3])) return {};
            wMagnitude += std::abs(double(worldToClipRows[3][row]));
        }
        if (!(wMagnitude > 0)) return {};
        result.clipPlane[1] = 1.0f;
        result.clipPlane[3] = -planeY;
        result.valid = true;
        return result;
    }
}
