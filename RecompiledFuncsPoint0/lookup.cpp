#include "recomp.h"

gpr get_entrypoint_address() { return (gpr)(int32_t)0x80046800u; }

const char* get_rom_name() { return ".z64"; }

