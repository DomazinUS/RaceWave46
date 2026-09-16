#ifndef __RECOMP_INPUT_TYPES_H__
#define __RECOMP_INPUT_TYPES_H__

#include <string>
#include <array>
#include "json/json.hpp"
#include "SDL.h"

namespace recompinput {
    #define DEFINE_N64_BUTTON_INPUTS() \
        DEFINE_INPUT(A, 0x8000, "A") \
        DEFINE_INPUT(B, 0x4000, "B") \
        DEFINE_INPUT(Z, 0x2000, "Z") \
        DEFINE_INPUT(L, 0x0020, "L") \
        DEFINE_INPUT(R, 0x0010, "R") \
        DEFINE_INPUT(START, 0x1000, "Start") \
        DEFINE_INPUT(C_UP, 0x0008, "C Up") \
        DEFINE_INPUT(C_DOWN, 0x0004, "C Down") \
        DEFINE_INPUT(C_LEFT, 0x0002, "C Left") \
        DEFINE_INPUT(C_RIGHT, 0x0001, "C Right") \
        DEFINE_INPUT(DPAD_UP, 0x0800, "D-Pad Up") \
        DEFINE_INPUT(DPAD_DOWN, 0x0400, "D-Pad Down") \
        DEFINE_INPUT(DPAD_LEFT, 0x0200, "D-Pad Left") \
        DEFINE_INPUT(DPAD_RIGHT, 0x0100, "D-Pad Right")

    #define DEFINE_N64_AXIS_INPUTS() \
        DEFINE_INPUT(Y_AXIS_POS, 0, "Up") \
        DEFINE_INPUT(Y_AXIS_NEG, 0, "Down") \
        DEFINE_INPUT(X_AXIS_NEG, 0, "Left") \
        DEFINE_INPUT(X_AXIS_POS, 0, "Right") \

    #define DEFINE_RECOMP_UI_INPUTS() \
        DEFINE_INPUT(TOGGLE_MENU, 0, "Toggle Menu") \
        DEFINE_INPUT(ACCEPT_MENU, 0, "Accept (Menu)") \
        DEFINE_INPUT(BACK_MENU, 0, "Back (Menu)") \
        DEFINE_INPUT(APPLY_MENU, 0, "Apply (Menu)") \
        DEFINE_INPUT(TAB_LEFT_MENU, 0, "Tab Left (Menu)") \
        DEFINE_INPUT(TAB_RIGHT_MENU, 0, "Tab Right (Menu)")

    #define DEFINE_ALL_INPUTS() \
        DEFINE_N64_AXIS_INPUTS() \
        DEFINE_N64_BUTTON_INPUTS() \
        DEFINE_RECOMP_UI_INPUTS()

    #define DEFINE_INPUT(name, value, readable) name,
    // - Enum containing every recomp input.
    // - Includes inputs that are specific to menu navigation.
    // - This represents what any controller/keyboard can bind to.
    enum class GameInput {
        DEFINE_ALL_INPUTS()

        COUNT,
        N64_BUTTON_START = A,
        N64_BUTTON_COUNT = C_RIGHT - N64_BUTTON_START + 1,
        N64_AXIS_START = X_AXIS_NEG,
        N64_AXIS_COUNT = Y_AXIS_POS - N64_AXIS_START + 1,
    };
    #undef DEFINE_INPUT

    // What type of source an input comes from (SDL_Scancode, SDL_GameControllerButton, SDL_GameControllerAxis, SDL_BUTTON, etc.)
    enum class InputType {
        None = 0, // Using zero for None ensures that default initialized InputFields are unbound.
        Keyboard,
        Mouse,
        ControllerDigital,
        ControllerAnalog // Axis input_id values are the SDL value + 1
    };

    
    // A single input. Combines the source of the input (see InputType) and a specific key/button/axis.
    struct InputField {
        InputType input_type;
        // Represents a single source input. e.g. A keyboard's shift key, or a controller's R trigger
        int32_t input_id;
        std::string to_string() const;
        auto operator<=>(const InputField& rhs) const = default;

        static InputField keyboard(SDL_Scancode key) {
            return InputField{ InputType::Keyboard, static_cast<int32_t>(key) };
        }

        static InputField controller_digital(SDL_GameControllerButton button) {
            return InputField{ InputType::ControllerDigital, static_cast<int32_t>(button) };
        }

        static InputField controller_analog(SDL_GameControllerAxis axis, bool positive = true) {
            return InputField{ InputType::ControllerAnalog, positive ? (static_cast<int32_t>(axis) + 1) : -(static_cast<int32_t>(axis) + 1) };
        }

        bool is_empty() const {
            return input_type == InputType::None;
        }
    };

    inline void to_json(nlohmann::json& j, const InputField& field) {
        j = nlohmann::json{ {"input_type", field.input_type}, {"input_id", field.input_id} };
    }

    inline void from_json(const nlohmann::json& j, InputField& field) {
        j.at("input_type").get_to(field.input_type);
        j.at("input_id").get_to(field.input_id);
    }

    // Represents the types of mapping/profiles that can be done.
    enum class InputDevice {
        Controller,
        Keyboard,
        COUNT
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(recompinput::InputDevice, {
        { recompinput::InputDevice::Controller, "Controller" },
        { recompinput::InputDevice::Keyboard, "Keyboard" },
    });


    inline const size_t num_game_inputs = static_cast<size_t>(GameInput::COUNT);

    const std::string& get_game_input_name(GameInput input);
    void set_game_input_name(GameInput input, const std::string& new_name);

    const std::string& get_game_input_description(GameInput input);
    void set_game_input_description(GameInput input, const std::string& new_description);

    bool get_game_input_disabled(GameInput input);
    void set_game_input_disabled(GameInput input, bool disabled);

    bool get_game_input_clearable(GameInput input);
    bool get_game_input_is_menu(GameInput input);

    const std::string& get_game_input_enum_name(GameInput input);
}

#endif
