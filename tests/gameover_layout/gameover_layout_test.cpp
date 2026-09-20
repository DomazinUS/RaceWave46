#include "recomp.h"
#include "common/rt64_wr64_ultrawide.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
unsigned assertions = 0;
void require(bool condition, const char* reason) {
    ++assertions;
    if (!condition) { std::cerr << reason << '\n'; std::exit(1); }
}
enum class Kind { Frame, FontState, Label, Number };
constexpr uint32_t StateStart = 0x802C7A00U;
constexpr size_t StateWords = 96;
using State = std::array<uint32_t, StateWords>;
struct Call {
    Kind kind;
    // Includes all argument-register and outgoing-stack slots through arg 14,
    // even the unused slots, to detect accidental changes beyond the six Xs.
    std::array<uint32_t, 14> args;
    State state;
    bool operator==(const Call&) const = default;
};
std::vector<Call> calls;
State state(uint8_t* rdram) {
    State result;
    for (size_t i = 0; i < result.size(); ++i) result[i] = MEM_W(i * 4, S32(StateStart));
    return result;
}
void capture(Kind kind, uint8_t* rdram, recomp_context* ctx) {
    Call call{kind, {uint32_t(ctx->r4), uint32_t(ctx->r5), uint32_t(ctx->r6), uint32_t(ctx->r7)}, state(rdram)};
    for (size_t i = 4; i < call.args.size(); ++i) call.args[i] = MEM_W(i * 4, ctx->r29);
    calls.push_back(call);
    // Keep the real caller's display-list cursor flow, using a synthetic
    // command size. The renderer and cartridge assets are not run here.
    ctx->r2 = ADD32(ctx->r4, 8);
}
}

extern "C" {
void func_i5_802C7698(uint8_t*, recomp_context*);
void baseline_func_i5_802C7698(uint8_t*, recomp_context*);
void regenerated_func_i5_802C7698(uint8_t*, recomp_context*);
void func_80094338(uint8_t* rdram, recomp_context* ctx) { capture(Kind::Frame, rdram, ctx); }
void func_801E946C(uint8_t* rdram, recomp_context* ctx) { capture(Kind::FontState, rdram, ctx); }
void func_801E3EE0(uint8_t* rdram, recomp_context* ctx) { capture(Kind::Label, rdram, ctx); }
void func_801EB00C(uint8_t* rdram, recomp_context* ctx) { capture(Kind::Number, rdram, ctx); }
void do_break(uint32_t) { std::abort(); }
void switch_error(const char*, uint32_t, uint32_t) { std::abort(); }
}

namespace {
using Function = void (*)(uint8_t*, recomp_context*);
struct Result {
    std::vector<Call> calls;
    std::array<uint32_t, 16> commands;
    std::array<uint32_t, 16> stack;
    State finalState;
    bool operator==(const Result&) const = default;
};
Result run(Function function, int requiredX, int myX, int requiredPoints, int myPoints) {
    static std::vector<uint8_t> memory(4 * 1024 * 1024);
    uint8_t* rdram = memory.data();
    for (int i = 0; i < 256; i += 4) MEM_W(i, S32(0x80002000)) = 0;
    for (int i = 0; i < 256; i += 4) MEM_W(i, S32(0x800FFF80)) = 0x13579BDFU;
    for (size_t i = 0; i < StateWords; ++i) MEM_W(i * 4, S32(StateStart)) = 0x10203040U + uint32_t(i);
    MEM_W(0, S32(0x802C7ACC)) = requiredX;
    MEM_W(0, S32(0x802C7AD0)) = myX;
    MEM_W(0, S32(0x802C7B34)) = requiredPoints;
    MEM_W(0, S32(0x802C7B30)) = myPoints;
    const State initialState = state(rdram);
    recomp_context ctx{};
    ctx.f_odd = &ctx.f0.u32h;
    ctx.r29 = S32(0x80100000);
    ctx.r31 = S32(0x80123400);
    ctx.r4 = S32(0x80002000);
    calls.clear();
    function(rdram, &ctx);
    require(calls.size() == 7, "Game Over did not issue exactly six draws and one font setup");
    require(uint32_t(ctx.r2) == 0x80002040, "Native display-list cursor chain changed");
    require(uint32_t(ctx.r29) == 0x80100000 && uint32_t(ctx.r31) == 0x80123400,
        "Native caller did not restore its stack and return address");
    require(state(rdram) == initialState, "Drawing changed Game Over animation or scoring state");
    for (const auto& call : calls) require(call.state == initialState, "A draw temporarily shifted animation globals");
    Result result{calls, {}, {}, state(rdram)};
    for (size_t i = 0; i < result.commands.size(); ++i) {
        result.commands[i] = MEM_W(i * 4, S32(0x80002000));
        result.stack[i] = MEM_W(i * 4, S32(0x800FFFC0));
    }
    return result;
}
void checkNativeFields(const Result& result, int requiredX, int myX, int requiredPoints, int myPoints, int offset) {
    const auto& c = result.calls;
    require(c[0].kind == Kind::Frame && c[1].kind == Kind::Frame && c[2].kind == Kind::FontState &&
        c[3].kind == Kind::Label && c[4].kind == Kind::Label && c[5].kind == Kind::Number && c[6].kind == Kind::Number,
        "Native draw order changed");
    for (size_t row = 0; row < 2; ++row) {
        const uint32_t x = uint32_t((row ? myX : requiredX) + offset);
        require(c[row].args[1] == 0 && c[row].args[2] == x && c[row].args[3] == 145 + 21 * row &&
            c[row].args[4] == 208 && c[row].args[5] == 15, "Frame kind, position, width, or height changed");
        require(c[3 + row].args[1] == 1 && c[3 + row].args[2] == 6 + row && c[3 + row].args[3] == x + 10 &&
            c[3 + row].args[4] == 147 + 21 * row && c[3 + row].args[5] == 0,
            "Label identity, native inset, Y, or flags changed");
        require(c[5 + row].args[1] == 2 && c[5 + row].args[2] == uint32_t(row ? myPoints : requiredPoints) &&
            c[5 + row].args[3] == x + 186 && c[5 + row].args[4] == 147 + 21 * row,
            "Numeric score, font type, native inset, or Y changed");
    }
    require(c[2].args[1] == 0, "Font flags changed");
    for (size_t i = 2; i < 14; ++i) require(c[2].args[i] == 255, "Native white font gradient changed");
}
}

int main() {
    unsigned scenarios = 0;
    const std::array<std::array<int, 2>, 5> scores{{{2, 1}, {0, 0}, {10, 9}, {28, 28}, {999, 2147483647}}};
    for (float aspect : {4.0f / 3.0f, 16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        const float expansion = RT64::wr64UltrawideExpansion(aspect);
        const auto layout = RT64::wr64UltrawideLayout(expansion, 1.0f, 424);
        for (int requiredX = -360; requiredX <= 680; requiredX += 4) {
            // Native sequence enters/exits with the second row reflected about
            // its settled X=56. Include offscreen positions on both sides.
            const int myX = 112 - requiredX;
            for (const auto& score : scores) {
                auto before = run(baseline_func_i5_802C7698, requiredX, myX, score[0], score[1]);
                auto after = run(func_i5_802C7698, requiredX, myX, score[0], score[1]);
                auto regenerated = run(regenerated_func_i5_802C7698, requiredX, myX, score[0], score[1]);
                require(after == regenerated, "Durable hook regeneration differs from checked-in native caller");
                checkNativeFields(before, requiredX, myX, score[0], score[1], 0);
                checkNativeFields(after, requiredX, myX, score[0], score[1], 52);
                for (auto& call : after.calls) {
                    if (call.kind == Kind::Frame) call.args[2] -= 52;
                    else if (call.kind == Kind::Label || call.kind == Kind::Number) call.args[3] -= 52;
                }
                require(after == before, "The centering correction changed more than the six draw X arguments");
                ++scenarios;
            }
        }
        auto settled = run(func_i5_802C7698, 56, 56, 2, 1);
        for (size_t row = 0; row < 2; ++row) {
            const auto& frame = settled.calls[row];
            const float center = float(frame.args[2]) + float(frame.args[4]) * 0.5f;
            const float screenCenter = layout.position(center * expansion);
            require(std::abs(screenCenter - layout.width * 0.5f) < 0.0001f,
                "Settled Game Over stats do not center on the displayed menu plane");
            // Negative control documents the observed 52-unit displacement.
            require(std::abs(layout.position(160.0f * expansion) - (layout.width * 0.5f - 52.0f)) < 0.0001f,
                "Baseline no longer demonstrates the reported off-center stats");
        }
    }
    std::cout << "Passed " << scenarios << " native Game Over scenarios, " << scenarios * 6
        << " draw-coordinate comparisons, " << assertions << " assertions.\n";
}
