// CPU-only topology validation; never launches the game or creates a window.
#include "../../lib/rt64/src/common/rt64_wr64_water_adjacency.h"

#include <cstdio>
#include <cstdlib>
#include <string>

namespace {
    size_t checks = 0;
    void require(bool condition, const char *message) {
        ++checks;
        if (!condition) {
            std::fprintf(stderr, "FAIL: %s\n", message);
            std::exit(1);
        }
    }
    void expectRejected(RT64::Wr64WaterAdjacency &adjacency, uint32_t count,
        const std::vector<float> &positions, const std::vector<uint16_t> &worlds,
        const std::vector<uint32_t> &indices, const char *reason) {
        require(!adjacency.build(count, positions, worlds, indices), "Invalid topology was accepted");
        require(std::string(adjacency.error) == reason, "Unexpected rejection reason");
        require(adjacency.words.empty() && adjacency.validNodes == 0 &&
            adjacency.weldDuplicates == 0 && adjacency.triangles == 0,
            "Failed build retained stale topology or stats");
    }
}

int main() {
    // Two draws meeting on duplicate IDs: 0/3 and 2/4 are the same nodes.
    // Vertex 6 is unrelated geometry and must have an empty header.
    std::vector<float> positions = {0, 0, 0, 1, 0, 0, 0, 0, 1,
        -0.0f, 0, 0, 0, -0.0f, 1, -1, 0.5f, 0, 0, 0, 0};
    std::vector<uint16_t> worlds(7, 2);
    const std::vector<uint32_t> accepted = {0, 1, 2, 3, 4, 5};
    const auto positionsBefore = positions;
    RT64::Wr64WaterAdjacency adjacency;
    require(adjacency.build(7, positions, worlds, accepted), "Valid split-draw topology failed");
    require(adjacency.validNodes == 4 && adjacency.weldDuplicates == 2 && adjacency.triangles == 2,
        "Weld or face statistics are wrong");
    require(adjacency.words[1] == 2 && adjacency.words[5] == 2 && adjacency.words[3] == 1 &&
        adjacency.words[11] == 1, "Shared and outer node valences are wrong");
    require(adjacency.words[0] == adjacency.words[6] && adjacency.words[4] == adjacency.words[8],
        "Duplicate seam vertices did not share an incident list");
    require(adjacency.words[12] == 0 && adjacency.words[13] == 0,
        "Unreferenced matching-position geometry entered the topology");
    require(adjacency.words.size() == 14 + 18, "Packed header/list size is wrong");
    require(positions == positionsBefore && worlds == std::vector<uint16_t>(7, 2),
        "Topology construction modified water inputs");
    for (uint32_t vertex = 0; vertex < 7; ++vertex) {
        const uint32_t offset = adjacency.words[vertex * 2];
        const uint32_t count = adjacency.words[vertex * 2 + 1];
        require(offset % 4 == 0 && uint64_t(offset / 4) + count * 3 <= adjacency.words.size(),
            "A packed incident list is outside the buffer");
    }
    const auto baseline = adjacency.words;
    std::vector<RT64::Wr64WaterAdjacency::Payload> presentation(7);
    for (auto &payload : presentation) payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    require(adjacency.build(7, positions, worlds, accepted, presentation) && adjacency.words == baseline,
        "Matching presentation payload prevented a legitimate seam weld");
    for (uint32_t component : {0U, 3U, 4U, 5U, 7U, 8U, 9U}) {
        ++presentation[3][component];
        require(adjacency.build(7, positions, worlds, accepted, presentation) &&
            adjacency.validNodes == 5 && adjacency.weldDuplicates == 1 && adjacency.words[1] == 1,
            "Divergent velocity/field/coverage identity was welded at an equal endpoint");
        --presentation[3][component];
    }
    presentation.pop_back();
    require(!adjacency.build(7, positions, worlds, accepted, presentation) &&
        std::string(adjacency.error) == "presentation-array-size" && adjacency.words.empty() &&
        adjacency.validNodes == 0 && adjacency.weldDuplicates == 0 && adjacency.triangles == 0,
        "Invalid presentation payload array did not clear topology and stats");
    std::vector<uint32_t> repeated = accepted;
    repeated.insert(repeated.end(), {2, 1, 3, 5, 4, 0, 0, 0, 1});
    require(adjacency.build(7, positions, worlds, repeated) && adjacency.words == baseline,
        "Duplicate/reversed draws or collapsed triangles changed weights");
    require(adjacency.triangles == 2, "Deduplication face count is wrong");

    worlds[3] = worlds[4] = worlds[5] = 3;
    require(adjacency.build(7, positions, worlds, accepted), "Separate transform domains failed");
    require(adjacency.validNodes == 6 && adjacency.weldDuplicates == 0 && adjacency.words[1] == 1,
        "Vertices from different transform domains were welded");
    worlds.assign(7, 2);
    positions[9] = 1e-6f;
    require(adjacency.build(7, positions, worlds, accepted) && adjacency.validNodes == 5,
        "Nearby unequal positions were incorrectly welded");
    positions = positionsBefore;

    require(adjacency.build(7, positions, worlds, {}), "Empty accepted-water topology failed");
    require(adjacency.words == std::vector<uint32_t>(14, 0) && adjacency.validNodes == 0,
        "Empty topology did not clear all headers");
    require(adjacency.build(7, positions, worlds, {0, 3, 6}) && adjacency.triangles == 0,
        "Collapsed face should be a graceful zero-normal fallback");
    require(adjacency.build(3, {0, 0, 0, 1, 0, 0, 2, 0, 0}, {0, 0, 0}, {0, 1, 2}) &&
        adjacency.triangles == 1, "Collinear current endpoint must remain evaluable on the GPU");

    expectRejected(adjacency, 7, positions, worlds, {0, 1}, "incomplete-triangle");
    expectRejected(adjacency, 7, positions, worlds, {0, 1, 7}, "vertex-index-out-of-range");
    expectRejected(adjacency, 8, positions, worlds, accepted, "vertex-array-size");
    auto invalidPositions = positions;
    invalidPositions[0] = std::numeric_limits<float>::quiet_NaN();
    expectRejected(adjacency, 7, invalidPositions, worlds, accepted, "nonfinite-water-position");
    invalidPositions[0] = std::numeric_limits<float>::infinity();
    expectRejected(adjacency, 7, invalidPositions, worlds, accepted, "nonfinite-water-position");
    expectRejected(adjacency, UINT32_MAX, {}, {}, {}, "header-overflow");

    std::vector<float> fanPositions = {0, 0, 0};
    std::vector<uint32_t> fanIndices;
    for (uint32_t i = 0; i < 66; ++i) {
        fanPositions.insert(fanPositions.end(), {float(i + 1), 0, 1});
        if (i < 65) fanIndices.insert(fanIndices.end(), {0, i + 1, i + 2});
    }
    std::vector<uint16_t> fanWorlds(67, 0);
    auto boundedFan = fanIndices;
    boundedFan.resize(64 * 3);
    require(adjacency.build(67, fanPositions, fanWorlds, boundedFan) && adjacency.words[1] == 64,
        "The maximum supported valence should succeed");
    expectRejected(adjacency, 67, fanPositions, fanWorlds, fanIndices, "water-valence-exceeds-64");
    require(adjacency.build(7, positions, worlds, accepted) && adjacency.words == baseline,
        "Valid rebuild after failure did not restore clean topology");
    std::printf("PASS: %zu CPU water adjacency checks.\n", checks);
}
