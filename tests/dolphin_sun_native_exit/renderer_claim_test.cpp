#include "hle/rt64_rdp.h"
#include "hle/rt64_workload.h"

#include <cstdio>
#include <cstdlib>
#include <stdexcept>

namespace {
unsigned checks = 0;
void require(bool condition, const char *message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
}

int main() {
#ifdef _WIN32
    _putenv_s("WR64_DOLPHIN_SUN_NATIVE_EXIT", "1");
#else
    setenv("WR64_DOLPHIN_SUN_NATIVE_EXIT", "1", 1);
#endif
    try {
        // Use the same concrete types and default alignment that RDP::drawRect
        // and State::fullSync hand to the final renderer. In particular, the
        // ordinary origin value must come from the engine, never a mock value.
        const RT64::ExtendedAlignment alignment;
        RT64::DrawCall call{};
        call.rectLeftOrigin = alignment.leftOrigin;
        call.rectRightOrigin = alignment.rightOrigin;
        require(call.rectLeftOrigin == G_EX_ORIGIN_NONE && call.rectRightOrigin == G_EX_ORIGIN_NONE,
            "RDP default rectangle origin disagrees with the extended GBI");
        call.triangleCount = 2;
        call.rectDsdx = call.rectDtdy = 0x555;
        call.tileIndex = 0;
        call.tileCount = 1;
        auto &sprite = call.wr64DolphinSunSprite;
        sprite.generation = 1;
        sprite.context = 0x28010100;
        sprite.recordId = 0x801C4170;
        sprite.admitted = true;
        sprite.centerX = 224.124649f;
        sprite.centerY = -4.27084351f;
        sprite.radiusX = sprite.radiusY = 12.0f;
        sprite.dsdx = sprite.dtdy = 0x555;

        RT64::DrawData data;
        data.triPosFloats.assign(24, 0.0f);
        data.triColorFloats.assign(24, 1.0f);
        // Actual submission274 carried zero vertical UV span. It must remain
        // available to native rendering while presentation selects full UVs.
        data.triTcFloats = {-212,4, -180.03125f,4, -212,4,
            -180.03125f,4, -180.03125f,4, -212,4};
        const auto nativeUV = data.triTcFloats;
        RT64::DrawCallTile tile{};
        tile.valid = true;
        tile.sampleWidth = tile.sampleHeight = 32;
        tile.tmemHashOrID = RT64::Wr64DolphinSunSpriteTexture;
        data.callTiles.push_back(tile);
        call.rect = RT64::FixedRect(848, 24, 944, 24);
        require(call.rect.isEmpty(), "recorded negative-center carrier must remain empty natively");
        call.wr64DolphinSunVertexStart = RT64::wr64DolphinSunAppendVertices(data, 0, sprite);
        require(call.wr64DolphinSunVertexStart == 6, "canonical vertices were not appended after the native quad");
        require(RT64::wr64DolphinSunClaimValid(call, data, true),
            "final renderer rejected authenticated DP carrier with actual RDP default origins");
        require(std::equal(nativeUV.begin(), nativeUV.end(), data.triTcFloats.begin()),
            "presentation append changed original native UVs");
        require(data.triTcFloats[12] == 0 && data.triTcFloats[13] == 0 &&
            data.triTcFloats[18] == 31.96875f && data.triTcFloats[19] == 31.96875f,
            "presentation retained the carrier's clipped UV span");

        for (float centerY : {40.125f, 5.0f, -0.75f, -4.27084351f, -13.0f, -128.0f}) {
            sprite.centerY = centerY;
            require(RT64::wr64DolphinSunClaimValid(call, data, true),
                "real draw-call claim changed across a valid signed top exit");
            const auto rect = RT64::wr64DolphinSunFullRect(sprite);
            require(rect[1] == centerY - 12 && rect[3] == centerY + 12,
                "full signed quad lost the producer's actual endpoint");
        }
        auto wrong = call;
        wrong.rectLeftOrigin = wrong.rectRightOrigin = 0x4000;
        require(!RT64::wr64DolphinSunClaimValid(wrong, data, true),
            "the former invented ordinary-origin value was accepted");
        wrong = call;
        wrong.rectLeftOrigin = G_EX_ORIGIN_LEFT;
        require(!RT64::wr64DolphinSunClaimValid(wrong, data, true), "explicit left alignment was claimed");
        require(!RT64::wr64DolphinSunClaimValid(call, data, false), "nonrectangle was claimed");
        data.callTiles[0].tmemHashOrID = 0xB82E909F647A31ADULL;
        require(!RT64::wr64DolphinSunClaimValid(call, data, true), "flare sibling was claimed as the DP disk");
        std::printf("PASS: %u actual DrawCall/DrawData/RDP alignment integration checks\n", checks);
        return 0;
    }
    catch (const std::exception &error) {
        std::fprintf(stderr, "FAIL after %u checks: %s\n", checks, error.what());
        return 1;
    }
}
