#pragma once

#include <atomic>
#include <cstdint>

namespace RT64 {
    enum class Wr64RTPrewarmStatus { Pending, Ready, Failed };

    // The native idle thread requests this only after its CPU logo has been
    // swapped in and unblanked, before creating the game's scheduler/audio
    // threads. The graphics API thread owns pipeline requests and completion.
    class Wr64RTStartupGate {
    public:
        enum class State : uint32_t { Idle, Requested, Pending, Ready, Bypassed, Failed, Cancelled };
    private:
        std::atomic<State> state_{State::Idle};
    public:
        void request() {
            State expected = State::Idle;
            state_.compare_exchange_strong(expected, State::Requested);
        }
        State state() const { return state_.load(); }
        bool waiting() const {
            const State s = state();
            return s == State::Requested || s == State::Pending;
        }
        void publish(State next) {
            State previous = state();
            while ((previous == State::Requested || previous == State::Pending) &&
                !state_.compare_exchange_weak(previous, next)) { }
        }
        // Renderer recreation is serialized before a new native boot begins.
        void reset() { state_.store(State::Idle); }
    };
    inline Wr64RTStartupGate wr64RTStartupGate;
}
