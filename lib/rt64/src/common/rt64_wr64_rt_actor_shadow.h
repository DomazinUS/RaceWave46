#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>

namespace RT64 {
    // The original actor renderer uses nineteen matrices per racer: the ski
    // body/arm/handle and the rider's articulated components. Racers interleave
    // at 0x40 bytes, components at 0x100. Native blobs start later at F808.
    constexpr uint32_t wr64RTActorRacerMask(uint32_t matrix) {
        if (matrix < 0x0300E108u || matrix > 0x0300F3C8u) return 0;
        const uint32_t relative = matrix - 0x0300E108u;
        return (relative & 0x3fu) ? 0 : 1u << ((relative & 0xffu) >> 6);
    }

    inline bool wr64RTAccumulateActorRacer(uint32_t &mask, uint32_t matrix) {
        const uint32_t next = wr64RTActorRacerMask(matrix);
        if (!next || (mask && mask != next)) return false;
        mask = next;
        return true;
    }

    struct Wr64RTActorShadowBounds {
        std::array<float, 3> minimum{}, maximum{};
        bool populated = false;
        bool reliable = true;

        void invalidate() { reliable = false; }

        // CPU matrices use row-vector layout, matching the uploaded HLSL
        // column-major matrix. The presentation matrix is held fixed while
        // enclosing every pos - velocity*(1-weight), weight in [0,1].
        bool include(const std::array<float, 3> &position, const std::array<float, 3> &velocity,
            const std::array<float, 16> &matrix) {
            if (!reliable) return false;
            for (float value : position) if (!std::isfinite(value)) { invalidate(); return false; }
            for (float value : velocity) if (!std::isfinite(value)) { invalidate(); return false; }
            for (float value : matrix) if (!std::isfinite(value)) { invalidate(); return false; }
            std::array<float, 3> lo{}, hi{};
            for (uint32_t axis = 0; axis < 3; ++axis) {
                double current = matrix[12 + axis], previous = current;
                double magnitude = std::abs(current) + 1.0;
                for (uint32_t component = 0; component < 3; ++component) {
                    const double m = matrix[component * 4 + axis];
                    current += double(position[component]) * m;
                    previous += (double(position[component]) - velocity[component]) * m;
                    magnitude += (std::abs(double(position[component])) +
                        std::abs(double(velocity[component]))) * std::abs(m);
                }
                // Cover CPU/GPU multiply-add and interpolated-input rounding,
                // including cancellation at large world coordinates. Outward
                // float rounding keeps this a bound rather than a tight fit.
                const double margin = 16.0 * std::numeric_limits<float>::epsilon() * magnitude;
                lo[axis] = std::nextafter(float(std::min(current, previous) - margin),
                    -std::numeric_limits<float>::infinity());
                hi[axis] = std::nextafter(float(std::max(current, previous) + margin),
                    std::numeric_limits<float>::infinity());
                if (!std::isfinite(lo[axis]) || !std::isfinite(hi[axis])) { invalidate(); return false; }
            }
            for (uint32_t axis = 0; axis < 3; ++axis) {
                minimum[axis] = populated ? std::min(minimum[axis], lo[axis]) : lo[axis];
                maximum[axis] = populated ? std::max(maximum[axis], hi[axis]) : hi[axis];
            }
            populated = true;
            return true;
        }
    };
}
