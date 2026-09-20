#include "common/rt64_wr64_dolphin_sun_sprite.h"
#include "wr64_render_provenance.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace RT64;
static size_t checks = 0;
static uint64_t outputDigest = 14695981039346656037ull;
static void digest(const void* data, size_t size) {
    const auto* bytes = static_cast<const uint8_t*>(data);
    for (size_t i=0; i<size; ++i) { outputDigest ^= bytes[i]; outputDigest *= 1099511628211ull; }
}
static void require(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
static void word(std::vector<uint8_t>& ram, uint32_t address, uint32_t value) {
    std::memcpy(ram.data() + (address & 0x1fffffffu), &value, 4);
}
static void real(std::vector<uint8_t>& ram, uint32_t address, float value) {
    std::memcpy(ram.data() + (address & 0x1fffffffu), &value, 4);
}
static void scope(std::vector<uint8_t>& ram, uint32_t course, uint32_t players, uint32_t phase, uint32_t mode) {
    word(ram, 0x800d8170, course); word(ram, 0x800dab28, players);
    word(ram, 0x801ce638, phase); word(ram, 0x800dab24, mode);
}
static constexpr uint32_t packet = 0x1000;
static const std::array<uint32_t, 6> original = {
    0xe4380060, 0x00320000, 0xb3000000, 0xf8300800, 0xb2000000, 0x05550555};
static void writePacket(std::vector<uint8_t>& ram) {
    std::memcpy(ram.data() + packet, original.data(), 24);
}
struct DrawData { std::vector<float> triPosFloats, triTcFloats, triColorFloats; };

int main(int argc, char** argv) {
    const char* gate = argc > 1 ? argv[1] : "";
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    _putenv_s("WR64_DOLPHIN_SUN_NATIVE_EXIT", gate);
    _putenv_s("WR64_DOLPHIN_SUN_NATIVE_TRACE", "");
#else
    if (*gate) setenv("WR64_DOLPHIN_SUN_NATIVE_EXIT", gate, 1);
    else unsetenv("WR64_DOLPHIN_SUN_NATIVE_EXIT");
    unsetenv("WR64_DOLPHIN_SUN_NATIVE_TRACE");
#endif
    try {
        require(wr64DolphinSunNativeExitEnabled() == (!*gate || std::strcmp(gate,"1")==0), "normal default/explicit gate behavior");
        std::vector<uint8_t> ram(0x800000);
        real(ram, 0x801c4178, 0.98f); real(ram, 0x801c4184, 0.8f);
        word(ram, 0x800d9944, 12);
        scope(ram, 0, 1, 1, 0);
        if (!wr64DolphinSunNativeExitEnabled()) {
            require(!wr64_dolphin_sun_begin(ram.data(), 212.0f, 5.0f), "explicit opt-out must be inert");
            writePacket(ram); auto before = ram;
            wr64_dolphin_sun_packet(ram.data(), 1, packet);
            require(ram == before, "gate-off producer changed RAM");
            require(wr64DolphinSunSeal(1).commands.empty(), "gate-off metadata exists");
        } else {
            for (uint32_t course = 0; course < 10; ++course)
                for (uint32_t players = 0; players < 4; ++players)
                    for (uint32_t phase = 0; phase < 4; ++phase)
                        for (uint32_t mode : {0u, 1u, 2u, 5u, 255u}) {
                            scope(ram, course, players, phase, mode);
                            const auto token = wr64_dolphin_sun_begin(ram.data(), 212.0f, 5.0f);
                            require(bool(token) == (course == 0 && players == 1 && phase == 1), "producer scope");
                        }
            scope(ram, 0, 1, 1, 0);
            real(ram, 0x801c4178, -64.0f);
            require(!wr64_dolphin_sun_begin(ram.data(), 212.0f, -5.0f), "tiny-W rejection admitted");
            real(ram, 0x801c4178, 0.98f); real(ram, 0x801c4184, -1.0f);
            require(!wr64_dolphin_sun_begin(ram.data(), 212.0f, -5.0f), "invalid facing admitted");
            real(ram, 0x801c4184, 0.8f);
            Wr64DolphinSunSprite example;
            uint64_t sequence = 1;
            for (int step = 192; step >= -512; --step) {
                const float y = float(step) / 4.0f;
                writePacket(ram);
                const uint32_t token = wr64_dolphin_sun_begin(ram.data(), 212.25f, y);
                require(token != 0, "valid signed producer rejected");
                const auto before = ram;
                wr64_dolphin_sun_packet(ram.data(), token, packet);
                if (std::trunc(y) >= 0) require(ram == before, "original positive packet changed");
                else {
                    require(std::equal(ram.begin(), ram.begin() + packet, before.begin()) &&
                        std::equal(ram.begin() + packet + 8, ram.end(), before.begin() + packet + 8),
                        "carrier changed unrelated RAM");
                    require((wr64DolphinSunReadWord(ram.data(), packet) & 0xfff) == 24, "carrier bottom");
                    require((wr64DolphinSunReadWord(ram.data(), packet + 4) & 0xfff) == 24, "carrier top");
                }
                wr64DolphinSunClaimed = wr64DolphinSunSeal(++sequence);
                auto sprite = wr64DolphinSunLookup(sequence, packet, ram.data());
                require(wr64DolphinSunSpriteValid(sprite), "authenticated producer lost");
                require(sprite.centerY == y && sprite.centerX == 212.25f, "native fractional coordinate lost");
                auto rect = wr64DolphinSunFullRect(sprite);
                require(rect[1] == y - 12 && rect[3] == y + 12, "signed full geometry");
                auto uv = wr64DolphinSunFullUV(sprite);
                require(uv == std::array<float,4>{0,0,31.96875f,31.96875f}, "full texture phase");
                digest(ram.data()+packet,24);
                digest(rect.data(),sizeof(float)*rect.size());
                digest(uv.data(),sizeof(float)*uv.size());
                require(!wr64DolphinSunLookup(sequence + 1, packet, ram.data()).admitted, "cross-task alias");
                ram[packet + 12] ^= 1;
                require(!wr64DolphinSunLookup(sequence, packet, ram.data()).admitted, "overwritten packet admitted");
                ram[packet + 12] ^= 1;
                example = sprite;
            }
            example.centerY = 5;
            writePacket(ram);
            auto token = wr64_dolphin_sun_begin(ram.data(), 212.25f, 5.0f);
            wr64_dolphin_sun_packet(ram.data(), token, packet);
            wr64_dolphin_sun_packet(ram.data(), token, packet);
            auto once = wr64DolphinSunSeal(++sequence);
            require(once.commands.size() == 1, "reused native token duplicated ownership");
            require(wr64DolphinSunRecord(ram.data(), packet, example), "first direct ownership");
            require(wr64DolphinSunRecord(ram.data(), packet, example), "second direct ownership");
            wr64DolphinSunClaimed = wr64DolphinSunSeal(++sequence);
            require(!wr64DolphinSunLookup(sequence, packet, ram.data()).admitted, "duplicate address was accepted");
            for (size_t i = 0; i <= Wr64DolphinSunMaxCommands; ++i)
                wr64DolphinSunRecord(ram.data(), packet, example);
            require(wr64DolphinSunSeal(++sequence).commands.empty(), "overflow did not fail closed");
            require(wr64DolphinSunRecord(ram.data(), packet, example), "overflow did not reset on seal");
            wr64DolphinSunClaimed = wr64DolphinSunSeal(++sequence);
            require(wr64DolphinSunLookup(sequence, packet, ram.data()).admitted, "post-overflow task rejected");
            auto other = example;
            ++other.generation;
            require(!wr64DolphinSunSameSprite(example, other), "generation crossed");
            other = example; other.context ^= 1u << 24;
            require(!wr64DolphinSunSameSprite(example, other), "scene mode crossed");
            other = example; other.recordId = 0x801c41a0;
            require(!wr64DolphinSunSpriteValid(other), "flare record admitted");
            scope(ram, 0, 1, 0, 2);
            require(!wr64_dolphin_sun_begin(ram.data(), 212.25f, 5.0f), "opening admitted");
            scope(ram, 0, 1, 1, 0);
            token = wr64_dolphin_sun_begin(ram.data(), 212.25f, 5.0f);
            wr64_dolphin_sun_packet(ram.data(), token, packet);
            auto resumed = wr64DolphinSunSeal(++sequence);
            require(resumed.commands.size() == 1 && resumed.commands[0].sprite.generation != example.generation,
                "producer generation survived scope loss");
            auto stationary = wr64DolphinSunFullRect(example);
            require(stationary[3] == 17, "native partial must not receive artificial exit motion");
            Wr64DolphinSunRectPair pair{1, {200, -23, 224, 1}, {200, -25, 224, -1}};
            for (int frame = 0; frame <= 60; ++frame) {
                float t = float(frame) / 60;
                auto rect = wr64DolphinSunInterpolate(pair, t);
                require(std::abs(rect[3] - (1 - 2*t)) < 0.00001f, "final physical exit interpolation");
                require(rect[3] - rect[1] == 24, "interpolation resized sprite");
            }
            DrawData data;
            data.triPosFloats.assign(48, 0.5f); data.triTcFloats.assign(24, 99.0f);
            data.triColorFloats.assign(48, 0.75f);
            auto prior = data;
            const auto start = wr64DolphinSunAppendVertices(data, 6, example);
            require(start == 12 && data.triPosFloats.size() == 72, "alternate vertex placement");
            require(std::equal(prior.triPosFloats.begin(), prior.triPosFloats.end(), data.triPosFloats.begin()), "native positions changed");
            require(std::equal(prior.triTcFloats.begin(), prior.triTcFloats.end(), data.triTcFloats.begin()), "native UVs changed");
            require(std::equal(prior.triColorFloats.begin(), prior.triColorFloats.end(), data.triColorFloats.begin()), "native colors changed");
            require(data.triTcFloats[24] == 0 && data.triTcFloats[26] == 31.96875f, "canonical appended UVs");
        }
        std::printf("PASS %zu checks; output digest %016llx\n", checks, static_cast<unsigned long long>(outputDigest));
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "FAIL: %s\n", error.what());
        return 1;
    }
}
