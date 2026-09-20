#pragma once

#include <thread>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <system_error>
#endif

namespace ultramodern {

// The window-owning thread must still answer synchronous window messages while
// joining graphics teardown. DXGI may send one from Present or swap-chain
// cleanup; a plain join would leave both threads waiting for each other.
// Service sent messages only: never replay queued input or call the normal
// frontend/game update loop after renderer shutdown has started.
inline void join_thread_servicing_window_messages(std::thread& thread) {
#ifdef _WIN32
    if (thread.joinable()) {
        const HANDLE handle = static_cast<HANDLE>(thread.native_handle());
        for (;;) {
            const DWORD result = MsgWaitForMultipleObjectsEx(
                1, &handle, INFINITE, QS_SENDMESSAGE, MWMO_INPUTAVAILABLE);
            if (result == WAIT_OBJECT_0) break;
            if (result == WAIT_OBJECT_0 + 1) {
                MSG message{};
                // PeekMessage dispatches pending nonqueued sent messages
                // internally. PM_NOREMOVE retains posted input and WM_QUIT.
                PeekMessageW(&message, nullptr, 0, 0, PM_NOREMOVE | PM_QS_SENDMESSAGE);
            } else {
                throw std::system_error(static_cast<int>(GetLastError()),
                    std::system_category(), "Waiting for runtime thread shutdown");
            }
        }
    }
#endif
    thread.join();
}

} // namespace ultramodern
