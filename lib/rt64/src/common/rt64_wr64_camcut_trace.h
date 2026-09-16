//
// WR64 camera-cut guard, R1.
//
// The defect
// ----------
// At every camera cut the game showed one wrong frame before the correct one:
// RT64 interpolated the camera across the cut, flying it from the outgoing shot
// to the incoming one over one native-frame pair (~9 display frames at 180 Hz
// against a 20 Hz native rate) and rendering the new scene through in-between
// cameras that never existed.
//
// Why the existing guard could not stop it
// ----------------------------------------
//   rt64_game_frame.cpp   the view/projection rigid body's components are
//                         initialised to G_EX_COMPONENT_INTERPOLATE, and for an
//                         untagged game (matrixId == G_EX_ID_AUTO, confirmed at
//                         runtime on every recorded frame) they stay that way
//                         while viewProjMap.mapped is set true unconditionally.
//   rt64_rigid_body.cpp   updateLinear's VelocityTolerance / MagnitudeThreshold
//                         test lives ONLY in the G_EX_COMPONENT_AUTO branch.
//                         Under INTERPOLATE it takes the else: lerpTranslation
//                         forced true, velocity history zeroed. updateAngular
//                         has no test at all - see its standing
//                         "FIXME: Defaults to always interpolate."
//
// So this is not a new rule. It is the rule the translation path already
// applies, extended to a path that could not reach it.
//
// The rule, calibrated from measurement
// -------------------------------------
// CAMCUT-R1 measured every camera pair over ~90 s of intro, 1827 native frames
// containing 21 cuts:
//
//   rot_deg    p50 0.55  p90 3.09  p95 4.51  normal max 10.91  cuts 18.5..176.6
//   trans      p50 55    p90 230   p95 350   normal max   812  cuts  723..12422
//
// Cuts are isolated single-frame spikes; the frames either side are almost
// always under 4 deg. Sustained fast motion looks nothing like that - 49
// consecutive-frame pairs above 5 deg in that run, all topping out near 10.9.
// Translation alone does NOT separate (a real cut at 723 sits below normal's
// 812); rotation plus the frame-to-frame ratio does.
//
//   cut = (rot >= RotTolerance AND rot / prevRot >= Ratio)
//      OR (trans >= TransTolerance AND trans / prevTrans >= Ratio)
//
// fires on 21 of 1827 frames (1.15%), one every 4.3 s, catching every event
// above 15 deg or 1000 units while leaving a maximum of 10.9 deg / 812 units
// untouched. The ratio clause protects ramps: a pan builds up, so its ratio
// never approaches the threshold, while cuts show ratios of 24x to 1e8. Ratio
// defaults to 10.0 - the same MagnitudeThreshold updateLinear already uses.
//
// The acos clamp is not cosmetic
// ------------------------------
// updateAngular computes acos((trace - 1) / 2) WITHOUT clamping. The
// measurement caught 27 frames where that argument left [-1,1] through ordinary
// rounding at near-zero rotation, which yields NaN. It is inert in that
// function today because lerpRotation is unconditionally true so nothing reads
// the result - but a guard that tests angular velocity would inherit the NaN
// and silently stop firing. This header clamps.
//
// Tuning and A/B
// --------------
//   WR64_CAMCUT_GUARD=0    disable the camera correction (measurement still runs)
//   WR64_CAMCUT_SUPPRESS=0 disable whole-pair interpolation suppression (R2)
//   WR64_CAMCUT_ROT_DEG    rotation tolerance in degrees   (default 12.0)
//   WR64_CAMCUT_TRANS      translation tolerance           (default 1000.0)
//   WR64_CAMCUT_RATIO      frame-to-frame ratio            (default 10.0)
//   WR64_CAMCUT_TRACE      path to a CSV of every evaluation, including whether
//                          the guard fired; dormant unless set
//
// The tolerances were calibrated on the intro. Gameplay, replay and the
// post-race pan are the scenes most likely to push past 10.9 deg, so re-measure
// there before treating these defaults as settled.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <mutex>

#include "rt64_math.h"

namespace RT64 {
    inline float wr64CamCutEnvFloat(const char *name, float fallback) {
        const char *value = std::getenv(name);
        if ((value == nullptr) || (value[0] == '\0')) {
            return fallback;
        }

        const double parsed = std::atof(value);
        return (parsed > 0.0) ? float(parsed) : fallback;
    }

    inline bool wr64CamCutGuardEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_CAMCUT_GUARD");
            // Default ON. Only an explicit 0 turns the correction off.
            return (value == nullptr) || (value[0] != '0');
        }();
        return enabled;
    }

    inline float wr64CamCutRotToleranceRad() {
        static const float tolerance = wr64CamCutEnvFloat("WR64_CAMCUT_ROT_DEG", 12.0f) * 0.0174532925f;
        return tolerance;
    }

    inline float wr64CamCutTransTolerance() {
        static const float tolerance = wr64CamCutEnvFloat("WR64_CAMCUT_TRANS", 1000.0f);
        return tolerance;
    }

    inline float wr64CamCutRatio() {
        static const float ratio = wr64CamCutEnvFloat("WR64_CAMCUT_RATIO", 10.0f);
        return ratio;
    }

    // Breaking the view-projection match does not stop world, vertex, tile, or
    // lookAt interpolation. Propagate camera cuts to the frame-weight calculation
    // to suppress every interpolation channel together.
    inline bool wr64CamCutSuppressEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_CAMCUT_SUPPRESS");
            // Default ON in this build: it is the experiment.
            return (value == nullptr) || (value[0] != '0');
        }();
        return enabled;
    }

    inline std::atomic<bool> &wr64CamCutPendingCut() {
        static std::atomic<bool> pending{false};
        return pending;
    }

    inline void wr64CamCutMarkCut() {
        wr64CamCutPendingCut().store(true, std::memory_order_release);
    }

    // Consumed once per native frame by the display loop, before it walks the
    // interpolated frames of the pair.
    inline bool wr64CamCutConsumePendingCut() {
        return wr64CamCutPendingCut().exchange(false, std::memory_order_acq_rel);
    }

    inline const char *wr64CamCutTracePath() {
        static const char *path = std::getenv("WR64_CAMCUT_TRACE");
        return path;
    }

    inline bool wr64CamCutTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64CamCutTracePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    inline std::FILE *wr64CamCutTraceFile() {
        static std::FILE *file = [] () -> std::FILE * {
            if (!wr64CamCutTraceArmed()) {
                return nullptr;
            }

            std::FILE *f = std::fopen(wr64CamCutTracePath(), "wb");
            if (f != nullptr) {
                std::fprintf(f,
                    "record,submission_frame,transforms_index,matrix_id,mapped_in,"
                    "trans_delta,rot_rad,rot_deg,acos_clamped,guard_fired\n");
                std::fflush(f);
            }
            else {
                std::fprintf(stderr, "[camcut] could not open %s for writing\n", wr64CamCutTracePath());
                std::fflush(stderr);
            }
            return f;
        }();
        return file;
    }

    struct Wr64CamCutHistory {
        float rotation = 0.0f;
        float translation = 0.0f;
        bool valid = false;
    };

    inline std::mutex &wr64CamCutMutex() {
        static std::mutex m;
        return m;
    }

    // Bounded by the number of view/projection transform slots a frame can hold.
    // Anything past the end simply gets no history, which biases toward firing.
    static constexpr uint32_t Wr64CamCutHistorySize = 256;

    inline Wr64CamCutHistory *wr64CamCutHistory() {
        static Wr64CamCutHistory history[Wr64CamCutHistorySize];
        return history;
    }

    inline void wr64CamCutAnnounceOnce() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static const bool announced = [] {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[camcut] guard %s (rot %.2f deg, trans %.1f, ratio %.1f)%s\n",
                wr64CamCutGuardEnabled() ? "ENGAGED" : "DISABLED",
                wr64CamCutRotToleranceRad() * 57.2957795f,
                wr64CamCutTransTolerance(),
                wr64CamCutRatio(),
                wr64CamCutTraceArmed() ? " trace armed" : ""); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        (void)announced;
    }

    // Returns true when the camera jumped between these two native frames, i.e.
    // the caller should break the match for this pair. Returns false when the
    // guard is disabled, so the measurement path stays usable for A/B.
    inline bool wr64CamCutEvaluate(
        uint64_t submissionFrame,
        uint32_t transformsIndex,
        uint32_t matrixId,
        bool mappedIn,
        const hlslpp::float4x4 &prevView,
        const hlslpp::float4x4 &curView)
    {
        wr64CamCutAnnounceOnce();

        // The same quantity updateLinear turns into its velocity.
        const hlslpp::float3 prevPosition = prevView[3].xyz;
        const hlslpp::float3 curPosition = curView[3].xyz;
        const float translationDelta = hlslpp::length(curPosition - prevPosition);

        // The same quantity updateAngular computes and then discards, clamped.
        const hlslpp::float3x3 invPrevRotation = hlslpp::inverse(rotationFrom3x3(extract3x3(prevView)));
        const hlslpp::float3x3 diffRotation = hlslpp::mul(invPrevRotation, rotationFrom3x3(extract3x3(curView)));
        const float diffTrace = traceFrom3x3(diffRotation);
        float cosArgument = (diffTrace - 1.0f) * 0.5f;
        const bool clamped = (cosArgument > 1.0f) || (cosArgument < -1.0f);
        cosArgument = (cosArgument > 1.0f) ? 1.0f : ((cosArgument < -1.0f) ? -1.0f : cosArgument);
        const float rotationRad = std::acos(cosArgument);

        bool fired = false;
        {
            std::lock_guard<std::mutex> lock(wr64CamCutMutex());

            Wr64CamCutHistory *slot = (transformsIndex < Wr64CamCutHistorySize)
                ? &wr64CamCutHistory()[transformsIndex]
                : nullptr;

            // No history means no basis for a ratio. Treat it as a jump: a guard
            // that fires when it should not costs one native-frame pair of
            // interpolation, which is invisible, while a guard that fails to fire
            // is the defect itself.
            const float Epsilon = 1e-6f;
            const bool haveHistory = (slot != nullptr) && slot->valid;
            const float rotationRatio = haveHistory
                ? (rotationRad / std::max(slot->rotation, Epsilon))
                : std::numeric_limits<float>::max();
            const float translationRatio = haveHistory
                ? (translationDelta / std::max(slot->translation, Epsilon))
                : std::numeric_limits<float>::max();

            const float ratio = wr64CamCutRatio();
            const bool rotationJump = (rotationRad >= wr64CamCutRotToleranceRad()) && (rotationRatio >= ratio);
            const bool translationJump = (translationDelta >= wr64CamCutTransTolerance()) && (translationRatio >= ratio);
            fired = wr64CamCutGuardEnabled() && mappedIn && (rotationJump || translationJump);

            if (fired) {
                wr64CamCutMarkCut();
            }

            if (slot != nullptr) {
                slot->rotation = rotationRad;
                slot->translation = translationDelta;
                slot->valid = true;
            }

            std::FILE *file = wr64CamCutTraceFile();
            if (file != nullptr) {
                static uint64_t record = 0;
                record++;
                std::fprintf(file, "%llu,%llu,%u,%u,%d,%.6f,%.8f,%.6f,%d,%d\n",
                    static_cast<unsigned long long>(record),
                    static_cast<unsigned long long>(submissionFrame),
                    transformsIndex,
                    matrixId,
                    mappedIn ? 1 : 0,
                    translationDelta,
                    rotationRad,
                    rotationRad * 57.2957795f,
                    clamped ? 1 : 0,
                    fired ? 1 : 0);
                std::fflush(file);
            }
        }

        return fired;
    }
};
