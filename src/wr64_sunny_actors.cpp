#include "wr64_sunny_actors.h"
#include "wr64_sunny_detail.hpp"

extern "C" void func_800694B8(uint8_t*, recomp_context*);

namespace {
constexpr uint32_t rdramBytes = 0x800000;
constexpr uint32_t firstPool = 0x8011F8E8, poolBytes = 0x18FE8;
constexpr uint32_t displayListBytes = 0x6000;
constexpr uint32_t reservedTail = 0x800, shadowCommandBytes = 2 * 16;
constexpr uint32_t shadowMatrix = 0xF808;
constexpr uint32_t commonBytes = 0x8290;
uint32_t word(uint8_t* rdram, uint32_t address) {
    return MEM_W(0, S32((address & 0x1FFFFFFF) | 0x80000000));
}
bool resident(uint32_t address, uint32_t size) {
    const auto physical = address & 0x1FFFFFFF;
    return physical < rdramBytes && size <= rdramBytes - physical;
}
}

extern "C" uint32_t wr64_sunny_actor_shadows(uint8_t* rdram, recomp_context* ctx) {
    if (!ctx || !wr64_sunny_detail_active(rdram)) return 0;
    // The original 1P pass also skips Drake Lake (800695E8), independently
    // of its two-player exclusion. Preserve that course's native treatment.
    if (word(rdram, 0x800D8170) == 4) return 0;
    const uint32_t view = word(rdram, 0x800DAB2C);
    const uint32_t count = word(rdram, 0x801982F0);
    const uint32_t racers[]{word(rdram, 0x800D48DC), word(rdram, 0x800D48E0)};
    if (view > 1 || count == 0 || count > 4 || racers[0] >= count ||
        racers[1] >= count || racers[0] == racers[1]) return 0;

    const uint32_t pool = word(rdram, 0x801518B8);
    const uint32_t start = uint32_t(ctx->r4);
    // GfxInitBuffers alternates two complete native pools. Their four reserved
    // shadow matrices are separate from the first 0x6000 display-list bytes.
    // Keep a conservative tail for the native passes that follow this one.
    if ((pool != firstPool && pool != firstPool + poolBytes) ||
        !resident(pool, poolBytes) || start < pool || (start & 7) != 0 ||
        start - pool > displayListBytes - reservedTail - shadowCommandBytes ||
        shadowMatrix + 4 * 64 > poolBytes) return 0;
    const uint32_t common = word(rdram, 0x80151984);
    // Segment 1 is loaded once by SysMain in both modes, independently of the
    // course and rider banks. Confirm the stock shadow list is resident.
    if (!resident(common, commonBytes) ||
        word(rdram, common + 0x68B0) != 0x06000000 ||
        word(rdram, common + 0x68B4) != 0x01006840 ||
        word(rdram, common + 0x68B8) != 0xB8000000) return 0;

    recomp_context draw = *ctx;
    draw.f_odd = draw.mips3_float_mode ? &draw.f1.u32l : &draw.f0.u32h;
    uint32_t cursor = start;
    for (uint32_t racer : racers) {
        draw.r4 = S32(cursor);
        draw.r5 = racer;
        // This existing function checks crash/submersion state, samples the
        // current water height and writes a world-space shadow matrix plus two
        // display-list commands. It does not advance rider or water simulation.
        func_800694B8(rdram, &draw);
        cursor = uint32_t(draw.r2);
    }
    // Both views use the same world-space matrices. Their native camera and
    // viewport remain active; no player-count or selected-racer global changes.
    ctx->r2 = S32(cursor);
    return 1;
}
