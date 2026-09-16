#include "common/rt64_wr64_cloud_coverage_settings.h"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

void register_cloud_schema(recomp::config::Config&);
namespace {
std::filesystem::path profile;
unsigned checks = 0;
void require(bool ok, const char* message) { ++checks; if (!ok) throw std::runtime_error(message); }
void run() {
    using recomp::config::Config;
    const auto path = profile / "enhancements.json";
    const nlohmann::json baseline = {{"wave_roundness", 50}, {"far_water_distance", "5x"},
        {"seabed_draw_distance", "5x"}, {"buoy_draw_distance", "2x"}, {"object_draw_distance", "2x"},
        {"water_reflections", "Rasterized"}, {"sunny_two_player_scenery", "Enhanced"}};
    { std::ofstream file(path); file << baseline; }
    RT64::setWr64CloudCoverageMode(1);
    Config config("Enhancements", "enhancements", false); register_cloud_schema(config);
    require(config.load_config(), "Existing profile failed to load");
    require(RT64::getWr64CloudCoverageMode() == 1, "Absent preference must load Extended");
    const auto& options = config.get_config_schema().options;
    require(options.size() == 1, "Unexpected extracted schema");
    const auto& choice = std::get<recomp::config::ConfigOptionEnum>(options[0].variant);
    require(choice.default_value == 1 && choice.options.size() == 2, "Unexpected cloud choices/default");
    require(choice.options[0].key == "Original" && choice.options[0].value == 0, "Original key changed");
    require(choice.options[1].key == "Extended" && choice.options[1].value == 1, "Extended key changed");
    const char* savedKeys[] = {"Original", "Extended"};
    for (unsigned mode : {1U, 0U, 1U, 0U}) {
        config.update_option_value("cloud_coverage", mode);
        require(RT64::getWr64CloudCoverageMode() == mode, "Live callback did not apply");
        require(config.save_config(), "Preference save failed");
        nlohmann::json saved; { std::ifstream file(path); file >> saved; }
        require(saved.at("cloud_coverage") == savedKeys[mode], "Stable choice not saved");
        for (const auto& item : baseline.items())
            require(saved.at(item.key()) == item.value(), "Existing enhancement preference changed");
        RT64::setWr64CloudCoverageMode(1U - mode);
        Config reopened("Enhancements", "enhancements", false); register_cloud_schema(reopened);
        require(reopened.load_config(), "Saved preference did not load");
        require(RT64::getWr64CloudCoverageMode() == mode, "Saved mode did not reach renderer");
    }
    auto malformed = baseline;
    malformed["cloud_coverage"] = "Unknown";
    { std::ofstream file(path); file << malformed; }
    RT64::setWr64CloudCoverageMode(1);
    require(config.load_config() && RT64::getWr64CloudCoverageMode() == 1,
        "Unknown saved option did not restore the release default");
    for (uint32_t invalid : {2U, 10U, UINT32_MAX}) {
        RT64::setWr64CloudCoverageMode(invalid);
        require(RT64::getWr64CloudCoverageMode() == 0, "Invalid renderer mode must fall back to Original");
    }
}
}
namespace recomp {
std::filesystem::path get_config_path() { return profile; }
const Version& get_project_version() { static const Version version; return version; }
}
int main() {
    try {
        profile = std::filesystem::temp_directory_path() / ("wr64-cloud-settings-" +
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(profile); run();
        std::cout << "PASS: " << checks << " cloud persistence checks\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << "FAIL: " << error.what() << '\n'; return 1; }
}
