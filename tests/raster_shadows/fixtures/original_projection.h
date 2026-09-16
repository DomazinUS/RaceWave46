// Accepted Original helper before Shadow Draw Distance, 2026-09-14.
// Source SHA-256: afe3ecad9119bba408a73b7f07c6f1c91daea57c2a84047981c34307fad71355
#pragma once

#include <cmath>
#include <cstdint>

namespace OriginalRT64 {
    inline constexpr uint32_t Wr64RasterShadowMapSize = 1024;
    inline constexpr float Wr64RasterShadowWidth = 4096.0f;
    inline constexpr float Wr64RasterShadowDepthSpan = 16384.0f;
    inline constexpr float Wr64RasterShadowTexelSize = Wr64RasterShadowWidth / Wr64RasterShadowMapSize;

    struct Wr64RasterShadowProjection {
        bool valid = false;
        // clip[i] = dot(rows[i], float4(worldPosition, 1)). No transposition.
        // Orthographic clip X/Y are [-1,1], Z is [0,1], and W is always 1.
        // Texture UV is (clip.x * .5 + .5, .5 - clip.y * .5).
        float rows[4][4] = {};
    };

    // Fixed world-space coverage; scene contents never affect these bounds.
    // toLight points from the scene toward the light, so depth increases away
    // from the light. The camera's two light-plane coordinates snap to the
    // shadow texel grid. Only its depth coordinate remains unsnapped.
    inline Wr64RasterShadowProjection wr64BuildRasterShadowProjection(
        const float camera[3], const float toLight[3]) {
        Wr64RasterShadowProjection result;
        if (!camera || !toLight) return result;
        double light[3];
        double lengthSquared = 0.0;
        for (uint32_t i = 0; i < 3; ++i) {
            if (!std::isfinite(camera[i]) || !std::isfinite(toLight[i])) return result;
            light[i] = toLight[i];
            lengthSquared += light[i] * light[i];
        }
        if (!(lengthSquared > 0.0) || !std::isfinite(lengthSquared)) return result;
        const double inverseLength = 1.0 / std::sqrt(lengthSquared);
        for (double &component : light) component *= inverseLength;

        // Normally use world Y as up. A fixed world Z reference avoids a
        // degenerate cross product for a nearly vertical light.
        const bool nearVertical = std::abs(light[1]) > 0.99;
        double right[3] = {nearVertical ? -light[1] : light[2],
            nearVertical ? light[0] : 0.0, nearVertical ? 0.0 : -light[0]};
        const double rightLength = std::sqrt(right[0] * right[0] + right[1] * right[1] + right[2] * right[2]);
        for (double &component : right) component /= rightLength;
        const double up[3] = {light[1] * right[2] - light[2] * right[1],
            light[2] * right[0] - light[0] * right[2], light[0] * right[1] - light[1] * right[0]};
        double centerRight = 0.0, centerUp = 0.0, centerLight = 0.0;
        for (uint32_t i = 0; i < 3; ++i) {
            centerRight += right[i] * camera[i];
            centerUp += up[i] * camera[i];
            centerLight += light[i] * camera[i];
            result.rows[0][i] = float(right[i] * (2.0 / Wr64RasterShadowWidth));
            result.rows[1][i] = float(up[i] * (2.0 / Wr64RasterShadowWidth));
            result.rows[2][i] = float(-light[i] / Wr64RasterShadowDepthSpan);
        }
        // floor(x + .5) gives one consistent global grid, including negative
        // coordinates and exact half-texel ties.
        centerRight = std::floor(centerRight / Wr64RasterShadowTexelSize + 0.5) * Wr64RasterShadowTexelSize;
        centerUp = std::floor(centerUp / Wr64RasterShadowTexelSize + 0.5) * Wr64RasterShadowTexelSize;
        result.rows[0][3] = float(-centerRight * (2.0 / Wr64RasterShadowWidth));
        result.rows[1][3] = float(-centerUp * (2.0 / Wr64RasterShadowWidth));
        result.rows[2][3] = float(0.5 + centerLight / Wr64RasterShadowDepthSpan);
        result.rows[3][3] = 1.0f;
        for (const auto &row : result.rows) for (float component : row) {
            if (!std::isfinite(component)) return Wr64RasterShadowProjection{};
        }
        result.valid = true;
        return result;
    }
}
