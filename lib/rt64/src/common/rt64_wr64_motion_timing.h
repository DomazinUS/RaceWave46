#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace RT64 {
    // Exposure is a duration, not half of whichever refresh interval happened
    // to be selected. 1/90 second keeps the trial visible at high refresh rates.
    inline float wr64MotionShutterScale(float presentationSeconds) {
        if (!std::isfinite(presentationSeconds) || presentationSeconds < 1.0f / 1000.0f ||
            presentationSeconds > 1.0f) return 0.0f;
        return (1.0f / 90.0f) / presentationSeconds;
    }

    // Only the blur velocity is normalized. Native presentation weights,
    // geometry, camera matching and frame scheduling remain untouched.
    // At a native-pair boundary, clamping the previous weight to zero can
    // shorten the measured interval (e.g. 20 -> 144 Hz). Recover the intended
    // exposure interval from the local derivative, not a stored blurred frame.
    inline float wr64MotionTimeScale(float currentWeight, float previousWeight,
        int32_t nativeRate, float presentationSeconds) {
        if (!std::isfinite(currentWeight) || !std::isfinite(previousWeight) ||
            !std::isfinite(presentationSeconds) || nativeRate <= 0 || presentationSeconds <= 0 ||
            currentWeight < 0 || currentWeight > 1 || previousWeight < 0 || previousWeight > 1)
            return 0.0f;
        const double actual = double(currentWeight) - double(previousWeight);
        const double expected = double(nativeRate) * double(presentationSeconds);
        // Equal weights are intentional at a camera cut. Tiny differences below
        // float weight resolution must not turn noise into a large velocity.
        if (actual <= 1e-6 || expected <= 0 || expected > 1.000001) return 0.0f;
        const double scale = (std::max)(1.0, (std::min)(expected, 1.0) / actual);
        // The integer-rate scheduler advances by at least one display tick;
        // its largest valid boundary correction is the native rate itself.
        if (!std::isfinite(scale) || scale > double(nativeRate) * 1.001) return 0.0f;
        return float(scale);
    }
}
