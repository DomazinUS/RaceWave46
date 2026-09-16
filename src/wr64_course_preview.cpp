#include "wr64_diagnostic_policy.h"
#include "wr64_course_preview.h"

#include <array>
#include <cstdio>
#include <cstdlib>

namespace {
constexpr uint32_t RdramBytes = 0x800000;
constexpr uint32_t PoolBytes = 0x6000;
constexpr uint32_t MapBytes = 21 * 8;
constexpr uint32_t ExtraBytes = 128; // Inline depth list +88, viewport alignment +40.
constexpr int32_t Left = 150, OldLeft = 254, Right = 396, Shift = 52;
struct Frame {
    uint8_t* rdram = nullptr;
    uint32_t pool = 0, start = 0, map = 0;
    bool ready = false, applied = false;
    std::array<uint32_t, 24> depth{};
};
thread_local Frame frame;

uint32_t get(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
void put(uint8_t* rdram, uint32_t address, uint32_t value) { MEM_W(0, S32(address)) = value; }
bool enabled() {
    static const bool value = [] {
        const char* setting = std::getenv("WR64_COURSE_PREVIEW");
        return !(setting && setting[0] == '0' && setting[1] == '\0');
    }();
    return value;
}
bool eligible(uint8_t* rdram) {
    const int players = MEM_H(0, S32(0x801CE60C));
    return enabled() && get(rdram, 0x801CE638) == 5 && (players == 1 || players == 2);
}
bool room(uint32_t cursor, uint32_t bytes) {
    return (cursor & 7) == 0 && cursor >= frame.pool &&
        cursor - frame.pool <= PoolBytes && bytes <= PoolBytes - (cursor - frame.pool);
}
}

extern "C" void wr64_course_preview_prepare(uint8_t* rdram, uint32_t cursor) {
    frame = {};
    if (!eligible(rdram)) return;
    frame.rdram = rdram;
    frame.start = cursor;
    frame.pool = get(rdram, 0x801518B8);
    if ((frame.pool & 0xE0000000U) != 0x80000000U ||
        (frame.pool & 0x1FFFFFFFU) > RdramBytes - PoolBytes || !room(cursor, 0x1000)) return;

    const uint32_t segment1 = get(rdram, 0x801CE6B4);
    const uint32_t segment8 = get(rdram, 0x801CE6D0);
    if (segment1 > RdramBytes - 0x6F748 || segment8 > RdramBytes - 0xA6E68) return;
    const uint32_t viewport = 0x80000000U + segment1 + 0x6F738;
    // This miniature map still uses a 320x240 viewport, centered at (325,106).
    // Its scale covers the expanded crop without changing its camera or zoom.
    if (get(rdram, viewport) != 0x028001E0U || get(rdram, viewport + 8) != 0x051401A8U) return;
    const uint32_t source = 0x80000000U + segment8 + 0xA6E00;
    constexpr std::array<uint8_t, 13> opcodes{0x03,0xB6,0xB7,0xBB,0xE7,0xBA,0xFC,0xB9,0xFE,0xFF,0xF7,0xF6,0xB8};
    for (uint32_t i = 0; i < opcodes.size(); ++i)
        if (get(rdram, source + i * 8) >> 24 != opcodes[i]) return;
    if (get(rdram, source + 4) != 0x080A6DA0U ||
        get(rdram, source + 68) != 0x00700000U ||
        get(rdram, source + 72) != 0xFF1001A7U ||
        get(rdram, source + 76) != 0x00700000U ||
        get(rdram, source + 88) != 0xF662C278U ||
        get(rdram, source + 92) != 0x003F80D4U || get(rdram, source + 100) != 0) return;
    // Read the user's loaded commands, excluding END. The shared ROM data is
    // never modified or embedded here. The IPS-selected course bank already
    // uses a 424-wide depth image at 0x700000 and clears X254..395. Extend only
    // its left edge; the original bank remains in the ROM but is not loaded.
    for (uint32_t i = 0; i < frame.depth.size(); ++i) frame.depth[i] = get(rdram, source + i * 4);
    frame.depth[23] = 0x002580D4U; // Left150 instead of254, same Y53.
    frame.ready = true;
}

extern "C" void wr64_course_preview_map_begin(uint8_t* rdram, uint32_t cursor) {
    frame.applied = false;
    frame.map = 0;
    if (!frame.ready || frame.rdram != rdram || !eligible(rdram) ||
        cursor != frame.start + 16 || !room(cursor, MapBytes + ExtraBytes)) return;
    frame.map = cursor;
}

extern "C" uint32_t wr64_course_preview_map_end(uint8_t* rdram, uint32_t cursor) {
    if (!frame.ready || frame.rdram != rdram || !frame.map || !eligible(rdram) ||
        cursor != frame.map + MapBytes || !room(frame.map, MapBytes + ExtraBytes)) return cursor;
    std::array<uint32_t, 42> native{};
    for (uint32_t i = 0; i < native.size(); ++i) native[i] = get(rdram, frame.map + i * 4);
    constexpr std::array<uint8_t, 21> opcodes{0x06,0xE7,0xFF,0xB4,0x01,0x01,0x03,0x06,0xFB,0xED,
        0x06,0xB6,0x06,0xB7,0xE7,0xB9,0x06,0xB6,0x06,0xE7,0xED};
    for (uint32_t i = 0; i < opcodes.size(); ++i)
        if (native[i * 2] >> 24 != opcodes[i]) return cursor;
    if (native[1] != 0x080A6E00U || native[4] != 0xFF1001A7U ||
        native[12] != 0x03800010U || native[13] != 0x0106F738U ||
        native[18] != 0xED3F80D4U || native[19] != 0x0063027CU ||
        get(rdram, frame.start) != 0x06000000U || get(rdram, frame.start + 4) != 0x080A6DB0U ||
        get(rdram, frame.start + 8) != 0xF662C278U || get(rdram, frame.start + 12) != 0x003F80D4U) return cursor;

    // Complete the rewrite locally before changing any emitted commands. The
    // map, depth clear, backing and subsequent UI either all use the new layout
    // or all retain the old one. Each native task owns its command-buffer copy.
    std::array<uint32_t, (MapBytes + ExtraBytes) / 4> output{};
    uint32_t index = 0;
    auto append = [&](uint32_t high, uint32_t low) { output[index++] = high; output[index++] = low; };
    for (uint32_t i = 0; i < 12; ++i)
        append(frame.depth[i * 2], frame.depth[i * 2 + 1]);
    for (uint32_t i = 1; i < 21; ++i) {
        if (i == 6) {
            append(0x00525464U, 0x10000064U);
            append(0x64000007U, 0x00000800U);
            append(uint32_t(uint16_t(-Shift * 4)) << 16, 0);
        }
        append(i == 9 ? 0xED2580D4U : native[i * 2], native[i * 2 + 1]);
        if (i == 6) {
            append(0x64000007U, 0x00000800U);
            append(0, 0);
        }
    }
    for (uint32_t i = 0; i < output.size(); ++i) put(rdram, frame.map + i * 4, output[i]);
    put(rdram, frame.start + 12, 0x002580D4U);
    frame.applied = true;
    return cursor + ExtraBytes;
}

extern "C" int32_t wr64_course_preview_x(int32_t original) {
    return frame.applied ? int32_t(SUB32(original, Shift)) : original;
}
extern "C" uint32_t wr64_course_preview_rect_x(uint32_t original) {
    return frame.applied ? original - (uint32_t(Shift) << 14) : original;
}

extern "C" void wr64_course_preview_mask(uint8_t* rdram, uint32_t cursor) {
    if (!frame.applied || frame.rdram != rdram || !room(cursor, 8)) return;
    const uint32_t high = get(rdram, cursor), low = get(rdram, cursor + 4);
    if ((high >> 24) != 0xF6) return;
    const int32_t left = (low >> 14) & 0x3FF, end = ((high >> 14) & 0x3FF) + 1;
    if (left < OldLeft || left > Right || end < left || end > Right) return;
    auto edge = [](int32_t x) { return Left + ((x - OldLeft) * (Right - Left) + (Right - OldLeft) / 2) / (Right - OldLeft); };
    // Affine remap of the existing animated rectangle, including empty width.
    // Preserve its Y fields and all six native open/close ticks and globals.
    put(rdram, cursor, (high & ~0x00FFC000U) | (uint32_t(edge(end) - 1) << 14));
    put(rdram, cursor + 4, (low & ~0x00FFC000U) | (uint32_t(edge(left)) << 14));
}

extern "C" void wr64_course_preview_finish(uint8_t* rdram, uint32_t cursor) {
    static const char* path = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_COURSE_PREVIEW_TRACE"));
    static bool header = false;
    static uint32_t count = 0;
    if (path && *path && frame.rdram == rdram && count < 20000) {
        if (std::FILE* file = std::fopen(path, header ? "a" : "w")) {
            if (!header) { std::fprintf(file, "frame,applied,players,pool,start,map,end,used,remaining\n"); header = true; }
            const int64_t used = int64_t(cursor) - frame.pool;
            std::fprintf(file, "%u,%d,%d,%08X,%08X,%08X,%08X,%lld,%lld\n", count++, frame.applied,
                int(MEM_H(0, S32(0x801CE60C))), frame.pool, frame.start, frame.map, cursor,
                static_cast<long long>(used), static_cast<long long>(PoolBytes - used));
            std::fclose(file);
        }
    }
    frame = {};
}
