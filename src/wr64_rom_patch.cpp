#include "wr64_rom_patch.hpp"

#include <cstddef>
#include <cstdio>

#include "wr64_rom_patch_data.h"

namespace {

// The cartridge image this patch applies to: Wave Race 64 (USA, Rev 1),
// 8 MiB, big-endian. The size is checked first because it is free, and the
// fingerprint second. Both are of the image AFTER the caller has normalised
// byte order, which is the only form that reaches here.
constexpr std::size_t kUnpatchedSize = 8388608u;
constexpr std::uint64_t kUnpatchedFingerprint = 0xAC96EB2872AD977DULL;

// FNV-1a, 64-bit. Deliberately self-contained: this file must not drag a hash
// library into the host layer for one comparison, and the REAL guarantee is
// the caller's own hash of the finished image - if this fingerprint ever
// matched something that is not the cartridge image, the patched result would
// fail that check and the ROM would be rejected exactly as an unknown one is.
std::uint64_t fingerprint(const std::vector<std::uint8_t> &data) {
    std::uint64_t hash = 0xCBF29CE484222325ULL;
    for (const std::uint8_t byte : data) {
        hash ^= byte;
        hash *= 0x100000001B3ULL;
    }
    return hash;
}

// IPS, the format the widescreen patch ships in: a "PATCH" magic, then records
// of a 24-bit big-endian offset and a 16-bit big-endian length followed by that
// many bytes, until the "EOF" marker. A zero length introduces a run-length
// record instead - a 16-bit count and one byte to repeat. Records may write
// past the end of the image, which is how the patch appends its 179 KiB of
// re-authored art.
bool apply_ips(const unsigned char *patch, std::size_t patch_size,
               std::vector<std::uint8_t> &rom) {
    if ((patch_size < 8u) || (patch[0] != 'P') || (patch[1] != 'A') ||
        (patch[2] != 'T') || (patch[3] != 'C') || (patch[4] != 'H')) {
        return false;
    }

    std::size_t pos = 5u;
    while (true) {
        // The end marker is three bytes; a record needs five to exist at all.
        if ((pos + 3u) > patch_size) {
            return false;
        }
        if ((patch[pos] == 'E') && (patch[pos + 1] == 'O') && (patch[pos + 2] == 'F')) {
            return true;
        }
        if ((pos + 5u) > patch_size) {
            return false;
        }

        const std::size_t offset = (std::size_t(patch[pos]) << 16) |
                                   (std::size_t(patch[pos + 1]) << 8) |
                                   std::size_t(patch[pos + 2]);
        const std::size_t length = (std::size_t(patch[pos + 3]) << 8) |
                                   std::size_t(patch[pos + 4]);
        pos += 5u;

        std::size_t count = length;
        std::uint8_t fill = 0u;
        const unsigned char *source = nullptr;

        if (length == 0u) {
            if ((pos + 3u) > patch_size) {
                return false;
            }
            count = (std::size_t(patch[pos]) << 8) | std::size_t(patch[pos + 1]);
            fill = std::uint8_t(patch[pos + 2]);
            pos += 3u;
        }
        else {
            if ((pos + length) > patch_size) {
                return false;
            }
            source = patch + pos;
            pos += length;
        }

        if ((offset + count) > rom.size()) {
            rom.resize(offset + count, 0u);
        }
        if (source != nullptr) {
            for (std::size_t i = 0; i < count; i++) {
                rom[offset + i] = std::uint8_t(source[i]);
            }
        }
        else {
            for (std::size_t i = 0; i < count; i++) {
                rom[offset + i] = fill;
            }
        }
    }
}

}  // namespace

namespace wr64::rom_patch {

bool apply_if_unpatched(std::vector<std::uint8_t> &rom) {
    if (rom.size() != kUnpatchedSize) {
        return false;
    }
    if (fingerprint(rom) != kUnpatchedFingerprint) {
        return false;
    }

    // Work on a copy: a patch that turns out to be malformed must not leave a
    // half-written image behind for the caller to hash.
    std::vector<std::uint8_t> patched = rom;
    if (!apply_ips(reinterpret_cast<const unsigned char *>(wr64_rom_patch_ips),
                   sizeof(wr64_rom_patch_ips), patched)) {
        return false;
    }

    rom = std::move(patched);
    std::printf("[rom] widescreen patch applied to the cartridge image\n");
    return true;
}

}  // namespace wr64::rom_patch
