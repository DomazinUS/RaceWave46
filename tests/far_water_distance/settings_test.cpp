#include "wr64_seabed_distance.hpp"
#include "common/rt64_wr64_far_water_distance.h"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

void registered_water_distance_schema(recomp::config::Config&);
namespace {
std::filesystem::path profile;
unsigned checks = 0;
void require(bool condition, const char* message) { ++checks; if (!condition) throw std::runtime_error(message); }
void run() {
    using recomp::config::Config;
    const auto path = profile / "enhancements.json";
    const nlohmann::json original = {{"water_reflections", "Rasterized"}, {"buoy_draw_distance", "2x"},
        {"sunny_two_player_scenery", "Enhanced"}, {"wave_roundness", 50}, {"camera_fov_extra_degrees", 10.0}};
    { std::ofstream file(path); file << original; }
    RT64::setWr64FarWaterDistanceMode(2); wr64::seabed_distance::set_mode(2);
    Config config("Enhancements", "enhancements", false); registered_water_distance_schema(config);
    require(config.load_config(), "Existing profile loads");
    require(RT64::getWr64FarWaterDistanceMode() == 5 && wr64::seabed_distance::mode() == 5, "Missing options default to the saved 5x preferences");
    constexpr std::array<const char*, 6> labels{"Original", "1.5x", "2x", "3x", "4x", "5x"};
    require(config.get_config_schema().options.size() == 2, "Only requested controls were extracted");
    for (uint32_t option = 0; option < 2; ++option) {
        const auto& schema = std::get<recomp::config::ConfigOptionEnum>(config.get_config_schema().options.at(option).variant);
        require(schema.default_value == 5 && schema.options.size() == labels.size(), "Control default or choices changed");
        for (uint32_t i = 0; i < labels.size(); ++i)
            require(schema.options[i].key == labels[i] && schema.options[i].value == i, "Stable mode labels changed");
    }
    for (uint32_t water : {1U, 2U, 3U, 4U, 5U, 0U}) for (uint32_t bed : {1U, 2U, 3U, 4U, 5U, 0U}) {
        config.update_option_value("far_water_distance", water);
        config.update_option_value("seabed_draw_distance", bed);
        require(RT64::getWr64FarWaterDistanceMode() == water && wr64::seabed_distance::mode() == bed, "Callbacks lost independent selections");
        require(config.save_config(), "Configuration save failed");
        nlohmann::json saved; { std::ifstream file(path); file >> saved; }
        require(saved.at("far_water_distance") == labels[water] && saved.at("seabed_draw_distance") == labels[bed], "Distance modes did not persist by stable key");
        for (const auto& item : original.items())
            require(saved.at(item.key()) == item.value(), "Saving changed an unrelated preference or buoy distance");
        RT64::setWr64FarWaterDistanceMode((water + 1) % labels.size()); wr64::seabed_distance::set_mode((bed + 1) % labels.size());
        Config reopened("Enhancements", "enhancements", false); registered_water_distance_schema(reopened);
        require(reopened.load_config() && RT64::getWr64FarWaterDistanceMode() == water && wr64::seabed_distance::mode() == bed, "Reloaded modes were not restored independently");
    }
}
}
namespace recomp {
std::filesystem::path get_config_path() { return profile; }
const Version& get_project_version() { static const Version version; return version; }
}
int main() {
    try {
        profile = std::filesystem::temp_directory_path() / ("wr64-water-distance-settings-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(profile); run();
        std::cout << "PASS " << checks << " production frontend persistence checks\n"; return 0;
    } catch (const std::exception& error) { std::cerr << "FAIL: " << error.what() << '\n'; return 1; }
}
