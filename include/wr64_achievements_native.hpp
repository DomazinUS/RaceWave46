#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <string>

namespace wr64::achievements::native {

inline constexpr std::size_t memory_size = 0x800000;
inline constexpr const char* original_rom_hash = "2048a640c12d1cf2052ba1629937d2ff";

// The existing N64 achievement definitions use the host-word RAM layout
// exposed by Mupen64Plus/RetroArch, not the CPU's big-endian byte view.
// This recompiler already stores words in that layout: copy bytes unchanged,
// matching rc_libretro_memory_read. Applying the guest MEM_B ^3 conversion
// here moves byte gates and reverses the definitions' little-endian operands.
// Do not wrap invalid addresses into RAM or expose the mod heap.
inline std::uint32_t read_memory_bytes(const std::uint8_t* rdram, std::size_t rdram_size,
    std::uint32_t address, std::uint8_t* output, std::uint32_t requested) {
    const std::size_t available = std::min(memory_size, rdram_size & ~std::size_t(3));
    if (!rdram || !output || address >= available) return 0;
    const auto count = static_cast<std::uint32_t>(
        std::min<std::size_t>(requested, available - address));
    std::memcpy(output, rdram + address, count);
    return count;
}

// Both identities are checked from actual bytes. The persisted runtime ROM
// is the exact shipped widescreen patch of the supported cartridge revision.
// Unknown images are never mapped to a supported achievement set.
std::string identify_rom(std::span<const std::uint8_t> rom);
void game_initialized(std::span<const std::uint8_t> rom);

} // namespace wr64::achievements::native
