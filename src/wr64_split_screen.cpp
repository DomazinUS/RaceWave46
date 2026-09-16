#include "wr64_split_screen.hpp"
#include "wr64_input.hpp"
#include "common/rt64_wr64_split_marker.h"
#include "common/rt64_wr64_separate_windows.h"
#include <atomic>
#include <cstring>

namespace {
std::atomic<uint32_t> selectedLayout{0};
thread_local bool nativeVerticalFrame = false;
thread_local bool nativePauseOpen = false;
thread_local bool nativeLapOpen = false;
template<class T> T read(const uint8_t* rdram, uint32_t address) {
    T result;
    const uint32_t offset = (address & 0x7FFFFFU) ^ (sizeof(T) == 2 ? 2U : 0U);
    std::memcpy(&result, rdram + offset, sizeof(T));
    return result;
}
}
namespace wr64::split_screen {
void set_mode(uint32_t value) { selectedLayout.store(value <= 2 ? value : 0, std::memory_order_relaxed); }
uint32_t mode() { return selectedLayout.load(std::memory_order_relaxed); }
void set_vertical(bool enabled) { set_mode(enabled ? 1U : 0U); }
bool separate_windows() { return mode() == 2 && RT64::wr64SeparateWindowsBackend.load(std::memory_order_acquire); }
bool vertical() { return mode() == 1 || separate_windows(); }
}

extern "C" uint32_t wr64_split_screen_frame(uint8_t* rdram, uint32_t cursor) {
    nativeVerticalFrame = false;
    nativePauseOpen = false;
    nativeLapOpen = false;
    if (!rdram) return cursor;
    const int players = read<int32_t>(rdram, 0x800DAB28);
    wr64::input::set_multiplayer_enabled(players == 2);
    const int state = read<int32_t>(rdram, 0x801CE638);
    const int mode = read<int32_t>(rdram, 0x800DAB24);
    // Gate and marker share one settings snapshot for this native frame.
    const uint32_t layout = wr64::split_screen::mode();
    const bool separate = layout == 2 && RT64::wr64SeparateWindowsBackend.load(std::memory_order_acquire);
    if ((layout != 1 && !separate) || players != 2 || state != 1 || mode < 40 || mode > 45)
        return cursor;

    // The native display-list pool has a fixed 24 KiB capacity. Leave the
    // existing tail reserve intact and reject malformed/unexpected cursors.
    const uint32_t pool = read<uint32_t>(rdram, 0x801518B8);
    constexpr uint32_t poolBytes = 0x6000, reserve = 0x800;
    if ((pool & 0xE0000007U) != 0x80000000U || (pool & 0x1FFFFFFFU) > 0x800000U - poolBytes ||
        (cursor & 7U) || cursor < pool || cursor - pool > poolBytes - reserve - 8)
        return cursor;
    const int pause = read<int16_t>(rdram, 0x801CE624);
    const int owner = read<int16_t>(rdram, 0x801CE62C);
    const uint32_t pauseOwner = pause >= 0 && (owner == 1 || owner == 2) ? uint32_t(owner) : 0;
    const uint32_t words[]{separate ? RT64::Wr64SeparateWindowsMarker : RT64::Wr64SplitMarker,
        RT64::Wr64SplitVersion | pauseOwner};
    std::memcpy(rdram + (cursor & 0x7FFFFFU), words, sizeof(words));
    nativeVerticalFrame = true;
    return cursor + 8;
}

extern "C" uint32_t wr64_split_screen_pause(uint8_t* rdram, uint32_t cursor, int begin) {
    if (!rdram || (!nativeVerticalFrame && !nativePauseOpen)) return cursor;
    const uint32_t pool = read<uint32_t>(rdram, 0x801518B8);
    if ((pool & 0xE0000007U) != 0x80000000U || (pool & 0x1FFFFFFFU) > 0x800000U - 0x6000 ||
        (cursor & 7U) || cursor < pool || cursor - pool > 0x6000U - (begin ? 0x800U : 8U))
        return cursor;
    uint32_t owner = 0;
    if (begin) {
        const int value = read<int16_t>(rdram, 0x801CE62C);
        if (value != 1 && value != 2) return cursor;
        owner = uint32_t(value);
        nativePauseOpen = true;
    } else {
        if (!nativePauseOpen) return cursor;
        nativePauseOpen = false;
    }
    const uint32_t words[]{RT64::Wr64SplitPauseMarker, RT64::Wr64SplitVersion | owner};
    std::memcpy(rdram + (cursor & 0x7FFFFFU), words, sizeof(words));
    return cursor + 8;
}

extern "C" uint32_t wr64_split_screen_lap(uint8_t* rdram, uint32_t cursor, int owner) {
    if (!rdram || owner < 0 || owner > 2 || (!nativeVerticalFrame && !nativeLapOpen)) return cursor;
    if (owner == 0 && !nativeLapOpen) return cursor;
    const uint32_t pool = read<uint32_t>(rdram, 0x801518B8);
    if ((pool & 0xE0000007U) != 0x80000000U || (pool & 0x1FFFFFFFU) > 0x800000U - 0x6000 ||
        (cursor & 7U) || cursor < pool || cursor - pool > 0x6000U - (owner ? 0x800U : 8U)) return cursor;
    const uint32_t words[]{RT64::Wr64SplitLapMarker, RT64::Wr64SplitVersion | uint32_t(owner)};
    std::memcpy(rdram + (cursor & 0x7FFFFFU), words, sizeof(words));
    nativeLapOpen = owner != 0;
    return cursor + 8;
}
