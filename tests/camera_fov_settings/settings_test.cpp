#include "wr64_camera_fov.hpp"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

void registered_fov_schema(recomp::config::Config&);
namespace {
std::filesystem::path profile;
unsigned checks = 0;
void require(bool value, const char* message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}
void run() {
    using recomp::config::Config;
    constexpr auto key = "camera_fov_extra_degrees";
    const auto path = profile / "enhancements.json";
    // An existing player's profile has no FOV entry and owns other settings.
    const nlohmann::json original = {{"water_reflections", "RayTraced"},
        {"sunny_two_player_scenery", "Enhanced"}, {"wave_roundness", 50}};
    { std::ofstream file(path); file << original; }
    wr64::camera_fov::set_extra_degrees(20.0);
    Config config("Enhancements", "enhancements", false);
    registered_fov_schema(config);
    require(config.load_config(), "Existing profile loads");
    require(wr64::camera_fov::extra_degrees() == 5.0, "Missing key restores the release default after another profile");
    const auto& option = config.get_config_schema().options.at(0);
    const auto& number = std::get<recomp::config::ConfigOptionNumber>(option.variant);
    require(number.min == 0.0 && number.max == 10.0 && number.default_value == 5.0 && !number.percent,
        "Production slider defaults to the saved five-degree preference");
    config.update_option_value(key, 10.0);
    require(wr64::camera_fov::extra_degrees() == 10.0, "Live production callback updates the native lens setting");
    require(config.save_config(), "Wider setting saves");
    nlohmann::json saved;
    { std::ifstream file(path); file >> saved; }
    require(saved.at(key) == 10.0, "Saved FOV uses stable numeric key");
    for (const auto& item : original.items()) {
        require(saved.at(item.key()) == item.value(), "FOV save preserves unrelated enhancement settings");
    }
    wr64::camera_fov::set_extra_degrees(0.0);
    Config reopened("Enhancements", "enhancements", false);
    registered_fov_schema(reopened);
    require(reopened.load_config() && wr64::camera_fov::extra_degrees() == 10.0, "Persisted FOV reaches native helper on load");
    reopened.update_option_value(key, 0.0);
    require(wr64::camera_fov::extra_degrees() == 0.0 && reopened.save_config(), "Original can be restored live and saved");
    wr64::camera_fov::set_extra_degrees(20.0);
    require(config.load_config() && wr64::camera_fov::extra_degrees() == 0.0, "Original survives reopening");

    // Previous experimental builds allowed a value of 20; loading that profile
    // must also correct the slider value rather than only clamping the lens.
    auto legacy = original;
    legacy[key] = 20.0;
    { std::ofstream file(path); file << legacy; }
    require(reopened.load_config() && wr64::camera_fov::extra_degrees() == 10.0,
        "Legacy twenty-degree profile reaches new native maximum on load");
    require(std::get<double>(reopened.get_option_value(key)) == 10.0,
        "Legacy value is normalized in frontend storage for the slider");
    require(reopened.save_config(), "Normalized legacy setting saves");
    { std::ifstream file(path); file >> saved; }
    require(saved.at(key) == 10.0, "Legacy profile saves the normalized ten-degree limit");
    for (const auto& item : original.items()) {
        require(saved.at(item.key()) == item.value(), "Legacy migration preserves unrelated enhancement settings");
    }
    require(config.load_config() && std::get<double>(config.get_option_value(key)) == 10.0 &&
        wr64::camera_fov::extra_degrees() == 10.0, "Normalized legacy profile reopens consistently");
}
}
namespace recomp {
std::filesystem::path get_config_path() { return profile; }
const Version& get_project_version() { static const Version version; return version; }
}
int main() {
    try {
        profile = std::filesystem::temp_directory_path() / ("wr64-fov-settings-" +
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(profile);
        run();
        std::cout << "PASS: " << checks << " frontend FOV persistence checks\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
