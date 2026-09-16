#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "common/rt64_common.h"
#include "common/rt64_wr64_celestial_identity.h"
#include "common/rt64_wr64_vertical_split.h"

// Only storage is modeled. The complete production claim, partition, pairing,
// continuity, message crop/UV and Dolphin disk code is extracted unchanged.
namespace RT64 {
struct Words { uint32_t H = 0, L = 0; };
struct DrawCall {
    uint32_t tileIndex = 0, tileCount = 0;
    FixedRect rect, scissorRect;
    Words colorCombiner, otherMode;
};
struct Call { DrawCall callDesc; struct { uint32_t rawVertexStart = 0; } meshDesc; };
struct Projection {
    enum class Type { Rectangle, Perspective };
    Type type = Type::Rectangle;
    uint32_t gameCallCount = 0;
    std::vector<Call> gameCalls;
};
struct FramebufferPair { uint32_t projectionCount = 0; std::vector<Projection> projections; };
struct DrawData {
    struct Tile { uint64_t tmemHashOrID; };
    std::vector<Tile> callTiles;
    std::vector<float> triTcFloats;
};
struct Workload {
    struct Wr64CelestialRectPair { uint64_t key; FixedRect prevRect, curRect; };
    struct Wr64CelestialTilePair { uint32_t curTileIndex, prevTileIndex; };
    uint64_t submissionFrame = 0;
    uint32_t fbPairCount = 1;
    std::vector<FramebufferPair> fbPairs = {{1, {Projection{}}}};
    DrawData drawData;
    std::vector<Wr64CelestialRectPair> wr64CelestialPrevRects;
    std::vector<Wr64CelestialTilePair> wr64CelestialTilePairs;
};
}
#include "pairing.inc"

using namespace RT64;
static uint32_t checks = 0;
static void check(bool ok, const char *what) {
    ++checks;
    if (!ok) { std::fprintf(stderr, "FAIL: %s\n", what); std::exit(1); }
}
static bool equal(const FixedRect &a, const FixedRect &b) {
    return a.ulx == b.ulx && a.uly == b.uly && a.lrx == b.lrx && a.lry == b.lry;
}
static FixedRect scissor(int view) {
    return {0, view == 2 ? 480 : 0, 1696, view == 1 ? 480 : 960};
}
static uint64_t add(Workload &w, uint64_t hash, int view, int x, int y, int size = 96) {
    auto &p = w.fbPairs[0].projections[0];
    Call c;
    c.callDesc.tileIndex = uint32_t(w.drawData.callTiles.size()); c.callDesc.tileCount = 1;
    c.callDesc.rect = {x, y, x + size, y + size}; c.callDesc.scissorRect = scissor(view);
    c.meshDesc.rawVertexStart = uint32_t(w.drawData.triTcFloats.size() / 2);
    w.drawData.triTcFloats.insert(w.drawData.triTcFloats.end(), {0,0,1,0,0,1,1,1});
    w.drawData.callTiles.push_back({hash});
    p.gameCalls.push_back(c); p.gameCallCount++;
    return wr64CelestialRectKey(0, 0, p.gameCallCount - 1);
}
static Workload frame(uint64_t n) { Workload w; w.submissionFrame = n; return w; }
static void compareBaseline(const Workload &previous, Workload current) {
    auto old = current;
    wr64CelestialPairRects(current, previous); wr64CelestialPairRectsOld(old, previous);
    check(current.wr64CelestialPrevRects.size() == old.wr64CelestialPrevRects.size(), "original pair count");
    check(current.wr64CelestialTilePairs.size() == old.wr64CelestialTilePairs.size(), "original tile count");
    for (size_t n = 0; n < current.wr64CelestialPrevRects.size(); ++n) {
        const auto &a = current.wr64CelestialPrevRects[n], &b = old.wr64CelestialPrevRects[n];
        check(a.key == b.key && equal(a.prevRect, b.prevRect) && equal(a.curRect, b.curRect), "original pair byte values");
    }
}
int main() {
    const uint64_t restored[] = {Wr64CelestialSunGlow, Wr64CelestialSunDisk, Wr64CelestialSunFlare, Wr64CelestialTcStar};
    for (uint64_t hash : restored) {
        // Native P1 exits while P2 enters. Same total count and a 120-pixel
        // separation pass the old continuity test, despite unrelated cameras.
        for (int from = 1; from <= 2; ++from) {
            auto prev = frame(10), cur = frame(11);
            add(prev, hash, from, 500, from == 1 ? 180 : 660);
            add(cur, hash, 3-from, 510, from == 1 ? 660 : 180);
            auto old = cur;
            wr64CelestialPairRectsOld(old, prev);
            check(old.wr64CelestialPrevRects.size() == 1, "old cross-camera pairing reproduced");
            wr64CelestialPairRects(cur, prev);
            check(cur.wr64CelestialPrevRects.empty(), "opposite view cannot inherit history");
        }
        // One view loses an object; stable P2 keeps its own history instead of
        // losing interpolation because the other player's count changed.
        for (int stable = 1; stable <= 2; ++stable) {
            auto prev = frame(20), cur = frame(21);
            add(prev, hash, 1, 400, 180); add(prev, hash, 2, 800, 660);
            uint64_t key = add(cur, hash, stable, stable == 1 ? 412 : 812, stable == 1 ? 180 : 660);
            auto old = cur; wr64CelestialPairRectsOld(old, prev);
            check(old.wr64CelestialPrevRects.empty(), "old count churn freezes stable view");
            wr64CelestialPairRects(cur, prev);
            check(cur.wr64CelestialPrevRects.size() == 1 && cur.wr64CelestialPrevRects[0].key == key, "stable view continues");
            check(cur.wr64CelestialPrevRects[0].prevRect.ulx == (stable == 1 ? 400 : 800), "correct previous camera");
        }
        // Both views retain their own ordered pieces. This includes the moon's
        // two same-texture passes and multiple native flare/star rectangles.
        auto prev = frame(30), cur = frame(31);
        for (int v = 1; v <= 2; ++v) for (int n = 0; n < 4; ++n) {
            add(prev, hash, v, 100+n*200, v == 1 ? 180 : 660, 8+n*4);
            add(cur, hash, v, 108+n*200, v == 1 ? 184 : 664, 8+n*4);
        }
        compareBaseline(prev, cur);
        // Full-frame originals and a gap in submission history are unchanged.
        prev = frame(40); cur = frame(41);
        add(prev, hash, 0, 400, 180); add(cur, hash, 0, 408, 184);
        compareBaseline(prev, cur); cur.submissionFrame += 1; compareBaseline(prev, cur);
    }
    for (int slot = 0; slot < Wr64CelestialTextureCount; ++slot) {
        for (int view = 0; view <= 2; ++view) {
            const bool sky = slot == 0 || slot == 1 || slot == 2 || slot == 4;
            auto clip = scissor(view);
            check(wr64CelestialRectView(slot, clip) == uint32_t(sky ? view : 0), "exact scope by texture and half");
            check(RT64::wr64VerticalHalfScissor(clip.ulx, clip.uly, clip.lrx, clip.lry) == view, "horizontal identity retained by vertical layout");
            clip.lrx -= 1;
            check(wr64CelestialRectView(slot, clip) == 0, "partial scissor is not an invented view");
        }
    }
    // Existing Dolphin disk and message UV/crop rules retain full behavior.
    for (uint64_t hash : {Wr64CelestialSunDiskDP, Wr64CelestialDpText, Wr64CelestialDpTextSiblings[0]}) {
        auto prev = frame(50), cur = frame(51);
        add(prev, hash, 0, 100, 800); add(cur, hash, 0, 108, 800);
        compareBaseline(prev, cur);
        cur.drawData.triTcFloats[0] = 0.1f; cur.drawData.triTcFloats[6] = 1.1f;
        compareBaseline(prev, cur);
    }
    // Unclaimed UI, perspective calls and spare inactive storage stay ignored.
    auto prev = frame(70), cur = frame(71);
    add(prev, 0x123, 1, 300, 200); add(cur, 0x123, 2, 308, 680);
    compareBaseline(prev, cur);
    add(prev, Wr64CelestialSunDisk, 1, 300, 200); add(cur, Wr64CelestialSunDisk, 1, 308, 200);
    prev.fbPairs[0].projections[0].type = Projection::Type::Perspective;
    cur.fbPairs[0].projections[0].type = Projection::Type::Perspective;
    compareBaseline(prev, cur);
    std::printf("PASS celestial view identity: %u checks\n", checks);
}
