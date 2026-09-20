#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include "common/rt64_math.h"
#include "common/rt64_wr64_lerpgate_trace.h"
#include "hle/rt64_rigid_body.h"
#include "hle/rt64_transform_group.h"

namespace RT64 {
struct DrawData {
    std::vector<hlslpp::float4x4> worldTransforms, lerpWorldTransforms, invTWorldTransforms, prevWorldTransforms;
    std::vector<uint32_t> worldTransformGroups;
    std::vector<TransformGroup> transformGroups;
};
struct Workload {
    DrawData drawData;
    std::multimap<uint32_t, uint32_t> transformIdMap;
    std::vector<uint32_t> transformIgnoredIds;
    uint64_t submissionFrame = 737;
};
struct GameFrameMap {
    struct TransformMap { RigidBody rigidBody; uint32_t prevTransformIndex = 0; bool mapped = false; };
    struct WorkloadMap { std::vector<TransformMap> transforms; std::vector<bool> prevTransformsMapped; };
};
struct ModifiedBuffers {};
struct GameFrame {
    void buildTransformIdMap(const Workload &, std::multimap<uint32_t, uint32_t> &, std::vector<uint32_t> &) const;
    void matchTransform(Workload &, const Workload &, GameFrameMap::WorkloadMap &, const GameFrameMap::WorkloadMap *,
        uint32_t, uint32_t, ModifiedBuffers &, bool, bool, const hlslpp::float4x4 *, const hlslpp::float4x4 *);
    void matchIds(Workload &, const Workload &, GameFrameMap::WorkloadMap &, const GameFrameMap::WorkloadMap *);
};
constexpr uint32_t RSP_EXTENDED_STACK_SIZE = 4;
struct RSP {
    std::array<int, RSP_EXTENDED_STACK_SIZE> viewportStack{};
    std::array<uint32_t, RSP_EXTENDED_STACK_SIZE> wr64ViewportAddressStack{};
    struct { std::array<uint16_t, RSP_EXTENDED_STACK_SIZE> viewportOriginStack{}; } extended;
    uint32_t viewportStackSize = 1;
    bool viewportChanged = false;
    void pushViewport();
    void popViewport();
};
}
#include "identity_functions.inc"

using namespace RT64;
static unsigned checks = 0, scenarios = 0;
static void check(bool pass, const char *message) {
    ++checks;
    if (!pass) { std::fprintf(stderr, "FAIL check %u: %s\n", checks, message); std::exit(1); }
}
static void near(float actual, float expected, const char *message) { check(std::abs(actual - expected) < 0.0002f, message); }
static hlslpp::float4x4 translated(float x) {
    return hlslpp::float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, 0, 0, 1);
}
static float tx(const hlslpp::float4x4 &matrix) { return float(matrix[3].x); }
static uint32_t add(Workload &w, uint32_t racer, uint32_t limb, uint32_t viewport, float x, bool legacy = false) {
    const auto decoded = decodeWr64ArticulatedMatrixAddress(0x0300E108U + (limb << 8) + (racer << 6));
    const uint32_t id = legacy ? (0x57000000U | (racer << 8) | limb) : wr64ArticulatedMatrixId(decoded, viewport);
    uint32_t index = uint32_t(w.drawData.worldTransforms.size());
    w.drawData.worldTransforms.push_back(translated(x));
    w.drawData.worldTransformGroups.push_back(uint32_t(w.drawData.transformGroups.size()));
    w.drawData.transformGroups.push_back(makeWr64FinalMatrixGroup(id, true));
    return index;
}
static GameFrameMap::WorkloadMap pair(Workload &prev, Workload &cur) {
    GameFrame frame;
    frame.buildTransformIdMap(prev, prev.transformIdMap, prev.transformIgnoredIds);
    frame.buildTransformIdMap(cur, cur.transformIdMap, cur.transformIgnoredIds);
    GameFrameMap::WorkloadMap map;
    map.transforms.resize(cur.drawData.worldTransforms.size());
    map.prevTransformsMapped.resize(prev.drawData.worldTransforms.size());
    frame.matchIds(cur, prev, map, nullptr);
    return map;
}

int main() {
    constexpr uint32_t p1 = 0x800DA8D0U, p2 = 0x800DA8E0U;
    std::set<uint32_t> allIds;
    for (uint32_t racer = 0; racer < 4; ++racer) {
        for (uint32_t limb = 0; limb < 19; ++limb) {
            ++scenarios;
            auto d = decodeWr64ArticulatedMatrixAddress(0x0300E108U + (limb << 8) + (racer << 6));
            check(d.valid && d.racerIndex == racer && d.limbIndex == limb, "native actor/limb decode");
            const uint32_t nativeId = 0x57000000U | (racer << 8) | limb;
            for (uint32_t address : {0U, 0x800DA8C0U, p1, 0x800DA8F0U, 0x800DA900U, 0x000DA8E0U})
                check(wr64ArticulatedMatrixId(d, address) == nativeId, "only exact native P2 viewport changes identity");
            check(wr64ArticulatedMatrixId(d, p2) == (nativeId | 0x10000U), "P2 identity partition");
            check(allIds.insert(wr64ArticulatedMatrixId(d, p1)).second, "unique P1 identity");
            check(allIds.insert(wr64ArticulatedMatrixId(d, p2)).second, "unique P2 identity");
            auto group = makeWr64FinalMatrixGroup(wr64ArticulatedMatrixId(d, p2), true);
            check(!group.decompose && group.ordering == G_EX_ORDER_LINEAR, "retains native linear matrix recipe");
            check(group.positionInterpolation == G_EX_COMPONENT_INTERPOLATE && group.rotationInterpolation == G_EX_COMPONENT_INTERPOLATE &&
                group.vertexInterpolation == G_EX_COMPONENT_INTERPOLATE && group.texcoordInterpolation == G_EX_COMPONENT_SKIP,
                "retains matrix and generated vertex interpolation");

            // The captured failure: a new earlier P1 draw must not consume P2's history.
            Workload prev, cur;
            add(prev, racer, limb, p2, 0);
            add(cur, racer, limb, p1, 56.24f);
            add(cur, racer, limb, p2, 56.24f);
            auto map = pair(prev, cur);
            check(!map.transforms[0].mapped, "new P1 copy has no invented history");
            check(map.transforms[1].mapped && map.transforms[1].prevTransformIndex == 0, "continuing P2 copy retains history on 1-to-2 draw count");
            for (float weight : {0.0f, 0.1f, 0.25f, 0.5f, 0.75f, 0.9f, 1.0f}) {
                interpolate(cur.drawData, prev.drawData, map, weight);
                near(tx(cur.drawData.lerpWorldTransforms[1]), 56.24f * weight, "actual TransformProcessor P2 output interpolates");
                near(tx(cur.drawData.lerpWorldTransforms[0]), 56.24f, "new visibility begins at current matrix");
            }

            Workload oldPrev, oldCur;
            add(oldPrev, racer, limb, p2, 0, true);
            add(oldCur, racer, limb, p1, 56.24f, true);
            add(oldCur, racer, limb, p2, 56.24f, true);
            auto oldMap = pair(oldPrev, oldCur);
            check(oldMap.transforms[0].mapped && !oldMap.transforms[1].mapped, "negative control reproduces shared-ID history theft");
            interpolate(oldCur.drawData, oldPrev.drawData, oldMap, 0.5f);
            near(tx(oldCur.drawData.lerpWorldTransforms[0]), 28.12f, "legacy early P1 copy consumes history");
            near(tx(oldCur.drawData.lerpWorldTransforms[1]), 56.24f, "legacy P2 output stays raw despite output-array existence");

            // All disappearance/continuation combinations, including P1-only and P2-only.
            for (uint32_t prevMask = 1; prevMask <= 3; ++prevMask) {
                for (uint32_t curMask = 1; curMask <= 3; ++curMask) {
                    ++scenarios;
                    Workload a, b;
                    for (uint32_t view = 0; view < 2; ++view) {
                        if (prevMask & (1U << view)) add(a, racer, limb, view ? p2 : p1, float(view * 100));
                        if (curMask & (1U << view)) add(b, racer, limb, view ? p2 : p1, float(view * 100 + 10));
                    }
                    auto m = pair(a, b);
                    interpolate(b.drawData, a.drawData, m, 0.5f);
                    uint32_t index = 0;
                    for (uint32_t view = 0; view < 2; ++view) if (curMask & (1U << view)) {
                        bool continued = (prevMask & (1U << view)) != 0;
                        check(m.transforms[index].mapped == continued, "only same-view history matches across count churn");
                        near(tx(b.drawData.lerpWorldTransforms[index]), float(view * 100 + (continued ? 5 : 10)), "same-view output on 1/2 copy transitions");
                        ++index;
                    }
                }
            }
        }
    }
    for (uint32_t invalid : {0x0200E108U, 0x0400E108U, 0x0300E107U, 0x0300F3C9U, 0x0300E109U, 0x0300E128U})
        check(!decodeWr64ArticulatedMatrixAddress(invalid).valid, "invalid matrix addresses remain untagged");

    RSP stack;
    stack.wr64ViewportAddressStack[0] = p1;
    stack.pushViewport();
    check(stack.wr64ViewportAddressStack[1] == p1, "actual push preserves viewport identity");
    stack.wr64ViewportAddressStack[1] = p2;
    stack.pushViewport();
    check(stack.wr64ViewportAddressStack[2] == p2, "nested P2 push preserves identity");
    stack.popViewport();
    check(stack.wr64ViewportAddressStack[stack.viewportStackSize - 1] == p2, "nested pop restores P2");
    stack.popViewport();
    check(stack.wr64ViewportAddressStack[stack.viewportStackSize - 1] == p1, "pop restores P1 without P2 leak");
    stack.popViewport();
    check(stack.viewportStackSize == 1, "viewport stack underflow protected");
    for (int i = 0; i < 8; ++i) stack.pushViewport();
    check(stack.viewportStackSize == RSP_EXTENDED_STACK_SIZE, "viewport stack overflow protected");
    std::printf("PASS: %u scenarios, %u checks; all 4 racers x 19 matrix slots, actual matching and interpolation, old-ID failure control.\n", scenarios, checks);
}
