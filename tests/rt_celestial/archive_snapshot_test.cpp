#include "common/rt64_wr64_rt_celestial.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: wr64_rt_celestial_archive_test <rdram.bin> <raw segment1> <raw segment8>\n";
        return 2;
    }
    std::ifstream file(argv[1], std::ios::binary);
    const std::vector<uint8_t> ram((std::istreambuf_iterator<char>(file)), {});
    if (ram.size() != 0x800000) {
        std::cerr << "Archive must contain exactly eight MiB of word-swapped RDRAM.\n";
        return 2;
    }
    auto word = [&](uint32_t address) {
        uint32_t value = 0;
        std::memcpy(&value, ram.data() + (address & 0x7fffff), sizeof(value));
        return value;
    };
    std::array<uint32_t, 16> nativeSegments{};
    for (uint32_t i = 0; i < 16; i++) { nativeSegments[i] = word(0x801CE6B0 + i * 4); }
    auto rawSegments = nativeSegments;
    try {
        for (uint32_t i = 0; i < 2; i++) {
            size_t end = 0;
            const std::string text(argv[2 + i]);
            const unsigned long long value = std::stoull(text, &end, 0);
            if (end != text.size() || value > UINT32_MAX) { throw std::invalid_argument("raw segment"); }
            rawSegments[i == 0 ? 1 : 8] = uint32_t(value);
        }
    }
    catch (const std::exception &) {
        std::cerr << "Raw segment arguments must be uint32 addresses.\n";
        return 2;
    }
    const uint32_t course = word(0x800D8170), players = word(0x800DAB28);
    const uint32_t expected = course == 0 ? 1 : course == 2 ? 2 : course == 6 ? 18 : 0;
    if (expected == 0 || players != 1) {
        std::cerr << "Archive is outside native one-player celestial scope.\n";
        return 2;
    }
    // Input addresses come from the archive's actual RSP commands. The native
    // CPU table independently identifies the corresponding physical asset base.
    for (uint32_t segment : { 1U, 8U }) {
        if ((rawSegments[segment] & 0xffffff) != (nativeSegments[segment] & 0xffffff)) {
            std::cerr << "Raw binding does not match this archive's native asset table.\n";
            return 1;
        }
    }
    const auto native = RT64::wr64RTCelestialReadSnapshot(ram.data(), ram.size(), nativeSegments, course, players);
    const auto raw = RT64::wr64RTCelestialReadSnapshot(ram.data(), ram.size(), rawSegments, course, players);
    if (native.count != expected || raw.count != expected || native.alphaWords != raw.alphaWords) {
        std::cerr << "FAIL course=" << course << " expected=" << expected << " native_table="
            << native.count << " raw_rsp=" << raw.count << '\n';
        return 1;
    }
    unsigned alphaChecks = 0;
    for (const auto &slot : std::array<std::array<uint32_t, 4>, 3>{ {
        {8,0x4400,1024,0}, {8,0x4C00,1024,1024}, {1,0x102B0,16,2048} } }) {
        if ((slot[3] == 1024 && course != 2) || (slot[3] == 2048 && course != 6)) { continue; }
        const uint64_t address = uint64_t(nativeSegments[slot[0]] & 0xffffff) + slot[1];
        if (address + slot[2] * 2 > ram.size()) { return 1; }
        for (uint32_t i = 0; i < slot[2]; i++) {
            const uint8_t actual = uint8_t(raw.alphaWords[(slot[3] + i) / 4] >> (((slot[3] + i) % 4) * 8));
            const uint8_t expectedAlpha = ram[(size_t(address) + i * 2 + 1) ^ 3];
            if (actual != expectedAlpha) { std::cerr << "Native alpha mismatch.\n"; return 1; }
            alphaChecks++;
        }
    }
    std::cout << "PASS archived course=" << course << " native_table=" << native.count
        << " raw_rsp=" << raw.count << " raw_segment8=0x" << std::hex << rawSegments[8] << std::dec
        << " exact_native_alpha_checks=" << alphaChecks << " input=" << argv[1] << '\n';
}
