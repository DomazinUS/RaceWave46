#include "wr64_twilight_buoy_lights.h"
#include "wr64_sunny_detail.hpp"

namespace {
constexpr uint32_t addressMask = 0x1FFFFFFF, rdramBytes = 0x800000;
constexpr uint32_t firstDisplayPool = 0x11F8E8, displayPoolStride = 0x18FE8;
constexpr uint32_t displayBytes = 0x6000, reservedDisplayTail = 0x800;
constexpr uint32_t firstMatrixPool = 0x198368, matrixPoolStride = 0xB2F0;
// Native dynamic matrices begin at +4140; sprite vertices begin at +5140.
constexpr uint32_t dynamicMatrixSlots = (0x5140 - 0x4140) / 64;
thread_local uint8_t* lightMemory = nullptr;
thread_local uint32_t lightFirstMatrix = 0;
uint32_t word(uint8_t* rdram, uint32_t address) {
    return MEM_W(0, S32((address & addressMask) | 0x80000000));
}
bool resident(uint32_t address, uint32_t size) {
    const uint32_t physical = address & addressMask;
    return physical < rdramBytes && size <= rdramBytes - physical;
}
bool residentModels(uint8_t* rdram) {
    // SysMain loads this common bank in both player modes. Each light root
    // wraps its existing native model; no course DMA or texture changes needed.
    const uint32_t base = word(rdram, 0x80151984);
    if (!base || !resident(base, 0x6FB70)) return false;
    constexpr uint32_t roots[] = {0x2BF48, 0x2BFD8, 0x2C798, 0x2C828};
    constexpr uint32_t models[] = {0x0102BED8, 0x0102BF58, 0x0102C728, 0x0102C7A8};
    for (uint32_t i = 0; i < 4; ++i) {
        if (word(rdram, base + roots[i]) != 0x06000000 ||
            word(rdram, base + roots[i] + 4) != models[i] ||
            word(rdram, base + roots[i] + 8) != 0xB8000000) return false;
    }
    return true;
}

bool remainingMatrices(uint8_t* rdram, uint32_t view, uint32_t& remaining) {
    const uint32_t objects = word(rdram, 0x801BFA40);
    if (objects > 64) return false;
    remaining = 0;
    for (uint32_t index = 0; index < objects; ++index) {
        const uint32_t object = 0x801BC940 + index * 0xC4;
        const uint32_t type = word(rdram, object + 0x54);
        // The immediately following native 8006D034 billboard pass.
        if (type == 2 && MEM_H(0, S32(0x801C0AC0 + index * 2)) >= 0) ++remaining;
        // P2 visibility has not been calculated during P1. Reserve every
        // potential dynamic transform in P2's earlier object and later
        // billboard passes, rather than assuming the cameras share a frustum.
        if (view == 0 && (type == 2 || (type == 1 && word(rdram, object + 0x58) != 0))) ++remaining;
    }
    // The native debris pass 800B4ABC draws every active one of these 16
    // records, without a camera cull, once in each remaining view.
    for (uint32_t index = 0; index < 16; ++index) {
        if (word(rdram, 0x801D7B70 + index * 0x24) != 0) remaining += view == 0 ? 2 : 1;
    }
    return true;
}
}

extern "C" void wr64_twilight_buoy_lights(uint8_t* rdram, recomp_context* ctx) {
    lightMemory = nullptr;
    if (!ctx || ctx->r24 != 2 || !wr64_sunny_detail_active(rdram) ||
        word(rdram, 0x800D8170) != 6 || word(rdram, 0x800DAB2C) > 1) return;
    const uint32_t count = word(rdram, 0x801BB120);
    if (count == 0 || count > 64) return;
    const uint32_t view = word(rdram, 0x800DAB2C);
    uint32_t lights = 0, possibleLights = 0;
    for (uint32_t index = 0; index < count; ++index) {
        const uint32_t buoy = 0x801AEE20 + index * 0x104;
        if (word(rdram, buoy + 0x9C) == 0 && word(rdram, buoy + 0xC8) != 0) {
            ++possibleLights;
            if (MEM_H(0, S32(0x801C0840 + index * 2)) >= 0) ++lights;
        }
    }
    if (lights == 0 || !resident(uint32_t(ctx->r29), 0x554) || !residentModels(rdram)) return;

    const uint32_t matrixPool = word(rdram, 0x801AE948) & addressMask;
    const uint32_t nextMatrix = word(rdram, 0x801AE950);
    uint32_t remaining = 0;
    if (!remainingMatrices(rdram, view, remaining)) return;
    // Both passes use the same translation: allocate one slot per checkpoint.
    // During P1 leave room for P2's potential checkpoint lights as well.
    const uint32_t required = lights + remaining + (view == 0 ? possibleLights : 0);
    if ((matrixPool != firstMatrixPool && matrixPool != firstMatrixPool + matrixPoolStride) ||
        required > dynamicMatrixSlots || nextMatrix > dynamicMatrixSlots - required) return;

    const uint32_t displayPool = word(rdram, 0x801518B8) & addressMask;
    const uint32_t cursor = word(rdram, uint32_t(ctx->r29) + 0x550) & addressMask;
    // Each native pass emits seven setup commands, then two per checkpoint.
    const uint32_t extraBytes = 112 + 32 * lights;
    if ((displayPool != firstDisplayPool && displayPool != firstDisplayPool + displayPoolStride) ||
        cursor < displayPool || (cursor & 7) != 0 ||
        cursor - displayPool > displayBytes - reservedDisplayTail - extraBytes) return;

    // Only this branch's temporary comparison changes. Both native passes use
    // the current view's visibility, append fresh matrices and retain their
    // original materials. They never advance animation or change the camera.
    ctx->r24 = 1;
    lightMemory = rdram;
    lightFirstMatrix = nextMatrix;
}

extern "C" void wr64_twilight_buoy_lights_reuse(uint8_t* rdram) {
    if (!rdram || lightMemory != rdram) return;
    // The two native passes have identical eligibility and call 801EDFFC with
    // the same X/0/Z values; no simulation runs between them. Their second
    // writes are byte-identical, so both lists can reference the same slots.
    MEM_W(0, S32(0x801AE950)) = lightFirstMatrix;
    lightMemory = nullptr;
}
