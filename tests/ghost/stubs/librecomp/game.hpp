#pragma once
#include "recomp.h"
#include <span>
namespace recomp {
std::span<const uint8_t> get_rom();
void do_rom_read(uint8_t*,gpr,uint32_t,std::size_t);
}
