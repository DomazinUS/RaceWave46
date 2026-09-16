#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include "wr64_free_ride_menu.hpp"
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

void register_free_ride_schema(recomp::config::Config&);
extern "C" void wr64_free_ride_course_menu(uint8_t*);
extern "C" void wr64_free_ride_course_refresh(uint8_t*);
extern "C" uint32_t wr64_free_ride_course_confirm(uint8_t*);

namespace {
std::filesystem::path profile;
unsigned checks = 0;
bool assetsAvailable = true;
bool adjacentEnhanced = false;
using Ram = std::vector<uint8_t>;
void require(bool ok, const char* message) { ++checks; if (!ok) throw std::runtime_error(message); }
template<class T> void put(Ram& ram, uint32_t address, T value) {
    std::memcpy(ram.data() + ((address & 0x7FFFFFu) ^ (sizeof(T) == 2 ? 2u : 0u)), &value, sizeof(value));
}
uint32_t get(const Ram& ram, uint32_t address) {
    uint32_t value; std::memcpy(&value, ram.data() + (address & 0x7FFFFFu), sizeof(value)); return value;
}
Ram menu() {
    Ram ram(0x800000);
    put(ram, 0x801CE638, 5); put(ram, 0x801CE608, 1); put<int16_t>(ram, 0x801CE60C, 2);
    put(ram, 0x802C76A4, 1);
    for (uint32_t i = 0; i < 9; ++i) put(ram, 0x800DAAD8 + 4 * i, i);
    return ram;
}
void expectMenu(bool enabled) {
    auto ram = menu(); wr64_free_ride_course_menu(ram.data());
    require(get(ram, 0x802C7558) == uint32_t(enabled), "saved callback did not control native course availability");
    require(get(ram, 0x802C76A4) == (enabled ? 0u : 1u), "native navigation minimum disagrees with setting");
    require(bool(wr64_free_ride_course_confirm(ram.data())) == enabled, "native Dolphin confirmation disagrees with setting");
}
void run() {
    using recomp::config::Config;
    require(wr64::free_ride::enabled(), "fresh process must default to ON");
    const auto path = profile / "enhancements.json";
    const nlohmann::json baseline = {{"sunny_two_player_scenery", "Enhanced"},
        {"split_screen_layout", "Separate windows (Experimental)"}, {"cloud_coverage", "Extended"},
        {"water_reflections", "Ray Traced"}, {"wave_roundness", 50}, {"far_water_distance", "5x"}};
    { std::ofstream file(path); file << baseline; }
    Config config("Enhancements", "enhancements", false); register_free_ride_schema(config);
    const auto& schema = config.get_config_schema();
    require(schema.options.size() == 2, "unexpected extracted neighboring option count");
    require(schema.options[0].id == "sunny_two_player_scenery" && schema.options[1].id == "dolphin_free_ride",
        "Free Ride must be adjacent to two-player visual detail");
    require(schema.options[1].name == "Two-player Dolphin Park" && !schema.options[1].hidden,
        "Free Ride option label or visibility changed");
    require(std::get<recomp::config::ConfigOptionBool>(schema.options[1].variant).default_value,
        "frontend default must be ON");
    wr64::free_ride::set_enabled(false);
    require(config.load_config(), "old profile load failed");
    require(wr64::free_ride::enabled(), "old profile without the option did not apply default ON callback");
    require(adjacentEnhanced, "neighboring saved two-player visual setting did not load");
    expectMenu(true);

    for (bool enabled : {false, true, false}) {
        config.update_option_value("dolphin_free_ride", enabled);
        require(wr64::free_ride::enabled() == enabled, "real live callback did not apply bool setting");
        require(adjacentEnhanced, "Free Ride callback changed adjacent visual preference");
        expectMenu(enabled);
        require(config.save_config(), "Free Ride preference save failed");
        nlohmann::json saved; { std::ifstream file(path); file >> saved; }
        require(saved.at("dolphin_free_ride").is_boolean() && saved.at("dolphin_free_ride") == enabled,
            "saved Free Ride preference is not the requested JSON boolean");
        for (const auto& entry : baseline.items())
            require(saved.at(entry.key()) == entry.value(), "saving Free Ride changed another enhancement");
        wr64::free_ride::set_enabled(!enabled);
        Config reloaded("Enhancements", "enhancements", false); register_free_ride_schema(reloaded);
        require(reloaded.load_config(), "saved profile reload failed");
        require(wr64::free_ride::enabled() == enabled, "saved ON/OFF did not override startup state through actual callback");
        expectMenu(enabled);
    }

    config.update_option_value("dolphin_free_ride", true);
    auto highlighted = menu(); wr64_free_ride_course_menu(highlighted.data());
    require(get(highlighted, 0x800DA9D0) == 0, "fixture should highlight Dolphin");
    config.update_option_value("dolphin_free_ride", false);
    wr64_free_ride_course_refresh(highlighted.data());
    require(get(highlighted, 0x802C7558) == 0 && get(highlighted, 0x802C76A4) == 1 &&
        get(highlighted, 0x800DA9D0) == 1, "switching OFF left the highlighted Dolphin row accessible");
    require(!wr64_free_ride_course_confirm(highlighted.data()), "OFF still allowed native Dolphin confirmation");
    config.update_option_value("dolphin_free_ride", true);
    wr64_free_ride_course_refresh(highlighted.data());
    require(get(highlighted, 0x802C7558) == 1 && get(highlighted, 0x802C76A4) == 0,
        "switching ON did not restore Dolphin to current course menu");

    auto running = menu(); put(running, 0x801CE638, 1); put(running, 0x800DAB24, 40);
    put(running, 0x800DAB28, 2); const auto unchanged = running;
    config.update_option_value("dolphin_free_ride", false);
    wr64_free_ride_course_refresh(running.data()); wr64_free_ride_course_menu(running.data());
    require(running == unchanged, "turning OFF changed an already-running native session");

    for (const nlohmann::json invalid : {nlohmann::json("OFF"), nlohmann::json(0), nlohmann::json(nullptr)}) {
        auto malformed = baseline; malformed["dolphin_free_ride"] = invalid;
        { std::ofstream file(path); file << malformed; }
        wr64::free_ride::set_enabled(false);
        require(config.load_config() && wr64::free_ride::enabled(), "malformed saved bool did not restore default ON");
    }
    assetsAvailable = false; expectMenu(false);
    assetsAvailable = true;
}
}
namespace recomp {
std::filesystem::path get_config_path() { return profile; }
const Version& get_project_version() { static const Version version; return version; }
}
namespace wr64::sunny_detail {
void set_enabled(bool enabled) { adjacentEnhanced = enabled; }
}
extern "C" uint32_t wr64_dolphin_free_ride_available(const uint8_t*) { return assetsAvailable; }
int main(int argc, char** argv) {
    try {
        require(argc == 2, "expected synthetic profile parent directory");
        profile = std::filesystem::absolute(argv[1]) / std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        std::filesystem::create_directories(profile); run();
        std::cout << "PASS " << checks << " actual frontend/config/menu setting checks; synthetic profile only\n";
        return 0;
    } catch (const std::exception& error) { std::cerr << "FAIL " << error.what() << '\n'; return 1; }
}
