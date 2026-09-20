#include "wr64_graphics_config.hpp"

#include <cstdlib>
#include <iostream>

namespace host = ultramodern::renderer;
using Native = RT64::UserConfiguration;
using wr64::renderer::apply_live_graphics_config;
using wr64::renderer::apply_startup_graphics_config;
using wr64::renderer::graphics_framebuffers_changed;

static_assert(static_cast<int>(host::Resolution::Original) == 0 &&
    static_cast<int>(host::Resolution::Original2x) == 1 &&
    static_cast<int>(host::Resolution::Auto) == 2 &&
    static_cast<int>(host::Resolution::Fixed720p) == 3 &&
    static_cast<int>(host::Resolution::Fixed1080p) == 4 &&
    static_cast<int>(host::Resolution::Fixed1440p) == 5 &&
    static_cast<int>(host::Resolution::Fixed2160p) == 6,
    "Adding multiplier choices must preserve every existing resolution enum value");

static int assertions = 0;
static void require(bool condition, const char* message) {
    ++assertions;
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(1);
    }
}

int main() {
    host::GraphicsConfig config{};
    config.res_option = host::Resolution::Original2x;
    config.ds_option = 4;
    config.ar_option = host::AspectRatio::Expand;
    config.hr_option = host::HUDRatioMode::Clamp16x9;
    config.msaa_option = host::Antialiasing::MSAA4X;
    config.rr_option = host::RefreshRate::Manual;
    config.rr_manual_value = 120;
    config.api_option = host::GraphicsApi::Vulkan;
    config.hpfb_option = host::HighPrecisionFramebuffer::Off;
    Native state;
    const auto original_filter = state.filtering;
    const auto original_upscale_2d = state.upscale2D;
    apply_startup_graphics_config(state, config);
    require(state.graphicsAPI == Native::GraphicsAPI::Vulkan, "saved Vulkan selection reaches device startup");
    require(state.resolution == Native::Resolution::Manual &&
        state.resolutionMultiplier == 8.0 && state.downsampleMultiplier == 4,
        "480p with 4x downsampling renders at 8x native and outputs 2x native");
    require(state.aspectRatio == Native::AspectRatio::Expand &&
        state.extAspectRatio == Native::AspectRatio::Manual && state.extAspectTarget == 16.0 / 9.0,
        "expanded world and 16:9 HUD remain independent");
    require(state.refreshRate == Native::RefreshRate::Manual && state.refreshRateTarget == 120,
        "saved 120 FPS is not replaced with 180 FPS");
    require(state.antialiasing == Native::Antialiasing::MSAA4X, "saved MSAA setting reaches requested renderer state");
    require(state.internalColorFormat == Native::InternalColorFormat::Standard, "saved standard framebuffer applies at startup");
    require(state.filtering == original_filter && state.upscale2D == original_upscale_2d,
        "frontend mapping preserves unrelated original texture and 2D rendering choices");

    auto previous = state;
    config.res_option = host::Resolution::Auto;
    config.rr_option = host::RefreshRate::Display;
    config.api_option = host::GraphicsApi::D3D12;
    config.hpfb_option = host::HighPrecisionFramebuffer::On;
    config.developer_mode = true;
    apply_live_graphics_config(state, config);
    require(state.resolution == Native::Resolution::WindowIntegerScale && state.downsampleMultiplier == 1,
        "switching to Auto discards previously selected downsampling");
    require(state.refreshRate == Native::RefreshRate::Display,
        "display presentation mode is honored without changing the native game update rate");
    require(state.graphicsAPI == Native::GraphicsAPI::Vulkan &&
        state.internalColorFormat == Native::InternalColorFormat::Standard && !state.developerMode,
        "live apply does not hot-swap device API, shader precision or developer hooks");
    require(graphics_framebuffers_changed(previous, state), "resolution switch discards stale framebuffers");

    previous = state;
    config.rr_option = host::RefreshRate::Original;
    apply_live_graphics_config(state, config);
    require(state.refreshRate == Native::RefreshRate::Original, "original presentation cadence can be restored");
    require(!graphics_framebuffers_changed(previous, state), "framerate-only change retains framebuffer history");

    previous = state;
    config.hr_option = host::HUDRatioMode::Full;
    apply_live_graphics_config(state, config);
    require(state.extAspectRatio == Native::AspectRatio::Expand &&
        graphics_framebuffers_changed(previous, state), "HUD ratio change invalidates affected framebuffers");

    struct ResolutionCase {
        host::Resolution resolution;
        const char* saved_key;
        int height;
        bool downsampling;
    };
    const ResolutionCase resolutions[] = {
        {host::Resolution::Original, "Original", 240, true},
        {host::Resolution::Original2x, "Original2x", 480, true},
        {host::Resolution::Fixed720p, "720p", 720, false},
        {host::Resolution::Original4x, "4x", 960, false},
        {host::Resolution::Fixed1080p, "1080p", 1080, false},
        {host::Resolution::Original5x, "5x", 1200, false},
        {host::Resolution::Fixed1440p, "1440p", 1440, false},
        {host::Resolution::Fixed2160p, "2160p", 2160, false},
    };
    for (const auto& resolution : resolutions) {
        const nlohmann::json saved = resolution.resolution;
        require(saved == resolution.saved_key, "resolution writes its stable graphics.json key");
        config.res_option = nlohmann::json(resolution.saved_key).get<host::Resolution>();
        require(config.res_option == resolution.resolution, "saved resolution is restored without falling back to Original");
        for (const int downsample : {0, 2, 4}) {
            config.ds_option = downsample;
            previous = state;
            apply_live_graphics_config(state, config);
            require(state.resolution == Native::Resolution::Manual, "explicit multipliers do not follow window size");
            require(240.0 * state.resolutionMultiplier / state.downsampleMultiplier == resolution.height,
                "every downsampling quality retains the selected output resolution");
            const int expected_downsample = resolution.downsampling ? std::max(downsample, 1) : 1;
            require(state.downsampleMultiplier == expected_downsample &&
                240.0 * state.resolutionMultiplier == resolution.height * expected_downsample,
                "higher multipliers ignore retained downsampling; Original modes keep supersampling");
            require(config.ds_option == downsample, "resolution application preserves saved downsampling preference");
            require(state.aspectRatio == Native::AspectRatio::Expand &&
                state.extAspectRatio == Native::AspectRatio::Expand,
                "selecting a multiplier preserves independent world and HUD aspect choices");
            if (previous.resolutionMultiplier != state.resolutionMultiplier) {
                require(graphics_framebuffers_changed(previous, state),
                    "switching fixed heights invalidates framebuffers even though both modes are Manual");
            }
            if (!resolution.downsampling && downsample != 0) {
                require(!graphics_framebuffers_changed(previous, state),
                    "changing ignored downsampling does not discard higher-multiplier framebuffers");
            }
            Native startup;
            apply_startup_graphics_config(startup, config);
            require(startup.resolution == state.resolution &&
                startup.resolutionMultiplier == state.resolutionMultiplier &&
                startup.downsampleMultiplier == state.downsampleMultiplier,
                "saved startup and live Apply use identical rendering dimensions");
            state.validate();
            require(240.0 * state.resolutionMultiplier / state.downsampleMultiplier == resolution.height,
                "RT64 validation retains exact preset height, including fractional 4.5x for 1080p");
            previous = state;
            apply_live_graphics_config(state, config);
            require(!graphics_framebuffers_changed(previous, state),
                "reapplying an unchanged multiplier retains framebuffer history");
        }
    }
    config.res_option = nlohmann::json("Auto").get<host::Resolution>();
    config.ds_option = 4;
    apply_live_graphics_config(state, config);
    require(config.res_option == host::Resolution::Auto && nlohmann::json(config.res_option) == "Auto" &&
        state.resolution == Native::Resolution::WindowIntegerScale &&
        state.resolutionMultiplier == 1.0 && state.downsampleMultiplier == 1 && config.ds_option == 4,
        "returning to Auto restores window scaling without losing the saved downsampling choice");

    apply_startup_graphics_config(state, config);
    require(state.graphicsAPI == Native::GraphicsAPI::D3D12 &&
        state.internalColorFormat == Native::InternalColorFormat::High && state.developerMode,
        "deferred settings apply when the renderer is recreated");
    config.api_option = host::GraphicsApi::Auto;
    config.hpfb_option = host::HighPrecisionFramebuffer::Auto;
    config.ar_option = host::AspectRatio::Original;
    config.hr_option = host::HUDRatioMode::Original;
    config.msaa_option = host::Antialiasing::None;
    apply_startup_graphics_config(state, config);
    require(state.graphicsAPI == Native::GraphicsAPI::Automatic &&
        state.internalColorFormat == Native::InternalColorFormat::Automatic,
        "automatic API and framebuffer precision remain automatic");
    require(state.aspectRatio == Native::AspectRatio::Original &&
        state.extAspectRatio == Native::AspectRatio::Original && state.antialiasing == Native::Antialiasing::None,
        "original aspect and disabled MSAA can be restored");
    std::cout << "PASS: " << assertions << " graphics mapping assertions\n";
}
