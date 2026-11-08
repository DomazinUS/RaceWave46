#pragma once

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>

namespace RT64 {
    enum class Wr64ShaderInput : uint32_t {
        // The presented image at the window's resolution.
        Internal = 0,
        // About 240 lines, for CRT and pixel-art shaders written for console output.
        Native = 1
    };

    struct Wr64ShaderSelection {
        // Absolute path to a .slangp preset. Empty disables the filter chain.
        std::string presetPath;
        // Changes only when presetPath changes, so input changes keep the compiled chain.
        uint64_t presetGeneration = 0;
        Wr64ShaderInput input = Wr64ShaderInput::Internal;
    };

    struct Wr64ShaderStatus {
        uint64_t presetGeneration = 0;
        bool failed = false;
        std::string message;
    };

    // Written by the settings UI and read by the present thread before each frame.
    struct Wr64ShaderState {
        std::mutex mutex;
        Wr64ShaderSelection selection;
        Wr64ShaderStatus status;
        std::atomic<uint64_t> statusRevision{0};
    };

    inline Wr64ShaderState &wr64ShaderState() {
        static Wr64ShaderState state;
        return state;
    }

    inline void setWr64ShaderPreset(const std::string &presetPath) {
        Wr64ShaderState &state = wr64ShaderState();
        const std::scoped_lock lock(state.mutex);
        if (state.selection.presetPath == presetPath) return;
        state.selection.presetPath = presetPath;
        state.selection.presetGeneration++;
    }

    inline void setWr64ShaderInput(uint32_t input) {
        Wr64ShaderState &state = wr64ShaderState();
        const std::scoped_lock lock(state.mutex);
        state.selection.input = input == uint32_t(Wr64ShaderInput::Native) ? Wr64ShaderInput::Native : Wr64ShaderInput::Internal;
    }

    inline Wr64ShaderSelection getWr64ShaderSelection() {
        Wr64ShaderState &state = wr64ShaderState();
        const std::scoped_lock lock(state.mutex);
        return state.selection;
    }

    // Reported by the present thread after it compiles (or fails to compile) a preset.
    inline void reportWr64ShaderStatus(uint64_t presetGeneration, bool failed, const std::string &message) {
        Wr64ShaderState &state = wr64ShaderState();
        {
            const std::scoped_lock lock(state.mutex);
            if (state.status.presetGeneration == presetGeneration && state.status.failed == failed &&
                state.status.message == message) return;
            state.status = { presetGeneration, failed, message };
        }
        state.statusRevision.fetch_add(1, std::memory_order_release);
    }

    inline uint64_t getWr64ShaderStatusRevision() {
        return wr64ShaderState().statusRevision.load(std::memory_order_acquire);
    }

    inline Wr64ShaderStatus getWr64ShaderStatus() {
        Wr64ShaderState &state = wr64ShaderState();
        const std::scoped_lock lock(state.mutex);
        return state.status;
    }
}
