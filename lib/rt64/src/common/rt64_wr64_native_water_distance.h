#pragma once
#include "rt64_wr64_far_water_distance.h"
#include "rt64_wr64_rt_view.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <map>
#include <set>
#include <vector>

namespace RT64 {
    // The shipped widescreen patch uses a 424x240 source viewport. Classify
    // before horizontal/vertical output mapping, just like split water effects.
    inline int32_t wr64FarWaterSourceOwner(const WR64RTViewDomain &domain) {
        const uint32_t split = wr64RTNativeRaceView(domain);
        if (split) return int32_t(split);
        if (!domain.perspective || domain.menuModelPreview || domain.menuWaterPreview) return -1;
        for (uint32_t axis = 0; axis < 3; ++axis)
            if (!std::isfinite(domain.scale[axis]) || !std::isfinite(domain.translate[axis])) return -1;
        return domain.scale[0] == 212.0f && std::abs(domain.scale[1]) == 120.0f &&
            domain.translate[0] == 212.0f && domain.translate[1] == 120.0f &&
            domain.scissor[0] == 0 && domain.scissor[1] == 0 &&
            domain.scissor[2] == 1696 && domain.scissor[3] == 960 ? 0 : -1;
    }
    struct Wr64NativeWaterDistanceVertex {
        uint32_t vertex = 0, source = 0;
        std::array<float, 3> position{}, velocity{};
    };
    struct Wr64NativeWaterDistanceView {
        uint32_t mode = 0, projection = 0, cameraIndex = 0;
        bool coherent = true;
        std::vector<Wr64NativeWaterDistanceVertex> vertices;
    };
    // Native 10/16-ring sheets already have six private outer fan vertices.
    // Keep their topology and neutral attributes, and change only outer X/Z.
    // The dense 12-ring one-player sheet continues to use its accepted annulus.
    template<typename Draw>
    bool wr64ExtendNativeWaterFan(Draw &draw, uint32_t first, uint32_t triangles,
        uint32_t projection, uint32_t owner, uint32_t requestedMode, uint32_t cameraIndex = 0) {
        if (owner > 2 || cameraIndex > 1 || !draw.wr64NativeWaterDistance[owner].vertices.empty()) return false;
        const uint32_t rings = triangles == 612 ? 10 : triangles == 1548 ? 16 : 0;
        if (!rings) return false;
        const size_t count = draw.posFloats.size() / 3;
        if (draw.posFloats.size() != count * 3 || draw.velFloats.size() != count * 3 ||
            draw.vertexSegmentedAddresses.size() != count || draw.viewProjIndices.size() != count ||
            draw.worldIndices.size() != count || uint64_t(first) + uint64_t(triangles) * 3 > draw.faceIndices.size()) return false;
        std::map<uint32_t, uint32_t> primary, suffix;
        std::set<uint32_t> primaryVertices, suffixVertices;
        std::map<std::pair<uint32_t,uint32_t>, uint32_t> edges;
        std::set<std::array<uint32_t,3>> uniqueFaces;
        uint32_t world = UINT32_MAX;
        for (uint32_t face = 0; face < triangles; ++face) {
            std::array<uint32_t,3> keys{};
            for (uint32_t c = 0; c < 3; ++c) {
                const uint32_t v = draw.faceIndices[first + face * 3 + c];
                if (v >= count || draw.viewProjIndices[v] != projection) return false;
                if (world == UINT32_MAX) world = draw.worldIndices[v];
                if (draw.worldIndices[v] != world) return false;
                const uint32_t key = draw.vertexSegmentedAddresses[v];
                if (key < 0x03000000 || key >= 0x04000000) return false;
                for (uint32_t axis = 0; axis < 3; ++axis)
                    if (!std::isfinite(draw.posFloats[v * 3 + axis]) || !std::isfinite(draw.velFloats[v * 3 + axis])) return false;
                keys[c] = key;
                auto &map = face < triangles - 12 ? primary : suffix;
                auto &physical = face < triangles - 12 ? primaryVertices : suffixVertices;
                const auto inserted = map.emplace(key, v);
                if (!inserted.second) for (uint32_t axis = 0; axis < 3; ++axis)
                    if (draw.posFloats[v * 3 + axis] != draw.posFloats[inserted.first->second * 3 + axis]) return false;
                physical.insert(v);
            }
            if (face < triangles - 12) {
                auto sorted = keys; std::sort(sorted.begin(), sorted.end());
                if (sorted[0] == sorted[1] || sorted[1] == sorted[2] || !uniqueFaces.insert(sorted).second) return false;
                for (uint32_t c = 0; c < 3; ++c) if (++edges[std::minmax(keys[c], keys[(c + 1) % 3])] > 2) return false;
            }
        }
        if (primary.size() != 1 + 3 * rings * (rings + 1) || suffix.size() != 12) return false;
        std::map<uint32_t, std::set<uint32_t>> boundary;
        for (const auto &edge : edges) if (edge.second == 1) {
            boundary[edge.first.first].insert(edge.first.second); boundary[edge.first.second].insert(edge.first.first);
        }
        if (boundary.size() != 6 * rings) return false;
        for (const auto &edge : boundary) if (edge.second.size() != 2) return false;
        std::set<uint32_t> outer;
        std::array<double, 3> center{}, centerVelocity{};
        uint32_t anchors = 0;
        for (const auto &entry : suffix) {
            if (!primary.count(entry.first)) { outer.insert(entry.first); continue; }
            if (!boundary.count(entry.first)) return false;
            for (uint32_t axis = 0; axis < 3; ++axis)
                if (draw.posFloats[entry.second * 3 + axis] != draw.posFloats[primary.at(entry.first) * 3 + axis]) return false;
            ++anchors;
            for (uint32_t axis = 0; axis < 3; ++axis) {
                center[axis] += draw.posFloats[entry.second * 3 + axis] / 6.0;
                centerVelocity[axis] += draw.velFloats[entry.second * 3 + axis] / 6.0;
            }
        }
        if (anchors != 6 || outer.size() != 6) return false;
        Wr64NativeWaterDistanceView pending;
        pending.mode = wr64FarWaterDistanceMode(requestedMode); pending.projection = projection; pending.cameraIndex = cameraIndex;
        const double scale = pending.mode == 0 ? 1.0 : pending.mode == 1 ? 1.5 : double(pending.mode);
        std::map<uint32_t, std::array<float,3>> positions;
        for (uint32_t v : suffixVertices) if (outer.count(draw.vertexSegmentedAddresses[v])) {
            if (primaryVertices.count(v)) return false;
            Wr64NativeWaterDistanceVertex vertex; vertex.vertex = v; vertex.source = draw.vertexSegmentedAddresses[v];
            for (uint32_t axis = 0; axis < 3; ++axis) {
                vertex.position[axis] = draw.posFloats[v * 3 + axis];
                vertex.velocity[axis] = draw.velFloats[v * 3 + axis];
                if (axis != 1 && pending.mode) {
                    vertex.position[axis] = float(center[axis] + (double(vertex.position[axis]) - center[axis]) * scale);
                    vertex.velocity[axis] = float(centerVelocity[axis] + (double(vertex.velocity[axis]) - centerVelocity[axis]) * scale);
                }
                if (!std::isfinite(vertex.position[axis]) || !std::isfinite(vertex.velocity[axis])) return false;
            }
            positions.emplace(v, vertex.position); pending.vertices.push_back(vertex);
        }
        // The native fan intentionally overlaps or collapses at some camera
        // headings. Original retains that exact geometry. For an extension,
        // prove a coherent annulus against the PRIMARY sheet's orientation;
        // comparing each old fan face's sign would reject valid extra coverage.
        const auto signedArea = [&](uint32_t face, bool expanded) {
            double points[3][2]{};
            for (uint32_t c = 0; c < 3; ++c) {
                const uint32_t v = draw.faceIndices[first + face * 3 + c];
                for (uint32_t axis = 0; axis < 2; ++axis)
                    points[c][axis] = expanded && positions.count(v) ? positions.at(v)[axis * 2] : draw.posFloats[v * 3 + axis * 2];
            }
            return (points[1][0]-points[0][0])*(points[2][1]-points[0][1]) -
                (points[1][1]-points[0][1])*(points[2][0]-points[0][0]);
        };
        double primaryArea = 0;
        for (uint32_t face = 0; face < triangles - 12; ++face) primaryArea += signedArea(face, false);
        if (std::abs(primaryArea) < 1e-5) return false;
        for (uint32_t face = triangles - 12; face < triangles; ++face)
            pending.coherent = pending.coherent && signedArea(face, true) * (primaryArea > 0 ? 1.0 : -1.0) > 1e-5;
        if (pending.mode && !pending.coherent) return false;
        for (const auto &vertex : pending.vertices) if (pending.mode)
            for (uint32_t axis : {0U, 2U}) draw.posFloats[vertex.vertex * 3 + axis] = vertex.position[axis];
        draw.wr64NativeWaterDistance[owner] = std::move(pending);
        return true;
    }

    // Run after every ordinary matcher. Stored committed endpoints carry their
    // own setting and view, so neither live settings nor another player's fan
    // can change the reconstructed previous endpoint.
    template<typename Draw>
    bool wr64FinalizeNativeWaterDistance(Draw &current, const Draw &previous, bool compatibleScene = true,
        const std::array<uint32_t, 3> *previousProjections = nullptr) {
        bool changed = false;
        for (uint32_t owner = 0; owner < 3; ++owner) {
            const auto &cur = current.wr64NativeWaterDistance[owner], &prev = previous.wr64NativeWaterDistance[owner];
            if (cur.vertices.empty() || (!cur.mode && !prev.mode)) continue;
            std::map<uint32_t, std::array<float,3>> old;
            if (compatibleScene && cur.coherent && prev.coherent && cur.cameraIndex == prev.cameraIndex &&
                (!previousProjections || (*previousProjections)[owner] == prev.projection)) for (const auto &v : prev.vertices) old.emplace(v.source, v.position);
            for (const auto &v : cur.vertices) {
                if (uint64_t(v.vertex) * 3 + 3 > current.velFloats.size()) continue;
                for (uint32_t axis : {0U, 2U}) current.velFloats[v.vertex * 3 + axis] = old.count(v.source)
                    ? v.position[axis] - old.at(v.source)[axis] : v.velocity[axis];
                changed = true;
            }
        }
        return changed;
    }
    // Resolve history through the renderer's actual scene/camera match. A
    // reordered workload or rejected camera cut must not inherit ordinal data.
    template<typename Workloads, typename WorkloadMap>
    bool wr64FinalizeMappedNativeWaterDistance(Workloads &workloads, uint32_t index,
        const WorkloadMap &mapping) {
        if (index >= workloads.size()) return false;
        auto &current = workloads[index];
        const bool previousAvailable = mapping.mapped && mapping.prevWorkloadIndex < workloads.size();
        const auto &previous = workloads[previousAvailable ? mapping.prevWorkloadIndex : index];
        const bool compatible = previousAvailable && current.wr64RtCourse == previous.wr64RtCourse;
        std::array<uint32_t,3> previousProjections{UINT32_MAX, UINT32_MAX, UINT32_MAX};
        if (compatible) for (uint32_t owner = 0; owner < 3; ++owner) {
            const auto &view = current.drawData.wr64NativeWaterDistance[owner];
            if (view.projection < mapping.viewProjections.size()) {
                const auto &projection = mapping.viewProjections[view.projection];
                if (projection.mapped) previousProjections[owner] = projection.prevTransformIndex;
            }
        }
        return wr64FinalizeNativeWaterDistance(current.drawData, previous.drawData, compatible, &previousProjections);
    }

}
