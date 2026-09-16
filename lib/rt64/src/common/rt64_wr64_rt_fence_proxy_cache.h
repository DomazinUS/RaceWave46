#pragma once

#include "rt64_wr64_rt_fence_proxy.h"
#include <cstring>
#include <utility>

namespace RT64 {
    // Eligibility is checked against the current draw BEFORE constructing this
    // key. The cache only replaces the pure cross-section expansion; source,
    // material, identity-transform and zero-velocity guards remain mandatory.
    struct Wr64RTFenceExpansionKey {
        std::array<uint32_t, 4> sources{};
        // Course, combiner L/H, other mode L/H, geometry mode. The caller also
        // revalidates the exact native tile format, dimensions and sampler.
        std::array<uint32_t, 6> material{};
        std::array<Wr64RTFenceVertex, 4> quad{};

        bool operator==(const Wr64RTFenceExpansionKey &other) const {
            // Preserve every float bit, including signed zero. No hash or
            // epsilon comparison can substitute another quad's geometry.
            return sources == other.sources && material == other.material &&
                std::memcmp(quad.data(), other.quad.data(), sizeof(quad)) == 0;
        }
    };

    class Wr64RTFenceExpansionCache {
    public:
        static constexpr size_t MaxEntries = 64;
        static constexpr size_t MaxVertexBytes = 4 * 1024 * 1024;
        static constexpr size_t MaxDrawVertices = 24576;
        struct Stats { uint64_t hits = 0, misses = 0, expansions = 0, evictions = 0; };

        bool append(const Wr64RTFenceExpansionKey &key, Wr64RTFenceProxy &output) {
            if (output.triangles.size() > MaxDrawVertices) return false;
            if (++clock_ == 0) {
                for (auto &entry : entries_) entry.used = 0;
                clock_ = 1;
            }
            for (auto &entry : entries_) {
                if (!entry.triangles.empty() && entry.key == key) {
                    ++stats_.hits;
                    entry.used = clock_;
                    return appendTriangles(entry.triangles, output);
                }
            }

            ++stats_.misses;
            Wr64RTFenceProxy generated;
            if (!wr64RTAppendFenceProxy(key.quad, generated)) return false;
            ++stats_.expansions;
            if (!appendTriangles(generated.triangles, output)) return false;
            const size_t bytes = generated.triangles.capacity() * sizeof(Wr64RTFenceVertex);
            if (bytes > MaxVertexBytes) return true;

            // Count allocated capacity, not just live vertices. Retention is
            // bounded even when a course/mod changes the admitted quad data.
            size_t slot = freeSlot();
            while (slot == MaxEntries || retainedBytes_ > MaxVertexBytes - bytes) {
                size_t oldest = MaxEntries;
                for (size_t i = 0; i < MaxEntries; ++i) {
                    if (!entries_[i].triangles.empty() &&
                        (oldest == MaxEntries || entries_[i].used < entries_[oldest].used)) oldest = i;
                }
                if (oldest == MaxEntries) return true;
                retainedBytes_ -= entries_[oldest].triangles.capacity() * sizeof(Wr64RTFenceVertex);
                std::vector<Wr64RTFenceVertex>().swap(entries_[oldest].triangles);
                ++stats_.evictions;
                slot = freeSlot();
            }
            entries_[slot].key = key;
            entries_[slot].triangles = std::move(generated.triangles);
            entries_[slot].used = clock_;
            retainedBytes_ += bytes;
            return true;
        }

        const Stats &stats() const { return stats_; }
        size_t retainedBytes() const { return retainedBytes_; }
        size_t entryCount() const {
            size_t count = 0;
            for (const auto &entry : entries_) count += !entry.triangles.empty();
            return count;
        }

    private:
        struct Entry {
            Wr64RTFenceExpansionKey key;
            std::vector<Wr64RTFenceVertex> triangles;
            uint64_t used = 0;
        };
        std::array<Entry, MaxEntries> entries_;
        size_t retainedBytes_ = 0;
        uint64_t clock_ = 0;
        Stats stats_;

        size_t freeSlot() const {
            for (size_t i = 0; i < MaxEntries; ++i) if (entries_[i].triangles.empty()) return i;
            return MaxEntries;
        }
        static bool appendTriangles(const std::vector<Wr64RTFenceVertex> &triangles, Wr64RTFenceProxy &output) {
            if (output.triangles.size() > MaxDrawVertices ||
                triangles.size() > MaxDrawVertices - output.triangles.size()) return false;
            output.triangles.insert(output.triangles.end(), triangles.begin(), triangles.end());
            return true;
        }
    };
}
