//
// RT64
//

#include "../../../../include/wr64_diagnostic_policy.h"

#include "common/rt64_math.h"
#include "common/rt64_wr64_sky_census.h"
#include "common/rt64_wr64_sky_bracket.h"
#include "common/rt64_wr64_camcut_trace.h"
#include "common/rt64_wr64_lerpgate_trace.h"
#include "common/rt64_wr64_viewport_pair.h"
#include "common/rt64_wr64_gantry_anchor.h"
#include "common/rt64_wr64_fish_school.h"
#include "common/rt64_wr64_sprite_families.h"
#include "common/rt64_wr64_dolphin_identity.h"
#include "common/rt64_wr64_dolphin_trace.h"
#include "common/rt64_wr64_drake_school.h"
#include "common/rt64_wr64_whale_identity.h"
#include "common/rt64_wr64_duck_identity.h"
#include "common/rt64_wr64_buoy_identity.h"
#include "common/rt64_wr64_area_buoy_identity.h"
#include "common/rt64_wr64_stunt_ring_identity.h"
#include "common/rt64_wr64_celestial_identity.h"
#include "common/rt64_wr64_rt_view.h"
#include "common/rt64_wr64_water_roundness.h"
#include "common/rt64_wr64_far_water_distance.h"

#include "rt64_game_frame.h"
#include "rt64_workload_queue.h"
#include "common/rt64_wr64_animal_replay.h"
#include "common/rt64_wr64_cloud_coverage_integration.h"
#include "wr64_forensic.h"

#include "xxHash/xxh3.h"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

namespace RT64 {
    // GameFrame

    static constexpr uint32_t Wr64ForensicBackdropGroupMask = 0xFFFFFF00U;
    static constexpr uint32_t Wr64ForensicBackdropGroupBase = 0x57524300U;
    static constexpr float Wr64ExactSkyChartCutThreshold = 384.0f;

    static uint32_t wr64FloatBits(float value) {
        uint32_t bits = 0;
        static_assert(sizeof(bits) == sizeof(value));
        std::memcpy(&bits, &value, sizeof(bits));
        return bits;
    }

    static bool isWr64CourseSkyDraw(const DrawCall &desc, uint32_t matrixIdHash) {
        return
            ((matrixIdHash & Wr64ForensicBackdropGroupMask) ==
                Wr64ForensicBackdropGroupBase) &&
            (desc.triangleCount == 6U) &&
            (desc.colorCombiner.L == 0xFC11C223U) &&
            (desc.colorCombiner.H == 0xFF87FFFFU) &&
            (desc.otherMode.L == 0x00504240U) &&
            (desc.otherMode.H == 0x00882C3FU);
    }

    static bool isWr64ForensicPrimaryBackdropTransform(
        const DrawData &drawData, uint32_t transformIndex)
    {
        if ((transformIndex >= drawData.worldTransformVertexIndices.size()) ||
            (transformIndex >= drawData.worldTransformGroups.size()) ||
            (drawData.vertexSegmentedAddresses.size() != drawData.vertexCount()) ||
            (drawData.worldTransformVertexCount(transformIndex) != 7U))
        {
            return false;
        }

        const uint32_t groupIndex = drawData.worldTransformGroups[transformIndex];
        if ((groupIndex >= drawData.transformGroups.size()) ||
            ((drawData.transformGroups[groupIndex].matrixId &
                Wr64ForensicBackdropGroupMask) != Wr64ForensicBackdropGroupBase))
        {
            return false;
        }

        const uint32_t vertexStart = drawData.worldTransformVertexIndices[transformIndex];
        if ((uint64_t(vertexStart) + 7ULL) > drawData.vertexSegmentedAddresses.size()) {
            return false;
        }

        const uint32_t addressBase = drawData.vertexSegmentedAddresses[vertexStart];
        if ((addressBase != 0x06000000U) && (addressBase != 0x06000070U)) {
            return false;
        }

        for (uint32_t i = 0; i < 7; i++) {
            if (drawData.vertexSegmentedAddresses[vertexStart + i] !=
                (addressBase + (i * 0x10U)))
            {
                return false;
            }
        }

        return true;
    }
    static constexpr uint64_t Wr64LateralDropletTextureHash = 0xD15D049BC4BE6C0CULL;

    // Smallest mesh that the water surface producer can emit. The producer's
    // grid dimension global takes 0x10, 0x0C or 0x0A, so the smallest possible
    // surface is a 10x10 lattice. Anything materially below that which happens
    // to live in the graphics pool is scratch geometry, not the water sheet.
    static constexpr uint32_t Wr64MinimumGeneratedWaterTriangles = 128;
    static constexpr uint32_t Wr64MinimumGeneratedWaterVertices = 64;

    static bool isWr64GeneratedWaterVertexAddress(uint32_t segmentedAddress) {
        // Segment 3 is gGfxPool, the per-frame graphics scratch allocator. Any
        // vertex sourced from it was written by the CPU during this frame
        // rather than read from ROM-resident geometry, which is the defining
        // property of the runtime-generated water surface on every course.
        //
        // This deliberately does not test a fixed pool offset. The previous
        // [0x03013D68, 0x030185E8) window was measured on Sunny Beach alone and
        // silently excluded any course whose producer lands elsewhere.
        return (segmentedAddress >= 0x03000000U) && (segmentedAddress < 0x04000000U);
    }

    // Identify the water surface by where its vertices came from, not by how it
    // is painted.
    //
    // The previous test required triangleCount == 876, one specific colour
    // combiner, one specific other mode, and one specific texture hash, all
    // sampled from Sunny Beach. A whole-frame provenance census across three
    // courses showed that the surface mesh itself is identical everywhere --
    // 876 triangles and 500 vertices drawn from the same pool span -- but that
    // the texture hash differs per course. Courses painting a different texture
    // on the identical mesh were therefore rejected and received no vertex
    // interpolation at all.
    //
    // Provenance is the property that actually defines this geometry: it is the
    // only mesh in the frame whose every indexed vertex is written into the
    // graphics pool by the CPU each frame. The same census confirmed that
    // exactly one draw call per frame satisfies that on every course, so this
    // test is both course-independent and unambiguous.
    // Water-surface interpolation is part of the production renderer path.
    // Diagnostic builds must not be able to silently disable it through
    // process environment inherited by an ordinary game launch.
    static bool wr64WaterInterpolationEnabled() {
        return true;
    }

    static bool isWr64GeneratedWaterProvenanceCall(const DrawData &drawData, const GameCall &call) {
        const DrawCall &desc = call.callDesc;
        if (desc.triangleCount < Wr64MinimumGeneratedWaterTriangles) {
            return false;
        }

        const uint64_t faceIndicesStart = call.meshDesc.faceIndicesStart;
        const uint64_t faceIndicesEnd = faceIndicesStart + (uint64_t(desc.triangleCount) * 3ULL);
        if (faceIndicesEnd > drawData.faceIndices.size()) {
            return false;
        }

        if (faceIndicesEnd <= faceIndicesStart) {
            return false;
        }

        if (drawData.vertexSegmentedAddresses.size() != drawData.vertexCount()) {
            return false;
        }

        uint32_t minVertexIndex = std::numeric_limits<uint32_t>::max();
        uint32_t maxVertexIndex = 0;
        for (uint64_t f = faceIndicesStart; f < faceIndicesEnd; f++) {
            const uint32_t vertexIndex = drawData.faceIndices[size_t(f)];
            if ((vertexIndex >= drawData.vertexSegmentedAddresses.size()) ||
                !isWr64GeneratedWaterVertexAddress(drawData.vertexSegmentedAddresses[vertexIndex])) {
                return false;
            }

            minVertexIndex = std::min(minVertexIndex, vertexIndex);
            maxVertexIndex = std::max(maxVertexIndex, vertexIndex);
        }

        // A large mesh built entirely from pool vertices still has to span
        // enough distinct vertices to be a surface lattice rather than a small
        // block of scratch geometry drawn many times over.
        return ((maxVertexIndex - minVertexIndex) + 1) >= Wr64MinimumGeneratedWaterVertices;
    }

    static bool isWr64GeneratedWaterCall(const DrawData &drawData, const GameCall &call) {
        return wr64WaterInterpolationEnabled() &&
            isWr64GeneratedWaterProvenanceCall(drawData, call);
    }

    static FILE *wr64WaterMeshTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *traceFile = []() -> FILE * {
            const char *enabled = std::getenv("WR64_WATER_MESH_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_WATER_MESH_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-water-mesh-trace.csv";
            }

            FILE *file = nullptr;
#ifdef _WIN32
            fopen_s(&file, path, "w");
#else
            file = std::fopen(path, "w");
#endif
            if (file != nullptr) {
                std::fprintf(file,
                    "submission_frame,stage,cur_workload,prev_workload,scene_projection,cur_call,prev_call,call_hash,prev_hash_candidates,"
                    "cur_transform,prev_transform,cur_group,prev_group,cur_matrix_id,prev_matrix_id,cur_matrix_count,prev_matrix_count,"
                    "cur_vertex_index,cur_vertex_count,prev_vertex_index,prev_vertex_count,vertex_mode,texcoord_mode,tile_mode,decompose,"
                    "cur_position_hash,prev_position_hash,cur_texcoord_hash,prev_texcoord_hash,transform_valid,accepted,"
                    "current_already_mapped,previous_already_mapped\n");
                std::fflush(file);
            }

            return file;
        }();
        return traceFile;
    }

    static FILE *wr64WaterVelocityOutputTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *traceFile = []() -> FILE * {
            const char *enabled = std::getenv("WR64_WATER_VELOCITY_OUTPUT_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_WATER_VELOCITY_OUTPUT_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-water-velocity-output-trace.csv";
            }

            FILE *file = nullptr;
#ifdef _WIN32
            fopen_s(&file, path, "w");
#else
            file = std::fopen(path, "w");
#endif
            if (file != nullptr) {
                std::fprintf(file,
                    "submission_frame,cur_transform,prev_transform,vertex_count,"
                    "surface_height_matches,nonzero_y_velocities,position_velocity_written,"
                    "y_velocity_mean_abs,y_velocity_rms,y_velocity_max_abs,"
                    "cur_position_hash,prev_position_hash\n");
                std::fflush(file);
            }

            return file;
        }();
        return traceFile;
    }

    static FILE *wr64WaterAttributeTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *traceFile = []() -> FILE * {
            const char *enabled = std::getenv("WR64_WATER_ATTRIBUTE_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_WATER_ATTRIBUTE_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-water-attribute-trace.csv";
            }

            FILE *file = nullptr;
#ifdef _WIN32
            fopen_s(&file, path, "w");
#else
            file = std::fopen(path, "w");
#endif
            if (file != nullptr) {
                std::fprintf(file,
                    "submission_frame,stage,cur_workload,prev_workload,cur_call,prev_call,"
                    "cur_transform,prev_transform,cur_vertex_index,cur_vertex_count,prev_vertex_index,prev_vertex_count,"
                    "cur_normcol_hash,prev_normcol_hash,normcol_changed_bytes,normcol_changed_vertices,normcol_max_abs_byte_delta,"
                    "cur_geometry_mode,prev_geometry_mode,cur_tile,prev_tile,cur_texture,prev_texture,"
                    "cur_uls,cur_ult,cur_lrs,cur_lrt,prev_uls,prev_ult,prev_lrs,prev_lrt,"
                    "cur_sample_width,cur_sample_height,prev_sample_width,prev_sample_height,"
                    "cur_min_s,cur_min_t,cur_max_s,cur_max_t,prev_min_s,prev_min_t,prev_max_s,prev_max_t\n");
                std::fflush(file);
            }

            return file;
        }();
        return traceFile;
    }

    static FILE *wr64WaterCorrespondenceTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *traceFile = []() -> FILE * {
            const char *enabled = std::getenv("WR64_WATER_CORRESPONDENCE_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_WATER_CORRESPONDENCE_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-water-correspondence-trace.csv";
            }

            FILE *file = nullptr;
#ifdef _WIN32
            fopen_s(&file, path, "w");
#else
            file = std::fopen(path, "w");
#endif
            if (file != nullptr) {
                std::fprintf(file,
                    "submission_frame,stage,cur_workload,prev_workload,cur_call,prev_call,"
                    "cur_transform,prev_transform,cur_vertex_index,prev_vertex_index,vertex_count,"
                    "position_changed,position_nonfinite,position_min,position_avg,position_rms,position_max,"
                    "position_abs_x_max,position_abs_y_max,position_abs_z_max,"
                    "texcoord_changed,texcoord_nonfinite,texcoord_min,texcoord_avg,texcoord_rms,texcoord_max,"
                    "cur_face_start,prev_face_start,index_count,"
                    "cur_index_min,cur_index_max,prev_index_min,prev_index_max,cur_unique_indices,prev_unique_indices,"
                    "cur_raw_index_hash,prev_raw_index_hash,cur_normalized_index_hash,prev_normalized_index_hash,"
                    "normalized_topology_equal\n");
                std::fflush(file);
            }

            return file;
        }();
        return traceFile;
    }

    static FILE *wr64WaterCallIdentityTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *traceFile = []() -> FILE * {
            const char *enabled = std::getenv("WR64_WATER_CALL_IDENTITY_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_WATER_CALL_IDENTITY_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-water-call-identity-trace.csv";
            }

            FILE *file = nullptr;
#ifdef _WIN32
            fopen_s(&file, path, "w");
#else
            file = std::fopen(path, "w");
#endif
            if (file != nullptr) {
                std::fprintf(file,
                    "submission_frame,call_hash,prev_hash_candidates,"
                    "cur_workload,prev_workload,scene_projection,cur_call,prev_call,matrix_ordinal,"
                    "cur_transform,prev_transform,cur_vertex_index,prev_vertex_index,"
                    "cur_vertex_count,prev_vertex_count,cur_generated_count,prev_generated_count,"
                    "cur_source_min,cur_source_max,prev_source_min,prev_source_max,"
                    "cur_sequence_hash,prev_sequence_hash,cur_multiset_hash,prev_multiset_hash,"
                    "sequence_equal,multiset_equal,multiset_intersection,intersection_over_cur,"
                    "matrix_pair_eligible\n");
                std::fflush(file);
            }

            return file;
        }();
        return traceFile;
    }

    struct Wr64WaterSourceIdentity {
        bool validRange = false;
        uint32_t vertexIndex = 0;
        uint32_t vertexCount = 0;
        uint32_t generatedCount = 0;
        uint32_t sourceMin = 0;
        uint32_t sourceMax = 0;
        uint64_t sequenceHash = 0;
        uint64_t multisetHash = 0;
        std::vector<uint32_t> sequence;
        std::vector<uint32_t> sorted;
    };

    static Wr64WaterSourceIdentity wr64WaterSourceIdentity(const DrawData &drawData, uint32_t transformIndex) {
        Wr64WaterSourceIdentity identity;
        if ((transformIndex >= drawData.worldTransformVertexIndices.size()) ||
            (transformIndex >= drawData.worldTransformGroups.size())) {
            return identity;
        }

        identity.vertexIndex = drawData.worldTransformVertexIndices[transformIndex];
        identity.vertexCount = drawData.worldTransformVertexCount(transformIndex);
        const uint64_t vertexEnd = uint64_t(identity.vertexIndex) + identity.vertexCount;
        if (vertexEnd > drawData.vertexSegmentedAddresses.size()) {
            return identity;
        }

        identity.validRange = true;
        identity.sequence.reserve(identity.vertexCount);
        for (uint32_t i = 0; i < identity.vertexCount; i++) {
            const uint32_t sourceAddress = drawData.vertexSegmentedAddresses[identity.vertexIndex + i];
            if (isWr64GeneratedWaterVertexAddress(sourceAddress)) {
                identity.sequence.emplace_back(sourceAddress);
            }
        }

        identity.generatedCount = uint32_t(identity.sequence.size());
        if (!identity.sequence.empty()) {
            identity.sourceMin = *std::min_element(identity.sequence.begin(), identity.sequence.end());
            identity.sourceMax = *std::max_element(identity.sequence.begin(), identity.sequence.end());
            identity.sequenceHash = XXH3_64bits(identity.sequence.data(), identity.sequence.size() * sizeof(uint32_t));
            identity.sorted = identity.sequence;
            std::sort(identity.sorted.begin(), identity.sorted.end());
            identity.multisetHash = XXH3_64bits(identity.sorted.data(), identity.sorted.size() * sizeof(uint32_t));
        }

        return identity;
    }

    static uint32_t wr64WaterMultisetIntersection(
        const std::vector<uint32_t> &lhs,
        const std::vector<uint32_t> &rhs)
    {
        uint32_t intersection = 0;
        size_t lhsIndex = 0;
        size_t rhsIndex = 0;
        while ((lhsIndex < lhs.size()) && (rhsIndex < rhs.size())) {
            if (lhs[lhsIndex] < rhs[rhsIndex]) {
                lhsIndex++;
            }
            else if (rhs[rhsIndex] < lhs[lhsIndex]) {
                rhsIndex++;
            }
            else {
                intersection++;
                lhsIndex++;
                rhsIndex++;
            }
        }

        return intersection;
    }

    static FILE *&wr64WaterPassTraceFileStorage() {
        static FILE *traceFile = nullptr;
        return traceFile;
    }

    static FILE *wr64WaterPassTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        FILE *&traceFile = wr64WaterPassTraceFileStorage();
        if (traceFile != nullptr) {
            return traceFile;
        }

        const char *enabled = std::getenv("WR64_WATER_PASS_TRACE");
        if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
            return nullptr;
        }

        const char *path = std::getenv("WR64_WATER_PASS_TRACE_PATH");
        if ((path == nullptr) || (path[0] == '\0')) {
            path = "wr64-water-pass-trace.csv";
        }

#ifdef _WIN32
        fopen_s(&traceFile, path, "w");
#else
        traceFile = std::fopen(path, "w");
#endif
        if (traceFile != nullptr) {
            std::fprintf(traceFile,
                "submission_frame,workload,scene_projection,exact_call,sibling_call,call_hash,"
                "overlaps_exact_transform,min_transform,max_transform,triangle_count,combiner,other_mode,"
                "tile_count,texture0,texture1,texture2,texture3,generated_vertex_count,"
                "vertex_mode,texcoord_mode,tile_mode,mixed_transform_groups\n");
            std::fflush(traceFile);
        }

        return traceFile;
    }

    static void wr64CloseWaterPassTraceFile() {
        FILE *&traceFile = wr64WaterPassTraceFileStorage();
        if (traceFile != nullptr) {
            std::fclose(traceFile);
            traceFile = nullptr;
        }
    }

    static bool wr64WaterPassTraceTriggerConsumed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        const char *enabled = std::getenv("WR64_WATER_PASS_TRACE");
        if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
            return false;
        }

        const char *path = std::getenv("WR64_WATER_PASS_TRACE_TRIGGER_PATH");
        if ((path == nullptr) || (path[0] == '\0')) {
            return false;
        }

        FILE *triggerFile = nullptr;
#ifdef _WIN32
        fopen_s(&triggerFile, path, "rb");
#else
        triggerFile = std::fopen(path, "rb");
#endif
        if (triggerFile == nullptr) {
            return false;
        }

        std::fclose(triggerFile);
        std::remove(path);
        return true;
    }

    // ---------------------------------------------------------------------
    // Diagnostic-only: whole-frame vertex provenance census.
    //
    // Unlike the sibling-pass inventory, this walks every scene projection and
    // every draw call in the captured frame, and reports, per call, how many of
    // its indexed vertices originate from each runtime-generated water producer
    // bank. It never reads or writes interpolation state and never changes any
    // rendering behavior.
    // ---------------------------------------------------------------------

    static constexpr uint32_t Wr64WaterBankAStart = 0x03013D68U;
    static constexpr uint32_t Wr64WaterBankBStart = 0x030170D8U;
    static constexpr uint32_t Wr64WaterBankBEnd = 0x030185E8U;

    static FILE *&wr64WaterCensusFileStorage() {
        static FILE *censusFile = nullptr;
        return censusFile;
    }

    static FILE *wr64WaterCensusFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        FILE *&censusFile = wr64WaterCensusFileStorage();
        if (censusFile != nullptr) {
            return censusFile;
        }

        const char *enabled = std::getenv("WR64_WATER_PROVENANCE_CENSUS");
        if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
            return nullptr;
        }

        const char *path = std::getenv("WR64_WATER_PROVENANCE_CENSUS_PATH");
        if ((path == nullptr) || (path[0] == '\0')) {
            path = "wr64-water-provenance-census.csv";
        }

#ifdef _WIN32
        fopen_s(&censusFile, path, "w");
#else
        censusFile = std::fopen(path, "w");
#endif
        if (censusFile != nullptr) {
            std::fprintf(censusFile,
                "submission_frame,scene_kind,scene_ordinal,projection_count,scene_projection,call,call_count,"
                "triangle_count,combiner,other_mode,tile_count,texture0,texture1,texture2,texture3,"
                "min_transform,max_transform,vertex_mode,texcoord_mode,tile_mode,"
                "indexed_refs,distinct_vertices,source_min,source_max,segment3_count,"
                "generated_bank_a,generated_bank_b,generated_total,classifier_selected\n");
            std::fflush(censusFile);
        }

        return censusFile;
    }

    static void wr64CloseWaterCensusFile() {
        FILE *&censusFile = wr64WaterCensusFileStorage();
        if (censusFile != nullptr) {
            std::fclose(censusFile);
            censusFile = nullptr;
        }
    }

    static bool wr64WaterCensusTriggerConsumed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        const char *enabled = std::getenv("WR64_WATER_PROVENANCE_CENSUS");
        if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
            return false;
        }

        const char *path = std::getenv("WR64_WATER_PROVENANCE_CENSUS_TRIGGER_PATH");
        if ((path == nullptr) || (path[0] == '\0')) {
            return false;
        }

        FILE *triggerFile = nullptr;
#ifdef _WIN32
        fopen_s(&triggerFile, path, "rb");
#else
        triggerFile = std::fopen(path, "rb");
#endif
        if (triggerFile == nullptr) {
            return false;
        }

        std::fclose(triggerFile);
        std::remove(path);
        return true;
    }

    // The census is armed once for a whole native frame and stays armed across
    // every matched scene (perspective and orthographic) in that frame, so a
    // single capture covers the entire submitted frame rather than whichever
    // scene happened to be matched first.
    static bool &wr64WaterCensusActive() {
        thread_local bool active = false;
        return active;
    }

    static uint32_t &wr64WaterCensusSceneKind() {
        thread_local uint32_t sceneKind = 0;
        return sceneKind;
    }

    static uint32_t &wr64WaterCensusSceneOrdinal() {
        thread_local uint32_t sceneOrdinal = 0;
        return sceneOrdinal;
    }

    static uint64_t &wr64WaterCensusRowCount() {
        thread_local uint64_t rowCount = 0;
        return rowCount;
    }

    static void wr64WriteWaterProvenanceCensus(uint32_t projectionCount, uint32_t sceneProjIndex,
        const Workload &workload, const Projection &proj)
    {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        FILE *censusFile = wr64WaterCensusFile();
        if (censusFile == nullptr) {
            return;
        }

        const uint32_t sceneKind = wr64WaterCensusSceneKind();
        const uint32_t sceneOrdinal = wr64WaterCensusSceneOrdinal();
        const DrawData &drawData = workload.drawData;
        const bool addressesValid = (drawData.vertexSegmentedAddresses.size() == drawData.vertexCount());

        // Emit an explicit placeholder for empty projections so that a capture
        // which produces no draw calls is distinguishable from a capture that
        // never ran at all.
        if (proj.gameCallCount == 0) {
            std::fprintf(censusFile,
                "%llu,%u,%u,%u,%u,%u,%u,"
                "%u,%llu,%llu,%u,%llu,%llu,%llu,%llu,"
                "%u,%u,%u,%u,%u,%u,%u,%08X,%08X,%u,%u,%u,%u,%u\n",
                static_cast<unsigned long long>(workload.submissionFrame),
                sceneKind, sceneOrdinal, projectionCount, sceneProjIndex, 0u, 0u,
                0u, 0ULL, 0ULL, 0u, 0ULL, 0ULL, 0ULL, 0ULL,
                0u, 0u, 255u, 255u, 255u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u);
            wr64WaterCensusRowCount()++;
            std::fflush(censusFile);
            return;
        }

        thread_local std::set<uint32_t> distinctVertices;
        for (uint32_t c = 0; c < proj.gameCallCount; c++) {
            const GameCall &call = proj.gameCalls[c];
            const DrawCall &desc = call.callDesc;
            const uint64_t combiner = (uint64_t(desc.colorCombiner.L) << 32) | desc.colorCombiner.H;
            const uint64_t otherMode = (uint64_t(desc.otherMode.L) << 32) | desc.otherMode.H;
            uint64_t textures[4] = {};
            for (uint32_t t = 0; (t < desc.tileCount) && (t < 4); t++) {
                const uint32_t tileIndex = desc.tileIndex + t;
                if (tileIndex < drawData.callTiles.size()) {
                    textures[t] = drawData.callTiles[tileIndex].tmemHashOrID;
                }
            }

            uint8_t vertexMode = UINT8_MAX;
            uint8_t texcoordMode = UINT8_MAX;
            uint8_t tileMode = UINT8_MAX;
            for (uint32_t m = desc.minWorldMatrix; m <= desc.maxWorldMatrix; m++) {
                if (m >= drawData.worldTransformGroups.size()) {
                    continue;
                }

                const uint32_t groupIndex = drawData.worldTransformGroups[m];
                if (groupIndex >= drawData.transformGroups.size()) {
                    continue;
                }

                const TransformGroup &group = drawData.transformGroups[groupIndex];
                if (vertexMode == UINT8_MAX) {
                    vertexMode = group.vertexInterpolation;
                    texcoordMode = group.texcoordInterpolation;
                    tileMode = group.tileInterpolation;
                }
            }

            distinctVertices.clear();
            uint32_t indexedRefs = 0;
            uint32_t bankA = 0;
            uint32_t bankB = 0;
            uint32_t segment3 = 0;
            uint32_t sourceMin = UINT32_MAX;
            uint32_t sourceMax = 0;
            if (addressesValid) {
                const uint64_t faceIndicesStart = call.meshDesc.faceIndicesStart;
                const uint64_t faceIndicesEnd = faceIndicesStart + (uint64_t(desc.triangleCount) * 3ULL);
                if (faceIndicesEnd <= drawData.faceIndices.size()) {
                    for (uint64_t f = faceIndicesStart; f < faceIndicesEnd; f++) {
                        const uint32_t vertexIndex = drawData.faceIndices[size_t(f)];
                        if (vertexIndex >= drawData.vertexSegmentedAddresses.size()) {
                            continue;
                        }

                        indexedRefs++;
                        if (!distinctVertices.emplace(vertexIndex).second) {
                            continue;
                        }

                        const uint32_t sourceAddress = drawData.vertexSegmentedAddresses[vertexIndex];
                        sourceMin = std::min(sourceMin, sourceAddress);
                        sourceMax = std::max(sourceMax, sourceAddress);

                        // Course-independent: any vertex sourced from segment 3
                        // came from the per-frame graphics pool rather than from
                        // ROM-resident geometry, so this counts runtime-generated
                        // vertices without assuming Sunny Beach's pool offsets.
                        if ((sourceAddress >= 0x03000000U) && (sourceAddress < 0x04000000U)) {
                            segment3++;
                        }

                        if ((sourceAddress >= Wr64WaterBankAStart) && (sourceAddress < Wr64WaterBankBStart)) {
                            bankA++;
                        }
                        else if ((sourceAddress >= Wr64WaterBankBStart) && (sourceAddress < Wr64WaterBankBEnd)) {
                            bankB++;
                        }
                    }
                }
            }

            if (sourceMin == UINT32_MAX) {
                sourceMin = 0;
            }

            std::fprintf(censusFile,
                "%llu,%u,%u,%u,%u,%u,%u,%u,%llu,%llu,%u,%llu,%llu,%llu,%llu,"
                "%u,%u,%u,%u,%u,%u,%u,%08X,%08X,%u,%u,%u,%u,%u\n",
                static_cast<unsigned long long>(workload.submissionFrame),
                sceneKind, sceneOrdinal,
                projectionCount, sceneProjIndex, c, proj.gameCallCount,
                desc.triangleCount,
                static_cast<unsigned long long>(combiner),
                static_cast<unsigned long long>(otherMode),
                desc.tileCount,
                static_cast<unsigned long long>(textures[0]),
                static_cast<unsigned long long>(textures[1]),
                static_cast<unsigned long long>(textures[2]),
                static_cast<unsigned long long>(textures[3]),
                desc.minWorldMatrix, desc.maxWorldMatrix,
                uint32_t(vertexMode), uint32_t(texcoordMode), uint32_t(tileMode),
                indexedRefs, uint32_t(distinctVertices.size()),
                sourceMin, sourceMax, segment3,
                bankA, bankB, bankA + bankB,
                uint32_t(isWr64GeneratedWaterCall(drawData, call)));
            wr64WaterCensusRowCount()++;
        }

        std::fflush(censusFile);
    }

    static bool isWr64LateralDropletTexture(uint64_t textureHash) {
        return textureHash == Wr64LateralDropletTextureHash;
    }

    static bool isWr64SprayTexture(uint64_t textureHash) {
        switch (textureHash) {
        case Wr64LateralDropletTextureHash:
        case 8371292674920036242ULL:
        case 2052846331279025397ULL:
        case 18320119018424284810ULL:
        case 5140981042672958958ULL:
        case 17989038883639880583ULL:
        case 12686994568661451282ULL:
        case 13128825516206750571ULL:
        case 10644436609240083271ULL:
        case 17220844374676425630ULL:
        case 18241821034709948613ULL:
        case 8935117185641429257ULL:
            return true;
        default:
            return false;
        }
    }

    static bool isWr64CircularSprayTexture(uint64_t textureHash) {
        switch (textureHash) {
        case Wr64LateralDropletTextureHash:
        case 8371292674920036242ULL:
        case 2052846331279025397ULL:
        case 18320119018424284810ULL:
        case 5140981042672958958ULL:
        case 17989038883639880583ULL:
        case 12686994568661451282ULL:
        case 13128825516206750571ULL:
            return true;
        default:
            return false;
        }
    }

    static bool wr64HoldLateralDropletsAtNativeRate() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_LATERAL_DROPLET_NATIVE_HOLD");
            return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
        }();
        return enabled;
    }

    struct Wr64SprayPrimitive {
        const GameCall *call = nullptr;
        uint32_t callIndex = 0;
        uint32_t triangle = 0;
        uint32_t triangleCount = 1;
        bool circular = false;
        // Verified native spout vertex bank, not a matrix or draw-call index.
        uint32_t nativeWakeOwner = UINT32_MAX;
        uint64_t textureHash = 0;
        hlslpp::float3 localCenter = hlslpp::float3(0.0f, 0.0f, 0.0f);
        hlslpp::float3 worldCenter = hlslpp::float3(0.0f, 0.0f, 0.0f);
        uint32_t worldIndex = UINT32_MAX;
        bool mixedWorldIndices = false;
        uint32_t worldSegmentedAddress = 0;
        uint32_t worldPhysicalAddress = 0;
        uint32_t vertexIndices[3] = { UINT32_MAX, UINT32_MAX, UINT32_MAX };
    };

    struct Wr64NativeWakeRun {
        uint32_t firstTriangle;
        uint32_t triangleCount;
        uint32_t owner;
    };

    static bool collectWr64NativeWakeRuns(const DrawData &data, const GameCall &call,
        std::vector<Wr64NativeWakeRun> &runs)
    {
        runs.clear();
        // USA DrawSplash (800B3970..800B3988) loads 16 vertices per craft
        // from segment 5 + 0x91C0 + craft*0x100. SetVertex writes the same
        // four banks. The render state stays constant between craft loads,
        // so RT64 can merge several independent wakes into one GameCall.
        constexpr uint32_t BankStart = 0x050091C0U;
        constexpr uint32_t BankSize = 0x100U;
        constexpr uint32_t BankCount = 4U;
        const uint64_t first = call.meshDesc.faceIndicesStart;
        const uint64_t count = uint64_t(call.callDesc.triangleCount) * 3U;
        if ((count == 0) || (first + count > data.faceIndices.size())) {
            return false;
        }
        uint32_t ownersSeen = 0;
        for (uint32_t triangle = 0; triangle < call.callDesc.triangleCount; triangle++) {
            uint32_t owner = UINT32_MAX;
            for (uint32_t corner = 0; corner < 3; corner++) {
                const uint32_t vertex = data.faceIndices[size_t(first + triangle * 3ULL + corner)];
                if (vertex >= data.vertexSegmentedAddresses.size()) {
                    return false;
                }
                const uint32_t address = data.vertexSegmentedAddresses[vertex];
                if ((address < BankStart) || (address >= BankStart + BankSize * BankCount) ||
                    ((address - BankStart) % 16U != 0)) {
                    return false;
                }
                const uint32_t vertexOwner = (address - BankStart) / BankSize;
                if ((owner != UINT32_MAX) && (owner != vertexOwner)) {
                    return false;
                }
                owner = vertexOwner;
            }
            if (runs.empty() || (runs.back().owner != owner)) {
                // The native producer emits each craft once. Repeated owners
                // or triangles joining banks are outside this verified layout.
                if (ownersSeen & (1U << owner)) {
                    return false;
                }
                ownersSeen |= 1U << owner;
                runs.push_back({triangle, 1U, owner});
            }
            else {
                runs.back().triangleCount++;
            }
        }
        return true;
    }

    static bool wr64WakeMatricesEqual(const hlslpp::float4x4 &a, const hlslpp::float4x4 &b) {
        float av[16], bv[16];
        hlslpp::store(av, a);
        hlslpp::store(bv, b);
        for (uint32_t i = 0; i < 16; i++) {
            if (!std::isfinite(av[i]) || !std::isfinite(bv[i]) || (std::fabs(av[i] - bv[i]) > 0.00001f)) {
                return false;
            }
        }
        return true;
    }

    static bool wr64NativeWakeBasisSupported(const Wr64SprayPrimitive &current,
        const Wr64SprayPrimitive *previous, const DrawData &currentData,
        const DrawData &previousData, const GameFrameMap::WorkloadMap &map)
    {
        if (current.mixedWorldIndices || (current.worldIndex >= currentData.worldTransforms.size())) {
            return false;
        }
        // A local vertex delta is meaningful only in the previous basis that
        // RT64 will actually present. Index renumbering and duplicate equal
        // matrices are fine; matrix addresses alone do not prove equivalence.
        const auto *presentedPrevious = &currentData.worldTransforms[current.worldIndex];
        if ((current.worldIndex < map.transforms.size()) && map.transforms[current.worldIndex].mapped) {
            const uint32_t index = map.transforms[current.worldIndex].prevTransformIndex;
            if (index >= previousData.worldTransforms.size()) {
                return false;
            }
            presentedPrevious = &previousData.worldTransforms[index];
        }
        if (previous != nullptr) {
            return !previous->mixedWorldIndices &&
                (previous->worldIndex < previousData.worldTransforms.size()) &&
                wr64WakeMatricesEqual(*presentedPrevious, previousData.worldTransforms[previous->worldIndex]);
        }
        // Holding a birth's vertices cannot cancel motion from an unrelated
        // mapped matrix. Such ambiguous bases are left outside this override.
        return wr64WakeMatricesEqual(*presentedPrevious, currentData.worldTransforms[current.worldIndex]);
    }

    static bool isWr64LateralDropletPrimitive(const Wr64SprayPrimitive &primitive) {
        return isWr64LateralDropletTexture(primitive.textureHash);
    }

    static FILE *wr64SprayTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *traceFile = []() -> FILE * {
            const char *enabled = std::getenv("WR64_SPRAY_MATCH_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_SPRAY_MATCH_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-spray-match-trace.csv";
            }

            FILE *file = nullptr;
#ifdef _WIN32
            fopen_s(&file, path, "w");
#else
            file = std::fopen(path, "w");
#endif
            if (file != nullptr) {
                std::fprintf(file,
                    "sequence,cur_workload,prev_workload,fb_pair,projection,class,cur_primitive,cur_call,cur_triangle,cur_hash,"
                    "cur_x,cur_y,cur_z,prev_count,available_best,available_best_distance,available_second,available_second_distance,"
                    "nearest_any,nearest_any_distance,nearest_any_consumed,chosen_hash,chosen_call,chosen_triangle,prev_x,prev_y,prev_z,"
                    "velocity_x,velocity_y,velocity_z,accepted,"
                    "cur_local_x,cur_local_y,cur_local_z,cur_world_index,cur_mixed_world_indices,cur_world_segmented,cur_world_physical,"
                    "prev_local_x,prev_local_y,prev_local_z,prev_world_index,prev_mixed_world_indices,prev_world_segmented,prev_world_physical,"
                    "transform_mapped,transform_prev_world_index,transform_prev_segmented,transform_prev_physical,transform_matches_chosen_physical,"
                    "inherited_birth_velocity,cur_v0,cur_v1,cur_v2,prev_v0,prev_v1,prev_v2,cur_call_triangle_count,"
                    "native_wake_owner,native_wake_basis_supported\n");
                std::fflush(file);
            }

            return file;
        }();
        return traceFile;
    }

    static bool wr64SprayCenters(const DrawData &drawData, const GameCall &call,
                                 uint32_t firstTriangle, uint32_t triangleCount,
                                 hlslpp::float3 &localCenter, hlslpp::float3 &worldCenter,
                                 uint32_t &worldIndex, bool &mixedWorldIndices,
                                 uint32_t &worldSegmentedAddress, uint32_t &worldPhysicalAddress) {
        const uint32_t indexStart = call.meshDesc.faceIndicesStart + firstTriangle * 3;
        const uint32_t indexCount = triangleCount * 3;
        if ((indexCount == 0) || ((indexStart + indexCount) > drawData.faceIndices.size())) {
            return false;
        }

        localCenter = hlslpp::float3(0.0f, 0.0f, 0.0f);
        worldCenter = hlslpp::float3(0.0f, 0.0f, 0.0f);
        worldIndex = UINT32_MAX;
        mixedWorldIndices = false;
        worldSegmentedAddress = 0;
        worldPhysicalAddress = 0;
        for (uint32_t i = 0; i < indexCount; i++) {
            const uint32_t vertexIndex = drawData.faceIndices[indexStart + i];
            const uint32_t floatIndex = vertexIndex * 3;
            if (((floatIndex + 2) >= drawData.posFloats.size()) ||
                (vertexIndex >= drawData.worldIndices.size())) {
                return false;
            }

            const uint32_t vertexWorldIndex = drawData.worldIndices[vertexIndex];
            if (vertexWorldIndex >= drawData.worldTransforms.size()) {
                return false;
            }
            if (worldIndex == UINT32_MAX) {
                worldIndex = vertexWorldIndex;
            }
            else if (worldIndex != vertexWorldIndex) {
                mixedWorldIndices = true;
            }

            const hlslpp::float3 localPosition(drawData.posFloats[floatIndex],
                                               drawData.posFloats[floatIndex + 1],
                                               drawData.posFloats[floatIndex + 2]);
            const hlslpp::float4 transformedPosition = hlslpp::mul(
                hlslpp::float4(localPosition, 1.0f), drawData.worldTransforms[vertexWorldIndex]);
            localCenter += localPosition;
            worldCenter += transformedPosition.xyz / transformedPosition.w;
        }

        localCenter /= float(indexCount);
        worldCenter /= float(indexCount);
        if (worldIndex < drawData.worldTransformSegmentedAddresses.size()) {
            worldSegmentedAddress = drawData.worldTransformSegmentedAddresses[worldIndex];
        }
        if (worldIndex < drawData.worldTransformPhysicalAddresses.size()) {
            worldPhysicalAddress = drawData.worldTransformPhysicalAddresses[worldIndex];
        }
        return true;
    }

    static void collectWr64SprayPrimitives(const Workload &workload, const Projection &projection,
                                            std::vector<Wr64SprayPrimitive> &primitives) {
        primitives.clear();
        const DrawData &drawData = workload.drawData;
        for (uint32_t c = 0; c < projection.gameCallCount; c++) {
            const GameCall &call = projection.gameCalls[c];
            const DrawCall &desc = call.callDesc;
            if ((desc.tileCount == 0) || (desc.tileIndex >= drawData.callTiles.size())) {
                continue;
            }

            const uint64_t textureHash = drawData.callTiles[desc.tileIndex].tmemHashOrID;
            if (!isWr64SprayTexture(textureHash)) {
                continue;
            }

            const bool circular = isWr64CircularSprayTexture(textureHash);
            const bool lateralDroplets = isWr64LateralDropletTexture(textureHash);
            thread_local std::vector<Wr64NativeWakeRun> wakeRuns;
            if (!circular && collectWr64NativeWakeRuns(drawData, call, wakeRuns)) {
                for (const Wr64NativeWakeRun &run : wakeRuns) {
                    Wr64SprayPrimitive primitive;
                    primitive.call = &call;
                    primitive.callIndex = c;
                    primitive.triangle = run.firstTriangle;
                    primitive.triangleCount = run.triangleCount;
                    primitive.nativeWakeOwner = run.owner;
                    primitive.textureHash = textureHash;
                    if (wr64SprayCenters(drawData, call, primitive.triangle, primitive.triangleCount,
                        primitive.localCenter, primitive.worldCenter, primitive.worldIndex,
                        primitive.mixedWorldIndices, primitive.worldSegmentedAddress, primitive.worldPhysicalAddress)) {
                        primitives.emplace_back(primitive);
                    }
                }
                continue;
            }
            // Composer identifies this exact draw as a 64-triangle batch of small
            // airborne droplets. N64 billboard particles are emitted as adjacent
            // two-triangle quads, so keep both halves rigid under one match.
            const uint32_t primitiveTriangleCount = lateralDroplets ? 2U : (circular ? 1U : desc.triangleCount);
            const uint32_t primitiveCount = lateralDroplets ? (desc.triangleCount / 2U) : (circular ? desc.triangleCount : 1U);
            for (uint32_t primitiveIndex = 0; primitiveIndex < primitiveCount; primitiveIndex++) {
                Wr64SprayPrimitive primitive;
                primitive.call = &call;
                primitive.callIndex = c;
                primitive.triangle = lateralDroplets ? (primitiveIndex * 2U) : (circular ? primitiveIndex : 0U);
                primitive.triangleCount = primitiveTriangleCount;
                primitive.circular = circular;
                primitive.textureHash = textureHash;
                if (circular) {
                    const uint32_t indexStart = call.meshDesc.faceIndicesStart + primitive.triangle * 3;
                    if ((indexStart + 3) <= drawData.faceIndices.size()) {
                        primitive.vertexIndices[0] = drawData.faceIndices[indexStart];
                        primitive.vertexIndices[1] = drawData.faceIndices[indexStart + 1];
                        primitive.vertexIndices[2] = drawData.faceIndices[indexStart + 2];
                    }
                }
                if (wr64SprayCenters(drawData, call, primitive.triangle, primitive.triangleCount,
                                     primitive.localCenter, primitive.worldCenter,
                                     primitive.worldIndex, primitive.mixedWorldIndices,
                                     primitive.worldSegmentedAddress, primitive.worldPhysicalAddress)) {
                    primitives.emplace_back(primitive);
                }
            }
        }
    }

    static void matchWr64SprayPrimitives(const std::vector<Wr64SprayPrimitive> &curPrimitives,
                                          const std::vector<Wr64SprayPrimitive> &prevPrimitives,
                                          std::vector<int32_t> &curToPrev) {
        constexpr double MaximumDistanceSquared = 200.0 * 200.0;
        constexpr double UnmatchedCost = 1000000000.0;
        constexpr double ForbiddenCost = 1000000000000.0;

        const uint32_t curCount = uint32_t(curPrimitives.size());
        const uint32_t prevCount = uint32_t(prevPrimitives.size());
        const uint32_t assignmentSize = curCount + prevCount;
        curToPrev.assign(curCount, -1);
        if (assignmentSize == 0) {
            return;
        }

        auto assignmentCost = [&](uint32_t row, uint32_t column) -> double {
            if (row >= curCount) {
                return 0.0;
            }

            if (column >= prevCount) {
                return UnmatchedCost;
            }

            const Wr64SprayPrimitive &curPrimitive = curPrimitives[row];
            const Wr64SprayPrimitive &prevPrimitive = prevPrimitives[column];
            if (curPrimitive.circular != prevPrimitive.circular) {
                return ForbiddenCost;
            }
            if ((curPrimitive.nativeWakeOwner != prevPrimitive.nativeWakeOwner) &&
                ((curPrimitive.nativeWakeOwner != UINT32_MAX) || (prevPrimitive.nativeWakeOwner != UINT32_MAX))) {
                return ForbiddenCost;
            }
            const bool curLateralDroplet = isWr64LateralDropletPrimitive(curPrimitive);
            const bool prevLateralDroplet = isWr64LateralDropletPrimitive(prevPrimitive);
            if (curLateralDroplet != prevLateralDroplet) {
                return ForbiddenCost;
            }
            if (curLateralDroplet && (curPrimitive.textureHash != prevPrimitive.textureHash)) {
                return ForbiddenCost;
            }

            const hlslpp::float3 delta = curPrimitive.worldCenter - prevPrimitive.worldCenter;
            const double distanceSquared = double(static_cast<float>(hlslpp::dot(delta, delta).x));
            return (distanceSquared <= MaximumDistanceSquared) ? distanceSquared : ForbiddenCost;
        };

        // Solve the complete frame's one-to-one assignment at once. Dummy rows and
        // columns permit births/deaths while the large unmatched cost preserves every
        // eligible correspondence before minimizing its total world-space distance.
        std::vector<double> rowPotential(assignmentSize + 1, 0.0);
        std::vector<double> columnPotential(assignmentSize + 1, 0.0);
        std::vector<uint32_t> columnRow(assignmentSize + 1, 0);
        std::vector<uint32_t> previousColumn(assignmentSize + 1, 0);
        for (uint32_t row = 1; row <= assignmentSize; row++) {
            columnRow[0] = row;
            uint32_t column0 = 0;
            std::vector<double> minimumValue(assignmentSize + 1, std::numeric_limits<double>::infinity());
            std::vector<bool> used(assignmentSize + 1, false);
            do {
                used[column0] = true;
                const uint32_t row0 = columnRow[column0];
                double delta = std::numeric_limits<double>::infinity();
                uint32_t column1 = 0;
                for (uint32_t column = 1; column <= assignmentSize; column++) {
                    if (used[column]) {
                        continue;
                    }

                    const double reducedCost = assignmentCost(row0 - 1, column - 1) - rowPotential[row0] - columnPotential[column];
                    if (reducedCost < minimumValue[column]) {
                        minimumValue[column] = reducedCost;
                        previousColumn[column] = column0;
                    }

                    if (minimumValue[column] < delta) {
                        delta = minimumValue[column];
                        column1 = column;
                    }
                }

                for (uint32_t column = 0; column <= assignmentSize; column++) {
                    if (used[column]) {
                        rowPotential[columnRow[column]] += delta;
                        columnPotential[column] -= delta;
                    }
                    else {
                        minimumValue[column] -= delta;
                    }
                }

                column0 = column1;
            } while (columnRow[column0] != 0);

            do {
                const uint32_t column1 = previousColumn[column0];
                columnRow[column0] = columnRow[column1];
                column0 = column1;
            } while (column0 != 0);
        }

        for (uint32_t column = 1; column <= assignmentSize; column++) {
            const uint32_t row = columnRow[column];
            if ((row == 0) || (row > curCount) || (column > prevCount)) {
                continue;
            }

            const uint32_t curIndex = row - 1;
            const uint32_t prevIndex = column - 1;
            if (assignmentCost(curIndex, prevIndex) < UnmatchedCost) {
                curToPrev[curIndex] = int32_t(prevIndex);
            }
        }
    }

    static bool interpolateWr64SprayProjection(Workload &curWorkload, const Projection &curProjection,
                                                const Workload &prevWorkload, const Projection &prevProjection,
                                                const GameFrameMap::WorkloadMap &curWorkloadMap,
                                                uint32_t fbPairIndex, uint32_t projectionIndex) {
        thread_local std::vector<Wr64SprayPrimitive> curPrimitives;
        thread_local std::vector<Wr64SprayPrimitive> prevPrimitives;
        thread_local std::vector<int32_t> curToPrev;
        thread_local std::vector<int32_t> prevAssignedBy;
        collectWr64SprayPrimitives(curWorkload, curProjection, curPrimitives);
        collectWr64SprayPrimitives(prevWorkload, prevProjection, prevPrimitives);
        matchWr64SprayPrimitives(curPrimitives, prevPrimitives, curToPrev);

        // The global assignment deliberately preserves every eligible spray
        // correspondence, but particle births/deaths can occasionally force a long
        // assignment chain. Keep its coherent high-speed transport and reject only
        // circular matches which disagree sharply with the robust motion of the
        // complete projection cohort. Rejected matches are handled as births below
        // instead of drawing an interpolated path between unrelated particles.
        thread_local std::vector<float> circularMotionX;
        thread_local std::vector<float> circularMotionY;
        thread_local std::vector<float> circularMotionZ;
        circularMotionX.clear();
        circularMotionY.clear();
        circularMotionZ.clear();
        for (uint32_t curPrimitiveIndex = 0; curPrimitiveIndex < curToPrev.size(); curPrimitiveIndex++) {
            const int32_t prevPrimitiveIndex = curToPrev[curPrimitiveIndex];
            if ((prevPrimitiveIndex < 0) ||
                !curPrimitives[curPrimitiveIndex].circular ||
                isWr64LateralDropletPrimitive(curPrimitives[curPrimitiveIndex])) {
                continue;
            }

            const hlslpp::float3 worldMotion =
                curPrimitives[curPrimitiveIndex].worldCenter -
                prevPrimitives[uint32_t(prevPrimitiveIndex)].worldCenter;
            circularMotionX.emplace_back(worldMotion.x);
            circularMotionY.emplace_back(worldMotion.y);
            circularMotionZ.emplace_back(worldMotion.z);
        }

        constexpr size_t MinimumCircularMotionCohort = 8;
        if (circularMotionX.size() >= MinimumCircularMotionCohort) {
            const auto componentMedian = [](std::vector<float> &values) {
                const size_t middle = values.size() / 2;
                std::nth_element(values.begin(), values.begin() + middle, values.end());
                return values[middle];
            };
            const hlslpp::float3 circularMotionMedian(
                componentMedian(circularMotionX),
                componentMedian(circularMotionY),
                componentMedian(circularMotionZ));
            constexpr float MaximumCircularMotionResidualSquared = 80.0f * 80.0f;
            for (uint32_t curPrimitiveIndex = 0; curPrimitiveIndex < curToPrev.size(); curPrimitiveIndex++) {
                const int32_t prevPrimitiveIndex = curToPrev[curPrimitiveIndex];
                if ((prevPrimitiveIndex < 0) ||
                    !curPrimitives[curPrimitiveIndex].circular ||
                    isWr64LateralDropletPrimitive(curPrimitives[curPrimitiveIndex])) {
                    continue;
                }

                const hlslpp::float3 worldMotion =
                    curPrimitives[curPrimitiveIndex].worldCenter -
                    prevPrimitives[uint32_t(prevPrimitiveIndex)].worldCenter;
                const hlslpp::float3 residual = worldMotion - circularMotionMedian;
                if (hlslpp::dot(residual, residual).x > MaximumCircularMotionResidualSquared) {
                    curToPrev[curPrimitiveIndex] = -1;
                }
            }
        }

        prevAssignedBy.assign(prevPrimitives.size(), -1);
        for (uint32_t curPrimitiveIndex = 0; curPrimitiveIndex < curToPrev.size(); curPrimitiveIndex++) {
            if (curToPrev[curPrimitiveIndex] >= 0) {
                prevAssignedBy[uint32_t(curToPrev[curPrimitiveIndex])] = int32_t(curPrimitiveIndex);
            }
        }

        bool modified = false;
        DrawData &curData = curWorkload.drawData;
        static std::atomic<uint64_t> traceSequence = 0;
        FILE *traceFile = wr64SprayTraceFile();
        thread_local std::vector<float> sharedVelocityX;
        thread_local std::vector<float> sharedVelocityY;
        thread_local std::vector<float> sharedVelocityZ;
        thread_local std::vector<std::pair<float, hlslpp::float3>> nearbyBirthVelocities;
        for (uint32_t curPrimitiveIndex = 0; curPrimitiveIndex < curPrimitives.size(); curPrimitiveIndex++) {
            const Wr64SprayPrimitive &curPrimitive = curPrimitives[curPrimitiveIndex];
            if (wr64HoldLateralDropletsAtNativeRate() &&
                isWr64LateralDropletPrimitive(curPrimitive)) {
                // Native-rate presentation diagnostic: general RT64 matching has
                // already populated velocity for this workload. Explicitly erase it
                // here, at the final spray override, so the newest native position is
                // held continuously across intermediate presentation frames.
                const uint32_t indexStart =
                    curPrimitive.call->meshDesc.faceIndicesStart +
                    curPrimitive.triangle * 3;
                for (uint32_t i = 0; i < 3; i++) {
                    const uint32_t vertexIndex = curData.faceIndices[indexStart + i];
                    const uint32_t floatIndex = vertexIndex * 3;
                    if ((floatIndex + 2) >= curData.velFloats.size()) {
                        continue;
                    }

                    curData.velFloats[floatIndex] = 0.0f;
                    curData.velFloats[floatIndex + 1] = 0.0f;
                    curData.velFloats[floatIndex + 2] = 0.0f;
                    modified = true;
                }

                continue;
            }

            const uint32_t bestIndex = (curToPrev[curPrimitiveIndex] >= 0) ? uint32_t(curToPrev[curPrimitiveIndex]) : UINT32_MAX;
            float bestDistanceSquared = (bestIndex != UINT32_MAX) ? 0.0f : FLT_MAX;
            uint32_t secondIndex = UINT32_MAX;
            float secondDistanceSquared = FLT_MAX;
            uint32_t nearestAnyIndex = UINT32_MAX;
            float nearestAnyDistanceSquared = FLT_MAX;
            for (uint32_t i = 0; i < prevPrimitives.size(); i++) {
                const Wr64SprayPrimitive &prevPrimitive = prevPrimitives[i];
                if (curPrimitive.circular != prevPrimitive.circular) {
                    continue;
                }

                const hlslpp::float3 delta = curPrimitive.worldCenter - prevPrimitive.worldCenter;
                const float distanceSquared = hlslpp::dot(delta, delta).x;
                if (distanceSquared < nearestAnyDistanceSquared) {
                    nearestAnyDistanceSquared = distanceSquared;
                    nearestAnyIndex = i;
                }

                if (i == bestIndex) {
                    bestDistanceSquared = distanceSquared;
                }
                else if (distanceSquared < secondDistanceSquared) {
                    secondDistanceSquared = distanceSquared;
                    secondIndex = i;
                }
            }

            constexpr float MaximumDistanceSquared = 200.0f * 200.0f;
            const bool accepted = (bestIndex != UINT32_MAX) && (bestDistanceSquared <= MaximumDistanceSquared);
            hlslpp::float3 velocity = hlslpp::float3(0.0f, 0.0f, 0.0f);
            if (accepted) {
                velocity = curPrimitive.localCenter - prevPrimitives[bestIndex].localCenter;
            }

            const bool nativeWake = curPrimitive.nativeWakeOwner != UINT32_MAX;
            const bool nativeWakeBasisSupported = !nativeWake || wr64NativeWakeBasisSupported(
                curPrimitive, accepted ? &prevPrimitives[bestIndex] : nullptr,
                curData, prevWorkload.drawData, curWorkloadMap);

            bool inheritedBirthVelocity = false;
            if (!accepted && curPrimitive.circular &&
                !isWr64LateralDropletPrimitive(curPrimitive)) {
                sharedVelocityX.clear();
                sharedVelocityY.clear();
                sharedVelocityZ.clear();
                nearbyBirthVelocities.clear();
                for (uint32_t cohortIndex = 0; cohortIndex < curPrimitives.size(); cohortIndex++) {
                    const Wr64SprayPrimitive &cohortPrimitive = curPrimitives[cohortIndex];
                    if (!cohortPrimitive.circular ||
                        (cohortPrimitive.callIndex != curPrimitive.callIndex) ||
                        (cohortPrimitive.textureHash != curPrimitive.textureHash) ||
                        (curToPrev[cohortIndex] < 0)) {
                        continue;
                    }

                    const uint32_t cohortPrevIndex = uint32_t(curToPrev[cohortIndex]);
                    const hlslpp::float3 cohortWorldDelta =
                        cohortPrimitive.worldCenter - prevPrimitives[cohortPrevIndex].worldCenter;
                    if (hlslpp::dot(cohortWorldDelta, cohortWorldDelta).x > MaximumDistanceSquared) {
                        continue;
                    }

                    const hlslpp::float3 cohortVelocity =
                        cohortPrimitive.localCenter - prevPrimitives[cohortPrevIndex].localCenter;
                    const hlslpp::float3 birthDelta =
                        cohortPrimitive.worldCenter - curPrimitive.worldCenter;
                    const float birthDistanceSquared = hlslpp::dot(birthDelta, birthDelta).x;
                    constexpr float MaximumBirthNeighborDistanceSquared = 120.0f * 120.0f;
                    if (birthDistanceSquared <= MaximumBirthNeighborDistanceSquared) {
                        nearbyBirthVelocities.emplace_back(birthDistanceSquared, cohortVelocity);
                    }
                }

                std::sort(nearbyBirthVelocities.begin(), nearbyBirthVelocities.end(),
                    [](const auto &left, const auto &right) {
                        return left.first < right.first;
                    });
                constexpr size_t MaximumBirthNeighborCount = 7;
                const size_t birthNeighborCount =
                    std::min(nearbyBirthVelocities.size(), MaximumBirthNeighborCount);
                for (size_t neighborIndex = 0; neighborIndex < birthNeighborCount; neighborIndex++) {
                    const hlslpp::float3 &neighborVelocity = nearbyBirthVelocities[neighborIndex].second;
                    sharedVelocityX.emplace_back(neighborVelocity.x);
                    sharedVelocityY.emplace_back(neighborVelocity.y);
                    sharedVelocityZ.emplace_back(neighborVelocity.z);
                }

                constexpr size_t MinimumCohortSize = 3;
                if (sharedVelocityX.size() >= MinimumCohortSize) {
                    const auto componentMedian = [](std::vector<float> &values) {
                        std::sort(values.begin(), values.end());
                        const size_t middle = values.size() / 2;
                        if ((values.size() & 1U) != 0) {
                            return values[middle];
                        }

                        return (values[middle - 1] + values[middle]) * 0.5f;
                    };

                    velocity = hlslpp::float3(componentMedian(sharedVelocityX),
                                               componentMedian(sharedVelocityY),
                                               componentMedian(sharedVelocityZ));
                    inheritedBirthVelocity = true;
                }
            }

            if (traceFile != nullptr) {
                const Wr64SprayPrimitive *chosen = accepted ? &prevPrimitives[bestIndex] : nullptr;
                bool transformMapped = false;
                uint32_t transformPrevWorldIndex = UINT32_MAX;
                uint32_t transformPrevSegmentedAddress = 0;
                uint32_t transformPrevPhysicalAddress = 0;
                if (curPrimitive.worldIndex < curWorkloadMap.transforms.size()) {
                    const GameFrameMap::TransformMap &transformMap =
                        curWorkloadMap.transforms[curPrimitive.worldIndex];
                    transformMapped = transformMap.mapped;
                    if (transformMapped) {
                        transformPrevWorldIndex = transformMap.prevTransformIndex;
                        if (transformPrevWorldIndex < prevWorkload.drawData.worldTransformSegmentedAddresses.size()) {
                            transformPrevSegmentedAddress =
                                prevWorkload.drawData.worldTransformSegmentedAddresses[transformPrevWorldIndex];
                        }
                        if (transformPrevWorldIndex < prevWorkload.drawData.worldTransformPhysicalAddresses.size()) {
                            transformPrevPhysicalAddress =
                                prevWorkload.drawData.worldTransformPhysicalAddresses[transformPrevWorldIndex];
                        }
                    }
                }
                const bool transformMatchesChosenPhysical =
                    (chosen != nullptr) && transformMapped &&
                    (chosen->worldPhysicalAddress == transformPrevPhysicalAddress);
                const bool nearestAnyConsumed = (nearestAnyIndex != UINT32_MAX) &&
                    (prevAssignedBy[nearestAnyIndex] >= 0) &&
                    (uint32_t(prevAssignedBy[nearestAnyIndex]) != curPrimitiveIndex);
                const uint64_t sequence = traceSequence.fetch_add(1, std::memory_order_relaxed);
                std::fprintf(traceFile,
                    "%llu,%llu,%llu,%u,%u,%s,%u,%u,%u,%llu,%.6f,%.6f,%.6f,%zu,%d,%.6f,%d,%.6f,%d,%.6f,%u,"
                    "%llu,%d,%d,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%u,"
                    "%.6f,%.6f,%.6f,%u,%u,%u,%u,%.6f,%.6f,%.6f,%u,%u,%u,%u,"
                    "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
                    static_cast<unsigned long long>(sequence),
                    static_cast<unsigned long long>(curWorkload.workloadId),
                    static_cast<unsigned long long>(prevWorkload.workloadId),
                    fbPairIndex, projectionIndex, curPrimitive.circular ? "circular" : "elongated",
                    curPrimitiveIndex, curPrimitive.callIndex, curPrimitive.triangle,
                    static_cast<unsigned long long>(curPrimitive.textureHash),
                    static_cast<double>(static_cast<float>(curPrimitive.worldCenter.x)),
                    static_cast<double>(static_cast<float>(curPrimitive.worldCenter.y)),
                    static_cast<double>(static_cast<float>(curPrimitive.worldCenter.z)),
                    prevPrimitives.size(),
                    (bestIndex == UINT32_MAX) ? -1 : static_cast<int>(bestIndex),
                    (bestIndex == UINT32_MAX) ? -1.0f : std::sqrt(bestDistanceSquared),
                    (secondIndex == UINT32_MAX) ? -1 : static_cast<int>(secondIndex),
                    (secondIndex == UINT32_MAX) ? -1.0f : std::sqrt(secondDistanceSquared),
                    (nearestAnyIndex == UINT32_MAX) ? -1 : static_cast<int>(nearestAnyIndex),
                    (nearestAnyIndex == UINT32_MAX) ? -1.0f : std::sqrt(nearestAnyDistanceSquared),
                    nearestAnyConsumed ? 1U : 0U,
                    (chosen == nullptr) ? 0ULL : static_cast<unsigned long long>(chosen->textureHash),
                    (chosen == nullptr) ? -1 : static_cast<int>(chosen->callIndex),
                    (chosen == nullptr) ? -1 : static_cast<int>(chosen->triangle),
                    (chosen == nullptr) ? 0.0 : static_cast<double>(static_cast<float>(chosen->worldCenter.x)),
                    (chosen == nullptr) ? 0.0 : static_cast<double>(static_cast<float>(chosen->worldCenter.y)),
                    (chosen == nullptr) ? 0.0 : static_cast<double>(static_cast<float>(chosen->worldCenter.z)),
                    static_cast<double>(static_cast<float>(velocity.x)),
                    static_cast<double>(static_cast<float>(velocity.y)),
                    static_cast<double>(static_cast<float>(velocity.z)), accepted ? 1U : 0U,
                    static_cast<double>(static_cast<float>(curPrimitive.localCenter.x)),
                    static_cast<double>(static_cast<float>(curPrimitive.localCenter.y)),
                    static_cast<double>(static_cast<float>(curPrimitive.localCenter.z)),
                    curPrimitive.worldIndex, curPrimitive.mixedWorldIndices ? 1U : 0U,
                    curPrimitive.worldSegmentedAddress, curPrimitive.worldPhysicalAddress,
                    (chosen == nullptr) ? 0.0 : static_cast<double>(static_cast<float>(chosen->localCenter.x)),
                    (chosen == nullptr) ? 0.0 : static_cast<double>(static_cast<float>(chosen->localCenter.y)),
                    (chosen == nullptr) ? 0.0 : static_cast<double>(static_cast<float>(chosen->localCenter.z)),
                    (chosen == nullptr) ? UINT32_MAX : chosen->worldIndex,
                    ((chosen != nullptr) && chosen->mixedWorldIndices) ? 1U : 0U,
                    (chosen == nullptr) ? 0U : chosen->worldSegmentedAddress,
                    (chosen == nullptr) ? 0U : chosen->worldPhysicalAddress,
                    transformMapped ? 1U : 0U,
                    transformPrevWorldIndex,
                    transformPrevSegmentedAddress,
                    transformPrevPhysicalAddress,
                    transformMatchesChosenPhysical ? 1U : 0U,
                    inheritedBirthVelocity ? 1U : 0U,
                    curPrimitive.vertexIndices[0],
                    curPrimitive.vertexIndices[1],
                    curPrimitive.vertexIndices[2],
                    (chosen == nullptr) ? UINT32_MAX : chosen->vertexIndices[0],
                    (chosen == nullptr) ? UINT32_MAX : chosen->vertexIndices[1],
                    (chosen == nullptr) ? UINT32_MAX : chosen->vertexIndices[2],
                    curPrimitive.call->callDesc.triangleCount,
                    curPrimitive.nativeWakeOwner,
                    nativeWakeBasisSupported ? 1U : 0U);
                if ((sequence & 0xFFULL) == 0) {
                    std::fflush(traceFile);
                }
            }

            if (nativeWake && !nativeWakeBasisSupported) {
                // Do not claim that clearing vertex motion repairs a wrong
                // shared matrix mapping; optional trace records this ambiguity.
                continue;
            }
            const bool holdUnmatchedPrimitive = !accepted &&
                (isWr64LateralDropletPrimitive(curPrimitive) || nativeWake);
            if (!accepted && !inheritedBirthVelocity && !holdUnmatchedPrimitive) {
                continue;
            }

            const uint32_t indexStart = curPrimitive.call->meshDesc.faceIndicesStart + curPrimitive.triangle * 3;
            for (uint32_t i = 0; i < curPrimitive.triangleCount * 3; i++) {
                const uint32_t vertexIndex = curData.faceIndices[indexStart + i];
                const uint32_t floatIndex = vertexIndex * 3;
                if ((floatIndex + 2) >= curData.velFloats.size()) {
                    continue;
                }

                curData.velFloats[floatIndex] = velocity.x;
                curData.velFloats[floatIndex + 1] = velocity.y;
                curData.velFloats[floatIndex + 2] = velocity.z;
                modified = true;
            }
        }

        return modified;
    }

    static bool interpolateWr64Spray(Workload &curWorkload, const Workload &prevWorkload,
                                     const GameFrameMap::WorkloadMap &curWorkloadMap) {
        bool modified = false;
        const uint32_t fbPairCount = std::min(curWorkload.fbPairCount, prevWorkload.fbPairCount);
        for (uint32_t f = 0; f < fbPairCount; f++) {
            const FramebufferPair &curFbPair = curWorkload.fbPairs[f];
            const FramebufferPair &prevFbPair = prevWorkload.fbPairs[f];
            const uint32_t projectionCount = std::min(curFbPair.projectionCount, prevFbPair.projectionCount);
            for (uint32_t p = 0; p < projectionCount; p++) {
                modified |= interpolateWr64SprayProjection(curWorkload, curFbPair.projections[p],
                                                           prevWorkload, prevFbPair.projections[p],
                                                           curWorkloadMap, f, p);
            }
        }

        return modified;
    }

    bool GameFrame::areFramebufferPairsCompatible(const WorkloadQueue &workloadQueue, const GameIndices::FramebufferPair &first, const GameIndices::FramebufferPair &second) {
        if (first == second) {
            return true;
        }

        const Workload &firstWorkload = workloadQueue.workloads[first.workloadIndex];
        const Workload &secondWorkload = workloadQueue.workloads[second.workloadIndex];
        const auto &firstFbPair = firstWorkload.fbPairs[first.fbPairIndex];
        const auto &secondFbPair = secondWorkload.fbPairs[second.fbPairIndex];
        if ((firstFbPair.depthRead || firstFbPair.depthWrite) && (secondFbPair.depthRead || secondFbPair.depthWrite)) {
            if (firstFbPair.depthImage.address != secondFbPair.depthImage.address) {
                return false;
            }
        }

        const auto &firstColorImage = firstFbPair.colorImage;
        const auto &secondColorImage = secondFbPair.colorImage;
        if ((firstColorImage.address != secondColorImage.address) ||
            (firstColorImage.fmt != secondColorImage.fmt) ||
            (firstColorImage.siz != secondColorImage.siz) ||
            (firstColorImage.width != secondColorImage.width))
        {
            return false;
        }

        return true;
    }

    bool GameFrame::isSceneCompatible(const WorkloadQueue &workloadQueue, const GameScene &scene, const GameIndices::Projection &proj) {
        assert(!scene.projections.empty());

        const float MatrixDiffTolerance = 1e-6f;
        const Workload &workload = workloadQueue.workloads[proj.workloadIndex];
        const FramebufferPair &fbPair = workload.fbPairs[proj.fbPairIndex];
        const Projection &fbProj = fbPair.projections[proj.projectionIndex];
        const GameIndices::Projection &firstProj = scene.projections.front();
        if (!areFramebufferPairsCompatible(workloadQueue, { firstProj.workloadIndex, firstProj.fbPairIndex }, { proj.workloadIndex, proj.fbPairIndex })) {
            return false;
        }

        const Workload &cmpWorkload = workloadQueue.workloads[firstProj.workloadIndex];
        const FramebufferPair &cmpFbPair = cmpWorkload.fbPairs[firstProj.fbPairIndex];
        const Projection &cmpProj = cmpFbPair.projections[firstProj.projectionIndex];
        const interop::float4x4 &cmpViewMatrix = cmpWorkload.drawData.viewTransforms[cmpProj.transformsIndex];
        const interop::float4x4 &fbViewMatrix = workload.drawData.viewTransforms[fbProj.transformsIndex];
        const float viewMatrixDiff = matrixDifference(cmpViewMatrix, fbViewMatrix);
        if (viewMatrixDiff > MatrixDiffTolerance) {
            return false;
        }

        const interop::float4x4 &cmpProjMatrix = cmpWorkload.drawData.projTransforms[cmpProj.transformsIndex];
        const interop::float4x4 &fbProjMatrix = workload.drawData.projTransforms[fbProj.transformsIndex];
        const float projMatrixDiff = matrixDifference(cmpProjMatrix, fbProjMatrix);
        if (projMatrixDiff > MatrixDiffTolerance) {
            return false;
        }

        return true;
    }

    void GameFrame::set(WorkloadQueue &workloadQueue, const uint32_t *workloadIndices, uint32_t indicesCount) {
        assert(workloadIndices != nullptr);
        assert(indicesCount > 0);

        matched = false;
        perspectiveScenes.clear();
        orthographicScenes.clear();
        workloads.clear();
        workloads.insert(workloads.end(), workloadIndices, workloadIndices + indicesCount);

        auto addProjection = [&](const WorkloadQueue &workloadQueue, const GameIndices::Projection &newProj, std::vector<GameScene> &gameScenes) {
            bool added = false;
            for (auto &gameScene : gameScenes) {
                if (isSceneCompatible(workloadQueue, gameScene, newProj)) {
                    gameScene.projections.emplace_back(newProj);
                    added = true;
                    break;
                }
            }

            if (!added) {
                gameScenes.emplace_back(GameScene());
                gameScenes.back().projections.emplace_back(newProj);
            }
        };

        for (uint32_t i = 0; i < indicesCount; i++) {
            uint32_t w = workloadIndices[i];
            const Workload &workload = workloadQueue.workloads[w];
            for (uint32_t f = 0; f < workload.fbPairCount; f++) {
                const FramebufferPair &fbPair = workload.fbPairs[f];
                for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                    const GameIndices::Projection newProj = { w, f, p };
                    const auto &fbPairProj = fbPair.projections[p];
                    switch (fbPairProj.type) {
                    case Projection::Type::Perspective:
                        addProjection(workloadQueue, newProj, perspectiveScenes);
                        break;
                    case Projection::Type::Orthographic:
                        addProjection(workloadQueue, newProj, orthographicScenes);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        // Use the default values for the preset scene.
        presetScene = PresetScene();

        /*
        // Use the settings from all enabled presets. Use the last one sorted by name enabled.
        // TODO: Figure out a way to skip the linear lookup on the map.
        for (const auto &it : sceneLibrary.presetMap) {
            if (!it.second.enabled) {
                continue;
            }

            gameFrame.presetScene = it.second;
        }
        */

        /*
        TODO: Must be per projection.
        if (presetScene.estimateAmbientLight && (lightManager.ambientSum > 0)) {
            hlslpp::float3 ambientLight = { 0.01f, 0.01f, 0.01f };
            ambientLight = lightManager.estimatedAmbientLight(gameFrame.presetScene.ambientLightIntensity);
            presetScene.ambientBaseColor = ambientLight;
            presetScene.ambientNoGIColor = ambientLight;
        }
        */

        for (const GameScene &scene : perspectiveScenes) {
            for (const GameIndices::Projection &projection : scene.projections) {
                Workload &workload = workloadQueue.workloads[projection.workloadIndex];
                FramebufferPair &fbPair = workload.fbPairs[projection.fbPairIndex];
                Projection &proj = fbPair.projections[projection.projectionIndex];

                // Add all the lights stored in the workload.
                for (const interop::PointLight &light : workload.pointLights) {
                    proj.addPointLight(light);
                }
            }
        }

        frameMap.clear();
        frameMap.workloads.resize(workloadQueue.workloads.size());
    }
    
    typedef std::pair<uint32_t, uint32_t> IndexPair;

    bool operator<(const IndexPair &lhs, const IndexPair &rhs) {
        return (lhs.first < rhs.first) || ((lhs.first == rhs.first) && lhs.second < rhs.second);
    }

    struct MatchCandidate {
        uint32_t curIndex = 0;
        uint32_t prevIndex = 0;
        float difference = FLT_MAX;

        // VIEWPORT-PAIR-R1. Only meaningful for scene candidates: whether both
        // scenes draw to the same scissor rect, i.e. whether they are the same
        // viewport. Defaults to true so transform candidates are unaffected.
        bool sameViewport = true;

        MatchCandidate(uint32_t curIndex, uint32_t prevIndex, float difference) {
            this->curIndex = curIndex;
            this->prevIndex = prevIndex;
            this->difference = difference;
        }

        MatchCandidate(uint32_t curIndex, uint32_t prevIndex, float difference, bool sameViewport) {
            this->curIndex = curIndex;
            this->prevIndex = prevIndex;
            this->difference = difference;
            this->sameViewport = sameViewport;
        }
    };

    bool operator<(const MatchCandidate &lhs, const MatchCandidate &rhs) {
        return lhs.difference < rhs.difference;
    }

    struct TransformMatchResult {
        float positionDifference = FLT_MAX;
        float orientationDifference = FLT_MAX;
        float screenSpaceDifference = FLT_MAX;
        bool valid = false;

        float computeDifference() const {
            if (!valid) {
                return FLT_MAX;
            }

            float totalDiff = 0.0f;

            const float PositionDiffScale = 1.0f;
            if (positionDifference < FLT_MAX) {
                totalDiff += positionDifference * PositionDiffScale;
            }

            const float OrientationDiffScale = 1.0f;
            if (orientationDifference < FLT_MAX) {
                totalDiff += orientationDifference * OrientationDiffScale;
            }

            const float ScreenSpaceDiffScale = 1.0f;
            if (screenSpaceDifference < FLT_MAX) {
                totalDiff += screenSpaceDifference * ScreenSpaceDiffScale;
            }

            return totalDiff;
        }
    };

    TransformMatchResult computeTransformMatch(const hlslpp::float4x4 &curTransform, const hlslpp::float4x4 &curViewProj, const hlslpp::float4x4 &prevTransform, const hlslpp::float4x4 &prevViewProj, const RigidBody *prevRigidBody) {
        TransformMatchResult matchResult;

        // Do not accept a match between these transforms if the determinant is different, which indicates they're mirrored from each other.
        const float m0det = hlslpp::determinant(extract3x3(prevTransform));
        const float m1det = hlslpp::determinant(extract3x3(curTransform));
        if ((m0det * m1det) < 0.0f) {
            return matchResult;
        }

        // Compute the difference between the translation components of the 4x4 matrices.
        const hlslpp::float3 curPos = curTransform[3].xyz;
        hlslpp::float3 prevPos = prevTransform[3].xyz;
        if (prevRigidBody != nullptr) {
            prevPos += prevRigidBody->linearVelocity;
        }

        matchResult.positionDifference = hlslpp::length(curPos - prevPos);

        // Compute the dot product difference between the normalized XYZ vectors of the 3x3 matrices.
        matchResult.orientationDifference =
            (1.0f - hlslpp::dot(hlslpp::normalize(curTransform[0].xyz), hlslpp::normalize(prevTransform[0].xyz))) +
            (1.0f - hlslpp::dot(hlslpp::normalize(curTransform[1].xyz), hlslpp::normalize(prevTransform[1].xyz))) +
            (1.0f - hlslpp::dot(hlslpp::normalize(curTransform[2].xyz), hlslpp::normalize(prevTransform[2].xyz)));

        // Compute the difference between the screen-space position of both transforms on their respective projections.
        hlslpp::float4 prevScreenPos = hlslpp::mul(prevTransform[3], prevViewProj);
        hlslpp::float4 curScreenPos = hlslpp::mul(curTransform[3], curViewProj);
        prevScreenPos = (fabs(prevScreenPos.w) < 1e-6f) ? prevScreenPos : prevScreenPos / prevScreenPos.w;
        curScreenPos = (fabs(curScreenPos.w) < 1e-6f) ? curScreenPos : curScreenPos / curScreenPos.w;
        matchResult.screenSpaceDifference = hlslpp::length(curScreenPos.xyz - prevScreenPos.xyz);
        
        matchResult.valid = true;
        return matchResult;
    }

    // GANTRY TRANSFORM IDENTITY. Default OFF - see rt64_wr64_gantry_anchor.h for the
    // measurement that led here and for why the matrix address is NOT the key.
    //
    // Runs immediately before buildTransformIdMap, which is the only window where
    // this works: the draws exist (so minWorldMatrix is filled) and the id map has
    // not been built yet.
    //
    // It NEVER mutates an existing TransformGroup. The default G_EX_ID_AUTO group is
    // shared by every transform in the workload, so writing a matrixId into it would
    // re-identify the entire scene. Instead it copies the transform's current group,
    // stamps the id on the copy, appends it, and repoints just that transform. A
    // transform the gantry table does not claim is left byte-identical.
    static void wr64GantryStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;
        // A SET of claimed transforms, not a transform->part map. The id is the rank
        // in this set, so it does not depend on which of the assembly's draws happen
        // to be present in a given frame - see rt64_wr64_gantry_anchor.h for the
        // measurement that forced this.
        thread_local std::set<uint32_t> wr64GantryClaimed;
        wr64GantryClaimed.clear();

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64GantryTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64GantryTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    if (!wr64GantryIdentityClaims(wr64GantryTexture, desc.triangleCount,
                            desc.colorCombiner.H, desc.colorCombiner.L,
                            desc.otherMode.H, desc.otherMode.L))
                    {
                        continue;
                    }

                    const uint32_t wr64GantryTransform = desc.minWorldMatrix;
                    if (wr64GantryTransform < drawData.worldTransformGroups.size()) {
                        wr64GantryClaimed.insert(wr64GantryTransform);
                    }
                }
            }
        }

        uint32_t wr64GantryRank = 0;
        for (const uint32_t wr64GantryTransform : wr64GantryClaimed) {
            const uint32_t wr64GantryOldGroup = drawData.worldTransformGroups[wr64GantryTransform];
            if (wr64GantryOldGroup >= drawData.transformGroups.size()) {
                wr64GantryRank++;
                continue;
            }

            // Copy, stamp the copy, append, repoint. The existing group is shared by
            // every transform in the workload and must never be written in place.
            TransformGroup wr64GantryGroup = drawData.transformGroups[wr64GantryOldGroup];
            wr64GantryGroup.matrixId = wr64GantryIdentityRankedId(wr64GantryRank);
            wr64GantryGroup.ordering = G_EX_ORDER_LINEAR;
            // The identity alone changed nothing visible, and this is why. Vertex
            // interpolation runs ONLY inside matchTransform - so before the identity
            // fix it could never run at all - and matchTransform gates it on
            // `vertexInterpolation != G_EX_COMPONENT_SKIP`. SKIP is the struct default
            // and nothing in a stock N64 ROM ever changes it, so the assembly's
            // vertices have always snapped at 20 Hz no matter how well its matrix
            // interpolated. Racer limbs get exactly this treatment already, through
            // makeWr64FinalMatrixGroup(matrixId, true) in rt64_rsp.cpp.
            //
            // The two are a pair: identity makes the transform match, this makes the
            // match do something. Neither is any use alone.
            // ...and the rest of the same recipe. Leaving position at AUTO left the
            // discontinuity gate in RigidBody::updateLinear free to veto, and the exit
            // is precisely the fast motion that gate is built to veto - so the one
            // moment that looks rough is the one moment interpolation was allowed to
            // be switched off. makeWr64FinalMatrixGroup forces every component for the
            // racer limbs for exactly this reason. Copy it whole rather than in parts.
            wr64GantryGroup.decompose = false;
            wr64GantryGroup.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64GantryGroup.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64GantryGroup.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64GantryGroup.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64GantryGroup.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64GantryGroup.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64GantryGroup.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;
            drawData.worldTransformGroups[wr64GantryTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64GantryGroup);
            wr64GantryRank++;
        }

        wr64GantryIdentityNote(wr64GantryClaimed.size());
    }

    // The tropical fish school. Same shape of pass as the gantry above and the
    // same three rules - walk before the id map is built, never mutate a shared
    // TransformGroup, apply the whole interpolation recipe - but the id itself is
    // derived differently, and rt64_wr64_fish_school.h has the measurement that
    // forced it.
    //
    // Eighteen near-identical two-triangle sprites. The matcher cannot tell one
    // clownfish from another, pairs the wrong ones, and produces a "velocity" that
    // is really the distance between two different fish. That is 88.1% of every
    // surviving lerp gate, and it is the camera stutter.
    //
    // The name is (which fish, which block, which of the three). Block, not a
    // running ordinal: when the game culls a whole triple - 23 frames out of 2,426
    // - it renumbers the survivors into a contiguous run, and a running ordinal
    // would promote the second triple into the first triple's ids and mispair 45
    // fish. Keeping the block index costs one comparison and was wrong 0 times in
    // 43,599 draws.
    static void wr64FishStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        // Ordered by transform index, which is the order the school is emitted in
        // and the order the block structure is expressed in. First draw wins, to
        // agree with the census this was measured from.
        thread_local std::map<uint32_t, int32_t> wr64FishClaimed;
        wr64FishClaimed.clear();
        Wr64AnimalReplayUses wr64FishReplayUses;

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64FishTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64FishTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    if (!wr64FishSchoolClaims(wr64FishTexture, desc.triangleCount,
                            desc.colorCombiner.H, desc.colorCombiner.L,
                            desc.otherMode.H, desc.otherMode.L))
                    {
                        continue;
                    }

                    const uint32_t wr64FishTransform = desc.minWorldMatrix;
                    if (wr64FishTransform < drawData.worldTransformGroups.size()) {
                        wr64FishClaimed.emplace(wr64FishTransform,
                            wr64FishSchoolSlot(wr64FishTexture));
                        wr64AnimalReplayRecord(wr64FishReplayUses, wr64FishTransform,
                            f, proj.scissorRect, desc, wr64FishTexture);
                    }
                }
            }
        }

        // Replaying one native animal draw for the second view does not create
        // another school. Remove only exact cross-viewport copies before numbering.
        const auto wr64FishReplayAliases = wr64AnimalReplayAliases(drawData, wr64FishReplayUses);
        for (const auto &alias : wr64FishReplayAliases) wr64FishClaimed.erase(alias.first);

        // The block rule. Within a block the textures ascend through the canonical
        // slot order, so a slot that does NOT ascend is a block boundary. A culled
        // triple leaves a slot that fails to ascend exactly where the boundary is,
        // which is why this recovers the right names from a short frame.
        uint32_t wr64FishGroup = 0;
        int32_t wr64FishLastSlot = -1;
        std::map<std::pair<int32_t, uint32_t>, uint32_t> wr64FishOrdinals;
        size_t wr64FishStamped = 0;
        size_t wr64FishSkipped = 0;
        size_t wr64FishSnapped = 0;

        // Where each ID was last seen. KEYED ON THE ID - the pass's own
        // identity - not the matrix address: the id is what buildTransformIdMap
        // pairs on, so the id's trajectory is the one whose discontinuities
        // sweep. Persistent across frames on purpose, exactly like the ducks'.
        struct Wr64FishSeen { uint64_t frame; float x, y, z; };
        thread_local std::unordered_map<uint32_t, Wr64FishSeen> wr64FishLastSeen;

        for (const auto &wr64FishEntry : wr64FishClaimed) {
            const uint32_t wr64FishTransform = wr64FishEntry.first;
            const int32_t wr64FishSlot = wr64FishEntry.second;
            if (wr64FishSlot < wr64FishLastSlot) {
                wr64FishGroup++;
            }
            wr64FishLastSlot = wr64FishSlot;

            const std::pair<int32_t, uint32_t> wr64FishKey(wr64FishSlot, wr64FishGroup);
            const uint32_t wr64FishOrdinal = wr64FishOrdinals[wr64FishKey]++;
            const uint32_t wr64FishId = wr64FishSchoolId(wr64FishSlot, wr64FishGroup, wr64FishOrdinal);
            if (wr64FishId == 0) {
                // Past the reserved id space. Leaving this one at G_EX_ID_AUTO puts
                // it back on the heuristic matcher, which is where it is today.
                // Wrapping it onto another fish's id would be actively worse.
                wr64FishSkipped++;
                continue;
            }

            const uint32_t wr64FishOldGroup = drawData.worldTransformGroups[wr64FishTransform];
            if (wr64FishOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            // THE CONTINUITY GUARD, added 2026-08-04 for Dolphin Park. This
            // pass shipped without one because Sunny Beach's id -> fish mapping
            // held on 100% of measured frames. Dolphin Park reassigns a slot's
            // occupant about once per tick somewhere in the school, the ordinal
            // keeps the id, and the matcher swept a fish to the newcomer's
            // position - the reported warping. Full numbers and the threshold
            // derivation are in rt64_wr64_fish_school.h.
            bool wr64FishJumped = false;
            if (wr64FishTransform < drawData.worldTransforms.size()) {
                const hlslpp::float4x4 &wr64FishM = drawData.worldTransforms[wr64FishTransform];
                const hlslpp::float3 wr64FishPos = wr64FishM[3].xyz;
                const float wr64FishX = float(wr64FishPos.x);
                const float wr64FishY = float(wr64FishPos.y);
                const float wr64FishZ = float(wr64FishPos.z);

                const auto wr64FishPrev = wr64FishLastSeen.find(wr64FishId);
                if (wr64FishPrev != wr64FishLastSeen.end()) {
                    const uint64_t wr64FishAge =
                        (workload.submissionFrame > wr64FishPrev->second.frame)
                            ? (workload.submissionFrame - wr64FishPrev->second.frame)
                            : 0;
                    if (wr64FishAge > 0) {
                        const float dx = wr64FishX - wr64FishPrev->second.x;
                        const float dy = wr64FishY - wr64FishPrev->second.y;
                        const float dz = wr64FishZ - wr64FishPrev->second.z;
                        const float wr64FishStep =
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                        wr64FishJumped = (wr64FishStep > Wr64FishContinuityUnits);
                    }
                }

                wr64FishLastSeen[wr64FishId] = Wr64FishSeen{
                    workload.submissionFrame, wr64FishX, wr64FishY, wr64FishZ };
            }

            // Copy, stamp the copy, append, repoint. The G_EX_ID_AUTO group is
            // shared by every transform in the workload; writing into it would
            // re-identify the whole scene.
            TransformGroup wr64FishTransformGroup = drawData.transformGroups[wr64FishOldGroup];
            wr64FishTransformGroup.matrixId = wr64FishId;
            wr64FishTransformGroup.ordering = G_EX_ORDER_LINEAR;
            // The whole makeWr64FinalMatrixGroup recipe, applied whole. Stamping an
            // id while leaving decompose on, or leaving one component on AUTO, is
            // what made the first gantry attempt change nothing byte for byte.
            wr64FishTransformGroup.decompose = false;
            wr64FishTransformGroup.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64FishTransformGroup.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64FishTransformGroup.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64FishTransformGroup.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64FishTransformGroup.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64FishTransformGroup.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64FishTransformGroup.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;

            // The reassignment frame keeps its name and loses its sweep. Vertex
            // and tile interpolation stay ON even here: the fish's own swim
            // animation is continuous across a reassignment, it is only the
            // placement that teleports - the same rule as the ducks' re-slot.
            if (wr64FishJumped) {
                wr64FishTransformGroup.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64FishTransformGroup.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64FishTransformGroup.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64FishTransformGroup.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64FishTransformGroup.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                wr64FishSnapped++;
            }

            drawData.worldTransformGroups[wr64FishTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64FishTransformGroup);
            wr64FishStamped++;
        }

        wr64AnimalReplayCopyGroups(drawData, wr64FishReplayAliases, wr64FishSchoolIsOurs);
        wr64FishSchoolNote(wr64FishStamped,
            wr64FishClaimed.empty() ? size_t(0) : size_t(wr64FishGroup) + 1,
            wr64FishSkipped, wr64FishSnapped);
    }

    // SEAGULL R4: THE TRAJECTORY IS THE BIRD. The R3 capture proved the
    // flock is 35 persistent birds whose matrix slots are RE-DEALT when the
    // visible roster changes - rank (R1) and address (R3) both churn with
    // the deal. What survives is the path: replaying the capture, nearest-
    // neighbour matching against a persistent registry kept all 35 names
    // through every churn with zero losses (largest true step 67 units;
    // radius 120/frame of absence). Full account and the kind split in
    // rt64_wr64_sprite_families.h.
    //
    // A remembered bird the game did not draw this frame is carried as a
    // GHOST: its last matrix is appended as a transform no draw references,
    // stamped with its id, so the id stays in the pairing map and a
    // returning bird pairs with its own last position and glides in - the
    // one-tick freeze on every return was the visible stepping. Ghosts set
    // vertex and texcoord interpolation to SKIP: they have a zero-length
    // vertex range, and the vertex-hash path must never look at it.
    static void wr64SeagullAssignTransformIdentity(Workload &workload,
        const std::set<uint32_t> &claimed, const std::map<uint32_t, uint8_t> &kinds)
    {
        DrawData &drawData = workload.drawData;

        struct Wr64SeagullEntry {
            uint32_t id;
            uint8_t kind;               // 1 = far sprite, 2 = near model
            interop::float4x4 matrix;   // last real matrix, the ghost's body
            float x, y, z;
            uint64_t frame;             // last frame the real bird was seen
        };
        thread_local std::vector<Wr64SeagullEntry> wr64SeagullRegistry;
        thread_local uint32_t wr64SeagullNextSerial = 0;

        struct Wr64SeagullBirdRef { uint32_t transform; uint8_t kind; float x, y, z; };
        std::vector<Wr64SeagullBirdRef> wr64SeagullBirds;
        wr64SeagullBirds.reserve(claimed.size());
        for (const uint32_t wr64SeagullTransform : claimed) {
            if ((wr64SeagullTransform >= drawData.worldTransforms.size()) ||
                (wr64SeagullTransform >= drawData.worldTransformGroups.size()))
            {
                continue;
            }

            // Far sprite only if the transform carried nothing but the far
            // texture; a mixed transform (never observed) counts as near.
            uint8_t wr64SeagullKind = 2;
            const auto wr64SeagullKindIt = kinds.find(wr64SeagullTransform);
            if ((wr64SeagullKindIt != kinds.end()) && (wr64SeagullKindIt->second == 1)) {
                wr64SeagullKind = 1;
            }

            const hlslpp::float4x4 &wr64SeagullM = drawData.worldTransforms[wr64SeagullTransform];
            const hlslpp::float3 wr64SeagullPos = wr64SeagullM[3].xyz;
            wr64SeagullBirds.push_back(Wr64SeagullBirdRef{ wr64SeagullTransform, wr64SeagullKind,
                float(wr64SeagullPos.x), float(wr64SeagullPos.y), float(wr64SeagullPos.z) });
        }

        // Every (bird, remembered bird) pair of one kind within the age-scaled
        // radius, matched greedily by ascending distance. ~35 birds against
        // ~35 entries; the loop is trivial.
        struct Wr64SeagullCandidate { float dist; uint32_t bird; uint32_t entry; };
        std::vector<Wr64SeagullCandidate> wr64SeagullCandidates;
        for (uint32_t b = 0; b < wr64SeagullBirds.size(); b++) {
            for (uint32_t e = 0; e < wr64SeagullRegistry.size(); e++) {
                const Wr64SeagullEntry &wr64SeagullEntry = wr64SeagullRegistry[e];
                if (wr64SeagullEntry.kind != wr64SeagullBirds[b].kind) {
                    continue;
                }
                if (wr64SeagullEntry.frame >= workload.submissionFrame) {
                    // Fed this frame already (a second workload in one frame):
                    // not a candidate, and not a ghost either.
                    continue;
                }
                const uint64_t wr64SeagullAge = workload.submissionFrame - wr64SeagullEntry.frame;
                if (wr64SeagullAge > Wr64SeagullCarryFrames) {
                    continue;
                }
                const float wr64SeagullRadius =
                    Wr64SeagullHandoffUnitsPerFrame * float(wr64SeagullAge);
                const float dx = wr64SeagullBirds[b].x - wr64SeagullEntry.x;
                const float dy = wr64SeagullBirds[b].y - wr64SeagullEntry.y;
                const float dz = wr64SeagullBirds[b].z - wr64SeagullEntry.z;
                const float wr64SeagullDist = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                if (wr64SeagullDist <= wr64SeagullRadius) {
                    wr64SeagullCandidates.push_back(Wr64SeagullCandidate{ wr64SeagullDist, b, e });
                }
            }
        }
        std::sort(wr64SeagullCandidates.begin(), wr64SeagullCandidates.end(),
            [](const Wr64SeagullCandidate &a, const Wr64SeagullCandidate &b) {
                return a.dist < b.dist;
            });

        std::vector<uint32_t> wr64SeagullBirdEntry(wr64SeagullBirds.size(), UINT32_MAX);
        std::vector<uint8_t> wr64SeagullEntryTaken(wr64SeagullRegistry.size(), 0);
        for (const Wr64SeagullCandidate &c : wr64SeagullCandidates) {
            if ((wr64SeagullBirdEntry[c.bird] != UINT32_MAX) || wr64SeagullEntryTaken[c.entry]) {
                continue;
            }
            wr64SeagullBirdEntry[c.bird] = c.entry;
            wr64SeagullEntryTaken[c.entry] = 1;
        }

        size_t wr64SeagullStamped = 0;
        for (uint32_t b = 0; b < wr64SeagullBirds.size(); b++) {
            uint32_t wr64SeagullId = 0;
            if (wr64SeagullBirdEntry[b] != UINT32_MAX) {
                Wr64SeagullEntry &wr64SeagullEntry = wr64SeagullRegistry[wr64SeagullBirdEntry[b]];
                wr64SeagullId = wr64SeagullEntry.id;
                wr64SeagullEntry.matrix = drawData.worldTransforms[wr64SeagullBirds[b].transform];
                wr64SeagullEntry.x = wr64SeagullBirds[b].x;
                wr64SeagullEntry.y = wr64SeagullBirds[b].y;
                wr64SeagullEntry.z = wr64SeagullBirds[b].z;
                wr64SeagullEntry.frame = workload.submissionFrame;
            }
            else {
                // Nothing in reach: a genuine spawn. Its first tick has no
                // previous frame to pair with, which is what a spawn looks
                // like; minting a name is the honest move, not a failure.
                wr64SeagullId = wr64SeagullSerialId(wr64SeagullNextSerial++);
                Wr64SeagullEntry wr64SeagullEntry;
                wr64SeagullEntry.id = wr64SeagullId;
                wr64SeagullEntry.kind = wr64SeagullBirds[b].kind;
                wr64SeagullEntry.matrix = drawData.worldTransforms[wr64SeagullBirds[b].transform];
                wr64SeagullEntry.x = wr64SeagullBirds[b].x;
                wr64SeagullEntry.y = wr64SeagullBirds[b].y;
                wr64SeagullEntry.z = wr64SeagullBirds[b].z;
                wr64SeagullEntry.frame = workload.submissionFrame;
                wr64SeagullRegistry.push_back(wr64SeagullEntry);
            }

            const uint32_t wr64SeagullOldGroup =
                drawData.worldTransformGroups[wr64SeagullBirds[b].transform];
            if (wr64SeagullOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            // Copy, stamp the copy, append, repoint - and the WHOLE recipe,
            // exactly like every pass above. No SKIP path: a matched bird is
            // within the radius by construction, and a minted bird has no
            // previous frame for the matcher to sweep it from.
            TransformGroup wr64SeagullGroup = drawData.transformGroups[wr64SeagullOldGroup];
            wr64SeagullGroup.matrixId = wr64SeagullId;
            wr64SeagullGroup.ordering = G_EX_ORDER_LINEAR;
            wr64SeagullGroup.decompose = false;
            wr64SeagullGroup.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGroup.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGroup.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGroup.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGroup.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGroup.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGroup.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;
            drawData.worldTransformGroups[wr64SeagullBirds[b].transform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64SeagullGroup);
            wr64SeagullStamped++;
        }

        // THE GHOST CARRY, and retirement. An entry fed this frame is kept;
        // one missing for longer than the window retires; the rest are
        // carried: the last matrix is appended as a transform NO DRAW
        // references, so the id stays in this frame's pairing map. The
        // ghost's vertex range is empty (worldTransformVertexIndices gets
        // vertexCount(), so the count comes out zero) and its vertex and
        // texcoord interpolation are SKIP, so the vertex-hash path never
        // dereferences the empty range.
        std::vector<Wr64SeagullEntry> wr64SeagullKept;
        wr64SeagullKept.reserve(wr64SeagullRegistry.size());
        for (const Wr64SeagullEntry &wr64SeagullEntry : wr64SeagullRegistry) {
            if (wr64SeagullEntry.frame >= workload.submissionFrame) {
                wr64SeagullKept.push_back(wr64SeagullEntry);
                continue;
            }
            const uint64_t wr64SeagullAge = workload.submissionFrame - wr64SeagullEntry.frame;
            if (wr64SeagullAge > Wr64SeagullCarryFrames) {
                continue;
            }

            drawData.worldTransforms.push_back(wr64SeagullEntry.matrix);
            TransformGroup wr64SeagullGhost;
            wr64SeagullGhost.matrixId = wr64SeagullEntry.id;
            wr64SeagullGhost.ordering = G_EX_ORDER_LINEAR;
            wr64SeagullGhost.decompose = false;
            wr64SeagullGhost.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGhost.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGhost.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGhost.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGhost.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGhost.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64SeagullGhost.vertexInterpolation = G_EX_COMPONENT_SKIP;
            wr64SeagullGhost.texcoordInterpolation = G_EX_COMPONENT_SKIP;
            drawData.worldTransformGroups.push_back(uint32_t(drawData.transformGroups.size()));
            drawData.transformGroups.emplace_back(wr64SeagullGhost);
            drawData.worldTransformSegmentedAddresses.push_back(0);
            drawData.worldTransformPhysicalAddresses.push_back(0);
            drawData.worldTransformVertexIndices.push_back(drawData.vertexCount());
            wr64SeagullKept.push_back(wr64SeagullEntry);
        }
        wr64SeagullRegistry.swap(wr64SeagullKept);

        wr64SpriteFamilyNote(uint32_t(Wr64FamilySeagulls), wr64SeagullStamped, 0, 0);
    }

    // Named scenery objects - the Port Blue helicopter, its newspaper sheet and
    // barrels, and the seagulls. Same pass shape as the gantry and the fish, and
    // rt64_wr64_sprite_families.h carries the measurement that decided WHICH
    // objects belong here and which were deliberately left out.
    //
    // The id is the rank among a family's claimed transforms. That is the
    // gantry's scheme: it needs no contiguity, and for a single-instance family
    // it is correct by construction because one claimed transform always ranks 0.
    //
    // Every family in the table was measured to keep its drawing order in at
    // least 99.5% of frames. The Sunset Bay dolphins (94.7%) and Drake Lake fish
    // (45.4%) are absent on purpose - see the header.
    static void wr64SpriteFamilyStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        // One set per family, ordered by transform index so the rank is stable.
        thread_local std::set<uint32_t> wr64SpriteClaimed[Wr64SpriteFamilyCount];
        for (uint32_t f = 0; f < uint32_t(Wr64SpriteFamilyCount); f++) {
            wr64SpriteClaimed[f].clear();
        }
        // R4: the seagull registry is split by kind (far sprite / near
        // model), decided by which textures claimed the transform: 1 means
        // only the far texture did, anything else is the near model.
        thread_local std::map<uint32_t, uint8_t> wr64SeagullKinds;
        wr64SeagullKinds.clear();
        Wr64AnimalReplayUses wr64SeagullReplayUses;

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64SpriteTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64SpriteTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    const int32_t wr64SpriteFamily = wr64SpriteFamilyClaim(wr64SpriteTexture,
                        desc.colorCombiner.H, desc.colorCombiner.L,
                        desc.otherMode.H, desc.otherMode.L);
                    if (wr64SpriteFamily < 0) {
                        continue;
                    }

                    const uint32_t wr64SpriteTransform = desc.minWorldMatrix;
                    if (wr64SpriteTransform < drawData.worldTransformGroups.size()) {
                        wr64SpriteClaimed[wr64SpriteFamily].insert(wr64SpriteTransform);
                        if (wr64SpriteFamily == int32_t(Wr64FamilySeagulls)) {
                            wr64SeagullKinds[wr64SpriteTransform] |=
                                (wr64SpriteTexture == Wr64SeagullFarTexture) ? uint8_t(1) : uint8_t(2);
                            wr64AnimalReplayRecord(wr64SeagullReplayUses, wr64SpriteTransform,
                                f, proj.scissorRect, desc, wr64SpriteTexture);
                        }
                    }
                }
            }
        }

        // Ranked sprite IDs can be reassigned when the claimed set changes. Track
        // continuity by ID, which is also the key used by buildTransformIdMap, and
        // skip smoothing across reassignment. Keep the history across frames; see
        // rt64_wr64_sprite_families.h for the threshold derivation.
        struct Wr64SpriteSeen { uint64_t frame; float x, y, z; };
        thread_local std::unordered_map<uint32_t, Wr64SpriteSeen> wr64SpriteLastSeen;

        for (uint32_t wr64SpriteFam = 0; wr64SpriteFam < uint32_t(Wr64SpriteFamilyCount); wr64SpriteFam++) {
            // R4: the seagulls are named by trajectory in their own pass;
            // rank and guard below now serve only the single-instance
            // families, where rank is correct by construction.
            if (wr64SpriteFam == uint32_t(Wr64FamilySeagulls)) {
                const auto aliases = wr64AnimalReplayAliases(drawData, wr64SeagullReplayUses);
                for (const auto &alias : aliases) wr64SpriteClaimed[wr64SpriteFam].erase(alias.first);
                wr64SeagullAssignTransformIdentity(workload, wr64SpriteClaimed[wr64SpriteFam], wr64SeagullKinds);
                wr64AnimalReplayCopyGroups(drawData, aliases, [](uint32_t id) {
                    return (id & 0xFFFF0000U) == Wr64SpriteSeagullIdBase;
                });
                continue;
            }
            uint32_t wr64SpriteRank = 0;
            size_t wr64SpriteStamped = 0;
            size_t wr64SpriteSkipped = 0;
            size_t wr64SpriteSnapped = 0;

            for (const uint32_t wr64SpriteTransform : wr64SpriteClaimed[wr64SpriteFam]) {
                const uint32_t wr64SpriteId = wr64SpriteFamilyRankedId(wr64SpriteFam, wr64SpriteRank);
                wr64SpriteRank++;
                if (wr64SpriteId == 0) {
                    // Past the reserved ids. Leaving it at G_EX_ID_AUTO puts it
                    // back on the heuristic, which is where it is today. Wrapping
                    // it onto another member's id would be actively worse.
                    wr64SpriteSkipped++;
                    continue;
                }

                const uint32_t wr64SpriteOldGroup = drawData.worldTransformGroups[wr64SpriteTransform];
                if (wr64SpriteOldGroup >= drawData.transformGroups.size()) {
                    continue;
                }

                bool wr64SpriteJumped = false;
                if (wr64SpriteTransform < drawData.worldTransforms.size()) {
                    const hlslpp::float4x4 &wr64SpriteM = drawData.worldTransforms[wr64SpriteTransform];
                    const hlslpp::float3 wr64SpritePos = wr64SpriteM[3].xyz;
                    const float wr64SpriteX = float(wr64SpritePos.x);
                    const float wr64SpriteY = float(wr64SpritePos.y);
                    const float wr64SpriteZ = float(wr64SpritePos.z);

                    const auto wr64SpritePrev = wr64SpriteLastSeen.find(wr64SpriteId);
                    if (wr64SpritePrev != wr64SpriteLastSeen.end()) {
                        const uint64_t wr64SpriteAge =
                            (workload.submissionFrame > wr64SpritePrev->second.frame)
                                ? (workload.submissionFrame - wr64SpritePrev->second.frame)
                                : 0;
                        if (wr64SpriteAge > 0) {
                            const float dx = wr64SpriteX - wr64SpritePrev->second.x;
                            const float dy = wr64SpriteY - wr64SpritePrev->second.y;
                            const float dz = wr64SpriteZ - wr64SpritePrev->second.z;
                            const float wr64SpriteStep =
                                std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                            wr64SpriteJumped = (wr64SpriteStep > Wr64SpriteContinuityUnits);
                        }
                    }

                    wr64SpriteLastSeen[wr64SpriteId] = Wr64SpriteSeen{
                        workload.submissionFrame, wr64SpriteX, wr64SpriteY, wr64SpriteZ };
                }

                // Copy, stamp the copy, append, repoint. The G_EX_ID_AUTO group is
                // shared by every transform in the workload; writing into it would
                // re-identify the whole scene.
                TransformGroup wr64SpriteGroup = drawData.transformGroups[wr64SpriteOldGroup];
                wr64SpriteGroup.matrixId = wr64SpriteId;
                wr64SpriteGroup.ordering = G_EX_ORDER_LINEAR;
                // The whole makeWr64FinalMatrixGroup recipe, applied whole. Stamping
                // an id while leaving decompose on, or one component on AUTO, is what
                // made the first gantry attempt change nothing byte for byte.
                wr64SpriteGroup.decompose = false;
                wr64SpriteGroup.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
                wr64SpriteGroup.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
                wr64SpriteGroup.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
                wr64SpriteGroup.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
                wr64SpriteGroup.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
                wr64SpriteGroup.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
                wr64SpriteGroup.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;

                // The rank-flip frame keeps its name and loses its sweep.
                // Vertex and tile interpolation stay ON even here: the flap
                // is the member's own animation and continuous across the
                // flip; only the placement teleports - the same rule as the
                // fish and the ducks' re-slot.
                if (wr64SpriteJumped) {
                    wr64SpriteGroup.positionInterpolation = G_EX_COMPONENT_SKIP;
                    wr64SpriteGroup.rotationInterpolation = G_EX_COMPONENT_SKIP;
                    wr64SpriteGroup.scaleInterpolation = G_EX_COMPONENT_SKIP;
                    wr64SpriteGroup.skewInterpolation = G_EX_COMPONENT_SKIP;
                    wr64SpriteGroup.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                    wr64SpriteSnapped++;
                }

                drawData.worldTransformGroups[wr64SpriteTransform] =
                    uint32_t(drawData.transformGroups.size());
                drawData.transformGroups.emplace_back(wr64SpriteGroup);
                wr64SpriteStamped++;
            }

            wr64SpriteFamilyNote(wr64SpriteFam, wr64SpriteStamped, wr64SpriteSkipped, wr64SpriteSnapped);
        }
    }

    // DOLPHIN IDENTITY. The first pass in this file that does NOT name by rank.
    //
    // The id comes from the address the transform's matrix was read from, so it
    // does not depend on how many dolphins are on screen, on their order, or on
    // one of them going away. See rt64_wr64_dolphin_identity.h for the run that
    // put rank at 5.3% wrong and the address at 0.06%.
    //
    // Same window as the other three: the draws exist so minWorldMatrix is
    // filled, and the id map has not been built yet.
    static void wr64DolphinStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        // A SET of claimed transforms. Ordered, but the order is not used for
        // anything here - it only makes the pass deterministic.
        thread_local std::set<uint32_t> wr64DolphinClaimed;
        wr64DolphinClaimed.clear();
        Wr64AnimalReplayUses wr64DolphinReplayUses;

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64DolphinTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64DolphinTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    // TEXTURE AND RENDER STATE FIRST, address second. Segment 6
                    // carries a great deal that is not a dolphin, and claiming by
                    // address would sweep all of it in.
                    if (!wr64DolphinClaims(wr64DolphinTexture,
                            desc.colorCombiner.H, desc.colorCombiner.L,
                            desc.otherMode.H, desc.otherMode.L))
                    {
                        continue;
                    }

                    const uint32_t wr64DolphinTransform = desc.minWorldMatrix;
                    if (wr64DolphinTransform < drawData.worldTransformGroups.size()) {
                        // The Time Trial ghost uses the original dolphin textures,
                        // but supplies stable per-part identities itself. Keep it
                        // out of native slot ownership and continuity history.
                        const uint32_t groupIndex = drawData.worldTransformGroups[wr64DolphinTransform];
                        if ((groupIndex < drawData.transformGroups.size()) &&
                            ((drawData.transformGroups[groupIndex].matrixId & 0xFFF00000u) == 0x57F00000u))
                        {
                            continue;
                        }
                        wr64DolphinClaimed.insert(wr64DolphinTransform);
                        wr64AnimalReplayRecord(wr64DolphinReplayUses, wr64DolphinTransform,
                            f, proj.scissorRect, desc, wr64DolphinTexture);
                    }
                }
            }
        }

        // Count a byte-identical native replay once before ownership/continuity.
        // Distinct geometry or overlapping viewports retain the collision guard.
        const auto wr64DolphinReplayAliases = wr64AnimalReplayAliases(drawData, wr64DolphinReplayUses);
        for (const auto &alias : wr64DolphinReplayAliases) wr64DolphinClaimed.erase(alias.first);


        // Two transforms resolving to one address would mean two objects
        // claiming to be the same thing, which is worse than the heuristic this
        // replaces. It was not observed once in 67,526 (frame, address) pairs,
        // so this is insurance rather than a fix - but the cost of being wrong
        // is an object teleporting, and the cost of the guard is a set lookup.
        thread_local std::set<uint32_t> wr64DolphinUsedIds;
        wr64DolphinUsedIds.clear();

        // R2. Where each address was last seen, so the identity it claims can be
        // checked before it is believed. See rt64_wr64_dolphin_identity.h: the
        // full recipe removes the discontinuity gate, so a wrong pairing stops
        // being a snap and becomes a visible glide, and the address IS wrong 45
        // times in 73,707. Persists across calls on purpose.
        struct Wr64DolphinSeen { uint64_t frame; float x, y, z; };
        thread_local std::unordered_map<uint32_t, Wr64DolphinSeen> wr64DolphinLastSeen;

        size_t wr64DolphinStamped = 0;
        size_t wr64DolphinSkipped = 0;
        size_t wr64DolphinCollided = 0;
        size_t wr64DolphinMoved = 0;

        // How many times this function has run, ever. If the stamper is called
        // more than once per submission frame, the record for an address is
        // overwritten before the next frame's comparison and the continuity test
        // silently compares a frame against itself. That is candidate 2 for why
        // 8,795 units passed at frame 1026, and this column is how it is told
        // apart from the other two.
        static thread_local uint32_t wr64DolphinStampSeq = 0;
        wr64DolphinStampSeq++;

        for (const uint32_t wr64DolphinTransform : wr64DolphinClaimed) {
            uint32_t wr64DolphinAddress = 0;
            if (wr64DolphinTransform < drawData.worldTransformSegmentedAddresses.size()) {
                wr64DolphinAddress =
                    drawData.worldTransformSegmentedAddresses[wr64DolphinTransform];
            }

            // ---- POSITION AND THE CONTINUITY TEST, BOTH HOISTED ABOVE EVERY
            // BRANCH. An identity that teleports is not the same object: if the
            // thing at this address moved further in one frame than a dolphin
            // can, the game handed the slot to a different animal, and naming it
            // would tell RT64 to interpolate across the gap.
            //
            // They are computed before the id and collision checks so that EVERY
            // exit path below can record what it saw. A trace that only reports
            // the interesting branch leaves the frame silent when the branch
            // taken is not the one expected - which is exactly the situation
            // being investigated.
            float wr64DolphinX = 0.0f, wr64DolphinY = 0.0f, wr64DolphinZ = 0.0f;
            bool wr64DolphinHasPos = false;
            if (wr64DolphinTransform < drawData.worldTransforms.size()) {
                // BIND TO hlslpp::float4x4 FIRST, on its own line. worldTransforms
                // holds interop::float4x4, whose operator[] returns a raw float*,
                // so chaining [3].xyz straight off the vector element does not
                // compile - the conversion happens on the reference bind. This is
                // the idiom the object census already uses in
                // rt64_framebuffer_renderer.cpp; collapsing it into one expression
                // cost a build.
                const hlslpp::float4x4 &wr64DolphinM =
                    drawData.worldTransforms[wr64DolphinTransform];
                const hlslpp::float3 wr64DolphinPos = wr64DolphinM[3].xyz;
                wr64DolphinX = float(wr64DolphinPos.x);
                wr64DolphinY = float(wr64DolphinPos.y);
                wr64DolphinZ = float(wr64DolphinPos.z);
                wr64DolphinHasPos = true;
            }

            bool wr64DolphinContinuous = true;
            bool wr64DolphinHadRecord = false;
            bool wr64DolphinInWindow = false;
            uint64_t wr64DolphinPrevFrame = 0;
            uint32_t wr64DolphinAgeOut = 0;
            float wr64DolphinStepOut = 0.0f;
            if (wr64DolphinHasPos) {
                const auto wr64DolphinPrev = wr64DolphinLastSeen.find(wr64DolphinAddress);
                if (wr64DolphinPrev != wr64DolphinLastSeen.end()) {
                    wr64DolphinHadRecord = true;
                    wr64DolphinPrevFrame = wr64DolphinPrev->second.frame;
                    const uint64_t wr64DolphinAge =
                        (workload.submissionFrame > wr64DolphinPrev->second.frame)
                            ? (workload.submissionFrame - wr64DolphinPrev->second.frame)
                            : 0;
                    wr64DolphinAgeOut = uint32_t(wr64DolphinAge);
                    const float dx = wr64DolphinX - wr64DolphinPrev->second.x;
                    const float dy = wr64DolphinY - wr64DolphinPrev->second.y;
                    const float dz = wr64DolphinZ - wr64DolphinPrev->second.z;
                    // Recorded unconditionally so the log shows the step even on
                    // the frames the window test throws away - candidate 1 is
                    // "the age disqualified an 8,795-unit step", and it can only
                    // be seen if the step is written down either way.
                    wr64DolphinStepOut = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                    // Only meaningful while there IS a previous-frame transform to
                    // interpolate from. Past the window nothing can slide.
                    // R4. The window is now a LABEL, not a gate. R2 only tested
                    // the step while a previous-frame transform existed to slide
                    // between, on the reasoning that past the window nothing can
                    // slide. The trace found the exception: at frame 191 the
                    // dolphins returned after 93 absent frames, 12,900 units from
                    // where they were last recorded, and were stamped with full
                    // interpolation because the age disqualified the step. Nothing
                    // paired with them that time, so nothing happened - but the
                    // remedy costs nothing and the near miss does not need to be
                    // left standing. Suppressing interpolation on a frame that had
                    // nothing to interpolate from is a no-op; letting a 12,900-unit
                    // step through unmarked is a bet.
                    wr64DolphinInWindow =
                        ((wr64DolphinAge > 0) && (wr64DolphinAge <= Wr64DolphinContinuityFrames));
                    if (wr64DolphinAge > 0) {
                        const float wr64DolphinStep = wr64DolphinStepOut;
                        wr64DolphinContinuous =
                            (wr64DolphinStep <= Wr64DolphinContinuityUnits);
                    }
                }

                wr64DolphinLastSeen[wr64DolphinAddress] = Wr64DolphinSeen{
                    workload.submissionFrame, wr64DolphinX, wr64DolphinY, wr64DolphinZ };
            }

            const uint32_t wr64DolphinId = wr64DolphinIdForAddress(wr64DolphinAddress);

            // The trace, from here down. Every branch, no exceptions.
            #define WR64_DOLPHIN_TRACE_ROW(verdictValue)                                  \
                wr64DolphinTraceRecord(workload.submissionFrame, wr64DolphinTransform,    \
                    wr64DolphinAddress, wr64DolphinId, (verdictValue),                    \
                    wr64DolphinHadRecord, wr64DolphinPrevFrame, wr64DolphinAgeOut,        \
                    wr64DolphinInWindow, wr64DolphinStepOut,                              \
                    wr64DolphinX, wr64DolphinY, wr64DolphinZ, wr64DolphinStampSeq)

            if (wr64DolphinId == 0) {
                // Outside the measured window. Leaving it at G_EX_ID_AUTO puts it
                // back on the heuristic, which is where it is today.
                wr64DolphinSkipped++;
                WR64_DOLPHIN_TRACE_ROW(Wr64DolphinVerdictNoId);
                continue;
            }

            if (!wr64DolphinUsedIds.insert(wr64DolphinId).second) {
                wr64DolphinCollided++;
                WR64_DOLPHIN_TRACE_ROW(Wr64DolphinVerdictCollision);
                continue;
            }

            const uint32_t wr64DolphinOldGroup = drawData.worldTransformGroups[wr64DolphinTransform];
            if (wr64DolphinOldGroup >= drawData.transformGroups.size()) {
                WR64_DOLPHIN_TRACE_ROW(Wr64DolphinVerdictBadGroup);
                continue;
            }

            // Copy, stamp the copy, append, repoint. The G_EX_ID_AUTO group is
            // shared by every transform in the workload; writing into it would
            // re-identify the whole scene.
            TransformGroup wr64DolphinGroup = drawData.transformGroups[wr64DolphinOldGroup];
            wr64DolphinGroup.matrixId = wr64DolphinId;
            wr64DolphinGroup.ordering = G_EX_ORDER_LINEAR;
            // Use the complete makeWr64FinalMatrixGroup recipe. Keep decomposition off:
            // interpolating these matrices directly avoids the uneven motion produced by
            // the decomposed rotation path. Components and ordering must remain consistent
            // with the other explicit-identity families.
            wr64DolphinGroup.decompose = false;
            wr64DolphinGroup.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DolphinGroup.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DolphinGroup.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DolphinGroup.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DolphinGroup.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DolphinGroup.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DolphinGroup.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;

            // ---- R4. THE TELEPORT FRAME KEEPS ITS NAME AND LOSES ITS SWEEP.
            //
            // R2 answered a discontinuity by WITHDRAWING the identity - leaving
            // the transform at G_EX_ID_AUTO for that frame and letting the
            // heuristic matcher and the AUTO gate deal with it, on the reasoning
            // that this is where the transform was before any of this work. The
            // decision trace proved that reasoning wrong, and the mechanism is
            // worth writing down because it is not obvious.
            //
            // buildTransformIdMap builds one id map per frame, and matching walks
            // the current and previous maps together, pairing only where the ids
            // are EQUAL. So withdrawing an id does not cost one frame of
            // identity - it costs two. The teleport frame has no id, and the
            // frame AFTER it has an id that the previous frame's map does not
            // contain, so it finds no partner either and drops through to the
            // heuristic as well. And that second frame is the dangerous one: it
            // has already been stamped with the full recipe, so it carries
            // G_EX_COMPONENT_INTERPOLATE, and RigidBody::updateLinear runs its
            // discontinuity gate ONLY for G_EX_COMPONENT_AUTO. A heuristically
            // paired transform with INTERPOLATE on it is smoothed unconditionally
            // against whatever the matcher handed it.
            //
            // Sunset Bay, 2026-07-31, the recorded relocation. It is staggered
            // across three consecutive submission frames, which is why it costs
            // more than one:
            //
            //   f802   all three cruising, 10 units/frame, all stamped
            //   f803   dolphin 1 +13,709   dolphin 3 +12,674   -> R2 withdrew both
            //          dolphin 2 still cruising                -> stamped
            //   f804   dolphin 2 +13,708                       -> R2 withdrew it
            //          dolphins 1 and 3 continuous at 12 and 0 -> stamped, and
            //          their ids are ABSENT from f803, so both go to the
            //          heuristic carrying INTERPOLATE
            //   f805   dolphin 2 continuous at 12              -> stamped, id
            //          absent from f804, same fall-through
            //
            // Three frames in a row with dolphins in the heuristic matcher and
            // the safety gate bypassed, on the one event it was built to catch.
            // Fifteen transforms with identical draw signatures in one candidate
            // pool is also exactly the limb-shuffling that address keying exists
            // to prevent. At 180 Hz against a ~30 Hz submission rate that is
            // around eighteen rendered frames. It is once per race, on lap 2 or
            // 3, with the dolphins behind the player - which is the report.
            //
            // R4 keeps the id on EVERY frame and suppresses the interpolation on
            // the frame that jumped. G_EX_COMPONENT_SKIP is the mechanism the
            // extended GBI already provides for this: updateLinear and
            // updateAngular both read `flag == G_EX_COMPONENT_INTERPOLATE`, so
            // SKIP resolves to false, and with decompose off lerp() takes the
            // lerpMatrixComponents path where every disabled component is copied
            // from the CURRENT matrix. The result is the current transform
            // verbatim for every sub-frame - one clean snap, which is what the
            // console did, instead of a sweep or a re-pairing.
            //
            // The id never lapses, so the frame after the teleport pairs by id
            // like any other and interpolates normally. Vertex and tile
            // interpolation stay on even here: the animation is continuous across
            // a relocation, it is only the placement that jumps.
            if (!wr64DolphinContinuous) {
                wr64DolphinGroup.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64DolphinGroup.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64DolphinGroup.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64DolphinGroup.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64DolphinGroup.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                wr64DolphinMoved++;
            }

            drawData.worldTransformGroups[wr64DolphinTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64DolphinGroup);
            wr64DolphinStamped++;
            WR64_DOLPHIN_TRACE_ROW(wr64DolphinContinuous
                ? Wr64DolphinVerdictStamped
                : Wr64DolphinVerdictStampedSkip);
            #undef WR64_DOLPHIN_TRACE_ROW
        }

        wr64AnimalReplayCopyGroups(drawData, wr64DolphinReplayAliases, wr64DolphinIsOurs);

        wr64DolphinNote(wr64DolphinStamped, wr64DolphinSkipped, wr64DolphinCollided,
            wr64DolphinMoved);
    }

    static void wr64DrakeSchoolStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        thread_local std::set<uint32_t> wr64DrakeClaimed;
        wr64DrakeClaimed.clear();
        Wr64AnimalReplayUses wr64DrakeReplayUses;

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64DrakeTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64DrakeTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    // TEXTURE AND RENDER STATE FIRST, address second. Four of
                    // this pool's addresses are also dolphin slots, and claiming
                    // by address would merge two animals.
                    if (!wr64DrakeSchoolClaims(wr64DrakeTexture, desc.triangleCount,
                            desc.colorCombiner.H, desc.colorCombiner.L,
                            desc.otherMode.H, desc.otherMode.L))
                    {
                        continue;
                    }

                    const uint32_t wr64DrakeTransform = desc.minWorldMatrix;
                    if (wr64DrakeTransform < drawData.worldTransformGroups.size()) {
                        wr64DrakeClaimed.insert(wr64DrakeTransform);
                        wr64AnimalReplayRecord(wr64DrakeReplayUses, wr64DrakeTransform,
                            f, proj.scissorRect, desc, wr64DrakeTexture);
                    }
                }
            }
        }

        // Count a byte-identical native replay once before ownership/continuity.
        // Distinct geometry or overlapping viewports retain the collision guard.
        const auto wr64DrakeReplayAliases = wr64AnimalReplayAliases(drawData, wr64DrakeReplayUses);
        for (const auto &alias : wr64DrakeReplayAliases) wr64DrakeClaimed.erase(alias.first);



        // Split-screen views can submit multiple transforms for one matrix address.
        // Stamp no address-derived ID when the address is duplicated within a frame;
        // otherwise the global ID merge can pair across viewports before scene matching.
        // Ambiguous transforms retain automatic scene-aware matching. Single-player
        // captures found no duplicates in 22,428 Drake Lake or 59,925 Southern Island pairs.
        thread_local std::unordered_map<uint32_t, uint32_t> wr64DrakeAddressUses;
        wr64DrakeAddressUses.clear();
        for (const uint32_t wr64DrakeCountTransform : wr64DrakeClaimed) {
            uint32_t wr64DrakeCountAddress = 0;
            if (wr64DrakeCountTransform < drawData.worldTransformSegmentedAddresses.size()) {
                wr64DrakeCountAddress =
                    drawData.worldTransformSegmentedAddresses[wr64DrakeCountTransform];
            }
            wr64DrakeAddressUses[wr64DrakeCountAddress]++;
        }

        // Kept as a backstop below the rule above. It can no longer fire, and it
        // costs a set lookup to keep it that way provably.
        thread_local std::set<uint32_t> wr64DrakeUsedIds;
        wr64DrakeUsedIds.clear();

        // Where each address was last seen, so the identity it claims can be
        // checked before it is believed. Separate from the dolphins' map on
        // purpose; see the note above. Persists across calls.
        struct Wr64DrakeSeen { uint64_t frame; float x, y, z; };
        thread_local std::unordered_map<uint32_t, Wr64DrakeSeen> wr64DrakeLastSeen;

        size_t wr64DrakeStamped = 0;
        size_t wr64DrakeSkipped = 0;
        size_t wr64DrakeCollided = 0;
        size_t wr64DrakeMoved = 0;

        for (const uint32_t wr64DrakeTransform : wr64DrakeClaimed) {
            uint32_t wr64DrakeAddress = 0;
            if (wr64DrakeTransform < drawData.worldTransformSegmentedAddresses.size()) {
                wr64DrakeAddress =
                    drawData.worldTransformSegmentedAddresses[wr64DrakeTransform];
            }

            // The two-player rule, before anything else is read or recorded.
            if (wr64DrakeAddressUses[wr64DrakeAddress] != 1) {
                wr64DrakeCollided++;
                continue;
            }

            // Position and the continuity test, both hoisted above every branch,
            // so the record is written on every exit path rather than only on the
            // interesting one.
            float wr64DrakeX = 0.0f, wr64DrakeY = 0.0f, wr64DrakeZ = 0.0f;
            bool wr64DrakeHasPos = false;
            if (wr64DrakeTransform < drawData.worldTransforms.size()) {
                // BIND TO hlslpp::float4x4 FIRST, on its own line. worldTransforms
                // holds interop::float4x4, whose operator[] returns a raw float*,
                // so chaining [3].xyz straight off the vector element does not
                // compile. Collapsing this into one expression cost a build once.
                const hlslpp::float4x4 &wr64DrakeM =
                    drawData.worldTransforms[wr64DrakeTransform];
                const hlslpp::float3 wr64DrakePos = wr64DrakeM[3].xyz;
                wr64DrakeX = float(wr64DrakePos.x);
                wr64DrakeY = float(wr64DrakePos.y);
                wr64DrakeZ = float(wr64DrakePos.z);
                wr64DrakeHasPos = true;
            }

            bool wr64DrakeContinuous = true;
            if (wr64DrakeHasPos) {
                const auto wr64DrakePrev = wr64DrakeLastSeen.find(wr64DrakeAddress);
                if (wr64DrakePrev != wr64DrakeLastSeen.end()) {
                    const uint64_t wr64DrakeAge =
                        (workload.submissionFrame > wr64DrakePrev->second.frame)
                            ? (workload.submissionFrame - wr64DrakePrev->second.frame)
                            : 0;
                    // Tested at ANY age, not only inside
                    // Wr64DrakeSchoolContinuityFrames. R4's demotion of that
                    // window from a gate to a label: suppressing interpolation on
                    // a frame that had nothing to interpolate from is a no-op,
                    // and letting a return-from-absence through unmarked is a
                    // bet. Replayed over the capture, 745 of the 2,270
                    // suppressions land on exactly that no-op case and 1,525 land
                    // on a transform that really would have been smoothed.
                    if (wr64DrakeAge > 0) {
                        const float dx = wr64DrakeX - wr64DrakePrev->second.x;
                        const float dy = wr64DrakeY - wr64DrakePrev->second.y;
                        const float dz = wr64DrakeZ - wr64DrakePrev->second.z;
                        const float wr64DrakeStep =
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                        wr64DrakeContinuous =
                            (wr64DrakeStep <= Wr64DrakeSchoolContinuityUnits);
                    }
                }

                wr64DrakeLastSeen[wr64DrakeAddress] = Wr64DrakeSeen{
                    workload.submissionFrame, wr64DrakeX, wr64DrakeY, wr64DrakeZ };
            }

            const uint32_t wr64DrakeId = wr64DrakeSchoolIdForAddress(wr64DrakeAddress);
            if (wr64DrakeId == 0) {
                // Outside the measured window. Leaving it at G_EX_ID_AUTO puts it
                // back on the heuristic, which is where it is today.
                wr64DrakeSkipped++;
                continue;
            }

            if (!wr64DrakeUsedIds.insert(wr64DrakeId).second) {
                wr64DrakeCollided++;
                continue;
            }

            const uint32_t wr64DrakeOldGroup = drawData.worldTransformGroups[wr64DrakeTransform];
            if (wr64DrakeOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            // Copy, stamp the copy, append, repoint. The G_EX_ID_AUTO group is
            // shared by every transform in the workload; writing into it would
            // re-identify the whole scene.
            TransformGroup wr64DrakeGroup = drawData.transformGroups[wr64DrakeOldGroup];
            wr64DrakeGroup.matrixId = wr64DrakeId;
            wr64DrakeGroup.ordering = G_EX_ORDER_LINEAR;
            // decompose = false. Tried true for the dolphins in R3 on sound
            // reasoning and the motion came back visibly worse; the note in
            // rt64_wr64_dolphin_identity.h says not to re-derive it, and this
            // pass is not the place to re-open it.
            wr64DrakeGroup.decompose = false;
            wr64DrakeGroup.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DrakeGroup.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DrakeGroup.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DrakeGroup.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DrakeGroup.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DrakeGroup.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DrakeGroup.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;

            // The relocation frame keeps its name and loses its sweep. Vertex and
            // tile interpolation stay on even here: the fish's own animation is
            // continuous across a relocation, it is only the placement that jumps.
            if (!wr64DrakeContinuous) {
                wr64DrakeGroup.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64DrakeGroup.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64DrakeGroup.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64DrakeGroup.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64DrakeGroup.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                wr64DrakeMoved++;
            }

            drawData.worldTransformGroups[wr64DrakeTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64DrakeGroup);
            wr64DrakeStamped++;
        }

        wr64AnimalReplayCopyGroups(drawData, wr64DrakeReplayAliases, wr64DrakeSchoolIsOurs);

        wr64DrakeSchoolNote(wr64DrakeStamped, wr64DrakeSkipped, wr64DrakeCollided,
            wr64DrakeMoved);
    }

    // SOUTHERN ISLAND WHALES. The same recipe again, with one addition: a second
    // reason to suppress interpolation.
    //
    // The segment-6 block hands its slots back and forth between a whale drawn at
    // scale 0.20 and one drawn at 0.05, thirteen times over a run. The handover
    // note said to put the scale in the KEY. It is not in the key - an id that
    // changes is an id that lapses, and a lapsed id costs two frames of pairing
    // with updateLinear's gate bypassed on both, which is the R2 defect the R4
    // block above exists to explain. The scale is a SKIP TRIGGER instead, so the
    // slot keeps one name for its whole life and only the smoothing goes.
    //
    // Position and scale agreed on all 50 flips in the capture - every one also
    // moved at least 236 units - so this is belt and braces rather than two
    // independent needs. They are counted separately so a run where they stop
    // agreeing is visible.
    static void wr64WhaleStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        // A MAP, not a set: the group decides which id page the address mints
        // from, so it has to survive from the claim to the stamp.
        thread_local std::map<uint32_t, int> wr64WhaleClaimed;
        wr64WhaleClaimed.clear();
        Wr64AnimalReplayUses wr64WhaleReplayUses;

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64WhaleTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64WhaleTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    // TEXTURE AND RENDER STATE FIRST, address second. The
                    // segment-6 group shares all ten of its addresses with the
                    // dolphins, the Drake Lake school, the tropical fish and the
                    // seagulls - and it shares 853 frames with the seagulls.
                    const int wr64WhaleGroup = wr64WhaleGroupForDraw(wr64WhaleTexture,
                        desc.colorCombiner.H, desc.colorCombiner.L,
                        desc.otherMode.H, desc.otherMode.L);
                    if (wr64WhaleGroup == Wr64WhaleGroupNone) {
                        continue;
                    }

                    const uint32_t wr64WhaleTransform = desc.minWorldMatrix;
                    if (wr64WhaleTransform < drawData.worldTransformGroups.size()) {
                        // emplace, not operator[]: a transform is claimed once,
                        // by the first draw that names it, and a later draw must
                        // not silently retag it into the other group.
                        wr64WhaleClaimed.emplace(wr64WhaleTransform, wr64WhaleGroup);
                        wr64AnimalReplayRecord(wr64WhaleReplayUses, wr64WhaleTransform,
                            f, proj.scissorRect, desc, wr64WhaleTexture);
                    }
                }
            }
        }

        // Count a byte-identical native replay once before ownership/continuity.
        // Distinct geometry or overlapping viewports retain the collision guard.
        const auto wr64WhaleReplayAliases = wr64AnimalReplayAliases(drawData, wr64WhaleReplayUses);
        for (const auto &alias : wr64WhaleReplayAliases) wr64WhaleClaimed.erase(alias.first);


        // The same two-player rule as the school above, for the same reason.
        // Measured no-op in one player: 0 of 59,925 (frame, address) pairs on
        // Southern Island carried more than one transform.
        thread_local std::unordered_map<uint32_t, uint32_t> wr64WhaleAddressUses;
        wr64WhaleAddressUses.clear();
        for (const auto &wr64WhaleCountEntry : wr64WhaleClaimed) {
            uint32_t wr64WhaleCountAddress = 0;
            if (wr64WhaleCountEntry.first < drawData.worldTransformSegmentedAddresses.size()) {
                wr64WhaleCountAddress =
                    drawData.worldTransformSegmentedAddresses[wr64WhaleCountEntry.first];
            }
            wr64WhaleAddressUses[wr64WhaleCountAddress]++;
        }

        thread_local std::set<uint32_t> wr64WhaleUsedIds;
        wr64WhaleUsedIds.clear();

        // Position AND scale, because both are checked. Persists across calls.
        struct Wr64WhaleSeen { uint64_t frame; float x, y, z, scale; };
        thread_local std::unordered_map<uint32_t, Wr64WhaleSeen> wr64WhaleLastSeen;

        size_t wr64WhaleStamped = 0;
        size_t wr64WhaleSkipped = 0;
        size_t wr64WhaleCollided = 0;
        size_t wr64WhaleMovedPosition = 0;
        size_t wr64WhaleMovedScale = 0;

        for (const auto &wr64WhaleEntry : wr64WhaleClaimed) {
            const uint32_t wr64WhaleTransform = wr64WhaleEntry.first;
            const int wr64WhaleGroup = wr64WhaleEntry.second;

            uint32_t wr64WhaleAddress = 0;
            if (wr64WhaleTransform < drawData.worldTransformSegmentedAddresses.size()) {
                wr64WhaleAddress =
                    drawData.worldTransformSegmentedAddresses[wr64WhaleTransform];
            }

            // The two-player rule, before anything else is read or recorded.
            if (wr64WhaleAddressUses[wr64WhaleAddress] != 1) {
                wr64WhaleCollided++;
                continue;
            }

            float wr64WhaleX = 0.0f, wr64WhaleY = 0.0f, wr64WhaleZ = 0.0f;
            float wr64WhaleScale = 0.0f;
            bool wr64WhaleHasPos = false;
            if (wr64WhaleTransform < drawData.worldTransforms.size()) {
                // BIND TO hlslpp::float4x4 FIRST, on its own line - worldTransforms
                // holds interop::float4x4 and the conversion happens on the bind.
                const hlslpp::float4x4 &wr64WhaleM =
                    drawData.worldTransforms[wr64WhaleTransform];
                const hlslpp::float3 wr64WhalePos = wr64WhaleM[3].xyz;
                wr64WhaleX = float(wr64WhalePos.x);
                wr64WhaleY = float(wr64WhalePos.y);
                wr64WhaleZ = float(wr64WhalePos.z);
                // THE X BASIS, not Z. Implicit conversion rather than float(...),
                // which is the idiom matchTransform and the matrix recorder both
                // use for hlslpp::length. The Z basis carries the animal's
                // rotation and jitters by up to 0.8% between frames; x and y do
                // not move at all. See rt64_wr64_whale_identity.h.
                const hlslpp::float3 wr64WhaleBasis = wr64WhaleM[0].xyz;
                wr64WhaleScale = hlslpp::length(wr64WhaleBasis);
                wr64WhaleHasPos = true;
            }

            bool wr64WhaleContinuous = true;
            bool wr64WhaleResized = false;
            if (wr64WhaleHasPos) {
                const auto wr64WhalePrev = wr64WhaleLastSeen.find(wr64WhaleAddress);
                if (wr64WhalePrev != wr64WhaleLastSeen.end()) {
                    const uint64_t wr64WhaleAge =
                        (workload.submissionFrame > wr64WhalePrev->second.frame)
                            ? (workload.submissionFrame - wr64WhalePrev->second.frame)
                            : 0;
                    // Both tests run at ANY age, the R4 shape: suppressing
                    // interpolation on a frame that had nothing to interpolate
                    // from is a no-op, and letting a return-from-absence through
                    // unmarked is a bet. g1 has 47 frame gaps in the capture and
                    // g2 has 8.
                    if (wr64WhaleAge > 0) {
                        const float dx = wr64WhaleX - wr64WhalePrev->second.x;
                        const float dy = wr64WhaleY - wr64WhalePrev->second.y;
                        const float dz = wr64WhaleZ - wr64WhalePrev->second.z;
                        const float wr64WhaleStep =
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                        wr64WhaleContinuous =
                            (wr64WhaleStep <= Wr64WhaleContinuityUnits);
                        wr64WhaleResized = wr64WhaleScaleChanged(
                            wr64WhalePrev->second.scale, wr64WhaleScale);
                    }
                }

                wr64WhaleLastSeen[wr64WhaleAddress] = Wr64WhaleSeen{
                    workload.submissionFrame, wr64WhaleX, wr64WhaleY, wr64WhaleZ,
                    wr64WhaleScale };
            }

            const uint32_t wr64WhaleId =
                wr64WhaleIdForAddress(wr64WhaleAddress, wr64WhaleGroup);
            if (wr64WhaleId == 0) {
                // Outside the group's own segment. Leaving it at G_EX_ID_AUTO
                // puts it back on the heuristic, which is where it is today.
                wr64WhaleSkipped++;
                continue;
            }

            if (!wr64WhaleUsedIds.insert(wr64WhaleId).second) {
                wr64WhaleCollided++;
                continue;
            }

            const uint32_t wr64WhaleOldGroup = drawData.worldTransformGroups[wr64WhaleTransform];
            if (wr64WhaleOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            TransformGroup wr64WhaleTg = drawData.transformGroups[wr64WhaleOldGroup];
            wr64WhaleTg.matrixId = wr64WhaleId;
            wr64WhaleTg.ordering = G_EX_ORDER_LINEAR;
            wr64WhaleTg.decompose = false;
            wr64WhaleTg.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64WhaleTg.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64WhaleTg.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64WhaleTg.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64WhaleTg.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64WhaleTg.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64WhaleTg.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;

            // Either trigger snaps the frame. Vertex and tile interpolation stay
            // on: the animal's own animation is continuous across a handover, it
            // is only the placement and the size that jump.
            if (!wr64WhaleContinuous || wr64WhaleResized) {
                wr64WhaleTg.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64WhaleTg.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64WhaleTg.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64WhaleTg.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64WhaleTg.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                if (!wr64WhaleContinuous) { wr64WhaleMovedPosition++; }
                if (wr64WhaleResized) { wr64WhaleMovedScale++; }
            }

            drawData.worldTransformGroups[wr64WhaleTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64WhaleTg);
            wr64WhaleStamped++;
        }

        wr64AnimalReplayCopyGroups(drawData, wr64WhaleReplayAliases, wr64WhaleIsOurs);

        wr64WhaleNote(wr64WhaleStamped, wr64WhaleSkipped, wr64WhaleCollided,
            wr64WhaleMovedPosition, wr64WhaleMovedScale);
    }

    // DRAKE LAKE DUCKS. The same recipe once more, with the one change that is
    // not cosmetic: THE DISCONTINUITY IS A PROPERTY OF THE DUCK, NOT THE PIECE.
    //
    // A duck is seven consecutive 0x40 addresses - six carrying one draw each of
    // the body texture, one carrying all six detail textures. It travels about 50
    // units a frame while its own pieces sit about 17 apart, which is the exact
    // condition under which nearest-position matching fails: replayed over the
    // capture, the heuristic these transforms fall to today picks the wrong
    // partner on 29.18% of them, and 1,216 of those mis-pairs cross to a
    // DIFFERENT DUCK up to 1,527 units away.
    //
    // Drake Lake slides its allocation window, so the block re-slots - 122 of
    // 42,657 transitions - and unlike the lake fish the step populations OVERLAP,
    // so no threshold separates them cleanly. A per-piece decision therefore
    // TEARS the animal: 34 torn duck-frames of 6,200 in replay, one piece
    // snapping while its neighbours interpolate. OR-ing the discontinuity across
    // the whole block gives 0 torn, for 186 extra snaps over the capture.
    //
    // The block is rebuilt from the claimed set every frame and never stored, so
    // a slid window cannot stale it. Full account in rt64_wr64_duck_identity.h.
    static void wr64DuckStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        thread_local std::set<uint32_t> wr64DuckClaimed;
        wr64DuckClaimed.clear();
        Wr64AnimalReplayUses wr64DuckReplayUses;

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64DuckTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64DuckTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    // TEXTURE AND RENDER STATE FIRST, address second. These
                    // addresses are shared with the lake fish and the dolphins;
                    // claiming by address would merge three animals. Triangle
                    // count is deliberately not tested - four of the seven
                    // textures were measured at two different counts, and
                    // requiring one would keep part of a duck and drop the rest.
                    if (!wr64DuckClaims(wr64DuckTexture,
                            desc.colorCombiner.H, desc.colorCombiner.L,
                            desc.otherMode.H, desc.otherMode.L))
                    {
                        continue;
                    }

                    const uint32_t wr64DuckTransform = desc.minWorldMatrix;
                    if (wr64DuckTransform < drawData.worldTransformGroups.size()) {
                        wr64DuckClaimed.insert(wr64DuckTransform);
                        wr64AnimalReplayRecord(wr64DuckReplayUses, wr64DuckTransform,
                            f, proj.scissorRect, desc, wr64DuckTexture);
                    }
                }
            }
        }

        // Count a byte-identical native replay once before ownership/continuity.
        // Distinct geometry or overlapping viewports retain the collision guard.
        const auto wr64DuckReplayAliases = wr64AnimalReplayAliases(drawData, wr64DuckReplayUses);
        for (const auto &alias : wr64DuckReplayAliases) wr64DuckClaimed.erase(alias.first);


        // ---- TWO PLAYER. AN ADDRESS THAT NAMES TWO THINGS NAMES NEITHER. ----
        //
        // Built in from the start this time. In split screen the scene is
        // submitted once per viewport, so one address arrives on two transforms
        // in the same frame, both mint the same id, and buildTransformIdMap pairs
        // them with each other across the seam. That cost a working two-player
        // build on 2026-08-02 when the fish and whales shipped without it.
        //
        // Measured no-op in one player: 0 of 43,265 (frame, address) pairs in the
        // duck capture carried more than one transform.
        thread_local std::unordered_map<uint32_t, uint32_t> wr64DuckAddressUses;
        wr64DuckAddressUses.clear();
        for (const uint32_t wr64DuckCountTransform : wr64DuckClaimed) {
            uint32_t wr64DuckCountAddress = 0;
            if (wr64DuckCountTransform < drawData.worldTransformSegmentedAddresses.size()) {
                wr64DuckCountAddress =
                    drawData.worldTransformSegmentedAddresses[wr64DuckCountTransform];
            }
            wr64DuckAddressUses[wr64DuckCountAddress]++;
        }

        struct Wr64DuckSeen { uint64_t frame; float x, y, z; };
        thread_local std::unordered_map<uint32_t, Wr64DuckSeen> wr64DuckLastSeen;

        // One entry per live address this frame, kept SORTED BY ADDRESS so the
        // 0x40 runs can be walked directly.
        struct Wr64DuckLive {
            uint32_t address;
            uint32_t transform;
            bool jumped;
        };
        thread_local std::vector<Wr64DuckLive> wr64DuckLive;
        wr64DuckLive.clear();

        size_t wr64DuckStamped = 0;
        size_t wr64DuckSkipped = 0;
        size_t wr64DuckCollided = 0;
        size_t wr64DuckMoved = 0;
        size_t wr64DuckPropagated = 0;

        for (const uint32_t wr64DuckTransform : wr64DuckClaimed) {
            uint32_t wr64DuckAddress = 0;
            if (wr64DuckTransform < drawData.worldTransformSegmentedAddresses.size()) {
                wr64DuckAddress =
                    drawData.worldTransformSegmentedAddresses[wr64DuckTransform];
            }

            // The two-player rule, before anything else is read or recorded.
            if (wr64DuckAddressUses[wr64DuckAddress] != 1) {
                wr64DuckCollided++;
                continue;
            }

            // BIND TO hlslpp::float4x4 FIRST, on its own line. worldTransforms
            // holds interop::float4x4, whose operator[] returns a raw float*, so
            // chaining [3].xyz straight off the vector element does not compile.
            float wr64DuckX = 0.0f, wr64DuckY = 0.0f, wr64DuckZ = 0.0f;
            bool wr64DuckHasPos = false;
            if (wr64DuckTransform < drawData.worldTransforms.size()) {
                const hlslpp::float4x4 &wr64DuckM =
                    drawData.worldTransforms[wr64DuckTransform];
                const hlslpp::float3 wr64DuckPos = wr64DuckM[3].xyz;
                wr64DuckX = float(wr64DuckPos.x);
                wr64DuckY = float(wr64DuckPos.y);
                wr64DuckZ = float(wr64DuckPos.z);
                wr64DuckHasPos = true;
            }

            bool wr64DuckJumped = false;
            if (wr64DuckHasPos) {
                const auto wr64DuckPrev = wr64DuckLastSeen.find(wr64DuckAddress);
                if (wr64DuckPrev != wr64DuckLastSeen.end()) {
                    const uint64_t wr64DuckAge =
                        (workload.submissionFrame > wr64DuckPrev->second.frame)
                            ? (workload.submissionFrame - wr64DuckPrev->second.frame)
                            : 0;
                    if (wr64DuckAge > 0) {
                        const float dx = wr64DuckX - wr64DuckPrev->second.x;
                        const float dy = wr64DuckY - wr64DuckPrev->second.y;
                        const float dz = wr64DuckZ - wr64DuckPrev->second.z;
                        const float wr64DuckStep =
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                        wr64DuckJumped = (wr64DuckStep > Wr64DuckContinuityUnits);
                    }
                }

                wr64DuckLastSeen[wr64DuckAddress] = Wr64DuckSeen{
                    workload.submissionFrame, wr64DuckX, wr64DuckY, wr64DuckZ };
            }

            wr64DuckLive.push_back(Wr64DuckLive{
                wr64DuckAddress, wr64DuckTransform, wr64DuckJumped });
        }

        // ---- THE DUCK MOVES WHOLE. -------------------------------------------
        //
        // Walk the live addresses in order and OR the discontinuity across every
        // run of consecutive 0x40 slots. Without this, a re-slot that trips only
        // some of a duck's seven pieces leaves the others interpolating and the
        // animal comes apart for a frame - 34 such frames of 6,200 in replay, 0
        // with this loop.
        std::sort(wr64DuckLive.begin(), wr64DuckLive.end(),
            [](const Wr64DuckLive &a, const Wr64DuckLive &b) { return a.address < b.address; });

        size_t wr64DuckRunBegin = 0;
        while (wr64DuckRunBegin < wr64DuckLive.size()) {
            size_t wr64DuckRunEnd = wr64DuckRunBegin;
            while (((wr64DuckRunEnd + 1) < wr64DuckLive.size())
                && ((wr64DuckLive[wr64DuckRunEnd + 1].address
                     - wr64DuckLive[wr64DuckRunEnd].address) == Wr64DuckBlockStride))
            {
                wr64DuckRunEnd++;
            }

            bool wr64DuckRunJumped = false;
            for (size_t i = wr64DuckRunBegin; i <= wr64DuckRunEnd; i++) {
                if (wr64DuckLive[i].jumped) {
                    wr64DuckRunJumped = true;
                    break;
                }
            }

            if (wr64DuckRunJumped) {
                for (size_t i = wr64DuckRunBegin; i <= wr64DuckRunEnd; i++) {
                    if (!wr64DuckLive[i].jumped) {
                        wr64DuckLive[i].jumped = true;
                        wr64DuckPropagated++;
                    }
                }
            }

            wr64DuckRunBegin = wr64DuckRunEnd + 1;
        }

        // Kept as a backstop below the two-player rule. It can no longer fire,
        // and it costs a set lookup to keep it that way provably.
        thread_local std::set<uint32_t> wr64DuckUsedIds;
        wr64DuckUsedIds.clear();

        for (const Wr64DuckLive &wr64DuckEntry : wr64DuckLive) {
            const uint32_t wr64DuckId = wr64DuckIdForAddress(wr64DuckEntry.address);
            if (wr64DuckId == 0) {
                // Outside the measured window. Leaving it at G_EX_ID_AUTO puts it
                // back on the heuristic, which is where it is today.
                wr64DuckSkipped++;
                continue;
            }

            if (!wr64DuckUsedIds.insert(wr64DuckId).second) {
                wr64DuckCollided++;
                continue;
            }

            const uint32_t wr64DuckOldGroup =
                drawData.worldTransformGroups[wr64DuckEntry.transform];
            if (wr64DuckOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            // Copy, stamp the copy, append, repoint. The G_EX_ID_AUTO group is
            // shared by every transform in the workload; writing into it would
            // re-identify the whole scene.
            TransformGroup wr64DuckTg = drawData.transformGroups[wr64DuckOldGroup];
            wr64DuckTg.matrixId = wr64DuckId;
            wr64DuckTg.ordering = G_EX_ORDER_LINEAR;
            wr64DuckTg.decompose = false;
            wr64DuckTg.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DuckTg.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DuckTg.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DuckTg.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DuckTg.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DuckTg.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64DuckTg.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;

            // The re-slot frame keeps its name and loses its sweep. Vertex and
            // tile interpolation stay on even here: the duck's own animation is
            // continuous across a re-slot, it is only the placement that jumps.
            if (wr64DuckEntry.jumped) {
                wr64DuckTg.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64DuckTg.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64DuckTg.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64DuckTg.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64DuckTg.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                wr64DuckMoved++;
            }

            drawData.worldTransformGroups[wr64DuckEntry.transform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64DuckTg);
            wr64DuckStamped++;
        }

        wr64AnimalReplayCopyGroups(drawData, wr64DuckReplayAliases, wr64DuckIsOurs);

        wr64DuckNote(wr64DuckStamped, wr64DuckSkipped, wr64DuckCollided,
            wr64DuckMoved, wr64DuckPropagated);
    }

    // THE COURSE BUOYS. Full account in rt64_wr64_buoy_identity.h.
    //
    // THIS IS THE DUCK PASS WITH THE BUOYS' OWN NUMBERS. R4 tried to be clever -
    // it set vertexInterpolation alone, because the buoys already paired by rank
    // and an id looked redundant - and the tail still stepped. The gantry note
    // above says why: "Copy it whole rather than in parts." So this copies it
    // whole: an id from the matrix address, ordering LINEAR, decompose false,
    // and every component forced.
    static void wr64BuoyStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        // transform -> LOWEST buoy texture index that claimed it. One transform
        // can be referenced by more than one buoy draw (L18 and L19 share a
        // transform), so the lowest index is taken to keep the choice
        // deterministic across frames - which is the whole point of an id.
        thread_local std::map<uint32_t, int> wr64BuoyClaimed;
        wr64BuoyClaimed.clear();

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64BuoyTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64BuoyTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    // TEXTURE ALONE. Render state cannot separate a buoy from a
                    // duck or a seagull - all three carry combiner FC127FFF
                    // FFFFF238 and other mode C8113078 00182CFF - and the four
                    // parts were measured at 1, 1, 4 and 2 triangles, so a
                    // triangle test would keep part of the object and drop the
                    // rest. The hash is the whole key.
                    const int wr64BuoyTexIdx = wr64BuoyTextureIndex(wr64BuoyTexture);
                    if (wr64BuoyTexIdx < 0) {
                        continue;
                    }

                    // Every world matrix the call spans, not just min. A call
                    // carrying several buoys would otherwise have one part named
                    // and the rest left on the heuristic.
                    for (uint32_t m = desc.minWorldMatrix; m <= desc.maxWorldMatrix; m++) {
                        if (m < drawData.worldTransformGroups.size()) {
                            const auto wr64BuoyPrevClaim = wr64BuoyClaimed.find(m);
                            if ((wr64BuoyPrevClaim == wr64BuoyClaimed.end())
                                || (wr64BuoyTexIdx < wr64BuoyPrevClaim->second))
                            {
                                wr64BuoyClaimed[m] = wr64BuoyTexIdx;
                            }
                        }
                    }
                }
            }
        }

        // ---- TWO PLAYER, KEYED ON (ADDRESS, TEXTURE). --------------------
        //
        // The duck version counts the ADDRESS alone, and on this object that is
        // wrong. Measured: 50% of (frame, address) pairs carry two transforms,
        // and all 1,249 of them carry DIFFERENT textures - a buoy's L9 and L10
        // sharing one matrix slot. None carried the same texture twice. Counting
        // the address alone therefore refused every buoy's billboard pair on
        // every frame, which is what made them flicker at distance.
        //
        // A REAL split-screen duplication is the same address AND the same
        // texture, because the scene is submitted whole per viewport. That is
        // what this counts, so the guard keeps its meaning and stops eating the
        // legitimate case.
        thread_local std::map<std::pair<uint32_t, int>, uint32_t> wr64BuoyAddressUses;
        wr64BuoyAddressUses.clear();
        for (const auto &wr64BuoyCountEntry : wr64BuoyClaimed) {
            uint32_t wr64BuoyCountAddress = 0;
            if (wr64BuoyCountEntry.first < drawData.worldTransformSegmentedAddresses.size()) {
                wr64BuoyCountAddress =
                    drawData.worldTransformSegmentedAddresses[wr64BuoyCountEntry.first];
            }
            wr64BuoyAddressUses[std::make_pair(wr64BuoyCountAddress, wr64BuoyCountEntry.second)]++;
        }

        // ---- CONTINUITY. The slot is recycled between buoys. -----------------
        // Measured: one address served four different buoys over a session. An
        // id alone would then lerp buoy A's last position into buoy B's first
        // and sweep it across the course, which is the failure that got texture
        // C7E16FE8A5BC21ED refused. A step past the threshold keeps the name and
        // drops the interpolation for that one frame.
        // KEYED ON THE ID, not the address. L9 and L10 share an address, so an
        // address-keyed history would have each overwriting the other's entry
        // every frame and both reading as a jump.
        struct Wr64BuoySeen { uint64_t frame; float x, y, z; };
        thread_local std::unordered_map<uint32_t, Wr64BuoySeen> wr64BuoyLastSeen;

        thread_local std::set<uint32_t> wr64BuoyUsedIds;
        wr64BuoyUsedIds.clear();

        size_t wr64BuoyStamped = 0;
        size_t wr64BuoySkipped = 0;
        size_t wr64BuoyCollided = 0;
        size_t wr64BuoyMoved = 0;

        for (const auto &wr64BuoyEntry : wr64BuoyClaimed) {
            const uint32_t wr64BuoyTransform = wr64BuoyEntry.first;
            const int wr64BuoyTexIndex = wr64BuoyEntry.second;

            uint32_t wr64BuoyAddress = 0;
            if (wr64BuoyTransform < drawData.worldTransformSegmentedAddresses.size()) {
                wr64BuoyAddress = drawData.worldTransformSegmentedAddresses[wr64BuoyTransform];
            }

            if (wr64BuoyAddressUses[std::make_pair(wr64BuoyAddress, wr64BuoyTexIndex)] > 1) {
                wr64BuoyCollided++;
                continue;
            }

            const uint32_t wr64BuoyId = wr64BuoyIdFor(wr64BuoyAddress, wr64BuoyTexIndex);
            if (wr64BuoyId == 0) {
                // Outside segment 5. Leaving it at G_EX_ID_AUTO puts it back on
                // the heuristic, which is where it is today.
                wr64BuoySkipped++;
                continue;
            }

            if (!wr64BuoyUsedIds.insert(wr64BuoyId).second) {
                wr64BuoyCollided++;
                continue;
            }

            const uint32_t wr64BuoyOldGroup = drawData.worldTransformGroups[wr64BuoyTransform];
            if (wr64BuoyOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            bool wr64BuoyJumped = false;
            if (wr64BuoyTransform < drawData.worldTransforms.size()) {
                const hlslpp::float4x4 &wr64BuoyM = drawData.worldTransforms[wr64BuoyTransform];
                const hlslpp::float3 wr64BuoyPos = wr64BuoyM[3].xyz;
                const float wr64BuoyX = float(wr64BuoyPos.x);
                const float wr64BuoyY = float(wr64BuoyPos.y);
                const float wr64BuoyZ = float(wr64BuoyPos.z);

                const auto wr64BuoyPrev = wr64BuoyLastSeen.find(wr64BuoyId);
                if (wr64BuoyPrev != wr64BuoyLastSeen.end()) {
                    const uint64_t wr64BuoyAge =
                        (workload.submissionFrame > wr64BuoyPrev->second.frame)
                            ? (workload.submissionFrame - wr64BuoyPrev->second.frame)
                            : 0;
                    if (wr64BuoyAge > 0) {
                        const float dx = wr64BuoyX - wr64BuoyPrev->second.x;
                        const float dy = wr64BuoyY - wr64BuoyPrev->second.y;
                        const float dz = wr64BuoyZ - wr64BuoyPrev->second.z;
                        const float wr64BuoyStep =
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                        wr64BuoyJumped = (wr64BuoyStep > Wr64BuoyContinuityUnits);
                    }
                }

                wr64BuoyLastSeen[wr64BuoyId] = Wr64BuoySeen{
                    workload.submissionFrame, wr64BuoyX, wr64BuoyY, wr64BuoyZ };
            }

            // Copy, stamp the copy, append, repoint. The G_EX_ID_AUTO group is
            // shared by every transform in the workload; writing into it would
            // re-identify the whole scene.
            TransformGroup wr64BuoyTg = drawData.transformGroups[wr64BuoyOldGroup];
            wr64BuoyTg.matrixId = wr64BuoyId;
            wr64BuoyTg.ordering = G_EX_ORDER_LINEAR;
            wr64BuoyTg.decompose = false;
            wr64BuoyTg.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64BuoyTg.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64BuoyTg.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64BuoyTg.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64BuoyTg.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64BuoyTg.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64BuoyTg.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;

            // The re-slot frame keeps its name and loses its sweep. Vertex and
            // tile interpolation stay ON even here: the buoy's own animation is
            // continuous across a re-slot, it is only the placement that jumps.
            if (wr64BuoyJumped) {
                wr64BuoyTg.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64BuoyTg.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64BuoyTg.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64BuoyTg.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64BuoyTg.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                wr64BuoyMoved++;
            }

            drawData.worldTransformGroups[wr64BuoyTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64BuoyTg);
            wr64BuoyStamped++;
        }

        wr64BuoyNote(wr64BuoyStamped, wr64BuoySkipped, wr64BuoyCollided, wr64BuoyMoved);
    }

    // THE AREA LIMITATION BUOYS. Full account in
    // rt64_wr64_area_buoy_identity.h - the short version: the same stamp
    // block as the course buoys, but the id comes from the buoy's POSITION,
    // because the measured segment-5 slots are a count-stack that shuffles
    // contents whenever visibility changes (137 of 141 positions served by
    // more than one slot; 3,632 same-slot content swaps of >200 units). The
    // address is exactly the wrong key for this object; the position - static
    // to the integer across 2,096 frames - is the only property a slot
    // shuffle preserves.
    static void wr64AreaBuoyStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;

        // transform -> LOWEST claiming texture index, for determinism if a
        // call ever spans both layers. Measured: the two textures never share
        // a transform (27,366 of 27,366), so this map is one entry per
        // transform in practice.
        thread_local std::map<uint32_t, int> wr64AreaBuoyClaimed;
        wr64AreaBuoyClaimed.clear();
        // AREABUOY-R4: the claiming texture per transform, so the stamp loop
        // can see a shade RE-BAKE (hash change under a stable id) and snap
        // the content instead of blending two incomparable bakes.
        thread_local std::map<uint32_t, uint64_t> wr64AreaBuoyTextures;
        wr64AreaBuoyTextures.clear();

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64AreaBuoyTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64AreaBuoyTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    // Try known textures first, then the measured one-triangle render-state
                    // fingerprint for rebaked course variants. See rt64_wr64_area_buoy_identity.h.
                    int wr64AreaBuoyTexIdx = wr64AreaBuoyTextureIndex(wr64AreaBuoyTexture);
                    bool wr64AreaBuoyVariant = false;
                    if (wr64AreaBuoyTexIdx < 0) {
                        if (!wr64AreaBuoyStateClaims(desc.colorCombiner.H, desc.colorCombiner.L,
                                desc.otherMode.H, desc.otherMode.L, desc.triangleCount))
                        {
                            continue;
                        }
                        // AREABUOY-R3: claim now, index by position rank
                        // below - the hash is NOT identity here (the shade
                        // re-bake flips it; see the header note).
                        wr64AreaBuoyTexIdx = Wr64AreaBuoyVariantBase;
                        wr64AreaBuoyVariant = true;
                    }

                    for (uint32_t m = desc.minWorldMatrix; m <= desc.maxWorldMatrix; m++) {
                        if (m < drawData.worldTransformGroups.size()) {
                            if (wr64AreaBuoyVariant) {
                                // Apply both guards only to render-state claims. Preserve the existing
                                // enumerated-texture path for Sunset Bay area buoys.
                                const uint32_t wr64AreaBuoySeg =
                                    (m < drawData.worldTransformSegmentedAddresses.size())
                                        ? (drawData.worldTransformSegmentedAddresses[m] >> 24)
                                        : 0u;
                                if (wr64AreaBuoySeg != 0x05u) {
                                    continue;
                                }
                                const uint32_t wr64AreaBuoyGroup = drawData.worldTransformGroups[m];
                                if ((wr64AreaBuoyGroup < drawData.transformGroups.size()) &&
                                    ((drawData.transformGroups[wr64AreaBuoyGroup].matrixId & 0xFF000000u) == 0x57000000u))
                                {
                                    continue;
                                }
                                wr64AreaBuoyVariantNote();
                            }
                            const auto wr64AreaBuoyPrevClaim = wr64AreaBuoyClaimed.find(m);
                            if ((wr64AreaBuoyPrevClaim == wr64AreaBuoyClaimed.end())
                                || (wr64AreaBuoyTexIdx < wr64AreaBuoyPrevClaim->second))
                            {
                                wr64AreaBuoyClaimed[m] = wr64AreaBuoyTexIdx;
                                wr64AreaBuoyTextures[m] = wr64AreaBuoyTexture;
                            }
                        }
                    }
                }
            }
        }

        // AREABUOY-R3: RE-INDEX THE FINGERPRINT CLAIMS BY POSITION RANK.
        // Every fingerprint claim landed above with the same placeholder
        // index; two layers of one buoy would mint the same id and refuse
        // each other. Group them by the buoy's own rounded position and
        // hand out ranks in transform order - the submission-order block
        // structure keeps "lower transform = same layer" stable across
        // frames AND across shade re-bakes, which a texture-hash bit does
        // not. Enumerated claims (indices 0/1) are untouched.
        thread_local std::map<std::pair<int32_t, int32_t>, int> wr64AreaBuoyVariantRanks;
        wr64AreaBuoyVariantRanks.clear();
        for (auto &wr64AreaBuoyRankEntry : wr64AreaBuoyClaimed) {
            if (wr64AreaBuoyRankEntry.second < Wr64AreaBuoyVariantBase) {
                continue;
            }
            const uint32_t wr64AreaBuoyRankTransform = wr64AreaBuoyRankEntry.first;
            if (wr64AreaBuoyRankTransform >= drawData.worldTransforms.size()) {
                continue;
            }
            const hlslpp::float4x4 &wr64AreaBuoyRankM =
                drawData.worldTransforms[wr64AreaBuoyRankTransform];
            const std::pair<int32_t, int32_t> wr64AreaBuoyRankPos{
                int32_t(std::lround(float(wr64AreaBuoyRankM[3].x))),
                int32_t(std::lround(float(wr64AreaBuoyRankM[3].z))) };
            int &wr64AreaBuoyRank = wr64AreaBuoyVariantRanks[wr64AreaBuoyRankPos];
            wr64AreaBuoyRankEntry.second = Wr64AreaBuoyVariantBase +
                std::min(wr64AreaBuoyRank, Wr64AreaBuoyVariantMaxRank);
            wr64AreaBuoyRank++;
        }

        // The id needs the transform's position, so it is minted once here
        // and counted before any stamp. A duplicated id in one frame - split
        // screen submitting the scene twice, or a 16-bit hash collision
        // between two on-screen buoys - refuses EVERY carrier and leaves
        // them on today's heuristic, the same behaviour the course-buoy
        // (address, texture) count enforces.
        thread_local std::map<uint32_t, uint32_t> wr64AreaBuoyIds;      // transform -> id
        thread_local std::map<uint32_t, uint32_t> wr64AreaBuoyIdUses;   // id -> count
        wr64AreaBuoyIds.clear();
        wr64AreaBuoyIdUses.clear();
        for (const auto &wr64AreaBuoyEntry : wr64AreaBuoyClaimed) {
            const uint32_t wr64AreaBuoyTransform = wr64AreaBuoyEntry.first;
            if (wr64AreaBuoyTransform >= drawData.worldTransforms.size()) {
                continue;
            }
            const hlslpp::float4x4 &wr64AreaBuoyM =
                drawData.worldTransforms[wr64AreaBuoyTransform];
            const hlslpp::float3 wr64AreaBuoyPos = wr64AreaBuoyM[3].xyz;
            const uint32_t wr64AreaBuoyId = wr64AreaBuoyIdFor(
                float(wr64AreaBuoyPos.x), float(wr64AreaBuoyPos.z),
                wr64AreaBuoyEntry.second);
            if (wr64AreaBuoyId == 0) {
                continue;
            }
            wr64AreaBuoyIds[wr64AreaBuoyTransform] = wr64AreaBuoyId;
            wr64AreaBuoyIdUses[wr64AreaBuoyId]++;
        }

        // CONTINUITY, keyed on the id. Not for slot recycling - the id does
        // not contain the slot - but for a hash collision handing one id
        // between two distant buoys across consecutive frames: name kept,
        // smoothing dropped, one tick.
        struct Wr64AreaBuoySeen { uint64_t frame; float x, y, z; uint64_t texture; };
        thread_local std::unordered_map<uint32_t, Wr64AreaBuoySeen> wr64AreaBuoyLastSeen;

        size_t wr64AreaBuoyStamped = 0;
        size_t wr64AreaBuoyCollided = 0;
        size_t wr64AreaBuoyMoved = 0;

        for (const auto &wr64AreaBuoyEntry : wr64AreaBuoyIds) {
            const uint32_t wr64AreaBuoyTransform = wr64AreaBuoyEntry.first;
            const uint32_t wr64AreaBuoyId = wr64AreaBuoyEntry.second;

            if (wr64AreaBuoyIdUses[wr64AreaBuoyId] > 1) {
                wr64AreaBuoyCollided++;
                continue;
            }

            const uint32_t wr64AreaBuoyOldGroup =
                drawData.worldTransformGroups[wr64AreaBuoyTransform];
            if (wr64AreaBuoyOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            bool wr64AreaBuoyJumped = false;
            // AREABUOY-R4: a texture-hash change under a stable id is the
            // shade RE-BAKE (a passing wave sweeping its shadow across the
            // buoy re-bakes it tick after tick). The transform keeps its
            // glide; only the baked CONTENT must not blend across bakes.
            bool wr64AreaBuoyRebaked = false;
            {
                const hlslpp::float4x4 &wr64AreaBuoyM =
                    drawData.worldTransforms[wr64AreaBuoyTransform];
                const hlslpp::float3 wr64AreaBuoyPos = wr64AreaBuoyM[3].xyz;
                const float wr64AreaBuoyX = float(wr64AreaBuoyPos.x);
                const float wr64AreaBuoyY = float(wr64AreaBuoyPos.y);
                const float wr64AreaBuoyZ = float(wr64AreaBuoyPos.z);
                const auto wr64AreaBuoyTexIt = wr64AreaBuoyTextures.find(wr64AreaBuoyTransform);
                const uint64_t wr64AreaBuoyTexNow =
                    (wr64AreaBuoyTexIt != wr64AreaBuoyTextures.end()) ? wr64AreaBuoyTexIt->second : 0;

                const auto wr64AreaBuoyPrev = wr64AreaBuoyLastSeen.find(wr64AreaBuoyId);
                if (wr64AreaBuoyPrev != wr64AreaBuoyLastSeen.end()) {
                    const uint64_t wr64AreaBuoyAge =
                        (workload.submissionFrame > wr64AreaBuoyPrev->second.frame)
                            ? (workload.submissionFrame - wr64AreaBuoyPrev->second.frame)
                            : 0;
                    if (wr64AreaBuoyAge > 0) {
                        const float dx = wr64AreaBuoyX - wr64AreaBuoyPrev->second.x;
                        const float dy = wr64AreaBuoyY - wr64AreaBuoyPrev->second.y;
                        const float dz = wr64AreaBuoyZ - wr64AreaBuoyPrev->second.z;
                        const float wr64AreaBuoyStep =
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                        wr64AreaBuoyJumped = (wr64AreaBuoyStep > Wr64AreaBuoyContinuityUnits);
                        wr64AreaBuoyRebaked = (wr64AreaBuoyTexNow != 0) &&
                            (wr64AreaBuoyPrev->second.texture != 0) &&
                            (wr64AreaBuoyTexNow != wr64AreaBuoyPrev->second.texture);
                    }
                }

                wr64AreaBuoyLastSeen[wr64AreaBuoyId] = Wr64AreaBuoySeen{
                    workload.submissionFrame, wr64AreaBuoyX, wr64AreaBuoyY, wr64AreaBuoyZ,
                    wr64AreaBuoyTexNow };
            }

            // Copy, stamp the copy, append, repoint - the G_EX_ID_AUTO group
            // is shared by every transform in the workload; writing into it
            // would re-identify the whole scene. The block is the recipe
            // COPIED WHOLE, the buoy R4 lesson.
            TransformGroup wr64AreaBuoyTg = drawData.transformGroups[wr64AreaBuoyOldGroup];
            wr64AreaBuoyTg.matrixId = wr64AreaBuoyId;
            wr64AreaBuoyTg.ordering = G_EX_ORDER_LINEAR;
            wr64AreaBuoyTg.decompose = false;
            wr64AreaBuoyTg.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64AreaBuoyTg.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64AreaBuoyTg.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64AreaBuoyTg.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64AreaBuoyTg.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64AreaBuoyTg.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64AreaBuoyTg.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64AreaBuoyTg.texcoordInterpolation = G_EX_COMPONENT_INTERPOLATE;

            if (wr64AreaBuoyJumped) {
                wr64AreaBuoyTg.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyTg.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyTg.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyTg.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyTg.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyMoved++;
            }

            // Texture rebakes need an explicit content snap because forced interpolation
            // bypasses the normal hash guard. Keep the transform glide unchanged.
            if (wr64AreaBuoyRebaked) {
                wr64AreaBuoyTg.tileInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyTg.vertexInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyTg.texcoordInterpolation = G_EX_COMPONENT_SKIP;
                wr64AreaBuoyRebakeNote();
            }

            drawData.worldTransformGroups[wr64AreaBuoyTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64AreaBuoyTg);
            wr64AreaBuoyStamped++;
        }

        wr64AreaBuoyNote(wr64AreaBuoyStamped, wr64AreaBuoyCollided, wr64AreaBuoyMoved);
    }

    // THE STUNT MODE RINGS. Full account in rt64_wr64_stunt_ring_identity.h.
    // The same position-keyed stamp as the area buoys - the rings sit on the
    // same kind of shuffling segment-5 count-stack (in the gantry's own
    // scratch region) - with one texture and one transform per ring, so
    // there is no texture index to fold in and no two-layer bookkeeping.
    // What the id buys here is the SPIN: the drawn rotation already lerps on
    // the ticks the heuristic pairs, and freezes on the ticks around slot
    // shuffles; an exact pairing removes the freezes, and carries the
    // collapse animation's scale run (1.0 -> 0.875 -> 0.75) through the same
    // path.
    static void wr64StuntRingStampTransformIdentity(Workload &workload) {
        DrawData &drawData = workload.drawData;
        workload.wr64StuntRingTilePairs.clear();

        thread_local std::set<uint32_t> wr64StuntRingClaimed;
        wr64StuntRingClaimed.clear();

        // transform -> the claiming calls' tiles, in call order. A ring is
        // ONE transform but TWO draw calls (the red and the white layer),
        // each with its own tiles. The spin's texture animation can live in
        // those tiles, and the engine's tile blend only reaches them through
        // scene-based call matching - the one path the ring's matrix id does
        // NOT already bypass. Collecting them here lets the stamp loop below
        // pair each ring's tiles with its own previous-frame self by the
        // ring's identity, the same way the celestial pass pairs the text's.
        struct Wr64StuntRingTiles {
            uint32_t tileIndex[4];
            uint32_t count = 0;
        };
        thread_local std::map<uint32_t, Wr64StuntRingTiles> wr64StuntRingCallTiles;
        wr64StuntRingCallTiles.clear();

        for (uint32_t f = 0; f < workload.fbPairCount; f++) {
            const FramebufferPair &fbPair = workload.fbPairs[f];
            for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                const Projection &proj = fbPair.projections[p];
                if (proj.type != Projection::Type::Perspective) {
                    continue;
                }

                for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                    const DrawCall &desc = proj.gameCalls[c].callDesc;
                    uint64_t wr64StuntRingTexture = 0;
                    if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                        wr64StuntRingTexture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                    }

                    // Tile 0 claims the whole draw; the white layer is the
                    // second TILE of the same call (never a draw of its own
                    // in 6,550 measured rows), so one hash covers the ring.
                    if (wr64StuntRingTexture != Wr64StuntRingTexture) {
                        // Claim course-specific ring textures by the 48-triangle torus fingerprint.
                        // Match combiner and otherModeH; allow otherModeL to vary with blender/fog state.
                        // See rt64_wr64_stunt_ring_identity.h for the captured-state evidence.
                        if (wr64StuntRingState(desc.triangleCount,
                            desc.colorCombiner.H, desc.colorCombiner.L,
                            desc.otherMode.H))
                        {
                            wr64StuntRingFingerprintNote();
                            if (desc.colorCombiner.L != Wr64StuntRingCombinerL) {
                                // Sunset Bay's one-byte tint, or a sibling.
                                wr64StuntRingTintNote();
                            }
                        }
                        else {
                            continue;
                        }
                    }

                    for (uint32_t m = desc.minWorldMatrix; m <= desc.maxWorldMatrix; m++) {
                        if (m < drawData.worldTransformGroups.size()) {
                            wr64StuntRingClaimed.insert(m);
                        }
                    }
                    if (desc.minWorldMatrix < drawData.worldTransformGroups.size()) {
                        Wr64StuntRingTiles &wr64StuntRingT =
                            wr64StuntRingCallTiles[desc.minWorldMatrix];
                        for (uint32_t t = 0; (t < desc.tileCount) && (wr64StuntRingT.count < 4); t++) {
                            wr64StuntRingT.tileIndex[wr64StuntRingT.count++] = desc.tileIndex + t;
                        }
                    }
                }
            }
        }

        thread_local std::map<uint32_t, uint32_t> wr64StuntRingIds;      // transform -> id
        thread_local std::map<uint32_t, uint32_t> wr64StuntRingIdUses;   // id -> count
        wr64StuntRingIds.clear();
        wr64StuntRingIdUses.clear();
        for (const uint32_t wr64StuntRingTransform : wr64StuntRingClaimed) {
            if (wr64StuntRingTransform >= drawData.worldTransforms.size()) {
                continue;
            }
            const hlslpp::float4x4 &wr64StuntRingM =
                drawData.worldTransforms[wr64StuntRingTransform];
            const hlslpp::float3 wr64StuntRingPos = wr64StuntRingM[3].xyz;
            const uint32_t wr64StuntRingId = wr64StuntRingIdFor(
                float(wr64StuntRingPos.x), float(wr64StuntRingPos.z));
            wr64StuntRingIds[wr64StuntRingTransform] = wr64StuntRingId;
            wr64StuntRingIdUses[wr64StuntRingId]++;
        }

        // Resolve colliding position hashes by stable (x,z) order. Two Port Blue rings
        // at (-4673,-3600) and (-4192,-4527) both hash to 0x4F22; rank bits 16-19 give
        // them distinct IDs. Refuse a bucket only if it exceeds sixteen members.
        thread_local std::map<uint32_t, std::vector<uint32_t>> wr64StuntRingIdGroups;
        wr64StuntRingIdGroups.clear();
        for (const auto &wr64StuntRingEntry : wr64StuntRingIds) {
            if (wr64StuntRingIdUses[wr64StuntRingEntry.second] > 1) {
                wr64StuntRingIdGroups[wr64StuntRingEntry.second].push_back(wr64StuntRingEntry.first);
            }
        }
        for (auto &wr64StuntRingGroup : wr64StuntRingIdGroups) {
            std::vector<uint32_t> &wr64StuntRingMembers = wr64StuntRingGroup.second;
            std::sort(wr64StuntRingMembers.begin(), wr64StuntRingMembers.end(),
                [&](uint32_t wr64StuntRingA, uint32_t wr64StuntRingB) {
                    // Bind to hlslpp::float4x4 BEFORE [3].xyz - the interop
                    // operator[] returns a raw const float * (the same trap
                    // the R5 renderer gate documents).
                    const hlslpp::float4x4 &wr64StuntRingMa =
                        drawData.worldTransforms[wr64StuntRingA];
                    const hlslpp::float4x4 &wr64StuntRingMb =
                        drawData.worldTransforms[wr64StuntRingB];
                    const hlslpp::float3 wr64StuntRingPa = wr64StuntRingMa[3].xyz;
                    const hlslpp::float3 wr64StuntRingPb = wr64StuntRingMb[3].xyz;
                    const float wr64StuntRingAx = float(wr64StuntRingPa.x);
                    const float wr64StuntRingBx = float(wr64StuntRingPb.x);
                    if (wr64StuntRingAx != wr64StuntRingBx) {
                        return wr64StuntRingAx < wr64StuntRingBx;
                    }
                    return float(wr64StuntRingPa.z) < float(wr64StuntRingPb.z);
                });
            const size_t wr64StuntRingRankCap =
                std::min<size_t>(wr64StuntRingMembers.size(), 16);
            for (size_t wr64StuntRingRank = 0; wr64StuntRingRank < wr64StuntRingRankCap; wr64StuntRingRank++) {
                wr64StuntRingIds[wr64StuntRingMembers[wr64StuntRingRank]] |=
                    uint32_t(wr64StuntRingRank) << 16;
            }
            wr64StuntRingRankNote();
        }
        if (!wr64StuntRingIdGroups.empty()) {
            // The final ids changed; the refusal below must judge THEM.
            wr64StuntRingIdUses.clear();
            for (const auto &wr64StuntRingEntry : wr64StuntRingIds) {
                wr64StuntRingIdUses[wr64StuntRingEntry.second]++;
            }
        }

        struct Wr64StuntRingSeen {
            uint64_t frame; float x, y, z;
            // The ring's claiming calls' tiles on that frame, so the next
            // frame can pair its tiles by the ring's own identity.
            uint32_t tileIndex[4]; uint32_t tileCount;
        };
        thread_local std::unordered_map<uint32_t, Wr64StuntRingSeen> wr64StuntRingLastSeen;

        size_t wr64StuntRingStamped = 0;
        size_t wr64StuntRingCollided = 0;
        size_t wr64StuntRingMoved = 0;

        for (const auto &wr64StuntRingEntry : wr64StuntRingIds) {
            const uint32_t wr64StuntRingTransform = wr64StuntRingEntry.first;
            const uint32_t wr64StuntRingId = wr64StuntRingEntry.second;

            if (wr64StuntRingIdUses[wr64StuntRingId] > 1) {
                wr64StuntRingCollided++;
                continue;
            }

            const uint32_t wr64StuntRingOldGroup =
                drawData.worldTransformGroups[wr64StuntRingTransform];
            if (wr64StuntRingOldGroup >= drawData.transformGroups.size()) {
                continue;
            }

            bool wr64StuntRingJumped = false;
            {
                const hlslpp::float4x4 &wr64StuntRingM =
                    drawData.worldTransforms[wr64StuntRingTransform];
                const hlslpp::float3 wr64StuntRingPos = wr64StuntRingM[3].xyz;
                const float wr64StuntRingX = float(wr64StuntRingPos.x);
                const float wr64StuntRingY = float(wr64StuntRingPos.y);
                const float wr64StuntRingZ = float(wr64StuntRingPos.z);

                const Wr64StuntRingTiles wr64StuntRingCurTiles =
                    wr64StuntRingCallTiles[wr64StuntRingTransform];

                const auto wr64StuntRingPrev = wr64StuntRingLastSeen.find(wr64StuntRingId);
                if (wr64StuntRingPrev != wr64StuntRingLastSeen.end()) {
                    const uint64_t wr64StuntRingAge =
                        (workload.submissionFrame > wr64StuntRingPrev->second.frame)
                            ? (workload.submissionFrame - wr64StuntRingPrev->second.frame)
                            : 0;
                    if (wr64StuntRingAge > 0) {
                        const float dx = wr64StuntRingX - wr64StuntRingPrev->second.x;
                        const float dy = wr64StuntRingY - wr64StuntRingPrev->second.y;
                        const float dz = wr64StuntRingZ - wr64StuntRingPrev->second.z;
                        const float wr64StuntRingStep =
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                        wr64StuntRingJumped = (wr64StuntRingStep > Wr64StuntRingContinuityUnits);
                    }

                    // THE SPIN'S TILES, paired by the ring's own identity.
                    // Consecutive frame, same ring, not jumped: hand this
                    // frame's tiles and last frame's to the engine's tile
                    // blend, positionally (call order is stable for a static
                    // ring). This bypasses scene-based call matching the same
                    // way the matrix id bypasses transform matching.
                    if ((wr64StuntRingAge == 1) && !wr64StuntRingJumped) {
                        const uint32_t wr64StuntRingPairN = std::min(
                            wr64StuntRingCurTiles.count, wr64StuntRingPrev->second.tileCount);
                        for (uint32_t t = 0; t < wr64StuntRingPairN; t++) {
                            workload.wr64StuntRingTilePairs.push_back(Workload::Wr64CelestialTilePair{
                                wr64StuntRingCurTiles.tileIndex[t],
                                wr64StuntRingPrev->second.tileIndex[t] });
                        }
                        if (wr64StuntRingPairN > 0) {
                            wr64StuntRingTileNote();
                        }
                    }
                }

                Wr64StuntRingSeen wr64StuntRingSeen{};
                wr64StuntRingSeen.frame = workload.submissionFrame;
                wr64StuntRingSeen.x = wr64StuntRingX;
                wr64StuntRingSeen.y = wr64StuntRingY;
                wr64StuntRingSeen.z = wr64StuntRingZ;
                wr64StuntRingSeen.tileCount = wr64StuntRingCurTiles.count;
                for (uint32_t t = 0; t < wr64StuntRingCurTiles.count; t++) {
                    wr64StuntRingSeen.tileIndex[t] = wr64StuntRingCurTiles.tileIndex[t];
                }
                wr64StuntRingLastSeen[wr64StuntRingId] = wr64StuntRingSeen;
            }

            TransformGroup wr64StuntRingTg = drawData.transformGroups[wr64StuntRingOldGroup];
            wr64StuntRingTg.matrixId = wr64StuntRingId;
            wr64StuntRingTg.ordering = G_EX_ORDER_LINEAR;
            wr64StuntRingTg.decompose = false;
            wr64StuntRingTg.positionInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64StuntRingTg.rotationInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64StuntRingTg.scaleInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64StuntRingTg.skewInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64StuntRingTg.perspectiveInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64StuntRingTg.tileInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64StuntRingTg.vertexInterpolation = G_EX_COMPONENT_INTERPOLATE;
            wr64StuntRingTg.texcoordInterpolation = G_EX_COMPONENT_INTERPOLATE;

            if (wr64StuntRingJumped) {
                wr64StuntRingTg.positionInterpolation = G_EX_COMPONENT_SKIP;
                wr64StuntRingTg.rotationInterpolation = G_EX_COMPONENT_SKIP;
                wr64StuntRingTg.scaleInterpolation = G_EX_COMPONENT_SKIP;
                wr64StuntRingTg.skewInterpolation = G_EX_COMPONENT_SKIP;
                wr64StuntRingTg.perspectiveInterpolation = G_EX_COMPONENT_SKIP;
                wr64StuntRingMoved++;
            }

            drawData.worldTransformGroups[wr64StuntRingTransform] =
                uint32_t(drawData.transformGroups.size());
            drawData.transformGroups.emplace_back(wr64StuntRingTg);
            wr64StuntRingStamped++;
        }

        wr64StuntRingNote(wr64StuntRingStamped, wr64StuntRingCollided, wr64StuntRingMoved);
    }

    // THE CELESTIAL BODIES. Full account in rt64_wr64_celestial_identity.h.
    //
    // Screen-space rects, not transforms, so this is NOT a stamp pass: nothing
    // here touches a TransformGroup or an id. It pairs each claimed sun rect
    // with its previous-frame self and leaves the pairs on the workload; the
    // transform processor blends them per output frame with the same weight
    // the matrices use, and the renderer draws the blended rect for exactly
    // those calls.
    //
    // PAIRING IS BY DRAW ORDER WITHIN THE TEXTURE, and the capture is why that
    // is sound: flare call indices are always a contiguous prefix 0..n-1 -
    // they drop from the tail - so order is identity while the count holds.
    // The equal-count gate refuses the tick when it does not (34 of ~2,500
    // transitions measured), and a strictly consecutive-frame pairing means an
    // off-screen sun re-enters with no partner and pops cleanly instead of
    // sweeping in from its last position seconds ago.
    static uint32_t wr64CelestialRectView(int textureIndex, const FixedRect &scissor) {
        // Only restored race sky effects acquire a per-view history. Dolphin
        // Park's disk/announcements keep their established shared history.
        if ((textureIndex != 0) && (textureIndex != 1) &&
            (textureIndex != 2) && (textureIndex != 4)) return 0;
        if ((scissor.ulx != 0) || (scissor.lrx != 424 * 4)) return 0;
        if ((scissor.uly == 0) && (scissor.lry == 120 * 4)) return 1;
        if ((scissor.uly == 120 * 4) && (scissor.lry == 240 * 4)) return 2;
        return 0;
    }

    // Stunt awards use exact native producer identities. Dolphin Park text
    // must retain the R14 UV/crop fold below: moving the current rebaked text
    // backwards reopens its pinned edge on the no-previous output frame.
    static void wr64HudPairRects(Workload &current, const Workload &previous) {
        if (current.submissionFrame != previous.submissionFrame + 1) return;
        struct Claim { uint64_t key; const DrawCall *draw; };
        auto equalRect = [](const FixedRect &a, const FixedRect &b) {
            return a.ulx == b.ulx && a.uly == b.uly && a.lrx == b.lrx && a.lry == b.lry;
        };
        std::vector<Claim> oldClaims;
        auto visit = [](const Workload &workload, auto callback) {
            for (uint32_t f = 0; f < workload.fbPairCount; ++f) {
                const auto &pair = workload.fbPairs[f];
                for (uint32_t p = 0; p < pair.projectionCount; ++p) {
                    const auto &projection = pair.projections[p];
                    if (projection.type != Projection::Type::Rectangle) continue;
                    for (uint32_t c = 0; c < projection.gameCallCount; ++c) {
                        const auto &draw = projection.gameCalls[c].callDesc;
                        // TourEnd clears Z between its panel and model passes.
                        // The native producer tags that F6 too, but a depth
                        // clear must never inherit the panel's scrolling offset.
                        if (draw.wr64HudMotion.kind == 3 &&
                            pair.colorImage.address == pair.depthImage.address &&
                            (draw.otherMode.H & 0x00300000U) == 0x00300000U) continue;
                        if (draw.wr64HudMotion.generation &&
                            (draw.wr64HudMotion.kind == 2 || draw.wr64HudMotion.kind == 3))
                            callback(Claim{wr64CelestialRectKey(f, p, c), &draw});
                    }
                }
            }
        };
        visit(previous, [&](Claim claim) { oldClaims.push_back(claim); });
        visit(current, [&](Claim claim) {
            const DrawCall &cur = *claim.draw;
            if (cur.wr64HudMotion.kind == 3) {
                // A native ending row is one moving panel. Its producers omit
                // whole strips until they enter the screen, so a newly visible
                // piece may have no previous draw. Use the authenticated row
                // transform shared by all its parts, including those new pieces.
                const Wr64HudMotion *previousPanel = nullptr;
                for (const auto &candidate : oldClaims) {
                    const auto &old = *candidate.draw;
                    if (!wr64HudContinuous(old.wr64HudMotion, cur.wr64HudMotion)) continue;
                    if (previousPanel && (previousPanel->x != old.wr64HudMotion.x ||
                        previousPanel->y != old.wr64HudMotion.y)) return;
                    previousPanel = &old.wr64HudMotion;
                }
                if (!previousPanel) return;
                FixedRect from = cur.rect;
                const int32_t dx = (previousPanel->x - cur.wr64HudMotion.x) * 4;
                const int32_t dy = (previousPanel->y - cur.wr64HudMotion.y) * 4;
                from.ulx += dx; from.lrx += dx; from.uly += dy; from.lry += dy;
                current.wr64CelestialPrevRects.push_back(Workload::Wr64CelestialRectPair{
                    claim.key, from, cur.rect});
                return;
            }
            const DrawCall *prev = nullptr;
            for (const auto &candidate : oldClaims) {
                if (!wr64HudContinuous(candidate.draw->wr64HudMotion, cur.wr64HudMotion)) continue;
                if (prev) return; // Duplicate producer/part is ambiguous.
                prev = candidate.draw;
            }
            if (!prev || cur.rectDsdx != prev->rectDsdx || cur.rectDtdy != prev->rectDtdy ||
                !equalRect(cur.scissorRect, prev->scissorRect) ||
                cur.rectLeftOrigin != prev->rectLeftOrigin || cur.rectRightOrigin != prev->rectRightOrigin ||
                cur.colorCombiner.H != prev->colorCombiner.H || cur.colorCombiner.L != prev->colorCombiner.L ||
                cur.otherMode.H != prev->otherMode.H || cur.otherMode.L != prev->otherMode.L) return;
            FixedRect from = cur.rect;
            const int32_t dx = (prev->wr64HudMotion.x - cur.wr64HudMotion.x) * 4;
            const int32_t dy = (prev->wr64HudMotion.y - cur.wr64HudMotion.y) * 4;
            from.ulx += dx; from.lrx += dx; from.uly += dy; from.lry += dy;
            if (!equalRect(from, prev->rect)) return;
            current.wr64CelestialPrevRects.push_back(Workload::Wr64CelestialRectPair{
                claim.key, from, cur.rect});
        });
    }

    static void wr64DolphinSunPairRects(Workload &current, const Workload &previous) {
        current.wr64DolphinSunPairs.clear();
        current.wr64DolphinSunOutputRects.clear();
        if (!wr64DolphinSunNativeExitEnabled() || current.submissionFrame != previous.submissionFrame + 1) return;
        struct Claim { uint64_t key; const DrawCall *draw; };
        auto collect = [](const Workload &workload) {
            std::vector<Claim> claims;
            for (uint32_t f = 0; f < workload.fbPairCount; ++f) {
                const auto &pair = workload.fbPairs[f];
                for (uint32_t p = 0; p < pair.projectionCount; ++p) {
                    const auto &projection = pair.projections[p];
                    for (uint32_t c = 0; c < projection.gameCallCount; ++c) {
                        const auto &draw = projection.gameCalls[c].callDesc;
                        if (wr64DolphinSunClaimValid(draw, workload.drawData, projection.type == Projection::Type::Rectangle))
                            claims.push_back({wr64CelestialRectKey(f, p, c), &draw});
                    }
                }
            }
            return claims;
        };
        const auto oldClaims = collect(previous);
        const auto newClaims = collect(current);
        for (const auto &claim : newClaims) {
            const auto &cur = *claim.draw;
            const DrawCall *prev = nullptr;
            size_t oldCount = 0, newCount = 0;
            for (const auto &candidate : oldClaims) {
                if (wr64DolphinSunSameSprite(candidate.draw->wr64DolphinSunSprite, cur.wr64DolphinSunSprite)) {
                    prev = candidate.draw;
                    ++oldCount;
                }
            }
            for (const auto &candidate : newClaims)
                if (wr64DolphinSunSameSprite(candidate.draw->wr64DolphinSunSprite, cur.wr64DolphinSunSprite)) ++newCount;
            if (oldCount != 1 || newCount != 1 || !prev) continue;
            if (!wr64DolphinSunMotionContinuous(prev->wr64DolphinSunSprite, cur.wr64DolphinSunSprite,
                    Wr64CelestialMaxStepQuarterPx * 0.25f)) continue;
            const auto &a = prev->scissorRect;
            const auto &b = cur.scissorRect;
            if (a.ulx != b.ulx || a.uly != b.uly || a.lrx != b.lrx || a.lry != b.lry ||
                prev->tileCount != cur.tileCount || prev->colorCombiner.H != cur.colorCombiner.H ||
                prev->colorCombiner.L != cur.colorCombiner.L || prev->otherMode.H != cur.otherMode.H ||
                prev->otherMode.L != cur.otherMode.L) continue;
            current.wr64DolphinSunPairs.push_back({claim.key,
                wr64DolphinSunFullRect(prev->wr64DolphinSunSprite), wr64DolphinSunFullRect(cur.wr64DolphinSunSprite)});
        }
    }

    static void wr64CelestialPairRects(Workload &curWorkload, const Workload &prevWorkload) {
        curWorkload.wr64CelestialPrevRects.clear();
        curWorkload.wr64CelestialTilePairs.clear();

        // Track the last full Dolphin Park disk frame. Reconstruct shortened exits only
        // within Wr64CelestialDpExitTailTicks, excluding persistent parked remnants.
        thread_local uint64_t wr64DpLastFullFrame = 0;

        // The previous SUBMISSION frame only. A gap - pause, menu, the sun
        // fully off screen - yields no pairs rather than stale ones.
        if ((prevWorkload.submissionFrame + 1) != curWorkload.submissionFrame) {
            return;
        }

        struct Wr64CelClaim {
            uint64_t key;
            uint64_t texture;
            FixedRect rect;
            uint32_t tileIndex;
            uint32_t tileCount;
            uint32_t rawVertexStart;
        };
        // Per watched texture, in draw order. The count and the index mapping
        // live in the header next to the hashes, so adding a texture is one
        // edit there rather than three loose literals here - which is exactly
        // how the Dolphin Park disk was added without touching this pass.
        constexpr uint32_t wr64CelViewCount = 3;
        thread_local std::vector<Wr64CelClaim> wr64CelCurByView[wr64CelViewCount * Wr64CelestialTextureCount];
        thread_local std::vector<Wr64CelClaim> wr64CelPrevByView[wr64CelViewCount * Wr64CelestialTextureCount];

        auto wr64CelCollect = [&](const Workload &workload, std::vector<Wr64CelClaim> *out) {
            for (uint32_t i = 0; i < wr64CelViewCount * Wr64CelestialTextureCount; i++) {
                out[i].clear();
            }
            const DrawData &drawData = workload.drawData;
            for (uint32_t f = 0; f < workload.fbPairCount; f++) {
                const FramebufferPair &fbPair = workload.fbPairs[f];
                for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                    const Projection &proj = fbPair.projections[p];
                    if (proj.type != Projection::Type::Rectangle) {
                        continue;
                    }
                    for (uint32_t c = 0; c < proj.gameCallCount; c++) {
                        const DrawCall &desc = proj.gameCalls[c].callDesc;
                        // Only Stunt awards bypass this pass. Warm-up text,
                        // including tagged native packets, needs the proven
                        // message UV/rebake handling and R14 forward fold.
                        if (desc.wr64HudMotion.generation &&
                            (desc.wr64HudMotion.kind == 2 || desc.wr64HudMotion.kind == 3)) continue;
                        // Authenticated native DP positions have a separate
                        // float path. Everything else keeps the R3 block below.
                        if (wr64DolphinSunClaimValid(desc, drawData, true)) continue;
                        uint64_t texture = 0;
                        if ((desc.tileCount > 0) && (desc.tileIndex < drawData.callTiles.size())) {
                            texture = drawData.callTiles[desc.tileIndex].tmemHashOrID;
                        }
                        int idx = wr64CelestialTextureIndex(texture);
                        if (idx < 0) {
                            // Every message can have a new texture hash. The
                            // measured render state identifies the family.
                            if (wr64CelestialDpTextState(desc.colorCombiner.H, desc.colorCombiner.L,
                                desc.otherMode.H, desc.otherMode.L, desc.rect.uly))
                            {
                                idx = 5;
                                wr64CelestialFingerprintNote();
                            }
                            else if (wr64CelestialDpStripState(desc.colorCombiner.H, desc.colorCombiner.L,
                                desc.otherMode.H, desc.otherMode.L, desc.rect.uly))
                            {
                                // The four background strips have their own
                                // count; they must not displace text pairing.
                                idx = 6;
                                wr64CelestialStripNote();
                            }
                            else {
                                continue;
                            }
                        }
                        else if (idx >= 6) {
                            // A pinned message is rebaked as columns exit.
                            // All known message hashes share the same family;
                            // the crop/continuity guards below validate pairs.
                            idx = 5;
                        }
                        const uint32_t view = wr64CelestialRectView(idx, desc.scissorRect);
                        out[view * Wr64CelestialTextureCount + idx].push_back(Wr64CelClaim{
                            wr64CelestialRectKey(f, p, c), texture, desc.rect,
                            desc.tileIndex, desc.tileCount,
                            proj.gameCalls[c].meshDesc.rawVertexStart });
                    }
                }
            }
        };

        wr64CelCollect(curWorkload, wr64CelCurByView);
        wr64CelCollect(prevWorkload, wr64CelPrevByView);

        size_t wr64CelPaired = 0;
        for (uint32_t bucket = 0; bucket < wr64CelViewCount * Wr64CelestialTextureCount; bucket++) {
            const int i = int(bucket % Wr64CelestialTextureCount);
            auto *wr64CelCur = wr64CelCurByView + bucket - i;
            auto *wr64CelPrev = wr64CelPrevByView + bucket - i;
            // EQUAL COUNT, per texture. Order is only identity while the count
            // holds; a changed count refuses this texture for this tick, which
            // is one held frame.
            if (wr64CelCur[i].empty() || (wr64CelCur[i].size() != wr64CelPrev[i].size())) {
                continue;
            }

            for (size_t n = 0; n < wr64CelCur[i].size(); n++) {
                // SAME TEXTURE ON BOTH SIDES, always. The state claim can put
                // two DIFFERENT messages in one slot while one scrolls out and
                // the next scrolls in; order keeps them aligned, and this
                // guard makes a swapped order a skipped pair instead of one
                // message blending into another.
                if (wr64CelCur[i][n].texture != wr64CelPrev[i][n].texture) {
                    // A left-pinned message can rebake after cropping exited texture columns.
                    // Recognize identical left/top/bottom edges and a small right-edge reduction.
                    // Use the current rectangle shifted by the cropped width as the previous-frame
                    // stand-in. The two bakes have incomparable UV spaces, so skip the UV fold below.
                    if ((i != 5) && (i != 6)) {
                        continue;
                    }
                    const FixedRect &wr64CelCropPrev = wr64CelPrev[i][n].rect;
                    const FixedRect &wr64CelCropCur = wr64CelCur[i][n].rect;
                    const int32_t wr64CelCropStep = wr64CelCropPrev.lrx - wr64CelCropCur.lrx;
                    if ((wr64CelCropPrev.ulx != wr64CelCropCur.ulx) ||
                        (wr64CelCropPrev.uly != wr64CelCropCur.uly) ||
                        (wr64CelCropPrev.lry != wr64CelCropCur.lry) ||
                        (wr64CelCropStep <= 0) || (wr64CelCropStep > 32))
                    {
                        continue;
                    }
                    // FORWARD, like the pinned fold (R12): gliding from cur
                    // toward the next step keeps the moving edge under the
                    // crop line; the backward stand-in started every tick
                    // 2px right of it and flashed background at 20 Hz.
                    FixedRect wr64CelCropAhead = wr64CelCropCur;
                    wr64CelCropAhead.ulx -= wr64CelCropStep;
                    wr64CelCropAhead.lrx -= wr64CelCropStep;
                    curWorkload.wr64CelestialPrevRects.push_back(Workload::Wr64CelestialRectPair{
                        wr64CelCur[i][n].key, wr64CelCropCur, wr64CelCropAhead });
                    wr64CelPaired++;
                    wr64CelestialCropNote();
                    continue;
                }
                const FixedRect &cur = wr64CelCur[i][n].rect;
                // A COPY, not a reference: the UV-shift fold below edits the
                // previous rect's corners before the pair is stored.
                FixedRect prev = wr64CelPrev[i][n].rect;
                // The stored pair's CUR side. Normally cur verbatim; the
                // pinned-rect forward fold (R12) shifts it instead of prev.
                FixedRect wr64CelCurOut = cur;

                // THE DP SUN PARK TRANSIT (DPSUN R1). Full account with the
                // measurements in rt64_wr64_celestial_identity.h. A shortened
                // (parked) rect's true position is the full-height rect
                // ending at its authored bottom; pairs involving a parked
                // side exist ONLY while the height actively moves (>= 8 qpx
                // per tick, or crossing the full/park boundary), with the
                // parked side(s) reconstructed before pairing. Plateau and
                // deep-park frames pair with nothing - the renderer collapses
                // exactly the parked frames that carry no pair, so the pale
                // square stays suppressed while exits and entries glide
                // through the top edge on real geometry. Slot 3 is the
                // Dolphin Park disk (Wr64CelestialSunDiskDP), the one
                // texture the park rule is scoped to.
                if (i == 3) {
                    // Reconstruct only the recent exit tail. Persistent parked rectangles can
                    // move horizontally without the accompanying real-sun effects; they must
                    // remain suppressed. Wr64CelestialDpExitTailTicks bounds reconstruction
                    // relative to the last full disk frame.
                    const bool wr64DpPrevParked =
                        wr64CelestialDpParkShortened(prev.uly, prev.lry);
                    const bool wr64DpCurParked =
                        wr64CelestialDpParkShortened(cur.uly, cur.lry);
                    if (!wr64DpCurParked && !wr64DpPrevParked) {
                        // FULL and staying full: remember the frame, pair
                        // through the normal path below.
                        wr64DpLastFullFrame = curWorkload.submissionFrame;
                    }
                    else if (wr64DpPrevParked || wr64DpCurParked) {
                        bool wr64DpDraw = false;
                        if (!wr64DpCurParked) {
                            // ENTRY: parked -> full. One reconstructed
                            // pair; the full frame brings the flares.
                            wr64DpDraw = true;
                            wr64DpLastFullFrame = curWorkload.submissionFrame;
                        }
                        else if (!wr64DpPrevParked) {
                            // EXIT START: full -> parked.
                            wr64DpDraw = true;
                        }
                        else if ((curWorkload.submissionFrame >= wr64DpLastFullFrame) &&
                                 ((curWorkload.submissionFrame - wr64DpLastFullFrame) <=
                                  uint64_t(Wr64CelestialDpExitTailTicks)) &&
                                 ((prev.lry - cur.lry) >= Wr64CelestialDpParkTransitStepQuarterPx))
                        {
                            // EXIT TAIL: still within reach of the real sun
                            // and still strictly shrinking.
                            wr64DpDraw = true;
                        }
                        if (!wr64DpDraw) {
                            continue;
                        }
                        if (wr64DpPrevParked) {
                            prev.uly = (prev.lry - Wr64CelestialDpFullRectQuarterPx) * 2;
                            prev.lry = prev.uly + Wr64CelestialDpFullRectQuarterPx;
                        }
                        if (wr64DpCurParked) {
                            wr64CelCurOut.uly =
                                (wr64CelCurOut.lry - Wr64CelestialDpFullRectQuarterPx) * 2;
                            wr64CelCurOut.lry =
                                wr64CelCurOut.uly + Wr64CelestialDpFullRectQuarterPx;
                        }
                        curWorkload.wr64CelestialPrevRects.push_back(Workload::Wr64CelestialRectPair{
                            wr64CelCur[i][n].key, prev, wr64CelCurOut });
                        wr64CelPaired++;
                        wr64CelestialUnparkNote();
                        continue;
                    }
                }

                // Continuity on the rect centre, quarter-pixels. Generous on
                // purpose - fast pans MUST interpolate; see the header.
                const float dx = float(cur.ulx + cur.lrx) * 0.5f - float(prev.ulx + prev.lrx) * 0.5f;
                const float dy = float(cur.uly + cur.lry) * 0.5f - float(prev.uly + prev.lry) * 0.5f;
                if (((dx * dx) + (dy * dy)) >
                    (Wr64CelestialMaxStepQuarterPx * Wr64CelestialMaxStepQuarterPx))
                {
                    continue;
                }

                // Scrolling messages move their rectangle until its left edge reaches the crop;
                // then TEXREC's S coordinate advances, baked into per-vertex UVs by RDP::drawRect.
                // Fold that UV delta into screen-rectangle motion because rectangle draws have
                // no texcoord-velocity path. Limit both fold directions to message boxes and
                // letter strips. Celestial edge-clamped rectangles require the plain corner
                // blend; applying message folds can open seams or separate disk and glow.
                const bool wr64CelMessageSlot = (i == 5) || (i == 6);
                if (wr64CelMessageSlot) {
                    const std::vector<float> &curTc = curWorkload.drawData.triTcFloats;
                    const std::vector<float> &prevTc = prevWorkload.drawData.triTcFloats;
                    const size_t curBase = size_t(wr64CelCur[i][n].rawVertexStart) * 2;
                    const size_t prevBase = size_t(wr64CelPrev[i][n].rawVertexStart) * 2;
                    // Vertex 0 carries (u1, v1) and vertex 3 carries (u2, v2)
                    // regardless of the flip flag - see the emplace order in
                    // RDP::drawRect.
                    if (((curBase + 8) <= curTc.size()) && ((prevBase + 8) <= prevTc.size())) {
                        const float u1c = curTc[curBase + 0], v1c = curTc[curBase + 1];
                        const float u2c = curTc[curBase + 6], v2c = curTc[curBase + 7];
                        const float u1p = prevTc[prevBase + 0], v1p = prevTc[prevBase + 1];
                        const float u2p = prevTc[prevBase + 6], v2p = prevTc[prevBase + 7];
                        // Texels-to-quarter-pixels scale, derived from the
                        // CURRENT call's own rect/UV span so it is exact for
                        // whatever dsdx the game used. Degenerate spans (a
                        // rect shrunk to a sliver) skip the adjustment; the
                        // one dropped tick pops instead of smearing.
                        const float du = u2c - u1c;
                        const float dv = v2c - v1c;
                        // Pinned messages use [cur -> cur-shift] so their moving edge remains under
                        // the crop for the whole tick. Moving rectangles use the backward fold.
                        // Test the left corner and y band for pinning; the right edge shrinks during
                        // exit. Starting at the current rectangle also agrees with output frames that
                        // have no previous-frame pair, keeping the text continuous across that boundary.
                        const bool wr64CelPinned =
                            (prev.ulx == cur.ulx) && (prev.uly == cur.uly) &&
                            (prev.lry == cur.lry);
                        if ((std::fabs(du) > 1e-4f) &&
                            ((u1c != u1p) || (u2c != u2p))) {
                            const float kx = float(cur.lrx - cur.ulx) / du;
                            if (std::fabs(kx) < 65536.0f) {
                                const int32_t sx1 = int32_t(std::lround(kx * (u1c - u1p)));
                                const int32_t sx2 = int32_t(std::lround(kx * (u2c - u2p)));
                                if (wr64CelPinned && (sx1 != 0)) {
                                    // The CONTENT shift (u1's) moves both
                                    // corners: the rect glides whole toward
                                    // next tick's position. prev must be the
                                    // RAW current rect - with the old
                                    // all-corners test prev==cur held by
                                    // definition, with lrx free it does not.
                                    wr64CelCurOut.ulx -= sx1;
                                    wr64CelCurOut.lrx -= sx1;
                                    prev = cur;
                                    wr64CelestialPinnedNote();
                                }
                                else {
                                    prev.ulx += sx1;
                                    prev.lrx += sx2;
                                    wr64CelestialUvNote();
                                }
                            }
                        }
                        if ((std::fabs(dv) > 1e-4f) &&
                            ((v1c != v1p) || (v2c != v2p))) {
                            const float ky = float(cur.lry - cur.uly) / dv;
                            if (std::fabs(ky) < 65536.0f) {
                                const int32_t sy1 = int32_t(std::lround(ky * (v1c - v1p)));
                                const int32_t sy2 = int32_t(std::lround(ky * (v2c - v2p)));
                                if (wr64CelPinned) {
                                    wr64CelCurOut.uly -= sy1;
                                    wr64CelCurOut.lry -= sy2;
                                    wr64CelestialPinnedNote();
                                }
                                else {
                                    prev.uly += sy1;
                                    prev.lry += sy2;
                                    wr64CelestialUvNote();
                                }
                            }
                        }
                    }
                }

                curWorkload.wr64CelestialPrevRects.push_back(Workload::Wr64CelestialRectPair{
                    wr64CelCur[i][n].key, prev, wr64CelCurOut });
                // The paired rect's TILES as well. Measured: the DP text does
                // NOT scroll through the tile (R4's announce never fired), so
                // for today's claim list this pairs values that are already
                // equal and blends nothing - it stays because it is the
                // correct guard for any future claimed rect whose game DOES
                // scroll the tile window, and the registration loop it feeds
                // now also serves the stunt rings.
                const uint32_t wr64CelTileN =
                    std::min(wr64CelCur[i][n].tileCount, wr64CelPrev[i][n].tileCount);
                for (uint32_t t = 0; t < wr64CelTileN; t++) {
                    curWorkload.wr64CelestialTilePairs.push_back(Workload::Wr64CelestialTilePair{
                        wr64CelCur[i][n].tileIndex + t, wr64CelPrev[i][n].tileIndex + t });
                }
                wr64CelPaired++;
            }
        }

        wr64CelestialNote(wr64CelPaired);
    }

    static bool wr64WaterCoverageRingEnabled() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_WATER_COVERAGE_RING");
            return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
        }();
        return enabled;
    }

    static bool wr64WaterTrailingPatchEnabled() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_WATER_TRAILING_PATCH");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        return enabled;
    }

    // Diagnostic combination candidate: preserve the stock far fan's six
    // outer vertices and their native interpolation, give only its six private
    // inner duplicates that same common X/Z slot delta, and sweep the dense
    // 72-edge boundary strip by the identical delta. Y/UV for the inner six
    // continue to use the accepted primary water interpolation.
    static bool wr64WaterCoherentFanStripEnabled() {
        static const bool enabled = []() {
            const char *value = std::getenv(
                "WR64_WATER_COHERENT_FAN_STRIP");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        return enabled;
    }

    // Replacement for the stock six-corner flat fan. The accepted 488-vertex
    // ripple field remains the literal inner boundary; four dense, shared
    // 72-vertex rings connect it to the stock outer perimeter without any
    // presentation-time reset/extrusion. This is the normal water path, not
    // an experiment selected through a runtime flag.
    static bool wr64WaterDenseAnnulusEnabled() {
        return true;
    }

    struct Wr64PrimaryWaterDatum {
        double height = 0.0;
        double spread = 0.0;
    };

    // Measure the native sheet's common vertical datum from one representative
    // of each logical producer. The 488 physical primary vertices contain 19
    // duplicated source addresses, leaving 469 independent water producers.
    // A median follows whole-sheet tide motion without being biased by wave
    // crests or troughs. Use the decoded VTX source identity rather than the
    // separately sampled mutable producer-key table. Augmentation verifies
    // coincident payloads before any generated surface reaches this helper.
    static bool measureWr64PrimaryWaterDatum(const DrawData &drawData,
        uint32_t waterBase, Wr64PrimaryWaterDatum &datum,
        const std::vector<float> *stagedPositions = nullptr)
    {
        // Extended changes the native flat boundary after Roundness. Keep the
        // accepted pre-recovery median for every neutral annulus endpoint.
        if (!stagedPositions && drawData.wr64WaveDistance.valid && drawData.wr64WaveDistance.mode) {
            datum.height = drawData.wr64WaveDistance.originalDatum;
            datum.spread = drawData.wr64WaveDistance.originalSpread;
            return std::isfinite(datum.height) && std::isfinite(datum.spread);
        }
        constexpr uint32_t PrimaryVertexCount = 488U;
        constexpr uint32_t LogicalProducerCount = 469U;
        const uint32_t vertexCount = drawData.vertexCount();
        const auto &positions = stagedPositions ? *stagedPositions : drawData.posFloats;
        if ((uint64_t(waterBase) + PrimaryVertexCount > vertexCount) ||
            (positions.size() != size_t(vertexCount) * 3ULL) ||
            (drawData.wr64WaterProducerKeys.size() != vertexCount) ||
            (drawData.vertexSegmentedAddresses.size() != vertexCount))
        {
            return false;
        }

        std::map<uint64_t, uint32_t> representativeByKey;
        for (uint32_t local = 0U; local < PrimaryVertexCount; local++) {
            const uint32_t vertex = waterBase + local;
            const uint32_t address =
                drawData.vertexSegmentedAddresses[vertex];
            if (!isWr64GeneratedWaterVertexAddress(address)) return false;

            representativeByKey.emplace(uint64_t(address), vertex);
        }
        if (representativeByKey.size() != LogicalProducerCount) return false;

        std::vector<double> heights;
        heights.reserve(LogicalProducerCount);
        double minimumHeight = std::numeric_limits<double>::infinity();
        double maximumHeight = -std::numeric_limits<double>::infinity();
        for (const auto &entry : representativeByKey) {
            const double height =
                double(positions[entry.second * 3U + 1U]);
            if (!std::isfinite(height)) return false;
            heights.push_back(height);
            minimumHeight = std::min(minimumHeight, height);
            maximumHeight = std::max(maximumHeight, height);
        }

        const size_t medianIndex = heights.size() / 2ULL;
        std::nth_element(heights.begin(), heights.begin() + medianIndex,
            heights.end());
        datum.height = heights[medianIndex];
        datum.spread = maximumHeight - minimumHeight;
        return std::isfinite(datum.height) && std::isfinite(datum.spread);
    }

    // Optional presentation-safe wave rounding. The normalized value is
    // exposed by the frontend slider below. The environment variable remains
    // the startup seed for non-frontend and first-run configurations; zero
    // preserves the milestone geometry byte-for-byte and 0.5 moves each
    // eligible height halfway toward its six-neighbour mean.
    static std::atomic<float> &wr64WaterLaplacianStrengthStorage() {
        static std::atomic<float> strength = []() {
            const char *value = std::getenv(
                "WR64_WATER_LAPLACIAN_STRENGTH");
            if ((value == nullptr) || (value[0] == '\0')) return 0.0f;

            char *end = nullptr;
            const float parsed = std::strtof(value, &end);
            if ((end == value) || (end == nullptr) || (end[0] != '\0') ||
                !std::isfinite(parsed))
            {
                return 0.0f;
            }

            return std::clamp(parsed, 0.0f, 1.0f);
        }();
        return strength;
    }

    void setWr64WaterLaplacianStrength(float strength) {
        if (!std::isfinite(strength)) strength = 0.0f;
        wr64WaterLaplacianStrengthStorage().store(
            std::clamp(strength, 0.0f, 1.0f),
            std::memory_order_relaxed);
    }

    float getWr64WaterLaplacianStrength() {
        return wr64WaterLaplacianStrengthStorage().load(
            std::memory_order_relaxed);
    }

    static bool wr64WaterBridgeStitchEnabled() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_WATER_BRIDGE_STITCH");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        return enabled;
    }

    // Presentation-only treatment for the stock twelve-triangle far-water
    // bridge. The primary 488-vertex ripple field is never written. Instead,
    // each of the bridge's twelve private vertices evaluates height and UV
    // from its nearest primary-field vertex while retaining its own current
    // X/Z coverage position. This removes the constant (y=0, uv=16,16) fan
    // presentation without translating, freezing, or otherwise changing the
    // interpolated ripple sheet.
    static bool wr64WaterRippleBridgeEnabled() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_WATER_RIPPLE_BRIDGE");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        return enabled;
    }

    static bool wr64WaterSuppressBridgeEnabled() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_WATER_SUPPRESS_BRIDGE");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        return enabled;
    }

    static bool wr64WaterBoundarySkirtEnabled() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_WATER_BOUNDARY_SKIRT");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        return enabled;
    }

    // Diagnostic only: omit the isolated final twelve triangles while leaving
    // the proven 864-triangle primary water field and every one of its vertex
    // attributes unchanged. This distinguishes the bridge itself from a hole
    // or lower layer before constructing any replacement coverage.
    static bool suppressWr64WaterBridge(Workload &workload,
        Projection &projection, uint32_t callIndex)
    {
        if (!wr64WaterSuppressBridgeEnabled() ||
            (callIndex >= projection.gameCallCount))
        {
            return false;
        }

        DrawData &drawData = workload.drawData;
        GameCall &waterCall = projection.gameCalls[callIndex];
        const uint32_t originalTriangleCount = waterCall.callDesc.triangleCount;
        const uint64_t faceStart = waterCall.meshDesc.faceIndicesStart;
        const uint64_t primaryFaceEnd = faceStart + (864ULL * 3ULL);
        if ((originalTriangleCount != 876U) ||
            (primaryFaceEnd > drawData.faceIndices.size()))
        {
            return false;
        }

        waterCall.callDesc.triangleCount = 864U;
        drawData.wr64WaterFaceIndices.assign(
            drawData.faceIndices.begin() + size_t(faceStart),
            drawData.faceIndices.begin() + size_t(primaryFaceEnd));
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
            "[water-suppress-bridge] frame=%llu primary=864 omitted=12\n",
            static_cast<unsigned long long>(workload.submissionFrame)); }
        return true;
    }

    // Replace the coarse six-corner bridge with a single dense skirt built
    // from the primary field's true 108-edge boundary. The outer copy of each
    // boundary vertex is placed on the stock far perimeter, but mode 6 clamps
    // its presented height and UV to that boundary source. This is deliberately
    // not wave extrapolation: it adds no gradients, layers, field sampling, or
    // motion to the accepted 488-vertex primary sheet.
    static bool augmentWr64WaterBoundarySkirt(Workload &workload,
        Projection &projection, uint32_t callIndex)
    {
        if (!wr64WaterBoundarySkirtEnabled() ||
            (callIndex >= projection.gameCallCount))
        {
            return false;
        }

        DrawData &drawData = workload.drawData;
        GameCall &waterCall = projection.gameCalls[callIndex];
        const uint32_t originalTriangleCount = waterCall.callDesc.triangleCount;
        const uint64_t faceStart = waterCall.meshDesc.faceIndicesStart;
        const uint64_t faceEnd = faceStart + uint64_t(originalTriangleCount) * 3ULL;
        if ((originalTriangleCount != 876U) ||
            (faceEnd > drawData.faceIndices.size()) ||
            (drawData.wr64WaterProducerKeys.size() != drawData.vertexCount()) ||
            (drawData.wr64WaterFieldInfo.size() !=
                size_t(drawData.vertexCount()) * 4ULL) ||
            (drawData.wr64WaterFieldPrevPosShiftX.size() != drawData.vertexCount()) ||
            (drawData.wr64WaterFieldPrevTcShiftZ.size() != drawData.vertexCount()))
        {
            return false;
        }

        struct BoundaryEdge {
            uint32_t a = 0;
            uint32_t b = 0;
            uint32_t count = 0;
        };
        std::map<std::pair<uint32_t, uint32_t>, BoundaryEdge> edgeMap;
        std::set<uint32_t> primaryVertices;
        for (uint32_t triangle = 0; triangle < 864U; triangle++) {
            const uint32_t offset = uint32_t(faceStart) + triangle * 3U;
            const uint32_t tri[3] = {
                drawData.faceIndices[offset + 0],
                drawData.faceIndices[offset + 1],
                drawData.faceIndices[offset + 2]
            };
            for (uint32_t corner = 0; corner < 3U; corner++) {
                const uint32_t vertex = tri[corner];
                if ((vertex >= drawData.wr64WaterProducerKeys.size()) ||
                    (drawData.wr64WaterProducerKeys[vertex] == 0))
                {
                    return false;
                }
                primaryVertices.insert(vertex);
                const uint32_t a = tri[corner];
                const uint32_t b = tri[(corner + 1U) % 3U];
                const auto key = (a < b) ? std::make_pair(a, b) :
                    std::make_pair(b, a);
                BoundaryEdge &edge = edgeMap[key];
                if (edge.count == 0) {
                    edge.a = a;
                    edge.b = b;
                }
                edge.count++;
            }
        }

        std::vector<BoundaryEdge> boundaryEdges;
        std::set<uint32_t> boundaryVertices;
        for (const auto &entry : edgeMap) {
            if (entry.second.count != 1U) continue;
            boundaryEdges.push_back(entry.second);
            boundaryVertices.insert(entry.second.a);
            boundaryVertices.insert(entry.second.b);
        }
        if ((boundaryEdges.size() != 108U) ||
            (boundaryVertices.size() != 108U))
        {
            return false;
        }

        std::set<uint32_t> privateInner;
        std::set<uint32_t> outerCornersSet;
        for (uint32_t triangle = 864U; triangle < 876U; triangle++) {
            const uint32_t offset = uint32_t(faceStart) + triangle * 3U;
            for (uint32_t corner = 0; corner < 3U; corner++) {
                const uint32_t vertex = drawData.faceIndices[offset + corner];
                if (vertex >= drawData.wr64WaterProducerKeys.size()) return false;
                if (drawData.wr64WaterProducerKeys[vertex] == 0)
                    outerCornersSet.insert(vertex);
                else if (primaryVertices.count(vertex) == 0)
                    privateInner.insert(vertex);
            }
        }
        if ((privateInner.size() != 6U) || (outerCornersSet.size() != 6U)) {
            return false;
        }

        std::vector<uint32_t> innerCorners;
        innerCorners.reserve(6);
        for (uint32_t inner : privateInner) {
            uint32_t match = UINT32_MAX;
            for (uint32_t boundary : boundaryVertices) {
                if (drawData.wr64WaterProducerKeys[boundary] ==
                    drawData.wr64WaterProducerKeys[inner])
                {
                    match = boundary;
                    break;
                }
            }
            if (match == UINT32_MAX) return false;
            innerCorners.push_back(match);
        }
        std::vector<uint32_t> outerCorners(
            outerCornersSet.begin(), outerCornersSet.end());
        const auto sortByAngle = [&](std::vector<uint32_t> &vertices) {
            double centerX = 0.0;
            double centerZ = 0.0;
            for (uint32_t vertex : vertices) {
                centerX += drawData.posFloats[vertex * 3U + 0U];
                centerZ += drawData.posFloats[vertex * 3U + 2U];
            }
            centerX /= double(vertices.size());
            centerZ /= double(vertices.size());
            std::sort(vertices.begin(), vertices.end(),
                [&](uint32_t a, uint32_t b) {
                    return std::atan2(
                        double(drawData.posFloats[a * 3U + 2U]) - centerZ,
                        double(drawData.posFloats[a * 3U + 0U]) - centerX) <
                        std::atan2(
                        double(drawData.posFloats[b * 3U + 2U]) - centerZ,
                        double(drawData.posFloats[b * 3U + 0U]) - centerX);
                });
        };
        sortByAngle(innerCorners);
        sortByAngle(outerCorners);

        double innerCenterX = 0.0, innerCenterZ = 0.0;
        double outerCenterX = 0.0, outerCenterZ = 0.0;
        for (uint32_t i = 0; i < 6U; i++) {
            innerCenterX += drawData.posFloats[innerCorners[i] * 3U + 0U];
            innerCenterZ += drawData.posFloats[innerCorners[i] * 3U + 2U];
            outerCenterX += drawData.posFloats[outerCorners[i] * 3U + 0U];
            outerCenterZ += drawData.posFloats[outerCorners[i] * 3U + 2U];
        }
        innerCenterX /= 6.0; innerCenterZ /= 6.0;
        outerCenterX /= 6.0; outerCenterZ /= 6.0;
        uint32_t bestRotation = 0;
        double bestCost = std::numeric_limits<double>::max();
        for (uint32_t rotation = 0; rotation < 6U; rotation++) {
            double cost = 0.0;
            for (uint32_t i = 0; i < 6U; i++) {
                double ix = drawData.posFloats[innerCorners[i] * 3U + 0U] - innerCenterX;
                double iz = drawData.posFloats[innerCorners[i] * 3U + 2U] - innerCenterZ;
                const uint32_t outer = outerCorners[(i + rotation) % 6U];
                double ox = drawData.posFloats[outer * 3U + 0U] - outerCenterX;
                double oz = drawData.posFloats[outer * 3U + 2U] - outerCenterZ;
                const double il = std::hypot(ix, iz);
                const double ol = std::hypot(ox, oz);
                if ((il > 1.0e-6) && (ol > 1.0e-6)) {
                    ix /= il; iz /= il; ox /= ol; oz /= ol;
                    cost += (ix - ox) * (ix - ox) + (iz - oz) * (iz - oz);
                }
            }
            if (cost < bestCost) { bestCost = cost; bestRotation = rotation; }
        }
        std::rotate(outerCorners.begin(),
            outerCorners.begin() + bestRotation, outerCorners.end());

        std::map<uint32_t, uint32_t> outerCopies;
        const uint32_t oldVertexCount = drawData.vertexCount();
        for (uint32_t source : boundaryVertices) {
            const double px = drawData.posFloats[source * 3U + 0U];
            const double pz = drawData.posFloats[source * 3U + 2U];
            uint32_t side = 0;
            float sideT = 0.0f;
            double bestDistance = std::numeric_limits<double>::max();
            for (uint32_t candidate = 0; candidate < 6U; candidate++) {
                const uint32_t a = innerCorners[candidate];
                const uint32_t b = innerCorners[(candidate + 1U) % 6U];
                const double ax = drawData.posFloats[a * 3U + 0U];
                const double az = drawData.posFloats[a * 3U + 2U];
                const double dx = drawData.posFloats[b * 3U + 0U] - ax;
                const double dz = drawData.posFloats[b * 3U + 2U] - az;
                const double lengthSquared = dx * dx + dz * dz;
                const double t = (lengthSquared > 1.0e-8) ? std::clamp(
                    ((px - ax) * dx + (pz - az) * dz) / lengthSquared,
                    0.0, 1.0) : 0.0;
                const double ex = px - (ax + dx * t);
                const double ez = pz - (az + dz * t);
                const double distance = ex * ex + ez * ez;
                if (distance < bestDistance) {
                    bestDistance = distance;
                    side = candidate;
                    sideT = float(t);
                }
            }

            const uint32_t outerA = outerCorners[side];
            const uint32_t outerB = outerCorners[(side + 1U) % 6U];
            const uint32_t appended = drawData.vertexCount();
            outerCopies.emplace(source, appended);
            const float position[3] = {
                drawData.posFloats[outerA * 3U + 0U] +
                    (drawData.posFloats[outerB * 3U + 0U] -
                    drawData.posFloats[outerA * 3U + 0U]) * sideT,
                drawData.posFloats[source * 3U + 1U],
                drawData.posFloats[outerA * 3U + 2U] +
                    (drawData.posFloats[outerB * 3U + 2U] -
                    drawData.posFloats[outerA * 3U + 2U]) * sideT
            };
            const float velocity[3] = {
                drawData.velFloats[source * 3U + 0U],
                drawData.velFloats[source * 3U + 1U],
                drawData.velFloats[source * 3U + 2U]
            };
            const float texcoord[2] = {
                drawData.tcFloats[source * 2U + 0U],
                drawData.tcFloats[source * 2U + 1U]
            };
            const float texcoordVelocity[2] = {
                drawData.tcVelFloats[source * 2U + 0U],
                drawData.tcVelFloats[source * 2U + 1U]
            };
            const uint8_t normalColor[4] = {
                drawData.normColBytes[source * 4U + 0U],
                drawData.normColBytes[source * 4U + 1U],
                drawData.normColBytes[source * 4U + 2U],
                drawData.normColBytes[source * 4U + 3U]
            };
            drawData.posFloats.insert(drawData.posFloats.end(), position, position + 3);
            drawData.velFloats.insert(drawData.velFloats.end(), velocity, velocity + 3);
            drawData.tcFloats.insert(drawData.tcFloats.end(), texcoord, texcoord + 2);
            drawData.tcVelFloats.insert(drawData.tcVelFloats.end(),
                texcoordVelocity, texcoordVelocity + 2);
            drawData.normColBytes.insert(drawData.normColBytes.end(),
                normalColor, normalColor + 4);
            drawData.viewProjIndices.push_back(drawData.viewProjIndices[source]);
            drawData.worldIndices.push_back(drawData.worldIndices[source]);
            drawData.fogIndices.push_back(drawData.fogIndices[source]);
            drawData.lightIndices.push_back(drawData.lightIndices[source]);
            drawData.lightCounts.push_back(drawData.lightCounts[source]);
            drawData.lookAtIndices.push_back(drawData.lookAtIndices[source]);
            drawData.vertexSegmentedAddresses.push_back(
                drawData.vertexSegmentedAddresses[source]);
            drawData.wr64WaterProducerKeys.push_back(0);
            drawData.wr64WaterVertexMask.push_back(4);
            const uint32_t info[4] = { 6U, source, 0U, 0U };
            drawData.wr64WaterFieldInfo.insert(
                drawData.wr64WaterFieldInfo.end(), info, info + 4);
            drawData.wr64WaterFieldPrevPosShiftX.push_back(hlslpp::float4(0.0f));
            drawData.wr64WaterFieldPrevTcShiftZ.push_back(hlslpp::float4(0.0f));
        }

        std::vector<uint32_t> skirtFaces;
        skirtFaces.reserve(boundaryEdges.size() * 6ULL);
        for (const BoundaryEdge &edge : boundaryEdges) {
            const uint32_t outerA = outerCopies.at(edge.a);
            const uint32_t outerB = outerCopies.at(edge.b);
            skirtFaces.insert(skirtFaces.end(), {
                edge.b, edge.a, outerA,
                edge.b, outerA, outerB });
        }

        std::vector<uint32_t> combinedFaces;
        combinedFaces.reserve((864U * 3U) + skirtFaces.size());
        combinedFaces.insert(combinedFaces.end(),
            drawData.faceIndices.begin() + size_t(faceStart),
            drawData.faceIndices.begin() + size_t(faceStart) + (864U * 3U));
        combinedFaces.insert(combinedFaces.end(), skirtFaces.begin(), skirtFaces.end());
        waterCall.meshDesc.faceIndicesStart = uint32_t(drawData.faceIndices.size());
        waterCall.callDesc.triangleCount = uint32_t(combinedFaces.size() / 3U);
        drawData.faceIndices.insert(drawData.faceIndices.end(),
            combinedFaces.begin(), combinedFaces.end());
        drawData.wr64WaterFaceIndices = combinedFaces;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
            "[water-boundary-skirt] frame=%llu primary=864 boundary=%zu added_vertices=%u added_triangles=%zu\n",
            static_cast<unsigned long long>(workload.submissionFrame),
            boundaryEdges.size(), drawData.vertexCount() - oldVertexCount,
            skirtFaces.size() / 3U); }
        return true;
    }

    // The final twelve stock triangles use six private copies of primary-field
    // corner vertices.  WR64_WATER_RIGID_BRIDGE deliberately gives that
    // isolated twelve-vertex bridge one coherent endpoint delta, which keeps
    // the flat fan from sweeping across the lower viewport but separates its
    // private inner corners from the untouched ripple field between native
    // endpoints.  Fill exactly that fractional-frame separation with a ring
    // that is degenerate at both native endpoints.  No vertex data is added or
    // changed; the accepted 488-vertex ripple interpolation remains bit exact.
    static bool augmentWr64WaterBridgeStitch(Workload &workload,
        Projection &projection, uint32_t callIndex)
    {
        if (!wr64WaterBridgeStitchEnabled() ||
            (callIndex >= projection.gameCallCount))
        {
            return false;
        }

        DrawData &drawData = workload.drawData;
        GameCall &waterCall = projection.gameCalls[callIndex];
        const uint32_t originalTriangleCount = waterCall.callDesc.triangleCount;
        const uint64_t faceStart = waterCall.meshDesc.faceIndicesStart;
        const uint64_t faceEnd = faceStart + uint64_t(originalTriangleCount) * 3ULL;
        if ((originalTriangleCount != 876) ||
            (faceEnd > drawData.faceIndices.size()) ||
            (drawData.wr64WaterProducerKeys.size() != drawData.vertexCount()))
        {
            return false;
        }

        std::set<uint32_t> primaryVertices;
        std::set<uint32_t> bridgeVertices;
        for (uint32_t triangle = 0; triangle < originalTriangleCount; triangle++) {
            const uint32_t offset = uint32_t(faceStart) + triangle * 3;
            for (uint32_t corner = 0; corner < 3; corner++) {
                const uint32_t vertex = drawData.faceIndices[offset + corner];
                if (triangle < 864) primaryVertices.insert(vertex);
                else bridgeVertices.insert(vertex);
            }
        }

        struct StitchPair {
            uint32_t primary = 0;
            uint32_t inner = 0;
            double angle = 0.0;
        };
        std::vector<uint32_t> privateInner;
        for (uint32_t vertex : bridgeVertices) {
            if ((primaryVertices.count(vertex) == 0) &&
                (vertex < drawData.wr64WaterProducerKeys.size()) &&
                (drawData.wr64WaterProducerKeys[vertex] != 0))
            {
                privateInner.push_back(vertex);
            }
        }
        if (privateInner.size() != 6) return false;

        double centerX = 0.0;
        double centerZ = 0.0;
        for (uint32_t inner : privateInner) {
            centerX += double(drawData.posFloats[inner * 3 + 0]);
            centerZ += double(drawData.posFloats[inner * 3 + 2]);
        }
        centerX /= 6.0;
        centerZ /= 6.0;

        std::vector<StitchPair> pairs;
        pairs.reserve(6);
        std::set<uint32_t> usedPrimary;
        for (uint32_t inner : privateInner) {
            const double ix = double(drawData.posFloats[inner * 3 + 0]);
            const double iy = double(drawData.posFloats[inner * 3 + 1]);
            const double iz = double(drawData.posFloats[inner * 3 + 2]);
            uint32_t best = UINT32_MAX;
            double bestDistance = std::numeric_limits<double>::max();
            for (uint32_t primary : primaryVertices) {
                if (usedPrimary.count(primary) != 0) continue;
                const double dx = ix - double(drawData.posFloats[primary * 3 + 0]);
                const double dy = iy - double(drawData.posFloats[primary * 3 + 1]);
                const double dz = iz - double(drawData.posFloats[primary * 3 + 2]);
                const double distance = dx * dx + dy * dy + dz * dz;
                if (distance < bestDistance) {
                    bestDistance = distance;
                    best = primary;
                }
            }
            if ((best == UINT32_MAX) || (bestDistance > 1.0e-6)) return false;
            usedPrimary.insert(best);
            pairs.push_back(StitchPair{ best, inner,
                std::atan2(iz - centerZ, ix - centerX) });
        }
        std::sort(pairs.begin(), pairs.end(), [](const StitchPair &a,
            const StitchPair &b) { return a.angle < b.angle; });

        std::vector<uint32_t> combinedFaces(
            drawData.faceIndices.begin() + size_t(faceStart),
            drawData.faceIndices.begin() + size_t(faceEnd));
        for (uint32_t i = 0; i < 6; i++) {
            const StitchPair &a = pairs[i];
            const StitchPair &b = pairs[(i + 1) % 6];
            combinedFaces.insert(combinedFaces.end(), {
                b.primary, a.primary, a.inner,
                b.primary, a.inner, b.inner });
        }
        waterCall.meshDesc.faceIndicesStart = uint32_t(drawData.faceIndices.size());
        waterCall.callDesc.triangleCount = uint32_t(combinedFaces.size() / 3);
        drawData.faceIndices.insert(drawData.faceIndices.end(),
            combinedFaces.begin(), combinedFaces.end());
        drawData.wr64WaterFaceIndices = combinedFaces;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
            "[water-stitch] frame=%llu primary=864 bridge=12 stitch=12\n",
            static_cast<unsigned long long>(workload.submissionFrame)); }
        return true;
    }

    // Add one degenerate quad per true primary boundary edge. Mode 6 in the
    // vertex processor extrudes only camera-exposed edges between native
    // endpoints. At weight 1 every quad collapses exactly onto its source edge.
    static bool augmentWr64WaterTrailingPatch(Workload &workload,
        Projection &projection, uint32_t callIndex)
    {
        if (!wr64WaterTrailingPatchEnabled() ||
            (callIndex >= projection.gameCallCount))
        {
            return false;
        }
        DrawData &drawData = workload.drawData;
        GameCall &waterCall = projection.gameCalls[callIndex];
        const uint32_t originalVertexCount = drawData.vertexCount();
        const uint32_t originalTriangleCount = waterCall.callDesc.triangleCount;
        const uint64_t faceStart = waterCall.meshDesc.faceIndicesStart;
        const uint64_t faceEnd = faceStart + uint64_t(originalTriangleCount) * 3ULL;
        if ((originalTriangleCount != 876) ||
            (faceEnd > drawData.faceIndices.size()) ||
            (drawData.wr64WaterProducerKeys.size() != originalVertexCount) ||
            (drawData.wr64WaterFieldInfo.size() !=
                (size_t(originalVertexCount) * 4ULL)) ||
            (drawData.wr64WaterFieldPrevPosShiftX.size() != originalVertexCount) ||
            (drawData.wr64WaterFieldPrevTcShiftZ.size() != originalVertexCount))
        {
            return false;
        }

        // The CPU-only provenance mask is normally populated later during
        // call matching.  This patch is appended before matching, so seed the
        // workload's original vertex range first.  Without that prefix the
        // 216 patch markers occupy mask[0..215] and matching discards them on
        // the inevitable mask-size mismatch.
        if (drawData.wr64WaterVertexMask.empty()) {
            drawData.wr64WaterVertexMask.assign(originalVertexCount, 0);
        }
        else if (drawData.wr64WaterVertexMask.size() != originalVertexCount) {
            return false;
        }

        struct Edge { uint32_t a, b, count; };
        std::map<std::pair<uint32_t, uint32_t>, Edge> edges;
        for (uint32_t triangle = 0; triangle < 864; triangle++) {
            const uint32_t offset = uint32_t(faceStart) + triangle * 3;
            const uint32_t tri[3] = { drawData.faceIndices[offset + 0],
                drawData.faceIndices[offset + 1], drawData.faceIndices[offset + 2] };
            for (uint32_t e = 0; e < 3; e++) {
                const uint32_t a = tri[e];
                const uint32_t b = tri[(e + 1) % 3];
                const auto key = (a < b) ? std::make_pair(a, b) :
                    std::make_pair(b, a);
                auto it = edges.find(key);
                if (it == edges.end()) edges.emplace(key, Edge{ a, b, 1 });
                else it->second.count++;
            }
        }

        // The primary draw is two disconnected meshes whose internal seam is
        // duplicated geometrically: 18 X/Z edges exist once in each component
        // (36 topological boundary edges total).  Extruding those coincident
        // seams produces the long folded rays seen in the first patch probe.
        // Cancel both copies and retain only the 72-edge exterior of the union.
        std::vector<Edge> topologicalBoundary;
        for (const auto &entry : edges) {
            if (entry.second.count == 1) {
                topologicalBoundary.push_back(entry.second);
            }
        }
        if (topologicalBoundary.size() != 108U) return false;

        const auto sameXZ = [&](uint32_t lhs, uint32_t rhs) {
            if (((uint64_t(lhs) + 1ULL) * 3ULL > drawData.posFloats.size()) ||
                ((uint64_t(rhs) + 1ULL) * 3ULL > drawData.posFloats.size()))
            {
                return false;
            }
            return (std::fabs(double(drawData.posFloats[lhs * 3U + 0U]) -
                    double(drawData.posFloats[rhs * 3U + 0U])) <= 1.0e-4) &&
                (std::fabs(double(drawData.posFloats[lhs * 3U + 2U]) -
                    double(drawData.posFloats[rhs * 3U + 2U])) <= 1.0e-4);
        };
        std::vector<bool> internalSeam(topologicalBoundary.size(), false);
        for (size_t i = 0; i < topologicalBoundary.size(); i++) {
            for (size_t j = i + 1; j < topologicalBoundary.size(); j++) {
                const Edge &a = topologicalBoundary[i];
                const Edge &b = topologicalBoundary[j];
                const bool coincident =
                    (sameXZ(a.a, b.a) && sameXZ(a.b, b.b)) ||
                    (sameXZ(a.a, b.b) && sameXZ(a.b, b.a));
                if (coincident) {
                    internalSeam[i] = true;
                    internalSeam[j] = true;
                }
            }
        }
        std::vector<Edge> exteriorBoundary;
        exteriorBoundary.reserve(topologicalBoundary.size());
        for (size_t i = 0; i < topologicalBoundary.size(); i++) {
            if (!internalSeam[i]) exteriorBoundary.push_back(topologicalBoundary[i]);
        }
        if (exteriorBoundary.size() != 72U) return false;

        const auto copyVertex = [&](uint32_t source, uint32_t edgeA,
            uint32_t edgeB) -> uint32_t
        {
            const uint32_t appended = drawData.vertexCount();
            const float pos[3] = { drawData.posFloats[source * 3 + 0],
                drawData.posFloats[source * 3 + 1], drawData.posFloats[source * 3 + 2] };
            const float vel[3] = { drawData.velFloats[source * 3 + 0],
                drawData.velFloats[source * 3 + 1], drawData.velFloats[source * 3 + 2] };
            const float tc[2] = { drawData.tcFloats[source * 2 + 0],
                drawData.tcFloats[source * 2 + 1] };
            const float tcVel[2] = { drawData.tcVelFloats[source * 2 + 0],
                drawData.tcVelFloats[source * 2 + 1] };
            const uint8_t nc[4] = { drawData.normColBytes[source * 4 + 0],
                drawData.normColBytes[source * 4 + 1],
                drawData.normColBytes[source * 4 + 2],
                drawData.normColBytes[source * 4 + 3] };
            drawData.posFloats.insert(drawData.posFloats.end(), pos, pos + 3);
            drawData.velFloats.insert(drawData.velFloats.end(), vel, vel + 3);
            drawData.tcFloats.insert(drawData.tcFloats.end(), tc, tc + 2);
            drawData.tcVelFloats.insert(drawData.tcVelFloats.end(), tcVel, tcVel + 2);
            drawData.normColBytes.insert(drawData.normColBytes.end(), nc, nc + 4);
            drawData.viewProjIndices.push_back(drawData.viewProjIndices[source]);
            drawData.worldIndices.push_back(drawData.worldIndices[source]);
            drawData.fogIndices.push_back(drawData.fogIndices[source]);
            drawData.lightIndices.push_back(drawData.lightIndices[source]);
            drawData.lightCounts.push_back(drawData.lightCounts[source]);
            drawData.lookAtIndices.push_back(drawData.lookAtIndices[source]);
            drawData.vertexSegmentedAddresses.push_back(
                drawData.vertexSegmentedAddresses[source]);
            drawData.wr64WaterProducerKeys.push_back(0);
            drawData.wr64WaterVertexMask.push_back(3);
            const uint32_t info[4] = { 6U, source, edgeA, edgeB };
            drawData.wr64WaterFieldInfo.insert(
                drawData.wr64WaterFieldInfo.end(), info, info + 4);
            drawData.wr64WaterFieldPrevPosShiftX.push_back(hlslpp::float4(0.0f));
            drawData.wr64WaterFieldPrevTcShiftZ.push_back(hlslpp::float4(0.0f));
            return appended;
        };

        std::vector<uint32_t> patchFaces;
        for (const Edge &edge : exteriorBoundary) {
            const uint32_t outerA = copyVertex(edge.a, edge.a, edge.b);
            const uint32_t outerB = copyVertex(edge.b, edge.a, edge.b);
            patchFaces.insert(patchFaces.end(), {
                edge.b, edge.a, outerA, edge.b, outerA, outerB });
        }
        if (patchFaces.size() != (72U * 2U * 3U)) return false;
        // The stock fan remains responsible for far/native-endpoint coverage.
        // These appended quads cover only the fractional-frame gap immediately
        // outside the primary boundary.
        std::vector<uint32_t> combinedFaces(
            drawData.faceIndices.begin() + size_t(faceStart),
            drawData.faceIndices.begin() + size_t(faceEnd));
        combinedFaces.insert(combinedFaces.end(), patchFaces.begin(), patchFaces.end());
        waterCall.meshDesc.faceIndicesStart = uint32_t(drawData.faceIndices.size());
        waterCall.callDesc.triangleCount = uint32_t(combinedFaces.size() / 3);
        drawData.faceIndices.insert(drawData.faceIndices.end(),
            combinedFaces.begin(), combinedFaces.end());
        drawData.wr64WaterFaceIndices = combinedFaces;
        static uint32_t wr64PatchAugmentProbeCount = 0;
        if (WR64_DIAGNOSTIC_ENABLED && wr64PatchAugmentProbeCount < 12) {
            wr64PatchAugmentProbeCount++;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                "[water-patch-augment] frame=%llu topology=488+12+144 vertices=%u triangles=%u mask=%zu field=%zu boundary=%zu exterior=%zu patchTris=%zu invariant=%s\n",
                static_cast<unsigned long long>(workload.submissionFrame),
                drawData.vertexCount(), waterCall.callDesc.triangleCount,
                drawData.wr64WaterVertexMask.size(),
                drawData.wr64WaterFieldInfo.size(), topologicalBoundary.size(),
                exteriorBoundary.size(), patchFaces.size() / 3,
                ((waterCall.callDesc.triangleCount == 1020U) &&
                    (drawData.vertexCount() == (originalVertexCount + 144U))) ?
                    "PASS" : "FAIL"); }
        }
        return true;
    }

    enum class Wr64DenseWaterCallResult : uint8_t {
        NotApplicable,
        Augmented,
        NativeRetained
    };

    struct Wr64DenseWaterPreflight {
        uint32_t triangleCount = 0U;
        uint32_t distinctVertexCount = 0U;
        uint64_t vertexSpan = 0ULL;
        uint32_t primaryDistinctVertexCount = 0U;
        uint64_t primaryVertexSpan = 0ULL;
        bool faceRangeValid = false;
        bool vertexRangeValid = false;
    };

    // Provenance is intentionally broad: several generated-water calls share
    // it over the opening lifecycle.  Dense coverage is only valid for the
    // exact unmodified 876-triangle sheet whose first 864 triangles use one
    // contiguous 488-vertex primary range and whose full call uses the
    // contiguous 500-vertex stock range.  This read-only preflight lets the
    // caller skip other provenance matches without confusing "not this call"
    // with a failure after the target sheet has been recognized.
    static bool preflightWr64WaterDenseAnnulus(const Workload &workload,
        const Projection &projection, uint32_t callIndex,
        Wr64DenseWaterPreflight &preflight)
    {
        constexpr uint32_t PrimaryTriangleCount = 864U;
        constexpr uint32_t StockTriangleCount = 876U;
        constexpr uint32_t PrimaryVertexCount = 488U;
        constexpr uint32_t StockVertexCount = 500U;

        if (callIndex >= projection.gameCallCount) return false;
        const DrawData &drawData = workload.drawData;
        const GameCall &waterCall = projection.gameCalls[callIndex];
        preflight.triangleCount = waterCall.callDesc.triangleCount;
        const uint64_t faceStart = waterCall.meshDesc.faceIndicesStart;
        const uint64_t indexCount =
            uint64_t(preflight.triangleCount) * 3ULL;
        if ((faceStart > drawData.faceIndices.size()) ||
            (indexCount > (drawData.faceIndices.size() - faceStart)))
        {
            return false;
        }
        preflight.faceRangeValid = true;

        std::set<uint32_t> stockVertices;
        std::set<uint32_t> primaryVertices;
        preflight.vertexRangeValid = true;
        for (uint64_t i = 0; i < indexCount; i++) {
            const uint32_t vertex =
                drawData.faceIndices[size_t(faceStart + i)];
            if (vertex >= drawData.vertexCount()) {
                preflight.vertexRangeValid = false;
                continue;
            }
            stockVertices.insert(vertex);
            if (i < (uint64_t(PrimaryTriangleCount) * 3ULL)) {
                primaryVertices.insert(vertex);
            }
        }
        preflight.distinctVertexCount = uint32_t(stockVertices.size());
        preflight.primaryDistinctVertexCount =
            uint32_t(primaryVertices.size());
        if (!stockVertices.empty()) {
            preflight.vertexSpan = uint64_t(*stockVertices.rbegin()) -
                uint64_t(*stockVertices.begin()) + 1ULL;
        }
        if (!primaryVertices.empty()) {
            preflight.primaryVertexSpan =
                uint64_t(*primaryVertices.rbegin()) -
                uint64_t(*primaryVertices.begin()) + 1ULL;
        }

        if (!preflight.vertexRangeValid ||
            (preflight.triangleCount != StockTriangleCount) ||
            (preflight.distinctVertexCount != StockVertexCount) ||
            (preflight.vertexSpan != StockVertexCount) ||
            (preflight.primaryDistinctVertexCount != PrimaryVertexCount) ||
            (preflight.primaryVertexSpan != PrimaryVertexCount))
        {
            return false;
        }
        const uint32_t waterBase = *stockVertices.begin();
        return (*primaryVertices.begin() == waterBase) &&
            (*primaryVertices.rbegin() ==
                (waterBase + PrimaryVertexCount - 1U));
    }

    // Replace only the stock six-corner, twelve-triangle flat coverage fan.
    // The accepted primary water remains the literal first 488 vertices and
    // first 864 triangles.  Four shared 72-vertex rings extend its canonical
    // exterior homothetically about the six proven fan anchors.  This mapping
    // is stateless and affine in both native endpoints, so ordinary mode-0
    // interpolation evaluates the same surface at every presentation weight.
    static bool augmentWr64WaterDenseAnnulus(Workload &workload,
        Projection &projection, uint32_t callIndex)
    {
        if (!wr64WaterDenseAnnulusEnabled() ||
            (callIndex >= projection.gameCallCount))
        {
            return false;
        }

        constexpr uint32_t PrimaryTriangleCount = 864U;
        constexpr uint32_t StockTriangleCount = 876U;
        constexpr uint32_t PrimaryVertexCount = 488U;
        constexpr uint32_t StockVertexCount = 500U;
        constexpr uint32_t BoundaryCount = 72U;
        constexpr uint32_t RingCount = 4U;
        constexpr uint32_t RingVertexCount = BoundaryCount * RingCount;
        constexpr uint32_t AnnulusTriangleCount =
            BoundaryCount * RingCount * 2U;
        constexpr uint32_t InvalidWaterProducerKey = UINT32_MAX;

        DrawData &drawData = workload.drawData;
        GameCall &waterCall = projection.gameCalls[callIndex];
        const uint32_t originalVertexCount = drawData.vertexCount();
        const uint64_t faceStart = waterCall.meshDesc.faceIndicesStart;
        const uint64_t faceEnd = faceStart +
            uint64_t(waterCall.callDesc.triangleCount) * 3ULL;
        const auto reject = [&](const char *reason) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                "[water-dense-augment-reject] frame=%llu call=%u reason=%s triangles=%u original_vertices=%u face_start=%llu face_end=%llu face_indices=%zu producer_keys=%zu mask=%zu\n",
                static_cast<unsigned long long>(workload.submissionFrame),
                callIndex, reason, waterCall.callDesc.triangleCount,
                originalVertexCount,
                static_cast<unsigned long long>(faceStart),
                static_cast<unsigned long long>(faceEnd),
                drawData.faceIndices.size(),
                drawData.wr64WaterProducerKeys.size(),
                drawData.wr64WaterVertexMask.size()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            return false;
        };
        const auto vertexArraysValid = [&]() {
            const size_t n = originalVertexCount;
            return (drawData.posFloats.size() == n * 3ULL) &&
                (drawData.velFloats.size() == n * 3ULL) &&
                (drawData.tcFloats.size() == n * 2ULL) &&
                (drawData.tcVelFloats.size() == n * 2ULL) &&
                (drawData.normColBytes.size() == n * 4ULL) &&
                (drawData.viewProjIndices.size() == n) &&
                (drawData.worldIndices.size() == n) &&
                (drawData.fogIndices.size() == n) &&
                (drawData.lightIndices.size() == n) &&
                (drawData.lightCounts.size() == n) &&
                (drawData.lookAtIndices.size() == n) &&
                (drawData.vertexSegmentedAddresses.size() == n) &&
                (drawData.wr64WaterProducerKeys.size() == n) &&
                (drawData.wr64WaterFieldInfo.size() == n * 4ULL) &&
                (drawData.wr64WaterFieldPrevPosShiftX.size() == n) &&
                (drawData.wr64WaterFieldPrevTcShiftZ.size() == n);
        };
        if ((originalVertexCount < StockVertexCount) ||
            (waterCall.callDesc.triangleCount != StockTriangleCount) ||
            (faceEnd > drawData.faceIndices.size()) || !vertexArraysValid())
        {
            return reject("precondition_or_vertex_arrays");
        }
        if (!drawData.wr64WaterVertexMask.empty() &&
            drawData.wr64WaterVertexMask.size() != originalVertexCount) {
            return reject("water_mask_size");
        }

        // The generated sheet is one contiguous 500-vertex subrange of a much
        // larger DrawData workload (4046 vertices in the opening capture), not
        // a standalone draw buffer.  Prove the call's exact contiguous range
        // before treating any global vertex index as a water-local identity.
        std::set<uint32_t> stockVertices;
        for (uint64_t f = faceStart; f < faceEnd; f++) {
            const uint32_t vertex = drawData.faceIndices[size_t(f)];
            if (vertex >= originalVertexCount) return reject("stock_vertex_oob");
            stockVertices.insert(vertex);
        }
        if (stockVertices.size() != StockVertexCount) {
            return reject("stock_vertex_count");
        }
        const uint32_t waterBase = *stockVertices.begin();
        if ((uint64_t(waterBase) + StockVertexCount) > originalVertexCount) {
            return reject("water_range_oob");
        }
        for (uint32_t local = 0; local < StockVertexCount; local++) {
            if (stockVertices.count(waterBase + local) != 1U) {
                return reject("stock_range_not_contiguous");
            }
        }
        // Producer words are raw game values. Zero is a legitimate primary
        // lattice identity. The producer-key reader only recognizes one
        // course's fixed gGfxPool windows, so an unrecognized key uses its
        // segment-3 source address in a disjoint 64-bit namespace.
        const auto primarySourceValid = [&](uint32_t vertex) {
            if ((vertex < waterBase) ||
                (vertex >= (waterBase + PrimaryVertexCount)) ||
                (vertex >= originalVertexCount))
            {
                return false;
            }
            const uint32_t address =
                drawData.vertexSegmentedAddresses[vertex];
            return isWr64GeneratedWaterVertexAddress(address);
        };
        bool sourceIdentity = false;
        const auto effectiveProducerKey = [&](uint32_t vertex) -> uint64_t {
            const uint32_t raw = drawData.wr64WaterProducerKeys[vertex];
            if (!sourceIdentity && raw != InvalidWaterProducerKey) return uint64_t(raw);
            return (1ULL << 32U) |
                uint64_t(drawData.vertexSegmentedAddresses[vertex]);
        };

        struct DirectedEdge {
            uint32_t a = 0;
            uint32_t b = 0;
            uint32_t count = 0;
            uint64_t keyA = 0;
            uint64_t keyB = 0;
        };
        std::map<std::pair<uint32_t, uint32_t>, DirectedEdge> edgeIncidence;
        std::set<uint32_t> primaryVertices;
        for (uint32_t triangle = 0; triangle < PrimaryTriangleCount; triangle++) {
            const uint32_t offset = uint32_t(faceStart) + triangle * 3U;
            const uint32_t tri[3] = {
                drawData.faceIndices[offset + 0U],
                drawData.faceIndices[offset + 1U],
                drawData.faceIndices[offset + 2U]
            };
            for (uint32_t corner = 0; corner < 3U; corner++) {
                const uint32_t a = tri[corner];
                const uint32_t b = tri[(corner + 1U) % 3U];
                if (!primarySourceValid(a) || !primarySourceValid(b)) {
                    return reject("primary_edge_vertex_or_provenance");
                }
                primaryVertices.insert(a);
                const auto idPair = (a < b) ? std::make_pair(a, b) :
                    std::make_pair(b, a);
                DirectedEdge &edge = edgeIncidence[idPair];
                if (edge.count == 0U) {
                    edge.a = a;
                    edge.b = b;
                }
                edge.count++;
            }
        }
        if (primaryVertices.size() != PrimaryVertexCount) {
            return reject("primary_vertex_count");
        }
        // This candidate is permitted to consume the proven water-local
        // primary prefix only. A same-sized but re-slotted set would invalidate every
        // persistent ring source identity even if the topology happened to
        // remain manifold.
        for (uint32_t local = 0; local < PrimaryVertexCount; local++) {
            if (primaryVertices.count(waterBase + local) != 1U) {
                return reject("primary_range_not_contiguous");
            }
        }

        // Repeated producer keys are the two primary components' coincident
        // seam vertices.  Verify they are genuinely identical before using a
        // deterministic representative for the shared logical boundary node.
        const char *duplicatePayloadReason = nullptr;
        const auto equalVertexPayload = [&](uint32_t a, uint32_t b) {
            for (uint32_t c = 0; c < 3U; c++) {
                if (wr64FloatBits(drawData.posFloats[a * 3U + c]) !=
                    wr64FloatBits(drawData.posFloats[b * 3U + c])) {
                    duplicatePayloadReason = "duplicate_payload_position";
                    return false;
                }
                if (wr64FloatBits(drawData.velFloats[a * 3U + c]) !=
                    wr64FloatBits(drawData.velFloats[b * 3U + c])) {
                    duplicatePayloadReason = "duplicate_payload_velocity";
                    return false;
                }
            }
            for (uint32_t c = 0; c < 2U; c++) {
                if (wr64FloatBits(drawData.tcFloats[a * 2U + c]) !=
                    wr64FloatBits(drawData.tcFloats[b * 2U + c])) {
                    duplicatePayloadReason = "duplicate_payload_texcoord";
                    return false;
                }
                if (wr64FloatBits(drawData.tcVelFloats[a * 2U + c]) !=
                    wr64FloatBits(drawData.tcVelFloats[b * 2U + c])) {
                    duplicatePayloadReason = "duplicate_payload_texcoord_velocity";
                    return false;
                }
            }
            for (uint32_t c = 0; c < 4U; c++) {
                if (drawData.normColBytes[a * 4U + c] !=
                    drawData.normColBytes[b * 4U + c]) {
                    duplicatePayloadReason = "duplicate_payload_normal_color";
                    return false;
                }
            }
            if ((drawData.viewProjIndices[a] != drawData.viewProjIndices[b]) ||
                (drawData.worldIndices[a] != drawData.worldIndices[b]) ||
                (drawData.fogIndices[a] != drawData.fogIndices[b]) ||
                (drawData.lightIndices[a] != drawData.lightIndices[b]) ||
                (drawData.lightCounts[a] != drawData.lightCounts[b]) ||
                (drawData.lookAtIndices[a] != drawData.lookAtIndices[b]) ||
                (drawData.vertexSegmentedAddresses[a] !=
                    drawData.vertexSegmentedAddresses[b]))
            {
                duplicatePayloadReason = "duplicate_payload_metadata";
                return false;
            }
            return true;
        };
        std::map<uint64_t, uint32_t> representativeByKey;
        uint32_t duplicateA = UINT32_MAX, duplicateB = UINT32_MAX;
        const auto buildRepresentatives = [&]() {
            representativeByKey.clear();
            duplicatePayloadReason = nullptr;
            for (uint32_t vertex : primaryVertices) {
                const uint64_t key = effectiveProducerKey(vertex);
                auto inserted = representativeByKey.emplace(key, vertex);
                if (!inserted.second) {
                    if (!equalVertexPayload(inserted.first->second, vertex)) {
                        duplicateA = inserted.first->second;
                        duplicateB = vertex;
                        return false;
                    }
                    inserted.first->second = std::min(inserted.first->second, vertex);
                }
            }
            return representativeByKey.size() == 469U;
        };
        if (!buildRepresentatives()) {
            const char *rawReason = duplicatePayloadReason ? duplicatePayloadReason : "producer_key_cardinality";
            // Producer keys are sampled separately from native VTX data and
            // can alias after the game reuses a grid cell/table. Recover only
            // from exact decoded source identity, never proximity or a merge
            // of differing payloads. All existing topology/anchor/winding
            // proofs below still apply to the recovered 469-node domain.
            sourceIdentity = true;
            const bool recovered = buildRepresentatives();
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                "[water-dense-identity] frame=%llu call=%u raw_reason=%s source_recovered=%u logical=%zu pair=%u,%u addresses=%08X,%08X\n",
                static_cast<unsigned long long>(workload.submissionFrame), callIndex,
                rawReason, unsigned(recovered), representativeByKey.size(), duplicateA, duplicateB,
                duplicateA < originalVertexCount ? drawData.vertexSegmentedAddresses[duplicateA] : 0u,
                duplicateB < originalVertexCount ? drawData.vertexSegmentedAddresses[duplicateB] : 0u); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            if (duplicateA < originalVertexCount && duplicateB < originalVertexCount) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                    "[water-dense-identity-payload] frame=%llu raw_keys=%08X,%08X position_a=%.9g,%.9g,%.9g position_b=%.9g,%.9g,%.9g\n",
                    static_cast<unsigned long long>(workload.submissionFrame),
                    drawData.wr64WaterProducerKeys[duplicateA], drawData.wr64WaterProducerKeys[duplicateB],
                    double(drawData.posFloats[duplicateA * 3]), double(drawData.posFloats[duplicateA * 3 + 1]), double(drawData.posFloats[duplicateA * 3 + 2]),
                    double(drawData.posFloats[duplicateB * 3]), double(drawData.posFloats[duplicateB * 3 + 1]), double(drawData.posFloats[duplicateB * 3 + 2])); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            }
            if (!recovered) return reject(duplicatePayloadReason ? duplicatePayloadReason : "source_identity_cardinality");
        }
        uint32_t primaryRawZeroCount = 0U;
        uint32_t firstPrimaryRawZero = UINT32_MAX;
        for (uint32_t vertex : primaryVertices) {
            if (drawData.wr64WaterProducerKeys[vertex] == 0U) {
                primaryRawZeroCount++;
                firstPrimaryRawZero = std::min(firstPrimaryRawZero, vertex);
            }
        }
        if (primaryRawZeroCount != 0U) {
            static uint32_t rawZeroProbeCount = 0U;
            if (rawZeroProbeCount < 8U) {
                rawZeroProbeCount++;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                    "[water-dense-primary-zero] frame=%llu call=%u action=ACCEPT raw_zero_count=%u first_local=%u first_address=0x%08X validity=exact_primary_range+water_pool_address+non_invalid_sentinel\n",
                    static_cast<unsigned long long>(workload.submissionFrame),
                    callIndex, primaryRawZeroCount,
                    firstPrimaryRawZero - waterBase,
                    drawData.vertexSegmentedAddresses[firstPrimaryRawZero]); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            }
        }

        std::vector<DirectedEdge> topologicalBoundary;
        for (const auto &entry : edgeIncidence) {
            if (entry.second.count != 1U) continue;
            DirectedEdge edge = entry.second;
            edge.keyA = effectiveProducerKey(edge.a);
            edge.keyB = effectiveProducerKey(edge.b);
            if (!primarySourceValid(edge.a) ||
                !primarySourceValid(edge.b) ||
                (edge.keyA == edge.keyB)) {
                return reject("boundary_key_invalid");
            }
            topologicalBoundary.push_back(edge);
        }
        if (topologicalBoundary.size() != 108U) {
            return reject("topological_boundary_count");
        }

        std::map<std::pair<uint64_t, uint64_t>,
            std::vector<DirectedEdge>> logicalEdges;
        for (const DirectedEdge &edge : topologicalBoundary) {
            const auto keyPair = (edge.keyA < edge.keyB) ?
                std::make_pair(edge.keyA, edge.keyB) :
                std::make_pair(edge.keyB, edge.keyA);
            logicalEdges[keyPair].push_back(edge);
        }
        std::vector<DirectedEdge> exteriorEdges;
        uint32_t seamPairCount = 0;
        for (const auto &entry : logicalEdges) {
            if (entry.second.size() == 1U) {
                exteriorEdges.push_back(entry.second.front());
            }
            else if (entry.second.size() == 2U) {
                const DirectedEdge &a = entry.second[0];
                const DirectedEdge &b = entry.second[1];
                if ((a.keyA != b.keyB) || (a.keyB != b.keyA)) {
                    return reject("logical_seam_direction");
                }
                seamPairCount++;
            }
            else {
                return reject("logical_edge_multiplicity");
            }
        }
        if ((exteriorEdges.size() != BoundaryCount) ||
            (seamPairCount != 18U)) {
            return reject("exterior_or_seam_count");
        }

        std::map<uint64_t, DirectedEdge> edgeByStartKey;
        std::map<uint64_t, uint32_t> incomingCount;
        for (const DirectedEdge &edge : exteriorEdges) {
            if (!edgeByStartKey.emplace(edge.keyA, edge).second) {
                return reject("duplicate_exterior_start");
            }
            incomingCount[edge.keyB]++;
        }
        if ((edgeByStartKey.size() != BoundaryCount) ||
            (incomingCount.size() != BoundaryCount)) {
            return reject("exterior_degree_cardinality");
        }
        for (const auto &entry : edgeByStartKey) {
            if (incomingCount[entry.first] != 1U) {
                return reject("exterior_indegree");
            }
        }

        // The proven contiguous suffix uses locals 488..493 for its six
        // private inner copies and 494..499 for its six outer corners.
        // Classify those structural slots directly because raw zero is also a
        // legitimate producer identity.
        std::set<uint64_t> privateInnerKeys;
        std::set<uint32_t> privateInnerVertices;
        std::set<uint32_t> stockOuterVertices;
        uint64_t startKey = 0;
        bool startKeySet = false;
        bool firstKeyConflict = false;
        bool allPrivateRawKeysValid = true;
        for (uint32_t triangle = PrimaryTriangleCount;
            triangle < StockTriangleCount; triangle++)
        {
            const uint32_t offset = uint32_t(faceStart) + triangle * 3U;
            for (uint32_t corner = 0; corner < 3U; corner++) {
                const uint32_t vertex = drawData.faceIndices[offset + corner];
                if (vertex >= originalVertexCount) {
                    return reject("suffix_vertex_oob");
                }
                const uint32_t local = vertex - waterBase;
                if ((local >= (PrimaryVertexCount + 6U)) &&
                    (local < StockVertexCount))
                {
                    stockOuterVertices.insert(vertex);
                }
                else if ((local >= PrimaryVertexCount) &&
                    (local < (PrimaryVertexCount + 6U)))
                {
                    if (drawData.wr64WaterProducerKeys[vertex] ==
                        InvalidWaterProducerKey)
                    {
                        allPrivateRawKeysValid = false;
                    }
                    const uint64_t key = effectiveProducerKey(vertex);
                    privateInnerKeys.insert(key);
                    privateInnerVertices.insert(vertex);
                    if (triangle == PrimaryTriangleCount) {
                        if (startKeySet && (startKey != key)) {
                            firstKeyConflict = true;
                        }
                        startKey = key;
                        startKeySet = true;
                    }
                }
                else {
                    return reject("suffix_unexpected_slot");
                }
            }
        }

        // Slot topology is mandatory regardless of producer identity.
        if ((privateInnerVertices.size() != 6U) ||
            (stockOuterVertices.size() != 6U)) {
            return reject("suffix_classification");
        }

        // Keep the original producer-key path first. It is the known-good
        // opening path and therefore must not be perturbed when all six keys
        // already name exterior boundary nodes.
        bool keyedSuffixValid = allPrivateRawKeysValid &&
            !firstKeyConflict && startKeySet &&
            (privateInnerKeys.size() == 6U) &&
            (privateInnerKeys.count(startKey) == 1U);
        if (keyedSuffixValid) {
            for (uint64_t privateKey : privateInnerKeys) {
                if (edgeByStartKey.count(privateKey) != 1U) {
                    keyedSuffixValid = false;
                    break;
                }
            }
        }

        if (!keyedSuffixValid) {
            // Producer metadata for the six private suffix copies is not a
            // stable identity on every course. Recover only their boundary
            // identity from the already-proven suffix slots and exterior
            // topology. Temporal velocity payload and segmented address are
            // deliberately excluded: neither identifies the current logical
            // boundary point, and neither is copied into generated vertices.
            const auto equalAnchorPayload = [&](uint32_t suffixVertex,
                uint32_t primaryVertex)
            {
                for (uint32_t c = 0; c < 3U; c++) {
                    if (wr64FloatBits(drawData.posFloats[
                            suffixVertex * 3U + c]) !=
                        wr64FloatBits(drawData.posFloats[
                            primaryVertex * 3U + c]))
                    {
                        return false;
                    }
                }
                for (uint32_t c = 0; c < 2U; c++) {
                    if (wr64FloatBits(drawData.tcFloats[
                            suffixVertex * 2U + c]) !=
                        wr64FloatBits(drawData.tcFloats[
                            primaryVertex * 2U + c]))
                    {
                        return false;
                    }
                }
                for (uint32_t c = 0; c < 4U; c++) {
                    if (drawData.normColBytes[suffixVertex * 4U + c] !=
                        drawData.normColBytes[primaryVertex * 4U + c])
                    {
                        return false;
                    }
                }
                return
                    (drawData.viewProjIndices[suffixVertex] ==
                        drawData.viewProjIndices[primaryVertex]) &&
                    (drawData.worldIndices[suffixVertex] ==
                        drawData.worldIndices[primaryVertex]) &&
                    (drawData.fogIndices[suffixVertex] ==
                        drawData.fogIndices[primaryVertex]) &&
                    (drawData.lightIndices[suffixVertex] ==
                        drawData.lightIndices[primaryVertex]) &&
                    (drawData.lightCounts[suffixVertex] ==
                        drawData.lightCounts[primaryVertex]) &&
                    (drawData.lookAtIndices[suffixVertex] ==
                        drawData.lookAtIndices[primaryVertex]);
            };

            std::map<uint32_t, uint64_t> recoveredKeyByVertex;
            std::set<uint64_t> recoveredKeys;
            for (uint32_t local = PrimaryVertexCount;
                local < (PrimaryVertexCount + 6U); local++)
            {
                const uint32_t suffixVertex = waterBase + local;
                uint64_t matchedKey = 0;
                uint32_t matchCount = 0;
                for (const auto &entry : edgeByStartKey) {
                    if (!equalAnchorPayload(suffixVertex,
                            entry.second.a)) continue;
                    matchedKey = entry.first;
                    matchCount++;
                }
                if (matchCount != 1U) {
                    return reject("suffix_anchor_payload_match");
                }
                recoveredKeyByVertex.emplace(suffixVertex, matchedKey);
                if (!recoveredKeys.insert(matchedKey).second) {
                    return reject("suffix_anchor_payload_duplicate");
                }
            }

            const uint32_t firstSuffixOffset = uint32_t(faceStart) +
                PrimaryTriangleCount * 3U;
            uint32_t firstAnchorCount = 0;
            uint64_t recoveredStartKey = 0;
            for (uint32_t corner = 0; corner < 3U; corner++) {
                const uint32_t vertex =
                    drawData.faceIndices[firstSuffixOffset + corner];
                auto recoveredIt = recoveredKeyByVertex.find(vertex);
                if (recoveredIt == recoveredKeyByVertex.end()) continue;
                recoveredStartKey = recoveredIt->second;
                firstAnchorCount++;
            }
            if (firstAnchorCount != 1U) {
                return reject("suffix_first_anchor_topology");
            }

            privateInnerKeys = recoveredKeys;
            startKey = recoveredStartKey;
            startKeySet = true;
        }

        if ((privateInnerKeys.size() != 6U) || !startKeySet) {
            return reject("suffix_classification");
        }
        for (uint32_t local = PrimaryVertexCount;
            local < (PrimaryVertexCount + 6U); local++)
        {
            if (privateInnerVertices.count(waterBase + local) != 1U) {
                return reject("suffix_private_slots");
            }
        }
        for (uint32_t local = PrimaryVertexCount + 6U;
            local < StockVertexCount; local++)
        {
            if (stockOuterVertices.count(waterBase + local) != 1U) {
                return reject("suffix_outer_slots");
            }
        }

        std::vector<DirectedEdge> orderedEdges;
        std::vector<uint32_t> orderedSources;
        orderedEdges.reserve(BoundaryCount);
        orderedSources.reserve(BoundaryCount);
        uint64_t key = startKey;
        for (uint32_t i = 0; i < BoundaryCount; i++) {
            auto edgeIt = edgeByStartKey.find(key);
            auto sourceIt = representativeByKey.find(key);
            if ((edgeIt == edgeByStartKey.end()) ||
                (sourceIt == representativeByKey.end())) {
                return reject("ordered_loop_lookup");
            }
            orderedEdges.push_back(edgeIt->second);
            orderedSources.push_back(sourceIt->second);
            key = edgeIt->second.keyB;
        }
        if (key != startKey) return reject("ordered_loop_not_closed");
        std::set<uint64_t> visitedKeys;
        for (const DirectedEdge &edge : orderedEdges) {
            if (!visitedKeys.insert(edge.keyA).second) {
                return reject("ordered_loop_duplicate_key");
            }
        }
        for (uint32_t i = 0; i < BoundaryCount; i++) {
            const bool isAnchor = privateInnerKeys.count(
                orderedEdges[i].keyA) != 0U;
            if (isAnchor != ((i % 12U) == 0U)) {
                return reject("anchor_cadence");
            }
        }

        // Stage every possible primary-height edit. A later native input
        // rejection (datum, anchors, winding or ring crossing) must leave the
        // original sheet and its mask/index buffers completely unchanged.
        std::vector<float> stagedPositions = drawData.posFloats;

        // Snapshot matching uses the untouched native interior, before the
        // existing Roundness pass. A mismatch retains the accepted flat edge.
        auto waveDistance = workload.wr64RtCourse == workload.wr64WaveDistanceSnapshot.course
            ? wr64PlanWaveDistance(drawData, workload.wr64WaveDistanceSnapshot, waterBase) : Wr64WaveDistanceDraw{};

        // Smooth a frozen snapshot of the completed primary sheet, after all
        // producer/seam/topology validation but before annulus generation,
        // scene matching and the final buffer upload. Doing this here avoids
        // RSP vertex-load batch ordering: every native endpoint is rounded
        // from all six neighbours before interpolation derives its velocity.
        //
        // Work in logical producer-key space so the 19 duplicated seam groups
        // receive one identical height. Only degree-six vertices are changed;
        // the 72-vertex exterior loop is intentionally left untouched to keep
        // the accepted annulus seam and coverage construction invariant.
        const float laplacianStrength =
            getWr64WaterLaplacianStrength();
        uint32_t smoothedLogicalVertices = 0U;
        uint32_t smoothedPhysicalVertices = 0U;
        uint32_t preservedBoundaryVertices = 0U;
        double maximumHeightDelta = 0.0;
        if (laplacianStrength > 0.0f) {
            std::map<uint64_t, std::set<uint64_t>> neighboursByKey;
            for (uint32_t triangle = 0U;
                triangle < PrimaryTriangleCount; triangle++)
            {
                const size_t offset = size_t(faceStart) +
                    size_t(triangle) * 3ULL;
                const uint32_t vertices[3] = {
                    drawData.faceIndices[offset + 0ULL],
                    drawData.faceIndices[offset + 1ULL],
                    drawData.faceIndices[offset + 2ULL]
                };
                const uint64_t keys[3] = {
                    effectiveProducerKey(vertices[0]),
                    effectiveProducerKey(vertices[1]),
                    effectiveProducerKey(vertices[2])
                };
                for (uint32_t a = 0U; a < 3U; a++) {
                    for (uint32_t b = 0U; b < 3U; b++) {
                        if ((a != b) && (keys[a] != keys[b])) {
                            neighboursByKey[keys[a]].insert(keys[b]);
                        }
                    }
                }
            }

            std::map<uint64_t, float> roundedHeightByKey;
            for (const auto &representative : representativeByKey) {
                const uint64_t producerKey = representative.first;
                const uint32_t source = representative.second;
                const float originalHeight =
                    stagedPositions[source * 3U + 1U];
                float roundedHeight = originalHeight;

                const auto neighboursIt = neighboursByKey.find(producerKey);
                if ((neighboursIt != neighboursByKey.end()) &&
                    (neighboursIt->second.size() == 6U))
                {
                    double meanHeight = 0.0;
                    bool completeNeighbourSet = true;
                    for (uint64_t neighbourKey : neighboursIt->second) {
                        const auto neighbourIt =
                            representativeByKey.find(neighbourKey);
                        if (neighbourIt == representativeByKey.end()) {
                            completeNeighbourSet = false;
                            break;
                        }
                        meanHeight += double(stagedPositions[
                            neighbourIt->second * 3U + 1U]);
                    }
                    if (completeNeighbourSet) {
                        meanHeight /= 6.0;
                        roundedHeight = float(double(originalHeight) +
                            double(laplacianStrength) *
                            (meanHeight - double(originalHeight)));
                        smoothedLogicalVertices++;
                        maximumHeightDelta = std::max(maximumHeightDelta,
                            std::fabs(double(roundedHeight) -
                                double(originalHeight)));
                    }
                }
                else {
                    preservedBoundaryVertices++;
                }

                roundedHeightByKey.emplace(producerKey, roundedHeight);
            }

            for (uint32_t vertex : primaryVertices) {
                const auto roundedIt = roundedHeightByKey.find(
                    effectiveProducerKey(vertex));
                if (roundedIt == roundedHeightByKey.end()) {
                    return reject("laplacian_missing_logical_height");
                }
                if (wr64FloatBits(stagedPositions[vertex * 3U + 1U]) !=
                    wr64FloatBits(roundedIt->second))
                {
                    smoothedPhysicalVertices++;
                }
                stagedPositions[vertex * 3U + 1U] = roundedIt->second;
            }

            static bool loggedLaplacianConfiguration = false;
            if (!loggedLaplacianConfiguration) {
                loggedLaplacianConfiguration = true;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                    "[water-laplacian] strength=%.3f logical=%zu smoothed_logical=%u smoothed_physical=%u preserved_boundary=%u max_height_delta=%.6f annulus_boundary_unchanged=1\n",
                    laplacianStrength, representativeByKey.size(),
                    smoothedLogicalVertices, smoothedPhysicalVertices,
                    preservedBoundaryVertices, maximumHeightDelta); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            }
        }

        Wr64PrimaryWaterDatum waterDatum;
        if (!measureWr64PrimaryWaterDatum(drawData, waterBase, waterDatum, &stagedPositions)) {
            return reject("water_datum");
        }
        if (waveDistance.valid) {
            waveDistance.originalDatum = waterDatum.height;
            waveDistance.originalSpread = waterDatum.spread;
            if (waveDistance.mode) for (const auto &vertex : waveDistance.boundary)
                stagedPositions[vertex.vertex * 3U + 1U] = vertex.height;
            for (auto &sample : waveDistance.samples) sample.height = stagedPositions[sample.vertex * 3U + 1U];
        }

        double centerX = 0.0;
        double centerZ = 0.0;
        double centerVelocityX = 0.0;
        double centerVelocityZ = 0.0;
        for (uint32_t i = 0; i < BoundaryCount; i += 12U) {
            const uint32_t source = orderedSources[i];
            centerX += double(stagedPositions[source * 3U + 0U]);
            centerZ += double(stagedPositions[source * 3U + 2U]);
            centerVelocityX += double(drawData.velFloats[source * 3U + 0U]);
            centerVelocityZ += double(drawData.velFloats[source * 3U + 2U]);
        }
        centerX /= 6.0;
        centerZ /= 6.0;
        centerVelocityX /= 6.0;
        centerVelocityZ /= 6.0;

        struct GeneratedVertex {
            float position[3] = {};
            float velocity[3] = {};
            float texcoord[2] = {};
            float texcoordVelocity[2] = {};
            uint8_t normalColor[4] = {};
            uint32_t source = 0;
            uint32_t layer = 0;
            uint32_t loopIndex = 0;
        };
        std::vector<GeneratedVertex> generated(RingVertexCount);
        // Original/Extended keep the accepted flat annulus. Extended+ carries
        // only the recovered boundary height into a fixed, tapered inner tail.
        // No sample is read beyond the existing native simulation domain.
        const uint32_t farWaterMode = wr64FarWaterDistanceMode(
            workload.wr64FarWaterDistanceMode);
        const uint32_t waveMode = waveDistance.valid ? waveDistance.mode : 0U;
        const auto generatedIndex = [=](uint32_t layer, uint32_t loopIndex) {
            return (layer - 1U) * BoundaryCount + loopIndex;
        };
        for (uint32_t layer = 1U; layer <= RingCount; layer++) {
            const double g = wr64WaveRingScale(waveMode, farWaterMode, layer);
            // Keep neutral UV/lighting. Original/Extended sit at the native
            // sheet datum; Extended+ tapers the current boundary displacement
            // back to that same datum by scale 2, without simulating new cells.
            const double h = 1.0;
            for (uint32_t i = 0; i < BoundaryCount; i++) {
                const uint32_t source = orderedSources[i];
                GeneratedVertex &out = generated[generatedIndex(layer, i)];
                out.source = source;
                out.layer = layer;
                out.loopIndex = i;
                const double sourceX = stagedPositions[source * 3U + 0U];
                const double sourceZ = stagedPositions[source * 3U + 2U];
                out.position[0] = float(centerX + g * (sourceX - centerX));
                out.position[1] = float(wr64WaveRingHeight(waveMode, g, waterDatum.height,
                    stagedPositions[source * 3U + 1U]));
                out.position[2] = float(centerZ + g * (sourceZ - centerZ));
                const double sourceVelocityX =
                    drawData.velFloats[source * 3U + 0U];
                const double sourceVelocityZ =
                    drawData.velFloats[source * 3U + 2U];
                out.velocity[0] = float(centerVelocityX + g *
                    (sourceVelocityX - centerVelocityX));
                // Scene matching finalizes this from independently measured
                // current/previous native water datums.
                out.velocity[1] = 0.0f;
                out.velocity[2] = float(centerVelocityZ + g *
                    (sourceVelocityZ - centerVelocityZ));
                for (uint32_t component = 0; component < 2U; component++) {
                    const double sourceTc =
                        drawData.tcFloats[source * 2U + component];
                    const double flatTarget = sourceTc +
                        std::remainder(16.0 - sourceTc, 32.0);
                    out.texcoord[component] = float(sourceTc +
                        h * (flatTarget - sourceTc));
                    out.texcoordVelocity[component] = float((1.0 - h) *
                        double(drawData.tcVelFloats[source * 2U + component]));
                }
                out.normalColor[0] = 0U;
                out.normalColor[1] = 127U;
                out.normalColor[2] = 0U;
                out.normalColor[3] =
                    drawData.normColBytes[source * 4U + 3U];
            }
        }

        const auto globalRingVertex = [&](uint32_t layer, uint32_t i) {
            return originalVertexCount + generatedIndex(layer, i);
        };
        std::vector<uint32_t> annulusFaces;
        annulusFaces.reserve(size_t(AnnulusTriangleCount) * 3ULL);
        for (uint32_t radial = 0; radial < RingCount; radial++) {
            for (uint32_t i = 0; i < BoundaryCount; i++) {
                const uint32_t next = (i + 1U) % BoundaryCount;
                const uint32_t innerA = (radial == 0U) ?
                    orderedEdges[i].a : globalRingVertex(radial, i);
                const uint32_t innerB = (radial == 0U) ?
                    orderedEdges[i].b : globalRingVertex(radial, next);
                const uint32_t outerA = globalRingVertex(radial + 1U, i);
                const uint32_t outerB = globalRingVertex(radial + 1U, next);
                const bool diagonalB = ((i % 12U) < 6U);
                if (diagonalB) {
                    annulusFaces.insert(annulusFaces.end(), {
                        innerB, innerA, outerB,
                        innerA, outerA, outerB });
                }
                else {
                    annulusFaces.insert(annulusFaces.end(), {
                        innerB, innerA, outerA,
                        innerB, outerA, outerB });
                }
            }
        }
        if (annulusFaces.size() != size_t(AnnulusTriangleCount) * 3ULL) {
            return reject("annulus_face_count");
        }

        const auto positionXZ = [&](uint32_t vertex) {
            if (vertex < originalVertexCount) {
                return std::pair<double, double>(
                    stagedPositions[vertex * 3U + 0U],
                    stagedPositions[vertex * 3U + 2U]);
            }
            const GeneratedVertex &v = generated[vertex - originalVertexCount];
            return std::pair<double, double>(v.position[0], v.position[2]);
        };
        const auto signedAreaXZ = [&](uint32_t a, uint32_t b, uint32_t c) {
            const auto pa = positionXZ(a);
            const auto pb = positionXZ(b);
            const auto pc = positionXZ(c);
            return (pb.first - pa.first) * (pc.second - pa.second) -
                (pb.second - pa.second) * (pc.first - pa.first);
        };
        double leastNegativeArea = -std::numeric_limits<double>::max();
        for (size_t f = 0; f < annulusFaces.size(); f += 3ULL) {
            const double area = signedAreaXZ(annulusFaces[f + 0ULL],
                annulusFaces[f + 1ULL], annulusFaces[f + 2ULL]);
            if (!(area < -1.0e-3)) {
                return reject("current_endpoint_winding");
            }
            leastNegativeArea = std::max(leastNegativeArea, area);
        }

        // Current-endpoint ring simplicity is an independent guard against a
        // locally clockwise but globally crossed annulus.
        const auto orient = [](const std::pair<double, double> &a,
            const std::pair<double, double> &b,
            const std::pair<double, double> &c)
        {
            return (b.first - a.first) * (c.second - a.second) -
                (b.second - a.second) * (c.first - a.first);
        };
        const auto properIntersection = [&](const std::pair<double, double> &a,
            const std::pair<double, double> &b,
            const std::pair<double, double> &c,
            const std::pair<double, double> &d)
        {
            const double abC = orient(a, b, c);
            const double abD = orient(a, b, d);
            const double cdA = orient(c, d, a);
            const double cdB = orient(c, d, b);
            return ((abC > 1.0e-6) != (abD > 1.0e-6)) &&
                ((cdA > 1.0e-6) != (cdB > 1.0e-6)) &&
                (std::fabs(abC) > 1.0e-6) &&
                (std::fabs(abD) > 1.0e-6) &&
                (std::fabs(cdA) > 1.0e-6) &&
                (std::fabs(cdB) > 1.0e-6);
        };
        for (uint32_t ring = 0; ring <= RingCount; ring++) {
            const auto ringVertex = [&](uint32_t i) {
                return (ring == 0U) ? orderedSources[i] :
                    globalRingVertex(ring, i);
            };
            for (uint32_t i = 0; i < BoundaryCount; i++) {
                const uint32_t iNext = (i + 1U) % BoundaryCount;
                for (uint32_t j = i + 1U; j < BoundaryCount; j++) {
                    const uint32_t jNext = (j + 1U) % BoundaryCount;
                    if ((i == j) || (iNext == j) || (jNext == i)) continue;
                    if (properIntersection(positionXZ(ringVertex(i)),
                        positionXZ(ringVertex(iNext)),
                        positionXZ(ringVertex(j)),
                        positionXZ(ringVertex(jNext)))) {
                        return reject("current_ring_crossing");
                    }
                }
            }
        }

        // Commit only after all input/topology/geometry proofs passed.
        // From here on failure denotes an internal implementation invariant,
        // not an unsupported native draw; retain the hard post-commit checks.
        drawData.posFloats.swap(stagedPositions);
        drawData.wr64WaveDistance = std::move(waveDistance);
        if (drawData.wr64WaveDistance.valid && drawData.wr64WaveDistance.mode) {
            static bool loggedWaveRecovery[9][3] = {};
            const uint32_t courseSlot = drawData.wr64WaveDistance.course;
            if (!loggedWaveRecovery[courseSlot][drawData.wr64WaveDistance.mode]) {
                loggedWaveRecovery[courseSlot][drawData.wr64WaveDistance.mode] = true;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[wave-distance] course=%u %s: 72 simulated boundary nodes recovered; 397 interior nodes and native physics preserved\n",
                    courseSlot,
                    drawData.wr64WaveDistance.mode == 2U ? "Extended+ with tapered visual tail" : "Extended"); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            }
        }
        drawData.wr64FarWaterDistanceMode = farWaterMode;
        if (drawData.wr64WaterVertexMask.empty())
            drawData.wr64WaterVertexMask.assign(originalVertexCount, 0);

        const auto hashPrimary = [&]() {
            uint64_t hash = 1469598103934665603ULL;
            const auto mix = [&](uint64_t value) {
                hash ^= value;
                hash *= 1099511628211ULL;
            };
            for (uint32_t vertex : primaryVertices) {
                mix(vertex);
                for (uint32_t c = 0; c < 3U; c++) {
                    mix(wr64FloatBits(drawData.posFloats[vertex * 3U + c]));
                    mix(wr64FloatBits(drawData.velFloats[vertex * 3U + c]));
                }
                for (uint32_t c = 0; c < 2U; c++) {
                    mix(wr64FloatBits(drawData.tcFloats[vertex * 2U + c]));
                    mix(wr64FloatBits(drawData.tcVelFloats[vertex * 2U + c]));
                }
                for (uint32_t c = 0; c < 4U; c++) {
                    mix(drawData.normColBytes[vertex * 4U + c]);
                }
            }
            return hash;
        };
        const uint64_t primaryHashBefore = hashPrimary();
        const auto hashFacePrefix = [](const std::vector<uint32_t> &indices,
            size_t start, size_t count)
        {
            uint64_t hash = 1469598103934665603ULL;
            for (size_t i = 0; i < count; i++) {
                hash ^= uint64_t(indices[start + i]);
                hash *= 1099511628211ULL;
            }
            return hash;
        };
        const size_t primaryFaceIndexCount =
            size_t(PrimaryTriangleCount) * 3ULL;
        const uint64_t primaryFaceHashBefore = hashFacePrefix(
            drawData.faceIndices, size_t(faceStart), primaryFaceIndexCount);

        for (const GeneratedVertex &vertex : generated) {
            drawData.posFloats.insert(drawData.posFloats.end(),
                vertex.position, vertex.position + 3);
            drawData.velFloats.insert(drawData.velFloats.end(),
                vertex.velocity, vertex.velocity + 3);
            drawData.tcFloats.insert(drawData.tcFloats.end(),
                vertex.texcoord, vertex.texcoord + 2);
            drawData.tcVelFloats.insert(drawData.tcVelFloats.end(),
                vertex.texcoordVelocity, vertex.texcoordVelocity + 2);
            drawData.normColBytes.insert(drawData.normColBytes.end(),
                vertex.normalColor, vertex.normalColor + 4);
            drawData.viewProjIndices.push_back(
                drawData.viewProjIndices[vertex.source]);
            drawData.worldIndices.push_back(drawData.worldIndices[vertex.source]);
            drawData.fogIndices.push_back(drawData.fogIndices[vertex.source]);
            drawData.lightIndices.push_back(drawData.lightIndices[vertex.source]);
            drawData.lightCounts.push_back(drawData.lightCounts[vertex.source]);
            drawData.lookAtIndices.push_back(drawData.lookAtIndices[vertex.source]);
            drawData.vertexSegmentedAddresses.push_back(
                drawData.vertexSegmentedAddresses[vertex.source]);
            drawData.wr64WaterProducerKeys.push_back(0U);
            drawData.wr64WaterVertexMask.push_back(5U);
            // field mode remains zero. The remaining words are CPU metadata
            // for the exact post-match velocity derivation.
            const uint32_t info[4] = {
                0U, vertex.source, vertex.layer, vertex.loopIndex
            };
            drawData.wr64WaterFieldInfo.insert(
                drawData.wr64WaterFieldInfo.end(), info, info + 4);
            drawData.wr64WaterFieldPrevPosShiftX.push_back(hlslpp::float4(0.0f));
            drawData.wr64WaterFieldPrevTcShiftZ.push_back(hlslpp::float4(0.0f));
        }

        std::vector<uint32_t> combinedFaces;
        combinedFaces.reserve(size_t(PrimaryTriangleCount +
            AnnulusTriangleCount) * 3ULL);
        combinedFaces.insert(combinedFaces.end(),
            drawData.faceIndices.begin() + size_t(faceStart),
            drawData.faceIndices.begin() + size_t(faceStart) +
                size_t(PrimaryTriangleCount) * 3ULL);
        combinedFaces.insert(combinedFaces.end(),
            annulusFaces.begin(), annulusFaces.end());
        waterCall.meshDesc.faceIndicesStart = uint32_t(drawData.faceIndices.size());
        waterCall.callDesc.triangleCount = PrimaryTriangleCount +
            AnnulusTriangleCount;
        drawData.faceIndices.insert(drawData.faceIndices.end(),
            combinedFaces.begin(), combinedFaces.end());
        drawData.wr64WaterFaceIndices = combinedFaces;

        const uint64_t primaryHashAfter = hashPrimary();
        const uint64_t originalPrimaryFaceHashAfter = hashFacePrefix(
            drawData.faceIndices, size_t(faceStart), primaryFaceIndexCount);
        const uint64_t combinedPrimaryFaceHash = hashFacePrefix(
            combinedFaces, 0ULL, primaryFaceIndexCount);
        const bool finalInvariant =
            (drawData.vertexCount() == (originalVertexCount + RingVertexCount)) &&
            (waterCall.callDesc.triangleCount ==
                (PrimaryTriangleCount + AnnulusTriangleCount)) &&
            (drawData.wr64WaterVertexMask.size() == drawData.vertexCount()) &&
            (primaryHashBefore == primaryHashAfter) &&
            (primaryFaceHashBefore == originalPrimaryFaceHashAfter) &&
            (primaryFaceHashBefore == combinedPrimaryFaceHash);
        static uint32_t probeCount = 0;
        static uint32_t previousFarWaterMode = UINT32_MAX;
        if ((probeCount < 32U) || !finalInvariant || previousFarWaterMode != farWaterMode) {
            probeCount++;
            previousFarWaterMode = farWaterMode;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                "[water-dense-annulus] frame=%llu water_base=%u generated_base=%u primary=488/864 boundary=108 canonical=72 seam_pairs=18 primary_raw_zero=%u rings=4 added_vertices=288 added_triangles=576 total_vertices=%u total_triangles=%u far_mode=%u outer_scale=%.3f water_y=%.6f water_spread=%.6f min_cw=%.6f primary_hash=%016llx/%016llx face_hash=%016llx/%016llx/%016llx invariant=%s\n",
                static_cast<unsigned long long>(workload.submissionFrame),
                waterBase, originalVertexCount,
                primaryRawZeroCount,
                drawData.vertexCount(), waterCall.callDesc.triangleCount,
                farWaterMode, wr64FarWaterRingScale(farWaterMode, RingCount),
                waterDatum.height, waterDatum.spread,
                leastNegativeArea,
                static_cast<unsigned long long>(primaryHashBefore),
                static_cast<unsigned long long>(primaryHashAfter),
                static_cast<unsigned long long>(primaryFaceHashBefore),
                static_cast<unsigned long long>(originalPrimaryFaceHashAfter),
                static_cast<unsigned long long>(combinedPrimaryFaceHash),
                finalInvariant ? "PASS" : "FAIL"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
        }
        if (!finalInvariant) {
            std::abort();
        }
        return true;
    }

    static Wr64DenseWaterCallResult tryAugmentWr64WaterDenseAnnulus(
        Workload &workload, Projection &projection, uint32_t callIndex)
    {
        Wr64DenseWaterPreflight preflight;
        if (!preflightWr64WaterDenseAnnulus(workload, projection, callIndex,
            preflight))
        {
            return Wr64DenseWaterCallResult::NotApplicable;
        }

        if (!augmentWr64WaterDenseAnnulus(workload, projection, callIndex)) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                "[water-dense-preflight] frame=%llu call=%u triangles=%u distinct=%u span=%llu primary_distinct=%u primary_span=%llu result=NATIVE_RETAINED_AFTER_SHAPE_MATCH\n",
                static_cast<unsigned long long>(workload.submissionFrame),
                callIndex, preflight.triangleCount,
                preflight.distinctVertexCount,
                static_cast<unsigned long long>(preflight.vertexSpan),
                preflight.primaryDistinctVertexCount,
                static_cast<unsigned long long>(preflight.primaryVertexSpan)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            return Wr64DenseWaterCallResult::NativeRetained;
        }
        return Wr64DenseWaterCallResult::Augmented;
    }

    // Diagnostic R1: extend only the generated sheet's existing boundary. The
    // 488 primary vertices, their velocities and their UVs are never edited.
    // A one-cell ring is made from copies of the 108 true boundary vertices,
    // so the coarse six-corner flat fan begins farther from the camera without
    // translating or resampling the accepted wave field.
    static bool augmentWr64WaterCoverageRing(Workload &workload, Projection &projection,
        uint32_t callIndex)
    {
        if (!wr64WaterCoverageRingEnabled() || (callIndex >= projection.gameCallCount)) {
            return false;
        }

        DrawData &drawData = workload.drawData;
        GameCall &waterCall = projection.gameCalls[callIndex];
        const uint32_t originalTriangleCount = waterCall.callDesc.triangleCount;
        const uint64_t faceStart = waterCall.meshDesc.faceIndicesStart;
        const uint64_t faceEnd = faceStart + (uint64_t(originalTriangleCount) * 3ULL);
        if ((faceEnd > drawData.faceIndices.size()) ||
            (drawData.wr64WaterProducerKeys.size() != drawData.vertexCount()))
        {
            return false;
        }

        struct BoundaryEdge {
            uint32_t a = 0;
            uint32_t b = 0;
            uint32_t interior = 0;
            uint32_t count = 0;
        };
        std::map<std::pair<uint32_t, uint32_t>, BoundaryEdge> edges;
        uint32_t primaryTriangleCount = 0;
        for (uint32_t triangle = 0; triangle < originalTriangleCount; triangle++) {
            const uint32_t i = uint32_t(faceStart) + triangle * 3;
            const uint32_t tri[3] = {
                drawData.faceIndices[i + 0], drawData.faceIndices[i + 1],
                drawData.faceIndices[i + 2]
            };
            const bool primary =
                (tri[0] < drawData.wr64WaterProducerKeys.size()) &&
                (tri[1] < drawData.wr64WaterProducerKeys.size()) &&
                (tri[2] < drawData.wr64WaterProducerKeys.size()) &&
                (drawData.wr64WaterProducerKeys[tri[0]] != 0) &&
                (drawData.wr64WaterProducerKeys[tri[1]] != 0) &&
                (drawData.wr64WaterProducerKeys[tri[2]] != 0);
            if (!primary) {
                continue;
            }
            primaryTriangleCount++;

            for (uint32_t e = 0; e < 3; e++) {
                const uint32_t a = tri[e];
                const uint32_t b = tri[(e + 1) % 3];
                const std::pair<uint32_t, uint32_t> key =
                    (a < b) ? std::make_pair(a, b) : std::make_pair(b, a);
                BoundaryEdge &edge = edges[key];
                if (edge.count == 0) {
                    edge.a = a;
                    edge.b = b;
                    edge.interior = tri[(e + 2) % 3];
                }
                edge.count++;
            }
        }

        std::vector<BoundaryEdge> boundaryEdges;
        std::set<uint32_t> boundaryVertices;
        for (const auto &entry : edges) {
            if (entry.second.count == 1) {
                boundaryEdges.push_back(entry.second);
                boundaryVertices.emplace(entry.second.a);
                boundaryVertices.emplace(entry.second.b);
            }
        }
        if ((boundaryEdges.size() < 24) || boundaryVertices.empty()) {
            return false;
        }
        // On the verified 500-vertex sheet the rippled surface is the prefix
        // (864 triangles) and the coarse flat six-corner fan is the suffix
        // (12 triangles).  Only replace that suffix when the provenance test
        // proves the same ordering; otherwise leave the call untouched.
        if (primaryTriangleCount >= originalTriangleCount) {
            return false;
        }
        for (uint32_t triangle = 0; triangle < primaryTriangleCount; triangle++) {
            const uint32_t i = uint32_t(faceStart) + triangle * 3;
            for (uint32_t corner = 0; corner < 3; corner++) {
                const uint32_t vertex = drawData.faceIndices[i + corner];
                if ((vertex >= drawData.wr64WaterProducerKeys.size()) ||
                    (drawData.wr64WaterProducerKeys[vertex] == 0))
                {
                    return false;
                }
            }
        }

        std::set<uint32_t> fanInnerVertices;
        std::set<uint32_t> fanOuterVertices;
        for (uint32_t triangle = primaryTriangleCount;
            triangle < originalTriangleCount; triangle++)
        {
            const uint32_t i = uint32_t(faceStart) + triangle * 3;
            for (uint32_t corner = 0; corner < 3; corner++) {
                const uint32_t vertex = drawData.faceIndices[i + corner];
                if (vertex >= drawData.wr64WaterProducerKeys.size()) {
                    return false;
                }
                if (drawData.wr64WaterProducerKeys[vertex] == 0) {
                    fanOuterVertices.emplace(vertex);
                }
                else {
                    fanInnerVertices.emplace(vertex);
                }
            }
        }
        if ((fanInnerVertices.size() != 6) || (fanOuterVertices.size() != 6)) {
            return false;
        }

        std::map<uint32_t, std::vector<uint32_t>> boundaryInteriorVertices;
        for (const BoundaryEdge &edge : boundaryEdges) {
            boundaryInteriorVertices[edge.a].push_back(edge.interior);
            boundaryInteriorVertices[edge.b].push_back(edge.interior);
        }

        // The six fan-inner vertices are exact producer duplicates of six
        // primary-boundary corners. Resolve them by producer identity, then
        // sort both hexagons by angle so every dense boundary point can map to
        // its corresponding position on the original far-field perimeter.
        std::vector<uint32_t> innerCorners;
        for (uint32_t inner : fanInnerVertices) {
            uint32_t match = UINT32_MAX;
            for (uint32_t boundary : boundaryVertices) {
                if (drawData.wr64WaterProducerKeys[boundary] ==
                    drawData.wr64WaterProducerKeys[inner])
                {
                    match = boundary;
                    break;
                }
            }
            if (match == UINT32_MAX) {
                return false;
            }
            innerCorners.push_back(match);
        }
        std::vector<uint32_t> outerCorners(
            fanOuterVertices.begin(), fanOuterVertices.end());
        const auto sortByAngle = [&](std::vector<uint32_t> &vertices) {
            double cx = 0.0;
            double cz = 0.0;
            for (uint32_t vertex : vertices) {
                cx += drawData.posFloats[vertex * 3 + 0];
                cz += drawData.posFloats[vertex * 3 + 2];
            }
            cx /= double(vertices.size());
            cz /= double(vertices.size());
            std::sort(vertices.begin(), vertices.end(), [&](uint32_t a, uint32_t b) {
                const double aa = std::atan2(
                    double(drawData.posFloats[a * 3 + 2]) - cz,
                    double(drawData.posFloats[a * 3 + 0]) - cx);
                const double ab = std::atan2(
                    double(drawData.posFloats[b * 3 + 2]) - cz,
                    double(drawData.posFloats[b * 3 + 0]) - cx);
                return aa < ab;
            });
        };
        sortByAngle(innerCorners);
        sortByAngle(outerCorners);

        double innerCenterX = 0.0;
        double innerCenterZ = 0.0;
        double outerCenterX = 0.0;
        double outerCenterZ = 0.0;
        for (uint32_t i = 0; i < 6; i++) {
            innerCenterX += drawData.posFloats[innerCorners[i] * 3 + 0];
            innerCenterZ += drawData.posFloats[innerCorners[i] * 3 + 2];
            outerCenterX += drawData.posFloats[outerCorners[i] * 3 + 0];
            outerCenterZ += drawData.posFloats[outerCorners[i] * 3 + 2];
        }
        innerCenterX /= 6.0;
        innerCenterZ /= 6.0;
        outerCenterX /= 6.0;
        outerCenterZ /= 6.0;
        uint32_t bestRotation = 0;
        double bestRotationCost = std::numeric_limits<double>::max();
        for (uint32_t rotation = 0; rotation < 6; rotation++) {
            double cost = 0.0;
            for (uint32_t i = 0; i < 6; i++) {
                const uint32_t inner = innerCorners[i];
                const uint32_t outer = outerCorners[(i + rotation) % 6];
                double ix = drawData.posFloats[inner * 3 + 0] - innerCenterX;
                double iz = drawData.posFloats[inner * 3 + 2] - innerCenterZ;
                double ox = drawData.posFloats[outer * 3 + 0] - outerCenterX;
                double oz = drawData.posFloats[outer * 3 + 2] - outerCenterZ;
                const double il = std::sqrt(ix * ix + iz * iz);
                const double ol = std::sqrt(ox * ox + oz * oz);
                if ((il > 1.0e-6) && (ol > 1.0e-6)) {
                    ix /= il; iz /= il; ox /= ol; oz /= ol;
                    const double dx = ix - ox;
                    const double dz = iz - oz;
                    cost += dx * dx + dz * dz;
                }
            }
            if (cost < bestRotationCost) {
                bestRotationCost = cost;
                bestRotation = rotation;
            }
        }
        std::rotate(outerCorners.begin(),
            outerCorners.begin() + bestRotation, outerCorners.end());

        const uint32_t oldVertexCount = drawData.vertexCount();
        const auto hasVertexArrays = [&](uint32_t vertex) {
            return (((uint64_t(vertex) + 1ULL) * 3ULL) <= drawData.posFloats.size()) &&
                (((uint64_t(vertex) + 1ULL) * 3ULL) <= drawData.velFloats.size()) &&
                (((uint64_t(vertex) + 1ULL) * 2ULL) <= drawData.tcFloats.size()) &&
                (((uint64_t(vertex) + 1ULL) * 2ULL) <= drawData.tcVelFloats.size()) &&
                (((uint64_t(vertex) + 1ULL) * 4ULL) <= drawData.normColBytes.size()) &&
                (vertex < drawData.viewProjIndices.size()) &&
                (vertex < drawData.worldIndices.size()) &&
                (vertex < drawData.fogIndices.size()) &&
                (vertex < drawData.lightIndices.size()) &&
                (vertex < drawData.lightCounts.size()) &&
                (vertex < drawData.lookAtIndices.size());
        };

        constexpr uint32_t CoverageLayerCount = 12;
        std::vector<std::map<uint32_t, uint32_t>> coverageLayers(
            CoverageLayerCount + 1);
        for (uint32_t source : boundaryVertices) {
            coverageLayers[0].emplace(source, source);
        }
        for (uint32_t source : boundaryVertices) {
            if (!hasVertexArrays(source)) {
                return false;
            }
            const std::vector<uint32_t> &interior =
                boundaryInteriorVertices[source];
            if (interior.empty()) {
                return false;
            }

            uint32_t side = 0;
            float sideT = 0.0f;
            double bestSideDistance = std::numeric_limits<double>::max();
            const double px = drawData.posFloats[source * 3 + 0];
            const double pz = drawData.posFloats[source * 3 + 2];
            for (uint32_t candidate = 0; candidate < 6; candidate++) {
                const uint32_t a = innerCorners[candidate];
                const uint32_t b = innerCorners[(candidate + 1) % 6];
                const double ax = drawData.posFloats[a * 3 + 0];
                const double az = drawData.posFloats[a * 3 + 2];
                const double bx = drawData.posFloats[b * 3 + 0];
                const double bz = drawData.posFloats[b * 3 + 2];
                const double dx = bx - ax;
                const double dz = bz - az;
                const double lengthSquared = dx * dx + dz * dz;
                const double t = (lengthSquared > 1.0e-8) ? std::clamp(
                    ((px - ax) * dx + (pz - az) * dz) / lengthSquared,
                    0.0, 1.0) : 0.0;
                const double ex = px - (ax + dx * t);
                const double ez = pz - (az + dz * t);
                const double distance = ex * ex + ez * ez;
                if (distance < bestSideDistance) {
                    bestSideDistance = distance;
                    side = candidate;
                    sideT = float(t);
                }
            }

            const uint32_t outerA = outerCorners[side];
            const uint32_t outerB = outerCorners[(side + 1) % 6];
            if (!hasVertexArrays(outerA) || !hasVertexArrays(outerB)) {
                return false;
            }

            float outerPosition[3] = {};
            float outerVelocity[3] = {};
            float outerTexcoord[2] = {};
            float outerTexcoordVelocity[2] = {};
            for (uint32_t component = 0; component < 3; component++) {
                const float posA = drawData.posFloats[outerA * 3 + component];
                const float posB = drawData.posFloats[outerB * 3 + component];
                const float velA = drawData.velFloats[outerA * 3 + component];
                const float velB = drawData.velFloats[outerB * 3 + component];
                outerPosition[component] = posA + (posB - posA) * sideT;
                outerVelocity[component] = velA + (velB - velA) * sideT;
            }
            for (uint32_t component = 0; component < 2; component++) {
                const float tcA = drawData.tcFloats[outerA * 2 + component];
                const float tcB = drawData.tcFloats[outerB * 2 + component];
                const float tcVelA = drawData.tcVelFloats[outerA * 2 + component];
                const float tcVelB = drawData.tcVelFloats[outerB * 2 + component];
                outerTexcoord[component] = tcA + (tcB - tcA) * sideT;
                outerTexcoordVelocity[component] =
                    tcVelA + (tcVelB - tcVelA) * sideT;
            }
            uint8_t outerNormalColor[4] = {};
            for (uint32_t component = 0; component < 4; component++) {
                const float colorA = float(
                    drawData.normColBytes[outerA * 4 + component]);
                const float colorB = float(
                    drawData.normColBytes[outerB * 4 + component]);
                outerNormalColor[component] = uint8_t(std::clamp(std::lround(
                    colorA + (colorB - colorA) * sideT), 0L, 255L));
            }
            float positionGradient[3] = {};
            float velocityGradient[3] = {};
            float texcoordGradient[2] = {};
            float texcoordVelocityGradient[2] = {};
            float normalColorGradient[4] = {};
            double interiorDistance = 0.0;
            for (uint32_t inside : interior) {
                const double dx = double(drawData.posFloats[source * 3 + 0]) -
                    double(drawData.posFloats[inside * 3 + 0]);
                const double dz = double(drawData.posFloats[source * 3 + 2]) -
                    double(drawData.posFloats[inside * 3 + 2]);
                interiorDistance += std::sqrt(dx * dx + dz * dz);
                for (uint32_t component = 0; component < 3; component++) {
                    positionGradient[component] +=
                        drawData.posFloats[source * 3 + component] -
                        drawData.posFloats[inside * 3 + component];
                    velocityGradient[component] +=
                        drawData.velFloats[source * 3 + component] -
                        drawData.velFloats[inside * 3 + component];
                }
                for (uint32_t component = 0; component < 2; component++) {
                    texcoordGradient[component] +=
                        drawData.tcFloats[source * 2 + component] -
                        drawData.tcFloats[inside * 2 + component];
                    texcoordVelocityGradient[component] +=
                        drawData.tcVelFloats[source * 2 + component] -
                        drawData.tcVelFloats[inside * 2 + component];
                }
                for (uint32_t component = 0; component < 4; component++) {
                    normalColorGradient[component] +=
                        float(drawData.normColBytes[source * 4 + component]) -
                        float(drawData.normColBytes[inside * 4 + component]);
                }
            }
            const float inverseInteriorCount = 1.0f / float(interior.size());
            interiorDistance *= double(inverseInteriorCount);
            for (float &value : positionGradient) value *= inverseInteriorCount;
            for (float &value : velocityGradient) value *= inverseInteriorCount;
            for (float &value : texcoordGradient) value *= inverseInteriorCount;
            for (float &value : texcoordVelocityGradient) value *= inverseInteriorCount;
            for (float &value : normalColorGradient) value *= inverseInteriorCount;
            const double outerDx = double(outerPosition[0]) -
                double(drawData.posFloats[source * 3 + 0]);
            const double outerDz = double(outerPosition[2]) -
                double(drawData.posFloats[source * 3 + 2]);
            const double outerDistance = std::sqrt(
                outerDx * outerDx + outerDz * outerDz);
            const float gradientScale = (interiorDistance > 1.0e-4) ?
                float(std::clamp(outerDistance / interiorDistance, 0.0, 8.0)) : 0.0f;
            const uint32_t fieldInfo[4] = {
                drawData.wr64WaterFieldInfo[outerA * 4 + 0],
                drawData.wr64WaterFieldInfo[outerA * 4 + 1],
                drawData.wr64WaterFieldInfo[outerA * 4 + 2],
                drawData.wr64WaterFieldInfo[outerA * 4 + 3]
            };
            const hlslpp::float4 fieldPrevPosShiftX =
                drawData.wr64WaterFieldPrevPosShiftX[outerA];
            const hlslpp::float4 fieldPrevTcShiftZ =
                drawData.wr64WaterFieldPrevTcShiftZ[outerA];

            for (uint32_t layer = 1; layer <= CoverageLayerCount; layer++) {
                const float layerT = float(layer) / float(CoverageLayerCount);
                const float t2 = layerT * layerT;
                const float t3 = t2 * layerT;
                const float hermiteSource = (2.0f * t3) - (3.0f * t2) + 1.0f;
                const float hermiteGradient = t3 - (2.0f * t2) + layerT;
                const float hermiteOuter = (-2.0f * t3) + (3.0f * t2);
                const uint32_t appended = drawData.vertexCount();
                coverageLayers[layer].emplace(source, appended);
                float position[3] = {};
                float velocity[3] = {};
                float texcoord[2] = {};
                float texcoordVelocity[2] = {};
                uint8_t normalColor[4] = {};
                for (uint32_t component = 0; component < 3; component++) {
                    const float sourcePos = drawData.posFloats[source * 3 + component];
                    const float sourceVel = drawData.velFloats[source * 3 + component];
                    if (component == 1) {
                        position[component] = hermiteSource * sourcePos +
                            hermiteGradient * positionGradient[component] * gradientScale +
                            hermiteOuter * outerPosition[component];
                        velocity[component] = hermiteSource * sourceVel +
                            hermiteGradient * velocityGradient[component] * gradientScale +
                            hermiteOuter * outerVelocity[component];
                    }
                    else {
                        position[component] = sourcePos +
                            (outerPosition[component] - sourcePos) * layerT;
                        velocity[component] = sourceVel +
                            (outerVelocity[component] - sourceVel) * layerT;
                    }
                }
                for (uint32_t component = 0; component < 2; component++) {
                    const float sourceTc = drawData.tcFloats[source * 2 + component];
                    const float sourceTcVel = drawData.tcVelFloats[source * 2 + component];
                    texcoord[component] = hermiteSource * sourceTc +
                        hermiteGradient * texcoordGradient[component] * gradientScale +
                        hermiteOuter * outerTexcoord[component];
                    texcoordVelocity[component] = hermiteSource * sourceTcVel +
                        hermiteGradient * texcoordVelocityGradient[component] * gradientScale +
                        hermiteOuter * outerTexcoordVelocity[component];
                }
                for (uint32_t component = 0; component < 4; component++) {
                    const float sourceColor = float(
                        drawData.normColBytes[source * 4 + component]);
                    normalColor[component] = uint8_t(std::clamp(std::lround(
                        hermiteSource * sourceColor + hermiteGradient *
                        normalColorGradient[component] * gradientScale +
                        hermiteOuter * float(outerNormalColor[component])),
                        0L, 255L));
                }

                drawData.posFloats.insert(drawData.posFloats.end(), position, position + 3);
                drawData.velFloats.insert(drawData.velFloats.end(), velocity, velocity + 3);
                drawData.tcFloats.insert(drawData.tcFloats.end(), texcoord, texcoord + 2);
                drawData.tcVelFloats.insert(drawData.tcVelFloats.end(),
                    texcoordVelocity, texcoordVelocity + 2);
                drawData.normColBytes.insert(drawData.normColBytes.end(),
                    normalColor, normalColor + 4);
                drawData.viewProjIndices.push_back(drawData.viewProjIndices[outerA]);
                drawData.worldIndices.push_back(drawData.worldIndices[outerA]);
                drawData.fogIndices.push_back(drawData.fogIndices[outerA]);
                drawData.lightIndices.push_back(drawData.lightIndices[outerA]);
                drawData.lightCounts.push_back(drawData.lightCounts[outerA]);
                drawData.lookAtIndices.push_back(drawData.lookAtIndices[outerA]);
                drawData.vertexSegmentedAddresses.push_back(
                    drawData.vertexSegmentedAddresses[outerA]);
                drawData.wr64WaterProducerKeys.push_back(0);
                // 2 distinguishes generated coverage vertices from the game's
                // original water vertices (1). It is CPU metadata only.
                drawData.wr64WaterVertexMask.push_back(2);
                drawData.wr64WaterFieldInfo.insert(drawData.wr64WaterFieldInfo.end(),
                    fieldInfo, fieldInfo + 4);
                drawData.wr64WaterFieldPrevPosShiftX.push_back(fieldPrevPosShiftX);
                drawData.wr64WaterFieldPrevTcShiftZ.push_back(fieldPrevTcShiftZ);
            }
        }

        std::vector<uint32_t> supplementalFaces;
        supplementalFaces.reserve(
            boundaryEdges.size() * 6 * CoverageLayerCount);
        for (uint32_t layer = 1; layer <= CoverageLayerCount; layer++) {
            for (const BoundaryEdge &edge : boundaryEdges) {
                const uint32_t innerA = coverageLayers[layer - 1].at(edge.a);
                const uint32_t innerB = coverageLayers[layer - 1].at(edge.b);
                const uint32_t outerA = coverageLayers[layer].at(edge.a);
                const uint32_t outerB = coverageLayers[layer].at(edge.b);
                // The stored edge direction is the primary triangle's winding.
                // Its interior is on the left; these occupy the opposite side.
                supplementalFaces.push_back(innerB);
                supplementalFaces.push_back(innerA);
                supplementalFaces.push_back(outerA);
                supplementalFaces.push_back(innerB);
                supplementalFaces.push_back(outerA);
                supplementalFaces.push_back(outerB);
            }
        }

        // Re-emit the accepted primary prefix and the replacement fan as one
        // contiguous index range. A separate call creates a visible blend seam
        // even with identical material state because this water is translucent.
        std::vector<uint32_t> combinedFaces;
        combinedFaces.reserve(size_t(primaryTriangleCount) * 3 +
            supplementalFaces.size());
        combinedFaces.insert(combinedFaces.end(),
            drawData.faceIndices.begin() + size_t(faceStart),
            drawData.faceIndices.begin() + size_t(faceStart) +
                size_t(primaryTriangleCount) * 3);
        combinedFaces.insert(combinedFaces.end(),
            supplementalFaces.begin(), supplementalFaces.end());
        waterCall.meshDesc.faceIndicesStart = uint32_t(drawData.faceIndices.size());
        waterCall.callDesc.triangleCount = uint32_t(combinedFaces.size() / 3);
        drawData.faceIndices.insert(drawData.faceIndices.end(),
            combinedFaces.begin(), combinedFaces.end());
        drawData.wr64WaterFaceIndices = combinedFaces;

        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
            "[water-coverage] frame=%llu primary=%u boundary=%u added_vertices=%u added_triangles=%u\n",
            static_cast<unsigned long long>(workload.submissionFrame),
            primaryTriangleCount, uint32_t(boundaryEdges.size()),
            drawData.vertexCount() - oldVertexCount,
            uint32_t(supplementalFaces.size() / 3)); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
        return true;
    }

    struct Wr64DenseAnnulusFinalizeResult {
        bool attempted = false;
        bool passed = false;
        bool suppressed = false;
        bool initialized = false;
    };

    // The generated rings are outside the original transform's 500-vertex
    // range, so ordinary call matching cannot write their velocities. Derive
    // them from the already accepted primary velocities after matchScenes.
    // All candidate values are staged and the full fractional-time winding is
    // proven before a single buffer element is committed.
    static Wr64DenseAnnulusFinalizeResult finalizeWr64WaterDenseAnnulus(
        DrawData &curDraw, const DrawData &prevDraw, uint64_t submissionFrame,
        bool compatibleHistory = true)
    {
        constexpr uint32_t PrimaryVertexCount = 488U;
        constexpr uint32_t StockVertexCount = 500U;
        constexpr uint32_t BoundaryCount = 72U;
        constexpr uint32_t RingCount = 4U;
        constexpr uint32_t RingVertexCount = BoundaryCount * RingCount;
        constexpr uint32_t PrimaryTriangleCount = 864U;
        constexpr uint32_t AnnulusTriangleCount =
            BoundaryCount * RingCount * 2U;
        constexpr uint32_t TotalTriangleCount =
            PrimaryTriangleCount + AnnulusTriangleCount;

        Wr64DenseAnnulusFinalizeResult result;
        if (!wr64WaterDenseAnnulusEnabled()) return result;
        uint32_t maskCount = 0;
        uint32_t generatedBase = UINT32_MAX;
        uint32_t generatedLast = 0U;
        for (uint32_t vertex = 0;
            vertex < curDraw.wr64WaterVertexMask.size(); vertex++)
        {
            if (curDraw.wr64WaterVertexMask[vertex] == 5U) {
                maskCount++;
                generatedBase = std::min(generatedBase, vertex);
                generatedLast = std::max(generatedLast, vertex);
            }
        }
        if (maskCount == 0U) return result;
        result.attempted = true;

        const auto fail = [&](const char *reason) -> Wr64DenseAnnulusFinalizeResult {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                "[water-dense-finalize] frame=%llu invariant=FAIL action=FATAL reason=%s mask=%u vertices=%u faces=%zu\n",
                static_cast<unsigned long long>(submissionFrame), reason,
                maskCount, curDraw.vertexCount(),
                curDraw.wr64WaterFaceIndices.size() / 3ULL); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
            // Once the stock fan has been replaced, rendering an internally
            // inconsistent or folded
            // generated surface would create the exact full-screen flashes
            // this candidate is designed to prevent.  Stop before upload.
            std::abort();
            return result;
        };
        const auto arraysValid = [](const DrawData &draw) {
            const size_t n = draw.vertexCount();
            return (draw.posFloats.size() == n * 3ULL) &&
                (draw.velFloats.size() == n * 3ULL) &&
                (draw.tcFloats.size() == n * 2ULL) &&
                (draw.tcVelFloats.size() == n * 2ULL) &&
                (draw.normColBytes.size() == n * 4ULL) &&
                (draw.vertexSegmentedAddresses.size() == n) &&
                (draw.wr64WaterProducerKeys.size() == n) &&
                (draw.wr64WaterVertexMask.size() == n) &&
                (draw.wr64WaterFieldInfo.size() == n * 4ULL);
        };
        if ((maskCount != RingVertexCount) || !arraysValid(curDraw) ||
            (generatedBase < StockVertexCount) ||
            (uint64_t(generatedBase) + RingVertexCount !=
                curDraw.vertexCount()) ||
            (generatedLast != (generatedBase + RingVertexCount - 1U)) ||
            (curDraw.wr64WaterFaceIndices.size() !=
                size_t(TotalTriangleCount) * 3ULL))
        {
            return fail("current_shape");
        }
        // The water range is not the end of DrawData: the opening workload has
        // 77 unrelated vertices after its 500 water slots. Derive the local
        // base from the retained primary face prefix, while the mask locates
        // the separately appended generated block.
        const auto deriveWaterBase = [&](const DrawData &draw,
            uint32_t drawGeneratedBase, uint32_t &drawWaterBase)
        {
            if (draw.wr64WaterFaceIndices.size() !=
                size_t(TotalTriangleCount) * 3ULL)
            {
                return false;
            }
            std::set<uint32_t> primaryVertices;
            const size_t primaryIndexCount =
                size_t(PrimaryTriangleCount) * 3ULL;
            for (size_t f = 0; f < primaryIndexCount; f++) {
                const uint32_t vertex = draw.wr64WaterFaceIndices[f];
                if (vertex >= drawGeneratedBase) return false;
                primaryVertices.insert(vertex);
            }
            if (primaryVertices.size() != PrimaryVertexCount) return false;
            drawWaterBase = *primaryVertices.begin();
            if ((uint64_t(drawWaterBase) + StockVertexCount) >
                drawGeneratedBase)
            {
                return false;
            }
            for (uint32_t local = 0; local < PrimaryVertexCount; local++) {
                if (primaryVertices.count(drawWaterBase + local) != 1U) {
                    return false;
                }
            }
            for (size_t f = primaryIndexCount;
                f < draw.wr64WaterFaceIndices.size(); f++)
            {
                const uint32_t vertex = draw.wr64WaterFaceIndices[f];
                const bool primary = (vertex >= drawWaterBase) &&
                    (vertex < (drawWaterBase + PrimaryVertexCount));
                const bool generated = (vertex >= drawGeneratedBase) &&
                    (vertex < (drawGeneratedBase + RingVertexCount));
                if (!primary && !generated) return false;
            }
            return true;
        };
        uint32_t waterBase = 0U;
        if (!deriveWaterBase(curDraw, generatedBase, waterBase)) {
            return fail("current_face_ranges");
        }
        // Match the augmenter's course-independent segment-3 provenance rule.
        // Generated vertices remain identified by mask and slot topology.
        const auto primarySourceValid = [&](const DrawData &draw,
            uint32_t source, uint32_t drawWaterBase)
        {
            if ((source < drawWaterBase) ||
                (source >= (drawWaterBase + PrimaryVertexCount)) ||
                (source >= draw.vertexCount()))
            {
                return false;
            }
            const uint32_t address = draw.vertexSegmentedAddresses[source];
            return isWr64GeneratedWaterVertexAddress(address);
        };

        uint32_t previousMaskCount = 0;
        uint32_t previousGeneratedBase = UINT32_MAX;
        uint32_t previousGeneratedLast = 0U;
        for (uint32_t vertex = 0;
            vertex < prevDraw.wr64WaterVertexMask.size(); vertex++)
        {
            if (prevDraw.wr64WaterVertexMask[vertex] == 5U) {
                previousMaskCount++;
                previousGeneratedBase = std::min(previousGeneratedBase, vertex);
                previousGeneratedLast = std::max(previousGeneratedLast, vertex);
            }
        }
        const bool previousDenseAvailable =
            compatibleHistory && (previousMaskCount == RingVertexCount) &&
            arraysValid(prevDraw) &&
            (previousGeneratedBase >= StockVertexCount) &&
            (uint64_t(previousGeneratedBase) + RingVertexCount ==
                prevDraw.vertexCount()) &&
            (previousGeneratedLast ==
                (previousGeneratedBase + RingVertexCount - 1U));
        if (compatibleHistory && (previousMaskCount != 0U) && !previousDenseAvailable) {
            return fail("previous_partial_shape");
        }
        uint32_t previousWaterBase = 0U;
        if (previousDenseAvailable && !deriveWaterBase(prevDraw,
            previousGeneratedBase, previousWaterBase))
        {
            return fail("previous_face_ranges");
        }
        result.initialized = !previousDenseAvailable;

        Wr64PrimaryWaterDatum currentWaterDatum;
        if (!measureWr64PrimaryWaterDatum(curDraw, waterBase,
                currentWaterDatum))
        {
            return fail("current_water_datum");
        }
        Wr64PrimaryWaterDatum previousWaterDatum = currentWaterDatum;
        if (previousDenseAvailable && !measureWr64PrimaryWaterDatum(prevDraw,
                previousWaterBase, previousWaterDatum))
        {
            return fail("previous_water_datum");
        }

        std::vector<uint32_t> ringVertexBySlot(RingVertexCount, UINT32_MAX);
        uint32_t sourceRebaseSlots = 0U;
        for (uint32_t vertex = 0; vertex < curDraw.vertexCount(); vertex++) {
            if (curDraw.wr64WaterVertexMask[vertex] != 5U) continue;
            if (curDraw.wr64WaterFieldInfo[vertex * 4U + 0U] != 0U)
            {
                return fail("current_mode");
            }
            const uint32_t source =
                curDraw.wr64WaterFieldInfo[vertex * 4U + 1U];
            const uint32_t layer =
                curDraw.wr64WaterFieldInfo[vertex * 4U + 2U];
            const uint32_t loopIndex =
                curDraw.wr64WaterFieldInfo[vertex * 4U + 3U];
            if (!primarySourceValid(curDraw, source, waterBase) ||
                (layer < 1U) || (layer > RingCount) ||
                (loopIndex >= BoundaryCount))
            {
                return fail("metadata");
            }
            const uint32_t slot = (layer - 1U) * BoundaryCount + loopIndex;
            if (vertex != (generatedBase + slot)) {
                return fail("slot_layout");
            }
            if (previousDenseAvailable) {
                const uint32_t previousVertex = previousGeneratedBase + slot;
                if ((prevDraw.wr64WaterVertexMask[previousVertex] != 5U) ||
                    (prevDraw.wr64WaterFieldInfo[
                        previousVertex * 4U + 0U] != 0U))
                {
                    return fail("previous_mode_or_mask_reset");
                }
                const uint32_t previousSource = prevDraw.wr64WaterFieldInfo[
                    previousVertex * 4U + 1U];
                if (!primarySourceValid(prevDraw, previousSource,
                        previousWaterBase) ||
                    ((source - waterBase) !=
                        (previousSource - previousWaterBase)) ||
                    (layer != prevDraw.wr64WaterFieldInfo[
                        previousVertex * 4U + 2U]) ||
                    (loopIndex != prevDraw.wr64WaterFieldInfo[
                        previousVertex * 4U + 3U]))
                {
                    return fail("metadata_reset");
                }
                // Producer keys describe the generated lattice domain, not a
                // persistent presentation identity.  The stock water normally
                // rebases those keys (and same-local-slot X/Z) when the camera
                // crosses a cell.  The annulus deliberately follows the
                // accepted current primary slot and its accepted velocity, so
                // record this event without treating it as interpolation
                // corruption.  Local source/layer/loop identity above remains
                // mandatory, and the all-weight winding proof below remains
                // the fail-closed geometry guard.
                if (curDraw.wr64WaterProducerKeys[source] !=
                    prevDraw.wr64WaterProducerKeys[previousSource])
                {
                    sourceRebaseSlots++;
                }
            }
            if (ringVertexBySlot[slot] != UINT32_MAX) {
                return fail("duplicate_slot");
            }
            ringVertexBySlot[slot] = vertex;
        }
        for (uint32_t vertex : ringVertexBySlot) {
            if (vertex == UINT32_MAX) return fail("missing_slot");
        }

        uint32_t anchorSources[6] = {};
        double centerPosition[2] = {};
        double centerVelocity[2] = {};
        for (uint32_t anchor = 0; anchor < 6U; anchor++) {
            const uint32_t ringVertex =
                ringVertexBySlot[anchor * 12U];
            const uint32_t source =
                curDraw.wr64WaterFieldInfo[ringVertex * 4U + 1U];
            anchorSources[anchor] = source;
            centerPosition[0] += curDraw.posFloats[source * 3U + 0U];
            centerPosition[1] += curDraw.posFloats[source * 3U + 2U];
            centerVelocity[0] += curDraw.velFloats[source * 3U + 0U];
            centerVelocity[1] += curDraw.velFloats[source * 3U + 2U];
        }
        centerPosition[0] /= 6.0;
        centerPosition[1] /= 6.0;
        centerVelocity[0] /= 6.0;
        centerVelocity[1] /= 6.0;
        const double previousCenterX = centerPosition[0] - centerVelocity[0];
        const double previousCenterZ = centerPosition[1] - centerVelocity[1];

        const auto hashStock = [&]() {
            uint64_t hash = 1469598103934665603ULL;
            const auto mix = [&](uint64_t value) {
                hash ^= value;
                hash *= 1099511628211ULL;
            };
            for (uint32_t local = 0; local < StockVertexCount; local++) {
                const uint32_t vertex = waterBase + local;
                for (uint32_t c = 0; c < 3U; c++) {
                    mix(wr64FloatBits(curDraw.posFloats[vertex * 3U + c]));
                    mix(wr64FloatBits(curDraw.velFloats[vertex * 3U + c]));
                }
                for (uint32_t c = 0; c < 2U; c++) {
                    mix(wr64FloatBits(curDraw.tcFloats[vertex * 2U + c]));
                    mix(wr64FloatBits(curDraw.tcVelFloats[vertex * 2U + c]));
                }
                for (uint32_t c = 0; c < 4U; c++) {
                    mix(curDraw.normColBytes[vertex * 4U + c]);
                }
            }
            return hash;
        };
        const uint64_t stockHashBefore = hashStock();

        std::vector<float> candidateVelocity = curDraw.velFloats;
        std::vector<float> candidateTcVelocity = curDraw.tcVelFloats;
        double maxCurrentFormulaError = 0.0;
        double maxPreviousFormulaError = 0.0;
        double maxPreviousSlotError = 0.0;
        const uint32_t currentFarWaterMode = curDraw.wr64FarWaterDistanceMode;
        const uint32_t previousFarWaterMode = previousDenseAvailable
            ? prevDraw.wr64FarWaterDistanceMode : currentFarWaterMode;
        const uint32_t currentWaveMode = curDraw.wr64WaveDistance.mode;
        const uint32_t previousWaveMode = previousDenseAvailable ? prevDraw.wr64WaveDistance.mode : currentWaveMode;
        for (uint32_t slot = 0; slot < RingVertexCount; slot++) {
            const uint32_t vertex = ringVertexBySlot[slot];
            const uint32_t source =
                curDraw.wr64WaterFieldInfo[vertex * 4U + 1U];
            const uint32_t layer =
                curDraw.wr64WaterFieldInfo[vertex * 4U + 2U];
            const double g = wr64WaveRingScale(currentWaveMode, currentFarWaterMode, layer);
            const double previousG = wr64WaveRingScale(previousWaveMode, previousFarWaterMode, layer);
            // Match augmentation's neutral UV/lighting and datum-relative
            // profile, including the optional Extended+ height tail.
            // Each native endpoint owns its extent: a setting/camera change
            // must interpolate from the previous extent, not reconstruct it
            // using the newest UI value.
            const double h = 1.0;
            const double expectedCurrent[3] = {
                centerPosition[0] + g *
                    (double(curDraw.posFloats[source * 3U + 0U]) -
                        centerPosition[0]),
                wr64WaveRingHeight(currentWaveMode, g, currentWaterDatum.height,
                    curDraw.posFloats[source * 3U + 1U]),
                centerPosition[1] + g *
                    (double(curDraw.posFloats[source * 3U + 2U]) -
                        centerPosition[1])
            };
            const double sourcePreviousX =
                double(curDraw.posFloats[source * 3U + 0U]) -
                double(curDraw.velFloats[source * 3U + 0U]);
            const double sourcePreviousZ =
                double(curDraw.posFloats[source * 3U + 2U]) -
                double(curDraw.velFloats[source * 3U + 2U]);
            // Retain the legacy flat-annulus formula for Original sessions.
            // Animated history is sampled at the generated point itself below:
            // a boundary sample is at a different radial location after a grid
            // recenter and cannot describe the previous rendered annulus.
            const double sourcePreviousY = double(curDraw.posFloats[source * 3U + 1U]) -
                double(curDraw.velFloats[source * 3U + 1U]);
            double expectedPrevious[3] = {
                previousCenterX + previousG * (sourcePreviousX - previousCenterX),
                wr64WaveRingHeight(previousWaveMode, previousG, previousWaterDatum.height, sourcePreviousY),
                previousCenterZ + previousG * (sourcePreviousZ - previousCenterZ)
            };
            if (currentWaveMode || previousWaveMode) {
                expectedPrevious[1] = curDraw.posFloats[vertex * 3U + 1U];
                const auto &surface = curDraw.wr64WaveDistance.previousSurface;
                double previousHeight = 0.0;
                if (previousDenseAvailable && surface.matches(prevDraw) &&
                    surface.sample(expectedPrevious[0], expectedPrevious[2], previousHeight))
                {
                    expectedPrevious[1] = previousHeight;
                }
            }
            for (uint32_t component = 0; component < 3U; component++) {
                maxCurrentFormulaError = std::max(maxCurrentFormulaError,
                    std::fabs(double(curDraw.posFloats[vertex * 3U + component]) -
                        expectedCurrent[component]));
                // Use the generated endpoint itself, not a second rounded
                // reconstruction of its velocity.  Ordinary mode-0 therefore
                // lands exactly on the affine previous endpoint at q=1.
                candidateVelocity[vertex * 3U + component] = float(
                    double(curDraw.posFloats[vertex * 3U + component]) -
                    expectedPrevious[component]);
                maxPreviousFormulaError = std::max(maxPreviousFormulaError,
                    std::fabs((double(curDraw.posFloats[vertex * 3U + component]) -
                        double(candidateVelocity[vertex * 3U + component])) -
                        expectedPrevious[component]));
                // With pinned X/Z, a rebased generated vertex samples another
                // point of the previous rendered surface, not its old local
                // slot. X/Z slot diagnostics and the winding proof still apply.
                if (previousDenseAvailable && (component != 1U || (currentWaveMode != 2U && previousWaveMode != 2U))) {
                    const uint32_t previousVertex =
                        previousGeneratedBase + slot;
                    maxPreviousSlotError = std::max(maxPreviousSlotError,
                        std::fabs(double(prevDraw.posFloats[
                            previousVertex * 3U + component]) -
                            expectedPrevious[component]));
                }
            }
            for (uint32_t component = 0; component < 2U; component++) {
                const double sourceTc =
                    curDraw.tcFloats[source * 2U + component];
                const double sourcePrevTc = sourceTc -
                    curDraw.tcVelFloats[source * 2U + component];
                const double flatTargetCurrent = sourceTc +
                    std::remainder(16.0 - sourceTc, 32.0);
                // Hold the current target representative fixed across this
                // native interval. Recomputing it from sourcePrevTc can choose
                // an equivalent +/-32 branch and manufacture a false reset.
                const double flatTargetPrevious = flatTargetCurrent;
                const double expectedCurrentTc = sourceTc + h *
                    (flatTargetCurrent - sourceTc);
                maxCurrentFormulaError = std::max(maxCurrentFormulaError,
                    std::fabs(double(curDraw.tcFloats[vertex * 2U + component]) -
                        expectedCurrentTc));
                const double expectedPreviousTc = sourcePrevTc + h *
                    (flatTargetPrevious - sourcePrevTc);
                candidateTcVelocity[vertex * 2U + component] = float(
                    double(curDraw.tcFloats[vertex * 2U + component]) -
                    expectedPreviousTc);
                maxPreviousFormulaError = std::max(maxPreviousFormulaError,
                    std::fabs(std::remainder(
                        (double(curDraw.tcFloats[vertex * 2U + component]) -
                            double(candidateTcVelocity[vertex * 2U + component])) -
                        expectedPreviousTc, 32.0)));
                if (previousDenseAvailable) {
                    const uint32_t previousVertex =
                        previousGeneratedBase + slot;
                    maxPreviousSlotError = std::max(maxPreviousSlotError,
                        std::fabs(std::remainder(
                            double(prevDraw.tcFloats[
                                previousVertex * 2U + component]) -
                            expectedPreviousTc, 32.0)));
                }
            }
        }
        if (!std::isfinite(maxCurrentFormulaError) ||
            !std::isfinite(maxPreviousFormulaError) ||
            !std::isfinite(maxPreviousSlotError) ||
            (maxCurrentFormulaError > 1.0e-2) ||
            (maxPreviousFormulaError > 1.0e-2))
        {
            return fail("endpoint_formula");
        }

        const auto areaAtInverseWeight = [&](uint32_t a, uint32_t b,
            uint32_t c, double q)
        {
            const auto coordinate = [&](uint32_t vertex, uint32_t component) {
                return double(curDraw.posFloats[vertex * 3U + component]) -
                    double(candidateVelocity[vertex * 3U + component]) * q;
            };
            const double ax = coordinate(a, 0U);
            const double az = coordinate(a, 2U);
            const double bx = coordinate(b, 0U);
            const double bz = coordinate(b, 2U);
            const double cx = coordinate(c, 0U);
            const double cz = coordinate(c, 2U);
            return (bx - ax) * (cz - az) - (bz - az) * (cx - ax);
        };
        double closestAreaToZero = -std::numeric_limits<double>::max();
        const size_t annulusFaceStart = size_t(PrimaryTriangleCount) * 3ULL;
        for (uint32_t triangle = 0; triangle < AnnulusTriangleCount; triangle++) {
            const size_t f = annulusFaceStart + size_t(triangle) * 3ULL;
            const uint32_t a = curDraw.wr64WaterFaceIndices[f + 0ULL];
            const uint32_t b = curDraw.wr64WaterFaceIndices[f + 1ULL];
            const uint32_t c = curDraw.wr64WaterFaceIndices[f + 2ULL];
            if ((a >= curDraw.vertexCount()) ||
                (b >= curDraw.vertexCount()) ||
                (c >= curDraw.vertexCount())) return fail("face_index");
            const double area0 = areaAtInverseWeight(a, b, c, 0.0);
            const double area1 = areaAtInverseWeight(a, b, c, 1.0);
            const double areaHalf = areaAtInverseWeight(a, b, c, 0.5);
            // A(q)=aq^2+bq+c, reconstructed from q=0,.5,1.
            const double quadraticC = area0;
            const double quadraticA = 2.0 * (area1 + area0 -
                (2.0 * areaHalf));
            const double quadraticB = area1 - area0 - quadraticA;
            double worst = std::max(area0, area1);
            if (std::fabs(quadraticA) > 1.0e-12) {
                const double extremum = -quadraticB / (2.0 * quadraticA);
                if ((extremum > 0.0) && (extremum < 1.0)) {
                    const double areaExtremum = quadraticA * extremum * extremum +
                        quadraticB * extremum + quadraticC;
                    worst = std::max(worst, areaExtremum);
                }
            }
            if (!(worst < -1.0e-3)) return fail("fractional_fold");
            closestAreaToZero = std::max(closestAreaToZero, worst);
        }

        for (uint32_t slot = 0; slot < RingVertexCount; slot++) {
            const uint32_t vertex = ringVertexBySlot[slot];
            for (uint32_t component = 0; component < 3U; component++) {
                curDraw.velFloats[vertex * 3U + component] =
                    candidateVelocity[vertex * 3U + component];
            }
            for (uint32_t component = 0; component < 2U; component++) {
                curDraw.tcVelFloats[vertex * 2U + component] =
                    candidateTcVelocity[vertex * 2U + component];
            }
        }
        const uint64_t stockHashAfter = hashStock();
        if (stockHashBefore != stockHashAfter) return fail("primary_mutation");

        result.passed = true;
        static uint32_t passProbeCount = 0;
        if (passProbeCount < 48U) {
            passProbeCount++;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                "[water-dense-finalize] frame=%llu invariant=PASS lifecycle=%s water_base=%u generated_base=%u previous_water_base=%u previous_generated_base=%u mask=288 mode=0 water_y=%.6f previous_water_y=%.6f water_spread=%.6f previous_water_spread=%.6f primary_hash=%016llx/%016llx source_rebase_slots=%u max_cur_error=%.8f max_prev_error=%.8f max_prev_slot_delta=%.8f closest_cw=%.6f\n",
                static_cast<unsigned long long>(submissionFrame),
                result.initialized ? "INIT" : "CONTINUE",
                waterBase, generatedBase,
                previousDenseAvailable ? previousWaterBase : UINT32_MAX,
                previousDenseAvailable ? previousGeneratedBase : UINT32_MAX,
                currentWaterDatum.height, previousWaterDatum.height,
                currentWaterDatum.spread, previousWaterDatum.spread,
                static_cast<unsigned long long>(stockHashBefore),
                static_cast<unsigned long long>(stockHashAfter),
                sourceRebaseSlots,
                maxCurrentFormulaError, maxPreviousFormulaError,
                maxPreviousSlotError,
                closestAreaToZero); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
        }
        return result;
    }

    template<typename Workloads, typename Mapping>
    static bool wr64MappedWaveAnnulusParticipates(const Workloads &workloads, uint32_t index, const Mapping &mapping) {
        return index < workloads.size() && (workloads[index].drawData.wr64WaveDistance.mode ||
            (mapping.mapped && mapping.prevWorkloadIndex < workloads.size() &&
                workloads[mapping.prevWorkloadIndex].drawData.wr64WaveDistance.mode));
    }

    template<typename Workloads, typename Mapping>
    static Wr64DenseAnnulusFinalizeResult finalizeWr64MappedWaveAnnulus(Workloads &workloads,
        uint32_t index, const Mapping &mapping) {
        if (!wr64MappedWaveAnnulusParticipates(workloads, index, mapping)) return {};
        auto &current = workloads[index];
        const auto *previous = mapping.mapped && mapping.prevWorkloadIndex < workloads.size()
            ? &workloads[mapping.prevWorkloadIndex] : nullptr;
        const auto &wave = current.drawData.wr64WaveDistance;
        const bool compatible = previous && wave.valid && previous->wr64RtCourse == current.wr64RtCourse &&
            previous->drawData.wr64WaveDistance.valid && wave.course == previous->drawData.wr64WaveDistance.course &&
            wave.camera == previous->drawData.wr64WaveDistance.camera &&
            wave.projection < mapping.viewProjections.size() && mapping.viewProjections[wave.projection].mapped &&
            mapping.viewProjections[wave.projection].prevTransformIndex == previous->drawData.wr64WaveDistance.projection;
        return finalizeWr64WaterDenseAnnulus(current.drawData,
            compatible ? previous->drawData : current.drawData, current.submissionFrame, compatible);
    }

    void GameFrame::match(RenderWorker *worker, WorkloadQueue &workloadQueue, const GameFrame &prevFrame, BufferUploader *velocityUploader, bool &velocityUploaderUsed, bool &tileInterpolationUsed, bool &lookAtInterpolationUsed) {
        tileInterpolationUsed = false;
        lookAtInterpolationUsed = false;
        matched = true;

        thread_local std::unordered_map<uint32_t, ModifiedBuffers> workloadsModified;
        workloadsModified.clear();

        for (uint32_t w = 0; w < workloads.size(); w++) {
            if (w >= prevFrame.workloads.size()) {
                continue;
            }

            // We assume the workloads will be detected in the same order between frames.
            GameFrameMap::WorkloadMap &workloadMap = frameMap.workloads[workloads[w]];
            workloadMap.prevWorkloadIndex = prevFrame.workloads[w];
            workloadMap.mapped = true;

            Workload &curWorkload = workloadQueue.workloads[workloads[w]];
            const Workload &prevWorkload = workloadQueue.workloads[workloadMap.prevWorkloadIndex];
            workloadMap.viewProjections.clear();
            workloadMap.viewProjections.resize(curWorkload.drawData.viewProjTransforms.size());
            workloadMap.transforms.clear();
            workloadMap.transforms.resize(curWorkload.drawData.worldTransforms.size());
            workloadMap.tiles.clear();
            workloadMap.tiles.resize(curWorkload.drawData.rdpTiles.size());
            workloadMap.lookAt.clear();
            workloadMap.lookAt.resize(curWorkload.drawData.rspLookAt.size());
            workloadMap.prevTransformsMapped.clear();
            workloadMap.prevTransformsMapped.resize(prevWorkload.drawData.worldTransforms.size());
            workloadMap.prevTilesMapped.clear();
            workloadMap.prevTilesMapped.resize(prevWorkload.drawData.rdpTiles.size());
            workloadMap.prevLookAtMapped.clear();
            workloadMap.prevLookAtMapped.resize(prevWorkload.drawData.rspLookAt.size());

            if (wr64GantryIdentityEnabled()) {
                wr64GantryStampTransformIdentity(curWorkload);
            }

            // Same window as the gantry: the draws exist so minWorldMatrix is
            // filled, and the id map has not been built yet, so a stamp landing
            // here is the one buildTransformIdMap sees. The two passes claim
            // disjoint draws - the gantry's render state and the school's do not
            // overlap - so their order between themselves does not matter.
            if (wr64FishSchoolEnabled()) {
                wr64FishStampTransformIdentity(curWorkload);
            }

            // Same window again: the draws exist so minWorldMatrix is filled, and
            // the id map has not been built yet. The three passes claim disjoint
            // draws - no texture appears in more than one table - so their order
            // between themselves does not matter.
            if (wr64SpriteFamilyEnabled()) {
                wr64SpriteFamilyStampTransformIdentity(curWorkload);
            }
            // The dolphins claim six textures that appear in no other table, so
            // this runs alongside the others rather than instead of them. It is
            // last only because it is newest.
            if (wr64DolphinIdentityEnabled()) {
                wr64DolphinStampTransformIdentity(curWorkload);
            }
            // Two more families on the same recipe. Both refuse any matrix address
            // that resolves to more than one transform in the frame, which is what
            // split screen produces - see the rule inside each pass.
            if (wr64DrakeSchoolEnabled()) {
                wr64DrakeSchoolStampTransformIdentity(curWorkload);
            }
            if (wr64WhaleIdentityEnabled()) {
                wr64WhaleStampTransformIdentity(curWorkload);
            }
            // The ducks. Same refusal of a doubled address, plus the whole-block
            // discontinuity that keeps a re-slotting duck from coming apart.
            if (wr64DuckIdentityEnabled()) {
                wr64DuckStampTransformIdentity(curWorkload);
            }
            // The course buoys. The same block as the ducks: id from the
            // matrix address, ordering LINEAR, every component forced, and a
            // continuity guard because the segment-5 slot is recycled between
            // buoys. R4 set only vertexInterpolation and it was not enough.
            if (wr64BuoyVertexLerpEnabled()) {
                wr64BuoyStampTransformIdentity(curWorkload);
            }
            // The area limitation buoys and the Stunt Mode rings: the same
            // stamp block again, with the id minted from the POSITION - the
            // one property their shuffling segment-5 count-stack slots
            // preserve. Claims are disjoint from every pass above (three
            // texture hashes, none in any other table).
            if (wr64AreaBuoyLerpEnabled()) {
                wr64AreaBuoyStampTransformIdentity(curWorkload);
            }
            if (wr64StuntRingLerpEnabled()) {
                wr64StuntRingStampTransformIdentity(curWorkload);
            }
            else {
                curWorkload.wr64StuntRingTilePairs.clear();
            }
            // The celestial bodies. NOT a stamp pass - it pairs the sun's
            // screen rects with their previous-frame selves so the transform
            // processor can blend them per output frame. Clears its own state,
            // so the disabled branch must clear too or a stale pairing from
            // the frame before the A/B flip would keep applying.
            if (wr64CelestialRectLerpEnabled()) {
                wr64CelestialPairRects(curWorkload, prevWorkload);
            }
            else {
                curWorkload.wr64CelestialPrevRects.clear();
                curWorkload.wr64CelestialTilePairs.clear();
            }
            wr64HudPairRects(curWorkload, prevWorkload);
            wr64DolphinSunPairRects(curWorkload, prevWorkload);

            // IDENTITY-CARRIED TILE PAIRS, registered with the engine's
            // per-output-frame tile blend (TileProcessor reads
            // workloadMap.tiles). Two producers feed this, both pairing a
            // draw's tiles with its own previous-frame self by an identity
            // the scene-based call matcher does not need:
            //
            //   celestial rects   rect draws never reach the transform
            //                     matcher, so nothing else ever maps their
            //                     tiles. (Measured 2026-08-05: the DP text's
            //                     scroll is NOT in the tile - it is folded
            //                     into the rect blend from the per-vertex
            //                     UVs - so these pairs currently blend
            //                     values that are already equal; they stay
            //                     as the guard for a claimed rect that DOES
            //                     scroll its tile.)
            //   stunt rings       the spin's texture animation. The rings'
            //                     transforms interpolate on every course
            //                     (measured), so the id-carried tile pair is
            //                     the channel that makes the visible spin
            //                     course-independent instead of hostage to
            //                     scene matching.
            //
            // Registered DIRECTLY with the previous frame's own values - no
            // wrap heuristics: both producers pair a draw to ITSELF, so prev
            // really is prev. Structurally different tiles are refused the
            // same way the transform tile matcher refuses them.
            thread_local std::vector<Workload::Wr64CelestialTilePair> wr64IdTilePairs;
            wr64IdTilePairs.clear();
            wr64IdTilePairs.insert(wr64IdTilePairs.end(),
                curWorkload.wr64CelestialTilePairs.begin(), curWorkload.wr64CelestialTilePairs.end());
            const size_t wr64CelestialTilePairCount = wr64IdTilePairs.size();
            wr64IdTilePairs.insert(wr64IdTilePairs.end(),
                curWorkload.wr64StuntRingTilePairs.begin(), curWorkload.wr64StuntRingTilePairs.end());
            for (size_t wr64TpIndex = 0; wr64TpIndex < wr64IdTilePairs.size(); wr64TpIndex++) {
                    const Workload::Wr64CelestialTilePair &wr64CelTp = wr64IdTilePairs[wr64TpIndex];
                    if ((wr64CelTp.curTileIndex >= curWorkload.drawData.rdpTiles.size()) ||
                        (wr64CelTp.prevTileIndex >= prevWorkload.drawData.rdpTiles.size()) ||
                        (wr64CelTp.curTileIndex >= workloadMap.tiles.size()) ||
                        (wr64CelTp.prevTileIndex >= workloadMap.prevTilesMapped.size()))
                    {
                        continue;
                    }

                    GameFrameMap::TileMap &wr64CelTileMap = workloadMap.tiles[wr64CelTp.curTileIndex];
                    if (wr64CelTileMap.mapped) {
                        continue;
                    }

                    const interop::RDPTile &wr64CelCurTile =
                        curWorkload.drawData.rdpTiles[wr64CelTp.curTileIndex];
                    const interop::RDPTile &wr64CelPrevTile =
                        prevWorkload.drawData.rdpTiles[wr64CelTp.prevTileIndex];
                    if ((wr64CelCurTile.fmt != wr64CelPrevTile.fmt) ||
                        (wr64CelCurTile.siz != wr64CelPrevTile.siz) ||
                        (wr64CelCurTile.stride != wr64CelPrevTile.stride) ||
                        (wr64CelCurTile.masks != wr64CelPrevTile.masks) ||
                        (wr64CelCurTile.maskt != wr64CelPrevTile.maskt) ||
                        (wr64CelCurTile.shifts != wr64CelPrevTile.shifts) ||
                        (wr64CelCurTile.shiftt != wr64CelPrevTile.shiftt) ||
                        (wr64CelCurTile.cms != wr64CelPrevTile.cms) ||
                        (wr64CelCurTile.cmt != wr64CelPrevTile.cmt))
                    {
                        continue;
                    }

                    wr64CelTileMap.prevUls = wr64CelPrevTile.uls;
                    wr64CelTileMap.prevUlt = wr64CelPrevTile.ult;
                    wr64CelTileMap.prevLrs = wr64CelPrevTile.lrs;
                    wr64CelTileMap.prevLrt = wr64CelPrevTile.lrt;
                    wr64CelTileMap.deltaUls = wr64CelCurTile.uls - wr64CelPrevTile.uls;
                    wr64CelTileMap.deltaUlt = wr64CelCurTile.ult - wr64CelPrevTile.ult;
                    wr64CelTileMap.deltaLrs = wr64CelCurTile.lrs - wr64CelPrevTile.lrs;
                    wr64CelTileMap.deltaLrt = wr64CelCurTile.lrt - wr64CelPrevTile.lrt;
                    wr64CelTileMap.mapped = true;
                    workloadMap.prevTilesMapped[wr64CelTp.prevTileIndex] = true;

                    const bool wr64CelTileMoved =
                        (wr64CelTileMap.deltaUls != 0.0f) || (wr64CelTileMap.deltaUlt != 0.0f) ||
                        (wr64CelTileMap.deltaLrs != 0.0f) || (wr64CelTileMap.deltaLrt != 0.0f);
                    tileInterpolationUsed = tileInterpolationUsed || wr64CelTileMoved;
                    // The celestial note belongs to the celestial pairs only;
                    // the rings announce their own pairing in the stamp pass.
                    if (wr64CelTileMoved && (wr64TpIndex < wr64CelestialTilePairCount)) {
                        wr64CelestialTileNote();
                    }
            }

            // R4: the seagull pass may have appended GHOST transforms, and the
            // per-transform map was sized before the stamps ran. resize keeps
            // every entry already constructed and default-constructs the new
            // tail (mapped = false) - exactly a ghost's starting state.
            workloadMap.transforms.resize(curWorkload.drawData.worldTransforms.size());

            buildTransformIdMap(curWorkload, curWorkload.transformIdMap, curWorkload.transformIgnoredIds);

            // Retrieve the matching maps for the current and previous workload.
            GameFrameMap::WorkloadMap &curWorkloadMap = frameMap.workloads[workloads[w]];
            const GameFrameMap::WorkloadMap *prevWorkloadMap = nullptr;
            if (prevFrame.matched && prevFrame.frameMap.workloads[workloadMap.prevWorkloadIndex].mapped) {
                prevWorkloadMap = &prevFrame.frameMap.workloads[workloadMap.prevWorkloadIndex];
            }

            // Match the transforms linearly in the order they were submitted.
            ModifiedBuffers modifiedBuffers;
            auto curIt = curWorkload.transformIdMap.begin();
            auto prevIt = prevWorkload.transformIdMap.begin();
            bool modifiedVelocityBuffer = false;
            while ((curIt != curWorkload.transformIdMap.end()) && (prevIt != prevWorkload.transformIdMap.end())) {
                if (curIt->first < prevIt->first) {
                    curIt++;
                }
                else if (curIt->first > prevIt->first) {
                    prevIt++;
                }
                else {
                    matchTransform(curWorkload, prevWorkload, curWorkloadMap, prevWorkloadMap, curIt->second, prevIt->second, modifiedBuffers, false, false, nullptr, nullptr);
                    curIt++;
                    prevIt++;
                }
            }

            // Ground truth on whether identity matching actually paired the assembly.
            // Dormant unless WR64_GANTRY_MATCH_TRACE names a file.
            if (wr64GantryIdentityEnabled() && wr64GantryMatchTraceArmed()) {
                uint32_t wr64GantryClaimedCount = 0;
                for (uint32_t t = 0; t < curWorkload.drawData.worldTransformGroups.size(); t++) {
                    const uint32_t wr64GantryGroupIndex = curWorkload.drawData.worldTransformGroups[t];
                    if (wr64GantryGroupIndex >= curWorkload.drawData.transformGroups.size()) {
                        continue;
                    }
                    if (wr64GantryIdentityIsOurs(curWorkload.drawData.transformGroups[wr64GantryGroupIndex].matrixId)) {
                        wr64GantryClaimedCount++;
                    }
                }

                for (uint32_t t = 0; t < curWorkload.drawData.worldTransformGroups.size(); t++) {
                    const uint32_t wr64GantryGroupIndex = curWorkload.drawData.worldTransformGroups[t];
                    if (wr64GantryGroupIndex >= curWorkload.drawData.transformGroups.size()) {
                        continue;
                    }

                    const uint32_t wr64GantryId =
                        curWorkload.drawData.transformGroups[wr64GantryGroupIndex].matrixId;
                    if (!wr64GantryIdentityIsOurs(wr64GantryId)) {
                        continue;
                    }

                    wr64GantryMatchRecord(wr64GantryId, wr64GantryClaimedCount,
                        curWorkload.transformIdMap.find(wr64GantryId) != curWorkload.transformIdMap.end(),
                        prevWorkload.transformIdMap.find(wr64GantryId) != prevWorkload.transformIdMap.end(),
                        curWorkloadMap.transforms[t].mapped);
                }
            }

            if (!modifiedBuffers.empty()) {
                workloadsModified[workloads[w]].merge(modifiedBuffers);
            }

            // Any transforms tagged with the empty ID will be instantly marked as used and skipped.
            for (uint32_t curIt : curWorkload.transformIgnoredIds) {
                GameFrameMap::TransformMap &curTransformMap = curWorkloadMap.transforms[curIt];
                curTransformMap.rigidBody = RigidBody();
                curTransformMap.prevTransformIndex = 0;
                curTransformMap.mapped = false;
            }
        }

        thread_local std::vector<MatchCandidate> matchCandidates;
        thread_local std::vector<bool> curScenesMatched;
        thread_local std::vector<bool> prevScenesMatched;
        auto matchScenes = [&](const std::vector<GameScene> &curScenes, const std::vector<GameScene> &prevScenes, uint32_t sceneKind) {
            // Find the scenes that are the closest match possible.
            //
            // VIEWPORT-PAIR-R1. The score below measures only how alike two cameras
            // are. In split screen that cannot tell the two viewports apart: the two
            // players are closer to each other than either camera is to its own
            // previous frame, so the cross terms beat the identity terms and the
            // greedy assignment hands each viewport the other one's history. The
            // scissor rect is what actually identifies a viewport and the game keeps
            // it stable, so it is collected here and preferred in the first pass.
            const bool viewportFirst = wr64ViewportPairFixEnabled();
            const bool traceArmed = wr64ViewportPairArmed();
            const uint32_t curSceneCount = uint32_t(curScenes.size());
            const uint32_t prevSceneCount = uint32_t(prevScenes.size());
            matchCandidates.clear();
            // [WR64] R2: A SCENE'S RECT IS THE MERGE OF ALL ITS PROJECTIONS.
            //
            // This used to read projections[0].scissorRect. A scene's position in
            // that vector is WALK ORDER, not viewport identity, so projections[0]
            // is whichever projection happened to be visited first - and if that
            // one never received a scissored draw its rect is the empty inverted
            // rect while a sibling projection in the same scene carries the real
            // one. Merging every projection gives the scene the rect it actually
            // occupies, which is the thing R1 wanted to compare in the first
            // place. Empty projections contribute nothing to a merge, so this
            // costs nothing where the old code was already right.
            auto wr64SceneRect = [&](const GameScene &scene) {
                FixedRect merged;
                for (const GameIndices::Projection &p : scene.projections) {
                    const Workload &w = workloadQueue.workloads[p.workloadIndex];
                    const Projection &pr = w.fbPairs[p.fbPairIndex].projections[p.projectionIndex];
                    if (!pr.scissorRect.isNull() && !pr.scissorRect.isEmpty()) {
                        merged.merge(pr.scissorRect);
                    }
                }
                return merged;
            };

            for (uint32_t i = 0; i < curScenes.size(); i++) {
                const GameIndices::Projection curFirstProj = curScenes[i].projections[0];
                const Workload &curWorkload = workloadQueue.workloads[curFirstProj.workloadIndex];
                const FramebufferPair &curFbPair = curWorkload.fbPairs[curFirstProj.fbPairIndex];
                const Projection &curProj = curFbPair.projections[curFirstProj.projectionIndex];
                const FixedRect curSceneRect = wr64SceneRect(curScenes[i]);
                const hlslpp::float4x4 &curViewTransform = curWorkload.drawData.viewTransforms[curProj.transformsIndex];
                const hlslpp::float4x4 &curProjTransform = curWorkload.drawData.projTransforms[curProj.transformsIndex];
                for (uint32_t j = 0; j < prevScenes.size(); j++) {
                    const GameIndices::Projection prevFirstProj = prevScenes[j].projections[0];
                    const Workload &prevWorkload = workloadQueue.workloads[prevFirstProj.workloadIndex];
                    const FramebufferPair &prevFbPair = prevWorkload.fbPairs[prevFirstProj.fbPairIndex];
                    const Projection &prevProj = prevFbPair.projections[prevFirstProj.projectionIndex];
                    const hlslpp::float4x4 &prevViewTransform = prevWorkload.drawData.viewTransforms[prevProj.transformsIndex];
                    const hlslpp::float4x4 &prevProjTransform = prevWorkload.drawData.projTransforms[prevProj.transformsIndex];
                    const float viewDiff = matrixDifference(curViewTransform, prevViewTransform);
                    const float projDiff = matrixDifference(curProjTransform, prevProjTransform);
                    const FixedRect prevSceneRect = wr64SceneRect(prevScenes[j]);
                    const bool sameViewport = wr64ViewportRectsEqual(curSceneRect, prevSceneRect);
                    matchCandidates.emplace_back(i, j, viewDiff + projDiff, sameViewport);

                    if (traceArmed) {
                        wr64ViewportPairRecord("cand", curWorkload.submissionFrame, sceneKind,
                            curSceneCount, prevSceneCount, i, j,
                            curProj.scissorRect, prevProj.scissorRect,
                            viewDiff, projDiff, sameViewport, 0);
                    }
                }
            }

            curScenesMatched.clear();
            prevScenesMatched.clear();
            curScenesMatched.resize(curScenes.size());
            prevScenesMatched.resize(prevScenes.size());
            std::stable_sort(matchCandidates.begin(), matchCandidates.end());

            auto assignScene = [&](const MatchCandidate &candidate, uint32_t pass) {
                if (traceArmed) {
                    const GameIndices::Projection curFirst = curScenes[candidate.curIndex].projections[0];
                    const Workload &curW = workloadQueue.workloads[curFirst.workloadIndex];
                    const Projection &curP = curW.fbPairs[curFirst.fbPairIndex].projections[curFirst.projectionIndex];
                    const GameIndices::Projection prevFirst = prevScenes[candidate.prevIndex].projections[0];
                    const Workload &prevW = workloadQueue.workloads[prevFirst.workloadIndex];
                    const Projection &prevP = prevW.fbPairs[prevFirst.fbPairIndex].projections[prevFirst.projectionIndex];
                    wr64ViewportPairRecord("pair", curW.submissionFrame, sceneKind,
                        curSceneCount, prevSceneCount, candidate.curIndex, candidate.prevIndex,
                        curP.scissorRect, prevP.scissorRect,
                        candidate.difference, 0.0f, candidate.sameViewport, pass);
                }

                matchScene(workloadQueue, prevFrame, curScenes[candidate.curIndex], prevScenes[candidate.prevIndex], workloadsModified, tileInterpolationUsed, lookAtInterpolationUsed);
                curScenesMatched[candidate.curIndex] = true;
                prevScenesMatched[candidate.prevIndex] = true;
            };

            // Pass 1: a viewport continues from the same viewport.
            for (const MatchCandidate &candidate : matchCandidates) {
                if (viewportFirst && !candidate.sameViewport) {
                    continue;
                }

                if (curScenesMatched[candidate.curIndex] || prevScenesMatched[candidate.prevIndex]) {
                    continue;
                }

                assignScene(candidate, 1);
            }

            // Pass 2: anything the first pass could not place falls back to the
            // original nearest-camera rule, so this can never match less than it did
            // before the change. With the fix off, pass 1 has already taken
            // everything and this finds nothing.
            for (const MatchCandidate &candidate : matchCandidates) {
                if (curScenesMatched[candidate.curIndex] || prevScenesMatched[candidate.prevIndex]) {
                    continue;
                }

                assignScene(candidate, 2);
            }

            if (traceArmed) {
                for (uint32_t i = 0; i < curSceneCount; i++) {
                    if (curScenesMatched[i]) {
                        continue;
                    }

                    const GameIndices::Projection curFirst = curScenes[i].projections[0];
                    const Workload &curW = workloadQueue.workloads[curFirst.workloadIndex];
                    const Projection &curP = curW.fbPairs[curFirst.fbPairIndex].projections[curFirst.projectionIndex];
                    wr64ViewportPairRecord("miss", curW.submissionFrame, sceneKind,
                        curSceneCount, prevSceneCount, i, UINT32_MAX,
                        curP.scissorRect, FixedRect(), 0.0f, 0.0f, false, 0);
                }
            }
        };

        // Coverage topology must exist before call hashes are paired. Mutating
        // triangle counts after matching makes this frame's stored workload
        // disagree with the next native frame and silently kills interpolation.
        const float splitRoundnessStrength = getWr64WaterLaplacianStrength();
        bool nativeFarWaterScope = false;
        for (uint32_t index : workloads) if (index < workloadQueue.workloads.size()) {
            const auto &scope = workloadQueue.workloads[index].wr64FarWaterDistanceViewScope;
            nativeFarWaterScope = nativeFarWaterScope || scope[0] || scope[1];
        }
        if (nativeFarWaterScope || splitRoundnessStrength > 0.0f || wr64WaterDenseAnnulusEnabled() ||
            wr64WaterCoverageRingEnabled() || wr64WaterTrailingPatchEnabled() ||
            wr64WaterBridgeStitchEnabled() || wr64WaterSuppressBridgeEnabled() ||
            wr64WaterBoundarySkirtEnabled()) {
            std::set<uint64_t> visitedProjections;
            std::set<uint64_t> roundedSplitViews;
            const auto augmentScenes = [&](const std::vector<GameScene> &scenes) {
                for (const GameScene &scene : scenes) {
                    for (const GameIndices::Projection &indices : scene.projections) {
                        const uint64_t key =
                            (uint64_t(indices.workloadIndex) << 32) |
                            (uint64_t(indices.fbPairIndex & 0xFFFFU) << 16) |
                            uint64_t(indices.projectionIndex & 0xFFFFU);
                        if (!visitedProjections.emplace(key).second ||
                            (indices.workloadIndex >= workloadQueue.workloads.size()))
                        {
                            continue;
                        }

                        Workload &waterWorkload =
                            workloadQueue.workloads[indices.workloadIndex];
                        if ((indices.fbPairIndex >= waterWorkload.fbPairs.size()) ||
                            (indices.projectionIndex >=
                                waterWorkload.fbPairs[indices.fbPairIndex].projections.size()))
                        {
                            continue;
                        }

                        Projection &waterProjection = waterWorkload
                            .fbPairs[indices.fbPairIndex].projections[indices.projectionIndex];
                        const uint32_t originalCallCount = waterProjection.gameCallCount;
                        for (uint32_t callIndex = 0; callIndex < originalCallCount; callIndex++) {
                            if (!isWr64GeneratedWaterProvenanceCall(
                                waterWorkload.drawData,
                                waterProjection.gameCalls[callIndex]))
                            {
                                continue;
                            }

                            Wr64NativeWaveDistanceView nativeWavePlan;
                            uint32_t nativeWaveFarMode = 0;
                            // The native smaller/larger sheets keep their original
                            // six-vertex flat fan. Expand that fan per source view;
                            // wave vertices, topology, materials and UVs stay native.
                            if (waterProjection.transformsIndex < waterWorkload.drawData.rspViewports.size()) {
                                const auto &vp = waterWorkload.drawData.rspViewports[waterProjection.transformsIndex];
                                const auto &waterCall = waterProjection.gameCalls[callIndex];
                                const auto &scissor = waterCall.callDesc.scissorRect;
                                WR64RTViewDomain domain;
                                domain.perspective = waterProjection.type == Projection::Type::Perspective;
                                domain.menuModelPreview = waterProjection.wr64MenuModelPreview;
                                domain.menuWaterPreview = waterProjection.wr64MenuWaterPreview;
                                domain.scale[0] = vp.scale.x; domain.scale[1] = vp.scale.y; domain.scale[2] = vp.scale.z;
                                domain.translate[0] = vp.translate.x; domain.translate[1] = vp.translate.y; domain.translate[2] = vp.translate.z;
                                domain.scissor[0] = scissor.ulx; domain.scissor[1] = scissor.uly;
                                domain.scissor[2] = scissor.lrx; domain.scissor[3] = scissor.lry;
                                const int32_t sourceOwner = wr64FarWaterSourceOwner(domain);
                                const uint32_t owner = sourceOwner < 0 ? 0U : uint32_t(sourceOwner);
                                const uint32_t view = owner ? owner - 1 : 0;
                                if (sourceOwner >= 0 && waterWorkload.wr64FarWaterDistanceViewScope[view] &&
                                    wr64ExtendNativeWaterFan(waterWorkload.drawData, waterCall.meshDesc.faceIndicesStart,
                                        waterCall.callDesc.triangleCount, waterProjection.transformsIndex, owner,
                                        waterWorkload.wr64FarWaterDistanceViewModes[view], waterWorkload.wr64FarWaterDistanceCameras[view])) {
                                    if (waterWorkload.wr64FarWaterDistanceViewModes[view])
                                        workloadsModified[indices.workloadIndex].position = true;
                                }
                                // Plan against the exact producer before Roundness
                                // changes interior heights. Each split view carries
                                // its own task-sealed snapshot and face metadata.
                                if (sourceOwner >= 0 && (owner || waterCall.callDesc.triangleCount != 876U)) {
                                    nativeWaveFarMode = waterWorkload.wr64FarWaterDistanceViewModes[view];
                                    nativeWavePlan = wr64PlanNativeWaveDistance(waterWorkload.drawData,
                                        waterWorkload.wr64WaveDistanceSnapshots[view], waterCall.meshDesc.faceIndicesStart,
                                        waterCall.callDesc.triangleCount, waterProjection.transformsIndex, owner);
                                }
                            }
                            const auto commitNativeWave = [&]() {
                                if (!nativeWavePlan.valid) return false;
                                auto &call = waterProjection.gameCalls[callIndex];
                                if (!wr64CommitNativeWaveDistance(waterWorkload.drawData, std::move(nativeWavePlan), nativeWaveFarMode,
                                        call.meshDesc.faceIndicesStart, call.callDesc.triangleCount)) return false;
                                const auto &views = waterWorkload.drawData.wr64NativeWaveDistance;
                                for (const auto &view : views) if (view.valid && view.mode) {
                                    workloadsModified[indices.workloadIndex].position = true;
                                    workloadsModified[indices.workloadIndex].positionVelocity = true;
                                    workloadsModified[indices.workloadIndex].texcoordVelocity = true;
                                    workloadsModified[indices.workloadIndex].wr64WaterField = true;
                                }
                                return true;
                            };

                            // Round the smaller native split-screen sheets
                            // independently of the one-player annulus. Source
                            // viewport ownership also works with Original
                            // assets and before vertical output remapping.
                            if (wr64SplitWaterRoundnessMatching(
                                    waterWorkload.wr64SplitWaterRoundnessScope, splitRoundnessStrength) &&
                                waterProjection.transformsIndex < waterWorkload.drawData.rspViewports.size()) {
                                const auto &vp = waterWorkload.drawData.rspViewports[waterProjection.transformsIndex];
                                const auto &scissor = waterProjection.gameCalls[callIndex].callDesc.scissorRect;
                                WR64RTViewDomain domain;
                                domain.perspective = waterProjection.type == Projection::Type::Perspective;
                                domain.menuModelPreview = waterProjection.wr64MenuModelPreview;
                                domain.menuWaterPreview = waterProjection.wr64MenuWaterPreview;
                                domain.scale[0] = vp.scale.x; domain.scale[1] = vp.scale.y; domain.scale[2] = vp.scale.z;
                                domain.translate[0] = vp.translate.x; domain.translate[1] = vp.translate.y; domain.translate[2] = vp.translate.z;
                                domain.scissor[0] = scissor.ulx; domain.scissor[1] = scissor.uly;
                                domain.scissor[2] = scissor.lrx; domain.scissor[3] = scissor.lry;
                                const uint32_t owner = wr64RTNativeRaceView(domain);
                                const uint64_t ownerKey = (uint64_t(indices.workloadIndex) << 32) | owner;
                                if (owner && !roundedSplitViews.count(ownerKey)) {
                                    const auto &waterCall = waterProjection.gameCalls[callIndex];
                                    const auto rounded = wr64RoundNativeSplitWater(waterWorkload.drawData,
                                        waterCall.meshDesc.faceIndicesStart, waterCall.callDesc.triangleCount,
                                        waterProjection.transformsIndex, owner, splitRoundnessStrength);
                                    if (rounded.applied) {
                                        roundedSplitViews.insert(ownerKey);
                                        workloadsModified[indices.workloadIndex].position = true;
                                        static float reportedStrength[2] = {-1.0f, -1.0f};
                                        if (reportedStrength[owner-1] != splitRoundnessStrength) {
                                            reportedStrength[owner-1] = splitRoundnessStrength;
                                            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[water-laplacian] native_view=%u strength=%.3f logical=%u boundary=%u changed=%u topology_unchanged=1\n",
                                                owner, splitRoundnessStrength, rounded.logicalVertices, rounded.boundaryVertices, rounded.changedVertices); }
                                            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
                                        }
                                        commitNativeWave();
                                        continue;
                                    }
                                }
                            }

                            if (commitNativeWave()) continue;

                            // Dense-annulus mode is deliberately exclusive. It
                            // replaces the stock fan and must never retain the
                            // old trailing strip or any other coverage probe.
                            bool augmented = false;
                            if (wr64WaterDenseAnnulusEnabled()) {
                                const Wr64DenseWaterCallResult denseResult =
                                    tryAugmentWr64WaterDenseAnnulus(
                                    waterWorkload, waterProjection, callIndex);
                                if (denseResult ==
                                    Wr64DenseWaterCallResult::NotApplicable)
                                {
                                    // A broad provenance match can precede
                                    // the exact generated sheet. Keep scanning
                                    // this projection rather than suppressing
                                    // or mutating the unrelated call.
                                    continue;
                                }
                                if (denseResult == Wr64DenseWaterCallResult::NativeRetained) {
                                    // The shape matched, but the decoded native
                                    // payload could not prove safe augmentation.
                                    // No mutations were committed: preserve the
                                    // native sheet, then retry normally next frame.
                                    continue;
                                }
                                augmented = true;
                            }
                            else if (wr64WaterBoundarySkirtEnabled()) {
                                augmented = augmentWr64WaterBoundarySkirt(
                                    waterWorkload, waterProjection, callIndex);
                            }
                            else if (wr64WaterSuppressBridgeEnabled()) {
                                augmented = suppressWr64WaterBridge(
                                    waterWorkload, waterProjection, callIndex);
                            }
                            else if (wr64WaterBridgeStitchEnabled()) {
                                augmented = augmentWr64WaterBridgeStitch(
                                    waterWorkload, waterProjection, callIndex);
                            }
                            else if (wr64WaterTrailingPatchEnabled()) {
                                augmented = augmentWr64WaterTrailingPatch(
                                    waterWorkload, waterProjection, callIndex);
                            }
                            else {
                                augmented = augmentWr64WaterCoverageRing(
                                    waterWorkload, waterProjection, callIndex);
                            }
                            if (augmented)
                            {
                                workloadsModified[indices.workloadIndex]
                                    .wr64WaterCoverage = true;
                            }
                            break;
                        }
                    }
                }
            };
            augmentScenes(perspectiveScenes);
            augmentScenes(orthographicScenes);
        }

        // Diagnostic-only: arm the whole-frame provenance census once per native
        // frame so that it spans every matched scene, perspective and
        // orthographic alike, instead of only the first scene to be matched.
        wr64WaterCensusActive() = wr64WaterCensusTriggerConsumed();
        wr64WaterCensusRowCount() = 0;
        wr64WaterCensusSceneOrdinal() = 0;

        wr64WaterCensusSceneKind() = 0;
        matchScenes(perspectiveScenes, prevFrame.perspectiveScenes, 0);
        wr64WaterCensusSceneKind() = 1;
        matchScenes(orthographicScenes, prevFrame.orthographicScenes, 1);

        if (wr64WaterCensusActive()) {
            wr64CloseWaterCensusFile();
            wr64WaterCensusActive() = false;
        }

        for (uint32_t index : workloads) {
            if (index < frameMap.workloads.size() && wr64FinalizeMappedWaveDistance(
                    workloadQueue.workloads, index, frameMap.workloads[index])) {
                workloadsModified[index].positionVelocity = true;
                workloadsModified[index].wr64WaterField = true;
            }
            if (index < frameMap.workloads.size() && wr64FinalizeMappedNativeWaterDistance(
                    workloadQueue.workloads, index, frameMap.workloads[index])) {
                workloadsModified[index].positionVelocity = true;
            }
            if (index < frameMap.workloads.size() && wr64FinalizeMappedNativeWaveDistance(
                    workloadQueue.workloads, index, frameMap.workloads[index])) {
                workloadsModified[index].positionVelocity = true;
                workloadsModified[index].texcoordVelocity = true;
                workloadsModified[index].wr64WaterField = true;
            }
        }

        // Finalize every participating wave workload through its actual map,
        // including current workloads beyond the previous frame's count.
        for (uint32_t index : workloads) {
            if (index >= frameMap.workloads.size()) continue;
            const auto result = finalizeWr64MappedWaveAnnulus(workloadQueue.workloads, index, frameMap.workloads[index]);
            if (result.attempted && result.passed) {
                workloadsModified[index].positionVelocity = true;
                workloadsModified[index].texcoordVelocity = true;
            }
        }

        for (uint32_t w = 0; (w < workloads.size()) && (w < prevFrame.workloads.size()); w++) {
            Workload &curWorkload = workloadQueue.workloads[workloads[w]];
            const Workload &prevWorkload = workloadQueue.workloads[prevFrame.workloads[w]];
            const GameFrameMap::WorkloadMap &curWorkloadMap = frameMap.workloads[workloads[w]];
            if (interpolateWr64Spray(curWorkload, prevWorkload, curWorkloadMap)) {
                workloadsModified[workloads[w]].positionVelocity = true;
            }

            if (!wr64MappedWaveAnnulusParticipates(workloadQueue.workloads, workloads[w], curWorkloadMap)) {
                const Wr64DenseAnnulusFinalizeResult denseFinalize =
                    finalizeWr64WaterDenseAnnulus(curWorkload.drawData,
                        prevWorkload.drawData, curWorkload.submissionFrame);
                if (denseFinalize.attempted && denseFinalize.passed) {
                    workloadsModified[workloads[w]].positionVelocity = true;
                    workloadsModified[workloads[w]].texcoordVelocity = true;
                }
            }

            // Coverage vertices are generated before matching with stable slot
            // ordering in both workloads. Give every one its exact native
            // endpoint delta after the ordinary water pass has finished. This
            // is independently traceable and cannot freeze when the camera
            // moves, unlike producerless vertices left at zero velocity.
            DrawData &curDraw = curWorkload.drawData;
            const DrawData &prevDraw = prevWorkload.drawData;
            if ((curDraw.wr64WaterVertexMask.size() == curDraw.vertexCount()) &&
                (prevDraw.wr64WaterVertexMask.size() == prevDraw.vertexCount()) &&
                (curDraw.vertexCount() == prevDraw.vertexCount()))
            {
                bool coverageVelocityWritten = false;
                for (uint32_t vertex = 0; vertex < curDraw.vertexCount(); vertex++) {
                    if ((curDraw.wr64WaterVertexMask[vertex] != 2) ||
                        (prevDraw.wr64WaterVertexMask[vertex] != 2))
                    {
                        continue;
                    }
                    for (uint32_t component = 0; component < 3; component++) {
                        curDraw.velFloats[vertex * 3 + component] =
                            curDraw.posFloats[vertex * 3 + component] -
                            prevDraw.posFloats[vertex * 3 + component];
                    }
                    for (uint32_t component = 0; component < 2; component++) {
                        float delta = curDraw.tcFloats[vertex * 2 + component] -
                            prevDraw.tcFloats[vertex * 2 + component];
                        constexpr float TexcoordPeriod = 8192.0f;
                        if (delta > (TexcoordPeriod * 0.5f)) {
                            delta -= TexcoordPeriod;
                        }
                        else if (delta < (-TexcoordPeriod * 0.5f)) {
                            delta += TexcoordPeriod;
                        }
                        curDraw.tcVelFloats[vertex * 2 + component] = delta;
                    }
                    coverageVelocityWritten = true;
                }
                if (coverageVelocityWritten) {
                    workloadsModified[workloads[w]].positionVelocity = true;
                    workloadsModified[workloads[w]].texcoordVelocity = true;
                }
            }
        }

        // The split-screen course IDs can match even when one scene does not.
        // Apply the established sky UV rebase correction after every velocity
        // writer, so it also covers that view before the buffers are uploaded.
        for (const uint32_t workloadIndex : workloads) {
            ModifiedBuffers skyModified;
            wr64SkyTexcoordFixSplitWorkload(workloadQueue, workloadIndex, skyModified);
            if (!skyModified.empty()) workloadsModified[workloadIndex].merge(skyModified);
        }

        // Extend the final native sky position/UV velocities with exactly the
        // affine weights used to construct its optional annulus. Running last
        // includes the existing rebase repair and does not pair synthetic slots.
        for (const uint32_t workloadIndex : workloads) {
            if (wr64FinalizeCloudCoverage(workloadQueue.workloads[workloadIndex])) {
                workloadsModified[workloadIndex].positionVelocity = true;
                workloadsModified[workloadIndex].texcoordVelocity = true;
            }
        }

        if (!workloadsModified.empty()) {
            thread_local std::vector<BufferUploader::Upload> uploads;
            uploads.clear();

            for (auto &it : workloadsModified) {
                Workload &workload = workloadQueue.workloads[it.first];
                if (it.second.wr64WaterCoverage) {
                    const RenderBufferFlags rtInputFlag =
                        (worker->device->getCapabilities().raytracing || worker->device->getCapabilities().rayQueries) ?
                        RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT :
                        RenderBufferFlag::NONE;
                    workload.updateOutputBuffers(worker);
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.posFloats.data(), { 0, workload.drawData.posFloats.size() }, sizeof(float), RenderBufferFlag::FORMATTED, { RenderFormat::R32_FLOAT }, &workload.drawBuffers.positionBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.velFloats.data(), { 0, workload.drawData.velFloats.size() }, sizeof(float), RenderBufferFlag::FORMATTED, { RenderFormat::R32_FLOAT }, &workload.drawBuffers.velocityBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.tcFloats.data(), { 0, workload.drawData.tcFloats.size() }, sizeof(float), RenderBufferFlag::FORMATTED, { RenderFormat::R32_FLOAT }, &workload.drawBuffers.texcoordBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.tcVelFloats.data(), { 0, workload.drawData.tcVelFloats.size() }, sizeof(float), RenderBufferFlag::FORMATTED, { RenderFormat::R32_FLOAT }, &workload.drawBuffers.texcoordVelocityBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.normColBytes.data(), { 0, workload.drawData.normColBytes.size() }, sizeof(uint8_t), RenderBufferFlag::FORMATTED | RenderBufferFlag::STORAGE, { RenderFormat::R8_UINT, RenderFormat::R8_SINT }, &workload.drawBuffers.normalColorBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.viewProjIndices.data(), { 0, workload.drawData.viewProjIndices.size() }, sizeof(uint16_t), RenderBufferFlag::FORMATTED | RenderBufferFlag::STORAGE, { RenderFormat::R16_UINT }, &workload.drawBuffers.viewProjIndicesBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.worldIndices.data(), { 0, workload.drawData.worldIndices.size() }, sizeof(uint16_t), RenderBufferFlag::FORMATTED | RenderBufferFlag::STORAGE, { RenderFormat::R16_UINT }, &workload.drawBuffers.worldIndicesBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.fogIndices.data(), { 0, workload.drawData.fogIndices.size() }, sizeof(uint16_t), RenderBufferFlag::FORMATTED | RenderBufferFlag::STORAGE, { RenderFormat::R16_UINT }, &workload.drawBuffers.fogIndicesBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.lightIndices.data(), { 0, workload.drawData.lightIndices.size() }, sizeof(uint16_t), RenderBufferFlag::FORMATTED | RenderBufferFlag::STORAGE, { RenderFormat::R16_UINT }, &workload.drawBuffers.lightIndicesBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.lightCounts.data(), { 0, workload.drawData.lightCounts.size() }, sizeof(uint8_t), RenderBufferFlag::FORMATTED | RenderBufferFlag::STORAGE, { RenderFormat::R8_UINT }, &workload.drawBuffers.lightCountsBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.lookAtIndices.data(), { 0, workload.drawData.lookAtIndices.size() }, sizeof(uint16_t), RenderBufferFlag::FORMATTED | RenderBufferFlag::STORAGE, { RenderFormat::R16_UINT }, &workload.drawBuffers.lookAtIndicesBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.wr64WaterFieldInfo.data(), { 0, workload.drawData.wr64WaterFieldInfo.size() }, sizeof(uint32_t), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.wr64WaterFieldInfoBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.wr64WaterFieldPrevPosShiftX.data(), { 0, workload.drawData.wr64WaterFieldPrevPosShiftX.size() }, sizeof(hlslpp::float4), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.wr64WaterFieldPrevPosShiftXBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.wr64WaterFieldPrevTcShiftZ.data(), { 0, workload.drawData.wr64WaterFieldPrevTcShiftZ.size() }, sizeof(hlslpp::float4), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.wr64WaterFieldPrevTcShiftZBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.faceIndices.data(), { 0, workload.drawData.faceIndices.size() }, sizeof(uint32_t), RenderBufferFlag::INDEX | RenderBufferFlag::STORAGE | rtInputFlag, { }, &workload.drawBuffers.faceIndicesBuffer });
                }
                // Height-only split-screen rounding retains topology and all
                // other streams, but its native endpoint must be re-uploaded.
                if (it.second.position && !it.second.wr64WaterCoverage) {
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.posFloats.data(), { 0, workload.drawData.posFloats.size() }, sizeof(float), RenderBufferFlag::FORMATTED, { RenderFormat::R32_FLOAT }, &workload.drawBuffers.positionBuffer });
                }
                // Coverage replacement already includes both velocity buffers.
                // Appending them again schedules overlapping transfer writes
                // within one upload batch, without an intervening dependency.
                if (it.second.positionVelocity && !it.second.wr64WaterCoverage) {
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.velFloats.data(), { 0, workload.drawData.velFloats.size() }, sizeof(float), RenderBufferFlag::FORMATTED, { RenderFormat::R32_FLOAT }, &workload.drawBuffers.velocityBuffer });
                }

                if (it.second.texcoordVelocity && !it.second.wr64WaterCoverage) {
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.tcVelFloats.data(), { 0, workload.drawData.tcVelFloats.size() }, sizeof(float), RenderBufferFlag::FORMATTED, { RenderFormat::R32_FLOAT }, &workload.drawBuffers.texcoordVelocityBuffer });
                }

                if (it.second.wr64WaterField && !it.second.wr64WaterCoverage) {
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.wr64WaterFieldInfo.data(), { 0, workload.drawData.wr64WaterFieldInfo.size() }, sizeof(uint32_t), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.wr64WaterFieldInfoBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.wr64WaterFieldPrevPosShiftX.data(), { 0, workload.drawData.wr64WaterFieldPrevPosShiftX.size() }, sizeof(hlslpp::float4), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.wr64WaterFieldPrevPosShiftXBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.wr64WaterFieldPrevTcShiftZ.data(), { 0, workload.drawData.wr64WaterFieldPrevTcShiftZ.size() }, sizeof(hlslpp::float4), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.wr64WaterFieldPrevTcShiftZBuffer });
                    uploads.emplace_back(BufferUploader::Upload{ workload.drawData.wr64WaterFieldFaceIndices.data(), { 0, workload.drawData.wr64WaterFieldFaceIndices.size() }, sizeof(uint32_t), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.wr64WaterFieldFaceIndicesBuffer });
                }
            }

            velocityUploader->submit(worker, uploads);
            velocityUploaderUsed = true;
        }
        else {
            velocityUploaderUsed = false;
        }
    }

    void GameFrame::matchScene(WorkloadQueue &workloadQueue, const GameFrame &prevFrame, const GameScene &curScene, const GameScene &prevScene, std::unordered_map<uint32_t, ModifiedBuffers> &workloadsModified, bool &tileInterpolationUsed, bool &lookAtInterpolationUsed) {
        if (curScene.projections.empty() || prevScene.projections.empty()) {
            return;
        }

        thread_local std::multimap<uint64_t, GameCallMap> curCallHashMap;
        thread_local std::multimap<uint64_t, GameCallMap> prevCallHashMap;
        curCallHashMap.clear();
        prevCallHashMap.clear();

        // Pick the first projection for reference of the scene.
        const GameIndices::Projection &firstCurProjIndices = curScene.projections[0];
        const GameIndices::Projection &firstPrevProjIndices = prevScene.projections[0];
        GameFrameMap::WorkloadMap &firstCurWorkloadMap = frameMap.workloads[firstCurProjIndices.workloadIndex];
        Workload &firstCurWorkload = workloadQueue.workloads[firstCurProjIndices.workloadIndex];
        const FramebufferPair &firstCurFbPair = firstCurWorkload.fbPairs[firstCurProjIndices.fbPairIndex];
        const Projection &firstCurProj = firstCurFbPair.projections[firstCurProjIndices.projectionIndex];
        const Workload &firstPrevWorkload = workloadQueue.workloads[firstPrevProjIndices.workloadIndex];
        const FramebufferPair &firstPrevFbPair = firstPrevWorkload.fbPairs[firstPrevProjIndices.fbPairIndex];
        const Projection &firstPrevProj = firstPrevFbPair.projections[firstPrevProjIndices.projectionIndex];
        const GameFrameMap::WorkloadMap *firstPrevWorkloadMap = nullptr;
        if (prevFrame.matched && prevFrame.frameMap.workloads[firstPrevProjIndices.workloadIndex].mapped) {
            firstPrevWorkloadMap = &prevFrame.frameMap.workloads[firstPrevProjIndices.workloadIndex];
        }

        // Build a multimap with all potential compatibilities between draw calls in the projections.
        // Diagnostic-only: the census is armed for the whole native frame by the
        // caller, so every matched scene contributes to the same capture.
        const bool wr64CensusArmed = wr64WaterCensusActive();
        const uint32_t wr64ProjectionCount = uint32_t(curScene.projections.size());
        if (wr64CensusArmed) {
            wr64WaterCensusSceneOrdinal()++;
        }

        uint32_t mappedViewProjIndex = UINT32_MAX;
        for (uint32_t p = 0; p < curScene.projections.size(); p++) {
            const GameIndices::Projection &curProjIndices = curScene.projections[p];
            Workload &curWorkload = workloadQueue.workloads[curProjIndices.workloadIndex];
            const FramebufferPair &curFbPair = curWorkload.fbPairs[curProjIndices.fbPairIndex];
            const Projection &curProj = curFbPair.projections[curProjIndices.projectionIndex];
            buildCallHashMap(p, curWorkload, curProj, curCallHashMap);

            if (wr64CensusArmed) {
                wr64WriteWaterProvenanceCensus(wr64ProjectionCount, p, curWorkload, curProj);
            }

            // Projection for the entire scene has been matched already, copy the mapping.
            if (mappedViewProjIndex < UINT32_MAX) {
                firstCurWorkloadMap.viewProjections[curProj.transformsIndex] = firstCurWorkloadMap.viewProjections[mappedViewProjIndex];
            }

            // Can't map to a previous projection.
            if (p >= prevScene.projections.size()) {
                continue;
            }

            if (mappedViewProjIndex == UINT32_MAX) {
                GameFrameMap::ViewProjectionMap &viewProjMap = firstCurWorkloadMap.viewProjections[curProj.transformsIndex];
                if (viewProjMap.mapped) {
                    mappedViewProjIndex = curProj.transformsIndex;
                    continue;
                }

                const GameIndices::Projection &prevProjIndices = prevScene.projections[p];
                const Workload &prevWorkload = workloadQueue.workloads[prevProjIndices.workloadIndex];
                const FramebufferPair &prevFbPair = prevWorkload.fbPairs[prevProjIndices.fbPairIndex];
                const Projection &prevProj = prevFbPair.projections[prevProjIndices.projectionIndex];
                const hlslpp::float4x4 &curView = curWorkload.drawData.viewTransforms[curProj.transformsIndex];
                const hlslpp::float4x4 &prevView = prevWorkload.drawData.viewTransforms[prevProj.transformsIndex];
                const uint32_t curProjGroupIndex = curWorkload.drawData.viewProjTransformGroups[curProj.transformsIndex];
                const uint32_t prevProjGroupIndex = prevWorkload.drawData.viewProjTransformGroups[prevProj.transformsIndex];
                const TransformGroup &curProjGroup = curWorkload.drawData.transformGroups[curProjGroupIndex];
                const TransformGroup &prevProjGroup = prevWorkload.drawData.transformGroups[prevProjGroupIndex];

                // Cameras usually look better with simple interpolation, so default decomposition to off.
                bool projectionDecompose = RT64::wr64SkyBracketEnvFlag("WR64_CAMERA_DECOMPOSE");
                uint8_t projectionLinearComponent = G_EX_COMPONENT_INTERPOLATE;
                uint8_t projectionAngularComponent = G_EX_COMPONENT_INTERPOLATE;
                uint8_t projectionScaleComponent = G_EX_COMPONENT_INTERPOLATE;
                uint8_t projectionSkewComponent = G_EX_COMPONENT_INTERPOLATE;
                uint8_t projectionPerspectiveComponent = G_EX_COMPONENT_INTERPOLATE;
                if ((curProjGroup.matrixId != G_EX_ID_IGNORE) && (curProjGroup.matrixId != G_EX_ID_AUTO)) {
                    projectionDecompose = curProjGroup.decompose;
                    projectionLinearComponent = curProjGroup.positionInterpolation;
                    projectionAngularComponent = curProjGroup.rotationInterpolation;
                    projectionScaleComponent = curProjGroup.scaleInterpolation;
                    projectionSkewComponent = curProjGroup.skewInterpolation;
                    projectionPerspectiveComponent = curProjGroup.perspectiveInterpolation;
                    viewProjMap.mapped = (curProjGroup.matrixId == prevProjGroup.matrixId);
                }
                else {
                    viewProjMap.mapped = (curProjGroup.matrixId == G_EX_ID_AUTO);
                }

                // CAMCUT-R1. A camera cut is a single-frame discontinuity, and the
                // camera can never reach RigidBody's discontinuity test: its
                // components are forced to G_EX_COMPONENT_INTERPOLATE and that test
                // lives only in the AUTO branch. Measure the same two quantities the
                // test would use and break the match when they say the camera
                // jumped. Breaking the match is RT64's own "cannot match" path -
                // ProjectionProcessor then shows the incoming camera immediately for
                // that one native-frame pair instead of flying to it.
                if (wr64CamCutEvaluate(curWorkload.submissionFrame, curProj.transformsIndex,
                        curProjGroup.matrixId, viewProjMap.mapped, prevView, curView)) {
                    viewProjMap.mapped = false;
                }

                if (viewProjMap.mapped) {
                    if (firstPrevWorkloadMap != nullptr) {
                        const GameFrameMap::ViewProjectionMap &prevViewProjMap = firstPrevWorkloadMap->viewProjections[prevProj.transformsIndex];
                        viewProjMap.rigidBody = prevViewProjMap.rigidBody;
                    }

                    viewProjMap.rigidBody.updateLinear(prevView, curView, projectionLinearComponent);
                    viewProjMap.rigidBody.updateAngular(prevView, curView, projectionAngularComponent, projectionScaleComponent, projectionSkewComponent);
                    viewProjMap.rigidBody.updateDecomposition(curView, projectionDecompose);
                    viewProjMap.prevTransformIndex = prevProj.transformsIndex;
                }
                else {
                    viewProjMap.rigidBody = RigidBody();
                }

                if (viewProjMap.mapped) {
                    mappedViewProjIndex = curProj.transformsIndex;
                }
            }
        }

        for (uint32_t p = 0; p < prevScene.projections.size(); p++) {
            const GameIndices::Projection &prevProjIndices = prevScene.projections[p];
            const Workload &prevWorkload = workloadQueue.workloads[prevProjIndices.workloadIndex];
            const FramebufferPair &prevFbPair = prevWorkload.fbPairs[prevProjIndices.fbPairIndex];
            const Projection &prevProj = prevFbPair.projections[prevProjIndices.projectionIndex];
            buildCallHashMap(p, prevWorkload, prevProj, prevCallHashMap);
        }

        // FIXME: Transform set needs to be done per unique workload detected.
        thread_local std::set<IndexPair> transformCheckSet;
        thread_local std::set<IndexPair> tileCheckSet;
        thread_local std::set<IndexPair> lookAtCheckSet;
        transformCheckSet.clear();
        tileCheckSet.clear();
        lookAtCheckSet.clear();
        thread_local std::set<uint32_t> wr64WaterCurTransforms;
        wr64WaterCurTransforms.clear();
        thread_local std::set<uint32_t> wr64ExactSkyCurTransforms;
        wr64ExactSkyCurTransforms.clear();

        // Observation only. Drops the previous frame's transform to signature map so
        // the rows written later in this frame describe this frame's geometry. Costs
        // one bool read when the census is off.
        wr64SkyCensusBeginFrame();

        // Traverse the map and fill the set with all the combinations of transforms to check.
        for (std::pair<uint64_t, GameCallMap> curIt : curCallHashMap) {
            auto prevRange = prevCallHashMap.equal_range(curIt.first);
            const GameIndices::Projection &waterCurProjIndices = curScene.projections[curIt.second.sceneProjIndex];
            Workload &waterCurWorkload = workloadQueue.workloads[waterCurProjIndices.workloadIndex];
            const FramebufferPair &waterCurFbPair = waterCurWorkload.fbPairs[waterCurProjIndices.fbPairIndex];
            const Projection &waterCurProj = waterCurFbPair.projections[waterCurProjIndices.projectionIndex];
            const GameCall &waterCurCall = waterCurProj.gameCalls[curIt.second.callIndex];
            const bool wr64WaterProvenanceCall =
                isWr64GeneratedWaterProvenanceCall(waterCurWorkload.drawData, waterCurCall);
            const bool wr64WaterCall = isWr64GeneratedWaterCall(waterCurWorkload.drawData, waterCurCall);
            const uint32_t wr64PrevHashCandidates = uint32_t(std::distance(prevRange.first, prevRange.second));
            uint32_t wr64SkyMatrixIdHash = 0;
            for (uint32_t m = waterCurCall.callDesc.minWorldMatrix;
                m <= waterCurCall.callDesc.maxWorldMatrix; m++)
            {
                const uint32_t groupIndex =
                    waterCurWorkload.drawData.worldTransformGroups[m];
                const TransformGroup &group =
                    waterCurWorkload.drawData.transformGroups[groupIndex];
                wr64SkyMatrixIdHash =
                    (wr64SkyMatrixIdHash * 33U) ^ group.matrixId;
            }
            const bool wr64ExactSkyCall =
                isWr64CourseSkyDraw(
                    waterCurCall.callDesc, wr64SkyMatrixIdHash);
            if (wr64ExactSkyCall) {
                for (uint32_t m = waterCurCall.callDesc.minWorldMatrix;
                    m <= waterCurCall.callDesc.maxWorldMatrix; m++)
                {
                    wr64ExactSkyCurTransforms.emplace(m);
                }
            }

            // Observation only. Records what each current transform index was drawn
            // with, so that when the census later catches a transform whose
            // translation lerp flipped off, the row can say which draw call that
            // transform belonged to. Without this the census would only report that
            // something flipped, not what. Reads nothing that the loop below does not
            // already read, and is skipped entirely when the census is off.
            if (wr64SkyCensusEnabled()) {
                const DrawCall &censusDesc = waterCurCall.callDesc;
                Wr64SkyCensusSignature censusSignature;
                censusSignature.colorCombiner = (uint64_t(censusDesc.colorCombiner.L) << 32) | censusDesc.colorCombiner.H;
                censusSignature.otherMode = (uint64_t(censusDesc.otherMode.L) << 32) | censusDesc.otherMode.H;
                for (uint32_t t = 0; (t < censusDesc.tileCount) && (t < 4); t++) {
                    const uint32_t tileIndex = censusDesc.tileIndex + t;
                    if (tileIndex < waterCurWorkload.drawData.callTiles.size()) {
                        censusSignature.textureHash = waterCurWorkload.drawData.callTiles[tileIndex].tmemHashOrID;
                        break;
                    }
                }

                censusSignature.triangleCount = censusDesc.triangleCount;
                censusSignature.minWorldMatrix = censusDesc.minWorldMatrix;
                censusSignature.maxWorldMatrix = censusDesc.maxWorldMatrix;
                censusSignature.callIndex = curIt.second.callIndex;

                for (uint32_t m = censusDesc.minWorldMatrix; m <= censusDesc.maxWorldMatrix; m++) {
                    if (m >= waterCurWorkload.drawData.worldTransformVertexIndices.size()) {
                        continue;
                    }

                    Wr64SkyCensusSignature transformSignature = censusSignature;
                    transformSignature.vertexCount = waterCurWorkload.drawData.worldTransformVertexCount(m);

                    const uint32_t vertexIndex = waterCurWorkload.drawData.worldTransformVertexIndices[m];
                    const uint64_t vertexEnd = uint64_t(vertexIndex) + transformSignature.vertexCount;
                    if (vertexEnd <= waterCurWorkload.drawData.vertexSegmentedAddresses.size()) {
                        transformSignature.firstVertexAddress = waterCurWorkload.drawData.vertexSegmentedAddresses[vertexIndex];

                        // How many of this transform's vertices came out of the
                        // graphics pool. The water sheet is entirely pool built and
                        // the sky is not, so this one number separates them without
                        // having to guess from triangle counts.
                        for (uint32_t v = 0; v < transformSignature.vertexCount; v++) {
                            transformSignature.generatedVertexCount +=
                                isWr64GeneratedWaterVertexAddress(waterCurWorkload.drawData.vertexSegmentedAddresses[vertexIndex + v]) ? 1u : 0u;
                        }
                    }

                    wr64SkyCensusRegisterCall(m, transformSignature);
                }
            }

            if (wr64WaterProvenanceCall) {
                std::vector<uint8_t> &waterMask = waterCurWorkload.drawData.wr64WaterVertexMask;
                if (waterMask.size() != waterCurWorkload.drawData.vertexCount()) {
                    static uint32_t wr64PatchMaskResetProbeCount = 0;
                    if (wr64WaterTrailingPatchEnabled() &&
                        (wr64PatchMaskResetProbeCount < 20))
                    {
                        wr64PatchMaskResetProbeCount++;
                        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                            "[water-patch-mask-reset] frame=%llu old=%zu vertices=%u\n",
                            static_cast<unsigned long long>(waterCurWorkload.submissionFrame),
                            waterMask.size(), waterCurWorkload.drawData.vertexCount()); }
                    }
                    waterMask.assign(waterCurWorkload.drawData.vertexCount(), 0);
                }
                const uint64_t waterFaceStart = waterCurCall.meshDesc.faceIndicesStart;
                const uint64_t waterFaceEnd = waterFaceStart +
                    (uint64_t(waterCurCall.callDesc.triangleCount) * 3ULL);
                if (waterFaceEnd <= waterCurWorkload.drawData.faceIndices.size()) {
                    waterCurWorkload.drawData.wr64WaterFaceIndices.assign(
                        waterCurWorkload.drawData.faceIndices.begin() + size_t(waterFaceStart),
                        waterCurWorkload.drawData.faceIndices.begin() + size_t(waterFaceEnd));
                    for (uint64_t f = waterFaceStart; f < waterFaceEnd; f++) {
                        const uint32_t vertexIndex = waterCurWorkload.drawData.faceIndices[size_t(f)];
                        if (vertexIndex < waterMask.size()) {
                            // Augmentation runs before provenance matching and
                            // assigns stronger CPU-only identities (2/3) to
                            // generated coverage vertices.  The augmented call
                            // includes those vertices in its face range, so do
                            // not flatten their identity back to ordinary water.
                            if (waterMask[vertexIndex] == 0) {
                                waterMask[vertexIndex] = 1;
                            }
                        }
                    }
                }
            }

            if (wr64WaterCall) {
                for (uint32_t m = waterCurCall.callDesc.minWorldMatrix; m <= waterCurCall.callDesc.maxWorldMatrix; m++) {
                    wr64WaterCurTransforms.emplace(m);
                }

                if (wr64WaterPassTraceTriggerConsumed()) {
                    FILE *passTraceFile = wr64WaterPassTraceFile();
                    if (passTraceFile != nullptr) {
                        for (const std::pair<uint64_t, GameCallMap> &siblingIt : curCallHashMap) {
                        if (siblingIt.second.sceneProjIndex != curIt.second.sceneProjIndex) {
                            continue;
                        }

                        const GameCall &siblingCall = waterCurProj.gameCalls[siblingIt.second.callIndex];
                        const DrawCall &siblingDesc = siblingCall.callDesc;
                        const bool overlapsExactTransform =
                            (siblingDesc.minWorldMatrix <= waterCurCall.callDesc.maxWorldMatrix) &&
                            (siblingDesc.maxWorldMatrix >= waterCurCall.callDesc.minWorldMatrix);
                        const uint64_t combiner = (uint64_t(siblingDesc.colorCombiner.L) << 32) | siblingDesc.colorCombiner.H;
                        const uint64_t otherMode = (uint64_t(siblingDesc.otherMode.L) << 32) | siblingDesc.otherMode.H;
                        uint64_t textures[4] = {};
                        for (uint32_t t = 0; (t < siblingDesc.tileCount) && (t < 4); t++) {
                            const uint32_t tileIndex = siblingDesc.tileIndex + t;
                            if (tileIndex < waterCurWorkload.drawData.callTiles.size()) {
                                textures[t] = waterCurWorkload.drawData.callTiles[tileIndex].tmemHashOrID;
                            }
                        }

                        uint32_t generatedVertexCount = 0;
                        uint8_t vertexMode = UINT8_MAX;
                        uint8_t texcoordMode = UINT8_MAX;
                        uint8_t tileMode = UINT8_MAX;
                        bool mixedTransformGroups = false;
                        for (uint32_t m = siblingDesc.minWorldMatrix; m <= siblingDesc.maxWorldMatrix; m++) {
                            if ((m >= waterCurWorkload.drawData.worldTransformVertexIndices.size()) ||
                                (m >= waterCurWorkload.drawData.worldTransformGroups.size()))
                            {
                                continue;
                            }

                            generatedVertexCount += waterCurWorkload.drawData.worldTransformVertexCount(m);
                            const uint32_t groupIndex = waterCurWorkload.drawData.worldTransformGroups[m];
                            if (groupIndex >= waterCurWorkload.drawData.transformGroups.size()) {
                                continue;
                            }

                            const TransformGroup &group = waterCurWorkload.drawData.transformGroups[groupIndex];
                            if (vertexMode == UINT8_MAX) {
                                vertexMode = group.vertexInterpolation;
                                texcoordMode = group.texcoordInterpolation;
                                tileMode = group.tileInterpolation;
                            }
                            else if ((vertexMode != group.vertexInterpolation) ||
                                (texcoordMode != group.texcoordInterpolation) ||
                                (tileMode != group.tileInterpolation))
                            {
                                mixedTransformGroups = true;
                            }
                        }

                        std::fprintf(passTraceFile,
                            "%llu,%u,%u,%u,%u,%llu,%u,%u,%u,%u,%llu,%llu,%u,"
                            "%llu,%llu,%llu,%llu,%u,%u,%u,%u,%u\n",
                            static_cast<unsigned long long>(waterCurWorkload.submissionFrame),
                            waterCurProjIndices.workloadIndex,
                            curIt.second.sceneProjIndex,
                            curIt.second.callIndex,
                            siblingIt.second.callIndex,
                            static_cast<unsigned long long>(siblingIt.first),
                            uint32_t(overlapsExactTransform),
                            siblingDesc.minWorldMatrix,
                            siblingDesc.maxWorldMatrix,
                            siblingDesc.triangleCount,
                            static_cast<unsigned long long>(combiner),
                            static_cast<unsigned long long>(otherMode),
                            siblingDesc.tileCount,
                            static_cast<unsigned long long>(textures[0]),
                            static_cast<unsigned long long>(textures[1]),
                            static_cast<unsigned long long>(textures[2]),
                            static_cast<unsigned long long>(textures[3]),
                            generatedVertexCount,
                            uint32_t(vertexMode),
                            uint32_t(texcoordMode),
                            uint32_t(tileMode),
                            uint32_t(mixedTransformGroups));
                        }

                        std::fflush(passTraceFile);
                        wr64CloseWaterPassTraceFile();
                    }
                }

                FILE *traceFile = wr64WaterMeshTraceFile();
                if ((traceFile != nullptr) && (wr64PrevHashCandidates == 0)) {
                    const uint32_t curMatrixCount = (waterCurCall.callDesc.maxWorldMatrix - waterCurCall.callDesc.minWorldMatrix) + 1;
                    std::fprintf(traceFile,
                        "%llu,call_no_previous_hash,%u,%u,%u,%u,%u,%llu,%u,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%llu,%llu,%llu,%llu,%u,%u,%u,%u\n",
                        static_cast<unsigned long long>(waterCurWorkload.submissionFrame),
                        waterCurProjIndices.workloadIndex, UINT32_MAX, curIt.second.sceneProjIndex,
                        curIt.second.callIndex, UINT32_MAX, static_cast<unsigned long long>(curIt.first), wr64PrevHashCandidates,
                        UINT32_MAX, UINT32_MAX, UINT32_MAX, UINT32_MAX, UINT32_MAX, UINT32_MAX,
                        curMatrixCount, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0ULL, 0ULL, 0ULL, 0ULL, 0, 0, 0, 0);
                    std::fflush(traceFile);
                }
            }

            for (auto prevIt = prevRange.first; prevIt != prevRange.second; prevIt++) {
                const GameIndices::Projection &curProjIndices = curScene.projections[curIt.second.sceneProjIndex];
                const Workload &curWorkload = workloadQueue.workloads[curProjIndices.workloadIndex];
                const FramebufferPair &curFbPair = curWorkload.fbPairs[curProjIndices.fbPairIndex];
                const Projection &curProj = curFbPair.projections[curProjIndices.projectionIndex];
                const GameCall &curCall = curProj.gameCalls[curIt.second.callIndex];
                const GameIndices::Projection &prevProjIndices = prevScene.projections[prevIt->second.sceneProjIndex];
                const Workload &prevWorkload = workloadQueue.workloads[prevProjIndices.workloadIndex];
                const FramebufferPair &prevFbPair = prevWorkload.fbPairs[prevProjIndices.fbPairIndex];
                const Projection &prevProj = prevFbPair.projections[prevProjIndices.projectionIndex];
                const GameCall &prevCall = prevProj.gameCalls[prevIt->second.callIndex];
                const uint32_t curWorldMatrixCount = (curCall.callDesc.maxWorldMatrix - curCall.callDesc.minWorldMatrix) + 1;
                const uint32_t prevWorldMatrixCount = (prevCall.callDesc.maxWorldMatrix - prevCall.callDesc.minWorldMatrix) + 1;
                if (wr64WaterCall) {
                    FILE *correspondenceTraceFile = wr64WaterCorrespondenceTraceFile();
                    if (correspondenceTraceFile != nullptr) {
                        const uint32_t curIndexCount = curCall.callDesc.triangleCount * 3;
                        const uint32_t prevIndexCount = prevCall.callDesc.triangleCount * 3;
                        const uint32_t curFaceStart = curCall.meshDesc.faceIndicesStart;
                        const uint32_t prevFaceStart = prevCall.meshDesc.faceIndicesStart;
                        const bool validTopology =
                            (curIndexCount == prevIndexCount) &&
                            ((curFaceStart + curIndexCount) <= curWorkload.drawData.faceIndices.size()) &&
                            ((prevFaceStart + prevIndexCount) <= prevWorkload.drawData.faceIndices.size());

                        uint32_t curIndexMin = 0;
                        uint32_t curIndexMax = 0;
                        uint32_t prevIndexMin = 0;
                        uint32_t prevIndexMax = 0;
                        uint32_t curUniqueIndices = 0;
                        uint32_t prevUniqueIndices = 0;
                        uint64_t curRawIndexHash = 0;
                        uint64_t prevRawIndexHash = 0;
                        uint64_t curNormalizedIndexHash = 0;
                        uint64_t prevNormalizedIndexHash = 0;
                        uint32_t normalizedTopologyEqual = 0;

                        if (validTopology && (curIndexCount > 0)) {
                            const uint32_t *curIndices = &curWorkload.drawData.faceIndices[curFaceStart];
                            const uint32_t *prevIndices = &prevWorkload.drawData.faceIndices[prevFaceStart];
                            curIndexMin = *std::min_element(curIndices, curIndices + curIndexCount);
                            curIndexMax = *std::max_element(curIndices, curIndices + curIndexCount);
                            prevIndexMin = *std::min_element(prevIndices, prevIndices + prevIndexCount);
                            prevIndexMax = *std::max_element(prevIndices, prevIndices + prevIndexCount);
                            curRawIndexHash = XXH3_64bits(curIndices, curIndexCount * sizeof(uint32_t));
                            prevRawIndexHash = XXH3_64bits(prevIndices, prevIndexCount * sizeof(uint32_t));

                            std::vector<uint32_t> curNormalized(curIndexCount);
                            std::vector<uint32_t> prevNormalized(prevIndexCount);
                            for (uint32_t i = 0; i < curIndexCount; i++) {
                                curNormalized[i] = curIndices[i] - curIndexMin;
                                prevNormalized[i] = prevIndices[i] - prevIndexMin;
                            }

                            curNormalizedIndexHash = XXH3_64bits(curNormalized.data(), curNormalized.size() * sizeof(uint32_t));
                            prevNormalizedIndexHash = XXH3_64bits(prevNormalized.data(), prevNormalized.size() * sizeof(uint32_t));
                            normalizedTopologyEqual = uint32_t(curNormalizedIndexHash == prevNormalizedIndexHash);

                            std::sort(curNormalized.begin(), curNormalized.end());
                            std::sort(prevNormalized.begin(), prevNormalized.end());
                            curUniqueIndices = uint32_t(std::unique(curNormalized.begin(), curNormalized.end()) - curNormalized.begin());
                            prevUniqueIndices = uint32_t(std::unique(prevNormalized.begin(), prevNormalized.end()) - prevNormalized.begin());
                        }

                        std::fprintf(correspondenceTraceFile,
                            "%llu,call_topology,%u,%u,%u,%u,"
                            "%u,%u,%u,%u,%u,"
                            "%u,%u,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,"
                            "%u,%u,%.9g,%.9g,%.9g,%.9g,"
                            "%u,%u,%u,%u,%u,%u,%u,%u,%u,"
                            "%llu,%llu,%llu,%llu,%u\n",
                            static_cast<unsigned long long>(curWorkload.submissionFrame),
                            curProjIndices.workloadIndex, prevProjIndices.workloadIndex,
                            curIt.second.callIndex, prevIt->second.callIndex,
                            UINT32_MAX, UINT32_MAX, 0, 0, 0,
                            0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                            0, 0, 0.0, 0.0, 0.0, 0.0,
                            curFaceStart, prevFaceStart, validTopology ? curIndexCount : 0,
                            curIndexMin, curIndexMax, prevIndexMin, prevIndexMax,
                            curUniqueIndices, prevUniqueIndices,
                            static_cast<unsigned long long>(curRawIndexHash),
                            static_cast<unsigned long long>(prevRawIndexHash),
                            static_cast<unsigned long long>(curNormalizedIndexHash),
                            static_cast<unsigned long long>(prevNormalizedIndexHash),
                            normalizedTopologyEqual);
                        std::fflush(correspondenceTraceFile);
                    }

                    FILE *attributeTraceFile = wr64WaterAttributeTraceFile();
                    if (attributeTraceFile != nullptr) {
                        const uint32_t pairedTileCount = std::min(curCall.callDesc.tileCount, prevCall.callDesc.tileCount);
                        for (uint32_t t = 0; t < pairedTileCount; t++) {
                            const uint32_t curTileIndex = curCall.callDesc.tileIndex + t;
                            const uint32_t prevTileIndex = prevCall.callDesc.tileIndex + t;
                            if ((curTileIndex >= curWorkload.drawData.callTiles.size()) ||
                                (prevTileIndex >= prevWorkload.drawData.callTiles.size()))
                            {
                                continue;
                            }

                            const DrawCallTile &curTile = curWorkload.drawData.callTiles[curTileIndex];
                            const DrawCallTile &prevTile = prevWorkload.drawData.callTiles[prevTileIndex];
                            std::fprintf(attributeTraceFile,
                                "%llu,call_tile,%u,%u,%u,%u,"
                                "%u,%u,%u,%u,%u,%u,"
                                "%llu,%llu,%u,%u,%u,"
                                "%08X,%08X,%u,%u,%016llX,%016llX,"
                                "%u,%u,%u,%u,%u,%u,%u,%u,"
                                "%u,%u,%u,%u,"
                                "%d,%d,%d,%d,%d,%d,%d,%d\n",
                                static_cast<unsigned long long>(curWorkload.submissionFrame),
                                curProjIndices.workloadIndex, prevProjIndices.workloadIndex,
                                curIt.second.callIndex, prevIt->second.callIndex,
                                UINT32_MAX, UINT32_MAX, 0, 0, 0, 0,
                                0ULL, 0ULL, 0, 0, 0,
                                curCall.callDesc.geometryMode, prevCall.callDesc.geometryMode,
                                curTileIndex, prevTileIndex,
                                static_cast<unsigned long long>(curTile.tmemHashOrID),
                                static_cast<unsigned long long>(prevTile.tmemHashOrID),
                                curTile.loadTile.uls, curTile.loadTile.ult, curTile.loadTile.lrs, curTile.loadTile.lrt,
                                prevTile.loadTile.uls, prevTile.loadTile.ult, prevTile.loadTile.lrs, prevTile.loadTile.lrt,
                                curTile.sampleWidth, curTile.sampleHeight, prevTile.sampleWidth, prevTile.sampleHeight,
                                curTile.minTexcoord.x, curTile.minTexcoord.y, curTile.maxTexcoord.x, curTile.maxTexcoord.y,
                                prevTile.minTexcoord.x, prevTile.minTexcoord.y, prevTile.maxTexcoord.x, prevTile.maxTexcoord.y);
                        }

                        std::fflush(attributeTraceFile);
                    }

                    FILE *traceFile = wr64WaterMeshTraceFile();
                    if (traceFile != nullptr) {
                        std::fprintf(traceFile,
                            "%llu,call_pair,%u,%u,%u,%u,%u,%llu,%u,"
                            "%u,%u,%u,%u,%u,%u,%u,%u,"
                            "%u,%u,%u,%u,%u,%u,%u,%u,"
                            "%llu,%llu,%llu,%llu,%u,%u,%u,%u\n",
                            static_cast<unsigned long long>(curWorkload.submissionFrame),
                            curProjIndices.workloadIndex, prevProjIndices.workloadIndex, curIt.second.sceneProjIndex,
                            curIt.second.callIndex, prevIt->second.callIndex, static_cast<unsigned long long>(curIt.first), wr64PrevHashCandidates,
                            UINT32_MAX, UINT32_MAX, UINT32_MAX, UINT32_MAX, UINT32_MAX, UINT32_MAX,
                            curWorldMatrixCount, prevWorldMatrixCount,
                            0, 0, 0, 0, 0, 0, 0, 0,
                            0ULL, 0ULL, 0ULL, 0ULL, 0,
                            uint32_t(curIt.second.doTransformMatching && prevIt->second.doTransformMatching), 0, 0);
                        std::fflush(traceFile);
                    }
                }

                if ((curWorldMatrixCount == prevWorldMatrixCount) && curIt.second.doTransformMatching && prevIt->second.doTransformMatching) {
                    for (uint32_t w = 0; w < curWorldMatrixCount; w++) {
                        const uint32_t curWorldMatrix = curCall.callDesc.minWorldMatrix + w;
                        const uint32_t curGroupIndex = curWorkload.drawData.worldTransformGroups[curWorldMatrix];
                        const TransformGroup &curGroup = curWorkload.drawData.transformGroups[curGroupIndex];
                        const uint32_t prevWorldMatrix = prevCall.callDesc.minWorldMatrix + w;
                        const uint32_t prevGroupIndex = prevWorkload.drawData.worldTransformGroups[prevWorldMatrix];
                        const TransformGroup &prevGroup = prevWorkload.drawData.transformGroups[prevGroupIndex];
                        const bool matrixPairEligible =
                            (curGroup.matrixId == prevGroup.matrixId) &&
                            ((curGroup.matrixId == G_EX_ID_AUTO) ||
                                ((curGroup.matrixId != G_EX_ID_IGNORE) && (curGroup.ordering == G_EX_ORDER_AUTO)));
                        if (wr64WaterCall) {
                            FILE *identityTraceFile = wr64WaterCallIdentityTraceFile();
                            if (identityTraceFile != nullptr) {
                                const Wr64WaterSourceIdentity curIdentity =
                                    wr64WaterSourceIdentity(curWorkload.drawData, curWorldMatrix);
                                const Wr64WaterSourceIdentity prevIdentity =
                                    wr64WaterSourceIdentity(prevWorkload.drawData, prevWorldMatrix);
                                const bool sequenceEqual =
                                    curIdentity.validRange && prevIdentity.validRange &&
                                    (curIdentity.sequence == prevIdentity.sequence);
                                const bool multisetEqual =
                                    curIdentity.validRange && prevIdentity.validRange &&
                                    (curIdentity.sorted == prevIdentity.sorted);
                                const uint32_t intersection =
                                    wr64WaterMultisetIntersection(curIdentity.sorted, prevIdentity.sorted);
                                const double intersectionOverCur = curIdentity.generatedCount > 0
                                    ? double(intersection) / double(curIdentity.generatedCount)
                                    : 0.0;
                                std::fprintf(identityTraceFile,
                                    "%llu,%016llX,%u,"
                                    "%u,%u,%u,%u,%u,%u,"
                                    "%u,%u,%u,%u,"
                                    "%u,%u,%u,%u,"
                                    "%08X,%08X,%08X,%08X,"
                                    "%016llX,%016llX,%016llX,%016llX,"
                                    "%u,%u,%u,%.9f,%u\n",
                                    static_cast<unsigned long long>(curWorkload.submissionFrame),
                                    static_cast<unsigned long long>(curIt.first),
                                    wr64PrevHashCandidates,
                                    curProjIndices.workloadIndex, prevProjIndices.workloadIndex,
                                    curIt.second.sceneProjIndex,
                                    curIt.second.callIndex, prevIt->second.callIndex, w,
                                    curWorldMatrix, prevWorldMatrix,
                                    curIdentity.vertexIndex, prevIdentity.vertexIndex,
                                    curIdentity.vertexCount, prevIdentity.vertexCount,
                                    curIdentity.generatedCount, prevIdentity.generatedCount,
                                    curIdentity.sourceMin, curIdentity.sourceMax,
                                    prevIdentity.sourceMin, prevIdentity.sourceMax,
                                    static_cast<unsigned long long>(curIdentity.sequenceHash),
                                    static_cast<unsigned long long>(prevIdentity.sequenceHash),
                                    static_cast<unsigned long long>(curIdentity.multisetHash),
                                    static_cast<unsigned long long>(prevIdentity.multisetHash),
                                    uint32_t(sequenceEqual), uint32_t(multisetEqual),
                                    intersection, intersectionOverCur,
                                    uint32_t(matrixPairEligible));
                                std::fflush(identityTraceFile);
                            }
                        }

                        if (matrixPairEligible) {
                            transformCheckSet.emplace(curWorldMatrix, prevWorldMatrix);
                        }
                    }
                }

                if ((curCall.callDesc.tileCount == prevCall.callDesc.tileCount) && (curIt.second.doTileInterpolation && prevIt->second.doTileInterpolation)) {
                    for (uint32_t t = 0; t < curCall.callDesc.tileCount; t++) {
                        const DrawCallTile &curCallTile = curWorkload.drawData.callTiles[curCall.callDesc.tileIndex + t];
                        const DrawCallTile &prevCallTile = prevWorkload.drawData.callTiles[prevCall.callDesc.tileIndex + t];
                        bool doTileMatching = curIt.second.doTileMatching && prevIt->second.doTileMatching;
                        if (doTileMatching && (curCallTile.tmemHashOrID != prevCallTile.tmemHashOrID)) {
                            continue;
                        }

                        tileCheckSet.emplace(curCall.callDesc.tileIndex + t, prevCall.callDesc.tileIndex + t);
                    }
                }

                const uint32_t textureGenMask = G_LIGHTING | G_TEXTURE_GEN;
                const bool curUsesTextureGen = (curCall.callDesc.geometryMode & textureGenMask) == textureGenMask;
                const bool prevUsesTextureGen = (prevCall.callDesc.geometryMode & textureGenMask) == textureGenMask;
                if (curUsesTextureGen && prevUsesTextureGen && (true && true)) { // TODO: Do look at matching condition.
                    // FIXME: We assume the same look at is used throughout the entire draw call, so we only check the first vertex.
                    const uint32_t curVertexIndex = curWorkload.drawData.faceIndices[curCall.meshDesc.faceIndicesStart];
                    const uint32_t prevVertexIndex = prevWorkload.drawData.faceIndices[prevCall.meshDesc.faceIndicesStart];
                    const uint32_t curLookAtIndex = curWorkload.drawData.lookAtIndices[curVertexIndex] >> RSP_LOOKAT_INDEX_SHIFT;
                    const uint32_t prevLookAtIndex = prevWorkload.drawData.lookAtIndices[prevVertexIndex] >> RSP_LOOKAT_INDEX_SHIFT;
                    lookAtCheckSet.emplace(curLookAtIndex, prevLookAtIndex);
                }
            }
        }

        // Compute all the differences between transforms and insert them into a vector that will be sorted according to the differences.
        thread_local std::vector<MatchCandidate> matchCandidates;
        matchCandidates.clear();

        const RigidBody *prevRigidBody;
        const hlslpp::float4x4 &firstCurViewProj = firstCurWorkload.drawData.viewProjTransforms[firstCurProj.transformsIndex];
        const hlslpp::float4x4 &firstPrevViewProj = firstPrevWorkload.drawData.viewProjTransforms[firstPrevProj.transformsIndex];
        for (const IndexPair &indices : transformCheckSet) {
            const hlslpp::float4x4 &curTransform = firstCurWorkload.drawData.worldTransforms[indices.first];
            const hlslpp::float4x4 &prevTransform = firstPrevWorkload.drawData.worldTransforms[indices.second];
            prevRigidBody = (firstPrevWorkloadMap != nullptr) ? &firstPrevWorkloadMap->transforms[indices.second].rigidBody : nullptr;

            TransformMatchResult matchResult = computeTransformMatch(curTransform, firstCurViewProj, prevTransform, firstPrevViewProj, prevRigidBody);
            if (wr64WaterCurTransforms.find(indices.first) != wr64WaterCurTransforms.end()) {
                const uint32_t curGroupIndex = firstCurWorkload.drawData.worldTransformGroups[indices.first];
                const uint32_t prevGroupIndex = firstPrevWorkload.drawData.worldTransformGroups[indices.second];
                const TransformGroup &curGroup = firstCurWorkload.drawData.transformGroups[curGroupIndex];
                const TransformGroup &prevGroup = firstPrevWorkload.drawData.transformGroups[prevGroupIndex];
                const uint32_t curVertexIndex = firstCurWorkload.drawData.worldTransformVertexIndices[indices.first];
                const uint32_t curVertexCount = firstCurWorkload.drawData.worldTransformVertexCount(indices.first);
                const uint32_t prevVertexIndex = firstPrevWorkload.drawData.worldTransformVertexIndices[indices.second];
                const uint32_t prevVertexCount = firstPrevWorkload.drawData.worldTransformVertexCount(indices.second);
                uint64_t curPositionHash = 0;
                uint64_t prevPositionHash = 0;
                uint64_t curTexcoordHash = 0;
                uint64_t prevTexcoordHash = 0;
                uint64_t curNormColHash = 0;
                uint64_t prevNormColHash = 0;
                uint32_t normColChangedBytes = 0;
                uint32_t normColChangedVertices = 0;
                uint32_t normColMaxAbsByteDelta = 0;
                if (curVertexCount == prevVertexCount) {
                    curPositionHash = XXH3_64bits(&firstCurWorkload.drawData.posFloats[curVertexIndex * 3], curVertexCount * 3 * sizeof(float));
                    prevPositionHash = XXH3_64bits(&firstPrevWorkload.drawData.posFloats[prevVertexIndex * 3], prevVertexCount * 3 * sizeof(float));
                    curTexcoordHash = XXH3_64bits(&firstCurWorkload.drawData.tcFloats[curVertexIndex * 2], curVertexCount * 2 * sizeof(float));
                    prevTexcoordHash = XXH3_64bits(&firstPrevWorkload.drawData.tcFloats[prevVertexIndex * 2], prevVertexCount * 2 * sizeof(float));

                    const size_t curNormColOffset = size_t(curVertexIndex) * 4;
                    const size_t prevNormColOffset = size_t(prevVertexIndex) * 4;
                    const size_t normColByteCount = size_t(curVertexCount) * 4;
                    if (((curNormColOffset + normColByteCount) <= firstCurWorkload.drawData.normColBytes.size()) &&
                        ((prevNormColOffset + normColByteCount) <= firstPrevWorkload.drawData.normColBytes.size()))
                    {
                        const uint8_t *curNormCol = &firstCurWorkload.drawData.normColBytes[curNormColOffset];
                        const uint8_t *prevNormCol = &firstPrevWorkload.drawData.normColBytes[prevNormColOffset];
                        curNormColHash = XXH3_64bits(curNormCol, normColByteCount);
                        prevNormColHash = XXH3_64bits(prevNormCol, normColByteCount);
                        for (uint32_t v = 0; v < curVertexCount; v++) {
                            bool vertexChanged = false;
                            for (uint32_t b = 0; b < 4; b++) {
                                const uint32_t byteIndex = (v * 4) + b;
                                const uint32_t curByte = curNormCol[byteIndex];
                                const uint32_t prevByte = prevNormCol[byteIndex];
                                if (curByte != prevByte) {
                                    normColChangedBytes++;
                                    vertexChanged = true;
                                    const uint32_t absDelta = (curByte > prevByte) ? (curByte - prevByte) : (prevByte - curByte);
                                    normColMaxAbsByteDelta = std::max(normColMaxAbsByteDelta, absDelta);
                                }
                            }

                            normColChangedVertices += vertexChanged ? 1U : 0U;
                        }
                    }
                }

                FILE *attributeTraceFile = wr64WaterAttributeTraceFile();
                if (attributeTraceFile != nullptr) {
                    std::fprintf(attributeTraceFile,
                        "%llu,transform_attribute,%u,%u,%u,%u,"
                        "%u,%u,%u,%u,%u,%u,"
                        "%llu,%llu,%u,%u,%u,"
                        "%08X,%08X,%u,%u,%016llX,%016llX,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%u,%u,%u,%u,"
                        "%d,%d,%d,%d,%d,%d,%d,%d\n",
                        static_cast<unsigned long long>(firstCurWorkload.submissionFrame),
                        firstCurProjIndices.workloadIndex, firstPrevProjIndices.workloadIndex,
                        UINT32_MAX, UINT32_MAX,
                        indices.first, indices.second,
                        curVertexIndex, curVertexCount, prevVertexIndex, prevVertexCount,
                        static_cast<unsigned long long>(curNormColHash),
                        static_cast<unsigned long long>(prevNormColHash),
                        normColChangedBytes, normColChangedVertices, normColMaxAbsByteDelta,
                        0U, 0U, UINT32_MAX, UINT32_MAX, 0ULL, 0ULL,
                        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
                        0U, 0U, 0U, 0U,
                        0, 0, 0, 0, 0, 0, 0, 0);
                    std::fflush(attributeTraceFile);
                }

                FILE *traceFile = wr64WaterMeshTraceFile();
                if (traceFile != nullptr) {
                    std::fprintf(traceFile,
                        "%llu,transform_candidate,%u,%u,%u,%u,%u,%llu,%u,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%llu,%llu,%llu,%llu,%u,%u,%u,%u\n",
                        static_cast<unsigned long long>(firstCurWorkload.submissionFrame),
                        firstCurProjIndices.workloadIndex, firstPrevProjIndices.workloadIndex, 0,
                        UINT32_MAX, UINT32_MAX, 0ULL, 0,
                        indices.first, indices.second, curGroupIndex, prevGroupIndex, curGroup.matrixId, prevGroup.matrixId,
                        0, 0,
                        curVertexIndex, curVertexCount, prevVertexIndex, prevVertexCount,
                        curGroup.vertexInterpolation, curGroup.texcoordInterpolation, curGroup.tileInterpolation, uint32_t(curGroup.decompose),
                        static_cast<unsigned long long>(curPositionHash), static_cast<unsigned long long>(prevPositionHash),
                        static_cast<unsigned long long>(curTexcoordHash), static_cast<unsigned long long>(prevTexcoordHash),
                        uint32_t(matchResult.valid), 0,
                        uint32_t(firstCurWorkloadMap.transforms[indices.first].mapped),
                        uint32_t(firstCurWorkloadMap.prevTransformsMapped[indices.second]));
                    std::fflush(traceFile);
                }
            }

            if (matchResult.valid) {
                matchCandidates.emplace_back(indices.first, indices.second, matchResult.computeDifference());
            }
        }

        ModifiedBuffers modifiedBuffers;
        std::stable_sort(matchCandidates.begin(), matchCandidates.end());
        for (const MatchCandidate candidate : matchCandidates) {
            const bool wr64WaterTransform = wr64WaterCurTransforms.find(candidate.curIndex) != wr64WaterCurTransforms.end();
            const bool wr64ExactSkyTransform =
                wr64ExactSkyCurTransforms.find(candidate.curIndex) !=
                wr64ExactSkyCurTransforms.end();
            const bool curAlreadyMapped = firstCurWorkloadMap.transforms[candidate.curIndex].mapped;
            const bool prevAlreadyMapped = firstCurWorkloadMap.prevTransformsMapped[candidate.prevIndex];
            if (firstCurWorkloadMap.transforms[candidate.curIndex].mapped) {
                if (wr64WaterTransform) {
                    FILE *traceFile = wr64WaterMeshTraceFile();
                    if (traceFile != nullptr) {
                        std::fprintf(traceFile,
                            "%llu,transform_rejected_already_mapped,%u,%u,%u,%u,%u,%llu,%u,"
                            "%u,%u,%u,%u,%u,%u,%u,%u,"
                            "%u,%u,%u,%u,%u,%u,%u,%u,"
                            "%llu,%llu,%llu,%llu,%u,%u,%u,%u\n",
                            static_cast<unsigned long long>(firstCurWorkload.submissionFrame),
                            firstCurProjIndices.workloadIndex, firstPrevProjIndices.workloadIndex, 0,
                            UINT32_MAX, UINT32_MAX, 0ULL, 0,
                            candidate.curIndex, candidate.prevIndex, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0,
                            0ULL, 0ULL, 0ULL, 0ULL, 1, 0, uint32_t(curAlreadyMapped), uint32_t(prevAlreadyMapped));
                        std::fflush(traceFile);
                    }
                }
                continue;
            }

            if (firstCurWorkloadMap.prevTransformsMapped[candidate.prevIndex]) {
                if (wr64WaterTransform) {
                    FILE *traceFile = wr64WaterMeshTraceFile();
                    if (traceFile != nullptr) {
                        std::fprintf(traceFile,
                            "%llu,transform_rejected_previous_mapped,%u,%u,%u,%u,%u,%llu,%u,"
                            "%u,%u,%u,%u,%u,%u,%u,%u,"
                            "%u,%u,%u,%u,%u,%u,%u,%u,"
                            "%llu,%llu,%llu,%llu,%u,%u,%u,%u\n",
                            static_cast<unsigned long long>(firstCurWorkload.submissionFrame),
                            firstCurProjIndices.workloadIndex, firstPrevProjIndices.workloadIndex, 0,
                            UINT32_MAX, UINT32_MAX, 0ULL, 0,
                            candidate.curIndex, candidate.prevIndex, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0,
                            0ULL, 0ULL, 0ULL, 0ULL, 1, 0, uint32_t(curAlreadyMapped), uint32_t(prevAlreadyMapped));
                        std::fflush(traceFile);
                    }
                }
                continue;
            }

            // Observation only. The inherited state has to be read here, before
            // matchTransform overwrites the current rigid body with it, and it is read
            // from the previous map, which matchTransform only reads. Nothing below is
            // written back; the census replays the AUTO decision on its own copy of
            // the numbers and writes a row when the decision flipped.
            bool wr64CensusHasPrev = false;
            bool wr64CensusPrevLerpTranslation = false;
            float wr64CensusPrevVelocity[3] = { 0.0f, 0.0f, 0.0f };
            float wr64CensusPrevPosition[3] = { 0.0f, 0.0f, 0.0f };
            float wr64CensusCurPosition[3] = { 0.0f, 0.0f, 0.0f };
            uint8_t wr64CensusPositionInterpolation = G_EX_COMPONENT_AUTO;
            if (wr64SkyCensusEnabled() && (firstPrevWorkloadMap != nullptr)) {
                const RigidBody &censusPrevBody = firstPrevWorkloadMap->transforms[candidate.prevIndex].rigidBody;
                wr64CensusPrevLerpTranslation = censusPrevBody.lerpTranslation;
                wr64CensusPrevVelocity[0] = censusPrevBody.linearVelocity.x;
                wr64CensusPrevVelocity[1] = censusPrevBody.linearVelocity.y;
                wr64CensusPrevVelocity[2] = censusPrevBody.linearVelocity.z;

                const hlslpp::float4x4 &censusPrevTransform = firstPrevWorkload.drawData.worldTransforms[candidate.prevIndex];
                const hlslpp::float4x4 &censusCurTransform = firstCurWorkload.drawData.worldTransforms[candidate.curIndex];
                const hlslpp::float3 censusPrevTranslation = censusPrevTransform[3].xyz;
                const hlslpp::float3 censusCurTranslation = censusCurTransform[3].xyz;
                wr64CensusPrevPosition[0] = censusPrevTranslation.x;
                wr64CensusPrevPosition[1] = censusPrevTranslation.y;
                wr64CensusPrevPosition[2] = censusPrevTranslation.z;
                wr64CensusCurPosition[0] = censusCurTranslation.x;
                wr64CensusCurPosition[1] = censusCurTranslation.y;
                wr64CensusCurPosition[2] = censusCurTranslation.z;

                const uint32_t censusGroupIndex = firstCurWorkload.drawData.worldTransformGroups[candidate.curIndex];
                wr64CensusPositionInterpolation = firstCurWorkload.drawData.transformGroups[censusGroupIndex].positionInterpolation;
                wr64CensusHasPrev = true;
            }

            matchTransform(firstCurWorkload, firstPrevWorkload, firstCurWorkloadMap, firstPrevWorkloadMap, candidate.curIndex, candidate.prevIndex, modifiedBuffers, wr64WaterTransform, wr64ExactSkyTransform, &firstCurViewProj, &firstPrevViewProj);

            if (wr64CensusHasPrev) {
                wr64SkyCensusObserve(firstCurWorkload.submissionFrame, candidate.curIndex, candidate.prevIndex,
                    wr64CensusPositionInterpolation, wr64CensusPrevLerpTranslation,
                    firstCurWorkloadMap.transforms[candidate.curIndex].rigidBody.lerpTranslation,
                    wr64CensusPrevVelocity, wr64CensusPrevPosition, wr64CensusCurPosition);
            }

            if (wr64WaterTransform) {
                const uint32_t curGroupIndex = firstCurWorkload.drawData.worldTransformGroups[candidate.curIndex];
                const uint32_t prevGroupIndex = firstPrevWorkload.drawData.worldTransformGroups[candidate.prevIndex];
                const TransformGroup &curGroup = firstCurWorkload.drawData.transformGroups[curGroupIndex];
                const TransformGroup &prevGroup = firstPrevWorkload.drawData.transformGroups[prevGroupIndex];
                const uint32_t curVertexIndex = firstCurWorkload.drawData.worldTransformVertexIndices[candidate.curIndex];
                const uint32_t curVertexCount = firstCurWorkload.drawData.worldTransformVertexCount(candidate.curIndex);
                const uint32_t prevVertexIndex = firstPrevWorkload.drawData.worldTransformVertexIndices[candidate.prevIndex];
                const uint32_t prevVertexCount = firstPrevWorkload.drawData.worldTransformVertexCount(candidate.prevIndex);
                uint64_t curPositionHash = 0;
                uint64_t prevPositionHash = 0;
                uint64_t curTexcoordHash = 0;
                uint64_t prevTexcoordHash = 0;
                if (curVertexCount == prevVertexCount) {
                    curPositionHash = XXH3_64bits(&firstCurWorkload.drawData.posFloats[curVertexIndex * 3], curVertexCount * 3 * sizeof(float));
                    prevPositionHash = XXH3_64bits(&firstPrevWorkload.drawData.posFloats[prevVertexIndex * 3], prevVertexCount * 3 * sizeof(float));
                    curTexcoordHash = XXH3_64bits(&firstCurWorkload.drawData.tcFloats[curVertexIndex * 2], curVertexCount * 2 * sizeof(float));
                    prevTexcoordHash = XXH3_64bits(&firstPrevWorkload.drawData.tcFloats[prevVertexIndex * 2], prevVertexCount * 2 * sizeof(float));
                }

                FILE *correspondenceTraceFile = wr64WaterCorrespondenceTraceFile();
                if (correspondenceTraceFile != nullptr) {
                    uint32_t positionChanged = 0;
                    uint32_t positionNonfinite = 0;
                    double positionMin = std::numeric_limits<double>::max();
                    double positionSum = 0.0;
                    double positionSquareSum = 0.0;
                    double positionMax = 0.0;
                    double positionAbsXMax = 0.0;
                    double positionAbsYMax = 0.0;
                    double positionAbsZMax = 0.0;
                    uint32_t texcoordChanged = 0;
                    uint32_t texcoordNonfinite = 0;
                    double texcoordMin = std::numeric_limits<double>::max();
                    double texcoordSum = 0.0;
                    double texcoordSquareSum = 0.0;
                    double texcoordMax = 0.0;

                    if ((curVertexCount == prevVertexCount) && (curVertexCount > 0)) {
                        const float *curPositions = &firstCurWorkload.drawData.posFloats[curVertexIndex * 3];
                        const float *prevPositions = &firstPrevWorkload.drawData.posFloats[prevVertexIndex * 3];
                        const float *curTexcoords = &firstCurWorkload.drawData.tcFloats[curVertexIndex * 2];
                        const float *prevTexcoords = &firstPrevWorkload.drawData.tcFloats[prevVertexIndex * 2];
                        const hlslpp::float2 wrappingModulo = firstCurWorkload.extended.texcoordWrapPoint;
                        const hlslpp::float2 wrappingModuloHalf = wrappingModulo / 2.0f;

                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            const double dx = double(curPositions[i * 3 + 0]) - double(prevPositions[i * 3 + 0]);
                            const double dy = double(curPositions[i * 3 + 1]) - double(prevPositions[i * 3 + 1]);
                            const double dz = double(curPositions[i * 3 + 2]) - double(prevPositions[i * 3 + 2]);
                            const double distance = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
                            if (std::isfinite(distance)) {
                                positionChanged += uint32_t(distance > 1.0e-6);
                                positionMin = std::min(positionMin, distance);
                                positionSum += distance;
                                positionSquareSum += distance * distance;
                                positionMax = std::max(positionMax, distance);
                                positionAbsXMax = std::max(positionAbsXMax, std::abs(dx));
                                positionAbsYMax = std::max(positionAbsYMax, std::abs(dy));
                                positionAbsZMax = std::max(positionAbsZMax, std::abs(dz));
                            }
                            else {
                                positionNonfinite++;
                            }

                            double ds = double(curTexcoords[i * 2 + 0]) - double(prevTexcoords[i * 2 + 0]);
                            double dt = double(curTexcoords[i * 2 + 1]) - double(prevTexcoords[i * 2 + 1]);
                            if ((wrappingModulo[0] != 0.0f) && (std::abs(ds) > double(wrappingModuloHalf[0]))) {
                                ds -= std::round(ds / double(wrappingModulo[0])) * double(wrappingModulo[0]);
                            }
                            if ((wrappingModulo[1] != 0.0f) && (std::abs(dt) > double(wrappingModuloHalf[1]))) {
                                dt -= std::round(dt / double(wrappingModulo[1])) * double(wrappingModulo[1]);
                            }

                            const double texcoordDistance = std::sqrt((ds * ds) + (dt * dt));
                            if (std::isfinite(texcoordDistance)) {
                                texcoordChanged += uint32_t(texcoordDistance > 1.0e-6);
                                texcoordMin = std::min(texcoordMin, texcoordDistance);
                                texcoordSum += texcoordDistance;
                                texcoordSquareSum += texcoordDistance * texcoordDistance;
                                texcoordMax = std::max(texcoordMax, texcoordDistance);
                            }
                            else {
                                texcoordNonfinite++;
                            }
                        }
                    }

                    const uint32_t finitePositionCount = curVertexCount - std::min(curVertexCount, positionNonfinite);
                    const uint32_t finiteTexcoordCount = curVertexCount - std::min(curVertexCount, texcoordNonfinite);
                    if (finitePositionCount == 0) {
                        positionMin = 0.0;
                    }
                    if (finiteTexcoordCount == 0) {
                        texcoordMin = 0.0;
                    }
                    const double positionAverage = (finitePositionCount > 0) ? (positionSum / double(finitePositionCount)) : 0.0;
                    const double positionRms = (finitePositionCount > 0) ? std::sqrt(positionSquareSum / double(finitePositionCount)) : 0.0;
                    const double texcoordAverage = (finiteTexcoordCount > 0) ? (texcoordSum / double(finiteTexcoordCount)) : 0.0;
                    const double texcoordRms = (finiteTexcoordCount > 0) ? std::sqrt(texcoordSquareSum / double(finiteTexcoordCount)) : 0.0;

                    std::fprintf(correspondenceTraceFile,
                        "%llu,transform_displacement,%u,%u,%u,%u,"
                        "%u,%u,%u,%u,%u,"
                        "%u,%u,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,"
                        "%u,%u,%.9g,%.9g,%.9g,%.9g,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%llu,%llu,%llu,%llu,%u\n",
                        static_cast<unsigned long long>(firstCurWorkload.submissionFrame),
                        firstCurProjIndices.workloadIndex, firstPrevProjIndices.workloadIndex,
                        UINT32_MAX, UINT32_MAX,
                        candidate.curIndex, candidate.prevIndex,
                        curVertexIndex, prevVertexIndex, (curVertexCount == prevVertexCount) ? curVertexCount : 0,
                        positionChanged, positionNonfinite,
                        positionMin, positionAverage, positionRms, positionMax,
                        positionAbsXMax, positionAbsYMax, positionAbsZMax,
                        texcoordChanged, texcoordNonfinite,
                        texcoordMin, texcoordAverage, texcoordRms, texcoordMax,
                        0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0ULL, 0ULL, 0ULL, 0ULL, 0);
                    std::fflush(correspondenceTraceFile);
                }

                FILE *traceFile = wr64WaterMeshTraceFile();
                if (traceFile != nullptr) {
                    std::fprintf(traceFile,
                        "%llu,transform_accepted,%u,%u,%u,%u,%u,%llu,%u,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%u,%u,%u,%u,%u,%u,%u,%u,"
                        "%llu,%llu,%llu,%llu,%u,%u,%u,%u\n",
                        static_cast<unsigned long long>(firstCurWorkload.submissionFrame),
                        firstCurProjIndices.workloadIndex, firstPrevProjIndices.workloadIndex, 0,
                        UINT32_MAX, UINT32_MAX, 0ULL, 0,
                        candidate.curIndex, candidate.prevIndex, curGroupIndex, prevGroupIndex, curGroup.matrixId, prevGroup.matrixId,
                        0, 0,
                        curVertexIndex, curVertexCount, prevVertexIndex, prevVertexCount,
                        curGroup.vertexInterpolation, curGroup.texcoordInterpolation, curGroup.tileInterpolation, uint32_t(curGroup.decompose),
                        static_cast<unsigned long long>(curPositionHash), static_cast<unsigned long long>(prevPositionHash),
                        static_cast<unsigned long long>(curTexcoordHash), static_cast<unsigned long long>(prevTexcoordHash),
                        1, 1, uint32_t(curAlreadyMapped), uint32_t(prevAlreadyMapped));
                    std::fflush(traceFile);
                }
            }
        }

        // Identify the sky draw by render signature and inspect its own face indices.
        // This diagnostic is inert unless WR64_SKY_BRACKET is enabled; correction also
        // requires WR64_SKY_BRACKET_HOLD and a measured violation.
        wr64SkyBracketEvaluate(workloadQueue, curScene, prevScene, firstCurWorkloadMap, modifiedBuffers);

        if (!modifiedBuffers.empty()) {
            workloadsModified[firstCurProjIndices.workloadIndex].merge(modifiedBuffers);
        }

        // Check for tile matches.
        for (const IndexPair &indices : tileCheckSet) {
            if (firstCurWorkloadMap.tiles[indices.first].mapped) {
                continue;
            }

            if (firstCurWorkloadMap.prevTilesMapped[indices.second]) {
                continue;
            }

            // Check for tile compatibility.
            const interop::RDPTile &curTile = firstCurWorkload.drawData.rdpTiles[indices.first];
            const interop::RDPTile &prevTile = firstPrevWorkload.drawData.rdpTiles[indices.second];
            if ((curTile.fmt != prevTile.fmt) ||
                (curTile.siz != prevTile.siz) ||
                (curTile.stride != prevTile.stride) ||
                (curTile.masks != prevTile.masks) ||
                (curTile.maskt != prevTile.maskt) ||
                (curTile.shifts != prevTile.shifts) ||
                (curTile.shiftt != prevTile.shiftt) ||
                (curTile.cms != prevTile.cms) ||
                (curTile.cmt != prevTile.cmt))
            {
                continue;
            }

            GameFrameMap::TileMap &curTileMap = firstCurWorkloadMap.tiles[indices.first];
            if (firstPrevWorkloadMap != nullptr) {
                const GameFrameMap::TileMap &prevTileMap = firstPrevWorkloadMap->tiles[indices.second];
                curTileMap = prevTileMap;
            }
            
            auto modulo = [](int a, int b) {
                if (b != 0) {
                    int r = a % b;
                    return r < 0 ? r + b : r;
                }
                else {
                    return a;
                }
            };

            const float deltaUls = curTile.uls - prevTile.uls;
            const float deltaUlt = curTile.ult - prevTile.ult;
            const float deltaLrs = curTile.lrs - prevTile.lrs;
            const float deltaLrt = curTile.lrt - prevTile.lrt;
            const bool tileScrolled = (deltaUls != 0.0f) || (deltaUlt != 0.0f) || (deltaLrs != 0.0f) || (deltaLrt != 0.0f);
            const int integerUls = std::lround(curTile.uls);
            const int integerUlt = std::lround(curTile.ult);
            const int integerLrs = std::lround(curTile.lrs);
            const int integerLrt = std::lround(curTile.lrt);
            const int expectedUls = std::lround(prevTile.uls + curTileMap.deltaUls);
            const int expectedUlt = std::lround(prevTile.ult + curTileMap.deltaUlt);
            const int expectedLrs = std::lround(prevTile.lrs + curTileMap.deltaLrs);
            const int expectedLrt = std::lround(prevTile.lrt + curTileMap.deltaLrt);
            const bool wrappedUls = (curTile.cms == G_TX_WRAP) && (modulo(integerUls, curTile.masks * 4) == modulo(expectedUls, curTile.masks * 4));
            const bool wrappedUlt = (curTile.cmt == G_TX_WRAP) && (modulo(integerUlt, curTile.maskt * 4) == modulo(expectedUlt, curTile.maskt * 4));
            const bool wrappedLrs = (curTile.cms == G_TX_WRAP) && (modulo(integerLrs, curTile.masks * 4) == modulo(expectedLrs, curTile.masks * 4));
            const bool wrappedLrt = (curTile.cmt == G_TX_WRAP) && (modulo(integerLrt, curTile.maskt * 4) == modulo(expectedLrt, curTile.maskt * 4));
            curTileMap.prevUls = curTile.uls - curTileMap.deltaUls;
            curTileMap.prevUlt = curTile.ult - curTileMap.deltaUlt;
            curTileMap.prevLrs = curTile.lrs - curTileMap.deltaLrs;
            curTileMap.prevLrt = curTile.lrt - curTileMap.deltaLrt;
            curTileMap.deltaUls = wrappedUls || (abs(deltaUls) >= curTile.masks * 2) ? curTileMap.deltaUls : deltaUls;
            curTileMap.deltaUlt = wrappedUlt || (abs(deltaUlt) >= curTile.maskt * 2) ? curTileMap.deltaUlt : deltaUlt;
            curTileMap.deltaLrs = wrappedLrs || (abs(deltaLrs) >= curTile.masks * 2) ? curTileMap.deltaLrs : deltaLrs;
            curTileMap.deltaLrt = wrappedLrt || (abs(deltaLrt) >= curTile.maskt * 2) ? curTileMap.deltaLrt : deltaLrt;
            curTileMap.mapped = true;
            firstCurWorkloadMap.prevTilesMapped[indices.second] = true;
            tileInterpolationUsed = tileInterpolationUsed || tileScrolled;
        }

        // Check for look at matches.
        for (const IndexPair &indices : lookAtCheckSet) {
            if (firstCurWorkloadMap.lookAt[indices.first].mapped) {
                continue;
            }

            if (firstCurWorkloadMap.prevLookAtMapped[indices.second]) {
                continue;
            }

            GameFrameMap::LookAtMap &curLookAtMap = firstCurWorkloadMap.lookAt[indices.first];
            if (firstPrevWorkloadMap != nullptr) {
                const GameFrameMap::LookAtMap &prevLookAtMap = firstPrevWorkloadMap->lookAt[indices.second];
                curLookAtMap = prevLookAtMap;
            }

            const interop::RSPLookAt &curLookAt = firstCurWorkload.drawData.rspLookAt[indices.first];
            const interop::RSPLookAt &prevLookAt = firstPrevWorkload.drawData.rspLookAt[indices.second];
            bool lookAtMoved = true;
            curLookAtMap.mapped = true;
            curLookAtMap.deltaX = hlslpp::float3(curLookAt.x) - hlslpp::float3(prevLookAt.x);
            curLookAtMap.deltaY = hlslpp::float3(curLookAt.y) - hlslpp::float3(prevLookAt.y);
            firstCurWorkloadMap.prevLookAtMapped[indices.second] = true;
            lookAtInterpolationUsed = lookAtInterpolationUsed || lookAtMoved;
        }
    }

    void GameFrame::matchTransform(Workload &curWorkload, const Workload &prevWorkload, GameFrameMap::WorkloadMap &curWorkloadMap, const GameFrameMap::WorkloadMap *prevWorkloadMap, uint32_t curTransformIndex, uint32_t prevTransformIndex, ModifiedBuffers &modifiedBuffers, bool forceGeneratedVertexInterpolation, bool protectExactSkyChartCut, const hlslpp::float4x4 *curViewProj, const hlslpp::float4x4 *prevViewProj) {
        GameFrameMap::TransformMap &curTransformMap = curWorkloadMap.transforms[curTransformIndex];
        if (prevWorkloadMap != nullptr) {
            curTransformMap.rigidBody = prevWorkloadMap->transforms[prevTransformIndex].rigidBody;
        }

        const hlslpp::float4x4 &curTransform = curWorkload.drawData.worldTransforms[curTransformIndex];
        const hlslpp::float4x4 &prevTransform = prevWorkload.drawData.worldTransforms[prevTransformIndex];
        const uint32_t curGroupIndex = curWorkload.drawData.worldTransformGroups[curTransformIndex];
        const TransformGroup &curGroup = curWorkload.drawData.transformGroups[curGroupIndex];
        const uint8_t vertexInterpolation = forceGeneratedVertexInterpolation ? G_EX_COMPONENT_INTERPOLATE : curGroup.vertexInterpolation;
        const uint8_t texcoordInterpolation = forceGeneratedVertexInterpolation ? G_EX_COMPONENT_INTERPOLATE : curGroup.texcoordInterpolation;
        // LERPGATE-R1 measurement. updateLinear overwrites linearVelocity, so the
        // previous frame's value has to be taken before the call for the ratio
        // term to mean anything. Records nothing unless WR64_LERPGATE_TRACE is set
        // and the AUTO guard actually switched translation interpolation off.
        const hlslpp::float3 wr64LerpGatePrevVelocity = curTransformMap.rigidBody.linearVelocity;
        curTransformMap.rigidBody.updateLinear(prevTransform, curTransform, curGroup.positionInterpolation);
        wr64LerpGateRecord(curWorkload.submissionFrame, curTransformIndex, curGroup.positionInterpolation,
            wr64LerpGatePrevVelocity, prevTransform, curTransform, curTransformMap.rigidBody.lerpTranslation);
        curTransformMap.rigidBody.updateAngular(prevTransform, curTransform, curGroup.rotationInterpolation, curGroup.scaleInterpolation, curGroup.skewInterpolation);

                curTransformMap.rigidBody.updatePerspective(prevTransform, curTransform, curGroup.perspectiveInterpolation);
        curTransformMap.rigidBody.updateDecomposition(curTransform, curGroup.decompose);
        curTransformMap.prevTransformIndex = prevTransformIndex;
        curTransformMap.mapped = true;
        curWorkloadMap.prevTransformsMapped[prevTransformIndex] = true;

        uint64_t curVertexHash = 0;
        uint64_t prevVertexHash = 0;
        bool wr64PositionVelocityWritten = false;
        uint32_t curVertexIndex = curWorkload.drawData.worldTransformVertexIndices[curTransformIndex];
        uint32_t curVertexCount = curWorkload.drawData.worldTransformVertexCount(curTransformIndex);
        uint32_t prevVertexIndex = prevWorkload.drawData.worldTransformVertexIndices[prevTransformIndex];
        uint32_t prevVertexCount = prevWorkload.drawData.worldTransformVertexCount(prevTransformIndex);
        std::vector<float> wr64PreviousSurfaceHeight;
        std::vector<uint8_t> wr64PreviousSurfaceHeightValid;
        std::vector<float> wr64PreviousSurfaceU;
        std::vector<float> wr64PreviousSurfaceV;
        bool wr64PreviousSurfaceTexcoordValid = false;
        // Marks which vertices of this transform actually came out of the
        // graphics pool, i.e. which ones are the water surface.
        //
        // A transform's vertex range is not the same thing as a draw call's
        // vertex range. The water call selects this transform, but anything
        // else drawn under the same world matrix shares the range. Without
        // this mask the water rules below were applied to that geometry too,
        // which zeroed its velocity and dropped it to native cadence for no
        // reason. Everything that is not the water surface keeps stock RT64
        // behaviour.
        std::vector<uint8_t> wr64GeneratedVertex;

        // WATERLOCK-R1. How far the camera travelled over this native frame,
        // expressed in the water transform's own space. Zero unless it is
        // recovered and passes the plausibility test below, in which case every
        // water vertex is rewound by it during the interpolated frames.
        float wr64SheetShiftX = 0.0f;
        float wr64SheetShiftZ = 0.0f;
        std::vector<float> wr64SheetShiftWeight;
        std::vector<float> wr64SheetQueryWeight;
        std::vector<uint8_t> wr64LatticeVertexOuter;
        const bool wr64CoherentFanStrip =
            wr64WaterCoherentFanStripEnabled();
        std::vector<uint8_t> wr64CoherentFanInnerVertex;
        bool wr64CoherentFanSlotValid = false;
        float wr64CoherentFanSlotDeltaX = 0.0f;
        float wr64CoherentFanSlotDeltaZ = 0.0f;
        // Diagnostic candidate: keep the six flat outer coverage vertices on
        // the same presentation endpoint as the 494 dense/bridge vertices.
        // The stock slot delta currently moves only those six vertices while
        // the connected inner edge is pinned, shearing the final 12 triangles
        // at fractional presentation weights. Environment-gated until both
        // geometry coverage and independent video continuity checks pass.
        const bool wr64CoherentOuterCoverage = []() {
            const char *value = std::getenv("WR64_WATER_COHERENT_OUTER");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        // Rejected rigid-bridge experiment. Keep it available only as an
        // explicit diagnostic; it must not silently replace the baseline or
        // the ripple-bridge candidate because it opens a fractional seam at
        // the duplicated inner edge.
        const bool wr64RigidBridgeCorrection = []() {
            const char *value = std::getenv("WR64_WATER_RIGID_BRIDGE");
            return (value != nullptr) && (value[0] != '\0') &&
                (value[0] != '0');
        }();
        uint32_t wr64ExactHits = 0;
        uint32_t wr64ProbeLattice = 0;
        uint32_t wr64ProbeSkirt = 0;
        double wr64ProbeSpacing = 0.0;
        // WATERLOCK-R6 probe carriers: what the CAMERA is doing during the
        // interpolated frames, which is now the thing under suspicion.
        int wr64CamMapped = -1;
        int wr64CamLerpTranslation = -1;
        int wr64CamLerpRotation = -1;
        double wr64CamProjectionDelta = -1.0;
        float wr64ProbeCameraX = 0.0f;
        float wr64ProbeCameraY = 0.0f;
        float wr64ProbeCameraZ = 0.0f;
        float wr64CameraLocalX = 0.0f;
        float wr64CameraLocalZ = 0.0f;
        bool wr64CameraLocalValid = false;
        if (forceGeneratedVertexInterpolation && (curVertexCount == prevVertexCount) && (curVertexCount > 0)) {
            wr64PreviousSurfaceHeight.assign(curVertexCount, 0.0f);
            wr64PreviousSurfaceHeightValid.assign(curVertexCount, 0);
            wr64PreviousSurfaceU.assign(curVertexCount, 0.0f);
            wr64PreviousSurfaceV.assign(curVertexCount, 0.0f);
            wr64SheetShiftWeight.assign(curVertexCount, 0.0f);
            wr64SheetQueryWeight.assign(curVertexCount, 0.0f);
            wr64GeneratedVertex.assign(curVertexCount, 0);
            const std::vector<uint32_t> &curAddresses = curWorkload.drawData.vertexSegmentedAddresses;
            const std::vector<uint32_t> &prevAddresses = prevWorkload.drawData.vertexSegmentedAddresses;
            const bool addressRangesValid =
                ((uint64_t(curVertexIndex) + curVertexCount) <= curAddresses.size()) &&
                ((uint64_t(prevVertexIndex) + prevVertexCount) <= prevAddresses.size());

            if (addressRangesValid) {
                for (uint32_t i = 0; i < curVertexCount; i++) {
                    wr64GeneratedVertex[i] =
                        isWr64GeneratedWaterVertexAddress(curAddresses[curVertexIndex + i]) ? 1 : 0;
                }

                // The water surface is a height field that the producer rebuilds
                // and recenters every native frame. Vertex identity is not
                // preserved across frames, and every attempt to interpolate this
                // mesh by pairing vertices has torn it: a wrong pairing moves a
                // vertex sideways, which opens seams, shears strips and detaches
                // triangles.
                //
                // So no vertex is ever paired for position. The previous surface
                // is treated as what it is -- a height field over local X/Z --
                // and is resampled at each current vertex's own X/Z. Only Y is
                // ever written; X and Z velocity stay exactly zero, so a vertex
                // cannot move laterally and the tearing failure mode is
                // structurally impossible rather than merely avoided.
                //
                // The resampling assumes nothing about how the sheet is laid
                // out. A previous version reconstructed an axis-aligned lattice
                // from the sample coordinates and sampled it bilinearly, which
                // is only valid if the grid really is axis aligned and perfectly
                // regular in local space. When it is not, the recovered cell
                // size collapses to the coordinate jitter, every lookup misses,
                // no previous height is recovered, and the whole sheet silently
                // holds -- water frozen at native cadence, indistinguishable
                // from interpolation being switched off.
                //
                // This version bins the previous samples into a uniform spatial
                // hash sized from their own measured spacing, then blends the
                // samples within one spacing of the query point using a
                // compactly supported inverse-distance kernel. It reproduces a
                // sample's height exactly where a previous sample coincides with
                // a current one, is continuous everywhere else so it cannot
                // facet or shimmer, and is indifferent to grid orientation,
                // spacing changes, duplicated strip vertices and irregular rows.
                const float *curPositions =
                    &curWorkload.drawData.posFloats[curVertexIndex * 3];
                const float *prevPositions =
                    &prevWorkload.drawData.posFloats[prevVertexIndex * 3];

                // Texcoords are optional here: if the ranges do not line up the
                // sampler still recovers heights and the UVs simply hold, which
                // is the behaviour this build replaces.
                const bool wr64TexcoordRangesValid =
                    (((uint64_t(curVertexIndex) + curVertexCount) * 2ULL) <= curWorkload.drawData.tcFloats.size()) &&
                    (((uint64_t(prevVertexIndex) + prevVertexCount) * 2ULL) <= prevWorkload.drawData.tcFloats.size());
                const float *curTexcoords = wr64TexcoordRangesValid
                    ? &curWorkload.drawData.tcFloats[curVertexIndex * 2] : nullptr;
                const float *prevTexcoords = wr64TexcoordRangesValid
                    ? &prevWorkload.drawData.tcFloats[prevVertexIndex * 2] : nullptr;
                wr64PreviousSurfaceTexcoordValid = wr64TexcoordRangesValid;
                (void)curTexcoords;

                // WATERLOCK-R3. The sheet now rewinds with the camera, so its
                // texture has to be resampled at the rewound point exactly like
                // its height. Holding the UVs while the sheet moves nails the
                // water texture to the camera: it sits still on screen for every
                // interpolated frame and jumps once per native frame, which is
                // the water reading as though nothing is interpolating at all.
                // Almost everything the eye tracks on this surface is the
                // texture, not the vertex heights.
                struct SurfaceSample {
                    float x;
                    float z;
                    float height;
                    float u;
                    float v;
                };

                std::vector<SurfaceSample> previousSamples;
                previousSamples.reserve(prevVertexCount);
                for (uint32_t j = 0; j < prevVertexCount; j++) {
                    if (!isWr64GeneratedWaterVertexAddress(prevAddresses[prevVertexIndex + j])) {
                        continue;
                    }

                    previousSamples.push_back(SurfaceSample{
                        prevPositions[j * 3 + 0],
                        prevPositions[j * 3 + 2],
                        prevPositions[j * 3 + 1],
                        (prevTexcoords != nullptr) ? prevTexcoords[j * 2 + 0] : 0.0f,
                        (prevTexcoords != nullptr) ? prevTexcoords[j * 2 + 1] : 0.0f });
                }

                if (previousSamples.size() >= 4) {
                    double minimumX = std::numeric_limits<double>::max();
                    double maximumX = std::numeric_limits<double>::lowest();
                    double minimumZ = std::numeric_limits<double>::max();
                    double maximumZ = std::numeric_limits<double>::lowest();
                    for (const SurfaceSample &sample : previousSamples) {
                        minimumX = std::min(minimumX, double(sample.x));
                        maximumX = std::max(maximumX, double(sample.x));
                        minimumZ = std::min(minimumZ, double(sample.z));
                        maximumZ = std::max(maximumZ, double(sample.z));
                    }

                    // Mean spacing of a roughly uniform point set is the square
                    // root of its area per sample. This holds for any
                    // orientation and needs no sorting, so coordinate jitter
                    // cannot collapse it the way a minimum-gap estimate can.
                    const double spanX = maximumX - minimumX;
                    const double spanZ = maximumZ - minimumZ;
                    const double sampleArea =
                        std::max(spanX * spanZ, 1.0e-9) / double(previousSamples.size());
                    const double spacing = std::sqrt(sampleArea);

                    // Rewind the finite water sheet with the interpolated camera. Leaving it at the
                    // current native position exposes its trailing edge while the camera retreats.
                    // The sheet's displacement is quantized to a 64-unit lattice, so use continuous
                    // camera translation instead of the sheet's cell-to-cell movement. The optional
                    // WATERLOCK diagnostic is limited to forty rows.
                    static uint32_t wr64ProbeCount = 0;
                    const bool wr64Probe = WR64_DIAGNOSTIC_ENABLED && (wr64ProbeCount < 40);
                    if (wr64Probe) {
                        wr64ProbeCount++;
                        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[waterlock] f=%llu enter verts=%u samples=%u\n",
                            static_cast<unsigned long long>(curWorkload.submissionFrame),
                            curVertexCount, uint32_t(previousSamples.size())); }
                        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
                    }

                    float wr64CameraShiftX = 0.0f;
                    float wr64CameraShiftZ = 0.0f;
                    bool wr64CameraShiftValid = false;
                    {
                        uint32_t wr64WaterVertex = curVertexCount;
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((i < wr64GeneratedVertex.size()) && (wr64GeneratedVertex[i] != 0)) {
                                wr64WaterVertex = i;
                                break;
                            }
                        }

                        const std::vector<uint16_t> &wr64CurViewProjIndices =
                            curWorkload.drawData.viewProjIndices;
                        if ((wr64WaterVertex < curVertexCount) &&
                            ((uint64_t(curVertexIndex) + wr64WaterVertex) < wr64CurViewProjIndices.size()))
                        {
                            const uint32_t wr64CurViewProjIndex =
                                wr64CurViewProjIndices[curVertexIndex + wr64WaterVertex];
                            if ((wr64CurViewProjIndex < curWorkloadMap.viewProjections.size()) &&
                                (wr64CurViewProjIndex < curWorkload.drawData.viewTransforms.size()))
                            {
                                // The projection pairing is decided earlier in
                                // matchScene, so it is already populated here.
                                // If it did not map, the same index is the right
                                // guess: the scene's projection list is rebuilt
                                // identically every frame.
                                const GameFrameMap::ViewProjectionMap &wr64ViewProjMap =
                                    curWorkloadMap.viewProjections[wr64CurViewProjIndex];
                                const uint32_t wr64PrevViewProjIndex = wr64ViewProjMap.mapped
                                    ? wr64ViewProjMap.prevTransformIndex
                                    : wr64CurViewProjIndex;
                                wr64CamMapped = wr64ViewProjMap.mapped ? 1 : 0;
                                wr64CamLerpTranslation = wr64ViewProjMap.rigidBody.lerpTranslation ? 1 : 0;
                                wr64CamLerpRotation = wr64ViewProjMap.rigidBody.lerpRotation ? 1 : 0;
                                if ((wr64CurViewProjIndex < curWorkload.drawData.projTransforms.size()) &&
                                    (wr64PrevViewProjIndex < prevWorkload.drawData.projTransforms.size()))
                                {
                                    const hlslpp::float4x4 &curProj =
                                        curWorkload.drawData.projTransforms[wr64CurViewProjIndex];
                                    const hlslpp::float4x4 &prevProj =
                                        prevWorkload.drawData.projTransforms[wr64PrevViewProjIndex];
                                    double projectionDelta = 0.0;
                                    for (uint32_t r = 0; r < 4; r++) {
                                        const hlslpp::float4 curRow = curProj[r];
                                        const hlslpp::float4 prevRow = prevProj[r];
                                        projectionDelta = std::max(projectionDelta, std::fabs(double(curRow.x) - double(prevRow.x)));
                                        projectionDelta = std::max(projectionDelta, std::fabs(double(curRow.y) - double(prevRow.y)));
                                        projectionDelta = std::max(projectionDelta, std::fabs(double(curRow.z) - double(prevRow.z)));
                                        projectionDelta = std::max(projectionDelta, std::fabs(double(curRow.w) - double(prevRow.w)));
                                    }

                                    wr64CamProjectionDelta = projectionDelta;
                                }

                                if (wr64PrevViewProjIndex < prevWorkload.drawData.viewTransforms.size()) {
                                    const hlslpp::float4x4 &wr64CurView =
                                        curWorkload.drawData.viewTransforms[wr64CurViewProjIndex];
                                    const hlslpp::float4x4 &wr64PrevView =
                                        prevWorkload.drawData.viewTransforms[wr64PrevViewProjIndex];

                                    // Row vector convention, so the camera's
                                    // world position is row 3 of the inverted
                                    // view matrix.
                                    const hlslpp::float4x4 wr64CurViewInverse = hlslpp::inverse(wr64CurView);
                                    const hlslpp::float4x4 wr64PrevViewInverse = hlslpp::inverse(wr64PrevView);
                                    const hlslpp::float3 wr64CurCamera = wr64CurViewInverse[3].xyz;
                                    wr64ProbeCameraX = float(wr64CurCamera.x);
                                    wr64ProbeCameraY = float(wr64CurCamera.y);
                                    wr64ProbeCameraZ = float(wr64CurCamera.z);
                                    const hlslpp::float3 wr64PrevCamera = wr64PrevViewInverse[3].xyz;
                                    const hlslpp::float3 wr64CurCameraLocal = hlslpp::mul(
                                        hlslpp::float4(wr64CurCamera, 1.0f),
                                        hlslpp::inverse(curTransform)).xyz;
                                    wr64CameraLocalX = float(wr64CurCameraLocal.x);
                                    wr64CameraLocalZ = float(wr64CurCameraLocal.z);
                                    wr64CameraLocalValid = true;

                                    // Height field, so only the horizontal part
                                    // of the camera's travel moves the sheet.
                                    // Carried into the transform's own space as a
                                    // direction, which is a no-op while the water
                                    // matrix stays the identity and correct if it
                                    // ever stops being one.
                                    const hlslpp::float4 wr64WorldShift(
                                        float(wr64CurCamera.x) - float(wr64PrevCamera.x),
                                        0.0f,
                                        float(wr64CurCamera.z) - float(wr64PrevCamera.z),
                                        0.0f);
                                    const hlslpp::float4 wr64LocalShift =
                                        hlslpp::mul(wr64WorldShift, hlslpp::inverse(curTransform));
                                    const float wr64ShiftX = float(wr64LocalShift.x);
                                    const float wr64ShiftZ = float(wr64LocalShift.z);

                                    // A camera cut, a respawn or a bad pairing
                                    // would hand back a shift the size of the
                                    // course. Anything past a quarter of the
                                    // sheet's own span is not travel, so it is
                                    // discarded and the sheet stays pinned for
                                    // that frame -- the behaviour this build
                                    // replaces, kept as the failure mode.
                                    const double wr64ShiftLimit = 0.25 * std::max(spanX, spanZ);
                                    if (std::isfinite(wr64ShiftX) && std::isfinite(wr64ShiftZ) &&
                                        (std::fabs(double(wr64ShiftX)) <= wr64ShiftLimit) &&
                                        (std::fabs(double(wr64ShiftZ)) <= wr64ShiftLimit))
                                    {
                                        wr64CameraShiftX = wr64ShiftX;
                                        wr64CameraShiftZ = wr64ShiftZ;
                                        wr64CameraShiftValid = true;
                                    }
                                }
                            }
                        }
                    }

                    if (wr64CameraShiftValid) {
                        wr64SheetShiftX = wr64CameraShiftX;
                        wr64SheetShiftZ = wr64CameraShiftZ;
                    }

                    // The stock bridge has six private inner corners followed
                    // by six producerless outer corners. The water path pins
                    // the inner X/Z to the primary field, while stock RT64
                    // interpolates the outer six by their common slot delta.
                    // That disagreement shears the fan on every fractional
                    // presentation and resets at the next native frame. Recover
                    // the one exact outer delta here and prove the full topology
                    // before this env-gated candidate is allowed to use it.
                    if (wr64CoherentFanStrip) {
                        wr64CoherentFanInnerVertex.assign(curVertexCount, 0);
                        std::vector<uint8_t> primaryIncidence(curVertexCount, 0);
                        std::vector<uint8_t> bridgeIncidence(curVertexCount, 0);
                        const std::vector<uint32_t> &waterFaces =
                            curWorkload.drawData.wr64WaterFaceIndices;
                        uint32_t stockTriangles = 0;
                        for (size_t f = 0;
                            ((f + 2) < waterFaces.size()) &&
                            (stockTriangles < 876U); f += 3, stockTriangles++)
                        {
                            const uint32_t tri[3] = { waterFaces[f + 0],
                                waterFaces[f + 1], waterFaces[f + 2] };
                            for (uint32_t corner = 0; corner < 3; corner++) {
                                const uint32_t global = tri[corner];
                                if ((global < curVertexIndex) ||
                                    (global >= (curVertexIndex + curVertexCount)))
                                {
                                    continue;
                                }
                                std::vector<uint8_t> &incidence =
                                    (stockTriangles < 864U) ?
                                    primaryIncidence : bridgeIncidence;
                                incidence[global - curVertexIndex] = 1;
                            }
                        }

                        const std::vector<uint32_t> &producerKeys =
                            curWorkload.drawData.wr64WaterProducerKeys;
                        const std::vector<uint8_t> &patchMask =
                            curWorkload.drawData.wr64WaterVertexMask;
                        const std::vector<uint32_t> &fieldInfo =
                            curWorkload.drawData.wr64WaterFieldInfo;
                        bool invariant = (stockTriangles == 876U) &&
                            (producerKeys.size() ==
                                curWorkload.drawData.vertexCount()) &&
                            (patchMask.size() ==
                                curWorkload.drawData.vertexCount()) &&
                            (fieldInfo.size() >=
                                (size_t(curWorkload.drawData.vertexCount()) *
                                    4ULL));
                        bool outerDeltaSet = false;
                        uint32_t primaryVertices = 0;
                        uint32_t innerVertices = 0;
                        uint32_t outerVertices = 0;
                        uint32_t innerPrimaryMatches = 0;
                        uint32_t innerStripMatches = 0;
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if (primaryIncidence[i] != 0) primaryVertices++;
                            if ((bridgeIncidence[i] == 0) ||
                                (primaryIncidence[i] != 0))
                            {
                                continue;
                            }
                            const uint32_t global = curVertexIndex + i;
                            if (global >= producerKeys.size()) {
                                invariant = false;
                                continue;
                            }
                            const uint32_t key = producerKeys[global];
                            if (key == 0U) {
                                outerVertices++;
                                const float deltaX = curPositions[i * 3 + 0] -
                                    prevPositions[i * 3 + 0];
                                const float deltaZ = curPositions[i * 3 + 2] -
                                    prevPositions[i * 3 + 2];
                                if (!std::isfinite(deltaX) ||
                                    !std::isfinite(deltaZ))
                                {
                                    invariant = false;
                                }
                                else if (!outerDeltaSet) {
                                    wr64CoherentFanSlotDeltaX = deltaX;
                                    wr64CoherentFanSlotDeltaZ = deltaZ;
                                    outerDeltaSet = true;
                                }
                                else if ((wr64FloatBits(deltaX) !=
                                        wr64FloatBits(
                                            wr64CoherentFanSlotDeltaX)) ||
                                    (wr64FloatBits(deltaZ) !=
                                        wr64FloatBits(
                                            wr64CoherentFanSlotDeltaZ)))
                                {
                                    invariant = false;
                                }
                                continue;
                            }

                            innerVertices++;
                            wr64CoherentFanInnerVertex[i] = 1;
                            bool primaryMatch = false;
                            for (uint32_t candidate = 0;
                                candidate < curVertexCount; candidate++)
                            {
                                if (primaryIncidence[candidate] == 0) continue;
                                const uint32_t candidateGlobal =
                                    curVertexIndex + candidate;
                                if ((candidateGlobal >= producerKeys.size()) ||
                                    (producerKeys[candidateGlobal] != key))
                                {
                                    continue;
                                }
                                primaryMatch =
                                    (wr64FloatBits(curPositions[i * 3 + 0]) ==
                                        wr64FloatBits(curPositions[
                                            candidate * 3 + 0])) &&
                                    (wr64FloatBits(curPositions[i * 3 + 2]) ==
                                        wr64FloatBits(curPositions[
                                            candidate * 3 + 2]));
                                if (primaryMatch) break;
                            }
                            if (primaryMatch) innerPrimaryMatches++;
                            else invariant = false;

                            bool stripMatch = false;
                            for (uint32_t patch = 0;
                                patch < patchMask.size(); patch++)
                            {
                                if ((patchMask[patch] != 3U) ||
                                    ((uint64_t(patch) + 1ULL) * 4ULL >
                                        fieldInfo.size()))
                                {
                                    continue;
                                }
                                const uint32_t infoOffset = patch * 4U;
                                const uint32_t source =
                                    fieldInfo[infoOffset + 1U];
                                if ((source < producerKeys.size()) &&
                                    (producerKeys[source] == key))
                                {
                                    stripMatch = true;
                                    break;
                                }
                            }
                            if (stripMatch) innerStripMatches++;
                            else invariant = false;
                        }
                        wr64CoherentFanSlotValid = invariant && outerDeltaSet &&
                            (primaryVertices == 488U) &&
                            (innerVertices == 6U) && (outerVertices == 6U) &&
                            (innerPrimaryMatches == 6U) &&
                            (innerStripMatches == 6U);
                        static uint32_t wr64CoherentFanProbeCount = 0;
                        if (WR64_DIAGNOSTIC_ENABLED && wr64CoherentFanProbeCount < 40U) {
                            wr64CoherentFanProbeCount++;
                            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                                "[water-coherent-fan] frame=%llu primary=%u inner=%u outer=%u primaryMatches=%u stripMatches=%u delta=(%.3f,%.3f) invariant=%s\n",
                                static_cast<unsigned long long>(
                                    curWorkload.submissionFrame),
                                primaryVertices, innerVertices, outerVertices,
                                innerPrimaryMatches, innerStripMatches,
                                double(wr64CoherentFanSlotDeltaX),
                                double(wr64CoherentFanSlotDeltaZ),
                                wr64CoherentFanSlotValid ? "PASS" : "FAIL"); }
                        }
                    }

                    // Activate only the degenerate boundary quads whose
                    // outward side is exposed when the camera is rewound.
                    // Leading/side edges remain exactly degenerate, avoiding
                    // translucent overdraw over the accepted primary sheet.
                    if (wr64WaterTrailingPatchEnabled() &&
                        (curWorkload.drawData.wr64WaterVertexMask.size() ==
                            curWorkload.drawData.vertexCount()))
                    {
                        std::vector<uint32_t> &fieldInfo =
                            curWorkload.drawData.wr64WaterFieldInfo;
                        std::vector<hlslpp::float4> &fieldPrevPos =
                            curWorkload.drawData.wr64WaterFieldPrevPosShiftX;
                        std::vector<hlslpp::float4> &fieldPrevTc =
                            curWorkload.drawData.wr64WaterFieldPrevTcShiftZ;
                        uint32_t wr64PatchVertices = 0;
                        uint32_t wr64PatchExposed = 0;
                        uint32_t wr64PatchActiveEdges = 0;
                        uint32_t wr64PatchClockwiseEdges = 0;
                        uint32_t wr64PatchFoldedEdges = 0;
                        const float wr64PatchDeltaX =
                            (wr64CoherentFanStrip &&
                                wr64CoherentFanSlotValid) ?
                            wr64CoherentFanSlotDeltaX : wr64SheetShiftX;
                        const float wr64PatchDeltaZ =
                            (wr64CoherentFanStrip &&
                                wr64CoherentFanSlotValid) ?
                            wr64CoherentFanSlotDeltaZ : wr64SheetShiftZ;
                        // Coverage vertices are appended after the transform's
                        // original vertex range, so curVertexCount (500 on the
                        // proven call) cannot reach them.  Scan the workload
                        // metadata by global vertex index; mask 3 is exclusive
                        // to this patch and keeps the update tightly scoped.
                        for (uint32_t global = 0;
                            global < curWorkload.drawData.wr64WaterVertexMask.size();
                            global++)
                        {
                            if ((global >= curWorkload.drawData.wr64WaterVertexMask.size()) ||
                                (curWorkload.drawData.wr64WaterVertexMask[global] != 3) ||
                                ((uint64_t(global) + 1ULL) * 4ULL > fieldInfo.size()) ||
                                (global >= fieldPrevPos.size()) ||
                                (global >= fieldPrevTc.size()))
                            {
                                continue;
                            }
                            const uint32_t info = global * 4;
                            const uint32_t edgeA = fieldInfo[info + 2];
                            const uint32_t edgeB = fieldInfo[info + 3];
                            const std::vector<float> &allPositions =
                                curWorkload.drawData.posFloats;
                            if (((uint64_t(edgeA) + 1ULL) * 3ULL > allPositions.size()) ||
                                ((uint64_t(edgeB) + 1ULL) * 3ULL > allPositions.size()))
                            {
                                continue;
                            }
                            const float ax = allPositions[edgeA * 3 + 0];
                            const float az = allPositions[edgeA * 3 + 2];
                            const float bx = allPositions[edgeB * 3 + 0];
                            const float bz = allPositions[edgeB * 3 + 2];
                            // The verified primary water triangles are clockwise
                            // in local X/Z, so their interior lies to the right
                            // of every directed boundary edge.  The exterior is
                            // therefore the left normal.  The previous right
                            // normal activated an inward-folded strip, which
                            // overlaid the waves and left the real trailing gap
                            // uncovered at the bottom of the viewport.
                            const float normalX = -(bz - az);
                            const float normalZ = bx - ax;
                            const float normalLength = std::hypot(normalX, normalZ);
                            const float outwardX = (normalLength > 1.0e-6f) ?
                                (normalX / normalLength) : 0.0f;
                            const float outwardZ = (normalLength > 1.0e-6f) ?
                                (normalZ / normalLength) : 0.0f;
                            const float exposure =
                                outwardX * (-wr64PatchDeltaX) +
                                outwardZ * (-wr64PatchDeltaZ);
                            const bool firstVertexOfEdge =
                                ((wr64PatchVertices & 1U) == 0U);
                            wr64PatchVertices++;
                            if (exposure > 0.0f) wr64PatchExposed++;
                            // Sweep exposed boundary edges by the same complete
                            // camera-relative delta as the sheet. Using one D
                            // for both endpoints keeps adjacent quads connected;
                            // projecting D separately onto each edge opened
                            // corner gaps and measured worse than this canonical
                            // full-delta strip.
                            const float shiftX = (exposure > 0.0f) ?
                                wr64PatchDeltaX : 0.0f;
                            const float shiftZ = (exposure > 0.0f) ?
                                wr64PatchDeltaZ : 0.0f;
                            fieldPrevPos[global].w = shiftX;
                            fieldPrevTc[global].z = shiftZ;

                            // Runtime geometry invariant for the two triangles
                            // emitted per edge: (b,a,a-D) and (b,a-D,b-D).
                            // The 864 primary triangles are all clockwise in XZ,
                            // so every active strip pair must also have two
                            // strictly negative signed areas. Log any violation;
                            // validation treats it as a hard candidate reject.
                            if (firstVertexOfEdge && (exposure > 0.0f)) {
                                wr64PatchActiveEdges++;
                                const float outerAx = ax - shiftX;
                                const float outerAz = az - shiftZ;
                                const float outerBx = bx - shiftX;
                                const float outerBz = bz - shiftZ;
                                const float area0 =
                                    (ax - bx) * (outerAz - bz) -
                                    (az - bz) * (outerAx - bx);
                                const float area1 =
                                    (outerAx - bx) * (outerBz - bz) -
                                    (outerAz - bz) * (outerBx - bx);
                                if ((area0 < -1.0e-4f) &&
                                    (area1 < -1.0e-4f))
                                {
                                    wr64PatchClockwiseEdges++;
                                }
                                else {
                                    wr64PatchFoldedEdges++;
                                }
                            }
                        }
                        static uint32_t wr64PatchProbeCount = 0;
                        if (WR64_DIAGNOSTIC_ENABLED && wr64PatchProbeCount < 40) {
                            wr64PatchProbeCount++;
                            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                                "[water-patch] frame=%llu sheetShift=(%.3f,%.3f) patchDelta=(%.3f,%.3f) topology=488+12+144 vertices=%u exposed=%u activeEdges=%u clockwise=%u folded=%u coherentFan=%s invariant=%s\n",
                                static_cast<unsigned long long>(curWorkload.submissionFrame),
                                double(wr64SheetShiftX), double(wr64SheetShiftZ),
                                double(wr64PatchDeltaX),
                                double(wr64PatchDeltaZ),
                                wr64PatchVertices, wr64PatchExposed,
                                wr64PatchActiveEdges, wr64PatchClockwiseEdges,
                                wr64PatchFoldedEdges,
                                wr64CoherentFanStrip ?
                                    (wr64CoherentFanSlotValid ? "PASS" : "FAIL") :
                                    "OFF",
                                ((wr64PatchVertices == 144U) &&
                                    (wr64PatchFoldedEdges == 0U) &&
                                    (wr64PatchClockwiseEdges ==
                                        wr64PatchActiveEdges)) ? "PASS" : "FAIL"); }
                        }
                    }

                    // WATERLOCK-R7. Dump the sheet. Every theory so far has
                    // been about the shape of this mesh -- where its border is,
                    // whether it has a seam, how its cells are laid out -- and
                    // not one of them was checked against the mesh itself.
                    // Twenty frames of it, written once, is smaller than another
                    // guess.
                    {
                        static FILE *sheetFile = nullptr;
                        static uint64_t sheetFrames = 0;
                        static bool sheetDone = false;
                        if (WR64_DIAGNOSTIC_ENABLED && !sheetDone) {
                            if (sheetFile == nullptr) {
                                sheetFile = std::fopen("wr64-water-sheet.csv", "w");
                                if (sheetFile != nullptr) {
                                    std::fprintf(sheetFile,
                                        "frame,slot,x,y,z,u,v,cam_x,cam_y,cam_z,shift_x,shift_z\n");
                                }
                            }

                            if (sheetFile != nullptr) {
                                for (uint32_t i = 0; i < curVertexCount; i++) {
                                    if ((i >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[i] == 0)) {
                                        continue;
                                    }

                                    std::fprintf(sheetFile,
                                        "%llu,%u,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n",
                                        static_cast<unsigned long long>(curWorkload.submissionFrame), i,
                                        double(curPositions[i * 3 + 0]),
                                        double(curPositions[i * 3 + 1]),
                                        double(curPositions[i * 3 + 2]),
                                        (curTexcoords != nullptr) ? double(curTexcoords[i * 2 + 0]) : 0.0,
                                        (curTexcoords != nullptr) ? double(curTexcoords[i * 2 + 1]) : 0.0,
                                        double(wr64ProbeCameraX), double(wr64ProbeCameraY), double(wr64ProbeCameraZ),
                                        double(wr64SheetShiftX), double(wr64SheetShiftZ));
                                }

                                sheetFrames++;
                                std::fflush(sheetFile);
                                if (sheetFrames >= 20) {
                                    std::fclose(sheetFile);
                                    sheetFile = nullptr;
                                    sheetDone = true;
                                    { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[waterlock] sheet dump complete: wr64-water-sheet.csv\n"); }
                                    { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
                                }
                            }
                        }
                    }

                    // WATERLOCK-R9. TWO MESHES, NOT ONE.
                    //
                    // The dump settled what this draw actually is. Four hundred
                    // and ninety four vertices form a hexagonal lattice on a
                    // 63.6 unit cell carrying the wave field. Six more sit at
                    // y = 0.0 exactly with texture coordinate (16,16) exactly --
                    // a flat far-field skirt about 3000 by 2600 units, no waves,
                    // one texel, covering most of the visible water. They were
                    // being treated as lattice vertices: two thousand units from
                    // the nearest previous sample, so the sampler fell through
                    // to its clamp and handed each of them the height of some
                    // lattice vertex near the craft. The entire far plane was
                    // being tilted and dragged every native frame. That is the
                    // warping, and it is why the smooth rewind looked soft.
                    //
                    // A skirt corner needs none of that. Its height never
                    // changes and neither does its texture coordinate, so its
                    // only honest velocity is the sheet's own translation, with
                    // zero in Y and zero in UV.
                    //
                    // Separate them by local density, which needs no assumption
                    // about slot order or magic values: a lattice vertex has a
                    // neighbour one cell away, a skirt corner has nothing within
                    // twenty cells. The median of those distances is also the
                    // true cell size -- the estimate this code used before came
                    // from the bounding box, which the skirt inflates to nearly
                    // double, so every search radius in the sampler was wrong as
                    // well.
                    std::vector<uint8_t> wr64LatticeVertex(curVertexCount, 0);
                    double wr64MeasuredSpacing = spacing;
                    double wr64LatticeMinX = 0.0;
                    double wr64LatticeMaxX = 0.0;
                    double wr64LatticeMinZ = 0.0;
                    double wr64LatticeMaxZ = 0.0;
                    bool wr64LatticeBoundsValid = false;
                    {
                        std::vector<double> neighbourDistances;
                        std::vector<double> nearestPerVertex(curVertexCount, -1.0);
                        neighbourDistances.reserve(curVertexCount);
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((i >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[i] == 0)) {
                                continue;
                            }

                            const double xi = double(curPositions[i * 3 + 0]);
                            const double zi = double(curPositions[i * 3 + 2]);
                            double best = std::numeric_limits<double>::max();
                            for (uint32_t j = 0; j < curVertexCount; j++) {
                                if ((j == i) || (j >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[j] == 0)) {
                                    continue;
                                }

                                const double dx = xi - double(curPositions[j * 3 + 0]);
                                const double dz = zi - double(curPositions[j * 3 + 2]);
                                const double distanceSquared = (dx * dx) + (dz * dz);
                                if ((distanceSquared > 1.0e-6) && (distanceSquared < best)) {
                                    best = distanceSquared;
                                }
                            }

                            if (best < std::numeric_limits<double>::max()) {
                                nearestPerVertex[i] = std::sqrt(best);
                                neighbourDistances.push_back(nearestPerVertex[i]);
                            }
                        }

                        if (!neighbourDistances.empty()) {
                            const size_t middle = neighbourDistances.size() / 2;
                            std::nth_element(neighbourDistances.begin(),
                                neighbourDistances.begin() + middle, neighbourDistances.end());
                            const double median = neighbourDistances[middle];
                            if (median > 1.0e-4) {
                                wr64MeasuredSpacing = median;
                                const double latticeLimit = median * 2.0;
                                for (uint32_t i = 0; i < curVertexCount; i++) {
                                    if ((nearestPerVertex[i] >= 0.0) && (nearestPerVertex[i] <= latticeLimit)) {
                                        wr64LatticeVertex[i] = 1;
                                        const double x = double(curPositions[i * 3 + 0]);
                                        const double z = double(curPositions[i * 3 + 2]);
                                        if (!wr64LatticeBoundsValid) {
                                            wr64LatticeMinX = wr64LatticeMaxX = x;
                                            wr64LatticeMinZ = wr64LatticeMaxZ = z;
                                            wr64LatticeBoundsValid = true;
                                        }
                                        else {
                                            wr64LatticeMinX = std::min(wr64LatticeMinX, x);
                                            wr64LatticeMaxX = std::max(wr64LatticeMaxX, x);
                                            wr64LatticeMinZ = std::min(wr64LatticeMinZ, z);
                                            wr64LatticeMaxZ = std::max(wr64LatticeMaxZ, z);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    wr64ProbeSpacing = wr64MeasuredSpacing;
                    wr64LatticeVertexOuter = wr64LatticeVertex;
                    const bool wr64RippleBridge = wr64WaterRippleBridgeEnabled();
                    if (wr64RigidBridgeCorrection || wr64RippleBridge) {
                        std::vector<uint8_t> primaryIncidence(curVertexCount, 0);
                        std::vector<uint8_t> bridgeIncidence(curVertexCount, 0);
                        const std::vector<uint32_t> &waterFaces =
                            curWorkload.drawData.wr64WaterFaceIndices;
                        uint32_t transformTriangle = 0;
                        for (size_t f = 0; (f + 2) < waterFaces.size(); f += 3) {
                            const uint32_t globalA = waterFaces[f + 0];
                            const uint32_t globalB = waterFaces[f + 1];
                            const uint32_t globalC = waterFaces[f + 2];
                            if ((globalA < curVertexIndex) || (globalB < curVertexIndex) ||
                                (globalC < curVertexIndex) ||
                                (globalA >= (curVertexIndex + curVertexCount)) ||
                                (globalB >= (curVertexIndex + curVertexCount)) ||
                                (globalC >= (curVertexIndex + curVertexCount)))
                            {
                                continue;
                            }

                            // The proven stock topology is an 864-triangle
                            // ripple prefix followed by its bridge.  Added
                            // stitch triangles intentionally mix a primary
                            // corner with a private bridge corner, so producer
                            // keys alone would misclassify that private corner
                            // as part of the ripple field and disable the rigid
                            // bridge policy we are measuring.
                            const bool primary = (transformTriangle < 864U);
                            transformTriangle++;
                            std::vector<uint8_t> &incidence =
                                primary ? primaryIncidence : bridgeIncidence;
                            incidence[globalA - curVertexIndex] = 1;
                            incidence[globalB - curVertexIndex] = 1;
                            incidence[globalC - curVertexIndex] = 1;
                        }

                        uint32_t rippleBridgeVertexCount = 0;
                        std::vector<uint32_t> &fieldInfo =
                            curWorkload.drawData.wr64WaterFieldInfo;
                        const bool fieldInfoValid =
                            fieldInfo.size() >=
                            (size_t(curWorkload.drawData.vertexCount()) * 4ULL);
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((bridgeIncidence[i] == 0) ||
                                (primaryIncidence[i] != 0))
                            {
                                continue;
                            }

                            if (wr64RigidBridgeCorrection) {
                                // Exclude all twelve bridge-only vertices from
                                // the pinned/generated branch below.  They then
                                // take the ordinary cur-prev position and UV
                                // endpoint deltas as one rigid flat structure.
                                wr64LatticeVertexOuter[i] = 0;
                            }

                            if (!wr64RippleBridge || !fieldInfoValid) {
                                continue;
                            }

                            // Both the six private inner corners and the six
                            // far outer corners map radially to the closest
                            // vertex used by the proven 864-triangle primary
                            // prefix. Private inner corners find their exact
                            // coincident original; far corners find the same
                            // boundary corner by distance in the X/Z plane.
                            uint32_t closestPrimary = UINT32_MAX;
                            double closestDistanceSquared =
                                std::numeric_limits<double>::max();
                            const double bridgeX = double(curPositions[i * 3 + 0]);
                            const double bridgeZ = double(curPositions[i * 3 + 2]);
                            for (uint32_t candidate = 0;
                                candidate < curVertexCount; candidate++)
                            {
                                if (primaryIncidence[candidate] == 0) {
                                    continue;
                                }

                                const double dx = bridgeX -
                                    double(curPositions[candidate * 3 + 0]);
                                const double dz = bridgeZ -
                                    double(curPositions[candidate * 3 + 2]);
                                const double distanceSquared = (dx * dx) + (dz * dz);
                                if (distanceSquared < closestDistanceSquared) {
                                    closestDistanceSquared = distanceSquared;
                                    closestPrimary = candidate;
                                }
                            }

                            if (closestPrimary == UINT32_MAX) {
                                continue;
                            }

                            const uint32_t globalVertex = curVertexIndex + i;
                            const uint32_t infoOffset = globalVertex * 4;
                            // Mode 6 already has the exact presentation
                            // contract required here: current X/Z remain fixed,
                            // while Y and UV are evaluated from sourceVertex's
                            // accepted interpolation at every output frame.
                            fieldInfo[infoOffset + 0] = 6U;
                            fieldInfo[infoOffset + 1] =
                                curVertexIndex + closestPrimary;
                            fieldInfo[infoOffset + 2] = 0U;
                            fieldInfo[infoOffset + 3] = 0U;
                            rippleBridgeVertexCount++;
                        }

                        if (rippleBridgeVertexCount > 0) {
                            modifiedBuffers.wr64WaterField = true;
                            static uint32_t rippleBridgeProbeCount = 0;
                            if (rippleBridgeProbeCount < 40) {
                                rippleBridgeProbeCount++;
                                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                                    "[water-ripple-bridge] frame=%llu vertices=%u primary=%u bridge=%u\n",
                                    static_cast<unsigned long long>(
                                        curWorkload.submissionFrame),
                                    rippleBridgeVertexCount,
                                    uint32_t(std::count(primaryIncidence.begin(),
                                        primaryIncidence.end(), uint8_t(1))),
                                    uint32_t(std::count(bridgeIncidence.begin(),
                                        bridgeIncidence.end(), uint8_t(1)))); }
                            }
                        }
                    }
                    for (uint32_t i = 0; i < curVertexCount; i++) {
                        if ((i >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[i] == 0)) {
                            continue;
                        }

                        if ((i < wr64LatticeVertex.size()) && (wr64LatticeVertex[i] != 0)) {
                            wr64ProbeLattice++;
                        }
                        else {
                            wr64ProbeSkirt++;
                        }
                    }

                    // Presentation-field diagnostic.  This is deliberately
                    // separate from every previous SHEET_* experiment: those
                    // experiments reduced a spatially moving wave sample to a
                    // single endpoint velocity.  Here the GPU receives both
                    // complete native fields and evaluates them at the actual
                    // presentation-time query point.
                    const bool wr64ContinuousPresentationField = []() {
                        const char *value = std::getenv("WR64_WATER_CONTINUOUS_FIELD");
                        return (value != nullptr) && (value[0] != '\0') &&
                            (value[0] != '0');
                    }();
                    const bool wr64ContinuousCoverageOnly = []() {
                        const char *value = std::getenv("WR64_WATER_CONTINUOUS_COVERAGE");
                        return (value != nullptr) && (value[0] != '\0') &&
                            (value[0] != '0');
                    }();
                    const bool wr64ContinuousHeightOnly = []() {
                        const char *value = std::getenv("WR64_WATER_CONTINUOUS_HEIGHT");
                        return (value != nullptr) && (value[0] != '\0') &&
                            (value[0] != '0');
                    }();
                    const bool wr64ExactPresentationField =
                        wr64ContinuousPresentationField || wr64ContinuousCoverageOnly ||
                        wr64ContinuousHeightOnly || []() {
                        const char *value = std::getenv("WR64_WATER_EXACT_PRESENT");
                        return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
                    }();
                    // Acceptance instrumentation needs a stable native-frame
                    // key for every presentation-rate sample of this call.
                    // This is metadata only and remains inert unless the
                    // water-present trace is armed.
                    curWorkload.drawData.wr64WaterSubmissionFrame =
                        curWorkload.submissionFrame;
                    if (wr64ExactPresentationField && wr64TexcoordRangesValid &&
                        (curWorkload.drawData.wr64WaterFieldInfo.size() >=
                            (size_t(curWorkload.drawData.vertexCount()) * 4)) &&
                        (curWorkload.drawData.wr64WaterFieldPrevPosShiftX.size() >=
                            curWorkload.drawData.vertexCount()) &&
                        (curWorkload.drawData.wr64WaterFieldPrevTcShiftZ.size() >=
                            curWorkload.drawData.vertexCount()))
                    {
                        std::vector<uint32_t> &fieldFaces =
                            curWorkload.drawData.wr64WaterFieldFaceIndices;
                        fieldFaces.clear();
                        const std::vector<uint32_t> &waterFaces =
                            curWorkload.drawData.wr64WaterFaceIndices;
                        const std::vector<uint32_t> &producerKeys =
                            curWorkload.drawData.wr64WaterProducerKeys;
                        for (size_t f = 0; (f + 2) < waterFaces.size(); f += 3) {
                            const uint32_t a = waterFaces[f + 0];
                            const uint32_t b = waterFaces[f + 1];
                            const uint32_t c = waterFaces[f + 2];
                            if ((a >= producerKeys.size()) || (b >= producerKeys.size()) ||
                                (c >= producerKeys.size()) || (producerKeys[a] == 0) ||
                                (producerKeys[b] == 0) || (producerKeys[c] == 0))
                            {
                                continue;
                            }

                            fieldFaces.push_back(a);
                            fieldFaces.push_back(b);
                            fieldFaces.push_back(c);
                        }

                        const uint32_t fieldTriangleCount = uint32_t(fieldFaces.size() / 3);
                        std::vector<uint32_t> &fieldInfo =
                            curWorkload.drawData.wr64WaterFieldInfo;
                        std::vector<hlslpp::float4> &fieldPrevPos =
                            curWorkload.drawData.wr64WaterFieldPrevPosShiftX;
                        std::vector<hlslpp::float4> &fieldPrevTc =
                            curWorkload.drawData.wr64WaterFieldPrevTcShiftZ;

                        // The game's finite grid recenters by whole lattice
                        // cells while the camera moves continuously. Preserve
                        // the camera-to-grid phase observed on the first frame
                        // and cancel only subsequent recenter jumps. This makes
                        // the coverage frame continuous without translating the
                        // wave field or changing its native endpoint values.
                        float wr64CoverageOffsetX = 0.0f;
                        float wr64CoverageOffsetZ = 0.0f;
                        if ((wr64ContinuousPresentationField || wr64ContinuousCoverageOnly ||
                            wr64ContinuousHeightOnly) &&
                            wr64CameraLocalValid && wr64LatticeBoundsValid)
                        {
                            struct CoveragePhaseState {
                                bool valid = false;
                                float cameraMinusCenterX = 0.0f;
                                float cameraMinusCenterZ = 0.0f;
                                float lastCameraX = 0.0f;
                                float lastCameraZ = 0.0f;
                                uint64_t lastFrame = 0;
                            };
                            static std::map<uint32_t, CoveragePhaseState> states;
                            CoveragePhaseState &state = states[curTransformIndex];
                            const float centerX = float((wr64LatticeMinX + wr64LatticeMaxX) * 0.5);
                            const float centerZ = float((wr64LatticeMinZ + wr64LatticeMaxZ) * 0.5);
                            const float cameraMinusCenterX = wr64CameraLocalX - centerX;
                            const float cameraMinusCenterZ = wr64CameraLocalZ - centerZ;
                            const double cameraStep = state.valid ? std::hypot(
                                double(wr64CameraLocalX - state.lastCameraX),
                                double(wr64CameraLocalZ - state.lastCameraZ)) : 0.0;
                            const double resetDistance = 0.25 * std::max(spanX, spanZ);
                            const bool reset = !state.valid ||
                                (curWorkload.submissionFrame < state.lastFrame) ||
                                (curWorkload.submissionFrame > (state.lastFrame + 2)) ||
                                (cameraStep > resetDistance);
                            if (reset) {
                                state.cameraMinusCenterX = cameraMinusCenterX;
                                state.cameraMinusCenterZ = cameraMinusCenterZ;
                                state.valid = true;
                            }
                            wr64CoverageOffsetX = cameraMinusCenterX - state.cameraMinusCenterX;
                            wr64CoverageOffsetZ = cameraMinusCenterZ - state.cameraMinusCenterZ;
                            state.lastCameraX = wr64CameraLocalX;
                            state.lastCameraZ = wr64CameraLocalZ;
                            state.lastFrame = curWorkload.submissionFrame;
                        }
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((i >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[i] == 0)) {
                                continue;
                            }

                            const uint32_t globalVertex = curVertexIndex + i;
                            const uint32_t infoOffset = globalVertex * 4;
                            // Mode 1 is a sampled rippled-field vertex. Mode 2
                            // is one of the six natively-flat outer vertices;
                            // it follows the same rigid coverage motion without
                            // inventing a wave value thousands of units away.
                            fieldInfo[infoOffset + 0] = wr64ContinuousCoverageOnly ? 3U :
                                (wr64ContinuousHeightOnly ?
                                    (((i < wr64LatticeVertex.size()) &&
                                        (wr64LatticeVertex[i] != 0)) ? 4U : 2U) :
                                (((i < wr64LatticeVertex.size()) &&
                                    (wr64LatticeVertex[i] != 0)) ? 1U : 2U));
                            fieldInfo[infoOffset + 1] = fieldTriangleCount;
                            fieldInfo[infoOffset + 2] = wr64FloatBits(wr64CoverageOffsetX);
                            fieldInfo[infoOffset + 3] = wr64FloatBits(wr64CoverageOffsetZ);
                            fieldPrevPos[globalVertex] = hlslpp::float4(
                                prevPositions[i * 3 + 0], prevPositions[i * 3 + 1],
                                prevPositions[i * 3 + 2], wr64SheetShiftX);
                            fieldPrevTc[globalVertex] = hlslpp::float4(
                                prevTexcoords[i * 2 + 0], prevTexcoords[i * 2 + 1],
                                wr64SheetShiftZ, 0.0f);
                        }

                        modifiedBuffers.wr64WaterField = (fieldTriangleCount > 0);
                    }

                    // The whole sheet rewinds by the camera's own travel, which
                    // is smooth. Stock pairing rewinds it along the lattice's
                    // quantised step instead -- measured as -64, +32, -63, -33,
                    // +1, -33 on consecutive frames -- so the surface lurches
                    // sixty four units back and forth every native frame. That
                    // is the warping. The camera's translation is the same
                    // motion without the staircase.
                    // WATERLOCK-R10. EACH MESH GETS WHAT IS EXACT FOR IT.
                    //
                    // Moving the lattice is what degrades it. Pinned, every
                    // query lands exactly on a previous grid node and the
                    // previous height is reproduced, not reconstructed. Rewound
                    // by the camera, the query lands most of a cell away from
                    // any node and the height becomes a linear guess across a
                    // triangle -- which is why it only comes apart once the
                    // camera is moving, and why it was clean standing still.
                    // So the lattice stays where it is.
                    //
                    // The skirt is the opposite. Its four corners have no
                    // texture detail and no height to lose -- flat, y = 0, one
                    // texel -- so nothing about them can be blurred by motion,
                    // and slot against slot is exact for them because the dump
                    // shows all six move by one shared vector. They take stock
                    // pairing and travel with the grid, as the game draws them.
                    //
                    // That also puts the seam between rippled water and flat
                    // skirt back in motion. It sits a couple of hundred units
                    // from the eye, and it is the one edge in this scene that a
                    // pinned sheet holds perfectly still for nine frames at a
                    // time instead of sweeping past.
                    const bool wr64CoherentSheetDiagnostic = []() {
                        const char *value = std::getenv("WR64_SHEET_COHERENT");
                        return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
                    }();
                    // Diagnostic: use the producer's actual topology
                    // translation instead of camera travel. Across every
                    // captured native update all 494 dense-lattice slots have
                    // one identical X/Z delta, even when their producer keys
                    // wrap to a new row.  Using its component median makes the
                    // two native endpoints exact without pairing wave height
                    // or UV by slot; those fields are still sampled spatially
                    // below at the position the vertex rewinds to.
                    const bool wr64TopologySheetDiagnostic = []() {
                        const char *value = std::getenv("WR64_SHEET_TOPOLOGY");
                        return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
                    }();
                    const bool wr64EdgeFalloffDiagnostic = []() {
                        const char *value = std::getenv("WR64_WATER_EDGE_FALLOFF");
                        return (value != nullptr) && (value[0] != '\0') &&
                            (value[0] != '0');
                    }();
                    if (wr64TopologySheetDiagnostic || wr64EdgeFalloffDiagnostic) {
                        std::vector<float> topologyShiftX;
                        std::vector<float> topologyShiftZ;
                        topologyShiftX.reserve(curVertexCount);
                        topologyShiftZ.reserve(curVertexCount);
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((i >= wr64LatticeVertex.size()) || (wr64LatticeVertex[i] == 0)) {
                                continue;
                            }

                            topologyShiftX.push_back(curPositions[i * 3 + 0] - prevPositions[i * 3 + 0]);
                            topologyShiftZ.push_back(curPositions[i * 3 + 2] - prevPositions[i * 3 + 2]);
                        }

                        const auto componentMedian = [](std::vector<float> &values) -> float {
                            if (values.empty()) {
                                return 0.0f;
                            }

                            const size_t middle = values.size() / 2;
                            std::nth_element(values.begin(), values.begin() + middle, values.end());
                            return values[middle];
                        };
                        wr64SheetShiftX = componentMedian(topologyShiftX);
                        wr64SheetShiftZ = componentMedian(topologyShiftZ);
                    }

                    const bool wr64SheetMotionDiagnostic = wr64CoherentSheetDiagnostic || wr64TopologySheetDiagnostic || []() {
                        const char *value = std::getenv("WR64_SHEET_MOTION");
                        return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
                    }();
                    const bool wr64SheetQueryDiagnostic = wr64CoherentSheetDiagnostic || wr64TopologySheetDiagnostic || []() {
                        const char *value = std::getenv("WR64_SHEET_QUERY");
                        return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
                    }();
                    for (uint32_t i = 0; i < curVertexCount; i++) {
                        wr64SheetShiftWeight[i] = wr64SheetMotionDiagnostic ? 1.0f : 0.0f;
                        wr64SheetQueryWeight[i] = wr64SheetQueryDiagnostic ? 1.0f : 0.0f;
                    }
                    if (wr64EdgeFalloffDiagnostic && (wr64MeasuredSpacing > 0.0)) {
                        std::map<std::pair<uint32_t, uint32_t>, uint32_t> edgeCounts;
                        const std::vector<uint32_t> &faces =
                            curWorkload.drawData.wr64WaterFaceIndices;
                        for (size_t f = 0; (f + 2) < faces.size(); f += 3) {
                            const uint32_t global[3] = {
                                faces[f + 0], faces[f + 1], faces[f + 2] };
                            bool primary = true;
                            for (uint32_t c = 0; c < 3; c++) {
                                if ((global[c] >= curWorkload.drawData.wr64WaterProducerKeys.size()) ||
                                    (curWorkload.drawData.wr64WaterProducerKeys[global[c]] == 0))
                                {
                                    primary = false;
                                }
                            }
                            if (!primary) continue;
                            for (uint32_t e = 0; e < 3; e++) {
                                const uint32_t a = global[e];
                                const uint32_t b = global[(e + 1) % 3];
                                const auto key = (a < b) ? std::make_pair(a, b) :
                                    std::make_pair(b, a);
                                edgeCounts[key]++;
                            }
                        }
                        std::vector<uint32_t> boundary;
                        for (const auto &entry : edgeCounts) {
                            if (entry.second == 1) {
                                boundary.push_back(entry.first.first);
                                boundary.push_back(entry.first.second);
                            }
                        }
                        std::sort(boundary.begin(), boundary.end());
                        boundary.erase(std::unique(boundary.begin(), boundary.end()),
                            boundary.end());
                        const double fadeWidth = wr64MeasuredSpacing * 4.0;
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((i >= wr64GeneratedVertex.size()) ||
                                (wr64GeneratedVertex[i] == 0)) continue;
                            const double x = curPositions[i * 3 + 0];
                            const double z = curPositions[i * 3 + 2];
                            double distance = std::numeric_limits<double>::max();
                            for (uint32_t global : boundary) {
                                if ((global < curVertexIndex) ||
                                    (global >= (curVertexIndex + curVertexCount))) continue;
                                const uint32_t local = global - curVertexIndex;
                                const double dx = x - curPositions[local * 3 + 0];
                                const double dz = z - curPositions[local * 3 + 2];
                                distance = std::min(distance, std::hypot(dx, dz));
                            }
                            const double linear = std::clamp(
                                1.0 - (distance / fadeWidth), 0.0, 1.0);
                            wr64SheetShiftWeight[i] = float(linear * linear);
                            // Preserve the accepted height/UV history exactly;
                            // only the low-detail edge footprint is deformed.
                            wr64SheetQueryWeight[i] = 0.0f;
                        }
                    }

                    // WATERLOCK-R5 note retained. Rewinding the
                    // sheet was never fixing coverage -- it was moving every
                    // query point off the sheet's own boundary, which is where
                    // the reconstruction below was failing. Fix the
                    // reconstruction and nothing has to move at all: the sheet
                    // is pinned again, so it is as sharp as it ever was, there
                    // is no blur under acceleration and no stretched band to
                    // flicker at the edge. The camera shift is still measured,
                    // because it is what the probe reports, but no vertex is
                    // moved by it. Every entry of the weight vector stays zero.

                    // One and a half spacings always reaches every corner of the
                    // cell a query point falls in, including the worst-case
                    // diagonal, so a query inside the sheet can never come up
                    // empty.
                    const double radius = wr64MeasuredSpacing * 1.5;
                    const double radiusSquared = radius * radius;
                    // WATERLOCK-R19. THE EXACT PATH WAS NEVER FIRING.
                    //
                    // This tolerance was one ten-thousandth of a cell, which
                    // assumes the grid recentres by an exact lattice vector. It
                    // does not: measured steps are -63, -33, +1 against a 63.63
                    // cell, integer-rounded and a unit or two off every time. So
                    // no query ever coincided, every vertex went through
                    // barycentric reconstruction, and that error is zero at the
                    // grid nodes and largest in the cell interiors -- a height
                    // error laid out on the grid, which is what the 96 pixel
                    // repeat in the crease band is.
                    //
                    // A twelfth of a cell is far tighter than the reconstruction
                    // it replaces and comfortably wider than the rounding, so a
                    // vertex sitting a unit or two from where a previous one sat
                    // takes that height outright.
                    const double wr64SnapDistance = wr64MeasuredSpacing / 12.0;
                    const double coincidentSquared = wr64SnapDistance * wr64SnapDistance;

                    if (radius > 0.0) {
                        std::unordered_map<uint64_t, std::vector<uint32_t>> sampleBuckets;
                        const auto bucketKey = [](int32_t ix, int32_t iz) -> uint64_t {
                            return (uint64_t(uint32_t(ix)) << 32) | uint64_t(uint32_t(iz));
                        };

                        // Bucket edge equals the search radius, so every sample
                        // within range of a query lives in the query's own cell
                        // or one of the eight around it.
                        for (uint32_t s = 0; s < uint32_t(previousSamples.size()); s++) {
                            const SurfaceSample &sample = previousSamples[s];
                            // A previous skirt corner is nowhere near the
                            // lattice and must never be a candidate for one.
                            if (wr64LatticeBoundsValid) {
                                const double margin = wr64MeasuredSpacing * 3.0;
                                if ((double(sample.x) < (wr64LatticeMinX - margin)) ||
                                    (double(sample.x) > (wr64LatticeMaxX + margin)) ||
                                    (double(sample.z) < (wr64LatticeMinZ - margin)) ||
                                    (double(sample.z) > (wr64LatticeMaxZ + margin)))
                                {
                                    continue;
                                }
                            }

                            const int32_t ix = int32_t(std::floor((double(sample.x) - minimumX) / radius));
                            const int32_t iz = int32_t(std::floor((double(sample.z) - minimumZ) / radius));
                            sampleBuckets[bucketKey(ix, iz)].push_back(s);
                        }

                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((i >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[i] == 0)) {
                                continue;
                            }

                            // Sampled where this vertex is rewound TO, not
                            // where it ends the frame. At weight 0 it is drawn
                            // at P - shift and it has to carry the previous
                            // surface's height at P - shift, or the sheet
                            // translates while its waves stay put.
                            if ((i < wr64LatticeVertex.size()) && (wr64LatticeVertex[i] == 0)) {
                                continue;
                            }

                            const float vertexWeight =
                                (i < wr64SheetQueryWeight.size()) ? wr64SheetQueryWeight[i] : 0.0f;
                            const double queryX =
                                double(curPositions[i * 3 + 0]) - (double(wr64SheetShiftX) * double(vertexWeight));
                            const double queryZ =
                                double(curPositions[i * 3 + 2]) - (double(wr64SheetShiftZ) * double(vertexWeight));
                            const int32_t cellX = int32_t(std::floor((queryX - minimumX) / radius));
                            const int32_t cellZ = int32_t(std::floor((queryZ - minimumZ) / radius));

                            // WATERLOCK-R2. THE BLEND WAS EATING THE WAVES.
                            //
                            // The previous version averaged every previous
                            // sample within one and a half spacings of the query
                            // -- on this lattice, seven to nineteen of them --
                            // with an inverse-distance weight. That is a
                            // low-pass filter with a 96 unit kernel sitting on
                            // top of the wave field. It was harmless while the
                            // sheet was pinned, because then the query landed
                            // exactly on a previous sample and the coincident
                            // test below returned that sample's height outright,
                            // so the blend almost never ran.
                            //
                            // Rewinding the sheet by the camera's travel moved
                            // the query off the lattice. The coincident test
                            // stopped firing, every vertex started going through
                            // the blend, and each interpolated frame began
                            // rendering a SMOOTHED copy of the previous surface
                            // that sharpens back up as the frame weight reaches
                            // one. Waves that flatten and re-form every native
                            // frame read exactly as waves that are not moving.
                            //
                            // A height field sampled on a triangular lattice
                            // does not need averaging: the three nearest samples
                            // are the corners of the cell the query is in, so
                            // interpolate across that triangle. Exact at every
                            // sample, linear in between, no smoothing at all,
                            // and continuous across cell boundaries because
                            // neighbouring triangles agree along their shared
                            // edge.
                            // WATERLOCK-R5. THE BORDER ROW WAS THE CREASE.
                            //
                            // Keeping the three nearest samples works everywhere
                            // except the one place it matters. Along the row the
                            // sheet has just exposed, all three nearest previous
                            // samples lie in the SAME lattice row -- they are
                            // collinear, they describe no triangle, and the code
                            // fell back to handing every vertex in that row the
                            // height of its single nearest sample. A whole row
                            // taking one value each from one row over has no
                            // variation across it. That is the flat, wave-free
                            // strip with a razor straight lattice-aligned border
                            // that turns with the craft and widens with speed.
                            //
                            // Rewinding the sheet hid it by moving every query
                            // deep inside the previous footprint, where triangles
                            // are never degenerate. That is why the full rewind
                            // cleared the crease and the pinned sheet brings it
                            // back, and it is the whole of the difference.
                            //
                            // So do not give up at the border. Keep eight
                            // candidates instead of three and walk them until a
                            // triangle with real area appears, then let the
                            // barycentric weights go outside the triangle. A
                            // vertex just past the edge of the previous surface
                            // gets that surface extended along its own slope,
                            // which is continuous with the water it joins,
                            // instead of a copy of one sample's height.
                            const uint32_t CandidateCapacity = 8;
                            uint32_t candidateIndices[CandidateCapacity];
                            double candidateDistances[CandidateCapacity];
                            uint32_t candidateCount = 0;
                            bool coincident = false;
                            float coincidentHeight = 0.0f;
                            float coincidentU = 0.0f;
                            float coincidentV = 0.0f;

                            for (int32_t oz = -1; (oz <= 1) && !coincident; oz++) {
                                for (int32_t ox = -1; (ox <= 1) && !coincident; ox++) {
                                    const auto bucket = sampleBuckets.find(bucketKey(cellX + ox, cellZ + oz));
                                    if (bucket == sampleBuckets.end()) {
                                        continue;
                                    }

                                    for (const uint32_t s : bucket->second) {
                                        const SurfaceSample &sample = previousSamples[s];
                                        const double dx = queryX - double(sample.x);
                                        const double dz = queryZ - double(sample.z);
                                        const double distanceSquared = (dx * dx) + (dz * dz);
                                        if (distanceSquared >= radiusSquared) {
                                            continue;
                                        }

                                        // A current vertex sitting exactly where
                                        // a previous one sat takes that height
                                        // outright. On the pinned sheet this is
                                        // every interior vertex, so the common
                                        // case is exact rather than approximated.
                                        if (distanceSquared <= coincidentSquared) {
                                            coincident = true;
                                            coincidentHeight = sample.height;
                                            coincidentU = sample.u;
                                            coincidentV = sample.v;
                                            break;
                                        }

                                        // Insertion sort into the candidate list,
                                        // nearest first, dropping the furthest.
                                        uint32_t slot = candidateCount;
                                        while ((slot > 0) && (candidateDistances[slot - 1] > distanceSquared)) {
                                            if (slot < CandidateCapacity) {
                                                candidateDistances[slot] = candidateDistances[slot - 1];
                                                candidateIndices[slot] = candidateIndices[slot - 1];
                                            }

                                            slot--;
                                        }

                                        if (slot < CandidateCapacity) {
                                            candidateDistances[slot] = distanceSquared;
                                            candidateIndices[slot] = s;
                                            candidateCount = std::min(candidateCount + 1, CandidateCapacity);
                                        }
                                    }
                                }
                            }

                            if (coincident) {
                                wr64ExactHits++;
                                wr64PreviousSurfaceHeight[i] = coincidentHeight;
                                wr64PreviousSurfaceU[i] = coincidentU;
                                wr64PreviousSurfaceV[i] = coincidentV;
                                wr64PreviousSurfaceHeightValid[i] = 1;
                                continue;
                            }

                            // Nearest two, then the closest third that gives the
                            // triangle real area. Scaled against the cell so the
                            // test means the same thing at any spacing.
                            bool reconstructed = false;
                            if (candidateCount >= 3) {
                                const double areaFloor = wr64MeasuredSpacing * wr64MeasuredSpacing * 1.0e-2;
                                for (uint32_t b = 1; (b < candidateCount) && !reconstructed; b++) {
                                    for (uint32_t c = b + 1; (c < candidateCount) && !reconstructed; c++) {
                                        const SurfaceSample &cornerA = previousSamples[candidateIndices[0]];
                                        const SurfaceSample &cornerB = previousSamples[candidateIndices[b]];
                                        const SurfaceSample &cornerC = previousSamples[candidateIndices[c]];
                                        const double determinant =
                                            ((double(cornerB.z) - double(cornerC.z)) * (double(cornerA.x) - double(cornerC.x))) +
                                            ((double(cornerC.x) - double(cornerB.x)) * (double(cornerA.z) - double(cornerC.z)));
                                        if (std::fabs(determinant) <= areaFloor) {
                                            continue;
                                        }

                                        const double weightA =
                                            (((double(cornerB.z) - double(cornerC.z)) * (queryX - double(cornerC.x))) +
                                             ((double(cornerC.x) - double(cornerB.x)) * (queryZ - double(cornerC.z)))) / determinant;
                                        const double weightB =
                                            (((double(cornerC.z) - double(cornerA.z)) * (queryX - double(cornerC.x))) +
                                             ((double(cornerA.x) - double(cornerC.x)) * (queryZ - double(cornerC.z)))) / determinant;
                                        const double weightC = 1.0 - weightA - weightB;

                                        // Inside the cell all three land in
                                        // [0,1]. Past the border they go outside
                                        // it, which is the extension doing its
                                        // job; the limit only stops a wave being
                                        // invented several cells away.
                                        const double weightLimit = 3.0;
                                        if ((std::fabs(weightA) > weightLimit) ||
                                            (std::fabs(weightB) > weightLimit) ||
                                            (std::fabs(weightC) > weightLimit))
                                        {
                                            continue;
                                        }

                                        wr64PreviousSurfaceHeight[i] = float(
                                            (weightA * double(cornerA.height)) +
                                            (weightB * double(cornerB.height)) +
                                            (weightC * double(cornerC.height)));
                                        wr64PreviousSurfaceU[i] = float(
                                            (weightA * double(cornerA.u)) +
                                            (weightB * double(cornerB.u)) +
                                            (weightC * double(cornerC.u)));
                                        wr64PreviousSurfaceV[i] = float(
                                            (weightA * double(cornerA.v)) +
                                            (weightB * double(cornerB.v)) +
                                            (weightC * double(cornerC.v)));
                                        wr64PreviousSurfaceHeightValid[i] = 1;
                                        reconstructed = true;
                                    }
                                }
                            }

                            if (reconstructed) {
                                continue;
                            }

                            // The full sweep that was here is reverted. Letting
                            // those vertices take a triangle from anywhere on
                            // the sheet more than doubled the mean vertical
                            // velocity across all five hundred and made both the
                            // crease and the edge flicker worse. A vertex with no
                            // history holds.
                            wr64PreviousSurfaceHeightValid[i] = 0;
                            continue;

                        }

                        // WATERLOCK-R12. THE NEW ROW WAS THE ONLY DISCONTINUITY.
                        //
                        // Pinned, thirty four vertices a frame recover no
                        // previous value; with the sheet moving, six. Those
                        // extra twenty eight are the row of cells the grid has
                        // just exposed as it recentres -- they were not on the
                        // sheet last frame, so no search invents a history for
                        // them. Held, they sit still for a whole native frame
                        // while every neighbour morphs around them: one
                        // straight, grid-aligned line of vertices behaving
                        // differently from the water they are attached to,
                        // wider the faster the grid recentres. That is the
                        // crease, and it is why every build that moved the
                        // sheet lost it -- moving puts the query back inside
                        // last frame's footprint and the row stops existing.
                        //
                        // They do not need a history of their own. They need to
                        // move like the water they join, so each takes the
                        // change of the nearest vertex that does have one.
                        std::vector<uint32_t> wr64NoHistory;
                        for (uint32_t i = 0; i < curVertexCount; i++) {
                            if ((i >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[i] == 0) ||
                                (i >= wr64LatticeVertex.size()) || (wr64LatticeVertex[i] == 0))
                            {
                                continue;
                            }

                            if ((i < wr64PreviousSurfaceHeightValid.size()) &&
                                (wr64PreviousSurfaceHeightValid[i] != 0))
                            {
                                continue;
                            }

                            wr64NoHistory.push_back(i);
                        }

                        // WATERLOCK-R13. Copying the nearest neighbour was still
                        // inventing detail: one arbitrary cell's wave change,
                        // stamped onto a whole row that then reads as a line.
                        // The median change of the sheet is not detail at all --
                        // it is the water's overall rise and fall for this frame.
                        // The exposed row breathes with the sheet instead of
                        // holding still or twitching, and there is nothing left
                        // on that edge for the eye to lock onto.
                        if (!wr64NoHistory.empty()) {
                            std::vector<float> heightChanges;
                            std::vector<float> uChanges;
                            std::vector<float> vChanges;
                            heightChanges.reserve(curVertexCount);
                            for (uint32_t n = 0; n < curVertexCount; n++) {
                                if ((n >= wr64PreviousSurfaceHeightValid.size()) ||
                                    (wr64PreviousSurfaceHeightValid[n] == 0) ||
                                    (n >= wr64LatticeVertex.size()) || (wr64LatticeVertex[n] == 0))
                                {
                                    continue;
                                }

                                heightChanges.push_back(curPositions[n * 3 + 1] - wr64PreviousSurfaceHeight[n]);
                                if (curTexcoords != nullptr) {
                                    uChanges.push_back(curTexcoords[n * 2 + 0] - wr64PreviousSurfaceU[n]);
                                    vChanges.push_back(curTexcoords[n * 2 + 1] - wr64PreviousSurfaceV[n]);
                                }
                            }

                            const auto medianOf = [](std::vector<float> &values) -> float {
                                if (values.empty()) {
                                    return 0.0f;
                                }

                                const size_t middle = values.size() / 2;
                                std::nth_element(values.begin(), values.begin() + middle, values.end());
                                return values[middle];
                            };

                            const float medianHeightChange = medianOf(heightChanges);
                            const float medianUChange = medianOf(uChanges);
                            const float medianVChange = medianOf(vChanges);
                            for (const uint32_t n : wr64NoHistory) {
                                wr64PreviousSurfaceHeight[n] = curPositions[n * 3 + 1] - medianHeightChange;
                                if (curTexcoords != nullptr) {
                                    wr64PreviousSurfaceU[n] = curTexcoords[n * 2 + 0] - medianUChange;
                                    wr64PreviousSurfaceV[n] = curTexcoords[n * 2 + 1] - medianVChange;
                                }

                                wr64PreviousSurfaceHeightValid[n] = 1;
                            }
                        }
                    }
                }
            }
        }

        if (((vertexInterpolation != G_EX_COMPONENT_SKIP) || (texcoordInterpolation == G_EX_COMPONENT_AUTO)) && (curVertexCount == prevVertexCount)) {
            const std::vector<float> &curPosFloats = curWorkload.drawData.posFloats;
            const std::vector<float> &prevPosFloats = prevWorkload.drawData.posFloats;
            std::vector<float> &curVelFloats = curWorkload.drawData.velFloats;
            curVertexHash = XXH3_64bits(&curPosFloats[curVertexIndex * 3], curVertexCount * 3 * sizeof(float));
            prevVertexHash = XXH3_64bits(&prevPosFloats[prevVertexIndex * 3], prevVertexCount * 3 * sizeof(float));

            // Same range check the rest of this file applies before touching
            // velFloats. It was the one velocity write in the function without
            // one; if it ever trips, the probe below says so instead of the
            // write running off the end of the buffer.
            const bool wr64VelocityRangeValid =
                ((uint64_t(curVertexIndex) + curVertexCount) * 3ULL) <= curVelFloats.size();
            if (!wr64VelocityRangeValid) {
                static uint32_t wr64RangeProbeCount = 0;
                if (WR64_DIAGNOSTIC_ENABLED && wr64RangeProbeCount < 8) {
                    wr64RangeProbeCount++;
                    { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[waterlock] f=%llu VELOCITY RANGE BAD idx=%u count=%u size=%u\n",
                        static_cast<unsigned long long>(curWorkload.submissionFrame),
                        curVertexIndex, curVertexCount, uint32_t(curVelFloats.size())); }
                    { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
                }
            }

            if ((vertexInterpolation != G_EX_COMPONENT_SKIP) && (curVertexHash != prevVertexHash) && wr64VelocityRangeValid) {
                const float *curPosFloatsRef = &curPosFloats[curVertexIndex * 3];
                const float *prevPosFloatsRef = &prevPosFloats[prevVertexIndex * 3];
                float *curVelFloatsRef = &curVelFloats[curVertexIndex * 3];
                for (uint32_t i = 0; i < curVertexCount; i++) {
                    const bool generatedVertex =
                        (i < wr64GeneratedVertex.size()) && (wr64GeneratedVertex[i] != 0) &&
                        (((i < wr64LatticeVertexOuter.size()) &&
                            (wr64LatticeVertexOuter[i] != 0)) ||
                         wr64CoherentOuterCoverage);
                    if (generatedVertex) {
                        // The same shift on every water vertex. A single
                        // rigid translation of the whole sheet cannot shear it,
                        // cannot open a seam and cannot detach a triangle --
                        // those need vertices to disagree, and here they cannot,
                        // because there is one shift for the sheet and it is not
                        // derived from pairing anything.
                        const float wr64VertexShiftWeight =
                            (i < wr64SheetShiftWeight.size()) ? wr64SheetShiftWeight[i] : 0.0f;
                        const bool coherentFanInner =
                            wr64CoherentFanStrip &&
                            wr64CoherentFanSlotValid &&
                            (i < wr64CoherentFanInnerVertex.size()) &&
                            (wr64CoherentFanInnerVertex[i] != 0);
                        curVelFloatsRef[i * 3 + 0] = coherentFanInner ?
                            wr64CoherentFanSlotDeltaX :
                            (wr64SheetShiftX * wr64VertexShiftWeight);

                        // Nothing gates this write. An earlier version held the
                        // whole sheet for one native frame whenever the producer
                        // rebased its grid, but freezing every water vertex and
                        // then snapping is exactly the stutter this code exists
                        // to remove. With X and Z pinned and the previous
                        // surface resampled as a continuous height field, a
                        // rebase morphs over one native frame instead of
                        // hitching, so no hold is needed.
                        curVelFloatsRef[i * 3 + 1] =
                            (i < wr64PreviousSurfaceHeightValid.size()) &&
                            (wr64PreviousSurfaceHeightValid[i] != 0)
                            ? (curPosFloatsRef[i * 3 + 1] - wr64PreviousSurfaceHeight[i])
                            : 0.0f;
                        curVelFloatsRef[i * 3 + 2] = coherentFanInner ?
                            wr64CoherentFanSlotDeltaZ :
                            (wr64SheetShiftZ * wr64VertexShiftWeight);
                        continue;
                    }

                    for (uint32_t j = 0; j < 3; j++) {
                        curVelFloatsRef[i * 3 + j] =
                            (curPosFloatsRef[i * 3 + j] - prevPosFloatsRef[i * 3 + j]);
                    }
                }

                modifiedBuffers.positionVelocity = true;
                wr64PositionVelocityWritten = forceGeneratedVertexInterpolation;
                if (forceGeneratedVertexInterpolation) {
                    static uint32_t wr64WriteProbeCount = 0;
                    if (WR64_DIAGNOSTIC_ENABLED && wr64WriteProbeCount < 40) {
                        wr64WriteProbeCount++;
                        double wr64ProbeYSum = 0.0;
                        double wr64ProbeYMax = 0.0;
                        uint32_t wr64ProbeYCount = 0;
                        for (uint32_t p = 0; p < curVertexCount; p++) {
                            if ((p >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[p] == 0)) {
                                continue;
                            }

                            const double y = std::fabs(double(curVelFloatsRef[p * 3 + 1]));
                            wr64ProbeYSum += y;
                            wr64ProbeYMax = std::max(wr64ProbeYMax, y);
                            wr64ProbeYCount++;
                        }

                        uint32_t wr64ProbeMoving = 0;
                        for (uint32_t p = 0; p < wr64SheetShiftWeight.size(); p++) {
                            if (wr64SheetShiftWeight[p] > 0.0f) {
                                wr64ProbeMoving++;
                            }
                        }

                        uint32_t wr64ProbeHeld = 0;
                        uint32_t wr64ProbeWater = 0;
                        for (uint32_t p = 0; p < curVertexCount; p++) {
                            if ((p >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[p] == 0)) {
                                continue;
                            }

                            wr64ProbeWater++;
                            if ((p >= wr64PreviousSurfaceHeightValid.size()) ||
                                (wr64PreviousSurfaceHeightValid[p] == 0))
                            {
                                wr64ProbeHeld++;
                            }
                        }

                        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                            "[waterlock] f=%llu CAM mapped=%d lerpTrans=%d lerpRot=%d projDelta=%.5f\n",
                            static_cast<unsigned long long>(curWorkload.submissionFrame),
                            wr64CamMapped, wr64CamLerpTranslation, wr64CamLerpRotation, wr64CamProjectionDelta); }

                        // R16: how many projections do the water's own vertices
                        // span? One means the sheet is a single scene and this is
                        // a dead end. Two means the frame is split and each half
                        // is matched on its own camera, which draws a line at a
                        // fixed row that nothing done to the vertices can touch.
                        {
                            const std::vector<uint16_t> &vpIdx = curWorkload.drawData.viewProjIndices;
                            std::vector<uint32_t> seen;
                            for (uint32_t p = 0; p < curVertexCount; p++) {
                                if ((p >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[p] == 0)) {
                                    continue;
                                }

                                if ((uint64_t(curVertexIndex) + p) >= vpIdx.size()) {
                                    continue;
                                }

                                const uint32_t v = vpIdx[curVertexIndex + p];
                                if (std::find(seen.begin(), seen.end(), v) == seen.end()) {
                                    seen.push_back(v);
                                }
                            }

                            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[waterlock] f=%llu water spans %u projection(s):",
                                static_cast<unsigned long long>(curWorkload.submissionFrame),
                                uint32_t(seen.size())); }
                            for (const uint32_t v : seen) {
                                const bool mapped = (v < curWorkloadMap.viewProjections.size())
                                    ? curWorkloadMap.viewProjections[v].mapped : false;
                                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, " [%u mapped=%d lerpT=%d lerpR=%d]", v, int(mapped),
                                    (v < curWorkloadMap.viewProjections.size())
                                        ? int(curWorkloadMap.viewProjections[v].rigidBody.lerpTranslation) : -1,
                                    (v < curWorkloadMap.viewProjections.size())
                                        ? int(curWorkloadMap.viewProjections[v].rigidBody.lerpRotation) : -1); }
                            }

                            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "  totalProjections=%u\n",
                                uint32_t(curWorkload.drawData.viewProjTransforms.size())); }
                            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
                        }

                        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                            "[waterlock] f=%llu lattice=%u skirt=%u cell=%.2f exactHits=%u of %u\n",
                            static_cast<unsigned long long>(curWorkload.submissionFrame),
                            wr64ProbeLattice, wr64ProbeSkirt, wr64ProbeSpacing,
                            wr64ExactHits, wr64ProbeLattice); }

                        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[waterlock] f=%llu moving=%u held=%u of %u water\n",
                            static_cast<unsigned long long>(curWorkload.submissionFrame),
                            wr64ProbeMoving, wr64ProbeHeld, wr64ProbeWater); }

                        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr,
                            "[waterlock] f=%llu shift=(%.3f,%.3f) velY mean=%.3f max=%.3f over %u\n",
                            static_cast<unsigned long long>(curWorkload.submissionFrame),
                            double(wr64SheetShiftX), double(wr64SheetShiftZ),
                            (wr64ProbeYCount > 0) ? (wr64ProbeYSum / double(wr64ProbeYCount)) : 0.0,
                            wr64ProbeYMax, wr64ProbeYCount); }
                        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
                    }
                }
            }
        }

        if (forceGeneratedVertexInterpolation) {
            FILE *velocityTraceFile = wr64WaterVelocityOutputTraceFile();
            if (velocityTraceFile != nullptr) {
                uint32_t surfaceHeightMatches = 0;
                uint32_t nonzeroYVelocities = 0;
                double yVelocityAbsoluteSum = 0.0;
                double yVelocitySquaredSum = 0.0;
                double yVelocityMaximumAbsolute = 0.0;
                const std::vector<float> &velocityFloats =
                    curWorkload.drawData.velFloats;
                for (uint32_t i = 0; i < curVertexCount; i++) {
                    if ((i < wr64PreviousSurfaceHeightValid.size()) &&
                        (wr64PreviousSurfaceHeightValid[i] != 0))
                    {
                        surfaceHeightMatches++;
                    }

                    const double yVelocity = double(
                        velocityFloats[(curVertexIndex + i) * 3 + 1]);
                    const double absoluteYVelocity = std::fabs(yVelocity);
                    if (absoluteYVelocity > 1.0e-6) {
                        nonzeroYVelocities++;
                    }

                    yVelocityAbsoluteSum += absoluteYVelocity;
                    yVelocitySquaredSum += yVelocity * yVelocity;
                    yVelocityMaximumAbsolute =
                        std::max(yVelocityMaximumAbsolute, absoluteYVelocity);
                }

                const double divisor =
                    (curVertexCount > 0) ? double(curVertexCount) : 1.0;
                std::fprintf(velocityTraceFile,
                    "%llu,%u,%u,%u,%u,%u,%u,%.9f,%.9f,%.9f,%llu,%llu\n",
                    static_cast<unsigned long long>(curWorkload.submissionFrame),
                    curTransformIndex,
                    prevTransformIndex,
                    curVertexCount,
                    surfaceHeightMatches,
                    nonzeroYVelocities,
                    uint32_t(wr64PositionVelocityWritten),
                    yVelocityAbsoluteSum / divisor,
                    std::sqrt(yVelocitySquaredSum / divisor),
                    yVelocityMaximumAbsolute,
                    static_cast<unsigned long long>(curVertexHash),
                    static_cast<unsigned long long>(prevVertexHash));
                std::fflush(velocityTraceFile);
            }
        }

        if ((texcoordInterpolation != G_EX_COMPONENT_SKIP) && (curVertexCount == prevVertexCount)) {
            const std::vector<float> &curTcFloats = curWorkload.drawData.tcFloats;
            const std::vector<float> &prevTcFloats = prevWorkload.drawData.tcFloats;
            std::vector<float> &curVelFloats = curWorkload.drawData.tcVelFloats;
            const hlslpp::float2 WrappingModulo = curWorkload.extended.texcoordWrapPoint;
            const hlslpp::float2 WrappingModuloHalf = WrappingModulo / 2.0f;
            uint64_t curTcHash = XXH3_64bits(&curTcFloats[curVertexIndex * 2], curVertexCount * 2 * sizeof(float));
            uint64_t prevTcHash = XXH3_64bits(&prevTcFloats[prevVertexIndex * 2], prevVertexCount * 2 * sizeof(float));
            if (((texcoordInterpolation != G_EX_COMPONENT_AUTO) || (curVertexHash == prevVertexHash)) && (curTcHash != prevTcHash)) {
                const float *curTcFloatsRef = &curTcFloats[curVertexIndex * 2];
                const float *prevTcFloatsRef = &prevTcFloats[prevVertexIndex * 2];
                float *curVelFloatsRef = &curVelFloats[curVertexIndex * 2];
                for (uint32_t i = 0; i < curVertexCount; i++) {
                    const bool generatedVertex =
                        (i < wr64GeneratedVertex.size()) && (wr64GeneratedVertex[i] != 0) &&
                        (((i < wr64LatticeVertexOuter.size()) &&
                            (wr64LatticeVertexOuter[i] != 0)) ||
                         wr64CoherentOuterCoverage);
                    if (generatedVertex) {
                        // WATERLOCK-R3.
                        //
                        // Holding these at zero was right while the sheet was
                        // pinned, and is wrong now that it rewinds. A pool slot
                        // is not a stable point on the water -- the producer
                        // refills the same slots every frame and recenters the
                        // lattice underneath them -- so differencing slot i
                        // against slot i still produces a bogus UV velocity and
                        // is still not an option. But holding the UV nails the
                        // texture to the sheet, and the sheet now travels with
                        // the camera, so the texture stops moving on screen for
                        // the whole native frame and then jumps. On a surface
                        // whose entire sense of motion comes from its texture,
                        // that is indistinguishable from no interpolation.
                        //
                        // Same answer as the height, from the same triangle: the
                        // previous UV field is resampled at the point this
                        // vertex is rewound to. Exact where a previous sample
                        // coincides, linear inside the cell, and derived from
                        // position rather than from slot identity, so the
                        // recentering distance never enters it.
                        // WATERLOCK-R18 BISECT. Geometry or texture.
                        //
                        // The crease band repeats every 92 to 97 pixels and one
                        // lattice cell at that distance is 96, so it is the grid
                        // itself. Both the height and the texture coordinate live
                        // on that grid, and the texture coordinate is the one
                        // that is badly non-affine: fitted against a plane it
                        // deviates by up to 9 of a 16 unit span, because the game
                        // ripples this water by perturbing UVs per vertex rather
                        // than only by moving heights.
                        //
                        // RT64 walks each UV in a straight line between two of
                        // those states. A straight line between two non-affine
                        // fields is not a sampling of any real field in between,
                        // and the disagreement is largest halfway through a
                        // native frame -- which is exactly why 60 Hz looks worse
                        // than 180 Hz and why speed makes no difference.
                        //
                        // Holding the UV takes that out entirely while leaving
                        // the geometry interpolating as it does now. If the
                        // crease goes, it is the texture and the ripple animation
                        // is what has to be solved. If it stays, it is the height
                        // and the texture is exonerated. Either answer is worth
                        // more than the guess it replaces.
                        static const bool wr64HoldWaterTexcoords = false;
                        if (wr64HoldWaterTexcoords) {
                            curVelFloatsRef[i * 2 + 0] = 0.0f;
                            curVelFloatsRef[i * 2 + 1] = 0.0f;
                        }
                        else if (wr64PreviousSurfaceTexcoordValid &&
                            (i < wr64PreviousSurfaceHeightValid.size()) &&
                            (wr64PreviousSurfaceHeightValid[i] != 0))
                        {
                            curVelFloatsRef[i * 2 + 0] =
                                (curTcFloatsRef[i * 2 + 0] - wr64PreviousSurfaceU[i]);
                            curVelFloatsRef[i * 2 + 1] =
                                (curTcFloatsRef[i * 2 + 1] - wr64PreviousSurfaceV[i]);

                            // Same unwrap the stock path applies. The water
                            // texture tiles, so a coordinate that crossed the
                            // wrap point differences to nearly a whole period
                            // and would drag the texture the long way round.
                            if (fabsf(curVelFloatsRef[i * 2]) > WrappingModuloHalf[0]) {
                                curVelFloatsRef[i * 2] -= lround(curVelFloatsRef[i * 2] / WrappingModulo[0]) * WrappingModulo[0];
                            }

                            if (fabsf(curVelFloatsRef[i * 2 + 1]) > WrappingModuloHalf[1]) {
                                curVelFloatsRef[i * 2 + 1] -= lround(curVelFloatsRef[i * 2 + 1] / WrappingModulo[1]) * WrappingModulo[1];
                            }
                        }
                        else {
                            curVelFloatsRef[i * 2 + 0] = 0.0f;
                            curVelFloatsRef[i * 2 + 1] = 0.0f;
                        }

                        continue;
                    }

                    curVelFloatsRef[i * 2 + 0] = (curTcFloatsRef[i * 2 + 0] - prevTcFloatsRef[i * 2 + 0]);
                    curVelFloatsRef[i * 2 + 1] = (curTcFloatsRef[i * 2 + 1] - prevTcFloatsRef[i * 2 + 1]);

                    if (fabsf(curVelFloatsRef[i * 2]) > WrappingModuloHalf[0]) {
                        curVelFloatsRef[i * 2] -= lround(curVelFloatsRef[i * 2] / WrappingModulo[0]) * WrappingModulo[0];
                    }

                    if (fabsf(curVelFloatsRef[i * 2 + 1]) > WrappingModuloHalf[1]) {
                        curVelFloatsRef[i * 2 + 1] -= lround(curVelFloatsRef[i * 2 + 1] / WrappingModulo[1]) * WrappingModulo[1];
                    }
                }
            }

            modifiedBuffers.texcoordVelocity = true;

            if (forceGeneratedVertexInterpolation) {
                static uint32_t wr64TcProbeCount = 0;
                if (WR64_DIAGNOSTIC_ENABLED && wr64TcProbeCount < 40) {
                    wr64TcProbeCount++;
                    double tcSum = 0.0;
                    double tcMax = 0.0;
                    uint32_t tcCount = 0;
                    float *probeVel = &curWorkload.drawData.tcVelFloats[curVertexIndex * 2];
                    for (uint32_t p = 0; p < curVertexCount; p++) {
                        if ((p >= wr64GeneratedVertex.size()) || (wr64GeneratedVertex[p] == 0)) {
                            continue;
                        }

                        const double m = std::fabs(double(probeVel[p * 2 + 0])) + std::fabs(double(probeVel[p * 2 + 1]));
                        tcSum += m;
                        tcMax = std::max(tcMax, m);
                        tcCount++;
                    }

                    { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[waterlock] f=%llu tcVel mean=%.3f max=%.3f over %u wrap=(%.1f,%.1f)\n",
                        static_cast<unsigned long long>(curWorkload.submissionFrame),
                        (tcCount > 0) ? (tcSum / double(tcCount)) : 0.0, tcMax, tcCount,
                        double(WrappingModulo[0]), double(WrappingModulo[1])); }
                    { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
                }
            }
        }

        // The exact course-sky draw identified by its proven render signature
        // uses world transform 2. Its transform range starts with a generated
        // seven-vertex fan, but may also contain later vertices submitted under
        // the same matrix. The older diagnostic only recognized the separate
        // seven-vertex transform 1 and therefore never modified the visible
        // sky draw.
        //
        // The game periodically rebases the fan to an equivalent coordinate
        // chart: the center barely moves while all six outer vertices move
        // together by thousands of units and their UVs are rebased with them.
        // Both native endpoints are valid. Linear interpolation between the
        // two representations is not, and creates the one-output sky
        // "mutation". On that measured cut only, hold the complete exact-sky
        // transform at its current native endpoint.
        if (wr64SkyBracketLegacyGateEnabled() && protectExactSkyChartCut &&
            (curVertexCount == prevVertexCount) &&
            (curVertexCount >= 7U))
        {
            const std::vector<uint32_t> &curAddresses =
                curWorkload.drawData.vertexSegmentedAddresses;
            const bool addressesValid =
                (uint64_t(curVertexIndex) + curVertexCount) <=
                curAddresses.size();
            const bool positionVelocitiesValid =
                ((uint64_t(curVertexIndex) + curVertexCount) * 3ULL) <=
                curWorkload.drawData.velFloats.size();
            const bool texcoordVelocitiesValid =
                ((uint64_t(curVertexIndex) + curVertexCount) * 2ULL) <=
                curWorkload.drawData.tcVelFloats.size();

            float maximumDisagreement = 0.0f;
            uint32_t fanOffset = UINT32_MAX;
            if (addressesValid && positionVelocitiesValid) {
                const float *positionVelocities =
                    &curWorkload.drawData.velFloats[curVertexIndex * 3];
                for (uint32_t start = 0; (start + 7U) <= curVertexCount;
                    start++)
                {
                    const uint32_t addressBase =
                        curAddresses[curVertexIndex + start];
                    if ((addressBase & 0xFF000000U) != 0x06000000U) {
                        continue;
                    }

                    bool contiguousFan = true;
                    for (uint32_t vertex = 1; vertex < 7; vertex++) {
                        if (curAddresses[curVertexIndex + start + vertex] !=
                            (addressBase + (vertex * 0x10U)))
                        {
                            contiguousFan = false;
                            break;
                        }
                    }
                    if (!contiguousFan) {
                        continue;
                    }

                    const float *center =
                        &positionVelocities[start * 3];
                    float disagreement = 0.0f;
                    for (uint32_t vertex = 1; vertex < 7; vertex++) {
                        const float *outer =
                            &positionVelocities[(start + vertex) * 3];
                        const float dx = outer[0] - center[0];
                        const float dy = outer[1] - center[1];
                        const float dz = outer[2] - center[2];
                        disagreement = std::max(disagreement,
                            std::sqrt((dx * dx) + (dy * dy) + (dz * dz)));
                    }

                    if (disagreement > maximumDisagreement) {
                        maximumDisagreement = disagreement;
                        fanOffset = start;
                    }
                }
            }

            if ((fanOffset != UINT32_MAX) &&
                (maximumDisagreement > Wr64ExactSkyChartCutThreshold))
            {
                float *positionVelocities =
                    &curWorkload.drawData.velFloats[curVertexIndex * 3];
                std::fill(positionVelocities,
                    positionVelocities + (curVertexCount * 3), 0.0f);
                modifiedBuffers.positionVelocity = true;

                if (texcoordVelocitiesValid) {
                    float *texcoordVelocities =
                        &curWorkload.drawData.tcVelFloats[curVertexIndex * 2];
                    std::fill(texcoordVelocities,
                        texcoordVelocities + (curVertexCount * 2), 0.0f);
                    modifiedBuffers.texcoordVelocity = true;
                }

                curTransformMap.rigidBody.lerpTranslation = false;
                curTransformMap.rigidBody.lerpRotation = false;
                curTransformMap.rigidBody.lerpScale = false;
                curTransformMap.rigidBody.lerpSkew = false;
                curTransformMap.rigidBody.lerpPerspective = false;

                WR64_DIAGNOSTIC_LOG(wr64_forensic_record(
                    WR64_FORENSIC_EXACT_SKY_CUT,
                    curWorkload.submissionFrame,
                    curTransformIndex,
                    prevTransformIndex,
                    fanOffset,
                    curVertexCount,
                    uint64_t(std::llround(
                        double(maximumDisagreement) * 1000.0)),
                    uint64_t(std::llround(
                        double(Wr64ExactSkyChartCutThreshold) * 1000.0)),
                    0););
            }
        }

        if (isWr64ForensicPrimaryBackdropTransform(
                curWorkload.drawData, curTransformIndex))
        {
            const DrawData &curDraw = curWorkload.drawData;
            const DrawData &prevDraw = prevWorkload.drawData;
            const bool previousIsBackdrop =
                isWr64ForensicPrimaryBackdropTransform(prevDraw, prevTransformIndex);
            const bool currentArraysValid =
                ((uint64_t(curVertexIndex) + curVertexCount) * 3ULL <= curDraw.posFloats.size()) &&
                ((uint64_t(curVertexIndex) + curVertexCount) * 3ULL <= curDraw.velFloats.size()) &&
                ((uint64_t(curVertexIndex) + curVertexCount) * 2ULL <= curDraw.tcFloats.size()) &&
                ((uint64_t(curVertexIndex) + curVertexCount) * 2ULL <= curDraw.tcVelFloats.size());

            if (currentArraysValid) {
                WR64_DIAGNOSTIC_LOG(wr64_forensic_capture_rt64_sky(
                    1, curWorkload.submissionFrame, curTransformIndex,
                    prevTransformIndex,
                    &curDraw.posFloats[curVertexIndex * 3],
                    &curDraw.velFloats[curVertexIndex * 3],
                    &curDraw.tcFloats[curVertexIndex * 2],
                    &curDraw.tcVelFloats[curVertexIndex * 2],
                    curVertexCount,
                    reinterpret_cast<const float *>(curViewProj), nullptr););
            }

            const bool previousArraysValid = previousIsBackdrop &&
                ((uint64_t(prevVertexIndex) + prevVertexCount) * 3ULL <= prevDraw.posFloats.size()) &&
                ((uint64_t(prevVertexIndex) + prevVertexCount) * 2ULL <= prevDraw.tcFloats.size());
            if (previousArraysValid) {
                WR64_DIAGNOSTIC_LOG(wr64_forensic_capture_rt64_sky(
                    0, prevWorkload.submissionFrame, prevTransformIndex,
                    curTransformIndex,
                    &prevDraw.posFloats[prevVertexIndex * 3], nullptr,
                    &prevDraw.tcFloats[prevVertexIndex * 2], nullptr,
                    prevVertexCount,
                    reinterpret_cast<const float *>(prevViewProj), nullptr););
            }
        }
    }
    
    void GameFrame::buildCallHashMap(uint32_t sceneProjIndex, const Workload &workload, const Projection &proj, std::multimap<uint64_t, GameCallMap> &hashMap) const {
        for (uint32_t c = 0; c < proj.gameCallCount; c++) {
            const GameCall &call = proj.gameCalls[c];
            uint32_t matrixIdHash = 0;
            bool doTransformMatching = false;
            bool doTileInterpolation = false;
            bool doTileMatching = false;
            for (uint32_t m = call.callDesc.minWorldMatrix; m <= call.callDesc.maxWorldMatrix; m++) {
                const uint32_t groupIndex = workload.drawData.worldTransformGroups[m];
                const TransformGroup &group = workload.drawData.transformGroups[groupIndex];
                matrixIdHash = matrixIdHash * 33 ^ group.matrixId;

                const bool usesIdWithAutoOrdering = (group.matrixId != G_EX_ID_AUTO) && (group.matrixId != G_EX_ID_IGNORE) && (group.ordering == G_EX_ORDER_AUTO);
                doTransformMatching = doTransformMatching || (group.matrixId == G_EX_ID_AUTO) || usesIdWithAutoOrdering;
                doTileInterpolation = doTileInterpolation || (group.tileInterpolation != G_EX_COMPONENT_SKIP);
                doTileMatching = doTileMatching || (group.tileInterpolation == G_EX_COMPONENT_AUTO);
            }

            hashMap.emplace(hashFromCall(call, matrixIdHash), GameCallMap{ sceneProjIndex, c, doTransformMatching, doTileInterpolation, doTileMatching });
        }
    }

    void GameFrame::buildTransformIdMap(const Workload &workload, std::multimap<uint32_t, uint32_t> &idMap, std::vector<uint32_t> &ignoredIdVector) const {
        idMap.clear();
        ignoredIdVector.clear();

        uint32_t transformCount = uint32_t(workload.drawData.worldTransformGroups.size());
        for (uint32_t i = 0; i < transformCount; i++) {
            const uint32_t groupIndex = workload.drawData.worldTransformGroups[i];
            const TransformGroup &group = workload.drawData.transformGroups[groupIndex];
            if (group.matrixId == G_EX_ID_AUTO) {
                continue;
            }
            else if (group.matrixId == G_EX_ID_IGNORE) {
                ignoredIdVector.emplace_back(i);
            }
            else if (group.ordering == G_EX_ORDER_LINEAR) {
                idMap.emplace(group.matrixId, i);
            }
        }
    }

    uint64_t GameFrame::hashFromCall(const GameCall &call, uint32_t matrixIdHash) const {
        struct CallMatchKey {
            interop::ColorCombiner colorCombiner;
            interop::OtherMode otherMode;
            uint32_t geometryMode;
            uint32_t triangleCount;
            uint32_t matrixIdHash;
        };

        CallMatchKey key;
        key.colorCombiner = call.callDesc.colorCombiner;
        key.otherMode = call.callDesc.otherMode;
        key.geometryMode = call.callDesc.geometryMode;
        key.triangleCount = call.callDesc.triangleCount;
        key.matrixIdHash = matrixIdHash;
        const uint64_t baseHash = XXH3_64bits(&key, sizeof(CallMatchKey));

        // The course sky has two distinct logical draws with identical stock
        // match keys. In the captured Sunset Bay failure they alternate between
        // local call ordinals 3 and 5. A 192x192 clipped draw was therefore
        // allowed to contribute history to the following 1696x960 full-frame
        // draw (and vice versa), even though their combiner, other mode,
        // triangle count, and matrix-group ID are identical.
        //
        // Preserve the local ordinal only for this proven sky family. Across
        // the retained capture this leaves 371/375 consecutive sky transitions
        // matched normally and separates exactly the four 3<->5 transitions;
        // those four are also the only 44.17x rectangle-state changes. No other
        // draw family has its stock call hash changed.
        if (isWr64CourseSkyDraw(call.callDesc, matrixIdHash)) {
            struct SkyCallIdentity {
                uint64_t baseHash;
                uint32_t callIndex;
                uint32_t marker;
            };

            const SkyCallIdentity identity = {
                baseHash,
                call.callDesc.callIndex,
                0x534B5932U
            };
            return XXH3_64bits(&identity, sizeof(identity));
        }

        return baseHash;
    }

    bool GameFrame::isDebuggerCameraEnabled(const WorkloadQueue &workloadQueue) {
        for (uint32_t w : workloads) {
            if (workloadQueue.workloads[w].debuggerCamera.enabled) {
                return true;
            }
        }

        return false;
    }

    /*
    void resetTransformMap(GameTransformMap &transformMap, const GameFrame &gameFrame) {
        transformMap.fbPairs.resize(gameFrame.fbPairCount);
        for (uint32_t f = 0; f < gameFrame.fbPairCount; f++) {
            const auto &gameFbPair = gameFrame.fbPairs[f];
            auto &mapFbPair = transformMap.fbPairs[f];
            mapFbPair.projections.resize(gameFbPair.projectionCount, { });
            for (uint32_t p = 0; p < gameFbPair.projectionCount; p++) {
                mapFbPair.projections[p].drawCalls.clear();
                mapFbPair.projections[p].drawCalls.resize(gameFbPair.projections[p].drawCallCount, { });
                mapFbPair.projections[p].transformCallMap.clear();
            }

            mapFbPair.prevFbPairIndex = 0;
            mapFbPair.mapped = false;
        }

        transformMap.transforms.clear();
        transformMap.transforms.resize(gameFrame.drawData.worldTransforms.size(), { });
    }

    void makeTransformCallMap(GameProjection &gameProj, std::multimap<uint32_t, uint32_t> &callMap) {
        for (uint32_t d = 0; d < gameProj.drawCallCount; d++) {
            const auto &curCall = gameProj.drawCalls[d];
            const uint32_t startIndex = std::max(curCall.callDesc.minWorldMatrix, static_cast<uint16_t>(1));
            for (uint32_t t = startIndex; t <= curCall.callDesc.maxWorldMatrix; t++) {
                callMap.emplace(t, d);
            }
        }
    }

    void GameFrame::matchPreviousFrame(GameFrame &prevFrame, RenderWorker *worker, BufferUploader *bufferUploader) {
        assert(worker != nullptr);
        assert(bufferUploader != nullptr);
        transformMap.submissionFrame = prevFrame.submissionFrame;
        resetTransformMap(transformMap, *this);
        transformMap.mapped = true;

        static std::vector<bool> prevTransformMapped;
        static std::vector<TransformMatchCandidate> matchCandidates;
        bool uploadVelBuffer = false;
        const auto &prevDrawData = prevFrame.drawData;
        prevTransformMapped.clear();
        prevTransformMapped.resize(prevDrawData.worldTransforms.size(), false);
        for (uint32_t f = 0; f < fbPairCount; f++) {
            if (f >= prevFrame.fbPairCount) {
                continue;
            }

            // Check if the framebuffer pairs are actually compatible.
            auto &curFbPair = fbPairs[f];
            auto &prevFbPair = prevFrame.fbPairs[f];
            if ((curFbPair.colorImage.width != prevFbPair.colorImage.width) || (curFbPair.colorImage.fmt != prevFbPair.colorImage.fmt) || (curFbPair.colorImage.siz != prevFbPair.colorImage.siz)) {
                continue;
            }

            auto &fbPairMap = transformMap.fbPairs[f];
            fbPairMap.mapped = true;
            fbPairMap.prevFbPairIndex = f;

            for (uint32_t p = 0; p < curFbPair.projectionCount; p++) {
                if (p >= prevFbPair.projectionCount) {
                    continue;
                }

                // Check if the projections are actually compatible.
                auto &curProj = curFbPair.projections[p];
                auto &prevProj = prevFbPair.projections[p];
                if (curProj.type != prevProj.type) {
                    continue;
                }

                // TODO: Support more than just perspective projections.
                if (curProj.type != GameProjection::Type::Perspective) {
                    continue;
                }

                auto &projMap = fbPairMap.projections[p];
                auto &callMap = projMap.transformCallMap;
                projMap.mapped = true;
                projMap.prevProjectionIndex = p;
                makeTransformCallMap(curProj, callMap);

                // Make a map for the previous frame if it's empty.
                auto &prevFbMap = prevFrame.transformMap.fbPairs[fbPairMap.prevFbPairIndex];
                auto &prevCallMap = prevFbMap.projections[projMap.prevProjectionIndex].transformCallMap;
                if (prevCallMap.empty()) {
                    makeTransformCallMap(prevProj, prevCallMap);
                }

                // Find all candidates for all transforms.
                // TODO: This double loop explodes in complexity. Consider building a lookup table based on the
                // compatibility of the calls to reduce the iteration time drastically. These could be combiner
                // and other mode flags.
                matchCandidates.clear();
                // [WR64] THE PREVIOUS FRAME'S CAMERA COMES FROM THE PREVIOUS
                // FRAME. This read said drawData - the CURRENT frame's draw data
                // - indexed by the PREVIOUS projection's transformsIndex.
                //
                // Everything else in this loop already reads prevDrawData:
                // prevDrawData.worldTransforms[prevTransform] a few lines below,
                // prevDrawData for the call-compatibility test, prevDrawData for
                // the tiles. The scene matcher earlier in this file gets it right
                // too - firstPrevWorkload.drawData, not the current workload's.
                // This one line was the odd one out.
                //
                // WHAT IT BROKE. computeTransformMatch projects both world
                // positions and scores object identity on the distance between
                // them:
                //
                //     screenSpaceDifference = length(curScreenPos - prevScreenPos)
                //
                // With the wrong matrix that term is not a screen-space distance
                // at all. transformsIndex is a PER-FRAME slot, so the previous
                // projection's index resolves to whatever camera occupies that
                // slot in the CURRENT frame - and in split screen that is the
                // other player's camera. It is also an index from one frame's
                // array used against another frame's, which reads past the end
                // the moment the two frames hold a different number of them.
                //
                // WHY THE BOTTOM HALF. For the first projection the two indices
                // usually coincide, so the error is small and nothing shows. For
                // the second viewport the slot resolves to a different camera and
                // the term is wrong by the whole distance between the players.
                //
                // WHY WHEN ONE BOAT PASSES THE OTHER. computeDifference adds the
                // position, orientation and screen-space terms. While the craft
                // are apart the first two separate them by themselves. When they
                // close up those two go quiet, the corrupted third term is what
                // decides, and a craft is paired with the OTHER player's previous
                // transform - so it interpolates from over there for as long as
                // they are level. That is the camera appearing to lose track of
                // whose boat it is following.
                const hlslpp::float4x4 &curViewProj = drawData.viewProjTransforms[curProj.transformsIndex];
                const hlslpp::float4x4 &prevViewProj = prevDrawData.viewProjTransforms[prevProj.transformsIndex];
                for (auto curIt = callMap.begin(); curIt != callMap.end();) {
                    const uint32_t curTransform = curIt->first;
                    if (!transformMap.transforms[curTransform].mapped) {
                        const auto &curMatrix = drawData.worldTransforms[curTransform];
                        for (auto prevIt = prevCallMap.begin(); prevIt != prevCallMap.end();) {
                            const uint32_t prevTransform = prevIt->first;
                            if (!prevTransformMapped[prevTransform]) {
                                const auto prevMatrix = prevDrawData.worldTransforms[prevTransform];
                                if (isCallCompatible(curProj.drawCalls[curIt->second], drawData, prevProj.drawCalls[prevIt->second], prevDrawData)) {
                                    const TransformMatchResult matchResult = computeTransformMatch(curMatrix, curViewProj, prevMatrix, prevViewProj, prevFrame.transformMap.transforms[prevTransform].rigidBody);
                                    if (matchResult.valid) {
                                        matchCandidates.push_back({ curTransform, prevTransform, matchResult.computeDifference() });
                                    }
                                }
                            }

                            do { ++prevIt; } while (prevIt != prevCallMap.end() && (prevTransform == prevIt->first));
                        }
                    }

                    do { ++curIt; } while (curIt != callMap.end() && (curTransform == curIt->first));
                }

                // Sort all the candidates and assign them.
                std::stable_sort(matchCandidates.begin(), matchCandidates.end());
                for (const TransformMatchCandidate candidate : matchCandidates) {
                    if (transformMap.transforms[candidate.curTransformIndex].mapped) {
                        continue;
                    }

                    if (prevTransformMapped[candidate.prevTransformIndex]) {
                        continue;
                    }

                    auto &curTransformMap = transformMap.transforms[candidate.curTransformIndex];
                    const hlslpp::float4x4 &prevMatrix = prevDrawData.worldTransforms[candidate.prevTransformIndex];
                    const hlslpp::float4x4 &curMatrix = drawData.worldTransforms[candidate.curTransformIndex];
                    curTransformMap.rigidBody = prevFrame.transformMap.transforms[candidate.prevTransformIndex].rigidBody;
                    curTransformMap.rigidBody.updateLinear(prevMatrix, curMatrix);
                    curTransformMap.rigidBody.updateAngular(prevMatrix, curMatrix);
                    curTransformMap.rigidBody.updateDecomposition(curMatrix);
                    curTransformMap.prevTransformIndex = candidate.prevTransformIndex;
                    curTransformMap.mapped = true;
                    prevTransformMapped[candidate.prevTransformIndex] = true;

                    const auto prevRange = prevCallMap.equal_range(candidate.prevTransformIndex);
                    const auto curRange = callMap.equal_range(candidate.curTransformIndex);
                    auto prevRangeIt = prevRange.first;
                    auto curRangeIt = curRange.first;
                    while ((prevRangeIt != prevRange.second) && (curRangeIt != curRange.second)) {
                        // Check if any material defined a custom match callback for this call.
                        GameDrawCall *curCall = &curProj.drawCalls[curRangeIt->second];
                        GameDrawCall *prevCall = &prevProj.drawCalls[prevRangeIt->second];
                        if (curCall->lerpDesc.matchCallback != nullptr) {
                            curCall->lerpDesc.matchCallback(this, curCall, &prevFrame, prevCall);
                        }

                        // Check if the mesh positions are different and compute the velocity buffer if required.
                        // TODO: Compute the velocity buffer and compute the hash some way.
                        const bool meshHashDifference = false;
                        uploadVelBuffer = uploadVelBuffer || meshHashDifference;

                        // Check if the texture hashes are different to mark it as an animated texture material.
                        bool tmemHashDifference = false;
                        if (curCall->callDesc.tileCount == prevCall->callDesc.tileCount) {
                            const uint32_t curTileBase = curCall->callDesc.tileIndex;
                            const uint32_t prevTileBase = prevCall->callDesc.tileIndex;
                            for (uint32_t t = 0; t < curCall->callDesc.tileCount && !tmemHashDifference; t++) {
                                const auto &curTile = drawData.callTiles[curTileBase + t];
                                const auto &prevTile = prevDrawData.callTiles[prevTileBase + t];
                                tmemHashDifference = (curTile.tmemHashOrID != prevTile.tmemHashOrID);
                            }
                        }

                        // TODO: Reimplement.
                        //curCall->materialDesc.lockMask = tmemHashDifference ? 1.0f : 0.0f;

                        auto &drawCall = projMap.drawCalls[curRangeIt->second];
                        drawCall.prevCallIndex = prevRangeIt->second;
                        drawCall.mapped = true;
                        prevRangeIt++;
                        curRangeIt++;
                    }
                }
            }
        }
    }
    */
};
