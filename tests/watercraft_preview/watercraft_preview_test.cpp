#include "recomp.h"
#include "wr64_watercraft_preview.h"
#include "common/rt64_wr64_ultrawide.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <string_view>
#include <vector>

extern "C" void native_caption_string(uint8_t*, recomp_context*);

namespace {
unsigned assertions = 0;
void require(bool condition, const char* reason) {
    ++assertions;
    if (!condition) { std::cerr << reason << '\n'; std::exit(1); }
}
constexpr uint32_t Output = 0x80020000, Stack = 0x80100000;
constexpr uint32_t Segment8 = 0x80300000, Clear = Segment8 + 0xBE500;
constexpr uint32_t PairLeftClear = Segment8 + 0xBE4A8;
constexpr uint32_t Segment1 = 0x80400000, SmallFont = Segment1 + 0x387C0;
using Packet = std::array<uint32_t, 2>;
using Packets = std::vector<Packet>;
using Function = void (*)(uint8_t*, recomp_context*);
Function prefixFunction;
Function pairMenuFunction;
bool changeNameReplay = false;
bool pairMenuReplay = false;
struct Glyph {
    uint32_t type, code;
    int32_t x, y;
    uint32_t scale;
    bool operator==(const Glyph&) const = default;
};
std::vector<Glyph> replayGlyphs;
int32_t replayPen;
struct Call {
    uint32_t kind;
    std::array<uint32_t, 13> args;
    std::vector<Glyph> glyphs;
    int32_t pen = 0;
    bool operator==(const Call&) const = default;
};
std::vector<Call> calls;
void put(uint8_t* rdram, uint32_t address, uint32_t value) { MEM_W(0, S32(address)) = value; }
uint32_t get(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
void emit(uint8_t* rdram, recomp_context* ctx, uint32_t tag) {
    put(rdram, uint32_t(ctx->r4), 0x7F000000 | tag);
    put(rdram, uint32_t(ctx->r4) + 4, 0);
    ctx->r2 = ADD32(ctx->r4, 8);
}
void capture(uint32_t kind, uint8_t* rdram, recomp_context* ctx) {
    Call call{kind, {uint32_t(ctx->r5), uint32_t(ctx->r6), uint32_t(ctx->r7)}};
    // Compare actual arguments, not unused outgoing stack slots containing a
    // preceding call's cursor. Existing Watercraft captures stay unchanged.
    const size_t count = (!changeNameReplay && !pairMenuReplay) || kind == 2 ? 13 : kind == 3 || kind == 11 ? 4 : 5;
    for (size_t i = 3; i < count; ++i) call.args[i] = MEM_W((i + 1) * 4, ctx->r29);
    if (kind == 3) {
        recomp_context replay = *ctx;
        replay.f_odd = &replay.f0.u32h;
        replay.r4 = S32(Output + 0x8000);
        replay.r29 = S32(Stack - 0x1000);
        MEM_W(0x10, replay.r29) = call.args[3];
        replayGlyphs.clear();
        replayPen = int32_t(ctx->r7);
        native_caption_string(rdram, &replay);
        call.glyphs = replayGlyphs;
        call.pen = replayPen;
    }
    calls.push_back(call);
    emit(rdram, ctx, kind);
}
}

extern "C" {
void func_8008FB74(uint8_t*, recomp_context*);
void baseline_func_8008FB74(uint8_t*, recomp_context*);
void regenerated_func_8008FB74(uint8_t*, recomp_context*);
void func_i2_802C70EC(uint8_t*, recomp_context*);
void baseline_func_i2_802C70EC(uint8_t*, recomp_context*);
void regenerated_func_i2_802C70EC(uint8_t*, recomp_context*);
void func_i2_802C5B4C(uint8_t*, recomp_context*);
void baseline_func_i2_802C5B4C(uint8_t*, recomp_context*);
void regenerated_func_i2_802C5B4C(uint8_t*, recomp_context*);
void baseline_func_i2_802C7C50(uint8_t*, recomp_context*);
void native_pair_func_i2_802C7C50(uint8_t*, recomp_context*);
void regenerated_func_i2_802C7C50(uint8_t*, recomp_context*);
void func_i8_802C5D3C(uint8_t*, recomp_context*);
void baseline_func_i8_802C5D3C(uint8_t*, recomp_context*);
void regenerated_func_i8_802C5D3C(uint8_t*, recomp_context*);
uint32_t wr64_experimental_viewport_borders() { return 1; }
void wr64_sunny_sky_cloud_camera(uint8_t*, recomp_context*) {}
void func_8004C998(uint8_t*, recomp_context* ctx) {
    calls.push_back({100, {uint32_t(ctx->r4), uint32_t(ctx->r5)}});
}
void func_8004C1D0(uint8_t*, recomp_context* ctx) {
    calls.push_back({101, {uint32_t(ctx->r4), uint32_t(ctx->r5)}});
}
void func_801E3EE0(uint8_t* rdram, recomp_context* ctx) { capture(1, rdram, ctx); }
void func_801E946C(uint8_t* rdram, recomp_context* ctx) { capture(2, rdram, ctx); }
void func_801E9858(uint8_t* rdram, recomp_context* ctx) { capture(3, rdram, ctx); }
void native_capture_pen(int32_t pen) { replayPen = pen; }
void func_801E80B0(uint8_t* rdram, recomp_context* ctx) {
    replayGlyphs.push_back({uint32_t(ctx->r5), uint32_t(ctx->r6), int32_t(ctx->r7), MEM_W(0x10, ctx->r29),
        uint32_t(MEM_W(0x48, ctx->r29))});
    ctx->r2 = ADD32(ctx->r4, 8);
}
void func_80093C44(uint8_t* rdram, recomp_context* ctx) { emit(rdram, ctx, 4); }
void func_8009328C(uint8_t* rdram, recomp_context* ctx) { prefixFunction(rdram, ctx); }
void func_800933C4(uint8_t* rdram, recomp_context* ctx) { prefixFunction(rdram, ctx); }
void func_i2_802C6ADC(uint8_t* rdram, recomp_context* ctx) { emit(rdram, ctx, 7); }
void func_i2_802C7C50(uint8_t* rdram, recomp_context* ctx) {
    pairMenuReplay = true;
    pairMenuFunction(rdram, ctx);
    pairMenuReplay = false;
}
void func_i2_802C86E4(uint8_t* rdram, recomp_context* ctx) {
    calls.push_back({12, {uint32_t(ctx->r5), uint32_t(ctx->r6)}});
    emit(rdram, ctx, 12);
}
void func_i2_802C88DC(uint8_t* rdram, recomp_context* ctx) { emit(rdram, ctx, 9); }
void func_i2_802C5E28(uint8_t*, recomp_context*) {}
void func_8007C31C(uint8_t*, recomp_context*) {}
void func_801EB180(uint8_t*, recomp_context*) {}
void func_801EB91C(uint8_t*, recomp_context*) {}
void func_801EBFE4(uint8_t*, recomp_context*) {}
void func_80094338(uint8_t* rdram, recomp_context* ctx) { capture(10, rdram, ctx); }
void func_801E4FE8(uint8_t* rdram, recomp_context* ctx) { capture(11, rdram, ctx); }
void func_i8_802C5EB8(uint8_t*, recomp_context*) {}
void func_801EC304(uint8_t*, recomp_context*) {}
void do_break(uint32_t) { std::abort(); }
void switch_error(const char*, uint32_t, uint32_t) { std::abort(); }
}

namespace {
void seedFont(uint8_t* rdram) {
    put(rdram, 0x801CE6B4, Segment1 & 0x1FFFFFFF);
    // Synthetic proportional advances and transparent padding deliberately
    // differ from each other; counting characters or only summing advances
    // cannot pass the visible-ink centering checks.
    for (int code = 0; code < 42; ++code) {
        MEM_B(code, S32(0x80226D98)) = int8_t(4 + (code * 7) % 5);
        for (int y = 0; y < 8; ++y) for (int x = 0; x < 8; ++x) {
            const bool visible = x >= code % 3 && x <= 7 - (code / 3) % 3 && y >= 1 && y <= 6;
            MEM_B(code * 64 + y * 8 + x, S32(SmallFont)) = int8_t(0xA0 | (visible ? 0xF : 0));
        }
    }
}
void seedName(uint8_t* rdram, uint32_t address, std::string_view name) {
    require(name.size() < 11, "Name fixture exceeds its native name field");
    const gpr namePointer = S32(address);
    for (size_t i = 0; i < name.size(); ++i) MEM_B(i, namePointer) = name[i];
    MEM_B(name.size(), namePointer) = 0;
}
bool nameUnchangedAfterFinish(uint8_t* rdram) {
    recomp_context ctx{};
    ctx.r29 = S32(Stack - 0x1800);
    ctx.r5 = 1;
    ctx.r6 = S32(0x801CB298);
    MEM_W(0xD8, ctx.r29) = 284;
    wr64_watercraft_preview_name(rdram, &ctx);
    return MEM_W(0xD8, ctx.r29) == 284;
}
Packet fill(int left, int top, int right, int bottom) {
    return {0xF6000000U | (uint32_t(right * 4) << 12) | uint32_t(bottom * 4),
            (uint32_t(left * 4) << 12) | uint32_t(top * 4)};
}
std::array<Packet, 11> clearFixture() {
    // Synthetic setup-state values, plus the independently decoded border
    // coordinates. No source display-list or texture asset is copied here.
    std::array<Packet, 11> result{};
    constexpr uint8_t opcodes[] = {0xE7, 0xBA, 0xBA, 0xB9, 0xFC, 0xB9, 0xF7};
    for (size_t i = 0; i < 7; ++i) result[i] = {uint32_t(opcodes[i]) << 24 | uint32_t(i), 0x10203040U + uint32_t(i)};
    result[7] = fill(160, 96, 162, 216);
    result[8] = fill(289, 96, 291, 216);
    result[9] = fill(161, 214, 291, 216);
    result[10] = {0xB8000000U, 0};
    return result;
}
std::array<Packet, 11> pairLeftClearFixture() {
    auto result = clearFixture();
    result[7] = fill(26, 96, 28, 216);
    result[8] = fill(155, 96, 157, 216);
    result[9] = fill(27, 214, 157, 216);
    return result;
}
struct Result {
    Packets packets;
    std::vector<Call> calls;
    std::vector<uint32_t> preserved;
    bool operator==(const Result&) const = default;
};
std::vector<uint32_t> preserved(uint8_t* rdram) {
    std::vector<uint32_t> result;
    // Include viewport records, projection/camera state, menu settings and
    // original shared coverage-list bytes. The native stack is scratch space.
    for (auto region : {std::array<uint32_t, 2>{0x800DA000, 0x1000},
        std::array<uint32_t, 2>{0x801C4000, 0xA800}, {0x802C8B00, 0x200},
        {Segment8 + 0xBE400, 0x200}, {Segment1 + 0x387C0, 42 * 64}, {0x80226D98, 0x90}}) {
        for (uint32_t offset = 0; offset < region[1]; offset += 4) result.push_back(get(rdram, region[0] + offset));
    }
    return result;
}
Result run(Function function, int version, int gameStat, int players, int playerIndex,
    int machineSequence, int choice, int buffer, int fault = 0, std::string_view customName = {}, int secondSequence = -1) {
    static std::vector<uint8_t> memory(8 * 1024 * 1024);
    std::fill(memory.begin(), memory.end(), 0);
    uint8_t* rdram = memory.data();
    put(rdram, 0x801CE638, gameStat);
    MEM_H(0, S32(0x801CE60C)) = int16_t(players);
    put(rdram, 0x800DAB2C, playerIndex);
    put(rdram, 0x800DAB24, 10); // native Machine menu mode; stubs don't advance it
    put(rdram, 0x8011F8E0, buffer);
    put(rdram, 0x80223930, choice);
    put(rdram, 0x80223934, (choice + 1) & 3);
    put(rdram, 0x800DA9C0, choice);
    put(rdram, 0x800DA9C4, (choice + 1) & 3);
    put(rdram, 0x802C8C58, machineSequence);
    put(rdram, 0x802C8C5C, secondSequence < 0 ? machineSequence : secondSequence);
    for (int i = 0; i < 4; ++i) put(rdram, 0x802C8BD8 + i * 4, i);
    seedFont(rdram);
    const std::array<std::string_view, 4> defaultNames{"R.HAYAMI", "D.MARINER", "A.STEWART", "M.JETER"};
    for (int i = 0; i < 4; ++i) {
        seedName(rdram, 0x801CB298 + i * 14, customName.empty() ? defaultNames[i] : customName);
        seedName(rdram, 0x800DA950 + i * 14, defaultNames[i]);
    }
    put(rdram, 0x801CE6D0, Segment8 & 0x1FFFFFFF);
    put(rdram, 0x801518B8, Output);
    for (int i = 0; i < 16; i += 2) MEM_H(i, S32(0x800DA8F0)) = int16_t(0x120 + i);
    MEM_H(0, S32(0x800DA8F0)) = 848; // authored X scale retained
    MEM_H(2, S32(0x800DA8F0)) = 480;
    MEM_H(8, S32(0x800DA8F0)) = 1320; // original center 330 in quarter pixels
    MEM_H(10, S32(0x800DA8F0)) = 624;
    put(rdram, 0x800DA900, 0x035001E0);
    put(rdram, 0x800DA904, 0x01FF0000);
    put(rdram, 0x800DA908, 0x01700270); // active IPS left preview center 92
    put(rdram, 0x800DA90C, 0x01FF0000);
    auto fixture = clearFixture();
    if (fault == 1) fixture[10][0] = 0xDEADBEEFU;
    if (fault == 2) fixture[1][0] = 0xDEADBEEFU;
    if (fault == 3) fixture[7][1] += 4;
    for (size_t i = 0; i < fixture.size(); ++i) {
        put(rdram, Clear + uint32_t(i * 8), fixture[i][0]);
        put(rdram, Clear + uint32_t(i * 8 + 4), fixture[i][1]);
    }
    auto leftFixture = pairLeftClearFixture();
    if (fault == 1) leftFixture[10][0] = 0xDEADBEEFU;
    if (fault == 2) leftFixture[1][0] = 0xDEADBEEFU;
    if (fault == 3) leftFixture[7][1] += 4;
    for (size_t i = 0; i < leftFixture.size(); ++i) {
        put(rdram, PairLeftClear + uint32_t(i * 8), leftFixture[i][0]);
        put(rdram, PairLeftClear + uint32_t(i * 8 + 4), leftFixture[i][1]);
    }
    if (fault == 4) put(rdram, 0x800DA8F0, 0x035101E0);
    if (fault == 5) put(rdram, 0x801518B8, 0xA0020000);
    if (fault == 6) put(rdram, 0x801518B8, Output - 0x5900); // only 0x700 bytes remain
    if (fault == 7) put(rdram, 0x801CE6D0, 0xFFFFFFFF);
    const auto before = preserved(rdram);
    recomp_context ctx{};
    ctx.f_odd = &ctx.f0.u32h;
    ctx.r29 = S32(Stack);
    ctx.r31 = S32(0x80001100);
    ctx.r16 = 0x12345678;
    ctx.r4 = S32(Output);
    ctx.r5 = playerIndex;
    prefixFunction = version == 0 ? baseline_func_8008FB74 : version == 1 ? func_8008FB74 : regenerated_func_8008FB74;
    pairMenuFunction = version == 0 ? baseline_func_i2_802C7C50 : version == 1 ? native_pair_func_i2_802C7C50 : regenerated_func_i2_802C7C50;
    wr64_watercraft_preview_prepare(rdram, Output);
    if (function == func_i2_802C70EC || function == baseline_func_i2_802C70EC || function == regenerated_func_i2_802C70EC) {
        recomp_context warm = ctx;
        warm.f_odd = &warm.f0.u32h;
        warm.r4 = S32(Output + 0x5000);
        prefixFunction(rdram, &warm);
    }
    calls.clear();
    function(rdram, &ctx);
    if (function == func_i2_802C5B4C || function == baseline_func_i2_802C5B4C || function == regenerated_func_i2_802C5B4C) {
        require(nameUnchangedAfterFinish(rdram) && wr64_watercraft_preview_scissor(0xED424180) == 0xED424180,
            "Preview state leaked after the native main-builder finished");
    }
    require(uint32_t(ctx.r29) == Stack && uint32_t(ctx.r31) == 0x80001100, "Native caller did not restore its stack/return address");
    require(ctx.r16 == 0x12345678, "Native caller did not preserve s0");
    const uint32_t end = uint32_t(ctx.r2);
    require(end >= Output && end < Output + 0x10000 && (end - Output) % 8 == 0, "Invalid native display-list cursor");
    Result result{{}, calls, preserved(rdram)};
    for (uint32_t cursor = Output; cursor < end; cursor += 8) result.packets.push_back({get(rdram, cursor), get(rdram, cursor + 4)});
    // Main's existing producer clears player_index. That native write is
    // compared to baseline below; independent caption/prefix writes none.
    if (function == func_i2_802C70EC || function == baseline_func_i2_802C70EC || function == regenerated_func_i2_802C70EC ||
        function == func_8008FB74 || function == baseline_func_8008FB74 || function == regenerated_func_8008FB74)
        require(result.preserved == before, "Preview drawing modified its viewport, camera, assets, or game settings");
    return result;
}

Packets removeViewportAlignment(const Packets& packets, bool active) {
    Packets result;
    int currentOffset = 0;
    unsigned alignCount = 0, enableCount = 0, movedViewports = 0;
    for (size_t i = 0; i < packets.size(); ++i) {
        const auto& p = packets[i];
        if (p == Packet{0x00525464, 0x10000064}) { ++enableCount; continue; }
        if (p[0] == 0x64000007) {
            require(i + 1 < packets.size(), "Truncated viewport alignment packet");
            require(p[1] == 0x800, "Viewport origin changed");
            const auto& next = packets[++i];
            require(uint16_t(next[0]) == 0 && next[1] == 0, "Viewport alignment changed Y or reserved fields");
            currentOffset = int16_t(next[0] >> 16);
            require(currentOffset == (alignCount == 0 ? -208 : 0), "Viewport offset or reset is incorrect");
            ++alignCount;
            continue;
        }
        if (p == Packet{0x03800010, 0x800DA8F0} && currentOffset) {
            require(currentOffset == -208, "Wrong translated viewport center");
            require((1320 + currentOffset) / 4 == 278, "Preview center did not move from 330 to 278");
            ++movedViewports;
        }
        result.push_back(p);
    }
    require(currentOffset == 0, "Viewport alignment leaked beyond the live preview");
    require(alignCount == (active ? 2U : 0U) && enableCount == (active ? 1U : 0U) && movedViewports == (active ? 1U : 0U),
        "Viewport alignment is missing or affected an unrelated mode");
    return result;
}
void normalizeScissor(Packets& packets, bool active) {
    unsigned adjusted = 0;
    for (auto& p : packets) if (p[0] >> 24 == 0xED && ((p[0] >> 12) & 0xFFF) == 161 * 4) {
        require((p[0] & 0xFFF) == 96 * 4 && p[1] == ((394U * 4) << 12 | 215U * 4),
            "Preview scissor changed its right edge or vertical coverage");
        p[0] = (p[0] & ~0x00FFF000U) | uint32_t(265 * 4) << 12;
        ++adjusted;
    }
    require(adjusted == (active ? 1U : 0U), "Preview scissor widening is missing or escaped its gate");
}
void normalizeCaption(Call& after, const Call& before, bool active, float panelCenter = 277.5f, int fallbackShift = -52) {
    require(after.kind == before.kind && after.kind == 3, "Native caption call order changed");
    require(after.args[0] == 1 && after.args[3] == 203, "Caption font type or Y changed");
    if (!active) return;
    if (after.glyphs.empty()) require(int(after.args[2]) == int(before.args[2]) + fallbackShift, "No-ink caption lost its previous fallback position");
    else {
        int left = std::numeric_limits<int>::max(), right = std::numeric_limits<int>::min();
        for (const auto& glyph : after.glyphs) {
            require(glyph.type == 1 && glyph.code < 42 && glyph.y == 203 && glyph.scale == 0x3F800000,
                "Native formatter changed font, glyph identity, Y, or scale");
            // These are the synthetic fixture's independently authored alpha
            // margins, placed by the real native formatter/converter. They are
            // distinct from its proportional advance and full 8-pixel cell.
            left = std::min(left, glyph.x + int(glyph.code % 3));
            right = std::max(right, glyph.x + 8 - int((glyph.code / 3) % 3));
        }
        require(std::abs((left + right) * 0.5f - panelCenter) <= 0.5f,
            "Visible caption ink is not centered in the preview panel");
    }
    const int shift = int(after.args[2]) - int(before.args[2]);
    for (auto& glyph : after.glyphs) glyph.x -= shift;
    after.pen -= shift;
    after.args[2] = before.args[2];
}
void normalizePairPackets(Packets& packets, const std::array<bool, 2>& active) {
    Packets normalized;
    std::array<unsigned, 2> moved{}, scissors{};
    unsigned enables = 0, alignments = 0;
    int offset = 0;
    for (size_t i = 0; i < packets.size(); ++i) {
        auto packet = packets[i];
        if (packet == Packet{0x00525464, 0x10000064}) { ++enables; continue; }
        if (packet[0] == 0x64000007) {
            require(i + 1 < packets.size() && packet[1] == 0x800, "Two-player viewport alignment origin changed");
            const auto data = packets[++i];
            require(uint16_t(data[0]) == 0 && data[1] == 0, "Two-player viewport alignment changed Y or reserved bits");
            const int next = int16_t(data[0] >> 16);
            require(next == 0 ? offset != 0 : offset == 0 && (next == 108 || next == -100),
                "Two-player viewport offset did not reset immediately");
            offset = next;
            ++alignments;
            continue;
        }
        if (offset != 0) {
            const int player = offset == 108 ? 0 : 1;
            require(packet == Packet{0x03800010, player == 0 ? 0x800DA900U : 0x800DA8F0U},
                "Two-player viewport translation escaped its native viewport load");
            require(active[player], "A hidden or invalid player preview was translated");
            ++moved[player];
        }
        if (packet == Packet{0xED070180, 0x0034835C}) {
            require(active[0], "Player 1 scissor escaped its preview gate");
            packet = {0xED060180, 0x0027035C};
            ++scissors[0];
        } else if (packet == Packet{0xED358180, 0x0063035C}) {
            require(active[1], "Player 2 scissor escaped its preview gate");
            packet = {0xED424180, 0x0062835C};
            ++scissors[1];
        }
        normalized.push_back(packet);
    }
    require(offset == 0 && enables == unsigned(active[0]) + unsigned(active[1]) && alignments == enables * 2,
        "Two-player preview alignment count or final reset is incorrect");
    for (int player = 0; player < 2; ++player)
        require(moved[player] == unsigned(active[player]) && scissors[player] == unsigned(active[player]),
            "Two-player viewport/scissor was missing, duplicated, or applied to the other player");
    packets = std::move(normalized);
}
void normalizePairCoverage(Packets& packets, const std::array<bool, 2>& active) {
    for (int player = 0; player < 2; ++player) {
        if (!active[player]) continue;
        auto expected = player == 0 ? pairLeftClearFixture() : clearFixture();
        expected[7] = player == 0 ? fill(27, 96, 29, 216) : fill(213, 96, 215, 216);
        expected[8] = player == 0 ? fill(209, 96, 211, 216) : fill(395, 96, 397, 216);
        expected[9] = player == 0 ? fill(28, 214, 211, 216) : fill(214, 214, 397, 216);
        auto start = std::search(packets.begin(), packets.end(), expected.begin(), expected.end() - 1);
        require(start != packets.end(), "Two-player border strips or inherited render state are incorrect");
        const auto offset = start - packets.begin();
        packets.erase(start, start + 10);
        packets.insert(packets.begin() + offset, Packet{0x06000000, player == 0 ? 0x080BE4A8U : 0x080BE500U});
    }
}
void comparePairBuilder(bool enabled, int leftSequence, int rightSequence, int choice, int buffer,
    std::string_view name = {}, int fault = 0) {
    const bool eligible = enabled && fault == 0;
    const std::array<bool, 2> active{eligible && leftSequence == 0, eligible && rightSequence == 0};
    auto before = run(baseline_func_i2_802C5B4C, 0, 4, 2, 0, leftSequence, choice, buffer, fault, name, rightSequence);
    auto after = run(func_i2_802C5B4C, 1, 4, 2, 0, leftSequence, choice, buffer, fault, name, rightSequence);
    auto recipe = run(regenerated_func_i2_802C5B4C, 2, 4, 2, 0, leftSequence, choice, buffer, fault, name, rightSequence);
    require(after == recipe, "Two-player native builder differs from its durable TOML recipe");
    require(after.packets.size() == before.packets.size() + 14 * (unsigned(active[0]) + unsigned(active[1])),
        "Two-player preview exceeded its 112-byte per-player command budget");
    normalizePairPackets(after.packets, active);
    normalizePairCoverage(after.packets, active);
    require(after.calls.size() == before.calls.size(), "Two-player wrapper changed its native draw-call count");
    unsigned captions = 0;
    for (size_t i = 0; i < after.calls.size(); ++i) {
        auto& call = after.calls[i];
        if (call.kind != 3) continue;
        const int player = before.calls[i].args[2] < 200 ? 0 : 1;
        normalizeCaption(call, before.calls[i], active[player], player == 0 ? 119.0f : 305.0f, player == 0 ? 29 : -25);
        ++captions;
    }
    require(captions == unsigned(leftSequence == 0) + unsigned(rightSequence == 0),
        "Two-player captions no longer follow their independent native selection states");
    require(after == before, "Two-player widening changed unrelated menu packets, stats, names, camera state, or asset data");
}
void seedPairIsolation(uint8_t* rdram, int player) {
    put(rdram, 0x801CE638, 4);
    MEM_H(0, S32(0x801CE60C)) = 2;
    put(rdram, 0x800DAB2C, player);
    put(rdram, 0x801518B8, Output);
    put(rdram, 0x801CE6D0, Segment8 & 0x1FFFFFFF);
    put(rdram, 0x800DA8F0, 0x035001E0);
    put(rdram, 0x800DA8F8, 0x05280270);
    put(rdram, 0x800DA900, 0x035001E0);
    put(rdram, 0x800DA908, 0x01700270);
    for (int side = 0; side < 2; ++side) {
        const auto fixture = side == 0 ? pairLeftClearFixture() : clearFixture();
        const uint32_t base = side == 0 ? PairLeftClear : Clear;
        for (size_t i = 0; i < fixture.size(); ++i) {
            put(rdram, base + uint32_t(i * 8), fixture[i][0]);
            put(rdram, base + uint32_t(i * 8 + 4), fixture[i][1]);
        }
    }
    seedFont(rdram);
    seedName(rdram, 0x801CB298, " A.B ");
    wr64_watercraft_preview_prepare(rdram, Output);
    recomp_context warm{};
    warm.f_odd = &warm.f0.u32h;
    warm.r29 = S32(Stack - 0x1000);
    warm.r4 = S32(Output);
    func_8008FB74(rdram, &warm);
}
void checkPairIsolation(bool enabled) {
    std::vector<uint8_t> memory(8 * 1024 * 1024);
    for (int player = 0; player < 2; ++player) for (int fault = 0; fault < 11; ++fault) {
        std::fill(memory.begin(), memory.end(), 0);
        uint8_t* rdram = memory.data();
        seedPairIsolation(rdram, player);
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(Stack);
        ctx.r5 = 1;
        ctx.r6 = S32(0x801CB298);
        ctx.f0.u64 = 0x1234567887654321ULL;
        put(rdram, Stack + 4, 0x13579BDF);
        put(rdram, Stack + 0xD8, player == 0 ? 46 : 284);
        put(rdram, Stack + 0xDC, player == 0 ? 19 : 257);
        if (fault == 1) put(rdram, 0x801CE638, 10);
        if (fault == 2) MEM_H(0, S32(0x801CE60C)) = 1;
        if (fault == 4) wr64_watercraft_preview_finish(rdram, Output);
        if (fault == 5) ctx.r5 = 2;
        if (fault == 6) put(rdram, Stack + 0xDC, 20);
        if (fault == 7) put(rdram, 0x802C8C58 + player * 4, 1);
        if (fault == 8) wr64_watercraft_preview_prepare(rdram, Output);
        if (fault == 9) ctx.r29 = S32(Stack + 1);
        if (fault == 10) MEM_H(0, S32(0x80226E28)) = 1;
        auto expected = memory;
        const auto beforeContext = ctx;
        wr64_watercraft_preview_name(fault == 3 ? rdram + 0x100 : rdram, &ctx);
        require(std::memcmp(&beforeContext, &ctx, sizeof(ctx)) == 0, "Two-player caption measurement changed caller registers");
        const bool active = enabled && (fault == 0 || fault == 10);
        const uint32_t nativeX = player == 0 ? 46 : 284;
        const uint32_t actualX = get(rdram, Stack + 0xD8);
        if (!active) require(actualX == nativeX, "Two-player caption escaped its player, frame, font, or stack scope");
        else if (fault == 10) require(actualX == (player == 0 ? 75U : 259U), "Two-player alternate font lost its bounded fallback");
        else require(actualX != nativeX && actualX != (player == 0 ? 75U : 259U), "Two-player caption retained fixed translation instead of ink centering");
        put(expected.data(), Stack + 0xD8, actualX);
        require(memory == expected, "Two-player caption changed RDRAM beyond its native caption X local");
        wr64_watercraft_preview_finish(rdram, Output);
    }
    for (int player = 0; player < 2; ++player) for (int fault = 0; fault < 9; ++fault) {
        std::fill(memory.begin(), memory.end(), 0);
        uint8_t* rdram = memory.data();
        seedPairIsolation(rdram, player);
        // A player-specific cleanup must survive the global native player
        // index moving on to the other view before the final menu overlay.
        put(rdram, 0x800DAB2C, 1 - player);
        const uint32_t lastSlot = Output + 0x6000 - 8;
        put(rdram, lastSlot, 0x06000000);
        put(rdram, lastSlot + 4, player == 0 ? 0x080BE4A8 : 0x080BE500);
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r2 = S32(lastSlot);
        ctx.r16 = S32(lastSlot + 8);
        ctx.r29 = S32(Stack);
        if (fault == 1) put(rdram, lastSlot, 0x07000000);
        if (fault == 2) put(rdram, lastSlot + 4, player == 0 ? 0x080BE500 : 0x080BE4A8);
        if (fault == 3) put(rdram, 0x802C8C58 + player * 4, 1);
        if (fault == 4) put(rdram, 0x801CE638, 10);
        if (fault == 5) wr64_watercraft_preview_prepare(rdram, Output);
        if (fault == 6) ctx.r16 = S32(lastSlot + 16);
        if (fault == 7) wr64_watercraft_preview_finish(rdram, Output);
        auto expected = memory;
        const auto beforeContext = ctx;
        wr64_two_player_preview_coverage(fault == 8 ? rdram + 0x100 : rdram, &ctx, player);
        if (enabled && fault == 0) {
            put(expected.data(), lastSlot, 0xE7000000);
            put(expected.data(), lastSlot + 4, 0);
        }
        require(memory == expected, "Two-player coverage fallback changed another view, shared asset, preceding command, or memory beyond the pool");
        require(std::memcmp(&beforeContext, &ctx, sizeof(ctx)) == 0, "Two-player final-slot fallback advanced native cursors or changed registers");
        if (fault == 0) {
            const auto after = memory;
            wr64_two_player_preview_coverage(rdram, &ctx, player);
            require(memory == after, "Two-player coverage cleanup was repeated");
        }
        wr64_watercraft_preview_finish(rdram, lastSlot + 8);
    }
}
void checkCapacityFallback(bool enabled) {
    std::vector<uint8_t> memory(8 * 1024 * 1024);
    uint8_t* rdram = memory.data();
    put(rdram, 0x801CE638, 4);
    MEM_H(0, S32(0x801CE60C)) = 1;
    put(rdram, 0x801518B8, Output);
    put(rdram, 0x801CE6D0, Segment8 & 0x1FFFFFFF);
    put(rdram, 0x800DA8F0, 0x035001E0);
    put(rdram, 0x800DA8F8, 0x05280270);
    const auto source = clearFixture();
    for (size_t i = 0; i < source.size(); ++i) {
        put(rdram, Clear + uint32_t(i * 8), source[i][0]);
        put(rdram, Clear + uint32_t(i * 8 + 4), source[i][1]);
    }
    wr64_watercraft_preview_prepare(rdram, Output);
    recomp_context ctx{};
    ctx.f_odd = &ctx.f0.u32h;
    ctx.r4 = S32(Output);
    ctx.r29 = S32(Stack);
    func_8008FB74(rdram, &ctx);
    const uint32_t lastSlot = Output + 0x6000 - 8;
    put(rdram, lastSlot - 4, 0x13579BDF);
    for (uint32_t address = lastSlot + 8; address < lastSlot + 96; address += 4) put(rdram, address, 0x2468ACE0);
    put(rdram, lastSlot, 0x06000000);
    put(rdram, lastSlot + 4, 0x080BE500);
    require(wr64_watercraft_preview_coverage(rdram, lastSlot) == lastSlot, "Capacity fallback advanced beyond the final native slot");
    require(get(rdram, lastSlot) == (enabled ? 0xE7000000U : 0x06000000U) &&
        get(rdram, lastSlot + 4) == (enabled ? 0U : 0x080BE500U), "Capacity fallback retained interior strips or changed disabled behavior");
    require(get(rdram, lastSlot - 4) == 0x13579BDF, "Capacity fallback overwrote the preceding command");
    for (uint32_t address = lastSlot + 8; address < lastSlot + 96; address += 4)
        require(get(rdram, address) == 0x2468ACE0, "Capacity fallback wrote beyond the native display-list pool");
    for (size_t i = 0; i < source.size(); ++i) require(get(rdram, Clear + uint32_t(i * 8)) == source[i][0] &&
        get(rdram, Clear + uint32_t(i * 8 + 4)) == source[i][1], "Capacity fallback mutated the shared source list");
    wr64_watercraft_preview_finish(rdram, lastSlot + 8);
    require(nameUnchangedAfterFinish(rdram) && wr64_watercraft_preview_scissor(0xED424180) == 0xED424180,
        "Capacity fallback left stale state after finish");
}
void checkNameHelperIsolation(bool enabled) {
    std::vector<uint8_t> memory(8 * 1024 * 1024);
    uint8_t* rdram = memory.data();
    for (int fault = 0; fault < 18; ++fault) {
        std::fill(memory.begin(), memory.end(), 0);
        put(rdram, 0x801CE638, 4);
        MEM_H(0, S32(0x801CE60C)) = 1;
        put(rdram, 0x801518B8, Output);
        put(rdram, 0x801CE6D0, Segment8 & 0x1FFFFFFF);
        put(rdram, 0x800DA8F0, 0x035001E0);
        put(rdram, 0x800DA8F8, 0x05280270);
        seedFont(rdram);
        seedName(rdram, 0x801CB298, " A.B ");
        const auto source = clearFixture();
        for (size_t i = 0; i < source.size(); ++i) {
            put(rdram, Clear + uint32_t(i * 8), source[i][0]);
            put(rdram, Clear + uint32_t(i * 8 + 4), source[i][1]);
        }
        wr64_watercraft_preview_prepare(rdram, Output);
        recomp_context warm{};
        warm.f_odd = &warm.f0.u32h;
        warm.r4 = S32(Output);
        warm.r29 = S32(Stack);
        func_8008FB74(rdram, &warm);
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(Stack);
        ctx.r5 = 1;
        ctx.r6 = S32(0x801CB298);
        ctx.r2 = 0x12345678;
        ctx.r7 = 0x87654321;
        ctx.f0.u64 = 0x1122334455667788ULL;
        put(rdram, Stack + 4, 0x13579BDF);
        put(rdram, Stack + 0xD8, 284);
        if (fault == 1) MEM_H(0, S32(0x801CE60C)) = 2;
        if (fault == 2) put(rdram, 0x801CE638, 10); // name-entry/other menu
        if (fault == 3) ctx.r5 = 0;
        if (fault == 5) ctx.r29 = S32(0x70000000);
        if (fault == 6) ctx.r29 = S32(Stack + 1);
        if (fault == 7) MEM_H(0, S32(0x80226E28)) = 1;
        if (fault == 8) put(rdram, 0x80228A44, 2);
        if (fault == 9) put(rdram, 0x801CE6B4, 0xFFFFFFFF);
        if (fault == 10 || fault == 11) MEM_B(10, S32(0x80226D98)) = fault == 10 ? 0 : 9;
        if (fault == 12) for (int i = 0; i < 42 * 64; ++i) MEM_B(i, S32(SmallFont)) = 0xA0;
        if (fault == 13) for (int i = 0; i < 11; ++i) MEM_B(i, S32(0x801CB298)) = 'A';
        if (fault == 14) MEM_B(0, S32(0x801CB298)) = 0;
        if (fault == 15) ctx.r6 = S32(0x70000000);
        if (fault == 16) ctx.r6 = S32(0x807FFFF8);
        if (fault == 17) seedName(rdram, 0x801CB298, "   ");
        std::array<uint8_t, sizeof(recomp_context)> contextBefore;
        std::memcpy(contextBefore.data(), &ctx, sizeof(ctx));
        auto expectedMemory = memory;
        wr64_watercraft_preview_name(fault == 4 ? rdram + 0x100 : rdram, &ctx);
        require(std::memcmp(contextBefore.data(), &ctx, sizeof(ctx)) == 0, "Name measurement modified caller registers or FPU context");
        const bool noOp = !enabled || (fault >= 1 && fault <= 6);
        const uint32_t actualX = get(rdram, Stack + 0xD8);
        if (noOp) require(actualX == 284, "Name correction escaped its frame/edition/font/stack gate");
        else if (fault) require(actualX == 232, "Unrecognized name/font data lost the previous accepted fallback position");
        else require(actualX != 232 && actualX != 284, "Valid proportional caption retained a fixed translation");
        {
            uint8_t* rdram = expectedMemory.data();
            MEM_W(0, S32(Stack + 0xD8)) = actualX;
        }
        require(memory == expectedMemory, "Name measurement changed memory beyond the native caption X local (including converter sp+4)");
        wr64_watercraft_preview_finish(rdram, Output);
    }
}

constexpr uint32_t NameClear = Segment8 + 0x62290;
void seedChangeNames(uint8_t* rdram, int stat, int players, int sequence, int choice,
    int buffer, int key, std::string_view customName, int fault) {
    put(rdram, 0x801CE638, stat);
    MEM_H(0, S32(0x801CE60C)) = int16_t(players);
    put(rdram, 0x800DAB24, 62);
    put(rdram, 0x801CE640, sequence);
    put(rdram, 0x8011F8E0, buffer);
    put(rdram, 0x801CE5F8, 0x80500000 + buffer * 0x2000);
    put(rdram, 0x802C7040, choice);
    put(rdram, 0x802C7534, 0x708090FF);
    put(rdram, 0x802C7538, key % 7);
    put(rdram, 0x802C753C, key / 7);
    put(rdram, 0x802C7564, key % 11);
    put(rdram, 0x802C7568, (key % 11) * 9);
    MEM_H(0, S32(0x802C7530)) = 0x6789;
    constexpr int order[] = {0, 2, 3, 1};
    constexpr std::string_view defaults[] = {"R.HAYAMI", "D.MARINER", "A.STEWART", "M.JETER"};
    seedFont(rdram);
    for (int code = 0; code < 48; ++code) MEM_B(code, S32(0x80226DC4)) = int8_t(6 + code % 7);
    for (int i = 0; i < 4; ++i) {
        put(rdram, 0x802C74F8 + i * 4, order[i]);
        MEM_H(i * 2, S32(0x802C74F0)) = int16_t(19 + 67 * i);
        seedName(rdram, 0x801CB298 + i * 14, customName.empty() ? defaults[i] : customName);
        for (int j = 11; j < 14; ++j) MEM_B(j, gpr(S32(0x801CB298 + i * 14))) = int8_t(40 + i + j);
    }
    seedName(rdram, 0x802C7548, "EDIT.NAME");
    seedName(rdram, 0x802C7554, "BACKUP");
    // Synthetic keyboard: ordinary letters, message cells, absolute-position
    // cells and hidden cells exercise the existing normal/highlight branches.
    for (int i = 0; i < 42; ++i) {
        const gpr entry = S32(0x802C7054 + i * 28);
        MEM_B(0, entry) = int8_t(1 | (i % 9 == 8 ? 0 : 2) | (i % 6 == 5 ? 4 : 0) | (i % 7 == 6 ? 8 : 0));
        MEM_H(2, entry) = 2;
        MEM_H(4, entry) = int16_t(i % 7 == 6 ? 125 : i % 3 - 1);
        MEM_H(6, entry) = int16_t(i % 7 == 6 ? 175 : i % 2);
        MEM_B(12, entry) = int8_t('A' + i % 26);
        put(rdram, uint32_t(entry) + 24, 40 + i);
    }
    put(rdram, 0x801CE6D0, Segment8 & 0x1FFFFFFF);
    put(rdram, 0x801518B8, Output);
    put(rdram, 0x800DA8F0, 0x035001E0);
    put(rdram, 0x800DA8F8, 0x05280270);
    // Independently audited ACTIVE IPS descriptor at ROM 0x97454 selects
    // [0x818D28,0x819A6C), decoded to segment 8 + 0x60000 (0x22E8 bytes).
    // Its border list is 0x08062290. Construct metadata and render state; do
    // not embed either compressed bank or cartridge display-list payload.
    auto fixture = clearFixture();
    if (fault == 1) fixture[10][0] = 0xDEADBEEF;
    if (fault == 2) fixture[8][1] += 4;
    if (fault == 3) fixture[1][0] = 0xDEADBEEF;
    for (size_t i = 0; i < fixture.size(); ++i) {
        const uint32_t address = (fault == 4 ? Clear : NameClear) + uint32_t(i * 8);
        put(rdram, address, fixture[i][0]);
        put(rdram, address + 4, fixture[i][1]);
    }
    if (fault == 5) put(rdram, 0x801518B8, Output - 0x5900);
    if (fault == 6) put(rdram, 0x800DA8F0, 0x035101E0);
    if (fault == 7) put(rdram, 0x801CE6D0, 0xFFFFFFFF);
    if (fault == 8) put(rdram, 0x801CE63C, 1); // native first-clear frame
}
std::vector<uint32_t> namePreserved(uint8_t* rdram) {
    auto result = preserved(rdram);
    for (auto region : {std::array<uint32_t, 2>{0x802C7040, 0x540}, {NameClear, 88},
        {0x80500000, 0x4000}}) {
        for (uint32_t i = 0; i < region[1]; i += 4) result.push_back(get(rdram, region[0] + i));
    }
    return result;
}
Result runChangeNames(int version, int stat, int players, int sequence, int choice,
    int buffer, int key, std::string_view customName = {}, int fault = 0) {
    static std::vector<uint8_t> memory(8 * 1024 * 1024);
    std::fill(memory.begin(), memory.end(), 0);
    uint8_t* rdram = memory.data();
    seedChangeNames(rdram, stat, players, sequence, choice, buffer, key, customName, fault);
    const auto before = namePreserved(rdram);
    wr64_watercraft_preview_finish(rdram, Output); // reset preceding fixture
    recomp_context ctx{};
    ctx.f_odd = &ctx.f0.u32h;
    ctx.r29 = S32(Stack);
    ctx.r31 = S32(0x80001100);
    ctx.r16 = 0x12345678;
    ctx.r4 = S32(Output);
    prefixFunction = version == 0 ? baseline_func_8008FB74 : version == 1 ? func_8008FB74 : regenerated_func_8008FB74;
    const Function versions[] = {baseline_func_i8_802C5D3C, func_i8_802C5D3C, regenerated_func_i8_802C5D3C};
    calls.clear();
    changeNameReplay = true;
    versions[version](rdram, &ctx);
    changeNameReplay = false;
    require(uint32_t(ctx.r29) == Stack && uint32_t(ctx.r31) == 0x80001100 && ctx.r16 == 0x12345678,
        "Change Names native stack, return address, or saved registers changed");
    const uint32_t end = uint32_t(ctx.r2);
    require(end >= Output && end < Output + 0x6000 && (end - Output) % 8 == 0, "Change Names cursor escaped native pool");
    Result result{{}, calls, namePreserved(rdram)};
    for (uint32_t cursor = Output; cursor < end; cursor += 8) result.packets.push_back({get(rdram,cursor),get(rdram,cursor+4)});
    // The native main clears only player_index and the first-clear flag. Seed
    // both at zero for ordinary cases, account explicitly for the clear flag.
    if (fault == 8) {
        put(rdram, 0x801CE63C, 1);
        require(namePreserved(rdram) == before, "First-clear frame changed names, camera, keyboard, or asset data");
        put(rdram, 0x801CE63C, 0);
    } else require(result.preserved == before, "Change Names rendering changed edit buffers, keyboard, saved names, or camera assets");
    ctx.r5 = 1; ctx.r6 = S32(0x801CB298); ctx.r7 = 123;
    wr64_change_name_preview_name(rdram, &ctx);
    require(ctx.r7 == 0 && nameUnchangedAfterFinish(rdram) && wr64_watercraft_preview_scissor(0xED424180) == 0xED424180,
        "Change Names state leaked after native finish/first-clear return");
    return result;
}
void compareChangeNames(bool active, int stat, int players, int sequence, int choice,
    int buffer, int key, std::string_view name = {}, int fault = 0) {
    auto before = runChangeNames(0,stat,players,sequence,choice,buffer,key,name,fault);
    auto after = runChangeNames(1,stat,players,sequence,choice,buffer,key,name,fault);
    auto recipe = runChangeNames(2,stat,players,sequence,choice,buffer,key,name,fault);
    require(after == recipe, "Change Names checked-in producer differs from TOML regeneration");
    require(after.packets.size() == before.packets.size() + (active ? 14 : 0), "Change Names exceeded 112 extra display-list bytes");
    after.packets = removeViewportAlignment(after.packets, active);
    normalizeScissor(after.packets, active);
    if (active) {
        auto expected = clearFixture();
        expected[8] = fill(393,96,395,216);
        expected[9] = fill(161,214,395,216);
        auto start = std::search(after.packets.begin(),after.packets.end(),expected.begin(),expected.end()-1);
        require(start != after.packets.end(), "Change Names active-bank border state/coordinates mismatch");
        auto offset = start - after.packets.begin();
        after.packets.erase(start,start+10);
        after.packets.insert(after.packets.begin()+offset,Packet{0x06000000,0x08062290});
    }
    unsigned captions = 0, editFields = 0, miniatures = 0;
    require(after.calls.size() == before.calls.size(), "Change Names native call count changed");
    for (size_t i = 0; i < after.calls.size(); ++i) {
        auto& call = after.calls[i];
        if (call.kind == 3 && call.args[0] == 1 && call.args[3] == 203) {
            normalizeCaption(call, before.calls[i], active);
            ++captions;
        }
        if (call.kind == 3 && call.args[1] == 0x802C7548) {
            require(call.args[0] == 2 && call.args[2] == 31 && call.args[3] == 98 && !call.glyphs.empty(),
                "Left editable name lost its original font, position, or text");
            ++editFields;
        }
        if (call.kind == 11) ++miniatures;
    }
    require(captions == (fault == 8 ? 0 : 1) && editFields == captions && miniatures == 4 * captions,
        "Change Names caption, edit field, or four miniature visibility changed");
    require(after == before, "Change Names preview changed keyboard/cursor/glyphs, miniatures, unrelated packets, or stored name state");
}
void checkChangeNameIsolation(bool enabled) {
    std::vector<uint8_t> memory(8 * 1024 * 1024);
    for (int fault = 0; fault < 9; ++fault) {
        std::fill(memory.begin(),memory.end(),0);
        uint8_t* rdram = memory.data();
        seedChangeNames(rdram,10,1,1,2,0,13," A.B ",0);
        wr64_change_name_preview_prepare(rdram,Output);
        recomp_context warm{}; warm.f_odd=&warm.f0.u32h; warm.r4=S32(Output); warm.r29=S32(Stack);
        func_8008FB74(rdram,&warm);
        recomp_context ctx{}; ctx.f_odd=&ctx.f0.u32h; ctx.r29=S32(Stack); ctx.r5=1;
        ctx.r6=S32(0x801CB298); ctx.r7=123; ctx.f0.u64=0x1234567887654321ULL;
        put(rdram,Stack+4,0x13579BDF); put(rdram,Stack+0xD8,0x2468ACE0);
        if (fault == 1) put(rdram,0x801CE638,4); // captured-state gate
        if (fault == 2) wr64_watercraft_preview_prepare(rdram,Output); // wrong prepare entry
        if (fault == 3) ctx.r5=2;
        if (fault == 4) MEM_H(0,S32(0x801CE60C))=2;
        if (fault == 5) MEM_H(0,S32(0x80226E28))=1;
        if (fault == 6) for (int i=0;i<11;++i) MEM_B(i,S32(0x801CB298))='A';
        if (fault == 7) wr64_watercraft_preview_finish(rdram,Output);
        auto beforeMemory=memory;
        auto beforeContext=ctx;
        wr64_change_name_preview_name(fault == 8 ? rdram+0x100 : rdram,&ctx);
        require(memory == beforeMemory, "Change Names measurement changed RDRAM or converter stack spill");
        const bool active=enabled && (fault==0 || fault==5 || fault==6);
        require(active ? (fault ? ctx.r7==S32(-52) : ctx.r7!=0 && ctx.r7!=S32(-52)) : ctx.r7==0,
            "Change Names caption delta escaped its frame gate or lost its fallback");
        beforeContext.r7=ctx.r7;
        require(std::memcmp(&beforeContext,&ctx,sizeof(ctx))==0,"Change Names measurement changed registers other than its explicit a3 result");
        wr64_watercraft_preview_finish(rdram,Output);
    }
}
}

int main(int argc, char**) {
    const bool enabled = argc == 1;
    unsigned prefixCases = 0, captionCases = 0, builderCases = 0, failClosedCases = 0, customNameCases = 0, pairBuilderCases = 0;
    for (float aspect : {4.0f / 3.0f, 16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for (int stat : {0, 2, 4, 10}) for (int players : {1, 2}) for (int index : {0, 1}) for (int buffer : {0, 1}) {
            const bool active = enabled && stat == 4 && players == 1;
            const bool pairActive = enabled && stat == 4 && players == 2;
            auto before = run(baseline_func_8008FB74, 0, stat, players, index, 0, index, buffer);
            auto after = run(func_8008FB74, 1, stat, players, index, 0, index, buffer);
            auto recipe = run(regenerated_func_8008FB74, 2, stat, players, index, 0, index, buffer);
            require(after == recipe, "Generated native viewport hooks differ from their TOML recipe");
            require(after.packets.size() == before.packets.size() + (active || pairActive ? 5 : 0), "Unexpected viewport command capacity change");
            if (players == 2) normalizePairPackets(after.packets, {pairActive && index == 0, pairActive && index == 1});
            else {
                after.packets = removeViewportAlignment(after.packets, active);
                normalizeScissor(after.packets, active);
            }
            require(after == before, "Unrelated native viewport/scissor/camera behavior changed");
            ++prefixCases;
        }
        for (int stat : {4, 10}) for (int players : {1, 2}) for (int index = 0; index < players; ++index) for (int sequence = 0; sequence <= 6; ++sequence)
            for (int choice = 0; choice < 4; ++choice) {
                const bool active = enabled && stat == 4 && players == 1;
                const bool pairActive = enabled && stat == 4 && players == 2 && sequence == 0;
                auto before = run(baseline_func_i2_802C70EC, 0, stat, players, index, sequence, choice, 0);
                auto after = run(func_i2_802C70EC, 1, stat, players, index, sequence, choice, 0);
                auto recipe = run(regenerated_func_i2_802C70EC, 2, stat, players, index, sequence, choice, 0);
                require(after == recipe, "Generated caption hook differs from its TOML recipe");
                unsigned captions = 0;
                for (size_t i = 0; i < after.calls.size(); ++i) if (after.calls[i].kind == 3) {
                    if (players == 2) normalizeCaption(after.calls[i], before.calls[i], pairActive,
                        index == 0 ? 119.0f : 305.0f, index == 0 ? 29 : -25);
                    else normalizeCaption(after.calls[i], before.calls[i], active);
                    ++captions;
                }
                require(captions == (players == 1 || sequence == 0 ? 1U : 0U), "Native caption visibility changed");
                require(after == before, "Caption correction changed other labels, meters, colors, choices, or command sizes");
                ++captionCases;
            }
        for (std::string_view name : {"I", "WWW", "A B", " A B ", "   ", "10-0", "A'@.Z", "a!?/", "ABCDEFGHIJ"})
            for (int index : {0, 1}) for (int choice = 0; choice < 4; ++choice) {
                // Index 0 exercises saved/custom names. Index 1 explicitly
                // reaches the alternate native caption call (original names).
                auto before = run(baseline_func_i2_802C70EC, 0, 4, 1, index, 0, choice, 0, 0, name);
                auto after = run(func_i2_802C70EC, 1, 4, 1, index, 0, choice, 0, 0, name);
                auto recipe = run(regenerated_func_i2_802C70EC, 2, 4, 1, index, 0, choice, 0, 0, name);
                require(after == recipe, "Custom-name hook regeneration differs from the current producer");
                for (size_t i = 0; i < after.calls.size(); ++i) if (after.calls[i].kind == 3)
                    normalizeCaption(after.calls[i], before.calls[i], enabled);
                require(after == before, "Custom-name centering changed glyphs, spacing, colors, or other menu content");
                ++customNameCases;
            }
        for (int players : {1, 2}) for (int sequence = 0; sequence <= 6; ++sequence) for (int buffer : {0, 1}) {
            if (players == 2) {
                comparePairBuilder(enabled, sequence, sequence, 0, buffer);
                ++pairBuilderCases;
                continue;
            }
            const bool active = enabled && players == 1;
            auto before = run(baseline_func_i2_802C5B4C, 0, 4, players, 0, sequence, 0, buffer);
            auto after = run(func_i2_802C5B4C, 1, 4, players, 0, sequence, 0, buffer);
            auto recipe = run(regenerated_func_i2_802C5B4C, 2, 4, players, 0, sequence, 0, buffer);
            require(after == recipe, "Generated final-builder hook differs from its TOML recipe");
            require(after.packets.size() == before.packets.size() + (active ? 14 : 0), "Full preview exceeded its 112-byte command budget");
            after.packets = removeViewportAlignment(after.packets, active);
            normalizeScissor(after.packets, active);
            if (active) {
                auto original = clearFixture();
                auto expected = original;
                expected[8] = fill(393, 96, 395, 216);
                expected[9] = fill(161, 214, 395, 216);
                auto start = std::search(after.packets.begin(), after.packets.end(), expected.begin(), expected.end() - 1);
                require(start != after.packets.end(), "The three coverage strips or inherited render state are incorrect");
                auto offset = start - after.packets.begin();
                after.packets.erase(start, start + 10);
                after.packets.insert(after.packets.begin() + offset, Packet{0x06000000, 0x080BE500});
            }
            require(after == before, "Preview border replacement altered unrelated menu packets, state, or shared assets");
            ++builderCases;
        }
        // One player can keep previewing while the other edits performance or
        // confirms a choice. Replay every independent pair of native states.
        for (int left = 0; left <= 6; ++left) for (int right = 0; right <= 6; ++right) {
            if (left == right) continue;
            comparePairBuilder(enabled, left, right, (left + right) % 4, (left ^ right) & 1);
            ++pairBuilderCases;
        }
        for (std::string_view name : {"I", "WWW", " A B ", "   ", "A'@.Z", "ABCDEFGHIJ"})
            for (int choice = 0; choice < 4; ++choice) {
                comparePairBuilder(enabled, 0, 0, choice, choice & 1, name);
                ++pairBuilderCases;
            }
        for (int fault = 1; fault <= 7; ++fault) {
            comparePairBuilder(enabled, 0, 0, fault & 3, fault & 1, {}, fault);
            ++pairBuilderCases;
        }
        for (int fault = 1; fault <= 7; ++fault) {
            for (auto functions : {std::array<Function, 3>{baseline_func_8008FB74, func_8008FB74, regenerated_func_8008FB74},
                std::array<Function, 3>{baseline_func_i2_802C70EC, func_i2_802C70EC, regenerated_func_i2_802C70EC},
                std::array<Function, 3>{baseline_func_i2_802C5B4C, func_i2_802C5B4C, regenerated_func_i2_802C5B4C}}) {
                auto before = run(functions[0], 0, 4, 1, 0, 0, 0, 0, fault);
                auto after = run(functions[1], 1, 4, 1, 0, 0, 0, 0, fault);
                auto recipe = run(functions[2], 2, 4, 1, 0, 0, 0, 0, fault);
                require(after == before && recipe == before, "Unverified runtime state did not retain the complete native preview");
                ++failClosedCases;
            }
        }
    }
    checkCapacityFallback(enabled);
    checkNameHelperIsolation(enabled);
    checkPairIsolation(enabled);
    const char* nameSetting=std::getenv("WR64_CHANGE_NAME_PREVIEW");
    const bool namesEnabled=!(nameSetting && std::string_view(nameSetting)=="0");
    unsigned changeNameCases=0;
    for (float aspect : {4.0f/3.0f,16.0f/9.0f,21.0f/9.0f,32.0f/9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for (int players : {1,2}) for (int sequence : {0,1}) for (int choice=0;choice<4;++choice)
            for (int buffer : {0,1}) {
                const int keys[]={0,6,13,29,35,40,41,18};
                compareChangeNames(namesEnabled && players==1,10,players,sequence,choice,buffer,keys[choice*2+buffer]);
                ++changeNameCases;
            }
        for (std::string_view name : {"I","WWW"," A B ","   ","A'@.Z","ABCDEFGHIJ"}) {
            compareChangeNames(namesEnabled,10,1,1,3,0,20,name); ++changeNameCases;
        }
        for (int fault=1;fault<=8;++fault) {
            compareChangeNames(false,10,1,1,2,0,13,{},fault); ++changeNameCases;
        }
        for (int stat : {0,4}) {
            compareChangeNames(false,stat,1,1,1,0,0); ++changeNameCases;
        }
    }
    checkChangeNameIsolation(namesEnabled);
    std::cout << "Passed " << prefixCases << " native viewport cases, " << captionCases << " native caption cases, "
        << builderCases << " native final-builder cases, " << failClosedCases << " fail-closed cases, " << assertions
        << " assertions, " << customNameCases << " custom/alternate name cases; feature " << (enabled ? "enabled" : "disabled")
        << "; " << changeNameCases << " Change Names builder cases and 9 isolation cases, feature " << (namesEnabled ? "enabled" : "disabled") << ".\n";
    std::cout << "Passed " << pairBuilderCases << " two-player native builders with independent viewports, captions, coverage, and selection states.\n";
}
