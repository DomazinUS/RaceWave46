#include "wr64_diagnostic_policy.h"
#include "wr64_sunny_detail.hpp"
#include "../lib/rt64/src/common/rt64_wr64_rt_two_player_assets.h"
#include <atomic>
#include <cstdio>
#include <cstring>

namespace {
std::atomic<bool> requested{false};
std::atomic<void (*)(const char*)> diagnosticSink{nullptr};
// The native game thread owns course loading and these resident-asset flags.
bool enabledForLoad = false;
bool fullShapeSelected = false;
bool fullTexturesSelected = false;
struct CourseAssets {
    uint32_t fullEntry, originalEntry, fullTextures, originalTextures;
    uint32_t fullSpan, originalSpan, graphicsBytes;
    uint32_t roots[6];
    uint64_t fullShapeHash, originalShapeHash, fullTextureHash, originalTextureHash;
    uint32_t fullShapeWords = 12;
    bool separateCommon = true;
};
#include "wr64_two_player_course_assets.inc"
int32_t loadedCourse = -1;
const CourseAssets* loadedAssets = nullptr;
constexpr uint32_t fullTables[]{0x800D5470, 0x800D54A0, 0x800D5530,
    0x800D5560, 0x800D55F0, 0x800D5620};

template<class T> T read(const uint8_t* rdram, uint32_t address) {
    T value;
    std::memcpy(&value, rdram + ((address & 0x7FFFFFU) ^ (sizeof(T) == 2 ? 2U : 0U)), sizeof(T));
    return value;
}
void write(uint8_t* rdram, uint32_t address, uint32_t value) {
    std::memcpy(rdram + (address & 0x7FFFFFU), &value, sizeof(value));
}
const CourseAssets* assetsForCourse(const uint8_t* rdram) {
    if (!rdram) return nullptr;
    const auto course = read<int32_t>(rdram, 0x800D8170);
    // Dolphin's unused VS graphics entry aliases Sunny Beach. Free Ride must
    // load the real Dolphin bank even with Original two-player scenery selected.
    if (course == 0 && read<int32_t>(rdram, 0x801CE608) == 1) return &dolphinAssets;
    return course >= 1 && course <= 8 ? &courses[course - 1] : nullptr;
}
bool twoPlayerLoad(const uint8_t* rdram) {
    if (!rdram) return false;
    const auto mode = read<int32_t>(rdram, 0x800DAB24);
    return mode >= 40 && mode <= 45 && assetsForCourse(rdram) &&
        read<int16_t>(rdram, 0x801CE60C) == 2;
}
bool sameLoadedCourse(const uint8_t* rdram) {
    return loadedAssets && twoPlayerLoad(rdram) &&
        read<int32_t>(rdram, 0x800D8170) == loadedCourse;
}
void diagnose(const char* stage, const uint8_t* rdram, uint32_t entry = 0) {
    auto sink = diagnosticSink.load(std::memory_order_relaxed);
    if (!sink || !rdram) return;
    char line[512];
    std::snprintf(line, sizeof(line),
        "%s requested=%d eligible=%d selected=%d course=%d mode=%d phase=%d players=%d layout=%d entry=%08X shape=%08X common=%08X roots=%08X,%08X,%08X,%08X,%08X,%08X full_textures=%d",
        stage, int(requested.load(std::memory_order_relaxed)), int(enabledForLoad), int(fullShapeSelected),
        read<int32_t>(rdram, 0x800D8170), read<int32_t>(rdram, 0x800DAB24),
        read<int32_t>(rdram, 0x801CE638), read<int32_t>(rdram, 0x800DAB28), read<int16_t>(rdram, 0x801CE60C),
        entry, read<uint32_t>(rdram, 0x800D45E4), read<uint32_t>(rdram, 0x800D45E8),
        read<uint32_t>(rdram, 0x801C1CD0), read<uint32_t>(rdram, 0x801C1CD4),
        read<uint32_t>(rdram, 0x801C1CD8), read<uint32_t>(rdram, 0x801C1CDC),
        read<uint32_t>(rdram, 0x801C1CE0), read<uint32_t>(rdram, 0x801C1CE4), int(fullTexturesSelected));
    sink(line);
}
uint64_t recordHash(const uint8_t* rdram, uint32_t address, uint32_t words) {
    uint64_t hash = 0xCBF29CE484222325ULL;
    for (uint32_t i = 0; i < words; ++i) {
        hash ^= read<uint32_t>(rdram, address + 4 * i);
        hash *= 0x100000001B3ULL;
    }
    return hash;
}
bool knownCourseMetadata(const uint8_t* rdram, const CourseAssets& assets, uint32_t course) {
    if (!rdram) return false;
    const uint32_t index = course * 4;
    if (read<uint32_t>(rdram, 0x800DC4F0 + index) != assets.fullEntry ||
        read<uint32_t>(rdram, 0x800DC514 + index) != assets.originalEntry ||
        read<uint32_t>(rdram, 0x800DCE3C + index) != assets.fullSpan ||
        read<uint32_t>(rdram, 0x800DCE60 + index) != assets.originalSpan ||
        read<uint32_t>(rdram, 0x800DC0E4 + index) != assets.fullTextures ||
        read<uint32_t>(rdram, 0x800DC108 + index) != assets.originalTextures ||
        recordHash(rdram, assets.fullEntry, assets.fullShapeWords) != assets.fullShapeHash ||
        recordHash(rdram, assets.originalEntry, 12) != assets.originalShapeHash ||
        recordHash(rdram, assets.fullTextures, 32) != assets.fullTextureHash ||
        recordHash(rdram, assets.originalTextures, 32) != assets.originalTextureHash) return false;
    for (unsigned i = 0; i < 6; ++i)
        if (read<uint32_t>(rdram, fullTables[i] + index) != assets.roots[i]) return false;
    if (course == 0) {
        // Both modes transfer the same Dolphin physics dataset. The unused VS
        // descriptor tables are stubs, so SetCourse selects the authored 1P
        // descriptors locally while all player/controller globals remain 2P.
        if (read<uint32_t>(rdram, 0x800DC698) != 0x800DC538 ||
            read<uint32_t>(rdram, 0x800DC6BC) != 0x800DC538 ||
            recordHash(rdram, 0x800DC538, 8) != 0x50589117AF32EF73ULL) return false;
        constexpr uint32_t tables[]{0x800D699C, 0x800D69CC, 0x800D69FC, 0x800D6A2C,
            0x800D6B1C, 0x800D6B4C, 0x800D6B7C, 0x800D6BAC};
        constexpr uint32_t descriptors[]{0x80306CF0, 0x80306D30, 0x80307430, 0x80307630,
            0x80307EB0, 0x803098B4, 0x8030936C, 0x80307EEC};
        for (unsigned i = 0; i < 8; ++i)
            if (read<uint32_t>(rdram, tables[i]) != descriptors[i]) return false;
    }
    return true;
}
bool knownCourseAssets(const uint8_t* rdram, const CourseAssets& assets, uint32_t course) {
    if (!knownCourseMetadata(rdram, assets, course)) return false;
    // Audited full banks fit the native 0x30000 graphics arena on all tracks.
    // Retain the original allocation and separate two-player course-data load.
    const uint32_t base = read<uint32_t>(rdram, 0x800D45E4);
    const uint32_t data = read<uint32_t>(rdram, 0x800D45EC);
    return base >= 0x80000000U && base <= 0x80800000U - 0x40000U &&
        data >= base + assets.graphicsBytes && data <= base + 0x30000U;
}
}

void wr64::sunny_detail::set_enabled(bool enabled) {
    requested.store(enabled, std::memory_order_relaxed);
}
void wr64::sunny_detail::set_diagnostic_sink(void (*sink)(const char*)) {
    diagnosticSink.store(sink, std::memory_order_relaxed);
}
void wr64::sunny_detail::note_diagnostic(const char* message) {
    if (auto sink = diagnosticSink.load(std::memory_order_relaxed)) sink(message);
}

extern "C" void wr64_sunny_detail_begin_load(uint8_t* rdram) {
    RT64::wr64RTPublishTwoPlayerAssets(nullptr, 0);
    enabledForLoad = false;
    fullShapeSelected = false;
    fullTexturesSelected = false;
    loadedAssets = nullptr;
    loadedCourse = -1;
    // This hook is on the native course-load branch (modes 7 and 40), not on
    // retries or the settings callback. A resident race keeps its asset choice.
    if (!twoPlayerLoad(rdram) || read<int32_t>(rdram, 0x800DAB24) != 40 ||
        (!requested.load(std::memory_order_relaxed) && read<int32_t>(rdram, 0x800D8170) != 0)) {
        diagnose("load-original", rdram);
        return;
    }
    const auto* assets = assetsForCourse(rdram);
    const auto course = read<int32_t>(rdram, 0x800D8170);
    enabledForLoad = knownCourseAssets(rdram, *assets, uint32_t(course));
    if (enabledForLoad) {
        loadedCourse = course;
        loadedAssets = assets;
    }
    diagnose(enabledForLoad ? "load-enhanced" : "load-unknown-assets", rdram);
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[two-player-detail] course=%d %s\n", course, enabledForLoad ?
        "loading single-player scenery; two-player gameplay retained" :
        "unrecognized asset layout; keeping original scenery"));
}

extern "C" uint32_t wr64_sunny_detail_assets(uint8_t* rdram, uint32_t entry) {
    // Redirect only the shape/common transfer at the loader boundary. Neither
    // the native queue nor its separate collision, rider and sky records change.
    const auto* assets = assetsForCourse(rdram);
    if (!assets || (entry != assets->originalEntry && entry != assets->originalTextures)) return entry;
    if (!enabledForLoad || !sameLoadedCourse(rdram)) {
        diagnose("asset-original", rdram, entry);
        return entry;
    }
    if (entry == assets->originalTextures) {
        fullTexturesSelected = true;
        diagnose("textures-enhanced", rdram, assets->fullTextures);
        return assets->fullTextures;
    } else {
        fullShapeSelected = true;
        diagnose("asset-enhanced", rdram, assets->fullEntry);
        return assets->fullEntry;
    }
}

extern "C" uint32_t wr64_sunny_detail_shape_span(uint8_t* rdram, uint32_t entry, uint32_t original) {
    // Match the selected payload even if a setting changes during loading.
    // The following flag-8 record uses this span to place segment 14 correctly.
    return fullShapeSelected && sameLoadedCourse(rdram) && entry == loadedAssets->fullEntry ?
        loadedAssets->fullSpan : original;
}

extern "C" uint32_t wr64_sunny_detail_active(uint8_t* rdram) {
    return fullShapeSelected && sameLoadedCourse(rdram) &&
        read<int32_t>(rdram, 0x800DAB28) == 2 && read<int32_t>(rdram, 0x801CE638) == 1 &&
        (!loadedAssets->separateCommon ||
        read<uint32_t>(rdram, 0x800D45E8) == read<uint32_t>(rdram, 0x800D45E4) + loadedAssets->fullSpan);
}

extern "C" uint32_t wr64_dolphin_free_ride_available(const uint8_t* rdram) {
    return knownCourseMetadata(rdram, dolphinAssets, 0);
}

extern "C" uint32_t wr64_sunny_detail_course_players(uint8_t* rdram, uint32_t original) {
    return original == 2 && loadedCourse == 0 && wr64_sunny_detail_water_active(rdram) ? 1 : original;
}

extern "C" uint32_t wr64_sunny_detail_water_active(uint8_t* rdram) {
    return fullTexturesSelected && wr64_sunny_detail_active(rdram);
}

extern "C" void wr64_sunny_detail_visuals(uint8_t* rdram) {
    if (!wr64_sunny_detail_active(rdram)) {
        RT64::wr64RTPublishTwoPlayerAssets(nullptr, 0);
        diagnose("visuals-original", rdram);
        return;
    }
    // SetCourse has completed its six visual writes. Race tracks retain their
    // native VS descriptors; Dolphin's separate local hook selects its real data.
    for (unsigned i = 0; i < 6; ++i) write(rdram, 0x801C1CD0 + i * 4, loadedAssets->roots[i]);
    // Publish the loaded asset choice, not the currently requested setting.
    // The RT64 producer snapshots this without calling game-thread helpers.
    RT64::wr64RTPublishTwoPlayerAssets(fullTexturesSelected ? rdram : nullptr, uint32_t(loadedCourse));
    diagnose("visuals-enhanced", rdram);
}
