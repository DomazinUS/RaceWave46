#pragma once

#include <cstdint>
#include <cstring>
#include <map>
#include <vector>
#include "rt64_common.h"

namespace RT64 {
    // Current-workload aliases only. Native animal matrix slots are recycled,
    // so addresses must never become temporal identities.
    struct Wr64AnimalReplayUse {
        uint32_t framebuffer = 0;
        FixedRect viewport;
        bool ambiguous = false;
        std::vector<uint64_t> signature;
    };
    using Wr64AnimalReplayUses = std::map<uint32_t, Wr64AnimalReplayUse>;

    template<typename Call>
    static void wr64AnimalReplayRecord(Wr64AnimalReplayUses &uses, uint32_t transform,
        uint32_t framebuffer, const FixedRect &viewport, const Call &call, uint64_t texture)
    {
        auto inserted = uses.emplace(transform, Wr64AnimalReplayUse{});
        auto &use = inserted.first->second;
        if (inserted.second) {
            use.framebuffer = framebuffer;
            use.viewport = viewport;
        }
        else if ((use.framebuffer != framebuffer) || (use.viewport.ulx != viewport.ulx) ||
            (use.viewport.uly != viewport.uly) || (use.viewport.lrx != viewport.lrx) ||
            (use.viewport.lry != viewport.lry))
        {
            use.ambiguous = true;
        }
        use.signature.insert(use.signature.end(), { texture, call.triangleCount,
            call.colorCombiner.H, call.colorCombiner.L, call.otherMode.H, call.otherMode.L });
    }

    template<typename T>
    static bool wr64AnimalReplayRangeEqual(const std::vector<T> &data,
        uint64_t a, uint64_t b, uint64_t count)
    {
        return (a <= data.size()) && (b <= data.size()) &&
            (count <= data.size() - a) && (count <= data.size() - b) &&
            (std::memcmp(data.data() + a, data.data() + b, size_t(count) * sizeof(T)) == 0);
    }

    template<typename Data>
    static bool wr64AnimalReplayGeometryEqual(const Data &data, uint32_t a, uint32_t b) {
        if ((a >= data.worldTransforms.size()) || (b >= data.worldTransforms.size()) ||
            (a >= data.worldTransformSegmentedAddresses.size()) ||
            (b >= data.worldTransformSegmentedAddresses.size()) ||
            (a >= data.worldTransformPhysicalAddresses.size()) ||
            (b >= data.worldTransformPhysicalAddresses.size()) ||
            (a >= data.worldTransformVertexIndices.size()) ||
            (b >= data.worldTransformVertexIndices.size())) return false;
        if ((data.worldTransformSegmentedAddresses[a] == 0) ||
            (data.worldTransformPhysicalAddresses[a] == 0) ||
            (data.worldTransformSegmentedAddresses[a] != data.worldTransformSegmentedAddresses[b]) ||
            (data.worldTransformPhysicalAddresses[a] != data.worldTransformPhysicalAddresses[b]) ||
            !wr64AnimalReplayRangeEqual(data.worldTransforms, a, b, 1)) return false;

        const uint32_t count = data.worldTransformVertexCount(a);
        if ((count == 0) || (count != data.worldTransformVertexCount(b))) return false;
        const uint64_t va = data.worldTransformVertexIndices[a];
        const uint64_t vb = data.worldTransformVertexIndices[b];
        // Equal decoded positions under equal world matrices prove equal current
        // world-space vertices. Clip-space positions intentionally differ by view.
        return wr64AnimalReplayRangeEqual(data.posFloats, va * 3, vb * 3, uint64_t(count) * 3) &&
            wr64AnimalReplayRangeEqual(data.tcFloats, va * 2, vb * 2, uint64_t(count) * 2) &&
            wr64AnimalReplayRangeEqual(data.normColBytes, va * 4, vb * 4, uint64_t(count) * 4) &&
            wr64AnimalReplayRangeEqual(data.vertexSegmentedAddresses, va, vb, count);
    }

    template<typename Data>
    static std::map<uint32_t, uint32_t> wr64AnimalReplayAliases(
        const Data &data, const Wr64AnimalReplayUses &uses)
    {
        std::map<uint32_t, uint32_t> aliases;
        std::map<uint32_t, std::vector<uint32_t>> representatives;
        for (const auto &entry : uses) {
            const uint32_t transform = entry.first;
            const auto &use = entry.second;
            const auto &rect = use.viewport;
            if (use.ambiguous || (rect.ulx >= rect.lrx) || (rect.uly >= rect.lry) ||
                (transform >= data.worldTransformPhysicalAddresses.size())) continue;
            auto &candidates = representatives[data.worldTransformPhysicalAddresses[transform]];
            for (const uint32_t candidate : candidates) {
                const auto &other = uses.at(candidate);
                const auto &r = other.viewport;
                const bool disjoint = (rect.lrx <= r.ulx) || (r.lrx <= rect.ulx) ||
                    (rect.lry <= r.uly) || (r.lry <= rect.uly);
                if ((use.framebuffer == other.framebuffer) && disjoint &&
                    (use.signature == other.signature) &&
                    wr64AnimalReplayGeometryEqual(data, candidate, transform))
                {
                    aliases.emplace(transform, candidate);
                    break;
                }
            }
            if (aliases.find(transform) == aliases.end()) candidates.push_back(transform);
        }
        return aliases;
    }

    template<typename Data, typename IsFamily>
    static void wr64AnimalReplayCopyGroups(Data &data,
        const std::map<uint32_t, uint32_t> &aliases, IsFamily isFamily)
    {
        for (const auto &alias : aliases) {
            if ((alias.first >= data.worldTransformGroups.size()) ||
                (alias.second >= data.worldTransformGroups.size())) continue;
            const uint32_t group = data.worldTransformGroups[alias.second];
            if ((group >= data.transformGroups.size()) ||
                !isFamily(data.transformGroups[group].matrixId)) continue;
            const auto copy = data.transformGroups[group];
            data.worldTransformGroups[alias.first] = uint32_t(data.transformGroups.size());
            data.transformGroups.push_back(copy);
        }
    }
}
