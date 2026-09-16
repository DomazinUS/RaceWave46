#include "common/rt64_wr64_wave_distance.h"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

void register_wave_schema(recomp::config::Config&);
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
    RT64::setWr64WaveDistanceMode(1);
    Config config("Enhancements", "enhancements", false); register_wave_schema(config);
    require(config.load_config(), "Existing profile failed to load");
    require(RT64::getWr64WaveDistanceMode() == 0, "New preference must default to Original");
    const auto& options = config.get_config_schema().options;
    require(options.size() == 1, "Unexpected extracted schema");
    require(config.is_config_option_hidden(0), "Parked wave experiment must remain hidden");
    const auto& choice = std::get<recomp::config::ConfigOptionEnum>(options[0].variant);
    require(choice.default_value == 0 && choice.options.size() == 3, "Unexpected wave choices/default");
    require(choice.options[0].key == "Original" && choice.options[0].value == 0, "Original key changed");
    require(choice.options[1].key == "Extended" && choice.options[1].value == 1, "Extended key changed");
    require(choice.options[2].key == "Extended+" && choice.options[2].value == 2, "Extended+ key missing");
    const char* savedKeys[] = {"Original", "Extended", "Extended+"};
    for (unsigned mode : {1U, 2U, 0U, 2U, 1U}) {
        config.update_option_value("wave_draw_distance", mode);
        require(RT64::getWr64WaveDistanceMode() == 0, "Hidden wave experiment became active");
        require(config.save_config(), "Preference save failed");
        nlohmann::json saved; { std::ifstream file(path); file >> saved; }
        require(saved.at("wave_draw_distance") == savedKeys[mode], "Stable choice not saved");
        for (const auto& item : baseline.items())
            require(saved.at(item.key()) == item.value(), "Existing enhancement preference changed");
        RT64::setWr64WaveDistanceMode((mode + 1U) % 3U);
        Config reopened("Enhancements", "enhancements", false); register_wave_schema(reopened);
        require(reopened.load_config(), "Saved preference did not load");
        require(std::get<uint32_t>(reopened.get_option_value("wave_draw_distance")) == mode,
            "Saved experiment preference was lost");
        require(RT64::getWr64WaveDistanceMode() == 0, "Older saved experiment became active while hidden");
    }
    RT64::setWr64WaveDistanceMode(99);
    require(RT64::getWr64WaveDistanceMode() == 0, "Invalid renderer mode must fall back to Original");
}
}
namespace recomp {
std::filesystem::path get_config_path() { return profile; }
const Version& get_project_version() { static const Version version; return version; }
}
int main() {
    try {
        profile = std::filesystem::temp_directory_path() / ("wr64-wave-distance-settings-" +
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(profile); run();
        std::cout << "PASS: " << checks << " wave-distance persistence checks\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << "FAIL: " << error.what() << '\n'; return 1; }
}
