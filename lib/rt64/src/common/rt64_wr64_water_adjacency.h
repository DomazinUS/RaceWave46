#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <map>
#include <set>
#include <vector>

namespace RT64 {
    // Reflection shading topology only. Positions and indices used to rasterize
    // the water are never modified. The GPU evaluates incident face normals
    // from its current presentation-time world-position buffer.
    struct Wr64WaterAdjacency {
        // Optional exact presentation identity: velocity XYZ, field info XYZW,
        // previous field height, X shift, and Z shift. Equal native endpoints
        // alone are insufficient when their displayed trajectories differ.
        using Payload = std::array<uint32_t, 10>;
        // One uint2 header per global vertex: absolute byte offset, face count.
        // Incident entries are uint3 global vertex indices. Welded vertices
        // share one list; unreferenced or collapsed-only vertices have count 0.
        std::vector<uint32_t> words;
        uint32_t validNodes = 0;
        uint32_t weldDuplicates = 0;
        uint32_t triangles = 0;
        const char *error = "";

        bool build(uint32_t vertexCount, const std::vector<float> &posFloats,
            const std::vector<uint16_t> &worldIndices,
            const std::vector<uint32_t> &acceptedWaterIndices,
            const std::vector<Payload> &presentation = {}) {
            words.clear();
            validNodes = weldDuplicates = triangles = 0;
            error = "";
            const auto reject = [&](const char *reason) {
                error = reason;
                return false;
            };
            const uint64_t headerWords = uint64_t(vertexCount) * 2;
            constexpr uint64_t MaxWords = uint64_t(UINT32_MAX) / sizeof(uint32_t);
            if (headerWords > MaxWords) return reject("header-overflow");
            if (posFloats.size() != uint64_t(vertexCount) * 3 || worldIndices.size() != vertexCount)
                return reject("vertex-array-size");
            if (!presentation.empty() && presentation.size() != vertexCount)
                return reject("presentation-array-size");
            if (acceptedWaterIndices.size() % 3 != 0) return reject("incomplete-triangle");

            // Ascending source IDs make representatives independent of draw
            // traversal order. Group only accepted water: scenery at matching
            // coordinates must never contribute a normal.
            std::vector<uint32_t> referenced = acceptedWaterIndices;
            for (uint32_t vertex : referenced) {
                if (vertex >= vertexCount) return reject("vertex-index-out-of-range");
            }
            std::sort(referenced.begin(), referenced.end());
            referenced.erase(std::unique(referenced.begin(), referenced.end()), referenced.end());

            using Key = std::array<uint32_t, 14>;
            using Face = std::array<uint32_t, 3>;
            std::map<Key, uint32_t> groupByKey;
            std::vector<uint32_t> groupByVertex(vertexCount, UINT32_MAX);
            std::vector<uint32_t> representatives;
            for (uint32_t vertex : referenced) {
                Key key = {worldIndices[vertex], 0, 0, 0};
                for (uint32_t component = 0; component < 3; ++component) {
                    float coordinate = posFloats[size_t(vertex) * 3 + component];
                    if (!std::isfinite(coordinate)) return reject("nonfinite-water-position");
                    // IEEE signed zero is the same spatial position.
                    if (coordinate == 0.0f) coordinate = 0.0f;
                    std::memcpy(&key[component + 1], &coordinate, sizeof(coordinate));
                }
                if (!presentation.empty())
                    std::copy(presentation[vertex].begin(), presentation[vertex].end(), key.begin() + 4);
                const auto inserted = groupByKey.emplace(key, uint32_t(representatives.size()));
                if (inserted.second) representatives.push_back(vertex);
                groupByVertex[vertex] = inserted.first->second;
            }

            std::set<Face> uniqueFaces;
            std::vector<std::vector<Face>> incident(representatives.size());
            uint64_t incidentWords = 0;
            for (size_t index = 0; index < acceptedWaterIndices.size(); index += 3) {
                const uint32_t a = groupByVertex[acceptedWaterIndices[index]];
                const uint32_t b = groupByVertex[acceptedWaterIndices[index + 1]];
                const uint32_t c = groupByVertex[acceptedWaterIndices[index + 2]];
                if (a == b || a == c || b == c) continue;
                Face canonical = {representatives[a], representatives[b], representatives[c]};
                std::sort(canonical.begin(), canonical.end());
                // Repeated draw ranges or reverse-wound copies are one face.
                // Winding is immaterial: the GPU orients area vectors upward.
                if (!uniqueFaces.insert(canonical).second) continue;
                if (incident[a].size() >= 64 || incident[b].size() >= 64 || incident[c].size() >= 64)
                    return reject("water-valence-exceeds-64");
                if (headerWords + incidentWords + 9 > MaxWords) return reject("adjacency-byte-offset-overflow");
                incident[a].push_back(canonical);
                incident[b].push_back(canonical);
                incident[c].push_back(canonical);
                incidentWords += 9;
            }

            std::vector<uint32_t> packed(size_t(headerWords), 0);
            packed.reserve(size_t(headerWords + incidentWords));
            std::vector<uint32_t> offsets(representatives.size(), 0);
            uint32_t populated = 0;
            for (size_t group = 0; group < incident.size(); ++group) {
                if (incident[group].empty()) continue;
                offsets[group] = uint32_t(packed.size() * sizeof(uint32_t));
                ++populated;
                for (const Face &face : incident[group]) packed.insert(packed.end(), face.begin(), face.end());
            }
            for (uint32_t vertex : referenced) {
                const uint32_t group = groupByVertex[vertex];
                packed[size_t(vertex) * 2] = offsets[group];
                packed[size_t(vertex) * 2 + 1] = uint32_t(incident[group].size());
            }
            words.swap(packed);
            validNodes = populated;
            weldDuplicates = uint32_t(referenced.size() - representatives.size());
            triangles = uint32_t(uniqueFaces.size());
            return true;
        }
    };
}
