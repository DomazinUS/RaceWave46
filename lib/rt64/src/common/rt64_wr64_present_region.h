#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace RT64 {
    // UVs describe the VI's complete image, independent of texture allocation
    // padding. An explicit output region always preserves its requested aspect.
    struct Wr64PresentRegion {
        bool enabled = false;
        float left = 0.0f, top = 0.0f, right = 1.0f, bottom = 1.0f;
        float aspect = 16.0f / 9.0f;
    };

    struct Wr64PresentRegionViewport {
        float x = 0.0f, y = 0.0f, width = 0.0f, height = 0.0f;
    };

    inline bool wr64PresentRegionValid(const Wr64PresentRegion &region) {
        return region.enabled && std::isfinite(region.left) && std::isfinite(region.top) &&
            std::isfinite(region.right) && std::isfinite(region.bottom) &&
            std::isfinite(region.aspect) && region.aspect > 0.0f &&
            region.left >= 0.0f && region.top >= 0.0f && region.right <= 1.0f &&
            region.bottom <= 1.0f && region.left < region.right && region.top < region.bottom;
    }

    inline Wr64PresentRegion wr64SeparatePresentRegion(uint32_t player) {
        if (player == 1) return { true, 0.0f, 0.0f, 0.5f, 1.0f, 16.0f / 9.0f };
        if (player == 2) return { true, 0.5f, 0.0f, 1.0f, 1.0f, 16.0f / 9.0f };
        return { true, 0.0f, 0.0f, 1.0f, 1.0f, 32.0f / 9.0f };
    }

    inline Wr64PresentRegionViewport wr64PresentRegionViewport(const Wr64PresentRegion &region,
        uint32_t width, uint32_t height)
    {
        if (!wr64PresentRegionValid(region) || width == 0 || height == 0) return {};
        const float fittedHeight = std::min(float(height), float(width) / region.aspect);
        const float fittedWidth = fittedHeight * region.aspect;
        return { (float(width) - fittedWidth) * 0.5f, (float(height) - fittedHeight) * 0.5f,
            fittedWidth, fittedHeight };
    }

    inline bool wr64SeparateDisplayedRace(bool direct3D12, bool scratch, bool taggedTarget) {
        return direct3D12 && !scratch && taggedTarget;
    }
}
