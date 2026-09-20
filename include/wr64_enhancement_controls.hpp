#pragma once

#include "librecomp/config.hpp"
#include "ultramodern/config.hpp"

namespace wr64::frontend {

struct EnhancementAvailability {
    bool d3d12 = false;
    bool ray_tracing = false;
    bool operator==(const EnhancementAvailability&) const = default;
};

inline EnhancementAvailability enhancement_availability(ultramodern::renderer::GraphicsApi selected,
    ultramodern::renderer::GraphicsApi active, bool device_ray_tracing) {
    using Api = ultramodern::renderer::GraphicsApi;
    // Pending choices cannot enable features on a device that has not started.
    const bool d3d12 = active == Api::D3D12 && (selected == Api::Auto || selected == Api::D3D12);
    return {d3d12, d3d12 && device_ray_tracing};
}

inline void update_enhancement_controls(recomp::config::Config& config, EnhancementAvailability available) {
    const auto enum_value = [&](const char* key) {
        return std::get<uint32_t>(config.get_option_value(key));
    };
    const bool sky = std::get<bool>(config.get_option_value("rt_sky_reflections"));
    const bool raster_sky = enum_value("sky_reflection_method") == 0u;
    const bool water_rt = available.ray_tracing && enum_value("water_reflections") == 1u;
    const bool reflection_distance = water_rt;
    const bool shadows_rt = water_rt && enum_value("shadow_method") == 2u;
    const bool shadows_raster = available.d3d12 && enum_value("shadow_method") == 1u;
    const bool raster_strength = available.d3d12 && sky && raster_sky;
    config.update_option_disabled("rt_sky_reflections", !available.d3d12);
    config.update_option_hidden("sky_reflection_method", !sky);
    config.update_option_hidden("raster_sky_strength", !raster_strength);
    config.update_option_disabled("raster_sky_strength", !raster_strength);
    config.update_option_hidden("rt_reflection_distance", !reflection_distance);
    config.update_option_hidden("rt_shadow_samples", !shadows_rt);
    config.update_option_disabled("rt_reflection_distance", !reflection_distance);
    config.update_option_disabled("rt_shadow_samples", !shadows_rt);
    config.update_option_hidden("raster_shadow_distance", !shadows_raster);
    config.update_option_disabled("raster_shadow_distance", !shadows_raster);

    const auto disable_choice = [&](const char* key, uint32_t value, bool disabled) {
        const auto& schema = config.get_config_schema();
        const size_t option_index = schema.options_by_id.at(key);
        const auto& options = std::get<recomp::config::ConfigOptionEnum>(schema.options[option_index].variant).options;
        for (uint32_t index = 0; index < options.size(); ++index) {
            if (options[index].value != value) continue;
            // The UI disable API takes a display index, not a saved enum value.
            if (config.get_enum_option_disabled(option_index, index) != disabled)
                config.update_enum_option_disabled(key, index, disabled);
            break;
        }
    };
    const auto set_details = [&](const char* key, const std::string& details) {
        const size_t option_index = config.get_config_schema().options_by_id.at(key);
        if (config.get_enum_option_details(option_index) != details)
            config.update_option_enum_details(key, details);
    };
    disable_choice("water_reflections", 3u, !available.d3d12);
    disable_choice("water_reflections", 1u, !available.ray_tracing);
    disable_choice("sky_reflection_method", 0u, !available.d3d12);
    disable_choice("sky_reflection_method", 1u, !available.ray_tracing);
    disable_choice("shadow_method", 1u, !available.d3d12);
    disable_choice("shadow_method", 2u, !water_rt);
    disable_choice("split_screen_layout", 2u, !available.d3d12);

    const std::string rt_details = available.ray_tracing ? "" :
        "Ray Traced unavailable: this device does not support the required ray tracing";
    set_details("water_reflections", available.d3d12 ? rt_details :
        "Rasterized / Ray Traced require Direct3D 12; using Original");
    set_details("sky_reflection_method", available.d3d12 ? rt_details :
        "Sky Reflections unavailable: requires Direct3D 12");
    set_details("shadow_method", !available.d3d12 ?
        "Rasterized / Ray Traced require Direct3D 12; using Original" :
        !available.ray_tracing ? rt_details : !water_rt ?
        "Ray Traced requires Water Reflections set to Ray Traced" : "");
    set_details("split_screen_layout", available.d3d12 ? "" :
        enum_value("split_screen_layout") == 2u ?
        "Separate windows requires Direct3D 12; using Horizontal" :
        "Separate windows requires Direct3D 12");
}

} // namespace wr64::frontend
