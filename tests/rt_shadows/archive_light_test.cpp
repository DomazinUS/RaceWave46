#include "common/rt64_wr64_rt_shadow.h"
#include "common/rt64_wr64_rt_celestial.h"
#include "native_light_presets.h"
#include <bit>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

static unsigned checks = 0;
static void require(bool result, const char *message) {
    checks++;
    if (!result) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
int main(int argc, char **argv) {
    if (argc < 2) { std::cerr << "Usage: wr64_rt_shadow_archive_test <rdram.bin> [...]\n"; return 2; }
    std::array<float, 3> previous{};
    bool changedDirection = false;
    unsigned sunnyCaptures = 0;
    for (int fileIndex = 1; fileIndex < argc; fileIndex++) {
        std::ifstream file(argv[fileIndex], std::ios::binary);
        const std::vector<uint8_t> ram((std::istreambuf_iterator<char>(file)), {});
        require(ram.size() == 0x800000, "archive must be eight MiB word-swapped RAM");
        // Independent byte-wise native big-endian decode through XOR3.
        auto byte = [&](uint32_t a) { return uint32_t(ram[(a & 0x7fffff) ^ 3]); };
        auto word = [&](uint32_t a) { return (byte(a)<<24) | (byte(a+1)<<16) | (byte(a+2)<<8) | byte(a+3); };
        auto real = [&](uint32_t a) { return std::bit_cast<float>(word(a)); };
        const uint32_t activeCourse = word(0x800d8170);
        require(activeCourse < 9 && word(0x800dab28) == 1, "actual archive is a native course in 1P");
        // The complete original table is resident regardless of active course.
        // Exercise each original record in place, without copying synthetic
        // direction/color data into the captured RAM.
        for (uint32_t course = 0; course < NativeLightPresets.size(); course++) {
            const auto &expectedPreset = NativeLightPresets[course];
            const auto light = RT64::wr64RTShadowReadLight(ram.data(), ram.size(), course, 1);
            const uint32_t preset = 0x800d9964 + course * 0x110;
            require(light.valid, "each actual archived course preset produces a valid light");
            const float length = std::sqrt(expectedPreset.direction[0]*expectedPreset.direction[0] +
                expectedPreset.direction[1]*expectedPreset.direction[1] + expectedPreset.direction[2]*expectedPreset.direction[2]);
            const double dolphinAngle = 56.0 * (2.0 * std::acos(-1.0) / 4096.0);
            const std::array<float, 3> expectedDirection = course == 0
                ? std::array<float, 3>{float(std::cos(dolphinAngle) / std::sqrt(2.0)), std::sqrt(0.5f), float(std::sin(dolphinAngle) / std::sqrt(2.0))}
                : course == 2
                ? std::array<float, 3>{ 0.5f, std::sqrt(0.5f), -0.5f }
                : std::array<float, 3>{ expectedPreset.direction[0]/length,
                    expectedPreset.direction[1]/length, expectedPreset.direction[2]/length };
            for (uint32_t i = 0; i < 3; i++) {
                require(real(preset+0xac+i*4) == expectedPreset.direction[i],
                    "archived native authored direction exactly matches expected US course record");
                require(word(preset+i*4) == expectedPreset.diffuse[i] &&
                    word(preset+12+i*4) == expectedPreset.ambient[i], "archived world-light colors match expected course record");
                require(light.diffuse[i] == float(expectedPreset.diffuse[i])/255 &&
                    light.ambient[i] == float(expectedPreset.ambient[i])/255,
                    "helper decodes each course's actual archived light colors");
                require(std::fabs(light.toLight[i]-expectedDirection[i]) < 1e-6f,
                    "fixed light agrees with native Dolphin/Sunset sun bearing or unchanged course preset");
            }
        }
        // Source table and native sun-angle constant are resident in every
        // capture. Compare independently decoded values, not fixture injection.
        require(real(0x800eab88) == 315.0f, "actual Sunset geographic sun angle is 315 degrees");
        const uint32_t sunIndex = uint32_t(real(0x800eab88) / 360.0f * 4096.0f) & 0xfff;
        require(sunIndex == 0xe00, "actual sun angle selects the fixed native Z entry");
        require(real(0x80154350+0x800) == 0.7071067690849304f &&
            real(0x80154350+0x3800) == -0.7071067690849304f,
            "actual native fixed-light entries match the 315-degree sun sine/cosine");
        if (activeCourse == 2) {
            const auto light = RT64::wr64RTShadowReadLight(ram.data(), ram.size(), 2, 1);
            const uint32_t live = 0x801cb058;
            const float liveLength = std::sqrt(real(live+0xac)*real(live+0xac) +
                real(live+0xb0)*real(live+0xb0) + real(live+0xb4)*real(live+0xb4));
            require(std::isfinite(liveLength) && liveLength > 1, "actual Sunset live light is finite and nonzero");
            for (uint32_t i = 0; i < 3; i++) {
                require(std::fabs(light.toLight[i]-real(live+0xac+i*4)/liveLength) < 1e-6f &&
                    std::fabs(light.toLight[i]-real(live+0xfc+i*4)/liveLength) < 1e-6f,
                    "reconstructed fixed direction matches actual Sunset world and rider light outputs");
            }
            std::array<uint32_t, 16> segments{};
            for (uint32_t i = 0; i < 16; i++) { segments[i] = word(0x801ce6b0+i*4); }
            const auto celestial = RT64::wr64RTCelestialReadSnapshot(ram.data(), ram.size(), segments, 2, 1);
            require(celestial.count == 2, "actual loaded Sunset produces native glow and disk");
            const float horizontal = std::hypot(light.toLight[0], light.toLight[2]);
            for (uint32_t i = 0; i < celestial.count; i++) {
                require(std::fabs(light.toLight[0]/horizontal-celestial.bodies[i].cosAzimuth) < 1e-6f &&
                    std::fabs(light.toLight[2]/horizontal-celestial.bodies[i].sinAzimuth) < 1e-6f,
                    "shadow light geographic direction matches actual native rendered sun/glow anchors");
            }
            std::cout << "SUNSET native_live_and_sun_anchors=matched direction=(" << light.toLight[0]
                << ',' << light.toLight[1] << ',' << light.toLight[2] << ")\n";
        }
        if (activeCourse != 1) {
            std::cout << "ARCHIVE " << argv[fileIndex] << " active_course=" << activeCourse << " all_nine_presets=valid\n";
            continue;
        }

        const uint32_t cameraIndex = word(0x80223930);
        require(cameraIndex < 4, "native camera index bounded");
        const uint32_t camera = 0x80227c80 + cameraIndex * 268;
        const float cameraX = real(camera+0x64), cameraZ = real(camera+0x6c);
        const uint32_t live = 0x801cb058;
        const uint32_t angle = word(live+0xa8);
        require(angle == 135, "actual live authored camera-relative offset135deg");
        const bool reverse = ((byte(0x800dab68)<<8) | byte(0x800dab69)) != 0;
        const uint32_t sineIndex = ((reverse ? 360-angle : angle) * 4096 / 360) & 0xfff;
        const double s = real(0x80154350+sineIndex*4), c = real(0x80154350+((sineIndex+1024)&0xfff)*4);
        const double x = cameraX*c-cameraZ*s, z = cameraX*s+cameraZ*c;
        const double length = std::hypot(x,z);
        require(std::isfinite(length) && length > 0.01, "native camera horizontal direction valid");
        const std::array<float,3> expected{float(64*x/length),64,float(64*z/length)};
        std::array<float,3> current{};
        for (uint32_t i = 0; i < 3; i++) {
            current[i] = real(live+0xac+i*4);
            require(std::fabs(current[i]-expected[i]) < 0.0001f, "actual world light matches native camera-rotation formula");
            require(std::fabs(real(live+0xfc+i*4)-expected[i]) < 0.0001f, "actual rider light follows same camera rotation");
        }
        if (sunnyCaptures > 0) { changedDirection |= std::fabs(current[0]-previous[0]) > 1 || std::fabs(current[2]-previous[2]) > 1; }
        sunnyCaptures++;
        previous = current;
        std::cout << "ARCHIVE " << argv[fileIndex] << " live=(" << current[0] << ',' << current[1] << ',' << current[2]
            << ") all_nine_presets=valid\n";
    }
    if (sunnyCaptures > 1) { require(changedDirection, "multiple actual Sunny views prove live light is not world-fixed"); }
    std::cout << "PASS " << checks << " actual archived native-light checks across " << argc-1
        << " captures, nine original presets per capture, " << sunnyCaptures << " Sunny camera-light regressions\n";
}
