#include <unordered_map>
#include "recompinput.h"

namespace recompinput {

    using default_game_input_device_mapping = std::unordered_map<GameInput, std::vector<InputField>>;

    default_game_input_device_mapping default_n64_mappings_keyboard = {
        { GameInput::A,              { InputField::keyboard(SDL_SCANCODE_SPACE) } },
        { GameInput::B,              { InputField::keyboard(SDL_SCANCODE_LSHIFT) } },
        { GameInput::L,              { InputField::keyboard(SDL_SCANCODE_E) } },
        { GameInput::B,              { InputField::keyboard(SDL_SCANCODE_LSHIFT) } },
        { GameInput::R,              { InputField::keyboard(SDL_SCANCODE_R) } },
        { GameInput::Z,              { InputField::keyboard(SDL_SCANCODE_Q) } },
        { GameInput::START,          { InputField::keyboard(SDL_SCANCODE_RETURN) } },
        { GameInput::C_LEFT,         { InputField::keyboard(SDL_SCANCODE_LEFT) } },
        { GameInput::C_RIGHT,        { InputField::keyboard(SDL_SCANCODE_RIGHT) } },
        { GameInput::C_UP,           { InputField::keyboard(SDL_SCANCODE_UP) } },
        { GameInput::C_DOWN,         { InputField::keyboard(SDL_SCANCODE_DOWN) } },
        { GameInput::DPAD_LEFT,      { InputField::keyboard(SDL_SCANCODE_J) } },
        { GameInput::DPAD_RIGHT,     { InputField::keyboard(SDL_SCANCODE_L) } },
        { GameInput::DPAD_UP,        { InputField::keyboard(SDL_SCANCODE_I) } },
        { GameInput::DPAD_DOWN,      { InputField::keyboard(SDL_SCANCODE_K) } },
        { GameInput::X_AXIS_NEG,     { InputField::keyboard(SDL_SCANCODE_A) } },
        { GameInput::X_AXIS_POS,     { InputField::keyboard(SDL_SCANCODE_D) } },
        { GameInput::Y_AXIS_POS,     { InputField::keyboard(SDL_SCANCODE_W) } },
        { GameInput::Y_AXIS_NEG,     { InputField::keyboard(SDL_SCANCODE_S) } },

        { GameInput::TOGGLE_MENU,    { InputField::keyboard(SDL_SCANCODE_ESCAPE) } },
        { GameInput::ACCEPT_MENU,    { InputField::keyboard(SDL_SCANCODE_RETURN) } },
        { GameInput::BACK_MENU,      { InputField::keyboard(SDL_SCANCODE_F15) } },
        { GameInput::APPLY_MENU,     { InputField::keyboard(SDL_SCANCODE_F) } },
        { GameInput::TAB_LEFT_MENU,  { InputField::keyboard(SDL_SCANCODE_F16) } },
        { GameInput::TAB_RIGHT_MENU, { InputField::keyboard(SDL_SCANCODE_F17) } }
    };

    default_game_input_device_mapping default_n64_mappings_controller = {
        { GameInput::A,              { InputField::controller_digital(SDL_CONTROLLER_BUTTON_SOUTH) } },
        { GameInput::B,              { InputField::controller_digital(SDL_CONTROLLER_BUTTON_WEST) } },
        { GameInput::L,              { InputField::controller_digital(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) } },
        { GameInput::R,              { InputField::controller_analog( SDL_CONTROLLER_AXIS_TRIGGERRIGHT, true) } },
        { GameInput::Z,              { InputField::controller_analog( SDL_CONTROLLER_AXIS_TRIGGERLEFT, true) } },
        { GameInput::START,          { InputField::controller_digital(SDL_CONTROLLER_BUTTON_START) } },
        { GameInput::C_LEFT,         { InputField::controller_analog( SDL_CONTROLLER_AXIS_RIGHTX, false), InputField::controller_digital(SDL_CONTROLLER_BUTTON_NORTH) } },
        { GameInput::C_RIGHT,        { InputField::controller_analog( SDL_CONTROLLER_AXIS_RIGHTX, true),  InputField::controller_digital(SDL_CONTROLLER_BUTTON_EAST) } },
        { GameInput::C_UP,           { InputField::controller_analog( SDL_CONTROLLER_AXIS_RIGHTY, false), InputField::controller_digital(SDL_CONTROLLER_BUTTON_RIGHTSTICK) } },
        { GameInput::C_DOWN,         { InputField::controller_analog( SDL_CONTROLLER_AXIS_RIGHTY, true),  InputField::controller_digital(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) } },
        { GameInput::DPAD_LEFT,      { InputField::controller_digital(SDL_CONTROLLER_BUTTON_DPAD_LEFT) } },
        { GameInput::DPAD_RIGHT,     { InputField::controller_digital(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) } },
        { GameInput::DPAD_UP,        { InputField::controller_digital(SDL_CONTROLLER_BUTTON_DPAD_UP) } },
        { GameInput::DPAD_DOWN,      { InputField::controller_digital(SDL_CONTROLLER_BUTTON_DPAD_DOWN) } },
        { GameInput::X_AXIS_NEG,     { InputField::controller_analog( SDL_CONTROLLER_AXIS_LEFTX, false) } },
        { GameInput::X_AXIS_POS,     { InputField::controller_analog( SDL_CONTROLLER_AXIS_LEFTX, true) } },
        { GameInput::Y_AXIS_POS,     { InputField::controller_analog( SDL_CONTROLLER_AXIS_LEFTY, false) } },
        { GameInput::Y_AXIS_NEG,     { InputField::controller_analog( SDL_CONTROLLER_AXIS_LEFTY, true) } },

        { GameInput::TOGGLE_MENU,    { InputField::controller_digital(SDL_CONTROLLER_BUTTON_BACK) } },
        { GameInput::ACCEPT_MENU,    { InputField::controller_digital(SDL_CONTROLLER_BUTTON_SOUTH) } },
        { GameInput::BACK_MENU,      { InputField::controller_digital(SDL_CONTROLLER_BUTTON_WEST) } },
        { GameInput::APPLY_MENU,     { InputField::controller_digital(SDL_CONTROLLER_BUTTON_NORTH), InputField::controller_digital(SDL_CONTROLLER_BUTTON_START) } },
        { GameInput::TAB_LEFT_MENU,  { InputField::controller_digital(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) } },
        { GameInput::TAB_RIGHT_MENU, { InputField::controller_digital(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) } },
    };

    // Flag to prevent the base game from changing default mappings after they have been used.
    static bool default_mappings_used = false;

    const std::vector<InputField>& get_default_mapping_for_input(recompinput::InputDevice device, const GameInput input) {
        static const std::vector<InputField> empty_input_field{};
        default_mappings_used = true;
        default_game_input_device_mapping *mapping = nullptr;

        switch (device) {
            case InputDevice::Keyboard: mapping = &default_n64_mappings_keyboard; break;
            case InputDevice::Controller: mapping = &default_n64_mappings_controller; break;
            default: return empty_input_field;
        }

        auto it = mapping->find(input);
        if (it != mapping->end()) {
            return it->second;
        }
        return empty_input_field;
    }

    void set_default_mapping_for_controller(GameInput input, const std::vector<InputField>& fields) {
        if (default_mappings_used) {
            throw std::runtime_error("Cannot set default mapping after it has been used.");
        }
        default_n64_mappings_controller[input] = fields;
    }

    void set_default_mapping_for_keyboard(GameInput input, const std::vector<InputField>& fields) {
        if (default_mappings_used) {
            throw std::runtime_error("Cannot set default mapping after it has been used.");
        }
        default_n64_mappings_keyboard[input] = fields;
    }
}
