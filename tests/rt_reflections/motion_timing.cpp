#include "../../lib/rt64/src/common/rt64_wr64_motion_timing.h"

#include <cstdio>
#include <limits>
#include <stdexcept>

static unsigned checks = 0;
static void require(bool result, const char *message) {
    ++checks;
    if (!result) throw std::runtime_error(message);
}

int main() {
    try {
        using RT64::wr64MotionTimeScale;
        using RT64::wr64MotionShutterScale;
        // Fixed exposure is measured in seconds: an object moving 720 output
        // pixels/second covers eight pixels in a 1/90-second shutter at every
        // presentation rate. This oracle is independent of interpolation.
        for (int display : {20,30,60,120,144,165,180,240}) {
            const float interval=1.0f/display;
            const double pixels=(720.0/display)*wr64MotionShutterScale(interval);
            require(std::abs(pixels-8.0)<0.000002,"physical blur length depends on refresh rate");
        }
        for(float invalid : {0.0f,-1.0f,0.0005f,1.01f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()})
            require(wr64MotionShutterScale(invalid)==0,"invalid shutter duration accepted");
        for (int native : {20, 30, 60}) for (int display : {60, 120, 143, 144, 165, 180, 240}) {
            if (display < native) continue;
            int64_t logicalTicks = 0, displayTicks = 0;
            double minimumRaw = 1.0, maximumScale = 1.0, maximumError = 0.0;
            unsigned frames = 0;
            // Replay the production integer clock and weight clamp for enough
            // native pairs to visit every remainder, independent of the helper.
            for (int pair = 0; pair < display * 2; ++pair) {
                logicalTicks += display;
                const int count = int((logicalTicks - displayTicks) / native);
                for (int frame = 0; frame < count; ++frame) {
                    const float previous = std::clamp(float(display + displayTicks - logicalTicks) / float(display), 0.0f, 1.0f);
                    displayTicks += native;
                    const float current = std::clamp(float(display + displayTicks - logicalTicks) / float(display), 0.0f, 1.0f);
                    const float scale = wr64MotionTimeScale(current, previous, native, 1.0f / display);
                    const double raw = (double(current) - previous) / (double(native) / display);
                    minimumRaw = (std::min)(minimumRaw, raw);
                    maximumScale = (std::max)(maximumScale, double(scale));
                    // A constant actor derivative is the independent oracle.
                    // It must have the same exposure length on boundary frames.
                    const double error = std::abs(raw * scale - 1.0);
                    maximumError = (std::max)(maximumError, error);
                    require(scale >= 1 && std::isfinite(scale), "valid scheduler interval rejected");
                    require(error < 0.00002, "constant-speed blur changes with native-pair phase");
                    const double pixels=(720.0/native)*(double(current)-previous)*scale*wr64MotionShutterScale(1.0f/display);
                    require(std::abs(pixels-8.0)<0.0002,"fixed exposure changed across a native-pair boundary");
                    ++frames;
                }
            }
            if (native == 20 && display == 144) require(std::abs(minimumRaw - .2) < 0.00001, "144 Hz boundary control missing");
            if (native == 20 && display == 165) require(std::abs(minimumRaw - .25) < 0.00001, "165 Hz boundary control missing");
            if (display % native == 0) require(maximumScale < 1.00001, "integer-ratio exposure changed");
            std::printf("%d -> %d Hz: %u frames, old minimum %.6f, maximum correction %.6f, normalized error %.9f\n",
                native, display, frames, minimumRaw, maximumScale, maximumError);
        }
        require(wr64MotionTimeScale(1, 0, 20, .05f) == 1, "native-rate exposure changed");
        require(wr64MotionTimeScale(1, 1, 20, 1.f / 144) == 0, "camera cut amplified");
        require(wr64MotionTimeScale(.5f, .5f, 20, .05f) == 0, "zero interval amplified");
        require(wr64MotionTimeScale(.2f, .8f, 20, .05f) == 0, "reversed interval accepted");
        require(wr64MotionTimeScale(.50000006f, .5f, 20, .05f) == 0, "subprecision interval amplified");
        require(wr64MotionTimeScale(1, 0, 0, .05f) == 0, "invalid rate accepted");
        require(wr64MotionTimeScale(1, 0, 20, 0) == 0, "invalid duration accepted");
        require(wr64MotionTimeScale(1, 0, 20, 1) == 0, "impossible interval accepted");
        require(wr64MotionTimeScale(1, -.1f, 20, .05f) == 0, "out-of-range weights accepted");
        require(wr64MotionTimeScale(std::numeric_limits<float>::quiet_NaN(), 0, 20, .05f) == 0, "NaN accepted");
        require(wr64MotionTimeScale(1, 0, 20, std::numeric_limits<float>::infinity()) == 0, "infinity accepted");
        std::printf("PASS: %u motion timing checks; native clock/weights remain unchanged.\n", checks);
        return 0;
    }
    catch (const std::exception &error) { std::printf("FAIL after %u: %s\n", checks, error.what());return 1; }
}
