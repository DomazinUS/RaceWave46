#ifndef __RECOMP_INPUT_MAPPING_H__
#define __RECOMP_INPUT_MAPPING_H__

#include "input_types.h"
#include "SDL.h"

namespace recompinput {
    constexpr SDL_GameControllerButton SDL_CONTROLLER_BUTTON_SOUTH = SDL_CONTROLLER_BUTTON_A;
    constexpr SDL_GameControllerButton SDL_CONTROLLER_BUTTON_EAST = SDL_CONTROLLER_BUTTON_B;
    constexpr SDL_GameControllerButton SDL_CONTROLLER_BUTTON_WEST = SDL_CONTROLLER_BUTTON_X;
    constexpr SDL_GameControllerButton SDL_CONTROLLER_BUTTON_NORTH = SDL_CONTROLLER_BUTTON_Y;
    using default_game_input_device_mapping = std::unordered_map<GameInput, std::vector<InputField>>;

    const std::vector<InputField>& get_default_mapping_for_input(recompinput::InputDevice device, const GameInput input);
    
    // Both setters should be called before any calls to get_default_mapping_for_input.

    /**
     * Sets the default mapping for a controller input.
     * 
     * Each input field should have `InputType::ControllerDigital` or `InputType::ControllerAnalog`,
     * or simply use `InputField::controller_digital` or `InputField::controller_analog` factory methods to create each of the `fields`.
     * 
     * See `default_n64_mappings_controller` in `input_mapping.cpp` for current defaults.
     * 
     * Example (Maps the first paddle and the left analog stick (positive) to the Z button):
     * 
```cpp
    set_default_mapping_for_controller(
        GameInput::Z,
        {
            InputField::controller_digital(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_PADDLE1),
            InputField::controller_analog(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX),
        }
    ); 
```
    */
    void set_default_mapping_for_controller(GameInput input, const std::vector<InputField>& fields);

    /**
     * Sets the default mapping for a keyboard input.
     * 
     * Each input field should have `InputType::Keyboard`,
     * or use the `InputField::keyboard` factory method to create the `fields`.
     * 
     * See `default_n64_mappings_keyboard` in `input_mapping.cpp` for current defaults.
     * 
     * Example:
     * 
```cpp
    set_default_mapping_for_keyboard(
        GameInput::Z,
        {
            InputField::keyboard(SDL_SCANCODE_Z),
            InputField::keyboard(SDL_SCANCODE_X),
        }
    ); 
```
    */
    void set_default_mapping_for_keyboard(GameInput input, const std::vector<InputField>& fields);
}

#endif
