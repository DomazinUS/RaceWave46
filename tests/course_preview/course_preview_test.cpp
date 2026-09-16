#include "recomp.h"
#include "wr64_course_preview.h"
#include "common/rt64_wr64_ultrawide.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
void func_i4_802C6778(uint8_t*, recomp_context*);
void baseline_func_i4_802C6778(uint8_t*, recomp_context*);
void regenerated_func_i4_802C6778(uint8_t*, recomp_context*);
void func_i4_802C5CDC(uint8_t*, recomp_context*);
void baseline_func_i4_802C5CDC(uint8_t*, recomp_context*);
void regenerated_func_i4_802C5CDC(uint8_t*, recomp_context*);
void func_i4_802C6ED0(uint8_t*, recomp_context*);
void native_difficulty_frame(uint8_t*, recomp_context*);
void native_score(uint8_t*, recomp_context*);
void native_time(uint8_t*, recomp_context*);
void native_string(uint8_t*, recomp_context*);
}

namespace {
unsigned assertions = 0, scenarios = 0;
std::string context;
void require(bool condition, const char* reason) {
    ++assertions;
    if (!condition) { std::cerr << context << ": " << reason << '\n'; std::exit(1); }
}
constexpr uint32_t Output = 0x80020000, Stack = 0x80100000;
constexpr uint32_t Segment1 = 0x80400000, Viewport = Segment1 + 0x6F738;
constexpr uint32_t Segment8 = 0x80300000, Depth = Segment8 + 0xA6E00;
using Packet = std::array<uint32_t, 2>;
using Packets = std::vector<Packet>;
using Function = void (*)(uint8_t*, recomp_context*);
void put(uint8_t* rdram, uint32_t address, uint32_t value) { MEM_W(0, S32(address)) = value; }
uint32_t get(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
Packet fill(int left, int top, int right, int bottom) {
    return {0xF6000000U | (uint32_t(right * 4) << 12) | uint32_t(bottom * 4),
        uint32_t(left * 4) << 12 | uint32_t(top * 4)};
}
Packet translate(Packet p, int delta) {
    for (auto& word : p) word = (word & ~0x00FFF000U) | (((((word >> 12) & 0xFFF) + delta * 4) & 0xFFF) << 12);
    return p;
}
struct Glyph {
    uint32_t font, code;
    int32_t x, y;
    std::array<uint32_t, 14> style;
    bool operator==(const Glyph&) const = default;
};
struct Call {
    uint32_t kind;
    std::array<uint32_t, 13> args{};
    std::vector<Glyph> glyphs;
    bool operator==(const Call&) const = default;
};
std::vector<Call> calls;
std::vector<Glyph> replayGlyphs;
void capture(uint32_t kind, uint8_t* rdram, recomp_context* ctx, Function replay = nullptr) {
    Call call{kind, {uint32_t(ctx->r5), uint32_t(ctx->r6), uint32_t(ctx->r7)}};
    // Only arguments consumed by this native producer are meaningful; the
    // remaining caller stack slots may contain stale display-list cursors.
    const size_t count = kind == 3 ? 13 : kind == 1 ? 5 : kind == 2 ? 6 : kind == 7 ? 2 : 4;
    for (size_t i = 3; i < count; ++i) call.args[i] = MEM_W((i + 1) * 4, ctx->r29);
    if (kind == 7) call.args[2] = 0;
    if (replay) {
        recomp_context native = *ctx;
        native.f_odd = &native.f0.u32h;
        native.r4 = S32(Output + 0x8000);
        native.r29 = S32(Stack - 0x1000);
        MEM_W(0x10, native.r29) = call.args[3];
        replayGlyphs.clear();
        replay(rdram, &native);
        call.glyphs = replayGlyphs;
    }
    calls.push_back(call);
    if (kind == 7) native_difficulty_frame(rdram, ctx);
    else {
        put(rdram, uint32_t(ctx->r4), 0x7F000000 | kind);
        put(rdram, uint32_t(ctx->r4) + 4, 0);
        ctx->r2 = ADD32(ctx->r4, 8);
    }
}
}

extern "C" {
void func_80094338(uint8_t* rdram, recomp_context* ctx) { capture(1, rdram, ctx); }
void func_801E3EE0(uint8_t* rdram, recomp_context* ctx) { capture(2, rdram, ctx); }
void func_801E946C(uint8_t* rdram, recomp_context* ctx) { capture(3, rdram, ctx); }
void func_80094200(uint8_t* rdram, recomp_context* ctx) { capture(4, rdram, ctx, native_score); }
void func_801E8B24(uint8_t* rdram, recomp_context* ctx) { capture(5, rdram, ctx, native_time); }
void func_801E9858(uint8_t* rdram, recomp_context* ctx) { capture(6, rdram, ctx, native_string); }
void func_i4_802C69C4(uint8_t* rdram, recomp_context* ctx) { capture(7, rdram, ctx); }
void func_801E80B0(uint8_t* rdram, recomp_context* ctx) {
    Glyph glyph{uint32_t(ctx->r5), uint32_t(ctx->r6), int32_t(ctx->r7), MEM_W(0x10, ctx->r29)};
    for (int i = 0; i < 14; ++i) glyph.style[i] = MEM_W(0x14 + i * 4, ctx->r29);
    replayGlyphs.push_back(glyph);
    ctx->r2 = ADD32(ctx->r4, 8);
}
void func_800CA210(uint8_t* rdram, recomp_context* ctx) {
    // The score producer's existing sprintf call formats one decimal digit.
    require(ctx->r6 <= 9, "native score formatter did not pass a decimal digit");
    MEM_B(0, ctx->r4) = int8_t('0' + ctx->r6);
    MEM_B(1, ctx->r4) = 0;
    ctx->r2 = 1;
}
void do_break(uint32_t) { std::abort(); }
void switch_error(const char*, uint32_t, uint32_t) { std::abort(); }
}

namespace {
std::array<Packet, 13> ipsSelectedDepthFixture() {
    // Independently verified runtime bank selection: the existing IPS changes
    // the ROM entry at 0x971DC from [0x330990,0x3320E0) to
    // [0x81758A,0x818D28), loaded at segment8+0xA0000. This fixture describes
    // the depth list at offset0x6E00 in THAT selected bank, not the unused
    // original compressed bank. Only metadata/decoded command fields are
    // retained; unrelated render-state payloads below are synthetic.
    constexpr uint8_t opcodes[] = {0x03,0xB6,0xB7,0xBB,0xE7,0xBA,0xFC,0xB9,0xFE,0xFF,0xF7,0xF6,0xB8};
    std::array<Packet, 13> result{};
    for (size_t i = 0; i < result.size(); ++i) result[i] = {uint32_t(opcodes[i]) << 24 | uint32_t(i), 0x01020300U + uint32_t(i)};
    result[0][1] = 0x080A6DA0;
    result[8] = {0xFE000000U, 0x00700000U};
    result[9] = {0xFF1001A7U, 0x00700000U}; // IPS already supplies width424
    result[11] = fill(254, 53, 395, 158); // F662C278/003F80D4
    result[12] = {0xB8000000U, 0};
    return result;
}
struct Settings {
    int stat = 5, players = 1, course = 0, variant = 0, buffer = 0;
    int score = 0, difficulty = 0, menu = 0, mask = -1, request = 1, fault = 0;
};
struct Result {
    Packets packets;
    std::vector<Call> calls;
    std::vector<uint32_t> preserved;
    std::array<uint32_t, 8> animation{};
    bool operator==(const Result&) const = default;
};
std::vector<uint32_t> preserved(uint8_t* rdram) {
    std::vector<uint32_t> result;
    for (auto region : {std::array<uint32_t,2>{0x800DA000,0x1800}, {0x801C1F00,0x1000},
        {0x80198300,0x100}, {0x801CE5F0,0x100}, {0x802C7530,0x1B0},
        {Viewport - 0x18, 0x40}, {Depth - 0x10,0x90}, {0x80226D70,0x140}})
        for (uint32_t offset = 0; offset < region[1]; offset += 4) result.push_back(get(rdram, region[0] + offset));
    return result;
}
void seed(uint8_t* rdram, const Settings& s) {
    put(rdram, 0x801CE638, s.stat);
    MEM_H(0, S32(0x801CE60C)) = int16_t(s.players);
    put(rdram, 0x801CE608, s.score ? 11 : 10);
    put(rdram, 0x800DA9D0, s.course);
    put(rdram, 0x802C7534, s.variant);
    put(rdram, 0x80151948, s.buffer);
    for (int i = 0; i < 3; ++i) put(rdram, 0x801542C0 + i * 4, 0x80160000 + i * 0x40000);
    put(rdram, 0x801CE5F8, 0x00200000);
    MEM_H(0, S32(0x802C76AC)) = 0x4321;
    put(rdram, 0x801CE6B4, Segment1 & 0x1FFFFFFF);
    put(rdram, 0x801CE6D0, Segment8 & 0x1FFFFFFF);
    put(rdram, 0x801518B8, Output);
    const std::array<int16_t, 8> vp{640,480,511,0,1300,424,511,0};
    for (int i = 0; i < 8; ++i) MEM_H(i * 2, S32(Viewport)) = vp[i];
    auto depth = ipsSelectedDepthFixture();
    for (size_t i = 0; i < depth.size(); ++i) {
        put(rdram, Depth + uint32_t(i * 8), depth[i][0]);
        put(rdram, Depth + uint32_t(i * 8 + 4), depth[i][1]);
    }
    for (int i = 0; i < 9; ++i) {
        const int course = (i * 5) % 9; // nonidentity table catches direct-index mistakes
        put(rdram, 0x800DAAD8 + i * 4, course);
        put(rdram, 0x800DAA10 + i * 4, 8 + i);
        put(rdram, 0x802C7558 + i * 4, i & 1);
        put(rdram, 0x802C7660 + i * 4, 3 + i);
        for (int j = 0; j < 4; ++j) put(rdram, 0x802C757C + i * 16 + j * 4, (i + j) & 1);
        for (auto address : {0x800DB5B0U, 0x800DB5F8U, 0x800DB6D0U}) {
            put(rdram, address + i * 8, 0x08002000 + i * 0x100 + (address & 0xFF));
            put(rdram, address + i * 8 + 4, 0x08003000 + i * 0x100 + (address & 0xFF));
        }
        put(rdram, 0x801C1FF0 + i * 60, 60001 + i * 731);
        put(rdram, 0x801C22C0 + i * 20, 21001 + i * 317);
        put(rdram, 0x801C23B0 + i * 20, 67001 + i * 547);
        put(rdram, 0x801C26E8 + i * 48, 12345 + i * 731);
    }
    put(rdram, 0x802C7548, s.menu);
    put(rdram, 0x802C754C, s.difficulty);
    put(rdram, 0x802C7550, 1);
    put(rdram, 0x802C7554, 1);
    put(rdram, 0x802C76C4, s.difficulty == 3);
    put(rdram, 0x802C76C8, (s.players == 2 ? 2 : 0) + (s.difficulty == 3));
    put(rdram, 0x802C76D0, s.difficulty == 3 ? 4 : 3);
    put(rdram, 0x800DAA04, s.course & 1);
    for (int i = 0; i < 6; ++i) {
        MEM_H(0, S32(0x802C7630 + i * 8)) = int16_t(-10 + i * 3);
        put(rdram, 0x802C7634 + i * 8, 30 + i);
    }
    const char* missing = "-'--@---";
    for (int i = 0; i < 9; ++i) MEM_B(i, S32(0x802C7690)) = missing[i];
    for (int i = 0; i < 0xB0; ++i) MEM_B(i, S32(0x80226D70)) = int8_t(5 + i % 4);
    put(rdram, 0x80226E24, std::bit_cast<uint32_t>(1.0f));
    MEM_H(0, S32(0x80226E28)) = 0;
    put(rdram, 0x802C7540, s.mask >= 0);
    put(rdram, 0x802C7538, 1);
    put(rdram, 0x802C753C, s.mask < 0 ? 0 : s.mask);
    put(rdram, 0x802C7544, s.request);
    put(rdram, 0x802C76B4, 246);
    put(rdram, 0x802C76B8, 33);
    put(rdram, 0x802C76BC, 142);
    put(rdram, 0x802C76C0, 106);
    if (s.fault == 1) put(rdram, Depth + 12 * 8, 0xDEADBEEF);
    if (s.fault == 2) put(rdram, Depth + 5 * 8, 0xDEADBEEF);
    if (s.fault == 3) put(rdram, Depth + 11 * 8 + 4, fill(255, 53, 395, 158)[1]);
    if (s.fault == 4) put(rdram, Viewport + 8, 0x051501A8);
    if (s.fault == 5) put(rdram, 0x801518B8, 0xA0020000);
    if (s.fault == 6) put(rdram, 0x801518B8, Output - 0x5900);
    if (s.fault == 7) put(rdram, 0x801CE6D0, 0xFFFFFFFF);
    if (s.fault == 8) put(rdram, 0x801CE6B4, 0xFFFFFFFF);
    if (s.fault == 9) put(rdram, Depth + 9 * 8, 0xFF10012FU);
    // The obsolete original-bank fixture previously let this suite pass even
    // though the enhancement never activated with the actual loaded assets.
    // Reject it in full, and reject each mixed-bank discrepancy independently.
    if (s.fault == 10 || s.fault == 11) put(rdram, Depth + 8 * 8 + 4, 0x002A0000);
    if (s.fault == 10 || s.fault == 12) put(rdram, Depth + 9 * 8 + 4, 0x002A0000);
    if (s.fault == 10 || s.fault == 13) put(rdram, Depth + 9 * 8, 0xFF10013F);
    if (s.fault == 10 || s.fault == 14) {
        const auto obsolete = fill(150,53,291,158);
        put(rdram,Depth+11*8,obsolete[0]); put(rdram,Depth+11*8+4,obsolete[1]);
    }
    if (s.fault == 15) put(rdram,Depth+11*8,fill(254,53,291,158)[0]);
}
std::array<uint32_t,8> animation(uint8_t* rdram) {
    return {get(rdram,0x802C7538),get(rdram,0x802C753C),get(rdram,0x802C7540),get(rdram,0x802C7548),
        get(rdram,0x802C76B4),get(rdram,0x802C76B8),get(rdram,0x802C76BC),get(rdram,0x802C76C0)};
}
Result run(int version, const Settings& s, bool mapOnly = false) {
    static std::vector<uint8_t> memory(8 * 1024 * 1024);
    std::fill(memory.begin(), memory.end(), 0);
    uint8_t* rdram = memory.data();
    seed(rdram, s);
    recomp_context ctx{};
    ctx.f_odd = &ctx.f0.u32h;
    ctx.r4 = S32(Output);
    ctx.r29 = S32(Stack);
    ctx.r31 = S32(0x80001234);
    if (s.mask >= 0) func_i4_802C6ED0(rdram, &ctx);
    auto state = animation(rdram);
    const auto before = preserved(rdram);
    ctx.r4 = S32(Output);
    calls.clear();
    if (mapOnly) {
        put(rdram, Output, 0x06000000);
        put(rdram, Output + 4, 0x080A6DB0);
        auto backing = fill(254,53,395,158);
        put(rdram, Output + 8, backing[0]); put(rdram, Output + 12, backing[1]);
        wr64_course_preview_prepare(rdram, Output);
        ctx.r4 = S32(Output + 16);
        Function functions[] = {baseline_func_i4_802C6778,func_i4_802C6778,regenerated_func_i4_802C6778};
        functions[version](rdram, &ctx);
    }
    else {
        Function functions[] = {baseline_func_i4_802C5CDC,func_i4_802C5CDC,regenerated_func_i4_802C5CDC};
        functions[version](rdram, &ctx);
    }
    const uint32_t end = uint32_t(ctx.r2);
    require(end >= Output && end < Output + 0x5000, "native producer returned an invalid cursor");
    Packets packets;
    for (uint32_t p = Output; p < end; p += 8) packets.push_back({get(rdram,p),get(rdram,p+4)});
    require(preserved(rdram) == before, "native drawing modified camera, records, animation, font, viewport or shared depth assets");
    if (mapOnly) wr64_course_preview_finish(rdram, end);
    require(wr64_course_preview_x(299) == 299, "preview translation leaked after menu finish");
    return {packets, calls, before, state};
}

Packets normalizeMapAndMenu(const Result& before, const Result& after, const Settings& s) {
    const auto& source = after.packets;
    require(source.size() == before.packets.size() + 16, "preview must add exactly128display-list bytes");
    require(source[0] == before.packets[0], "backing setup changed");
    require(source[1] == fill(150,53,395,158), "backing must fill the enlarged crop");
    Packets normal{source[0], before.packets[1]};
    const auto depth = ipsSelectedDepthFixture();
    for (size_t i = 0; i < 12; ++i) {
        auto expected = depth[i];
        // The active IPS bank already owns width424 and depth0x00700000.
        // Only the fill's left edge may change; every other word must match.
        if (i == 11) expected = fill(150,53,395,158);
        require(source[2+i] == expected, "inlined depth state/pointer/stride/rectangle mismatch");
    }
    normal.push_back({0x06000000,0x080A6E00});
    size_t p = 14;
    for (size_t native = 1; native < 21; ++native) {
        if (native == 6) {
            require(source[p++] == Packet{0x00525464,0x10000064}, "viewport extension enable missing");
            require(source[p++] == Packet{0x64000007,0x800}, "preview viewport alignment missing");
            require(source[p++] == Packet{uint32_t(uint16_t(-208)) << 16,0}, "preview center offset must be -52pixels");
        }
        auto packet = source[p++];
        if (native == 9) {
            require(packet == Packet{0xED2580D4,0x0063027C}, "scissor must be150,53..396,159");
            packet[0] = 0xED3F80D4;
        }
        normal.push_back(packet);
        if (native == 6) {
            require(source[p++] == Packet{0x64000007,0x800}, "viewport alignment reset missing");
            require(source[p++] == Packet{0,0}, "viewport alignment reset leaked offsets");
        }
    }
    require(p == 39, "map packet accounting changed");
    size_t b = 23;
    while (p < source.size()) {
        auto packet = source[p++];
        require(b < before.packets.size(), "extra unexpected menu packet");
        const auto baseline = before.packets[b++];
        if (packet[0] >> 24 == 0xF6 && baseline[0] >> 24 == 0xF6) {
            // The only post-map fill is the original difficulty open/close
            // mask. Its native controller and all Y/count state stay intact.
            const int left = (baseline[1] >> 14) & 0x3FF;
            const int end = ((baseline[0] >> 14) & 0x3FF) + 1;
            auto edge = [](int x) { return 150 + ((x-254)*246 + 71)/142; };
            auto expected = baseline;
            if (left >= 254 && left <= 396 && end >= left && end <= 396) {
                expected[0] = (expected[0] & ~0x00FFC000U) | uint32_t(edge(end)-1) << 14;
                expected[1] = (expected[1] & ~0x00FFC000U) | uint32_t(edge(left)) << 14;
            }
            require(packet == expected, "difficulty mask lost native animation proportions/Y or enlarged coverage");
            packet = baseline;
        }
        else if (baseline[0] >> 24 == 0xE4) {
            // Actual native difficulty frame and 2P handicap texture strips
            // translate uniformly; textureUV, tile, scale and Y are exact.
            require(packet == translate(baseline,-52), "difficulty/handicap rectangle must translate intact");
            packet = baseline;
        }
        normal.push_back(packet);
    }
    return normal;
}
void compare(const Result& before, Result after, const Settings& s, bool active) {
    require(before.animation == after.animation, "native open/close controller state changed");
    require(before.preserved == after.preserved, "layout changed native shared camera/menu/save state");
    if (!active) { require(before == after, "disabled or rejected preview must equal native output exactly"); return; }
    require(normalizeMapAndMenu(before, after, s) == before.packets,
        "preview changed unrelated map geometry, projection, renderstate or menu packets");
    require(after.calls.size() == before.calls.size(), "native text/frame call count changed");
    unsigned records = 0, numeric = 0;
    for (size_t i = 0; i < before.calls.size(); ++i) {
        const auto& native = before.calls[i];
        auto& changed = after.calls[i];
        int field = -1;
        if (native.kind == 1 && native.args[1] == 275) { field = 1; ++records; }
        if (native.kind == 2 && native.args[2] >= 250) field = 2;
        if (native.kind >= 4 && native.kind <= 6) { field = 2; ++numeric; }
        if (native.kind == 7) field = 0;
        if (field >= 0) {
            require(changed.args[field] == native.args[field] - 52, "record/modal producer X shift mismatch");
            if (native.kind == 1) {
                const float frameCenter = changed.args[1] + changed.args[3] * 0.5f;
                require(frameCenter == 273.5f, "record frames do not center under the expanded preview");
                const float width = RT64::wr64UltrawideLogicalWidth();
                const float expansion = width / 424.0f;
                const auto layout = RT64::wr64UltrawideLayout(expansion,1.0f,424);
                require(std::abs(layout.position(frameCenter * expansion) -
                    layout.position(273.0f * expansion)) <= 0.501f,
                    "record/map center alignment changed at this presentation ratio");
            }
            changed.args[field] += 52;
            require(changed.glyphs.size() == native.glyphs.size(), "record glyph count changed");
            if (native.kind >= 4 && native.kind <= 6)
                require(native.glyphs.size() == (native.kind == 4 ? 5 : 8), "native record formatter did not replay every glyph");
            for (auto& glyph : changed.glyphs) glyph.x += 52;
        }
        require(changed == native, "layout changed glyph values/spacing/font/style/Y or unrelated labels");
    }
    if (!before.calls.empty()) {
        require(records == (s.score ? 2 : 4), "missing record frame coverage");
        require(numeric == (s.score ? 1 : 2), "missing record number/string coverage");
    }
}
void scenario(const Settings& s, bool disabled, bool mapOnly = false) {
    ++scenarios;
    context = "case" + std::to_string(scenarios) + " stat=" + std::to_string(s.stat) +
        " players=" + std::to_string(s.players) + " course=" + std::to_string(s.course) +
        " mask=" + std::to_string(s.mask) + " fault=" + std::to_string(s.fault);
    auto before = run(0,s,mapOnly);
    auto current = run(1,s,mapOnly);
    require(current == run(2,s,mapOnly), "checked-in producer differs from regenerated hook recipe");
    compare(before, current, s, !disabled && s.stat == 5 && (s.players == 1 || s.players == 2) && s.fault == 0);
}

void atomicRejection(bool disabled) {
    std::vector<uint8_t> memory(8 * 1024 * 1024), unrelated(8 * 1024 * 1024);
    uint8_t* rdram = memory.data();
    for (int fault = 0; fault < 17; ++fault) {
        context = "atomic map rewrite " + std::to_string(fault);
        std::fill(memory.begin(),memory.end(),0);
        Settings settings;
        if (fault >= 11) settings.fault = fault - 1; // obsolete/mixed source banks
        seed(rdram,settings);
        put(rdram,Output,0x06000000); put(rdram,Output+4,0x080A6DB0);
        const auto backing = fill(254,53,395,158);
        put(rdram,Output+8,backing[0]); put(rdram,Output+12,backing[1]);
        for (int offset = -32; offset < 0; offset += 4) put(rdram,Output+offset,0xAABBCCDD);
        for (int offset = 16+296; offset < 16+328; offset += 4) put(rdram,Output+offset,0x11223344);
        wr64_course_preview_prepare(rdram,Output);
        wr64_course_preview_map_begin(rdram,Output + (fault == 1 ? 24 : 16));
        recomp_context ctx{}; ctx.f_odd=&ctx.f0.u32h; ctx.r4=S32(Output+16); ctx.r29=S32(Stack);
        baseline_func_i4_802C6778(rdram,&ctx);
        const uint32_t nativeEnd = uint32_t(ctx.r2);
        require(nativeEnd == Output+16+168,"native map extent unexpectedly changed");
        if (fault == 3) put(rdram,0x801CE638,4);
        if (fault == 4) MEM_H(0,S32(0x801CE60C))=3;
        if (fault == 6) put(rdram,Output+16+6*8+4,0x0106F748);
        if (fault == 7) put(rdram,Output+16+12*8,0xDE000000);
        if (fault == 8) put(rdram,Output+16+2*8,0xFF10013F);
        if (fault == 9) put(rdram,Output,0x06000001);
        if (fault == 10) put(rdram,Output+12,fill(255,53,395,158)[1]);
        const auto snapshot = memory;
        const uint32_t suppliedEnd = fault == 2 ? nativeEnd-8 : nativeEnd;
        const uint32_t result = wr64_course_preview_map_end(fault == 5 ? unrelated.data() : rdram,suppliedEnd);
        if (disabled || fault) {
            require(result == suppliedEnd,"rejected map rewrite moved the output cursor");
            require(memory == snapshot,"rejected map rewrite partially changed RDRAM");
            require(wr64_course_preview_x(299) == 299,"rejected map rewrite enabled record translation");
        }
        else {
            require(result == nativeEnd+128,"accepted map rewrite byte count mismatch");
            require(wr64_course_preview_x(299) == 247,"accepted map did not activate scoped UI translation");
            for (int offset = -32; offset < 0; offset += 4)
                require(get(rdram,Output+offset)==0xAABBCCDD,"map rewrite wrote before its owned output");
            for (int offset = 16+296; offset < 16+328; offset += 4)
                require(get(rdram,Output+offset)==0x11223344,"map rewrite wrote beyond its owned output");
            for (auto packet : {Packet{0xED3F80D4,0x0063027C},fill(10,53,20,158),fill(390,53,398,158)}) {
                put(rdram,Output+400,packet[0]); put(rdram,Output+404,packet[1]);
                wr64_course_preview_mask(rdram,Output+400);
                require(Packet{get(rdram,Output+400),get(rdram,Output+404)}==packet,
                    "mask helper changed an unrelated packet/rectangle");
            }
        }
        wr64_course_preview_finish(rdram,result);
        require(wr64_course_preview_x(299)==299,"finish leaked preview state");
        require(wr64_course_preview_rect_x(0xE4600278)==0xE4600278,"finish leaked rectangle translation");
    }
}
}

int main(int argc, char**) {
    const bool disabled = argc > 1;
    atomicRejection(disabled);
    for (float aspect : {4.0f/3.0f,16.0f/9.0f,21.0f/9.0f,32.0f/9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for (int course = 0; course < 9; ++course) for (int variant = 0; variant < 2; ++variant)
            for (int players : {1,2}) for (int records = 0; records < 3; ++records) {
                Settings s;
                s.course=course; s.variant=variant; s.players=players; s.buffer=course%3;
                s.score=records==2; s.difficulty=records==1 ? 3 : 0;
                for (int menu : {0,1}) { s.menu=menu; scenario(s,disabled); }
            }
        for (int players : {1,2}) for (int request : {1,2}) for (int tick = 0; tick < 6; ++tick) {
            Settings s; s.players=players; s.request=request; s.mask=tick; s.menu=request==2;
            scenario(s,disabled);
        }
        for (int stat : {0,4,5,10}) for (int players : {0,1,2,3}) {
            Settings s; s.stat=stat; s.players=players; s.menu=1; scenario(s,disabled);
        }
        for (int fault = 1; fault <= 15; ++fault) {
            Settings s; s.fault=fault; s.menu=1; scenario(s,disabled);
        }
        for (int course = 0; course < 9; ++course) for (int variant : {0,1}) {
            Settings s; s.course=course; s.variant=variant; scenario(s,disabled,true);
        }
    }
    std::cout << "Native Course Select preview " << (disabled ? "disabled" : "enabled") << ": "
        << scenarios << " scenarios; " << assertions << " assertions passed.\n";
}
