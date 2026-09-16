#include <algorithm>
#include <mutex>
#include <span>
#include <atomic>
#include <cstdio>

#include "recompinput/recompinput.h"
#include "recompinput/input_state.h"
#include "recompinput/input_binding.h"
#include "recompinput/players.h"
#include "recompui/config.h"

using namespace recompinput;

template <typename T>
using InputArray = std::array<T, max_num_players_supported>;

static struct {
    const Uint8* keys = nullptr;
    SDL_Keymod keymod = SDL_Keymod::KMOD_NONE;
    int numkeys = 0;
    std::atomic_int32_t mouse_wheel_pos = 0;
    std::mutex controllers_mutex;
    std::vector<SDL_GameController*> detected_controllers{};
    std::unordered_map<SDL_JoystickID, ControllerState> controller_states;

    std::array<float, 2> mouse_delta{};
    std::mutex pending_input_mutex;
    std::array<float, 2> pending_mouse_delta{};

    InputArray<float> cur_rumble{};
    InputArray<bool> rumble_active{};
} InputState;

void recompinput::poll_inputs() {
    InputState.keys = SDL_GetKeyboardState(&InputState.numkeys);
    InputState.keymod = SDL_GetModState();
    static bool first_poll = true;

    {
        std::lock_guard lock{ InputState.controllers_mutex };
        InputState.detected_controllers.clear();

        static std::vector<size_t> free_controllers;
        free_controllers.clear();

        for (const auto& [id, state] : InputState.controller_states) {
            (void)id; // Avoid unused variable warning.
            SDL_GameController* controller = state.controller;
            if (controller != nullptr) {
                free_controllers.emplace_back(InputState.detected_controllers.size());
                InputState.detected_controllers.push_back(controller);
            }
        }
    }

    // Read the deltas while resetting them to zero.
    {
        std::lock_guard lock{ InputState.pending_input_mutex };

        for (auto &state_pair : InputState.controller_states) {
            ControllerState &state = state_pair.second;
            state.rotation_delta = state.pending_rotation_delta;
            state.pending_rotation_delta = { 0.0f, 0.0f };
        }

        InputState.mouse_delta = InputState.pending_mouse_delta;
        InputState.pending_mouse_delta = { 0.0f, 0.0f };
    }
}

void recompinput::set_rumble(int controller_num, bool on) {
    InputState.rumble_active[controller_num] = on;
}

void recompinput::reset_rumble() {
    InputState.rumble_active.fill(false);
    InputState.cur_rumble.fill(0.0f);
    std::lock_guard lock{ InputState.controllers_mutex };
    for (const auto& [id, state] : InputState.controller_states) {
        (void)id;
        if (state.controller != nullptr && SDL_GameControllerGetAttached(state.controller)) {
            SDL_JoystickRumble(SDL_GameControllerGetJoystick(state.controller), 0, 0, 0);
        }
    }
}

static float smoothstep(float from, float to, float amount) {
    amount = (amount * amount) * (3.0f - 2.0f * amount);
    return std::lerp(from, to, amount);
}

// Update rumble to attempt to mimic the way n64 rumble ramps up and falls off
void recompinput::update_rumble() {
    auto do_rumble = [](SDL_GameController* controller, uint16_t rumble_strength, uint32_t duration) {
        if (controller == nullptr || !SDL_GameControllerGetAttached(controller)) return;
        SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);
        SDL_JoystickID joystick_id = SDL_JoystickInstanceID(joystick);
        ControllerState &state = InputState.controller_states[joystick_id];

        // Skip setting rumble for controllers that failed to rumble previously.
        if (state.rumble_failed) {
           return;
        }
        // SDL maps DualSense low/high output to its left/right actuators.
        // Send the existing mono N64 envelope to both; retain the established
        // high-channel response for other controllers and USB adapters.
        const uint16_t low_strength = SDL_GameControllerGetType(controller) == SDL_CONTROLLER_TYPE_PS5
            ? rumble_strength : 0;
        int err = SDL_JoystickRumble(joystick, low_strength, rumble_strength, duration);
        if (err != 0) {
            std::fprintf(stderr, "[rumble] controller %d output failed: %s\n",
                int(joystick_id), SDL_GetError());
            state.rumble_failed = true;
        }
    };

    // Skip rumble processing if the game doesn't have a rumble strength option. 
    if (!recompui::config::general::has_rumble_strength_option()) {
        return;
    }
    size_t rumbles_to_run = recompinput::players::is_single_player_mode() ? 1 : recompinput::players::get_number_of_assigned_players();
    if (rumbles_to_run > InputState.cur_rumble.size()) {
        rumbles_to_run = InputState.cur_rumble.size();
    }
    for (size_t i = 0; i < rumbles_to_run; i++) {
        // Note: values are not accurate! just approximations based on feel
        if (InputState.rumble_active[i]) {
            InputState.cur_rumble[i] += 0.17f;
            if (InputState.cur_rumble[i] > 1) InputState.cur_rumble[i] = 1;
        }
        else {
            InputState.cur_rumble[i] *= 0.92f;
            InputState.cur_rumble[i] -= 0.01f;
            if (InputState.cur_rumble[i] < 0) InputState.cur_rumble[i] = 0;
        }
        float smooth_rumble = smoothstep(0, 1, InputState.cur_rumble[i]);

        uint16_t rumble_strength = smooth_rumble * (recompui::config::general::get_rumble_strength(i) * 0xFFFF / 100);
        // Renew active output on every host update, including unchanged levels.
        // SDL's input pump expires an unrefreshed command; this is not a hardware
        // timeout if that pump also stalls. Zero output remains an immediate stop.
        constexpr uint32_t rumble_refresh_duration_ms = 50;
        const uint32_t duration = rumble_strength != 0 ? rumble_refresh_duration_ms : 0;
        {
            std::lock_guard lock{ InputState.controllers_mutex };
            if (recompinput::players::is_single_player_mode()) {
                for (const auto &controller : InputState.detected_controllers) {
                    do_rumble(controller, rumble_strength, duration);
                }
            }
            else {
                auto &player = recompinput::players::get_player(i);
                if (player.controller != nullptr) {
                    do_rumble(player.controller, rumble_strength, duration);
                }
            }
        }
    }
}

bool controller_button_state(int controller_num, int32_t input_id) {
    if (input_id >= 0 && input_id < SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX) {
        SDL_GameControllerButton button = (SDL_GameControllerButton)input_id;
        bool ret = false;
        {
            std::lock_guard lock{ InputState.controllers_mutex };
            if (recompinput::players::is_single_player_mode()) {
                for (const auto &controller : InputState.detected_controllers) {
                    ret |= SDL_GameControllerGetButton(controller, button);
                }
            }
            else {
                auto &player = recompinput::players::get_player(controller_num);
                if (player.controller != nullptr) {
                    ret |= SDL_GameControllerGetButton(player.controller, button);
                }
            }
        }

        return ret;
    }
    return false;
}

static std::atomic_bool right_analog_suppressed = false;

float controller_axis_state(int controller_num, int32_t input_id, bool allow_suppression) {
    if (abs(input_id) - 1 < SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX) {
        SDL_GameControllerAxis axis = (SDL_GameControllerAxis)(abs(input_id) - 1);
        bool negative_range = input_id < 0;
        float ret = 0.0f;

        {
            auto gather_axis_state = [&](SDL_GameController* controller) {
                float cur_val = SDL_GameControllerGetAxis(controller, axis) * (1 / 32768.0f);
                if (negative_range) {
                    cur_val = -cur_val;
                }

                // Check if this input is a right analog axis and suppress it accordingly.
                if (allow_suppression && right_analog_suppressed.load() &&
                    (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX || axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY)) {
                    cur_val = 0;
                }

                return std::clamp(cur_val, 0.0f, 1.0f);
            };

            std::lock_guard lock{ InputState.controllers_mutex };
            if (recompinput::players::is_single_player_mode()) {
                for (SDL_GameController *controller : InputState.detected_controllers) {
                    float controller_state = gather_axis_state(controller);
                    if (fabsf(controller_state) > fabsf(ret)) {
                        ret = controller_state;
                    }
                }
            }
            else {
                auto &player = recompinput::players::get_player(controller_num);
                if (player.controller != nullptr) {
                    ret = gather_axis_state(player.controller);
                }
            }
        }

        return std::clamp(ret, 0.0f, 1.0f);
    }
    return false;
}

bool recompinput::should_override_keystate(SDL_Scancode key, SDL_Keymod mod) {
    // Override Enter when Alt is held.
    if (key == SDL_Scancode::SDL_SCANCODE_RETURN) {
        if (mod & SDL_Keymod::KMOD_ALT) {
            return true;
        }
    }

    return false;
}

float recompinput::get_input_analog(int controller_num, const InputField& field) {
    switch (field.input_type) {
    case InputType::Keyboard:
        if (InputState.keys && field.input_id >= 0 && field.input_id < InputState.numkeys) {
            if (should_override_keystate(static_cast<SDL_Scancode>(field.input_id), InputState.keymod)) {
                return 0.0f;
            }
            return InputState.keys[field.input_id] ? 1.0f : 0.0f;
        }
        return 0.0f;
    case InputType::ControllerDigital:
        return controller_button_state(controller_num, field.input_id) ? 1.0f : 0.0f;
    case InputType::ControllerAnalog:
        return controller_axis_state(controller_num, field.input_id, true);
    case InputType::Mouse:
        // TODO mouse support
        return 0.0f;
    case InputType::None:
        return false;
    }
}

float recompinput::get_input_analog(int controller_num, const std::span<const InputField> fields) {
    float ret = 0.0f;
    for (const auto& field : fields) {
        ret += get_input_analog(controller_num, field);
    }
    return std::clamp(ret, 0.0f, 1.0f);
}

bool recompinput::get_input_digital(int controller_num, const InputField& field) {
    switch (field.input_type) {
    case InputType::Keyboard:
        if (InputState.keys && field.input_id >= 0 && field.input_id < InputState.numkeys) {
            if (should_override_keystate(static_cast<SDL_Scancode>(field.input_id), InputState.keymod)) {
                return false;
            }
            return InputState.keys[field.input_id] != 0;
        }
        return false;
    case InputType::ControllerDigital:
        return controller_button_state(controller_num, field.input_id);
    case InputType::ControllerAnalog:
        // TODO adjustable threshold
        return controller_axis_state(controller_num, field.input_id, true) >= recompinput::axis_digital_threshold;
    case InputType::Mouse:
        // TODO mouse support
        return false;
    case InputType::None:
        return false;
    }
}

bool recompinput::get_input_digital(int controller_num, const std::span<const InputField> fields) {
    bool ret = 0;
    for (const auto& field : fields) {
        ret |= get_input_digital(controller_num, field);
    }
    return ret;
}

void recompinput::get_gyro_deltas(int controller_num, float* x, float* y) {
    float sensitivity = (float)recompui::config::general::get_gyro_sensitivity() / 100.0f;
    std::array<float, 2> cur_rotation_delta = { 0.0f, 0.0f };

    if (players::is_single_player_mode()) {
        {
            std::lock_guard lock{ InputState.controllers_mutex };
            for (const auto &state_pair : InputState.controller_states) {
                const ControllerState &state = state_pair.second;
                cur_rotation_delta[0] += state.rotation_delta[0];
                cur_rotation_delta[1] += state.rotation_delta[1];
            }
        }

    } else {
        auto &player = players::get_player(controller_num);
        if (player.controller == nullptr) {
            *x = 0.0f;
            *y = 0.0f;
            return;
        }
        SDL_JoystickID joystick_id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(player.controller));
        ControllerState &state = get_controller_state(joystick_id);
        cur_rotation_delta = state.rotation_delta;
    }

    *x = cur_rotation_delta[0] * sensitivity;
    *y = cur_rotation_delta[1] * sensitivity;
}

void recompinput::get_mouse_deltas(float* x, float* y) {
    std::array<float, 2> cur_mouse_delta = InputState.mouse_delta;
    float sensitivity = (float)recompui::config::general::get_mouse_sensitivity() / 100.0f;
    *x = cur_mouse_delta[0] * sensitivity;
    *y = cur_mouse_delta[1] * sensitivity;
}

void recompinput::apply_joystick_deadzone(float x_in, float y_in, float* x_out, float* y_out) {
    float joystick_deadzone = (float)recompui::config::general::get_joystick_deadzone() / 100.0f;

    if (fabsf(x_in) < joystick_deadzone) {
        x_in = 0.0f;
    }
    else {
        if (x_in > 0.0f) {
            x_in -= joystick_deadzone;
        }
        else {
            x_in += joystick_deadzone;
        }

        x_in /= (1.0f - joystick_deadzone);
    }

    if (fabsf(y_in) < joystick_deadzone) {
        y_in = 0.0f;
    }
    else {
        if (y_in > 0.0f) {
            y_in -= joystick_deadzone;
        }
        else {
            y_in += joystick_deadzone;
        }

        y_in /= (1.0f - joystick_deadzone);
    }

    *x_out = x_in;
    *y_out = y_in;
}

void recompinput::get_right_analog(int controller_num, float* x, float* y) {
    float x_val =
        controller_axis_state(controller_num, (SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX + 1), false) -
        controller_axis_state(controller_num, -(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX + 1), false);
    float y_val =
        controller_axis_state(controller_num, (SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY + 1), false) -
        controller_axis_state(controller_num, -(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY + 1), false);
    apply_joystick_deadzone(x_val, y_val, x, y);
}

void recompinput::set_right_analog_suppressed(bool suppressed) {
    right_analog_suppressed.store(suppressed);
}

// Disable input if any menu that blocks input is open.
bool recompinput::game_input_disabled() {
    return recompui::is_context_capturing_input();
}

// Disable all input if an input is being polled or currently binding.
bool recompinput::all_input_disabled() {
    return
        recompinput::playerassignment::is_blocking_input() ||
        recompinput::binding::is_binding();
}

ControllerState &recompinput::get_controller_state(SDL_JoystickID joystick_id) {
    std::lock_guard lock{ InputState.controllers_mutex };
    return InputState.controller_states[joystick_id];
}

SDL_GameController *recompinput::get_controller_from_joystick_id(SDL_JoystickID joystick_id) {
    std::lock_guard lock{ InputState.controllers_mutex };
    auto it = InputState.controller_states.find(joystick_id);
    if (it != InputState.controller_states.end()) {
        return it->second.controller;
    }
    return nullptr;
}

void recompinput::add_controller_state(SDL_JoystickID joystick_id, SDL_GameController* controller) {
    std::lock_guard lock{ InputState.controllers_mutex };
    ControllerState& state = InputState.controller_states[SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller))];
    state.controller = controller;
}

void recompinput::remove_controller_state(SDL_JoystickID joystick_id) {
    std::lock_guard lock{ InputState.controllers_mutex };
    InputState.controller_states.erase(joystick_id);
}

void recompinput::add_rotation_deltas(SDL_JoystickID joystick_id, float rot_x, float rot_y) {
    std::lock_guard lock{ InputState.pending_input_mutex };
    ControllerState &state = InputState.controller_states[joystick_id];
    state.pending_rotation_delta[0] += rot_x;
    state.pending_rotation_delta[1] += rot_y;
}

void recompinput::add_mouse_deltas(float delta_x, float delta_y) {
    std::lock_guard lock{ InputState.pending_input_mutex };
    InputState.pending_mouse_delta[0] += delta_x;
    InputState.pending_mouse_delta[1] += delta_y;
}
void recompinput::add_mouse_wheel_delta(int32_t delta) {
    InputState.mouse_wheel_pos.fetch_add(delta);
}
