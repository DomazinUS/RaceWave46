#include "wr64_draw_distance.hpp"
#include "wr64_object_distance.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <bit>
#include <cmath>

namespace {
constexpr uint32_t objectBase = 0x801AEE20, objectStride = 0x104;
constexpr uint32_t visibilityBase = 0x801C0840, maxObjects = 64, matrixSlots = 12;
constexpr uint32_t firstDisplayPool = 0x8011F8E8, displayPoolStride = 0x18FE8;
constexpr uint32_t displayBytes = 0x6000, reservedDisplayTail = 0x3000;
// A normal buoy has two four-command sprite layers and a seven-command
// label/pontoon pass (120 bytes). Reserve 192 bytes for each added buoy.
constexpr uint32_t extraDisplayBytes = 192;
constexpr uint32_t firstMatrixPool = 0x80198368, matrixPoolStride = 0xB2F0;
std::atomic<uint32_t> selectedMode{0};

struct Frame {
    uint8_t* rdram = nullptr;
    recomp_context* context = nullptr;
    uint32_t stack = 0, count = 0, pool = 0, extra = 0, tailReserve = reservedDisplayTail;
    uint64_t nearRegister = 0, farRegister = 0;
    bool scaled = false, pending = false, nativeVisibilityReady = false;
    uint32_t buoyMode = 0;
    bool extendDolphinEntrance = false;
    std::array<float, maxObjects> distances{};
    std::array<bool, maxObjects> ordinary{};
    std::array<bool, maxObjects> dolphinEntrance{};
    std::array<int16_t, maxObjects> nativeVisibility{};
};
thread_local Frame frame;

constexpr uint32_t areaBase = 0x801BB138, areaStride = 0x18, areaCount = 0x801BC938;
constexpr uint32_t areaVisibilityBase = 0x801C08C0, maxAreaObjects = 256, areaMatrixSlots = 32;
// From EF10 to the checkpoint capacity hook: 58 fixed commands (464 bytes),
// and two four-command layers per visible area object (64 bytes). Round the
// fixed allowance up, and reserve the checkpoint pass's existing budget too.
constexpr uint32_t areaSetupBytes = 512, areaDisplayBytes = 64;
struct AreaFrame {
    uint8_t* rdram = nullptr;
    recomp_context* context = nullptr;
    uint32_t stack = 0, count = 0, pool = 0, visible = 0, tailReserve = reservedDisplayTail;
    uint64_t nearRegister = 0, farRegister = 0;
    bool scaled = false, pending = false, nativeVisibilityReady = false;
    std::array<float, maxAreaObjects> distances{};
    std::array<bool, maxAreaObjects> ordinary{};
    std::array<int16_t, maxAreaObjects> nativeVisibility{};
};
thread_local AreaFrame area;

uint32_t word(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
float real(uint8_t* rdram, uint32_t address) { return std::bit_cast<float>(word(rdram, address)); }
bool resident(uint32_t address, uint32_t bytes) {
    return address >= 0x80000000 && address <= 0x80800000 - bytes;
}
bool worldCamera(uint8_t* rdram, recomp_context* ctx) {
    const uint32_t players = word(rdram, 0x800DAB28), view = word(rdram, 0x800DAB2C);
    if (word(rdram, 0x800D8170) > 8 || players < 1 || players > 2 || view >= players) return false;
    // DrawBuoy selects these same cameras at 8006E6CC and 8006E750. Camera
    // type/phase do not change either roster or its per-view matrix allocation,
    // so introductions, the Dolphin opening and race cameras share this path.
    const uint32_t index = word(rdram, 0x80223930 + view * 4);
    return index <= 1 && uint32_t(ctx->r22) == 0x80227C80 + index * 0x10C;
}
uint32_t tailReserve(uint8_t* rdram) {
    // Both views append into the same display pool. P1 leaves additional room
    // for the second view; this is conservative headroom, not a full-frame bound.
    return word(rdram, 0x800DAB28) == 2 && word(rdram, 0x800DAB2C) == 0 ? 0x4800 : reservedDisplayTail;
}
bool sameCall(uint8_t* rdram, recomp_context* ctx) {
    return ctx && frame.rdram == rdram && frame.context == ctx && frame.stack == uint32_t(ctx->r29);
}
bool sameAreaCall(uint8_t* rdram, recomp_context* ctx) {
    return ctx && area.rdram == rdram && area.context == ctx && area.stack == uint32_t(ctx->r29);
}
void restoreAreaVisibility(uint8_t* rdram) {
    for (uint32_t i = 0; i < area.count; ++i)
        MEM_H(0, S32(areaVisibilityBase + i * 2)) = area.nativeVisibility[i];
}
void restoreVisibility(uint8_t* rdram) {
    for (uint32_t i = 0; i < frame.count; ++i)
        MEM_H(0, S32(visibilityBase + i * 2)) = frame.nativeVisibility[i];
}
int16_t nativeFade(float distance, uint32_t near, uint32_t far) {
    if (distance <= float(near)) return 0;
    // Keep the native float operation order and truncation at 8006EB4C..6C.
    const float numerator = (distance - float(near)) * 255.0f;
    return int16_t(std::min(int32_t(numerator / float(far - near)), 255));
}
}

namespace wr64::draw_distance {
void set_mode(uint32_t value) { selectedMode.store(value <= 2 ? value : 0, std::memory_order_relaxed); }
uint32_t mode() { return selectedMode.load(std::memory_order_relaxed); }
}

extern "C" void wr64_draw_distance_begin(uint8_t* rdram, recomp_context* ctx) {
    frame = {};
    const uint32_t mode = selectedMode.load(std::memory_order_relaxed);
    const bool entranceRequested = wr64::object_distance::mode() == 3;
    // Original is an exact no-op, including invalid pointers and registers.
    if ((!mode && !entranceRequested) || !rdram || !ctx) return;
    // The lettered Dolphin entrance is start_dol_model in the checkpoint pass,
    // not a static-object roster entry. Only the new Object 3x option extends
    // it; retain every pre-existing choice and other course/stunt gate.
    const bool extendEntrance = entranceRequested && word(rdram, 0x800D8170) == 0 &&
        word(rdram, 0x801CE620) != 11;
    if (!mode && !extendEntrance) return;
    if (!worldCamera(rdram, ctx)) return;
    const uint32_t camera = uint32_t(ctx->r22);
    const uint32_t stack = uint32_t(ctx->r29);
    const uint32_t descriptor = uint32_t(ctx->r2);
    const uint32_t count = word(rdram, 0x801BB120);
    const uint32_t pool = word(rdram, 0x801518B8);
    const uint32_t matrices = word(rdram, 0x801AE948);
    const uint32_t near = uint32_t(ctx->r17), far = uint32_t(ctx->r18);
    if (!resident(stack, 0x5F0) || (stack & 7) || descriptor != 0x801CB058 + word(rdram, 0x800DAB2C) * 0x110 ||
        word(rdram, 0x801C0C80) != descriptor || word(rdram, descriptor + 0xA0) != near ||
        word(rdram, descriptor + 0xA4) != far || near >= far || far > 1000000 ||
        count == 0 || count > maxObjects ||
        (pool != firstDisplayPool && pool != firstDisplayPool + displayPoolStride) ||
        (matrices != firstMatrixPool && matrices != firstMatrixPool + matrixPoolStride)) return;
    const uint32_t cursor = word(rdram, stack + 0x550);
    if ((cursor & 7) || cursor < pool || cursor > pool + displayBytes) return;
    const float cameraX = real(rdram, camera + 0x4C), cameraZ = real(rdram, camera + 0x54);
    if (!std::isfinite(cameraX) || !std::isfinite(cameraZ)) return;
    for (uint32_t i = 0; i < count; ++i) {
        const uint32_t object = objectBase + i * objectStride;
        const float dx = real(rdram, object) - cameraX, dz = real(rdram, object + 8) - cameraZ;
        const float distance = std::sqrt(dx * dx + dz * dz);
        if (!std::isfinite(distance)) return;
        frame.distances[i] = distance;
        // Other records in the same array include special course objects.
        // Only the three ordinary buoy materials get an extended range.
        frame.ordinary[i] = word(rdram, object + 0x9C) == 0 && word(rdram, object + 0x98) <= 2;
        const uint32_t type = word(rdram, object + 0x98);
        frame.dolphinEntrance[i] = extendEntrance && word(rdram, object + 0x9C) == 1 &&
            (type == 3 || type == 5);
    }
    frame.rdram = rdram;
    frame.context = ctx;
    frame.stack = stack;
    frame.count = count;
    frame.pool = pool;
    frame.tailReserve = tailReserve(rdram);
    frame.buoyMode = mode;
    frame.extendDolphinEntrance = extendEntrance;
    frame.nearRegister = ctx->r17;
    frame.farRegister = ctx->r18;
    frame.scaled = true;
    const uint32_t numerator = extendEntrance ? 6 : mode == 1 ? 3 : 4;
    ctx->r17 = S32(near * numerator / 2);
    ctx->r18 = S32(far * numerator / 2);
}

extern "C" void wr64_draw_distance_finish(uint8_t* rdram, recomp_context* ctx) {
    if (!frame.scaled || !sameCall(rdram, ctx)) return;
    // The following native object families reuse s1/s2. Restore them before
    // any gate or fallback, without writing the shared descriptor itself.
    ctx->r17 = frame.nearRegister;
    ctx->r18 = frame.farRegister;
    frame.scaled = false;
    const uint32_t near = uint32_t(frame.nearRegister), far = uint32_t(frame.farRegister);
    const uint32_t buoyNumerator = frame.buoyMode == 0 ? 2 : frame.buoyMode == 1 ? 3 : 4;
    std::array<uint32_t, maxObjects> extraIndices{};
    uint32_t originalCount = 0, extraCount = 0;
    for (uint32_t i = 0; i < frame.count; ++i) {
        const uint32_t object = objectBase + i * objectStride;
        int16_t visibility = MEM_H(0, S32(visibilityBase + i * 2));
        const float cutoff = word(rdram, object + 0x9C) == 1 ? float(far) * 2.0f : float(far);
        const bool nativeVisible = visibility >= 0 && frame.distances[i] < cutoff;
        frame.nativeVisibility[i] = nativeVisible ? nativeFade(frame.distances[i], near, far) : -1;
        if (nativeVisible) ++originalCount;
        if (frame.dolphinEntrance[i] && nativeVisible) {
            visibility = frame.nativeVisibility[i];
            MEM_H(0, S32(visibilityBase + i * 2)) = visibility;
        }
        if (frame.extendDolphinEntrance && frame.ordinary[i]) {
            // Native visibility used the larger portal range. Restore each
            // ordinary buoy's own range and fade before preparing matrices.
            const uint32_t buoyNear = near * buoyNumerator / 2;
            const uint32_t buoyFar = far * buoyNumerator / 2;
            if (visibility >= 0 && frame.distances[i] < float(buoyFar))
                visibility = nativeFade(frame.distances[i], buoyNear, buoyFar);
            else visibility = frame.nativeVisibility[i];
            MEM_H(0, S32(visibilityBase + i * 2)) = visibility;
        }
        if (!frame.ordinary[i] && !frame.dolphinEntrance[i]) {
            MEM_H(0, S32(visibilityBase + i * 2)) = frame.nativeVisibility[i];
        }
        else if (visibility >= 0 && !nativeVisible) {
            extraIndices[extraCount++] = i;
        }
    }
    frame.nativeVisibilityReady = true;
    // Native code only prepares twelve transforms, but its subsequent draws
    // walk the whole visibility table. Never let an extra buoy use a stale
    // matrix index, and never evict a buoy the original pass would have drawn.
    if (originalCount > matrixSlots || selectedMode.load(std::memory_order_relaxed) != frame.buoyMode ||
        (frame.extendDolphinEntrance && wr64::object_distance::mode() != 3)) {
        restoreVisibility(rdram);
        return;
    }
    std::sort(extraIndices.begin(), extraIndices.begin() + extraCount, [](uint32_t a, uint32_t b) {
        return frame.distances[a] != frame.distances[b] ? frame.distances[a] < frame.distances[b] : a < b;
    });
    frame.extra = std::min(extraCount, matrixSlots - originalCount);
    for (uint32_t i = frame.extra; i < extraCount; ++i)
        MEM_H(0, S32(visibilityBase + extraIndices[i] * 2)) = -1;
    frame.pending = true;
}

extern "C" void wr64_draw_distance_capacity(uint8_t* rdram, recomp_context* ctx) {
    if (!frame.pending || !sameCall(rdram, ctx)) return;
    frame.pending = false;
    const uint32_t cursor = word(rdram, frame.stack + 0x550);
    const uint32_t required = frame.tailReserve + frame.extra * extraDisplayBytes;
    // This hook is after the other object draws and before the first buoy
    // matrix. All later buoy layers therefore agree on any capacity fallback.
    if (word(rdram, 0x801518B8) != frame.pool || (cursor & 7) || cursor < frame.pool ||
        cursor > frame.pool + displayBytes - required ||
        selectedMode.load(std::memory_order_relaxed) != frame.buoyMode ||
        (frame.extendDolphinEntrance && wr64::object_distance::mode() != 3)) restoreVisibility(rdram);
}

extern "C" void wr64_draw_distance_end(uint8_t* rdram, recomp_context* ctx) {
    if (!frame.nativeVisibilityReady || !sameCall(rdram, ctx)) return;
    // The body and detail lists are complete. Twilight lights and later
    // overlays share this table and allocate dynamic matrices;
    // they must see precisely the original visibility and fade values.
    // This also safely handles a prior capacity rollback, and is idempotent.
    restoreVisibility(rdram);
    frame = {};
}

extern "C" void wr64_area_draw_distance_begin(uint8_t* rdram, recomp_context* ctx) {
    area = {};
    const uint32_t mode = selectedMode.load(std::memory_order_relaxed);
    if (!mode || !rdram || !ctx) return;
    if (!worldCamera(rdram, ctx)) return;
    const uint32_t camera = uint32_t(ctx->r22);
    const uint32_t stack = uint32_t(ctx->r29), descriptor = word(rdram, 0x801C0C80);
    const uint32_t count = word(rdram, areaCount), pool = word(rdram, 0x801518B8);
    const uint32_t matrices = word(rdram, 0x801AE948);
    const uint32_t near = uint32_t(ctx->r17), far = uint32_t(ctx->r18);
    if (!resident(stack, 0x5F0) || (stack & 7) || descriptor != 0x801CB058 + word(rdram, 0x800DAB2C) * 0x110 ||
        word(rdram, descriptor + 0xA0) != near || word(rdram, descriptor + 0xA4) != far ||
        near >= far || far > 1000000 || count == 0 || count > maxAreaObjects ||
        uint32_t(ctx->r11) != count ||
        (pool != firstDisplayPool && pool != firstDisplayPool + displayPoolStride) ||
        (matrices != firstMatrixPool && matrices != firstMatrixPool + matrixPoolStride)) return;
    const uint32_t cursor = word(rdram, stack + 0x550);
    if ((cursor & 7) || cursor < pool || cursor > pool + displayBytes) return;
    const float cameraX = real(rdram, camera + 0x4C), cameraZ = real(rdram, camera + 0x54);
    if (!std::isfinite(cameraX) || !std::isfinite(cameraZ)) return;
    for (uint32_t i = 0; i < count; ++i) {
        const uint32_t object = areaBase + i * areaStride;
        const float dx = real(rdram, object) - cameraX, dz = real(rdram, object + 8) - cameraZ;
        const float distance = std::sqrt(dx * dx + dz * dz);
        if (!std::isfinite(distance)) return;
        area.distances[i] = distance;
        area.ordinary[i] = word(rdram, object + 0x10) <= 1;
    }
    area.rdram = rdram;
    area.context = ctx;
    area.stack = stack;
    area.count = count;
    area.pool = pool;
    area.tailReserve = tailReserve(rdram);
    area.nearRegister = ctx->r17;
    area.farRegister = ctx->r18;
    area.scaled = true;
    const uint32_t numerator = mode == 1 ? 3 : 4;
    ctx->r17 = S32(near * numerator / 2);
    ctx->r18 = S32(far * numerator / 2);
}

extern "C" void wr64_area_draw_distance_finish(uint8_t* rdram, recomp_context* ctx) {
    if (!area.scaled || !sameAreaCall(rdram, ctx)) return;
    ctx->r17 = area.nearRegister;
    ctx->r18 = area.farRegister;
    area.scaled = false;
    const uint32_t near = uint32_t(area.nearRegister), far = uint32_t(area.farRegister);
    std::array<uint32_t, maxAreaObjects> extraIndices{};
    uint32_t originalCount = 0, extraCount = 0;
    for (uint32_t i = 0; i < area.count; ++i) {
        const int16_t visibility = MEM_H(0, S32(areaVisibilityBase + i * 2));
        const bool nativeVisible = visibility >= 0 && area.distances[i] < float(far);
        area.nativeVisibility[i] = nativeVisible ? nativeFade(area.distances[i], near, far) : -1;
        if (nativeVisible) ++originalCount;
        if (!area.ordinary[i])
            MEM_H(0, S32(areaVisibilityBase + i * 2)) = area.nativeVisibility[i];
        else if (visibility >= 0 && !nativeVisible)
            extraIndices[extraCount++] = i;
    }
    area.nativeVisibilityReady = true;
    if (originalCount > areaMatrixSlots || selectedMode.load(std::memory_order_relaxed) == 0) {
        restoreAreaVisibility(rdram);
        return;
    }
    std::sort(extraIndices.begin(), extraIndices.begin() + extraCount, [](uint32_t a, uint32_t b) {
        return area.distances[a] != area.distances[b] ? area.distances[a] < area.distances[b] : a < b;
    });
    const uint32_t extra = std::min(extraCount, areaMatrixSlots - originalCount);
    for (uint32_t i = extra; i < extraCount; ++i)
        MEM_H(0, S32(areaVisibilityBase + extraIndices[i] * 2)) = -1;
    area.visible = originalCount + extra;
    area.pending = true;
}

extern "C" void wr64_area_draw_distance_capacity(uint8_t* rdram, recomp_context* ctx) {
    if (!area.pending || !sameAreaCall(rdram, ctx)) return;
    area.pending = false;
    const uint32_t checkpointBudget = frame.pending && sameCall(rdram, ctx) ? frame.extra * extraDisplayBytes : 0;
    const uint32_t required = area.tailReserve + checkpointBudget + areaSetupBytes + area.visible * areaDisplayBytes;
    const uint32_t cursor = word(rdram, area.stack + 0x550);
    if (word(rdram, 0x801518B8) != area.pool || (cursor & 7) || cursor < area.pool ||
        cursor > area.pool + displayBytes - required ||
        selectedMode.load(std::memory_order_relaxed) == 0) restoreAreaVisibility(rdram);
}

extern "C" void wr64_area_draw_distance_end(uint8_t* rdram, recomp_context* ctx) {
    if (!area.nativeVisibilityReady || !sameAreaCall(rdram, ctx)) return;
    restoreAreaVisibility(rdram);
    area = {};
}
