#pragma once

#include <span>

// disable warning: '/*' within block comment [-Wcomment] for GamepadMotion.hpp
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcomment"
#include "GamepadMotion.hpp"
#pragma GCC diagnostic pop

#include "ultramodern/input.hpp"
#include "recompinput/recompinput.h"

namespace recompinput {
    struct ControllerState {
        SDL_GameController* controller;
        std::array<float, 3> latest_accelerometer;
        GamepadMotion motion;
        uint32_t prev_gyro_timestamp;
        std::array<float, 2> rotation_delta{};
        std::array<float, 2> pending_rotation_delta{};
        bool rumble_failed;

        ControllerState() : controller{}, latest_accelerometer{}, motion{}, prev_gyro_timestamp{}, rotation_delta{}, pending_rotation_delta{}, rumble_failed{} {
            motion.Reset();
            motion.SetCalibrationMode(GamepadMotionHelpers::CalibrationMode::Stillness | GamepadMotionHelpers::CalibrationMode::SensorFusion);
        };
    };

    void poll_inputs();
    void set_rumble(int controller_num, bool on);
    void update_rumble();
    // Stop physical motors and discard envelopes before changing player devices.
    void reset_rumble();
    bool should_override_keystate(SDL_Scancode key, SDL_Keymod mod);
    float get_input_analog(int controller_num, const InputField& field);
    float get_input_analog(int controller_num, const std::span<const InputField> fields);
    bool get_input_digital(int controller_num, const InputField& field);
    bool get_input_digital(int controller_num, const std::span<const InputField> fields);
    void get_gyro_deltas(int controller_num, float* x, float* y);
    void get_mouse_deltas(float* x, float* y);
    void get_right_analog(int controller_num, float* x, float* y);
    void apply_joystick_deadzone(float x_in, float y_in, float* x_out, float* y_out);
    void set_right_analog_suppressed(bool suppressed);
    bool game_input_disabled();
    bool all_input_disabled();
    ControllerState &get_controller_state(SDL_JoystickID joystick_id);
    SDL_GameController *get_controller_from_joystick_id(SDL_JoystickID joystick_id);
    void add_controller_state(SDL_JoystickID joystick_id, SDL_GameController* controller);
    void remove_controller_state(SDL_JoystickID joystick_id);
    void add_rotation_deltas(SDL_JoystickID joystick_id, float rot_x, float rot_y);
    void add_mouse_deltas(float delta_x, float delta_y);
    void add_mouse_wheel_delta(int32_t delta);
}
