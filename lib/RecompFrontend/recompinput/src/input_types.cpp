#include "recompinput.h"
#include <string>
#include <array>
#include <unordered_map>
#include <unordered_set>

namespace recompinput {

#define DEFINE_INPUT(name, value, readable) readable,
static std::array<std::string, num_game_inputs> game_input_names = {
    DEFINE_ALL_INPUTS()
};
#undef DEFINE_INPUT

constexpr std::array<std::string, num_game_inputs> get_default_game_input_descriptions() {
#define DEFINE_INPUT(name, value, readable) "",
    std::array<std::string, num_game_inputs> descriptions = {
        DEFINE_ALL_INPUTS()
    };
    descriptions[static_cast<size_t>(GameInput::TOGGLE_MENU)] = "Open or close this configuration menu from in game.";
    descriptions[static_cast<size_t>(GameInput::ACCEPT_MENU)] = "In the recomp interface, performs the action for the currently highlighted item. Like pressing a button, or toggling a switch.";
    descriptions[static_cast<size_t>(GameInput::BACK_MENU)] = "In the recomp interface, returns to the header or backs out to a previous menu.";
    descriptions[static_cast<size_t>(GameInput::APPLY_MENU)] = "In the recomp interface, if changes are made to a configuration that requires applying your settings, this will apply the current changes.";
    descriptions[static_cast<size_t>(GameInput::TAB_LEFT_MENU)] = "In the recomp interface, switches the active tab to the one on the left of the current tab.";
    descriptions[static_cast<size_t>(GameInput::TAB_RIGHT_MENU)] = "In the recomp interface, switches the active tab to the one on the right of the current tab.";
#undef DEFINE_INPUT
    return descriptions;
}

static std::array<std::string, num_game_inputs> game_input_descriptions = get_default_game_input_descriptions();

#define DEFINE_INPUT(name, value, readable) #name,
static const std::array<std::string, num_game_inputs> game_input_enum_names = {
    DEFINE_ALL_INPUTS()
};
#undef DEFINE_INPUT

static std::unordered_set<GameInput> disabled_game_inputs = {};

const std::string& get_game_input_name(GameInput input) {
    return game_input_names.at(static_cast<size_t>(input));
}

void set_game_input_name(GameInput input, const std::string& new_name) {
    game_input_names.at(static_cast<size_t>(input)) = new_name;
}

const std::string& get_game_input_description(GameInput input) {
    return game_input_descriptions.at(static_cast<size_t>(input));
}

void set_game_input_description(GameInput input, const std::string& new_description) {
    game_input_descriptions.at(static_cast<size_t>(input)) = new_description;
}

bool get_game_input_disabled(GameInput input) {
    return disabled_game_inputs.find(input) != disabled_game_inputs.end();
}

void set_game_input_disabled(GameInput input, bool disabled) {
    if (disabled) {
        disabled_game_inputs.insert(input);
    } else {
        disabled_game_inputs.erase(input);
    }
}

bool get_game_input_clearable(GameInput input) {
    return !(input == GameInput::TOGGLE_MENU || input == GameInput::ACCEPT_MENU);
}

bool get_game_input_is_menu(GameInput input) {
#define DEFINE_INPUT(name, value, readable) case GameInput::name: return true;

    switch (input) {
        DEFINE_RECOMP_UI_INPUTS()
    default:
        return false;
    }

#undef DEFINE_INPUT
}

const std::string& get_game_input_enum_name(GameInput input) {
    return game_input_enum_names.at(static_cast<size_t>(input));
}

static std::string controller_button_to_string(SDL_GameControllerButton button) {
    switch (button) {
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:
        return PF_GAMEPAD_A;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B:
        return PF_GAMEPAD_B;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X:
        return PF_GAMEPAD_X;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y:
        return PF_GAMEPAD_Y;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK:
        return PF_XBOX_VIEW;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_GUIDE:
        return PF_GAMEPAD_HOME;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START:
        return PF_XBOX_MENU;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSTICK:
        return PF_ANALOG_L_CLICK;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        return PF_ANALOG_R_CLICK;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        return PF_XBOX_LEFT_SHOULDER;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        return PF_XBOX_RIGHT_SHOULDER;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP:
        return PF_DPAD_UP;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        return PF_DPAD_DOWN;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        return PF_DPAD_LEFT;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        return PF_DPAD_RIGHT;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MISC1:
        return PF_STEAM_OPTIONS;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_PADDLE1:
        return PF_GAMEPAD_L4;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_PADDLE2:
        return PF_GAMEPAD_R4;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_PADDLE3:
        return PF_GAMEPAD_L5;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_PADDLE4:
        return PF_GAMEPAD_R5;
    case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_TOUCHPAD:
        return PF_SONY_TOUCHPAD;
    default:
        return recompinput::unknown_device_input;
    }
}

static std::unordered_map<SDL_Scancode, std::string> scancode_codepoints{
    {SDL_SCANCODE_LEFT, PF_KEYBOARD_LEFT},
    // NOTE: UP and RIGHT are swapped with promptfont.
    {SDL_SCANCODE_UP, PF_KEYBOARD_RIGHT},
    {SDL_SCANCODE_RIGHT, PF_KEYBOARD_UP},
    {SDL_SCANCODE_DOWN, PF_KEYBOARD_DOWN},
    {SDL_SCANCODE_A, PF_KEYBOARD_A},
    {SDL_SCANCODE_B, PF_KEYBOARD_B},
    {SDL_SCANCODE_C, PF_KEYBOARD_C},
    {SDL_SCANCODE_D, PF_KEYBOARD_D},
    {SDL_SCANCODE_E, PF_KEYBOARD_E},
    {SDL_SCANCODE_F, PF_KEYBOARD_F},
    {SDL_SCANCODE_G, PF_KEYBOARD_G},
    {SDL_SCANCODE_H, PF_KEYBOARD_H},
    {SDL_SCANCODE_I, PF_KEYBOARD_I},
    {SDL_SCANCODE_J, PF_KEYBOARD_J},
    {SDL_SCANCODE_K, PF_KEYBOARD_K},
    {SDL_SCANCODE_L, PF_KEYBOARD_L},
    {SDL_SCANCODE_M, PF_KEYBOARD_M},
    {SDL_SCANCODE_N, PF_KEYBOARD_N},
    {SDL_SCANCODE_O, PF_KEYBOARD_O},
    {SDL_SCANCODE_P, PF_KEYBOARD_P},
    {SDL_SCANCODE_Q, PF_KEYBOARD_Q},
    {SDL_SCANCODE_R, PF_KEYBOARD_R},
    {SDL_SCANCODE_S, PF_KEYBOARD_S},
    {SDL_SCANCODE_T, PF_KEYBOARD_T},
    {SDL_SCANCODE_U, PF_KEYBOARD_U},
    {SDL_SCANCODE_V, PF_KEYBOARD_V},
    {SDL_SCANCODE_W, PF_KEYBOARD_W},
    {SDL_SCANCODE_X, PF_KEYBOARD_X},
    {SDL_SCANCODE_Y, PF_KEYBOARD_Y},
    {SDL_SCANCODE_Z, PF_KEYBOARD_Z},
    {SDL_SCANCODE_0, PF_KEYBOARD_0},
    {SDL_SCANCODE_1, PF_KEYBOARD_1},
    {SDL_SCANCODE_2, PF_KEYBOARD_2},
    {SDL_SCANCODE_3, PF_KEYBOARD_3},
    {SDL_SCANCODE_4, PF_KEYBOARD_4},
    {SDL_SCANCODE_5, PF_KEYBOARD_5},
    {SDL_SCANCODE_6, PF_KEYBOARD_6},
    {SDL_SCANCODE_7, PF_KEYBOARD_7},
    {SDL_SCANCODE_8, PF_KEYBOARD_8},
    {SDL_SCANCODE_9, PF_KEYBOARD_9},
    {SDL_SCANCODE_ESCAPE, PF_KEYBOARD_ESCAPE},
    {SDL_SCANCODE_F1, PF_KEYBOARD_F1},
    {SDL_SCANCODE_F2, PF_KEYBOARD_F2},
    {SDL_SCANCODE_F3, PF_KEYBOARD_F3},
    {SDL_SCANCODE_F4, PF_KEYBOARD_F4},
    {SDL_SCANCODE_F5, PF_KEYBOARD_F5},
    {SDL_SCANCODE_F6, PF_KEYBOARD_F6},
    {SDL_SCANCODE_F7, PF_KEYBOARD_F7},
    {SDL_SCANCODE_F8, PF_KEYBOARD_F8},
    {SDL_SCANCODE_F9, PF_KEYBOARD_F9},
    {SDL_SCANCODE_F10, PF_KEYBOARD_F10},
    {SDL_SCANCODE_F11, PF_KEYBOARD_F11},
    {SDL_SCANCODE_F12, PF_KEYBOARD_F12},
    {SDL_SCANCODE_F13, "F13"},
    {SDL_SCANCODE_F14, "F14"},
    {SDL_SCANCODE_F15, "F15"},
    {SDL_SCANCODE_F16, "F16"},
    {SDL_SCANCODE_F17, "F17"},
    {SDL_SCANCODE_F18, "F18"},
    {SDL_SCANCODE_F19, "F19"},
    {SDL_SCANCODE_F20, "F20"},
    {SDL_SCANCODE_F21, "F21"},
    {SDL_SCANCODE_F22, "F22"},
    {SDL_SCANCODE_F23, "F23"},
    {SDL_SCANCODE_F24, "F24"},
    {SDL_SCANCODE_PRINTSCREEN, PF_KEYBOARD_PRINT_SCREEN},
    {SDL_SCANCODE_SCROLLLOCK, PF_KEYBOARD_SCROLL_LOCK},
    {SDL_SCANCODE_PAUSE, PF_KEYBOARD_PAUSE},
    {SDL_SCANCODE_INSERT, PF_KEYBOARD_INSERT},
    {SDL_SCANCODE_HOME, PF_KEYBOARD_HOME},
    {SDL_SCANCODE_PAGEUP, PF_KEYBOARD_PAGE_UP},
    {SDL_SCANCODE_DELETE, PF_KEYBOARD_DELETE},
    {SDL_SCANCODE_END, PF_KEYBOARD_END},
    {SDL_SCANCODE_PAGEDOWN, PF_KEYBOARD_PAGE_DOWN},
    {SDL_SCANCODE_SPACE, PF_KEYBOARD_SPACE},
    {SDL_SCANCODE_BACKSPACE, PF_KEYBOARD_BACKSPACE},
    {SDL_SCANCODE_TAB, PF_KEYBOARD_TAB},
    {SDL_SCANCODE_RETURN, PF_KEYBOARD_ENTER},
    {SDL_SCANCODE_CAPSLOCK, PF_KEYBOARD_CAPS},
    {SDL_SCANCODE_NUMLOCKCLEAR, PF_KEYBOARD_NUM_LOCK},
    {SDL_SCANCODE_LSHIFT, "L" PF_KEYBOARD_SHIFT},
    {SDL_SCANCODE_RSHIFT, "R" PF_KEYBOARD_SHIFT},
};

static std::string keyboard_input_to_string(SDL_Scancode key) {
    if (scancode_codepoints.find(key) != scancode_codepoints.end()) {
        return scancode_codepoints[key];
    }
    return recompinput::unknown_device_input;
}

static std::string controller_axis_to_string(int axis) {
    bool positive = axis > 0;
    SDL_GameControllerAxis actual_axis = SDL_GameControllerAxis(abs(axis) - 1);
    switch (actual_axis) {
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX:
        return positive ? PF_ANALOG_L_RIGHT : PF_ANALOG_L_LEFT;
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY:
        return positive ? PF_ANALOG_L_DOWN : PF_ANALOG_L_UP;
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX:
        return positive ? PF_ANALOG_R_RIGHT : PF_ANALOG_R_LEFT;
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY:
        return positive ? PF_ANALOG_R_DOWN : PF_ANALOG_R_UP;
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT:
        return positive ? PF_XBOX_LEFT_TRIGGER : PF_XBOX_LEFT_TRIGGER_PULL;
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
        return positive ? PF_XBOX_RIGHT_TRIGGER : PF_XBOX_RIGHT_TRIGGER_PULL;
    default:
        return recompinput::unknown_device_input;
        //! Does not render correctly. Have not encountered any unknown axis yet.
        // return "Axis " + std::to_string(actual_axis) + (positive ? '+' : '-');
    }
}

std::string recompinput::InputField::to_string() const {
    switch (input_type) {
    case InputType::None:
        return "";
    case InputType::ControllerDigital:
        return controller_button_to_string((SDL_GameControllerButton)input_id);
    case InputType::ControllerAnalog:
        return controller_axis_to_string(input_id);
    case InputType::Keyboard:
        return keyboard_input_to_string((SDL_Scancode)input_id);
    default:
        return recompinput::unknown_device_input;
    }
}

};
