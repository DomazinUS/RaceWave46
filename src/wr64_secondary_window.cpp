#include "wr64_secondary_window.hpp"
#include "wr64_app_icon.hpp"
#include "../lib/rt64/src/common/rt64_wr64_separate_windows.h"

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <cstdio>

namespace wr64::window {
namespace {
constexpr wchar_t kSecondaryClass[] = L"WaveRace64RecompiledPlayer2";
struct SecondaryWindow {
    HWND handle = nullptr;
    bool race_active = false;
    bool attempted_creation = false;
    bool fullscreen = false;
    RECT windowed_rect{};
    LONG_PTR windowed_style = WS_OVERLAPPEDWINDOW;
} secondary;

bool active_race() {
    return RT64::wr64SeparateWindowsBackend.load() &&
        RT64::wr64SecondaryRaceActive.load();
}

void publish_window_state(HWND handle) {
    const bool drawable = handle && IsWindowVisible(handle) && !IsIconic(handle) &&
        !RT64::wr64SecondaryWindowClosed.load();
    RT64::wr64SecondaryWindowDrawable.store(drawable);
    RT64::wr64SecondaryWindowFocused.store(drawable && active_race() &&
        GetForegroundWindow() == handle);
}

void toggle_secondary_fullscreen(HWND handle) {
    if (!secondary.fullscreen) {
        MONITORINFO monitor{};
        monitor.cbSize = sizeof(monitor);
        if (!GetMonitorInfoW(MonitorFromWindow(handle, MONITOR_DEFAULTTONEAREST), &monitor)) return;
        secondary.windowed_style = GetWindowLongPtrW(handle, GWL_STYLE);
        GetWindowRect(handle, &secondary.windowed_rect);
        SetWindowLongPtrW(handle, GWL_STYLE,
            (secondary.windowed_style & ~LONG_PTR(WS_OVERLAPPEDWINDOW)) | WS_POPUP);
        SetWindowPos(handle, HWND_TOP, monitor.rcMonitor.left, monitor.rcMonitor.top,
            monitor.rcMonitor.right - monitor.rcMonitor.left,
            monitor.rcMonitor.bottom - monitor.rcMonitor.top,
            SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
        secondary.fullscreen = true;
    }
    else {
        SetWindowLongPtrW(handle, GWL_STYLE, secondary.windowed_style);
        const RECT& rect = secondary.windowed_rect;
        SetWindowPos(handle, nullptr, rect.left, rect.top, rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);
        secondary.fullscreen = false;
    }
}

LRESULT CALLBACK secondary_window_proc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case WM_CLOSE:
        // The swapchain can still reference this HWND. Close only hides it and
        // suppresses reopening until presentation leaves the current race.
        RT64::wr64SecondaryWindowClosed.store(true);
        RT64::wr64SecondaryWindowDrawable.store(false);
        RT64::wr64SecondaryWindowFocused.store(false);
        ShowWindow(handle, SW_HIDE);
        return 0;
    case WM_KEYDOWN:
        if (wparam == VK_F11) {
            if ((lparam & (LPARAM(1) << 30)) == 0) toggle_secondary_fullscreen(handle);
            return 0;
        }
        break;
    case WM_SYSKEYDOWN:
        if (wparam == VK_RETURN && (lparam & (LPARAM(1) << 29))) {
            if ((lparam & (LPARAM(1) << 30)) == 0) toggle_secondary_fullscreen(handle);
            return 0;
        }
        break;
    case WM_ACTIVATE:
        if (LOWORD(wparam) == WA_INACTIVE) {
            RT64::wr64SecondaryWindowFocused.store(false);
        }
        else {
            RT64::wr64SecondaryWindowFocused.store(active_race() &&
                !RT64::wr64SecondaryWindowClosed.load() && !IsIconic(handle));
        }
        break;
    case WM_SIZE:
        if (wparam == SIZE_MINIMIZED) {
            RT64::wr64SecondaryWindowDrawable.store(false);
            RT64::wr64SecondaryWindowFocused.store(false);
        }
        else {
            publish_window_state(handle);
        }
        break;
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT: {
        PAINTSTRUCT paint{};
        HDC dc = BeginPaint(handle, &paint);
        if (!active_race()) {
            FillRect(dc, &paint.rcPaint, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        }
        EndPaint(handle, &paint);
        return 0;
    }
    default:
        break;
    }
    // This is a raw Win32 window: its keyboard, resize and close messages do
    // not become SDL events for the primary UI, and it never posts WM_QUIT.
    return DefWindowProcW(handle, message, wparam, lparam);
}

HWND create_secondary_window(HWND primary) {
    HINSTANCE instance = GetModuleHandleW(nullptr);
    WNDCLASSEXW window_class{};
    window_class.cbSize = sizeof(window_class);
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = secondary_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(32512));
    window_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    window_class.lpszClassName = kSecondaryClass;
    if (!RegisterClassExW(&window_class) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) return nullptr;

    RECT client{};
    GetClientRect(primary, &client);
    LONG width = client.right - client.left;
    if (width < 640) width = 640;
    if (width > 1280) width = 1280;
    RECT rect{0, 0, width, (width * 9) / 16};
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);
    return CreateWindowExW(0, kSecondaryClass, L"Wave Race 64: Recompiled - Player 2",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        nullptr, nullptr, instance, nullptr);
}
}

void update_secondary_window(void* primary_handle) {
    const bool active = primary_handle && active_race();
    if (active && !secondary.race_active) {
        RT64::wr64SecondaryWindowClosed.store(false);
        secondary.attempted_creation = false;
        if (secondary.handle) ShowWindow(secondary.handle, SW_SHOWNOACTIVATE);
    }
    if (active && !secondary.handle && !secondary.attempted_creation) {
        secondary.attempted_creation = true;
        secondary.handle = create_secondary_window(static_cast<HWND>(primary_handle));
        if (secondary.handle) {
            apply_app_icon(secondary.handle);
            RT64::wr64SecondaryWindowHandle.store(reinterpret_cast<uintptr_t>(secondary.handle));
            ShowWindow(secondary.handle, SW_SHOWNOACTIVATE);
        }
        else {
            std::fprintf(stderr, "[window] Could not create Player 2 window: %lu\n", GetLastError());
        }
    }
    if (secondary.handle && secondary.race_active && !active) {
        // Clear the last race immediately; presentation also clears its second
        // swapchain between races. Keep position, size and fullscreen state.
        InvalidateRect(secondary.handle, nullptr, FALSE);
    }
    secondary.race_active = active;
    publish_window_state(secondary.handle);
}
}
#else
namespace wr64::window {
void update_secondary_window(void*) {}
}
#endif
