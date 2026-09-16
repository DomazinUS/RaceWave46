#pragma once

#include <array>
#include <condition_variable>
#include <cstddef>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

namespace RT64 {
    // Fixed key space, one worker, one attempt per key until explicit reset.
    // Published objects never move or disappear while callers may use them.
    template <typename T, size_t Capacity>
    class Wr64AsyncCache {
        static_assert(Capacity > 0, "An asynchronous cache needs at least one key");
    public:
        enum class State { Empty, Queued, Ready, Failed };
    private:
        struct Entry { State state = State::Empty; std::unique_ptr<T> result; };
        struct Job { size_t key; std::function<std::unique_ptr<T>()> build; };
        std::array<Entry, Capacity> entries_{};
        std::deque<Job> jobs_;
        std::mutex mutex_;
        std::condition_variable changed_;
        std::thread worker_;
        bool active_ = false;
        bool stopping_ = false;

        void run() {
            for (;;) {
                Job job;
                {
                    std::unique_lock lock(mutex_);
                    changed_.wait(lock, [&] { return stopping_ || !jobs_.empty(); });
                    if (jobs_.empty()) return;
                    job = std::move(jobs_.front()); jobs_.pop_front();
                    active_ = true;
                }
                std::unique_ptr<T> result;
                try { result = job.build(); } catch (...) { /* Sticky failure. */ }
                // Release captured configuration/resources before publishing
                // idle, so wait/reset is also a complete lifetime boundary.
                job.build = {};
                {
                    std::lock_guard lock(mutex_);
                    auto &entry = entries_[job.key];
                    entry.result = std::move(result);
                    entry.state = entry.result ? State::Ready : State::Failed;
                    active_ = false;
                }
                changed_.notify_all();
            }
        }

    public:
        Wr64AsyncCache() = default;
        Wr64AsyncCache(const Wr64AsyncCache &) = delete;
        Wr64AsyncCache &operator=(const Wr64AsyncCache &) = delete;
        ~Wr64AsyncCache() {
            { std::lock_guard lock(mutex_); stopping_ = true; }
            changed_.notify_all();
            if (worker_.joinable()) worker_.join();
        }

        const T *get(size_t key, std::function<std::unique_ptr<T>()> build, bool wait) {
            if (key >= Capacity) return nullptr;
            std::unique_lock lock(mutex_);
            if (stopping_) return nullptr;
            auto &entry = entries_[key];
            if (entry.state == State::Empty) {
                try {
                    if (!worker_.joinable()) worker_ = std::thread([this] { run(); });
                    jobs_.push_back({key, std::move(build)});
                    entry.state = State::Queued;
                } catch (...) { entry.state = State::Failed; }
                changed_.notify_all();
            }
            if (wait) changed_.wait(lock, [&] { return entry.state == State::Ready || entry.state == State::Failed; });
            return entry.result.get();
        }

        void waitForPending() {
            std::unique_lock lock(mutex_);
            changed_.wait(lock, [&] { return jobs_.empty() && !active_; });
        }

        State state(size_t key) {
            std::lock_guard lock(mutex_);
            return key < Capacity ? entries_[key].state : State::Failed;
        }

        // Caller must prevent new requests and wait for GPU users of returned
        // pointers. Driver object destruction occurs outside the state mutex.
        void reset() {
            waitForPending();
            std::array<std::unique_ptr<T>, Capacity> retired;
            {
                std::lock_guard lock(mutex_);
                for (size_t i = 0; i < Capacity; ++i) {
                    retired[i] = std::move(entries_[i].result);
                    entries_[i].state = State::Empty;
                }
            }
        }
    };
}
