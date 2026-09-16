#pragma once

#include <algorithm>
#include <atomic>
#include <cmath>

namespace RT64 {
    // The USA IPS image already owns its 424x240 layout. The last 0.63% of
    // horizontal fit at 16:9 belongs to presentation and remains unchanged.
    inline constexpr float Wr64BaselineAspect = 16.0f / 9.0f;
    inline constexpr float Wr64BaselineWidth = 424.0f;
    inline std::atomic<float> wr64UltrawideWidth{Wr64BaselineWidth};

    inline float wr64UltrawideExpansion(float displayAspect) {
        if (!std::isfinite(displayAspect)) return 1.0f;
        return std::clamp(displayAspect / Wr64BaselineAspect, 1.0f, 2.0f);
    }

    inline float wr64UsaSceneAspect(float displayAspect, bool expand) {
        return expand && std::isfinite(displayAspect)
            ? std::clamp(displayAspect, Wr64BaselineAspect, Wr64BaselineAspect * 2.0f)
            : Wr64BaselineAspect;
    }

    // Both USA's original HUD plane and its 16:9 setting use the IPS baseline.
    // Only the requested additional width moves widgets away from that plane.
    inline float wr64UsaHudExtensionPercentage(float sceneAspect, float hudAspect) {
        const float extension = sceneAspect - Wr64BaselineAspect;
        if (!(extension > 0.0f) || !std::isfinite(hudAspect)) return 0.0f;
        return std::clamp((hudAspect - Wr64BaselineAspect) / extension, 0.0f, 1.0f);
    }

    struct Wr64PresentationExtent {
        float width;
        float height;
    };

    // USA's scene renderer supports the authored 16:9 image through its 32:9
    // extension. Fit that image outside this range; VIRenderer centres it and
    // the frontend continues drawing independently across the whole window.
    inline Wr64PresentationExtent wr64UsaPresentationExtent(float width, float height, bool expand = true) {
        Wr64PresentationExtent result{width, height};
        if (!(width > 0.0f) || !(height > 0.0f) ||
            !std::isfinite(width) || !std::isfinite(height)) return result;
        const float aspect = width / height;
        if (aspect < Wr64BaselineAspect) result.height = width / Wr64BaselineAspect;
        else {
            const float maximumAspect = Wr64BaselineAspect * (expand ? 2.0f : 1.0f);
            if (aspect > maximumAspect) result.width = height * maximumAspect;
        }
        return result;
    }

    inline void wr64UltrawidePublishAspect(float displayAspect) {
        wr64UltrawideWidth.store(Wr64BaselineWidth * wr64UltrawideExpansion(displayAspect),
            std::memory_order_relaxed);
    }

    // Host celestial producers may read this from the native game thread.
    // Draw-call transforms use their own workload's scale, never this global,
    // so an older queued frame cannot pick up a later window resize.
    inline float wr64UltrawideLogicalWidth() {
        return wr64UltrawideWidth.load(std::memory_order_relaxed);
    }

    struct Wr64UltrawideLayout {
        float width = 0.0f;
        float inverseExpansion = 1.0f;
        float halfExtension = 0.0f;

        bool active() const { return inverseExpansion < 1.0f; }

        // Convert the existing stretched screen plane back to its 16:9-size
        // content, then translate the complete identified widget to its edge.
        float position(float stretchedX, int anchor = 0) const {
            return width * 0.5f + (stretchedX - width * 0.5f) * inverseExpansion
                + float(anchor) * halfExtension;
        }

        float extent(float stretchedWidth) const {
            return stretchedWidth * inverseExpansion;
        }
    };

    inline Wr64UltrawideLayout wr64UltrawideLayout(float scaleX, float scaleY, int framebufferWidth) {
        Wr64UltrawideLayout result;
        result.width = float(framebufferWidth) * scaleX;
        if (framebufferWidth == 424 && scaleY > 0.0f && scaleX > scaleY * 1.000001f) {
            result.inverseExpansion = scaleY / scaleX;
            result.halfExtension = float(framebufferWidth) * (scaleX - scaleY) * 0.5f;
        }
        return result;
    }

    inline Wr64UltrawideLayout wr64UltrawideHudLayout(Wr64UltrawideLayout scene, float extensionPercentage) {
        scene.halfExtension *= std::clamp(extensionPercentage, 0.0f, 1.0f);
        return scene;
    }
}
