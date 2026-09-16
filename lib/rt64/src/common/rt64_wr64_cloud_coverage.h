#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

namespace RT64 {
    struct Wr64CloudCoverageVertex {
        std::array<float, 3> position{};
        std::array<float, 2> uv{};
        uint8_t alpha = 0;
    };

    struct Wr64CloudCoverageInput {
        // Native fan order: center, then six perimeter vertices.
        std::array<Wr64CloudCoverageVertex, 7> vertices{};
        std::array<float, 3> camera{};
        float slope = 0.0f;
        float intercept = 0.0f;
    };

    struct Wr64CloudCoverageAddedVertex {
        std::array<float, 3> position{};
        std::array<float, 2> uv{};
        // The same affine weights apply to the repaired native position and
        // texcoord velocities. This extends the current native texture chart,
        // including its scrolling, rather than stretching its finite border.
        std::array<float, 7> weights{};
        uint8_t alpha = 0;
    };

    struct Wr64CloudCoverageMesh {
        bool valid = false;
        std::vector<Wr64CloudCoverageAddedVertex> vertices;
        // Annulus only. Indices 0..6 name untouched native vertices; 7+ name
        // the added vertices above. The original six triangles stay separate.
        std::vector<uint32_t> indices;
    };

    inline Wr64CloudCoverageMesh wr64BuildCloudCoverage(const Wr64CloudCoverageInput &input) {
        Wr64CloudCoverageMesh result;
        constexpr unsigned Rings = 16;
        auto finite = [](double value) { return std::isfinite(value) && std::abs(value) <= 1.0e7; };
        if (!std::isfinite(input.slope) || !std::isfinite(input.intercept) ||
            input.slope >= -1.0e-6f || input.slope < -1.0f ||
            input.intercept <= 0.0f || input.intercept > 4096.0f) return result;
        const double zeroRadius = -double(input.intercept) / input.slope;
        // Bound the extension independently of data supplied by a course.
        if (!finite(zeroRadius) || zeroRadius < 16.0 || zeroRadius > 16384.0) return result;
        for (float value : input.camera) if (!finite(value)) return result;
        for (const auto &vertex : input.vertices) {
            for (float value : vertex.position) if (!finite(value)) return result;
            for (float value : vertex.uv) if (!finite(value)) return result;
            if (std::abs(vertex.position[1] - input.vertices[0].position[1]) > 0.01f) return result;
            const double distance = std::hypot(double(vertex.position[0]) - input.camera[0],
                double(vertex.position[2]) - input.camera[2]);
            const double expectedAlpha = std::clamp(std::round(distance * input.slope + input.intercept), 0.0, 255.0);
            // Reject a stale camera/coefficient snapshot or a different alpha
            // producer. Fixed native matrices and integer vertices can differ
            // slightly from the original unquantized camera calculation.
            if (std::abs(expectedAlpha - vertex.alpha) > 2.0) return result;
        }

        // Offset the actual convex perimeter's six supporting lines until
        // they contain the native zero-opacity circle around this camera.
        // Replacing only its radius fails because the native ring center also
        // moves with that radius. Keeping the original fan avoids changing its
        // interpolated opacity, which a seven-vertex replacement would do.
        double area = 0.0;
        for (unsigned i = 0; i < 6; ++i) {
            const auto &a = input.vertices[i + 1].position;
            const auto &b = input.vertices[(i + 1) % 6 + 1].position;
            area += double(a[0]) * b[2] - double(a[2]) * b[0];
        }
        if (std::abs(area) < 1.0) return result;
        const double orientation = area > 0.0 ? 1.0 : -1.0;
        struct Line { double x, z, d; } lines[6];
        for (unsigned i = 0; i < 6; ++i) {
            const auto &a = input.vertices[i + 1].position;
            const auto &b = input.vertices[(i + 1) % 6 + 1].position;
            const double dx = double(b[0]) - a[0], dz = double(b[2]) - a[2];
            const double length = std::hypot(dx, dz);
            if (length < 1.0) return result;
            const double nx = orientation * dz / length, nz = -orientation * dx / length;
            const double nativeD = nx * a[0] + nz * a[2];
            // Reject folded/nonconvex fans, including a center on the border.
            for (unsigned j = 0; j < 7; ++j) {
                const auto &p = input.vertices[j].position;
                if (nx * p[0] + nz * p[2] > nativeD + 0.01) return result;
            }
            const auto &center = input.vertices[0].position;
            if (nativeD - nx * center[0] - nz * center[2] < 0.01) return result;
            lines[i] = { nx, nz, std::max(nativeD + 1.0,
                nx * input.camera[0] + nz * input.camera[2] + zeroRadius + 32.0) };
        }
        std::array<std::array<double, 2>, 6> outer{};
        for (unsigned i = 0; i < 6; ++i) {
            const Line &a = lines[(i + 5) % 6], &b = lines[i];
            const double determinant = a.x * b.z - a.z * b.x;
            if (std::abs(determinant) < 0.1) return result;
            outer[i] = { (a.d * b.z - a.z * b.d) / determinant,
                (a.x * b.d - a.d * b.x) / determinant };
            for (double value : outer[i]) if (!finite(value)) return result;
            for (const auto &line : lines)
                if (line.x * outer[i][0] + line.z * outer[i][1] > line.d + 0.01) return result;
        }

        // Choose the best-conditioned native triangle for UV gradients. The
        // individual rim vertex remains the exact anchor, so native UV/alpha
        // quantization does not make a crack along the shared inner boundary.
        unsigned basisA = 0, basisB = 1, basisC = 2;
        double determinant = 0.0;
        for (unsigned a = 0; a < 5; ++a) for (unsigned b = a + 1; b < 6; ++b)
            for (unsigned c = b + 1; c < 7; ++c) {
                const auto &p = input.vertices[a].position;
                const auto &q = input.vertices[b].position;
                const auto &r = input.vertices[c].position;
                const double candidate = (double(q[0]) - p[0]) * (double(r[2]) - p[2]) -
                    (double(q[2]) - p[2]) * (double(r[0]) - p[0]);
                if (std::abs(candidate) > std::abs(determinant)) {
                    basisA = a; basisB = b; basisC = c; determinant = candidate;
                }
            }
        if (std::abs(determinant) < 1.0) return result;
        const auto &a = input.vertices[basisA].position;
        const auto &b = input.vertices[basisB].position;
        const auto &c = input.vertices[basisC].position;
        const double bx = double(b[0]) - a[0], bz = double(b[2]) - a[2];
        const double cx = double(c[0]) - a[0], cz = double(c[2]) - a[2];
        // A native S16 texture-coordinate wrap inside the fan (or a changed
        // producer) cannot be extrapolated as one chart. Retain its original
        // draw instead. Two raw 1/32-texel steps allow native quantization.
        for (const auto &native : input.vertices) {
            const double dx = double(native.position[0]) - a[0];
            const double dz = double(native.position[2]) - a[2];
            const double u = (dx * cz - dz * cx) / determinant;
            const double v = (bx * dz - bz * dx) / determinant;
            for (unsigned component = 0; component < 2; ++component) {
                const double fitted = input.vertices[basisA].uv[component] +
                    u * (double(input.vertices[basisB].uv[component]) - input.vertices[basisA].uv[component]) +
                    v * (double(input.vertices[basisC].uv[component]) - input.vertices[basisA].uv[component]);
                if (std::abs(fitted - native.uv[component]) > 0.0625) return result;
            }
        }
        result.vertices.reserve(Rings * 6);
        result.indices.reserve(Rings * 36);
        for (unsigned ring = 1; ring <= Rings; ++ring) {
            const double t = double(ring) / Rings;
            for (unsigned i = 0; i < 6; ++i) {
                const auto &native = input.vertices[i + 1];
                const double dx = (outer[i][0] - native.position[0]) * t;
                const double dz = (outer[i][1] - native.position[2]) * t;
                const double u = (dx * cz - dz * cx) / determinant;
                const double v = (bx * dz - bz * dx) / determinant;
                if (!finite(u) || !finite(v) || std::abs(u) + std::abs(v) > 64.0) return {};
                Wr64CloudCoverageAddedVertex vertex;
                vertex.weights[i + 1] = 1.0f;
                vertex.weights[basisA] -= float(u + v);
                vertex.weights[basisB] += float(u);
                vertex.weights[basisC] += float(v);
                for (unsigned component = 0; component < 3; ++component) {
                    double value = native.position[component] +
                        u * (double(b[component]) - a[component]) +
                        v * (double(c[component]) - a[component]);
                    if (!finite(value)) return {};
                    vertex.position[component] = float(value);
                }
                for (unsigned component = 0; component < 2; ++component) {
                    const double value = native.uv[component] +
                        u * (double(input.vertices[basisB].uv[component]) - input.vertices[basisA].uv[component]) +
                        v * (double(input.vertices[basisC].uv[component]) - input.vertices[basisA].uv[component]);
                    if (!finite(value)) return {};
                    vertex.uv[component] = float(value);
                }
                const double distance = std::hypot(double(vertex.position[0]) - input.camera[0],
                    double(vertex.position[2]) - input.camera[2]);
                vertex.alpha = uint8_t(std::clamp(std::round(distance * input.slope + input.intercept), 0.0, 255.0));
                if (ring == Rings && vertex.alpha != 0) return {};
                result.vertices.push_back(vertex);
            }
            const uint32_t inner = ring == 1 ? 1 : 7 + (ring - 2) * 6;
            const uint32_t next = 7 + (ring - 1) * 6;
            for (unsigned i = 0; i < 6; ++i) {
                const unsigned j = (i + 1) % 6;
                result.indices.insert(result.indices.end(),
                    { inner + i, next + i, inner + j, inner + j, next + i, next + j });
            }
        }
        result.valid = true;
        return result;
    }
}
