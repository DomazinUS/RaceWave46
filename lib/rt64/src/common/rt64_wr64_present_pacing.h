#pragma once

#include <cstdint>

namespace RT64 {
// A waitable DXGI swap chain limits queue depth; SyncInterval=1 supplies the
// display cadence. Do not also sleep to an independently rounded CPU period
// when that cadence already supplies the requested rate. Lower manual limits
// still need the CPU limiter, as do other backends and unsynchronized output.
constexpr bool wr64PresentUsesDisplayPacing(bool d3d12, bool vsync,
    bool presentWait, uint32_t targetRate, uint32_t swapChainRate) {
    return d3d12 && vsync && presentWait && (swapChainRate > 0) &&
        (targetRate >= swapChainRate);
}
} // namespace RT64
