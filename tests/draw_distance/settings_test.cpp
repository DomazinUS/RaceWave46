#include "wr64_draw_distance.hpp"
#include "wr64_object_distance.hpp"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

void registered_draw_distance_schema(recomp::config::Config&);
namespace {
std::filesystem::path profile;
unsigned checks = 0;
void require(bool condition, const char* message) {
    ++checks; if (!condition) throw std::runtime_error(message);
}
void run() {
    using recomp::config::Config;
    constexpr auto buoyKey = "buoy_draw_distance";
    constexpr auto objectKey = "object_draw_distance";
    const auto path = profile / "enhancements.json";
    const nlohmann::json original = {{"water_reflections", "Rasterized"},
        {"sunny_two_player_scenery", "Enhanced"}, {"wave_roundness", 50}, {"camera_fov_extra_degrees", 10.0},
        {"far_water_distance", "5x"}, {"seabed_draw_distance", "5x"}, {"raster_shadow_distance", "3x"}};
    { std::ofstream file(path); file << original; }
    wr64::draw_distance::set_mode(2);
    wr64::object_distance::set_mode(3);
    Config config("Enhancements", "enhancements", false);
    registered_draw_distance_schema(config);
    require(config.load_config(), "Existing profile loads");
    require(wr64::draw_distance::mode() == 2 && wr64::object_distance::mode() == 3,
        "Missing options restore the saved 2x buoy and 3x object defaults");
    auto previousProfile = original;
    previousProfile[buoyKey] = "2x";
    { std::ofstream file(path); file << previousProfile; }
    wr64::object_distance::set_mode(2);
    require(config.load_config() && wr64::draw_distance::mode() == 2 && wr64::object_distance::mode() == 3,
        "Adding object distance preserves an existing 2x buoy choice while defaulting only the new option");
    previousProfile[objectKey] = "2x";
    { std::ofstream file(path); file << previousProfile; }
    require(config.load_config() && wr64::draw_distance::mode() == 2 && wr64::object_distance::mode() == 2,
        "Adding 3x preserves the existing serialized 2x object choice");
    constexpr std::array<const char*, 3> buoyKeys{"Original", "1.5x", "2x"};
    constexpr std::array<const char*, 4> objectKeys{"Original", "1.5x", "2x", "3x"};
    require(config.get_config_schema().options.size() == 2, "Both actual distance selectors are extracted");
    for (const auto& option : config.get_config_schema().options) {
        const auto& schema = std::get<recomp::config::ConfigOptionEnum>(option.variant);
        require(option.id == buoyKey || option.id == objectKey, "Only known distance selectors were extracted");
        const auto count = option.id == buoyKey ? buoyKeys.size() : objectKeys.size();
        require(schema.default_value == (option.id == buoyKey ? 2u : 3u) && schema.options.size() == count,
            "Object selector has four options while buoy selector retains its original three");
        for (uint32_t i = 0; i < count; ++i)
            require(schema.options[i].key == (option.id == buoyKey ? buoyKeys[i] : objectKeys[i]) && schema.options[i].value == i,
                "Production labels map to stable native mode values");
    }
    wr64::draw_distance::set_mode(3);
    require(wr64::draw_distance::mode() == 0, "New object mode does not add an unsupported 3x buoy mode");
    for (uint32_t buoy : {1U, 2U, 0U}) for (uint32_t object : {1U, 2U, 3U, 0U}) {
        config.update_option_value(buoyKey, buoy);
        config.update_option_value(objectKey, object);
        require(wr64::draw_distance::mode() == buoy && wr64::object_distance::mode() == object,
            "Production callbacks apply independent multipliers immediately");
        require(config.save_config(), "Selected multiplier saves");
        nlohmann::json saved; { std::ifstream file(path); file >> saved; }
        require(saved.at(buoyKey) == buoyKeys[buoy] && saved.at(objectKey) == objectKeys[object],
            "Enums persist as their stable setting keys");
        for (const auto& item : original.items())
            require(saved.at(item.key()) == item.value(), "Saving preserves every unrelated preference");
        wr64::draw_distance::set_mode((buoy + 1) % 3);
        wr64::object_distance::set_mode((object + 1) % 4);
        Config reopened("Enhancements", "enhancements", false);
        registered_draw_distance_schema(reopened);
        require(reopened.load_config() && wr64::draw_distance::mode() == buoy && wr64::object_distance::mode() == object,
            "Reopened profile applies both persisted multipliers to native helpers");
    }
}
}
namespace recomp {
std::filesystem::path get_config_path() { return profile; }
const Version& get_project_version() { static const Version version; return version; }
}
int main() {
    try {
        profile = std::filesystem::temp_directory_path() / ("wr64-draw-distance-settings-" +
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(profile);
        run();
        std::cout << "PASS " << checks << " production frontend persistence checks\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n'; return 1;
    }
}
