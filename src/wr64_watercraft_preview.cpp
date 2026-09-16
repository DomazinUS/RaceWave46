#include "wr64_diagnostic_policy.h"
#include "wr64_watercraft_preview.h"

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" void func_801E9B04(uint8_t* rdram, recomp_context* ctx);

namespace {
constexpr uint32_t Viewport = 0x800DA8F0;
constexpr uint32_t WatercraftCoverageList = 0x080BE500;
constexpr uint32_t ChangeNameCoverageList = 0x08062290;
constexpr uint32_t PoolBytes = 0x6000;
constexpr uint32_t NativeRdramBytes = 0x800000;
constexpr int32_t PreviewExtension = 104; // USA menu plane 424 minus original 320.

// Native display-list production runs on one game thread. The render thread
// receives complete commands in the game's own alternating task buffers; it
// never reads these preparation flags or a shared mutable viewport copy.
struct Frame {
    uint8_t* rdram = nullptr;
    uint32_t state = 0, coverageList = 0;
    uint32_t pool = 0;
    uint32_t start = 0;
    uint32_t viewportCursor = 0;
    uint32_t coverageCursor = 0;
    bool ready = false;
    bool applied = false;
    bool coverageApplied = false;
    std::array<uint32_t, 20> coverage{};
};
thread_local Frame frame;

// Both live VS previews are drawn before either caption or cleanup list.
// Track their application separately; the second view must not overwrite the
// first view's eligibility, and tuning/confirmation may omit either scene.
struct PairFrame {
    uint8_t* rdram = nullptr;
    uint32_t pool = 0;
    bool ready = false;
    std::array<bool, 2> applied{}, covered{};
    std::array<std::array<uint32_t, 20>, 2> coverage{};
};
thread_local PairFrame pairFrame;
constexpr std::array<uint32_t, 2> PairViewports{0x800DA900, Viewport};
constexpr std::array<uint32_t, 2> PairCoverageLists{0x080BE4A8, WatercraftCoverageList};
// The native title frame spans [28,396) on the 424-wide menu plane.
// Equal panels share those outer edges and leave a centered four-pixel gap.
constexpr std::array<int32_t, 2> PairLeft{28, 214};
constexpr std::array<int32_t, 2> PairRight{210, 396};
constexpr std::array<int32_t, 2> PairNativeCenters{92, 330};
constexpr std::array<int32_t, 2> PairCaptionFallbackShift{29, -25};

uint32_t get(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
void put(uint8_t* rdram, uint32_t address, uint32_t value) { MEM_W(0, S32(address)) = value; }
bool featureEnabled(const char* name) {
    const char* setting = std::getenv(name);
    return !(setting && setting[0] == '0' && setting[1] == '\0');
}
bool enabled(uint32_t state) {
    static const bool watercraft = featureEnabled("WR64_WATERCRAFT_PREVIEW");
    static const bool changeName = featureEnabled("WR64_CHANGE_NAME_PREVIEW");
    return state == 4 ? watercraft : state == 10 && changeName;
}
bool eligible(uint8_t* rdram) {
    return enabled(frame.state) && get(rdram, 0x801CE638) == frame.state &&
        MEM_H(0, S32(0x801CE60C)) == 1;
}
bool room(uint32_t cursor, uint32_t bytes) {
    return (cursor & 7) == 0 && cursor >= frame.pool &&
        cursor - frame.pool <= PoolBytes && bytes <= PoolBytes - (cursor - frame.pool);
}
uint32_t fillWord(int32_t x, int32_t y) {
    return (uint32_t(x * 4) << 12) | uint32_t(y * 4);
}
void command(uint8_t* rdram, uint32_t cursor, uint32_t high, uint32_t low) {
    put(rdram, cursor, high);
    put(rdram, cursor + 4, low);
}
bool pairEligible(uint8_t* rdram) {
    return pairFrame.ready && pairFrame.rdram == rdram && enabled(4) &&
        get(rdram, 0x801CE638) == 4 && MEM_H(0, S32(0x801CE60C)) == 2;
}
bool pairRoom(uint32_t cursor, uint32_t bytes) {
    return (cursor & 7) == 0 && cursor >= pairFrame.pool &&
        cursor - pairFrame.pool <= PoolBytes && bytes <= PoolBytes - (cursor - pairFrame.pool);
}
void preparePair(uint8_t* rdram, uint32_t cursor) {
    pairFrame = {};
    if (!enabled(4) || get(rdram, 0x801CE638) != 4 || MEM_H(0, S32(0x801CE60C)) != 2) return;
    pairFrame.pool = get(rdram, 0x801518B8);
    if ((pairFrame.pool & 0xE0000000U) != 0x80000000U ||
        (pairFrame.pool & 0x1FFFFFFFU) > NativeRdramBytes - PoolBytes || !pairRoom(cursor, 0x800)) return;
    const uint32_t base = get(rdram, 0x801CE6D0);
    const std::array<uint8_t, 11> opcodes{0xE7, 0xBA, 0xBA, 0xB9, 0xFC, 0xB9, 0xF7, 0xF6, 0xF6, 0xF6, 0xB8};
    for (uint32_t player = 0; player < 2; ++player) {
        if (get(rdram, PairViewports[player]) != 0x035001E0U ||
            get(rdram, PairViewports[player] + 8) != (player == 0 ? 0x01700270U : 0x05280270U)) return;
        const uint32_t offset = PairCoverageLists[player] & 0x00FFFFFFU;
        if (base > NativeRdramBytes - offset - 88) return;
        const uint32_t source = 0x80000000U + base + offset;
        for (size_t i = 0; i < opcodes.size(); ++i) {
            if ((get(rdram, source + uint32_t(i * 8)) >> 24) != opcodes[i]) return;
        }
        // The coverage lists use the original 320-wide asset coordinates.
        // P2's native IPS scene/caption is already anchored104pixels right.
        const int32_t left = player == 0 ? 26 : 160;
        const int32_t right = player == 0 ? 155 : 289;
        const std::array<std::array<int32_t, 4>, 3> rectangles{{
            {left, 96, left + 2, 216}, {right, 96, right + 2, 216}, {left + 1, 214, right + 2, 216}
        }};
        for (size_t i = 0; i < rectangles.size(); ++i) {
            const auto& r = rectangles[i];
            if (get(rdram, source + 56 + uint32_t(i * 8)) != (0xF6000000U | fillWord(r[2], r[3])) ||
                get(rdram, source + 60 + uint32_t(i * 8)) != fillWord(r[0], r[1])) return;
        }
        if (get(rdram, source + 80) != 0xB8000000U || get(rdram, source + 84) != 0) return;
        auto& coverage = pairFrame.coverage[player];
        for (size_t i = 0; i < coverage.size(); ++i) coverage[i] = get(rdram, source + uint32_t(i * 4));
        const int32_t newLeft = PairLeft[player] - 1;
        const int32_t newRight = PairRight[player] - 1;
        coverage[14] = 0xF6000000U | fillWord(newLeft + 2, 216);
        coverage[15] = fillWord(newLeft, 96);
        coverage[16] = 0xF6000000U | fillWord(newRight + 2, 216);
        coverage[17] = fillWord(newRight, 96);
        coverage[18] = 0xF6000000U | fillWord(newRight + 2, 216);
        coverage[19] = fillWord(newLeft + 1, 214);
    }
    pairFrame.rdram = rdram;
    pairFrame.ready = true;
}
void prepare(uint8_t* rdram, uint32_t cursor, uint32_t state, uint32_t coverageList) {
    frame = {};
    frame.state = state;
    frame.coverageList = coverageList;
    if (!eligible(rdram)) return;
    frame.rdram = rdram;
    frame.start = cursor;
    frame.pool = get(rdram, 0x801518B8);
    const uint32_t physicalPool = frame.pool & 0x1FFFFFFF;
    if ((frame.pool & 0xE0000000U) != 0x80000000U ||
        physicalPool > NativeRdramBytes - PoolBytes || !room(cursor, 0x800)) return;

    // Only the verified USA preview viewport is eligible. Its 424x240 scale
    // already covers a wider scene than the 129-pixel crop. Preserve that scale,
    // projection, vertical FOV, camera motion, and the original viewport bytes.
    if (get(rdram, Viewport) != 0x035001E0U ||
        get(rdram, Viewport + 8) != 0x05280270U) return;

    // Resolve the existing loaded USA display list through the native CPU
    // segment-8 table. Read its state from the user's ROM at runtime; no asset
    // or cartridge display-list implementation is embedded in the executable.
    const uint32_t base = get(rdram, 0x801CE6D0);
    const uint32_t offset = coverageList & 0x00FFFFFFU;
    if (base > NativeRdramBytes - offset - 88) return;
    const uint32_t source = 0x80000000U + base + offset;
    const std::array<uint8_t, 11> opcodes{0xE7, 0xBA, 0xBA, 0xB9, 0xFC, 0xB9, 0xF7, 0xF6, 0xF6, 0xF6, 0xB8};
    for (size_t i = 0; i < opcodes.size(); ++i) {
        if ((get(rdram, source + uint32_t(i * 8)) >> 24) != opcodes[i]) return;
    }
    const std::array<std::array<int32_t, 4>, 3> rectangles{{
        {160, 96, 162, 216}, {289, 96, 291, 216}, {161, 214, 291, 216}
    }};
    for (size_t i = 0; i < rectangles.size(); ++i) {
        const auto& r = rectangles[i];
        if (get(rdram, source + 56 + uint32_t(i * 8)) != (0xF6000000U | fillWord(r[2], r[3])) ||
            get(rdram, source + 60 + uint32_t(i * 8)) != fillWord(r[0], r[1])) return;
    }
    if (get(rdram, source + 80) != 0xB8000000U || get(rdram, source + 84) != 0) return;
    for (size_t i = 0; i < frame.coverage.size(); ++i) frame.coverage[i] = get(rdram, source + uint32_t(i * 4));
    // The left strip already meets the restored left edge. Move the right
    // strip and extend the bottom strip to the existing USA preview right edge.
    frame.coverage[16] = 0xF6000000U | fillWord(291 + PreviewExtension, 216);
    frame.coverage[17] = fillWord(289 + PreviewExtension, 96);
    frame.coverage[18] = 0xF6000000U | fillWord(291 + PreviewExtension, 216);
    frame.ready = true;
}
}

extern "C" void wr64_watercraft_preview_prepare(uint8_t* rdram, uint32_t cursor) {
    preparePair(rdram, cursor);
    prepare(rdram, cursor, 4, WatercraftCoverageList);
}

extern "C" void wr64_change_name_preview_prepare(uint8_t* rdram, uint32_t cursor) {
    pairFrame = {};
    prepare(rdram, cursor, 10, ChangeNameCoverageList);
}

extern "C" void wr64_two_player_preview_viewport(uint8_t* rdram, recomp_context* ctx, uint32_t player) {
    if (player >= 2 || !pairEligible(rdram) || get(rdram, 0x800DAB2C) != player ||
        uint32_t(ctx->r24) != PairViewports[player]) return;
    pairFrame.applied[player] = false;
    const uint32_t cursor = uint32_t(ctx->r4);
    if (uint32_t(ctx->r5) != cursor + 8 || uint32_t(ctx->r6) != cursor + 8 || !pairRoom(cursor, 0x800)) return;
    // Center the unchanged scene projection within each panel. RT64 uses
    // quarter-pixel viewport offsets: the new centers are119 and305.
    const int32_t offset = (PairLeft[player] + PairRight[player]) * 2 - PairNativeCenters[player] * 4;
    command(rdram, cursor, 0x00525464U, 0x10000064U);
    command(rdram, cursor + 8, 0x64000007U, 0x00000800U);
    command(rdram, cursor + 16, uint32_t(uint16_t(offset)) << 16, 0);
    command(rdram, cursor + 32, 0x64000007U, 0x00000800U);
    command(rdram, cursor + 40, 0, 0);
    ctx->r4 = S32(cursor + 24);
    ctx->r5 = S32(cursor + 48);
    ctx->r6 = S32(cursor + 48);
    pairFrame.applied[player] = true;
}

extern "C" void wr64_two_player_preview_scissor(uint8_t* rdram, recomp_context* ctx, uint32_t player) {
    if (player >= 2 || !pairEligible(rdram) || !pairFrame.applied[player] || get(rdram, 0x800DAB2C) != player) return;
    const uint32_t high = player == 0 ? 0xED060180U : 0xED424180U;
    const uint32_t low = player == 0 ? 0x0027035CU : 0x0062835CU;
    if (uint32_t(ctx->r14) != high || uint32_t(ctx->r15) != low) return;
    ctx->r14 = S32(0xED000000U | fillWord(PairLeft[player], 96));
    ctx->r15 = S32(fillWord(PairRight[player], 215));
}

extern "C" void wr64_two_player_preview_coverage(uint8_t* rdram, recomp_context* ctx, uint32_t player) {
    if (player >= 2 || !pairEligible(rdram) || !pairFrame.applied[player] || pairFrame.covered[player] ||
        get(rdram, 0x802C8C58 + player * 4) != 0) return;
    const uint32_t cursor = uint32_t(ctx->r2);
    if (uint32_t(ctx->r16) != cursor + 8 || !pairRoom(cursor, 8) || get(rdram, cursor) != 0x06000000U ||
        get(rdram, cursor + 4) != PairCoverageLists[player]) return;
    if (!pairRoom(cursor, 88)) {
        // Omit old edge strips if the enlarged cleanup cannot fit, as in1P.
        command(rdram, cursor, 0xE7000000U, 0);
        pairFrame.covered[player] = true;
        return;
    }
    const auto& coverage = pairFrame.coverage[player];
    for (size_t i = 0; i < coverage.size(); ++i) put(rdram, cursor + uint32_t(i * 4), coverage[i]);
    ctx->r16 = S32(cursor + 80);
    pairFrame.covered[player] = true;
}

extern "C" void wr64_watercraft_preview_viewport(uint8_t* rdram, recomp_context* ctx) {
    frame.applied = false;
    if (!eligible(rdram) || !frame.ready || frame.rdram != rdram || uint32_t(ctx->r24) != Viewport) return;
    const uint32_t cursor = uint32_t(ctx->r4);
    if (uint32_t(ctx->r5) != cursor + 8 || uint32_t(ctx->r6) != cursor + 8 || !room(cursor, 0x800)) {
        frame.ready = false;
        return;
    }
    // Standard RT64 viewport alignment applies when the following native
    // viewport loads. Reset the alignment immediately afterward: the loaded
    // preview keeps its new center while all later viewport loads stay normal.
    // Only 40 additional bytes, with no borrowed native matrix or asset storage.
    command(rdram, cursor, 0x00525464U, 0x10000064U);
    command(rdram, cursor + 8, 0x64000007U, 0x00000800U);
    command(rdram, cursor + 16, uint32_t(uint16_t(-PreviewExtension * 2)) << 16, 0);
    // Native instructions write the original viewport command into cursor+24.
    command(rdram, cursor + 32, 0x64000007U, 0x00000800U);
    command(rdram, cursor + 40, 0, 0);
    ctx->r4 = S32(cursor + 24);
    ctx->r5 = S32(cursor + 48);
    ctx->r6 = S32(cursor + 48);
    frame.viewportCursor = cursor;
    frame.applied = true;
}

extern "C" uint32_t wr64_watercraft_preview_scissor(uint32_t original) {
    return frame.applied && original == 0xED424180U ? 0xED284180U : original;
}

namespace {
bool captionOrigin(uint8_t* rdram, recomp_context* ctx, int32_t& origin, int32_t panelLeft = 161, int32_t panelRight = 394) {
    const uint32_t stack = uint32_t(ctx->r29);
    if ((stack & 0xE0000003U) != 0x80000000U ||
        (stack & 0x1FFFFFFFU) > NativeRdramBytes - 8) return false;
    if (MEM_H(0, S32(0x80226E28)) != 0 || get(rdram, 0x80228A44) == 2) return false;
    const uint32_t name = uint32_t(ctx->r6);
    constexpr uint32_t NameBytes = 11; // Ten editable characters plus terminator.
    if ((name & 0xE0000000U) != 0x80000000U ||
        (name & 0x1FFFFFFFU) > NativeRdramBytes - NameBytes) return false;
    constexpr uint32_t GlyphOffset = 0x387C0;
    constexpr uint32_t GlyphCount = 42;
    const uint32_t segment = get(rdram, 0x801CE6B4);
    if (segment > NativeRdramBytes - GlyphOffset - GlyphCount * 64) return false;
    const uint32_t glyphBase = 0x80000000U + segment + GlyphOffset;

    // Measure the actual visible ink, including baked outlines, rather than
    // fixed character cells. Read the font advances and IA8 alpha from the
    // user's loaded USA data; no font assets or copied tables are embedded.
    int32_t pen = 0, left = 0, right = 0;
    bool ink = false;
    recomp_context converter{};
    converter.r29 = ctx->r29;
    for (uint32_t i = 0; i < NameBytes; ++i) {
        const uint8_t character = MEM_BU(0, S32(name + i));
        if (character == 0) {
            if (ink) {
                // Round the visible ink's centered origin to the nearest native
                // pixel in the requested panel. Menu coordinates are aspect-stable.
                origin = (panelLeft + panelRight - left - right + 1) / 2;
            }
            return ink;
        }
        if (i == NameBytes - 1) return false;
        converter.r4 = 1;
        converter.r5 = int8_t(character);
        // Reuse the existing native ASCII converter. Its sole memory write is
        // the a1 spill at sp+4; restore it and keep all caller registers intact.
        const uint32_t argument = MEM_W(4, ctx->r29);
        func_801E9B04(rdram, &converter);
        MEM_W(4, ctx->r29) = argument;
        const uint32_t code = uint32_t(converter.r2);
        if (code == 255) { pen += 8; continue; }
        if (code >= GlyphCount) return false;
        const uint32_t advance = MEM_BU(0, S32(0x80226D98U + code));
        if (advance == 0 || advance > 8) return false;
        for (uint32_t pixel = 0; pixel < 64; ++pixel) {
            if ((MEM_BU(0, S32(glyphBase + code * 64 + pixel)) & 15) == 0) continue;
            const int32_t x = pen + int32_t(pixel % 8);
            if (!ink || x < left) left = x;
            if (!ink || x + 1 > right) right = x + 1;
            ink = true;
        }
        pen += int32_t(advance);
    }
    return false;
}
}

extern "C" void wr64_watercraft_preview_name(uint8_t* rdram, recomp_context* ctx) {
    if (pairEligible(rdram) && ctx->r5 == 1) {
        const uint32_t stack = uint32_t(ctx->r29);
        if ((stack & 0xE0000003U) != 0x80000000U ||
            (stack & 0x1FFFFFFFU) > NativeRdramBytes - 0xE0) return;
        const uint32_t tag = MEM_W(0xDC, ctx->r29);
        if (tag != 19 && tag != 257) return;
        const uint32_t player = tag == 19 ? 0 : 1;
        if (!pairFrame.applied[player] || get(rdram, 0x802C8C58 + player * 4) != 0) return;
        // Alternate fonts retain their native placement relative to the crop
        // midpoint, rounded to a whole pixel. The normal font uses visible ink.
        int32_t origin = ADD32(MEM_W(0xD8, ctx->r29), PairCaptionFallbackShift[player]);
        captionOrigin(rdram, ctx, origin, PairLeft[player], PairRight[player]);
        MEM_W(0xD8, ctx->r29) = origin;
        return;
    }
    if (frame.state != 4 || !frame.applied || frame.rdram != rdram || !eligible(rdram) || ctx->r5 != 1) return;
    const uint32_t stack = uint32_t(ctx->r29);
    if ((stack & 0xE0000003U) != 0x80000000U ||
        (stack & 0x1FFFFFFFU) > NativeRdramBytes - 0xDC) return;

    // Preserve the accepted Watercraft fallback and its native delay-slot local.
    int32_t origin = SUB32(MEM_W(0xD8, ctx->r29), PreviewExtension / 2);
    captionOrigin(rdram, ctx, origin);
    MEM_W(0xD8, ctx->r29) = origin;
}

extern "C" void wr64_change_name_preview_name(uint8_t* rdram, recomp_context* ctx) {
    // The scoped i8 caption delay slot adds the original X284 to this offset.
    // All keyboard/input-name calls keep their native arguments and behavior.
    ctx->r7 = 0;
    if (frame.state != 10 || !frame.applied || frame.rdram != rdram || !eligible(rdram) || ctx->r5 != 1) return;
    int32_t origin = 284 - PreviewExtension / 2;
    captionOrigin(rdram, ctx, origin);
    ctx->r7 = S32(origin - 284);
}

extern "C" uint32_t wr64_watercraft_preview_coverage(uint8_t* rdram, uint32_t cursor) {
    if (!frame.applied || frame.rdram != rdram || !room(cursor, 8) || get(rdram, cursor) != 0x06000000U ||
        get(rdram, cursor + 4) != frame.coverageList) return cursor;
    frame.coverageCursor = cursor;
    if (!room(cursor, 88)) {
        // Keep the expanded scene coherent if only the original command fits.
        // Omit edge cleanup instead of drawing the old strips through its
        // interior. The native caller retains its original cursor advance.
        command(rdram, cursor, 0xE7000000U, 0);
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[watercraft-preview] Insufficient final display-list space\n"));
        return cursor;
    }
    // Inline the loaded list's ten commands, omitting only its END. The main
    // builder's existing +8 advances past the final command. This adds72 bytes
    // and preserves the exact original coverage state and inclusive endpoints.
    for (size_t i = 0; i < frame.coverage.size(); ++i) put(rdram, cursor + uint32_t(i * 4), frame.coverage[i]);
    frame.coverageApplied = true;
    return cursor + 72;
}

extern "C" void wr64_watercraft_preview_finish(uint8_t* rdram, uint32_t cursor) {
    static const char* paths[] = {WR64_DIAGNOSTIC_ENV(std::getenv("WR64_WATERCRAFT_PREVIEW_TRACE")), WR64_DIAGNOSTIC_ENV(std::getenv("WR64_CHANGE_NAME_PREVIEW_TRACE"))};
    static bool headers[2]{};
    static uint32_t sequences[2]{};
    const uint32_t kind = frame.state == 10 ? 1 : 0;
    const char* path = paths[kind];
    bool& headerWritten = headers[kind];
    uint32_t& sequence = sequences[kind];
    if (path && *path && frame.rdram == rdram && sequence < 20000) {
        if (std::FILE* file = std::fopen(path, headerWritten ? "a" : "w")) {
            if (!headerWritten) {
                std::fprintf(file, "frame,applied,state,players,pool,start,viewport,coverage,end,used,remaining,coverage_applied\n");
                headerWritten = true;
            }
            const int64_t used = int64_t(cursor) - frame.pool;
            std::fprintf(file, "%u,%d,%u,%d,%08X,%08X,%08X,%08X,%08X,%lld,%lld,%d\n",
                sequence++, frame.applied, get(rdram, 0x801CE638), int(MEM_H(0, S32(0x801CE60C))),
                frame.pool, frame.start, frame.viewportCursor, frame.coverageCursor, cursor,
                static_cast<long long>(used), static_cast<long long>(PoolBytes - used), frame.coverageApplied);
            std::fclose(file);
        }
    }
    frame = {};
    pairFrame = {};
}
