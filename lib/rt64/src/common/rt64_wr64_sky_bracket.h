// WR64 sky bracket diagnostics sample the identified draw's own face indices.
// Do not infer its geometry from a transform-wide vertex count or segment prefix:
// other draws can share the transform.
//
// At fixed NDC sample points, project the fan at previous/current endpoints and
// intermediate weights. Compare perspective-correct texture coordinates against
// the endpoint segment to identify interpolation outside the native bracket.
// Near-plane projection makes the optional NDC check noisy, so it is disabled by
// default. Correlate violations with tile state as well as geometry.
//
// Calibration rotates the fan around its normal without changing UVs. Uniform
// UV-velocity injection remains linear and cannot calibrate this bracket test.
// WR64_SKY_BRACKET enables the detector; WR64_SKY_BRACKET_TRACE selects its CSV;
// WR64_SKY_BRACKET_HOLD holds a detected violation at the current endpoint;
// WR64_SKY_BRACKET_INJECT controls calibration frequency. Texture tolerance is
// set by WR64_SKY_BRACKET_TOLERANCE (default 16); WR64_SKY_BRACKET_USE_NDC and
// WR64_SKY_BRACKET_NDC control the optional NDC test (default tolerance 0.02).
// WR64_SKY_LEGACY_R3 retains the separate legacy segment-6 diagnostic.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "hle/rt64_game_frame.h"
#include "hle/rt64_workload.h"
#include "hle/rt64_workload_queue.h"

namespace RT64 {
    // ---------------------------------------------------------------------
    // Environment
    // ---------------------------------------------------------------------

    inline bool wr64SkyBracketEnvFlag(const char *name) {
        const char *value = std::getenv(name);
        return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
    }

    inline bool wr64SkyBracketEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_BRACKET");
        return enabled;
    }

    inline bool wr64SkyBracketHoldEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_BRACKET_HOLD");
        return enabled;
    }

    // The per-vertex NDC test measured p90 = 10.6 and a maximum of 48462 on a
    // real session: a backdrop fan reaches the near plane constantly, and a
    // vertex with a tiny positive w projects to enormous NDC. At any tolerance
    // that catches a real excursion it fires on nine frames in ten. It is now
    // logged but excluded from the verdict unless explicitly asked for.
    inline bool wr64SkyBracketUseNdc() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_BRACKET_USE_NDC");
        return enabled;
    }

    inline bool wr64SkyBracketLegacyGateEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_LEGACY_R3");
        return enabled;
    }

    inline uint64_t wr64SkyBracketInjectPeriod() {
        static const uint64_t period = []() -> uint64_t {
            const char *value = std::getenv("WR64_SKY_BRACKET_INJECT");
            if ((value == nullptr) || (value[0] == '\0')) {
                return 0;
            }

            const long long parsed = std::atoll(value);
            return (parsed > 0) ? uint64_t(parsed) : 0;
        }();

        return period;
    }

    inline float wr64SkyBracketTexelTolerance() {
        static const float tolerance = []() -> float {
            const char *value = std::getenv("WR64_SKY_BRACKET_TOLERANCE");
            if ((value == nullptr) || (value[0] == '\0')) {
                return 16.0f;
            }

            const double parsed = std::atof(value);
            return (parsed > 0.0) ? float(parsed) : 16.0f;
        }();

        return tolerance;
    }

    inline float wr64SkyBracketNdcTolerance() {
        static const float tolerance = []() -> float {
            const char *value = std::getenv("WR64_SKY_BRACKET_NDC");
            if ((value == nullptr) || (value[0] == '\0')) {
                return 0.02f;
            }

            const double parsed = std::atof(value);
            return (parsed > 0.0) ? float(parsed) : 0.02f;
        }();

        return tolerance;
    }

    inline FILE *wr64SkyBracketTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *file = []() -> FILE * {
            if (!wr64SkyBracketEnabled()) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_SKY_BRACKET_TRACE");
            const char *resolved = ((path != nullptr) && (path[0] != '\0')) ? path : "wr64-sky-bracket.csv";
            FILE *opened = std::fopen(resolved, "wb");
            if (opened == nullptr) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[sky-bracket] COULD NOT OPEN TRACE FILE '%s'. Another copy of the game is "
                    "probably still running and holding it. Nothing will be recorded this run.\n",
                    resolved); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }

            if (opened != nullptr) {
                std::fprintf(opened,
                    "detector_build,submission_frame,workload_id,occurrence,found,call_index,tri_count,unique_vertices,"
                    "min_world_matrix,max_world_matrix,matrix_id,matrix_id_hash,transform_mapped,"
                    "prev_transform_index,covered_samples,coverage_breaks,total_samples,wrap_u,wrap_v,"
                    "cover0,cover1,valid0,valid1,ndc_radius0,ndc_radius1,prev_match_error,map_error,map_residual,repaired,"
                    "sweep_total,sweep_vertices,sweep_world,sweep_viewproj,snapped,collapse_held,"
                    "cover_w0,cover_w25,cover_w50,cover_w75,cover_w100,area_swell,area_held,"
                    "g_decompose,g_pos,g_rot,g_scale,g_skew,g_persp,g_vertex,g_texcoord,g_tile,g_lookat,"
                    "g_ordering,g_aspect,g_editable,vp_matrix_id,vp_ordering,vp_decompose"
                    "worst_texel_deviation,worst_texel_weight,uv_span,"
                    "worst_ndc_deviation,worst_ndc_weight,ndc_span,"
                    "vertex_position_delta_max,vertex_texcoord_delta_max,"
                    "injected,violated,held\n");
                std::fflush(opened);
            }

            return opened;
        }();

        return file;
    }

    // ---------------------------------------------------------------------
    // The proven render signature of the visible course sky draw.
    //
    // Match the native draw state without assuming a matrix or vertex address.
    // RGB dithering changes color quantization, not this texture-coordinate
    // chart. The captured P2 cloud uses 00882CFF (dithering disabled), while P1
    // uses 00882C3F. Comparing those bits excluded P2 from both the established
    // rebase correction and its diagnostics. All other state remains exact.
    // ---------------------------------------------------------------------

    inline bool wr64SkyBracketIsExactSkyCall(const DrawCall &desc) {
        constexpr uint32_t rgbDitherMask = 3U << G_MDSFT_RGBDITHER;
        return
            (desc.triangleCount == 6U) &&
            (desc.colorCombiner.L == 0xFC11C223U) &&
            (desc.colorCombiner.H == 0xFF87FFFFU) &&
            (desc.otherMode.L == 0x00504240U) &&
            ((desc.otherMode.H & ~rgbDitherMask) == 0x00882C3FU);
    }

    struct Wr64SkyBracketLocation {
        bool found = false;
        uint32_t workloadIndex = 0;
        uint32_t fbPairIndex = 0;
        uint32_t projectionIndex = 0;
        uint32_t callIndex = 0;
        uint32_t faceIndicesStart = 0;
        uint32_t triangleCount = 0;
        uint32_t minWorldMatrix = 0;
        uint32_t maxWorldMatrix = 0;
        uint32_t transformsIndex = 0;
    };

    // Every occurrence, not the first. Two-player splits the screen and draws
    // the backdrop once per viewport, and a finder that stops at the first match
    // would measure one half and silently leave the other unexamined -- the same
    // class of mistake this whole file exists to undo.
    inline void wr64SkyBracketFindAll(const WorkloadQueue &workloadQueue, const GameScene &scene,
        std::vector<Wr64SkyBracketLocation> &out, uint32_t limit)
    {
        out.clear();
        for (const GameIndices::Projection &indices : scene.projections) {
            if (indices.workloadIndex >= workloadQueue.workloads.size()) {
                continue;
            }

            const Workload &workload = workloadQueue.workloads[indices.workloadIndex];
            if (indices.fbPairIndex >= workload.fbPairs.size()) {
                continue;
            }

            const FramebufferPair &fbPair = workload.fbPairs[indices.fbPairIndex];
            if (indices.projectionIndex >= fbPair.projections.size()) {
                continue;
            }

            const Projection &projection = fbPair.projections[indices.projectionIndex];
            const uint32_t callCount = std::min(projection.gameCallCount, uint32_t(projection.gameCalls.size()));
            for (uint32_t c = 0; c < callCount; c++) {
                const GameCall &call = projection.gameCalls[c];
                if (!wr64SkyBracketIsExactSkyCall(call.callDesc)) {
                    continue;
                }

                Wr64SkyBracketLocation location;
                location.found = true;
                location.workloadIndex = indices.workloadIndex;
                location.fbPairIndex = indices.fbPairIndex;
                location.projectionIndex = indices.projectionIndex;
                location.callIndex = c;
                location.faceIndicesStart = call.meshDesc.faceIndicesStart;
                location.triangleCount = call.callDesc.triangleCount;
                location.minWorldMatrix = call.callDesc.minWorldMatrix;
                location.maxWorldMatrix = call.callDesc.maxWorldMatrix;
                location.transformsIndex = projection.transformsIndex;
                out.push_back(location);
                if (uint32_t(out.size()) >= limit) {
                    return;
                }
            }
        }
    }

    // ---------------------------------------------------------------------
    // Evaluation
    // ---------------------------------------------------------------------

    struct Wr64SkyBracketVertex {
        float ndcX = 0.0f;
        float ndcY = 0.0f;
        float invW = 0.0f;
        float u = 0.0f;
        float v = 0.0f;
        // Clip space is kept as well as NDC. NDC does not exist for a vertex behind
        // the eye, and this fan has one on every frame measured, so the sampler has
        // to clip rather than discard.
        float clipX = 0.0f;
        float clipY = 0.0f;
        float clipW = 0.0f;
        bool finite = false;
        bool valid = false;
    };
    // Row vector times matrix, matching this renderer's convention
    // (see computeTransformMatch: hlslpp::mul(transform[3], viewProj)).
    inline void wr64SkyBracketProjectClip(const float *position, const hlslpp::float4x4 &world,
        const hlslpp::float4x4 &viewProj, Wr64SkyBracketVertex &out)
    {
        const hlslpp::float4 local(position[0], position[1], position[2], 1.0f);
        const hlslpp::float4 worldPosition = hlslpp::mul(local, world);
        const hlslpp::float4 clipPosition = hlslpp::mul(worldPosition, viewProj);
        out.clipX = float(clipPosition.x);
        out.clipY = float(clipPosition.y);
        out.clipW = float(clipPosition.w);
        out.finite = std::isfinite(out.clipX) && std::isfinite(out.clipY) && std::isfinite(out.clipW);
        if (out.finite && (out.clipW > 1.0e-6f)) {
            out.ndcX = out.clipX / out.clipW;
            out.ndcY = out.clipY / out.clipW;
            out.invW = 1.0f / out.clipW;
            out.valid = true;
        }
        else {
            out.ndcX = 0.0f;
            out.ndcY = 0.0f;
            out.invW = 0.0f;
            out.valid = false;
        }
    }

    inline void wr64SkyBracketProject(const float *position, const hlslpp::float4x4 &world, const hlslpp::float4x4 &viewProj,
        float &outX, float &outY, float &outInvW)
    {
        const hlslpp::float4 local(position[0], position[1], position[2], 1.0f);
        const hlslpp::float4 worldPosition = hlslpp::mul(local, world);
        const hlslpp::float4 clipPosition = hlslpp::mul(worldPosition, viewProj);
        const float clipX = float(clipPosition.x);
        const float clipY = float(clipPosition.y);
        const float clipW = float(clipPosition.w);

        // Strictly positive, not merely non-zero. A vertex behind the eye has
        // negative w, and dividing by it mirrors the point through the origin:
        // the barycentric test would then happily "cover" a sample point with a
        // triangle that is not on screen at all, and report a violation that
        // never reached a pixel. Treating those vertices as invalid loses the
        // sample instead, which is the safe direction to fail in.
        if (!(clipW > 1.0e-6f) || !std::isfinite(clipW)) {
            outX = 0.0f;
            outY = 0.0f;
            outInvW = 0.0f;
            return;
        }

        outX = clipX / clipW;
        outY = clipY / clipW;
        outInvW = 1.0f / clipW;
    }

    // Perspective-correct sample of the fan at one NDC point.
    // Returns false when no triangle covers the point.
    // Sample the fan at a screen point, clipping against the near plane instead of
    // discarding triangles that cross it.
    //
    // The previous version required all three vertices of a triangle to be in front
    // of the eye and skipped the triangle otherwise. On this draw that was fatal:
    // valid0/valid1 read 6 of 7 on every frame of every run, so one vertex is always
    // behind the eye, and the layer dump puts this draw's area at 1628160 quarter
    // pixels -- exactly 1696x960, the whole screen -- while the sampler was only
    // ever covering 5 to 10 of its 25 sample points. Every measurement taken with it
    // described a third of the sky, and specifically not the part crossing the near
    // plane. The renderer clips these triangles; so does this now.
    //
    // Clipping is done in homogeneous space, where u, v and position are all linear,
    // so the interpolated attributes on a clipped edge are exact. One plane against
    // a triangle yields at most four vertices.
    inline bool wr64SkyBracketSampleFan(const std::vector<Wr64SkyBracketVertex> &vertices,
        const std::vector<uint32_t> &localFaces, float pointX, float pointY, float &outU, float &outV)
    {
        struct ClipVertex {
            float x = 0.0f, y = 0.0f, w = 0.0f, u = 0.0f, v = 0.0f;
        };

        const float NearW = 1.0e-5f;
        const size_t triangleCount = localFaces.size() / 3;
        for (size_t t = 0; t < triangleCount; t++) {
            const Wr64SkyBracketVertex *corner[3] = {
                &vertices[localFaces[(t * 3) + 0]],
                &vertices[localFaces[(t * 3) + 1]],
                &vertices[localFaces[(t * 3) + 2]]
            };

            if (!corner[0]->finite || !corner[1]->finite || !corner[2]->finite) {
                continue;
            }

            ClipVertex polygon[5];
            uint32_t polygonCount = 0;
            for (uint32_t i = 0; i < 3; i++) {
                const Wr64SkyBracketVertex &from = *corner[i];
                const Wr64SkyBracketVertex &to = *corner[(i + 1) % 3];
                const bool fromInside = (from.clipW > NearW);
                const bool toInside = (to.clipW > NearW);
                if (fromInside && (polygonCount < 5)) {
                    polygon[polygonCount++] = { from.clipX, from.clipY, from.clipW, from.u, from.v };
                }

                if ((fromInside != toInside) && (polygonCount < 5)) {
                    const float denominator = to.clipW - from.clipW;
                    if (std::fabs(denominator) < 1.0e-20f) {
                        continue;
                    }

                    const float s = (NearW - from.clipW) / denominator;
                    polygon[polygonCount++] = {
                        from.clipX + ((to.clipX - from.clipX) * s),
                        from.clipY + ((to.clipY - from.clipY) * s),
                        NearW,
                        from.u + ((to.u - from.u) * s),
                        from.v + ((to.v - from.v) * s)
                    };
                }
            }

            if (polygonCount < 3) {
                continue;
            }

            // The clipped polygon is convex and entirely in front of the eye, so a
            // triangle fan over it is a valid decomposition.
            for (uint32_t k = 1; (k + 1) < polygonCount; k++) {
                const ClipVertex &pa = polygon[0];
                const ClipVertex &pb = polygon[k];
                const ClipVertex &pc = polygon[k + 1];
                const float ax = pa.x / pa.w, ay = pa.y / pa.w, ai = 1.0f / pa.w;
                const float bx = pb.x / pb.w, by = pb.y / pb.w, bi = 1.0f / pb.w;
                const float cx = pc.x / pc.w, cy = pc.y / pc.w, ci = 1.0f / pc.w;
                if (!std::isfinite(ax) || !std::isfinite(bx) || !std::isfinite(cx)) {
                    continue;
                }

                const float v0x = bx - ax, v0y = by - ay;
                const float v1x = cx - ax, v1y = cy - ay;
                const float denominator = (v0x * v1y) - (v1x * v0y);
                if (std::fabs(denominator) < 1.0e-12f) {
                    continue;
                }

                const float v2x = pointX - ax, v2y = pointY - ay;
                const float beta = ((v2x * v1y) - (v1x * v2y)) / denominator;
                const float gamma = ((v0x * v2y) - (v2x * v0y)) / denominator;
                const float alpha = 1.0f - beta - gamma;
                const float edgeEpsilon = -1.0e-4f;
                if ((alpha < edgeEpsilon) || (beta < edgeEpsilon) || (gamma < edgeEpsilon)) {
                    continue;
                }

                const float weightSum = (alpha * ai) + (beta * bi) + (gamma * ci);
                if (!(std::fabs(weightSum) > 1.0e-12f) || !std::isfinite(weightSum)) {
                    continue;
                }

                outU = ((alpha * pa.u * ai) + (beta * pb.u * bi) + (gamma * pc.u * ci)) / weightSum;
                outV = ((alpha * pa.v * ai) + (beta * pb.v * bi) + (gamma * pc.v * ci)) / weightSum;
                if (std::isfinite(outU) && std::isfinite(outV)) {
                    return true;
                }
            }
        }

        return false;
    }

    // Distance from a point to the segment [p0, p1], counting overshoot past
    // either end. This is the whole test: zero means the interpolated result is
    // somewhere between the two native results, which is the only place it is
    // allowed to be.
    inline float wr64SkyBracketSegmentDeviation(float px, float py, float x0, float y0, float x1, float y1) {
        const float dx = x1 - x0;
        const float dy = y1 - y0;
        const float lengthSquared = (dx * dx) + (dy * dy);
        if (lengthSquared < 1.0e-12f) {
            const float ex = px - x0;
            const float ey = py - y0;
            return std::sqrt((ex * ex) + (ey * ey));
        }

        float t = (((px - x0) * dx) + ((py - y0) * dy)) / lengthSquared;
        t = std::max(0.0f, std::min(1.0f, t));
        const float ex = px - (x0 + (t * dx));
        const float ey = py - (y0 + (t * dy));
        return std::sqrt((ex * ex) + (ey * ey));
    }

    inline float wr64SkyBracketUnwrap(float value, float reference, float modulo) {
        if (!(modulo > 0.0f)) {
            return value;
        }

        const float difference = value - reference;
        if (std::fabs(difference) <= (modulo * 0.5f)) {
            return value;
        }

        return value - (std::round(difference / modulo) * modulo);
    }


    // ---------------------------------------------------------------------
    // Event dump
    //
    // prev_match_error came back 0.000 on every one of 2440 frames, so RT64's
    // pairing is exact: current-minus-velocity IS the previous frame's sky,
    // vertex for vertex. The thousand-unit jumps are therefore real -- the game's
    // own producer re-anchors the fan -- and RT64 is faithfully interpolating
    // across a discontinuity that should never be interpolated at all.
    //
    // That is the chart rebase, confirmed on the visible draw for the first time.
    // What is still unknown is its exact structure: what the seven vertices and
    // their texture coordinates actually do across one of these events, and
    // whether the world matrix or view projection compensates. Designing a
    // correction without that is guesswork, and this project has had enough of
    // that. So on every large event, dump everything needed to reconstruct it
    // offline: both native states in full, plus both matrices.
    // ---------------------------------------------------------------------

    inline float wr64SkyBracketEventThreshold() {
        static const float threshold = []() -> float {
            const char *value = std::getenv("WR64_SKY_BRACKET_EVENT_DELTA");
            if ((value == nullptr) || (value[0] == '\0')) {
                return 500.0f;
            }

            const double parsed = std::atof(value);
            return (parsed > 0.0) ? float(parsed) : 500.0f;
        }();

        return threshold;
    }

    inline FILE *wr64SkyBracketEventFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *file = []() -> FILE * {
            if (!wr64SkyBracketEnabled()) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_SKY_BRACKET_EVENTS");
            const char *resolved = ((path != nullptr) && (path[0] != '\0')) ? path : "wr64-sky-bracket-events.txt";
            return std::fopen(resolved, "wb");
        }();

        return file;
    }

    inline void wr64SkyBracketWriteMatrix(FILE *file, const char *tag, uint64_t frame, const hlslpp::float4x4 &m) {
        std::fprintf(file, "%s,%llu", tag, static_cast<unsigned long long>(frame));
        for (uint32_t r = 0; r < 4; r++) {
            const hlslpp::float4 row = m[r];
            std::fprintf(file, ",%.6f,%.6f,%.6f,%.6f",
                float(row.x), float(row.y), float(row.z), float(row.w));
        }

        std::fprintf(file, "\n");
    }


    // ---------------------------------------------------------------------
    // THE REPAIR
    //
    // What the sky actually is, measured: a flat hexagonal patch at constant
    // height, seven vertices, whose texture coordinates lie exactly on one affine
    // map from world position to texel (fit residual 0.005 across every event, and
    // the seventh vertex sits on the same map as the other six). The game slides
    // that patch to follow the camera and adjusts the map to match, so the patch's
    // own position is invisible: what you see is decided entirely by the map.
    //
    // Twice a race or so the game re-centres the patch in one large step -- 4475,
    // 5288, 9395 units measured, against 40 in an ordinary frame -- and changes the
    // map in the same frame. Both native frames are correct. RT64 then interpolates
    // the vertex positions and the texture coordinates separately and linearly,
    // and that is where it breaks:
    //
    //     uv_i(w)  =  lerp(uv_i_prev, uv_i_cur)
    //     but the correct answer is  M_w( pos_i(w) ),  M_w = lerp(M_prev, M_cur)
    //
    // Expand the second one and the two agree except for a single quadratic term,
    // dA . dp . w(1-w), where dA is the change in the map and dp the change in
    // position. In an ordinary frame dp is 40 and the term vanishes. On a
    // re-centring frame dp is thousands and it does not:
    //
    //     frame  179   ring jump 9395   error 17.11 texture units  (span 164)
    //     frame  239   ring jump 4475   error  6.59               (span 103)
    //     frame 1789   ring jump 5288   error  1.09               (span 105)
    //     every ordinary frame          error  0.00 to 0.01
    //
    // Seventeen texture units out of a hundred and sixty is a tenth of the visible
    // sky, arriving and leaving inside one native interval. That is the mutation.
    //
    // The fix removes the term rather than suppressing its effect. dp is what
    // multiplies the error, and dp is the patch's re-centring, which is invisible.
    // So hold the geometry across the interval -- dp becomes exactly zero -- and
    // give each vertex the texture coordinate the PREVIOUS map assigns to its
    // CURRENT position. The interpolation is then exactly M_w at every weight, for
    // every vertex, with no residual at all. Not a threshold, not a gate, not a
    // freeze: the sky keeps moving smoothly through the whole interval, because the
    // map is what moves it.
    //
    // Safe on ordinary frames too, so it runs unconditionally: when dp is small the
    // correction is arithmetically indistinguishable from stock behaviour. Holding
    // the patch for one native interval displaces it relative to the camera by at
    // most that frame's camera motion (765 to 1100 units measured) against a patch
    // inradius of 2598, so it cannot uncover the view.
    //
    // Falls back to stock behaviour whenever the premise fails: if the previous
    // draw is missing, if the vertex count changed, or if the texture coordinates
    // do not actually lie on a plane map.
    // ---------------------------------------------------------------------

    struct Wr64SkyPlaneMap {
        bool valid = false;
        uint32_t axisA = 0;
        uint32_t axisB = 2;
        float u[3] = { 0.0f, 0.0f, 0.0f };
        float v[3] = { 0.0f, 0.0f, 0.0f };
        float residual = 0.0f;
    };

    inline bool wr64SkySolve3(double m[3][3], double r[3], double out[3]) {
        for (uint32_t c = 0; c < 3; c++) {
            uint32_t pivot = c;
            for (uint32_t k = c + 1; k < 3; k++) {
                if (std::fabs(m[k][c]) > std::fabs(m[pivot][c])) { pivot = k; }
            }

            if (std::fabs(m[pivot][c]) < 1e-9) { return false; }
            if (pivot != c) {
                for (uint32_t j = 0; j < 3; j++) { std::swap(m[c][j], m[pivot][j]); }
                std::swap(r[c], r[pivot]);
            }

            for (uint32_t k = 0; k < 3; k++) {
                if (k == c) { continue; }
                const double factor = m[k][c] / m[c][c];
                for (uint32_t j = c; j < 3; j++) { m[k][j] -= factor * m[c][j]; }
                r[k] -= factor * r[c];
            }
        }

        for (uint32_t i = 0; i < 3; i++) { out[i] = r[i] / m[i][i]; }
        return true;
    }

    // Fit uv = A*axisA + B*axisB + C over the fan's own vertices.
    inline Wr64SkyPlaneMap wr64SkyFitPlaneMap(const std::vector<float> &positions, const std::vector<float> &texcoords) {
        Wr64SkyPlaneMap map;
        const uint32_t count = uint32_t(positions.size() / 3);
        if (count < 3) { return map; }

        // Use the two axes the patch actually spreads over; the third is flat.
        float minimum[3] = { positions[0], positions[1], positions[2] };
        float maximum[3] = { positions[0], positions[1], positions[2] };
        for (uint32_t i = 1; i < count; i++) {
            for (uint32_t axis = 0; axis < 3; axis++) {
                minimum[axis] = std::min(minimum[axis], positions[(i * 3) + axis]);
                maximum[axis] = std::max(maximum[axis], positions[(i * 3) + axis]);
            }
        }

        uint32_t order[3] = { 0, 1, 2 };
        for (uint32_t a = 0; a < 3; a++) {
            for (uint32_t b = a + 1; b < 3; b++) {
                if ((maximum[order[b]] - minimum[order[b]]) > (maximum[order[a]] - minimum[order[a]])) {
                    std::swap(order[a], order[b]);
                }
            }
        }

        map.axisA = order[0];
        map.axisB = order[1];

        double m[3][3] = {};
        double ru[3] = {};
        double rv[3] = {};
        for (uint32_t i = 0; i < count; i++) {
            const double a = positions[(i * 3) + map.axisA];
            const double b = positions[(i * 3) + map.axisB];
            const double u = texcoords[(i * 2) + 0];
            const double v = texcoords[(i * 2) + 1];
            m[0][0] += a * a; m[0][1] += a * b; m[0][2] += a;
            m[1][0] += a * b; m[1][1] += b * b; m[1][2] += b;
            m[2][0] += a;     m[2][1] += b;     m[2][2] += 1.0;
            ru[0] += a * u; ru[1] += b * u; ru[2] += u;
            rv[0] += a * v; rv[1] += b * v; rv[2] += v;
        }

        double mu[3][3]; double mv[3][3];
        std::memcpy(mu, m, sizeof(m));
        std::memcpy(mv, m, sizeof(m));
        double su[3]; double sv[3];
        if (!wr64SkySolve3(mu, ru, su) || !wr64SkySolve3(mv, rv, sv)) { return map; }

        for (uint32_t i = 0; i < 3; i++) {
            map.u[i] = float(su[i]);
            map.v[i] = float(sv[i]);
        }

        for (uint32_t i = 0; i < count; i++) {
            const float a = positions[(i * 3) + map.axisA];
            const float b = positions[(i * 3) + map.axisB];
            map.residual = std::max(map.residual,
                std::fabs((map.u[0] * a) + (map.u[1] * b) + map.u[2] - texcoords[(i * 2) + 0]));
            map.residual = std::max(map.residual,
                std::fabs((map.v[0] * a) + (map.v[1] * b) + map.v[2] - texcoords[(i * 2) + 1]));
        }

        map.valid = std::isfinite(map.residual);
        return map;
    }

    // ---------------------------------------------------------------------
    // TEXCOORD COLLAPSE GUARD
    //
    // The signature, measured on a full race once the sampler stopped discarding
    // near-plane triangles: frames 1273 to 1307, a 1.7 second cluster, endpoint
    // span 0.3 to 1.6 texture units -- the two native frames put the SAME sky on
    // that screen point -- while the interpolated middle sat 200 to 672 units away
    // from both. Position delta a normal 46. Texture coordinate velocity 82 to 1078.
    //
    // Both real frames agree and the frame between them does not. That is the
    // defect stated exactly, and it is what a coordinate chart rebase looks like
    // from the screen: the producer renumbers the texture coordinates, both native
    // frames still draw the same sky through the new numbers and the old, and only
    // the interpolation between the two numberings is meaningless.
    //
    // So the condition is not a tuned threshold. It is: the endpoints agree, the
    // middle does not. Ordinary motion cannot produce that -- if the sky is moving,
    // the endpoints differ, and the span does not collapse. When it happens, the
    // texture coordinates for that one interval are not interpolated; the geometry
    // still is, so the sky keeps moving.
    // ---------------------------------------------------------------------

    // ---------------------------------------------------------------------
    // AREA GUARD
    //
    // Measured over a 111 second race: area_swell was 0.0000 on every frame
    // including the 99th percentile, and 1.50 on exactly one -- frame 1242 at
    // 62.1 seconds, coverage 10, 25, 25, 25, 10. The sky covers ten of twenty-five
    // sample points at BOTH native frames and all twenty-five at every weight in
    // between. Its texel deviation on that frame was 0.9 and its position delta 73,
    // both entirely ordinary, which is why every earlier test reported it clean.
    //
    // That is the same event the screenshots caught: 15 percent, 35 percent, 15
    // percent, over consecutive presented frames with the HUD frozen. One per race,
    // and nothing else in the run comes near it.
    //
    // The endpoints bracket the truth. An interpolated frame that covers more of
    // the screen than either native frame is drawing sky where neither of them put
    // any, and the fix is to not invent that interval: hold the patch where the
    // current native frame has it. Fifty milliseconds, once a race, against the sky
    // filling the screen and snapping back.
    // ---------------------------------------------------------------------

    // The sky is tagged TEXCOORD = INTERPOLATE, which opts it out of RT64's own
    // chart-rebase guard at rt64_game_frame.cpp:3227 -- under AUTO, texture
    // coordinates are only interpolated when the vertex positions are unchanged.
    // This flips that one value back for the 0x575243xx group and leaves every
    // other component of the flicker fix alone.
    // Log every distinct matrix id that passes through RSP::matrixId, once each,
    // and whether the override fired on it. The sky's own group reads 57524300, the
    // override is reaching the game -- it visibly changes the water -- and yet the
    // sky's group still dumps as INTERPOLATE. One of those three facts is wrong and
    // this says which.
    inline void wr64SkyNoteMatrixId(uint32_t id, bool overridden) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static FILE *file = []() -> FILE * {
            return wr64SkyBracketEnvFlag("WR64_SKY_TC_AUTO") ? std::fopen("wr64-sky-matrixids.txt", "wb") : nullptr;
        }();

        if (file == nullptr) {
            return;
        }

        static std::vector<uint32_t> seen;
        for (uint32_t i = 0; i < uint32_t(seen.size()); i++) {
            if (seen[i] == id) {
                return;
            }
        }

        if (seen.size() >= 512) {
            return;
        }

        seen.push_back(id);
        std::fprintf(file, "%08X  override=%u\n", id, uint32_t(overridden));
        std::fflush(file);
    }

    // ---------------------------------------------------------------------
    // THE FIX
    //
    // Proven by running it: TEXCOORD = INTERPOLATE gives a smooth sky and the
    // once-per-race mutation, because it blends texture coordinates straight
    // across the frames where the producer renumbers them. TEXCOORD = AUTO removes
    // the mutation completely -- two full races, Sunny Beach and Sunset Bay, zero
    // occurrences -- but AUTO means "interpolate only when the vertex positions are
    // unchanged", and this fan moves every frame, so the texture stops
    // interpolating at all and the old fast flicker returns.
    //
    // Neither setting is right because the object needs different behaviour on
    // different frames. Keep INTERPOLATE so the texture stays smooth, and drop the
    // texture-coordinate velocity only on the frames where the patch is actually
    // re-anchored.
    //
    // Those frames are unambiguous in the measurements: ordinary motion moves the
    // vertices about 40 units with a 99th percentile of 207, and a re-anchor moves
    // them 3000 to 9395. Fifteen times the tail, with nothing in the gap.
    // ---------------------------------------------------------------------

    // DEFAULT ON. This is the fix, not an experiment: it is what removes the sky
    // mutation, and it ships enabled whether or not the detector is armed.
    // WR64_SKY_TC_SMART=0 turns it off for A/B comparison; anything else, including
    // leaving it unset, leaves it on.
    inline bool wr64SkyTexcoordSmartEnabled() {
        static const bool enabled = []() -> bool {
            const char *value = std::getenv("WR64_SKY_TC_SMART");
            if ((value == nullptr) || (value[0] == '\0')) {
                return true;
            }

            return (value[0] != '0');
        }();

        return enabled;
    }

    // The renumbering is visible in the TEXTURE COORDINATES, not the geometry.
    // Measured across two full races: texcoord delta has a median of 0.75 units per
    // frame, and at the mutation cluster it ran 82 to 1078 while the position delta
    // stayed at an entirely ordinary 46. Triggering on position missed it, which is
    // exactly what happened. Twenty units is twenty-seven times the median.
    inline float wr64SkyTexcoordJumpThreshold() {
        static const float threshold = []() -> float {
            const char *value = std::getenv("WR64_SKY_TC_JUMP");
            if ((value == nullptr) || (value[0] == '\0')) { return 20.0f; }
            const double parsed = std::atof(value);
            return (parsed > 0.0) ? float(parsed) : 20.0f;
        }();

        return threshold;
    }

    inline float wr64SkyReanchorThreshold() {
        static const float threshold = []() -> float {
            const char *value = std::getenv("WR64_SKY_REANCHOR");
            if ((value == nullptr) || (value[0] == '\0')) { return 1000.0f; }
            const double parsed = std::atof(value);
            return (parsed > 0.0) ? float(parsed) : 1000.0f;
        }();

        return threshold;
    }

    inline bool wr64SkyTexcoordAutoEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_TC_AUTO");
        return enabled;
    }

    inline bool wr64SkyAreaGuardEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_AREA_GUARD");
        return enabled;
    }

    inline bool wr64SkyCollapseGuardEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_COLLAPSE_GUARD");
        return enabled;
    }

    inline bool wr64SkySnapEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_SNAP");
        return enabled;
    }

    inline float wr64SkySnapThreshold() {
        static const float threshold = []() -> float {
            const char *value = std::getenv("WR64_SKY_SNAP_NDC");
            if ((value == nullptr) || (value[0] == '\0')) { return 0.25f; }
            const double parsed = std::atof(value);
            return (parsed > 0.0) ? float(parsed) : 0.25f;
        }();

        return threshold;
    }

    inline bool wr64SkyMapInterpolationEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_SKY_MAP_INTERP");
        return enabled;
    }

    // Record sky tile state independently of geometry. Tile interpolation uses
    // prevUls/prevUlt derived from inherited deltas; stale wrap history can move the
    // sampled window even when vertices and UVs remain well behaved. Log native
    // windows, inherited deltas, mapping flags, format, and wrap settings rather
    // than inferring a tile fault from the geometry test alone.

    inline FILE *wr64TileProbeFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *file = []() -> FILE * {
            if (!wr64SkyBracketEnvFlag("WR64_SKY_TILE_PROBE")) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_SKY_TILE_TRACE");
            const char *resolved = ((path != nullptr) && (path[0] != '\0')) ? path : "wr64-sky-tiles.csv";
            FILE *opened = std::fopen(resolved, "wb");
            if (opened == nullptr) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[sky-tile] COULD NOT OPEN '%s'\n", resolved); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
                return nullptr;
            }

            std::fprintf(opened,
                "submission_frame,tile_slot,tile_index,mapped,"
                "cur_uls,cur_ult,cur_lrs,cur_lrt,prev_uls,prev_ult,prev_lrs,prev_lrt,"
                "delta_uls,delta_ult,delta_lrs,delta_lrt,"
                "jump_uls,jump_ult,jump_lrs,jump_lrt,"
                "masks,maskt,shifts,shiftt,cms,cmt,fmt,siz,stride,address,palette,"
                "wrap_periods_uls,wrap_periods_ult\n");
            return opened;
        }();

        return file;
    }

    inline void wr64TileProbeWrite(const Workload &curWorkload, const GameCall &call,
        GameFrameMap::WorkloadMap &curWorkloadMap, uint64_t submissionFrame)
    {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        FILE *file = wr64TileProbeFile();
        if (file == nullptr) { return; }

        const DrawData &draw = curWorkload.drawData;
        const uint32_t tileCount = std::min(call.callDesc.tileCount, 8U);
        for (uint32_t t = 0; t < tileCount; t++) {
            const uint32_t tileIndex = call.callDesc.tileIndex + t;
            if (tileIndex >= draw.rdpTiles.size()) { break; }
            if (tileIndex >= curWorkloadMap.tiles.size()) { break; }

            const interop::RDPTile &tile = draw.rdpTiles[tileIndex];
            const GameFrameMap::TileMap &map = curWorkloadMap.tiles[tileIndex];

            // How far the interpolation will actually travel this interval, and how
            // many texture wrap periods that is. Anything at or beyond one period is
            // the whole texture sliding through the frame.
            const float jumpUls = tile.uls - map.prevUls;
            const float jumpUlt = tile.ult - map.prevUlt;
            const float periodS = float(tile.masks) * 4.0f;
            const float periodT = float(tile.maskt) * 4.0f;

            std::fprintf(file,
                "%llu,%u,%u,%u,"
                "%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,"
                "%.3f,%.3f,%.3f,%.3f,"
                "%.3f,%.3f,%.3f,%.3f,"
                "%d,%d,%.3f,%.3f,%d,%d,%d,%d,%d,%08X,%d,"
                "%.4f,%.4f\n",
                static_cast<unsigned long long>(submissionFrame), t, tileIndex, uint32_t(map.mapped),
                tile.uls, tile.ult, tile.lrs, tile.lrt,
                map.prevUls, map.prevUlt, map.prevLrs, map.prevLrt,
                map.deltaUls, map.deltaUlt, map.deltaLrs, map.deltaLrt,
                jumpUls, jumpUlt, tile.lrs - map.prevLrs, tile.lrt - map.prevLrt,
                tile.masks, tile.maskt, tile.shifts, tile.shiftt,
                tile.cms, tile.cmt, tile.fmt, tile.siz, tile.stride,
                uint32_t(tile.address), tile.palette,
                (periodS > 0.0f) ? (jumpUls / periodS) : 0.0f,
                (periodT > 0.0f) ? (jumpUlt / periodT) : 0.0f);
        }
    }



    // ---------------------------------------------------------------------
    // PROJECTION INTERPOLATION GUARD
    //
    // ProjectionProcessor interpolates the view matrix and the projection matrix
    // separately and then multiplies them (PP:124, PP:130, PP:143). Turning on
    // decomposition fixes only the first of those: the view goes through slerp and
    // stays orthonormal, while the projection is still blended element by element
    // by lerpMatrix. A component-wise blend of two different perspective matrices
    // is not a perspective matrix at intermediate weights -- the frustum it
    // describes is not the frustum either native frame had -- and the geometry that
    // suffers is whatever sits closest to w = 0. That is this sky: a horizontal
    // plane running to the horizon, with one of its seven vertices behind the eye
    // on literally every frame measured, and ndc_radius peaking above 100000.
    //
    // The processor already has the correct branch; it simply is not reached. When
    // interpolateProjection is false it assigns curProjTransform to both outputs,
    // which is a valid projection by construction. This guard routes there whenever
    // the two projections actually differ, and leaves the existing behaviour alone
    // when they are effectively identical, where interpolating is a no-op anyway.
    // ---------------------------------------------------------------------

    inline bool wr64ProjectionGuardEnabled() {
        static const bool enabled = wr64SkyBracketEnvFlag("WR64_PROJ_GUARD");
        return enabled;
    }

    inline bool wr64ProjectionsEffectivelyIdentical(const hlslpp::float4x4 &a, const hlslpp::float4x4 &b) {
        float worst = 0.0f;
        float scale = 1.0e-6f;
        for (uint32_t r = 0; r < 4; r++) {
            const hlslpp::float4 rowA = a[r];
            const hlslpp::float4 rowB = b[r];
            const float valuesA[4] = { float(rowA.x), float(rowA.y), float(rowA.z), float(rowA.w) };
            const float valuesB[4] = { float(rowB.x), float(rowB.y), float(rowB.z), float(rowB.w) };
            for (uint32_t c = 0; c < 4; c++) {
                worst = std::max(worst, std::fabs(valuesA[c] - valuesB[c]));
                scale = std::max(scale, std::fabs(valuesB[c]));
            }
        }

        return (worst / scale) < 1.0e-3f;
    }

    struct Wr64SkyBracketResult {
        bool evaluated = false;
        bool violated = false;
        bool held = false;
        bool injected = false;
        uint32_t uniqueVertices = 0;
        uint32_t coveredSamples = 0;
        uint32_t coverageBreaks = 0;
        uint32_t totalSamples = 0;
        float wrapU = 0.0f;
        float wrapV = 0.0f;
        // Coverage at each weight, not just at the endpoints.
        //
        // Six consecutive presented frames were measured off screenshots: the sky
        // plane occupied 14.78, 15.73, 15.16, 15.24, 35.34 and 15.82 percent of the
        // frame. One presented frame at more than double the area, then straight
        // back. The boat, beach and palm did not move, so it is not the camera --
        // it is this patch's own silhouette.
        //
        // Every test built before this one asked which texel lands on a given screen
        // point. None asked how much of the screen the patch covers. That is why
        // they all came back clean while the defect was plainly visible.
        uint32_t coverAtWeight[5] = { 0, 0, 0, 0, 0 };
        float areaSwell = 0.0f;
        uint32_t endpointCover0 = 0;
        uint32_t endpointCover1 = 0;
        uint32_t validVertices0 = 0;
        uint32_t validVertices1 = 0;
        float ndcRadius0 = 0.0f;
        float ndcRadius1 = 0.0f;
        float previousMatchError = -1.0f;
        bool collapseHeld = false;
        bool areaHeld = false;
        // The sky's TransformGroup as the display list tagged it. RT64 already has a
        // first-class way to say "this object's vertex data must not be interpolated"
        // -- G_EX_COMPONENT_SKIP on vertexInterpolation / texcoordInterpolation --
        // and rt64_rsp.cpp:89 shows the project using it for its own groups. Ten
        // rounds were spent fighting the interpolation without ever checking whether
        // this object is simply tagged wrong. SKIP=0, INTERPOLATE=1, AUTO=2;
        // ORDER_LINEAR=0, ORDER_AUTO=1.
        uint32_t groupDecompose = 0;
        uint32_t groupPosition = 0;
        uint32_t groupRotation = 0;
        uint32_t groupScale = 0;
        uint32_t groupSkew = 0;
        uint32_t groupPerspective = 0;
        uint32_t groupVertex = 0;
        uint32_t groupTexcoord = 0;
        uint32_t groupTile = 0;
        uint32_t groupLookAt = 0;
        uint32_t groupOrdering = 0;
        uint32_t groupAspect = 0;
        uint32_t groupEditable = 0;
        uint32_t viewProjOrdering = 0;
        uint32_t viewProjMatrixId = 0;
        uint32_t viewProjDecompose = 0;
        float sweepTotal = 0.0f;
        float sweepVertices = 0.0f;
        float sweepWorld = 0.0f;
        float sweepViewProj = 0.0f;
        bool snapped = false;
        float mapError = 0.0f;
        float mapResidual = -1.0f;
        bool repaired = false;
        uint32_t prevTransformIndex = 0;
        uint32_t matrixId = 0;
        uint32_t matrixIdHash = 0;
        bool transformMapped = false;
        float worstTexelDeviation = 0.0f;
        float worstTexelWeight = 0.0f;
        float uvSpan = 0.0f;
        float worstNdcDeviation = 0.0f;
        float worstNdcWeight = 0.0f;
        float ndcSpan = 0.0f;
        float vertexPositionDeltaMax = 0.0f;
        float vertexTexcoordDeltaMax = 0.0f;
    };

    inline void wr64SkyBracketEvaluateOne(WorkloadQueue &workloadQueue,
        const Wr64SkyBracketLocation &curLocation, const Wr64SkyBracketLocation &prevLocation,
        uint32_t occurrence, GameFrameMap::WorkloadMap &curWorkloadMap, ModifiedBuffers &modifiedBuffers)
    {
        Wr64SkyBracketResult result;

        FILE *traceFile = wr64SkyBracketTraceFile();
        uint64_t submissionFrame = 0;
        uint64_t workloadId = 0;

        if (curLocation.found) {
            Workload &curWorkload = workloadQueue.workloads[curLocation.workloadIndex];
            submissionFrame = curWorkload.submissionFrame;
            workloadId = curWorkload.workloadId;
        }

        auto writeRow = [&]() {
            if (traceFile == nullptr) {
                return;
            }

            std::fprintf(traceFile,
                "R4C,%llu,%llu,%u,%u,%u,%u,%u,%u,%u,%08X,%08X,%u,%u,%u,%u,%u,%.3f,%.3f,%u,%u,%u,%u,%.4f,%.4f,%.4f,%.4f,%.5f,%u,%.4f,%.4f,%.4f,%.4f,%u,%u,%u,%u,%u,%u,%u,%.4f,%u,"
                "%.6f,%.4f,%.6f,%.6f,%.4f,%.6f,%.6f,%.6f,%u,%u,%u\n",
                static_cast<unsigned long long>(submissionFrame),
                static_cast<unsigned long long>(workloadId),
                occurrence,
                uint32_t(curLocation.found && prevLocation.found),
                curLocation.callIndex,
                curLocation.triangleCount,
                result.uniqueVertices,
                curLocation.minWorldMatrix,
                curLocation.maxWorldMatrix,
                result.matrixId,
                result.matrixIdHash,
                uint32_t(result.transformMapped),
                result.prevTransformIndex,
                result.coveredSamples,
                result.coverageBreaks,
                result.totalSamples,
                result.wrapU,
                result.wrapV,
                result.endpointCover0,
                result.endpointCover1,
                result.validVertices0,
                result.validVertices1,
                result.ndcRadius0,
                result.ndcRadius1,
                result.previousMatchError,
                result.mapError,
                result.mapResidual,
                uint32_t(result.repaired),
                result.sweepTotal,
                result.sweepVertices,
                result.sweepWorld,
                result.sweepViewProj,
                uint32_t(result.snapped),
                uint32_t(result.collapseHeld),
                result.coverAtWeight[0],
                result.coverAtWeight[1],
                result.coverAtWeight[2],
                result.coverAtWeight[3],
                result.coverAtWeight[4],
                result.areaSwell,
                uint32_t(result.areaHeld),
                result.worstTexelDeviation,
                result.worstTexelWeight,
                result.uvSpan,
                result.worstNdcDeviation,
                result.worstNdcWeight,
                result.ndcSpan,
                result.vertexPositionDeltaMax,
                result.vertexTexcoordDeltaMax,
                uint32_t(result.injected),
                uint32_t(result.violated),
                uint32_t(result.held));
            std::fflush(traceFile);
        };

        if (!curLocation.found || !prevLocation.found) {
            writeRow();
            return;
        }

        Workload &curWorkload = workloadQueue.workloads[curLocation.workloadIndex];
        const Workload &prevWorkload = workloadQueue.workloads[prevLocation.workloadIndex];
        DrawData &curDraw = curWorkload.drawData;
        const DrawData &prevDraw = prevWorkload.drawData;

        // Follow the call's own face indices. No transform ranges, no segment
        // assumptions, no vertex-count assumptions.
        const uint32_t indexCount = curLocation.triangleCount * 3U;
        if ((uint64_t(curLocation.faceIndicesStart) + indexCount) > curDraw.faceIndices.size()) {
            writeRow();
            return;
        }

        std::vector<uint32_t> globalVertices;
        std::vector<uint32_t> localFaces;
        globalVertices.reserve(16);
        localFaces.reserve(indexCount);
        for (uint32_t i = 0; i < indexCount; i++) {
            const uint32_t globalIndex = curDraw.faceIndices[curLocation.faceIndicesStart + i];
            uint32_t local = UINT32_MAX;
            for (uint32_t g = 0; g < uint32_t(globalVertices.size()); g++) {
                if (globalVertices[g] == globalIndex) {
                    local = g;
                    break;
                }
            }

            if (local == UINT32_MAX) {
                local = uint32_t(globalVertices.size());
                globalVertices.push_back(globalIndex);
            }

            localFaces.push_back(local);
        }

        const uint32_t uniqueCount = uint32_t(globalVertices.size());
        result.uniqueVertices = uniqueCount;
        if ((uniqueCount < 3U) || (uniqueCount > 64U)) {
            writeRow();
            return;
        }

        for (uint32_t g = 0; g < uniqueCount; g++) {
            const uint64_t vertex = globalVertices[g];
            if ((((vertex + 1ULL) * 3ULL) > curDraw.posFloats.size()) ||
                (((vertex + 1ULL) * 3ULL) > curDraw.velFloats.size()) ||
                (((vertex + 1ULL) * 2ULL) > curDraw.tcFloats.size()) ||
                (((vertex + 1ULL) * 2ULL) > curDraw.tcVelFloats.size()) ||
                (vertex >= curDraw.worldIndices.size()))
            {
                writeRow();
                return;
            }
        }

        // The world matrix this call is drawn with, and whatever it was matched to.
        const uint32_t curTransformIndex = curLocation.minWorldMatrix;
        if ((curTransformIndex >= curDraw.worldTransforms.size()) ||
            (curTransformIndex >= curWorkloadMap.transforms.size()) ||
            (curTransformIndex >= curDraw.worldTransformGroups.size()))
        {
            writeRow();
            return;
        }

        {
            const uint32_t groupIndex = curDraw.worldTransformGroups[curTransformIndex];
            if (groupIndex < curDraw.transformGroups.size()) {
                const TransformGroup &g = curDraw.transformGroups[groupIndex];
                result.groupDecompose = uint32_t(g.decompose);
                result.groupPosition = g.positionInterpolation;
                result.groupRotation = g.rotationInterpolation;
                result.groupScale = g.scaleInterpolation;
                result.groupSkew = g.skewInterpolation;
                result.groupPerspective = g.perspectiveInterpolation;
                result.groupVertex = g.vertexInterpolation;
                result.groupTexcoord = g.texcoordInterpolation;
                result.groupTile = g.tileInterpolation;
                result.groupLookAt = g.lookAtInterpolation;
                result.groupOrdering = g.ordering;
                result.groupAspect = g.aspectMode;
                result.groupEditable = g.editable;
                result.matrixId = curDraw.transformGroups[groupIndex].matrixId;
            }

            uint32_t hash = 0;
            for (uint32_t m = curLocation.minWorldMatrix; (m <= curLocation.maxWorldMatrix) && (m < curDraw.worldTransformGroups.size()); m++) {
                const uint32_t groupIt = curDraw.worldTransformGroups[m];
                if (groupIt < curDraw.transformGroups.size()) {
                    hash = (hash * 33U) ^ curDraw.transformGroups[groupIt].matrixId;
                }
            }

            result.matrixIdHash = hash;
        }

        const GameFrameMap::TransformMap &transformMap = curWorkloadMap.transforms[curTransformIndex];
        result.transformMapped = transformMap.mapped;
        result.prevTransformIndex = transformMap.prevTransformIndex;
        if (!transformMap.mapped || (transformMap.prevTransformIndex >= prevDraw.worldTransforms.size())) {
            // Nothing is being interpolated for this call, so nothing can be
            // out of bracket. Still logged, because a sky that stops being
            // matched is itself worth knowing about.
            writeRow();
            return;
        }

        const hlslpp::float4x4 &curWorld = curDraw.worldTransforms[curTransformIndex];
        const hlslpp::float4x4 &prevWorld = prevDraw.worldTransforms[transformMap.prevTransformIndex];

        if ((curLocation.transformsIndex >= curDraw.viewProjTransforms.size()) ||
            (prevLocation.transformsIndex >= prevDraw.viewProjTransforms.size()))
        {
            writeRow();
            return;
        }

        const hlslpp::float4x4 &curViewProj = curDraw.viewProjTransforms[curLocation.transformsIndex];
        const hlslpp::float4x4 &prevViewProj = prevDraw.viewProjTransforms[prevLocation.transformsIndex];
        const bool viewProjMapped =
            (curLocation.transformsIndex < curWorkloadMap.viewProjections.size()) &&
            curWorkloadMap.viewProjections[curLocation.transformsIndex].mapped;

        if (curLocation.transformsIndex < curDraw.viewProjTransformGroups.size()) {
            const uint32_t vpGroupIndex = curDraw.viewProjTransformGroups[curLocation.transformsIndex];
            if (vpGroupIndex < curDraw.transformGroups.size()) {
                const TransformGroup &vpg = curDraw.transformGroups[vpGroupIndex];
                result.viewProjMatrixId = vpg.matrixId;
                result.viewProjOrdering = vpg.ordering;
                result.viewProjDecompose = uint32_t(vpg.decompose);
            }
        }

        // When the view projection was not matched, the renderer does not
        // interpolate it either: every output this native interval is drawn
        // through the current camera. Model that exactly rather than borrowing
        // the world transform's rigid body, which would lerp the camera along a
        // path nothing is going to render and manufacture deviation out of
        // nothing.
        const RigidBody identityBody;
        const RigidBody &viewProjBody = viewProjMapped
            ? curWorkloadMap.viewProjections[curLocation.transformsIndex].rigidBody
            : identityBody;

        // Inject the calibration rotation before evaluation and upload it to the draw.
        // Unlike uniform UV velocity, rotating the fan changes the screen-to-texture map
        // nonlinearly and creates a detectable interior bracket violation.
        const uint64_t injectPeriod = wr64SkyBracketInjectPeriod();
        if ((injectPeriod > 0) && ((curWorkload.submissionFrame % injectPeriod) == 0)) {
            double centroid[3] = { 0.0, 0.0, 0.0 };
            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                for (uint32_t axis = 0; axis < 3; axis++) {
                    centroid[axis] += double(curDraw.posFloats[(vertex * 3) + axis]);
                }
            }

            for (uint32_t axis = 0; axis < 3; axis++) {
                centroid[axis] /= double(uniqueCount);
            }

            // The fan's plane, from the two offsets furthest from parallel.
            float bestNormal[3] = { 0.0f, 0.0f, 0.0f };
            float bestLength = 0.0f;
            for (uint32_t a = 0; a < uniqueCount; a++) {
                const size_t va = size_t(globalVertices[a]);
                const float ax = curDraw.posFloats[(va * 3) + 0] - float(centroid[0]);
                const float ay = curDraw.posFloats[(va * 3) + 1] - float(centroid[1]);
                const float az = curDraw.posFloats[(va * 3) + 2] - float(centroid[2]);
                for (uint32_t b = a + 1; b < uniqueCount; b++) {
                    const size_t vb = size_t(globalVertices[b]);
                    const float bx = curDraw.posFloats[(vb * 3) + 0] - float(centroid[0]);
                    const float by = curDraw.posFloats[(vb * 3) + 1] - float(centroid[1]);
                    const float bz = curDraw.posFloats[(vb * 3) + 2] - float(centroid[2]);
                    const float cx = (ay * bz) - (az * by);
                    const float cy = (az * bx) - (ax * bz);
                    const float cz = (ax * by) - (ay * bx);
                    const float length = std::sqrt((cx * cx) + (cy * cy) + (cz * cz));
                    if (length > bestLength) {
                        bestLength = length;
                        bestNormal[0] = cx / length;
                        bestNormal[1] = cy / length;
                        bestNormal[2] = cz / length;
                    }
                }
            }

            if (bestLength > 1.0e-6f) {
                // Rodrigues, minus 25 degrees.
                const float cosTheta = 0.90630779f;
                const float sinTheta = -0.42261826f;
                for (uint32_t g = 0; g < uniqueCount; g++) {
                    const size_t vertex = size_t(globalVertices[g]);
                    const float vx = curDraw.posFloats[(vertex * 3) + 0] - float(centroid[0]);
                    const float vy = curDraw.posFloats[(vertex * 3) + 1] - float(centroid[1]);
                    const float vz = curDraw.posFloats[(vertex * 3) + 2] - float(centroid[2]);
                    const float crossX = (bestNormal[1] * vz) - (bestNormal[2] * vy);
                    const float crossY = (bestNormal[2] * vx) - (bestNormal[0] * vz);
                    const float crossZ = (bestNormal[0] * vy) - (bestNormal[1] * vx);
                    const float dot = (bestNormal[0] * vx) + (bestNormal[1] * vy) + (bestNormal[2] * vz);
                    const float oneMinusCos = 1.0f - cosTheta;
                    const float prevX = float(centroid[0]) + (vx * cosTheta) + (crossX * sinTheta) + (bestNormal[0] * dot * oneMinusCos);
                    const float prevY = float(centroid[1]) + (vy * cosTheta) + (crossY * sinTheta) + (bestNormal[1] * dot * oneMinusCos);
                    const float prevZ = float(centroid[2]) + (vz * cosTheta) + (crossZ * sinTheta) + (bestNormal[2] * dot * oneMinusCos);
                    curDraw.velFloats[(vertex * 3) + 0] = curDraw.posFloats[(vertex * 3) + 0] - prevX;
                    curDraw.velFloats[(vertex * 3) + 1] = curDraw.posFloats[(vertex * 3) + 1] - prevY;
                    curDraw.velFloats[(vertex * 3) + 2] = curDraw.posFloats[(vertex * 3) + 2] - prevZ;
                }

                modifiedBuffers.positionVelocity = true;
                result.injected = true;
            }
        }

        // Endpoint and interior evaluations. Weight 0 is the previous native
        // frame as the GPU will reconstruct it (current minus velocity); weight 1
        // is the current native frame.
        const float weights[5] = { 0.0f, 0.25f, 0.5f, 0.75f, 1.0f };
        std::vector<Wr64SkyBracketVertex> evaluated[5];
        for (uint32_t w = 0; w < 5; w++) {
            evaluated[w].assign(uniqueCount, Wr64SkyBracketVertex());
            const float weight = weights[w];
            const float back = 1.0f - weight;

            hlslpp::float4x4 world;
            hlslpp::float4x4 viewProj;
            if (weight <= 0.0f) {
                world = prevWorld;
                viewProj = viewProjMapped ? prevViewProj : curViewProj;
            }
            else if (weight >= 1.0f) {
                world = curWorld;
                viewProj = curViewProj;
            }
            else {
                world = transformMap.rigidBody.lerp(weight, prevWorld, curWorld, true);
                viewProj = viewProjMapped
                    ? viewProjBody.lerp(weight, prevViewProj, curViewProj, true)
                    : curViewProj;
            }

            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                const float position[3] = {
                    curDraw.posFloats[(vertex * 3) + 0] - (curDraw.velFloats[(vertex * 3) + 0] * back),
                    curDraw.posFloats[(vertex * 3) + 1] - (curDraw.velFloats[(vertex * 3) + 1] * back),
                    curDraw.posFloats[(vertex * 3) + 2] - (curDraw.velFloats[(vertex * 3) + 2] * back)
                };

                Wr64SkyBracketVertex &entry = evaluated[w][g];
                entry.u = curDraw.tcFloats[(vertex * 2) + 0] - (curDraw.tcVelFloats[(vertex * 2) + 0] * back);
                entry.v = curDraw.tcFloats[(vertex * 2) + 1] - (curDraw.tcVelFloats[(vertex * 2) + 1] * back);
                wr64SkyBracketProjectClip(position, world, viewProj, entry);
                if (!std::isfinite(entry.u) || !std::isfinite(entry.v)) {
                    entry.finite = false;
                    entry.valid = false;
                }
            }
        }

        for (uint32_t g = 0; g < uniqueCount; g++) {
            const Wr64SkyBracketVertex &start = evaluated[0][g];
            const Wr64SkyBracketVertex &end = evaluated[4][g];
            if (start.valid) {
                result.validVertices0++;
                result.ndcRadius0 = std::max(result.ndcRadius0,
                    std::sqrt((start.ndcX * start.ndcX) + (start.ndcY * start.ndcY)));
            }

            if (end.valid) {
                result.validVertices1++;
                result.ndcRadius1 = std::max(result.ndcRadius1,
                    std::sqrt((end.ndcX * end.ndcX) + (end.ndcY * end.ndcY)));
            }
        }

        // Does the state RT64 will interpolate away from actually correspond to
        // the sky the previous native frame drew?
        //
        // The GPU reconstructs the previous vertex as current minus velocity. If
        // the transform pairing is sound that reconstruction equals the previous
        // frame's own sky vertices exactly. If it does not, RT64 is interpolating
        // this frame's sky away from something that was never on screen, which is
        // a one-output mutation by construction. Nothing else in this file can
        // tell those two cases apart.
        {
            const uint32_t prevIndexCount = prevLocation.triangleCount * 3U;
            if ((uint64_t(prevLocation.faceIndicesStart) + prevIndexCount) <= prevDraw.faceIndices.size()) {
                std::vector<uint32_t> prevUnique;
                prevUnique.reserve(16);
                for (uint32_t i = 0; i < prevIndexCount; i++) {
                    const uint32_t globalIndex = prevDraw.faceIndices[prevLocation.faceIndicesStart + i];
                    bool seen = false;
                    for (uint32_t g = 0; g < uint32_t(prevUnique.size()); g++) {
                        if (prevUnique[g] == globalIndex) { seen = true; break; }
                    }

                    if (!seen) {
                        prevUnique.push_back(globalIndex);
                    }
                }

                if (uint32_t(prevUnique.size()) == uniqueCount) {
                    float worst = 0.0f;
                    bool usable = true;
                    for (uint32_t g = 0; g < uniqueCount; g++) {
                        const size_t curVertex = size_t(globalVertices[g]);
                        const size_t prevVertex = size_t(prevUnique[g]);
                        if (((prevVertex + 1) * 3) > prevDraw.posFloats.size()) { usable = false; break; }
                        for (uint32_t axis = 0; axis < 3; axis++) {
                            const float reconstructed =
                                curDraw.posFloats[(curVertex * 3) + axis] - curDraw.velFloats[(curVertex * 3) + axis];
                            worst = std::max(worst, std::fabs(reconstructed - prevDraw.posFloats[(prevVertex * 3) + axis]));
                        }
                    }

                    if (usable) {
                        result.previousMatchError = worst;
                    }
                }
            }
        }

        for (uint32_t g = 0; g < uniqueCount; g++) {
            const size_t vertex = size_t(globalVertices[g]);
            const float dx = curDraw.velFloats[(vertex * 3) + 0];
            const float dy = curDraw.velFloats[(vertex * 3) + 1];
            const float dz = curDraw.velFloats[(vertex * 3) + 2];
            result.vertexPositionDeltaMax = std::max(result.vertexPositionDeltaMax,
                std::sqrt((dx * dx) + (dy * dy) + (dz * dz)));
            const float du = curDraw.tcVelFloats[(vertex * 2) + 0];
            const float dv = curDraw.tcVelFloats[(vertex * 2) + 1];
            result.vertexTexcoordDeltaMax = std::max(result.vertexTexcoordDeltaMax,
                std::sqrt((du * du) + (dv * dv)));
        }

        // Primary test: what texel shows through a fixed screen point.
        const hlslpp::float2 wrapPoint = curWorkload.extended.texcoordWrapPoint;
        const float wrapU = float(wrapPoint[0]);
        const float wrapV = float(wrapPoint[1]);
        result.wrapU = wrapU;
        result.wrapV = wrapV;
        const int gridSide = 5;
        const float gridExtent = 0.85f;
        for (int gy = 0; gy < gridSide; gy++) {
            for (int gx = 0; gx < gridSide; gx++) {
                result.totalSamples++;
                const float pointX = -gridExtent + ((2.0f * gridExtent) * float(gx) / float(gridSide - 1));
                const float pointY = -gridExtent + ((2.0f * gridExtent) * float(gy) / float(gridSide - 1));

                float u0 = 0.0f;
                float v0 = 0.0f;
                float u1 = 0.0f;
                float v1 = 0.0f;
                const bool covered0 = wr64SkyBracketSampleFan(evaluated[0], localFaces, pointX, pointY, u0, v0);
                const bool covered1 = wr64SkyBracketSampleFan(evaluated[4], localFaces, pointX, pointY, u1, v1);
                if (covered0) { result.endpointCover0++; }
                if (covered1) { result.endpointCover1++; }
                if (!covered0 || !covered1) {
                    continue;
                }

                u1 = wr64SkyBracketUnwrap(u1, u0, wrapU);
                v1 = wr64SkyBracketUnwrap(v1, v0, wrapV);

                bool covered = true;
                float worstHere = 0.0f;
                float worstWeightHere = 0.0f;
                for (uint32_t w = 1; w < 4; w++) {
                    float uw = 0.0f;
                    float vw = 0.0f;
                    if (!wr64SkyBracketSampleFan(evaluated[w], localFaces, pointX, pointY, uw, vw)) {
                        // Both native frames put sky on this screen point and the
                        // interpolated frame does not. That is not a sample we
                        // failed to take, it is the sky visibly leaving a place it
                        // was never supposed to leave, and it is exactly what a
                        // violent excursion looks like from here: the fan swings
                        // away, coverage collapses, and every deviation the test
                        // can still measure reads zero.
                        //
                        // Measured: a 90-degree injected rotation scored 0.000
                        // deviation with 0 covered samples on 9 runs out of 11,
                        // and was therefore never held. Counting the break fixes
                        // that, and it fixes the same blindness for the real
                        // defect.
                        covered = false;
                        break;
                    }

                    uw = wr64SkyBracketUnwrap(uw, u0, wrapU);
                    vw = wr64SkyBracketUnwrap(vw, v0, wrapV);
                    const float deviation = wr64SkyBracketSegmentDeviation(uw, vw, u0, v0, u1, v1);
                    if (deviation > worstHere) {
                        worstHere = deviation;
                        worstWeightHere = weights[w];
                    }
                }

                if (!covered) {
                    result.coverageBreaks++;
                    continue;
                }

                result.coveredSamples++;
                if (worstHere > result.worstTexelDeviation) {
                    result.worstTexelDeviation = worstHere;
                    result.worstTexelWeight = worstWeightHere;
                    const float spanU = u1 - u0;
                    const float spanV = v1 - v0;
                    result.uvSpan = std::sqrt((spanU * spanU) + (spanV * spanV));
                }
            }
        }

        // Secondary test: the fan's own vertices in NDC. Catches a geometry
        // excursion that happens to leave the sampled texel alone.
        for (uint32_t g = 0; g < uniqueCount; g++) {
            const Wr64SkyBracketVertex &start = evaluated[0][g];
            const Wr64SkyBracketVertex &end = evaluated[4][g];
            if (!start.valid || !end.valid) {
                continue;
            }

            for (uint32_t w = 1; w < 4; w++) {
                const Wr64SkyBracketVertex &middle = evaluated[w][g];
                if (!middle.valid) {
                    continue;
                }

                // A vertex just in front of the near plane projects to
                // enormous NDC. That is not an excursion, it is a division.
                const float NdcSanityLimit = 4.0f;
                if ((std::fabs(start.ndcX) > NdcSanityLimit) || (std::fabs(start.ndcY) > NdcSanityLimit) ||
                    (std::fabs(end.ndcX) > NdcSanityLimit) || (std::fabs(end.ndcY) > NdcSanityLimit) ||
                    (std::fabs(middle.ndcX) > NdcSanityLimit) || (std::fabs(middle.ndcY) > NdcSanityLimit))
                {
                    continue;
                }

                const float deviation = wr64SkyBracketSegmentDeviation(
                    middle.ndcX, middle.ndcY, start.ndcX, start.ndcY, end.ndcX, end.ndcY);
                if (deviation > result.worstNdcDeviation) {
                    result.worstNdcDeviation = deviation;
                    result.worstNdcWeight = weights[w];
                    const float spanX = end.ndcX - start.ndcX;
                    const float spanY = end.ndcY - start.ndcY;
                    result.ndcSpan = std::sqrt((spanX * spanX) + (spanY * spanY));
                }
            }
        }

        result.evaluated = true;
        result.violated =
            ((result.coveredSamples > 0) && (result.worstTexelDeviation > wr64SkyBracketTexelTolerance())) ||
            (result.coverageBreaks > 0) ||
            (wr64SkyBracketUseNdc() && (result.worstNdcDeviation > wr64SkyBracketNdcTolerance()));

        // The correction. Not a threshold on a proxy: this fires only when the
        // interpolated sky has been shown to land somewhere neither native frame
        // ever put it. Holding at the current native endpoint is the one choice
        // that is guaranteed to be a state the game actually drew.
        if (result.violated && wr64SkyBracketHoldEnabled()) {
            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                curDraw.velFloats[(vertex * 3) + 0] = 0.0f;
                curDraw.velFloats[(vertex * 3) + 1] = 0.0f;
                curDraw.velFloats[(vertex * 3) + 2] = 0.0f;
                curDraw.tcVelFloats[(vertex * 2) + 0] = 0.0f;
                curDraw.tcVelFloats[(vertex * 2) + 1] = 0.0f;
            }

            modifiedBuffers.positionVelocity = true;
            modifiedBuffers.texcoordVelocity = true;

            for (uint32_t m = curLocation.minWorldMatrix; (m <= curLocation.maxWorldMatrix) && (m < curWorkloadMap.transforms.size()); m++) {
                GameFrameMap::TransformMap &entry = curWorkloadMap.transforms[m];
                entry.rigidBody.lerpTranslation = false;
                entry.rigidBody.lerpRotation = false;
                entry.rigidBody.lerpScale = false;
                entry.rigidBody.lerpSkew = false;
                entry.rigidBody.lerpPerspective = false;
            }

            result.held = true;
        }

        if (result.violated) {
            static uint32_t reported = 0;
            if (reported < 40) {
                reported++;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[sky-bracket] frame %llu: texel deviation %.3f (tol %.3f, span %.3f) "
                    "coverage breaks %u of %u at weight %.2f%s%s\n",
                    static_cast<unsigned long long>(submissionFrame),
                    result.worstTexelDeviation, wr64SkyBracketTexelTolerance(), result.uvSpan,
                    result.coverageBreaks, result.totalSamples,
                    result.worstTexelWeight,
                    result.injected ? " [INJECTED]" : "",
                    result.held ? " [HELD]" : ""); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
        }

        // How much of the screen the patch actually covers at each weight. This is
        // deliberately independent of the texel test above: a sample point counts
        // here if the fan covers it at that weight, full stop, with no requirement
        // that any other weight also covers it.
        {
            for (uint32_t w = 0; w < 5; w++) {
                for (int gy = 0; gy < gridSide; gy++) {
                    for (int gx = 0; gx < gridSide; gx++) {
                        const float pointX = -gridExtent + ((2.0f * gridExtent) * float(gx) / float(gridSide - 1));
                        const float pointY = -gridExtent + ((2.0f * gridExtent) * float(gy) / float(gridSide - 1));
                        float u, v;
                        if (wr64SkyBracketSampleFan(evaluated[w], localFaces, pointX, pointY, u, v)) {
                            result.coverAtWeight[w]++;
                        }
                    }
                }
            }

            // The endpoints bracket the truth. Any interior weight that covers more
            // of the screen than either of them is showing sky where neither native
            // frame put any.
            const float endpointMax = float(std::max(result.coverAtWeight[0], result.coverAtWeight[4]));
            float interiorMax = 0.0f;
            for (uint32_t w = 1; w < 4; w++) {
                interiorMax = std::max(interiorMax, float(result.coverAtWeight[w]));
            }

            result.areaSwell = (endpointMax > 0.0f) ? ((interiorMax - endpointMax) / endpointMax) : 0.0f;
        }

        if (wr64SkyAreaGuardEnabled() && (result.areaSwell > 0.25f)) {
            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                curDraw.velFloats[(vertex * 3) + 0] = 0.0f;
                curDraw.velFloats[(vertex * 3) + 1] = 0.0f;
                curDraw.velFloats[(vertex * 3) + 2] = 0.0f;
                curDraw.tcVelFloats[(vertex * 2) + 0] = 0.0f;
                curDraw.tcVelFloats[(vertex * 2) + 1] = 0.0f;
            }

            modifiedBuffers.positionVelocity = true;
            modifiedBuffers.texcoordVelocity = true;
            result.areaHeld = true;
        }

        // The producer re-anchored the patch this frame. Its texture coordinates were
        // renumbered to match, so both native frames still draw the same sky and
        // blending between the two numberings is meaningless. Drop the texture
        // coordinate velocity for this one interval and leave the geometry alone, so
        // the sky keeps moving and the texture simply does not slide through the
        // renumbering.
        if (wr64SkyTexcoordSmartEnabled() &&
            ((result.vertexTexcoordDeltaMax > wr64SkyTexcoordJumpThreshold()) ||
             (result.vertexPositionDeltaMax > wr64SkyReanchorThreshold())))
        {
            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                curDraw.tcVelFloats[(vertex * 2) + 0] = 0.0f;
                curDraw.tcVelFloats[(vertex * 2) + 1] = 0.0f;
            }

            modifiedBuffers.texcoordVelocity = true;
            result.collapseHeld = true;
        }

        // The endpoints agree and the middle does not: refuse to interpolate the
        // texture coordinates for this one interval. Geometry is left alone, so the
        // sky keeps moving; only the meaningless part of the motion is dropped.
        if (wr64SkyCollapseGuardEnabled() &&
            (result.coveredSamples > 0) &&
            (result.worstTexelDeviation > 20.0f) &&
            (result.worstTexelDeviation > (result.uvSpan * 3.0f)))
        {
            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                curDraw.tcVelFloats[(vertex * 2) + 0] = 0.0f;
                curDraw.tcVelFloats[(vertex * 2) + 1] = 0.0f;
            }

            modifiedBuffers.texcoordVelocity = true;
            result.collapseHeld = true;
        }

        // ---------------------------------------------------------------------
        // THE SWEEP
        //
        // Every instrument in this campaign, mine included, asked the same question:
        // is the path between the two native frames well behaved? None of them ever
        // asked whether the sky should be travelling that far between them at all.
        // It should not. Measured over a full race, the sky's screen position moves
        // a median of 0.007 NDC per native interval -- essentially nothing -- and
        // then, a couple of times a minute, it moves 1 to 4.7, which is one to two
        // whole screen widths inside fifty milliseconds. The bracket test scores
        // every one of those a clean 0.00, because a straight line between two
        // endpoints is a straight line no matter how far apart they are.
        //
        // That is a seventy-fold separation between real motion and discontinuity,
        // so distinguishing them needs no tuned threshold, and refusing to animate
        // the second kind is not suppression -- interpolating across it was never
        // meaningful in the first place.
        //
        // Both sources are recorded separately, because they need different levers:
        // the producer re-anchoring the patch (vertices), and the world or view
        // matrices moving. Setting the transform's mapped flag false makes
        // TransformProcessor use the current matrix at every weight, which is the
        // clean way to say "do not interpolate this one this interval".
        // ---------------------------------------------------------------------
        {
            auto screenPoint = [](const float *position, const hlslpp::float4x4 &world,
                const hlslpp::float4x4 &viewProj, float &outX, float &outY) -> bool
            {
                float invW = 0.0f;
                wr64SkyBracketProject(position, world, viewProj, outX, outY, invW);
                return (invW != 0.0f) && (std::fabs(outX) <= 4.0f) && (std::fabs(outY) <= 4.0f);
            };

            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                const float curPosition[3] = {
                    curDraw.posFloats[(vertex * 3) + 0],
                    curDraw.posFloats[(vertex * 3) + 1],
                    curDraw.posFloats[(vertex * 3) + 2]
                };

                const float prevPosition[3] = {
                    curPosition[0] - curDraw.velFloats[(vertex * 3) + 0],
                    curPosition[1] - curDraw.velFloats[(vertex * 3) + 1],
                    curPosition[2] - curDraw.velFloats[(vertex * 3) + 2]
                };

                float ax, ay, bx, by;
                if (screenPoint(curPosition, curWorld, curViewProj, ax, ay) &&
                    screenPoint(prevPosition, prevWorld, prevViewProj, bx, by))
                {
                    result.sweepTotal = std::max(result.sweepTotal, std::sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
                }

                if (screenPoint(curPosition, prevWorld, prevViewProj, ax, ay) &&
                    screenPoint(prevPosition, prevWorld, prevViewProj, bx, by))
                {
                    result.sweepVertices = std::max(result.sweepVertices, std::sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
                }

                if (screenPoint(prevPosition, curWorld, prevViewProj, ax, ay) &&
                    screenPoint(prevPosition, prevWorld, prevViewProj, bx, by))
                {
                    result.sweepWorld = std::max(result.sweepWorld, std::sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
                }

                if (screenPoint(prevPosition, prevWorld, curViewProj, ax, ay) &&
                    screenPoint(prevPosition, prevWorld, prevViewProj, bx, by))
                {
                    result.sweepViewProj = std::max(result.sweepViewProj, std::sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
                }
            }

            if (wr64SkySnapEnabled() && (result.sweepTotal > wr64SkySnapThreshold())) {
                for (uint32_t g = 0; g < uniqueCount; g++) {
                    const size_t vertex = size_t(globalVertices[g]);
                    curDraw.velFloats[(vertex * 3) + 0] = 0.0f;
                    curDraw.velFloats[(vertex * 3) + 1] = 0.0f;
                    curDraw.velFloats[(vertex * 3) + 2] = 0.0f;
                    curDraw.tcVelFloats[(vertex * 2) + 0] = 0.0f;
                    curDraw.tcVelFloats[(vertex * 2) + 1] = 0.0f;
                }

                // REVERTED. Freezing this projection's camera reproduced the
                // two-player camera flicker in single player: the sky shares its
                // projection with the world geometry, so clearing the flag hitches
                // the whole scene, not just the sky. Do not do this again.
                // TransformProcessor::process uses drawData.worldTransforms[t] for
                // every weight when this is false, and still fills all three output
                // vectors, so the sizes stay consistent and nothing downstream reads
                // uninitialised memory.
                curWorkloadMap.transforms[curTransformIndex].mapped = false;
                modifiedBuffers.positionVelocity = true;
                modifiedBuffers.texcoordVelocity = true;
                result.snapped = true;
            }
        }

        // Measure the error the current interpolation will actually make, and if
        // asked, remove it. Both use the same fitted maps, so the CSV always shows
        // what the frame would have cost.
        {
            std::vector<float> prevPositions(uniqueCount * 3);
            std::vector<float> prevTexcoords(uniqueCount * 2);
            std::vector<float> curPositions(uniqueCount * 3);
            std::vector<float> curTexcoords(uniqueCount * 2);
            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                for (uint32_t axis = 0; axis < 3; axis++) {
                    curPositions[(g * 3) + axis] = curDraw.posFloats[(vertex * 3) + axis];
                    prevPositions[(g * 3) + axis] =
                        curDraw.posFloats[(vertex * 3) + axis] - curDraw.velFloats[(vertex * 3) + axis];
                }

                for (uint32_t axis = 0; axis < 2; axis++) {
                    curTexcoords[(g * 2) + axis] = curDraw.tcFloats[(vertex * 2) + axis];
                    prevTexcoords[(g * 2) + axis] =
                        curDraw.tcFloats[(vertex * 2) + axis] - curDraw.tcVelFloats[(vertex * 2) + axis];
                }
            }

            const Wr64SkyPlaneMap prevMap = wr64SkyFitPlaneMap(prevPositions, prevTexcoords);
            const Wr64SkyPlaneMap curMap = wr64SkyFitPlaneMap(curPositions, curTexcoords);
            const bool mapsUsable =
                prevMap.valid && curMap.valid &&
                (prevMap.axisA == curMap.axisA) && (prevMap.axisB == curMap.axisB) &&
                (prevMap.residual < 1.0f) && (curMap.residual < 1.0f);

            if (mapsUsable) {
                result.mapResidual = std::max(prevMap.residual, curMap.residual);

                // Worst gap, at the interval's midpoint, between what linear
                // interpolation of the raw arrays produces and what interpolating
                // the map itself would produce.
                for (uint32_t g = 0; g < uniqueCount; g++) {
                    const float pa = prevPositions[(g * 3) + prevMap.axisA];
                    const float pb = prevPositions[(g * 3) + prevMap.axisB];
                    const float ca = curPositions[(g * 3) + curMap.axisA];
                    const float cb = curPositions[(g * 3) + curMap.axisB];
                    const float ma = (pa + ca) * 0.5f;
                    const float mb = (pb + cb) * 0.5f;
                    const float idealU = 0.5f * ((prevMap.u[0] * ma) + (prevMap.u[1] * mb) + prevMap.u[2])
                                       + 0.5f * ((curMap.u[0] * ma) + (curMap.u[1] * mb) + curMap.u[2]);
                    const float idealV = 0.5f * ((prevMap.v[0] * ma) + (prevMap.v[1] * mb) + prevMap.v[2])
                                       + 0.5f * ((curMap.v[0] * ma) + (curMap.v[1] * mb) + curMap.v[2]);
                    const float linearU = 0.5f * (prevTexcoords[(g * 2) + 0] + curTexcoords[(g * 2) + 0]);
                    const float linearV = 0.5f * (prevTexcoords[(g * 2) + 1] + curTexcoords[(g * 2) + 1]);
                    result.mapError = std::max(result.mapError,
                        std::sqrt(((linearU - idealU) * (linearU - idealU)) +
                                  ((linearV - idealV) * (linearV - idealV))));
                }

                if (wr64SkyMapInterpolationEnabled()) {
                    // Hold the geometry so the change in position is exactly zero,
                    // and hand each vertex the texture coordinate the previous map
                    // puts at its current position. Interpolation is then exactly
                    // the interpolated map, at every weight.
                    for (uint32_t g = 0; g < uniqueCount; g++) {
                        const size_t vertex = size_t(globalVertices[g]);
                        const float ca = curPositions[(g * 3) + curMap.axisA];
                        const float cb = curPositions[(g * 3) + curMap.axisB];
                        const float previousU = (prevMap.u[0] * ca) + (prevMap.u[1] * cb) + prevMap.u[2];
                        const float previousV = (prevMap.v[0] * ca) + (prevMap.v[1] * cb) + prevMap.v[2];
                        curDraw.velFloats[(vertex * 3) + 0] = 0.0f;
                        curDraw.velFloats[(vertex * 3) + 1] = 0.0f;
                        curDraw.velFloats[(vertex * 3) + 2] = 0.0f;
                        curDraw.tcVelFloats[(vertex * 2) + 0] = curTexcoords[(g * 2) + 0] - previousU;
                        curDraw.tcVelFloats[(vertex * 2) + 1] = curTexcoords[(g * 2) + 1] - previousV;
                    }

                    modifiedBuffers.positionVelocity = true;
                    modifiedBuffers.texcoordVelocity = true;
                    result.repaired = true;
                }
            }
        }

        {
            const Workload &probeWorkload = workloadQueue.workloads[curLocation.workloadIndex];
            if (curLocation.fbPairIndex < probeWorkload.fbPairs.size()) {
                const FramebufferPair &probePair = probeWorkload.fbPairs[curLocation.fbPairIndex];
                if (curLocation.projectionIndex < probePair.projections.size()) {
                    const Projection &probeProjection = probePair.projections[curLocation.projectionIndex];
                    if (curLocation.callIndex < probeProjection.gameCalls.size()) {
                        wr64TileProbeWrite(probeWorkload, probeProjection.gameCalls[curLocation.callIndex],
                            curWorkloadMap, submissionFrame);
                    }
                }
            }
        }

        // Full reconstruction of a large event, so the correction can be designed
        // from the actual numbers instead of from a theory about them.
        {
            static uint32_t eventsWritten = 0;
            const bool large =
                (result.vertexPositionDeltaMax > wr64SkyBracketEventThreshold()) || result.violated;
            FILE *eventFile = wr64SkyBracketEventFile();
            if (large && (eventFile != nullptr) && (eventsWritten < 60)) {
                eventsWritten++;
                std::fprintf(eventFile,
                    "EVENT,%llu,%u,%.4f,%.4f,%.4f,%u,%u,%u,%u,%u,%u,%.3f\n",
                    static_cast<unsigned long long>(submissionFrame),
                    uniqueCount,
                    result.vertexPositionDeltaMax,
                    result.vertexTexcoordDeltaMax,
                    result.worstTexelDeviation,
                    result.coveredSamples,
                    result.coverageBreaks,
                    result.endpointCover0,
                    result.endpointCover1,
                    uint32_t(result.violated),
                    curTransformIndex,
                    result.wrapU);

                const bool addressesUsable =
                    curDraw.vertexSegmentedAddresses.size() == curDraw.vertexCount();
                for (uint32_t g = 0; g < uniqueCount; g++) {
                    const size_t vertex = size_t(globalVertices[g]);
                    const uint32_t address = addressesUsable ? curDraw.vertexSegmentedAddresses[vertex] : 0u;
                    std::fprintf(eventFile,
                        "VTX,%llu,%u,%08X,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n",
                        static_cast<unsigned long long>(submissionFrame), g, address,
                        curDraw.posFloats[(vertex * 3) + 0] - curDraw.velFloats[(vertex * 3) + 0],
                        curDraw.posFloats[(vertex * 3) + 1] - curDraw.velFloats[(vertex * 3) + 1],
                        curDraw.posFloats[(vertex * 3) + 2] - curDraw.velFloats[(vertex * 3) + 2],
                        curDraw.posFloats[(vertex * 3) + 0],
                        curDraw.posFloats[(vertex * 3) + 1],
                        curDraw.posFloats[(vertex * 3) + 2],
                        curDraw.tcFloats[(vertex * 2) + 0] - curDraw.tcVelFloats[(vertex * 2) + 0],
                        curDraw.tcFloats[(vertex * 2) + 1] - curDraw.tcVelFloats[(vertex * 2) + 1],
                        curDraw.tcFloats[(vertex * 2) + 0],
                        curDraw.tcFloats[(vertex * 2) + 1]);
                }

                wr64SkyBracketWriteMatrix(eventFile, "WORLDPREV", submissionFrame, prevWorld);
                wr64SkyBracketWriteMatrix(eventFile, "WORLDCUR", submissionFrame, curWorld);
                wr64SkyBracketWriteMatrix(eventFile, "VPPREV", submissionFrame, prevViewProj);
                wr64SkyBracketWriteMatrix(eventFile, "VPCUR", submissionFrame, curViewProj);
                std::fflush(eventFile);
            }
        }

        // One-shot dump of how this draw is actually tagged. These flags come from
        // the display list via RSP::setGroupProperties and are constant per draw, so
        // once is enough. RT64's own answer to "this object's numbers are not
        // blendable" is G_EX_COMPONENT_SKIP on vertexInterpolation and
        // texcoordInterpolation -- rt64_rsp.cpp:89 uses exactly that for the groups
        // this project synthesises itself. If the sky is tagged INTERPOLATE, the
        // object is described wrong to the renderer and no downstream guard is the
        // right fix.
        {
            static bool dumped = false;
            if (!dumped) {
                dumped = true;
                const char *names[3] = { "SKIP", "INTERPOLATE", "AUTO" };
                auto nameOf = [&](uint32_t value) { return (value < 3) ? names[value] : "?"; };
                const char *lines =
                    "\n[sky-group] the sky draw as the display list tagged it\n"
                    "  matrixId            %08X\n"
                    "  decompose           %u\n"
                    "  position            %u (%s)\n"
                    "  rotation            %u (%s)\n"
                    "  scale               %u (%s)\n"
                    "  skew                %u (%s)\n"
                    "  perspective         %u (%s)\n"
                    "  VERTEX              %u (%s)\n"
                    "  TEXCOORD            %u (%s)\n"
                    "  tile                %u (%s)\n"
                    "  lookAt              %u (%s)\n"
                    "  ordering            %u (%s)\n"
                    "  aspectMode          %u\n"
                    "  editable            %u\n"
                    "  viewProj matrixId   %08X\n"
                    "  viewProj ordering   %u (%s)\n"
                    "  viewProj decompose  %u\n\n";
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, lines,
                    result.matrixId, result.groupDecompose,
                    result.groupPosition, nameOf(result.groupPosition),
                    result.groupRotation, nameOf(result.groupRotation),
                    result.groupScale, nameOf(result.groupScale),
                    result.groupSkew, nameOf(result.groupSkew),
                    result.groupPerspective, nameOf(result.groupPerspective),
                    result.groupVertex, nameOf(result.groupVertex),
                    result.groupTexcoord, nameOf(result.groupTexcoord),
                    result.groupTile, nameOf(result.groupTile),
                    result.groupLookAt, nameOf(result.groupLookAt),
                    result.groupOrdering, (result.groupOrdering == 0) ? "LINEAR" : "AUTO",
                    result.groupAspect, result.groupEditable,
                    result.viewProjMatrixId,
                    result.viewProjOrdering, (result.viewProjOrdering == 0) ? "LINEAR" : "AUTO",
                    result.viewProjDecompose); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }

                // Every group in the workload, so a second entry carrying the same
                // matrixId cannot hide. The override fires (override=1 in the id log)
                // and the group this draw resolves to still reads INTERPOLATE, so the
                // two are not the same object and this says which index is which.
                FILE *tableFile = std::fopen("wr64-sky-grouptable.txt", "wb");
                if (tableFile != nullptr) {
                    std::fprintf(tableFile, "sky uses transform %u -> group index %u\n",
                        curTransformIndex,
                        (curTransformIndex < curDraw.worldTransformGroups.size())
                            ? curDraw.worldTransformGroups[curTransformIndex] : 0xFFFFFFFFu);
                    std::fprintf(tableFile, "worldTransformGroups (%u entries): ",
                        uint32_t(curDraw.worldTransformGroups.size()));
                    for (uint32_t i = 0; i < uint32_t(curDraw.worldTransformGroups.size()); i++) {
                        std::fprintf(tableFile, "%u ", curDraw.worldTransformGroups[i]);
                    }

                    std::fprintf(tableFile, "\n\ntransformGroups (%u entries):\n",
                        uint32_t(curDraw.transformGroups.size()));
                    for (uint32_t i = 0; i < uint32_t(curDraw.transformGroups.size()); i++) {
                        const TransformGroup &entry = curDraw.transformGroups[i];
                        std::fprintf(tableFile, "  [%3u] matrixId=%08X vertex=%u texcoord=%u tile=%u ordering=%u\n",
                            i, entry.matrixId, entry.vertexInterpolation,
                            entry.texcoordInterpolation, entry.tileInterpolation, entry.ordering);
                    }

                    std::fclose(tableFile);
                }

                FILE *groupFile = std::fopen("wr64-sky-group.txt", "wb");
                if (groupFile != nullptr) {
                    std::fprintf(groupFile, lines,
                        result.matrixId, result.groupDecompose,
                        result.groupPosition, nameOf(result.groupPosition),
                        result.groupRotation, nameOf(result.groupRotation),
                        result.groupScale, nameOf(result.groupScale),
                        result.groupSkew, nameOf(result.groupSkew),
                        result.groupPerspective, nameOf(result.groupPerspective),
                        result.groupVertex, nameOf(result.groupVertex),
                        result.groupTexcoord, nameOf(result.groupTexcoord),
                        result.groupTile, nameOf(result.groupTile),
                        result.groupLookAt, nameOf(result.groupLookAt),
                        result.groupOrdering, (result.groupOrdering == 0) ? "LINEAR" : "AUTO",
                        result.groupAspect, result.groupEditable,
                        result.viewProjMatrixId,
                        result.viewProjOrdering, (result.viewProjOrdering == 0) ? "LINEAR" : "AUTO",
                        result.viewProjDecompose);
                    std::fclose(groupFile);
                }
            }
        }

        writeRow();
    }


    // ---------------------------------------------------------------------
    // SCENE-WIDE CENSUS
    //
    // R1, R2 and R3 measured the wrong object. R4 found the right object and then
    // repeated the same mistake one level up: it ASSUMED the mutation lived in
    // that object because a handover document said so, and never tested it. The
    // draw's interpolation residue was found, measured at 17.11 texture units,
    // and repaired to exactly zero -- and the mutation on screen did not change.
    //
    // So this stops guessing which draw it is. Every call in the scene gets the
    // same bracket measurement, and the ranking says which one is misbehaving.
    // A call that cannot be paired with the previous frame at all is reported too,
    // because a draw that appears or vanishes for one interval is a mutation
    // nothing else here would catch.
    // ---------------------------------------------------------------------


    struct Wr64CensusEntry {
        uint32_t projectionIndex = 0;
        uint32_t callIndex = 0;
        uint32_t triangleCount = 0;
        uint32_t uniqueVertices = 0;
        uint32_t transformIndex = 0;
        uint32_t matrixId = 0;
        uint32_t coveredSamples = 0;
        uint32_t coverageBreaks = 0;
        uint32_t paired = 0;
        uint32_t ccL = 0, ccH = 0, omL = 0, omH = 0;
        float deviation = 0.0f;
        float uvSpan = 0.0f;
        float positionDelta = 0.0f;
        float texcoordDelta = 0.0f;
    };

    inline FILE *wr64CensusFile() {
        static FILE *file = []() -> FILE * {
            if (!wr64SkyBracketEnvFlag("WR64_SKY_CENSUS")) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_SKY_CENSUS_TRACE");
            const char *resolved = ((path != nullptr) && (path[0] != '\0')) ? path : "wr64-sky-census.csv";
            FILE *opened = std::fopen(resolved, "wb");
            if (opened == nullptr) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[sky-census] COULD NOT OPEN '%s'\n", resolved); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
                return nullptr;
            }

            std::fprintf(opened,
                "submission_frame,rank,projection,call,tri_count,unique_vertices,transform,matrix_id,"
                "combiner_l,combiner_h,othermode_l,othermode_h,paired,covered,breaks,"
                "deviation,uv_span,pos_delta,tc_delta\n");
            return opened;
        }();

        return file;
    }

    inline uint64_t wr64CensusSignature(const GameCall &call) {
        uint64_t key = 1469598103934665603ULL;
        const uint32_t parts[5] = {
            call.callDesc.colorCombiner.L, call.callDesc.colorCombiner.H,
            call.callDesc.otherMode.L, call.callDesc.otherMode.H,
            call.callDesc.triangleCount
        };

        for (uint32_t i = 0; i < 5; i++) {
            key ^= uint64_t(parts[i]);
            key *= 1099511628211ULL;
        }

        return key;
    }

    // One call, three weights, a coarse grid. Deliberately cheap: this runs on
    // every call in the scene, not one.
    inline bool wr64CensusMeasure(const Workload &curWorkload, const Workload &prevWorkload,
        const GameCall &curCall, const GameCall &prevCall,
        uint32_t curTransformsIndex, uint32_t prevTransformsIndex,
        GameFrameMap::WorkloadMap &curWorkloadMap, Wr64CensusEntry &out)
    {
        const DrawData &curDraw = curWorkload.drawData;
        const DrawData &prevDraw = prevWorkload.drawData;
        const uint32_t indexCount = curCall.callDesc.triangleCount * 3U;
        if ((indexCount == 0) || (curCall.callDesc.triangleCount > 64U)) { return false; }
        if ((uint64_t(curCall.meshDesc.faceIndicesStart) + indexCount) > curDraw.faceIndices.size()) { return false; }

        std::vector<uint32_t> globalVertices;
        std::vector<uint32_t> localFaces;
        globalVertices.reserve(64);
        localFaces.reserve(indexCount);
        for (uint32_t i = 0; i < indexCount; i++) {
            const uint32_t globalIndex = curDraw.faceIndices[curCall.meshDesc.faceIndicesStart + i];
            uint32_t local = UINT32_MAX;
            for (uint32_t g = 0; g < uint32_t(globalVertices.size()); g++) {
                if (globalVertices[g] == globalIndex) { local = g; break; }
            }

            if (local == UINT32_MAX) {
                local = uint32_t(globalVertices.size());
                globalVertices.push_back(globalIndex);
                if (globalVertices.size() > 256) { return false; }
            }

            localFaces.push_back(local);
        }

        const uint32_t uniqueCount = uint32_t(globalVertices.size());
        for (uint32_t g = 0; g < uniqueCount; g++) {
            const uint64_t vertex = globalVertices[g];
            if (((vertex + 1) * 3) > curDraw.posFloats.size()) { return false; }
            if (((vertex + 1) * 3) > curDraw.velFloats.size()) { return false; }
            if (((vertex + 1) * 2) > curDraw.tcFloats.size()) { return false; }
            if (((vertex + 1) * 2) > curDraw.tcVelFloats.size()) { return false; }
        }

        // Nothing moved, nothing to measure. This is what keeps the census cheap
        // enough to run on every call in the scene at native cadence.
        float earlyPos = 0.0f;
        float earlyTc = 0.0f;
        for (uint32_t g = 0; g < uniqueCount; g++) {
            const size_t vertex = size_t(globalVertices[g]);
            for (uint32_t axis = 0; axis < 3; axis++) {
                earlyPos = std::max(earlyPos, std::fabs(curDraw.velFloats[(vertex * 3) + axis]));
            }

            for (uint32_t axis = 0; axis < 2; axis++) {
                earlyTc = std::max(earlyTc, std::fabs(curDraw.tcVelFloats[(vertex * 2) + axis]));
            }
        }

        const uint32_t curTransformIndex = curCall.callDesc.minWorldMatrix;
        if ((curTransformIndex >= curDraw.worldTransforms.size()) ||
            (curTransformIndex >= curWorkloadMap.transforms.size())) { return false; }

        const GameFrameMap::TransformMap &transformMap = curWorkloadMap.transforms[curTransformIndex];
        if (!transformMap.mapped || (transformMap.prevTransformIndex >= prevDraw.worldTransforms.size())) { return false; }
        if ((curTransformsIndex >= curDraw.viewProjTransforms.size()) ||
            (prevTransformsIndex >= prevDraw.viewProjTransforms.size())) { return false; }

        const hlslpp::float4x4 &curWorld = curDraw.worldTransforms[curTransformIndex];
        const hlslpp::float4x4 &prevWorld = prevDraw.worldTransforms[transformMap.prevTransformIndex];
        const hlslpp::float4x4 &curViewProj = curDraw.viewProjTransforms[curTransformsIndex];
        const hlslpp::float4x4 &prevViewProj = prevDraw.viewProjTransforms[prevTransformsIndex];
        const bool viewProjMapped =
            (curTransformsIndex < curWorkloadMap.viewProjections.size()) &&
            curWorkloadMap.viewProjections[curTransformsIndex].mapped;

        bool matricesIdentical = true;
        for (uint32_t r = 0; (r < 4) && matricesIdentical; r++) {
            const hlslpp::float4 curWorldRow = curWorld[r];
            const hlslpp::float4 prevWorldRow = prevWorld[r];
            const hlslpp::float4 curViewRow = curViewProj[r];
            const hlslpp::float4 prevViewRow = prevViewProj[r];
            const float curValues[8] = { float(curWorldRow.x), float(curWorldRow.y), float(curWorldRow.z), float(curWorldRow.w),
                                         float(curViewRow.x), float(curViewRow.y), float(curViewRow.z), float(curViewRow.w) };
            const float prevValues[8] = { float(prevWorldRow.x), float(prevWorldRow.y), float(prevWorldRow.z), float(prevWorldRow.w),
                                          float(prevViewRow.x), float(prevViewRow.y), float(prevViewRow.z), float(prevViewRow.w) };
            for (uint32_t i = 0; i < 8; i++) {
                if (std::fabs(curValues[i] - prevValues[i]) > 1.0e-6f) { matricesIdentical = false; break; }
            }
        }

        if (matricesIdentical && (earlyPos < 1.0e-6f) && (earlyTc < 1.0e-6f)) { return false; }

        out.transformIndex = curTransformIndex;
        if (curTransformIndex < curDraw.worldTransformGroups.size()) {
            const uint32_t groupIndex = curDraw.worldTransformGroups[curTransformIndex];
            if (groupIndex < curDraw.transformGroups.size()) {
                out.matrixId = curDraw.transformGroups[groupIndex].matrixId;
            }
        }

        const hlslpp::float2 wrapPoint = curWorkload.extended.texcoordWrapPoint;
        const float wrapU = float(wrapPoint[0]);
        const float wrapV = float(wrapPoint[1]);

        const float weights[3] = { 0.0f, 0.5f, 1.0f };
        std::vector<Wr64SkyBracketVertex> evaluated[3];
        for (uint32_t w = 0; w < 3; w++) {
            const float weight = weights[w];
            hlslpp::float4x4 world;
            hlslpp::float4x4 viewProj;
            if (weight <= 0.0f) {
                world = prevWorld;
                viewProj = viewProjMapped ? prevViewProj : curViewProj;
            }
            else if (weight >= 1.0f) {
                world = curWorld;
                viewProj = curViewProj;
            }
            else {
                world = transformMap.rigidBody.lerp(weight, prevWorld, curWorld, true);
                viewProj = viewProjMapped
                    ? curWorkloadMap.viewProjections[curTransformsIndex].rigidBody.lerp(weight, prevViewProj, curViewProj, true)
                    : curViewProj;
            }

            evaluated[w].resize(uniqueCount);
            for (uint32_t g = 0; g < uniqueCount; g++) {
                const size_t vertex = size_t(globalVertices[g]);
                const float rewind = 1.0f - weight;
                const float position[3] = {
                    curDraw.posFloats[(vertex * 3) + 0] - (curDraw.velFloats[(vertex * 3) + 0] * rewind),
                    curDraw.posFloats[(vertex * 3) + 1] - (curDraw.velFloats[(vertex * 3) + 1] * rewind),
                    curDraw.posFloats[(vertex * 3) + 2] - (curDraw.velFloats[(vertex * 3) + 2] * rewind)
                };
                Wr64SkyBracketVertex &entry = evaluated[w][g];
                entry.u = curDraw.tcFloats[(vertex * 2) + 0] - (curDraw.tcVelFloats[(vertex * 2) + 0] * rewind);
                entry.v = curDraw.tcFloats[(vertex * 2) + 1] - (curDraw.tcVelFloats[(vertex * 2) + 1] * rewind);
                wr64SkyBracketProjectClip(position, world, viewProj, entry);
            }
        }

        float worstPos = 0.0f;
        float worstTc = 0.0f;
        for (uint32_t g = 0; g < uniqueCount; g++) {
            const size_t vertex = size_t(globalVertices[g]);
            const float dx = curDraw.velFloats[(vertex * 3) + 0];
            const float dy = curDraw.velFloats[(vertex * 3) + 1];
            const float dz = curDraw.velFloats[(vertex * 3) + 2];
            worstPos = std::max(worstPos, std::sqrt((dx * dx) + (dy * dy) + (dz * dz)));
            const float du = curDraw.tcVelFloats[(vertex * 2) + 0];
            const float dv = curDraw.tcVelFloats[(vertex * 2) + 1];
            worstTc = std::max(worstTc, std::sqrt((du * du) + (dv * dv)));
        }

        for (int gx = -1; gx <= 1; gx++) {
            for (int gy = -1; gy <= 1; gy++) {
                const float pointX = float(gx) * 0.6f;
                const float pointY = float(gy) * 0.6f;
                float u0, v0, u1, v1, um, vm;
                const bool c0 = wr64SkyBracketSampleFan(evaluated[0], localFaces, pointX, pointY, u0, v0);
                const bool c1 = wr64SkyBracketSampleFan(evaluated[2], localFaces, pointX, pointY, u1, v1);
                if (!c0 || !c1) { continue; }
                if (!wr64SkyBracketSampleFan(evaluated[1], localFaces, pointX, pointY, um, vm)) {
                    out.coverageBreaks++;
                    continue;
                }

                out.coveredSamples++;
                const float su = wr64SkyBracketUnwrap(u1, u0, wrapU);
                const float sv = wr64SkyBracketUnwrap(v1, v0, wrapV);
                const float mu = wr64SkyBracketUnwrap(um, u0, wrapU);
                const float mv = wr64SkyBracketUnwrap(vm, v0, wrapV);
                out.uvSpan = std::max(out.uvSpan, std::sqrt(((su - u0) * (su - u0)) + ((sv - v0) * (sv - v0))));
                out.deviation = std::max(out.deviation,
                    wr64SkyBracketSegmentDeviation(mu, mv, u0, v0, su, sv));
            }
        }

        out.triangleCount = curCall.callDesc.triangleCount;
        out.uniqueVertices = uniqueCount;
        out.positionDelta = worstPos;
        out.texcoordDelta = worstTc;
        out.ccL = curCall.callDesc.colorCombiner.L;
        out.ccH = curCall.callDesc.colorCombiner.H;
        out.omL = curCall.callDesc.otherMode.L;
        out.omH = curCall.callDesc.otherMode.H;
        out.paired = 1;
        return true;
    }

    inline void wr64CensusEvaluate(WorkloadQueue &workloadQueue, const GameScene &curScene, const GameScene &prevScene,
        GameFrameMap::WorkloadMap &curWorkloadMap)
    {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        FILE *file = wr64CensusFile();
        if (file == nullptr) { return; }

        struct Slot { const GameCall *call; uint32_t projection; uint32_t call_index; uint32_t transformsIndex; uint32_t workloadIndex; };
        std::vector<Slot> curSlots;
        std::vector<Slot> prevSlots;
        auto gather = [&](const GameScene &scene, std::vector<Slot> &slots) {
            for (const GameIndices::Projection &indices : scene.projections) {
                if (indices.workloadIndex >= workloadQueue.workloads.size()) { continue; }
                const Workload &workload = workloadQueue.workloads[indices.workloadIndex];
                if (indices.fbPairIndex >= workload.fbPairs.size()) { continue; }
                const FramebufferPair &pair = workload.fbPairs[indices.fbPairIndex];
                if (indices.projectionIndex >= pair.projections.size()) { continue; }
                const Projection &projection = pair.projections[indices.projectionIndex];
                const uint32_t callCount = std::min(projection.gameCallCount, uint32_t(projection.gameCalls.size()));
                for (uint32_t c = 0; c < callCount; c++) {
                    slots.push_back({ &projection.gameCalls[c], indices.projectionIndex, c,
                                      projection.transformsIndex, indices.workloadIndex });
                }
            }
        };

        gather(curScene, curSlots);
        gather(prevScene, prevSlots);
        if (curSlots.empty()) { return; }

        const uint64_t frame = workloadQueue.workloads[curSlots[0].workloadIndex].submissionFrame;

        std::vector<Wr64CensusEntry> results;
        results.reserve(curSlots.size());
        std::vector<uint32_t> used(prevSlots.size(), 0);
        for (const Slot &cur : curSlots) {
            const uint64_t key = wr64CensusSignature(*cur.call);
            int matched = -1;
            for (uint32_t p = 0; p < uint32_t(prevSlots.size()); p++) {
                if (used[p]) { continue; }
                if (wr64CensusSignature(*prevSlots[p].call) != key) { continue; }
                matched = int(p);
                break;
            }

            Wr64CensusEntry entry;
            entry.projectionIndex = cur.projection;
            entry.callIndex = cur.call_index;
            entry.triangleCount = cur.call->callDesc.triangleCount;
            entry.ccL = cur.call->callDesc.colorCombiner.L;
            entry.ccH = cur.call->callDesc.colorCombiner.H;
            entry.omL = cur.call->callDesc.otherMode.L;
            entry.omH = cur.call->callDesc.otherMode.H;
            if (matched < 0) {
                // Unpaired: present now, absent a frame ago. Reported as its own event.
                results.push_back(entry);
                continue;
            }

            used[matched] = 1;
            const Workload &curWorkload = workloadQueue.workloads[cur.workloadIndex];
            const Workload &prevWorkload = workloadQueue.workloads[prevSlots[matched].workloadIndex];
            if (wr64CensusMeasure(curWorkload, prevWorkload, *cur.call, *prevSlots[matched].call,
                                  cur.transformsIndex, prevSlots[matched].transformsIndex, curWorkloadMap, entry)) {
                results.push_back(entry);
            }
        }

        std::sort(results.begin(), results.end(), [](const Wr64CensusEntry &a, const Wr64CensusEntry &b) {
            if (a.paired != b.paired) { return a.paired < b.paired; }
            return a.deviation > b.deviation;
        });

        const uint32_t limit = std::min<uint32_t>(6, uint32_t(results.size()));
        for (uint32_t i = 0; i < limit; i++) {
            const Wr64CensusEntry &e = results[i];
            if ((e.paired == 1) && (e.deviation <= 0.75f) && (e.coverageBreaks == 0)) { continue; }
            std::fprintf(file,
                "%llu,%u,%u,%u,%u,%u,%u,%08X,%08X,%08X,%08X,%08X,%u,%u,%u,%.4f,%.4f,%.3f,%.3f\n",
                static_cast<unsigned long long>(frame), i,
                e.projectionIndex, e.callIndex, e.triangleCount, e.uniqueVertices,
                e.transformIndex, e.matrixId, e.ccL, e.ccH, e.omL, e.omH,
                e.paired, e.coveredSamples, e.coverageBreaks,
                e.deviation, e.uvSpan, e.positionDelta, e.texcoordDelta);
        }

        std::fflush(file);
    }

    // ---------------------------------------------------------------------
    // The shipped correction, without the instrument
    //
    // wr64SkyBracketEvaluateOne carries the fix, but it also samples a 5x5 grid at
    // five weights, decomposes the world-to-texel map and writes a CSV row, and none
    // of that belongs in a normal session. This is the same correction reduced to
    // what it needs: find the sky calls, measure the per-vertex texture-coordinate
    // and position velocities, and zero the texture-coordinate velocity on the
    // frames where the producer has renumbered the patch.
    //
    // Deliberately kept in step with the block in wr64SkyBracketEvaluateOne: same
    // thresholds, same predicate, same action. Only one of the two ever runs.
    // ---------------------------------------------------------------------

    inline void wr64SkyTexcoordFixOne(WorkloadQueue &workloadQueue, const Wr64SkyBracketLocation &location,
        ModifiedBuffers &modifiedBuffers)
    {
        if (!location.found) {
            return;
        }

        Workload &workload = workloadQueue.workloads[location.workloadIndex];
        DrawData &draw = workload.drawData;
        const uint32_t indexCount = location.triangleCount * 3U;
        if ((uint64_t(location.faceIndicesStart) + indexCount) > draw.faceIndices.size()) {
            return;
        }

        uint32_t globalVertices[64];
        uint32_t uniqueCount = 0;
        for (uint32_t i = 0; i < indexCount; i++) {
            const uint32_t globalIndex = draw.faceIndices[location.faceIndicesStart + i];
            bool seen = false;
            for (uint32_t g = 0; g < uniqueCount; g++) {
                if (globalVertices[g] == globalIndex) {
                    seen = true;
                    break;
                }
            }

            if (!seen) {
                if (uniqueCount >= 64U) {
                    return;
                }

                globalVertices[uniqueCount] = globalIndex;
                uniqueCount++;
            }
        }

        if (uniqueCount < 3U) {
            return;
        }

        for (uint32_t g = 0; g < uniqueCount; g++) {
            const uint64_t vertex = globalVertices[g];
            if ((((vertex + 1ULL) * 3ULL) > draw.velFloats.size()) ||
                (((vertex + 1ULL) * 2ULL) > draw.tcVelFloats.size()))
            {
                return;
            }
        }

        float positionDeltaMax = 0.0f;
        float texcoordDeltaMax = 0.0f;
        for (uint32_t g = 0; g < uniqueCount; g++) {
            const size_t vertex = size_t(globalVertices[g]);
            const float dx = draw.velFloats[(vertex * 3) + 0];
            const float dy = draw.velFloats[(vertex * 3) + 1];
            const float dz = draw.velFloats[(vertex * 3) + 2];
            positionDeltaMax = std::max(positionDeltaMax, std::sqrt((dx * dx) + (dy * dy) + (dz * dz)));
            const float du = draw.tcVelFloats[(vertex * 2) + 0];
            const float dv = draw.tcVelFloats[(vertex * 2) + 1];
            texcoordDeltaMax = std::max(texcoordDeltaMax, std::sqrt((du * du) + (dv * dv)));
        }

        if ((texcoordDeltaMax <= wr64SkyTexcoordJumpThreshold()) &&
            (positionDeltaMax <= wr64SkyReanchorThreshold()))
        {
            return;
        }

        for (uint32_t g = 0; g < uniqueCount; g++) {
            const size_t vertex = size_t(globalVertices[g]);
            draw.tcVelFloats[(vertex * 2) + 0] = 0.0f;
            draw.tcVelFloats[(vertex * 2) + 1] = 0.0f;
        }

        modifiedBuffers.texcoordVelocity = true;
    }

    inline void wr64SkyTexcoordFixApply(WorkloadQueue &workloadQueue, const GameScene &curScene,
        ModifiedBuffers &modifiedBuffers)
    {
        thread_local std::vector<Wr64SkyBracketLocation> locations;
        wr64SkyBracketFindAll(workloadQueue, curScene, locations, 4);
        for (const Wr64SkyBracketLocation &location : locations) {
            wr64SkyTexcoordFixOne(workloadQueue, location, modifiedBuffers);
        }
    }

    // ID matching can write the course fan's velocities even when its scene
    // receives no previous-scene match. Complete the same correction after all
    // matching for native split-screen workloads, before the velocity upload.
    inline void wr64SkyTexcoordFixSplitWorkload(WorkloadQueue &workloadQueue,
        uint32_t workloadIndex, ModifiedBuffers &modifiedBuffers)
    {
        if (!wr64SkyTexcoordSmartEnabled() || wr64SkyBracketEnabled() ||
            (workloadIndex >= workloadQueue.workloads.size())) return;

        const Workload &workload = workloadQueue.workloads[workloadIndex];
        const DrawData &draw = workload.drawData;
        uint32_t availableViews = 0;
        for (const auto &group : draw.transformGroups) {
            availableViews |= group.matrixId == 0x57524300U ? 1U :
                group.matrixId == 0x57524301U ? 2U : 0U;
            if (availableViews == 3U) break;
        }
        if (availableViews != 3U) return;

        uint32_t views = 0;
        const auto courseView = [&](const GameCall &call, bool sky) -> uint32_t {
            const DrawCall &desc = call.callDesc;
            if ((desc.minWorldMatrix > desc.maxWorldMatrix) ||
                (desc.maxWorldMatrix >= draw.worldTransforms.size()) ||
                (desc.maxWorldMatrix >= draw.worldTransformGroups.size())) return 0;
            const auto viewForTransform = [&](uint32_t transform) -> uint32_t {
                const uint32_t group = draw.worldTransformGroups[transform];
                if (group >= draw.transformGroups.size()) return 0;
                const uint32_t id = draw.transformGroups[group].matrixId;
                return id == 0x57524300U ? 1U : id == 0x57524301U ? 2U : 0U;
            };

            // Reject ordinary scenery using only its transform range. Inspect
            // faces only for course-group candidates, never every scene vertex.
            uint32_t possibleViews = 0;
            for (uint32_t transform = desc.minWorldMatrix;
                transform <= desc.maxWorldMatrix; ++transform)
                possibleViews |= viewForTransform(transform);
            if (possibleViews == 0) return 0;
            if (!sky && (possibleViews & ~views) == 0) return 0;

            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t count = uint64_t(desc.triangleCount) * 3U;
            if ((count == 0) || (first + count > draw.faceIndices.size())) return 0;
            uint32_t view = 0;
            for (uint64_t i = first; i < first + count; ++i) {
                const uint32_t vertex = draw.faceIndices[size_t(i)];
                if (vertex >= draw.worldIndices.size()) return 0;
                const uint32_t transform = draw.worldIndices[vertex];
                if ((transform < desc.minWorldMatrix) ||
                    (transform > desc.maxWorldMatrix)) return 0;
                const uint32_t vertexView = viewForTransform(transform);
                if (vertexView == 0 || (view != 0 && view != vertexView)) return 0;
                view = vertexView;
            }
            return view;
        };

        thread_local std::vector<Wr64SkyBracketLocation> locations;
        locations.clear();
        const uint32_t fbCount = std::min(workload.fbPairCount, uint32_t(workload.fbPairs.size()));
        for (uint32_t f = 0; f < fbCount; ++f) {
            const FramebufferPair &fb = workload.fbPairs[f];
            const uint32_t projectionCount = std::min(fb.projectionCount, uint32_t(fb.projections.size()));
            for (uint32_t p = 0; p < projectionCount; ++p) {
                const Projection &projection = fb.projections[p];
                if (projection.type != Projection::Type::Perspective) continue;
                const uint32_t callCount = std::min(projection.gameCallCount, uint32_t(projection.gameCalls.size()));
                for (uint32_t c = 0; c < callCount; ++c) {
                    const GameCall &call = projection.gameCalls[c];
                    const bool sky = wr64SkyBracketIsExactSkyCall(call.callDesc);
                    if (!sky && views == 3U) continue;
                    const uint32_t view = courseView(call, sky);
                    if (view == 0) continue;
                    views |= view;
                    if (!sky) continue;
                    Wr64SkyBracketLocation location;
                    location.found = true;
                    location.workloadIndex = workloadIndex;
                    location.fbPairIndex = f;
                    location.projectionIndex = p;
                    location.callIndex = c;
                    location.faceIndicesStart = call.meshDesc.faceIndicesStart;
                    location.triangleCount = call.callDesc.triangleCount;
                    location.minWorldMatrix = call.callDesc.minWorldMatrix;
                    location.maxWorldMatrix = call.callDesc.maxWorldMatrix;
                    location.transformsIndex = projection.transformsIndex;
                    locations.push_back(location);
                }
            }
        }

        // Both IDs are authored by the two native course wrappers. The 1P
        // wrapper only emits 57524300. A missing cloud may still leave its
        // view's background call, so scope does not require two visible clouds.
        if (views != 3U) return;
        for (const Wr64SkyBracketLocation &location : locations)
            wr64SkyTexcoordFixOne(workloadQueue, location, modifiedBuffers);
    }

    // The scene entry point. Called from GameFrame::matchScene per matched
    // scene pair, after transform matching has settled and before
    // modifiedBuffers is merged.
    inline void wr64SkyBracketEvaluate(WorkloadQueue &workloadQueue, const GameScene &curScene, const GameScene &prevScene,
        GameFrameMap::WorkloadMap &curWorkloadMap, ModifiedBuffers &modifiedBuffers)
    {
        // Detector off -- the normal case, and what ships. Apply the correction and
        // nothing else: no sampling, no CSV, no census, no injection.
        if (!wr64SkyBracketEnabled()) {
            if (wr64SkyTexcoordSmartEnabled()) {
                wr64SkyTexcoordFixApply(workloadQueue, curScene, modifiedBuffers);
            }

            return;
        }

        thread_local std::vector<Wr64SkyBracketLocation> curLocations;
        thread_local std::vector<Wr64SkyBracketLocation> prevLocations;
        wr64SkyBracketFindAll(workloadQueue, curScene, curLocations, 4);
        wr64SkyBracketFindAll(workloadQueue, prevScene, prevLocations, 4);

        // Nothing of ours in this scene. matchScene runs for every matched scene
        // pair, orthographic and menu scenes included, and writing a row for each
        // of those would bury the rows that mean something under an order of
        // magnitude more that do not.
        if (curLocations.empty()) {
            wr64CensusEvaluate(workloadQueue, curScene, prevScene, curWorkloadMap);
            return;
        }

        wr64CensusEvaluate(workloadQueue, curScene, prevScene, curWorkloadMap);

        const size_t pairCount = std::min(curLocations.size(), prevLocations.size());
        for (size_t i = 0; i < curLocations.size(); i++) {
            const Wr64SkyBracketLocation unmatched;
            wr64SkyBracketEvaluateOne(workloadQueue, curLocations[i],
                (i < pairCount) ? prevLocations[i] : unmatched,
                uint32_t(i), curWorkloadMap, modifiedBuffers);
        }
    }
};
