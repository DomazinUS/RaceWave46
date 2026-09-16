//
// WR64 VI meter - did the GAME flip early, or did the VI CLOCK run fast?
//
// The finding this exists to resolve
// ----------------------------------
// The native frame timer (rt64_wr64_cadence_meter.h) found the stutter. Over
// three races on Sunset Bay, one native frame per race arrives about 28 ms early,
// mid-race, in an otherwise flat 50 ms stream:
//
//     race 1  f1313:  50.64 49.15 49.88 49.47 [22.04] 48.43 49.54 52.50
//     race 2  f3038:  50.23 50.06 50.33 49.12 [22.22] 48.95 50.48 49.63
//     race 3  f4682:  51.32 50.23 50.13 48.41 [30.67 40.71] 50.75 49.86
//
// Total isolation: 4,798 mid-race frames, exactly three events, nothing at all
// between 35 and 40 ms, next shortest in the whole run 45 ms. Once per race, at
// a different point each time, which is the report exactly.
//
// It is visible because RT64 gives that short frame the SAME nine interpolated
// frames as a full one - display_frames is 9 on all three - so one game tick's
// motion, which occupied 22 ms of real time, is shown over a rigid 50 ms. The
// whole image drops to about 44% speed for 50 ms and snaps back.
//
// The fork this measures
// ----------------------
// State::updateScreen runs once per VI. It pushes a factor only when the game
// actually flips the framebuffer, counting the VIs in between:
//
//     if (viDifferent && viVisible) { pushVI(...); pushFactor(counter + 1); counter = 0; }
//     else if (viVisible)           { counter++; }
//
// At 20 Hz the factor is 3 - three VIs per flip. So a 22 ms native frame is one
// of exactly two things:
//
//   THE GAME FLIPPED EARLY   the factor dropped to 1 or 2 for that frame, i.e.
//                            the game's own logic ran short. Authentic console
//                            behaviour, and the port is reproducing it faithfully.
//
//   THE VI CLOCK RAN FAST    the factor stayed 3 and three VIs elapsed in 22 ms
//                            instead of 50. That is the recomp runtime's pacing,
//                            and it is a port bug.
//
// There is already an argument for the second: logicalRateFromFactors requires
// three consecutive factors to AGREE, so a changed factor forces the rate to 0
// for three pushes, which shows up as batch=1 frames with no interpolation at
// all. The run has 21 of those and EVERY ONE is inside a race load. Not one
// mid-race. So the factor probably never moved - but that is an inference from
// an absence, and an absence is the weakest evidence there is. This measures it.
//
// What it records
// ---------------
// One row per updateScreen call - every VI, about 60 a second - with the
// wall-clock gap since the previous one. The two cases are then trivially
// distinguishable in the file:
//
//   VI gaps steady at 16.7 ms, one flip after 2 VIs   -> the game flipped early
//   VI gaps bunched, three of them inside 22 ms       -> the clock ran fast
//
//   WR64_VI_METER   names the CSV. Diagnostic, default off.
//
// steady_clock, and FLUSHED ON EVERY ROW. This game reaches its exit handlers
// about one run in four, so anything that dumps from a static destructor is
// worthless here - the frame-time probe established that over three wasted play
// sessions.
//
// 60 rows a second against the cadence meter's 20 is still nothing, and this
// runs on the game thread rather than the present thread, which is the one that
// must never block.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>

namespace RT64 {
    inline const char *wr64ViMeterPath() {
        static const char *path = std::getenv("WR64_VI_METER");
        return path;
    }

    inline bool wr64ViMeterArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64ViMeterPath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[vimeter] armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    struct Wr64ViMeterState {
        std::FILE *file = nullptr;
        bool opened = false;
        size_t written = 0;
        uint64_t viIndex = 0;
        std::chrono::steady_clock::time_point lastVi{};
        bool haveVi = false;
        // The flip is the interesting event: the gap between framebuffer flips is
        // the native frame period the cadence meter measures downstream.
        std::chrono::steady_clock::time_point lastFlip{};
        bool haveFlip = false;
        size_t flips = 0;
        size_t shortFlips = 0;
        // A SELF-CALIBRATING BASELINE, not a hardcoded period.
        //
        // The first draft compared the flip gap against a literal 30 ms, which
        // silently assumes the game flips every 50 ms. Its own self-test ran a
        // scaled-down clock and every single flip was reported as short. The
        // cadence meter had exactly this bug and there is a build gate against it
        // there; the same rule applies here. The baseline is learned from the run,
        // so this works at 20 Hz, at 30 Hz, and on any course or mode that differs.
        int64_t flipBaselineUs = 0;
        size_t flipSamples = 0;
        // The usual VIs-per-flip for this run, learned the same way. Comparing the
        // event's factor against a LEARNED value rather than a literal 3 keeps the
        // verdict correct at 30 Hz, where the normal factor is 2.
        uint32_t baselineFactor = 0;
    };

    // Flips needed before the baseline is trusted. Below this the meter records
    // but never calls anything short, because an unwarmed average would flag the
    // first frames of a run - which are loads, and therefore noise.
    static constexpr size_t Wr64ViMeterWarmupFlips = 24;

    // A flip closer together than this fraction of the learned baseline counts as
    // the timing event.
    //
    // 0.8 IS NOT ARBITRARY AND 0.6 WAS WRONG. The self-test caught it: a flip that
    // consumes 2 VIs instead of 3 lands at 0.667 of baseline, so a 0.6 threshold
    // would have missed the "game flipped early" case entirely - in the scaled test
    // AND in the real game. Measured jitter reaches 0.9 (45 ms against a 50 ms
    // baseline, 14 frames in the recorded run), and the events being hunted came in
    // at 0.44. 0.8 sits in the gap: above a factor-2 flip, below ordinary jitter.
    static constexpr double Wr64ViMeterShortFraction = 0.8;

    inline std::mutex &wr64ViMeterMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    // Leaked on purpose, same as every other recorder here: anything that might be
    // touched during teardown must outlive teardown.
    inline Wr64ViMeterState &wr64ViMeterState() {
        static Wr64ViMeterState *s = new Wr64ViMeterState();
        return *s;
    }

    static constexpr size_t Wr64ViMeterMaxRows = 1500000;

    // flipped   - the game changed the visible framebuffer on this VI
    // factor    - VIs consumed by this flip, i.e. what pushFactor was given.
    //             Zero on a VI that did not flip.
    inline void wr64ViMeterRecord(bool flipped, uint32_t factor, bool viVisible,
        bool fromEarlyPresent, uint32_t fbAddress)
    {
        if (!wr64ViMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64ViMeterMutex());
        Wr64ViMeterState &s = wr64ViMeterState();

        if (!s.opened) {
            s.opened = true;
            s.file = std::fopen(wr64ViMeterPath(), "wb");
            if (s.file != nullptr) {
                std::fprintf(s.file,
                    "vi_index,vi_gap_us,flipped,factor,flip_gap_us,vi_visible,"
                    "from_early_present,fb_address\n");
                std::fflush(s.file);
            }
            else {
                std::fprintf(stderr, "[vimeter] could not open %s for writing\n",
                    wr64ViMeterPath());
                std::fflush(stderr);
            }
        }

        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        int64_t viGapUs = 0;
        if (s.haveVi) {
            viGapUs = std::chrono::duration_cast<std::chrono::microseconds>(now - s.lastVi).count();
        }
        s.lastVi = now;
        s.haveVi = true;

        int64_t flipGapUs = 0;
        if (flipped) {
            if (s.haveFlip) {
                flipGapUs = std::chrono::duration_cast<std::chrono::microseconds>(now - s.lastFlip).count();
            }
            s.lastFlip = now;
            s.haveFlip = true;
            s.flips++;

            // The event, named out loud as it happens, against a baseline learned
            // from this run rather than an assumed 50 ms. The factor in the line is
            // the whole answer: unchanged means the clock ran fast, fewer means the
            // game flipped early.
            //
            // The baseline is updated only from flips that are NOT short, so one
            // short flip cannot drag the reference down and hide the next one.
            // TWO INDEPENDENT DETECTORS, because the two cases leave different
            // evidence and only one of them is a timing question.
            //
            //   fewer VIs than usual  -> the game flipped early. EXACT, no
            //                            threshold: the factor is an integer and
            //                            either it dropped or it did not.
            //   gap short, factor same -> the clock ran fast. This one genuinely is
            //                            a timing comparison.
            //
            // Relying on the timing test alone was the first draft's mistake, and it
            // would have silently missed the case it most needed to catch.
            const bool warm = (s.flipSamples >= Wr64ViMeterWarmupFlips);
            const bool fewerVis = warm && (s.baselineFactor > 0) && (factor < s.baselineFactor);
            const bool gapShort = warm && (flipGapUs > 0) &&
                (double(flipGapUs) < (double(s.flipBaselineUs) * Wr64ViMeterShortFraction));
            const bool shortFlip = fewerVis || gapShort;
            if (shortFlip) {
                s.shortFlips++;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[vimeter] SHORT FLIP: %.1f ms after the last one (usual %.1f),"
                    " factor %u (%s)\n",
                    double(flipGapUs) / 1000.0, double(s.flipBaselineUs) / 1000.0, factor,
                    fewerVis ? "fewer VIs than usual - THE GAME FLIPPED EARLY"
                             : "factor unchanged - THE VI CLOCK RAN FAST"); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            else if (flipGapUs > 0) {
                // Exponential moving average, slow enough that a genuine rate change
                // is followed within a second or so but a single frame moves it
                // barely at all.
                s.flipBaselineUs = (s.flipSamples == 0)
                    ? flipGapUs
                    : ((s.flipBaselineUs * 15) + flipGapUs) / 16;
                s.baselineFactor = (s.flipSamples == 0) ? factor : s.baselineFactor;
                if (factor > s.baselineFactor) {
                    s.baselineFactor = factor;
                }
                s.flipSamples++;
            }
        }

        const uint64_t index = s.viIndex++;
        if ((s.file == nullptr) || (s.written >= Wr64ViMeterMaxRows)) {
            return;
        }

        std::fprintf(s.file, "%llu,%lld,%u,%u,%lld,%u,%u,%08X\n",
            static_cast<unsigned long long>(index),
            static_cast<long long>(viGapUs),
            flipped ? 1u : 0u,
            factor,
            static_cast<long long>(flipGapUs),
            viVisible ? 1u : 0u,
            fromEarlyPresent ? 1u : 0u,
            fbAddress);
        std::fflush(s.file);
        s.written++;
    }
};
