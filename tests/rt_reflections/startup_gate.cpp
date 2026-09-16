#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>

#include "common/rt64_wr64_async_cache.h"
#include "common/rt64_wr64_rt_startup.h"

using Gate = RT64::Wr64RTStartupGate;
using Cache = RT64::Wr64AsyncCache<int, 3>;
static unsigned checks = 0;
static void require(bool value, const char *message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}

int main() {
    try {
        Gate gate;
        Cache cache;
        require(gate.state() == Gate::State::Idle && !gate.waiting(), "Unrequested boot must not block");
        require(cache.state(0) == Cache::State::Empty && cache.state(99) == Cache::State::Failed,
            "Cache must distinguish unrequested and invalid configurations");
        std::mutex mutex;
        std::condition_variable changed;
        bool compilerStarted = false, releaseCompiler = false;
        std::atomic<unsigned> openingTicks{0}, musicStarts{0}, compiles{0};
        gate.request();
        std::thread native([&] {
            while (gate.waiting()) std::this_thread::yield();
            ++musicStarts;
            ++openingTicks;
        });
        auto compile = [&] {
            ++compiles;
            std::unique_lock lock(mutex);
            compilerStarted = true;
            changed.notify_all();
            changed.wait(lock, [&] { return releaseCompiler; });
            return std::make_unique<int>(7);
        };
        cache.get(0, compile, false);
        { std::unique_lock lock(mutex); changed.wait(lock, [&] { return compilerStarted; }); }
        gate.publish(Gate::State::Pending);
        bool remainedHeld = true;
        const auto begin = std::chrono::steady_clock::now();
        for (unsigned i = 0; i < 4000; ++i) {
            cache.get(0, compile, false);
            remainedHeld &= cache.state(0) == Cache::State::Queued && gate.waiting() &&
                openingTicks == 0 && musicStarts == 0;
        }
        const auto pollMs = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - begin).count();
        { std::lock_guard lock(mutex); releaseCompiler = true; }
        changed.notify_all();
        cache.waitForPending();
        gate.publish(cache.state(0) == Cache::State::Ready ? Gate::State::Ready : Gate::State::Failed);
        native.join();
        require(remainedHeld, "Opening/music advanced while the compiler was held");
        require(compiles == 1 && pollMs < 250, "Readiness polls blocked or repeatedly compiled");
        require(openingTicks == 1 && musicStarts == 1 && gate.state() == Gate::State::Ready,
            "Ready boot must begin its opening once, from the first tick");
        gate.request(); gate.publish(Gate::State::Pending);
        require(!gate.waiting(), "A completed boot was accidentally rearmed");

        gate.reset(); gate.request();
        cache.get(1, []() -> std::unique_ptr<int> { throw std::runtime_error("injected native PSO failure"); }, false);
        cache.waitForPending();
        require(cache.state(1) == Cache::State::Failed, "Native compile failure was indistinguishable from pending");
        gate.publish(Gate::State::Failed);
        require(!gate.waiting() && gate.state() == Gate::State::Failed, "Failed optional preparation trapped the logo");
        for (auto terminal : { Gate::State::Ready, Gate::State::Failed, Gate::State::Bypassed, Gate::State::Cancelled }) {
            gate.reset(); gate.request(); gate.publish(terminal);
            gate.publish(Gate::State::Pending); gate.request();
            require(gate.state() == terminal && !gate.waiting(), "Terminal result was overwritten by stale pending work");
        }
        // A quit racing a late successful compilation must never re-hold the
        // native thread or revive preparation after shutdown.
        for (unsigned i = 0; i < 100; ++i) {
            gate.reset(); gate.request(); gate.publish(Gate::State::Pending);
            std::thread completion([&] { gate.publish(Gate::State::Ready); });
            gate.publish(Gate::State::Cancelled);
            completion.join();
            require(!gate.waiting(), "Concurrent completion/cancellation trapped native startup");
        }
        std::printf("PASS %u startup checks; 4000 held-compiler polls %.3f ms\n", checks, pollMs);
        return 0;
    } catch (const std::exception &e) {
        std::fprintf(stderr, "FAIL %s\n", e.what());
        return 1;
    }
}
