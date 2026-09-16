#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
float wr64_sun_logical_width(void);
float wr64_sun_half_extension(void);
uint32_t wr64_sun_logical_width_bits(void);
int32_t wr64_sun_logical_right_edge(void);
int32_t wr64_sun_horizontal_cull_limit(void);
float wr64_sun_record_window_limit(void);
int32_t wr64_sun_right_exit_probe(uint32_t record_address, int32_t course, float facing);
int32_t wr64_sun_right_exit_keep(uint32_t x_bits, uint32_t half_width_bits);
int32_t wr64_sun_dolphin_exit_keep(uint32_t x_bits, uint32_t half_width_bits);
float wr64_sun_wash_edge(int32_t course, float facing, double native_cutoff,
    uint32_t x_bits, uint32_t half_width_bits, int32_t sprite_radius);
float wr64_dolphin_sun_effects(uint8_t* ram, float native_factor);
#ifdef __cplusplus
}
#endif
