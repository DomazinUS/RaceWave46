#include "wr64_frontend.hpp"
#include "wr64_manual_frontend.hpp"
#include "wr64_graphics_restart.hpp"
#include "wr64_diagnostic_policy.h"

#ifdef WR64_ENABLE_FRONTEND

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <chrono>
#include <fstream>
#include <mutex>

#include "SDL.h"

#include "recompui/recompui.h"
#include "recompui/program_config.h"
#include "recompui/config.h"
#include "base/ui_launcher.h"
#include "base/ui_game_option.h"
#include "elements/ui_label.h"
#include "util/file.h"
#include "ultramodern/ultramodern.hpp"
#include "recompinput/input_events.h"
#include "recompinput/profiles.h"
#include "wr64_input.hpp"
#include "wr64_split_screen.hpp"
#include "wr64_camera_fov.hpp"
#include "wr64_draw_distance.hpp"
#include "wr64_object_distance.hpp"
#include "wr64_seabed_distance.hpp"
#include "wr64_sunny_detail.hpp"
#include "wr64_free_ride_menu.hpp"
#include "config/ui_config_page_controls.h"
#include "wr64_editions.hpp"
#include "wr64_game_rumble.hpp"
#include "wr64_ghost.hpp"
#include "wr64_texture_packs.hpp"
#include "wr64_achievements_ui.hpp"
#include "librecomp/game.hpp"
#include "librecomp/config.hpp"
#include "wr64_gameplay_settings.hpp"
#include "wr64_enhancement_controls.hpp"
#include "hle/rt64_game_frame.h"
#include "common/rt64_wr64_ui_filter.h"
#include "common/rt64_wr64_far_water_distance.h"
#include "common/rt64_wr64_cloud_coverage_settings.h"
#include "common/rt64_wr64_wave_distance.h"
#include "common/rt64_wr64_ui_filter_diagnostics.h"
#include "common/rt64_wr64_rt_diagnostics.h"
#include "common/rt64_wr64_rt_settings.h"
#include "common/rt64_wr64_frame_pacing_diagnostic.h"
#include "common/rt64_wr64_diagnostic_history.h"

// recompui/src/base/ui_launcher.cpp:27 declares
//     extern std::vector<recomp::GameEntry> supported_games;
// and its default_launcher_init_callback indexes supported_games[0] FOUR times
// with no size check (ui_launcher.cpp:633). init_launcher_menu() is called
// unconditionally from create_menus(), which runs inside RT64's init hook - so
// an empty vector is not a blank launcher, it is a crash during UI creation.
//
// Their own comment above that extern reads:
//     TODO: Store somewhere else and have base game register/initialize.
// wr64::frontend::register_game below is this project doing exactly that.
std::vector<recomp::GameEntry> supported_games{};
extern SDL_Window* window;

namespace wr64::frontend {
namespace {

bool configured = false;
std::atomic_int pending_fullscreen{-1};
std::atomic_uint pending_fullscreen_toggles{0};
std::atomic_uint pending_settings_toggles{0};
std::atomic_uint pending_refresh_rate{0};
std::atomic_uint64_t pending_multisampling{0};
std::atomic_uint active_graphics_api{0};
std::atomic_uint pending_graphics_reconfiguration{0};
bool graphics_reconfiguration_failed = false;
bool graphics_reconfiguration_rollback = false;
EnhancementAvailability enhancement_controls_available{};

constexpr double DefaultWaveRoundnessPercent = 50.0;
constexpr const char *EnhancementsTabName = "Enhancements";
constexpr const char *EnhancementsTabId = "enhancements";
constexpr const char *WaveRoundnessOptionId = "wave_roundness";
constexpr const char *UsaAspectDescription =
    "Original uses this USA build's native 16:9 view. Expand matches wider windows, including ultrawide displays.";

void toggle_settings_on_ui_thread();

// Optional UI-filter diagnostics contain bounded metadata, never texture, ROM,
// or save data. Install before settings load to capture the selected mode.
struct UiFilterDiagnosticLog {
    std::mutex mutex;
    std::ofstream stream;
    std::atomic_uint entries{0};
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
};

UiFilterDiagnosticLog& uiFilterDiagnosticLog() {
    // Keep the sink valid through renderer thread shutdown and static teardown.
    static auto* log = new UiFilterDiagnosticLog;
    return *log;
}

void writeUiFilterDiagnostic(const char* stage, const char* details) {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    auto& log = uiFilterDiagnosticLog();
    constexpr unsigned int MaxEntries = 1024;
    if (log.entries.load(std::memory_order_relaxed) >= MaxEntries) return;
    std::lock_guard lock(log.mutex);
    if (!log.stream || log.entries.load(std::memory_order_relaxed) >= MaxEntries) return;
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - log.start).count();
    log.stream << elapsed << "ms " << stage << ' ' << details << '\n';
    if (log.entries.fetch_add(1, std::memory_order_relaxed) + 1 == MaxEntries) {
        log.stream << "Diagnostic limit reached; rendering continues normally.\n";
        RT64::setWr64UiFilterDiagnosticSink(nullptr);
    }
    log.stream.flush();
}

void initializeUiFilterDiagnostic() {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    try {
        auto& log = uiFilterDiagnosticLog();
        log.stream.open(recomp::get_config_path() / "ui-filter-diagnostic.log", std::ios::trunc);
        if (!log.stream) return;
        RT64::setWr64UiFilterDiagnosticSink(writeUiFilterDiagnostic);
        writeUiFilterDiagnostic("session", "USA manual canary; UI filter metadata only; maximum 1024 entries");
    } catch (const std::exception& error) {
        std::fprintf(stderr, "[frontend] could not open filter diagnostic: %s\n", error.what());
    }
}

struct SunnySceneryDiagnosticLog {
    std::mutex mutex;
    std::ofstream stream;
    unsigned int entries = 0;
};
SunnySceneryDiagnosticLog& sunnySceneryDiagnosticLog() {
    static auto* log = new SunnySceneryDiagnosticLog;
    return *log;
}
void writeSunnySceneryDiagnostic(const char* details) {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    auto& log = sunnySceneryDiagnosticLog();
    std::lock_guard lock(log.mutex);
    if (!log.stream || log.entries >= 128) return;
    log.stream << details << '\n';
    if (++log.entries == 128) log.stream << "Diagnostic limit reached.\n";
    log.stream.flush();
}
void initializeSunnySceneryDiagnostic() {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    try {
        auto& log = sunnySceneryDiagnosticLog();
        log.stream.open(recomp::get_config_path() / "two-player-detail.log", std::ios::trunc);
        if (!log.stream) return;
        wr64::sunny_detail::set_diagnostic_sink(writeSunnySceneryDiagnostic);
        writeSunnySceneryDiagnostic("Two-player visual detail: course-load and bounded animal events; maximum 128 lines.");
    } catch (const std::exception&) {
        std::fprintf(stderr, "[two-player-detail] could not open diagnostic log\n");
    }
}

struct RTReflectionDiagnosticLog {
    std::mutex mutex;
    std::ofstream stream;
    std::atomic_uint entries{0};
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
};

RTReflectionDiagnosticLog& rtReflectionDiagnosticLog() {
    // Renderer workers can finish after frontend teardown. Retain the sink and
    // its synchronization objects until the process exits.
    static auto* log = new RTReflectionDiagnosticLog;
    return *log;
}

void writeRTReflectionDiagnostic(const char* stage, const char* details) {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    auto& log = rtReflectionDiagnosticLog();
    constexpr unsigned int MaxRecords = 511; // One final marker keeps the file at 512 lines.
    if (log.entries.load(std::memory_order_relaxed) >= MaxRecords) return;
    std::lock_guard lock(log.mutex);
    if (!log.stream || log.entries.load(std::memory_order_relaxed) >= MaxRecords) return;
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - log.start).count();
    log.stream << elapsed << "ms " << stage << ' ' << details << '\n';
    if (log.entries.fetch_add(1, std::memory_order_relaxed) + 1 == MaxRecords) {
        log.stream << "Diagnostic limit reached; rendering continues normally.\n";
        RT64::setWr64RTDiagnosticSink(nullptr);
    }
    log.stream.flush();
}

void initializeRTReflectionDiagnostic() {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    try {
        auto& log = rtReflectionDiagnosticLog();
        log.stream.open(recomp::get_config_path() / "rt-reflections.log", std::ios::trunc);
        if (!log.stream) {
            std::fprintf(stderr, "[frontend] could not open reflection diagnostic\n");
            return;
        }
        RT64::setWr64RTDiagnosticSink(writeRTReflectionDiagnostic);
        writeRTReflectionDiagnostic("session", "USA water reflection prototype; maximum 512 lines");
    } catch (const std::exception& error) {
        std::fprintf(stderr, "[frontend] could not open reflection diagnostic: %s\n", error.what());
    }
}

struct FramePacingDiagnosticLog {
    std::mutex mutex;
    std::ofstream stream;
    unsigned int entries = 0;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
};

FramePacingDiagnosticLog& framePacingDiagnosticLog() {
    // Keep synchronization/file lifetime valid until renderer workers exit.
    static auto* log = new FramePacingDiagnosticLog;
    return *log;
}

void writeFramePacingDiagnostic(const char* stage, const char* details) noexcept {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    try {
        auto& log = framePacingDiagnosticLog();
        std::lock_guard lock(log.mutex);
        constexpr unsigned int MaxRecords = 511;
        if (!log.stream || log.entries >= MaxRecords) return;
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - log.start).count();
        log.stream << elapsed << "ms " << stage << ' ' << details << '\n';
        if (++log.entries == MaxRecords) {
            log.stream << "Diagnostic limit reached; rendering continues normally.\n";
            RT64::setWr64FramePacingDiagnosticSink(nullptr);
        }
        log.stream.flush();
        if (!log.stream) RT64::setWr64FramePacingDiagnosticSink(nullptr);
    } catch (...) {
        // A diagnostic disk/locking failure must never escape a render worker.
        RT64::setWr64FramePacingDiagnosticSink(nullptr);
    }
}

void initializeFramePacingDiagnostic() noexcept {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    try {
        auto& log = framePacingDiagnosticLog();
        const auto path = recomp::get_config_path() / "frame-pacing.log";
        std::error_code error;
        if (!RT64::wr64ArchiveDiagnosticSession(path, error)) {
            std::fprintf(stderr, "[frontend] preserving prior frame-pacing log; new logging disabled: %s\n",
                error.message().c_str());
            return;
        }
        log.stream.open(path, std::ios::trunc);
        if (!log.stream) return;
        RT64::setWr64FramePacingDiagnosticSink(writeFramePacingDiagnostic);
        writeFramePacingDiagnostic("session", "numeric-only; 2-second producer summaries; maximum 512 lines; "
            "configuration fields are latest unless named max; config_changes marks mixed windows; "
            "render passes are GPU submissions, not display frames");
    } catch (...) {
        RT64::setWr64FramePacingDiagnosticSink(nullptr);
    }
}

double initialWaveRoundnessPercent() {
    const char *environmentValue = std::getenv(
        "WR64_WATER_LAPLACIAN_STRENGTH");
    if ((environmentValue == nullptr) ||
        (environmentValue[0] == '\0'))
    {
        return DefaultWaveRoundnessPercent;
    }

    char *end = nullptr;
    const double parsed = std::strtod(environmentValue, &end);
    if ((end == environmentValue) || (end == nullptr) ||
        (end[0] != '\0') || !std::isfinite(parsed))
    {
        return DefaultWaveRoundnessPercent;
    }

    return std::clamp(parsed, 0.0, 1.0) * 100.0;
}

void applyWaveRoundness(double percent) {
    RT64::setWr64WaterLaplacianStrength(
        float(std::clamp(percent, 0.0, 100.0) / 100.0));
}

void applyWaterReflections(uint32_t mode) {
    RT64::setWr64WaterReflections(mode);
    WR64_DIAGNOSTIC_LOG(
        const auto selected = RT64::getWr64RTSettings();
        char details[128];
        std::snprintf(details, sizeof(details), "selected=%u reflections=%u sky=%u source=frontend rasterSky=%u rasterReflections=%u", mode,
            unsigned(selected.reflections), unsigned(selected.skyReflections),
            unsigned(selected.rasterSky), unsigned(selected.rasterReflections));
        RT64::wr64RTDiagnostic("setting", details));
}

void applyRayTracedShadows(bool enabled) {
    RT64::setWr64RayTracedShadows(enabled);
    WR64_DIAGNOSTIC_LOG(RT64::wr64RTDiagnostic("shadow-setting", enabled ? "selected=1 source=frontend" : "selected=0 source=frontend"));
}

void applyShadowMethod(uint32_t method) {
    RT64::setWr64ShadowMethod(method);
    WR64_DIAGNOSTIC_LOG(
        char details[64];
        std::snprintf(details, sizeof(details), "selected=%u source=frontend", method);
        RT64::wr64RTDiagnostic("shadow-setting", details));
}

void applySkyReflections(bool enabled) {
    RT64::setWr64SkyReflections(enabled);
    WR64_DIAGNOSTIC_LOG(RT64::wr64RTDiagnostic("sky-setting", enabled ? "selected=1 source=frontend" : "selected=0 source=frontend"));
}

void applySkyReflectionMethod(uint32_t method) {
    RT64::setWr64SkyReflectionMethod(method);
}

void updateSkyReflectionControls(recomp::config::Config& config) {
    update_enhancement_controls(config, enhancement_controls_available);
}

void updateReflectionBackendAvailability() {
    using Api = ultramodern::renderer::GraphicsApi;
    const unsigned int reported = active_graphics_api.load();
    const auto active = (reported & 0xffu) != 0u ? Api((reported & 0xffu) - 1u) : Api::Auto;
    const auto selected = Api(std::get<uint32_t>(recompui::config::get_graphics_config()
        .get_temp_option_value(recompui::config::graphics::options::api_option)));
    const auto available = enhancement_availability(selected, active, (reported & (1u << 16)) != 0);
    if (available == enhancement_controls_available) return;
    enhancement_controls_available = available;
    updateSkyReflectionControls(recompui::config::get_config(EnhancementsTabId));
}

bool migrateReflectionProfile(nlohmann::json& profile) {
    if (!profile.is_object()) return false;
    const auto water = profile.find("water_reflections");
    std::string key = water != profile.end() && water->is_string() ? water->get<std::string>() : std::string{};
    for (char& c : key) if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
    const bool legacyRaster = key == "rastersky" ||
        (water != profile.end() && water->is_number() && *water == 2);
    bool changed = false;
    if (legacyRaster) {
        profile["water_reflections"] = "Original";
        changed = true;
    }
    // An explicit method marks the independent sky model and is authoritative,
    // including Original water with a deliberately enabled sky reflection.
    if (!profile.contains("sky_reflection_method")) {
        const bool rasterObjects = key == "rasterized";
        profile["sky_reflection_method"] = (legacyRaster || rasterObjects) ? "Rasterized" : "RayTraced";
        const auto sky = profile.find("rt_sky_reflections");
        profile["rt_sky_reflections"] = rasterObjects ?
            (sky != profile.end() && sky->is_boolean() && sky->get<bool>()) :
            (legacyRaster || key == "raytraced") && (sky == profile.end() || !sky->is_boolean() || sky->get<bool>());
        changed = true;
    }
    else if (legacyRaster && !profile.contains("rt_sky_reflections")) {
        profile["rt_sky_reflections"] = true;
    }
    if (!profile.contains("shadow_method")) {
        const auto shadows = profile.find("ray_traced_shadows");
        profile["shadow_method"] = shadows != profile.end() && shadows->is_boolean() && !shadows->get<bool>() ?
            "Original" : "RayTraced";
        changed = true;
    }
    return changed;
}

bool loadReflectionProfile(recomp::config::Config& config) {
    bool changed = false;
    nlohmann::json migrated;
    const bool loaded = config.load_config([&](nlohmann::json& profile) {
        if (!profile.is_object()) return false;
        changed = migrateReflectionProfile(profile);
        if (changed) migrated = profile;
        return true;
    });
    // Config's normal backup writer retains the original profile. Save the
    // migrated JSON itself so unrelated preferences are preserved verbatim.
    return loaded && (!changed || config.save_config_json(migrated));
}

void applyReflectionDistance(double percent) {
    RT64::setWr64ReflectionDistance(percent);
    WR64_DIAGNOSTIC_LOG(
        char details[80];
        std::snprintf(details, sizeof(details), "percent=%u source=frontend", RT64::getWr64RTSettings().reflectionDistancePercent);
        RT64::wr64RTDiagnostic("reflection-distance", details));
}

void applyShadowSamples(double samples) {
    RT64::setWr64ShadowSamples(samples);
    WR64_DIAGNOSTIC_LOG(
        char details[80];
        std::snprintf(details, sizeof(details), "rays=%u source=frontend", RT64::getWr64RTSettings().shadowSamples);
        RT64::wr64RTDiagnostic("shadow-quality", details));
}

void applyRasterSkyStrength(double percent) {
    RT64::setWr64RasterSkyStrength(percent);
}

void updateGraphicsApiDetails() {
    if (active_graphics_api.load() == 0) return;
    auto& graphics = recompui::config::get_graphics_config();
    const auto& option = recompui::config::graphics::options::api_option;
    const bool game_started = ultramodern::is_game_started();
    const uint64_t key = 1u | (uint64_t(game_started) << 1) | (uint64_t(graphics_reconfiguration_failed) << 2);
    static uint64_t previous_key = 0;
    if (key == previous_key) return;

    std::string details;
    graphics.update_option_disabled(option, game_started);
    if (graphics_reconfiguration_failed) details = "The selected API could not start; the previous API was restored.";
    graphics.update_option_enum_details(option, details);
    previous_key = key;
}

void process_pending_ui() {
    try {
        wr64::achievements_ui::update();
        if (const unsigned int result = pending_graphics_reconfiguration.exchange(0)) {
            struct ResumeInput {
                ~ResumeInput() {
                    graphics_reconfiguration_rollback = false;
                    recompui::set_input_suspended(false);
                }
            } resume_input;
            graphics_reconfiguration_failed = (result & 1u) != 0;
            if (graphics_reconfiguration_failed) {
                auto& graphics = recompui::config::get_graphics_config();
                graphics_reconfiguration_rollback = true;
                const auto& option = recompui::config::graphics::options::api_option;
                graphics.update_option_value(option, uint32_t(result >> 8));
                graphics.apply_option_value(option);
                if (!graphics.save_config_json(graphics.get_json_config())) {
                    std::fprintf(stderr, "[frontend] could not save restored graphics API selection\n");
                }
                graphics_reconfiguration_rollback = false;
            }
        }
        updateGraphicsApiDetails();
        updateReflectionBackendAvailability();
        if (const unsigned int rate = pending_refresh_rate.exchange(0)) {
            recompui::config::graphics::update_refresh_rate(rate);
        }
        if (const uint64_t support = pending_multisampling.exchange(0)) {
            const unsigned int counts = static_cast<unsigned int>(support);
            const bool sample_positions = (support & (uint64_t(1) << 32)) != 0;
            auto& graphics = recompui::config::get_graphics_config();
            for (const auto [option, count] : {
                std::pair{ultramodern::renderer::Antialiasing::MSAA2X, 2u},
                std::pair{ultramodern::renderer::Antialiasing::MSAA4X, 4u}}) {
                graphics.update_enum_option_disabled(recompui::config::graphics::options::msaa_option,
                    uint32_t(option), (counts & count) == 0);
            }
            graphics.update_option_enum_details(recompui::config::graphics::options::msaa_option,
                sample_positions ? "" : "MSAA unavailable: this device lacks programmable sample positions");
        }
        const unsigned int fullscreen_toggles = pending_fullscreen_toggles.exchange(0);
        const unsigned int settings_toggles = pending_settings_toggles.exchange(0);
        if (recompui::is_input_suspended()) return;
        wr64::input::process_pending_ui();
        if (fullscreen_toggles & 1u) {
            auto& graphics = recompui::config::get_graphics_config();
            const auto& option = recompui::config::graphics::options::wm_option;
            const auto current = std::get<uint32_t>(graphics.get_option_value(option));
            const auto next = current == uint32_t(ultramodern::renderer::WindowMode::Windowed)
                ? ultramodern::renderer::WindowMode::Fullscreen : ultramodern::renderer::WindowMode::Windowed;
            graphics.update_option_value(option, uint32_t(next));
            graphics.apply_option_value(option);
            // save_config_json invokes the normal renderer callback using only
            // applied values; other pending Graphics edits remain pending.
            graphics.save_config_json(graphics.get_json_config());
        }
        if (settings_toggles & 1u) toggle_settings_on_ui_thread();
    } catch (const std::exception& error) {
        std::fprintf(stderr, "[frontend] could not update settings: %s\n", error.what());
    }
}

} // namespace

void register_game(const recomp::GameEntry& entry) {
    supported_games.push_back(entry);
}

void configure() {
    if (configured) {
        return;
    }

    if (supported_games.empty()) {
        // Every path into the launcher dereferences element zero. Refusing here
        // turns a crash inside RT64's init hook into one line on the console.
        std::fprintf(stderr,
            "[frontend] no game registered - call wr64::frontend::register_game "
            "before configure(). The settings UI will not be started.\n");
        return;
    }

    try {
        // Establish frontend ownership before any renderer work or inherited
        // development flags can activate a parked effect. finalize() below
        // applies the saved choices after all options have been registered.
        RT64::setWr64WaterReflections(0);
        RT64::setWr64RayTracedShadows(true);
        RT64::setWr64SkyReflections(false);
        RT64::setWr64SkyReflectionMethod(0u);
        RT64::setWr64ReflectionDistance(100.0);
        RT64::setWr64ShadowSamples(16.0);
        RT64::setWr64RasterShadowDistance(0u);
        RT64::setWr64RasterSkyStrength(100.0);
        RT64::setWr64CloudCoverageMode(0u);
        initializeUiFilterDiagnostic();
        initializeRTReflectionDiagnostic();
        initializeSunnySceneryDiagnostic();
        initializeFramePacingDiagnostic();
        // These two throw from their GETTERS when unset, and recompui::message_box
        // reads the name, so an error anywhere later would itself become an
        // exception. They go first.
        recompui::programconfig::set_program_name("Wave Race 64: Recompiled");
        recompui::programconfig::set_program_id(u8"waverace64");
        wr64::texture_packs::register_mod_types();

        // REQUIRED. UIState's constructor throws
        //     "No primary font was registered with recompui::register_primary_font"
        // and it runs inside RT64's render hook, where a throw is a crash with no
        // useful message. This branch uses the supplied Lato font with its OFL
        // notice and copies it into assets/ during the build.
        //
        // The second argument is the font FAMILY, which RmlUi reads from the
        // font's internal name rather than its filename. assets/recomp.rcss must
        // name the same family.
        recompui::register_primary_font("LatoLatin-Regular.ttf", "LatoLatin");

        recompui::register_extra_font("LatoLatin-Bold.ttf");
        wr64::manual_frontend::configure_theme();
        recompui::register_launcher_init_callback(wr64::manual_frontend::create_launcher);

        // Keep the current settings behavior under the manual-style widgets.
        // Create the familiar General/Controls/Graphics/Sound tabs first.
        auto& generalConfig = recompui::config::create_general_tab(recompui::config::GeneralTabOptions{
            .has_rumble_strength = false, // Register below the gameplay toggle.
            .has_gyro_sensitivity = false,
            .has_mouse_sensitivity = false,
            .has_player_two_rumble_strength = true,
        });
        generalConfig.add_bool_option("gameplay_rumble", "Gameplay rumble",
            "Adds engine, impact and water-contact rumble to gameplay. The player rumble strengths control each assigned device's output.", true);
        generalConfig.add_option_change_callback("gameplay_rumble",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) { wr64_game_rumble_set_enabled(std::get<bool>(value)); });
        recompui::config::general::add_rumble_strength_options(true);
        generalConfig.add_option_hidden_dependency(recompui::config::general::options::rumble_strength,
            "gameplay_rumble", false);
        generalConfig.add_option_hidden_dependency(recompui::config::general::options::rumble_strength_p2,
            "gameplay_rumble", false);
        generalConfig.add_bool_option("show_ghost", "Show Time Trial ghost",
            "Race against the dolphin from your best run or a saved ghost. Recording continues while the ghost is hidden.", true);
        generalConfig.add_option_change_callback("show_ghost",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) { wr64::ghost::set_visible(std::get<bool>(value)); });

        if (wr64::input::ready()) {
            recompui::set_player_assignment_callback(
                [] { wr64::input::request_multiplayer_assignment(); },
                [] { return wr64::input::multiplayer_requested() ? 2u : 0u; });
            recompui::config::create_controls_tab();
        }
        else {
            std::fprintf(stderr,
                "[frontend] input did not initialise; the Controls tab is omitted "
                "rather than shown empty\n");
        }
        auto& graphicsConfig = recompui::config::create_graphics_tab();
        graphicsConfig.update_option_description(recompui::config::graphics::options::ar_option, UsaAspectDescription);
        graphicsConfig.update_option_description(recompui::config::graphics::options::api_option,
            "Selects the graphics API. Before starting a race, select Apply to switch in the current window.");
        graphicsConfig.add_option_change_callback(recompui::config::graphics::options::api_option,
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant previous,
                recomp::config::OptionChangeContext context) {
                if (context != recomp::config::OptionChangeContext::Permanent || value == previous ||
                    graphics_reconfiguration_rollback || active_graphics_api.load() == 0) return;
                graphics_reconfiguration_failed = false;
                // Apply runs on the UI render thread. Stop input immediately,
                // before another queued event could start the game. The config
                // save callback sends the actual work to the graphics thread.
                recompui::set_input_suspended(true);
            });
        recompui::config::create_sound_tab();

        // Live, persisted control over the existing water-height smoothing
        // pass. An explicitly supplied environment value seeds a fresh
        // configuration; after that, the saved frontend setting is the
        // authoritative value.
        const double initialRoundness = initialWaveRoundnessPercent();
        applyWaveRoundness(initialRoundness);

        recomp::config::Config &enhancementsConfig =
            recompui::config::create_config_tab(
                EnhancementsTabName,
                EnhancementsTabId,
                false);
        enhancementsConfig.add_number_option("camera_fov_extra_degrees", "Field of View",
            "Widens the chase-camera view by up to 10 degrees in one-player and two-player races. 0 keeps the original view.",
            0.0, 10.0, 1.0, 0, false, 5.0);
        enhancementsConfig.add_option_change_callback("camera_fov_extra_degrees",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                const double degrees = std::get<double>(value);
                wr64::camera_fov::set_extra_degrees(degrees);
                // Older experimental profiles allowed 20. Keep the displayed
                // and next saved value consistent with the native limit.
                if (!std::isfinite(degrees) || degrees < 0.0 || degrees > 10.0) {
                    enhancementsConfig.update_option_value("camera_fov_extra_degrees", wr64::camera_fov::extra_degrees());
                }
            });
        enhancementsConfig.add_enum_option("hud_menu_filter", "HUD & Menu Filtering",
            "Filters supported original game lettering and HUD textures. Original keeps the current rendering. Light gently smooths pixel boundaries. Enhanced also rounds matching diagonal edges.",
            {{0u, "Original"}, {1u, "Light"}, {2u, "Enhanced"}}, 2u);
        enhancementsConfig.add_option_change_callback("hud_menu_filter",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                const uint32_t mode = std::get<uint32_t>(value);
                RT64::setWr64UiFilter(mode);
                WR64_DIAGNOSTIC_LOG(
                    char details[96];
                    std::snprintf(details, sizeof(details), "selected=%u renderer=%u", mode, RT64::getWr64UiFilter());
                    RT64::wr64UiFilterDiagnostic("setting", details));
            });
        enhancementsConfig.add_number_option(
            WaveRoundnessOptionId,
            "Wave Roundness",
            "Rounds the waves in one-player and two-player modes. 0% keeps the original faceted waves; 50% is the recommended rounded look. Changes apply immediately.",
            0.0,
            100.0,
            1.0,
            0,
            true,
            initialRoundness);
        enhancementsConfig.add_option_change_callback(
            WaveRoundnessOptionId,
            [](recomp::config::ConfigValueVariant currentValue,
                recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext)
            {
                applyWaveRoundness(std::get<double>(currentValue));
            });
        enhancementsConfig.add_enum_option("water_reflections", "Water Reflections",
            "Original uses the game's original water rendering. Rasterized and Ray Traced require Direct3D 12. Ray Traced also requires compatible ray-tracing hardware. Rasterized provides scenery and object reflections without hardware ray tracing, on all courses and Dolphin Park's opening. Sky Reflections is a separate choice.\n\nTwo-player reflections require Enhanced visual detail before loading the race. Unavailable saved choices use Original rendering until their requirements are met.",
            {{0u, "Original"}, {3u, "Rasterized"}, {1u, "RayTraced", "Ray Traced"}}, 0u);
        enhancementsConfig.add_number_option("rt_reflection_distance", "Reflection Distance",
            "Limits how far scenery contributes to ray-traced water reflections and obscures ray-traced sky reflections. Lower values can improve performance but omit distant objects. Available when Water Reflections uses Ray Traced. Applies immediately.",
            25.0, 100.0, 5.0, 0, true, 100.0);
        enhancementsConfig.add_bool_option("rt_sky_reflections", "Sky Reflections",
            "Requires Direct3D 12. Reflects the sky, clouds, sun, moon and stars on the water independently of Water Reflections. Available on all courses, including Dolphin Park's opening. Two-player support requires Enhanced visual detail. Unavailable saved choices remain inactive until their requirements are met.", false);
        enhancementsConfig.add_enum_option("sky_reflection_method", "Sky Reflection Method",
            "Both methods require Direct3D 12. Rasterized provides a cheaper sky reflection without hardware ray tracing. Ray Traced requires compatible ray-tracing hardware. Either sky method works with any Water Reflections choice.",
            {{0u, "Rasterized"}, {1u, "RayTraced", "Ray Traced"}}, 1u);
        enhancementsConfig.add_number_option("raster_sky_strength", "Rasterized Reflection Strength",
            "Makes rasterized sky reflections more visible on the water.",
            100.0, 200.0, 5.0, 0, true, 100.0);
        enhancementsConfig.add_enum_option("shadow_method", "Shadows",
            "Original keeps the game's shadows. Rasterized and Ray Traced require Direct3D 12. Rasterized adds soft shadows to water and shore with any Water Reflections choice, without hardware ray tracing. Ray Traced requires compatible ray-tracing hardware and Ray Traced water reflections. Two-player support requires Enhanced visual detail before loading the race. Unavailable saved choices use Original shadows until their requirements are met.",
            {{0u, "Original"}, {1u, "Rasterized"}, {2u, "RayTraced", "Ray Traced"}}, 0u);
        enhancementsConfig.add_number_option("rt_shadow_samples", "Soft Shadow Quality",
            "Number of rays used for soft shadow edges. Lower values can improve performance but make the edges less smooth. Shadow width and strength stay the same. Requires Shadows and Water Reflections set to Ray Traced. Applies immediately.",
            4.0, 16.0, 4.0, 0, false, 16.0);
        enhancementsConfig.add_enum_option("raster_shadow_distance", "Shadow Draw Distance",
            "Extends rasterized shadow coverage on all courses, both players' views and Dolphin Park's opening. Higher values trade shadow sharpness for distance. Increase object and buoy distances too if their distant shadows are missing. Applies immediately; Original keeps the current range. Two-player shadows require Enhanced visual detail before loading the race.",
            {{0u, "Original"}, {1u, "1.5x"}, {2u, "2x"}, {3u, "3x"}}, 3u);
        enhancementsConfig.add_enum_option("buoy_draw_distance", "Buoy Draw Distance",
            "Extends checkpoint and area-limit buoy visibility across all courses, both players' views and Dolphin Park's opening. Nearby buoys take priority in crowded areas. Applies immediately; Original keeps the native distances. Twilight City's buoy light beams retain their original range.",
            {{0u, "Original"}, {1u, "1.5x"}, {2u, "2x"}}, 2u);
        enhancementsConfig.add_option_change_callback("buoy_draw_distance",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                wr64::draw_distance::set_mode(std::get<uint32_t>(value));
            });
        enhancementsConfig.add_enum_option("object_draw_distance", "Object Draw Distance",
            "Extends static 3D scenery, including ramps and ice, across all courses, both players' views and Dolphin Park's opening. 3x also extends the lettered Dolphin Park entrance. Applies immediately; Original keeps the native distance. Other moving objects, flat scenery sprites and terrain keep their existing visibility rules.",
            {{0u, "Original"}, {1u, "1.5x"}, {2u, "2x"}, {3u, "3x"}}, 3u);
        enhancementsConfig.add_option_change_callback("object_draw_distance",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                wr64::object_distance::set_mode(std::get<uint32_t>(value));
            });
        enhancementsConfig.add_enum_option("wave_draw_distance", "Wave Draw Distance (Experimental)",
        "Original is recommended for stable visuals. This experiment covers all courses, opening and course introductions, and both players in two-player mode. Extended animates the outer native wave ring; Extended+ carries that motion farther and fades it into flat water. Both can show sharp spikes or dips, popping, and uneven animation, especially with Extended+. Applies immediately; gameplay physics are unchanged.",
            {{0u, "Original"}, {1u, "Extended"}, {2u, "Extended+"}}, 0u);
        enhancementsConfig.update_option_hidden("wave_draw_distance", true);
        enhancementsConfig.add_option_change_callback("wave_draw_distance",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                // Keep older saved choices, but leave the hidden experiment inactive.
                RT64::setWr64WaveDistanceMode(0u);
            });
        enhancementsConfig.add_enum_option("far_water_distance", "Water Surface Distance",
            "Extends the flat outer water surface across all courses, both players' views and Dolphin Park's opening. Higher values push its distant edge toward the horizon. Increase Seabed Draw Distance alongside it where the water is transparent. Animated waves keep their existing range. Applies immediately; Original keeps the current coverage.",
            {{0u, "Original"}, {1u, "1.5x"}, {2u, "2x"}, {3u, "3x"}, {4u, "4x"}, {5u, "5x"}}, 5u);
        enhancementsConfig.add_option_change_callback("far_water_distance",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                RT64::setWr64FarWaterDistanceMode(std::get<uint32_t>(value));
            });
        enhancementsConfig.add_enum_option("cloud_coverage", "Cloud coverage",
            "Extended draws clouds beyond their original boundary. Applies immediately where clouds are present. In two-player races, Enhanced visual detail restores the cloud layers this setting extends.",
            {{0u, "Original"}, {1u, "Extended"}}, 1u);
        enhancementsConfig.add_option_change_callback("cloud_coverage",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                RT64::setWr64CloudCoverageMode(std::get<uint32_t>(value));
            });
        enhancementsConfig.add_enum_option("seabed_draw_distance", "Seabed Draw Distance",
            "Extends the underwater floor across all courses and Dolphin Park's opening. Match Water Surface Distance when extending the distant waterline, or adjust separately. Both players get their own floor with Enhanced visual detail; Original two-player water is opaque. Applies immediately; Original keeps the current coverage.",
            {{0u, "Original"}, {1u, "1.5x"}, {2u, "2x"}, {3u, "3x"}, {4u, "4x"}, {5u, "5x"}}, 5u);
        enhancementsConfig.add_option_change_callback("seabed_draw_distance",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                wr64::seabed_distance::set_mode(std::get<uint32_t>(value));
            });
        enhancementsConfig.add_option_change_callback("raster_sky_strength",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                const double requested = std::get<double>(value);
                applyRasterSkyStrength(requested);
                const auto selected = RT64::getWr64RTSettings();
                if (requested != selected.rasterSkyStrengthPercent)
                    enhancementsConfig.update_option_value("raster_sky_strength", double(selected.rasterSkyStrengthPercent));
                updateSkyReflectionControls(enhancementsConfig);
            });
        enhancementsConfig.add_option_change_callback("sky_reflection_method",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                applySkyReflectionMethod(std::get<uint32_t>(value));
                updateSkyReflectionControls(enhancementsConfig);
            });
        enhancementsConfig.add_option_change_callback("rt_reflection_distance",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                const double requested = std::get<double>(value);
                applyReflectionDistance(requested);
                const double selected = RT64::getWr64RTSettings().reflectionDistancePercent;
                if (requested != selected) enhancementsConfig.update_option_value("rt_reflection_distance", selected);
            });
        enhancementsConfig.add_option_change_callback("rt_shadow_samples",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                const double requested = std::get<double>(value);
                applyShadowSamples(requested);
                const double selected = RT64::getWr64RTSettings().shadowSamples;
                if (requested != selected) enhancementsConfig.update_option_value("rt_shadow_samples", selected);
            });
        enhancementsConfig.add_option_change_callback("shadow_method",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                applyShadowMethod(std::get<uint32_t>(value));
                updateSkyReflectionControls(enhancementsConfig);
            });
        enhancementsConfig.add_option_change_callback("raster_shadow_distance",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                RT64::setWr64RasterShadowDistance(std::get<uint32_t>(value));
            });
        enhancementsConfig.add_option_change_callback("rt_sky_reflections",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                applySkyReflections(std::get<bool>(value));
                updateSkyReflectionControls(enhancementsConfig);
            });
        enhancementsConfig.add_option_change_callback("water_reflections",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                const uint32_t mode = std::get<uint32_t>(value);
                applyWaterReflections(mode);
                updateSkyReflectionControls(enhancementsConfig);
            });
        enhancementsConfig.add_enum_option("split_screen_layout", "Two-player display",
            "Vertical is recommended only for 32:9 screens. It places players side by side, giving each player a 16:9 view.\n\n"
            "Horizontal places player 1 above player 2.\n\nSeparate windows requires Direct3D 12. During two-player races each player gets a full 16:9 view in a separate window. Move Player 2 to another monitor; F11 toggles its fullscreen view. Menus stay in the primary window and Player 2 stays black between races. Closing Player 2 shows both views in the primary window until the next race. Select before loading a race. Vulkan uses Horizontal when this choice is saved.",
            {{0u, "Horizontal"}, {1u, "Vertical"}, {2u, "Separate windows (Experimental)", "Separate windows"}}, 0u);
        enhancementsConfig.add_option_change_callback("split_screen_layout",
            [&enhancementsConfig](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                wr64::split_screen::set_mode(std::get<uint32_t>(value));
                updateSkyReflectionControls(enhancementsConfig);
            });
        // Retain the saved key so existing Original/Enhanced choices carry over.
        enhancementsConfig.add_enum_option("sunny_two_player_scenery", "Two-player visual detail",
            "Enhanced restores single-player scenery, water materials, sky detail, detailed checkpoint buoys and native wildlife across all race courses. Both players see the restored detail. Applies when the next course loads.",
            {{0u, "Original"}, {1u, "Enhanced"}}, 1u);
        enhancementsConfig.add_option_change_callback("sunny_two_player_scenery",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) { wr64::sunny_detail::set_enabled(std::get<uint32_t>(value) == 1u); });
        enhancementsConfig.add_bool_option("dolphin_free_ride", "Two-player Dolphin Park",
            "Adds Dolphin Park to two-player Course Select for untimed Free Ride with music, without tutorial text or narration. Works with all two-player display layouts.\n\n"
            "Turning this off removes Dolphin Park from Course Select. A Free Ride session already in progress continues until you leave it.", true);
        enhancementsConfig.add_option_change_callback("dolphin_free_ride",
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) { wr64::free_ride::set_enabled(std::get<bool>(value)); });
        // Keep the unfinished ghost-management tab hidden. The in-game dolphin
        // ghost and its General visibility setting remain available.

        recompui::config::create_mods_tab();
        wr64::achievements_ui::register_tab();

        // Loads <id>.json for each tab from the path main.cpp registered, or
        // writes defaults. Must come after every create_*_tab call: init_modal
        // throws if finalize has not run.
        // Re-fetch after all tabs have been added: creating tabs may relocate
        // the Config objects in their owning vector.
        auto& loadedEnhancements = recompui::config::get_config(EnhancementsTabId);
        if (!loadReflectionProfile(loadedEnhancements))
            throw std::runtime_error("Could not preserve the reflection profile migration.");
        if (!load_general_gameplay_settings(recompui::config::get_general_config(),
                loadedEnhancements.get_json_config()))
            throw std::runtime_error("Could not preserve the gameplay settings migration.");
        recompui::config::finalize();

        // Always open the frontend fullscreen, including existing windowed
        // profiles. Apply this once in memory after loading the profile so
        // the renderer, settings UI and F11 agree, without rewriting the
        // saved settings just because the application was started.
        if (std::get<uint32_t>(recompui::config::get_graphics_config().get_option_value(
                recompui::config::graphics::options::wm_option)) ==
                static_cast<uint32_t>(ultramodern::renderer::WindowMode::Windowed)) {
            recompui::config::graphics::toggle_fullscreen();
        }

        recompui::register_ui_frame_callback(process_pending_ui);
        configured = true;
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[frontend] ready: USA manual frontend\n"));
    }
    catch (const std::exception& error) {
        std::fprintf(stderr, "[frontend] configure failed: %s\n", error.what());
        std::fprintf(stderr, "[frontend] the game will run without the settings UI\n");
    }
}

bool ready() {
    return configured;
}

void reload_edition_settings() {
    // Single-process USA frontend: settings already belong to this core.
}

void request_fullscreen(bool fullscreen) { pending_fullscreen.store(fullscreen ? 1 : 0); }
void report_display_refresh_rate(unsigned int refresh_rate) { pending_refresh_rate.store(refresh_rate); }
void report_multisampling_support(unsigned int sample_counts, bool sample_positions) {
    pending_multisampling.store(uint64_t(sample_counts) | (uint64_t(sample_positions) << 32) | (uint64_t(1) << 33));
}
void report_graphics_api(ultramodern::renderer::GraphicsApi active_api,
    ultramodern::renderer::GraphicsApi startup_selection, bool ray_tracing_supported) {
    active_graphics_api.store((static_cast<unsigned int>(active_api) + 1u) |
        (static_cast<unsigned int>(startup_selection) << 8) |
        (static_cast<unsigned int>(ray_tracing_supported) << 16));
}
void report_graphics_reconfiguration(bool succeeded,
    ultramodern::renderer::GraphicsApi restored_selection) {
    pending_graphics_reconfiguration.store((succeeded ? 2u : 1u) |
        (static_cast<unsigned int>(restored_selection) << 8));
}

void toggle_fullscreen() {
    if (!configured || recompui::is_input_suspended()) return;
    pending_fullscreen_toggles.fetch_add(1);
}

void pump() {
    if (!configured) {
        // The UI never came up, so recompinput's event handler would reach into
        // a recompui that does not exist. Drain SDL here instead, or the window
        // stops responding and the close button does nothing.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                ultramodern::quit();
            }
        }
        return;
    }

    if (window && !wr64::editions::child_running()) {
        const int mode = pending_fullscreen.exchange(-1);
        if (mode >= 0) {
            const bool current = (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
            if (current != (mode != 0) && SDL_SetWindowFullscreen(window,
                mode ? Uint32(SDL_WINDOW_FULLSCREEN_DESKTOP) : 0u) != 0)
                std::fprintf(stderr, "[frontend] could not change window mode: %s\n", SDL_GetError());
        }
    }

    // X, and Alt+F4, just quit.
    //
    // recompinput turns SDL_QUIT into a confirmation prompt once the game has
    // started (input_events.cpp:107-114). Taking the event before it gets
    // there is what makes the close button mean close. SDL_PeepEvents removes
    // only SDL_QUIT and leaves the rest of the queue alone.
    //
    // SDL_PumpEvents FIRST, and it is not optional. SDL_PeepEvents does not
    // pump - SDL_PollEvent is the one that does. Without this the peep reads
    // an empty queue every frame, then handle_events() below calls
    // SDL_PollEvent, which pumps, turns the pending WM_CLOSE into SDL_QUIT and
    // delivers it to recompinput in the same breath. The prompt appears and
    // nothing here ever sees the event.
    //
    // Called from the window's own update loop, which is the thread that
    // created the window - the only thread SDL_PumpEvents may be called from.
    SDL_PumpEvents();
    SDL_Event quit_event;
    if (SDL_PeepEvents(&quit_event, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT) > 0) {
        ultramodern::quit();
        return;
    }

    // Everything else: SDL_PollEvent, the UI's events, controller hotplug,
    // SDL_CONTROLLERDEVICEADDED into recompinput's controller list, player
    // assignment presses, and recompui::process_game_started() - which the
    // draw hook needs or it keeps re-opening the launcher over the running
    // game (ui_state.cpp:659).
    recompinput::handle_events();
    // Direct core launches can start before UI creation. Close the pre-game
    // launcher once the core is ready, without dismissing later settings menus.
    static bool core_ui_started = false;
    if (!wr64::editions::is_launcher() && !core_ui_started && ultramodern::is_game_started()) {
        recompui::hide_all_contexts();
        core_ui_started = true;
    }
}

void toggle_settings() {
    if (!configured || recompui::is_input_suspended()) return;
    pending_settings_toggles.fetch_add(1);
}

namespace {
void toggle_settings_on_ui_thread() {
    if (!configured || recompui::is_input_suspended()) {
        return;
    }
    try {
        // Ask the modal itself rather than the context: is_open_now() is the
        // flag the modal maintains, so it cannot disagree with reality.
        if (recompui::config::get_config_modal()->is_open_now()) {
            // close() returns false when the modal DECLINED to close - a tab
            // with unapplied changes raises its own confirmation prompt
            // instead. Nothing to do about that here; the prompt is the
            // correct behaviour and it is already on screen.
            recompui::config::close();
        }
        else {
            if (!wr64::editions::is_launcher()) {
                // Native L also toggles visibility. Show its current value
                // when reopening settings, rather than a stale checkbox.
                auto& general = recompui::config::get_general_config();
                const bool visible = wr64::ghost::status().visible;
                if (std::get<bool>(general.get_option_value("show_ghost")) != visible)
                    general.set_option_value("show_ghost", visible);
            }
            recompui::config::open();
        }
    }
    catch (const std::exception& error) {
        // Every one of get_config_modal/open/close throws if the modal was
        // never built, which happens when RT64's init hook did not run. A key
        // press must not take the process down.
        std::fprintf(stderr, "[frontend] could not toggle settings: %s\n", error.what());
    }
}
} // namespace

} // namespace wr64::frontend

#else // WR64_ENABLE_FRONTEND

namespace wr64::frontend {
void register_game(const recomp::GameEntry&) {}
void configure() {}
void handle_event(const SDL_Event&) {}
void update() {}
bool ready() { return false; }
void toggle_settings() {}
void reload_edition_settings() {}
void request_fullscreen(bool) {}
void toggle_fullscreen() {}
void report_display_refresh_rate(unsigned int) {}
void report_multisampling_support(unsigned int, bool) {}
void report_graphics_api(ultramodern::renderer::GraphicsApi, ultramodern::renderer::GraphicsApi, bool) {}
void report_graphics_reconfiguration(bool, ultramodern::renderer::GraphicsApi) {}
} // namespace wr64::frontend

#endif
