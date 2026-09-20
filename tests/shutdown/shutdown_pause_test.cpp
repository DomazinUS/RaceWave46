// Compile the real recorder implementation in this TU to control its private
// pause state without enabling the recorder, allocating its ring or exporting.
#include "src/wr64_forensic.cpp"
#include <future>
#include <optional>
#include <stdexcept>

enum class GameStatus { None, Running, Quit };
std::atomic_bool exited = false;
std::atomic<GameStatus> game_status = GameStatus::None;
std::mutex current_game_mutex;
std::optional<int> current_game;
namespace ultramodern { void quit(); }
#include "runtime_quit.inc"

static void check(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}

int main() {
    using namespace std::chrono_literals;
    try {
        // A notifier must take the same mutex used by the wait predicate.
        // This closes the check-to-sleep missed-notification window.
        gRecorder.paused = true;
        std::unique_lock pause_lock(gRecorder.pauseMutex);
        auto quitting = std::async(std::launch::async, [] { ultramodern::quit(); });
        while (!exited.load()) std::this_thread::yield();
        const bool blocked_on_pause_mutex = quitting.wait_for(20ms) == std::future_status::timeout;
        const bool paused_before_unlock = gRecorder.paused.load();
        pause_lock.unlock();
        quitting.get();
        check(blocked_on_pause_mutex && paused_before_unlock,
            "Quit released the pause predicate without taking its wait mutex");
        check(!gRecorder.paused && game_status == GameStatus::Quit,
            "Real quit did not release pause and notify startup state");

        for (unsigned iteration = 0; iteration < 128; ++iteration) {
            exited = false;
            game_status = iteration & 1 ? GameStatus::Running : GameStatus::None;
            current_game = 1;
            gRecorder.paused = true;
            std::atomic_uint entered = 0, finished = 0;
            std::unique_lock gate(gRecorder.pauseMutex);
            auto worker = [&] {
                ++entered;
                wr64_forensic_wait_if_paused();
                ++finished;
            };
            std::thread vi(worker), graphics(worker);
            while (entered.load() != 2) std::this_thread::yield();
            std::thread quit_thread([] { ultramodern::quit(); });
            while (!exited.load()) std::this_thread::yield();
            gate.unlock();
            quit_thread.join(); vi.join(); graphics.join();
            check(finished == 2 && !gRecorder.paused && !current_game,
                "Quit stranded a paused runtime worker or failed to clear the active game");
            check(game_status == (iteration & 1 ? GameStatus::Running : GameStatus::Quit),
                "Quit changed the existing native game-state transition");
        }
        // A join of an in-flight exporter must finish before its memory owner
        // may release RDRAM. The CMake source guard checks that runtime order.
        std::array<unsigned char, 8> live_memory{42};
        std::promise<void> release_export;
        auto released = release_export.get_future();
        std::atomic_bool exported = false;
        gRecorder.exportThread = std::thread([&] {
            released.wait();
            exported = live_memory[0] == 42;
        });
        auto stopping = std::async(std::launch::async, [] { wr64_forensic_shutdown(); });
        const bool waits_for_export = stopping.wait_for(20ms) == std::future_status::timeout;
        release_export.set_value(); stopping.get();
        check(waits_for_export && exported && !gRecorder.exportThread.joinable(),
            "Forensic shutdown did not finish an active export before memory release");
        wr64_forensic_shutdown(); // main's second call remains harmless.
        std::puts("Actual runtime quit releases VI/Gfx pause races; 128 two-worker cycles passed.");
        std::puts("Actual forensic shutdown waits for its exporter; runtime source joins it before RDRAM free.");
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "%s\n", error.what());
        return 1;
    }
}
