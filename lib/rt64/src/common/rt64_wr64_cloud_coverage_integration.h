#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

#include "rt64_math.h"
#include "rt64_wr64_cloud_coverage.h"
#include "rt64_wr64_cloud_coverage_settings.h"
#include "rt64_wr64_rt_sky.h"
#include "hle/rt64_workload.h"

namespace RT64 {
    inline bool wr64CloudCoverageIdentity(const interop::float4x4 &matrix) {
        for (uint32_t r = 0; r < 4; ++r) for (uint32_t c = 0; c < 4; ++c) {
            const float value = matrix[r][c];
            if (!std::isfinite(value) || std::abs(value - (r == c ? 1.0f : 0.0f)) > 1.0e-5f)
                return false;
        }
        return true;
    }

    // Authenticate the decoded native packet family, including its own seven
    // source slots and exact closed fan. No screen-region or texture-hash guess
    // admits a second sky family or creates an absent native draw.
    inline bool wr64CloudCoverageSources(const DrawData &draw, const GameCall &call,
        uint32_t view, std::array<uint32_t, 7> &sources) {
        const auto &desc = call.callDesc;
        if (!wr64RTSkySignature(desc.triangleCount, desc.colorCombiner.L,
                desc.colorCombiner.H, desc.otherMode.L, desc.otherMode.H) ||
            desc.extendedType != DrawExtendedType::None || !desc.textureOn || desc.tileCount != 1 ||
            view >= draw.viewTransforms.size() || view >= draw.rspViewports.size() ||
            desc.tileIndex >= draw.callTiles.size() || desc.tileIndex >= draw.rdpTiles.size()) return false;
        const auto &tile = draw.callTiles[desc.tileIndex];
        const auto &rdp = draw.rdpTiles[desc.tileIndex];
        // State::flush decodes the native mask bits (6, 5) into the sampling
        // periods (64, 32) stored in interop::RDPTile. Comparing against raw
        // bits here rejects every real cloud packet before it can be extended.
        if (!tile.valid || tile.tileCopyUsed || tile.sampleWidth != 64 || tile.sampleHeight != 32 ||
            rdp.fmt != 3 || rdp.siz != 2 || rdp.cms != G_TX_WRAP || rdp.cmt != G_TX_WRAP ||
            rdp.masks != 64 || rdp.maskt != 32) return false;
        const uint32_t count = draw.vertexCount();
        if (draw.posFloats.size() != size_t(count) * 3 || draw.velFloats.size() != size_t(count) * 3 ||
            draw.tcFloats.size() != size_t(count) * 2 || draw.tcVelFloats.size() != size_t(count) * 2 ||
            draw.normColBytes.size() != size_t(count) * 4 || draw.viewProjIndices.size() != count ||
            draw.fogIndices.size() != count || draw.lightIndices.size() != count ||
            draw.lightCounts.size() != count || draw.lookAtIndices.size() != count ||
            draw.vertexSegmentedAddresses.size() != count || draw.wr64WaterProducerKeys.size() != count)
            return false;
        const uint64_t first = call.meshDesc.faceIndicesStart;
        if (first + 18 > draw.faceIndices.size()) return false;
        sources.fill(UINT32_MAX);
        uint32_t sourceBase = 0;
        for (uint32_t i = 0; i < 18; ++i) {
            const uint32_t vertex = draw.faceIndices[size_t(first) + i];
            if (vertex >= count || (draw.wr64CloudNativeVertexCount != UINT32_MAX &&
                vertex >= draw.wr64CloudNativeVertexCount)) return false;
            const uint32_t address = draw.vertexSegmentedAddresses[vertex];
            const uint32_t base = address >= 0x060001C0U && address <= 0x06000220U
                ? 0x060001C0U : address >= 0x06000230U && address <= 0x06000290U ? 0x06000230U : 0;
            if (!base || (address & 15U) || (sourceBase && sourceBase != base)) return false;
            sourceBase = base;
            const uint32_t slot = (address - base) / 16U;
            if (sources[slot] != UINT32_MAX && sources[slot] != vertex) return false;
            sources[slot] = vertex;
        }
        for (uint32_t source : sources) if (source == UINT32_MAX) return false;
        for (uint32_t face = 0; face < 6; ++face) {
            if (draw.faceIndices[size_t(first) + face * 3] != sources[0] ||
                draw.faceIndices[size_t(first) + face * 3 + 1] != sources[face + 1] ||
                draw.faceIndices[size_t(first) + face * 3 + 2] != sources[(face + 1) % 6 + 1]) return false;
        }
        for (uint32_t source : sources) {
            if (draw.viewProjIndices[source] != view || draw.worldIndices[source] >= draw.worldTransforms.size() ||
                !wr64CloudCoverageIdentity(draw.worldTransforms[draw.worldIndices[source]]) ||
                draw.fogIndices[source] || draw.lightCounts[source] || draw.lookAtIndices[source]) return false;
            for (uint32_t component = 0; component < 3; ++component)
                if (draw.normColBytes[source * 4 + component] != draw.normColBytes[sources[0] * 4 + component])
                    return false;
            for (size_t m = 0; m + 1 < draw.modifyPosUints.size(); m += 2)
                if ((draw.modifyPosUints[m] >> 1) == source) return false;
        }
        return true;
    }

    inline bool wr64AppendCloudCoverage(DrawData &draw, GameCall &call,
        uint32_t view, float slope, float intercept, bool enabledForWorkload) {
        if (!enabledForWorkload || call.wr64CloudCoverage.vertexStart != UINT32_MAX) return false;
        std::array<uint32_t, 7> sources{};
        if (!wr64CloudCoverageSources(draw, call, view, sources)) return false;
        Wr64CloudCoverageInput input;
        input.slope = slope;
        input.intercept = intercept;
        const hlslpp::float4x4 inverseView = hlslpp::inverse(draw.viewTransforms[view]);
        const hlslpp::float3 camera = inverseView[3].xyz;
        input.camera = { float(camera.x), float(camera.y), float(camera.z) };
        for (uint32_t slot = 0; slot < 7; ++slot) {
            const uint32_t source = sources[slot];
            for (uint32_t c = 0; c < 3; ++c) input.vertices[slot].position[c] = draw.posFloats[source * 3 + c];
            for (uint32_t c = 0; c < 2; ++c) input.vertices[slot].uv[c] = draw.tcFloats[source * 2 + c];
            input.vertices[slot].alpha = draw.normColBytes[source * 4 + 3];
        }
        const Wr64CloudCoverageMesh mesh = wr64BuildCloudCoverage(input);
        if (!mesh.valid || mesh.vertices.size() != 96 || mesh.indices.size() != 576 ||
            uint64_t(draw.vertexCount()) + mesh.vertices.size() > UINT32_MAX ||
            uint64_t(draw.faceIndices.size()) + 18 + mesh.indices.size() > UINT32_MAX) return false;
        for (uint32_t index : mesh.indices) if (index >= 7 + mesh.vertices.size()) return false;
        const uint32_t oldCount = draw.vertexCount();
        if ((!draw.wr64WaterVertexMask.empty() && draw.wr64WaterVertexMask.size() != oldCount) ||
            (!draw.wr64WaterFieldInfo.empty() && draw.wr64WaterFieldInfo.size() != size_t(oldCount) * 4) ||
            (!draw.wr64WaterFieldPrevPosShiftX.empty() && draw.wr64WaterFieldPrevPosShiftX.size() != oldCount) ||
            (!draw.wr64WaterFieldPrevTcShiftZ.empty() && draw.wr64WaterFieldPrevTcShiftZ.size() != oldCount)) return false;
        std::vector<uint32_t> combined(draw.faceIndices.begin() + call.meshDesc.faceIndicesStart,
            draw.faceIndices.begin() + call.meshDesc.faceIndicesStart + 18);
        for (uint32_t index : mesh.indices)
            combined.push_back(index < 7 ? sources[index] : oldCount + index - 7);

        // Commit before the native uploader takes pointers into these vectors.
        // Every original vertex, index and call range remains untouched.
        if (draw.wr64CloudNativeVertexCount == UINT32_MAX) draw.wr64CloudNativeVertexCount = oldCount;
        auto &coverage = call.wr64CloudCoverage;
        coverage.vertexStart = oldCount;
        coverage.sources = sources;
        coverage.faceIndicesStart = uint32_t(draw.faceIndices.size());
        coverage.faceCount = uint32_t(combined.size() / 3);
        coverage.weights.reserve(mesh.vertices.size());
        for (const auto &vertex : mesh.vertices) {
            draw.posFloats.insert(draw.posFloats.end(), vertex.position.begin(), vertex.position.end());
            draw.velFloats.insert(draw.velFloats.end(), 3, 0.0f);
            draw.tcFloats.insert(draw.tcFloats.end(), vertex.uv.begin(), vertex.uv.end());
            draw.tcVelFloats.insert(draw.tcVelFloats.end(), 2, 0.0f);
            for (uint32_t c = 0; c < 3; ++c) draw.normColBytes.push_back(draw.normColBytes[sources[0] * 4 + c]);
            draw.normColBytes.push_back(vertex.alpha);
            draw.viewProjIndices.push_back(uint16_t(view));
            draw.worldIndices.push_back(draw.worldIndices[sources[0]]);
            draw.fogIndices.push_back(0);
            draw.lightIndices.push_back(0);
            draw.lightCounts.push_back(0);
            draw.lookAtIndices.push_back(0);
            // Synthetic vertices never impersonate a native producer slot.
            draw.vertexSegmentedAddresses.push_back(0);
            draw.wr64WaterProducerKeys.push_back(0);
            if (!draw.wr64WaterVertexMask.empty()) draw.wr64WaterVertexMask.push_back(0);
            if (!draw.wr64WaterFieldInfo.empty()) draw.wr64WaterFieldInfo.insert(draw.wr64WaterFieldInfo.end(), 4, 0);
            if (!draw.wr64WaterFieldPrevPosShiftX.empty()) draw.wr64WaterFieldPrevPosShiftX.emplace_back(0.0f);
            if (!draw.wr64WaterFieldPrevTcShiftZ.empty()) draw.wr64WaterFieldPrevTcShiftZ.emplace_back(0.0f);
            coverage.weights.push_back(vertex.weights);
        }
        draw.faceIndices.insert(draw.faceIndices.end(), combined.begin(), combined.end());
        return true;
    }

    inline bool wr64CloudCoveragePresentationValid(const DrawData &draw, const GameCall &call,
        uint32_t view) {
        const auto &coverage = call.wr64CloudCoverage;
        if (coverage.faceCount != 198 || coverage.weights.size() != 96 ||
            uint64_t(coverage.vertexStart) + 96 > draw.vertexCount() ||
            uint64_t(coverage.faceIndicesStart) + 594 > draw.faceIndices.size()) return false;
        std::array<uint32_t, 7> sources{};
        if (!wr64CloudCoverageSources(draw, call, view, sources) || sources != coverage.sources) return false;
        for (uint32_t source : sources) {
            const uint32_t world = draw.worldIndices[source];
            if (world < draw.lerpWorldTransforms.size() &&
                !wr64CloudCoverageIdentity(draw.lerpWorldTransforms[world])) return false;
        }
        for (uint32_t i = 0; i < 18; ++i)
            if (draw.faceIndices[coverage.faceIndicesStart + i] != draw.faceIndices[call.meshDesc.faceIndicesStart + i])
                return false;
        return true;
    }

    inline bool wr64CloudCoverageEndingDepth(DrawData &draw, GameCall &call,
        uint32_t view, bool endingScope) {
        // The award camera has a 4096-unit far plane. Its clouds retain
        // opacity out to 8182 units, so extending their geometry alone still
        // leaves a straight depth-clip edge (including above the podium).
        // This authenticated backdrop never reads or writes scene depth.
        // Give only this cloud call's raster shader a finite interior depth while
        // retaining native projected XY/W, perspective UVs and opacity.
        const uint32_t index = call.callDesc.callIndex;
        if (!endingScope || !wr64CloudCoveragePresentationValid(draw, call, view) ||
            call.callDesc.otherMode.zCmp() || call.callDesc.otherMode.zUpd() ||
            call.callDesc.otherMode.zSource() != G_ZS_PIXEL ||
            index >= draw.rdpParams.size() || index >= draw.renderParams.size() ||
            call.shaderDesc.otherMode.L != call.callDesc.otherMode.L ||
            call.shaderDesc.otherMode.H != call.callDesc.otherMode.H ||
            draw.renderParams[index].omL != call.shaderDesc.otherMode.L ||
            draw.renderParams[index].omH != call.shaderDesc.otherMode.H) return false;
        call.shaderDesc.otherMode.L |= G_ZS_PRIM;
        draw.renderParams[index].omL = call.shaderDesc.otherMode.L;
        draw.rdpParams[index].primDepth = { 0.5f, 0.0f };
        return true;
    }

    // Run after all native sky velocity writers, including UV-rebase repair.
    // Applying the geometry's same fixed weights makes every fractional output
    // follow the existing native presentation chart without matching new slots.
    inline bool wr64FinalizeCloudCoverageCall(DrawData &draw, GameCall &call, uint32_t view) {
        auto &coverage = call.wr64CloudCoverage;
        if (!coverage.faceCount) return false;
        if (!wr64CloudCoveragePresentationValid(draw, call, view)) {
            coverage.faceCount = 0;
            return false;
        }
        for (uint32_t i = 0; i < coverage.weights.size(); ++i) {
            const uint32_t vertex = coverage.vertexStart + i;
            for (uint32_t component = 0; component < 3; ++component) {
                float velocity = 0.0f;
                for (uint32_t s = 0; s < 7; ++s)
                    velocity += coverage.weights[i][s] * draw.velFloats[coverage.sources[s] * 3 + component];
                draw.velFloats[vertex * 3 + component] = velocity;
                if (!std::isfinite(velocity)) coverage.faceCount = 0;
            }
            for (uint32_t component = 0; component < 2; ++component) {
                float velocity = 0.0f;
                for (uint32_t s = 0; s < 7; ++s)
                    velocity += coverage.weights[i][s] * draw.tcVelFloats[coverage.sources[s] * 2 + component];
                draw.tcVelFloats[vertex * 2 + component] = velocity;
                if (!std::isfinite(velocity)) coverage.faceCount = 0;
            }
        }
        return true;
    }

    inline bool wr64FinalizeCloudCoverage(Workload &workload) {
        DrawData &draw = workload.drawData;
        if (draw.wr64CloudNativeVertexCount == UINT32_MAX) return false;
        bool changed = false;
        for (uint32_t f = 0; f < workload.fbPairCount; ++f) {
            auto &pair = workload.fbPairs[f];
            for (uint32_t p = 0; p < pair.projectionCount; ++p) {
                auto &projection = pair.projections[p];
                for (uint32_t c = 0; c < projection.gameCallCount; ++c) {
                    changed |= wr64FinalizeCloudCoverageCall(draw, projection.gameCalls[c], projection.transformsIndex);
                }
            }
        }
        return changed;
    }
}
