#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <optional>

#include "json/json.hpp"

namespace ultramodern {
    namespace renderer {
        enum class Resolution {
            Original,
            Original2x,
            Auto,
            Fixed720p,
            Fixed1080p,
            Fixed1440p,
            Fixed2160p,
            Original4x,
            Original5x,
            OptionCount
        };

        // Preserve existing enum values and serialized keys when changing UI
        // labels. Multipliers scale the 240-line image; width follows aspect
        // ratio independently, and Auto uses the window-derived scale.
        constexpr double resolution_scale(Resolution resolution) {
            switch (resolution) {
            case Resolution::Original: return 1.0;
            case Resolution::Original2x: return 2.0;
            case Resolution::Fixed720p: return 3.0;
            case Resolution::Fixed1080p: return 4.5;
            case Resolution::Fixed1440p: return 6.0;
            case Resolution::Fixed2160p: return 9.0;
            case Resolution::Original4x: return 4.0;
            case Resolution::Original5x: return 5.0;
            default: return 0.0;
            }
        }

        constexpr bool resolution_supports_downsampling(Resolution resolution) {
            // Scales above 2x render directly at their selected height. A saved
            // 4x downsampling quality must not multiply the 4.5x scale again.
            return resolution == Resolution::Original || resolution == Resolution::Original2x;
        }
        enum class WindowMode {
            Windowed,
            Fullscreen,
            OptionCount
        };
        enum class HUDRatioMode {
            Original,
            Clamp16x9,
            Full,
            OptionCount
        };
        enum class GraphicsApi {
            Auto,
            D3D12,
            Vulkan,
            Metal,
            OptionCount
        };
        enum class AspectRatio {
            Original,
            Expand,
            Manual,
            OptionCount
        };
        enum class Antialiasing {
            None,
            MSAA2X,
            MSAA4X,
            MSAA8X,
            OptionCount
        };
        enum class RefreshRate {
            Original,
            Display,
            Manual,
            OptionCount
        };
        enum class HighPrecisionFramebuffer {
            Auto,
            On,
            Off,
            OptionCount
        };
        enum class PresentationMode {
            Console,
            SkipBuffering,
            PresentEarly
        };

        class GraphicsConfig {
        public:
            bool developer_mode;
            Resolution res_option;
            WindowMode wm_option;
            HUDRatioMode hr_option;
            GraphicsApi api_option;
            AspectRatio ar_option;
            Antialiasing msaa_option;
            RefreshRate rr_option;
            HighPrecisionFramebuffer hpfb_option;
            int rr_manual_value;
            int ds_option;

            virtual ~GraphicsConfig() = default;

            auto operator<=>(const GraphicsConfig& rhs) const = default;
        };

        // Return a coherent snapshot; callers must not retain a reference to
        // storage that the UI can replace concurrently.
        GraphicsConfig get_graphics_config();
        void set_graphics_config(const GraphicsConfig& new_config);

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::Resolution, {
            {ultramodern::renderer::Resolution::Original, "Original"},
            {ultramodern::renderer::Resolution::Original2x, "Original2x"},
            {ultramodern::renderer::Resolution::Auto, "Auto"},
            {ultramodern::renderer::Resolution::Fixed720p, "720p"},
            {ultramodern::renderer::Resolution::Fixed1080p, "1080p"},
            {ultramodern::renderer::Resolution::Fixed1440p, "1440p"},
            {ultramodern::renderer::Resolution::Fixed2160p, "2160p"},
            {ultramodern::renderer::Resolution::Original4x, "4x"},
            {ultramodern::renderer::Resolution::Original5x, "5x"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::WindowMode, {
            {ultramodern::renderer::WindowMode::Windowed, "Windowed"},
            {ultramodern::renderer::WindowMode::Fullscreen, "Fullscreen"}
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::HUDRatioMode, {
            {ultramodern::renderer::HUDRatioMode::Original, "Original"},
            {ultramodern::renderer::HUDRatioMode::Clamp16x9, "Clamp16x9"},
            {ultramodern::renderer::HUDRatioMode::Full, "Full"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::GraphicsApi, {
            {ultramodern::renderer::GraphicsApi::Auto, "Auto"},
            {ultramodern::renderer::GraphicsApi::D3D12, "D3D12"},
            {ultramodern::renderer::GraphicsApi::Vulkan, "Vulkan"},
            {ultramodern::renderer::GraphicsApi::Metal, "Metal"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::AspectRatio, {
            {ultramodern::renderer::AspectRatio::Original, "Original"},
            {ultramodern::renderer::AspectRatio::Expand, "Expand"},
            {ultramodern::renderer::AspectRatio::Manual, "Manual"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::Antialiasing, {
            {ultramodern::renderer::Antialiasing::None, "None"},
            {ultramodern::renderer::Antialiasing::MSAA2X, "MSAA2X"},
            {ultramodern::renderer::Antialiasing::MSAA4X, "MSAA4X"},
            {ultramodern::renderer::Antialiasing::MSAA8X, "MSAA8X"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::RefreshRate, {
            {ultramodern::renderer::RefreshRate::Original, "Original"},
            {ultramodern::renderer::RefreshRate::Display, "Display"},
            {ultramodern::renderer::RefreshRate::Manual, "Manual"},
        });

        NLOHMANN_JSON_SERIALIZE_ENUM(ultramodern::renderer::HighPrecisionFramebuffer, {
            {ultramodern::renderer::HighPrecisionFramebuffer::Auto, "Auto"},
            {ultramodern::renderer::HighPrecisionFramebuffer::On, "On"},
            {ultramodern::renderer::HighPrecisionFramebuffer::Off, "Off"},
        });
    }
}

#endif
