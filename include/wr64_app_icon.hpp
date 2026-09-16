#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace wr64::window {
inline void apply_app_icon(HWND handle) {
    // Shared icons belong to the executable module and live for the process.
    const HINSTANCE instance = GetModuleHandleW(nullptr);
    const auto large = static_cast<HICON>(LoadImageW(instance, MAKEINTRESOURCEW(1),
        IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_SHARED));
    const auto small = static_cast<HICON>(LoadImageW(instance, MAKEINTRESOURCEW(1),
        IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_SHARED));
    if (large) SendMessageW(handle, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(large));
    if (small) SendMessageW(handle, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(small));
}
}
#endif
