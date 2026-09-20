#pragma once

#include <algorithm>

#include "common/rt64_user_configuration.h"
#include "ultramodern/config.hpp"

namespace wr64::renderer {

// Apply only settings that RT64 can change while its device is running. Keep
// API, shader precision and developer hooks unchanged until the next startup.
inline void apply_live_graphics_config(RT64::UserConfiguration& target,
    const ultramodern::renderer::GraphicsConfig& source) {
    namespace host = ultramodern::renderer;
    using Native = RT64::UserConfiguration;
    const double resolution_scale = host::resolution_scale(source.res_option);
    const int downsample = host::resolution_supports_downsampling(source.res_option) ?
        std::max(source.ds_option, 1) : 1;
    if (resolution_scale > 0.0) {
        target.resolution = Native::Resolution::Manual;
        target.resolutionMultiplier = downsample * resolution_scale;
        target.downsampleMultiplier = downsample;
    }
    else {
        target.resolution = Native::Resolution::WindowIntegerScale;
        target.resolutionMultiplier = 1.0;
        target.downsampleMultiplier = 1;
    }

    switch (source.ar_option) {
    case host::AspectRatio::Original: target.aspectRatio = Native::AspectRatio::Original; break;
    case host::AspectRatio::Manual: target.aspectRatio = Native::AspectRatio::Manual; break;
    default: target.aspectRatio = Native::AspectRatio::Expand; break;
    }
    switch (source.hr_option) {
    case host::HUDRatioMode::Original:
        target.extAspectRatio = Native::AspectRatio::Original;
        break;
    case host::HUDRatioMode::Clamp16x9:
        target.extAspectRatio = Native::AspectRatio::Manual;
        target.extAspectTarget = 16.0 / 9.0;
        break;
    default:
        target.extAspectRatio = Native::AspectRatio::Expand;
        break;
    }
    switch (source.msaa_option) {
    case host::Antialiasing::MSAA2X: target.antialiasing = Native::Antialiasing::MSAA2X; break;
    case host::Antialiasing::MSAA4X: target.antialiasing = Native::Antialiasing::MSAA4X; break;
    case host::Antialiasing::MSAA8X: target.antialiasing = Native::Antialiasing::MSAA8X; break;
    default: target.antialiasing = Native::Antialiasing::None; break;
    }
    switch (source.rr_option) {
    case host::RefreshRate::Original: target.refreshRate = Native::RefreshRate::Original; break;
    case host::RefreshRate::Manual: target.refreshRate = Native::RefreshRate::Manual; break;
    default: target.refreshRate = Native::RefreshRate::Display; break;
    }
    target.refreshRateTarget = std::clamp(source.rr_manual_value, 20, 240);
    target.displayBuffering = Native::DisplayBuffering::Triple;
}

inline void apply_startup_graphics_config(RT64::UserConfiguration& target,
    const ultramodern::renderer::GraphicsConfig& source) {
    namespace host = ultramodern::renderer;
    using Native = RT64::UserConfiguration;
    apply_live_graphics_config(target, source);
    switch (source.api_option) {
    case host::GraphicsApi::D3D12: target.graphicsAPI = Native::GraphicsAPI::D3D12; break;
    case host::GraphicsApi::Vulkan: target.graphicsAPI = Native::GraphicsAPI::Vulkan; break;
    case host::GraphicsApi::Metal: target.graphicsAPI = Native::GraphicsAPI::Metal; break;
    default: target.graphicsAPI = Native::GraphicsAPI::Automatic; break;
    }
    switch (source.hpfb_option) {
    case host::HighPrecisionFramebuffer::Off: target.internalColorFormat = Native::InternalColorFormat::Standard; break;
    case host::HighPrecisionFramebuffer::On: target.internalColorFormat = Native::InternalColorFormat::High; break;
    default: target.internalColorFormat = Native::InternalColorFormat::Automatic; break;
    }
    target.developerMode = source.developer_mode;
}

inline bool graphics_framebuffers_changed(const RT64::UserConfiguration& previous,
    const RT64::UserConfiguration& current) {
    return previous.resolution != current.resolution ||
        previous.resolutionMultiplier != current.resolutionMultiplier ||
        previous.downsampleMultiplier != current.downsampleMultiplier ||
        previous.aspectRatio != current.aspectRatio ||
        previous.extAspectRatio != current.extAspectRatio ||
        previous.extAspectTarget != current.extAspectTarget ||
        previous.antialiasing != current.antialiasing;
}

} // namespace wr64::renderer
