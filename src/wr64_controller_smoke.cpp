#include "wr64_diagnostic_policy.h"
#include "wr64_controller_smoke.hpp"
#include "wr64_editions.hpp"

#include <array>
#include <charconv>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <span>

#include "SDL.h"

namespace {
using Clock = std::chrono::steady_clock;
struct Action {
    unsigned time_ms;
    SDL_GameControllerButton button;
    bool pressed;
};
// Sustained holds span six or more native20Hz input samples. The first two
// presses test Start; later A presses can advance ordinary title/menu screens.
constexpr std::array core_actions{
    Action{8000, SDL_CONTROLLER_BUTTON_START, true},
    Action{8300, SDL_CONTROLLER_BUTTON_START, false},
    Action{11000, SDL_CONTROLLER_BUTTON_START, true},
    Action{11300, SDL_CONTROLLER_BUTTON_START, false},
    Action{12000, SDL_CONTROLLER_BUTTON_DPAD_DOWN, true},
    Action{12300, SDL_CONTROLLER_BUTTON_DPAD_DOWN, false},
    Action{14000, SDL_CONTROLLER_BUTTON_A, true},
    Action{14300, SDL_CONTROLLER_BUTTON_A, false},
    Action{17000, SDL_CONTROLLER_BUTTON_A, true},
    Action{17300, SDL_CONTROLLER_BUTTON_A, false},
    Action{20000, SDL_CONTROLLER_BUTTON_A, true},
    Action{20300, SDL_CONTROLLER_BUTTON_A, false},
    Action{23000, SDL_CONTROLLER_BUTTON_START, true},
    Action{23300, SDL_CONTROLLER_BUTTON_START, false},
    Action{29000, SDL_CONTROLLER_BUTTON_START, true},
    Action{29300, SDL_CONTROLLER_BUTTON_START, false},
    Action{32000, SDL_CONTROLLER_BUTTON_A, true},
    Action{42000, SDL_CONTROLLER_BUTTON_A, false},
    Action{50000, SDL_CONTROLLER_BUTTON_A, true},
    Action{62000, SDL_CONTROLLER_BUTTON_A, false},
};

// Exercise the real launcher's SDL/UI path. The long A hold straddles a manual
// child close; returning to the selector must wait for release before accepting
// a fresh selection. The final Down/A pair checks that input resumes afterwards.
constexpr std::array launcher_actions{
    Action{8000, SDL_CONTROLLER_BUTTON_A, true},
    Action{8300, SDL_CONTROLLER_BUTTON_A, false},
    Action{20000, SDL_CONTROLLER_BUTTON_DPAD_DOWN, true},
    Action{23000, SDL_CONTROLLER_BUTTON_DPAD_DOWN, false},
    Action{24000, SDL_CONTROLLER_BUTTON_A, true},
    Action{27000, SDL_CONTROLLER_BUTTON_A, false},
    Action{28000, SDL_CONTROLLER_BUTTON_START, true},
    Action{31000, SDL_CONTROLLER_BUTTON_START, false},
    Action{45000, SDL_CONTROLLER_BUTTON_A, true},
    Action{105000, SDL_CONTROLLER_BUTTON_A, false},
    Action{110000, SDL_CONTROLLER_BUTTON_DPAD_DOWN, true},
    Action{110300, SDL_CONTROLLER_BUTTON_DPAD_DOWN, false},
    Action{112000, SDL_CONTROLLER_BUTTON_A, true},
    Action{112300, SDL_CONTROLLER_BUTTON_A, false},
};

struct SmokeState {
    bool attempted = false;
    bool finished = false;
    SDL_Joystick* joystick = nullptr;
    SDL_JoystickID id = -1;
    Clock::time_point started{};
    std::size_t next_action = 0;
    unsigned delay_ms = 0;
    uint64_t rumble_calls = 0;
    uint64_t nonzero_rumble_calls = 0;
};
SmokeState smoke;

bool requested() {
    static const bool value = [] {
        const char* env = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_CONTROLLER_SMOKE"));
        return env && std::strcmp(env, "1") == 0;
    }();
    return value;
}

bool time_trial_requested() {
    static const bool value = [] {
        const char* env = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_CONTROLLER_SMOKE_MODE"));
        return env && std::strcmp(env, "timetrial") == 0;
    }();
    return value;
}

bool launcher_requested() {
    static const bool value = [] {
        const char* env = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_CONTROLLER_SMOKE_MODE"));
        return env && std::strcmp(env, "launcher") == 0;
    }();
    return value;
}

unsigned elapsed_ms() {
    return unsigned(std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - smoke.started).count());
}

int SDLCALL virtual_rumble(void*, Uint16 low, Uint16 high) {
    ++smoke.rumble_calls;
    if (low != 0 || high != 0) {
        if (smoke.nonzero_rumble_calls++ == 0) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-smoke] t=%ums first virtual rumble low=%u high=%u\n",
                elapsed_ms(), unsigned(low), unsigned(high)));
        }
    }
    return 0;
}

void attach() {
    smoke.attempted = true;
    smoke.started = Clock::now();
    if (const char* value = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_CONTROLLER_SMOKE_DELAY_MS"))) {
        // from_chars rejects signs/whitespace for unsigned input; require the
        // complete string and a bounded value before creating any device.
        const char* end = value + std::strlen(value);
        const auto parsed = std::from_chars(value, end, smoke.delay_ms);
        if (parsed.ec != std::errc{} || parsed.ptr != end || smoke.delay_ms > 300000) {
            std::fprintf(stderr, "[controller-smoke] invalid WR64_CONTROLLER_SMOKE_DELAY_MS; expected unsigned0..300000, diagnostic disabled\n");
            smoke.finished = true;
            return;
        }
    }
    // Same SDL virtual-pad setup as tests/controller_integration. This handle
    // represents only our synthetic input; physical devices are never opened.
    SDL_VirtualJoystickDesc desc{};
    desc.version = SDL_VIRTUAL_JOYSTICK_DESC_VERSION;
    desc.type = SDL_JOYSTICK_TYPE_GAMECONTROLLER;
    desc.naxes = SDL_CONTROLLER_AXIS_MAX;
    desc.nbuttons = SDL_CONTROLLER_BUTTON_MAX;
    desc.button_mask = (1U << SDL_CONTROLLER_BUTTON_MAX) - 1U;
    desc.axis_mask = (1U << SDL_CONTROLLER_AXIS_MAX) - 1U;
    desc.name = "Wave Race USA diagnostic virtual controller";
    desc.Rumble = virtual_rumble;
    const int index = SDL_JoystickAttachVirtualEx(&desc);
    if (index < 0) {
        std::fprintf(stderr, "[controller-smoke] virtual attach failed: %s\n", SDL_GetError());
        smoke.finished = true;
        return;
    }
    smoke.id = SDL_JoystickGetDeviceInstanceID(index);
    smoke.joystick = SDL_JoystickOpen(index);
    if (!smoke.joystick) {
        std::fprintf(stderr, "[controller-smoke] virtual open failed: %s\n", SDL_GetError());
        SDL_JoystickDetachVirtual(index);
        smoke.finished = true;
        return;
    }
    SDL_JoystickSetVirtualAxis(smoke.joystick, SDL_CONTROLLER_AXIS_TRIGGERLEFT, -32768);
    SDL_JoystickSetVirtualAxis(smoke.joystick, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, -32768);
    if (launcher_requested()) {
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-smoke] attached own virtual id=%d; mode=launcher; delay_ms=%u added to all actions and detach; A8..8.3s; hidden-parent Down20..23s/A24..27s/Start28..31s; return-time A45..105s; fresh Down110..110.3s/A112..112.3s; detach120s\n", int(smoke.id), smoke.delay_ms));
    }
    else {
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-smoke] attached own virtual id=%d; delay_ms=%u added to all actions and detach; Start holds8s/11s/23s/29s, A14s/17s/20s, throttle32..42s/50..62s; detach64s\n", int(smoke.id), smoke.delay_ms));
    }
    if (time_trial_requested() && !launcher_requested()) {
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-smoke] mode=timetrial; Down hold12..12.3s selects native main-menu row1\n"));
    }
}
}

void wr64_controller_smoke_shutdown() {
    if (!smoke.joystick) return;
    SDL_JoystickSetVirtualButton(smoke.joystick, SDL_CONTROLLER_BUTTON_START, 0);
    SDL_JoystickSetVirtualButton(smoke.joystick, SDL_CONTROLLER_BUTTON_A, 0);
    SDL_JoystickSetVirtualButton(smoke.joystick, SDL_CONTROLLER_BUTTON_DPAD_DOWN, 0);
    // Device indices can change after hotplug. Only inspect IDs of virtual
    // entries; detach precisely the instance created above, never another pad.
    for (int index = 0; index < SDL_NumJoysticks(); ++index) {
        if (SDL_JoystickIsVirtual(index) && SDL_JoystickGetDeviceInstanceID(index) == smoke.id) {
            if (SDL_JoystickDetachVirtual(index) != 0) {
                std::fprintf(stderr, "[controller-smoke] detach failed: %s\n", SDL_GetError());
            }
            break;
        }
    }
    SDL_JoystickClose(smoke.joystick);
    smoke.joystick = nullptr;
    smoke.finished = true;
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-smoke] finished t=%ums rumble_calls=%llu nonzero=%llu\n", elapsed_ms(),
        static_cast<unsigned long long>(smoke.rumble_calls),
        static_cast<unsigned long long>(smoke.nonzero_rumble_calls)));
}

void wr64_controller_smoke_update() {
    if (!requested() || smoke.finished) return;
    // Environment is inherited by launched cores. Keep the launcher's synthetic
    // input exclusively in the parent process, and ordinary game smoke there
    // exclusively in the core. This never changes a physical device's state.
    if (wr64::editions::is_launcher() != launcher_requested()) return;
    if (!smoke.attempted) {
        if ((SDL_WasInit(SDL_INIT_GAMECONTROLLER) & SDL_INIT_GAMECONTROLLER) == 0) return;
        attach();
    }
    if (!smoke.joystick) return;
    const unsigned time_ms = elapsed_ms();
    const std::span<const Action> actions = launcher_requested()
        ? std::span<const Action>(launcher_actions)
        : std::span<const Action>(core_actions);
    while (smoke.next_action < actions.size() && actions[smoke.next_action].time_ms + smoke.delay_ms <= time_ms) {
        const auto& action = actions[smoke.next_action++];
        if (action.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN && !launcher_requested() && !time_trial_requested()) continue;
        const int result = SDL_JoystickSetVirtualButton(smoke.joystick, action.button, action.pressed ? 1 : 0);
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[controller-smoke] t=%ums %s=%d result=%d\n", time_ms,
            action.button == SDL_CONTROLLER_BUTTON_START ? "Start" :
                action.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN ? "Down" : "A", int(action.pressed), result));
    }
    const unsigned detach_ms = launcher_requested() ? 120000 : 64000;
    if (time_ms >= detach_ms + smoke.delay_ms) wr64_controller_smoke_shutdown();
    // Leave event pumping and native sampling to the existing frontend/game
    // paths. Injecting an emulator button word would bypass the test's purpose.
}
