#include "recomp.h"
#include "common/rt64_wr64_ultrawide.h"
#include "common/rt64_wr64_menu_projection.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <bit>
#include <iostream>
#include <vector>

extern "C" {
void do_break(uint32_t) { std::abort(); }
void func_80094338(uint8_t*, recomp_context*);
void func_801E7FD8(uint8_t*, recomp_context*);
void baseline_func_80094338(uint8_t*, recomp_context*);
void baseline_func_801E7FD8(uint8_t*, recomp_context*);
void func_801E80B0(uint8_t*, recomp_context*);
void baseline_func_801E80B0(uint8_t*, recomp_context*);
void func_801E3EE0(uint8_t*, recomp_context*);
void baseline_func_801E3EE0(uint8_t*, recomp_context*);
void regenerated_func_80094338(uint8_t*, recomp_context*);
void regenerated_func_801E7FD8(uint8_t*, recomp_context*);
void regenerated_func_801E80B0(uint8_t*, recomp_context*);
void regenerated_func_801E3EE0(uint8_t*, recomp_context*);
void func_801E8800(uint8_t*, recomp_context*) { std::abort(); }
void switch_error(const char*, uint32_t, uint32_t) { std::abort(); }
}
using Function = void (*)(uint8_t*, recomp_context*);
void require(bool value, const char* message) {
    if (!value) { std::cerr << message << '\n'; std::exit(1); }
}
std::vector<uint32_t> run(Function function, bool fill, int x, int width, int height = 28, int y = 71, int kind = 0, bool font = false, bool message = false, bool validateRecipe = true) {
    std::vector<uint8_t> memory(4 * 1024 * 1024);
    uint8_t* rdram = memory.data();
    recomp_context ctx{};
    ctx.f_odd = &ctx.f0.u32h;
    ctx.r29 = S32(0x80100000);
    ctx.r4 = S32(0x80002000);
    ctx.r5 = fill ? x : kind;
    ctx.r6 = fill ? y : x;
    ctx.r7 = fill ? x + width - 1 : y;
    MEM_W(0x10, ctx.r29) = fill ? y + height - 1 : width;
    MEM_W(0x14, ctx.r29) = height;
    if (font) {
        ctx.r5 = kind;
        ctx.r6 = 1; // valid glyph code
        ctx.r7 = x;
        MEM_W(0x10, ctx.r29) = y;
        MEM_W(0x14, ctx.r29) = 0; // regular rectangle font
        MEM_W(0x48, ctx.r29) = std::bit_cast<uint32_t>(1.0f);
    }
    if (message) {
        ctx.r5 = kind;
        ctx.r6 = 0;
        ctx.r7 = x;
        MEM_W(0x10, ctx.r29) = y;
        MEM_W(0x14, ctx.r29) = 0;
        MEM_W(0x18, ctx.r29) = 0;
        const uint32_t tables[] = {0x802263C0, 0x80226568, 0x80226A48, 0x80226890, 0x802264F8};
        MEM_W(0, S32(tables[kind])) = 0x01020000; // synthetic texture address; no ROM assets
        MEM_W(4, S32(tables[kind])) = width;
    }
    function(rdram, &ctx);
    const uint32_t end = uint32_t(ctx.r2);
    require(end >= 0x80002000 && end <= 0x80003000, "display-list builder returned an invalid cursor");
    std::vector<uint32_t> commands;
    for (uint32_t p = 0x80002000; p < end; p += 4) commands.push_back(MEM_W(0, S32(p)));
    for (size_t i = 0; i + 5 < commands.size(); i += 2) if (commands[i] == 0x64000002) {
        require(i >= 10 && commands[i - 10] == 0x00525464 && commands[i - 9] == 0x10000064,
            "extended texture packet did not reuse the native load-sync slot for enablement");
        i += 4;
    }
    Function regenerated = function == func_80094338 ? regenerated_func_80094338 :
        function == func_801E7FD8 ? regenerated_func_801E7FD8 :
        function == func_801E80B0 ? regenerated_func_801E80B0 :
        function == func_801E3EE0 ? regenerated_func_801E3EE0 : nullptr;
    // Release linkers may fold identical checked-in and regenerated functions
    // to the same address. Explicitly bound comparison depth; pointer identity
    // alone cannot distinguish those copies and would recurse indefinitely.
    if (validateRecipe && regenerated) require(commands == run(regenerated, fill, x, width, height, y, kind, font, message, false),
        "durable config hooks differ from checked-in native producer edits");
    return commands;
}
int main() {
    for (uint32_t slot = 0; slot < 8; ++slot)
        require(RT64::wr64MenuModelPreview(0x07000A40, 0x07001280 + slot * 16), "missing native result viewport slot");
    for (uint32_t viewport : {0x0700127FU, 0x07001281U, 0x07001300U, 0x01001280U})
        require(!RT64::wr64MenuModelPreview(0x07000A40, viewport), "unrelated viewport incorrectly classified as a preview");
    require(!RT64::wr64MenuModelPreview(0x07001300, 0x07001280), "shutter projection classified as a preview");
    RT64::wr64UltrawidePublishAspect(16.0f / 9.0f);
    for (int x = -600; x <= 900; x += 5) {
        for (int kind : {0, 1, 2}) {
            require(run(func_80094338, false, x, 369, 28, 71, kind) ==
                run(baseline_func_80094338, false, x, 369, 28, 71, kind), "16:9 Waku commands changed");
        }
        require(run(func_801E7FD8, true, x, 45) == run(baseline_func_801E7FD8, true, x, 45),
            "16:9 black frame commands changed");
        for (int kind : {0, 1, 2, 3, 4, 5})
            require(run(func_801E80B0, false, x, 0, 0, 71, kind, true) ==
                run(baseline_func_801E80B0, false, x, 0, 0, 71, kind, true), "16:9 regular font commands changed");
        for (int kind : {0, 1, 2, 3, 4}) for (int width : {64, 320})
            require(run(func_801E3EE0, false, x, width, 0, 71, kind, false, true) ==
                run(baseline_func_801E3EE0, false, x, width, 0, 71, kind, false, true), "16:9 message commands changed");
    }
    // Demonstrate the native producer's missing left fringe before changing it.
    auto native = run(baseline_func_80094338, false, -20, 369);
    unsigned rectangles = 0;
    for (size_t i = 0; i + 5 < native.size(); i += 2) {
        if ((native[i] >> 24) == 0xE4) {
            require(((native[i + 1] >> 12) & 0xFFF) == 0, "expected native zero clipping");
            ++rectangles;
        }
    }
    require(rectangles == 4, "native Waku must emit four independently loaded strips");
    for (int kind : {0, 1, 2, 3, 4, 5}) {
        auto glyph = run(baseline_func_801E80B0, false, -4, 0, 0, 71, kind, true);
        unsigned glyphs = 0;
        for (size_t i = 0; i + 5 < glyph.size(); i += 2) if ((glyph[i] >> 24) == 0xE4) {
            require(((glyph[i + 1] >> 12) & 0xFFF) == 0, "expected native font left clipping");
            ++glyphs;
        }
        require(glyphs == 1, "regular native font did not emit one glyph");
    }
    unsigned wideCases = 0;
    for (float aspect : {21.0f / 9.0f, 32.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        const float expansion = RT64::wr64UltrawideExpansion(aspect);
        const float fringe = 424.0f * (expansion - 1.0f) * 0.5f;
        const auto layout = RT64::wr64UltrawideLayout(expansion, 1.0f, 424);
        for (int x = -650; x <= 850; x += 5) {
            for (int height : {16, 23, 24, 25, 28}) {
                auto wide = run(func_80094338, false, x, 369, height);
                unsigned count = 0;
                int previousBottom = 71 * 4;
                for (size_t i = 0; i + 1 < wide.size(); i += 2) {
                    require((wide[i] >> 24) != 0xE4, "wide Waku still emitted unsigned native rectangle");
                    if (wide[i] != 0x64000002) continue;
                    require(i + 5 < wide.size(), "truncated extended rectangle");
                    int left = int16_t(wide[i + 2] >> 16), top = int16_t(wide[i + 2]);
                    int right = int16_t(wide[i + 3] >> 16), bottom = int16_t(wide[i + 3]);
                    require(left == x * 4 && right == (x + 369) * 4, "Waku clipped or wrapped horizontal extent");
                    require(top == previousBottom && bottom >= top, "adjacent Waku strips have a gap or overlap");
                    require(int16_t(wide[i + 4] >> 16) == 0, "Waku retained native clipped UV phase");
                    require(std::abs(layout.position(float(left) * 0.25f * expansion) - (x + fringe)) < 0.001f,
                        "Waku does not follow the centered menu coordinate plane");
                    require(wide[i + 5] == (uint32_t(0x40000 / 369) << 16 | uint16_t(0x8000 / height)),
                        "Waku texture scale changed");
                    previousBottom = bottom;
                    ++count;
                    i += 4;
                }
                const bool visible = x < 424 + int(std::ceil(fringe)) && x + 369 >= -int(std::ceil(fringe));
                require(count == (visible ? 4 : 0), "Waku prematurely disappears in an ultrawide fringe");
                if (count) require(previousBottom == (71 + height) * 4, "Waku last strip lost its lower edge");
                if (count) require(wide.size() == run(baseline_func_80094338, false, 20, 369, height).size(),
                    "Waku added display-list capacity per strip");
                ++wideCases;
            }
            auto fill = run(func_801E7FD8, true, x, 45);
            const bool visibleFill = x < 424 + int(std::ceil(fringe)) && x + 44 >= -int(std::ceil(fringe));
            require(fill.size() == (visibleFill ? 6 : 0), "black frame prematurely disappears");
            if (visibleFill) {
                require(fill[2] == 0x64000003 && int16_t(fill[4] >> 16) == x * 4 &&
                    int16_t(fill[5] >> 16) == (x + 45) * 4, "black frame extent or endpoint convention changed");
            }
            ++wideCases;
            for (int kind : {0, 1, 2, 3, 4, 5}) {
                const auto nativeGlyph = run(baseline_func_801E80B0, false, 100, 0, 0, 71, kind, true);
                int glyphWidth = 0;
                for (size_t i = 0; i + 5 < nativeGlyph.size(); i += 2) if ((nativeGlyph[i] >> 24) == 0xE4)
                    glyphWidth = int((nativeGlyph[i] >> 12) & 0xFFF) / 4 - 100;
                require(glyphWidth > 0, "baseline regular font width unavailable");
                auto glyph = run(func_801E80B0, false, x, 0, 0, 71, kind, true);
                unsigned count = 0;
                for (size_t i = 0; i + 5 < glyph.size(); i += 2) if (glyph[i] == 0x64000002) {
                    require(int16_t(glyph[i + 2] >> 16) == x * 4 &&
                        int16_t(glyph[i + 3] >> 16) == (x + glyphWidth) * 4, "regular font lost signed extent");
                    require(int16_t(glyph[i + 4] >> 16) == 0 && glyph[i + 5] == 0x04000400,
                        "regular font UV phase/scale changed");
                    ++count;
                    i += 4;
                }
                bool expected = x < 424 + int(std::ceil(fringe)) && x + glyphWidth >= -int(std::ceil(fringe));
                require(count == (expected ? 1 : 0), "regular glyph visibility differs from its menu frame");
                if (count) require(glyph.size() == nativeGlyph.size(), "regular glyph added display-list capacity");
                ++wideCases;
            }
            for (int kind : {0, 1, 2, 3, 4}) for (int width : {64, 320}) {
                auto message = run(func_801E3EE0, false, x, width, 0, 71, kind, false, true);
                auto nativeMessage = run(baseline_func_801E3EE0, false, 20, width, 0, 71, kind, false, true);
                require(message.size() == nativeMessage.size(), "message added display-list capacity");
                unsigned strips = 0;
                for (size_t i = 0; i + 5 < message.size(); i += 2) if (message[i] == 0x64000002) {
                    require(int16_t(message[i + 2] >> 16) == x * 4 &&
                        int16_t(message[i + 3] >> 16) == (x + width) * 4, "message strip lost signed extent");
                    require(int16_t(message[i + 4] >> 16) == 0 && message[i + 5] == 0x04000400,
                        "message UV phase/scale changed");
                    ++strips;
                    i += 4;
                }
                require(strips == ((kind == 2 || kind == 3) && width == 320 ? 2 : 1), "missing message strips");
                ++wideCases;
            }
        }
    }
    const size_t nativeFillBytes = run(baseline_func_801E7FD8, true, 100, 45).size() * 4;
    const size_t wideFillBytes = run(func_801E7FD8, true, 100, 45).size() * 4;
    require(nativeFillBytes == 8 && wideFillBytes == 24, "fill command-capacity accounting changed");
    std::cout << "Native replay: 6020 native16:9 byte-equivalence comparisons; " << wideCases
        << " ultrawide frame/glyph/message cases preserve signed extents, UV slope, and joined strips.\n"
        << "All production paths match durable config hooks applied to the immutable baseline.\n"
        << "No extra texture commands; result four-box fill delta = " << 4 * (wideFillBytes - nativeFillBytes)
        << " bytes (eight-box bound = " << 8 * (wideFillBytes - nativeFillBytes) << ").\n";
}
