#include "librecomp/config.hpp"
#include "recompui/config.h"
#include "recompui/renderer.h"

static bool created_graphics_config = false;

namespace recompui {
    namespace config {
        recomp::config::Config &get_graphics_config() {
            if (!created_graphics_config) {
                throw std::runtime_error("Graphics config has not been created yet. Call create_graphics_tab() first.");
            }
            return config::get_config(config::graphics::id);
        }

        using EnumOptionVector = const std::vector<recomp::config::ConfigOptionEnumOption>;
        static EnumOptionVector resolution_options = {
            // Keep saved values separate from the visible multiplier labels.
            {ultramodern::renderer::Resolution::Original, "Original", "1x (Original)"},
            {ultramodern::renderer::Resolution::Original2x, "Original2x", "2x"},
            {ultramodern::renderer::Resolution::Fixed720p, "720p", "3x"},
            {ultramodern::renderer::Resolution::Original4x, "4x", "4x"},
            {ultramodern::renderer::Resolution::Fixed1080p, "1080p", "4.5x"},
            {ultramodern::renderer::Resolution::Original5x, "5x", "5x"},
            {ultramodern::renderer::Resolution::Fixed1440p, "1440p", "6x"},
            {ultramodern::renderer::Resolution::Fixed2160p, "2160p", "9x"},
            {ultramodern::renderer::Resolution::Auto, "Auto", "Auto"},
        };

        enum class DownsamplingOption {
            Off = 0,
            X2 = 2,
            X4 = 4,
        };
        static EnumOptionVector downsampling_options = {
            {DownsamplingOption::Off, "Off"},
            {DownsamplingOption::X2, "2x"},
            {DownsamplingOption::X4, "4x"},
        };

        static EnumOptionVector window_mode_options = {
            {ultramodern::renderer::WindowMode::Windowed, "Windowed"},
            {ultramodern::renderer::WindowMode::Fullscreen, "Fullscreen"}
        };

        #if defined(_WIN32)
        #define ALLOW_D3D12
        #endif
        #if defined(_WIN32) || defined(__linux__)
        #define ALLOW_VULKAN
        #endif
        #if defined(__APPLE__)
        #define ALLOW_METAL
        #endif

        static EnumOptionVector graphics_api_options = {
            {ultramodern::renderer::GraphicsApi::Auto, "Auto"},
        #ifdef ALLOW_D3D12
            {ultramodern::renderer::GraphicsApi::D3D12, "D3D12"},
        #endif
        #ifdef ALLOW_VULKAN
            {ultramodern::renderer::GraphicsApi::Vulkan, "Vulkan"},
        #endif
        #ifdef ALLOW_METAL
            {ultramodern::renderer::GraphicsApi::Metal, "Metal"},
        #endif
        };

        static EnumOptionVector aspect_ratio_options = {
            {ultramodern::renderer::AspectRatio::Original, "Original"},
            {ultramodern::renderer::AspectRatio::Expand, "Expand"},
            // {ultramodern::renderer::AspectRatio::Manual, "Manual"},
        };

        static EnumOptionVector antialiasing_options = {
            {ultramodern::renderer::Antialiasing::None, "None"},
            {ultramodern::renderer::Antialiasing::MSAA2X, "MSAA2X", "2X"},
            {ultramodern::renderer::Antialiasing::MSAA4X, "MSAA4X", "4X"},
            // {ultramodern::renderer::Antialiasing::MSAA8X, "MSAA8X"},
        };

        static EnumOptionVector refresh_rate_options = {
            {ultramodern::renderer::RefreshRate::Original, "Original"},
            {ultramodern::renderer::RefreshRate::Display, "Display"},
            {ultramodern::renderer::RefreshRate::Manual, "Manual"},
        };

        static EnumOptionVector hpfb_options = {
            {ultramodern::renderer::HighPrecisionFramebuffer::Auto, "Auto"},
            {ultramodern::renderer::HighPrecisionFramebuffer::On, "On"},
            {ultramodern::renderer::HighPrecisionFramebuffer::Off, "Off"},
        };

        static EnumOptionVector hud_ratio_mode_options = {
            {ultramodern::renderer::HUDRatioMode::Original, "Original"},
            {ultramodern::renderer::HUDRatioMode::Clamp16x9, "Clamp16x9", "16:9"},
            {ultramodern::renderer::HUDRatioMode::Full, "Expand"},
        };

        static const std::string get_downsampling_details(ultramodern::renderer::Resolution res_option, DownsamplingOption ds_option) {
            if (!ultramodern::renderer::resolution_supports_downsampling(res_option)) {
                return "Available only at 1x and 2x resolution";
            }
            if (ds_option == DownsamplingOption::X2 || ds_option == DownsamplingOption::X4) {
                const int output_height = int(240 * ultramodern::renderer::resolution_scale(res_option));
                const int render_height = output_height * int(ds_option);
                return "Rendered in " + std::to_string(render_height) + "p and scaled to " +
                    std::to_string(output_height) + "p";
            }
            return "";
        }

        using OptionChangeContext = recomp::config::OptionChangeContext;

        static recomp::config::ConfigValueVariant get_graphics_value_variant(const std::string& key, OptionChangeContext change_context) {
            if (change_context == OptionChangeContext::Temporary) {
                return get_graphics_config().get_temp_option_value(key);
            } else {
                return get_graphics_config().get_option_value(key);
            }
        }

        template <typename T, typename ValType>
        T get_graphics_value(const std::string& key, OptionChangeContext change_context = OptionChangeContext::Permanent) {
            return static_cast<T>(std::get<ValType>(get_graphics_value_variant(key, change_context)));
        }

        template <typename T = uint32_t>
        T get_graphics_enum_value(const std::string& key, OptionChangeContext change_context = OptionChangeContext::Permanent) {
            return get_graphics_value<T, uint32_t>(key, change_context);
        }
    
        template <typename T = uint32_t>
        T get_graphics_number_value(const std::string& key, OptionChangeContext change_context = OptionChangeContext::Permanent) {
            return get_graphics_value<T, double>(key, change_context);
        }

        static bool get_graphics_bool_value(const std::string& key, OptionChangeContext change_context = OptionChangeContext::Permanent) {
            return std::get<bool>(get_graphics_value_variant(key, change_context));
        }

        static void determine_downsampling_display(ultramodern::renderer::Resolution res_option, OptionChangeContext change_context) {
            DownsamplingOption ds_opt = get_graphics_enum_value<DownsamplingOption>(graphics::options::ds_option, change_context);
            get_graphics_config().update_option_enum_details(graphics::options::ds_option, get_downsampling_details(res_option, ds_opt));
        }

        static std::string get_framerate_text(uint32_t refresh_rate) {
            return
                "Sets the game's output framerate. This option does not affect gameplay."
                "<br />"
                "<br />"
                "Note: If you have issues with <recomp-color primary>Display</recomp-color> mode while using an external frame limiter, use <recomp-color primary>Manual</recomp-color> mode instead and configure it to that same frame limit."
                "<br />"
                "<br />"
                "<recomp-color primary>Detected display refresh rate: " + std::to_string(refresh_rate) + "hz</recomp-color>";
        }

        static void apply_graphics_config() {
            ultramodern::renderer::GraphicsConfig new_config;
            new_config.developer_mode = get_graphics_bool_value(graphics::options::developer_mode);
            new_config.res_option = get_graphics_enum_value<ultramodern::renderer::Resolution>(graphics::options::res_option);
            new_config.wm_option = get_graphics_enum_value<ultramodern::renderer::WindowMode>(graphics::options::wm_option);
            new_config.hr_option = get_graphics_enum_value<ultramodern::renderer::HUDRatioMode>(graphics::options::hr_option);
            new_config.api_option = get_graphics_enum_value<ultramodern::renderer::GraphicsApi>(graphics::options::api_option);
            new_config.ar_option = get_graphics_enum_value<ultramodern::renderer::AspectRatio>(graphics::options::ar_option);
            new_config.msaa_option = get_graphics_enum_value<ultramodern::renderer::Antialiasing>(graphics::options::msaa_option);
            new_config.rr_option = get_graphics_enum_value<ultramodern::renderer::RefreshRate>(graphics::options::rr_option);
            new_config.hpfb_option = get_graphics_enum_value<ultramodern::renderer::HighPrecisionFramebuffer>(graphics::options::hpfb_option);
            new_config.rr_manual_value = get_graphics_number_value<int>(graphics::options::rr_manual_value);

            new_config.ds_option = get_graphics_enum_value<int>(graphics::options::ds_option);

            ultramodern::renderer::set_graphics_config(new_config);
        }

        void graphics::update_msaa_supported(bool supported) {
            recomp::config::Config &config = get_graphics_config();
            if (!supported) {
                config.update_option_enum_details(
                    graphics::options::msaa_option,
                    supported ? "Available" : "Not available (missing sample positions support)"
                );
                config.update_option_disabled(
                    graphics::options::msaa_option,
                    true
                );
            } else {
                auto max_msaa = recompui::renderer::RT64MaxMSAA();
                if (max_msaa < RT64::UserConfiguration::Antialiasing::MSAA2X) {
                    config.update_enum_option_disabled(graphics::options::msaa_option, static_cast<uint32_t>(ultramodern::renderer::Antialiasing::MSAA2X), true);
                }
                if (max_msaa < RT64::UserConfiguration::Antialiasing::MSAA4X) {
                    config.update_enum_option_disabled(graphics::options::msaa_option, static_cast<uint32_t>(ultramodern::renderer::Antialiasing::MSAA4X), true);
                }
            }
        }

        void graphics::update_refresh_rate(uint32_t refresh_rate) {
            recomp::config::Config& config = get_graphics_config();
            std::string framerate_text = get_framerate_text(refresh_rate);
            config.update_option_description(graphics::options::rr_option, framerate_text);
            config.update_option_description(graphics::options::rr_manual_value, framerate_text);
        }

        void graphics::toggle_fullscreen() {
            auto current_wm = get_graphics_enum_value<ultramodern::renderer::WindowMode>(graphics::options::wm_option, OptionChangeContext::Temporary);
            auto new_wm = current_wm == ultramodern::renderer::WindowMode::Windowed ? ultramodern::renderer::WindowMode::Fullscreen : ultramodern::renderer::WindowMode::Windowed;
            get_graphics_config().set_option_value(graphics::options::wm_option, static_cast<uint32_t>(new_wm));
            get_graphics_config().apply_option_value(graphics::options::wm_option);
            apply_graphics_config();
        }

        recomp::config::Config &create_graphics_tab(const std::string &name) {
            created_graphics_config = true;

            recomp::config::Config &config = recompui::config::create_config_tab(name, graphics::id, true);
            config.set_save_callback(apply_graphics_config);
            config.set_load_callback(apply_graphics_config);

            config.add_bool_option(
                graphics::options::developer_mode,
                "Dev Mode",
                "Enables developer features.",
                false,
                true
            );

            config.add_enum_option(
                graphics::options::res_option,
                "Resolution",
                "Scales the game's original 240-line image. Lower multipliers reduce rendering cost, including ray tracing."
                "<br /><br />"
                "<recomp-color primary>Target heights:</recomp-color> 1x = 240, 2x = 480, 3x = 720, 4x = 960, 4.5x = 1080, 5x = 1200, 6x = 1440, 9x = 2160 pixels."
                "<br /><br />"
                "Width follows <recomp-color primary>Aspect Ratio</recomp-color>. At 3x, approximate targets are 1280 x 720 (16:9), 1680 x 720 (21:9), or 2560 x 720 (32:9). Ultrawide widths follow the display's actual proportions. This build uses a widescreen image, letterboxed on 4:3 screens."
                "<br /><br />"
                "<recomp-color primary>Auto</recomp-color> rounds the window height up to a whole multiple of 240: 1080 becomes 1200; 1440 stays 1440. Downsampling Quality applies only at 1x and 2x.",
                resolution_options,
                ultramodern::renderer::Resolution::Auto
            );
            {
                config.add_option_change_callback(
                    graphics::options::res_option,
                    [](recomp::config::ConfigValueVariant cur_value, recomp::config::ConfigValueVariant prev_value, OptionChangeContext change_context) {
                        auto new_opt = static_cast<ultramodern::renderer::Resolution>(std::get<uint32_t>(cur_value));
                        determine_downsampling_display(new_opt, change_context);
                    }
                );
            }

            config.add_enum_option(
                graphics::options::ds_option,
                "Downsampling Quality",
                "Renders at a higher resolution and scales it down to the selected resolution for increased quality. Available at <recomp-color primary>1x</recomp-color> and <recomp-color primary>2x</recomp-color> resolution."
                "<br />"
                "<br />"
                "<recomp-color primary>2x</recomp-color> doubles both rendering dimensions; <recomp-color primary>4x</recomp-color> quadruples them. For example, 2x resolution with 4x downsampling renders at 1920 lines and scales down to 480 lines. This increases rendering cost, including ray tracing."
                "<br /><br />"
                "Higher resolution multipliers and Auto ignore this setting. Your downsampling choice is retained when switching back to 1x or 2x.",
                downsampling_options,
                DownsamplingOption::X4
            );
            {
                config.add_option_change_callback(
                    graphics::options::ds_option,
                    [](recomp::config::ConfigValueVariant cur_value, recomp::config::ConfigValueVariant prev_value, OptionChangeContext change_context) {
                        auto resolution_opt = get_graphics_enum_value<ultramodern::renderer::Resolution>(graphics::options::res_option, change_context);
                        determine_downsampling_display(resolution_opt, change_context);
                    }
                );

                config.add_option_disable_dependency(
                    graphics::options::ds_option,
                    graphics::options::res_option,
                    ultramodern::renderer::Resolution::Auto,
                    ultramodern::renderer::Resolution::Fixed720p,
                    ultramodern::renderer::Resolution::Fixed1080p,
                    ultramodern::renderer::Resolution::Fixed1440p,
                    ultramodern::renderer::Resolution::Fixed2160p,
                    ultramodern::renderer::Resolution::Original4x,
                    ultramodern::renderer::Resolution::Original5x
                );
    
                config.on_json_parse_option(graphics::options::ds_option, [](const nlohmann::json& j) {
                    // Older/partial profiles can omit this option. Match the
                    // enum's supported values and retain its default otherwise.
                    return (j == 0 || j == 2 || j == 4) ? j.get<uint32_t>() :
                        static_cast<uint32_t>(DownsamplingOption::X4);
                });
    
                config.on_json_serialize_option(graphics::options::ds_option, [](const recomp::config::ConfigValueVariant& value) {
                    return nlohmann::json(std::get<uint32_t>(value));
                });
            }

            config.add_enum_option(
                graphics::options::ar_option,
                "Aspect Ratio",
                "<recomp-color primary>Original</recomp-color> keeps this build's 16:9 image. <recomp-color primary>Expand</recomp-color> widens the view to match the window or fullscreen display, up to 32:9. Narrower displays, including 4:3, show the widescreen image with letterboxing.",
                aspect_ratio_options,
                ultramodern::renderer::AspectRatio::Expand
            );

            config.add_enum_option(
                graphics::options::wm_option,
                "Window Mode",
                "Sets whether the game should display <recomp-color primary>Windowed</recomp-color> or <recomp-color primary>Fullscreen</recomp-color>. You can also use <recomp-color primary>F11</recomp-color> or <recomp-color primary>Alt + Enter</recomp-color> to toggle this option.",
                window_mode_options,
                ultramodern::renderer::WindowMode::Fullscreen
            );

            config.add_enum_option(
                graphics::options::rr_option,
                "Framerate",
                get_framerate_text(60),
                refresh_rate_options,
                ultramodern::renderer::RefreshRate::Display
            );

            config.add_number_option(
                graphics::options::rr_manual_value,
                "",
                get_framerate_text(60),
                20.0, 240.0, 1.0, 0, false, 90.0
            );
            {
                config.add_option_hidden_dependency(
                    graphics::options::rr_manual_value,
                    graphics::options::rr_option,
                    ultramodern::renderer::RefreshRate::Original,
                    ultramodern::renderer::RefreshRate::Display
                );
            }

            config.add_enum_option(
                graphics::options::msaa_option,
                "MS Anti-Aliasing",
                "Sets the multisample anti-aliasing (MSAA) quality level. This reduces jagged edges in the final image at the expense of rendering performance."
                "<br />"
                "<br />"
                "<recomp-color primary>Note: This option won't be available if your GPU does not support programmable MSAA sample positions, as it is currently required to avoid rendering glitches.</recomp-color>",
                antialiasing_options,
                ultramodern::renderer::Antialiasing::None
            );

            config.add_enum_option(
                graphics::options::hr_option,
                "HUD Placement",
                "Adjusts the placement of HUD elements to fit the selected aspect ratio. <recomp-color primary>Expand</recomp-color> will use the aspect ratio of the game's output window.",
                hud_ratio_mode_options,
                // New profiles should expose this port's expanded HUD by
                // default. Loading a saved profile retains its explicit choice.
                ultramodern::renderer::HUDRatioMode::Full
            );

            config.add_enum_option(
                graphics::options::api_option,
                "Graphics API",
                "Selects the graphics API to use. Changes take effect the next time the game is launched.",
                graphics_api_options,
#ifdef ALLOW_D3D12
                ultramodern::renderer::GraphicsApi::D3D12
#else
                ultramodern::renderer::GraphicsApi::Auto
#endif
            );

            config.add_enum_option(
                graphics::options::hpfb_option,
                "High Precision Framebuffer",
                "Sets whether to use a high precision framebuffer.",
                hpfb_options,
                ultramodern::renderer::HighPrecisionFramebuffer::Off,
                true
            );

            return config;
        }
    }
} // namespace recompui
