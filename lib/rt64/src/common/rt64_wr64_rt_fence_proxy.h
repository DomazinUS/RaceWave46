#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

namespace RT64 {
    struct Wr64RTFenceVertex {
        std::array<float, 4> position{};
        std::array<float, 2> uv{};
        std::array<float, 2> padding{};
        std::array<float, 4> shade{};
    };
    static_assert(sizeof(Wr64RTFenceVertex) == 48, "Fence proxy shader vertex stride");

    struct Wr64RTFenceProxy {
        uint32_t drawIndex = 0;
        // Unindexed triangle list, private to shadow queries. The original
        // visible/reflected geometry and its native streams remain untouched.
        std::vector<Wr64RTFenceVertex> triangles;
    };

    // Exact Sunny Beach i_cottage_6_txt rope/post quads in jetc_1_v. Restrict
    // source identity before generating a volumetric approximation; unrelated
    // course assets can reuse segment D and must not receive this treatment.
    inline bool wr64RTIsSunnyFenceQuad(uint32_t course, const std::array<uint32_t, 6> &sources) {
        if (course != 1) return false;
        uint32_t first = sources[0];
        for (uint32_t source : sources) first = std::min(first, source);
        if (first < 0x0D00C840u || (first - 0x0D00C840u) % 64u) return false;
        const uint32_t vertex = (first - 0x0D00C840u) / 16u;
        if (!(vertex == 8 || (vertex >= 16 && vertex <= 56) || vertex == 64 || vertex == 68 ||
            (vertex >= 80 && vertex <= 120))) return false;
        uint32_t all = 0;
        for (uint32_t face = 0; face < 2; ++face) {
            uint32_t mask = 0;
            for (uint32_t j = 0; j < 3; ++j) {
                const uint32_t source = sources[face * 3 + j];
                if (source < first || source > first + 48 || ((source - first) & 15)) return false;
                const uint32_t bit = 1u << ((source - first) / 16);
                if (mask & bit) return false;
                mask |= bit;
            }
            all |= mask;
        }
        return all == 15;
    }

    // One narrow cross-section every two original S texels. Each section keeps
    // the exact native T range, including clamping below the authored texture.
    // Alpha holes are evaluated by the original material in the shadow shader.
    // This bounded thin-volume approximation makes an edge-on post/rope card
    // occlude light without turning a whole texture repeat sideways.
    inline bool wr64RTAppendFenceProxy(const std::array<Wr64RTFenceVertex, 4> &quad,
        Wr64RTFenceProxy &output) {
        constexpr size_t maxVerticesPerDraw = 24576;
        constexpr size_t maxSlicesPerQuad = 2048;
        constexpr float halfDepth = 2.0f;
        constexpr float stepS = 2.0f;
        for (const auto &v : quad) {
            for (float f : v.position) if (!std::isfinite(f)) return false;
            for (float f : v.uv) if (!std::isfinite(f)) return false;
            for (float f : v.shade) if (!std::isfinite(f)) return false;
            if (std::abs(v.position[3] - 1.0f) > 1e-5f) return false;
        }
        std::array<uint32_t, 4> order{0,1,2,3};
        std::sort(order.begin(), order.end(), [&](uint32_t a, uint32_t b) {
            return quad[a].position[1] > quad[b].position[1];
        });
        const auto &a = quad[order[0]], &b = quad[order[1]];
        const auto &c = quad[order[2]], &d = quad[order[3]];
        if (std::abs(a.position[1]-b.position[1]) > 1e-3f ||
            std::abs(c.position[1]-d.position[1]) > 1e-3f ||
            a.position[1]-c.position[1] < 1.0f) return false;
        auto distanceXZ = [](const Wr64RTFenceVertex &p, const Wr64RTFenceVertex &q) {
            return std::hypot(p.position[0]-q.position[0],p.position[2]-q.position[2]);
        };
        const auto &bottomA = distanceXZ(a,c) < distanceXZ(a,d) ? c : d;
        const auto &bottomB = distanceXZ(a,c) < distanceXZ(a,d) ? d : c;
        if (distanceXZ(a,bottomA) > 1e-3f || distanceXZ(b,bottomB) > 1e-3f ||
            std::abs(a.uv[0]-bottomA.uv[0]) > .04f || std::abs(b.uv[0]-bottomB.uv[0]) > .04f ||
            // The native curved-end quad92 has an authored3/32-texel T
            // offset across both edges. Retain it in interpolation.
            std::abs(a.uv[1]-b.uv[1]) > .125f || std::abs(bottomA.uv[1]-bottomB.uv[1]) > .125f) return false;
        const float length = distanceXZ(a,b);
        const float uA = (a.uv[0]+bottomA.uv[0])*.5f;
        const float uB = (b.uv[0]+bottomB.uv[0])*.5f;
        const float uMin = std::min(uA,uB), uMax = std::max(uA,uB);
        if (!std::isfinite(length) || length < 1.0f || uMax-uMin < 1.0f ||
            uMax-uMin > stepS*maxSlicesPerQuad || std::abs(uMin) > 1000000 || std::abs(uMax) > 1000000) return false;
        const float start = std::ceil((uMin-.5f)/stepS)*stepS+.5f;
        const size_t count = start <= uMax ? size_t(std::floor((uMax-start)/stepS))+1 : 0;
        if (count == 0 || count > maxSlicesPerQuad || output.triangles.size() > maxVerticesPerDraw ||
            count*6 > maxVerticesPerDraw-output.triangles.size()) return false;
        const float nx = (b.position[2]-a.position[2])/length*halfDepth;
        const float nz = (a.position[0]-b.position[0])/length*halfDepth;
        auto interpolate = [](const Wr64RTFenceVertex &p, const Wr64RTFenceVertex &q, float t) {
            Wr64RTFenceVertex v;
            for (size_t i=0;i<4;++i) {
                v.position[i]=p.position[i]+(q.position[i]-p.position[i])*t;
                v.shade[i]=p.shade[i]+(q.shade[i]-p.shade[i])*t;
            }
            for (size_t i=0;i<2;++i) v.uv[i]=p.uv[i]+(q.uv[i]-p.uv[i])*t;
            return v;
        };
        output.triangles.reserve(output.triangles.size()+count*6);
        for (size_t i=0;i<count;++i) {
            const float u = start+float(i)*stepS, t=(u-uA)/(uB-uA);
            auto top=interpolate(a,b,t), bottom=interpolate(bottomA,bottomB,t);
            top.uv[0]=bottom.uv[0]=u;
            std::array<Wr64RTFenceVertex,4> cross{top,bottom,bottom,top};
            for (size_t j=0;j<4;++j) {
                const float sign = j<2 ? -1.0f : 1.0f;
                cross[j].position[0]+=sign*nx; cross[j].position[2]+=sign*nz;
            }
            for (uint32_t j : {0u,1u,2u,0u,2u,3u}) output.triangles.push_back(cross[j]);
        }
        return true;
    }
}
