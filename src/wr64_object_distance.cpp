#include "wr64_object_distance.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <bit>
#include <cmath>

namespace {
constexpr uint32_t objectBase = 0x801BC940, objectStride = 0xC4, maxObjects = 64;
constexpr uint32_t visibilityBase = 0x801C0AC0;
constexpr uint32_t firstDisplayPool = 0x8011F8E8, displayPoolStride = 0x18FE8;
constexpr uint32_t displayBytes = 0x6000, reservedDisplayTail = 0x3000;
constexpr uint32_t firstSplitViewReserve = 0x4800;
// Native 80071650..8007180C emits at most nine commands per solid object.
// Static ramps and ice use resident per-object matrices, so neither adds a
// shared matrix allocation. The remaining E674 tail is <=11928 bytes even
// with both Twilight light passes and maximum 64-record rosters.
constexpr uint32_t objectDisplayBytes = 72;
std::atomic<uint32_t> selectedMode{0};

struct Frame {
    uint8_t* rdram = nullptr;
    recomp_context* context = nullptr;
    uint32_t stack = 0, count = 0;
    std::array<uint32_t, maxObjects> indices{};
    std::array<int16_t, maxObjects> visibility{};
};
thread_local Frame frame;

uint32_t word(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
float real(uint8_t* rdram, uint32_t address) { return std::bit_cast<float>(word(rdram, address)); }
bool resident(uint32_t address, uint32_t bytes) {
    return address >= 0x80000000 && address <= 0x80800000 - bytes;
}
}

namespace wr64::object_distance {
void set_mode(uint32_t value) { selectedMode.store(value <= 3 ? value : 0, std::memory_order_relaxed); }
uint32_t mode() { return selectedMode.load(std::memory_order_relaxed); }
}

extern "C" void wr64_object_distance_begin(uint8_t* rdram, recomp_context* ctx) {
    const uint32_t selected = selectedMode.load(std::memory_order_relaxed);
    // Original never accesses native memory or modifies registers.
    if (!selected || !rdram || !ctx || frame.count) return;
    const uint32_t course = word(rdram, 0x800D8170);
    const uint32_t players = word(rdram, 0x800DAB28), view = word(rdram, 0x800DAB2C);
    if (course > 8 || players < 1 || players > 2 || view >= players) return;
    // s6 has been reused by this point in DrawBuoy; recover the same view's
    // camera through the native selector instead of interpreting that register.
    // This hook only runs in the native world-object pass. The same fixed
    // matrix bank is used in the opening, introductions and either race view.
    const uint32_t cameraIndex = word(rdram, 0x80223930 + view * 4);
    if (cameraIndex > 1) return;
    const uint32_t camera = 0x80227C80 + cameraIndex * 0x10C;
    const uint32_t stack = uint32_t(ctx->r29);
    const uint32_t count = word(rdram, 0x801BFA40);
    const uint32_t descriptor = word(rdram, 0x801C0C80);
    const uint32_t pool = word(rdram, 0x801518B8);
    if (!resident(stack, 0x5F0) || (stack & 7) || !count || count > maxObjects ||
        descriptor != 0x801CB058 + view * 0x110 ||
        (pool != firstDisplayPool && pool != firstDisplayPool + displayPoolStride)) return;
    // Twilight's two late light passes traverse the checkpoint roster. They
    // see restored native visibility, but their bound still needs this count.
    if (course == 6 && word(rdram, 0x801BB120) > maxObjects) return;
    const uint32_t near = word(rdram, descriptor + 0xA0), far = word(rdram, descriptor + 0xA4);
    const uint32_t cursor = word(rdram, stack + 0x550);
    if (near >= far || far > 1000000 || (cursor & 7) || cursor < pool || cursor > pool + displayBytes) return;
    const float cameraX = real(rdram, camera + 0x4C), cameraZ = real(rdram, camera + 0x54);
    const float forwardX = real(rdram, stack + 0x568), forwardZ = real(rdram, stack + 0x564);
    if (!std::isfinite(cameraX) || !std::isfinite(cameraZ) ||
        !std::isfinite(forwardX) || !std::isfinite(forwardZ)) return;
    constexpr float distanceScales[] = {1.0f, 1.5f, 2.0f, 3.0f};
    const float cutoff = float(far) * distanceScales[selected];
    uint32_t bodyCount = 0;
    std::array<float, maxObjects> distances{};
    Frame pending;
    for (uint32_t i = 0; i < count; ++i) {
        const uint32_t object = objectBase + i * objectStride;
        const int16_t visibility = MEM_H(0, S32(visibilityBase + i * 2));
        const uint32_t renderClass = word(rdram, object + 0x54);
        if (visibility >= 0 && renderClass == 1) ++bodyCount;
        const uint32_t kind = word(rdram, object + 0x4C);
        // SetCrsObj initializes resident matrices for ramps (1) and ice (10).
        // Gates and floating obstacles use count-stack matrices; sprite/ring
        // families have separate passes. Leave their admission native.
        if ((kind != 1 && kind != 10) || renderClass != 1 ||
            word(rdram, object + 0x58) != 0 ||
            (!word(rdram, object + 0xB4) && !word(rdram, object + 0xB8))) continue;
        if (visibility >= 0) continue;
        const float dx = real(rdram, object) - cameraX, dz = real(rdram, object + 8) - cameraZ;
        const float distance = std::sqrt(dx * dx + dz * dz);
        if (!std::isfinite(distance)) return;
        // A negative result inside the original range is not ours to override.
        if (distance < float(far) || distance >= cutoff) continue;
        // Reproduce the native 8006EDE4..8006EE18 gate. Only ramps bypass it;
        // ice must remain in the forward half-plane of this particular view.
        if (kind != 1 && !((dx / distance) * forwardX + (dz / distance) * forwardZ > 0.0f)) continue;
        distances[i] = distance;
        pending.indices[pending.count] = i;
        pending.visibility[pending.count++] = visibility;
    }
    if (!pending.count) return;
    // Both split-screen views append to one pool. Reserve more in the first
    // view for the second view and caller effects; this is a conservative
    // headroom policy, not a bound on every possible full-frame native effect.
    const uint32_t reserve = players == 2 && view == 0 ? firstSplitViewReserve : reservedDisplayTail;
    const uint32_t required = reserve + objectDisplayBytes * bodyCount;
    const uint32_t available = pool + displayBytes - cursor;
    if (available < required) return;
    // Preserve every native body, then admit the nearest extras that fit.
    // Sorting only indices leaves all object records and matrix identities intact.
    std::sort(pending.indices.begin(), pending.indices.begin() + pending.count,
        [&](uint32_t a, uint32_t b) { return distances[a] != distances[b] ? distances[a] < distances[b] : a < b; });
    pending.count = std::min(pending.count, (available - required) / objectDisplayBytes);
    if (!pending.count) return;
    for (uint32_t i = 0; i < pending.count; ++i)
        pending.visibility[i] = MEM_H(0, S32(visibilityBase + pending.indices[i] * 2));
    pending.rdram = rdram;
    pending.context = ctx;
    pending.stack = stack;
    frame = pending;
    for (uint32_t i = 0; i < frame.count; ++i)
        MEM_H(0, S32(visibilityBase + frame.indices[i] * 2)) = 0;
}

extern "C" void wr64_object_distance_end(uint8_t* rdram, recomp_context* ctx) {
    if (!frame.count || !ctx || frame.rdram != rdram || frame.context != ctx ||
        frame.stack != uint32_t(ctx->r29)) return;
    // Restore before course roots, tree sprites, effects and other late
    // consumers. Changing the selected mode midway cannot suppress cleanup.
    for (uint32_t i = 0; i < frame.count; ++i)
        MEM_H(0, S32(visibilityBase + frame.indices[i] * 2)) = frame.visibility[i];
    frame = {};
}
