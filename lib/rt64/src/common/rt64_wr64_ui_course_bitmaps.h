#pragma once

#include <array>
#include <cstdint>

namespace RT64 {
    struct Wr64UiCourseBitmap {
        uint64_t tmemHash;
        uint32_t width, height;
        const char *name;
    };

    // Native USA course names and shared course/round record labels only.
    // All nine Course Select names and BEST LAP/TIME join exact native IA8
    // TMEM hashes and dimensions from watercraft-21-census.csv (20260907).
    // Remaining identities are reconstructed from the USA Rev 1 message tables,
    // using the actual current IPS-selected banks for segment-8 bitmaps.
    // See captured_course_labels.h for independent source addresses and which
    // entries have recorded draw metadata. No unknown/world texture is admitted.
    // USA GMESG_KIND12 uses ten rows; ROUND adds DHT_ROUND=1 (eleven rows).
    // Color/selection variants reuse these same texture bytes and dimensions.
    inline constexpr std::array<Wr64UiCourseBitmap, 26> Wr64UiCourseBitmaps = {{
        {0x52C0E4F0186CD43EULL,  80, 10, "DOLPHIN PARK"},
        {0xC6D7BE36D2807B6AULL,  80, 10, "SUNNY BEACH"},
        {0x774D7FAB519131EEULL,  72, 10, "SUNSET BAY"},
        {0x8F3E74F88B7A24A2ULL,  72, 10, "DRAKE LAKE"},
        {0x6CB42BB19CEA806CULL,  96, 10, "MARINE FORTRESS"},
        {0x2B176290DE7558A5ULL,  64, 10, "PORT BLUE"},
        {0x4B4C78E8335B0760ULL,  80, 10, "TWILIGHT CITY"},
        {0xE0339559F6AA2901ULL,  88, 10, "GLACIER COAST"},
        {0xFB8EEAB2E7F9CF76ULL,  96, 10, "SOUTHERN ISLAND"},
        {0x076A4F22505F3DDCULL,  48,  8, "BEST LAP"},
        {0x1243D51F32E566C5ULL,  56,  8, "BEST TIME"},
        {0x3DB694FDE50904CEULL, 152, 10, "POINTS NEEDED TO ADVANCE"},
        {0x7C3831C19381920FULL,  72, 10, "YOUR POINTS"},
        {0x9E90AE0E9FE4F25CULL,  40,  8, "POINTS"},
        {0x98A35E2D896482FDULL,  80,  8, "CURRENT TIME"},
        {0x3FD209D3D9A023EFULL,  56, 11, "ROUND 1"},
        {0xFDC5D38E404BAC29ULL,  56, 11, "ROUND 2"},
        {0x4AC39FA9D21D8CC5ULL,  56, 11, "ROUND 3"},
        {0xEE6240AB31FF7028ULL,  56, 11, "ROUND 4"},
        {0x9FF69FF15878A2C8ULL,  56, 11, "ROUND 5"},
        {0x87631347AB995B8BULL,  56, 11, "ROUND 6"},
        {0xC9860988769FFB95ULL,  56, 11, "ROUND 7"},
        {0x77C4C48631C4050FULL,  56, 11, "ROUND 8"},
        {0x539BAB154B278137ULL,  88, 11, "FINAL ROUND"},
        {0x78DDCE7070210F60ULL,  64,  8, "BEST SCORE"},
        {0x300A37232533D6F7ULL,  88,  8, "COURSE RECORD"},
    }};
}
