#pragma once
#include <cstdint>

namespace RT64 {
// Private USA metadata carried by an otherwise inert F3DEX SPNOOP. It travels
// with the native display list; it is never a cross-thread rendering latch.
constexpr uint32_t Wr64SplitMarker = 0x00575256U;
constexpr uint32_t Wr64SeparateWindowsMarker = 0x00574457U;
constexpr uint32_t Wr64SplitVersion = 0x01000000U;
constexpr uint32_t Wr64SplitPauseMarker = 0x00575250U;
constexpr uint32_t Wr64SplitLapMarker = 0x0057524CU;

struct Wr64LapScope {
    uint32_t first[2]{UINT32_MAX, UINT32_MAX};
    uint32_t last[2]{};
    uint8_t openOwner = 0;
};

inline bool wr64DecodeLapMarker(uint32_t word0, uint32_t word1,
    bool vertical, uint32_t callIndex, Wr64LapScope &scope) {
    if (word0 != Wr64SplitLapMarker ||
        (word1 & 0xFFFFFFFCU) != Wr64SplitVersion || (word1 & 3U) == 3U) return false;
    if (!vertical) return true;
    const uint8_t owner = uint8_t(word1 & 3U);
    if (owner != 0) {
        // An incomplete previous bracket cannot become a valid owner range.
        if (scope.openOwner != 0) {
            scope.first[scope.openOwner - 1] = UINT32_MAX;
            scope.last[scope.openOwner - 1] = 0;
        }
        scope.openOwner = owner;
        scope.first[owner - 1] = callIndex;
        scope.last[owner - 1] = 0;
    } else if (scope.openOwner != 0) {
        scope.last[scope.openOwner - 1] = callIndex;
        scope.openOwner = 0;
    }
    return true;
}

inline int wr64LapOwner(const Wr64LapScope &scope, uint32_t callIndex) {
    for (int owner = 1; owner <= 2; owner++) {
        const int index = owner - 1;
        if (scope.first[index] < scope.last[index] && callIndex >= scope.first[index] &&
            callIndex < scope.last[index]) return owner;
    }
    return 0;
}
inline bool wr64DecodeSplitMarker(uint32_t word0, uint32_t word1,
                                 bool& vertical, uint8_t& pauseOwner, bool* separate = nullptr) {
    if ((word0 != Wr64SplitMarker && word0 != Wr64SeparateWindowsMarker) || (word1 & 0xFFFFFFFCU) != Wr64SplitVersion ||
        (word1 & 3U) == 3U) return false;
    vertical = true;
    if (separate) *separate = word0 == Wr64SeparateWindowsMarker;
    pauseOwner = uint8_t(word1 & 3U);
    return true;
}
}
