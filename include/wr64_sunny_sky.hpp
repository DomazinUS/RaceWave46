#pragma once
#include <cstdint>
#include "recomp.h"

extern "C" {
void wr64_sunny_sky_bottom_camera(uint8_t* rdram, recomp_context* ctx);
uint32_t wr64_sunny_sky_bottom_draw(uint8_t* rdram, uint32_t original);
void wr64_sunny_sky_cloud_camera(uint8_t* rdram, recomp_context* ctx);
uint32_t wr64_sunny_sky_material_players(uint8_t* rdram, uint32_t original);
uint32_t wr64_sunny_sky_fog_update(uint8_t* rdram, uint32_t original);
void wr64_sunny_sky_cloud_color(uint8_t* rdram, recomp_context* ctx);
void wr64_sunny_sky_cloud_draw(uint8_t* rdram, recomp_context* ctx);
}
