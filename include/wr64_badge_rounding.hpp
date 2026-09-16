#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace wr64::achievement_badges {
// Input and output are decoded straight RGBA: the UI renderer multiplies RGB
// by source alpha while blending. Modify alpha only, once on a separate image
// copy, not on a cached PNG or an existing variant.
// Invalid dimensions/payload leave the input unchanged.
inline bool round_badge_pixels(std::vector<char>& rgba, uint32_t width, uint32_t height) {
    if (width == 0 || height == 0 || width > 512 || height > 512 ||
        rgba.size() != std::size_t(width) * height * 4) return false;

    const float half_width = float(width) * 0.5f;
    const float half_height = float(height) * 0.5f;
    const float radius = float(std::min(width, height)) * 0.1f;
    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            // Signed distance at the pixel center to the rounded rectangle.
            // The transition from -0.5 to +0.5 covers one texture pixel.
            const float qx = std::abs(float(x) + 0.5f - half_width) - (half_width - radius);
            const float qy = std::abs(float(y) + 0.5f - half_height) - (half_height - radius);
            const float outside_x = std::max(qx, 0.0f);
            const float outside_y = std::max(qy, 0.0f);
            const float distance = std::sqrt(outside_x * outside_x + outside_y * outside_y) +
                std::min(std::max(qx, qy), 0.0f) - radius;
            const float coverage = std::clamp(0.5f - distance, 0.0f, 1.0f);
            const auto offset = (std::size_t(y) * width + x) * 4;
            const auto original_alpha = static_cast<unsigned char>(rgba[offset + 3]);
            const auto alpha = static_cast<unsigned int>(std::lround(float(original_alpha) * coverage));
            rgba[offset + 3] = static_cast<char>(alpha);
        }
    }
    return true;
}
}
