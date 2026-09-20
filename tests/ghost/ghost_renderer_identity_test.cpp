#include "hle/rt64_transform_group.h"
#include "common/rt64_wr64_dolphin_identity.h"
#include "common/rt64_wr64_dolphin_trace.h"

#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// Container-only stand-ins avoid creating a GPU device. The extracted function,
// texture classifier and TransformGroup remain the production implementations.
namespace RT64 {
struct DrawCall {
    uint32_t tileCount = 1, tileIndex = 0, minWorldMatrix = 0;
    struct Words { uint32_t H, L; };
    Words colorCombiner{Wr64DolphinCombinerH, Wr64DolphinCombinerL};
    Words otherMode{Wr64DolphinOtherModeH, Wr64DolphinOtherModeL};
};
struct GameCall { DrawCall callDesc; };
struct Projection {
    enum class Type { Perspective, Orthographic };
    Type type = Type::Perspective;
    uint32_t gameCallCount = 0;
    std::vector<GameCall> gameCalls;
};
struct FramebufferPair {
    uint32_t projectionCount = 1;
    std::array<Projection, 1> projections;
};
struct DrawData {
    struct Tile { uint64_t tmemHashOrID; };
    std::vector<Tile> callTiles;
    std::vector<uint32_t> worldTransformGroups, worldTransformSegmentedAddresses;
    std::vector<hlslpp::float4x4> worldTransforms;
    std::vector<TransformGroup> transformGroups;
};
struct Workload {
    uint64_t submissionFrame = 0;
    uint32_t fbPairCount = 1;
    std::array<FramebufferPair, 1> fbPairs;
    DrawData drawData;
};
#include "dolphin_stamper_test.inc"
}

namespace {
using namespace RT64;
int checks = 0;
void require(bool ok, const char* message) {
    ++checks;
    if (!ok) throw std::runtime_error(message);
}
constexpr unsigned parts = 6;
constexpr uint32_t ghostId = 0x57F12300;

void append_dolphin(Workload& workload, float x, uint32_t firstId) {
    auto& data = workload.drawData;
    auto& projection = workload.fbPairs[0].projections[0];
    unsigned part = 0;
    for (const auto texture : wr64DolphinTextures()) {
        const auto transform = uint32_t(data.worldTransformGroups.size());
        TransformGroup group;
        if (firstId != G_EX_ID_AUTO) {
            group.matrixId = firstId + part;
            group.decompose = false;
            group.ordering = G_EX_ORDER_LINEAR;
            group.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            group.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            group.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;
        }
        data.worldTransformGroups.push_back(uint32_t(data.transformGroups.size()));
        data.transformGroups.push_back(group);
        data.worldTransformSegmentedAddresses.push_back(0x06000610 + part * 0x40);
        data.worldTransforms.emplace_back(
            hlslpp::float4(1, 0, 0, 0), hlslpp::float4(0, 1, 0, 0),
            hlslpp::float4(0, 0, 1, 0), hlslpp::float4(x, 0, 0, 1));
        DrawCall draw;
        draw.tileIndex = uint32_t(data.callTiles.size());
        draw.minWorldMatrix = transform;
        data.callTiles.push_back({texture});
        projection.gameCalls.push_back({draw});
        ++part;
    }
    projection.gameCallCount = uint32_t(projection.gameCalls.size());
}

void check_native(const Workload& workload, unsigned firstTransform, bool interpolates) {
    for (unsigned part = 0; part < parts; ++part) {
        const auto groupIndex = workload.drawData.worldTransformGroups[firstTransform + part];
        const auto& group = workload.drawData.transformGroups[groupIndex];
        require(group.matrixId == (0x57700610 + part * 0x40),
            "native gray dolphin retains its existing segment-address identity");
        require(group.positionInterpolation == (interpolates ? G_EX_COMPONENT_INTERPOLATE : G_EX_COMPONENT_SKIP),
            "native continuity history is isolated from ghost positions");
        require(group.vertexInterpolation == G_EX_COMPONENT_INTERPOLATE &&
            group.tileInterpolation == G_EX_COMPONENT_INTERPOLATE && !group.decompose,
            "native final-matrix interpolation recipe is preserved");
    }
}

void check_ghost(const Workload& workload, unsigned firstTransform, uint32_t firstId) {
    for (unsigned part = 0; part < parts; ++part) {
        const auto groupIndex = workload.drawData.worldTransformGroups[firstTransform + part];
        require(groupIndex == firstTransform + part,
            "normal dolphin classifier leaves the ghost's original group binding untouched");
        const auto& group = workload.drawData.transformGroups[groupIndex];
        require(group.matrixId == firstId + part && !group.decompose &&
            group.ordering == G_EX_ORDER_LINEAR &&
            group.positionInterpolation == G_EX_COMPONENT_INTERPOLATE &&
            group.rotationInterpolation == G_EX_COMPONENT_INTERPOLATE &&
            group.vertexInterpolation == G_EX_COMPONENT_INTERPOLATE,
            "original gray textures preserve explicit ghost part identities and flags");
    }
}
}

int main() {
    try {
        // This test must never write the developer's optional live trace file.
#ifdef _WIN32
        _putenv_s("WR64_DOLPHIN_TRACE", "");
#else
        unsetenv("WR64_DOLPHIN_TRACE");
#endif
        require(wr64DolphinTextures().size() == parts, "all six original dolphin textures are exercised");

        Workload mixed; mixed.submissionFrame = 100;
        // Same segment addresses deliberately exercise ownership collisions.
        // Ghost first ensures an omitted guard steals the native animals' IDs.
        append_dolphin(mixed, 10000, ghostId);
        append_dolphin(mixed, 0, G_EX_ID_AUTO);
        wr64DolphinStampTransformIdentity(mixed);
        check_ghost(mixed, 0, ghostId);
        check_native(mixed, parts, true);
        require(mixed.drawData.transformGroups.size() == parts * 3,
            "only native dolphins append heuristic identity groups");

        Workload normal; normal.submissionFrame = 101;
        append_dolphin(normal, 10, G_EX_ID_AUTO);
        wr64DolphinStampTransformIdentity(normal);
        check_native(normal, 0, true);

        Workload ghostOnly; ghostOnly.submissionFrame = 102;
        append_dolphin(ghostOnly, -50000, 0x57FFFF00);
        wr64DolphinStampTransformIdentity(ghostOnly);
        check_ghost(ghostOnly, 0, 0x57FFFF00);
        require(ghostOnly.drawData.transformGroups.size() == parts,
            "ghost-only frame cannot allocate native identity groups");

        Workload afterGhost; afterGhost.submissionFrame = 103;
        append_dolphin(afterGhost, 40, G_EX_ID_AUTO);
        wr64DolphinStampTransformIdentity(afterGhost);
        check_native(afterGhost, 0, true);

        Workload nativeTeleport; nativeTeleport.submissionFrame = 104;
        append_dolphin(nativeTeleport, 1000, G_EX_ID_AUTO);
        wr64DolphinStampTransformIdentity(nativeTeleport);
        check_native(nativeTeleport, 0, false);

        Workload recovered; recovered.submissionFrame = 105;
        append_dolphin(recovered, 1002, G_EX_ID_AUTO);
        wr64DolphinStampTransformIdentity(recovered);
        check_native(recovered, 0, true);
        std::cout << checks << " production dolphin-stamper checks passed; workload containers are test doubles.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
