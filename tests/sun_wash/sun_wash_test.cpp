// Execute the native wash gate, alpha arithmetic, flare chain, and wash
// display-list producer. Synthetic records isolate visibility from rendering.
#include "recomp.h"
#include "wr64_ultrawide.hpp"
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
void func_8008BD2C(uint8_t*, recomp_context*);
void baseline_func_8008BD2C(uint8_t*, recomp_context*);
void regenerated_func_8008BD2C(uint8_t*, recomp_context*);
void func_80051538(uint8_t*, recomp_context*);
void baseline_func_80051538(uint8_t*, recomp_context*);
void regenerated_func_80051538(uint8_t*, recomp_context*);
}
using Function = void (*)(uint8_t*, recomp_context*);
static unsigned checks = 0, cases = 0, unchanged = 0, continued = 0, delegated = 0;
static bool borders = true;
static std::string description;
static void require(bool condition, const char* message) {
    ++checks;
    if (!condition) {
        std::cerr << message << ": " << description << '\n';
        std::exit(1);
    }
}
extern "C" uint32_t wr64_experimental_viewport_borders() { return borders; }
extern "C" void func_8008A0E0(uint8_t* rdram, recomp_context* ctx) {
    require(MEM_W(0, S32(0x800D8170)) == 7 && MEM_W(0, S32(0x801CE638)) == 21,
        "unexpected course-specific sun delegation");
    ctx->r2 = ctx->r4;
    ++delegated;
}

struct Result {
    std::array<uint32_t, 8> state{};
    std::array<uint8_t, 0x140> records{};
    std::vector<uint32_t> flares;
    bool operator==(const Result&) const = default;
    int enabled() const { return int(state[0]); }
    int alpha() const { return int(state[5] >> 16); }
};

struct Replay {
    std::vector<uint8_t> memory = std::vector<uint8_t>(8 * 1024 * 1024);
    void number(uint32_t address, float value) {
        uint8_t* rdram = memory.data();
        MEM_W(0, S32(address)) = std::bit_cast<uint32_t>(value);
    }
    void constant(uint32_t address, double value) {
        uint8_t* rdram = memory.data();
        SD(std::bit_cast<uint64_t>(value), 0, S32(address));
    }
    Replay() {
        uint8_t* rdram = memory.data();
        MEM_B(0, S32(0x800DA624)) = 150;
        MEM_B(1, S32(0x800DA624)) = 127;
        MEM_B(2, S32(0x800DA624)) = 128;
        constant(0x800EAB98, 0.7);
        // Flare sizes and record coordinates are fixture values. The native
        // producer still computes and emits every flare command itself.
        for (uint32_t p = 0x801C41A0; p < 0x801C42A0; p += 4) number(p, 8.0f);
    }
    std::vector<uint32_t> commands(uint32_t end) {
        uint8_t* rdram = memory.data();
        require(end >= 0x80500000 && end < 0x80502000 && (end & 7) == 0,
            "invalid native display-list cursor");
        std::vector<uint32_t> result;
        for (uint32_t p = 0x80500000; p < end; p += 4) result.push_back(MEM_W(0, S32(p)));
        return result;
    }
    Result run(Function function, int course, float facing, float center, float y, float height, int mode, int radius) {
        uint8_t* rdram = memory.data();
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r31 = S32(0x80654320);
        ctx.r4 = S32(0x80500000);
        std::memset(rdram + 0x700000 - 0x200, 0, 0x400);
        std::memset(rdram + 0x500000, 0xA5, 0x2000);
        // Nonzero sentinels expose accidental writes or stale alpha changes.
        for (int i = 0; i < 8; ++i) MEM_W(i * 4, S32(0x800D47E0)) = 0x007B0035;
        MEM_W(0, S32(0x800D47E0)) = 0;
        MEM_W(0, S32(0x800D8170)) = course;
        MEM_W(course * 4, S32(0x800D9944)) = radius;
        MEM_W(0, S32(0x801CE638)) = mode;
        MEM_W(0, S32(0x80223930)) = 1; // Exercise selected camera stride 268.
        number(0x80227D00 + 268, height);
        const std::array<float, 6> record{center - 12, y, 1, 12, 12, facing};
        for (int i = 0; i < 6; ++i) number(0x801C4170 + i * 4, record[i]);
        std::array<uint8_t, 0x140> recordsBefore{};
        std::memcpy(recordsBefore.data(), rdram + 0x1C4170, recordsBefore.size());
        function(rdram, &ctx);
        require(uint32_t(ctx.r29) == 0x80700000 && uint32_t(ctx.r31) == 0x80654320,
            "native producer failed to restore stack or return register");
        Result result;
        for (int i = 0; i < 8; ++i) result.state[i] = MEM_W(i * 4, S32(0x800D47E0));
        std::memcpy(result.records.data(), rdram + 0x1C4170, result.records.size());
        require(result.records == recordsBefore, "wash producer changed sun or flare records");
        result.flares = commands(uint32_t(ctx.r2));
        return result;
    }
    std::vector<uint32_t> draw(Function function, const Result& result, unsigned scroll) {
        uint8_t* rdram = memory.data();
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r4 = S32(0x80500000);
        std::memset(rdram + 0x500000, 0xA5, 0x2000);
        for (int i = 0; i < 8; ++i) MEM_W(i * 4, S32(0x800D47E0)) = result.state[i];
        MEM_W(0, S32(0x800D47FC)) = scroll;
        function(rdram, &ctx);
        require(MEM_W(0, S32(0x800D47FC)) == (result.enabled() ? ((scroll - 1) & 127) : scroll),
            "native wash texture scrolling changed");
        return commands(uint32_t(ctx.r2));
    }
};

static int nativeAlpha(float facing, int course, float height) {
    // Maintain native single-precision operation order and final truncation.
    volatile float factor = course == 0 ? std::clamp((height - 20.0f) / 100.0f, 0.0f, 1.0f) : 1.0f;
    volatile float value = float(course == 0 ? 150 : 128) * facing;
    value = value * facing;
    value = value * facing;
    value = value * facing;
    value = value * factor;
    return int(value);
}

static Result compare(Replay& replay, int course, float facing, float center, float y, float height,
                      int mode = 0, int radius = 0) {
    if (radius == 0) radius = course == 0 ? 12 : 24;
    description = "width=" + std::to_string(wr64_sun_logical_width()) + " course=" + std::to_string(course) +
        " facing=" + std::to_string(facing) + " center=" + std::to_string(center) +
        " y=" + std::to_string(y) + " height=" + std::to_string(height) + " radius=" + std::to_string(radius);
    const auto before = replay.run(baseline_func_8008BD2C, course, facing, center, y, height, mode, radius);
    const auto after = replay.run(func_8008BD2C, course, facing, center, y, height, mode, radius);
    const auto regenerated = replay.run(regenerated_func_8008BD2C, course, facing, center, y, height, mode, radius);
    require(after == regenerated, "checked-in wash producer differs from durable hook recipe");
    require(after.flares == before.flares, "wash correction changed native lens flares");
    require(after.records == before.records, "wash correction changed projected records");
    for (int i : {1, 6, 7}) require(after.state[i] == before.state[i], "wash correction changed unrelated state");
    for (int i : {2, 3, 4, 5}) require((after.state[i] & 0xFFFF) == (before.state[i] & 0xFFFF),
        "wash correction changed bytes beside native halfword fields");
    if (course == 0 || course == 2) {
        require(before.enabled() == (double(facing) > 0.7 ? 2 : 0), "baseline angular cutoff not reproduced");
        if (before.enabled()) require(before.alpha() == nativeAlpha(facing, course, height),
            "baseline alpha differs from native facing power and height factor");
        const float overlap = std::max(0.0f, std::min(center + float(radius), wr64_sun_logical_width()) -
            std::max(center - float(radius), 0.0f));
        const bool extension = wr64_sun_logical_width() > 424 && facing > 0 && double(facing) <= 0.7;
        if (extension) {
            require(after.enabled() == (overlap > 0 ? 2 : 0), "wash does not follow visible disk overlap");
            if (overlap == 0) require(after == before, "fully offscreen wash changed native state");
            if (after.enabled()) {
                // The native producer multiplies its float alpha before
                // truncating; do not truncate the native base prematurely.
                volatile float value = float(course == 0 ? 150 : 128) * facing;
                value = value * facing;
                value = value * facing;
                value = value * facing;
                value = value * (course == 0 ? std::clamp((height - 20.0f) / 100.0f, 0.0f, 1.0f) : 1.0f);
                value = value * (overlap / (2 * radius));
                require(after.alpha() == int(value), "wash altered native power, DP height factor, or edge taper");
            }
        }
        if (after.enabled()) {
            require((after.state[2] >> 16) == 245 && (after.state[3] >> 16) == 255 &&
                (after.state[4] >> 16) == 215, "native wash RGB changed");
        }
    }
    if (wr64_sun_logical_width() <= 424 || (course != 0 && course != 2) || double(facing) > 0.7 || facing <= 0) {
        require(after == before, "repair changed protected aspect, course, or angular state");
        ++unchanged;
    }
    if (after.enabled() && !before.enabled()) ++continued;
    ++cases;
    return after;
}

static void verifyDraw(Replay& replay, const Result& state, unsigned scroll) {
    const auto before = replay.draw(baseline_func_80051538, state, scroll);
    const auto after = replay.draw(func_80051538, state, scroll);
    const auto regenerated = replay.draw(regenerated_func_80051538, state, scroll);
    require(after == regenerated, "checked-in wash emitter differs from durable hook recipe");
    require(after == before, "wash correction changed native overlay geometry, sampling, blend, or color");
    if (!state.enabled()) {
        require(after.empty(), "disabled wash still emitted commands");
        return;
    }
    unsigned rectangles = 0;
    for (size_t i = 0; i + 1 < after.size(); i += 2) {
        if ((after[i] >> 24) != 0xE4) continue;
        ++rectangles;
        require(after[i] == (borders ? 0xE46A03C0U : 0xE467C36CU) &&
            after[i + 1] == (borders ? 0U : 0x00020050U), "unexpected wash rectangle bounds");
    }
    require(rectangles == 1, "enabled wash must emit exactly one screen rectangle");
}

int main() {
    Replay replay;
    for (float aspect : {4.0f / 3.0f, 16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f, 48.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        const float width = wr64_sun_logical_width();
        for (int course = 0; course < 9; ++course)
            for (float facing : {-1.0f, -0.01f, 0.0f, 0.1f, 0.49f, 0.5f, 0.6f, 0.6999f,
                    0.7f, std::nextafter(0.7f, 1.0f), 0.8f, 1.0f})
                for (float center : {-200.0f, -24.0f, -1.0f, 0.0f, 24.0f, width / 2, width - 24,
                        width - 1, width, width + 23, width + 128, width + 200})
                    for (float height : {0.0f, 20.0f, 30.0f, 70.0f, 120.0f, 200.0f})
                        compare(replay, course, facing, center, 110.0f, height);
        for (int course : {0, 2})
            for (float y : {-200.0f, -24.0f, 0.0f, 12.0f, 120.0f, 239.0f, 240.0f, 440.0f})
                for (float facing : {0.49f, 0.6f, 0.6999f, 0.8f})
                    compare(replay, course, facing, width - 1, y, 70.0f);
        compare(replay, 7, 0.8f, width / 2, 110.0f, 70.0f, 21);
        if (width > 424) {
            for (int course : {0, 2}) for (int radius : {8, 12, 24}) {
                int previousAlpha = 255;
                for (int position = int(width) - radius - 1; position <= int(width) + radius + 1; ++position) {
                    const auto state = compare(replay, course, 0.69f, float(position), 110.0f, 120.0f, 0, radius);
                    const int alpha = state.enabled() ? state.alpha() : 0;
                    require(alpha <= previousAlpha, "right-edge wash taper increased during exit");
                    previousAlpha = alpha;
                }
                require(previousAlpha == 0, "right-edge wash did not finish at zero");
                previousAlpha = 255;
                for (int position = radius + 1; position >= -radius - 1; --position) {
                    const auto state = compare(replay, course, 0.69f, float(position), 110.0f, 120.0f, 0, radius);
                    const int alpha = state.enabled() ? state.alpha() : 0;
                    require(alpha <= previousAlpha, "left-edge wash taper increased during exit");
                    previousAlpha = alpha;
                }
                require(previousAlpha == 0, "left-edge wash did not finish at zero");
                const auto state = compare(replay, course, 0.69f, width - radius, 110.0f, 120.0f, 0, radius);
                require(state.enabled() && state.alpha() >= 29, "full visible disk lost its wash at the old angular cutoff");
            }
        }
        for (bool borderMode : {false, true}) {
            borders = borderMode;
            for (int course : {0, 2})
                for (float facing : {-1.0f, 0.6f, 0.8f, 1.0f}) {
                    const auto state = compare(replay, course, facing, width - 1, 110.0f, 70.0f);
                    for (unsigned scroll : {0U, 1U, 127U}) verifyDraw(replay, state, scroll);
                }
        }
    }
    require(delegated == 15, "course-specific sun delegation coverage missing");
    require(continued > 1000, "insufficient formerly rejected wash coverage");
    std::cout << cases << " native wash/flare replays; " << unchanged << " exact protected-state comparisons; "
        << continued << " previously rejected wash states enabled; " << checks << " assertions.\n";
}
