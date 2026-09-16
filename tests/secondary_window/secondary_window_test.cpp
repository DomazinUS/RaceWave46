#include <windows.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace fake {
HWND primary = reinterpret_cast<HWND>(uintptr_t(1));
HWND player2 = reinterpret_cast<HWND>(uintptr_t(2));
HWND other = reinterpret_cast<HWND>(uintptr_t(3));
HWND foreground = primary;
bool visible = false, iconic = false, create_success = true;
int creates = 0, shows = 0, hides = 0, paints = 0, invalidates = 0, style_changes = 0;
WNDPROC proc = nullptr;
LONG_PTR style = WS_OVERLAPPEDWINDOW;
RECT rect{50, 60, 1330, 780};
BOOL is_visible(HWND) { return visible; }
BOOL is_iconic(HWND) { return iconic; }
HWND get_foreground() { return foreground; }
BOOL get_monitor_info(HMONITOR, LPMONITORINFO info) { info->rcMonitor = {1920, 0, 3840, 1080}; return TRUE; }
HMONITOR monitor_from_window(HWND, DWORD) { return reinterpret_cast<HMONITOR>(uintptr_t(4)); }
LONG_PTR get_style(HWND, int) { return style; }
LONG_PTR set_style(HWND, int field, LONG_PTR value) {
    if (field != GWL_STYLE) std::abort(); // Never write either window's userdata.
    ++style_changes; auto previous = style; style = value; return previous;
}
BOOL get_rect(HWND, LPRECT output) { *output = rect; return TRUE; }
BOOL set_position(HWND handle, HWND, int x, int y, int width, int height, UINT) {
    if (handle != player2) std::abort();
    rect = {x, y, x + width, y + height}; return TRUE;
}
BOOL show(HWND handle, int command) {
    if (handle != player2) std::abort();
    if (command == SW_HIDE) { visible = false; ++hides; }
    else { visible = true; iconic = false; ++shows; }
    return TRUE;
}
HDC begin_paint(HWND, LPPAINTSTRUCT paint) { paint->rcPaint = {0, 0, 1280, 720}; return nullptr; }
BOOL end_paint(HWND, const PAINTSTRUCT*) { return TRUE; }
int fill(HDC, const RECT*, HBRUSH) { ++paints; return 1; }
HGDIOBJ stock(int) { return nullptr; }
LRESULT default_proc(HWND, UINT, WPARAM, LPARAM) { return 0; }
HMODULE module(LPCWSTR) { return nullptr; }
HCURSOR cursor(HINSTANCE, LPCWSTR) { return nullptr; }
ATOM register_class(const WNDCLASSEXW* value) { proc = value->lpfnWndProc; return 1; }
DWORD last_error() { return ERROR_ACCESS_DENIED; }
BOOL client_rect(HWND, LPRECT output) { *output = {0, 0, 1600, 900}; return TRUE; }
BOOL adjust_rect(LPRECT output, DWORD, BOOL, DWORD) { output->right += 16; output->bottom += 39; return TRUE; }
HWND create(DWORD, LPCWSTR, LPCWSTR, DWORD flags, int, int, int, int,
    HWND parent, HMENU, HINSTANCE, LPVOID) {
    if (parent || (flags & WS_CHILD)) std::abort(); // Independent top-level window.
    ++creates; return create_success ? player2 : nullptr;
}
BOOL invalidate(HWND, const RECT*, BOOL) { ++invalidates; return TRUE; }
}

#define IsWindowVisible fake::is_visible
#define IsIconic fake::is_iconic
#define GetForegroundWindow fake::get_foreground
#define GetMonitorInfoW fake::get_monitor_info
#define MonitorFromWindow fake::monitor_from_window
#define GetWindowLongPtrW fake::get_style
#define SetWindowLongPtrW fake::set_style
#define GetWindowRect fake::get_rect
#define SetWindowPos fake::set_position
#define ShowWindow fake::show
#define BeginPaint fake::begin_paint
#define EndPaint fake::end_paint
#define FillRect fake::fill
#define GetStockObject fake::stock
#define DefWindowProcW fake::default_proc
#define GetModuleHandleW fake::module
#define LoadCursorW fake::cursor
#define RegisterClassExW fake::register_class
#define GetLastError fake::last_error
#define GetClientRect fake::client_rect
#define AdjustWindowRectEx fake::adjust_rect
#define CreateWindowExW fake::create
#define InvalidateRect fake::invalidate
#include "../../src/wr64_secondary_window.cpp"

int checks = 0;
void check(bool condition, const char* name) {
    ++checks;
    if (!condition) { std::fprintf(stderr, "FAILED: %s\n", name); std::exit(1); }
}

int main() {
    using namespace RT64;
    using wr64::window::update_secondary_window;
    update_secondary_window(fake::primary);
    check(fake::creates == 0, "no window before supported active race");
    wr64SecondaryRaceActive = true;
    update_secondary_window(fake::primary);
    check(fake::creates == 0, "unsupported backend does not create");
    wr64SeparateWindowsBackend = true;
    update_secondary_window(nullptr);
    check(fake::creates == 0, "headless primary does not create");
    update_secondary_window(fake::primary);
    check(fake::creates == 1 && fake::visible, "first race creates and shows");
    check(wr64SecondaryWindowHandle == uintptr_t(fake::player2) && wr64SecondaryWindowDrawable,
        "published stable handle and drawable");
    check(fake::foreground == fake::primary && !wr64SecondaryWindowFocused, "creation does not steal focus");
    update_secondary_window(fake::primary);
    check(fake::creates == 1, "normal updates reuse window");

    fake::foreground = fake::player2;
    fake::proc(fake::player2, WM_ACTIVATE, WA_ACTIVE, 0);
    check(wr64SecondaryWindowFocused, "Player 2 focus enables transient input");
    fake::foreground = fake::other;
    fake::proc(fake::player2, WM_ACTIVATE, WA_INACTIVE, 0);
    check(!wr64SecondaryWindowFocused, "other app removes transient input");
    fake::foreground = fake::player2;
    update_secondary_window(fake::primary);
    check(wr64SecondaryWindowFocused, "poll refreshes foreground predicate");

    const RECT windowed = fake::rect;
    fake::proc(fake::player2, WM_KEYDOWN, VK_F11, 0);
    check(fake::style_changes == 1 && fake::rect.left == 1920 && fake::rect.right == 3840,
        "F11 fullscreen follows Player 2 monitor");
    fake::proc(fake::player2, WM_KEYDOWN, VK_F11, LPARAM(1) << 30);
    check(fake::style_changes == 1, "F11 auto-repeat ignored");
    fake::proc(fake::player2, WM_SYSKEYDOWN, VK_RETURN, LPARAM(1) << 29);
    check(fake::style_changes == 2 && fake::rect.left == windowed.left &&
        fake::rect.bottom == windowed.bottom && fake::style == WS_OVERLAPPEDWINDOW,
        "Alt Enter restores original rectangle and style");

    fake::iconic = true;
    fake::proc(fake::player2, WM_SIZE, SIZE_MINIMIZED, 0);
    check(!wr64SecondaryWindowDrawable && !wr64SecondaryWindowFocused, "minimize suspends drawable and focus");
    fake::iconic = false;
    fake::proc(fake::player2, WM_SIZE, SIZE_RESTORED, 0);
    check(wr64SecondaryWindowDrawable, "restore resumes drawable");
    fake::proc(fake::player2, WM_CLOSE, 0, 0);
    update_secondary_window(fake::primary);
    check(fake::hides == 1 && !fake::visible && wr64SecondaryWindowClosed &&
        !wr64SecondaryWindowDrawable && !wr64SecondaryWindowFocused, "close hides for current race");
    check(wr64SecondaryWindowHandle == uintptr_t(fake::player2), "close preserves swapchain handle");
    update_secondary_window(fake::primary);
    check(fake::shows == 1 && fake::creates == 1, "closed race never reopens");
    wr64SecondaryRaceActive = false;
    update_secondary_window(fake::primary);
    fake::proc(fake::player2, WM_PAINT, 0, 0);
    check(fake::invalidates == 1 && fake::paints == 1, "race end requests black paint");
    wr64SecondaryRaceActive = true;
    update_secondary_window(fake::primary);
    check(fake::shows == 2 && fake::creates == 1 && !wr64SecondaryWindowClosed &&
        wr64SecondaryWindowDrawable, "next race reopens identical window");
    wr64SecondaryRaceActive = false;
    update_secondary_window(fake::primary);
    check(fake::visible && wr64SecondaryWindowDrawable && !wr64SecondaryWindowFocused,
        "between races retains visible black swapchain without input override");

    // Start a fresh simulated process and prove failed creation is bounded,
    // with a retry at the next race boundary rather than every UI tick.
    wr64::window::secondary = {};
    wr64SecondaryWindowHandle = 0;
    fake::create_success = false;
    const int previous_creates = fake::creates;
    wr64SecondaryRaceActive = true;
    update_secondary_window(fake::primary);
    update_secondary_window(fake::primary);
    check(fake::creates == previous_creates + 1 && wr64SecondaryWindowHandle == 0 &&
        !wr64SecondaryWindowDrawable, "failed creation tried once per race");
    wr64SecondaryRaceActive = false;
    update_secondary_window(fake::primary);
    fake::create_success = true;
    wr64SecondaryRaceActive = true;
    update_secondary_window(fake::primary);
    check(fake::creates == previous_creates + 2 && wr64SecondaryWindowDrawable,
        "next race retries failed creation");
    std::printf("PASS: %d actual-source window lifecycle checks; all Win32 calls substituted, no window created.\n", checks);
}
