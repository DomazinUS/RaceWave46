#include "wr64_sunny_animals_load.hpp"
#include "wr64_sunny_detail.hpp"
#include <cstdio>
#include <cstring>

namespace {
template<class T> T read(const uint8_t* rdram, uint32_t address) {
    T value;
    std::memcpy(&value, rdram + ((address & 0x7FFFFFU) ^ (sizeof(T) == 2 ? 2U : 0U)), sizeof(value));
    return value;
}

bool residentAnimals(const uint8_t* rdram) {
    // Native 2P loads each course's animal banks even though it skips actor
    // creation. Validate those actual parsed banks; never substitute Sunny's
    // model addresses or require animation data for a static model bank.
    // Course IDs and layouts come from the native 93A54/9684C/96048 path.
    constexpr int8_t courseBanks[9][2] = {
        {0, 2}, {3, 2}, {0, -1}, {3, -1}, {6, 4},
        {7, -1}, {-1, -1}, {1, 3}, {8, -1}
    };
    struct Bank {
        uint32_t bytes, animationOffset, parts;
        uint32_t roots[9];
    };
    constexpr Bank banks[] = {
        {0xC21C, 0xC1FC, 6, {0x2810, 0x2EF0, 0x31A8, 0x2E60, 0x2AB8, 0x3008}},
        {0x30F8, 0x30EC, 4, {0x1070, 0x1460, 0x1658, 0x1770}},
        {0x3580, 0x3578, 9, {0x2A40, 0x2AC0, 0x2B40, 0x2BC0, 0x2C40, 0x2CC0, 0x2D40, 0x2DC0, 0x2E40}},
        {0x2FAC, 0x2FA8, 5, {0x17F0, 0x19B8, 0x1A38, 0x1AB8, 0x1B38}},
        {0x0DA0, 0x0D9C, 3, {0x08C0, 0x0940, 0x09C0}},
        {0x0D58, 0, 1, {0x0C80}},
        {0x2C04, 0x2C00, 5, {0x2050, 0x2348, 0x23C8, 0x2448, 0x24C8}},
        {0x6C68, 0, 3, {0x6560, 0x6470, 0x64E8}},
        {0x1C60, 0x1C58, 4, {0x1230, 0x0F50, 0x1170, 0x10E0}}
    };
    const auto course = read<uint32_t>(rdram, 0x800D8170);
    if (course > 8) return false;
    const auto segment8 = read<uint32_t>(rdram, 0x801CE6D0) & 0x1FFFFFFFU;
    if (segment8 == 0 || segment8 >= 0x800000U) return false;
    uint32_t offset = 0x60000;
    for (uint32_t slot = 0; slot < 2; ++slot) {
        const int32_t expected = courseBanks[course][slot];
        const uint32_t descriptor = 0x801CE7D8 + slot * 8;
        if (read<int32_t>(rdram, descriptor) != expected ||
            read<uint32_t>(rdram, descriptor + 4) != 0x08000000U + offset) return false;
        if (expected < 0) continue;
        const Bank& bank = banks[expected];
        if (offset > 0x800000U - segment8 || bank.bytes > 0x800000U - segment8 - offset) return false;
        const uint32_t record = 0x801CE780 + slot * 0x2C;
        if (read<uint16_t>(rdram, 0x801CE768 + expected * 2) != slot ||
            read<uint32_t>(rdram, record) != bank.parts) return false;
        // record+4 is a relocated animation-table pointer, not its count.
        if (bank.animationOffset && read<uint32_t>(rdram, record + 4) !=
                0x80000000U + segment8 + offset + bank.animationOffset) return false;
        for (uint32_t part = 0; part < bank.parts; ++part)
            if (read<uint32_t>(rdram, record + 8 + part * 4) !=
                    0x08000000U + offset + bank.roots[part]) return false;
        offset = (offset + bank.bytes + 0x3F) & ~0x3FU;
    }
    return true;
}
}

extern "C" uint32_t wr64_sunny_animals_ready(uint8_t* rdram) {
    return rdram && wr64_sunny_detail_active(rdram) && residentAnimals(rdram);
}

extern "C" uint32_t wr64_sunny_animals_init_players(uint8_t* rdram, uint32_t original) {
    // Change only the initializer's local player-count comparison. Each course
    // then creates its own native roster. Global players, both racers and the
    // shared update frequency remain native; behavior remains P1-authoritative.
    if (original != 2 || !rdram || !wr64_sunny_detail_active(rdram)) return original;
    const bool ready = residentAnimals(rdram);
    char line[192];
    std::snprintf(line, sizeof(line),
        "animals-init ready=%d bank_ids=%u,%u animation_tables=%08X,%08X",
        int(ready), read<uint32_t>(rdram, 0x801CE7D8), read<uint32_t>(rdram, 0x801CE7E0),
        read<uint32_t>(rdram, 0x801CE784), read<uint32_t>(rdram, 0x801CE7B0));
    wr64::sunny_detail::note_diagnostic(line);
    return ready ? 1 : original;
}
