// Replay the actual USA display-list producer using synthetic projected sun
// records. Only existing source is extracted at build time; no ROM is needed.
#include "recomp.h"
#include "wr64_ultrawide.hpp"
#include "common/rt64_wr64_ultrawide.h"
#include <algorithm>
#include <array>
#include <bit>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
void func_8008D94C(uint8_t*, recomp_context*);
void baseline_func_8008D94C(uint8_t*, recomp_context*);
void regenerated_func_8008D94C(uint8_t*, recomp_context*);
}
using Function = void (*)(uint8_t*, recomp_context*);
static unsigned checks = 0, cases = 0, baselineCases = 0, wideCases = 0, repairedRectangles = 0;
static std::string caseDescription;
static void require(bool value, const char* message) {
    ++checks;
    if (!value) {
        std::cerr << message << ": " << caseDescription << '\n';
        std::exit(1);
    }
}

struct Replay {
    std::vector<uint8_t> memory = std::vector<uint8_t>(8 * 1024 * 1024);
    std::vector<uint32_t> run(Function function, int course, int radius, float x, float y, float visibility) {
        uint8_t* rdram = memory.data();
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r4 = S32(0x80500000);
        // Reset the producer's stack and output, including its untouched
        // course-specific stack slots, before every independent replay.
        std::memset(rdram + 0x700000 - 0x100, 0, 0x200);
        std::memset(rdram + 0x500000, 0xA5, 0x1000);
        MEM_W(0, S32(0x800D8170)) = course;
        MEM_W(course * 4, S32(0x800D9944)) = radius;
        const std::array<float, 6> record{x, y, 1.0f, 0.0f, 0.0f, visibility};
        for (int i = 0; i < int(record.size()); ++i)
            MEM_W(i * 4, S32(0x801C4170)) = std::bit_cast<uint32_t>(record[i]);
        function(rdram, &ctx);
        const uint32_t end = uint32_t(ctx.r2);
        require(end >= 0x80500000 && end < 0x80501000 && (end & 7) == 0,
            "invalid display-list cursor");
        require(uint32_t(ctx.r29) == 0x80700000, "producer did not restore its stack");
        std::vector<uint32_t> words;
        for (uint32_t p = 0x80500000; p < end; p += 4) words.push_back(MEM_W(0, S32(p)));
        return words;
    }
};

static void compare(Replay& replay, int course, int radius, float x, float y, float visibility) {
    caseDescription = "width=" + std::to_string(wr64_sun_logical_width()) +
        " course=" + std::to_string(course) + " radius=" + std::to_string(radius) +
        " x=" + std::to_string(x) + " y=" + std::to_string(y) +
        " visibility=" + std::to_string(visibility);
    const auto baseline = replay.run(baseline_func_8008D94C, course, radius, x, y, visibility);
    const auto current = replay.run(func_8008D94C, course, radius, x, y, visibility);
    const auto regenerated = replay.run(regenerated_func_8008D94C, course, radius, x, y, visibility);
    require(current == regenerated, "checked-in producer differs from durable config hook recipe");
    require(current.size() == baseline.size(), "repair changed display-list size or visibility");
    const bool sunsetWide = course == 2 && wr64_sun_logical_width() > 424.0f;
    if (!sunsetWide) {
        require(current == baseline, "repair altered an unaffected aspect ratio or course");
        ++baselineCases;
    }
    unsigned rectangles = 0;
    for (size_t i = 0; i < current.size(); ++i) {
        // Horizontal UV is the high halfword of a B3 data command. All
        // geometry, texture/tile state, vertical UV, slope, and color remain
        // byte-identical, including existing vertical and left-edge clipping.
        const bool horizontalUv = (i & 1) && current[i - 1] == 0xB3000000;
        require((sunsetWide && horizontalUv) ?
            ((current[i] & 0xFFFF) == (baseline[i] & 0xFFFF)) : current[i] == baseline[i],
            "repair changed a field outside horizontal UV");
        if (horizontalUv && sunsetWide) {
            // The geometry producer clips a center to at least its radius.
            // Its existing crop accumulator stores radius - center whenever
            // either axis crosses that edge. Retain that native behavior;
            // an unclipped positive horizontal position adds no U offset.
            const int centerX = int(x), centerY = int(y);
            const int crop = (centerX < radius || centerY < radius) ? radius - centerX : 0;
            const uint16_t expectedU = uint16_t(crop * 32);
            require(uint16_t(current[i] >> 16) == expectedU,
                "sun UV includes an offset unrelated to native left clipping");
            if (centerX >= radius && centerY >= radius)
                require(uint16_t(current[i] >> 16) == 0, "unclipped sun did not start at U=0");
            if (current[i] != baseline[i]) ++repairedRectangles;
        }
        if ((i & 1) == 0 && (current[i] >> 24) == 0xE4) {
            ++rectangles;
            require(i + 5 < current.size() && current[i + 2] == 0xB3000000 &&
                current[i + 4] == 0xB2000000, "invalid sun rectangle packet");
        }
    }
    if (course == 2 && y >= 0 && y < 240) {
        const int centerX = std::max(int(x), radius);
        const unsigned expected = visibility >= 0 && centerX < wr64_sun_horizontal_cull_limit() ? 2U : 0U;
        require(rectangles == expected, "disk/glow emission changed at the right edge");
    }
    if (sunsetWide) ++wideCases;
    ++cases;
}

int main() {
    std::signal(SIGSEGV, [](int) {
        std::cerr << "Producer memory fault: " << caseDescription << '\n';
        std::_Exit(2);
    });
    Replay replay;
    // Every integer x includes both sides of the 512-pixel signed-shift
    // boundary and every neighboring odd/even phase in 21:9 and 32:9.
    for (float aspect : {4.0f / 3.0f, 16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for (int course = 0; course < 9; ++course)
            for (int x = -80; x <= 1050; ++x)
                compare(replay, course, 24, float(x), 110.0f, 1.0f);
        // The actual Sunset Bay radius is 24. Additional synthetic radii
        // exercise clipping independently of that single authored value.
        for (int radius : {16, 24, 32, 48, 64}) {
            for (int x : {-80, -1, 0, radius - 1, radius, radius + 1,
                    radius + 510, radius + 511, radius + 512, radius + 513,
                    555, 556, 557, 683, 684, 685, 847, 848, 849, 975, 976, 977})
                for (int y : {-1, 0, radius - 1, radius, radius + 1, 239, 240})
                    for (float visibility : {-0.25f, 0.0f, 1.0f})
                        compare(replay, 2, radius, float(x) + 0.75f, float(y), visibility);
        }
    }
    require(repairedRectangles > 100, "immutable baseline failed to reproduce the original UV corruption");
    std::cout << cases << " native sun replays; " << baselineCases
        << " exact baseline comparisons for unaffected courses/aspects; " << wideCases
        << " Sunset ultrawide cases; " << repairedRectangles
        << " previously corrupt disk/glow UV packets repaired; " << checks << " assertions.\n"
        << "All output matches the durable config hook recipe; geometry, visibility, vertical UV, colors,"
           " texture state, and command sizes remain unchanged. No ROM, game, or display required.\n";
}
