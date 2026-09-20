#pragma once

#include <atomic>
#include <cstdint>

namespace RT64 {
// The renderer publishes availability; the UI thread owns the HWND for the
// process lifetime. Hiding/closing Player 2 never destroys an in-use swapchain.
inline std::atomic<bool> wr64SeparateWindowsBackend{false};
inline std::atomic<bool> wr64SecondaryRaceActive{false};
inline std::atomic<uintptr_t> wr64SecondaryWindowHandle{0};
inline std::atomic<bool> wr64SecondaryWindowDrawable{false};
inline std::atomic<bool> wr64SecondaryWindowClosed{false};
inline std::atomic<bool> wr64SecondaryWindowFocused{false};

inline constexpr float Wr64SeparateWindowsAspect = 32.0f / 9.0f;
inline constexpr float Wr64SeparatePlayerAspect = 16.0f / 9.0f;
}
