#pragma once
#include <cstddef>
#include <cstdint>
namespace recomp {
constexpr std::uint32_t rom_base=0x10000000;
void* alloc(uint8_t*,std::size_t);void free(uint8_t*,void*);
}
