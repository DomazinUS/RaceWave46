#include "recomp.h"
#include "wr64_draw_distance.hpp"
#include "wr64_object_distance.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

extern "C" {
void baseline_visibility(uint8_t*, recomp_context*);
void enhanced_visibility(uint8_t*, recomp_context*);
void regenerated_visibility(uint8_t*, recomp_context*);
void native_buoy_matrices(uint8_t*, recomp_context*);
void enhanced_buoy_matrices(uint8_t*, recomp_context*);
void enhanced_buoy_end(uint8_t*, recomp_context*);
void enhanced_area_matrices(uint8_t*, recomp_context*);
void native_area_matrices(uint8_t*, recomp_context*);
void enhanced_area_end(uint8_t*, recomp_context*);
void area_type0_top(uint8_t*, recomp_context*);
void area_type0_bottom(uint8_t*, recomp_context*);
void area_type1_top(uint8_t*, recomp_context*);
void area_type1_bottom(uint8_t*, recomp_context*);
void native_twilight_tail(uint8_t*, recomp_context*);
void extended_twilight_tail(uint8_t*, recomp_context*);
void native_camera_direction(uint8_t*, recomp_context*);
void native_checkpoint_body(uint8_t*, recomp_context*);
void native_object_body(uint8_t*, recomp_context*);
void extended_object_body(uint8_t*, recomp_context*);
void wr64_draw_distance_begin(uint8_t*, recomp_context*);
void wr64_draw_distance_finish(uint8_t*, recomp_context*);
void wr64_draw_distance_capacity(uint8_t*, recomp_context*);
}

namespace {
using Ram = std::vector<uint8_t>;
using Fn = void(*)(uint8_t*, recomp_context*);
constexpr uint32_t Size = 0x800000, Stack = 0x807FE000;
constexpr uint32_t Buoy = 0x801AEE20, Visibility = 0x801C0840, Indices = 0x801C0B40;
constexpr uint32_t Count = 0x801BB120, Descriptor = 0x801CB058;
constexpr uint32_t Camera = 0x80227C80, DrawPool = 0x8011F8E8, MatrixPool = 0x80198368;
constexpr uint32_t Area = 0x801BB138, AreaCount = 0x801BC938, AreaVisibility = 0x801C08C0, AreaIndices = 0x801C0B80;
unsigned checks = 0, cases = 0;
uint64_t accesses = 0;
bool enhancedTwoPlayerLights = false;
void require(bool value, const char* text) {
    ++checks;
    if (!value) { std::cerr << "FAIL case " << cases << ": " << text << '\n'; std::exit(1); }
}
void put(Ram& r, uint32_t at, uint32_t value) { auto* rdram = r.data(); MEM_W(0, S32(at)) = value; }
uint32_t word(const Ram& r, uint32_t at) { return *reinterpret_cast<const uint32_t*>(r.data() + (at & 0x7FFFFF)); }
void number(Ram& r, uint32_t at, float value) { put(r, at, std::bit_cast<uint32_t>(value)); }
int16_t visibility(const Ram& r, unsigned index, uint32_t base = Visibility) {
    return *reinterpret_cast<const int16_t*>(r.data() + (((base + index * 2) ^ 2) & 0x7FFFFF));
}
void context(recomp_context& c) { c = {}; c.f_odd = &c.f0.u32h; c.r29 = S32(Stack); }
Ram initial(const std::vector<float>& distances, unsigned course = 1, unsigned camera = 0) {
    Ram ram(Size, 0); auto* rdram = ram.data();
    put(ram, 0x800DAB28, 1); put(ram, 0x800DAB2C, 0); put(ram, 0x800DAB24, 41);
    put(ram, 0x800D8170, course); put(ram, 0x801CE638, 1); put(ram, Count, uint32_t(distances.size()));
    put(ram, 0x801C0C80, Descriptor); put(ram, Descriptor + 0xA0, 1000); put(ram, Descriptor + 0xA4, 2000);
    put(ram, Descriptor + 0x110 + 0xA0, 1000); put(ram, Descriptor + 0x110 + 0xA4, 2000);
    for (unsigned view = 0; view < 2; ++view) {
        put(ram, Descriptor + view * 0x110 + 0x78, 900);
        put(ram, Descriptor + view * 0x110 + 0x7C, 1000);
    }
    put(ram, 0x801518B8, DrawPool); put(ram, 0x801AE948, MatrixPool); put(ram, Stack + 0x550, DrawPool + 0x100);
    put(ram, 0x80223930, camera);
    const uint32_t cam = Camera + camera * 0x10C;
    put(ram, cam, 4); put(ram, cam + 0xE8, camera);
    number(ram, cam + 0x4C, 0); number(ram, cam + 0x50, 80); number(ram, cam + 0x54, 0);
    number(ram, Stack + 0x568, 0); number(ram, Stack + 0x564, 1);
    for (unsigned i = 0; i < distances.size(); ++i) {
        const uint32_t b = Buoy + i * 0x104;
        number(ram, b, 0); number(ram, b + 4, 20); number(ram, b + 8, distances[i]);
        number(ram, b + 0x60, 10); number(ram, b + 0x64, 20); number(ram, b + 0x68, distances[i] + 10);
        put(ram, b + 0x98, i % 2); put(ram, b + 0x9C, 0); put(ram, b + 0xC8, 1);
        MEM_H(0, S32(Visibility + 2 * i)) = -7; MEM_B(0, S32(Indices + i)) = 0xFE;
    }
    // The excluded area-roster type 2 and the following object category
    // straddle the native range. Neither may gain scaled distances.
    constexpr std::array<float, 3> otherDistances{500, 1500, 2500};
    put(ram, 0x801BC938, 3); put(ram, 0x801BFA40, 3);
    for (unsigned i = 0; i < otherDistances.size(); ++i) {
        number(ram, 0x801BB138 + i * 0x18 + 8, otherDistances[i]);
        put(ram, 0x801BB138 + i * 0x18 + 0x10, 2);
        number(ram, 0x801BC940 + i * 0xC4 + 8, otherDistances[i]);
        put(ram, 0x801BC940 + i * 0xC4 + 0x4C, 1);
    }
    return ram;
}
void run(Ram& ram, Fn fn, recomp_context* live = nullptr) {
    recomp_context local; auto& c = live ? *live : local; context(c);
    const uint32_t descriptor = word(ram, 0x801C0C80);
    c.r2 = S32(descriptor); c.r4 = word(ram, Count);
    c.r22 = S32(Camera + word(ram, 0x80223930 + 4 * word(ram, 0x800DAB2C)) * 0x10C); c.f24.fl = 0;
    fn(ram.data(), &c);
    require(c.r17 == word(ram, descriptor + 0xA0) && c.r18 == word(ram, descriptor + 0xA4),
        "course distance registers restored before other object lists");
    require(uint32_t(c.r29) == Stack, "native visibility stack balanced");
}
void preserved(const Ram& before, const Ram& after, bool matrices = false, bool areaMatrices = false) {
    bool good = true;
    for (unsigned i = 0; i < Size; ++i) if (before[i] != after[i]) {
        const uint32_t at = 0x80000000 + i;
        bool allowed = (at >= Stack - 0x100 && at < Stack + 0x600) ||
            (at >= Visibility && at < Visibility + 0x80) ||
            (at >= AreaVisibility && at < AreaVisibility + ((word(before, AreaCount) * 2 + 3) & ~3U)) ||
            (at >= 0x801C0AC0 && at < 0x801C0AC8);
        if (matrices) allowed |= (at >= MatrixPool + 0x95C0 && at < MatrixPool + 0x98C0) ||
            (at >= MatrixPool + 0x9BC0 && at < MatrixPool + 0x9EC0) ||
            (at >= Indices && at < Indices + 64);
        if (areaMatrices) {
            const auto pool = word(before, 0x801AE948);
            allowed |= (at >= pool + 0xA1C0 && at < pool + 0xA9C0) ||
                (at >= AreaIndices && at < AreaIndices + 256);
        }
        good &= allowed;
    }
    require(good, "only rendering scratch, native matrices and visibility changed; course/physics/camera unchanged");
}
void otherListsEqual(const Ram& a, const Ram& b) {
    for (const auto base : {0x801C08C0U, 0x801C0AC0U})
        for (unsigned i = 0; i < 3; ++i)
            require(visibility(a, i, base) == visibility(b, i, base), "unrelated native object distances unchanged");
}
void distanceCases() {
    const std::vector<float> distances{100, 1000, 1500, 1999, 2000, 2250, 2500, 2999, 3000, 3500, 3999, 4000};
    for (unsigned course = 0; course <= 8; ++course) for (unsigned camera = 0; camera < 2; ++camera)
        for (unsigned setting = 0; setting < 3; ++setting) {
            ++cases; auto input = initial(distances, course, camera);
            auto original = input; run(original, baseline_visibility);
            auto result = input; wr64::draw_distance::set_mode(setting); run(result, enhanced_visibility);
            auto regenerated = input; run(regenerated, regenerated_visibility);
            require(result == regenerated, "durable regenerated hook output identical");
            preserved(input, result); otherListsEqual(original, result);
            if (setting == 0) { require(result == original, "Original preserves native visibility byte-for-byte on every course"); continue; }
            auto independent = input;
            put(independent, Descriptor + 0xA0, setting == 1 ? 1500 : 2000);
            put(independent, Descriptor + 0xA4, setting == 1 ? 3000 : 4000);
            run(independent, baseline_visibility);
            for (unsigned i = 0; i < distances.size(); ++i)
                require(visibility(result, i) == visibility(independent, i), "extended buoy visibility/fade matches original native math with scaled limits");
            require(visibility(original, 6) == -1 && visibility(result, 6) >= 0, "a buoy beyond native cutoff now visible");
        }
}
void rejectionCases() {
    for (unsigned setting = 0; setting < 3; ++setting) {
        ++cases; auto input = initial({2500, -2500, 2500, 2500, 2500, -3500});
        put(input, Buoy + 2 * 0x104 + 0xC8, 0); // inactive
        put(input, Buoy + 3 * 0x104 + 0xC0, 2); // native phase skip
        put(input, 0x800D4B04, 1);
        number(input, Buoy + 4 * 0x104, 2500); number(input, Buoy + 4 * 0x104 + 8, 0); // sideways
        put(input, Buoy + 5 * 0x104 + 0x9C, 1); // native special billboard: double cutoff, angular bypass
        auto original = input; run(original, baseline_visibility);
        auto result = input; recomp_context c; wr64::draw_distance::set_mode(setting); run(result, enhanced_visibility, &c);
        if (!setting) require(result == original, "Original retains exceptional type and state rules");
        for (unsigned i : {1U, 2U, 3U, 4U}) require(visibility(result, i) == -1, "native behind-camera, side, inactive and phase exclusions retained");
        require(visibility(result, 5) >= 0, "native double-radius special type is preserved");
        otherListsEqual(original, result); preserved(input, result);
    }
}
void capacityCases() {
    // Near native entries deliberately come after every extended entry. A
    // prefix-only cap would discard them; the nine nearest extras are odd IDs.
    std::vector<float> distances{3900, 2100, 3800, 2200, 3700, 2300, 3600, 2400, 3500, 2500,
        3400, 2600, 3300, 2700, 3200, 2800, 3100, 2900, 3000, 500, 900, 1900};
    for (unsigned setting : {1U, 2U}) {
        ++cases; auto input = initial(distances); auto original = input; run(original, baseline_visibility);
        auto result = input; recomp_context c; wr64::draw_distance::set_mode(setting); run(result, enhanced_visibility, &c);
        unsigned admitted = 0;
        for (unsigned i = 0; i < distances.size(); ++i) {
            const bool expected = i >= 19 || (i < 18 && i % 2 == 1);
            require((visibility(result, i) >= 0) == expected, "capacity preserves native-visible entries and nearest nine new entries");
            admitted += visibility(result, i) >= 0;
        }
        require(admitted == 12, "expanded visible buoys fit all twelve native matrix slots");
        otherListsEqual(original, result);
        context(c); c.r2 = S32(Buoy); c.r4 = S32(0x801C0000); c.r9 = S32(Visibility);
        c.r22 = S32(Camera); c.r30 = S32(Buoy); c.f24.fl = 0; c.f26.fl = 1;
        enhanced_buoy_matrices(result.data(), &c);
        require(c.r13 == 12, "native matrix preparation processes every admitted buoy");
        const auto* rdram = result.data(); unsigned slot = 0;
        for (unsigned i = 0; i < distances.size(); ++i) if (visibility(result, i) >= 0) {
            require(result[((Indices + i) ^ 3) & 0x7FFFFF] == slot++, "every visible buoy references a prepared native matrix slot");
        }
        preserved(input, result, true);
        require(word(result, MatrixPool + 0x98C0) == 0 && word(result, MatrixPool + 0x9EC0) == 0,
            "thirteenth base/tail slots and other view bank untouched");
        enhanced_buoy_end(result.data(), &c);
        for (unsigned i = 0; i < distances.size(); ++i)
            require(visibility(result, i) == visibility(original, i), "late native overlays receive exact original buoy visibility and fade");
        preserved(input, result, true);
        const auto ended = result; enhanced_buoy_end(result.data(), &c);
        require(result == ended, "completed-frame end hook is idempotent");
    }
}
void unsupportedCases() {
    // Execute the same complete native loop in unsupported frontend/mode
    // states; the helper must be a byte-identical no-op.
    const std::vector<std::pair<uint32_t, uint32_t>> mutations{
        {0x800DAB28, 3}, {0x800DAB28, 0}, {0x800DAB2C, 1}, {0x800D8170, 9},
        {0x801C0C80, Descriptor + 4},
        {0x801518B8, DrawPool + 8}, {0x801AE948, MatrixPool + 8}};
    wr64::draw_distance::set_mode(2);
    for (auto [address, value] : mutations) {
        ++cases; auto input = initial({500, 2500}); put(input, address, value);
        auto original = input, result = input;
        run(original, baseline_visibility); run(result, enhanced_visibility);
        require(result == original, "unsupported mode, camera, descriptor or pool preserves complete native output");
    }
    ++cases; auto empty = initial({}); auto original = empty; run(original, baseline_visibility); run(empty, enhanced_visibility);
    require(empty == original, "empty native list remains unchanged");
    for (unsigned value : {3U, 100U, 0xFFFFFFFFU}) {
        wr64::draw_distance::set_mode(value);
        require(wr64::draw_distance::mode() == 0, "invalid persisted draw-distance mode defaults to Original");
    }
}
void fallbackCases() {
    const std::vector<float> distances{500, 1500, 1999, 2100, 2300, 2500};
    constexpr unsigned Extras = 3;
    const uint32_t boundary = DrawPool + 0x6000 - (0x3000 + 192 * Extras);
    for (int variant = 0; variant < 6; ++variant) {
        ++cases; auto input = initial(distances); auto original = input; run(original, baseline_visibility);
        auto result = input; recomp_context c; wr64::draw_distance::set_mode(2); run(result, enhanced_visibility, &c);
        const auto scaled = result;
        if (variant == 0) put(result, Stack + 0x550, boundary);
        if (variant == 1) put(result, Stack + 0x550, boundary + 8);
        if (variant == 2) put(result, Stack + 0x550, DrawPool + 1);
        if (variant == 3) put(result, Stack + 0x550, DrawPool - 8);
        if (variant == 4) put(result, 0x801518B8, DrawPool + 0x18FE8);
        if (variant == 5) wr64::draw_distance::set_mode(0);
        wr64_draw_distance_capacity(result.data(), &c);
        for (unsigned i = 0; i < distances.size(); ++i)
            require(visibility(result, i) == visibility(variant == 0 ? scaled : original, i),
                "exact remaining DL capacity retains extension; shortage, changed pool/mode restores native visibility and fade");
        const auto after = result; wr64_draw_distance_capacity(result.data(), &c);
        require(after == result, "capacity fallback consumed once without accumulating changes");
        enhanced_buoy_end(result.data(), &c);
        for (unsigned i = 0; i < distances.size(); ++i)
            require(visibility(result, i) == visibility(original, i), "end restores original visibility after either capacity decision");
    }
    // A native crowded state already over twelve visible entries must remain
    // byte-for-byte native; this experiment is never allowed to add more.
    ++cases; auto crowded = initial(std::vector<float>(13, 1500));
    auto original = crowded; run(original, baseline_visibility);
    wr64::draw_distance::set_mode(2); run(crowded, enhanced_visibility);
    require(crowded == original, "original over-budget crowd falls back without modifying native visibility/fade");
    // Apply repeatedly to actual native inputs: limits are local registers,
    // so neither course data nor later frames acquire multiplied distances.
    ++cases; auto input = initial(distances), repeated = input;
    wr64::draw_distance::set_mode(2); run(repeated, enhanced_visibility);
    const auto first = repeated; run(repeated, enhanced_visibility);
    require(repeated == first, "repeated frames do not accumulate distance multipliers");
    auto originalAgain = input; run(originalAgain, baseline_visibility);
    wr64::draw_distance::set_mode(0); run(repeated, enhanced_visibility);
    require(repeated == originalAgain, "switching back to Original reconstructs exact native frame");
    // Malformed inputs go directly to the hook, avoiding intentionally running
    // native instructions with corrupt camera/list pointers afterwards.
    const std::vector<std::pair<uint32_t, uint32_t>> invalidWords{
        {Count, 65}, {Count, 0}, {Descriptor + 0xA0, 2000}, {Descriptor + 0xA4, 1000001},
        {Camera + 0x4C, 0x7FC00000}, {Buoy, 0x7F800000}, {0x80223930, 2}};
    wr64::draw_distance::set_mode(2);
    for (const auto [address, value] : invalidWords) {
        ++cases; auto ram = initial(distances); put(ram, address, value);
        recomp_context c; context(c); c.r2 = S32(Descriptor); c.r17 = word(ram, Descriptor + 0xA0);
        c.r18 = word(ram, Descriptor + 0xA4); c.r22 = S32(Camera);
        const auto before = ram; const auto near = c.r17, far = c.r18;
        wr64_draw_distance_begin(ram.data(), &c); wr64_draw_distance_finish(ram.data(), &c);
        require(c.r17 == near && c.r18 == far && ram == before, "invalid list, limits or coordinate rejects extension without touching RAM/registers");
    }
    ++cases; wr64::draw_distance::set_mode(0);
    wr64_draw_distance_begin(nullptr, nullptr); wr64_draw_distance_finish(nullptr, nullptr); wr64_draw_distance_capacity(nullptr, nullptr);
    require(true, "Original accepts null hook inputs without reading memory");
    ++cases; auto unmatched = initial(distances); recomp_context live, other;
    wr64::draw_distance::set_mode(2); run(unmatched, enhanced_visibility, &live); const auto pending = unmatched;
    context(other); enhanced_buoy_end(unmatched.data(), &other);
    require(unmatched == pending, "unmatched context cannot consume the current frame's visibility restoration");
    enhanced_buoy_end(unmatched.data(), &live);
}
void fillArea(Ram& ram, const std::vector<float>& distances) {
    put(ram, AreaCount, uint32_t(distances.size())); auto* rdram = ram.data();
    for (unsigned i = 0; i < distances.size(); ++i) {
        const uint32_t object = Area + i * 0x18;
        number(ram, object, 0); number(ram, object + 4, 20); number(ram, object + 8, distances[i]);
        put(ram, object + 0x10, i % 2);
        MEM_H(0, S32(AreaVisibility + i * 2)) = -7;
        MEM_B(0, S32(AreaIndices + i)) = 0xFE;
    }
}
void thirdListEqual(const Ram& a, const Ram& b) {
    for (unsigned i = 0; i < 3; ++i)
        require(visibility(a, i, 0x801C0AC0) == visibility(b, i, 0x801C0AC0), "third native object roster retains authored distance and fade");
}
void endBoth(Ram& ram, recomp_context& c) {
    enhanced_area_end(ram.data(), &c); enhanced_buoy_end(ram.data(), &c);
}
void areaDistanceCases() {
    const std::vector<float> distances{100, 1000, 1500, 1999, 2000, 2250, 2500, 2999, 3000, 3500, 3999, 4000};
    for (unsigned course = 0; course <= 8; ++course) for (unsigned camera = 0; camera < 2; ++camera)
        for (unsigned setting = 0; setting < 3; ++setting) {
            ++cases; auto input = initial({500, 2500}, course, camera); fillArea(input, distances);
            auto original = input; run(original, baseline_visibility);
            auto independent = input;
            put(independent, Descriptor + 0xA0, setting == 1 ? 1500 : 2000);
            put(independent, Descriptor + 0xA4, setting == 1 ? 3000 : 4000);
            run(independent, baseline_visibility);
            auto result = input; recomp_context c; wr64::draw_distance::set_mode(setting); run(result, enhanced_visibility, &c);
            const bool active = setting != 0;
            if (!active) require(result == original, "Original preserves both complete native buoy rosters on every course");
            for (unsigned i = 0; i < distances.size(); ++i)
                require(visibility(result, i, AreaVisibility) == visibility(active ? independent : original, i, AreaVisibility),
                    "area buoy distance and fade match unmodified native math with independently scaled limits");
            if (active) require(visibility(original, 6, AreaVisibility) == -1 && visibility(result, 6, AreaVisibility) >= 0,
                "area-limit buoy beyond native cutoff is now visible");
            // Checkpoint behavior must remain the validated implementation.
            for (unsigned i = 0; i < 2; ++i)
                require(visibility(result, i) == visibility(active ? independent : original, i), "checkpoint extension retains its validated distance and fade");
            thirdListEqual(original, result); preserved(input, result);
            endBoth(result, c);
            for (unsigned i = 0; i < distances.size(); ++i)
                require(visibility(result, i, AreaVisibility) == visibility(original, i, AreaVisibility), "area end restores exact original visibility for later native consumers");
            for (unsigned i = 0; i < 2; ++i)
                require(visibility(result, i) == visibility(original, i), "checkpoint end restoration remains independent");
        }
}
void areaRejectionCases() {
    for (unsigned setting = 0; setting < 3; ++setting) {
        ++cases; auto input = initial({500, 2500}); fillArea(input, {2500, -2500, 2500, 2500, 2500, 2500, 2500, 2500});
        number(input, Area + 2 * 0x18, 2500); number(input, Area + 2 * 0x18 + 8, 0);
        put(input, Area + 3 * 0x18 + 0x10, 4); put(input, Area + 4 * 0x18 + 0x10, 5);
        put(input, Area + 5 * 0x18 + 0x10, 6);
        put(input, Area + 6 * 0x18 + 0x10, 2); put(input, Area + 7 * 0x18 + 0x10, 3);
        auto original = input, result = input; run(original, baseline_visibility);
        recomp_context c; wr64::draw_distance::set_mode(setting); run(result, enhanced_visibility, &c);
        for (unsigned i : {1U, 2U, 3U, 4U, 5U, 6U, 7U})
            require(visibility(result, i, AreaVisibility) == visibility(original, i, AreaVisibility),
                "area angular exclusions, hidden types4/5, tetrapods2/3 and unsupported materials retain native output");
        if (setting) require(visibility(result, 0, AreaVisibility) >= 0,
            "ordinary colored area buoy gains selected distance");
        thirdListEqual(original, result); preserved(input, result); endBoth(result, c);
    }
    // Area support is independent of the checkpoint roster being nonempty.
    ++cases; wr64_draw_distance_begin(nullptr, nullptr);
    auto input = initial({}); fillArea(input, {500, 2500}); auto original = input; run(original, baseline_visibility);
    auto result = input; recomp_context c; wr64::draw_distance::set_mode(2); run(result, enhanced_visibility, &c);
    require(visibility(original, 1, AreaVisibility) < 0 && visibility(result, 1, AreaVisibility) >= 0,
        "area buoys extend when no checkpoints are present");
    endBoth(result, c);
}
void areaMatrixCases() {
    std::vector<float> distances;
    for (unsigned i = 0; i < 47; ++i) distances.push_back(2800.0f - float(i) * 17.0f);
    distances.insert(distances.end(), {500, 900, 1900});
    for (unsigned buffer = 0; buffer < 2; ++buffer) for (unsigned setting : {1U, 2U}) {
        ++cases; auto input = initial({500, 2500}); fillArea(input, distances);
        put(input, Area + 48 * 0x18 + 0x10, 2); put(input, Area + 49 * 0x18 + 0x10, 3);
        const uint32_t matrices = MatrixPool + buffer * 0xB2F0;
        put(input, 0x801AE948, matrices); put(input, 0x801518B8, DrawPool + buffer * 0x18FE8);
        put(input, Stack + 0x550, DrawPool + buffer * 0x18FE8 + 0x100);
        auto original = input; run(original, baseline_visibility);
        auto result = input; recomp_context c; wr64::draw_distance::set_mode(setting); run(result, enhanced_visibility, &c);
        unsigned admitted = 0;
        for (unsigned i = 0; i < distances.size(); ++i) {
            const bool expected = i >= 18;
            require((visibility(result, i, AreaVisibility) >= 0) == expected, "area capacity keeps native-visible entries and nearest29 extra buoys");
            admitted += visibility(result, i, AreaVisibility) >= 0;
        }
        require(admitted == 32, "expanded area visibility fits32 native matrix slots");
        context(c); c.r11 = S32(0x801C0000); c.r22 = S32(Camera); c.f24.fl = 0;
        enhanced_area_matrices(result.data(), &c);
        unsigned slot = 0;
        for (unsigned i = 0; i < distances.size(); ++i) if (visibility(result, i, AreaVisibility) >= 0) {
            require(result[((AreaIndices + i) ^ 3) & 0x7FFFFF] == slot++, "each area buoy uses its prepared native matrix slot");
            const uint32_t matrix = matrices + 0xA1C0 + (slot - 1) * 64;
            require(std::any_of(result.begin() + (matrix & 0x7FFFFF), result.begin() + (matrix & 0x7FFFFF) + 64,
                [](uint8_t value) { return value != 0; }), "actual native area matrix exists");
        }
        require(slot == 32 && word(result, matrices + 0xA9C0) == 0, "all32 slots prepared and adjacent second-view bank untouched");
        require(visibility(result, 1) >= 0, "area admission preserves the checkpoint extension");
        thirdListEqual(original, result); preserved(input, result, false, true);
        endBoth(result, c);
        for (unsigned i = 0; i < distances.size(); ++i)
            require(visibility(result, i, AreaVisibility) == visibility(original, i, AreaVisibility), "area matrix preparation ends with original late-consumer visibility");
    }
}
uint32_t areaSpritePackets(Ram& ram, recomp_context& c) {
    const uint32_t start = word(ram, Stack + 0x550);
    const std::array<Fn, 4> passes{area_type0_top, area_type0_bottom, area_type1_top, area_type1_bottom};
    for (const auto pass : passes) {
        context(c); c.r11 = word(ram, AreaCount); c.r12 = 0x0102CD78;
        c.r17 = S32(0xE7000000); c.r18 = 0x0500A1C0 + word(ram, 0x800DAB2C) * 0x800; c.r19 = S32(0xFB000000);
        c.r20 = 0x01020040; c.r21 = S32(-1); c.r23 = S32(0x801C0C80); c.r31 = 0x06000000;
        put(ram, Stack + 0x540, 0x0102CDD8); put(ram, Stack + 0x544, 0x0102CDA8);
        put(ram, Stack + 0x548, 0x0102CC70); put(ram, Stack + 0x54C, 0x0102CC58);
        pass(ram.data(), &c);
    }
    return word(ram, Stack + 0x550) - start;
}
void areaJointBudgetCases() {
    constexpr unsigned CheckpointExtras = 3, AreaVisible = 6;
    const uint32_t checkpointReserve = 0x3000 + CheckpointExtras * 192;
    const uint32_t areaCost = 512 + AreaVisible * 64;
    const uint32_t boundary = DrawPool + 0x6000 - checkpointReserve - areaCost;
    for (unsigned variant = 0; variant < 5; ++variant) {
        ++cases; auto input = initial({500, 1500, 1999, 2100, 2300, 2500});
        fillArea(input, {500, 1500, 1999, 2100, 2300, 2500});
        auto original = input; run(original, baseline_visibility);
        auto result = input; recomp_context c; wr64::draw_distance::set_mode(2); run(result, enhanced_visibility, &c);
        const auto extended = result;
        const uint32_t cursor = variant == 1 ? boundary + 8 : (variant == 2 ? DrawPool - 8 : boundary);
        put(result, Stack + 0x550, cursor);
        if (variant == 3) put(result, 0x801518B8, DrawPool + 0x18FE8);
        if (variant == 4) wr64::draw_distance::set_mode(0);
        context(c); c.r11 = S32(0x801C0000); c.r22 = S32(Camera); c.f24.fl = 0;
        enhanced_area_matrices(result.data(), &c);
        for (unsigned i = 0; i < AreaVisible; ++i) {
            require(visibility(result, i, AreaVisibility) == visibility(variant == 0 ? extended : original, i, AreaVisibility),
                "joint DL guard admits exact boundary and otherwise restores native area visibility/fade");
            require(visibility(result, i) == visibility(extended, i), "area fallback does not discard checkpoint extension");
        }
        if (variant <= 1) {
            const uint32_t bytes = areaSpritePackets(result, c);
            const uint32_t rendered = variant == 0 ? AreaVisible : 3;
            require(bytes == rendered * 64, "actual two native sprite layers emit64 bytes per visible area buoy");
            unsigned matrices = 0;
            for (uint32_t at = cursor; at < cursor + bytes; at += 8) if (word(result, at) == 0x01020040) {
                const uint32_t matrix = word(result, at + 4);
                require(matrix >= 0x0500A1C0 && matrix < 0x0500A9C0 && ((matrix - 0x0500A1C0) % 64) == 0,
                    "both rendered sprite layers reference prepared area matrix slots");
                ++matrices;
            }
            require(matrices == rendered * 2, "both native area sprite layers rendered once per admitted buoy");
            put(result, Stack + 0x550, word(result, Stack + 0x550) + 512);
            enhanced_area_end(result.data(), &c); wr64_draw_distance_capacity(result.data(), &c);
            for (unsigned i = 0; i < AreaVisible; ++i)
                require(visibility(result, i) == visibility(extended, i), "joint budget retains checkpoint extension after actual area sprite packets and fixed-cost reserve");
        }
        endBoth(result, c);
        for (unsigned i = 0; i < AreaVisible; ++i)
            require(visibility(result, i, AreaVisibility) == visibility(original, i, AreaVisibility), "area end restores baseline after either budget result");
    }
}
void areaGuardCases() {
    const std::vector<std::pair<uint32_t, uint32_t>> unsupported{
        {0x800DAB28, 3}, {0x800DAB2C, 1}, {0x800D8170, 9},
        {0x801C0C80, Descriptor + 4}, {0x801518B8, DrawPool + 8}, {0x801AE948, MatrixPool + 8}};
    wr64::draw_distance::set_mode(2);
    for (const auto [address, value] : unsupported) {
        ++cases; auto input = initial({500, 2500}); fillArea(input, {500, 2500}); put(input, address, value);
        auto original = input, result = input; run(original, baseline_visibility);
        recomp_context c; run(result, enhanced_visibility, &c);
        require(result == original, "unsupported state/camera/descriptor/pool preserves both complete native buoy rosters");
        endBoth(result, c);
    }
    ++cases; auto input = initial({500, 2500}); std::vector<float> distances(256, 5000);
    distances[254] = 500; distances[255] = 2500; fillArea(input, distances);
    auto original = input; run(original, baseline_visibility);
    auto result = input; recomp_context c; run(result, enhanced_visibility, &c);
    require(visibility(original, 255, AreaVisibility) < 0 && visibility(result, 255, AreaVisibility) >= 0,
        "last valid area roster entry participates in distance extension");
    context(c); c.r11 = S32(0x801C0000); c.r22 = S32(Camera); c.f24.fl = 0;
    enhanced_area_matrices(result.data(), &c);
    require(result[((AreaIndices + 254) ^ 3) & 0x7FFFFF] == 0 && result[((AreaIndices + 255) ^ 3) & 0x7FFFFF] == 1,
        "native traversal of256 area records produces bounded indices for final two entries");
    preserved(input, result, false, true); endBoth(result, c);
    require(word(result, 0x801C0C80) == Descriptor, "last area matrix index preserves adjacent descriptor pointer");

    ++cases; input = initial({500, 2500}); fillArea(input, std::vector<float>(33, 1500));
    original = input; run(original, baseline_visibility); result = input; run(result, enhanced_visibility, &c);
    for (unsigned i = 0; i < 33; ++i)
        require(visibility(result, i, AreaVisibility) == visibility(original, i, AreaVisibility),
            "native overfull33-area-buoy state falls back without changing authored visibility/fade");
    require(visibility(result, 1) >= 0, "native area crowd does not turn off checkpoint extension");
    endBoth(result, c);

    for (unsigned variant = 0; variant < 6; ++variant) {
        ++cases; auto ram = initial({500}); fillArea(ram, {500, 2500}); context(c);
        c.r11 = 2; c.r17 = 1000; c.r18 = 2000; c.r22 = S32(Camera);
        if (variant == 0) { put(ram, AreaCount, 257); c.r11 = 257; }
        if (variant == 1) { put(ram, AreaCount, 0); c.r11 = 0; }
        if (variant == 2) put(ram, Area + 8, 0x7FC00000);
        if (variant == 3) c.r11 = 1;
        if (variant == 4) c.r29 += 1;
        if (variant == 5) c.r22 += 4;
        const auto before = ram;
        wr64_area_draw_distance_begin(ram.data(), &c); wr64_area_draw_distance_finish(ram.data(), &c);
        wr64_area_draw_distance_end(ram.data(), &c);
        require(c.r17 == 1000 && c.r18 == 2000 && ram == before,
            "invalid area count, coordinates, register count, stack or camera leave RAM and distance registers unchanged");
    }
    ++cases; wr64::draw_distance::set_mode(0);
    wr64_area_draw_distance_begin(nullptr, nullptr); wr64_area_draw_distance_finish(nullptr, nullptr);
    wr64_area_draw_distance_capacity(nullptr, nullptr); wr64_area_draw_distance_end(nullptr, nullptr);
    require(true, "Original area helpers handle null inputs without touching memory");
}
void worldScopeCases() {
    // Admission follows actual world rendering, including the opening and
    // scripted cameras. View and camera indices deliberately differ in half
    // the cases, as they select different things in native code.
    constexpr std::array<unsigned, 5> phases{0, 1, 4, 10, 21};
    constexpr std::array<unsigned, 5> modes{2, 41, 42, 43, 44};
    for (unsigned course = 0; course <= 8; ++course)
        for (unsigned players = 1; players <= 2; ++players)
            for (unsigned view = 0; view < players; ++view)
                for (unsigned scene = 0; scene < phases.size(); ++scene) {
                    ++cases;
                    const unsigned camera = (view + scene) % 2;
                    auto input = initial({500, 1500, 2500, 4500}, course, camera);
                    fillArea(input, {500, 1500, 2500, 4500});
                    put(input, 0x800DAB28, players); put(input, 0x800DAB2C, view);
                    put(input, 0x801C0C80, Descriptor + view * 0x110);
                    put(input, 0x80223930 + view * 4, camera);
                    put(input, 0x801CE638, phases[scene]); put(input, 0x800DAB24, modes[scene]);
                    put(input, Camera + camera * 0x10C, scene);
                    put(input, Camera + camera * 0x10C + 0xE8, 1 - camera);
                    auto original = input; run(original, baseline_visibility);
                    auto result = input; recomp_context c;
                    wr64::draw_distance::set_mode(0); run(result, enhanced_visibility, &c);
                    require(result == original, "Original is exact in every course, view and world camera state");
                    result = input; wr64::draw_distance::set_mode(2); run(result, enhanced_visibility, &c);
                    for (const auto base : {Visibility, AreaVisibility}) {
                        require(visibility(original, 2, base) < 0 && visibility(result, 2, base) >= 0,
                            "both buoy families extend in all course/player/view/opening and scripted-camera combinations");
                        require(visibility(result, 3, base) < 0, "world scope retains the selected far cutoff");
                    }
                    thirdListEqual(original, result); preserved(input, result);
                    endBoth(result, c);
                    for (const auto base : {Visibility, AreaVisibility}) for (unsigned i = 0; i < 4; ++i)
                        require(visibility(result, i, base) == visibility(original, i, base),
                            "every world view restores its original scratch visibility before the next view");
                }
}
void twoPlayerMatrixCases() {
    std::vector<float> checkpoints(10, 2500), boundaries(30, 2500);
    checkpoints.insert(checkpoints.end(), {500, 1500});
    boundaries.insert(boundaries.end(), {500, 1500});
    for (unsigned buffer = 0; buffer < 2; ++buffer) for (bool swapped : {false, true}) {
        ++cases; auto result = initial(checkpoints, 6); fillArea(result, boundaries);
        const uint32_t matrices = MatrixPool + buffer * 0xB2F0;
        const uint32_t pool = DrawPool + buffer * 0x18FE8;
        put(result, 0x800DAB28, 2); put(result, 0x80223930, swapped ? 1 : 0);
        put(result, 0x80223934, swapped ? 0 : 1);
        put(result, 0x801AE948, matrices); put(result, 0x801518B8, pool);
        put(result, Stack + 0x550, pool + 0x100);
        number(result, Camera + 0x10C + 0x50, 100);
        for (unsigned view = 0; view < 2; ++view) {
            put(result, 0x800DAB2C, view);
            put(result, 0x801C0C80, Descriptor + view * 0x110);
            const uint32_t camera = Camera + word(result, 0x80223930 + view * 4) * 0x10C;
            const auto before = result;
            auto original = result; run(original, baseline_visibility);
            recomp_context c; wr64::draw_distance::set_mode(2); run(result, enhanced_visibility, &c);
            context(c); c.r11 = S32(0x801C0000); c.r22 = S32(camera); c.f24.fl = 0;
            enhanced_area_matrices(result.data(), &c);
            for (unsigned i = 0; i < 32; ++i)
                require(result[((AreaIndices + i) ^ 3) & 0x7FFFFF] == i, "both views prepare all32 area matrix indices");
            enhanced_area_end(result.data(), &c);
            context(c); c.r2 = S32(Buoy); c.r4 = S32(0x801C0000); c.r9 = S32(Visibility);
            c.r22 = S32(camera); c.r30 = S32(Buoy); c.f24.fl = 0; c.f26.fl = 1;
            enhanced_buoy_matrices(result.data(), &c);
            for (unsigned i = 0; i < 12; ++i)
                require(result[((Indices + i) ^ 3) & 0x7FFFFF] == i, "both views prepare all12 checkpoint matrix indices");
            for (const auto [offset, bytes] : {std::pair{0x95C0U + view * 0x300U, 0x300U},
                    std::pair{0x9BC0U + view * 0x300U, 0x300U}, std::pair{0xA1C0U + view * 0x800U, 0x800U}}) {
                const auto first = (matrices + offset) & 0x7FFFFF;
                for (unsigned i = 0; i < bytes; i += 64)
                    require(std::any_of(result.begin() + first + i, result.begin() + first + i + 64,
                        [](uint8_t value) { return value != 0; }), "every admitted object has a native matrix in the selected view bank");
            }
            for (const auto [offset, bytes] : {std::pair{0x95C0U + (1 - view) * 0x300U, 0x300U},
                    std::pair{0x9BC0U + (1 - view) * 0x300U, 0x300U}, std::pair{0xA1C0U + (1 - view) * 0x800U, 0x800U}}) {
                const auto first = (matrices + offset) & 0x7FFFFF;
                require(std::equal(before.begin() + first, before.begin() + first + bytes, result.begin() + first),
                    "one view never overwrites the other view's prepared matrices");
            }
            enhanced_buoy_end(result.data(), &c);
            for (unsigned i = 0; i < 12; ++i)
                require(visibility(result, i) == visibility(original, i), "P1/P2 checkpoint visibility restores independently");
            require(word(result, 0x801AE950) == 0, "two full buoy banks allocate no shared dynamic matrices");
        }
    }
}
void twilightCleanupCases() {
    constexpr uint32_t common = 0x80480000;
    for (unsigned players = 1; players <= 2; ++players) for (unsigned view = 0; view < players; ++view)
        for (bool enhanced : {false, true}) {
            ++cases; enhancedTwoPlayerLights = enhanced;
            auto input = initial({500, 1500, 2500, 3500}, 6); fillArea(input, {500, 2500});
            put(input, 0x800DAB28, players); put(input, 0x800DAB2C, view);
            put(input, 0x801C0C80, Descriptor + view * 0x110);
            put(input, 0x80223934, 1); number(input, Camera + 0x10C + 0x50, 80);
            put(input, 0x801AE950, 17); put(input, 0x80151984, common & 0x1FFFFFFF);
            constexpr uint32_t roots[] = {0x2BF48, 0x2BFD8, 0x2C798, 0x2C828};
            constexpr uint32_t models[] = {0x0102BED8, 0x0102BF58, 0x0102C728, 0x0102C7A8};
            for (unsigned i = 0; i < 4; ++i) {
                put(input, common + roots[i], 0x06000000); put(input, common + roots[i] + 4, models[i]);
                put(input, common + roots[i] + 8, 0xB8000000);
            }
            auto original = input; run(original, baseline_visibility);
            auto result = input; recomp_context c; wr64::draw_distance::set_mode(2); run(result, enhanced_visibility, &c);
            require(visibility(result, 2) >= 0 && visibility(result, 3) >= 0, "Twilight body pass receives the selected extended buoys");
            enhanced_area_end(result.data(), &c);
            context(c); c.r24 = players; c.r21 = S32(0x800DAB28);
            const uint32_t start = DrawPool + 0x100;
            put(result, Stack + 0x550, start);
            extended_twilight_tail(result.data(), &c);
            recomp_context native; context(native); native.r24 = players; native.r21 = S32(0x800DAB28);
            put(original, Stack + 0x550, start); native_twilight_tail(original.data(), &native);
            const uint32_t end = word(result, Stack + 0x550);
            require(end == word(original, Stack + 0x550), "distance extension adds no Twilight light display commands");
            require(word(result, 0x801AE950) == word(original, 0x801AE950), "distance extension adds no Twilight shared light matrices");
            const auto first = start & 0x7FFFFF;
            require(std::equal(original.begin() + first, original.begin() + first + end - start, result.begin() + first),
                "actual native Twilight light packets remain byte-identical in1P and both2P views");
            const auto matrices = (MatrixPool + 0x4140) & 0x7FFFFF;
            require(std::equal(original.begin() + matrices, original.begin() + matrices + 0x1000, result.begin() + matrices),
                "actual native Twilight dynamic matrix bytes remain unchanged");
            for (unsigned i = 0; i < 4; ++i)
                require(visibility(result, i) == visibility(original, i), "cleanup precedes the first Twilight light branch");
            const auto once = result; enhanced_buoy_end(result.data(), &c);
            require(once == result, "already consumed light cleanup remains idempotent");
        }
    enhancedTwoPlayerLights = false;
}
void twoPlayerBudgetCases() {
    for (unsigned view = 0; view < 2; ++view) for (unsigned shortage = 0; shortage < 2; ++shortage) {
        ++cases; auto input = initial({500, 2500}); fillArea(input, {500, 2500});
        put(input, 0x800DAB28, 2); put(input, 0x800DAB2C, view); put(input, 0x80223934, 1);
        put(input, 0x801C0C80, Descriptor + view * 0x110);
        number(input, Camera + 0x10C + 0x50, 80);
        auto original = input; run(original, baseline_visibility);
        auto result = input; recomp_context c; wr64::draw_distance::set_mode(2); run(result, enhanced_visibility, &c);
        const uint32_t reserve = view == 0 ? 0x4800 : 0x3000;
        const uint32_t boundary = DrawPool + 0x6000 - reserve - 192 - 512 - 2 * 64;
        put(result, Stack + 0x550, boundary + shortage * 8);
        wr64_area_draw_distance_capacity(result.data(), &c);
        require((visibility(result, 1, AreaVisibility) >= 0) == (shortage == 0),
            "P1 reserves18KiB and P2 reserves12KiB: exact joint boundary passes and one-command shortage rolls back");
        enhanced_area_end(result.data(), &c);
        put(result, Stack + 0x550, DrawPool + 0x6000 - reserve - 192 + shortage * 8);
        wr64_draw_distance_capacity(result.data(), &c);
        require((visibility(result, 1) >= 0) == (shortage == 0), "both view-specific checkpoint reserves enforce their exact capacity boundary");
        endBoth(result, c);
        for (const auto base : {Visibility, AreaVisibility})
            require(visibility(result, 1, base) == visibility(original, 1, base), "capacity decisions restore native visibility for the next view");
    }
}
void archivedOpening(const char* path) {
    ++cases; std::ifstream input(path, std::ios::binary);
    Ram capture((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    require(capture.size() == Size, "Dolphin opening archive has complete8MiB native RAM");
    require(word(capture, 0x800D8170) == 0 && word(capture, 0x801CE638) == 0 &&
        word(capture, 0x800DAB24) == 2 && word(capture, 0x800DAB28) == 1 &&
        word(capture, 0x800DAB2C) == 0, "actual archived opening globals are retained, not relabelled as gameplay");
    require(word(capture, Count) == 60 && word(capture, AreaCount) == 205,
        "actual Dolphin opening checkpoint and area rosters retained");
    recomp_context direction; context(direction);
    direction.r22 = S32(Camera + word(capture, 0x80223930) * 0x10C);
    native_camera_direction(capture.data(), &direction);
    const uint32_t pool = word(capture, 0x801518B8);
    put(capture, Stack + 0x550, pool + 0x100);
    auto original = capture; run(original, baseline_visibility);
    auto unchanged = capture; wr64::draw_distance::set_mode(0); run(unchanged, enhanced_visibility);
    require(unchanged == original, "Original remains exact with the complete archived opening data");
    for (unsigned setting : {1U, 2U}) {
        auto result = capture; recomp_context c; wr64::draw_distance::set_mode(setting); run(result, enhanced_visibility, &c);
        unsigned addedCheckpoint = 0, addedArea = 0, totalCheckpoint = 0, totalArea = 0;
        for (unsigned i = 0; i < word(capture, Count); ++i) {
            const bool before = visibility(original, i) >= 0, after = visibility(result, i) >= 0;
            require(!before || after, "archived native-visible checkpoints retain priority");
            addedCheckpoint += after && !before; totalCheckpoint += after;
        }
        for (unsigned i = 0; i < word(capture, AreaCount); ++i) {
            const bool before = visibility(original, i, AreaVisibility) >= 0, after = visibility(result, i, AreaVisibility) >= 0;
            require(!before || after, "archived native-visible area buoys retain priority");
            addedArea += after && !before; totalArea += after;
        }
        std::cout << "Archived opening setting " << setting << ": checkpoint extra " << addedCheckpoint
            << ", area extra " << addedArea << ", total " << totalCheckpoint << ", " << totalArea << '\n';
        require(addedArea > 0, "the unchanged archived opening gains actual distant area buoys");
        require(totalCheckpoint <= 12 && totalArea <= 32, "actual opening extension respects both native matrix capacities");
        wr64_area_draw_distance_capacity(result.data(), &c); enhanced_area_end(result.data(), &c);
        wr64_draw_distance_capacity(result.data(), &c); enhanced_buoy_end(result.data(), &c);
        for (unsigned i = 0; i < word(capture, Count); ++i)
            require(visibility(result, i) == visibility(original, i), "actual opening checkpoint visibility restores exactly");
        for (unsigned i = 0; i < word(capture, AreaCount); ++i)
            require(visibility(result, i, AreaVisibility) == visibility(original, i, AreaVisibility), "actual opening area visibility restores exactly");
        preserved(original, result);
        std::cout << "Opening " << (setting == 1 ? "1.5x" : "2x") << ": added " << addedCheckpoint
            << " checkpoints, " << addedArea << " area buoys; totals " << totalCheckpoint << "/12 and " << totalArea << "/32\n";
    }
}
void combinedTwoPlayerPackets() {
    constexpr uint32_t objects = 0x801BC940, objectVisibility = 0x801C0AC0;
    for (unsigned buffer = 0; buffer < 2; ++buffer) for (unsigned startOffset : {0x100U, 0x3000U, 0x4000U})
        for (unsigned mode : {0U, 2U}) {
            ++cases;
            std::vector<float> checkpoints{500, 1500}, boundaries{500, 1500};
            for (unsigned i = 0; i < 10; ++i) checkpoints.push_back(2100.f + i * 100.f);
            for (unsigned i = 0; i < 30; ++i) boundaries.push_back(2100.f + i * 30.f);
            auto ram = initial(checkpoints, 1); fillArea(ram, boundaries);
            const uint32_t pool = DrawPool + buffer * 0x18FE8, matrices = MatrixPool + buffer * 0xB2F0;
            put(ram, 0x800DAB28, 2); put(ram, 0x80223930, 0); put(ram, 0x80223934, 1);
            put(ram, 0x801518B8, pool); put(ram, 0x801AE948, matrices);
            put(ram, matrices + 0xB1C0, 0xDEADBEEF); put(ram, pool + 0x6000, 0xAABBCCDD);
            put(ram, Stack + 0x550, pool + startOffset);
            number(ram, Camera + 0x10C + 0x50, 100);
            put(ram, 0x801BFA40, 14);
            for (unsigned i = 0; i < 14; ++i) {
                const uint32_t object = objects + i * 0xC4;
                number(ram, object + 8, i == 0 ? 500.f : 2100.f + i * 75.f);
                put(ram, object + 0x4C, 1); put(ram, object + 0x54, 1);
                put(ram, object + 0xB4, 0x0D02BDE8); put(ram, object + 0xB8, 0x0D02BDF8);
                for (unsigned j = 0; j < 64; ++j)
                    ram[((0x801C0CD0 + i * 64 + j) & 0x7FFFFF)] = uint8_t(1 + i + j);
            }
            wr64::draw_distance::set_mode(mode); wr64::object_distance::set_mode(mode);
            enhancedTwoPlayerLights = true; // Exercise the existing seven-command detail pass too.
            unsigned newObjectCalls = 0;
            for (unsigned view = 0; view < 2; ++view) {
                put(ram, 0x800DAB2C, view); put(ram, 0x801C0C80, Descriptor + view * 0x110);
                const uint32_t start = word(ram, Stack + 0x550), camera = Camera + view * 0x10C;
                auto native = ram; run(native, baseline_visibility);
                recomp_context c; run(ram, enhanced_visibility, &c);
                context(c); c.r11 = S32(0x801C0000); c.r22 = S32(camera); c.f24.fl = 0;
                enhanced_area_matrices(ram.data(), &c);
                areaSpritePackets(ram, c); enhanced_area_end(ram.data(), &c);
                // The omitted fixed area setup is conservatively charged by
                // its independently audited512-byte allowance, not called a
                // rendered packet. All variable body commands below are native.
                put(ram, Stack + 0x550, word(ram, Stack + 0x550) + 512);
                context(c); c.r2 = S32(Buoy); c.r4 = S32(0x801C0000); c.r9 = S32(Visibility);
                c.r22 = S32(camera); c.r30 = S32(Buoy); c.f24.fl = 0; c.f26.fl = 1;
                enhanced_buoy_matrices(ram.data(), &c);
                c.r16 = 0; c.r17 = S32(0xE7000000); c.r19 = S32(0xFB000000);
                c.r20 = 0x01020040; c.r21 = S32(-1); c.r23 = S32(0x801C0C80); c.r31 = 0x06000000;
                native_checkpoint_body(ram.data(), &c);
                const uint32_t objectStart = word(ram, Stack + 0x550);
                c.r2 = c.r7 = S32(0x801C0000); c.r16 = 0; c.r17 = S32(0xE7000000);
                c.r20 = 0x01020040; c.r23 = 0x2000; c.r10 = S32(0xB900031D);
                c.r11 = S32(0xC8113078); c.r31 = 0x06000000; c.r22 = S32(0xBC00000E);
                extended_object_body(ram.data(), &c);
                const uint32_t objectBytes = word(ram, Stack + 0x550) - objectStart;
                require(objectBytes >= 72 && objectBytes % 72 == 0, "combined body pass preserves the native ramp and emits complete72-byte object packets");
                newObjectCalls += objectBytes / 72 - 1;
                for (unsigned i = 0; i < 14; ++i)
                    require(visibility(ram, i, objectVisibility) == visibility(native, i, objectVisibility),
                        "combined object admission restores the native table while buoy admission is still pending");
                enhanced_buoy_end(ram.data(), &c);
                for (unsigned i = 0; i < checkpoints.size(); ++i)
                    require(visibility(ram, i) == visibility(native, i), "combined checkpoint table restores before the second view");
                const uint32_t end = word(ram, Stack + 0x550);
                require(end >= start && end <= pool + 0x6000, "sequential native area, checkpoint and object packets stay within one shared2P display pool");
                for (uint32_t command = start; command < end; command += 8) if (word(ram, command) == 0x01020040) {
                    const uint32_t matrix = word(ram, command + 4);
                    if ((matrix >> 24) == 5) {
                        const uint32_t offset = matrix & 0xFFFFFF;
                        const bool valid = (offset >= 0x95C0 + view * 0x300 && offset < 0x98C0 + view * 0x300) ||
                            (offset >= 0x9BC0 + view * 0x300 && offset < 0x9EC0 + view * 0x300) ||
                            (offset >= 0xA1C0 + view * 0x800 && offset < 0xA9C0 + view * 0x800);
                        require(valid && offset % 64 == 0, "actual combined sprite/detail packets reference the current view's bounded matrix banks");
                    }
                }
            }
            require(mode != 0 || newObjectCalls == 0, "Original retains native object packet count in the combined2P run");
            if (mode == 2 && startOffset == 0x100) require(newObjectCalls > 0,
                "normal-headroom combined2P case visibly admits farther objects alongside buoy extensions");
            require(word(ram, pool + 0x6000) == 0xAABBCCDD && word(ram, matrices + 0xB1C0) == 0xDEADBEEF,
                "combined2P packets preserve display-pool and matrix-bank boundary sentinels");
            require(word(ram, 0x801AE950) == 0, "combined static objects and buoy banks add no shared dynamic matrices");
        }
    enhancedTwoPlayerLights = false;
}
Ram portalScene(const std::vector<float>& distances, unsigned portalCount = 1) {
    auto ram = initial(distances, 0);
    put(ram, 0x801CE638, 0); put(ram, 0x800DAB24, 2); // Opening, not relabelled as a race.
    for (unsigned view = 0; view < 2; ++view) {
        put(ram, Descriptor + view * 0x110 + 0xA0, 400);
        put(ram, Descriptor + view * 0x110 + 0xA4, 5000);
    }
    for (unsigned i = 0; i < portalCount; ++i) {
        const uint32_t object = Buoy + i * 0x104;
        put(ram, object + 0x98, i % 2 ? 5 : 3);
        put(ram, object + 0x9C, 1);
        // The native portal matrix builder recomputes its center from these
        // endpoints. Keep a real, nondegenerate gate at the tested distance.
        number(ram, object + 0x0C, -100); number(ram, object + 0x10, 20);
        number(ram, object + 0x14, distances[i]);
        number(ram, object + 0x18, 100); number(ram, object + 0x1C, 20);
        number(ram, object + 0x20, distances[i]);
        number(ram, object + 0x70, 1); number(ram, object + 0x74, 0);
    }
    return ram;
}
unsigned portalPackets(Ram& ram, recomp_context& c) {
    const uint32_t camera = Camera + word(ram, 0x80223930 + word(ram, 0x800DAB2C) * 4) * 0x10C;
    enhanced_area_end(ram.data(), &c);
    context(c); c.r2 = S32(Buoy); c.r4 = S32(0x801C0000); c.r9 = S32(Visibility);
    c.r22 = S32(camera); c.r30 = S32(Buoy); c.f24.fl = 0; c.f26.fl = 1;
    enhanced_buoy_matrices(ram.data(), &c);
    const uint32_t start = word(ram, Stack + 0x550);
    c.r16 = 0; c.r17 = S32(0xE7000000); c.r19 = S32(0xFB000000);
    c.r20 = 0x01020040; c.r21 = S32(-1); c.r23 = S32(0x801C0C80); c.r31 = 0x06000000;
    native_checkpoint_body(ram.data(), &c);
    unsigned calls = 0;
    for (uint32_t at = start; at < word(ram, Stack + 0x550); at += 8)
        calls += word(ram, at) == 0x06000000 && word(ram, at + 4) == 0x0D02B640;
    return calls;
}
void dolphinPortalDistances() {
    for (unsigned type : {3U, 5U}) for (unsigned objectMode = 0; objectMode < 4; ++objectMode)
    for (unsigned buoyMode = 0; buoyMode < 3; ++buoyMode)
    for (float distance : {9999.f, 10000.f, 20000.f, 29999.f, 30000.f, -29999.f}) {
        ++cases; auto input = portalScene({distance, 5500, 8500, 12000, 500});
        put(input, Buoy + 0x98, type);
        auto native = input; run(native, baseline_visibility);
        auto oracle = input;
        put(oracle, Descriptor + 0xA0, 1200); put(oracle, Descriptor + 0xA4, 15000);
        run(oracle, baseline_visibility);
        // An independent ordinary-buoy run is the old behavior that Object 3x
        // must preserve exactly, including the buoy's selected fade values.
        wr64::object_distance::set_mode(0); wr64::draw_distance::set_mode(buoyMode);
        auto reference = input; recomp_context old; run(reference, enhanced_visibility, &old);
        const auto buoyReference = reference; endBoth(reference, old);
        wr64::object_distance::set_mode(objectMode);
        auto result = input; recomp_context c; run(result, enhanced_visibility, &c);
        const bool expected = visibility(objectMode == 3 ? oracle : native, 0) >= 0;
        require((visibility(result, 0) >= 0) == expected,
            "Dolphin portal admission follows native 10000/30000 cutoff for the selected object mode");
        if (visibility(native, 0) >= 0)
            require(visibility(result, 0) == visibility(native, 0), "Already-visible portal retains its native fade");
        for (unsigned i = 1; i < 5; ++i)
            require(visibility(result, i) == visibility(buoyReference, i),
                "Portal extension changed an ordinary buoy's independent selected distance or fade");
        otherListsEqual(buoyReference, result); preserved(input, result);
        require(portalPackets(result, c) == unsigned(expected),
            "Actual native checkpoint pass did not emit exactly the expected start_dol_model display list");
        require(word(result, 0x801AE950) == 0, "Portal extension consumed shared dynamic matrices");
        endBoth(result, c);
        for (unsigned i = 0; i < 5; ++i)
            require(visibility(result, i) == visibility(native, i), "Portal cleanup failed to restore exact native visibility/fade");
    }
    wr64::object_distance::set_mode(0);
}
void dolphinPortalGuards() {
    const std::vector<std::pair<uint32_t, uint32_t>> exclusions{
        {0x800D8170, 1}, {0x800D8170, 2}, {0x800D8170, 7}, {0x801CE620, 11},
        {Buoy + 0x98, 0}, {Buoy + 0x98, 4}, {Buoy + 0x98, 6}, {Buoy + 0x9C, 0},
        {Buoy + 0x9C, 2}, {Buoy + 0xC8, 0}, {Buoy + 0xC0, 2}};
    for (unsigned buoyMode = 0; buoyMode < 3; ++buoyMode) for (auto [at, value] : exclusions) {
        ++cases; auto input = portalScene({20000, 5500, 500});
        put(input, at, value); put(input, 0x800D4B04, 1);
        wr64::draw_distance::set_mode(buoyMode); wr64::object_distance::set_mode(0);
        auto reference = input; recomp_context old; run(reference, enhanced_visibility, &old);
        const auto oldVisible = reference; endBoth(reference, old);
        wr64::object_distance::set_mode(3);
        auto result = input; recomp_context c; run(result, enhanced_visibility, &c);
        for (unsigned i = 0; i < 3; ++i)
            require(visibility(result, i) == visibility(oldVisible, i),
                "Portal extension changed another course/game/gate family or bypassed native inactive/phase rejection");
        preserved(input, result); endBoth(result, c);
    }
    wr64::object_distance::set_mode(0);
}
void dolphinPortalCapacity() {
    std::vector<float> distances;
    for (unsigned i = 0; i < 15; ++i) distances.push_back(25000.f - i * 1000.f);
    distances.insert(distances.end(), {500, 900, 1900});
    wr64::draw_distance::set_mode(0); wr64::object_distance::set_mode(3);
    for (unsigned view = 0; view < 2; ++view) for (unsigned buffer = 0; buffer < 2; ++buffer) {
        ++cases; auto input = portalScene(distances, 15);
        const uint32_t matrices = MatrixPool + buffer * 0xB2F0, pool = DrawPool + buffer * 0x18FE8;
        put(input, 0x800DAB28, 2); put(input, 0x800DAB2C, view);
        put(input, 0x801C0C80, Descriptor + view * 0x110); put(input, 0x80223934, 1);
        number(input, Camera + 0x10C + 0x50, 80);
        put(input, 0x801AE948, matrices); put(input, 0x801518B8, pool);
        put(input, Stack + 0x550, pool + 0x100);
        auto native = input; run(native, baseline_visibility);
        auto result = input; recomp_context c; run(result, enhanced_visibility, &c);
        for (unsigned i = 0; i < distances.size(); ++i)
            require((visibility(result, i) >= 0) == (i >= 6),
                "Portal crowd evicted native-visible buoys or failed to choose the nearest nine portal extras");
        require(portalPackets(result, c) == 9, "Twelve-slot portal crowd emitted wrong native model count");
        unsigned slot = 0;
        for (unsigned i = 6; i < distances.size(); ++i)
            require(result[((Indices + i) ^ 3) & 0x7FFFFF] == slot++, "Portal crowd used a stale/out-of-range native matrix index");
        for (const auto offset : {0x95C0U, 0x9BC0U}) {
            const uint32_t first = (matrices + offset + (1 - view) * 0x300) & 0x7FFFFF;
            require(std::equal(input.begin() + first, input.begin() + first + 0x300, result.begin() + first),
                "Portal crowd overwrote the other player's matrix bank");
        }
        require(word(result, 0x801AE950) == 0, "Portal crowd consumed shared dynamic matrices");
        endBoth(result, c);
        for (unsigned i = 0; i < distances.size(); ++i)
            require(visibility(result, i) == visibility(native, i), "Portal crowd failed native cleanup");
    }
    for (unsigned variant = 0; variant < 4; ++variant) {
        ++cases; auto input = portalScene({20000, 500}); auto native = input; run(native, baseline_visibility);
        wr64::draw_distance::set_mode(0); wr64::object_distance::set_mode(3);
        auto result = input; recomp_context c; run(result, enhanced_visibility, &c);
        require(visibility(result, 0) >= 0, "Portal capacity fixture failed to extend entrance");
        put(result, Stack + 0x550, DrawPool + 0x6000 - 0x3000 - 192 + (variant == 1 ? 8 : 0));
        if (variant == 2) wr64::object_distance::set_mode(2);
        if (variant == 3) wr64::draw_distance::set_mode(1);
        wr64_draw_distance_capacity(result.data(), &c);
        require((visibility(result, 0) >= 0) == (variant == 0),
            "Portal exact-fit/one-command-short budget or changed setting failed safe rollback");
        const auto once = result; wr64_draw_distance_capacity(result.data(), &c);
        require(once == result, "Portal capacity decision was not idempotent");
        endBoth(result, c);
        for (unsigned i = 0; i < 2; ++i)
            require(visibility(result, i) == visibility(native, i), "Portal rollback did not restore native visibility");
    }
    wr64::object_distance::set_mode(0); wr64::draw_distance::set_mode(0);
}
}
extern "C" uint32_t wr64_sunny_detail_active(uint8_t*) { return enhancedTwoPlayerLights ? 1U : 0U; }
extern "C" void do_break(uint32_t) { require(false, "native break"); }
extern "C" void* wr64_test_address(uint8_t* r, uint64_t at, unsigned width, const char*, int) {
    ++accesses; const uint32_t address = uint32_t(at);
    require(address >= 0x80000000 && address <= 0x80800000 - width, "native read/write inside RDRAM");
    return r + (address & 0x7FFFFF);
}
int main(int argc, char** argv) {
    distanceCases(); rejectionCases(); capacityCases(); unsupportedCases(); fallbackCases();
    areaDistanceCases(); areaRejectionCases(); areaMatrixCases(); areaJointBudgetCases(); areaGuardCases();
    worldScopeCases(); twoPlayerMatrixCases(); twilightCleanupCases(); twoPlayerBudgetCases();
    combinedTwoPlayerPackets();
    dolphinPortalDistances(); dolphinPortalGuards(); dolphinPortalCapacity();
    if (argc > 1) archivedOpening(argv[1]);
    std::cout << "PASS " << cases << " native visibility/capacity scenarios, " << checks << " checks, " << accesses << " checked accesses\n";
}
