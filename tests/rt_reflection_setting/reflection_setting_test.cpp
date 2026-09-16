#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include "common/rt64_wr64_rt_diagnostics.h"
#include "common/rt64_wr64_rt_settings.h"
#include "wr64_enhancement_controls.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

void registered_reflection_schema(recomp::config::Config& config);
void applyWaterReflections(uint32_t mode);
void applySkyReflections(bool enabled);
void applySkyReflectionMethod(uint32_t method);
void applyRayTracedShadows(bool enabled);
void applyShadowMethod(uint32_t method);
void applyReflectionDistance(double percent);
void applyShadowSamples(double samples);
void applyRasterSkyStrength(double percent);
bool migrateReflectionProfile(nlohmann::json& profile);
bool loadReflectionProfile(recomp::config::Config& config);
void initializeRTReflectionDiagnostic();
void updateSkyReflectionControls(recomp::config::Config& config);
extern wr64::frontend::EnhancementAvailability enhancement_controls_available;

namespace {
namespace fs = std::filesystem;
using Config = recomp::config::Config;
using Json = nlohmann::json;
using Availability = wr64::frontend::EnhancementAvailability;
fs::path profileDirectory;
unsigned assertions = 0;
void require(bool condition, const char* message) {
    ++assertions;
    if (!condition) throw std::runtime_error(message);
}
void selection(bool water, bool sky, uint32_t method, bool shadows = true,
    uint32_t distance = 100, uint32_t samples = 16, uint32_t strength = 100, bool rasterShadows = false,
    bool rasterReflections = false, uint32_t rasterShadowDistance = 0u) {
    const auto actual = RT64::getWr64RTSettings();
    require(actual.reflections == water && actual.skyReflections == sky &&
        actual.rasterSky == (method == 0u) && actual.shadows == shadows &&
        actual.reflectionDistancePercent == distance && actual.shadowSamples == samples &&
        actual.rasterSkyStrengthPercent == strength && actual.rasterShadows == rasterShadows &&
        actual.rasterReflections == rasterReflections && actual.rasterShadowDistanceMode == rasterShadowDistance,
        "Published snapshot lost an independent reflection or quality selection");
}
bool hidden(const Config& config, const char* id) {
    return config.is_config_option_hidden(config.get_config_schema().options_by_id.at(id));
}
bool disabled(const Config& config, const char* id) {
    return config.is_config_option_disabled(config.get_config_schema().options_by_id.at(id));
}
void controls(const Config& config, bool water, bool sky, uint32_t method, bool shadows,
    Availability available = {true, true}) {
    require(!hidden(config, "water_reflections") && !hidden(config, "rt_sky_reflections"),
        "Independent water/sky controls were hidden");
    require(disabled(config, "rt_sky_reflections") == !available.d3d12,
        "Sky toggle availability does not match renderer support");
    require(hidden(config, "sky_reflection_method") == !sky, "Sky method did not hide with Sky Reflections off");
    const bool strength = available.d3d12 && sky && method == 0u;
    require(hidden(config, "raster_sky_strength") == !strength &&
        disabled(config, "raster_sky_strength") == !strength,
        "Raster strength availability ignored backend, sky toggle or method");
    require(!hidden(config, "shadow_method") && !disabled(config, "shadow_method"),
        "Independent Shadows control is unavailable");
    const bool rasterShadows = available.d3d12 &&
        std::get<uint32_t>(config.get_option_value("shadow_method")) == 1u;
    require(hidden(config, "raster_shadow_distance") == !rasterShadows &&
        disabled(config, "raster_shadow_distance") == !rasterShadows,
        "Raster shadow distance requires supported Rasterized shadows");
    const bool showDistance = available.ray_tracing && water;
    const bool showSamples = available.ray_tracing && water && shadows;
    require(disabled(config, "rt_reflection_distance") == !showDistance &&
        disabled(config, "rt_shadow_samples") == !showSamples &&
        hidden(config, "rt_reflection_distance") == !showDistance &&
        hidden(config, "rt_shadow_samples") == !showSamples,
        "RT quality rows did not hide and disable according to their actual dependencies");
}
Json read_json(const fs::path& path) {
    Json value;
    std::ifstream file(path);
    file >> value;
    return value;
}
Json read_profile(const fs::path& directory) { return read_json(directory / "enhancements.json"); }
void write_profile(const fs::path& directory, const Json& value) {
    fs::create_directories(directory);
    std::ofstream file(directory / "enhancements.json");
    file << value.dump();
}
void set_environment(const char* name, const char* value) {
#ifdef _WIN32
    _putenv_s(name, value ? value : "");
#else
    if (value) setenv(name, value, 1);
    else unsetenv(name);
#endif
}
void ownership_contract() {
    selection(false, false, 0);
    require(RT64::wr64RTDevelopmentEffectsAllowed(), "Initial development gate changed");
    constexpr RT64::Wr64RTSettings aggregate{false, true};
    require(!aggregate.skyReflections && aggregate.rasterSky && aggregate.rasterSkyStrengthPercent == 100 &&
        !aggregate.rasterShadows && !aggregate.rasterReflections && aggregate.rasterShadowDistanceMode == 0u,
        "Snapshot aggregate defaults enable an unintended reflection");
    for (const char* name : {"WR64_RT_REFLECTIONS", "WR64_RT_SKY_EXPERIMENT", "WR64_RT_SHADOW_EXPERIMENT",
            "WR64_RT_AO_EXPERIMENT", "WR64_OBJECT_MOTION_BLUR_EXPERIMENT"})
        set_environment(name, "1");
    selection(false, false, 0);
    applySkyReflections(true);
    applySkyReflectionMethod(0);
    applyWaterReflections(1);
    applyRayTracedShadows(false);
    selection(true, true, 0, false);
    require(!RT64::wr64RTDevelopmentEffectsAllowed(), "Frontend ownership left parked effects enabled");
    require(std::string(std::getenv("WR64_RT_REFLECTIONS")) == "1", "Settings mutated the legacy environment");
    for (uint32_t method : {0u, 1u}) {
        applySkyReflectionMethod(method);
        for (uint32_t water : {0u, 1u, 2u, 3u, 99u}) {
            applyWaterReflections(water);
            selection(water == 1u, true, method, false, 100, 16, 100, false, water == 3u);
        }
    }
    RT64::setWr64SkyReflectionMethod(99);
    selection(false, true, 0, false);
    for (uint32_t method : {0u, 1u, 2u, 99u}) {
        applyShadowMethod(method);
        selection(false, true, 0, method >= 2u, 100, 16, 100, method == 1u);
    }
    applyShadowMethod(1);
    applyRayTracedShadows(true);
    selection(false, true, 0);
    applyShadowMethod(1);
    applyRayTracedShadows(false);
    selection(false, true, 0, false);

    std::atomic_bool start{false};
    auto run = [&](auto callback) {
        return std::thread([&, callback] {
            while (!start.load(std::memory_order_acquire)) std::this_thread::yield();
            for (unsigned i = 0; i < 10000; ++i) callback(i);
        });
    };
    auto water = run([](unsigned i) { RT64::setWr64WaterReflections((i & 1u) ? 3u : 1u); });
    auto sky = run([](unsigned i) { RT64::setWr64SkyReflections((i & 1u) != 0); });
    auto method = run([](unsigned i) { RT64::setWr64SkyReflectionMethod(i & 1u); });
    auto shadows = run([](unsigned i) { RT64::setWr64ShadowMethod((i & 1u) ? 1u : 2u); });
    auto distance = run([](unsigned i) { RT64::setWr64ReflectionDistance((i & 1u) ? 55 : 100); });
    auto samples = run([](unsigned i) { RT64::setWr64ShadowSamples((i & 1u) ? 8 : 16); });
    auto strength = run([](unsigned i) { RT64::setWr64RasterSkyStrength((i & 1u) ? 175 : 100); });
    auto rasterDistance = run([](unsigned i) { RT64::setWr64RasterShadowDistance(i % 4u); });
    std::atomic_bool invalidShadowSnapshot{false};
    std::atomic_bool invalidWaterSnapshot{false};
    auto reader = run([&](unsigned) {
        const auto snapshot = RT64::getWr64RTSettings();
        if (snapshot.shadows && snapshot.rasterShadows) invalidShadowSnapshot.store(true);
        if (snapshot.reflections && snapshot.rasterReflections) invalidWaterSnapshot.store(true);
    });
    start.store(true, std::memory_order_release);
    water.join(); sky.join(); method.join(); shadows.join(); distance.join(); samples.join(); strength.join(); rasterDistance.join(); reader.join();
    require(!invalidShadowSnapshot.load(), "Concurrent shadow selection published both methods");
    require(!invalidWaterSnapshot.load(), "Concurrent water selection published both methods");
    selection(false, true, 1, false, 55, 8, 175, true, true, 3u);
    for (const char* name : {"WR64_RT_REFLECTIONS", "WR64_RT_SKY_EXPERIMENT", "WR64_RT_SHADOW_EXPERIMENT",
            "WR64_RT_AO_EXPERIMENT", "WR64_OBJECT_MOTION_BLUR_EXPERIMENT"}) {
        set_environment(name, nullptr);
        require(std::getenv(name) == nullptr, "Could not clear inherited feature flags");
    }
    selection(false, true, 1, false, 55, 8, 175, true, true, 3u);
    RT64::setWr64RasterShadowDistance(0u);
}
void schema_and_combinations() {
    Config config("Enhancements", "enhancements", false);
    registered_reflection_schema(config);
    const auto& water = std::get<recomp::config::ConfigOptionEnum>(config.get_option("water_reflections").variant);
    const auto& method = std::get<recomp::config::ConfigOptionEnum>(config.get_option("sky_reflection_method").variant);
    const auto& shadow = std::get<recomp::config::ConfigOptionEnum>(config.get_option("shadow_method").variant);
    const auto& shadowDistance = std::get<recomp::config::ConfigOptionEnum>(config.get_option("raster_shadow_distance").variant);
    const char* distanceKeys[] = {"Original", "1.5x", "2x", "3x"};
    require(shadowDistance.options.size() == 4 && shadowDistance.default_value == 3 &&
        config.get_option("raster_shadow_distance").name == "Shadow Draw Distance",
        "Raster shadow distance schema/default changed");
    for (uint32_t i = 0; i < 4; ++i)
        require(shadowDistance.options[i].value == i && shadowDistance.options[i].key == distanceKeys[i] &&
            shadowDistance.options[i].name == distanceKeys[i], "Raster shadow distance enum key or display order changed");
    require(shadow.options.size() == 3 && shadow.default_value == 0 &&
        shadow.options[0].value == 0 && shadow.options[0].key == "Original" &&
        shadow.options[1].value == 1 && shadow.options[1].key == "Rasterized" &&
        shadow.options[2].value == 2 && shadow.options[2].key == "RayTraced" &&
        shadow.options[2].name == "Ray Traced" && config.get_option("shadow_method").name == "Shadows",
        "Shadows must expose Original/Rasterized/Ray Traced and default to Original");
    require(!config.get_config_schema().options_by_id.contains("ray_traced_shadows"),
        "Retired shadow bool remains exposed in the UI");
    require(water.options.size() == 3 && water.default_value == 0 &&
        water.options[0].value == 0 && water.options[0].key == "Original" && water.options[0].name == "Original" &&
        water.options[1].value == 3 && water.options[1].key == "Rasterized" && water.options[1].name == "Rasterized" &&
        water.options[2].value == 1 && water.options[2].key == "RayTraced" && water.options[2].name == "Ray Traced",
        "Water Reflections must display Original/Rasterized/Ray Traced while preserving values 0/3/1 and retiring legacy2");
    require(method.options.size() == 2 && method.default_value == 1 &&
        method.options[0].value == 0 && method.options[0].key == "Rasterized" &&
        method.options[1].value == 1 && method.options[1].key == "RayTraced" && method.options[1].name == "Ray Traced",
        "Sky method must retain the saved Ray Traced choice");
    require(!std::get<recomp::config::ConfigOptionBool>(config.get_option("rt_sky_reflections").variant).default_value,
        "Fresh profiles must leave Sky Reflections off");
    require(config.get_option("rt_sky_reflections").name == "Sky Reflections" &&
        config.get_option("sky_reflection_method").name == "Sky Reflection Method",
        "Independent sky control labels changed");
    // Scope is verified by the native scope fixture; concise help text can be
    // edited without changing the settings, migration or visibility contract.
    require(!config.get_option("rt_sky_reflections").description.empty() &&
        !config.get_option("sky_reflection_method").description.empty(),
        "Sky controls are missing their help text");
    const auto& strength = std::get<recomp::config::ConfigOptionNumber>(config.get_option("raster_sky_strength").variant);
    require(strength.min == 100 && strength.max == 200 && strength.step == 5 && strength.default_value == 100 &&
        strength.precision == 0 && strength.percent, "Raster strength range changed");
    require(config.get_option("raster_sky_strength").name == "Rasterized Reflection Strength" &&
        config.get_option("raster_sky_strength").description == "Makes rasterized sky reflections more visible on the water.",
        "Raster strength label or description changed");
    const auto& distance = std::get<recomp::config::ConfigOptionNumber>(config.get_option("rt_reflection_distance").variant);
    const auto& samples = std::get<recomp::config::ConfigOptionNumber>(config.get_option("rt_shadow_samples").variant);
    require(distance.min == 25 && distance.max == 100 && distance.step == 5 && distance.default_value == 100 &&
        distance.percent && distance.precision == 0, "Reflection distance range changed");
    require(samples.min == 4 && samples.max == 16 && samples.step == 4 && samples.default_value == 16 &&
        !samples.percent && samples.precision == 0, "Shadow quality range changed");

    const auto directory = profileDirectory / "modern";
    config.set_config_directory(directory);
    require(loadReflectionProfile(config), "Fresh profile failed to load");
    selection(false, false, 1, false, 100, 16, 100, false, false, 3u);
    controls(config, false, false, 1, false);
    const auto fresh = read_profile(directory);
    require(fresh.at("water_reflections") == "Original" && fresh.at("rt_sky_reflections") == false &&
        fresh.at("sky_reflection_method") == "RayTraced" && fresh.at("shadow_method") == "Original" &&
        fresh.at("raster_shadow_distance") == "3x",
        "Fresh profile did not use the saved Original settings and 3x shadow distance");
    config.update_option_value("sky_reflection_method", 0u);
    config.update_option_value("rt_sky_reflections", false);
    config.clear_config_option_updates();
    config.update_option_value("rt_sky_reflections", true);
    bool methodHiddenUpdate = false, strengthHiddenUpdate = false;
    for (const auto& update : config.get_config_option_updates()) {
        if (std::find(update.updates.begin(), update.updates.end(), recomp::config::ConfigOptionUpdateType::Hidden) == update.updates.end()) continue;
        const auto& id = config.get_option(update.option_index).id;
        methodHiddenUpdate |= id == "sky_reflection_method";
        strengthHiddenUpdate |= id == "raster_sky_strength";
    }
    require(methodHiddenUpdate && strengthHiddenUpdate, "Sky toggle did not notify the real UI of hidden-row changes");
    config.update_option_value("rt_reflection_distance", 55.0);
    config.update_option_value("rt_shadow_samples", 8.0);
    config.update_option_value("raster_sky_strength", 200.0);
    // All water/sky combinations and all three independent shadow methods
    // must survive a save and actual reload.
    for (uint32_t waterSelected : {0u, 1u, 3u}) for (uint32_t methodSelected : {0u, 1u})
        for (bool skySelected : {false, true}) for (uint32_t shadows : {0u, 1u, 2u}) {
        config.update_option_value("water_reflections", waterSelected);
        config.update_option_value("sky_reflection_method", methodSelected);
        config.update_option_value("rt_sky_reflections", skySelected);
        config.update_option_value("shadow_method", shadows);
        selection(waterSelected == 1u, skySelected, methodSelected, shadows == 2u, 55, 8, 200, shadows == 1u, waterSelected == 3u, 3u);
        controls(config, waterSelected == 1u, skySelected, methodSelected, shadows == 2u);
        require(config.save_config(), "Independent choices failed to save");
        const auto saved = read_profile(directory);
        require(saved.at("water_reflections") == (waterSelected == 3u ? "Rasterized" : waterSelected == 1u ? "RayTraced" : "Original") &&
            saved.at("sky_reflection_method") == (methodSelected ? "RayTraced" : "Rasterized") &&
            saved.at("rt_sky_reflections") == skySelected &&
            saved.at("shadow_method") == (shadows == 0u ? "Original" : shadows == 1u ? "Rasterized" : "RayTraced"),
            "Saved method/water/shadow keys are unstable");
        applyWaterReflections(waterSelected == 3u ? 1u : 3u);
        applySkyReflections(!skySelected);
        applySkyReflectionMethod(1u - methodSelected);
        applyRasterSkyStrength(100);
        require(loadReflectionProfile(config), "Independent choices failed to reload");
        selection(waterSelected == 1u, skySelected, methodSelected, shadows == 2u, 55, 8, 200, shadows == 1u, waterSelected == 3u, 3u);
        controls(config, waterSelected == 1u, skySelected, methodSelected, shadows == 2u);
        require(read_profile(directory) == saved, "An explicit new sky method was overwritten by migration");
    }
}
void backend_controls_contract() {
    using Api = ultramodern::renderer::GraphicsApi;
    using Update = recomp::config::ConfigOptionUpdateType;
    Config config("Enhancements", "enhancements", false);
    registered_reflection_schema(config);
    const auto directory = profileDirectory / "backend-controls";
    config.set_config_directory(directory);
    require(loadReflectionProfile(config), "Backend test profile failed to load");
    config.update_option_value("water_reflections", 1u);
    config.update_option_value("rt_sky_reflections", true);
    config.update_option_value("sky_reflection_method", 1u);
    config.update_option_value("shadow_method", 2u);
    config.update_option_value("split_screen_layout", 2u);
    config.update_option_value("rt_reflection_distance", 55.0);
    config.update_option_value("rt_shadow_samples", 8.0);
    config.update_option_value("raster_sky_strength", 175.0);
    require(config.save_config(), "Backend test choices failed to save");
    const auto saved = read_profile(directory);

    const auto hasUpdate = [&](const char* id, Update type) {
        const size_t index = config.get_config_schema().options_by_id.at(id);
        for (const auto& update : config.get_config_option_updates()) {
            if (update.option_index == index &&
                std::find(update.updates.begin(), update.updates.end(), type) != update.updates.end())
                return true;
        }
        return false;
    };
    const auto choices = [&](Availability available) {
        const bool waterRt = std::get<uint32_t>(config.get_option_value("water_reflections")) == 1u;
        struct Choice { const char* id; std::vector<bool> disabled; };
        // Explicit display-order expectations catch the nonsequential water
        // values: Rasterized is saved as 3, Ray Traced as 1.
        for (const Choice choice : {
                Choice{"water_reflections", {false, !available.d3d12, !available.ray_tracing}},
                Choice{"sky_reflection_method", {!available.d3d12, !available.ray_tracing}},
                Choice{"shadow_method", {false, !available.d3d12, !available.ray_tracing || !waterRt}},
                Choice{"split_screen_layout", {false, false, !available.d3d12}}}) {
            const size_t index = config.get_config_schema().options_by_id.at(choice.id);
            for (uint32_t displayIndex = 0; displayIndex < choice.disabled.size(); ++displayIndex)
                require(config.get_enum_option_disabled(index, displayIndex) ==
                    choice.disabled[displayIndex],
                    "Backend/hardware availability disabled the wrong choice or left an unsupported choice selectable");
            const auto& details = config.get_enum_option_details(index);
            const bool anyDisabled = std::find(choice.disabled.begin(), choice.disabled.end(), true) != choice.disabled.end();
            require(anyDisabled ? details.size() > 12 : details.empty(),
                "Unsupported choices need a meaningful explanation that clears when supported");
            if (!available.d3d12)
                require(details.find("Direct3D") != std::string::npos,
                    "API restriction did not identify the required graphics API");
            else if (std::string(choice.id) != "split_screen_layout" && !available.ray_tracing)
                require(details.find("ray tracing") != std::string::npos,
                    "Hardware restriction was incorrectly explained as an API restriction");
            else if (std::string(choice.id) == "shadow_method" && !waterRt)
                require(details.find("Water Reflections") != std::string::npos,
                    "RT shadow dependency was not explained");
            require(!disabled(config, choice.id), "Backend availability disabled the whole method row");
        }
    };

    // Pending API choices cannot enable a feature on the currently active
    // backend. D3D12 without ray-tracing hardware still supports raster effects
    // and a second window. Cover all 32 API/hardware permutations.
    for (Api selected : {Api::Auto, Api::D3D12, Api::Vulkan, Api::Metal})
        for (Api active : {Api::Auto, Api::D3D12, Api::Vulkan, Api::Metal})
        for (bool hardwareRt : {false, true}) {
        const bool d3d12 = active == Api::D3D12 && (selected == Api::Auto || selected == Api::D3D12);
        const auto available = wr64::frontend::enhancement_availability(selected, active, hardwareRt);
        require(available == Availability{d3d12, d3d12 && hardwareRt},
            "Selected/active API and hardware policy incorrectly enabled an enhancement");
        enhancement_controls_available = available;
        updateSkyReflectionControls(config);
        choices(available);
        controls(config, true, true, 1u, true, available);
        selection(true, true, 1u, true, 55, 8, 175, false, false, 3u);
        require(config.save_config() && read_profile(directory) == saved,
            "Changing graphics API/hardware silently rewrote rendering or separate-window preferences");
        config.clear_config_option_updates();
        updateSkyReflectionControls(config);
        require(config.get_config_option_updates().empty(),
            "Unchanged availability produced repeated UI update queue traffic");
    }

    enhancement_controls_available = {true, true};
    updateSkyReflectionControls(config);
    config.clear_config_option_updates();
    enhancement_controls_available = {false, false};
    updateSkyReflectionControls(config);
    for (const char* id : {"water_reflections", "sky_reflection_method", "shadow_method", "split_screen_layout"})
        require(hasUpdate(id, Update::EnumDisabled) && hasUpdate(id, Update::EnumDetails),
            "API changes failed to notify the UI of unavailable choices and their explanation");
    require(hasUpdate("rt_sky_reflections", Update::Disabled), "API change did not disable the sky toggle in the UI");
    for (const char* id : {"rt_reflection_distance", "rt_shadow_samples"})
        require(hasUpdate(id, Update::Hidden) && hasUpdate(id, Update::Disabled),
            "API change did not notify the UI of hidden quality rows");
    for (const auto& update : config.get_config_option_updates())
        require(std::find(update.updates.begin(), update.updates.end(), Update::Value) == update.updates.end(),
            "Changing availability rewrote an option value");

    // Config can load unavailable preferences even though the UI disallows
    // choosing them. Every method/layout combination must survive all three
    // supported capability states without being normalized to a fallback.
    for (uint32_t water : {0u, 1u, 3u}) for (bool sky : {false, true})
        for (uint32_t method : {0u, 1u}) for (uint32_t shadows : {0u, 1u, 2u})
        for (uint32_t layout : {0u, 1u, 2u}) {
        config.update_option_value("water_reflections", water);
        config.update_option_value("rt_sky_reflections", sky);
        config.update_option_value("sky_reflection_method", method);
        config.update_option_value("shadow_method", shadows);
        config.update_option_value("split_screen_layout", layout);
        require(config.save_config(), "Inactive rendering/layout choices failed to save");
        const auto inactive = read_profile(directory);
        for (Availability available : {Availability{false, false}, Availability{true, false}, Availability{true, true}}) {
            enhancement_controls_available = available;
            updateSkyReflectionControls(config);
            choices(available);
            controls(config, water == 1u, sky, method, shadows == 2u, available);
            selection(water == 1u, sky, method, shadows == 2u, 55, 8, 175, shadows == 1u, water == 3u, 3u);
            require(config.save_config() && read_profile(directory) == inactive,
                "Changing capabilities changed inactive saved choices");
            config.clear_config_option_updates();
            updateSkyReflectionControls(config);
            require(config.get_config_option_updates().empty(), "Stable combination caused repeated UI traffic");
        }
    }
    enhancement_controls_available = {true, true};
}
void migration_contract() {
    Config config("Enhancements", "enhancements", false);
    registered_reflection_schema(config);
    unsigned id = 0;
    struct LegacyWater { Json value; bool ray, raster; bool rasterObjects = false; };
    const std::vector<LegacyWater> modes{
        {"Original",false,false}, {"RayTraced",true,false}, {"rAyTrAcEd",true,false},
        {"RasterSky",false,true}, {"rAsTeRsKy",false,true}, {2,false,true},
        {nullptr,false,false}, {"unknown",false,false}
    };
    for (const auto& water : modes) for (int sky = -1; sky <= 2; ++sky) {
        const auto directory = profileDirectory / ("legacy-" + std::to_string(id++));
        Json old{{"water_reflections",water.value}, {"ray_traced_shadows",false},
            {"rt_reflection_distance",55}, {"rt_shadow_samples",8}, {"raster_sky_strength",175},
            {"wave_roundness",37}, {"unrelated",{{"nested","keep exactly"}}}};
        if (sky >= 0) old["rt_sky_reflections"] = sky == 2 ? Json("bad") : Json(sky != 0);
        write_profile(directory, old);
        config.set_config_directory(directory);
        require(loadReflectionProfile(config), "Legacy profile migration failed");
        const bool skySelected = (water.ray || water.raster) && sky != 0;
        selection(water.ray, skySelected, water.raster ? 0u : 1u, false, 55, 8, 175, false, water.rasterObjects, 3u);
        controls(config, water.ray, skySelected, water.raster ? 0u : 1u, false);
        const auto migrated = read_profile(directory);
        require(migrated.at("sky_reflection_method") == (water.raster ? "Rasterized" : "RayTraced") &&
            migrated.at("rt_sky_reflections") == skySelected, "Migration changed the prior rendering choice");
        if (water.raster) require(migrated.at("water_reflections") == "Original", "Retired RasterSky water value survived migration");
        for (const auto& [key, value] : old.items()) {
            if (key != "water_reflections" && key != "rt_sky_reflections")
                require(migrated.at(key) == value, "Migration changed an unrelated preference");
        }
        require(read_json(directory / "enhancements.json.bak") == old, "Migration did not preserve the original backup");
        Json again = migrated;
        require(!migrateReflectionProfile(again) && again == migrated, "Migration is not idempotent");
        require(loadReflectionProfile(config) && read_profile(directory) == migrated &&
            read_json(directory / "enhancements.json.bak") == old, "Modern reload rewrote a migrated profile or its backup");
    }
    const auto directory = profileDirectory / "old-unrelated";
    const Json unrelated{{"wave_roundness",37}};
    write_profile(directory, unrelated);
    config.set_config_directory(directory);
    require(loadReflectionProfile(config), "Pre-reflection profile failed to migrate");
    selection(false, false, 1, true, 100, 16, 100, false, false, 3u);
    require(read_profile(directory).at("wave_roundness") == 37, "Pre-reflection profile lost its enhancement");

    for (const Json& method : {Json("Rasterized"), Json("RayTraced"), Json("rAyTrAcEd"),
            Json("unknown"), Json(nullptr), Json(1)}) {
        const Json modern{{"water_reflections","Original"}, {"rt_sky_reflections",true},
            {"sky_reflection_method",method}, {"raster_sky_strength",175}, {"shadow_method","RayTraced"}};
        write_profile(directory, modern);
        require(loadReflectionProfile(config), "Explicit method profile failed to load");
        const bool ray = method != "Rasterized";
        selection(false, true, ray ? 1u : 0u, true, 100, 16, 175, false, false, 3u);
        require(read_profile(directory) == modern, "Explicit method key was silently replaced");
    }
    Json mixedLegacy{{"water_reflections",2}, {"sky_reflection_method","RayTraced"},
        {"rt_sky_reflections",false}, {"raster_sky_strength",175}};
    require(migrateReflectionProfile(mixedLegacy) && mixedLegacy.at("water_reflections") == "Original" &&
        mixedLegacy.at("sky_reflection_method") == "RayTraced" && mixedLegacy.at("rt_sky_reflections") == false &&
        mixedLegacy.at("raster_sky_strength") == 175, "Retired water migration overrode an explicit method");
}
void raster_water_profile_contract() {
    Config config("Enhancements", "enhancements", false);
    registered_reflection_schema(config);
    unsigned id = 0;
    // The new enum token opts into scenery reflections. The retired token
    // and numeric2 still migrate to Original water and never enable this bit.
    struct Water { Json value; uint32_t selected; bool legacy; };
    const std::vector<Water> waters{{"Rasterized",3,false},{"rAsTeRiZeD",3,false},
        {"RasterSky",0,true},{"rAsTeRsKy",0,true},{2,0,true},{3,0,false},{"3",0,false}};
    for(const auto &water:waters)for(uint32_t skyMethod:{0u,1u})for(bool sky:{false,true})
        for(uint32_t shadow:{0u,1u,2u}) {
        const auto directory=profileDirectory/("raster-water-"+std::to_string(id++));
        const Json original{{"water_reflections",water.value},{"rt_sky_reflections",sky},
            {"sky_reflection_method",skyMethod?"RayTraced":"Rasterized"},
            {"shadow_method",shadow==0u?"Original":shadow==1u?"Rasterized":"RayTraced"},
            {"rt_reflection_distance",55},{"rt_shadow_samples",8},{"raster_sky_strength",200},
            {"unrelated",{{"nested","keep exactly"}}}};
        write_profile(directory,original);config.set_config_directory(directory);
        require(loadReflectionProfile(config),"Rasterized water profile failed to load");
        selection(false, sky, skyMethod, shadow==2u, 55, 8, 200, shadow==1u, water.selected==3u, 3u);
        controls(config,false,sky,skyMethod,shadow==2u);
        Json expected=original;
        if(water.legacy)expected["water_reflections"]="Original";
        require(read_profile(directory)==expected,"Raster water migration changed an explicit independent preference");
        if(water.legacy)require(read_json(directory/"enhancements.json.bak")==original,
            "Retired RasterSky migration lost its exact profile backup");
        else require(!fs::exists(directory/"enhancements.json.bak"),"An explicit modern water profile was unnecessarily migrated");
        require(loadReflectionProfile(config)&&read_profile(directory)==expected,
            "Raster water reload is not idempotent");
        require(config.save_config(),"Rasterized water failed to save its canonical enum token");
        require(read_profile(directory).at("water_reflections")== (water.selected==3u?"Rasterized":"Original"),
            "Rasterized water saved an unstable or retired enum value");
        applyWaterReflections(1);require(loadReflectionProfile(config),"Saved rasterized water failed to reload");
        selection(false, sky, skyMethod, shadow==2u, 55, 8, 200, shadow==1u, water.selected==3u, 3u);
    }
    // A new Rasterized-water profile missing sky method uses the current cheap
    // method default, keeps an explicit sky bool, and never enables sky itself.
    for(const char *water:{"Rasterized","rAsTeRiZeD"})for(int sky=-1;sky<=2;++sky) {
        const auto directory=profileDirectory/("raster-water-missing-method-"+std::to_string(id++));
        Json original{{"water_reflections",water},{"shadow_method","Rasterized"},
            {"rt_reflection_distance",55},{"rt_shadow_samples",8},{"raster_sky_strength",200}};
        if(sky>=0)original["rt_sky_reflections"]=sky==2?Json("true"):Json(sky==1);
        write_profile(directory,original);config.set_config_directory(directory);
        require(loadReflectionProfile(config),"New raster water with missing sky method failed to recover");
        selection(false, sky==1, 0, false, 55, 8, 200, true, true, 3u);
        controls(config,false,sky==1,0,false);
        const auto migrated=read_profile(directory);
        require(migrated.at("water_reflections")==water&&migrated.at("sky_reflection_method")=="Rasterized"&&
            migrated.at("rt_sky_reflections")== (sky==1)&&migrated.at("raster_sky_strength")==200,
            "New raster water migration silently changed sky, water or saved strength");
        require(read_json(directory/"enhancements.json.bak")==original,"Missing-method recovery lost its backup");
        require(loadReflectionProfile(config)&&read_profile(directory)==migrated,
            "Missing-method raster-water migration is not idempotent");
    }
}

void numeric_and_corrupt_contract() {
    Config config("Enhancements", "enhancements", false);
    registered_reflection_schema(config);
    const auto directory = profileDirectory / "numbers";
    config.set_config_directory(directory);
    require(loadReflectionProfile(config), "Numeric profile failed to load");
    config.update_option_value("water_reflections", 1u);
    config.update_option_value("rt_sky_reflections", true);
    config.update_option_value("shadow_method", 0u);
    config.update_option_value("sky_reflection_method", 0u);
    struct Case { double input; uint32_t distance, samples, strength; };
    const Case cases[] = {
        {-1e300,25,4,100}, {0,25,4,100}, {6,25,8,100}, {10,25,12,100}, {14,25,16,100},
        {27.4,25,16,100}, {27.5,30,16,100}, {42,40,16,100}, {97.4,95,16,100},
        {97.5,100,16,100}, {100,100,16,100}, {102.49,100,16,100}, {102.5,100,16,105},
        {127.5,100,16,130}, {175,100,16,175}, {197.49,100,16,195}, {197.5,100,16,200},
        {200,100,16,200}, {1e300,100,16,200},
        {std::numeric_limits<double>::infinity(),100,16,100},
        {-std::numeric_limits<double>::infinity(),100,16,100},
        {std::numeric_limits<double>::quiet_NaN(),100,16,100}
    };
    for (const auto& c : cases) {
        config.update_option_value("rt_reflection_distance", c.input);
        config.update_option_value("rt_shadow_samples", c.input);
        config.update_option_value("raster_sky_strength", c.input);
        selection(true, true, 0, false, c.distance, c.samples, c.strength, false, false, 3u);
        require(std::get<double>(config.get_option_value("rt_reflection_distance")) == c.distance &&
            std::get<double>(config.get_option_value("rt_shadow_samples")) == c.samples &&
            std::get<double>(config.get_option_value("raster_sky_strength")) == c.strength,
            "Sanitized renderer values disagree with the displayed numeric values");
        controls(config, true, true, 0, false);
        require(config.save_config(), "Sanitized numeric profile failed to save");
        const auto saved = read_profile(directory);
        require(saved.at("rt_reflection_distance") == c.distance && saved.at("rt_shadow_samples") == c.samples &&
            saved.at("raster_sky_strength") == c.strength, "Sanitized numbers did not persist");
    }
    for (const Json& invalid : {Json("bad"), Json(nullptr), Json(true), Json::array(), Json::object()}) {
        write_profile(directory, {{"water_reflections","RayTraced"}, {"rt_sky_reflections",true},
            {"sky_reflection_method","Rasterized"}, {"ray_traced_shadows",false},
            {"rt_reflection_distance",invalid}, {"rt_shadow_samples",invalid}, {"raster_sky_strength",invalid}});
        require(loadReflectionProfile(config), "Invalid numeric values prevented profile recovery");
        selection(true, true, 0, false, 100, 16, 100, false, false, 3u);
        controls(config, true, true, 0, false);
    }
    for (const Json& invalid : {Json("true"), Json(nullptr), Json(1), Json::array(), Json::object()}) {
        write_profile(directory, {{"water_reflections","RayTraced"}, {"rt_sky_reflections",invalid},
            {"sky_reflection_method","RayTraced"}, {"ray_traced_shadows",invalid}});
        require(loadReflectionProfile(config), "Invalid bool values prevented profile recovery");
        selection(true, false, 1, true, 100, 16, 100, false, false, 3u);
        controls(config, true, false, 1, true);
    }
    for (const Json& invalid : {Json("Rasterized Sky"), Json(nullptr), Json(1), Json(3), Json(true), Json::array(), Json::object()}) {
        write_profile(directory, {{"water_reflections",invalid}, {"rt_sky_reflections",true},
            {"sky_reflection_method","Rasterized"}});
        require(loadReflectionProfile(config), "Invalid water enum prevented profile recovery");
        selection(false, true, 0, true, 100, 16, 100, false, false, 3u);
        controls(config, false, true, 0, true);
    }
    write_profile(directory, Json::array({1,2,3}));
    require(!loadReflectionProfile(config) && read_profile(directory) == Json::array({1,2,3}),
        "Non-object profile was silently reset");
}

void shadow_migration_contract() {
    Config config("Enhancements", "enhancements", false);
    registered_reflection_schema(config);
    unsigned id = 0;
    const std::vector<Json> legacyValues{
        false, true, "true", nullptr, 1, Json::array(), Json::object()
    };
    // A missing/invalid old boolean recovers its established default (true).
    for (bool water : {false, true}) for (uint32_t skyMethod : {0u, 1u})
        for (int oldIndex = -1; oldIndex < int(legacyValues.size()); ++oldIndex) {
        const auto directory = profileDirectory / ("shadow-legacy-" + std::to_string(id++));
        Json old{{"water_reflections",water ? "RayTraced" : "Original"},
            {"rt_sky_reflections",true}, {"sky_reflection_method",skyMethod ? "RayTraced" : "Rasterized"},
            {"rt_reflection_distance",55}, {"rt_shadow_samples",8}, {"raster_sky_strength",200},
            {"unrelated",{{"nested","preserve"}}}};
        if (oldIndex >= 0) old["ray_traced_shadows"] = legacyValues[oldIndex];
        const bool ray = oldIndex != 0;
        write_profile(directory, old);
        config.set_config_directory(directory);
        require(loadReflectionProfile(config), "Old shadow bool failed to migrate");
        selection(water, true, skyMethod, ray, 55, 8, 200, false, false, 3u);
        controls(config, water, true, skyMethod, ray);
        const auto migrated = read_profile(directory);
        require(migrated.at("shadow_method") == (ray ? "RayTraced" : "Original"),
            "Shadow migration lost the old boolean/default choice");
        for (const auto& [key, value] : old.items())
            require(migrated.at(key) == value, "Shadow migration changed another preference");
        require(read_json(directory / "enhancements.json.bak") == old,
            "Shadow migration did not back up the original profile");
        Json again = migrated;
        require(!migrateReflectionProfile(again) && again == migrated,
            "Shadow migration is not idempotent");
        require(loadReflectionProfile(config) && read_profile(directory) == migrated &&
            read_json(directory / "enhancements.json.bak") == old,
            "Shadow reload rewrote the profile or its backup");
    }
    struct Method { Json value; uint32_t selected; };
    const std::vector<Method> methods{
        {"Original",0}, {"oRiGiNaL",0}, {"Rasterized",1}, {"rAsTeRiZeD",1},
        {"RayTraced",2}, {"rAyTrAcEd",2}, {"unknown",0}, {nullptr,0},
        {0,0}, {1,0}, {2,0}, {true,0}, {Json::array(),0}, {Json::object(),0}
    };
    // An explicit new enum is authoritative over either old bool. Invalid
    // serialized enum types use Config's normal default without rewriting it.
    for (bool water : {false, true}) for (uint32_t skyMethod : {0u, 1u})
        for (bool oldBool : {false, true}) for (const auto& method : methods) {
        const auto directory = profileDirectory / ("shadow-modern-" + std::to_string(id++));
        const Json modern{{"water_reflections",water ? "RayTraced" : "Original"},
            {"rt_sky_reflections",true}, {"sky_reflection_method",skyMethod ? "RayTraced" : "Rasterized"},
            {"shadow_method",method.value}, {"ray_traced_shadows",oldBool},
            {"rt_reflection_distance",55}, {"rt_shadow_samples",8}, {"raster_sky_strength",200}};
        write_profile(directory, modern);
        config.set_config_directory(directory);
        require(loadReflectionProfile(config), "Explicit shadow method prevented profile recovery");
        selection(water, true, skyMethod, method.selected == 2u, 55, 8, 200, method.selected == 1u, false, 3u);
        controls(config, water, true, skyMethod, method.selected == 2u);
        require(read_profile(directory) == modern, "Migration overrode an explicit shadow method");
        require(!fs::exists(directory / "enhancements.json.bak"), "Unchanged modern profile was unnecessarily backed up");
    }
}

void raster_shadow_distance_contract() {
    Config config("Enhancements", "enhancements", false);
    registered_reflection_schema(config);
    const auto directory = profileDirectory / "raster-shadow-distance";
    const Json old{{"water_reflections","Rasterized"},{"rt_sky_reflections",true},
        {"sky_reflection_method","Rasterized"},{"shadow_method","Rasterized"},
        {"rt_reflection_distance",55},{"rt_shadow_samples",8},{"raster_sky_strength",175},
        {"wave_roundness",37},{"unrelated",{{"nested","retain exactly"}}}};
    write_profile(directory, old);
    config.set_config_directory(directory);
    RT64::setWr64RasterShadowDistance(3u);
    require(loadReflectionProfile(config), "Older profile failed to load with new distance option");
    selection(false, true, 0u, false, 55, 8, 175, true, true, 3u);
    require(std::get<uint32_t>(config.get_option_value("raster_shadow_distance")) == 3u &&
        read_profile(directory) == old, "Missing distance did not default to 3x without rewriting old profile");
    const char* keys[] = {"Original", "1.5x", "2x", "3x"};
    for (Availability backend : {Availability{false, false}, Availability{true, false}, Availability{true, true}})
        for (uint32_t shadow : {0u, 1u, 2u})
        for (uint32_t distance = 0; distance < 4; ++distance) {
        enhancement_controls_available = backend;
        config.update_option_value("shadow_method", shadow);
        updateSkyReflectionControls(config);
        config.update_option_value("raster_shadow_distance", distance);
        controls(config, false, true, 0u, shadow == 2u, backend);
        selection(false, true, 0u, shadow == 2u, 55, 8, 175, shadow == 1u, true, distance);
        const auto index = config.get_config_schema().options_by_id.at("raster_shadow_distance");
        for (uint32_t display = 0; display < 4; ++display)
            require(!config.get_enum_option_disabled(index, display),
                "Raster distance choice was disabled individually instead of gating its parent row");
        require(config.save_config(), "Raster shadow distance failed to save");
        const auto saved = read_profile(directory);
        require(saved.at("raster_shadow_distance") == keys[distance], "Raster distance saved an unstable enum token");
        for (const auto& [key, value] : old.items()) if (key != "shadow_method")
            require(saved.at(key) == value, "Raster shadow distance changed unrelated preferences");
        RT64::setWr64RasterShadowDistance((distance + 1u) % 4u);
        require(loadReflectionProfile(config), "Raster shadow distance failed to reload");
        selection(false, true, 0u, shadow == 2u, 55, 8, 175, shadow == 1u, true, distance);
        controls(config, false, true, 0u, shadow == 2u, backend);
        require(read_profile(directory) == saved, "Distance reload rewrote saved preferences");
    }
    enhancement_controls_available = {false, false};
    config.update_option_value("shadow_method", 0u);
    updateSkyReflectionControls(config);
    config.clear_config_option_updates();
    config.update_option_value("shadow_method", 1u);
    require(hidden(config,"raster_shadow_distance") && disabled(config,"raster_shadow_distance"),
        "Selecting a saved Rasterized shadow preference exposed unsupported Vulkan distance controls");
    config.clear_config_option_updates();
    enhancement_controls_available = {true, false};
    updateSkyReflectionControls(config);
    bool hiddenUpdate = false, disabledUpdate = false;
    for (const auto& update : config.get_config_option_updates()) {
        if (config.get_option(update.option_index).id != "raster_shadow_distance") continue;
        hiddenUpdate |= std::find(update.updates.begin(), update.updates.end(),
            recomp::config::ConfigOptionUpdateType::Hidden) != update.updates.end();
        disabledUpdate |= std::find(update.updates.begin(), update.updates.end(),
            recomp::config::ConfigOptionUpdateType::Disabled) != update.updates.end();
    }
    require(hiddenUpdate && disabledUpdate && !hidden(config,"raster_shadow_distance") &&
        !disabled(config,"raster_shadow_distance"), "Switching to D3D12 did not restore raster distance without RT hardware");

    for (const Json& bad : {Json("unknown"),Json(3),Json(nullptr),Json(true),Json::array(),Json::object()}) {
        auto profile = old;
        profile["raster_shadow_distance"] = bad;
        write_profile(directory,profile);
        require(loadReflectionProfile(config), "Invalid distance prevented profile recovery");
        selection(false, true, 0u, false, 55, 8, 175, true, true, 3u);
        require(read_profile(directory) == profile, "Invalid distance load rewrote existing profile");
    }
    // Changing only the new packed field must preserve every other setting bit.
    for (uint32_t selected : {0u,1u,2u,3u,4u,UINT32_MAX}) {
        const auto before = RT64::Wr64RTSettingsDetail::value.load();
        RT64::setWr64RasterShadowDistance(selected);
        const auto after = RT64::Wr64RTSettingsDetail::value.load();
        require((before & ~RT64::Wr64RTSettingsDetail::RasterShadowDistanceMask) ==
            (after & ~RT64::Wr64RTSettingsDetail::RasterShadowDistanceMask),
            "Raster distance setter changed a sibling packed setting");
        require(RT64::getWr64RTSettings().rasterShadowDistanceMode == (selected <= 3u ? selected : 0u),
            "Raster distance setter failed valid range or invalid fallback");
    }
    enhancement_controls_available = {true, true};
}

void diagnostic_contract() {
    require(RT64::wr64RTDiagnosticEnabled(), "Reflection sink was not installed before loading settings");
    RT64::wr64RTDiagnostic("producer", "course=1 players=1 eligible=1");
    {
        std::ifstream file(profileDirectory / "rt-reflections.log");
        std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        require(text.find("session USA water reflection prototype") != std::string::npos,
            "Reflection session was not flushed to its own log");
        require(text.find("setting selected=1 reflections=1 sky=1 source=frontend") != std::string::npos,
            "Actual frontend selection is missing from the reflection log");
        require(text.find("shadow-setting selected=0 source=frontend") != std::string::npos,
            "Actual frontend shadow choice is missing from the reflection log");
        require(text.find("producer course=1 players=1 eligible=1") != std::string::npos,
            "Renderer diagnostic bridge did not reach the frontend log");
    }
    std::vector<std::thread> writers;
    for (unsigned t = 0; t < 8; ++t) {
        writers.emplace_back([] {
            for (unsigned i = 0; i < 100; ++i) RT64::wr64RTDiagnostic("build", "ready=1");
        });
    }
    for (auto& writer : writers) writer.join();
    require(!RT64::wr64RTDiagnosticEnabled(), "Reflection sink did not disable at its session limit");
    std::ifstream file(profileDirectory / "rt-reflections.log");
    unsigned lines = 0;
    std::string line, last;
    while (std::getline(file, line)) { ++lines; last = line; }
    require(lines == 512 && last == "Diagnostic limit reached; rendering continues normally.",
        "Concurrent reflection writers exceeded the 512-line budget or lost the final marker");
}

} // namespace
namespace recomp {
std::filesystem::path get_config_path() { return profileDirectory; }
const Version& get_project_version() { static const Version version; return version; }
}
int main() {
    profileDirectory = fs::current_path() / ("isolated-reflection-profile-" +
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        fs::create_directories(profileDirectory);
        initializeRTReflectionDiagnostic();
        ownership_contract();
        diagnostic_contract();
        schema_and_combinations();
        backend_controls_contract();
        migration_contract();
        raster_water_profile_contract();
        numeric_and_corrupt_contract();
        shadow_migration_contract();
        raster_shadow_distance_contract();
        std::cout << "Passed " << assertions << " production reflection setting/persistence assertions.\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
