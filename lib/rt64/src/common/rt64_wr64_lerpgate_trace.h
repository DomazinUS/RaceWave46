//
// WR64 lerp-gate measurement, R1.
//
// MEASUREMENT ONLY. Nothing here changes what is rendered. Dormant unless
// WR64_LERPGATE_TRACE names an output file.
//
// What it is for
// --------------
// An infrequent stutter while the camera follows the player, reported in turns
// and at the same corners. An Observatory capture taken seconds after it
// happened ruled out everything about timing:
//
//   presentation   4257 presents, median 5.551 ms = 180.2 Hz, largest gap in
//                  21 s = 6.190 ms = 1.12x median, nothing above 3x
//   game frames    426 gfx_tasks, median 50.029 ms = 19.99 Hz, max 1.03x
//   workloads      constant 2 per frame, so frameMap.workloads[].mapped never
//                  goes false and the process/upload asymmetry never fires
//   camera         path smooth, no missing frames, projection-set changes do
//                  not disturb the pairing
//
// So the hitch is not in WHEN frames appear. It is in WHAT is drawn in them,
// which points at a per-object interpolation decision.
//
// The suspect
// -----------
// World transforms use G_EX_COMPONENT_AUTO (TransformGroup defaults), unlike
// the camera which is forced to INTERPOLATE, so they DO reach the
// discontinuity test in RigidBody::updateLinear:
//
//   dotCurVel = max(dot(prevVelDir, curVelDir), Epsilon)
//   curVelMag /= dotCurVel                  // a DIRECTION change inflates it
//   lerpTranslation = (curVelMag < 5.0) || (curVelMag / prevVelMag) < 10.0
//
// When that returns false the object stops interpolating for the pair: it holds
// at its native position for all ~9 display frames and then snaps. That is the
// shape of a single stutter, and it matches the behaviour noted during the sky
// work ("nine display frames pinned, then a snap").
//
// The open question is whether it actually trips during a turn, and on which
// transform. At constant speed the ratio test needs roughly 84 degrees of
// direction change in one native frame, which no jetski does - so if this is
// the cause, the trip has to come from the speed term as well, or from some
// object other than the player. That is exactly what this measures. Do not
// assume it is the player's transform.
//
// Output
// ------
//   kind=frame  one row per native frame: how many transforms were evaluated,
//               how many had translation interpolation switched OFF, and how
//               many gate rows were dropped by the per-frame cap
//   kind=gate   one row per switched-off transform (capped, default 24 per
//               frame) with every term of the test, so the reason is visible
//               rather than inferred
//
// Read it against where the stutter was felt. If the gate rows cluster on those
// corners, that is the mechanism; if they are constant everywhere or absent,
// it is not, and this eliminates it cleanly.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>

#include "rt64_math.h"
#include "../include/rt64_extended_gbi.h"

namespace RT64 {
    inline const char *wr64LerpGatePath() {
        static const char *path = std::getenv("WR64_LERPGATE_TRACE");
        return path;
    }

    inline bool wr64LerpGateArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64LerpGatePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    inline uint32_t wr64LerpGatePerFrameCap() {
        static const uint32_t cap = [] {
            const char *v = std::getenv("WR64_LERPGATE_CAP");
            const int parsed = (v != nullptr) ? std::atoi(v) : 0;
            return (parsed > 0) ? uint32_t(parsed) : 24u;
        }();
        return cap;
    }

    // LERPGATE-FIX-R1. Default ON. Set WR64_LERPGATE_FIX=0 to restore the
    // original AUTO test (dot-product inflation with a 1e-6 floor) for A/B.
    inline bool wr64LerpGateFixEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_LERPGATE_FIX");
            const bool on = (value == nullptr) || (value[0] != '0');
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[lerpgate] AUTO translation guard: %s\n",
                on ? "REPAIRED (no dot inflation, no zero-history gating)" : "original"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return on;
        }();
        return enabled;
    }

    // Absolute step, in world units, past which an object with no usable velocity
    // history is treated as having teleported rather than moved. Measured gap in
    // the data is 100..200 with only 2 samples in it; default sits in the middle.
    inline float wr64LerpGateJumpTolerance() {
        static const float tolerance = [] {
            const char *v = std::getenv("WR64_LERPGATE_JUMP");
            const double parsed = (v != nullptr) ? std::atof(v) : 0.0;
            return (parsed > 0.0) ? float(parsed) : 150.0f;
        }();
        return tolerance;
    }

    inline std::mutex &wr64LerpGateMutex() {
        static std::mutex m;
        return m;
    }

    inline std::FILE *wr64LerpGateFile() {
        static std::FILE *file = [] () -> std::FILE * {
            if (!wr64LerpGateArmed()) {
                return nullptr;
            }

            std::FILE *f = std::fopen(wr64LerpGatePath(), "wb");
            if (f != nullptr) {
                std::fprintf(f,
                    "kind,submission_frame,transform_index,component,"
                    "evaluated,gated,dropped,"
                    "prev_vel_mag,cur_vel_mag,dot,inflated_mag,ratio\n");
                std::fflush(f);
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[lerpgate] trace armed -> %s (cap %u rows/frame)\n",
                    wr64LerpGatePath(), wr64LerpGatePerFrameCap()); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            else {
                std::fprintf(stderr, "[lerpgate] could not open %s for writing\n", wr64LerpGatePath());
                std::fflush(stderr);
            }
            return f;
        }();
        return file;
    }

    struct Wr64LerpGateFrame {
        uint64_t frame = UINT64_MAX;
        uint32_t evaluated = 0;
        uint32_t gated = 0;
        uint32_t dropped = 0;
    };

    inline Wr64LerpGateFrame &wr64LerpGateFrameState() {
        static Wr64LerpGateFrame state;
        return state;
    }

    // Flushes the per-frame summary when the native frame changes. Caller holds
    // the mutex.
    inline void wr64LerpGateFlushLocked(std::FILE *file, uint64_t frame) {
        Wr64LerpGateFrame &s = wr64LerpGateFrameState();
        if (s.frame == frame) {
            return;
        }

        if ((s.frame != UINT64_MAX) && (file != nullptr)) {
            std::fprintf(file, "frame,%llu,,,%u,%u,%u,,,,,\n",
                static_cast<unsigned long long>(s.frame), s.evaluated, s.gated, s.dropped);
            std::fflush(file);
        }

        s.frame = frame;
        s.evaluated = 0;
        s.gated = 0;
        s.dropped = 0;
    }

    // Call immediately AFTER RigidBody::updateLinear, passing the linearVelocity
    // captured immediately BEFORE it (updateLinear overwrites that member).
    inline void wr64LerpGateRecord(
        uint64_t submissionFrame,
        uint32_t transformIndex,
        uint8_t componentInterpolation,
        const hlslpp::float3 &prevLinearVelocity,
        const hlslpp::float4x4 &prevTransform,
        const hlslpp::float4x4 &curTransform,
        bool lerpTranslationResult)
    {
        if (!wr64LerpGateArmed()) {
            return;
        }

        std::FILE *file = wr64LerpGateFile();
        if (file == nullptr) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64LerpGateMutex());
        wr64LerpGateFlushLocked(file, submissionFrame);

        Wr64LerpGateFrame &s = wr64LerpGateFrameState();
        s.evaluated++;

        // Only the AUTO path can gate; anything else was decided by the flag.
        if (lerpTranslationResult || (componentInterpolation != G_EX_COMPONENT_AUTO)) {
            return;
        }

        s.gated++;
        if (s.gated > wr64LerpGatePerFrameCap()) {
            s.dropped++;
            return;
        }

        // Recompute exactly what updateLinear computed, so the row shows the
        // reason rather than an inference about it.
        const float Epsilon = 1e-6f;
        const hlslpp::float3 prevPosition = prevTransform[3].xyz;
        const hlslpp::float3 curPosition = curTransform[3].xyz;
        const hlslpp::float3 curLinearVelocity = curPosition - prevPosition;
        const float prevVelMag = hlslpp::length(prevLinearVelocity);
        const float curVelMag = hlslpp::length(curLinearVelocity);
        const float dotCurVel = std::max(
            hlslpp::dot(prevLinearVelocity / std::max(prevVelMag, Epsilon),
                        curLinearVelocity / std::max(curVelMag, Epsilon))[0], Epsilon);
        const float inflated = curVelMag / dotCurVel;
        const float ratio = inflated / std::max(prevVelMag, Epsilon);

        std::fprintf(file, "gate,%llu,%u,%u,,,,%.4f,%.4f,%.6f,%.4f,%.4f\n",
            static_cast<unsigned long long>(submissionFrame),
            transformIndex,
            uint32_t(componentInterpolation),
            prevVelMag, curVelMag, dotCurVel, inflated, ratio);
        std::fflush(file);
    }
};
