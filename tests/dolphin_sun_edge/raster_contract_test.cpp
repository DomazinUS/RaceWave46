#define HLSL_CPU
#include "shared/rt64_raster_params.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>

static unsigned checks = 0;
static void require(bool value, const char *reason) {
    ++checks;
    if (!value) { std::fprintf(stderr, "FAIL: %s\n", reason); std::exit(1); }
}
static float saturate(float value) { return std::clamp(value, 0.0f, 1.0f); }
static float asfloat(uint32_t bits) { float value; std::memcpy(&value, &bits, sizeof(value)); return value; }
#include "raster_contract.inc"

int main() {
    static_assert(sizeof(interop::RasterParams) == 32, "Raster push constant ABI changed");
    static_assert(offsetof(interop::RasterParams, screenScale) == 16, "Scale ABI changed");
    static_assert(offsetof(interop::RasterParams, screenOffset) == 24, "Offset ABI changed");
    require(WR64_DOLPHIN_SUN_FADE_TAG != 0 && WR64_DOLPHIN_SUN_FADE_TAG != 1,
        "Dolphin tag collides with default or alternate pipeline tag");

    interop::RasterParams params{};
    params.renderIndex = 47;
    params.padding.x = 0x12345678;
    params.screenScale = {0.25f, 0.5f};
    params.screenOffset = {-0.125f, 0.75f};
    const auto original = params;
    for (float loss : {0.0f, 0.125f, 0.5f, 0.875f, 1.0f, 1.5f}) {
        stampOpacity(params, loss);
        require(params.renderIndex == original.renderIndex && params.padding.x == original.padding.x &&
                params.screenScale.x == original.screenScale.x && params.screenScale.y == original.screenScale.y &&
                params.screenOffset.x == original.screenOffset.x && params.screenOffset.y == original.screenOffset.y,
            "sun stamp changed unrelated raster constants");
        float alpha = 0.8f, compare = 0.6f;
        const bool visible = shadeOpacity(params, alpha, compare);
        if (loss >= 1.0f) require(!visible, "fully faded disk still enters the blender");
        else {
            require(visible, "partially visible disk was discarded");
            require(std::abs(alpha - 0.8f * (1.0f - loss)) < 0.000001f &&
                    std::abs(compare - 0.6f * (1.0f - loss)) < 0.000001f,
                "combined alpha and alpha comparison disagree on opacity");
        }
        // The next ordinary draw reuses this object, including after a fully
        // transparent disk. No tag or float bits may leak into the next draw.
        stampOpacity(params, 0.0f);
        require(params.padding.y == 0 && params.padding.z == 0,
            "sun fade leaked into a following flare/HUD/ordinary draw");
        alpha = 0.8f; compare = 0.6f;
        require(shadeOpacity(params, alpha, compare) && alpha == 0.8f && compare == 0.6f,
            "default shader path changed alpha");
    }
    for (uint32_t tag : {uint32_t(0), uint32_t(1), WR64_DOLPHIN_SUN_FADE_TAG ^ 1u, UINT32_MAX}) {
        params.padding.z = tag;
        params.padding.y = 0x7FC00000; // NaN under an unrelated lane contract.
        float alpha = 0.8f, compare = 0.6f;
        require(shadeOpacity(params, alpha, compare) && alpha == 0.8f && compare == 0.6f,
            "unrelated tag interpreted the reserved lane as sun opacity");
    }
    std::printf("PASS: %u raster opacity contract checks\n", checks);
}
