#include "common/rt64_wr64_rt_shadow.h"
#include "native_light_presets.h"
#include <bit>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

static unsigned checks = 0;
static void require(bool result, const char *message) {
    checks++;
    if (!result) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
int main() {
    std::vector<uint8_t> ram(0x800000);
    uint32_t preset = 0xd9a74;
    uint32_t currentCourse = 1;
    auto word = [&](uint32_t offset, uint32_t value) { std::memcpy(ram.data() + preset + offset, &value, 4); };
    auto real = [&](uint32_t offset, float value) { word(offset, std::bit_cast<uint32_t>(value)); };
    auto absoluteReal = [&](uint32_t address, float value) { std::memcpy(ram.data() + address, &value, 4); };
    auto resetSunDirection = [&] {
        absoluteReal(0x154b50, 0.7071067690849304f);
        absoluteReal(0x157b50, -0.7071067690849304f);
        const double radians = 56.0 * (2.0 * std::acos(-1.0) / 4096.0);
        absoluteReal(0x154350 + 56 * 4, float(std::sin(radians)));
        absoluteReal(0x154350 + 1080 * 4, float(std::cos(radians)));
    };
    resetSunDirection();
    auto reset = [&] {
        const auto &native = NativeLightPresets[currentCourse];
        for (uint32_t i = 0; i < 3; i++) {
            word(i * 4, native.diffuse[i]); word(0xc + i * 4, native.ambient[i]);
            real(0xac + i * 4, native.direction[i]);
        }
    };
    auto read = [&] { return RT64::wr64RTShadowReadLight(ram.data(), ram.size(), currentCourse, 1); };
    for (currentCourse = 0; currentCourse < NativeLightPresets.size(); currentCourse++) {
        preset = 0xd9964 + currentCourse * 0x110;
        reset();
        const auto light = read();
        const auto &native = NativeLightPresets[currentCourse];
        require(light.valid, "all nine original world-light presets are valid");
        const float length = std::sqrt(native.direction[0]*native.direction[0] +
            native.direction[1]*native.direction[1] + native.direction[2]*native.direction[2]);
        const double dolphinAngle = 56.0 * (2.0 * std::acos(-1.0) / 4096.0);
        const std::array<float, 3> expectedDirection = currentCourse == 0
            ? std::array<float, 3>{float(std::cos(dolphinAngle) / std::sqrt(2.0)), std::sqrt(0.5f), float(std::sin(dolphinAngle) / std::sqrt(2.0))}
            : currentCourse == 2
            ? std::array<float, 3>{ 0.5f, std::sqrt(0.5f), -0.5f }
            : std::array<float, 3>{ native.direction[0]/length, native.direction[1]/length, native.direction[2]/length };
        for (uint32_t i = 0; i < 3; i++) {
            require(std::fabs(light.toLight[i] - expectedDirection[i]) < 1e-6f,
                "Dolphin and Sunset follow their native sun bearing; other directions remain identical");
            require(light.diffuse[i] == float(native.diffuse[i])/255 &&
                light.ambient[i] == float(native.ambient[i])/255,
                "fog/night course native colors remain distinct");
        }
    }
    currentCourse = 1; preset = 0xd9a74;
    reset();
    const auto expected = read();
    require(expected.valid, "valid native Sunny Beach preset");
    require(std::fabs(expected.toLight[0] + std::sqrt(0.5f)) < 1e-6f &&
        std::fabs(expected.toLight[1] - std::sqrt(0.5f)) < 1e-6f && expected.toLight[2] == 0,
        "world-space upward authored direction");
    for (unsigned i = 0; i < 3; i++) {
        require(expected.diffuse[i] == 1 && std::fabs(expected.ambient[i] - 140.0f / 255) < 1e-6f,
            "separate native world diffuse and ambient");
    }
    // Camera/light/view state must not steer the new world-fixed shadow light.
    for (uint32_t i = 0; i < 0x110 * 2; i++) { ram[0x1cb058 + i] = uint8_t(i * 37); }
    for (uint32_t i = 0; i < 268 * 2; i++) { ram[0x227c80 + i] = uint8_t(i * 17); }
    require(read().toLight == expected.toLight, "camera and mutable native lighting cannot rotate shadows");
    currentCourse = 2; preset = 0xd9b84;
    reset();
    const auto sunset = read();
    require(sunset.valid && sunset.toLight[0] > 0 && sunset.toLight[2] < 0,
        "Sunset sun lies in positive-X negative-Z world quadrant");
    require(std::fabs(sunset.toLight[1] - std::hypot(sunset.toLight[0], sunset.toLight[2])) < 1e-6f,
        "native Sunset light retains authored 45-degree elevation");
    for (uint32_t sample = 0; sample < 32; sample++) {
        for (uint32_t i = 0; i < 268 * 2; i++) { ram[0x227c80 + i] = uint8_t(i * 17 + sample * 29); }
        for (uint32_t i = 0; i < 0x110 * 2; i++) { ram[0x1cb058 + i] = uint8_t(i * 37 + sample * 13); }
        for (uint32_t i = 0; i < 32; i++) { ram[0x1c4170 + i] = uint8_t(sample * 31 + i); }
        ram[0xdab68 ^ 3] = uint8_t(sample & 1);
        require(read().toLight == sunset.toLight,
            "Sunset camera/translation/live-light/celestial-cull/reverse state cannot rotate shadows");
    }
    // A point above flat water casts away from the native sun, not towards it.
    const float height = 20;
    const std::array<float, 2> displacement{
        -height * sunset.toLight[0] / sunset.toLight[1],
        -height * sunset.toLight[2] / sunset.toLight[1] };
    require(displacement[0] < 0 && displacement[1] > 0 &&
        std::fabs(std::hypot(displacement[0], displacement[1]) - height) < 1e-5f,
        "Sunset shadow displacement opposes native 315-degree sun at its unchanged elevation");
    for (uint32_t address : { 0x154b50U, 0x157b50U }) {
        for (float invalid : { 0.0f, 2.0f, std::numeric_limits<float>::infinity(),
            std::numeric_limits<float>::quiet_NaN() }) {
            resetSunDirection(); absoluteReal(address, invalid);
            require(!read().valid, "invalid native sun table disables Sunset shadow direction");
            require(RT64::wr64RTShadowReadLight(ram.data(), ram.size(), 1, 1).toLight == expected.toLight,
                "invalid Sunset data does not alter previously validated Sunny light");
        }
    }
    resetSunDirection();
    currentCourse = 0; preset = 0xd9964; reset();
    const auto dolphin = read();
    require(dolphin.valid && dolphin.toLight[0] > 0 && dolphin.toLight[2] > 0,
        "Dolphin light must face the sun in positive X and positive Z");
    const auto beforeRead = ram;
    const auto two = RT64::wr64RTTwoPlayerShadowReadLight(ram.data(), ram.size(), 0, 2, true);
    require(two.valid && two.toLight == dolphin.toLight && ram == beforeRead,
        "both Dolphin players use the same world light without modifying the game");
    require(-height*dolphin.toLight[0]/dolphin.toLight[1] < 0 &&
        -height*dolphin.toLight[2]/dolphin.toLight[1] < 0,
        "Dolphin shadows extend away from the visible sun");
    for (unsigned sample=0; sample<32; ++sample) {
        for (uint32_t i=0; i<0x220; ++i) ram[0x1CB058+i]=uint8_t(sample*13+i);
        for (uint32_t i=0; i<0x218; ++i) ram[0x227C80+i]=uint8_t(sample*17+i);
        for (uint32_t i=0; i<0x20; ++i) ram[0x1C4170+i]=uint8_t(sample*31+i);
        // Neither the parked screen record nor pixel height is a world light.
        const uint32_t fakeHeight = sample*10000;
        std::memcpy(ram.data()+0xd9924,&fakeHeight,4);
        require(read().toLight==dolphin.toLight,"camera, parked sun and sprite height moved world shadows");
    }
    for (uint32_t address : {0x154430U,0x155430U}) {
        for (float invalid : {2.0f,std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()}) {
            resetSunDirection();absoluteReal(address,invalid);
            require(!read().valid,"invalid Dolphin sine-table data accepted");
            require(RT64::wr64RTShadowReadLight(ram.data(),ram.size(),2,1).toLight==sunset.toLight,
                "bad Dolphin data changed Sunset lighting");
        }
    }
    resetSunDirection();
    currentCourse = 1; preset = 0xd9a74;
    require(!RT64::wr64RTShadowReadLight(nullptr, ram.size(), 1, 1).valid, "null RAM rejected");
    require(!RT64::wr64RTShadowReadLight(ram.data(), 0x7fffff, 1, 1).valid, "truncated RAM rejected");
    for (uint32_t course = 0; course < 12; course++) {
        for (uint32_t players = 0; players < 4; players++) {
            require(RT64::wr64RTShadowReadLight(ram.data(), ram.size(), course, players).valid ==
                (course < 9 && players == 1), "light support restricted to nine course worlds in 1P");
        }
    }
    for (currentCourse = 0; currentCourse < NativeLightPresets.size(); currentCourse++) {
        preset = 0xd9964 + currentCourse * 0x110;
        for (float invalid : { 0.0f, -80.0f, 128.0f, -128.0f,
            std::numeric_limits<float>::infinity(), std::numeric_limits<float>::quiet_NaN() }) {
            reset(); real(0xb0, invalid); require(!read().valid, "bad or downward direction rejected on each course");
        }
        reset(); real(0xac, 0); real(0xb0, 0.01f); real(0xb4, 0);
        require(!read().valid, "almost-zero vector rejected on each course");
        for (uint32_t offset : { 0U,4U,8U,12U,16U,20U }) {
            reset(); word(offset, 256); require(!read().valid, "out-of-range light channel rejected");
            word(offset, UINT32_MAX); require(!read().valid, "negative light channel rejected");
        }
        reset(); word(0, 0); word(4, 0); word(8, 0); require(!read().valid, "no direct light rejected");
        reset();
    }
    for (uint32_t course = 0; course < 12; course++) {
        for (uint32_t players = 0; players < 4; players++) {
            for (uint32_t phase = 0; phase < 12; phase++) {
                for (uint32_t mode = 0; mode < 64; mode++) {
                    const bool supported = course < 9 && players == 1 &&
                        (phase == 1 || (phase == 8 && (mode == 30 || mode == 31)) ||
                            (course == 0 && phase == 0 && mode >= 2 && mode <= 4));
                    require(RT64::wr64RTShadowScope(true, true, course, players, phase, mode) == supported,
                        "complete course/player/phase/mode scope table");
                    require(!RT64::wr64RTShadowScope(false, true, course, players, phase, mode) &&
                        !RT64::wr64RTShadowScope(true, false, course, players, phase, mode),
                        "disabled setting or missing reflection scope rejects shadows");
                }
            }
        }
    }
    require(!RT64::wr64RTShadowReadLight(ram.data(), ram.size(), UINT32_MAX, 1).valid,
        "overflowing course ID cannot address beyond the native table");
    require(!RT64::wr64RTShadowScope(true, true, 9, 1, 4, 10) &&
        !RT64::wr64RTShadowScope(true, true, 9, 1, 10, 62), "both rider-preview menus stay excluded");
    std::cout << "PASS " << checks << " shadow scope/light checks\n";
}
