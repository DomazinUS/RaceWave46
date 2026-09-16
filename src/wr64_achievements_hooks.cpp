#include "wr64_achievements_native.hpp"
#include "wr64_achievements.hpp"

#include <cstdio>
#include <string_view>

#include "rc_consoles.h"
#include "rc_hash.h"

namespace wr64::achievements::native {

std::string identify_rom(std::span<const std::uint8_t> rom) {
    // select_rom normalizes byte order before applying our patch and pads the
    // resulting file to a whole word. Include that exact persisted padding.
    constexpr std::size_t original_size = 8388608;
    constexpr std::size_t patched_size = 8572592;
    constexpr std::string_view patched_hash = "003acf892c9569b8691dc1ca73f6c4de";
    if (rom.size() != original_size && rom.size() != patched_size) return {};
    char hash[33]{};
    if (!rc_hash_generate_from_buffer(hash, RC_CONSOLE_NINTENDO_64, rom.data(), rom.size())) return {};
    if ((rom.size() == original_size && std::string_view(hash) == original_rom_hash) ||
        (rom.size() == patched_size && std::string_view(hash) == patched_hash))
        return original_rom_hash;
    return {};
}

void game_initialized(std::span<const std::uint8_t> rom) {
    const auto identity = identify_rom(rom);
    set_game_identity(identity);
    if (identity.empty())
        std::fprintf(stderr, "[achievements] Game identity is unsupported; achievement processing is unavailable.\n");
}

} // namespace wr64::achievements::native

// Invoked by the native scheduler's VI-message branch, not the asynchronous
// host VI callback or an interpolated presentation. Guest RAM is stable here.
extern "C" void wr64_achievements_native_frame(std::uint8_t* rdram) {
    wr64::achievements::native_frame(rdram);
}
