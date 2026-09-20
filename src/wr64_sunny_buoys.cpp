#include "wr64_sunny_buoys.hpp"
#include "wr64_sunny_detail.hpp"

namespace {
constexpr uint32_t rdramBytes = 0x800000;
constexpr uint32_t addressMask = 0x1FFFFFFF;
constexpr uint32_t firstPool = 0x11F8E8, poolBytes = 0x18FE8;
constexpr uint32_t displayListBytes = 0x6000, reservedTail = 0x800;
uint32_t word(uint8_t* rdram, uint32_t address) {
    return MEM_W(0, S32((address & addressMask) | 0x80000000));
}
bool resident(uint32_t address, uint32_t size) {
    const uint32_t physical = address & addressMask;
    return physical < rdramBytes && size <= rdramBytes - physical;
}
}

extern "C" void wr64_sunny_buoy_details(uint8_t* rdram, recomp_context* ctx) {
    if (!ctx || ctx->r24 != 2 || !wr64_sunny_detail_active(rdram)) return;
    const uint32_t view = word(rdram, 0x800DAB2C);
    const uint32_t count = word(rdram, 0x801BB120);
    // The native index table has 64 bytes; each view's prepared matrix bank
    // has twelve slots. This pass only consumes matrices already built by
    // DrawBuoy at 0x8006FFF8, including in the original two-player path.
    if (view > 1 || count == 0 || count > 64) return;
    uint32_t details = 0;
    for (uint32_t index = 0; index < count; ++index) {
        const uint32_t object = 0x801AEE20 + index * 0x104;
        const int16_t visibility = MEM_H(0, S32(0x801C0840 + index * 2));
        if (visibility < 0 || word(rdram, object + 0x9C) != 0 ||
            word(rdram, object + 0xC8) == 0) continue;
        if (MEM_BU(0, S32(0x801C0B40 + index)) >= 12 || ++details > 12) return;
    }
    if (details == 0 || !resident(uint32_t(ctx->r29), 0x554)) return;

    const uint32_t pool = word(rdram, 0x801518B8) & addressMask;
    const uint32_t cursor = word(rdram, uint32_t(ctx->r29) + 0x550) & addressMask;
    // Native setup emits three commands and each eligible buoy emits seven.
    // Leave space for the later native passes in this same display-list pool.
    const uint32_t extraBytes = 24 + details * 56;
    if ((pool != firstPool && pool != firstPool + poolBytes) ||
        cursor < pool || (cursor & 7) != 0 ||
        cursor - pool > displayListBytes - reservedTail - extraBytes) return;

    // At 0x800713FC t8 holds only this visual pass's player-count comparison.
    // The native block is shared by all eight VS courses. It retains its
    // visibility, checkpoint type, active-state, L/R material selection and
    // per-view transform choices; course eligibility belongs to the load latch.
    ctx->r24 = 1;
}
