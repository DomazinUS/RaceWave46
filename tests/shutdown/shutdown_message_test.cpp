#include "ultramodern/join_thread.hpp"
#include <atomic>
#include <cstdio>
#include <cstdlib>

static void check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "%s\n", message);
        std::exit(1);
    }
}

constexpr UINT SentMessage = WM_APP + 41;
constexpr UINT PostedMessage = WM_APP + 42;
static unsigned sent_count = 0;
static unsigned posted_count = 0;
static DWORD owning_thread = 0;

static LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    if (message == SentMessage) {
        check(GetCurrentThreadId() == owning_thread, "Sent message escaped window-owning thread");
        ++sent_count;
        return wparam + 1;
    }
    if (message == PostedMessage) {
        ++posted_count;
        return 0;
    }
    return DefWindowProcW(window, message, wparam, lparam);
}

int main() {
    owning_thread = GetCurrentThreadId();
    WNDCLASSW klass{};
    klass.lpfnWndProc = window_proc;
    klass.hInstance = GetModuleHandleW(nullptr);
    klass.lpszClassName = L"WR64ShutdownMessageOnlyTest";
    check(RegisterClassW(&klass) != 0, "Cannot register test message window");
    // Message-only: no visible window, graphics device, SDL, game, or desktop input.
    HWND window = CreateWindowExW(0, klass.lpszClassName, L"", 0, 0, 0, 0, 0,
        HWND_MESSAGE, nullptr, klass.hInstance, nullptr);
    check(window != nullptr, "Cannot create message-only test window");
    check(PostMessageW(window, PostedMessage, 123, 0) != 0, "Cannot queue posted-message sentinel");
    PostQuitMessage(29);

    HANDLE started = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    check(started != nullptr, "Cannot create worker event");
    std::atomic_bool answered = false;
    std::thread worker([&] {
        SetEvent(started);
        check(SendMessageW(window, SentMessage, 7, 0) == 8, "First synchronous reply was lost");
        check(SendMessageW(window, SentMessage, 8, 0) == 9, "Second synchronous reply was lost");
        answered = true;
    });
    check(WaitForSingleObject(started, 1000) == WAIT_OBJECT_0, "Worker did not start");
    // The old non-pumping join cannot complete a worker that needs a window
    // reply. Bound that reproduction, then use the real runtime helper.
    check(WaitForSingleObject(worker.native_handle(), 30) == WAIT_TIMEOUT,
        "Expected old non-pumping wait to stall while window reply is pending");
    check(!answered.load(), "Worker unexpectedly completed without a message pump");
    ultramodern::join_thread_servicing_window_messages(worker);
    check(answered.load() && sent_count == 2, "Shutdown wait failed to answer synchronous requests");
    check(!worker.joinable(), "Worker was not joined");
    check(posted_count == 0, "Shutdown wait replayed queued application actions");

    MSG message{};
    check(PeekMessageW(&message, window, PostedMessage, PostedMessage, PM_REMOVE) != 0 &&
        message.message == PostedMessage && message.wParam == 123, "Shutdown wait consumed posted application input");
    // PostQuitMessage is low priority; drain the posted sentinel before asking
    // for WM_QUIT, even when the PeekMessage range specifically requests it.
    check(PeekMessageW(&message, nullptr, WM_QUIT, WM_QUIT, PM_REMOVE) != 0 &&
        message.message == WM_QUIT && message.wParam == 29, "Shutdown wait consumed WM_QUIT");

    // Repeated joins cover arrival during the wait and the already-finished case.
    for (unsigned i = 0; i < 64; ++i) {
        std::thread sender([&] { SendMessageW(window, SentMessage, i, 0); });
        ultramodern::join_thread_servicing_window_messages(sender);
    }
    std::thread finished([] {});
    check(WaitForSingleObject(finished.native_handle(), 1000) == WAIT_OBJECT_0, "Empty worker did not finish");
    ultramodern::join_thread_servicing_window_messages(finished);
    check(sent_count == 66 && posted_count == 0, "Unexpected dispatch counts");
    CloseHandle(started);
    DestroyWindow(window);
    UnregisterClassW(klass.lpszClassName, klass.hInstance);
    std::puts("Bounded old-wait deadlock reproduced; synchronous replies complete during real runtime joins.");
    std::puts("Posted input and WM_QUIT preserved; message-only HWND never shown.");
}
