#include "recomp.h"
#include "wr64_free_ride.h"
#include <array>
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
void func_800C21F4(uint8_t*, recomp_context*);
void baseline_func_800C21F4(uint8_t*, recomp_context*);
void n_alSynRemovePlayer(uint8_t*, recomp_context*);
void AudioThread_QueueCmdS8(uint8_t*, recomp_context*);
}
using Function = void (*)(uint8_t*, recomp_context*);
using Command = std::array<uint32_t, 2>;
static std::vector<Command> commands;
static std::vector<std::array<uint32_t, 4>> dependencyCalls;
static unsigned checks = 0, starts = 0;
static std::string description;
static void require(bool condition, const char* message) {
    ++checks;
    if (!condition) {
        std::cerr << description << ": " << message << '\n';
        std::exit(1);
    }
}
extern "C" void AudioThread_QueueCmd(uint8_t* rdram, recomp_context* ctx) {
    commands.push_back({uint32_t(ctx->r4), uint32_t(MEM_W(0, ctx->r5))});
}
extern "C" void music_fixture_stub(uint32_t id, recomp_context* ctx) {
    dependencyCalls.push_back({id, uint32_t(ctx->r4), uint32_t(ctx->r5), uint32_t(ctx->r6)});
}
extern "C" void switch_error(const char*, uint32_t, uint32_t) {
    require(false, "unexpected native switch target");
}
extern "C" void do_break(uint32_t) { require(false, "unexpected native break"); }

struct Replay {
    std::vector<uint8_t> memory = std::vector<uint8_t>(8 * 1024 * 1024);
    recomp_context ctx{};
    uint32_t word(uint32_t address) const {
        uint32_t value;
        std::memcpy(&value, memory.data() + (address & 0x7FFFFF), 4);
        return value;
    }
    void word(uint32_t address, uint32_t value) {
        std::memcpy(memory.data() + (address & 0x7FFFFF), &value, 4);
    }
    void reset_context() {
        ctx = {};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r31 = S32(0x80654320);
    }
    Replay() {
        reset_context();
        word(0x800D8170, 0); word(0x800DAB28, 2); word(0x801CE638, 1);
        word(0x800DAB24, 40); word(0x801CE608, 1); word(0x801CE620, 1);
        word(0x801D7DC0, 1); // Native VS audio kind.
        word(0x800E7C98, 1); // Native music enabled.
        word(0x801D7DCC, 0x19); // Previous screen's track must be replaced.
    }
    void run(Function fn) {
        ctx.f_odd = &ctx.f0.u32h;
        fn(memory.data(), &ctx);
    }
    void initialize(Function fn = func_800C21F4, unsigned audioEvent = 7) {
        reset_context();
        ctx.r4 = audioEvent;
        ctx.r5 = word(0x800D8170);
        run(fn);
        require(ctx.r29 == S32(0x80700000) && ctx.r31 == S32(0x80654320), "initializer stack/return changed");
    }
    void tick(unsigned count) {
        for (unsigned i = 0; i < count; ++i) {
            reset_context();
            run(n_alSynRemovePlayer);
            require(ctx.r29 == S32(0x80700000) && ctx.r31 == S32(0x80654320), "scheduler stack/return changed");
        }
    }
};
static unsigned command_count(uint32_t command) {
    unsigned count = 0;
    for (auto row : commands) count += row[0] == command;
    return count;
}
static void equivalent(const Replay& fixture, unsigned event = 7) {
    Replay baseline = fixture, current = fixture;
    commands.clear(); dependencyCalls.clear();
    baseline.initialize(baseline_func_800C21F4, event);
    const auto oldCommands = commands;
    const auto oldCalls = dependencyCalls;
    commands.clear(); dependencyCalls.clear();
    current.initialize(func_800C21F4, event);
    require(oldCommands == commands && oldCalls == dependencyCalls, "out-of-scope native calls changed");
    require(baseline.memory == current.memory, "out-of-scope native RAM changed");
    baseline.ctx.f_odd = current.ctx.f_odd = nullptr;
    require(std::memcmp(&baseline.ctx, &current.ctx, sizeof(recomp_context)) == 0,
            "out-of-scope native registers changed");
}

int main() {
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    _set_error_mode(_OUT_TO_STDERR);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif
    description = "native VS preload lacks start event";
    Replay baseline;
    commands.clear(); baseline.initialize(baseline_func_800C21F4);
    require(command_count(0x81000600) == 1, "native VS did not preload Dolphin track6");
    require(baseline.word(0x801D7DCC) == 6, "native VS did not select Dolphin track6");
    require(baseline.word(0x800E7CD8) == 0, "native VS unexpectedly scheduled course0 music");
    baseline.tick(24);
    require(command_count(0x82020601) == 0, "negative control unexpectedly started Dolphin music");

    description = "Free Ride starts once and restarts once per native initialization";
    Replay current;
    for (unsigned restart = 0; restart < 3; ++restart) {
        commands.clear(); current.initialize();
        require(command_count(0x81000600) == 1, "native preload changed");
        require(current.word(0x800E7CD8) == 8, "Warm Up countdown not scheduled");
        require(current.word(0x801D7DCC) == 6, "Dolphin track selection changed");
        require(command_count(0x82020601) == 0, "music started before native countdown");
        current.tick(7);
        require(command_count(0x82020601) == 0 && current.word(0x800E7CD8) == 1, "early or stalled start");
        current.tick(1);
        require(command_count(0x82020601) == 1 && current.word(0x800E7CD8) == 0, "native start command absent");
        require(command_count(0x41020000) == 1, "native sequence volume setup absent");
        for (auto row : commands) {
            if (row[0] == 0x82020601) require(row[1] == 0, "native music fade-in argument changed");
            if (row[0] == 0x41020000) require(row[1] == 0x3F0CCCCD, "native music volume changed");
        }
        current.tick(120);
        require(command_count(0x82020601) == 1, "music retriggered during ordinary updates");
        ++starts;
    }

    description = "only music countdown differs at initialization";
    Replay oldInit, newInit;
    commands.clear(); dependencyCalls.clear(); oldInit.initialize(baseline_func_800C21F4);
    const auto oldCommands = commands;
    const auto oldCalls = dependencyCalls;
    commands.clear(); dependencyCalls.clear(); newInit.initialize();
    require(commands == oldCommands && dependencyCalls == oldCalls, "native initializer/audio/SFX calls changed");
    newInit.word(0x800E7CD8, oldInit.word(0x800E7CD8));
    require(newInit.memory == oldInit.memory, "initializer changed state outside music countdown");

    description = "music setting and other native states preserved";
    const std::array<std::array<uint32_t, 2>, 13> negatives{{
        {0x800E7C98, 0}, {0x800D8170, 1}, {0x800D8170, 2}, {0x800D8170, 7},
        {0x800DAB28, 1}, {0x801CE638, 0}, {0x801CE638, 2}, {0x800DAB24, 20},
        {0x801CE608, 4}, {0x801CE620, 4}, {0x801D7DC0, 0}, {0x801D7DC0, 2}, {0x801D7DC0, 3}}};
    for (auto change : negatives) {
        Replay r; r.word(change[0], change[1]); equivalent(r);
    }
    Replay muted; muted.word(0x800E7C98, 0); commands.clear(); muted.initialize(); muted.tick(24);
    require(command_count(0x82020601) == 0, "native music-off setting overridden");
    for (unsigned event : {0u,1u,2u,3u,4u,5u,6u,8u,9u,10u,11u,12u}) equivalent(Replay{}, event);

    description = "single-player Warm Up keeps original music path";
    Replay warmup; warmup.word(0x800DAB28, 1); warmup.word(0x801CE608, 4);
    warmup.word(0x801CE620, 4); warmup.word(0x801D7DC0, 0);
    equivalent(warmup);
    commands.clear(); warmup.initialize(); warmup.tick(8);
    require(command_count(0x82020601) == 1, "Warm Up native music no longer starts");

    description = "speech filter remains separate from music";
    Replay r; r.reset_context(); r.ctx.r4 = 0x06000C00; r.ctx.r5 = 127;
    commands.clear(); r.run(AudioThread_QueueCmdS8);
    require(commands.empty(), "narrator speech filter regressed");
    require(!wr64_free_ride_skip_audio(r.memory.data(), 0x82020601), "music command classified as speech");
    require(!wr64_free_ride_skip_audio(r.memory.data(), 0x41020000), "music volume classified as speech");
    wr64_free_ride_schedule_music(nullptr);
    r.word(0x801D7DC4, 2); r.word(0x801D7DCC, 6);
    const auto mismatched = r.memory;
    wr64_free_ride_schedule_music(r.memory.data());
    require(r.memory == mismatched, "mismatched native audio course admitted");
    r.word(0x801D7DC4, 0); r.word(0x801D7DCC, 3);
    const auto wrongTrack = r.memory;
    wr64_free_ride_schedule_music(r.memory.data());
    require(r.memory == wrongTrack, "wrong native track admitted");
    std::cout << "{\"status\":\"passed\",\"checks\":" << checks
              << ",\"native_music_start_cycles\":" << starts
              << ",\"sequence\":6,\"actual_game_launched\":false}\n";
}
