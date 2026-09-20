#include "wr64_two_player_celestial_draw.h"
#include "wr64_two_player_celestial.hpp"
#include "wr64_sunny_detail.hpp"

#include <algorithm>
#include <array>
#include <cstring>

extern "C" {
void func_8008D94C(uint8_t*, recomp_context*);
void func_8008CFEC(uint8_t*, recomp_context*);
void func_8008D454(uint8_t*, recomp_context*);
void func_8008BD2C(uint8_t*, recomp_context*);
void func_80051538(uint8_t*, recomp_context*);
}

namespace {
constexpr uint32_t NativeDrawBudget = 0x1800;
constexpr uint32_t WashState = 0x800D47E0;
struct PendingWash {
    uint8_t* rdram = nullptr;
    uint32_t frame = 0, pool = 0;
    bool visible = false;
};
thread_local PendingWash firstViewWash;

uint32_t word(uint8_t* rdram, uint32_t address) {
    return uint32_t(MEM_W(0, S32(address)));
}
void put(uint8_t* rdram, uint32_t address, uint32_t value) {
    MEM_W(0, S32(address)) = value;
}
bool room(uint8_t* rdram, uint32_t cursor) {
    if (!rdram || !wr64_sunny_detail_active(rdram)) return false;
    const uint32_t pool = word(rdram, 0x801518B8);
    return (pool == 0x8011F8E8 || pool == 0x801388D0) &&
        !(cursor & 7) && cursor >= pool &&
        cursor - pool <= 0x6000 - 0x800 - NativeDrawBudget - 32;
}
uint32_t scissor(uint8_t* rdram, uint32_t cursor, uint32_t view) {
    put(rdram, cursor, 0xE7000000);
    put(rdram, cursor + 4, 0);
    put(rdram, cursor + 8, 0xED000000 | (view * 480));
    put(rdram, cursor + 12, 0x006A0000 | ((view + 1) * 480));
    return cursor + 16;
}
uint32_t call(uint8_t* rdram, recomp_context* parent, uint32_t cursor,
              void (*native)(uint8_t*, recomp_context*)) {
    recomp_context child = *parent;
    child.f_odd = &child.f0.u32h;
    child.r4 = S32(cursor);
    native(rdram, &child);
    return uint32_t(child.r2);
}

// Native celestial sprites use the full 240-line projection chart. Both 2P
// cameras retain its scale and move the center by 60 lines. Clip before packing
// the unsigned RDP coordinates, advancing texture T when the top is clipped.
// Exact half-scissors also let the existing vertical-split world mapping place
// these rectangles alongside their owning camera without HUD anchoring.
uint32_t mapRectangles(uint8_t* rdram, uint32_t start, uint32_t end, uint32_t view) {
    if (end < start || end - start > NativeDrawBudget || (end & 7)) return start;
    const int shift = view ? 240 : -240;
    const int top = int(view * 480), bottom = top + 480;
    uint32_t output = start;
    for (uint32_t input = start; input < end;) {
        uint32_t w0 = word(rdram, input), w1 = word(rdram, input + 4);
        if ((w0 >> 24) == 0xE4 && input + 24 <= end) {
            uint32_t st = word(rdram, input + 12);
            const uint32_t delta = word(rdram, input + 20);
            const int oldTop = int(w1 & 0xFFF) + shift;
            const int y0 = std::max(oldTop, top);
            const int y1 = std::min(int(w0 & 0xFFF) + shift, bottom);
            if (y0 < y1) {
                const int t = int(int16_t(st & 0xFFFF)) +
                    (y0 - oldTop) * int(int16_t(delta & 0xFFFF)) / 128;
                st = (st & 0xFFFF0000) | uint16_t(t);
                put(rdram, output, (w0 & ~0xFFFu) | uint32_t(y1));
                put(rdram, output + 4, (w1 & ~0xFFFu) | uint32_t(y0));
                put(rdram, output + 8, word(rdram, input + 8));
                put(rdram, output + 12, st);
                put(rdram, output + 16, word(rdram, input + 16));
                put(rdram, output + 20, delta);
                output += 24;
            }
            input += 24;
        }
        else {
            if ((w0 >> 24) == 0xED) {
                w0 = 0xED000000 | uint32_t(top);
                w1 = 0x006A0000 | uint32_t(bottom);
            }
            put(rdram, output, w0);
            put(rdram, output + 4, w1);
            input += 8;
            output += 8;
        }
    }
    return output;
}
}

extern "C" uint32_t wr64_two_player_celestial_draw(uint8_t* rdram, recomp_context* ctx, uint32_t cursor) {
    if (!room(rdram, cursor) || !wr64_two_player_celestial_begin(rdram, ctx)) return cursor;
    const uint32_t view = wr64_two_player_celestial_view();
    const uint32_t start = scissor(rdram, cursor, view);
    uint32_t end;
    if (word(rdram, 0x800D8170) == 0 || word(rdram, 0x800D8170) == 2) end = call(rdram, ctx, start, func_8008D94C);
    else {
        end = call(rdram, ctx, start, func_8008CFEC);
        end = call(rdram, ctx, end, func_8008D454);
    }
    end = mapRectangles(rdram, start, end, view);
    wr64_two_player_celestial_end(rdram);
    return scissor(rdram, end, view);
}

extern "C" uint32_t wr64_two_player_sun_overlay(uint8_t* rdram, recomp_context* ctx, uint32_t cursor) {
    if (!rdram) return cursor;
    const uint32_t currentView = word(rdram, 0x800DAB2C);
    const uint32_t frame = word(rdram, 0x800E62C4);
    const uint32_t pool = word(rdram, 0x801518B8);
    if (currentView == 0 || firstViewWash.rdram != rdram ||
        firstViewWash.frame != frame || firstViewWash.pool != pool) firstViewWash = {};
    if (!rdram || (word(rdram, 0x800D8170) != 0 && word(rdram, 0x800D8170) != 2) || !room(rdram, cursor) ||
        !wr64_two_player_celestial_begin(rdram, ctx)) return cursor;
    const uint32_t view = wr64_two_player_celestial_view();
    std::array<uint8_t, 32> saved;
    std::memcpy(saved.data(), rdram + (WashState & 0x7FFFFF), saved.size());
    const uint32_t scroll = word(rdram, WashState + 28);
    const uint32_t start = scissor(rdram, cursor, view);
    uint32_t end = call(rdram, ctx, start, func_8008BD2C);
    const bool visibleWash = word(rdram, WashState) != 0;
    end = call(rdram, ctx, end, func_80051538);
    end = mapRectangles(rdram, start, end, view);
    // Both views sample the same scroll phase; advance it once after P2.
    std::memcpy(rdram + (WashState & 0x7FFFFF), saved.data(), saved.size());
    if (view == 0) firstViewWash = {rdram, frame, pool, visibleWash};
    else {
        if (firstViewWash.visible || visibleWash) put(rdram, WashState + 28, (scroll - 1) & 127);
        firstViewWash = {};
    }
    wr64_two_player_celestial_end(rdram);
    return scissor(rdram, end, view);
}

extern "C" uint32_t wr64_two_player_sun_skip_shared_wash(uint8_t* rdram) {
    // Mode 2 is the native sun wash; leave transition/other overlay modes alone.
    return rdram && wr64_two_player_celestial_view() == 2 &&
        wr64_sunny_detail_active(rdram) && (word(rdram, 0x800D8170) == 0 || word(rdram, 0x800D8170) == 2) &&
        word(rdram, WashState) == 2;
}
