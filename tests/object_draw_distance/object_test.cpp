#include "recomp.h"
#include "wr64_object_distance.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

extern "C" {
void original_visibility(uint8_t*, recomp_context*);
void original_draw(uint8_t*, recomp_context*);
void enhanced_draw(uint8_t*, recomp_context*);
void enhanced_begin(uint8_t*, recomp_context*);
void enhanced_end(uint8_t*, recomp_context*);
}
namespace {
using Ram = std::vector<uint8_t>;
using Fn = void(*)(uint8_t*, recomp_context*);
constexpr uint32_t Size = 0x800000, Stack = 0x807FE000;
constexpr uint32_t Objects = 0x801BC940, Count = 0x801BFA40, Visibility = 0x801C0AC0;
constexpr uint32_t Descriptor = 0x801CB058, Camera = 0x80227C80, DrawPool = 0x8011F8E8;
constexpr uint32_t MatrixPool = 0x80198368, MatrixCount = 0x801AE950, StaticMatrices = 0x801C0CD0;
unsigned checks = 0, cases = 0;
uint64_t accesses = 0;
void require(bool value, const char* message) {
    ++checks;
    if (!value) { std::cerr << "FAIL case " << cases << ": " << message << '\n'; std::exit(1); }
}
void put(Ram& r, uint32_t at, uint32_t value) { auto* rdram = r.data(); MEM_W(0, S32(at)) = value; }
uint32_t word(const Ram& r, uint32_t at) { return *reinterpret_cast<const uint32_t*>(r.data() + (at & 0x7FFFFF)); }
void number(Ram& r, uint32_t at, float value) { put(r, at, std::bit_cast<uint32_t>(value)); }
int16_t visible(const Ram& r, unsigned i) {
    return *reinterpret_cast<const int16_t*>(r.data() + (((Visibility + i * 2) ^ 2) & 0x7FFFFF));
}
void context(recomp_context& c) { c = {}; c.f_odd = &c.f0.u32h; c.r29 = S32(Stack); }
void runVisibility(Ram& r) {
    recomp_context c; context(c);
    const uint32_t descriptor = word(r, 0x801C0C80);
    c.r2 = S32(descriptor); c.r4 = word(r, 0x801BB120);
    c.r22 = S32(Camera + word(r, 0x80223930 + word(r, 0x800DAB2C) * 4) * 0x10C); c.f24.fl = 0;
    original_visibility(r.data(), &c);
    require(c.r17 == word(r, descriptor + 0xA0) && c.r18 == word(r, descriptor + 0xA4),
        "Original visibility changed course thresholds");
}
void drawContext(recomp_context& c) {
    context(c);
    c.r2 = c.r7 = S32(0x801C0000); c.r16 = 0;
    c.r17 = S32(0xE7000000); c.r20 = 0x01020040; c.r23 = 0x2000;
    c.r10 = S32(0xB900031D); c.r11 = S32(0xC8113078); c.r31 = 0x06000000;
    // The enclosing draw function has repurposed s6 by this point. A helper
    // must reconstruct the active native camera, not interpret s6 as one.
    c.r22 = S32(0xBC00000E);
}
void draw(Ram& r, Fn fn) { recomp_context c; drawContext(c); fn(r.data(), &c); }
Ram initial(float distance, unsigned cameraIndex = 0) {
    Ram r(Size, 0); auto* rdram = r.data();
    put(r, 0x800D8170, 0); put(r, 0x800DAB28, 1); put(r, 0x801CE638, 1);
    put(r, 0x800DAB2C, 0); put(r, 0x800DAB24, 41); put(r, 0x80223930, cameraIndex);
    put(r, 0x801C0C80, Descriptor); put(r, Descriptor + 0xA0, 400); put(r, Descriptor + 0xA4, 5000);
    put(r, 0x801518B8, DrawPool); put(r, 0x801AE948, MatrixPool); put(r, MatrixCount, 7);
    put(r, Stack + 0x550, DrawPool + 0x100);
    const uint32_t camera = Camera + cameraIndex * 0x10C;
    put(r, camera, 4); put(r, camera + 0xE8, cameraIndex);
    number(r, camera + 0x50, 80); number(r, Stack + 0x568, 0); number(r, Stack + 0x564, 1);
    put(r, Count, 3);
    for (unsigned i = 0; i < 3; ++i) {
        const uint32_t object = Objects + i * 0xC4;
        number(r, object + 8, i == 0 ? distance : i == 1 ? 500 : 6500);
        put(r, object + 0x4C, i < 2 ? 1 : 11); put(r, object + 0x54, i < 2 ? 1 : 2);
        put(r, object + 0xB4, i < 2 ? 0x0D02BDE8 : 0);
        put(r, object + 0xB8, i < 2 ? 0x0D02BDF8 : 0x0D02B700);
        for (unsigned j = 0; j < 16; ++j) number(r, object + 0x74 + j * 4, j % 5 == 0 ? 1.f : 0.f);
        for (unsigned j = 0; j < 64; ++j) r[(StaticMatrices & 0x7FFFFF) + i * 64 + j] = uint8_t(i * 64 + j);
        MEM_H(0, S32(Visibility + i * 2)) = -7;
    }
    runVisibility(r);
    return r;
}
void renderingOnly(const Ram& before, const Ram& after) {
    const uint32_t from = word(before, Stack + 0x550), to = word(after, Stack + 0x550);
    bool good = true;
    for (uint32_t i = 0; i < Size; ++i) if (before[i] != after[i]) {
        const uint32_t at = 0x80000000 + i;
        good &= (at >= Stack - 0x100 && at < Stack + 0x600) || (at >= from && at < to);
    }
    require(good, "Draw changed object physics, cached transforms, native visibility or another memory bank");
    require(word(before, MatrixCount) == word(after, MatrixCount), "Static ramp consumed a shared matrix slot");
}
std::vector<uint32_t> modelCalls(const Ram& r, uint32_t begin) {
    std::vector<uint32_t> models;
    for (uint32_t p = begin; p < word(r, Stack + 0x550); p += 8)
        if (word(r, p) == 0x06000000) models.push_back(word(r, p + 4));
    return models;
}
void visibilityRestored(const Ram& before, const Ram& after) {
    for (unsigned i = 0; i < word(before, Count); ++i)
        require(visible(before, i) == visible(after, i), "Later native object consumers received changed visibility/fade");
}
void distances() {
    constexpr float far[] = {5000, 7500, 10000, 15000};
    constexpr uint32_t near[] = {400, 600, 800, 1200};
    for (unsigned mode = 0; mode < 4; ++mode) for (unsigned camera = 0; camera < 2; ++camera)
    for (float distance : {0.f, 400.f, 4999.f, 5000.f, 6500.f, 7499.f, 7500.f, 9999.f, 10000.f,
        12000.f, 14999.f, 15000.f, 15001.f, -6500.f, -12000.f, -14999.f, -15000.f}) {
        ++cases; auto input = initial(distance, camera), original = input, enhanced = input;
        wr64::object_distance::set_mode(mode);
        auto oracle = input;
        put(oracle, Descriptor + 0xA0, near[mode]);
        put(oracle, Descriptor + 0xA4, uint32_t(far[mode])); runVisibility(oracle);
        recomp_context c; drawContext(c); enhanced_begin(enhanced.data(), &c);
        require((visible(enhanced, 0) >= 0) == (visible(oracle, 0) >= 0),
            "Ramp admission differs from the complete native visibility loop at scaled distance");
        require(visible(enhanced, 1) == visible(input, 1) && visible(enhanced, 2) == visible(input, 2),
            "Existing ramp fade or tree visibility changed during the ramp pass");
        enhanced_end(enhanced.data(), &c);
        require(enhanced == input, "Begin/end failed to restore exact pre-pass memory");
        draw(original, original_draw); draw(enhanced, enhanced_draw);
        if (!mode) require(enhanced == original, "Original is not byte-identical through the complete native draw pass");
        const unsigned expectedRamps = unsigned(std::abs(distance) < far[mode]) + 1;
        require(word(enhanced, Stack + 0x550) - word(input, Stack + 0x550) == expectedRamps * 72,
            "Native ramp pass emitted unexpected packet count");
        const auto models = modelCalls(enhanced, word(input, Stack + 0x550));
        require(models.size() == expectedRamps * 2, "Expanded ramp lost its deck/support model pair");
        for (size_t i = 0; i < models.size(); i += 2)
            require(models[i] == 0x0D02BDE8 && models[i + 1] == 0x0D02BDF8, "Wrong object asset was drawn");
        renderingOnly(input, enhanced); visibilityRestored(input, enhanced);
    }
}
void unsupported() {
    wr64::object_distance::set_mode(3);
    for (auto [address, value] : std::vector<std::pair<uint32_t, uint32_t>>{
        {0x800D8170, 9}, {0x800D8170, UINT32_MAX}, {0x800DAB28, 0}, {0x800DAB28, 3},
        {0x800DAB2C, 1}, {0x80223930, 2}, {0x801C0C80, Descriptor + 4},
        {Objects + 0x4C, 11}, {Objects + 0x54, 2}, {Objects + 0x58, 1},
        {Objects + 0x4C, 0}, {Objects + 0x4C, 2}, {Objects + 0x4C, 8}}) {
        ++cases; auto input = initial(6500); put(input, address, value);
        auto a = input, b = input; draw(a, original_draw); draw(b, enhanced_draw);
        require(a == b, "Unsupported scene/camera/asset/animated object changed native draw output");
    }
    for (unsigned mode : {4u, 99u, UINT32_MAX}) {
        ++cases; wr64::object_distance::set_mode(mode);
        require(wr64::object_distance::mode() == 0, "Invalid setting did not select Original");
        auto a = initial(6500), b = a; draw(a, original_draw); draw(b, enhanced_draw);
        require(a == b, "Invalid setting changed native rendering");
    }
}
void capacity() {
    wr64::object_distance::set_mode(3);
    for (unsigned poolIndex = 0; poolIndex < 2; ++poolIndex) for (bool crowded : {false, true})
    for (int shortage : {0, 8}) {
        ++cases; auto input = initial(12000);
        const uint32_t pool = DrawPool + poolIndex * 0x18FE8;
        put(input, 0x801518B8, pool);
        const unsigned total = crowded ? 64 : 3;
        if (crowded) {
            // Put both ramps last, testing the final two resident matrix slots.
            const auto original = input;
            put(input, Count, total);
            for (unsigned i = 0; i < total; ++i) {
                const uint32_t object = Objects + i * 0xC4;
                std::copy_n(original.data() + (Objects & 0x7FFFFF), 0xC4, input.data() + (object & 0x7FFFFF));
                if (i < 62) {
                    put(input, object + 0x4C, 11); put(input, object + 0xB4, 0); put(input, object + 0xB8, 0);
                    number(input, object + 8, 500);
                }
            }
        } else number(input, Objects + 0xC4 + 8, 12000);
        runVisibility(input);
        // Both extra static ramps cost precisely 9 commands each. Existing
        // solid objects receive the same conservative 9-command allowance.
        const uint32_t budget = 0x3000 + 72 * (crowded ? 64 : 2);
        const uint32_t cursor = pool + 0x6000 - budget + uint32_t(shortage);
        put(input, Stack + 0x550, cursor);
        auto output = input; draw(output, enhanced_draw);
        const unsigned admitted = shortage ? 1 : 2;
        require(word(output, Stack + 0x550) == cursor + (crowded ? 62 * 24 : 0) + admitted * 72,
            "Exact display-list boundary or nearest-extra capacity fallback is wrong");
        renderingOnly(input, output); visibilityRestored(input, output);
        std::vector<uint32_t> matrixReferences;
        for (uint32_t at = cursor; at < word(output, Stack + 0x550); at += 8)
            if (word(output, at) == 0x01020040) matrixReferences.push_back(word(output, at + 4));
        require(matrixReferences.size() == (crowded ? 62u : 0u) + admitted,
            "Native matrix-reference count differs from admitted objects");
        for (uint32_t matrix : matrixReferences)
            require(matrix >= StaticMatrices && matrix + 64 <= StaticMatrices + 64 * 64 &&
                ((matrix - StaticMatrices) % 64) == 0, "Object references a matrix outside its 64-slot resident bank");
        if (crowded && !shortage)
            require(matrixReferences[62] == StaticMatrices + 62 * 64 &&
                matrixReferences[63] == StaticMatrices + 63 * 64, "Last two native ramp matrix identities were lost");
    }
}
void guardAndLifetime() {
    for (unsigned variant = 0; variant < 12; ++variant) {
        ++cases; wr64::object_distance::set_mode(3); auto input = initial(12000);
        recomp_context c; drawContext(c);
        if (variant == 0) put(input, Count, 0);
        if (variant == 1) put(input, Count, 65);
        if (variant == 2) put(input, Stack + 0x550, DrawPool + 1);
        if (variant == 3) put(input, Stack + 0x550, DrawPool - 8);
        if (variant == 4) put(input, Stack + 0x550, DrawPool + 0x6008);
        if (variant == 5) put(input, 0x801518B8, DrawPool + 8);
        if (variant == 6) put(input, Descriptor + 0xA0, 5000);
        if (variant == 7) put(input, Descriptor + 0xA4, 1000001);
        if (variant == 8) number(input, Camera + 0x4C, std::numeric_limits<float>::infinity());
        if (variant == 9) number(input, Objects + 8, std::numeric_limits<float>::quiet_NaN());
        if (variant == 10) c.r29 += 1;
        if (variant == 11) c.r29 = S32(0x807FFFF8);
        const auto before = input;
        enhanced_begin(input.data(), &c); enhanced_end(input.data(), &c);
        require(input == before, "Malformed count, range, pool, coordinate or stack changed native memory");
    }
    ++cases; auto input = initial(6500), before = input;
    // A hidden ramp inside its original range may have another native reason
    // to stay hidden. This control cannot override it.
    number(input, Objects + 8, 1000); before = input;
    recomp_context c; drawContext(c); enhanced_begin(input.data(), &c); enhanced_end(input.data(), &c);
    require(input == before, "A hidden ramp inside original range was overridden");
    ++cases; input = initial(6500); before = input; enhanced_begin(input.data(), &c);
    require(visible(input, 0) == 0, "Eligible static ramp did not enter its temporary draw pass");
    const auto active = input;
    enhanced_begin(input.data(), &c);
    require(input == active, "Repeated begin changed an active frame");
    recomp_context wrong; drawContext(wrong); enhanced_end(input.data(), &wrong);
    require(input == active, "An unmatched context restored another draw frame");
    c.r29 += 8; enhanced_end(input.data(), &c); c.r29 -= 8;
    require(input == active, "An unmatched stack restored another draw frame");
    wr64::object_distance::set_mode(0); enhanced_end(input.data(), &c);
    require(input == before, "Changing mode mid-pass prevented visibility restoration");
    enhanced_end(input.data(), &c); require(input == before, "Repeated end changed a completed frame");
    enhanced_begin(nullptr, nullptr); enhanced_end(nullptr, nullptr);
}
void nativeAnimatedControl() {
    ++cases; wr64::object_distance::set_mode(3); auto input = initial(12000);
    put(input, Objects + 0xC4 + 0x58, 1); // Already-visible native animated object.
    auto original = input, enhanced = input; draw(original, original_draw); draw(enhanced, enhanced_draw);
    require(word(original, MatrixCount) == word(input, MatrixCount) + 1 &&
        word(enhanced, MatrixCount) == word(original, MatrixCount), "Static extension changed native animated allocation count");
    const uint32_t slot = word(input, MatrixCount);
    require(std::equal(original.begin() + (MatrixPool & 0x7FFFFF) + 0x4140 + slot * 64,
        original.begin() + (MatrixPool & 0x7FFFFF) + 0x4140 + (slot + 1) * 64,
        enhanced.begin() + (MatrixPool & 0x7FFFFF) + 0x4140 + slot * 64),
        "Static extension changed the native animated matrix produced by _MtxF_to_Mtx");
    require(word(enhanced, Stack + 0x550) == word(original, Stack + 0x550) + 72,
        "Animated native control changed the extra static ramp packet budget");
    visibilityRestored(input, enhanced);
}
void allWorldViews() {
    for (unsigned course = 0; course < 9; ++course) for (unsigned players : {1u, 2u})
    for (unsigned view = 0; view < players; ++view) for (unsigned phase : {0u, 1u})
    for (unsigned mode = 0; mode < 4; ++mode) {
        ++cases; auto input = initial(6500);
        put(input, 0x800D8170, course); put(input, 0x800DAB28, players); put(input, 0x800DAB2C, view);
        put(input, 0x801CE638, phase); put(input, 0x800DAB24, phase ? 41 : 2);
        const unsigned index = 1 - view;
        put(input, 0x80223930 + view * 4, index);
        const uint32_t descriptor = Descriptor + view * 0x110;
        put(input, 0x801C0C80, descriptor);
        put(input, descriptor + 0xA0, 400); put(input, descriptor + 0xA4, view ? 4000 : 5000);
        const uint32_t camera = Camera + index * 0x10C, other = Camera + (1 - index) * 0x10C;
        number(input, camera + 0x4C, 1234); number(input, camera + 0x54, -2000);
        number(input, other + 0x4C, -20000); number(input, other + 0x54, 20000);
        put(input, camera, phase ? 5 : 0); put(input, camera + 0xE8, 99);
        for (unsigned i = 0; i < 2; ++i) {
            number(input, Objects + i * 0xC4, 1234);
            number(input, Objects + i * 0xC4 + 8, -2000 + (i ? 500.f : view ? 5200.f : 6500.f));
            put(input, Objects + i * 0xC4 + 0xB4, 0x0E00A000 + course * 0x80);
            put(input, Objects + i * 0xC4 + 0xB8, 0x0E00A010 + course * 0x80);
        }
        runVisibility(input);
        require(visible(input, 0) < 0 && visible(input, 1) >= 0, "Per-view fixture did not establish native priority");
        auto native = input, enhanced = input;
        wr64::object_distance::set_mode(mode); draw(native, original_draw); draw(enhanced, enhanced_draw);
        if (!mode) require(native == enhanced, "All-course/view/phase Original parity failed");
        else require(word(enhanced, Stack + 0x550) == word(native, Stack + 0x550) + 72,
            "All-course/view/phase selected the wrong camera, descriptor or static model family");
        visibilityRestored(input, enhanced);
        require(word(input, MatrixCount) == word(enhanced, MatrixCount), "World-view expansion consumed dynamic matrices");
    }
}
void iceAndNativeFamilies() {
    wr64::object_distance::set_mode(3);
    for (unsigned kind : {1u, 2u, 3u, 5u, 8u, 10u, 11u}) for (float z : {-12000.f, 12000.f}) {
        ++cases; auto input = initial(z); put(input, 0x800D8170, 8);
        put(input, Objects + 0x4C, kind);
        put(input, Objects + 0x54, kind == 3 || kind == 11 ? 2 : kind == 8 ? 3 : 1);
        put(input, Objects + 0x58, kind == 2 ? 3 : kind == 5 ? 4 : kind == 8 ? 5 : 0);
        put(input, Objects + 0xB4, 0x0E009808); put(input, Objects + 0xB8, 0);
        runVisibility(input);
        auto oracle = input; put(oracle, Descriptor + 0xA4, 15000); runVisibility(oracle);
        recomp_context c; drawContext(c); auto during = input;
        enhanced_begin(during.data(), &c);
        const bool eligible = kind == 1 || kind == 10;
        require((visible(during, 0) >= 0) == (eligible && visible(oracle, 0) >= 0),
            "Static family or forward half-plane differs from the actual native visibility oracle");
        enhanced_end(during.data(), &c); require(during == input, "Family test cleanup changed native memory");
        auto native = input, enhanced = input; draw(native, original_draw); draw(enhanced, enhanced_draw);
        const bool added = kind == 1 || (kind == 10 && z > 0);
        require(word(enhanced, Stack + 0x550) == word(native, Stack + 0x550) + (added ? 48u : 0u),
            "Single-root ice packet or excluded dynamic/sprite family behavior is wrong");
        renderingOnly(input, enhanced); visibilityRestored(input, enhanced);
    }
}
void nearestAndSequentialViews() {
    wr64::object_distance::set_mode(3);
    ++cases; auto input = initial(12000); const auto record = input;
    put(input, Count, 64);
    for (unsigned i = 0; i < 64; ++i) {
        const uint32_t object = Objects + i * 0xC4;
        std::copy_n(record.data() + (Objects & 0x7FFFFF), 0xC4, input.data() + (object & 0x7FFFFF));
        number(input, object + 8, 11000 + float(63 - i) * 40);
    }
    runVisibility(input);
    // Only three additions fit, and those are the last three resident objects.
    const uint32_t cursor = DrawPool + 0x6000 - 0x3000 - 3 * 72;
    put(input, Stack + 0x550, cursor); const auto before = input;
    recomp_context c; drawContext(c); enhanced_begin(input.data(), &c);
    for (unsigned i = 0; i < 64; ++i) require((visible(input, i) >= 0) == (i >= 61), "Nearest-extra admission is not distance ordered");
    enhanced_end(input.data(), &c); require(input == before, "Sorted admission restored visibility to the wrong indices");
    draw(input, enhanced_draw);
    require(word(input, Stack + 0x550) == cursor + 3 * 72, "Nearest-extra packet budget overflowed");
    visibilityRestored(before, input); renderingOnly(before, input);

    ++cases; input = initial(12000); put(input, 0x800DAB28, 2);
    put(input, 0x80223930, 0); put(input, 0x80223934, 1);
    number(input, Camera + 0x10C + 0x54, 23000);
    put(input, Descriptor + 0x110 + 0xA0, 400); put(input, Descriptor + 0x110 + 0xA4, 5000);
    // A single shared display pool is used sequentially. Each view restores
    // the visibility that its own native camera computed before the next view.
    // The first ramp is beyond 2x but inside 3x from both cameras; the second
    // is native-visible from view 0 and beyond even 3x from view 1.
    for (unsigned view : {0u, 1u, 0u}) {
        put(input, 0x800DAB2C, view); put(input, 0x801C0C80, Descriptor + view * 0x110);
        runVisibility(input); auto native = input; draw(native, original_draw);
        auto oracle = input;
        put(oracle, Descriptor + view * 0x110 + 0xA0, 1200);
        put(oracle, Descriptor + view * 0x110 + 0xA4, 15000); runVisibility(oracle);
        require(visible(input, 0) < 0 && visible(oracle, 0) >= 0 &&
            (visible(input, 1) >= 0) == (visible(oracle, 1) >= 0),
            "Sequential 3x native oracle no longer establishes exactly one extra ramp per view");
        const auto beforeView = input; draw(input, enhanced_draw);
        require(word(input, Stack + 0x550) == word(native, Stack + 0x550) + 72,
            "Sequential views shared stale admission or ignored their own camera");
        visibilityRestored(beforeView, input); renderingOnly(beforeView, input);
    }
}
void splitViewCapacity() {
    wr64::object_distance::set_mode(3);
    for (unsigned players : {1u, 2u}) for (unsigned view = 0; view < players; ++view)
    for (unsigned poolIndex : {0u, 1u}) for (unsigned shortage : {0u, 8u}) {
        ++cases; auto input = initial(12000);
        put(input, 0x800DAB28, players); put(input, 0x800DAB2C, view);
        const uint32_t descriptor = Descriptor + view * 0x110;
        put(input, 0x801C0C80, descriptor);
        put(input, descriptor + 0xA0, 400); put(input, descriptor + 0xA4, 5000);
        const uint32_t reserve = players == 2 && view == 0 ? 0x4800 : 0x3000;
        const uint32_t pool = DrawPool + poolIndex * 0x18FE8;
        const uint32_t cursor = pool + 0x6000 - reserve - 2 * 72 + shortage;
        put(input, 0x801518B8, pool); put(input, Stack + 0x550, cursor);
        runVisibility(input); const auto before = input;
        draw(input, enhanced_draw);
        require(word(input, Stack + 0x550) == cursor + (shortage ? 72u : 144u),
            "First split-screen view reserve or exact extra-object capacity boundary is wrong");
        require(pool + 0x6000 - word(input, Stack + 0x550) >= reserve,
            "Object admission consumed its reserved remaining view/tail budget");
        visibilityRestored(before, input); renderingOnly(before, input);
    }
}
void archive(const char* path) {
    ++cases;
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    require(file && file.tellg() == Size, "Dolphin archive must be an original 8 MiB RDRAM capture");
    Ram captured(Size); file.seekg(0); file.read(reinterpret_cast<char*>(captured.data()), Size);
    require(word(captured, 0x800D8170) == 0 && word(captured, Count) == 14 &&
        word(captured, Descriptor + 0xA0) == 400 && word(captured, Descriptor + 0xA4) == 5000,
        "Archive is not the verified Dolphin Park scene");
    for (unsigned i = 0; i < 14; ++i) require(word(captured, Objects + i * 0xC4 + 0x4C) == (i < 2 ? 1u : 11u),
        "Archive object identities differ from two ramps and twelve trees");
    put(captured, Stack + 0x550, word(captured, 0x801518B8) + 0x100);
    number(captured, Stack + 0x568, 0); number(captured, Stack + 0x564, 1);
    // Exercise the original opening state with its real camera and objects.
    runVisibility(captured);
    for (unsigned mode = 0; mode < 4; ++mode) {
        ++cases; wr64::object_distance::set_mode(mode);
        auto nativeOpening = captured, changedOpening = captured;
        draw(nativeOpening, original_draw); draw(changedOpening, enhanced_draw);
        if (!mode) require(nativeOpening == changedOpening, "Archived opening Original parity failed");
        else require(word(changedOpening, Stack + 0x550) == word(nativeOpening, Stack + 0x550) + 72,
            "Actual archived opening did not extend the distant ramp");
        renderingOnly(captured, changedOpening); visibilityRestored(captured, changedOpening);
    }
    // Replay the same archived objects, camera, assets and transforms in the
    // supported warmup phase. This is a CPU fixture, not a new game capture.
    put(captured, 0x801CE638, 1); put(captured, 0x800DAB24, 41);
    runVisibility(captured);
    require(visible(captured, 0) == -1 && visible(captured, 1) >= 0, "Archive no longer reproduces the missing distant ramp");
    for (unsigned mode = 0; mode < 4; ++mode) {
        ++cases; wr64::object_distance::set_mode(mode);
        auto after = captured; draw(after, enhanced_draw);
        require(word(after, Stack + 0x550) - word(captured, Stack + 0x550) == (mode ? 144u : 72u),
            "Archived distant ramp did not add precisely its native nine draw commands");
        renderingOnly(captured, after); visibilityRestored(captured, after);
        if (!mode) { auto native = captured; draw(native, original_draw); require(native == after, "Archived Original parity failed"); }
    }
}
}
extern "C" void do_break(uint32_t) { require(false, "Native break"); }
extern "C" void* wr64_test_address(uint8_t* ram, uint64_t at, unsigned width, const char*, int) {
    ++accesses; const uint32_t address = uint32_t(at);
    require(address >= 0x80000000 && address <= 0x80800000 - width, "Native memory access escaped RDRAM");
    return ram + (address & 0x7FFFFF);
}
int main(int argc, char** argv) {
    if (argc == 2) archive(argv[1]);
    else { distances(); unsupported(); capacity(); guardAndLifetime(); nativeAnimatedControl();
        allWorldViews(); iceAndNativeFamilies(); nearestAndSequentialViews(); splitViewCapacity(); }
    std::cout << "PASS " << cases << " native object scenarios, " << checks << " checks, " << accesses << " checked accesses\n";
}
