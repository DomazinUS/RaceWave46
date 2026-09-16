#include "wr64_diagnostic_policy.h"
#include "wr64_window.hpp"
#include "wr64_app_icon.hpp"
#include "wr64_composer_window.hpp"
#include "wr64_forensic.h"
#include "wr64_frontend.hpp"
#include "wr64_input.hpp"
#include "wr64_game_rumble.hpp"
#include "wr64_controller_smoke.hpp"
#ifdef WR64_ENABLE_FRONTEND
#include "recompinput/recompinput.h"
#endif

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>

extern "C" float wr64_experimental_3d_aspect();

#if defined(_WIN32) || defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#ifdef WR64_ENABLE_RT64
// This host owns main(). Without SDL_MAIN_HANDLED, SDL.h rewrites `main` to
// `SDL_main` in every translation unit that includes it.
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_syswm.h>

// recompui/src/base/ui_state.cpp declares
//     extern SDL_Window* window;
// at global scope and dereferences it in init_hook() and get_window_size().
// This definition is that symbol. Nothing links recompui yet, so today it is
// simply the one place that owns the window pointer.
//
// CAREFUL: wr64::window below is also a NAMESPACE, so every reference to this
// variable from inside it must be spelled ::window - unqualified `window`
// finds the namespace first and fails to compile.
SDL_Window* window = nullptr;
#endif

namespace wr64::window {
namespace {

bool enabled = false;

#if defined(_WIN32) || defined(__CYGWIN__)
struct WindowState {
    HWND handle = nullptr;
    bool fullscreen = false;
    bool lock_aspect = false;
    float locked_client_aspect = 16.0f / 9.0f;
    RECT windowed_rect{};
    DWORD windowed_style = WS_OVERLAPPEDWINDOW;
};

// SDL stores its own SDL_WindowData pointer in GWLP_USERDATA for every window
// it creates. The window procedure below therefore must NOT touch
// GWLP_USERDATA - writing it would destroy SDL's pointer and crash SDL on the
// next message it handles. There is exactly one game window, so a file-static
// is both correct and simpler than the window word it replaces.
WindowState* window_state = nullptr;

#ifdef WR64_ENABLE_RT64
// The window procedure SDL installed, saved when the subclass below replaces
// it. Every message this file does not consume is forwarded to it.
WNDPROC sdl_window_proc = nullptr;
#ifndef WR64_ENABLE_FRONTEND
bool quit_requested = false;
#endif
#else
constexpr wchar_t kWindowClass[] = L"WaveRace64RecompiledWindow";
#endif

bool is_fullscreen() {
#ifdef WR64_ENABLE_RT64
    return (::window != nullptr) &&
        ((SDL_GetWindowFlags(::window) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0);
#else
    return (window_state != nullptr) && window_state->fullscreen;
#endif
}

void toggle_fullscreen(HWND handle) {
#ifdef WR64_ENABLE_RT64
    (void)handle;
#ifdef WR64_ENABLE_FRONTEND
    if (wr64::frontend::ready()) {
        wr64::frontend::toggle_fullscreen();
        return;
    }
#endif
    if (::window == nullptr) {
        return;
    }
    // SDL owns the window, so the borderless-fullscreen swap goes through SDL
    // rather than through GWL_STYLE directly - a hand-rolled style change
    // would leave SDL's own idea of the window state stale. This is also the
    // exact call recompui's graphics settings make, so the two agree by
    // construction rather than by luck.
    SDL_SetWindowFullscreen(
        ::window,
        is_fullscreen() ? 0u : static_cast<Uint32>(SDL_WINDOW_FULLSCREEN_DESKTOP));
#else
    auto* state = window_state;
    if (state == nullptr) {
        return;
    }

    if (!state->fullscreen) {
        state->windowed_style = static_cast<DWORD>(GetWindowLongPtrW(handle, GWL_STYLE));
        GetWindowRect(handle, &state->windowed_rect);

        MONITORINFO monitor{.cbSize = sizeof(MONITORINFO)};
        GetMonitorInfoW(MonitorFromWindow(handle, MONITOR_DEFAULTTONEAREST), &monitor);
        SetWindowLongPtrW(
            handle,
            GWL_STYLE,
            static_cast<LONG_PTR>((state->windowed_style & ~WS_OVERLAPPEDWINDOW) | WS_POPUP));
        SetWindowPos(
            handle,
            HWND_TOP,
            monitor.rcMonitor.left,
            monitor.rcMonitor.top,
            monitor.rcMonitor.right - monitor.rcMonitor.left,
            monitor.rcMonitor.bottom - monitor.rcMonitor.top,
            SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
        state->fullscreen = true;
    }
    else {
        SetWindowLongPtrW(handle, GWL_STYLE, static_cast<LONG_PTR>(state->windowed_style));
        SetWindowPos(
            handle,
            nullptr,
            state->windowed_rect.left,
            state->windowed_rect.top,
            state->windowed_rect.right - state->windowed_rect.left,
            state->windowed_rect.bottom - state->windowed_rect.top,
            SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);
        state->fullscreen = false;
    }
#endif
}

LRESULT CALLBACK window_proc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
        case WM_KEYDOWN:
#if WR64_DIAGNOSTIC_ENABLED
            if (wparam == VK_F8) {
                wr64_forensic_freeze_pause_export();
                return 0;
            }
            if (wparam == VK_F9) {
                wr64_forensic_resume_reset();
                return 0;
            }
            if ((wparam == VK_F10) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0)) {
                wr64::composer::toggle();
                return 0;
            }
#endif
            if (wparam == VK_F11) {
                toggle_fullscreen(handle);
                return 0;
            }
#ifdef WR64_ENABLE_FRONTEND
            if (wparam == VK_F1) {
                // RT64 owns F1 while developer mode is active. Its message
                // hook opens the native Inspector before this subclass sees
                // the key; do not also open the frontend settings overlay.
                if (ultramodern::renderer::get_graphics_config().developer_mode) {
                    break;
                }
                // Temporary. recompinput owns the menu toggle from stage 5,
                // where it becomes a rebindable input rather than a fixed key.
                wr64::frontend::toggle_settings();
                return 0;
            }
#endif
            break;
        case WM_SYSKEYDOWN:
            if ((wparam == VK_F10) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0)) {
                wr64::composer::toggle();
                return 0;
            }
            if (wparam == VK_RETURN && (lparam & (1LL << 29)) != 0) {
                toggle_fullscreen(handle);
                return 0;
            }
#ifdef WR64_ENABLE_RT64
            if (wparam == VK_F4 && (lparam & (1LL << 29)) != 0) {
                // Alt+F4. Today DefWindowProc turns this into WM_CLOSE. SDL
                // consumes WM_SYSKEYDOWN itself, so ask for the close here
                // rather than depending on SDL forwarding it.
                PostMessageW(handle, WM_CLOSE, 0, 0);
                return 0;
            }
#endif
            break;
        case WM_SIZING: {
            auto* state = window_state;
            if ((state == nullptr) || !state->lock_aspect || is_fullscreen() ||
                (state->locked_client_aspect <= 0.0f)) {
                break;
            }

            auto* proposed = reinterpret_cast<RECT*>(lparam);
            RECT currentWindow{};
            RECT currentClient{};
            GetWindowRect(handle, &currentWindow);
            GetClientRect(handle, &currentClient);
            const LONG nonClientWidth =
                (currentWindow.right - currentWindow.left) - (currentClient.right - currentClient.left);
            const LONG nonClientHeight =
                (currentWindow.bottom - currentWindow.top) - (currentClient.bottom - currentClient.top);

            LONG clientWidth = std::max<LONG>(1,
                (proposed->right - proposed->left) - nonClientWidth);
            LONG clientHeight = std::max<LONG>(1,
                (proposed->bottom - proposed->top) - nonClientHeight);

            const bool horizontalEdge = (wparam == WMSZ_LEFT) || (wparam == WMSZ_RIGHT);
            const bool verticalEdge = (wparam == WMSZ_TOP) || (wparam == WMSZ_BOTTOM);
            if (horizontalEdge) {
                clientHeight = std::max<LONG>(1,
                    static_cast<LONG>(std::lround(clientWidth / state->locked_client_aspect)));
            }
            else if (verticalEdge) {
                clientWidth = std::max<LONG>(1,
                    static_cast<LONG>(std::lround(clientHeight * state->locked_client_aspect)));
            }
            else if ((static_cast<float>(clientWidth) / static_cast<float>(clientHeight)) >
                state->locked_client_aspect) {
                clientHeight = std::max<LONG>(1,
                    static_cast<LONG>(std::lround(clientWidth / state->locked_client_aspect)));
            }
            else {
                clientWidth = std::max<LONG>(1,
                    static_cast<LONG>(std::lround(clientHeight * state->locked_client_aspect)));
            }

            const LONG outerWidth = clientWidth + nonClientWidth;
            const LONG outerHeight = clientHeight + nonClientHeight;
            const bool draggingLeft = (wparam == WMSZ_LEFT) ||
                (wparam == WMSZ_TOPLEFT) || (wparam == WMSZ_BOTTOMLEFT);
            const bool draggingTop = (wparam == WMSZ_TOP) ||
                (wparam == WMSZ_TOPLEFT) || (wparam == WMSZ_TOPRIGHT);
            if (draggingLeft) {
                proposed->left = proposed->right - outerWidth;
            }
            else {
                proposed->right = proposed->left + outerWidth;
            }
            if (draggingTop) {
                proposed->top = proposed->bottom - outerHeight;
            }
            else {
                proposed->bottom = proposed->top + outerHeight;
            }
            return TRUE;
        }
        case WM_ERASEBKGND:
            return 1;
#ifndef WR64_ENABLE_RT64
        case WM_CLOSE:
            DestroyWindow(handle);
            return 0;
        case WM_DESTROY:
            wr64_forensic_force_resume();
            wr64::composer::shutdown();
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT paint{};
            HDC dc = BeginPaint(handle, &paint);
            RECT client{};
            GetClientRect(handle, &client);
            HBRUSH background = CreateSolidBrush(RGB(4, 22, 42));
            FillRect(dc, &client, background);
            DeleteObject(background);

            SetBkMode(dc, TRANSPARENT);
            SetTextColor(dc, RGB(232, 244, 255));
            DrawTextW(
                dc,
                L"Wave Race 64: Recompiled\n\n"
                L"Native runtime is running.\n"
                L"RT64 rendering integration is the next gate.",
                -1,
                &client,
                DT_CENTER | DT_VCENTER | DT_WORDBREAK);
            EndPaint(handle, &paint);
            return 0;
        }
#endif
        default:
            break;
    }
#ifdef WR64_ENABLE_RT64
    if (sdl_window_proc != nullptr) {
        return CallWindowProcW(sdl_window_proc, handle, message, wparam, lparam);
    }
#endif
    return DefWindowProcW(handle, message, wparam, lparam);
}
#endif

} // namespace

void set_enabled(bool value) {
    enabled = value;
}

ultramodern::gfx_callbacks_t::gfx_data_t create_gfx() {
#if defined(_WIN32) || defined(__CYGWIN__)
    return new WindowState{};
#else
    return nullptr;
#endif
}

ultramodern::renderer::WindowHandle create_window(
    ultramodern::gfx_callbacks_t::gfx_data_t data) {
#if defined(_WIN32) || defined(__CYGWIN__)
    auto* state = static_cast<WindowState*>(data);
    window_state = state;
    if (enabled) {
        const float requested_aspect = wr64_experimental_3d_aspect();
        // Presentation now expands the world and preserves the HUD at the
        // current window aspect. A requested diagnostic ratio still locks the
        // test window; ordinary interactive resizing follows the live target.
        state->lock_aspect = requested_aspect > 0.0f;
        state->locked_client_aspect = (requested_aspect > 0.0f)
            ? requested_aspect
            : (16.0f / 9.0f);
        const LONG client_width = (requested_aspect > 2.0f) ? 1260 : 1280;
        const LONG client_height = (requested_aspect > 0.0f)
            ? static_cast<LONG>(std::lround(client_width / requested_aspect))
            : 720;

#ifdef WR64_ENABLE_RT64
        // Pin DPI behaviour to exactly what the raw Win32 window did. This
        // executable carries no DPI manifest, so it has always run DPI-unaware
        // and RT64 has always rendered at the unscaled client size. SDL can
        // change process DPI awareness on its own, which would silently change
        // the render resolution on a scaled display. Crisp high-DPI output is a
        // real setting and belongs in the graphics settings later, not as a
        // side effect of moving the window to SDL.
        SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "unaware");
        SDL_SetHint(SDL_HINT_WINDOWS_DPI_SCALING, "0");
        // The composer's pop-out is a separate top-level window on this same
        // thread, and SDL's pump is what dispatches its messages from here on.
        SDL_SetHint(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, "1");
        SDL_SetMainReady();

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::fprintf(stderr, "[window] SDL_Init(SDL_INIT_VIDEO) failed: %s\n", SDL_GetError());
            return {nullptr, GetCurrentThreadId()};
        }

        // SDL_CreateWindow takes the CLIENT size and does the
        // AdjustWindowRectEx itself. Handing it the outer size the old code
        // computed would make the window larger than it is today by exactly
        // the border and caption.
        Uint32 window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
#ifdef WR64_ENABLE_FRONTEND
        // configure() has already applied the startup mode. Use it at window
        // creation too, so the frontend never flashes a windowed frame first.
        if (ultramodern::renderer::get_graphics_config().wm_option ==
                ultramodern::renderer::WindowMode::Fullscreen) {
            window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
#endif
        ::window = SDL_CreateWindow(
            "Wave Race 64: Recompiled",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            static_cast<int>(client_width),
            static_cast<int>(client_height),
            window_flags);
        if (::window == nullptr) {
            std::fprintf(stderr, "[window] SDL_CreateWindow failed: %s\n", SDL_GetError());
            return {nullptr, GetCurrentThreadId()};
        }

        // RT64 has only ever wanted the HWND, and it still gets exactly that.
        SDL_SysWMinfo wm_info{};
        SDL_VERSION(&wm_info.version);
        if (SDL_GetWindowWMInfo(::window, &wm_info) != SDL_TRUE) {
            std::fprintf(stderr, "[window] SDL_GetWindowWMInfo failed: %s\n", SDL_GetError());
            return {nullptr, GetCurrentThreadId()};
        }
        state->handle = wm_info.info.win.window;

        // Subclass AFTER SDL_CreateWindow, so SDL has finished installing its
        // own procedure and its own window data first.
        //
        // SDL2 has no WM_SIZING equivalent and no aspect-ratio API at all, so
        // the aspect lock keeps the proven Win32 arithmetic and reaches it
        // through this subclass instead of being reimplemented against a
        // different set of events.
        SetLastError(0);
        sdl_window_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(
            state->handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(window_proc)));
        if (sdl_window_proc == nullptr) {
            std::fprintf(
                stderr,
                "[window] SetWindowLongPtrW(GWLP_WNDPROC) failed: %lu - the aspect lock, "
                "F8/F9, Ctrl+F10 and F11 are not installed\n",
                GetLastError());
        }
#else
        HINSTANCE instance = GetModuleHandleW(nullptr);
        WNDCLASSEXW window_class{
            .cbSize = sizeof(WNDCLASSEXW),
            .style = CS_HREDRAW | CS_VREDRAW,
            .lpfnWndProc = window_proc,
            .hInstance = instance,
            .hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(32512)),
            .lpszClassName = kWindowClass,
        };
        RegisterClassExW(&window_class);

        constexpr DWORD window_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
        RECT window_rect{0, 0, client_width, client_height};
        AdjustWindowRectEx(&window_rect, window_style, FALSE, 0);

        state->handle = CreateWindowExW(
            0,
            kWindowClass,
            L"Wave Race 64: Recompiled",
            window_style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            window_rect.right - window_rect.left,
            window_rect.bottom - window_rect.top,
            nullptr,
            nullptr,
            instance,
            state);
        if (state->handle == nullptr) {
            std::fprintf(stderr, "[window] CreateWindowExW failed: %lu\n", GetLastError());
        }
#endif

        if (state->handle != nullptr) {
            wr64::window::apply_app_icon(state->handle);
            RECT client{};
            GetClientRect(state->handle, &client);
            WR64_DIAGNOSTIC_LOG(std::fprintf(
                stderr,
                "[window] client size: %ldx%ld (resizable%s)\n",
                client.right - client.left,
                client.bottom - client.top,
                state->lock_aspect ? ", aspect locked" : ""));
            wr64::composer::initialize(state->handle);
        }
    }

#if defined(_WIN32)
    return {state->handle, GetCurrentThreadId()};
#else
    return reinterpret_cast<ultramodern::renderer::WindowHandle>(state->handle);
#endif
#else
    (void)data;
    return reinterpret_cast<ultramodern::renderer::WindowHandle>(1);
#endif
}

void update_gfx(ultramodern::gfx_callbacks_t::gfx_data_t data) {
#if defined(_WIN32) || defined(__CYGWIN__)
    auto* state = static_cast<WindowState*>(data);
    update_secondary_window(state->handle);
#ifdef WR64_ENABLE_RT64
    // SDL_PollEvent pumps the Win32 message queue for EVERY window owned by
    // this thread - internally it is PeekMessage with a null HWND, exactly like
    // the loop it replaces. So the subclass above still receives F8, F9,
    // Ctrl+F10, F11 and WM_SIZING, and the composer's pop-out window still gets
    // its own messages. This REPLACES the hand-written pump rather than sitting
    // beside it; two PeekMessage loops would steal messages from each other.
    //
    // WM_QUIT is no longer the quit signal. SDL answers WM_CLOSE with
    // SDL_WINDOWEVENT_CLOSE and SDL_QUIT and never calls PostQuitMessage, so
    // both are handled here and the close button, Alt+F4 and a quit request
    // all reach the same teardown whichever one SDL delivers first.
#ifdef WR64_ENABLE_FRONTEND
    // recompinput::handle_events() OWNS SDL_PollEvent from here on. It is not
    // optional and it cannot be shared: a second SDL_PollEvent loop would steal
    // events from it at random. Everything the old loop did now happens inside
    // it - the UI's events, controller hotplug and player assignment.
    //
    // Except the quit. pump() takes SDL_QUIT for itself before handing the rest
    // to recompinput, because recompinput would raise a confirmation prompt.
    // The close button closes.
    //
    // The forensic and composer teardown moved to main(), after recomp::start
    // returns. That is where it always belonged; it only lived here because this
    // loop used to be the one place that saw the window close.
    wr64_controller_smoke_update();
    wr64::frontend::pump();
    if (recompinput::game_input_disabled()) wr64_game_rumble_reset();
    wr64_game_rumble_update();
    wr64::input::update_rumble();
#else
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        const bool close_requested =
            (event.type == SDL_QUIT) ||
            ((event.type == SDL_WINDOWEVENT) &&
             (event.window.event == SDL_WINDOWEVENT_CLOSE) &&
             (::window != nullptr) &&
             (event.window.windowID == SDL_GetWindowID(::window)));
        if (close_requested && !quit_requested) {
            quit_requested = true;
            wr64_forensic_force_resume();
            wr64::composer::shutdown();
            ultramodern::quit();
        }
    }
#endif
#else
    MSG message{};
    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
        if (message.message == WM_QUIT) {
            ultramodern::quit();
            return;
        }
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
#endif
    wr64::composer::update();

    if (state->handle != nullptr) {
#ifndef WR64_ENABLE_RT64
        InvalidateRect(state->handle, nullptr, FALSE);
#endif
    }
#else
    (void)data;
#endif
}

} // namespace wr64::window
