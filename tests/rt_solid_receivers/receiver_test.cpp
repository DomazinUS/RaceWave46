#include "common/rt64_wr64_rt_material.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

constexpr uint32_t ZMODE_DEC = 3;
struct OtherMode { uint32_t L; uint32_t zMode() const { return (L >> 10) & 3; } };
struct GameCall {
    struct { uint32_t faceIndicesStart = 0; } meshDesc;
    struct { uint32_t triangleCount = 2; OtherMode otherMode{0x00552078}; } callDesc;
};
struct DrawData {
    std::vector<uint32_t> faceIndices{0, 1, 2, 0, 2, 3};
    std::vector<uint32_t> worldIndices{0, 0, 0, 0};
    std::vector<uint32_t> worldTransformSegmentedAddresses{0x0300E408};
};
struct Result {
    struct { struct { float x = 1; } shadowOptions; struct { float x = 0; } aoOptions; } params;
    // Match the production scene flags referenced by the extracted receiver
    // selector since raster shadows and planar reflection became independent.
    bool rasterShadows = false, traceReflections = true;
    std::vector<uint32_t> shoreDraws, aoOnlyDraws, fenceCandidates;
};
struct Fixture {
    GameCall call;
    struct { bool vertexTestZ = false; } triangles;
    struct { bool matched = false; } composer;
    bool wrongWayArrow = false, trafficLights = false, nextMark = false;
    bool buoyLetter = false, beam = false, viewportNudge = false, manualViewport = false;
    uint32_t draw = 37;
};
#include "native_receiver_selection.inl"

static unsigned checks = 0;
static void require(bool result, const char *message) {
    ++checks;
    if (!result) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}

int main() {
    // Native material and matrix identities documented in the actor provenance
    // and START archive suites. Eligibility must not depend on a static world
    // matrix now that the same current geometry already enters the shadow AS.
    struct NativeCase { uint32_t mode, matrix; const char *name; };
    const NativeCase cases[] = {
        {0x00552078, 0x0300E408, "rider articulated surface"},
        {0xC8112078, 0x0300E108, "watercraft articulated surface"},
        {0xC8112078, 0x01031000, "separately transformed solid object"},
        {0xC8113078, 0x01031000, "separately transformed texture-edge object"},
        {0xC8112078, 0x02000A40, "native static solid world"},
        {0xC8113078, 0x02000A40, "native static cutout world"},
    };
    for (const auto &native : cases) {
        Fixture fixture;
        fixture.call.callDesc.otherMode.L = native.mode;
        DrawData data;
        data.worldTransformSegmentedAddresses[0] = native.matrix;
        Result result;
        selectNativeReceiver(fixture, data, result);
        require(result.shoreDraws == std::vector<uint32_t>{37}, native.name);
        require(result.aoOnlyDraws.empty(), "directional receiver never inherits AO-only exclusion");
        require(result.fenceCandidates.size() == (native.matrix == 0x02000A40),
            "only the native static matrix reaches fence proxy eligibility");
        result = {}; result.params.shadowOptions.x = 0;
        selectNativeReceiver(fixture, data, result);
        require(result.shoreDraws.empty() && result.aoOnlyDraws.empty(), "shadow toggle off restores ordinary material");
        result.params.aoOptions.x = 1;
        selectNativeReceiver(fixture, data, result);
        require(result.shoreDraws.size() == 1, "parked AO admission unchanged when directional shadows off");
        require(result.aoOnlyDraws.size() == (native.matrix != 0x02000A40), "parked AO-only policy unchanged");
    }

    // Every existing semantic or screen-space exclusion must remain effective
    // with directional shadows and with the old development-only AO flag.
    for (unsigned exclusion = 0; exclusion < 9; ++exclusion) {
        Fixture fixture;
        switch (exclusion) {
            case 0: fixture.wrongWayArrow = true; break;
            case 1: fixture.trafficLights = true; break;
            case 2: fixture.nextMark = true; break;
            case 3: fixture.buoyLetter = true; break;
            case 4: fixture.beam = true; break;
            case 5: fixture.composer.matched = true; break;
            case 6: fixture.viewportNudge = true; break;
            case 7: fixture.manualViewport = true; break;
            case 8: fixture.triangles.vertexTestZ = true; break;
        }
        DrawData data;
        Result result; result.params.aoOptions.x = 1;
        selectNativeReceiver(fixture, data, result);
        require(result.shoreDraws.empty() && result.aoOnlyDraws.empty(), "excluded semantic/screen draw cannot receive shadows");
    }
    for (uint32_t mode : {0x005049D8u, 0x0F0A4000u, 0x00504240u, 0xC8113058u,
                         0xC8113878u, 0xC811207Bu, 0xC8112C78u, 0xC8113C78u}) {
        Fixture fixture; fixture.call.callDesc.otherMode.L = mode;
        DrawData data;
        Result result;
        selectNativeReceiver(fixture, data, result);
        require(result.shoreDraws.empty(), "native water, sky, no-depth, translucent, dither and decals excluded");
    }
    DrawData articulated;
    articulated.worldIndices = {0, 1, 2, 3};
    articulated.worldTransformSegmentedAddresses = {0x0300E108, 0x0300E208, 0x0300E308, 0x0300E408};
    Result result;
    selectNativeReceiver(Fixture{}, articulated, result);
    require(result.shoreDraws.size() == 1 && result.fenceCandidates.empty(),
        "draw spanning articulated component matrices receives without becoming a fence");
    std::cout << "PASS " << checks << " production native receiver admission checks\n";
}
