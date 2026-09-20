#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <map>
#include <set>
#include <vector>

namespace RT64 {
    // Snapshot the native race state before publishing the workload. Original
    // and Enhanced assets share these two-player sheets; menus do not.
    inline constexpr bool wr64NativeSplitWaterScope(uint32_t course, uint32_t players,
        uint32_t phase, uint32_t mode, bool loadedEnhanced = false) {
        return course <= 8 && (course != 0 || loadedEnhanced) && players == 2 && phase == 1 &&
            mode >= 40 && mode <= 45;
    }

    inline bool wr64SplitWaterRoundnessMatching(bool nativeScope, float strength) {
        return nativeScope && std::isfinite(strength) && strength > 0.0f;
    }

    struct Wr64WaterRoundnessResult {
        bool applied = false;
        uint32_t logicalVertices = 0, boundaryVertices = 0, changedVertices = 0;
    };

    // Native 2P water uses either the 10-ring sheet (600 primary triangles)
    // or the special 16-ring sheet (1536). The last twelve faces are its far
    // fan. This is height filtering only: no annulus, masks or topology edits.
    // DrawData is a template so the same production function can be exercised
    // against decoded native display lists without constructing a renderer.
    template<typename DrawData>
    Wr64WaterRoundnessResult wr64RoundNativeSplitWater(DrawData &draw, uint32_t first,
        uint32_t triangles, uint32_t projection, uint32_t nativeView, float strength) {
        Wr64WaterRoundnessResult result;
        const uint32_t rings = triangles == 612 ? 10 : triangles == 1548 ? 16 : 0;
        if (!rings || nativeView < 1 || nativeView > 2 || !std::isfinite(strength) || strength <= 0) return result;
        strength = std::min(strength, 1.0f);
        const size_t vertices = draw.posFloats.size() / 3;
        const uint64_t end = uint64_t(first) + uint64_t(triangles) * 3;
        if (draw.posFloats.size() != vertices * 3 || end > draw.faceIndices.size() ||
            draw.vertexSegmentedAddresses.size() != vertices || draw.viewProjIndices.size() != vertices ||
            draw.worldIndices.size() != vertices) return result;
        const uint32_t primaryTriangles = triangles - 12;
        std::map<uint32_t, uint32_t> representatives;
        std::map<uint32_t, std::set<uint32_t>> neighbours;
        std::map<std::pair<uint32_t,uint32_t>, uint32_t> edges;
        std::set<std::array<uint32_t,3>> faces;
        std::set<uint32_t> primaryPhysical, suffixPhysical;
        uint32_t world = UINT32_MAX;
        for (uint32_t t = 0; t < triangles; ++t) {
            uint32_t keys[3];
            for (uint32_t corner = 0; corner < 3; ++corner) {
                const uint32_t v = draw.faceIndices[size_t(first) + size_t(t) * 3 + corner];
                if (v >= vertices || draw.viewProjIndices[v] != projection) return result;
                if (world == UINT32_MAX) world = draw.worldIndices[v];
                if (draw.worldIndices[v] != world) return result;
                const uint32_t address = draw.vertexSegmentedAddresses[v];
                if (address < 0x03000000U || address >= 0x04000000U) return result;
                for (uint32_t c = 0; c < 3; ++c) if (!std::isfinite(draw.posFloats[size_t(v) * 3 + c])) return result;
                keys[corner] = address;
                if (t >= primaryTriangles) { suffixPhysical.insert(v); continue; }
                primaryPhysical.insert(v);
                const auto inserted = representatives.emplace(address, v);
                if (!inserted.second) {
                    const uint32_t other = inserted.first->second;
                    // A reloaded source can be welded only if the captured
                    // endpoint really is identical. Never average an alias.
                    for (uint32_t c = 0; c < 3; ++c)
                        if (draw.posFloats[size_t(v)*3+c] != draw.posFloats[size_t(other)*3+c]) return result;
                }
            }
            if (t >= primaryTriangles) continue;
            if (keys[0] == keys[1] || keys[1] == keys[2] || keys[2] == keys[0]) return result;
            std::array<uint32_t,3> sorted = {keys[0],keys[1],keys[2]};
            std::sort(sorted.begin(),sorted.end());
            if (!faces.insert(sorted).second) return result;
            for (uint32_t c = 0; c < 3; ++c) {
                const uint32_t a = keys[c], b = keys[(c+1)%3];
                neighbours[a].insert(b); neighbours[b].insert(a);
                if (++edges[std::minmax(a,b)] > 2) return result;
            }
        }
        const uint32_t expectedLogical = 1 + 3*rings*(rings+1), expectedBoundary = 6*rings;
        if (representatives.size() != expectedLogical) return result;
        std::map<uint32_t,std::set<uint32_t>> boundaryEdges;
        for (const auto &edge : edges) if (edge.second == 1) {
            boundaryEdges[edge.first.first].insert(edge.first.second);
            boundaryEdges[edge.first.second].insert(edge.first.first);
        }
        if (boundaryEdges.size() != expectedBoundary) return result;
        for (const auto &edge : boundaryEdges) if (edge.second.size() != 2) return result;
        // Prove one connected primary sheet, rather than accepting disjoint
        // patches with the right aggregate counts.
        std::set<uint32_t> visited;
        std::vector<uint32_t> pending{representatives.begin()->first};
        while (!pending.empty()) {
            const uint32_t key = pending.back(); pending.pop_back();
            if (!visited.insert(key).second) continue;
            for (uint32_t next : neighbours[key]) if (!visited.count(next)) pending.push_back(next);
        }
        if (visited.size() != expectedLogical) return result;
        for (uint32_t v : suffixPhysical) {
            const uint32_t key = draw.vertexSegmentedAddresses[v];
            if (representatives.count(key) && !boundaryEdges.count(key)) return result;
        }
        std::map<uint32_t,float> rounded;
        for (const auto &item : representatives) {
            const uint32_t key = item.first, v = item.second;
            const size_t degree = neighbours[key].size();
            const bool boundary = boundaryEdges.count(key) != 0;
            if ((boundary && degree != 3 && degree != 4) || (!boundary && degree != 6)) return result;
            const float y = draw.posFloats[size_t(v)*3+1];
            double mean = 0;
            if (!boundary) {
                for (uint32_t next : neighbours[key]) mean += double(draw.posFloats[size_t(representatives.at(next))*3+1]);
                mean /= 6;
            }
            const float value = boundary ? y : float(double(y)+double(strength)*(mean-double(y)));
            if (!std::isfinite(value)) return result;
            rounded.emplace(key,value);
        }
        // Commit after all validation and all means use the frozen input.
        for (uint32_t v : primaryPhysical) {
            const float y = rounded.at(draw.vertexSegmentedAddresses[v]);
            result.changedVertices += draw.posFloats[size_t(v)*3+1] != y ? 1u : 0u;
            draw.posFloats[size_t(v)*3+1] = y;
        }
        result.applied = true;
        result.logicalVertices = expectedLogical; result.boundaryVertices = expectedBoundary;
        return result;
    }
}
