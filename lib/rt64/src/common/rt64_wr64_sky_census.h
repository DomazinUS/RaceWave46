//
// Wave Race 64 skybox census.
//
// Observation only. Nothing in this file is read back by the renderer, and no
// function here returns a value that any caller acts on. It exists to answer one
// question with data instead of a guess: which draw call is the skybox, and what
// exactly happens to it in the frame where it flickers?
//
// WR64_SKY_CENSUS=1        enable
// WR64_SKY_CENSUS_LOG      csv path, default wr64-sky-census.csv
// WR64_SKY_CENSUS_ROWS     row cap, default 20000
//
// Inert unless WR64_SKY_CENSUS is set. Disabled cost is one latched bool.
//
// What it is watching for, and why.
//
// RT64 renders the frames between two native ones by lerping each object's world
// matrix. RigidBody::updateLinear decides per object whether the translation part
// of that lerp is allowed, and Wave Race is an unmodified ROM that never emits a
// matrix group, so every object in the game takes the AUTO branch of that
// decision. AUTO computes:
//
//     curVel     = curPos - prevPos
//     dot        = max(dot(unit(prevVel), unit(curVel)), 1e-6)
//     curVelMag  = |curVel| / dot                          <-- note the divide
//     lerp       = (curVelMag < 5) || (curVelMag / max(|prevVel|, 1e-6)) < 10
//
// The divide happens before the test. So a direction reversal, where the true dot
// is negative and gets clamped up to 1e-6, inflates the magnitude by a factor of a
// million and forces lerp off. A body that was just re-matched has |prevVel| == 0,
// which produces a dot of zero, the same clamp and the same inflation.
//
// When lerp is off, lerpTransforms takes the current translation verbatim for the
// whole native window. At 20 Hz native against a 180 Hz display that is nine
// display frames of an object sitting where it will be rather than easing to it,
// and then one frame of it snapping back once the decision flips again. On a
// skybox, which fills the screen, that reads as a flicker.
//
// That mechanism is proven. What is not known is which draw call the skybox
// actually is, and the fix has to be applied at that call's own emission site
// rather than to the shared AUTO heuristic, which every object in the game
// depends on. So this census logs the identifying signature of whatever geometry
// flips its translation lerp, at the moment it flips, and leaves the behaviour
// completely alone.
//
// The arithmetic below is recomputed from the caller's own inputs rather than
// read out of RigidBody, so rt64_rigid_body.cpp does not need to change and stays
// byte for byte what the validated build compiles.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>

namespace RT64 {
    inline bool wr64SkyCensusEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_SKY_CENSUS");
            return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
        }();
        return enabled;
    }

    inline uint64_t wr64SkyCensusRowCap() {
        static const uint64_t cap = []() -> uint64_t {
            const char *value = std::getenv("WR64_SKY_CENSUS_ROWS");
            if ((value == nullptr) || (value[0] == '\0')) {
                return 20000ULL;
            }

            const long long parsed = std::atoll(value);
            return (parsed > 0) ? uint64_t(parsed) : 20000ULL;
        }();
        return cap;
    }

    // Everything known about the draw call that selected a world matrix. Filled in
    // during the call hash map traversal, where the GameCall is in scope, and read
    // back later in the match candidate loop, where it is not.
    struct Wr64SkyCensusSignature {
        uint64_t colorCombiner = 0;
        uint64_t otherMode = 0;
        uint64_t textureHash = 0;
        uint32_t triangleCount = 0;
        uint32_t vertexCount = 0;
        uint32_t generatedVertexCount = 0;
        uint32_t firstVertexAddress = 0;
        uint32_t minWorldMatrix = 0;
        uint32_t maxWorldMatrix = 0;
        uint32_t callIndex = 0;
    };

    inline std::FILE *wr64SkyCensusFile() {
        static std::FILE *file = []() -> std::FILE * {
            const char *path = std::getenv("WR64_SKY_CENSUS_LOG");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-sky-census.csv";
            }

            std::FILE *opened = std::fopen(path, "w");
            if (opened != nullptr) {
                std::fprintf(opened,
                    "frame,event,cur_transform,prev_transform,position_interpolation,"
                    "prev_lerp_translation,cur_lerp_translation,"
                    "prev_vel_mag,raw_cur_vel_mag,dot,inflated_cur_vel_mag,inflation,ratio_vs_prev,"
                    "cur_x,cur_y,cur_z,prev_x,prev_y,prev_z,"
                    "has_signature,triangle_count,vertex_count,generated_vertex_count,first_vertex_address,"
                    "color_combiner,other_mode,texture_hash,min_world_matrix,max_world_matrix,call_index\n");
                std::fflush(opened);
            }

            return opened;
        }();
        return file;
    }

    // Per native frame registry of world matrix index to the call that drew it.
    // thread_local because the frame matcher runs on one thread and this must not
    // introduce a lock onto a path that is being measured for stalls.
    inline std::unordered_map<uint32_t, Wr64SkyCensusSignature> &wr64SkyCensusRegistry() {
        static thread_local std::unordered_map<uint32_t, Wr64SkyCensusSignature> registry;
        return registry;
    }

    inline void wr64SkyCensusBeginFrame() {
        if (!wr64SkyCensusEnabled()) {
            return;
        }

        wr64SkyCensusRegistry().clear();
    }

    inline void wr64SkyCensusRegisterCall(uint32_t transformIndex, const Wr64SkyCensusSignature &signature) {
        if (!wr64SkyCensusEnabled()) {
            return;
        }

        // First writer wins. A world matrix shared by several calls keeps the first
        // one seen rather than the last, so the column stays stable across frames
        // instead of depending on map iteration order.
        wr64SkyCensusRegistry().emplace(transformIndex, signature);
    }

    // Replays the AUTO branch of RigidBody::updateLinear on the caller's own
    // inputs and writes a row when the decision is interesting. Positions and the
    // inherited velocity come in as plain floats so this header does not need to
    // know about hlslpp.
    inline void wr64SkyCensusObserve(uint64_t frame, uint32_t curTransformIndex, uint32_t prevTransformIndex,
        uint8_t positionInterpolation, bool prevLerpTranslation, bool curLerpTranslation,
        const float prevVelocity[3], const float prevPosition[3], const float curPosition[3])
    {
        if (!wr64SkyCensusEnabled()) {
            return;
        }

        static uint64_t rowsWritten = 0;
        if (rowsWritten >= wr64SkyCensusRowCap()) {
            return;
        }

        // The same constants rt64_rigid_body.cpp uses. If that file ever changes
        // these, this census silently stops describing what the renderer did, so
        // the build pins its hash.
        const float Epsilon = 1e-6f;
        const float VelocityTolerance = 5.0f;
        const float MagnitudeThreshold = 10.0f;

        const float curVel[3] = {
            curPosition[0] - prevPosition[0],
            curPosition[1] - prevPosition[1],
            curPosition[2] - prevPosition[2]
        };

        const float prevVelMag = std::sqrt(
            (prevVelocity[0] * prevVelocity[0]) +
            (prevVelocity[1] * prevVelocity[1]) +
            (prevVelocity[2] * prevVelocity[2]));
        const float rawCurVelMag = std::sqrt(
            (curVel[0] * curVel[0]) + (curVel[1] * curVel[1]) + (curVel[2] * curVel[2]));

        const float prevScale = 1.0f / ((prevVelMag > Epsilon) ? prevVelMag : Epsilon);
        const float curScale = 1.0f / ((rawCurVelMag > Epsilon) ? rawCurVelMag : Epsilon);
        const float rawDot =
            ((prevVelocity[0] * prevScale) * (curVel[0] * curScale)) +
            ((prevVelocity[1] * prevScale) * (curVel[1] * curScale)) +
            ((prevVelocity[2] * prevScale) * (curVel[2] * curScale));
        const float dot = (rawDot > Epsilon) ? rawDot : Epsilon;
        const float inflatedCurVelMag = rawCurVelMag / dot;
        const float inflation = (rawCurVelMag > Epsilon) ? (inflatedCurVelMag / rawCurVelMag) : 1.0f;
        const float ratioVsPrev = inflatedCurVelMag / ((prevVelMag > Epsilon) ? prevVelMag : Epsilon);

        // A steady decision is not a flicker. What matters is the frame where it
        // changes, plus the near misses where the clamp did real work without
        // tipping the result, because those are the same mechanism one step short
        // of firing.
        const bool flipped = (prevLerpTranslation != curLerpTranslation);
        const bool clamped = (inflation >= 100.0f);
        if (!flipped && !clamped) {
            return;
        }

        std::FILE *file = wr64SkyCensusFile();
        if (file == nullptr) {
            return;
        }

        const char *event = flipped
            ? (curLerpTranslation ? "lerp_on" : "lerp_off")
            : "clamped_no_flip";

        const std::unordered_map<uint32_t, Wr64SkyCensusSignature> &registry = wr64SkyCensusRegistry();
        auto signatureIt = registry.find(curTransformIndex);
        const bool hasSignature = (signatureIt != registry.end());
        const Wr64SkyCensusSignature blank;
        const Wr64SkyCensusSignature &signature = hasSignature ? signatureIt->second : blank;

        std::fprintf(file,
            "%llu,%s,%u,%u,%u,%u,%u,"
            "%.6f,%.6f,%.9f,%.6f,%.1f,%.6f,"
            "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,"
            "%u,%u,%u,%u,0x%08X,"
            "0x%016llX,0x%016llX,0x%016llX,%u,%u,%u\n",
            static_cast<unsigned long long>(frame), event, curTransformIndex, prevTransformIndex,
            uint32_t(positionInterpolation), uint32_t(prevLerpTranslation), uint32_t(curLerpTranslation),
            double(prevVelMag), double(rawCurVelMag), double(dot), double(inflatedCurVelMag),
            double(inflation), double(ratioVsPrev),
            double(curPosition[0]), double(curPosition[1]), double(curPosition[2]),
            double(prevPosition[0]), double(prevPosition[1]), double(prevPosition[2]),
            uint32_t(hasSignature), signature.triangleCount, signature.vertexCount,
            signature.generatedVertexCount, signature.firstVertexAddress,
            static_cast<unsigned long long>(signature.colorCombiner),
            static_cast<unsigned long long>(signature.otherMode),
            static_cast<unsigned long long>(signature.textureHash),
            signature.minWorldMatrix, signature.maxWorldMatrix, signature.callIndex);
        std::fflush(file);

        rowsWritten++;

        // Unused here, kept so the tolerance constants above are visibly the ones
        // the renderer applies rather than numbers that drifted apart silently.
        (void)VelocityTolerance;
        (void)MagnitudeThreshold;
    }
}
