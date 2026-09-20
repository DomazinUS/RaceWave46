#pragma once

#include "hle/rt64_workload.h"
#include "render/rt64_wr64_layer_trace.h"

namespace RT64 {
    inline constexpr uint64_t Wr64WatercraftShadeSignature = 0x6FA7628759844120ULL;
    // Native USA21:9 census, Watercraft Select header:176x18 at(38,28),
    // hash342EB798B5720B9A. This is also the verified Shindou host identity.
    inline constexpr uint64_t Wr64WatercraftHeaderTexture = 0x342EB798B5720B9AULL;

    inline bool wr64WatercraftSelectFramebuffer(const Workload &workload, uint32_t pairIndex) {
        if (pairIndex >= workload.fbPairs.size()) return false;
        const auto &pair = workload.fbPairs[pairIndex];
        const auto projectionEnd = std::min<uint32_t>(pair.projectionCount, uint32_t(pair.projections.size()));
        for (uint32_t pr = 0; pr < projectionEnd; ++pr) {
            const auto &projection = pair.projections[pr];
            const auto callEnd = std::min<uint32_t>(projection.gameCallCount, uint32_t(projection.gameCalls.size()));
            for (uint32_t d = 0; d < callEnd; ++d) {
                const auto &call = projection.gameCalls[d];
                if (projection.type == Projection::Type::Rectangle && call.callDesc.tileCount == 1 &&
                    call.callDesc.tileIndex < workload.drawData.callTiles.size()) {
                    const auto &tile = workload.drawData.callTiles[call.callDesc.tileIndex];
                    if (tile.tmemHashOrID == Wr64WatercraftHeaderTexture &&
                        tile.sampleWidth == 176 && tile.sampleHeight == 18) return true;
                }
                if (projection.type != Projection::Type::Orthographic) continue;
                if (call.callDesc.triangleCount != 2) continue;
                if (WR64LayerTrace::composerCallIdentity(workload, pairIndex, pr, d,
                        projection, call) == Wr64WatercraftShadeSignature) return true;
            }
        }
        return false;
    }

    inline bool wr64WatercraftShadeProjection(const Workload &workload,
        uint32_t pairIndex, uint32_t projectionIndex)
    {
        const auto &projection = workload.fbPairs[pairIndex].projections[projectionIndex];
        // Called only after the complete framebuffer has identified Watercraft
        // Select. Its one-call untextured two-triangle ortho shade follows the
        // tiled backdrop, independently of the four perspective craft views.
        return projection.type == Projection::Type::Orthographic &&
            projection.gameCallCount == 1 && !projection.gameCalls.empty() &&
            projection.gameCalls.front().callDesc.triangleCount == 2 &&
            projection.gameCalls.front().callDesc.tileCount == 0;
    }
}
