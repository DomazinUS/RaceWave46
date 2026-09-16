#include "wr64_seabed_distance.hpp"
#include "../lib/rt64/src/common/rt64_wr64_rt_two_player_assets.h"

#include <array>
#include <atomic>
#include <bit>
#include <cmath>
#include <limits>

namespace {
std::atomic<uint32_t> selectedMode{0};
uint32_t word(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
float real(uint8_t* rdram, uint32_t address) { return std::bit_cast<float>(word(rdram, address)); }
bool resident(uint32_t address, uint32_t size) {
    return address >= 0x80000000U && address <= 0x80800000U - size;
}
struct Vertex { int16_t x, y, z, u, v; };
int64_t cross(const Vertex& a, const Vertex& b, const Vertex& c) {
    return int64_t(int(b.x) - a.x) * (int(c.z) - a.z) -
        int64_t(int(b.z) - a.z) * (int(c.x) - a.x);
}
bool validFan(const std::array<Vertex, 7>& vertices) {
    int sign = 0;
    for (unsigned i = 1; i <= 6; ++i) {
        const auto& a = vertices[i];
        const auto& b = vertices[i % 6 + 1];
        const auto& c = vertices[(i + 1) % 6 + 1];
        const int64_t turn = cross(a, b, c), center = cross(a, b, vertices[0]);
        if (a.y != vertices[0].y || !turn || !center) return false;
        if (!sign) sign = turn > 0 ? 1 : -1;
        if ((turn > 0 ? 1 : -1) != sign || (center > 0 ? 1 : -1) != sign) return false;
    }
    return true;
}
bool shortValue(float value, int16_t& result) {
    if (!std::isfinite(value)) return false;
    // SysUtils_Round (80047BE0) rounds halves away from zero, in float.
    const float adjusted = value < 0.0f ? value - 0.5f : value + 0.5f;
    if (adjusted <= -32769.0f || adjusted >= 32768.0f) return false;
    const int32_t rounded = int32_t(adjusted);
    if (rounded < -32768 || rounded > 32767) return false;
    result = int16_t(rounded);
    return true;
}
bool textureCoordinate(int16_t coordinate, float camera, float ratio,
    float divisor, int32_t offset, int16_t& result)
{
    // Exact native operation order at 8004CBDC..CC08 / 8004CC18..CC44.
    // UVs must grow with geometry to retain the original texel density.
    const float delta = float(coordinate) - camera;
    const float projected = delta * ratio;
    const float value = (projected + camera) / divisor;
    if (!std::isfinite(value)) return false;
    const float adjusted = value < 0.0f ? value - 0.5f : value + 0.5f;
    if (!std::isfinite(adjusted) || double(adjusted) < double(INT32_MIN) ||
        double(adjusted) > double(INT32_MAX)) return false;
    const int64_t complete = int64_t(int32_t(adjusted)) + offset;
    // Preserve the original UV branch. A periodic rebase is equivalent at
    // native endpoints but can slide the texture during interpolation.
    if (complete < -32768 || complete > 32767) return false;
    result = int16_t(complete);
    return true;
}
}

namespace wr64::seabed_distance {
void set_mode(uint32_t value) { selectedMode.store(value <= 5 ? value : 0, std::memory_order_relaxed); }
uint32_t mode() { return selectedMode.load(std::memory_order_relaxed); }
}

extern "C" void wr64_seabed_distance_finish(uint8_t* rdram, recomp_context* ctx) {
    const uint32_t selected = selectedMode.load(std::memory_order_relaxed);
    // Original does not inspect registers or RDRAM, even for invalid pointers.
    if (!selected || !rdram || !ctx) return;
    const uint32_t course = word(rdram, 0x800D8170), players = word(rdram, 0x800DAB28);
    const uint32_t phase = word(rdram, 0x801CE638), view = word(rdram, 0x800DAB2C);
    const uint32_t raceMode = word(rdram, 0x800DAB24);
    const bool race = phase == 1 && raceMode >= 40 && raceMode <= 45;
    const bool world = players == 1 ? course <= 8 &&
        (phase == 1 || (phase == 8 && (raceMode == 30 || raceMode == 31)) || (phase == 1 && raceMode == 7) ||
            (course == 0 && phase == 0 && raceMode >= 2 && raceMode <= 4)) :
        players == 2 && course <= 8 && race &&
            (course != 0 || RT64::wr64RTTwoPlayerAssetsReady(rdram, course));
    if (!world || view >= players || view > 1) return;
    const uint32_t cameraIndex = word(rdram, 0x80223930 + view * 4);
    const uint32_t camera = uint32_t(ctx->r19), stack = uint32_t(ctx->r29);
    if (cameraIndex > 1 || camera != 0x80227C80U + cameraIndex * 0x10CU ||
        (word(rdram, camera) != 3 && word(rdram, camera) != 4 && word(rdram, camera) != 5) || word(rdram, camera + 0xE8) != cameraIndex ||
        !resident(stack, 0x50) || (stack & 7U)) return;
    const uint32_t buffer = word(rdram, 0x8011F8E0);
    const uint32_t output = word(rdram, stack + 0x4C);
    // The existing native two-player sky/bottom adapter gives each view its
    // reserved seven-vertex slot. Never expand a shared camera-zero fallback.
    if (buffer > 1 || output != 0x801C43F8U + buffer * 0x3630U + view * 0x70U) return;

    const float ratio = ctx->f20.fl;
    const float cameraX = real(rdram, camera + 0x4C), cameraZ = real(rdram, camera + 0x54);
    const float divisorX = real(rdram, 0x801924CC), divisorZ = real(rdram, 0x801924D0);
    if (!std::isfinite(ratio) || !std::isfinite(cameraX) || !std::isfinite(cameraZ) ||
        !std::isfinite(divisorX) || !std::isfinite(divisorZ) || divisorX <= 0 || divisorZ <= 0) return;
    const int32_t offsetX = int32_t(word(rdram, 0x800D4774)), offsetZ = int32_t(word(rdram, 0x800D4778));
    std::array<Vertex, 7> staged{};
    for (unsigned i = 0; i < staged.size(); ++i) {
        const uint32_t address = output + i * 16;
        auto& v = staged[i];
        v = {MEM_H(0, S32(address)), MEM_H(2, S32(address)), MEM_H(4, S32(address)),
            MEM_H(8, S32(address)), MEM_H(10, S32(address))};
        int16_t expectedU = 0, expectedV = 0;
        if (!textureCoordinate(v.x, cameraX, ratio, divisorX, offsetX, expectedV) ||
            !textureCoordinate(v.z, cameraZ, ratio, divisorZ, offsetZ, expectedU) ||
            expectedU != v.u || expectedV != v.v) return;
    }
    if (!validFan(staged)) return;

    const float multiplier = selected == 1 ? 1.5f : float(selected);
    // The authored center remains fixed, and only the six outer draw vertices
    // move. These are private SOT_DYNAMIC slots, not the source wave vertices.
    for (unsigned i = 1; i < staged.size(); ++i) {
        auto& v = staged[i];
        if (!shortValue(float(staged[0].x) + float(int(v.x) - staged[0].x) * multiplier, v.x) ||
            !shortValue(float(staged[0].z) + float(int(v.z) - staged[0].z) * multiplier, v.z) ||
            !textureCoordinate(v.z, cameraZ, ratio, divisorZ, offsetZ, v.u) ||
            !textureCoordinate(v.x, cameraX, ratio, divisorX, offsetX, v.v)) return;
    }
    if (!validFan(staged)) return;
    for (unsigned i = 1; i < staged.size(); ++i) {
        const uint32_t address = output + i * 16;
        const auto& v = staged[i];
        MEM_H(0, S32(address)) = v.x;
        MEM_H(4, S32(address)) = v.z;
        MEM_H(8, S32(address)) = v.u;
        MEM_H(10, S32(address)) = v.v;
    }
}
