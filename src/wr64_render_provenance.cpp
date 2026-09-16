#include "wr64_diagnostic_policy.h"
#include "wr64_render_provenance.h"

#include <algorithm>
#include <atomic>
#include <deque>
#include <mutex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef WR64_ENABLE_RT64
#include "common/rt64_wr64_cpu_logo.h"
#include "common/rt64_wr64_rt_startup.h"
#include "common/rt64_wr64_hud_motion.h"
#include "common/rt64_wr64_dolphin_sun_sprite.h"
#include "common/rt64_wr64_wave_distance.h"
#include "ultramodern/ultramodern.hpp"
#define XXH_INLINE_ALL
#include "contrib/xxHash/xxhash.h"
#endif

#ifdef WR64_ENABLE_RT64
// Runtime shutdown flag, also consumed by its VI and thread-cleaner loops.
extern std::atomic_bool exited;
extern "C" void yield_self_1ms(uint8_t *rdram);
#endif

extern "C" void wr64_wait_for_rt_startup(uint8_t *rdram) {
#ifdef WR64_ENABLE_RT64
    RT64::wr64RTStartupGate.request();
    while (RT64::wr64RTStartupGate.waiting() && !exited.load()) {
        // Service native external messages and yield, rather than blocking the
        // emulated scheduler or the graphics/window thread during driver work.
        yield_self_1ms(rdram);
    }
    if (exited.load()) RT64::wr64RTStartupGate.publish(RT64::Wr64RTStartupGate::State::Cancelled);
#endif
}

extern "C" void wr64_note_cpu_boot_logo(uint8_t* rdram, uint32_t framebuffer) {
#ifdef WR64_ENABLE_RT64
    const uint32_t address = framebuffer & 0x1FFFFFFFu;
    if (rdram && address <= 0x800000u - RT64::Wr64CpuLogoBytes) {
        RT64::wr64RegisterCpuLogo(address,
            XXH3_64bits(rdram + address, RT64::Wr64CpuLogoBytes));
    }
#endif
}

namespace {
struct PendingTask {
    uint64_t sequence;
    uint32_t taskAddress;
    uint32_t contextRa;
    uint32_t rootDisplayList;
    uint32_t ucode;
    uint32_t ucodeData;
#ifdef WR64_ENABLE_RT64
    RT64::Wr64HudBatch hud;
    RT64::Wr64DolphinSunBatch sun;
#endif
};

std::atomic<uint64_t> nextSequence{1};
std::mutex pendingMutex;
std::deque<PendingTask> pendingTasks;
constexpr size_t MaxPendingTasks = 256;
}

extern "C" void wr64_note_gfx_task(
    uint32_t task_address,
    uint32_t context_ra,
    uint32_t root_display_list,
    uint32_t ucode,
    uint32_t ucode_data)
{
    std::scoped_lock lock(pendingMutex);
    const uint64_t sequence = nextSequence.fetch_add(1, std::memory_order_relaxed);
#ifdef WR64_ENABLE_RT64
    RT64::wr64SealWaveDistanceTask(sequence);
#endif
    pendingTasks.push_back(PendingTask{
        sequence,
        task_address,
        context_ra,
        root_display_list,
        ucode,
        ucode_data
#ifdef WR64_ENABLE_RT64
        , RT64::wr64HudSeal(sequence)
        , RT64::wr64DolphinSunSeal(sequence)
#endif
    });
    while (pendingTasks.size() > MaxPendingTasks) {
        pendingTasks.pop_front();
    }
}

extern "C" uint64_t wr64_claim_gfx_task(
    uint32_t root_display_list,
    uint32_t ucode,
    uint32_t ucode_data,
    uint32_t* task_address,
    uint32_t* context_ra)
{
    std::scoped_lock lock(pendingMutex);
#ifdef WR64_ENABLE_RT64
    RT64::wr64HudClaimed = {};
    RT64::wr64DolphinSunClaimed = {};
#endif
    const auto match = std::find_if(pendingTasks.begin(), pendingTasks.end(),
        [=](const PendingTask& task) {
            return (task.rootDisplayList == root_display_list) &&
                (task.ucode == ucode) && (task.ucodeData == ucode_data);
        });
    if (match == pendingTasks.end()) {
        if (task_address != nullptr) *task_address = 0;
        if (context_ra != nullptr) *context_ra = 0;
        return 0;
    }

    const PendingTask task = *match;
    pendingTasks.erase(pendingTasks.begin(), std::next(match));
    if (task_address != nullptr) *task_address = task.taskAddress;
    if (context_ra != nullptr) *context_ra = task.contextRa;
#ifdef WR64_ENABLE_RT64
    RT64::wr64HudClaimed = task.hud;
    RT64::wr64DolphinSunClaimed = task.sun;
#endif
    return task.sequence;
}

extern "C" void wr64_hud_score_spawn(uint32_t address) {
#ifdef WR64_ENABLE_RT64
    if (address >= 0x80228ae0u && address < 0x80228b50u &&
        (address - 0x80228ae0u) % 28 == 0)
        RT64::wr64HudSpawn((address - 0x80228ae0u) / 28);
#endif
}
extern "C" void wr64_hud_park_spawn() {
#ifdef WR64_ENABLE_RT64
    RT64::wr64HudSpawn(4);
#endif
}
extern "C" void wr64_ending_hud_spawn() {
#ifdef WR64_ENABLE_RT64
    RT64::wr64HudSpawn(5);
#endif
}
#ifdef WR64_ENABLE_RT64
static uint32_t wr64HudContext(const uint8_t *ram) {
    return (RT64::wr64HudReadWord(ram, 0x800d8170u) & 255u) |
        ((RT64::wr64HudReadWord(ram, 0x800dab28u) & 255u) << 8) |
        ((RT64::wr64HudReadWord(ram, 0x801ce638u) & 255u) << 16) |
        ((RT64::wr64HudReadWord(ram, 0x800dab24u) & 255u) << 24);
}

namespace {
struct DolphinSunProducer {
    RT64::Wr64DolphinSunSprite sprite{};
    uint32_t token = 0;
    uint64_t generation = 0;
    uint32_t previousContext = 0;
    bool continuous = false;
};
thread_local DolphinSunProducer dolphinSunProducer;

float dolphinSunFloat(const uint8_t* ram, uint32_t address) {
    const uint32_t bits = RT64::wr64HudReadWord(ram, address);
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

void dolphinSunNativeTrace(uint32_t token, uint32_t packet,
    const RT64::Wr64DolphinSunSprite& sprite, bool carrier) {
    // An explicit test-launch path is required. This does not access profiles
    // or dump arbitrary memory, and cannot grow without a bound.
    static std::mutex mutex;
    static FILE* file = []() -> FILE* {
        const char* path = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_DOLPHIN_SUN_NATIVE_TRACE"));
        if (!path || !*path) return nullptr;
        FILE* result = std::fopen(path, "wx");
        if (result) std::fputs("token,packet,generation,context,center_x,center_y,radius,dsdx,dtdy,carrier\n", result);
        return result;
    }();
    if (!file) return;
    std::lock_guard lock(mutex);
    static uint32_t rows = 0;
    if (rows++ >= 200000) return;
    std::fprintf(file, "%u,%08X,%llu,%08X,%.9g,%.9g,%.9g,%d,%d,%u\n",
        token, packet, static_cast<unsigned long long>(sprite.generation), sprite.context,
        sprite.centerX, sprite.centerY, sprite.radiusX, sprite.dsdx, sprite.dtdy, carrier ? 1u : 0u);
    if ((rows & 127u) == 0) std::fflush(file);
}
}
#endif

extern "C" uint32_t wr64_dolphin_sun_begin(uint8_t* ram, float center_x, float center_y) {
#ifdef WR64_ENABLE_RT64
    auto& producer = dolphinSunProducer;
    producer.sprite = {};
    if (!ram || !RT64::wr64DolphinSunNativeExitEnabled()) {
        producer.continuous = false;
        return 0;
    }
    const uint32_t context = wr64HudContext(ram);
    const float depth = dolphinSunFloat(ram, 0x801c4178u);
    const float facing = dolphinSunFloat(ram, 0x801c4184u);
    const int32_t radius = int32_t(RT64::wr64HudReadWord(ram, 0x800d9944u));
    // The opening and every other course/player/phase keep their established
    // producer. The -64 depth is the native tiny-W rejection sentinel.
    if ((context & 0x00ffffffu) != 0x00010100u || radius != 12 ||
        !std::isfinite(center_x) || !std::isfinite(center_y) ||
        !std::isfinite(depth) || depth == -64.0f ||
        !std::isfinite(facing) || facing < 0.0f ||
        center_x < -128.0f || center_x > 4096.0f ||
        center_y < -128.0f || center_y >= 240.0f) {
        producer.continuous = false;
        return 0;
    }
    if (!producer.continuous || producer.previousContext != context) ++producer.generation;
    producer.continuous = true;
    producer.previousContext = context;
    auto& sprite = producer.sprite;
    sprite.generation = producer.generation;
    sprite.context = context;
    sprite.recordId = 0x801c4170u;
    sprite.view = 0;
    sprite.admitted = true;
    sprite.centerX = center_x;
    sprite.centerY = center_y;
    sprite.radiusX = sprite.radiusY = float(radius);
    // Full native disk texture origin. The packet's derivative is captured
    // after emission; its clipped S/T is deliberately not reused.
    sprite.preclipS = sprite.preclipT = 0;
    sprite.flip = false;
    if (++producer.token == 0) ++producer.token;
    return producer.token;
#else
    return 0;
#endif
}

extern "C" void wr64_dolphin_sun_packet(uint8_t* ram, uint32_t token, uint32_t packet) {
#ifdef WR64_ENABLE_RT64
    auto& producer = dolphinSunProducer;
    if (!ram || !token || token != producer.token || !producer.sprite.admitted) return;
    const uint32_t address = packet & 0x1fffffffu;
    if (!address || (address & 7u) != 0 || address > 0x800000u - 24u ||
        (RT64::wr64HudReadWord(ram, address) >> 24) != 0xe4u ||
        RT64::wr64HudReadWord(ram, address + 8) != 0xb3000000u ||
        RT64::wr64HudReadWord(ram, address + 16) != 0xb2000000u) return;
    auto sprite = producer.sprite;
    const uint32_t derivative = RT64::wr64HudReadWord(ram, address + 20);
    sprite.dsdx = int16_t(derivative >> 16);
    sprite.dtdy = int16_t(derivative);
    if (sprite.dsdx != 0x555 || sprite.dtdy != 0x555) return;
    const bool carrier = std::trunc(sprite.centerY) < 0.0f;
    if (carrier) {
        // The original producer emitted nothing for negative integer centers.
        // Keep native rendering empty; final presentation alone uses the
        // authenticated full signed quad. Use an interior zero-height carrier
        // so the general screen-edge snap cannot accidentally add coverage.
        for (uint32_t offset : {0u, 4u}) {
            uint32_t word = RT64::wr64HudReadWord(ram, address + offset);
            word = (word & ~0xfffu) | 24u;
            std::memcpy(ram + address + offset, &word, sizeof(word));
        }
    }
    RT64::wr64DolphinSunRecord(ram, address, sprite);
    dolphinSunNativeTrace(token, address, sprite, carrier);
    producer.sprite = {};
#endif
}

extern "C" void wr64_hud_score_draw(uint8_t *ram, uint32_t address, uint32_t begin, uint32_t end) {
#ifdef WR64_ENABLE_RT64
    if (!ram || address < 0x80228ae0u || address >= 0x80228b50u ||
        (address - 0x80228ae0u) % 28 != 0) return;
    const uint32_t kind = RT64::wr64HudReadWord(ram, address);
    const uint32_t score = RT64::wr64HudReadWord(ram, address + 4);
    const uint32_t age = RT64::wr64HudReadWord(ram, address + 8);
    const int32_t x = int32_t(RT64::wr64HudReadWord(ram, address + 12));
    const int32_t y = int32_t(RT64::wr64HudReadWord(ram, address + 16));
    const int32_t offset = int32_t(RT64::wr64HudReadWord(ram, address + 24));
    if (kind < 1 || kind > 3 || score > 99999 || age >= 23 ||
        x < -100 || x > 0 || y < -100 || y > 0 || (offset != 0 && offset != -32)) return;
    RT64::Wr64HudMotion motion;
    motion.kind = 2; motion.slot = (address - 0x80228ae0u) / 28;
    motion.content = (kind << 24) | score; motion.age = age;
    motion.x = x; motion.y = y + offset; motion.context = wr64HudContext(ram);
    RT64::wr64HudRecord(ram, begin, end, motion, motion.slot);
#endif
}
extern "C" void wr64_hud_park_draw(uint8_t *ram, uint32_t slot, uint32_t begin, uint32_t end) {
#ifdef WR64_ENABLE_RT64
    if (!ram || slot >= 3 || RT64::wr64HudReadWord(ram, 0x802c96a8u) != 1) return;
    const uint32_t id = RT64::wr64HudReadWord(ram, 0x802c96c0u + slot * 4);
    const int32_t x = int32_t(RT64::wr64HudReadWord(ram, 0x802c96b4u + slot * 4));
    if (id > 2048 || x < -8192 || x > 8192) return;
    RT64::Wr64HudMotion motion;
    motion.kind = 1; motion.slot = slot; motion.content = id;
    motion.x = x; motion.y = 200; motion.context = wr64HudContext(ram);
    RT64::wr64HudRecord(ram, begin, end, motion, 4);
#endif
}

extern "C" void wr64_ending_hud_draw(uint8_t *ram, uint32_t row, uint32_t begin, uint32_t end) {
#ifdef WR64_ENABLE_RT64
    if (!ram || row < 0x802c6e80u || row >= 0x802c6f20u || (row & 15u)) return;
    const uint32_t context = wr64HudContext(ram);
    const uint32_t mode = context >> 24;
    // The exact native TourEnd producer owns these rows; the same overlay
    // address in another mode cannot claim the warm-up or ordinary race HUD.
    if ((context & 0x00ffffffu) != 0x00150107u || (mode != 102 && mode != 103) ||
        RT64::wr64HudReadWord(ram, row) == 0) return;
    const uint32_t content = RT64::wr64HudReadWord(ram, row + 4);
    const int32_t x = int32_t(RT64::wr64HudReadWord(ram, row + 8));
    const int32_t y = int32_t(RT64::wr64HudReadWord(ram, row + 12));
    if ((content > 8 && content != 10) || x < -1024 || x > 1024 || y < -1024 || y > 1024) return;
    RT64::Wr64HudMotion motion;
    motion.kind = 3;
    motion.slot = (row - 0x802c6e80u) / 16;
    motion.content = content;
    motion.context = context;
    motion.x = x;
    motion.y = y;
    RT64::wr64HudRecord(ram, begin, end, motion, 5);
#endif
}
