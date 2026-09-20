#pragma once
#include "common/rt64_common.h"
#include <cstdint>
#include <vector>

struct FinishHudFixtureDraw {
    RT64::FixedRect rect;
    uint64_t hash;
    int32_t projection = 3;
};
struct FinishHudFixtureResult {
    RT64::FixedRect rect;
    int anchor;
};

// Compiles the actual renderer's row census, membership, translation and
// ultrawide anchor selection over minimal draw metadata. No GPU is created.
std::vector<FinishHudFixtureResult> finishHudActualRenderer(
    const std::vector<FinishHudFixtureDraw> &draws, int framebufferWidth,
    float halfExtension, bool twoPlayer);
