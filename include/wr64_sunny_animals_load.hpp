#pragma once
#include <cstdint>

extern "C" {
uint32_t wr64_sunny_animals_ready(uint8_t* rdram);
uint32_t wr64_sunny_animals_init_players(uint8_t* rdram, uint32_t original);
}
