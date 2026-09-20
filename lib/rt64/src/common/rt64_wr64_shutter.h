#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>

namespace RT64 {
    // USA's four original cover + leading-edge pairs. Segment 1 is the
    // resident copy starting at ROM 0xF6090; each half contains 18 vertices.
    // No asset, model transform, or native animation value is modified.
    inline bool wr64UsaShutterVertex(uint32_t address) {
        constexpr uint32_t bases[] = {0x0105A7A8U, 0x0105B3D8U, 0x0105C008U, 0x0105CC38U};
        for (uint32_t base : bases) {
            if (address >= base && address < base + 0x240U && (address - base) % 16U == 0) return true;
        }
        return false;
    }

    template<class DrawData, class GameCall>
    inline bool wr64UsaShutterCall(const DrawData& data, const GameCall& call) {
        const uint64_t start = call.meshDesc.faceIndicesStart;
        const uint64_t count = uint64_t(call.callDesc.triangleCount) * 3U;
        if (count == 0 || start + count > data.faceIndices.size()) return false;
        for (uint64_t i = start; i < start + count; ++i) {
            const uint32_t vertex = data.faceIndices[size_t(i)];
            if (vertex >= data.vertexSegmentedAddresses.size() || vertex >= data.worldIndices.size() ||
                !wr64UsaShutterVertex(data.vertexSegmentedAddresses[vertex])) return false;
            const uint32_t world = data.worldIndices[vertex];
            if (world >= data.worldTransformSegmentedAddresses.size() ||
                data.worldTransformSegmentedAddresses[world] != 0x07001340U) return false;
        }
        return true;
    }

    struct Wr64UsaShutterMapping { float scale, offset; };

    inline Wr64UsaShutterMapping wr64UsaShutterMapping(float scale, float offset,
        float halfPixel, float expansion) {
        if (!(expansion > 1.0f) || !std::isfinite(expansion)) return {scale, offset};
        // Native USA replay proves the shutter is a screen transition: its
        // x/424 trajectory must remain x/outputWidth. The world-camera FOV
        // correction currently contracts that trajectory. Undo that contraction
        // for these indexed draws only, retaining the raster half-pixel origin.
        return {scale * expansion, halfPixel + (offset - halfPixel) * expansion};
    }
}
