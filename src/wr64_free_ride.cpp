#include "wr64_free_ride.h"

#include <cstring>

namespace {
constexpr uint32_t rdram_mask = 0x007FFFFF;
constexpr uint32_t rules_base = 0x801C2938;
constexpr uint32_t rules_stride = 0x378;

// Recompiled RDRAM stores native aligned words in host byte order.
uint32_t word(const uint8_t* rdram, uint32_t address) {
    uint32_t value;
    std::memcpy(&value, rdram + (address & rdram_mask), sizeof(value));
    return value;
}
}

extern "C" int wr64_free_ride_active(const uint8_t* rdram) {
    if (rdram == nullptr) {
        return 0;
    }
    const uint32_t mode = word(rdram, 0x800DAB24);
    return word(rdram, 0x800D8170) == 0
        && word(rdram, 0x800DAB28) == 2
        && word(rdram, 0x801CE638) == 1
        && mode >= 40 && mode <= 45
        && word(rdram, 0x801CE608) == 1
        && word(rdram, 0x801CE620) == 1;
}

extern "C" int wr64_free_ride_skip_retirement(const uint8_t* rdram, uint32_t record_address) {
    if (!wr64_free_ride_active(rdram)) {
        return 0;
    }
    // Require the actual KSEG0 record pointer used by native callers. Do not
    // turn arbitrary addresses or non-player records into exempt racers.
    for (uint32_t player = 0; player < 2; ++player) {
        const uint32_t rider = word(rdram, 0x800D48DC + player * 4);
        if (rider < 4 && record_address == rules_base + rider * rules_stride) {
            return 1;
        }
    }
    return 0;
}

extern "C" int wr64_free_ride_skip_audio(const uint8_t* rdram, uint32_t command) {
    if (command != 0x06000C00 && command != 0x06000C01 && command != 0x06000C02) {
        return 0;
    }
    return wr64_free_ride_active(rdram);
}

extern "C" void wr64_free_ride_schedule_music(uint8_t* rdram) {
    if (!wr64_free_ride_active(rdram)
        || word(rdram, 0x801D7DC0) != 1
        || word(rdram, 0x801D7DC4) != 0
        || word(rdram, 0x801D7DCC) != 6
        || word(rdram, 0x800E7C98) == 0) {
        return;
    }
    // VS normally schedules music from the race-start event. Dolphin Park has
    // no competitive start event, so use Warm Up's eight-tick native countdown
    // after the VS initializer has selected/preloaded Dolphin's sequence 6.
    const uint32_t countdown = 8;
    std::memcpy(rdram + (0x800E7CD8 & rdram_mask), &countdown, sizeof(countdown));
}

extern "C" int wr64_free_ride_skip_hud(const uint8_t* rdram, uint32_t native_site) {
    switch (native_site) {
    case 0x801F42FC: // Two VS timer draws inside the mixed timer/speed producer.
    case 0x801FAEB8: // Large lap / final-lap presentation.
    case 0x801FBFB4: // VS score marks, separate from the speed producer.
        return wr64_free_ride_active(rdram);
    default:
        return 0;
    }
}
