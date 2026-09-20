#pragma once
#include <cstdint>

// The original Sunny experiment covers the eight native VS race courses and
// the authenticated Dolphin Park Free Ride bank.
// Retain these hook names and the saved setting key for compatibility.

namespace wr64::sunny_detail {
void set_enabled(bool enabled);
void set_diagnostic_sink(void (*sink)(const char*));
void note_diagnostic(const char* message);
}

extern "C" {
void wr64_sunny_detail_begin_load(uint8_t* rdram);
uint32_t wr64_sunny_detail_active(uint8_t* rdram);
uint32_t wr64_sunny_detail_water_active(uint8_t* rdram);
uint32_t wr64_sunny_detail_assets(uint8_t* rdram, uint32_t entry);
uint32_t wr64_sunny_detail_shape_span(uint8_t* rdram, uint32_t entry, uint32_t original);
void wr64_sunny_detail_visuals(uint8_t* rdram);
uint32_t wr64_dolphin_free_ride_available(const uint8_t* rdram);
uint32_t wr64_sunny_detail_course_players(uint8_t* rdram, uint32_t original);
}
