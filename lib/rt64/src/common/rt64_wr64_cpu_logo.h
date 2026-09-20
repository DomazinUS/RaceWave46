#pragma once

#include <cstdint>
#include <mutex>
#include "rt64_wr64_ultrawide.h"

namespace RT64 {
// This identifies the CPU image produced by the USA boot blitter, using bytes
// from the user's ROM at runtime. No image contents or asset hash is embedded.
// Address alone is insufficient: the game later reuses these framebuffers.
struct Wr64CpuLogoSignature {
    std::mutex mutex;
    uint32_t address = 0;
    uint64_t hash = 0;
    bool valid = false;
};
inline Wr64CpuLogoSignature wr64CpuLogoSignature;
inline constexpr uint32_t Wr64CpuLogoWidth = 424;
inline constexpr uint32_t Wr64CpuLogoHeight = 240;
inline constexpr uint32_t Wr64CpuLogoBytes = Wr64CpuLogoWidth * Wr64CpuLogoHeight * 2;

inline void wr64RegisterCpuLogo(uint32_t address, uint64_t hash) {
    const std::lock_guard lock(wr64CpuLogoSignature.mutex);
    wr64CpuLogoSignature.address = address;
    wr64CpuLogoSignature.hash = hash;
    wr64CpuLogoSignature.valid = true;
}

inline bool wr64IsCpuLogo(uint32_t address, uint32_t width, uint32_t height, uint64_t hash) {
    if (width != Wr64CpuLogoWidth || height != Wr64CpuLogoHeight) return false;
    const std::lock_guard lock(wr64CpuLogoSignature.mutex);
    return wr64CpuLogoSignature.valid && address == wr64CpuLogoSignature.address &&
        hash == wr64CpuLogoSignature.hash;
}

inline Wr64PresentationExtent wr64CpuAwarePresentationExtent(float width, float height,
    bool expand, bool scratchImage, bool cpuBootLogo) {
    return wr64UsaPresentationExtent(width, height, expand && !(scratchImage && cpuBootLogo));
}
} // namespace RT64
