// CPU contract for the native shore blender. GPU fixtures execute RasterPS;
// this test independently compares surface-before-fog attenuation with the
// reconstruction used after RasterPS and decodes the real archived modes.
#define HLSL_CPU
#include "shared/rt64_blender.h"
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>

using interop::Blender;
using interop::OtherMode;
static unsigned checks = 0;
static void require(bool value, const char *message) {
    ++checks;
    if (!value) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}

static bool supportedFog(const OtherMode om) {
    const auto inputs = om.blenderInputs();
    return om.cycleType() == G_CYC_2CYCLE && !om.forceBlend() &&
        Blender::usesStandardFogCycle(inputs, 0) &&
        Blender::decodeInputP(inputs, true) == Blender::PM_CC_OR_BLENDER;
}

static bool supportedOpaque(const OtherMode om) {
    return om.cycleType() == G_CYC_1CYCLE && !om.forceBlend() &&
        Blender::decodeInputP(om.blenderInputs(), false) == Blender::PM_CC_OR_BLENDER;
}

int main() {
    // Exact Sunny beach and support materials from the original archived
    // DrawCalls. Coverage-times-alpha distinguishes cutouts, not fog behavior.
    for (uint32_t low : { 0xC8112078u, 0xC8113078u }) {
        const OtherMode om{ low, 0x00182CFFu };
        require(supportedFog(om), "archived shore mode uses supported native fog");
        require(!Blender::usesAlphaBlend(om), "native shore writes opaque fogged color");
        require(Blender::blendCycleCount(om) == 1 && Blender::combineCycleCount(om) == 2,
            "fog happens once before final unforced color pass");
        for (uint32_t dither = 0; dither < 4; ++dither) {
            // RasterPS's optional alpha-dither modification is inside #if 0;
            // native alpha-dither selector bits do not alter the fog path.
            const OtherMode varied{ low, (om.H & ~0x30u) | (dither << 4) };
            require(supportedFog(varied), "dither selection cannot change fog blender coefficients");
        }
    }
    require(supportedOpaque({ 0x00552078u, 0x00082CFFu }),
        "native one-cycle opaque material permits surface attenuation");
    require(!supportedFog({ 0xC8116078u, 0x00182CFFu }),
        "forced second blend is outside the proven reconstruction");
    require(!supportedFog({ 0xD8112078u, 0x00182CFFu }),
        "final framebuffer passthrough must not be shadowed");
    require(!supportedFog({ 0x88112078u, 0x00182CFFu }),
        "non-fog first-cycle color cannot use the fog reconstruction");
    require(!supportedOpaque({ 0x005049D8u, 0x00082CFFu }),
        "native water or translucent beam remains outside shore opaque path");

    constexpr std::array<std::array<double, 3>, 5> colors{{
        { 0, 0, 0 }, { 1, 1, 1 }, { .13, .42, .76 },
        { .94, .33, .07 }, { .5, .5, .5 }
    }};
    unsigned positiveControls = 0;
    for (const auto &surface : colors) for (const auto &fog : colors)
    for (double f : { 0., 1. / 255., .25, .5, 254. / 255., 1. })
    for (double q : { 0., .45, .7, 1. }) for (unsigned channel = 0; channel < 3; ++channel) {
        // Reference: attenuate the surface, then blend the unchanged fog.
        const double expected = (1 - f) * (q * surface[channel]) + f * fog[channel];
        // Native standard blender normalizes A + (1-A) to one; its overflow
        // threshold is 1 + 8/255, unreachable for these normalized inputs.
        const double native = f * fog[channel] + (1 - f) * surface[channel];
        const double corrected = q * native + (1 - q) * f * fog[channel];
        require(std::abs(corrected - expected) < 1e-12,
            "post-blender reconstruction equals independently composed surface plus fog");
        if (f == 1) require(std::abs(corrected - fog[channel]) < 1e-12,
            "fully fogged pixel keeps the complete native fog color");
        if (f == 0) require(corrected == q * surface[channel],
            "no fog reduces to native surface attenuation");
        if (q == 1) require(corrected == native,
            "unoccluded output is exactly the original native color");
        if (std::abs(q * native - expected) > 1e-3) ++positiveControls;
    }
    require(positiveControls > 100,
        "fixture detects the former bug that incorrectly darkened atmospheric fog");
    std::cout << "PASS " << checks << " native shore fog checks\n";
}
