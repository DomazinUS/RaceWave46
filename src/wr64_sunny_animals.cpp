#include "wr64_sunny_animals.hpp"
#include "wr64_sunny_animals_load.hpp"
#include "wr64_sunny_detail.hpp"
#include <cstdio>
#include <cstring>

extern "C" void func_800916B4(uint8_t*, recomp_context*);

namespace {
constexpr uint32_t addressMask = 0x1FFFFFFF;
constexpr uint32_t firstPool = 0x11F8E8, poolStride = 0x18FE8;
constexpr uint32_t displayListBytes = 0x6000, reservedTail = 0x800;
// Native animal setup emits six commands (light count, two lights, sync, fog
// color, fog factor); allow exactly that cost before the copied animal body.
constexpr uint32_t setupBudget = 0x30;
struct Capture {
    uint8_t* memory = nullptr;
    uint32_t frame = 0, buffer = 0, pool = 0, begin = 0, end = 0, course = 0;
    bool pending = false;
};
// All three hooks execute on the native game thread. The commands and their
// referenced matrices live in the current native double-buffered task.
Capture capture;
uint32_t diagnosticEvents = 0;
uint32_t word(uint8_t* rdram, uint32_t address) {
    return MEM_W(0, S32(address));
}
bool knownPool(uint32_t pool) {
    return pool == firstPool || pool == firstPool + poolStride;
}
bool inPool(uint32_t cursor, uint32_t pool, uint32_t bytes = 0) {
    return knownPool(pool) && (cursor & 7) == 0 && cursor >= pool &&
        bytes <= displayListBytes && cursor - pool <= displayListBytes - bytes;
}
bool sameTask(uint8_t* rdram) {
    return capture.memory == rdram &&
        capture.frame == word(rdram, 0x800E62C4) &&
        capture.buffer == word(rdram, 0x8011F8E0) &&
        capture.course == word(rdram, 0x800D8170) &&
        capture.pool == (word(rdram, 0x801518B8) & addressMask);
}
uint32_t bodyBudget(uint8_t* rdram) {
    uint32_t bytes = 0;
    uint32_t matrices = 0;
    bool hasPenguins = false;
    // Count all potential draws before native P1 visibility/LOD culling.
    // A full gull emits 23 commands, its distant form 3, each fish school 11.
    // Other native species fit the full-gull bound except the penguin (24).
    // Native ADC8C reserves each species' matrices, but omits type 13. Keep an
    // upper bound for a penguin roster before executing its native renderer.
    constexpr uint32_t matrixCosts[] = {0, 8, 1, 8, 1, 6, 6, 4, 4, 4, 4, 0, 4, 7};
    for (uint32_t i = 0; i < 30; ++i) {
        const uint32_t actor = 0x801CF060 + i * 0xBC;
        const uint32_t type = word(rdram, actor) + word(rdram, actor + 4);
        if (type == 0) continue;
        bytes += type == 13 ? 192 : (type == 4 ? 24 : (type >= 7 && type <= 9 ? 88 : 184));
        matrices += type < 14 ? matrixCosts[type] : 0;
        hasPenguins |= type == 13;
    }
    if (hasPenguins && matrices >= 192) return displayListBytes;
    return bytes;
}
void noteOnce(uint32_t bit, const char* stage, uint8_t* rdram, uint32_t cursor, uint32_t bytes) {
    if ((diagnosticEvents & bit) != 0) return;
    diagnosticEvents |= bit;
    char message[256];
    std::snprintf(message, sizeof(message),
        "animals-%s view=%u update=%u buffer=%u pool=%08X cursor=%08X bytes=%u actors=%u matrices=%u",
        stage, word(rdram, 0x800DAB2C), word(rdram, 0x800E62C4), word(rdram, 0x8011F8E0),
        word(rdram, 0x801518B8), cursor, bytes, word(rdram, 0x800E62C8), word(rdram, 0x801D06B8));
    wr64::sunny_detail::note_diagnostic(message);
}
}

extern "C" uint32_t wr64_sunny_animals_replay(uint8_t* rdram, recomp_context* ctx) {
    if (!ctx || !rdram || !wr64_sunny_animals_ready(rdram)) {
        capture = {};
        return 0;
    }
    const uint32_t view = word(rdram, 0x800DAB2C);
    if (view == 0) {
        capture = {};
        const uint32_t pool = word(rdram, 0x801518B8) & addressMask;
        if (!inPool(uint32_t(ctx->r4) & addressMask, pool,
                bodyBudget(rdram) + setupBudget + reservedTail)) {
            noteOnce(1, "p1-capacity-skip", rdram, uint32_t(ctx->r4), bodyBudget(rdram));
            ctx->r2 = ctx->r4;
            return 1;
        }
        return 0;
    }
    if (view != 1) {
        capture = {};
        return 0;
    }

    // Even if no valid P1 body is available, never run another animal update
    // through the P2 draw. Return an unchanged cursor for this optional pass.
    ctx->r2 = ctx->r4;
    const bool usable = capture.pending && sameTask(rdram);
    capture.pending = false;
    if (!usable || capture.end <= capture.begin) {
        noteOnce(2, "p2-empty-or-stale", rdram, uint32_t(ctx->r4), 0);
        return 1;
    }
    const uint32_t bytes = capture.end - capture.begin;
    const uint32_t destination = uint32_t(ctx->r4) & addressMask;
    if (destination < capture.end ||
        !inPool(destination, capture.pool, bytes + setupBudget + reservedTail)) {
        noteOnce(4, "p2-capacity-skip", rdram, uint32_t(ctx->r4), bytes);
        return 1;
    }

    // P2 retains its own camera, viewport, lighting and fog. Native 916B4
    // installs only the latter two; the captured body starts after P1 setup.
    recomp_context setup = *ctx;
    setup.f_odd = setup.mips3_float_mode ? &setup.f1.u32l : &setup.f0.u32h;
    func_800916B4(rdram, &setup);
    const uint32_t body = uint32_t(setup.r2) & addressMask;
    if (body < destination || body - destination > setupBudget ||
        !inPool(body, capture.pool, bytes + reservedTail)) return 1;
    std::memmove(rdram + body, rdram + capture.begin, bytes);
    ctx->r2 = ADD32(setup.r2, bytes);
    noteOnce(8, "p2-replayed", rdram, uint32_t(ctx->r2), bytes);
    return 1;
}

extern "C" void wr64_sunny_animals_capture_begin(uint8_t* rdram, recomp_context* ctx) {
    if (!ctx || !rdram || !wr64_sunny_animals_ready(rdram) ||
        word(rdram, 0x800DAB2C) != 0) return;
    const uint32_t pool = word(rdram, 0x801518B8) & addressMask;
    const uint32_t begin = uint32_t(ctx->r2) & addressMask;
    const uint32_t buffer = word(rdram, 0x8011F8E0);
    if (buffer > 1 || !inPool(begin, pool)) return;
    capture = {rdram, word(rdram, 0x800E62C4), buffer, pool, begin, begin,
        word(rdram, 0x800D8170), true};
}

extern "C" void wr64_sunny_animals_capture_end(uint8_t* rdram, recomp_context* ctx) {
    if (!ctx || !rdram || !capture.pending || !sameTask(rdram) ||
        word(rdram, 0x800DAB2C) != 0) return;
    const uint32_t end = uint32_t(ctx->r2) & addressMask;
    if (end < capture.begin || !inPool(end, capture.pool)) {
        capture = {};
        return;
    }
    capture.end = end;
    if (end > capture.begin) noteOnce(16, "p1-captured", rdram, uint32_t(ctx->r2), end - capture.begin);
}
