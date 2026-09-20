#pragma once
#include <array>
#include <cstdint>

// Independently decoded US Rev1 table at800D9964, matched against the archived
// RDRAM table and prior reference-object byte audit. These are test expectations,
// not replacement production lighting or mutable camera-record values.
struct NativeLightPreset {
    const char *name;
    std::array<float, 3> direction;
    std::array<uint32_t, 3> diffuse;
    std::array<uint32_t, 3> ambient;
};
inline constexpr std::array<NativeLightPreset, 9> NativeLightPresets{{
    {"Dolphin Park",    {-80,80,0}, {255,255,255}, {120,120,120}},
    {"Sunny Beach",     {-80,80,0}, {255,255,255}, {140,140,140}},
    {"Sunset Bay",      {0,85,85},  {255,255,255}, {85,21,10}},
    {"Marine Fortress", {0,85,85},  {175,175,175}, {80,90,90}},
    {"Drake Lake",      {0,85,85},  {180,180,180}, {100,100,80}},
    {"Port Blue",       {0,85,85},  {255,255,255}, {111,122,163}},
    {"Twilight City",   {0,85,85},  {220,220,220}, {120,130,150}},
    {"Southern Island", {0,85,85},  {255,255,255}, {140,140,140}},
    {"Glacier Coast",   {0,85,85},  {255,255,255}, {205,205,205}}
}};
