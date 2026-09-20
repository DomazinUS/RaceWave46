#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <map>
#include <mutex>
#include <set>
#include <vector>
#include "rt64_wr64_far_water_distance.h"
#include "rt64_wr64_rt_two_player_assets.h"

namespace RT64 {
    inline constexpr uint32_t wr64WaveDistanceMode(uint32_t mode) { return mode <= 2U ? mode : 0U; }
    inline constexpr bool wr64WaveDistanceCourse(uint32_t course) { return course <= 8U; }
    inline std::atomic<uint32_t> wr64WaveDistanceSetting{0U};
    inline void setWr64WaveDistanceMode(uint32_t mode) {
        wr64WaveDistanceSetting.store(wr64WaveDistanceMode(mode), std::memory_order_relaxed);
    }
    inline uint32_t getWr64WaveDistanceMode() {
        return wr64WaveDistanceSetting.load(std::memory_order_relaxed);
    }

    // Extended+ carries the existing boundary height into the same generated
    // annulus. Its animated profile is independent of flat-water distance;
    // only the final, already-flat ring retains that separate setting.
    inline constexpr double wr64WaveRingScale(uint32_t mode, uint32_t farMode, uint32_t layer) {
        constexpr double scales[3] = {1.125, 1.5, 2.0};
        return mode == 2U && layer >= 1U && layer <= 3U
            ? scales[layer - 1U] : wr64FarWaterRingScale(farMode, layer);
    }
    inline double wr64WaveRingHeight(uint32_t mode, double scale, double datum, double boundary) {
        if (mode != 2U || scale >= 2.0) return datum;
        const double t = std::clamp(scale - 1.0, 0.0, 1.0);
        const double weight = 1.0 - t * t * (3.0 - 2.0 * t);
        return datum + weight * (boundary - datum);
    }

    // func_8004EAA4 advances the current native 10/12/16-ring local hexagon.
    // func_80050204 flattens its last ring when writing vertices. Recovery reads that
    // existing state; it never expands or writes the gameplay wave simulation.
    struct Wr64WaveDistanceNode {
        uint32_t key = 0;
        int16_t x = 0, z = 0, rawHeight = 0;
        int8_t q = 0, r = 0;
        bool boundary(uint32_t rings = 12) const {
            return std::max({std::abs(int(q)), std::abs(int(r)), std::abs(int(q) - int(r))}) == int(rings);
        }
    };
    struct Wr64WaveDistanceSnapshot {
        bool valid = false;
        bool producerSealed = false;
        uint32_t mode = 0, camera = 0, course = UINT32_MAX;
        uint32_t rings = 12, view = 0, players = 1, phase = 1, raceMode = 40, sea = 0;
        uint32_t sourceAddress = 0x03013D68U;
        int32_t centerX = 0, centerZ = 0, tide = 0;
        std::vector<Wr64WaveDistanceNode> nodes = std::vector<Wr64WaveDistanceNode>(469);
    };

    // Called at native water emission (or by offline native replay tests),
    // never from frame/GPU workers. The RSP consumes a task-sealed copy.
    // A second identical read rejects a changing producer table/state. Exact
    // decoded-interior equality below additionally ties it to this native draw.
    inline Wr64WaveDistanceSnapshot wr64CaptureWaveDistance(const uint8_t *ram,
        size_t size, uint32_t requestedMode, uint32_t view = 0) {
        if (!ram || size < 0x800000U) return {};
        // These older diagnostic paths move/sample the coverage in a different
        // coordinate frame. The bounded extension supports the release path.
        for (const char *name : {"WR64_WATER_CONTINUOUS_FIELD", "WR64_WATER_CONTINUOUS_COVERAGE", "WR64_WATER_CONTINUOUS_HEIGHT", "WR64_WATER_EXACT_PRESENT"}) {
            const char *value = std::getenv(name);
            if (value && value[0] != '\0' && value[0] != '0') return {};
        }
        const auto word = [&](uint32_t address) {
            uint32_t value; std::memcpy(&value, ram + (address & 0x7FFFFFU), 4); return value;
        };
        const auto half = [&](uint32_t address) {
            int16_t value; std::memcpy(&value, ram + ((address & 0x7FFFFFU) ^ 2U), 2); return value;
        };
        const auto byte = [&](uint32_t address) { return int8_t(ram[(address & 0x7FFFFFU) ^ 3U]); };
        const auto scoped = [&]() {
            if (view > 1) return false;
            const uint32_t camera = word(0x80223930U + view * 4U), players = word(0x800DAB28U);
            const uint32_t sea = word(0x801CE64CU), rings = sea == 1 ? 16U : (players == 2 || sea == 2 ? 10U : 12U);
            if (sea > 2 || word(0x80192494U) != rings || word(0x8019249CU) != 1 + 3 * rings * (rings + 1) || camera > 1U) return false;
            const uint32_t address = 0x80227C80U + camera * 0x10CU;
            return wr64FarWaterDistanceScope(word(0x800D8170U), players, word(0x801CE638U), word(0x800DAB24U),
                view, camera, word(address), word(address + 0xE8U),
                wr64RTTwoPlayerAssetsReady(ram, word(0x800D8170U)));
        };
        const auto capture = [&]() {
            Wr64WaveDistanceSnapshot out;
            if (!scoped()) return out;
            out.mode = wr64WaveDistanceMode(requestedMode);
            out.course = word(0x800D8170U);
            out.view = view; out.players = word(0x800DAB28U); out.phase = word(0x801CE638U);
            out.raceMode = word(0x800DAB24U); out.sea = word(0x801CE64CU); out.rings = word(0x80192494U);
            out.nodes.resize(word(0x8019249CU));
            out.sourceAddress = view ? 0x030170D8U : 0x03013D68U;
            out.camera = word(0x80223930U + view * 4U);
            out.centerX = int32_t(word(0x80192420U + view * 0x1CU)); out.centerZ = int32_t(word(0x80192424U + view * 0x1CU));
            out.tide = int32_t(word(0x80192458U));
            std::set<std::pair<int,int>> coordinates;
            std::set<uint32_t> keys;
            uint32_t boundary = 0, centerKey = UINT32_MAX;
            for (uint32_t i = 0; i < out.nodes.size(); ++i) {
                auto &node = out.nodes[i];
                node.q = byte(0x80160430U + i * 2U); node.r = byte(0x80160431U + i * 2U);
                if (std::max({std::abs(int(node.q)), std::abs(int(node.r)), std::abs(int(node.q)-int(node.r))}) > int(out.rings) ||
                    !coordinates.emplace(node.q, node.r).second) return Wr64WaveDistanceSnapshot{};
                node.key = word(0x80160A98U + i * 8U);
                if (node.key >= 0x30000U || (node.key & 3U) || !keys.insert(node.key).second) return Wr64WaveDistanceSnapshot{};
                node.x = half(0x80160A9CU + i * 8U); node.z = half(0x80160A9EU + i * 8U);
                node.rawHeight = half(0x80162420U + node.key);
                boundary += node.boundary(out.rings);
                if (!node.q && !node.r) centerKey = node.key;
            }
            if (boundary != 6U * out.rings || centerKey == UINT32_MAX) return Wr64WaveDistanceSnapshot{};
            const int column = int((centerKey / 4U) & 127U), row = int((centerKey / 4U) >> 7U);
            for (const auto &node : out.nodes) {
                const int x = column + node.q;
                const uint32_t key = uint32_t(((row + node.r + (x & -128) + 1536) % 384) * 128 + (x & 127)) * 4U;
                if (node.key != key) return Wr64WaveDistanceSnapshot{};
            }
            out.valid = scoped() && out.course == word(0x800D8170U);
            return out;
        };
        const auto first = capture();
        if (!first.valid) return {};
        const auto second = capture();
        if (!second.valid || first.rings != second.rings || first.players != second.players || first.phase != second.phase ||
            first.raceMode != second.raceMode || first.sea != second.sea || first.course != second.course || first.camera != second.camera || first.centerX != second.centerX ||
            first.centerZ != second.centerZ || first.tide != second.tide) return {};
        for (size_t i = 0; i < first.nodes.size(); ++i) {
            const auto &a = first.nodes[i], &b = second.nodes[i];
            if (a.key != b.key || a.q != b.q || a.r != b.r || a.x != b.x || a.z != b.z || a.rawHeight != b.rawHeight) return {};
        }
        return first;
    }

    // Native CPU publishes immediately after each water producer returns, while
    // its shared key table and simulation still belong to that view. The RSP
    // producer copies the matching graphics-pool packet; render workers never
    // read the global table, which P1 overwrites after P2 in ordinary split play.
    struct Wr64WaveDistancePacket {
        const uint8_t *ram = nullptr;
        uint32_t pool = 0;
        Wr64WaveDistanceSnapshot snapshot;
        std::vector<uint8_t> nativeVertices;
    };
    inline std::mutex wr64WavePacketMutex;
    inline std::vector<Wr64WaveDistancePacket> wr64WavePackets;
    inline std::map<uint64_t, std::vector<Wr64WaveDistancePacket>> wr64WaveTaskPackets;
    inline void wr64SealWaveDistanceTask(uint64_t sequence) {
        std::lock_guard<std::mutex> lock(wr64WavePacketMutex);
        auto &packets = wr64WaveTaskPackets[sequence];
        if (!wr64WavePackets.empty()) {
            const auto &last = wr64WavePackets.back();
            for (const auto &packet : wr64WavePackets)
                if (packet.pool == last.pool && packet.ram == last.ram) packets.push_back(packet);
        }
        while (wr64WaveTaskPackets.size() > 256) wr64WaveTaskPackets.erase(wr64WaveTaskPackets.begin());
    }
    inline std::vector<Wr64WaveDistancePacket> wr64ClaimWaveDistanceTask(uint64_t sequence) {
        std::lock_guard<std::mutex> lock(wr64WavePacketMutex);
        const auto found = wr64WaveTaskPackets.find(sequence);
        if (found == wr64WaveTaskPackets.end()) return {};
        auto out = std::move(found->second);
        wr64WaveTaskPackets.erase(wr64WaveTaskPackets.begin(), std::next(found));
        return out;
    }
    inline void wr64PublishWaveDistance(const uint8_t *ram, uint32_t view) {
        if (!ram || view > 1) return;
        uint32_t pool; std::memcpy(&pool, ram + 0x1518B8U, 4); pool &= 0x7FFFFFU;
        {
            std::lock_guard<std::mutex> lock(wr64WavePacketMutex);
            // A failed new producer must never retain the old pool's flattened
            // output as apparent evidence for a now-stale boundary snapshot.
            wr64WavePackets.erase(std::remove_if(wr64WavePackets.begin(), wr64WavePackets.end(), [&](const auto &p) {
                return p.ram == ram && p.pool == pool && p.snapshot.view == view;
            }), wr64WavePackets.end());
        }
        auto snapshot = wr64CaptureWaveDistance(ram, 0x800000U, getWr64WaveDistanceMode(), view);
        if (!snapshot.valid) return;
        const size_t address = pool + (snapshot.sourceAddress & 0xFFFFFFU), bytes = snapshot.nodes.size() * 16U;
        if (address + bytes > 0x800000U) return;
        Wr64WaveDistancePacket packet; packet.ram = ram; packet.pool = pool; packet.snapshot = std::move(snapshot);
        packet.nativeVertices.assign(ram + address, ram + address + bytes);
        std::lock_guard<std::mutex> lock(wr64WavePacketMutex);
        wr64WavePackets.erase(std::remove_if(wr64WavePackets.begin(), wr64WavePackets.end(), [&](const auto &p) {
            return p.ram == ram && p.pool == pool && p.snapshot.view == view;
        }), wr64WavePackets.end());
        if (wr64WavePackets.size() >= 16) wr64WavePackets.erase(wr64WavePackets.begin());
        wr64WavePackets.push_back(std::move(packet));
    }
    inline std::array<Wr64WaveDistanceSnapshot, 2> wr64ConsumeWaveDistance(const uint8_t *ram, size_t size, uint32_t pool,
        const std::vector<Wr64WaveDistancePacket> *taskPackets = nullptr) {
        std::array<Wr64WaveDistanceSnapshot, 2> out{};
        if (!ram || size < 0x800000U) return out;
        pool &= 0x7FFFFFU;
        const auto word = [&](uint32_t address) { uint32_t value; std::memcpy(&value, ram + (address & 0x7FFFFFU), 4); return value; };
        std::lock_guard<std::mutex> lock(wr64WavePacketMutex);
        for (const auto &p : taskPackets ? *taskPackets : wr64WavePackets) {
            const auto &s = p.snapshot;
            const size_t address = pool + (s.sourceAddress & 0xFFFFFFU);
            if (p.ram != ram || p.pool != pool || s.view > 1 || !s.valid ||
                s.course != word(0x800D8170U) || s.players != word(0x800DAB28U) || s.phase != word(0x801CE638U) ||
                s.raceMode != word(0x800DAB24U) || s.sea != word(0x801CE64CU) || s.rings != word(0x80192494U) ||
                s.camera != word(0x80223930U + s.view * 4U) || address + p.nativeVertices.size() > size ||
                std::memcmp(ram + address, p.nativeVertices.data(), p.nativeVertices.size()) != 0) continue;
            out[s.view] = s;
            out[s.view].producerSealed = true;
        }
        // Sea mode 1 deliberately renders the one freshly produced 16-ring
        // source through both cameras. Keep source identity but bind each view.
        if (out[0].valid && out[0].sea == 1 && out[0].players == 2) {
            const uint32_t camera = word(0x80223934U), address = 0x80227C80U + (camera <= 1 ? camera * 0x10CU : 0U);
            if (wr64FarWaterDistanceScope(out[0].course, 2, out[0].phase, out[0].raceMode, 1,
                    camera, word(address), word(address + 0xE8U), true)) {
                out[1] = out[0]; out[1].view = 1; out[1].camera = camera;
            }
        }
        return out;
    }

    struct Wr64WaveDistanceVertex {
        uint32_t vertex = 0, slot = 0, key = 0;
        float height = 0;
    };
    struct Wr64WaveDistanceSample {
        uint32_t vertex = 0, key = 0;
        float x = 0, height = 0, z = 0;
    };
    // A render-history cache, built once during the mapped boundary pass and
    // reused for the annulus. Positions are copied from the immutable previous
    // draw; these identities are compared only and are never dereferenced.
    struct Wr64WaveDistanceSurface {
        struct Triangle {
            double x[3], y[3], z[3];
            double minX, maxX, minZ, maxZ, inverseArea;
        };
        std::vector<Triangle> triangles;
        const float *positionIdentity = nullptr;
        const uint32_t *faceIdentity = nullptr;
        size_t positionCount = 0, faceCount = 0;
        template<typename Draw> bool matches(const Draw &draw) const {
            return !triangles.empty() && positionIdentity == draw.posFloats.data() &&
                faceIdentity == draw.wr64WaterFaceIndices.data() &&
                positionCount == draw.posFloats.size() && faceCount == draw.wr64WaterFaceIndices.size();
        }
        bool sample(double x, double z, double &height, double floatEndpointTolerance = 0.0) const {
            if (!std::isfinite(x) || !std::isfinite(z)) return false;
            constexpr double EdgeTolerance = 1.0e-7;
            for (const auto &t : triangles) {
                const double boundsTolerance = std::max(1.0e-5, floatEndpointTolerance);
                if (x < t.minX - boundsTolerance || x > t.maxX + boundsTolerance ||
                    z < t.minZ - boundsTolerance || z > t.maxZ + boundsTolerance) continue;
                const double dx = x - t.x[0], dz = z - t.z[0];
                double b = (dx * (t.z[2] - t.z[0]) - dz * (t.x[2] - t.x[0])) * t.inverseArea;
                double c = ((t.x[1] - t.x[0]) * dz - (t.z[1] - t.z[0]) * dx) * t.inverseArea;
                double a = 1.0 - b - c;
                const double ta = floatEndpointTolerance > 0 ? floatEndpointTolerance * std::hypot(t.x[2] - t.x[1], t.z[2] - t.z[1]) * std::abs(t.inverseArea) : 0;
                const double tb = floatEndpointTolerance > 0 ? floatEndpointTolerance * std::hypot(t.x[2] - t.x[0], t.z[2] - t.z[0]) * std::abs(t.inverseArea) : 0;
                const double tc = floatEndpointTolerance > 0 ? floatEndpointTolerance * std::hypot(t.x[1] - t.x[0], t.z[1] - t.z[0]) * std::abs(t.inverseArea) : 0;
                if (a < -std::max(EdgeTolerance, ta) || b < -std::max(EdgeTolerance, tb) || c < -std::max(EdgeTolerance, tc)) continue;
                // Only absorb numerical error at a shared edge; never extend
                // a triangle's slope into uncovered water.
                a = std::max(a, 0.0); b = std::max(b, 0.0); c = std::max(c, 0.0);
                height = (a * t.y[0] + b * t.y[1] + c * t.y[2]) / (a + b + c);
                return std::isfinite(height);
            }
            return false;
        }
    };
    struct Wr64WaveDistanceDraw {
        bool valid = false;
        uint32_t mode = 0, camera = 0, course = UINT32_MAX, projection = UINT32_MAX;
        uint32_t players = 1, phase = 1, raceMode = 40, sea = 0;
        int32_t centerX = 0, centerZ = 0;
        double originalDatum = 0, originalSpread = 0;
        std::vector<Wr64WaveDistanceVertex> boundary;
        std::vector<Wr64WaveDistanceSample> samples;
        Wr64WaveDistanceSurface previousSurface;
    };

    template<typename Draw>
    Wr64WaveDistanceSurface wr64BuildWaveDistanceSurface(const Draw &draw) {
        Wr64WaveDistanceSurface out;
        const size_t count = draw.vertexCount();
        const auto &wave = draw.wr64WaveDistance;
        if (!wave.valid || !wr64WaveDistanceCourse(wave.course) || wave.samples.size() != 469U ||
            count < 788U || draw.posFloats.size() != count * 3U ||
            draw.viewProjIndices.size() != count || draw.worldIndices.size() != count ||
            draw.wr64WaterVertexMask.size() != count || draw.wr64WaterFaceIndices.size() != 1440U * 3U) return out;
        uint32_t waterBase = UINT32_MAX;
        for (const auto &sample : wave.samples) waterBase = std::min(waterBase, sample.vertex);
        const uint32_t generatedBase = uint32_t(count - 288U);
        if (uint64_t(waterBase) + 500U > generatedBase || wave.projection != draw.viewProjIndices[waterBase]) return out;
        const auto world = draw.worldIndices[waterBase];
        for (size_t vertex = 0; vertex < count; ++vertex)
            if ((draw.wr64WaterVertexMask[vertex] == 5U) != (vertex >= generatedBase)) return out;
        out.triangles.reserve(1440U);
        for (size_t face = 0; face < draw.wr64WaterFaceIndices.size(); face += 3U) {
            Wr64WaveDistanceSurface::Triangle t{};
            for (uint32_t corner = 0; corner < 3U; ++corner) {
                const uint32_t vertex = draw.wr64WaterFaceIndices[face + corner];
                const bool primary = vertex >= waterBase && uint64_t(vertex) < uint64_t(waterBase) + 488U;
                const bool generated = vertex >= generatedBase && vertex < count;
                if ((!primary && !generated) || (face < 864U * 3U && !primary) ||
                    draw.viewProjIndices[vertex] != wave.projection || draw.worldIndices[vertex] != world) return {};
                t.x[corner] = draw.posFloats[vertex * 3U];
                t.y[corner] = draw.posFloats[vertex * 3U + 1U];
                t.z[corner] = draw.posFloats[vertex * 3U + 2U];
                if (!std::isfinite(t.x[corner]) || !std::isfinite(t.y[corner]) || !std::isfinite(t.z[corner])) return {};
            }
            const double area = (t.x[1] - t.x[0]) * (t.z[2] - t.z[0]) -
                (t.z[1] - t.z[0]) * (t.x[2] - t.x[0]);
            if (!(area < -1.0e-3) || !std::isfinite(area)) return {};
            t.inverseArea = 1.0 / area;
            t.minX = std::min({t.x[0], t.x[1], t.x[2]}); t.maxX = std::max({t.x[0], t.x[1], t.x[2]});
            t.minZ = std::min({t.z[0], t.z[1], t.z[2]}); t.maxZ = std::max({t.z[0], t.z[1], t.z[2]});
            out.triangles.push_back(t);
        }
        out.positionIdentity = draw.posFloats.data(); out.faceIdentity = draw.wr64WaterFaceIndices.data();
        out.positionCount = draw.posFloats.size(); out.faceCount = draw.wr64WaterFaceIndices.size();
        return out;
    }

    // Read-only plan after dense topology/seam validation, before smoothing.
    // Require all 469 source slots and all 397 native interior heights. This
    // declines recovery if the snapshot belongs to another game update.
    template<typename Draw>
    Wr64WaveDistanceDraw wr64PlanWaveDistance(const Draw &draw,
        const Wr64WaveDistanceSnapshot &snapshot, uint32_t base) {
        Wr64WaveDistanceDraw out;
        if (!snapshot.valid || snapshot.rings != 12 || snapshot.view != 0 || snapshot.sourceAddress != 0x03013D68U ||
            !wr64WaveDistanceCourse(snapshot.course) || uint64_t(base) + 500U > draw.vertexCount()) return out;
        const size_t count = draw.vertexCount();
        if (draw.posFloats.size() != count * 3U || draw.vertexSegmentedAddresses.size() != count ||
            draw.wr64WaterProducerKeys.size() != count || draw.viewProjIndices.size() != count || draw.worldIndices.size() != count) return out;
        std::set<uint32_t> seen, boundary;
        const uint32_t projection = draw.viewProjIndices[base], world = draw.worldIndices[base];
        for (uint32_t v = base; v < base + 488U; ++v) {
            const uint32_t address = draw.vertexSegmentedAddresses[v];
            if (address < 0x03013D68U || (address - 0x03013D68U) % 16U) return {};
            const uint32_t slot = (address - 0x03013D68U) / 16U;
            if (slot >= snapshot.nodes.size() || draw.viewProjIndices[v] != projection || draw.worldIndices[v] != world) return {};
            const auto &node = snapshot.nodes[slot];
            const int32_t height = (int32_t(node.rawHeight) >= 0 ? int32_t(node.rawHeight) / 256 : (int32_t(node.rawHeight) - 255) / 256);
            const float x = float(int16_t(uint32_t(snapshot.centerX) + uint32_t(int32_t(node.x))));
            const float z = float(int16_t(uint32_t(snapshot.centerZ) + uint32_t(int32_t(node.z))));
            const float y = float(int16_t(uint32_t(snapshot.tide) + uint32_t(node.boundary() ? 0 : height)));
            if (draw.posFloats[v * 3U] != x || draw.posFloats[v * 3U + 2U] != z || draw.posFloats[v * 3U + 1U] != y ||
                (!snapshot.producerSealed && draw.wr64WaterProducerKeys[v] != node.key)) return {};
            if (seen.insert(slot).second) out.samples.push_back({v, node.key, x, y, z});
            if (node.boundary()) {
                boundary.insert(slot);
                out.boundary.push_back({v, slot, node.key, snapshot.mode ?
                    float(int16_t(uint32_t(snapshot.tide) + uint32_t(height))) : y});
            }
        }
        if (seen.size() != 469U || boundary.size() != 72U) return {};
        // Six native fan anchors are private physical aliases, with different
        // segmented addresses. Match their already-validated exact endpoints.
        const size_t primaryBoundaryCount = out.boundary.size();
        std::set<uint32_t> anchors;
        for (uint32_t v = base + 488U; v < base + 494U; ++v) {
            uint32_t found = UINT32_MAX;
            for (size_t i = 0; i < primaryBoundaryCount; ++i) {
                const auto &candidate = out.boundary[i];
                bool same = draw.viewProjIndices[v] == projection && draw.worldIndices[v] == world;
                for (uint32_t axis = 0; axis < 3; ++axis)
                    same = same && draw.posFloats[v * 3U + axis] == draw.posFloats[candidate.vertex * 3U + axis];
                if (same) {
                    if (found != UINT32_MAX && out.boundary[found].slot != candidate.slot) return {};
                    found = uint32_t(i);
                }
            }
            if (found == UINT32_MAX || !anchors.insert(out.boundary[found].slot).second) return {};
            auto alias = out.boundary[found]; alias.vertex = v; out.boundary.push_back(alias);
        }
        out.valid = true; out.mode = snapshot.mode; out.camera = snapshot.camera; out.course = snapshot.course; out.projection = projection;
        out.players = snapshot.players; out.phase = snapshot.phase; out.raceMode = snapshot.raceMode; out.sea = snapshot.sea;
        out.centerX = snapshot.centerX; out.centerZ = snapshot.centerZ;
        return out;
    }

    // Match the previous rendered surface at the accepted previous X/Z. A
    // recentered boundary can now occupy old interior or old annulus geometry;
    // its current wave-cell key alone cannot identify that rendered height.
    // Interior matching and all X/Z/UV endpoints remain unchanged. Unsupported
    // history/coverage holds current Y instead of inventing an outside sample.
    template<typename Draw>
    bool wr64FinalizeWaveDistance(Draw &current, const Draw *previous,
        bool compatibleScene, uint32_t previousProjection = UINT32_MAX) {
        auto &cur = current.wr64WaveDistance;
        const auto *prev = previous ? &previous->wr64WaveDistance : nullptr;
        if (!cur.valid || (!cur.mode && (!prev || !prev->valid || !prev->mode))) return false;
        cur.previousSurface = {};
        if (compatibleScene && prev && prev->valid && cur.course == prev->course && cur.camera == prev->camera &&
            cur.players == prev->players && cur.phase == prev->phase && cur.raceMode == prev->raceMode && cur.sea == prev->sea &&
            std::abs(int64_t(cur.centerX) - prev->centerX) <= 192 && std::abs(int64_t(cur.centerZ) - prev->centerZ) <= 192 &&
            previousProjection == prev->projection) {
            cur.previousSurface = wr64BuildWaveDistanceSurface(*previous);
        }
        for (const auto &v : cur.boundary) {
            if (uint64_t(v.vertex) * 3U + 2U >= current.velFloats.size()) continue;
            const double x = double(current.posFloats[v.vertex * 3U]) - double(current.velFloats[v.vertex * 3U]);
            const double z = double(current.posFloats[v.vertex * 3U + 2U]) - double(current.velFloats[v.vertex * 3U + 2U]);
            double height = 0.0;
            current.velFloats[v.vertex * 3U + 1U] = cur.previousSurface.sample(x, z, height)
                ? float(double(current.posFloats[v.vertex * 3U + 1U]) - height) : 0.0f;
            if (uint64_t(v.vertex) * 4U < current.wr64WaterFieldInfo.size()) current.wr64WaterFieldInfo[v.vertex * 4U] = 0U;
        }
        return true;
    }

    template<typename Workloads, typename Mapping>
    bool wr64FinalizeMappedWaveDistance(Workloads &workloads, uint32_t index, const Mapping &mapping) {
        if (index >= workloads.size()) return false;
        auto &current = workloads[index];
        const bool available = mapping.mapped && mapping.prevWorkloadIndex < workloads.size();
        const auto *previous = available ? &workloads[mapping.prevWorkloadIndex] : nullptr;
        uint32_t previousProjection = UINT32_MAX;
        const auto projection = current.drawData.wr64WaveDistance.projection;
        if (available && projection < mapping.viewProjections.size() && mapping.viewProjections[projection].mapped)
            previousProjection = mapping.viewProjections[projection].prevTransformIndex;
        return wr64FinalizeWaveDistance(current.drawData, previous ? &previous->drawData : nullptr,
            available && current.wr64RtCourse == previous->wr64RtCourse, previousProjection);
    }
}
