#include "recomp.h"
#include "wr64_free_ride.h"

#include <array>
#include <bit>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#include <crtdbg.h>
#endif

extern "C" {
#define NATIVE(name) void name(uint8_t*, recomp_context*); void baseline_##name(uint8_t*, recomp_context*);
NATIVE(func_800762D0)
NATIVE(func_800C32A0)
NATIVE(func_800C377C)
NATIVE(AudioThread_QueueCmdS8)
NATIVE(func_i1_802C5DF4)
NATIVE(func_801F4120)
NATIVE(func_801FBFB4)
#undef NATIVE
}
using Function = void (*)(uint8_t*, recomp_context*);
static unsigned checks = 0;
static std::string description;
static void require(bool value, const char* message) {
    ++checks;
    if (!value) {
        std::cerr << description << ": " << message << '\n';
        std::exit(1);
    }
}
static std::vector<std::array<uint32_t, 2>> audio;
static unsigned resultCalls = 0, timerCalls = 0, sceneAudioCalls = 0;
extern "C" void AudioThread_QueueCmd(uint8_t* rdram, recomp_context* ctx) {
    audio.push_back({uint32_t(ctx->r4), uint32_t(MEM_W(0, ctx->r5))});
}
extern "C" void func_801F25E0(uint8_t*, recomp_context*) { ++timerCalls; }
extern "C" void func_800BFDD0(uint8_t*, recomp_context*) { ++sceneAudioCalls; }
extern "C" void func_800BFE70(uint8_t*, recomp_context*) { ++sceneAudioCalls; }
extern "C" void func_800BFEF8(uint8_t*, recomp_context*) { ++sceneAudioCalls; }
extern "C" void func_i1_802C6FE0(uint8_t*, recomp_context*) { ++resultCalls; }
extern "C" void func_i1_802C6DCC(uint8_t*, recomp_context*) { ++resultCalls; }
extern "C" void func_i1_802C7394(uint8_t*, recomp_context*) { ++resultCalls; }
extern "C" void do_break(uint32_t) { require(false, "unexpected native break"); }

struct Replay {
    std::vector<uint8_t> memory = std::vector<uint8_t>(8 * 1024 * 1024);
    recomp_context ctx{};
    uint32_t word(uint32_t address) const {
        uint32_t v;
        std::memcpy(&v, memory.data() + (address & 0x7FFFFF), 4);
        return v;
    }
    void word(uint32_t address, uint32_t value) {
        std::memcpy(memory.data() + (address & 0x7FFFFF), &value, 4);
    }
    void half(uint32_t address, uint16_t value) {
        std::memcpy(memory.data() + ((address & 0x7FFFFF) ^ 2), &value, 2);
    }
    void number(uint32_t address, float value) { word(address, std::bit_cast<uint32_t>(value)); }
    void reset_context() {
        ctx = {};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r31 = S32(0x80654320);
    }
    Replay() {
        reset_context();
        word(0x800D8170, 0);
        word(0x800DAB28, 2);
        word(0x801CE638, 1);
        word(0x800DAB24, 40);
        word(0x801CE608, 1);
        word(0x801CE620, 1);
        word(0x800D48DC, 0);
        word(0x800D48E0, 2);
        half(0x801CE624, 0xFFFF);
        number(0x801C39B4, 12.5f);
        number(0x800E9D94, 0.25f); // Native retirement ordering increment.
        word(0x80510000, 0x80500000);
    }
    void run(Function fn) {
        ctx.f_odd = &ctx.f0.u32h;
        fn(memory.data(), &ctx);
    }
};
static bool same_context(recomp_context a, recomp_context b) {
    a.f_odd = b.f_odd = nullptr;
    return std::memcmp(&a, &b, sizeof(a)) == 0;
}
static void equivalent(const Replay& fixture, Function baseline, Function patched) {
    Replay a = fixture, b = fixture;
    audio.clear(); resultCalls = timerCalls = sceneAudioCalls = 0;
    a.run(baseline);
    const auto oldAudio = audio;
    const auto oldResults = resultCalls, oldTimers = timerCalls, oldScene = sceneAudioCalls;
    audio.clear(); resultCalls = timerCalls = sceneAudioCalls = 0;
    b.run(patched);
    require(a.memory == b.memory, "out-of-scope native RAM changed");
    require(same_context(a.ctx, b.ctx), "out-of-scope native registers changed");
    require(oldAudio == audio && oldResults == resultCalls && oldTimers == timerCalls && oldScene == sceneAudioCalls,
            "out-of-scope native calls changed");
}

int main() {
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    _set_error_mode(_OUT_TO_STDERR);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif
    description = "exact Free Ride identity";
    Replay base;
    require(wr64_free_ride_active(nullptr) == 0, "null RDRAM admitted");
    require(wr64_free_ride_active(base.memory.data()) == 1, "2P Dolphin VS rejected");
    for (unsigned mode = 0; mode <= 60; ++mode) {
        Replay r = base; r.word(0x800DAB24, mode);
        require(bool(wr64_free_ride_active(r.memory.data())) == (mode >= 40 && mode <= 45), "native mode scope");
    }
    const std::array<std::array<uint32_t, 2>, 9> negatives{{
        {0x800D8170, 1}, {0x800D8170, 7}, {0x800DAB28, 1}, {0x800DAB28, 4},
        {0x801CE638, 0}, {0x801CE638, 2}, {0x801CE608, 4}, {0x801CE620, 4}, {0x801CE620, 11}}};
    for (auto change : negatives) {
        Replay r = base; r.word(change[0], change[1]);
        require(!wr64_free_ride_active(r.memory.data()), "single-player/other-course/phase/kind admitted");
        r.ctx.r4 = S32(0x801C2938);
        equivalent(r, baseline_func_800762D0, func_800762D0);
        r.reset_context(); r.ctx.r4 = 0x06000C00; r.ctx.r5 = 127;
        equivalent(r, baseline_AudioThread_QueueCmdS8, AudioThread_QueueCmdS8);
        r.reset_context();
        equivalent(r, baseline_func_i1_802C5DF4, func_i1_802C5DF4);
    }

    description = "selected-rider retirement guard";
    for (unsigned rider = 0; rider < 4; ++rider) {
        const uint32_t record = 0x801C2938 + rider * 0x378;
        for (uint32_t elapsed : {0u, 599998u, 599999u, 600000u}) {
            Replay r = base; r.word(record + 0x19C, elapsed); r.ctx.r4 = S32(record);
            const bool selected = rider == 0 || rider == 2;
            require(bool(wr64_free_ride_skip_retirement(r.memory.data(), record)) == selected, "record selection guard");
            if (!selected) {
                equivalent(r, baseline_func_800762D0, func_800762D0);
                continue;
            }
            Replay old = r; old.run(baseline_func_800762D0);
            require(old.word(record + 0x2EC) == (elapsed >= 599999 ? 2u : 1u), "negative control did not retire");
            const auto before = r.memory; const auto context = r.ctx;
            r.run(func_800762D0);
            require(r.memory == before && same_context(r.ctx, context), "retirement guard changed native state");
        }
    }
    for (uint32_t bad : {0u, 0x001C2938u, 0xA01C2938u, 0x801C2939u, 0x801C3718u}) {
        require(!wr64_free_ride_skip_retirement(base.memory.data(), bad), "invalid record admitted");
    }

    description = "speech-only queue filtering";
    for (uint32_t command : {0x06000C00u, 0x06000C01u, 0x06000C02u, 0x06000F00u, 0x01000C00u, 0x06000C03u, 0x46000C00u}) {
        Replay r = base; r.ctx.r4 = command; r.ctx.r5 = 127;
        const Replay commandFixture = r;
        const bool speech = command >= 0x06000C00 && command <= 0x06000C02;
        audio.clear(); r.run(AudioThread_QueueCmdS8);
        require(audio.size() == (speech ? 0 : 1), "speech/engine/music/SFX command filter");
        if (!speech) equivalent(commandFixture, baseline_AudioThread_QueueCmdS8, AudioThread_QueueCmdS8);
    }
    for (auto pair : {std::array<Function,2>{baseline_func_800C32A0, func_800C32A0},
                     std::array<Function,2>{baseline_func_800C377C, func_800C377C}}) {
        Replay old = base, r = base;
        old.ctx.r4 = r.ctx.r4 = 23; old.ctx.r5 = r.ctx.r5 = 3; old.ctx.r6 = r.ctx.r6 = 9;
        audio.clear(); old.run(pair[0]); const size_t oldCount = audio.size();
        require(oldCount > 0, "native announcer negative control emitted nothing");
        audio.clear(); r.run(pair[1]); require(audio.empty(), "native tutorial/race voice still queued");
        require(std::memcmp(old.memory.data()+0x1D7DF0, r.memory.data()+0x1D7DF0, 8) == 0,
                "speech queue policy changed native scheduling state");
        require(r.ctx.r29 == old.ctx.r29 && r.ctx.r31 == old.ctx.r31, "speech caller stack/return changed");
    }

    description = "result-only tail bypass, native pause/control prelude";
    unsigned nativeResultCases = 0;
    for (unsigned flags = 0; flags < 16; ++flags) {
        Replay r = base;
        r.word(0x801C2938 + 0x2EC, flags & 1);
        r.word(0x801C2938 + 0x2F4, (flags >> 1) & 1);
        r.word(0x801C2938 + 2 * 0x378 + 0x2EC, (flags >> 2) & 1);
        r.word(0x801C2938 + 2 * 0x378 + 0x2F4, (flags >> 3) & 1);
        r.word(0x801CB3F0, 12); r.word(0x801CB3F4, 7);
        r.word(0x801CE650, 2); r.word(0x801CE648, 1);
        r.half(0x801CE6FC, 1); r.word(0x802C9440, 1);
        Replay old = r;
        resultCalls = 0; old.run(baseline_func_i1_802C5DF4); nativeResultCases += resultCalls != 0;
        resultCalls = 0; r.run(func_i1_802C5DF4);
        require(resultCalls == 0, "finish/retirement result transition survived");
        require(r.word(0x801CB3F0) == 12 && r.word(0x801CB3F4) == 7, "VS record/win counter changed");
        require(r.word(0x801CE648) == old.word(0x801CE648), "native pause/control prelude changed");
        require(r.word(0x801CE648) == 3, "native prelude negative control inactive");
        require(r.ctx.r29 == S32(0x80700000) && r.ctx.r31 == S32(0x80654320), "results epilogue skipped");
    }
    require(nativeResultCases > 0, "native result negative controls never transitioned");

    description = "native two-player timer block and explicit HUD scope";
    Replay old = base, r = base;
    old.ctx.r4 = r.ctx.r4 = S32(0x80510000);
    timerCalls = 0; old.run(baseline_func_801F4120);
    require(timerCalls == 2, "native 2P timer negative control");
    timerCalls = 0; r.run(func_801F4120);
    require(timerCalls == 0, "2P timer still emitted");
    require(r.ctx.r29 == old.ctx.r29, "timer block changed stack allocation");
    // The extraction script also compares the complete speed-rendering suffix.
    for (uint32_t site : {0x801F42FCu, 0x801FAEB8u, 0x801FBFB4u}) {
        require(wr64_free_ride_skip_hud(base.memory.data(), site), "confirmed competitive HUD site rejected");
    }
    for (uint32_t site : {0u, 0x801FC4D4u, 0x801F4120u, 0x801F6150u, 0x801F2060u}) {
        require(!wr64_free_ride_skip_hud(base.memory.data(), site), "speed/shared/warm-up HUD producer masked");
    }
    r = base; r.ctx.r4 = S32(0x80510000);
    const auto memoryBefore = r.memory; const auto contextBefore = r.ctx;
    r.run(func_801FBFB4);
    require(r.memory == memoryBefore && same_context(r.ctx, contextBefore), "VS-score skip changed caller state");
    std::cout << "{\"status\":\"passed\",\"checks\":" << checks
              << ",\"native_result_negative_controls\":" << nativeResultCases
              << ",\"actual_game_launched\":false}\n";
}
