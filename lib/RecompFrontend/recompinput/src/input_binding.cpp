#include "recompinput.h"
#include "input_binding.h"
#include "input_state.h"
#include "players.h"
#include "profiles.h"

namespace recompinput {

    static struct {
        bool active = false;
        // Designates when binding has been cancelled or completed and the event queue should be purged/ignored.
        bool skip_events = false;
        int player_index = -1;
        recompinput::GameInput game_input = recompinput::GameInput::COUNT;
        int binding_index = -1;
        recompinput::InputField new_binding = {};
        recompinput::InputDevice device = recompinput::InputDevice::COUNT;

        void reset() {
            active = false;
            skip_events = false;
            player_index = -1;
            game_input = recompinput::GameInput::COUNT;
            binding_index = -1;
            new_binding = {};
            device = recompinput::InputDevice::COUNT;
        }
    } BindingState;

    void binding::start_scanning(int player_index, recompinput::GameInput game_input, int binding_index, recompinput::InputDevice device) {
        BindingState.active = true;
        BindingState.skip_events = false;
        BindingState.player_index = player_index;
        BindingState.game_input = game_input;
        BindingState.binding_index = binding_index;
        BindingState.device = device;
    }

    void binding::stop_scanning() {
        BindingState.reset();
        BindingState.skip_events = true;
    }

    bool binding::is_binding() {
        return BindingState.active;
    }

    bool binding::is_controller_being_bound(SDL_JoystickID joystick_id) {
        if (BindingState.device != InputDevice::Controller) {
            return false;
        }

        if (players::is_single_player_mode()) {
            return true;
        }

        const auto& player = players::get_player(BindingState.player_index);
        if (player.controller != nullptr) {
            SDL_JoystickID assigned_id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(player.controller));
            if (assigned_id == joystick_id) {
                return true;
            }
        }

        return false;
    }

    void binding::set_scanned_input(recompinput::InputField value) {
        profiles::set_input_binding(
            profiles::get_input_profile_for_player(BindingState.player_index, BindingState.device),
            BindingState.game_input,
            BindingState.binding_index,
            value
        );
        binding::stop_scanning();
    }

    recompinput::InputDevice binding::get_scanning_device() {
        return BindingState.device;
    }

    bool binding::should_skip_events() {
        return BindingState.skip_events;
    }

    void binding::stop_skipping_events() {
        BindingState.skip_events = false;
    }

    recompinput::GameInput binding::get_scanning_game_input() {
        return BindingState.game_input;
    }
}
