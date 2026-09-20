#include <hlsl++.h>
#include "shared/rt64_hlsl.h"
#include <algorithm>
#include <atomic>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace RT64 {
// Container-only stand-ins. Math and all spray helper bodies are production.
struct DrawCall { uint32_t triangleCount = 0, tileCount = 1, tileIndex = 0; };
struct GameCall { DrawCall callDesc; struct Mesh { uint32_t faceIndicesStart = 0; } meshDesc; };
struct Projection { uint32_t gameCallCount = 0; std::vector<GameCall> gameCalls; };
struct FramebufferPair { uint32_t projectionCount = 1; std::vector<Projection> projections{1}; };
struct DrawData {
    struct Tile { uint64_t tmemHashOrID; };
    std::vector<Tile> callTiles;
    std::vector<uint32_t> faceIndices, worldIndices, vertexSegmentedAddresses;
    std::vector<uint32_t> worldTransformSegmentedAddresses, worldTransformPhysicalAddresses;
    std::vector<float> posFloats, velFloats;
    std::vector<interop::float4x4> worldTransforms;
};
struct Workload { uint64_t workloadId = 0; uint32_t fbPairCount = 1; std::vector<FramebufferPair> fbPairs{1}; DrawData drawData; };
struct GameFrameMap {
    struct TransformMap { uint32_t prevTransformIndex = 0; bool mapped = false; };
    struct WorkloadMap { std::vector<TransformMap> transforms; };
};
#include "spray_test.inc"
}

namespace {
using namespace RT64;
constexpr uint64_t Wake = 10644436609240083271ULL;
constexpr uint64_t OtherWakePhase = 17220844374676425630ULL;
constexpr uint64_t Unknown = 0x0123456789ABCDEFULL;
unsigned checks = 0;
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
hlslpp::float4x4 matrix(float x = 0, float angle = 0) {
    const float c = std::cos(angle), s = std::sin(angle);
    return hlslpp::float4x4(hlslpp::float4(c, 0, -s, 0), hlslpp::float4(0, 1, 0, 0),
        hlslpp::float4(s, 0, c, 0), hlslpp::float4(x, 0, 0, 1));
}
uint32_t addMatrix(Workload& work, hlslpp::float4x4 value = matrix()) {
    auto& data = work.drawData;
    const uint32_t index = uint32_t(data.worldTransforms.size());
    data.worldTransforms.push_back(value);
    // All native spout actors share automatic; this must never be their owner.
    data.worldTransformSegmentedAddresses.push_back(0x02000A40);
    data.worldTransformPhysicalAddresses.push_back(0x80170A40);
    return index;
}
GameFrameMap::WorkloadMap mapping(std::initializer_list<uint32_t> previousIndices) {
    GameFrameMap::WorkloadMap result;
    for (uint32_t index : previousIndices) result.transforms.push_back({index, true});
    return result;
}
void appendWake(Workload& work, uint32_t owner, float x, uint32_t world = 0,
    bool merge = false, uint64_t texture = Wake, uint32_t projection = 0)
{
    auto& data = work.drawData;
    if (data.worldTransforms.empty()) addMatrix(work);
    auto& fb = work.fbPairs[0];
    if (fb.projections.size() <= projection) fb.projections.resize(projection + 1);
    fb.projectionCount = uint32_t(fb.projections.size());
    auto& proj = fb.projections[projection];
    const uint32_t firstVertex = uint32_t(data.posFloats.size() / 3);
    const uint32_t firstFace = uint32_t(data.faceIndices.size());
    for (uint32_t i = 0; i < 16; ++i) {
        data.posFloats.insert(data.posFloats.end(), {x + (i % 2 ? 6.0f : -6.0f), 0, -float(i / 2) * 10});
        data.velFloats.insert(data.velFloats.end(), {i % 2 ? 400.0f : -400.0f, 0, 0});
        data.worldIndices.push_back(world);
        data.vertexSegmentedAddresses.push_back(owner < 4 ? 0x050091C0 + owner * 0x100 + i * 16 : 0);
    }
    for (uint32_t i = 0; i < 7; ++i) {
        const uint32_t a = firstVertex + i * 2;
        data.faceIndices.insert(data.faceIndices.end(), {a, a + 1, a + 2, a + 2, a + 1, a + 3});
    }
    if (merge) {
        proj.gameCalls.back().callDesc.triangleCount += 14;
    }
    else {
        GameCall call;
        call.callDesc.triangleCount = 14;
        call.callDesc.tileIndex = uint32_t(data.callTiles.size());
        call.meshDesc.faceIndicesStart = firstFace;
        data.callTiles.push_back({texture});
        proj.gameCalls.push_back(call);
    }
    proj.gameCallCount = uint32_t(proj.gameCalls.size());
}
bool wakeVelocity(const Workload& work, size_t firstVertex, float x, float z = 0) {
    for (size_t i = firstVertex; i < firstVertex + 16; ++i) {
        if (std::fabs(work.drawData.velFloats[i * 3] - x) > 0.001f ||
            std::fabs(work.drawData.velFloats[i * 3 + 1]) > 0.001f ||
            std::fabs(work.drawData.velFloats[i * 3 + 2] - z) > 0.001f) return false;
    }
    return true;
}
void mergedOwners() {
    Workload previous, current;
    appendWake(previous, 0, 0); appendWake(previous, 1, 50, 0, true);
    appendWake(current, 0, 45); appendWake(current, 1, 5, 0, true);
    std::vector<Wr64SprayPrimitive> primitives;
    collectWr64SprayPrimitives(current, current.fbPairs[0].projections[0], primitives);
    require(primitives.size() == 2, "one merged draw must produce two whole native wakes");
    require(primitives[0].triangleCount == 14 && primitives[1].triangleCount == 14,
        "native wake triangle strips remain whole, never individual triangles");
    require(interpolateWr64Spray(current, previous, mapping({0})), "merged wakes receive velocity");
    require(wakeVelocity(current, 0, 45) && wakeVelocity(current, 16, -45),
        "neighbor craft retain independent owner motion when proximity crosses");
}
}

int main() {
    try {
#ifdef _WIN32
        _putenv_s("WR64_SPRAY_MATCH_TRACE", "");
        _putenv_s("WR64_LATERAL_DROPLET_NATIVE_HOLD", "");
#else
        unsetenv("WR64_SPRAY_MATCH_TRACE");
        unsetenv("WR64_LATERAL_DROPLET_NATIVE_HOLD");
#endif
        mergedOwners();
        for (float movement : {0.0f, 10.0f, -35.0f}) {
            Workload previous, current;
            appendWake(previous, 2, 100); appendWake(current, 2, 100 + movement, 0, false, OtherWakePhase);
            require(interpolateWr64Spray(current, previous, mapping({0})), "steady native wake is accepted across texture animation");
            require(wakeVelocity(current, 0, movement), "stationary and continuous wakes preserve coherent movement");
        }
        for (bool farPrevious : {false, true}) {
            Workload previous, current;
            if (farPrevious) appendWake(previous, 0, 1000);
            appendWake(current, 0, 0);
            // With no previous frame's matrix, no mapped old basis is claimed.
            const auto map = farPrevious ? mapping({0}) : GameFrameMap::WorkloadMap{};
            require(interpolateWr64Spray(current, previous, map), "native birth/recycled owner clears generic velocity");
            require(wakeVelocity(current, 0, 0), "birth/recycled far slot stays at incoming native geometry");
        }
        {
            Workload previous, current;
            appendWake(previous, 0, 0); appendWake(previous, 1, 50);
            // Reordered draw calls and changed visibility cannot transfer owner.
            appendWake(current, 1, 5); appendWake(current, 0, 45);
            require(interpolateWr64Spray(current, previous, mapping({0})), "reordered separate calls match");
            require(wakeVelocity(current, 0, -45) && wakeVelocity(current, 16, 45), "draw order is not craft identity");
        }
        {
            Workload previous, current;
            addMatrix(previous, matrix(50, 0.4f)); addMatrix(previous, matrix());
            addMatrix(current, matrix()); addMatrix(current, matrix(55, 0.45f));
            appendWake(previous, 0, 0, 0); appendWake(current, 0, 5, 1);
            require(interpolateWr64Spray(current, previous, mapping({1, 0})), "matrix renumbering and continuous rotation remain supported");
            require(wakeVelocity(current, 0, 5), "correct mapped nonidentity basis preserves local wake velocity");
        }
        {
            Workload previous, current;
            addMatrix(previous, matrix(50, 0.4f)); addMatrix(previous, matrix(50, 0.4f));
            addMatrix(current, matrix(55, 0.45f));
            appendWake(previous, 0, 0, 1); appendWake(current, 0, 5);
            require(interpolateWr64Spray(current, previous, mapping({0})), "duplicate equivalent matrix values are compatible");
            require(wakeVelocity(current, 0, 5), "matrix values, not indices or physical pointers, define the basis");
        }
        {
            Workload previous, current;
            addMatrix(previous, matrix()); addMatrix(previous, matrix(1000, 0.5f));
            appendWake(previous, 0, 0); appendWake(current, 0, 5);
            auto before = current.drawData.velFloats;
            auto map = mapping({1});
            require(!interpolateWr64Spray(current, previous, map), "unsupported shared-matrix mapping is not claimed fixed by vertex clearing");
            require(current.drawData.velFloats == before && map.transforms[0].prevTransformIndex == 1,
                "unsupported basis is reported without rewriting shared transforms or their vertex result");
        }
        {
            Workload previous, current;
            appendWake(previous, 4, 0); appendWake(current, 4, 10);
            require(interpolateWr64Spray(current, previous, mapping({0})), "unknown provenance retains legacy matching");
            require(wakeVelocity(current, 0, 10), "legacy accepted unknown wake is preserved");
            Workload birth; appendWake(birth, 4, 0); Workload empty;
            auto before = birth.drawData.velFloats;
            require(!interpolateWr64Spray(birth, empty, {}) && birth.drawData.velFloats == before,
                "unknown provenance birth behavior is unchanged");
        }
        {
            Workload previous, current;
            appendWake(previous, 4, 0); appendWake(current, 0, 10);
            require(interpolateWr64Spray(current, previous, mapping({0})) && wakeVelocity(current, 0, 0),
                "known owner must not borrow unknown predecessor even when nearby");
        }
        for (uint64_t texture : {Unknown, Wr64LateralDropletTextureHash, 8371292674920036242ULL}) {
            Workload previous, current;
            appendWake(previous, 0, 0, 0, false, texture); appendWake(current, 0, 10, 0, false, texture);
            std::vector<Wr64SprayPrimitive> primitives;
            collectWr64SprayPrimitives(current, current.fbPairs[0].projections[0], primitives);
            const size_t expected = texture == Unknown ? 0 : (texture == Wr64LateralDropletTextureHash ? 7 : 14);
            require(primitives.size() == expected, "unrelated/lateral/circular classification unchanged even with native bank addresses");
        }
        {
            Workload previous, current;
            appendWake(previous, 0, 0, 0, false, Wake, 0); appendWake(previous, 0, 1000, 0, false, Wake, 1);
            appendWake(current, 0, 10, 0, false, Wake, 0); appendWake(current, 0, 1010, 0, false, Wake, 1);
            require(interpolateWr64Spray(current, previous, mapping({0})), "two camera projections are paired by producer order");
            require(wakeVelocity(current, 0, 10) && wakeVelocity(current, 16, 10), "same craft bank in another camera cannot cross-pair");
        }
        {
            Workload previous, current;
            appendWake(previous, 0, 0); appendWake(current, 0, 10);
            // A malformed triangle straddling banks is unknown, not invented ownership.
            current.drawData.vertexSegmentedAddresses[0] = 0x050092C0;
            std::vector<Wr64SprayPrimitive> primitives;
            collectWr64SprayPrimitives(current, current.fbPairs[0].projections[0], primitives);
            require(primitives.size() == 1, "ambiguous topology keeps whole legacy call");
            require(interpolateWr64Spray(current, previous, mapping({0})) == false,
                "ambiguous unknown call cannot claim a known native owner's predecessor");
        }
        std::cout << checks << " native wake ownership checks passed using production helper bodies.\n";
        std::cout << "No aspect-ratio branch, GPU, game, ROM, window or personal profile is involved.\n";
        return 0;
    }
    catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
