#include "wr64_diagnostic_policy.h"
#ifdef WR64_ENABLE_RT64

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <cctype>
#include <utility>

#include "hle/rt64_application.h"
#include "common/rt64_wr64_rt_startup.h"
#include "common/rt64_wr64_separate_windows.h"
#include "common/rt64_wr64_rt_diagnostics.h"
#include "common/rt64_wr64_rt_settings.h"
#include "wr64_renderer.hpp"
#include "wr64_graphics_config.hpp"
#include "wr64_graphics_restart.hpp"
#include "wr64_render_provenance.h"
#include "wr64_forensic.h"
#include "librecomp/game.hpp"
#include "ultramodern/config.hpp"
#include "ultramodern/ultramodern.hpp"
#ifdef WR64_ENABLE_FRONTEND
#include "recompui/recompui.h"
#include "recompui/config.h"
#include "recompui/renderer.h"
#include "wr64_frontend.hpp"
#endif

extern "C" float wr64_experimental_3d_aspect();

namespace wr64::renderer {
namespace {

uint8_t dmem[0x1000]{};
uint8_t imem[0x1000]{};
uint8_t dummy_rom_header[0x40]{};

unsigned int mi_intr_reg = 0;
unsigned int dpc_start_reg = 0;
unsigned int dpc_end_reg = 0;
unsigned int dpc_current_reg = 0;
unsigned int dpc_status_reg = 0;
unsigned int dpc_clock_reg = 0;
unsigned int dpc_bufbusy_reg = 0;
unsigned int dpc_pipebusy_reg = 0;
unsigned int dpc_tmem_reg = 0;

constexpr int kReferenceHeight = 240;

std::optional<int> wr64_presentation_rate_override() {
    const char *value = std::getenv("WR64_FORCE_PRESENTATION_HZ");
    if ((value != nullptr) && (value[0] != '\0')) {
        char* end = nullptr;
        const long parsed = std::strtol(value, &end, 10);
        if ((end != value) && (*end == '\0') && (parsed >= 20) && (parsed <= 240)) {
            return static_cast<int>(parsed);
        }
    }

    const char* legacy = std::getenv("WR64_FORCE_PRESENTATION_20HZ");
    if (legacy != nullptr && legacy[0] != '\0' && legacy[0] != '0') return 20;
    return std::nullopt;
}

RT64::UserConfiguration::GraphicsAPI wr64_requested_graphics_api(
    RT64::UserConfiguration::GraphicsAPI saved_api) {
    const char *value = std::getenv("WR64_GRAPHICS_API");
    if ((value == nullptr) || (value[0] == '\0')) return saved_api;
    std::string override_value(value);
    std::transform(override_value.begin(), override_value.end(), override_value.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    using Api = RT64::UserConfiguration::GraphicsAPI;
    if (override_value == "vulkan") return Api::Vulkan;
    if (override_value == "d3d12") return Api::D3D12;
    if (override_value == "metal") return Api::Metal;
    if (override_value == "auto" || override_value == "automatic") return Api::Automatic;
    std::fprintf(stderr, "[rt64] ignoring invalid WR64_GRAPHICS_API='%s'\n", value);
    return saved_api;
}

void apply_presentation_override(RT64::UserConfiguration& config) {
    if (const auto forced_rate = wr64_presentation_rate_override()) {
        config.refreshRate = RT64::UserConfiguration::RefreshRate::Manual;
        config.refreshRateTarget = *forced_rate;
    }
}

const char *graphics_api_name(RT64::UserConfiguration::GraphicsAPI value) {
    switch (value) {
        case RT64::UserConfiguration::GraphicsAPI::D3D12: return "D3D12";
        case RT64::UserConfiguration::GraphicsAPI::Vulkan: return "Vulkan";
        case RT64::UserConfiguration::GraphicsAPI::Metal: return "Metal";
        case RT64::UserConfiguration::GraphicsAPI::Automatic: return "automatic";
    }
    return "unknown";
}

bool viewport_trace_enabled() {
    const char* value = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_VIEWPORT_TRACE"));
    return value != nullptr && value[0] != '\0' && value[0] != '0';
}

const char* aspect_ratio_name(RT64::UserConfiguration::AspectRatio value) {
    switch (value) {
        case RT64::UserConfiguration::AspectRatio::Original: return "original";
        case RT64::UserConfiguration::AspectRatio::Expand: return "expand";
        case RT64::UserConfiguration::AspectRatio::Manual: return "manual";
        case RT64::UserConfiguration::AspectRatio::OptionCount: break;
    }
    return "unknown";
}

const char* refresh_rate_name(RT64::UserConfiguration::RefreshRate value) {
    switch (value) {
        case RT64::UserConfiguration::RefreshRate::Original: return "original";
        case RT64::UserConfiguration::RefreshRate::Display: return "display";
        case RT64::UserConfiguration::RefreshRate::Manual: return "manual";
        case RT64::UserConfiguration::RefreshRate::OptionCount: break;
    }
    return "unknown";
}

void check_interrupts() {}

ultramodern::renderer::SetupResult map_setup_result(
    RT64::Application::SetupResult result) {
    using SetupResult = ultramodern::renderer::SetupResult;
    switch (result) {
        case RT64::Application::SetupResult::Success:
            return SetupResult::Success;
        case RT64::Application::SetupResult::DynamicLibrariesNotFound:
            return SetupResult::DynamicLibrariesNotFound;
        case RT64::Application::SetupResult::InvalidGraphicsAPI:
            return SetupResult::InvalidGraphicsAPI;
        case RT64::Application::SetupResult::GraphicsAPINotFound:
            return SetupResult::GraphicsAPINotFound;
        case RT64::Application::SetupResult::GraphicsDeviceNotFound:
            return SetupResult::GraphicsDeviceNotFound;
    }
    return SetupResult::GraphicsDeviceNotFound;
}

ultramodern::renderer::GraphicsApi map_graphics_api(
    RT64::UserConfiguration::GraphicsAPI api) {
    using GraphicsApi = ultramodern::renderer::GraphicsApi;
    switch (api) {
        case RT64::UserConfiguration::GraphicsAPI::D3D12:
            return GraphicsApi::D3D12;
        case RT64::UserConfiguration::GraphicsAPI::Vulkan:
            return GraphicsApi::Vulkan;
        case RT64::UserConfiguration::GraphicsAPI::Metal:
            return GraphicsApi::Metal;
        case RT64::UserConfiguration::GraphicsAPI::Automatic:
            return GraphicsApi::Auto;
    }
    return GraphicsApi::Auto;
}

class RT64Context final : public ultramodern::renderer::RendererContext {
public:
    RT64Context(
        uint8_t* rdram,
        ultramodern::renderer::WindowHandle window_handle,
        bool developer_mode) : rdram(rdram), window_handle(window_handle) {
        auto initial_config = ultramodern::renderer::get_graphics_config();
        initial_config.developer_mode = developer_mode;
        initialize(initial_config);
    }

    void initialize(const ultramodern::renderer::GraphicsConfig& frontend_config) {
        RT64::wr64RTStartupGate.reset();
        supported_sample_counts = 1;
        last_display_refresh_rate = 0;
        RT64::Application::Core core{};
        core.window = window_handle.window;
        core.checkInterrupts = check_interrupts;
        core.HEADER = dummy_rom_header;
        core.RDRAM = rdram;
        core.DMEM = dmem;
        core.IMEM = imem;
        core.MI_INTR_REG = &mi_intr_reg;
        core.DPC_START_REG = &dpc_start_reg;
        core.DPC_END_REG = &dpc_end_reg;
        core.DPC_CURRENT_REG = &dpc_current_reg;
        core.DPC_STATUS_REG = &dpc_status_reg;
        core.DPC_CLOCK_REG = &dpc_clock_reg;
        core.DPC_BUFBUSY_REG = &dpc_bufbusy_reg;
        core.DPC_PIPEBUSY_REG = &dpc_pipebusy_reg;
        core.DPC_TMEM_REG = &dpc_tmem_reg;

        vi_regs = ultramodern::renderer::get_vi_regs();
        auto* vi = vi_regs;
        core.VI_STATUS_REG = &vi->VI_STATUS_REG;
        core.VI_ORIGIN_REG = &vi->VI_ORIGIN_REG;
        core.VI_WIDTH_REG = &vi->VI_WIDTH_REG;
        core.VI_INTR_REG = &vi->VI_INTR_REG;
        core.VI_V_CURRENT_LINE_REG = &vi->VI_V_CURRENT_LINE_REG;
        core.VI_TIMING_REG = &vi->VI_TIMING_REG;
        core.VI_V_SYNC_REG = &vi->VI_V_SYNC_REG;
        core.VI_H_SYNC_REG = &vi->VI_H_SYNC_REG;
        core.VI_LEAP_REG = &vi->VI_LEAP_REG;
        core.VI_H_START_REG = &vi->VI_H_START_REG;
        core.VI_V_START_REG = &vi->VI_V_START_REG;
        core.VI_V_BURST_REG = &vi->VI_V_BURST_REG;
        core.VI_X_SCALE_REG = &vi->VI_X_SCALE_REG;
        core.VI_Y_SCALE_REG = &vi->VI_Y_SCALE_REG;

        RT64::ApplicationConfiguration config{};
        config.detectDataPath = false;
        config.dataPath = recomp::get_config_path();
        // Frontend graphics.json is authoritative. Do not load a competing
        // RT64 configuration file over the selected edition's settings.
        config.useConfigurationFile = false;
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[rt64] creating application\n"));
        app = std::make_unique<RT64::Application>(core, config);
        apply_startup_graphics_config(app->userConfig, frontend_config);
        app->userConfig.developerMode = frontend_config.developer_mode;
        app->userConfig.graphicsAPI = wr64_requested_graphics_api(app->userConfig.graphicsAPI);
        apply_presentation_override(app->userConfig);
        // Discover the actual device's format and sample-position support
        // before creating any multisampled shaders for the requested setting.
        app->userConfig.antialiasing = RT64::UserConfiguration::Antialiasing::None;

        WR64_DIAGNOSTIC_LOG(std::fprintf(
            stderr,
            "[rt64] setting up requested %s renderer\n",
            graphics_api_name(app->userConfig.graphicsAPI)));
#ifdef WR64_ENABLE_FRONTEND
        // The ENTIRE render integration for the settings UI. This sets three
        // function pointers in an RT64 global (rhi/rt64_render_hooks.cpp);
        // RT64 then calls init from Application::setup (hle/rt64_application.cpp:298),
        // draw from the present path (hle/rt64_present_queue.cpp:701) and deinit
        // on teardown (rt64_application.cpp:677).
        //
        // It must come BEFORE app->setup, because setup is what fires the init
        // hook that builds the UI. recompui ships an entire RT64Context of its
        // own that does this; we do not use it, because ours carries the task
        // claiming, the forensic recording and the layer traces.
        recompui::set_render_hooks();
#endif
        setup_result = map_setup_result(app->setup(window_handle.thread_id));
        chosen_api = map_graphics_api(app->chosenGraphicsAPI);
        RT64::wr64SeparateWindowsBackend.store(setup_result == ultramodern::renderer::SetupResult::Success &&
            app->chosenGraphicsAPI == RT64::UserConfiguration::GraphicsAPI::D3D12, std::memory_order_release);
        if (setup_result != ultramodern::renderer::SetupResult::Success) {
            std::fprintf(stderr, "[rt64] renderer setup failed (%d)\n", static_cast<int>(setup_result));
            app->end();
            app.reset();
        }
        else {
            configure_multisampling_support();
            const auto initial_config = app->userConfig;
            apply_live_graphics_config(app->userConfig, frontend_config);
            apply_presentation_override(app->userConfig);
            constrain_multisampling();
            if (initial_config.antialiasing != app->userConfig.antialiasing) {
                app->updateMultisampling();
            }
            app->updateUserConfig(graphics_framebuffers_changed(initial_config, app->userConfig));
#ifdef WR64_ENABLE_FRONTEND
            recompui::renderer::check_texture_pack_actions(*app, texture_pack_state, true);
            wr64::frontend::report_graphics_api(chosen_api, frontend_config.api_option,
                app->workloadQueue->framebufferRenderer->wr64RTSupported);
            wr64::frontend::request_fullscreen(
                frontend_config.wm_option == ultramodern::renderer::WindowMode::Fullscreen);
#else
            app->setFullScreen(frontend_config.wm_option == ultramodern::renderer::WindowMode::Fullscreen);
#endif
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[rt64] renderer setup complete\n"));
            WR64_DIAGNOSTIC_LOG(std::fprintf(
                stderr,
                "[rt64] active graphics API: %s\n",
                graphics_api_name(app->chosenGraphicsAPI)));
            WR64_DIAGNOSTIC_LOG(std::fprintf(
                stderr,
                "[rt64] graphics config: %s, aspect=%s, refresh=%s (%d Hz)\n",
                app->userPaths.configurationPath.string().c_str(),
                aspect_ratio_name(app->userConfig.aspectRatio),
                refresh_rate_name(app->userConfig.refreshRate),
                app->userConfig.refreshRateTarget));
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[window] F11 or Alt+Enter toggles borderless fullscreen\n"));
            report_graphics_settings();
            initialized_config = frontend_config;
        }
    }

    ~RT64Context() override = default;

    bool valid() override { return app != nullptr; }

    bool update_config(
        const ultramodern::renderer::GraphicsConfig& old_config,
        const ultramodern::renderer::GraphicsConfig& new_config) override {
        if (old_config == new_config || !app) return false;
        if (old_config.api_option != new_config.api_option) {
            return reconfigure_api(new_config);
        }
        if (old_config.wm_option != new_config.wm_option) {
#ifdef WR64_ENABLE_FRONTEND
            wr64::frontend::request_fullscreen(
                new_config.wm_option == ultramodern::renderer::WindowMode::Fullscreen);
#else
            app->setFullScreen(new_config.wm_option == ultramodern::renderer::WindowMode::Fullscreen);
#endif
        }
        const auto previous = app->userConfig;
        apply_live_graphics_config(app->userConfig, new_config);
        apply_presentation_override(app->userConfig);
        constrain_multisampling();
        if (previous.antialiasing != app->userConfig.antialiasing) app->updateMultisampling();
        app->updateUserConfig(graphics_framebuffers_changed(previous, app->userConfig));
        if (old_config.hpfb_option != new_config.hpfb_option ||
            old_config.developer_mode != new_config.developer_mode) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[rt64] framebuffer precision and developer-mode changes apply after restart\n"));
        }
        report_graphics_settings();
        return true;
    }

    void enable_instant_present() override {}

    // The runtime queues one of these per VI for as long as the game has not
    // started - DummyWorkloadAction in ultramodern/src/events.cpp. It is new:
    // the runtime this project shipped on had no such action, so the pre-game
    // frames were a dummy VI mode plus a screen update and nothing else.
    // This RT64 has no matching entry point to forward it to either -
    // rt64_application.h exposes processDisplayLists, updateScreen, setup and
    // end, and nothing that renders a blank workload. Empty is therefore both
    // the only available implementation and exactly what R4 did.
    void send_dummy_workload(uint32_t fb_address) override { (void)fb_address; }

    void send_dl(const OSTask* task) override {
#ifdef WR64_ENABLE_FRONTEND
        recompui::renderer::check_texture_pack_actions(*app, texture_pack_state);
#endif
        uint32_t task_address = 0;
        uint32_t context_ra = 0;
        const uint64_t task_sequence = wr64_claim_gfx_task(
            task->t.data_ptr,
            task->t.ucode,
            task->t.ucode_data,
            &task_address,
            &context_ra);
        wr64_forensic_set_task(task_sequence);
        wr64_forensic_record(WR64_FORENSIC_GFX_TASK,
            task_sequence, task_address, context_ra, task->t.data_ptr,
            task->t.ucode, task->t.ucode_data, task->t.data_size, 0);
        app->state->wr64CurrentTaskSequence = task_sequence;
        app->state->wr64HudCurrent = {};
        app->state->wr64WaveTaskPackets = RT64::wr64ClaimWaveDistanceTask(task_sequence);
        app->state->wr64CurrentTaskAddress = task_address;
        app->state->wr64CurrentTaskContextRa = context_ra;
        app->state->wr64CurrentRootDisplayList = task->t.data_ptr;
        app->state->wr64CurrentUcode = task->t.ucode;
        app->state->wr64CurrentUcodeData = task->t.ucode_data;
        static bool first_task = true;
        if (first_task) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(
                stderr,
                "[rt64] first display list: ucode=%08X data=%08X dl=%08X\n",
                task->t.ucode,
                task->t.ucode_data,
                task->t.data_ptr));
            first_task = false;
        }
        app->state->rsp->reset();
        app->interpreter->loadUCodeGBI(
            task->t.ucode & 0x03FFFFFF,
            task->t.ucode_data & 0x03FFFFFF,
            true);
        app->processDisplayLists(
            app->core.RDRAM,
            task->t.data_ptr & 0x03FFFFFF,
            0,
            true);

        trace_render_bounds(task);
    }

    void update_screen() override {
        static bool first_update = true;
        if (first_update) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[rt64] first screen update\n"));
            first_update = false;
        }
        screen_update_count++;
        wr64_forensic_record(WR64_FORENSIC_VI, screen_update_count,
            vi_regs != nullptr ? vi_regs->VI_ORIGIN_REG : 0,
            vi_regs != nullptr ? vi_regs->VI_WIDTH_REG : 0,
            vi_regs != nullptr ? vi_regs->VI_STATUS_REG : 0,
            vi_regs != nullptr ? vi_regs->VI_H_START_REG : 0,
            vi_regs != nullptr ? vi_regs->VI_V_START_REG : 0,
            vi_regs != nullptr ? vi_regs->VI_X_SCALE_REG : 0,
            vi_regs != nullptr ? vi_regs->VI_Y_SCALE_REG : 0);
        trace_vi_state();
        app->updateScreen();
        poll_startup_prewarm();
#ifdef WR64_ENABLE_FRONTEND
        const uint32_t refresh_rate = get_display_framerate();
        if (wr64::frontend::ready() && refresh_rate > 0 && refresh_rate != last_display_refresh_rate) {
            wr64::frontend::report_display_refresh_rate(refresh_rate);
            last_display_refresh_rate = refresh_rate;
        }
#endif
    }

    void shutdown() override {
        RT64::wr64SecondaryRaceActive.store(false, std::memory_order_release);
        RT64::wr64SeparateWindowsBackend.store(false, std::memory_order_release);
        RT64::wr64RTStartupGate.publish(RT64::Wr64RTStartupGate::State::Cancelled);
        if (app != nullptr) {
            app->end();
            app.reset();
        }
    }

    uint32_t get_display_framerate() const override {
        if (app != nullptr && app->sharedQueueResources != nullptr &&
            app->sharedQueueResources->swapChainRate > 0) {
            return app->sharedQueueResources->swapChainRate;
        }
        return 60;
    }

    float get_resolution_scale() const override {
        if (app == nullptr) {
            return 1.0F;
        }
        switch (app->userConfig.resolution) {
            case RT64::UserConfiguration::Resolution::WindowIntegerScale:
                if (app->sharedQueueResources != nullptr &&
                    app->sharedQueueResources->swapChainHeight > 0) {
                    const uint32_t height = app->sharedQueueResources->swapChainHeight;
                    return std::max(
                        static_cast<float>((height + kReferenceHeight - 1) / kReferenceHeight),
                        1.0F);
                }
                break;
            case RT64::UserConfiguration::Resolution::Manual:
                return static_cast<float>(app->userConfig.resolutionMultiplier);
            case RT64::UserConfiguration::Resolution::Original:
            case RT64::UserConfiguration::Resolution::OptionCount:
                break;
        }
        return 1.0F;
    }

private:
    bool reconfigure_api(const ultramodern::renderer::GraphicsConfig& requested) {
        auto recovery = requested;
        recovery.api_option = initialized_config.api_option;
        if (ultramodern::is_game_started()) {
            // UI disables this option during gameplay; also reject changes
            // from callers outside the UI while a ROM thread is active.
            ultramodern::renderer::set_graphics_config(recovery);
#ifdef WR64_ENABLE_FRONTEND
            wr64::frontend::report_graphics_reconfiguration(false, recovery.api_option);
#endif
            return true;
        }
#ifdef WR64_ENABLE_FRONTEND
        recompui::set_input_suspended(true);
        recompui::begin_renderer_reconfiguration();
#endif
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[rt64] applying graphics API in the current frontend window\n"));
        const auto stop = [this] {
            RT64::wr64SecondaryRaceActive.store(false, std::memory_order_release);
            RT64::wr64SeparateWindowsBackend.store(false, std::memory_order_release);
            if (app) { app->end(); app.reset(); }
        };
        const auto start = [this](const auto& config) {
            try {
                initialize(config);
                return valid();
            }
            catch (const std::exception& error) {
                std::fprintf(stderr, "[rt64] graphics API setup exception: %s\n", error.what());
                setup_result = ultramodern::renderer::SetupResult::GraphicsDeviceNotFound;
                return false;
            }
        };
        const auto result = wr64::frontend::reconfigure_graphics(requested, recovery, stop, start);
#ifdef WR64_ENABLE_FRONTEND
        recompui::end_renderer_reconfiguration();
#endif
        const bool applied = result == wr64::frontend::GraphicsReconfigurationResult::Applied;
        if (!applied) ultramodern::renderer::set_graphics_config(recovery);
        if (result == wr64::frontend::GraphicsReconfigurationResult::Failed) {
            std::fprintf(stderr, "[rt64] graphics API setup and recovery both failed\n");
            ultramodern::quit();
        }
#ifdef WR64_ENABLE_FRONTEND
        wr64::frontend::report_graphics_reconfiguration(applied, recovery.api_option);
#endif
        return true;
    }

    void poll_startup_prewarm() {
        using State = RT64::Wr64RTStartupGate::State;
        auto &gate = RT64::wr64RTStartupGate;
        if (!gate.waiting()) return;
        const auto selected = RT64::getWr64RTSettings();
        const auto *renderer = app->workloadQueue->framebufferRenderer.get();
        const bool cachedSky = selected.skyReflections && selected.rasterSky && renderer->wr64RasterSkySupported;
        const bool raySky = selected.skyReflections && !selected.rasterSky && renderer->wr64RTSupported;
        const bool rayObjects = selected.reflections && renderer->wr64RTSupported;
        const bool rasterShadows = selected.rasterShadows && renderer->wr64RasterSkySupported;
        const bool rasterReflections = selected.rasterReflections && renderer->wr64RasterSkySupported;
        if (!cachedSky && !raySky && !rayObjects && !rasterShadows && !rasterReflections) {
            gate.publish(State::Bypassed);
            RT64::wr64RTDiagnostic("startup-prewarm", "state=bypassed");
            return;
        }
        if (gate.state() == State::Requested) {
            gate.publish(State::Pending);
            RT64::wr64RTDiagnostic("startup-prewarm", "state=pending native_logo=1 game_threads_created=0");
        }
        const auto multisampling = RT64::RasterShader::generateMultisamplingPattern(
            app->userConfig.msaaSampleCount(), app->device->getCapabilities().sampleLocations);
        const auto status = app->workloadQueue->framebufferRenderer->prewarmWr64RTPipelines(
            app->device.get(), app->rasterShaderCache->shaderUber->pipelineLayout.get(), multisampling,
            raySky, selected.shadows && rayObjects, false, rayObjects, cachedSky, rasterShadows, rasterReflections);
        if (status != RT64::Wr64RTPrewarmStatus::Pending) {
            const bool ready = status == RT64::Wr64RTPrewarmStatus::Ready;
            gate.publish(ready ? State::Ready : State::Failed);
            RT64::wr64RTDiagnostic("startup-prewarm", ready ? "state=ready" : "state=failed native_fallback=1");
            if (!ready) std::fprintf(stderr, "[rt64] Optional RT preparation failed; continuing with native rendering.\n");
        }
    }
    void report_graphics_settings() const {
        const auto& config = app->userConfig;
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
            "[rt64] applied graphics: resolution=%s scale=%.2f downsample=%d "
            "samples=%u aspect=%s HUD=%s refresh=%s target=%d\n",
            config.resolution == RT64::UserConfiguration::Resolution::WindowIntegerScale ? "auto" : "manual",
            config.resolutionMultiplier, config.downsampleMultiplier, config.msaaSampleCount(),
            aspect_ratio_name(config.aspectRatio), aspect_ratio_name(config.extAspectRatio),
            refresh_rate_name(config.refreshRate), config.refreshRateTarget));
    }

    void configure_multisampling_support() {
        // This custom context does not populate RecompFrontend's separate
        // RT64Context globals. Query the device that actually renders USA.
        const auto& capabilities = app->device->getCapabilities();
        supported_sample_counts = capabilities.sampleLocations
            ? app->device->getSampleCountsSupported(RT64::RenderTarget::colorBufferFormat(app->shaderLibrary->usesHDR)) &
              app->device->getSampleCountsSupported(RT64::RenderTarget::depthBufferFormat())
            : 1;
#ifdef WR64_ENABLE_FRONTEND
        if (!wr64::frontend::ready()) return;
        wr64::frontend::report_multisampling_support(supported_sample_counts, capabilities.sampleLocations);
#endif
    }

    void constrain_multisampling() {
        if ((supported_sample_counts & app->userConfig.msaaSampleCount()) == 0)
            app->userConfig.antialiasing = RT64::UserConfiguration::Antialiasing::None;
    }

    void trace_vi_state() {
        if (!viewport_trace_enabled() || vi_regs == nullptr || trace_line_count >= 256) {
            return;
        }

        const uint32_t values[] = {
            vi_regs->VI_STATUS_REG,
            vi_regs->VI_WIDTH_REG,
            vi_regs->VI_H_START_REG,
            vi_regs->VI_V_START_REG,
            vi_regs->VI_X_SCALE_REG,
            vi_regs->VI_Y_SCALE_REG,
        };
        if (vi_trace_initialized && std::equal(std::begin(values), std::end(values), std::begin(last_vi_values))) {
            return;
        }

        std::copy(std::begin(values), std::end(values), std::begin(last_vi_values));
        vi_trace_initialized = true;
        trace_line_count++;

        const uint32_t h_start = (vi_regs->VI_H_START_REG >> 16) & 0x3FFU;
        const uint32_t h_end = vi_regs->VI_H_START_REG & 0x3FFU;
        const uint32_t v_start = (vi_regs->VI_V_START_REG >> 16) & 0x3FFU;
        const uint32_t v_end = vi_regs->VI_V_START_REG & 0x3FFU;
        const uint32_t x_scale = vi_regs->VI_X_SCALE_REG & 0xFFFU;
        const uint32_t x_offset = (vi_regs->VI_X_SCALE_REG >> 16) & 0xFFFU;
        const uint32_t y_scale = vi_regs->VI_Y_SCALE_REG & 0xFFFU;
        const uint32_t y_offset = (vi_regs->VI_Y_SCALE_REG >> 16) & 0xFFFU;
        const double estimated_width = x_scale != 0
            ? (static_cast<double>(h_end - h_start) * 1024.0) / static_cast<double>(x_scale)
            : 0.0;
        const double estimated_height = y_scale != 0
            ? (static_cast<double>(v_end - v_start) * 1024.0) / (2.0 * static_cast<double>(y_scale))
            : 0.0;

        WR64_DIAGNOSTIC_LOG(std::fprintf(
            stderr,
            "[rt64] viewport trace VI: screen=%llu status=%08X origin=%06X width=%u "
            "h=(%u,%u) v=(%u,%u) scale=(%u,%u) offset=(%u,%u) estimated=%.2fx%.2f\n",
            static_cast<unsigned long long>(screen_update_count),
            vi_regs->VI_STATUS_REG,
            vi_regs->VI_ORIGIN_REG & 0xFFFFFFU,
            vi_regs->VI_WIDTH_REG,
            h_start,
            h_end,
            v_start,
            v_end,
            x_scale,
            y_scale,
            x_offset,
            y_offset,
            estimated_width,
            estimated_height));
    }

    void trace_render_bounds(const OSTask* task) {
        if (!viewport_trace_enabled() || app == nullptr || trace_line_count >= 256) {
            return;
        }

        const auto& rdp = *app->state->rdp;
        const auto& rsp = *app->state->rsp;
        const auto& scissor = rdp.scissorRectStack[rdp.scissorStackSize - 1];
        const auto& viewport = rsp.viewportStack[rsp.viewportStackSize - 1];

        const int32_t values[] = {
            scissor.ulx,
            scissor.uly,
            scissor.lrx,
            scissor.lry,
            static_cast<int32_t>(viewport.scale.x * 4.0f),
            static_cast<int32_t>(viewport.scale.y * 4.0f),
            static_cast<int32_t>(viewport.translate.x * 4.0f),
            static_cast<int32_t>(viewport.translate.y * 4.0f),
            static_cast<int32_t>(rdp.colorImage.width),
        };
        if (bounds_trace_initialized && std::equal(std::begin(values), std::end(values), std::begin(last_bounds_values))) {
            return;
        }

        std::copy(std::begin(values), std::end(values), std::begin(last_bounds_values));
        bounds_trace_initialized = true;
        trace_line_count++;

        WR64_DIAGNOSTIC_LOG(std::fprintf(
            stderr,
            "[rt64] viewport trace DL: screen=%llu task=%08X color=%06X/%u "
            "scissor=(%.2f,%.2f)-(%.2f,%.2f) viewport-scale=(%.2f,%.2f) "
            "viewport-translate=(%.2f,%.2f) viewport-rect=(%.2f,%.2f)-(%.2f,%.2f)\n",
            static_cast<unsigned long long>(screen_update_count),
            task->t.data_ptr,
            rdp.colorImage.address & 0xFFFFFFU,
            rdp.colorImage.width,
            static_cast<double>(scissor.ulx) / 4.0,
            static_cast<double>(scissor.uly) / 4.0,
            static_cast<double>(scissor.lrx) / 4.0,
            static_cast<double>(scissor.lry) / 4.0,
            viewport.scale.x,
            viewport.scale.y,
            viewport.translate.x,
            viewport.translate.y,
            viewport.translate.x - viewport.scale.x,
            viewport.translate.y - viewport.scale.y,
            viewport.translate.x + viewport.scale.x,
            viewport.translate.y + viewport.scale.y));
    }

    std::unique_ptr<RT64::Application> app;
#ifdef WR64_ENABLE_FRONTEND
    recompui::renderer::TexturePackState texture_pack_state;
#endif
    uint8_t* rdram;
    ultramodern::renderer::WindowHandle window_handle;
    ultramodern::renderer::GraphicsConfig initialized_config{};
    ultramodern::renderer::ViRegs* vi_regs = nullptr;
    uint64_t screen_update_count = 0;
    uint32_t trace_line_count = 0;
    uint32_t supported_sample_counts = 1;
    uint32_t last_display_refresh_rate = 0;
    bool vi_trace_initialized = false;
    bool bounds_trace_initialized = false;
    uint32_t last_vi_values[6]{};
    int32_t last_bounds_values[9]{};
};

} // namespace

std::unique_ptr<ultramodern::renderer::RendererContext> create_render_context(
    uint8_t* rdram,
    ultramodern::renderer::WindowHandle window_handle,
    bool developer_mode) {
    return std::make_unique<RT64Context>(rdram, window_handle, developer_mode);
}

} // namespace wr64::renderer

#endif
