#include "wr64_diagnostic_policy.h"
#include "wr64_championship_preview.h"

#include <array>
#include <cstdio>
#include <cstdlib>

namespace {
constexpr uint32_t RdramBytes = 0x800000, PoolBytes = 0x6000;
constexpr uint32_t ExtraBytes = 536, TailReserve = 0x800;
struct Frame {
    uint8_t* rdram = nullptr;
    uint32_t pool = 0, start = 0, segment1 = 0, segment8 = 0;
    bool ready = false;
    const char* status = "inactive";
    std::array<uint32_t, 104> border{};
    std::array<uint32_t, 24> depth{};
};
thread_local Frame frame;

uint32_t get(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
void put(uint8_t* rdram, uint32_t address, uint32_t value) { MEM_W(0, S32(address)) = value; }
bool enabled() {
    static const bool value = [] {
        const char* setting = std::getenv("WR64_CHAMPIONSHIP_PREVIEW");
        return !(setting && setting[0] == '0' && setting[1] == '\0');
    }();
    return value;
}
bool eligible(uint8_t* rdram) {
    const uint32_t mode = get(rdram, 0x800DAB24);
    return enabled() && get(rdram, 0x801CE638) == 8 && (mode == 30 || mode == 31) &&
        MEM_H(0, S32(0x801CE60C)) == 1 && get(rdram, 0x802C7028) == 1 &&
        get(rdram, 0x80223938) != 0;
}
bool room(uint32_t cursor, uint32_t bytes) {
    return (cursor & 7) == 0 && cursor >= frame.pool &&
        cursor - frame.pool <= PoolBytes && bytes <= PoolBytes - (cursor - frame.pool);
}
uint32_t finish(uint32_t cursor, const char* status) {
    static const char* path = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_CHAMPIONSHIP_PREVIEW_TRACE"));
    static bool header = false;
    static uint32_t count = 0;
    if (path && *path && frame.rdram && count < 20000) {
        if (std::FILE* file = std::fopen(path, header ? "a" : "w")) {
            if (!header) {
                std::fprintf(file, "frame,status,state,mode,pool,start,end,used,remaining\n");
                header = true;
            }
            const int64_t used = int64_t(cursor) - frame.pool;
            std::fprintf(file, "%u,%s,%u,%u,%08X,%08X,%08X,%lld,%lld\n", count++, status,
                get(frame.rdram, 0x801CE638), get(frame.rdram, 0x800DAB24), frame.pool,
                frame.start, cursor, static_cast<long long>(used), static_cast<long long>(PoolBytes - used));
            std::fclose(file);
        }
    }
    frame = {};
    return cursor;
}
}

extern "C" void wr64_championship_preview_prepare(uint8_t* rdram, uint32_t cursor) {
    frame = {};
    if (!rdram) return;
    frame.rdram = rdram;
    frame.start = cursor;
    frame.pool = get(rdram, 0x801518B8);
    if (!eligible(rdram)) return;
    frame.status = "buffer";
    if ((frame.pool & 0xE0000007U) != 0x80000000U ||
        (frame.pool & 0x1FFFFFFFU) > RdramBytes - PoolBytes || !room(cursor, 0x1000)) return;

    frame.status = "segments";
    frame.segment1 = get(rdram, 0x801CE6B4);
    frame.segment8 = get(rdram, 0x801CE6D0);
    if ((frame.segment1 & 7) || (frame.segment8 & 7) ||
        frame.segment1 > RdramBytes - 0x6F738 || frame.segment8 > RdramBytes - 0x4E628) return;

    frame.status = "viewport";
    const uint32_t viewport = 0x80000000U + frame.segment1 + 0x6F728;
    constexpr std::array<uint32_t, 4> viewportWords{0x028001E0,0x01FF0000,0x01A401CC,0x01FF0000};
    for (uint32_t i = 0; i < viewportWords.size(); ++i)
        if (get(rdram, viewport + i * 4) != viewportWords[i]) return;

    // Fingerprints follow the IPS-selected bank at descriptor ROM 0x972A4.
    // Only command metadata is authored here: texture data and lists come
    // from the user's loaded ROM, and the shared bank is never changed.
    frame.status = "depth";
    const uint32_t depth = 0x80000000U + frame.segment8 + 0x4E418;
    constexpr std::array<uint8_t, 13> depthOps{0x03,0xB6,0xB7,0xBB,0xE7,0xBA,0xFC,0xB9,0xFE,0xFF,0xF7,0xF6,0xB8};
    for (uint32_t i = 0; i < depthOps.size(); ++i)
        if (get(rdram, depth + i * 8) >> 24 != depthOps[i]) return;
    if (get(rdram, depth + 4) != 0x0804E408U || get(rdram, depth + 68) != 0x00700000U ||
        get(rdram, depth + 72) != 0xFF1001A7U || get(rdram, depth + 76) != 0x00700000U ||
        get(rdram, depth + 88) != 0xF62CC298U || get(rdram, depth + 92) != 0x0007C0FCU ||
        get(rdram, depth + 96) != 0xB8000000U || get(rdram, depth + 100) != 0) return;
    for (uint32_t i = 0; i < frame.depth.size(); ++i) frame.depth[i] = get(rdram, depth + i * 4);
    frame.depth[22] = 0xF646C298U; // Clear inclusive right edge 179 -> 283.

    frame.status = "border";
    const uint32_t border = 0x80000000U + frame.segment8 + 0x4E4E0;
    constexpr std::array<uint32_t, 4> textures{0x08047008,0x080473B8,0x08047768,0x080479E0};
    constexpr std::array<uint32_t, 4> rectHigh{0xE42E00FC,0xE42E02A8,0xE507C29C,0xE52DC29C};
    constexpr std::array<uint32_t, 4> rectLow{0x000700F0,0x0007029C,0x000700FC,0x002D00FC};
    for (uint32_t strip = 0; strip < 4; ++strip) {
        const bool horizontal = strip < 2;
        const uint32_t base = border + strip * 80;
        const std::array<uint8_t, 10> ops{0xFD,0xF5,0xE6,uint8_t(horizontal ? 0xF4 : 0xF3),
            0xE7,0xF5,0xF2,uint8_t(horizontal ? 0xE4 : 0xE5),0xB3,0xB2};
        for (uint32_t i = 0; i < ops.size(); ++i)
            if (get(rdram, base + i * 8) >> 24 != ops[i]) return;
        if (get(rdram, base + 4) != textures[strip] || get(rdram, base + 56) != rectHigh[strip] ||
            get(rdram, base + 60) != rectLow[strip] || get(rdram, base + 64) != 0xB3000000U ||
            get(rdram, base + 68) != (horizontal ? 0U : 0x0CE00000U) ||
            get(rdram, base + 72) != 0xB2000000U ||
            get(rdram, base + 76) != (horizontal ? 0x04000400U : 0xFC000400U)) return;
    }
    if (get(rdram, border + 320) != 0xB8000000U || get(rdram, border + 324) != 0) return;
    uint32_t used = 0;
    auto append = [&](uint32_t hi, uint32_t lo) { frame.border[used++] = hi; frame.border[used++] = lo; };
    for (uint32_t strip = 0; strip < 4; ++strip) {
        const uint32_t base = border + strip * 80;
        if (strip < 2) {
            // Load the original texture once. Its four-pixel endcaps include
            // the bevel and transparent outer column; stretching those moves
            // the corner inward relative to the unscaled vertical border.
            for (uint32_t command = 0; command < 7; ++command)
                append(get(rdram, base + command * 8), get(rdram, base + command * 8 + 4));
            auto slice = [&](uint32_t left, uint32_t right, uint32_t s, uint32_t step) {
                append((rectHigh[strip] & ~0x00FFF000U) | (right * 4U << 12),
                    (rectLow[strip] & ~0x00FFF000U) | (left * 4U << 12));
                append(0xB3000000U, s * 32U << 16);
                append(0xB2000000U, (step << 16) | 0x0400U);
            };
            slice(28, 32, 0, 1024);
            slice(32, 284, 4, 601); // round(1024 * 148 / 252): stretch only the middle.
            slice(284, 288, 152, 1024);
        } else {
            // Vertical strips keep their three-pixel width and UV direction.
            for (uint32_t command = 0; command < 10; ++command) {
                const bool rightRectangle = strip == 3 && command == 7;
                append(rightRectangle ? 0xE547C29CU : get(rdram, base + command * 8),
                    rightRectangle ? 0x004700FCU : get(rdram, base + command * 8 + 4));
            }
        }
    }
    if (used != frame.border.size()) return;
    frame.ready = true;
    frame.status = "ready";
}

extern "C" uint32_t wr64_championship_preview_finish(uint8_t* rdram, uint32_t cursor) {
    if (!frame.ready || frame.rdram != rdram) return finish(cursor, frame.status);
    if (!eligible(rdram) || frame.pool != get(rdram, 0x801518B8) ||
        frame.segment1 != get(rdram, 0x801CE6B4) || frame.segment8 != get(rdram, 0x801CE6D0))
        return finish(cursor, "scope-changed");
    if (cursor <= frame.start || !room(cursor, ExtraBytes + TailReserve)) return finish(cursor, "capacity");

    // The native builder has variable map/opacity branches. Find its exact
    // targets in the complete output, retaining all other commands verbatim.
    constexpr std::array<uint32_t, 5> high{0x06000000,0xF62D42A0,0x06000000,0x03800010,0xED07C0FC};
    constexpr std::array<uint32_t, 5> low{0x0804E4E0,0x0007C0FC,0x0804E418,0x0106F728,0x002D029C};
    std::array<uint32_t, 5> found{}, counts{};
    for (uint32_t at = frame.start; at < cursor; at += 8) {
        const uint32_t hi = get(rdram, at), lo = get(rdram, at + 4);
        // The audited builder calls static/segmented lists only. Refuse an
        // unexpected in-buffer call rather than relocate a possible branch.
        if (hi >> 24 == 0x06 && ((lo & 0xE0000000U) == 0x80000000U || lo < RdramBytes)) {
            const uint32_t target = 0x80000000U | (lo & 0x1FFFFFFFU);
            if (target >= frame.start && target < cursor) return finish(cursor, "internal-call");
        }
        for (uint32_t i = 0; i < high.size(); ++i) {
            if (hi == high[i] && lo == low[i]) { found[i] = at; ++counts[i]; }
        }
    }
    for (uint32_t i = 0; i < found.size(); ++i)
        if (counts[i] != 1 || (i && found[i] <= found[i - 1])) return finish(cursor, "commands");
    if (found[3] != found[2] + 6 * 8 || found[4] != found[2] + 9 * 8 ||
        get(rdram, found[2] + 16) != 0xFF1001A7U ||
        get(rdram, found[3] + 8) != 0x06000000U || get(rdram, found[3] + 12) != 0x0106F748U ||
        get(rdram, cursor - 8) != 0xED000000U || get(rdram, cursor - 4) != 0x0069C3BCU)
        return finish(cursor, "map-tail");

    // Commit only after validating and constructing the whole replacement.
    // The frame, backing, depth clear and map either all expand, or none do.
    std::array<uint32_t, PoolBytes / 4> output{};
    uint32_t used = 0;
    auto append = [&](uint32_t hi, uint32_t lo) { output[used++] = hi; output[used++] = lo; };
    for (uint32_t at = frame.start; at < cursor; at += 8) {
        if (at == found[0] || at == found[2]) {
            const auto* words = at == found[0] ? frame.border.data() : frame.depth.data();
            const uint32_t size = at == found[0] ? uint32_t(frame.border.size()) : uint32_t(frame.depth.size());
            for (uint32_t i = 0; i < size; i += 2) append(words[i], words[i + 1]);
        } else {
            if (at == found[3]) {
                append(0x00525464U, 0x10000064U);
                append(0x64000007U, 0x00000800U);
                append(0x00D00000U, 0); // Viewport center X105 ->157 (+52*4).
            }
            append(at == found[1] ? 0xF64742A0U : get(rdram, at),
                at == found[4] ? 0x0047029CU : get(rdram, at + 4));
            if (at == found[3]) {
                append(0x64000007U, 0x00000800U);
                append(0, 0);
            }
        }
    }
    if (used * 4 != cursor - frame.start + ExtraBytes) return finish(cursor, "size");
    for (uint32_t i = 0; i < used; ++i) put(rdram, frame.start + i * 4, output[i]);
    return finish(cursor + ExtraBytes, "applied");
}
