#include "librecomp/config.hpp"
#include "recompui/config.h"
#include "util/steam_deck.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>

namespace recompui {

static bool created_general_config = false;
// UI edits and config loads publish values for the SDL rumble thread. That
// thread must not read Config's storage while the UI changes or reloads it.
static std::array<std::atomic<double>, 2> rumble_strengths{25.0, 25.0};
static bool player_two_rumble_strength = false;

namespace config {
    recomp::config::Config &get_general_config() {
        if (!created_general_config) {
            throw std::runtime_error("General config has not been created yet. Call create_general_tab() first.");
        }
        return config::get_config(config::general::id);
    }

    using EnumOptionVector = const std::vector<recomp::config::ConfigOptionEnumOption>;
    enum class BackgroundInputMode {
        Off,
        On,
        OptionCount
    };
    static EnumOptionVector background_input_options = {
        {BackgroundInputMode::Off, "Off"},
        {BackgroundInputMode::On, "On"},
    };

    template <typename T = uint32_t>
    T get_general_config_enum_value(const std::string& option_id) {
        return static_cast<T>(std::get<uint32_t>(get_general_config().get_option_value(option_id)));
    }

    template <typename T = uint32_t>
    T get_general_config_number_value(const std::string& option_id) {
        return static_cast<T>(std::get<double>(get_general_config().get_option_value(option_id)));
    }

    bool get_general_config_bool_value(const std::string& option_id) {
        return std::get<bool>(get_general_config().get_option_value(option_id));
    }
    
    void general::add_rumble_strength_options(bool has_player_two) {
        recomp::config::Config &config = get_general_config();
        player_two_rumble_strength = has_player_two;
        rumble_strengths[0].store(25.0);
        rumble_strengths[1].store(25.0);
        config.add_percent_number_option(
            general::options::rumble_strength,
            player_two_rumble_strength ? "Player 1 Rumble Strength" : "Rumble Strength",
            "Controls the strength of rumble when using a controller that supports it. "
            "<b>Setting this to zero will disable rumble.</b>",
            25.0
        );
        if (player_two_rumble_strength) {
            config.add_percent_number_option(
                general::options::rumble_strength_p2,
                "Player 2 Rumble Strength",
                "Controls the strength of rumble when using a controller that supports it. "
                "<b>Setting this to zero will disable rumble.</b>",
                25.0);
        }
        const auto publish_strength = [](size_t player) {
            return [player](recomp::config::ConfigValueVariant value,
                recomp::config::ConfigValueVariant, recomp::config::OptionChangeContext) {
                const double percent = std::get<double>(value);
                rumble_strengths[player].store(std::isfinite(percent)
                    ? std::clamp(percent, 0.0, 100.0) : 25.0, std::memory_order_relaxed);
            };
        };
        // Keep the original key for existing saved player-one values.
        config.add_option_change_callback(general::options::rumble_strength, publish_strength(0));
        if (player_two_rumble_strength) {
            config.add_option_change_callback(general::options::rumble_strength_p2, publish_strength(1));
        }
    }

    bool general::has_rumble_strength_option() {
        return get_general_config().has_option(general::options::rumble_strength);
    }

    double general::get_rumble_strength() {
        return get_rumble_strength(0);
    }

    double general::get_rumble_strength(size_t player_index) {
        const size_t index = player_index == 1 && player_two_rumble_strength ? 1 : 0;
        return rumble_strengths[index].load(std::memory_order_relaxed);
    }

    bool general::has_gyro_sensitivity_option() {
        return get_general_config().has_option(general::options::gyro_sensitivity);
    }
    
    double general::get_gyro_sensitivity() {
        return get_general_config_number_value<double>(general::options::gyro_sensitivity);
    }
    
    bool general::has_mouse_sensitivity_option() {
        return get_general_config().has_option(general::options::mouse_sensitivity);
    }
    
    double general::get_mouse_sensitivity() {
        return get_general_config_number_value<double>(general::options::mouse_sensitivity);
    }
    
    double general::get_joystick_deadzone() {
        return get_general_config_number_value<double>(general::options::joystick_deadzone);
    }
    
    bool general::get_background_input_mode_enabled() {
        return get_general_config_enum_value<BackgroundInputMode>(general::options::background_input_mode) == BackgroundInputMode::On;
    }
    
    bool general::get_debug_mode_enabled() {
        return get_general_config_bool_value(general::options::debug_mode);
    }

    recomp::config::Config &create_general_tab(const GeneralTabOptions& options, const std::string &name) {
        created_general_config = true;
        recomp::config::Config &config = recompui::config::create_config_tab(name, general::id, false);

        config.add_bool_option(
            general::options::debug_mode,
            "Debug Mode",
            "Enables debugging features.",
            false,
            true // hidden by default
        );

        if (options.has_rumble_strength) {
            general::add_rumble_strength_options(options.has_player_two_rumble_strength);
        }

        if (options.has_gyro_sensitivity) {
            config.add_percent_number_option(
                general::options::gyro_sensitivity,
                "Gyro Sensitivity",
                "Controls the sensitivity of gyro aiming when using items in first person for controllers that support it."
                "<b>Setting this to zero will disable gyro.</b>"
                "<br />"
                "<br />"
                "<b>Note: To recalibrate controller gyro, set the controller down on a still, flat surface for 5 seconds.</b>",
                25.0
            );
        }

        if (options.has_mouse_sensitivity) {
            config.add_percent_number_option(
                general::options::mouse_sensitivity,
                "Mouse Sensitivity",
                "Controls the sensitivity of mouse aiming when using items in first person. <b>Setting this to zero will disable mouse aiming.</b>"
                "<br />"
                "<br />"
                "<b>Note: This option does not allow mouse buttons to activate items. Mouse aiming is intended to be used with inputs that are mapped to mouse movement, such as gyro on Steam Deck.</b>",
                is_steam_deck() ? 50.0 : 0.0 // steam deck overrides default to 50%
            );
        }

        config.add_percent_number_option(
            general::options::joystick_deadzone,
            "Joystick Deadzone",
            "Applies a deadzone to joystick inputs.",
            5.0
        );

        config.add_enum_option(
            general::options::background_input_mode,
            "Background Input Mode",
            "Allows the game to read controller input when out of focus."
            "<br/>"
            "<b>This setting does not affect keyboard input.</b>",
            background_input_options,
            BackgroundInputMode::On
        );

        return config;
    }
} // namespace config
} // namespace recompui
