#include "wr64_sunny_detail.hpp"
#include "wr64_free_ride_menu.hpp"
#include <atomic>
#include <cstdint>
#include <cstring>

namespace {
std::atomic<bool> requested{true};
template<class T> T read(const uint8_t* ram, uint32_t address) {
    T value;
    std::memcpy(&value, ram + ((address & 0x7FFFFFu) ^ (sizeof(T) == 2 ? 2u : 0u)), sizeof(value));
    return value;
}
template<class T> void write(uint8_t* ram, uint32_t address, T value) {
    std::memcpy(ram + ((address & 0x7FFFFFu) ^ (sizeof(T) == 2 ? 2u : 0u)), &value, sizeof(value));
}
bool menuContext(const uint8_t* ram) {
    return ram && read<int32_t>(ram, 0x801CE638) == 5 &&
        read<int32_t>(ram, 0x801CE608) == 1 &&
        read<int16_t>(ram, 0x801CE60C) == 2;
}
bool eligible(const uint8_t* ram) {
    return requested.load(std::memory_order_relaxed) && menuContext(ram) &&
        wr64_dolphin_free_ride_available(ram);
}
void unlock(uint8_t* ram) {
    write<int32_t>(ram, 0x802C7558, 1);
    for (uint32_t difficulty = 0; difficulty < 4; ++difficulty)
        write<int32_t>(ram, 0x802C757C + difficulty * 4, difficulty == 0 ? 1 : 0);
    write<int32_t>(ram, 0x802C76A4, 0);
}
}

namespace wr64::free_ride {
void set_enabled(bool value) { requested.store(value, std::memory_order_relaxed); }
bool enabled() { return requested.load(std::memory_order_relaxed); }
}

// Native Course Select has just rebuilt availability and the navigation range.
// Unlock only its unused Dolphin row, after authenticating the actual ROM data.
extern "C" void wr64_free_ride_course_menu(uint8_t* ram) {
    if (!eligible(ram)) return;
    unlock(ram);
}

// Course input resumes after the settings overlay closes. Refresh before it
// handles confirmation so disabling a highlighted Dolphin cannot enter it.
extern "C" void wr64_free_ride_course_refresh(uint8_t* ram) {
    if (!menuContext(ram)) return;
    if (eligible(ram)) {
        unlock(ram);
        return;
    }
    write<int32_t>(ram, 0x802C7558, 0);
    write<int32_t>(ram, 0x802C76A4, 1);
    if (read<int32_t>(ram, 0x800DA9D0) == 0) write<int32_t>(ram, 0x800DA9D0, 1);
}

// Reuse the native direct-confirm branch, without changing the VS game kind.
// Free Ride has no difficulty/reverse choice; other courses keep those menus.
extern "C" uint32_t wr64_free_ride_course_confirm(uint8_t* ram) {
    // Use the availability sampled by this frame's input-entry hook. A settings
    // callback on the UI thread must not split one native confirmation between
    // the unlocked Free Ride branch and the normal difficulty branch.
    if (!menuContext(ram) || read<int32_t>(ram, 0x802C7558) != 1 ||
        !wr64_dolphin_free_ride_available(ram)) return 0;
    const auto selection = read<uint32_t>(ram, 0x800DA9D0);
    if (selection >= 9 || read<uint32_t>(ram, 0x800DAAD8 + selection * 4) != 0) return 0;
    write<int32_t>(ram, 0x801CB338, 0);
    write<int16_t>(ram, 0x800DAB68, 0);
    write<int32_t>(ram, 0x801CE61C, 1);
    return 1;
}
