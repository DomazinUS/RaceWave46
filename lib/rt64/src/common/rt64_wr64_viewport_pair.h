//
// WR64 viewport pairing, R1.
//
// What it fixes
// -------------
// In two-player split screen, the player's own craft rockets in from the edge of
// the screen and back out again, several times a second, in the SECOND viewport
// only. Measured on Wave_Race_2Player.mp4: over frames 69-118 the bottom half
// changes 2.0x-3.4x more per frame than the top half, while the top half is
// perfectly steady. Intermediate frames catch the craft mid-flight, so it is
// being interpolated across the jump rather than popped.
//
// The mechanism is in GameFrame::match's scene assignment, not in any per-object
// rule. isSceneCompatible() puts each player's viewport in its own GameScene,
// because their view matrices differ. matchScenes() then pairs this frame's
// scenes with the previous frame's by one score:
//
//     matrixDifference(curView, prevView) + matrixDifference(curProj, prevProj)
//
// That score measures only how alike two cameras are - and two cameras following
// two players down the same stretch of water are very alike indeed. The cross
// terms (this frame's top half against last frame's bottom half) routinely come
// out smaller than the identity terms, because frame-to-frame camera motion is
// larger than the gap between the two players. When they do, the greedy
// assignment takes the cross pairing, and then the only seat left for the other
// scene is the other cross pairing - so BOTH viewports match against the wrong
// half. Every world transform in a viewport is then interpolated against the
// other viewport's previous frame.
//
// Most of the frame survives that silently: water, terrain and distant scenery
// sit at similar places in both views, so the wrong pairing lands somewhere
// close and nothing shows. The player's own craft does not. It is a few units
// from the camera in its own view and far away in the other, so the wrong
// pairing sweeps it across the whole screen. That is the artifact, exactly.
//
// Why the scissor rect
// --------------------
// No threshold on camera similarity can separate two split-screen cameras; they
// really are that close, and in a straight line they are momentarily identical.
// The viewport's identity is not its camera, it is the part of the screen it
// draws to - and the game keeps that stable frame to frame. Projection carries
// it already, as the merge of its draw calls' scissor rects, so the top half can
// only ever continue from the top half.
//
// This is a preference, not an exclusion. Scenes that cannot be placed by
// viewport fall back to the original nearest-camera rule in a second pass, so
// the assignment can never come out emptier than it did before this change. In
// single player there is one perspective scene and the only candidate pairs a
// rect with itself, so nothing here can alter it.
//
//   WR64_VIEWPORT_PAIR_FIX     0 restores the original nearest-camera assignment
//   WR64_VIEWPORT_PAIR_TRACE   CSV of every candidate and every decision
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>

#include "rt64_common.h"

namespace RT64 {
    // Default ON. Set WR64_VIEWPORT_PAIR_FIX=0 to restore the original behaviour
    // on the same binary, which is the A/B control.
    inline bool wr64ViewportPairFixEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_VIEWPORT_PAIR_FIX");
            const bool on = (value == nullptr) || (value[0] != '0');
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[viewportpair] scene assignment: %s\n",
                on ? "viewport-first (same scissor rect continues from itself)"
                   : "original (nearest camera wins)"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return on;
        }();
        return enabled;
    }

    inline const char *wr64ViewportPairPath() {
        static const char *path = std::getenv("WR64_VIEWPORT_PAIR_TRACE");
        return path;
    }

    inline bool wr64ViewportPairArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64ViewportPairPath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    // Four-edge equality. Deliberately strict: the trace prints the rects, so if
    // they ever jitter it will be visible as fallback rows rather than guessed at
    // with a tolerance.
    //
    // ★★ R2, 2026-08-03: AN EMPTY RECT PROVES NOTHING, SO IT MUST NOT COMPARE
    // EQUAL TO ANOTHER EMPTY ONE.
    //
    // Projection::scissorRect starts at reset() - the inverted rect - and only
    // ever grows from scissored draw calls, so a projection that never received
    // one keeps it for life. Plain four-edge equality then compares INT32_MAX to
    // INT32_MAX and answers TRUE, and two projections that drew NOTHING are
    // declared "the same viewport".
    //
    // Measured over one two-player session: 3,271 of 11,107 pairings, 29.4%,
    // every one taken in PASS 1 as if the rect had proved something. On 44 frames
    // it left two current and two previous scenes all equally "the same
    // viewport", with only the nearest-camera score left to separate them - which
    // is the exact coin flip R1 exists to remove, hiding inside the pass that was
    // supposed to have removed it. The pass 2 counter reads zero throughout,
    // which is why the summary always looked clean.
    //
    // With this guard those pairings fall to pass 2 and are decided by
    // nearest-camera EXPLICITLY, which is the honest answer for a scene that drew
    // nothing, instead of being silently claimed by pass 1.
    inline bool wr64ViewportRectsEqual(const FixedRect &a, const FixedRect &b) {
        if (a.isNull() || b.isNull() || a.isEmpty() || b.isEmpty()) {
            return false;
        }

        return (a.ulx == b.ulx) && (a.uly == b.uly) && (a.lrx == b.lrx) && (a.lry == b.lry);
    }

    inline std::mutex &wr64ViewportPairMutex() {
        static std::mutex m;
        return m;
    }

    inline std::FILE *wr64ViewportPairFile() {
        static std::FILE *file = [] () -> std::FILE * {
            if (!wr64ViewportPairArmed()) {
                return nullptr;
            }

            std::FILE *f = std::fopen(wr64ViewportPairPath(), "wb");
            if (f != nullptr) {
                std::fprintf(f,
                    "kind,submission_frame,scene_kind,cur_scenes,prev_scenes,"
                    "cur_index,prev_index,"
                    "cur_ulx,cur_uly,cur_lrx,cur_lry,"
                    "prev_ulx,prev_uly,prev_lrx,prev_lry,"
                    "view_diff,proj_diff,same_viewport,pass\n");
                std::fflush(f);
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[viewportpair] trace armed -> %s\n", wr64ViewportPairPath()); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            else {
                std::fprintf(stderr, "[viewportpair] could not open %s for writing\n", wr64ViewportPairPath());
                std::fflush(stderr);
            }
            return f;
        }();
        return file;
    }

    // kind=cand   one row per (cur scene, prev scene) pair considered
    // kind=pair   the pairing actually used; pass 1 = matched by viewport,
    //             pass 2 = fell back to nearest camera
    // kind=miss   a current scene that ended up with no previous scene at all
    inline void wr64ViewportPairRecord(
        const char *kind,
        uint64_t submissionFrame,
        uint32_t sceneKind,
        uint32_t curSceneCount,
        uint32_t prevSceneCount,
        uint32_t curIndex,
        uint32_t prevIndex,
        const FixedRect &curRect,
        const FixedRect &prevRect,
        float viewDiff,
        float projDiff,
        bool sameViewport,
        uint32_t pass)
    {
        if (!wr64ViewportPairArmed()) {
            return;
        }

        std::FILE *file = wr64ViewportPairFile();
        if (file == nullptr) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64ViewportPairMutex());
        std::fprintf(file, "%s,%llu,%u,%u,%u,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%.9g,%.9g,%u,%u\n",
            kind,
            static_cast<unsigned long long>(submissionFrame),
            sceneKind, curSceneCount, prevSceneCount, curIndex, prevIndex,
            int(curRect.ulx), int(curRect.uly), int(curRect.lrx), int(curRect.lry),
            int(prevRect.ulx), int(prevRect.uly), int(prevRect.lrx), int(prevRect.lry),
            viewDiff, projDiff, uint32_t(sameViewport), pass);
        std::fflush(file);
    }
};
