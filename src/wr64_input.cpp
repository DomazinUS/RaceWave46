#include "wr64_diagnostic_policy.h"
#include "wr64_input.hpp"

#ifdef WR64_ENABLE_FRONTEND

#include <array>
#include <atomic>
#include <cstdio>
#include <filesystem>
#include <mutex>

#include "SDL.h"
#include "librecomp/game.hpp"
#include "recompinput/players.h"
#include "recompinput/profiles.h"
#include "recompinput/recompinput.h"
#include "composites/ui_assign_players_modal.h"
#include "config/ui_config_page_controls.h"
#include "wr64_launcher_input.hpp"

namespace wr64::input {
namespace {
constexpr int kPlayerCount = 2;
bool initialized = false;
std::mutex adapter_mutex;
std::atomic_bool multiplayer_request = false;
std::atomic_bool multiplayer_mode = false;
std::atomic_bool multiplayer_ready = false;
std::atomic_bool multiplayer_cancelled = false;
std::atomic_bool assignment_retry = false;
std::array<bool, kPlayerCount> new_keyboard_profiles{};
bool assignment_profiles_ready = false;
bool assignment_release_pending = false;

bool multiplayer_ports() {
    return multiplayer_mode.load() ||
        (multiplayer_request.load() && !multiplayer_cancelled.load());
}

bool assigned_device_present(int player) {
    if (!recompinput::players::get_player_is_assigned(player)) return false;
    const auto& assigned = recompinput::players::get_player(player);
    return assigned.controller != nullptr
        ? SDL_GameControllerGetAttached(assigned.controller) == SDL_TRUE
        : assigned.keyboard_enabled;
}

void refresh_controls() {
    if (recompui::controls_page != nullptr) recompui::controls_page->force_update();
}

void begin_assignment() {
    recompinput::reset_rumble();
    multiplayer_ready.store(false);
    assignment_profiles_ready = assignment_release_pending = false;
    for (int player = 0; player < kPlayerCount; ++player) {
        new_keyboard_profiles[player] = recompinput::profiles::get_input_profile_by_key(
            recompinput::profiles::get_mp_keyboard_profile_key(player)) < 0;
    }
    recompinput::playerassignment::start();
    recompui::AssignPlayersModal::open();
    refresh_controls();
}

void use_single_player(bool cancelled) {
    recompinput::reset_rumble();
    recompinput::playerassignment::stop();
    recompui::AssignPlayersModal::close();
    recompinput::players::set_player_count_range(1, kPlayerCount);
    recompinput::players::set_single_player_mode(true);
    multiplayer_mode.store(false);
    multiplayer_ready.store(false);
    assignment_profiles_ready = assignment_release_pending = false;
    multiplayer_cancelled.store(cancelled);
    refresh_controls();
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[input] single-player aggregation restored%s\n",
        cancelled ? " (player assignment cancelled)" : ""));
}

void isolate_player_profiles() {
    bool keyboard_seen = false;
    for (int player = 0; player < kPlayerCount; ++player) {
        const auto& assigned = recompinput::players::get_player(player);
        const bool keyboard = assigned.controller == nullptr && assigned.keyboard_enabled;
        // Assignment commits only the selected device's profile upstream. Clear
        // the other slot so a leftover SP keyboard cannot drive both racers.
        recompinput::profiles::set_input_profile_for_player(player, -1,
            keyboard ? recompinput::InputDevice::Controller : recompinput::InputDevice::Keyboard);
        if (keyboard && new_keyboard_profiles[player] && !keyboard_seen) {
            const int profile = recompinput::profiles::get_input_profile_for_player(
                player, recompinput::InputDevice::Keyboard);
            const int single = recompinput::profiles::get_sp_keyboard_profile_index();
            for (int input = 0; input < static_cast<int>(recompinput::GameInput::COUNT); ++input) {
                for (size_t binding = 0; binding < recompinput::num_bindings_per_input; ++binding) {
                    const auto id = static_cast<recompinput::GameInput>(input);
                    recompinput::profiles::set_input_binding(profile, id, binding,
                        recompinput::profiles::get_input_binding(single, id, binding));
                }
            }
        }
        // A second keyboard keeps its separate upstream mapping; copying the
        // same defaults to both keyboard players would couple their controls.
        keyboard_seen |= keyboard;
        new_keyboard_profiles[player] = false;
    }
}

bool neutral_input(std::uint16_t* buttons, float* x, float* y) {
    *buttons = 0;
    *x = *y = 0.0f;
    return true;
}
}

void initialize() {
    if (initialized) return;
    SDL_Init(0);
    // SDL 2.26's simple Bluetooth DualSense reports cannot carry rumble.
    // Select enhanced reports before enumeration (and the firmware query),
    // while allowing an explicit SDL hint/environment setting to take priority.
    SDL_SetHintWithPriority(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE, "1", SDL_HINT_DEFAULT);
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0) {
        std::fprintf(stderr, "[input] SDL initialization failed: %s\n", SDL_GetError());
        return;
    }
    recompinput::profiles::initialize_input_bindings();
    // In single-player mode RecompInput combines the keyboard and every detected
    // controller into player 1, matching the standard RecompFrontend behavior.
    // Native two-player selection enables explicit device assignment later.
    recompinput::players::set_single_player_mode(true);
    recompinput::players::set_player_count_range(1, kPlayerCount);

    const auto config = recomp::get_config_path() / "controls.json";
    if (std::filesystem::exists(config)) {
        recompinput::profiles::load_controls_config(config);
    }
    recompinput::set_game_input_description(recompinput::GameInput::A, "Accelerate");
    recompinput::set_game_input_description(recompinput::GameInput::B, "Brake and reverse");
    recompinput::set_game_input_description(recompinput::GameInput::START, "Pause");
    initialized = true;
}

void shutdown() {
    if (initialized) {
        recompinput::profiles::save_controls_config(recomp::get_config_path() / "controls.json");
    }
}

bool ready() {
    return initialized;
}

void set_multiplayer_enabled(bool enabled) {
    const bool previous = multiplayer_request.exchange(enabled);
    if (!enabled || !previous) {
        multiplayer_cancelled.store(false);
        multiplayer_ready.store(false);
    }
}

bool multiplayer_requested() {
    return multiplayer_request.load();
}

void request_multiplayer_assignment() {
    if (multiplayer_request.load()) {
        multiplayer_ready.store(false);
        multiplayer_cancelled.store(false);
        assignment_retry.store(true);
    }
}

void poll() {
    std::lock_guard lock{adapter_mutex};
    if (initialized) {
        static std::atomic_bool logged_poll = false;
        if (WR64_DIAGNOSTIC_ENABLED && !logged_poll.exchange(true)) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[input] polling active\n"));
        }
        recompinput::poll_inputs();
    }
}

void process_pending_ui() {
    // get_n64_input() may acquire the UI mutex while holding adapter_mutex.
    // The UI callback must never wait in the reverse order; retry next frame.
    std::unique_lock lock{adapter_mutex, std::try_to_lock};
    if (!lock.owns_lock()) return;
    if (initialized) {
        recompinput::playerassignment::process_pending_ui();
        const bool requested = multiplayer_request.load();
        const bool retry = assignment_retry.exchange(false);
        if (!requested) {
            if (multiplayer_mode.load()) use_single_player(false);
            multiplayer_cancelled.store(false);
        } else if ((!multiplayer_mode.load() && !multiplayer_cancelled.load()) || retry) {
            recompinput::players::set_player_count_range(kPlayerCount, kPlayerCount);
            recompinput::players::set_single_player_mode(false);
            multiplayer_mode.store(true);
            begin_assignment();
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[input] assign two independent players\n"));
        }
        if (multiplayer_mode.load()) {
            if (recompinput::playerassignment::was_cancelled()) {
                use_single_player(true);
            } else if (recompinput::playerassignment::is_active()) {
                if (multiplayer_ready.exchange(false)) recompinput::reset_rumble();
                return;
            } else if (recompinput::players::get_number_of_assigned_players() != kPlayerCount ||
                !assigned_device_present(0) || !assigned_device_present(1)) {
                begin_assignment();
                return;
            } else if (!assignment_profiles_ready) {
                isolate_player_profiles();
                assignment_profiles_ready = true;
                // The Confirm button must be released before its input can
                // select a watercraft or accelerate in the native game.
                assignment_release_pending = true;
            }
        }
    }
}

void update_rumble() {
    std::lock_guard lock{adapter_mutex};
    if (initialized && assignment_release_pending && multiplayer_mode.load() &&
        multiplayer_request.load() && !assignment_retry.load() &&
        !recompinput::playerassignment::is_active() &&
        assigned_device_present(0) && assigned_device_present(1) &&
        wr64::editions::controls_released()) {
        assignment_release_pending = false;
        multiplayer_ready.store(true);
    }
    if (initialized && !(multiplayer_ports() && !multiplayer_ready.load())) {
        // Advance the existing envelope on the host loop. UI/profile changes
        // are applied separately by process_pending_ui under the UI mutex.
        recompinput::update_rumble();
    }
}

bool get(int controller, std::uint16_t* buttons, float* x, float* y) {
    std::lock_guard lock{adapter_mutex};
    const bool single_player = !multiplayer_ports();
    if (!initialized || controller < 0 || controller >= kPlayerCount) {
        static std::atomic_bool logged_unassigned = false;
        if (WR64_DIAGNOSTIC_ENABLED && !logged_unassigned.exchange(true)) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[input] player %d is not connected\n", controller + 1));
        }
        return false;
    }
    // Native startup caches osContInit's port bitmap and never queries again.
    // Reserve P2 from boot, but never aggregate any single-player input into it.
    if (single_player && controller == 1) return neutral_input(buttons, x, y);
    // Keep the two virtual ports present while choosing/reconnecting devices.
    // Returning one physical port here makes the native game alias P2 to P1.
    if (!single_player && (!multiplayer_ready.load() ||
        recompinput::playerassignment::is_active() ||
        !assigned_device_present(0) || !assigned_device_present(1))) {
        multiplayer_ready.store(false);
        return neutral_input(buttons, x, y);
    }
    static std::atomic_bool logged_assigned = false;
    if (WR64_DIAGNOSTIC_ENABLED && !logged_assigned.exchange(true)) {
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[input] player %d active (%s mode)\n", controller + 1,
            single_player ? "single-player" : "assigned"));
    }
    const bool result = recompinput::profiles::get_n64_input(controller, buttons, x, y);
    static std::atomic_bool logged_activity = false;
    if (WR64_DIAGNOSTIC_ENABLED && (*buttons != 0 || *x != 0.0f || *y != 0.0f) && !logged_activity.exchange(true)) {
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[input] first game input buttons=%04X stick=(%.3f,%.3f)\n",
            *buttons, *x, *y));
    }
    return result;
}

void set_rumble(int controller, bool enabled) {
    std::lock_guard lock{adapter_mutex};
    const bool single_player = !multiplayer_ports();
    if (initialized && controller >= 0 && controller < kPlayerCount &&
        ((single_player && controller == 0) ||
         (!single_player && multiplayer_ready.load() &&
          !recompinput::playerassignment::is_active() && assigned_device_present(controller)))) {
        static std::array<int, kPlayerCount> last_state = {-1, -1};
        if (WR64_DIAGNOSTIC_ENABLED && last_state[controller] != static_cast<int>(enabled)) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[rumble] player %d motor %s\n",
                controller + 1, enabled ? "on" : "off"));
            last_state[controller] = static_cast<int>(enabled);
        }
        recompinput::set_rumble(controller, enabled);
    }
}

ultramodern::input::connected_device_info_t get_connected_device_info(int controller) {
    std::lock_guard lock{adapter_mutex};
    using ultramodern::input::Device;
    using ultramodern::input::Pak;
    if (!initialized || controller < 0 || controller >= kPlayerCount) {
        return {Device::None, Pak::None};
    }
    // Both virtual ports must exist at osContInit; native startup retains their
    // physical mapping. SP P2 reads remain neutral and cannot request rumble.
    // RecompFrontend safely ignores the motor request when that player's
    // assigned device has no physical haptics (for example, a keyboard).
    return {Device::Controller, Pak::RumblePak};
}
}

#else
namespace wr64::input {
void initialize() {}
void shutdown() {}
bool ready() { return false; }
void update_rumble() {}
void set_multiplayer_enabled(bool) {}
bool multiplayer_requested() { return false; }
void request_multiplayer_assignment() {}
void process_pending_ui() {}
}
#endif
