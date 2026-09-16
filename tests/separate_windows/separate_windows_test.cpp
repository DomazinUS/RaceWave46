#include "wr64_split_screen.hpp"
#include "common/rt64_wr64_split_marker.h"
#include "common/rt64_wr64_separate_windows.h"
#include "common/rt64_wr64_vertical_split.h"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include <array>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

void registered_split_schema(recomp::config::Config&);
namespace {
unsigned checks = 0, inputCalls = 0;
bool multiplayer = false;
std::filesystem::path profile;
constexpr uint32_t Pool = 0x80300000, Cursor = Pool + 0x40;
void require(bool ok, const char* message) { ++checks; if (!ok) throw std::runtime_error(message); }
template<class T> void put(std::vector<uint8_t>& bytes, uint32_t address, T value) {
    const auto offset = (address & 0x7FFFFFU) ^ (sizeof(T) == 2 ? 2U : 0U);
    std::memcpy(bytes.data() + offset, &value, sizeof(value));
}
uint32_t word(const std::vector<uint8_t>& bytes, uint32_t address) {
    uint32_t value; std::memcpy(&value, bytes.data() + (address & 0x7FFFFFU), 4); return value;
}
void context(std::vector<uint8_t>& bytes, int players = 2, int phase = 1, int mode = 40) {
    put(bytes, 0x800DAB28, int32_t(players)); put(bytes, 0x801CE638, int32_t(phase));
    put(bytes, 0x800DAB24, int32_t(mode)); put(bytes, 0x801518B8, Pool);
    put(bytes, 0x801CE624, int16_t(-1)); put(bytes, 0x801CE62C, int16_t(0));
}
void native_scope() {
    using namespace wr64::split_screen;
    require(mode() == 0 && !vertical() && !separate_windows(), "Fresh process must retain Horizontal");
    std::vector<uint8_t> memory(0x800000, 0xCD);
    for (bool backend : {false, true}) {
        RT64::wr64SeparateWindowsBackend.store(backend);
        set_mode(2);
        require(mode() == 2 && separate_windows() == backend && vertical() == backend,
            "Separate windows did not preserve saved choice while gating unsupported backend");
        for (int players : {1, 2, 3}) for (int phase : {0, 1, 4, 5, 8, 10, 18})
        for (int raceMode : {39, 40, 41, 42, 43, 44, 45, 46}) {
            context(memory, players, phase, raceMode);
            const bool emits = backend && players == 2 && phase == 1 && raceMode >= 40 && raceMode <= 45;
            auto expected = memory;
            if (emits) {
                put(expected, Cursor, RT64::Wr64SeparateWindowsMarker);
                put(expected, Cursor + 4, RT64::Wr64SplitVersion);
            }
            const unsigned previousInput = inputCalls;
            require(wr64_split_screen_frame(memory.data(), Cursor) == Cursor + (emits ? 8 : 0),
                "Separate marker did not follow native race/finish/menu scope");
            require(memory == expected, "Marker changed native state outside its eight-byte packet");
            require(inputCalls == previousInput + 1 && multiplayer == (players == 2),
                "Layout/backend selection changed independent player input routing");
            if (emits) {
                bool verticalFrame = false, separateFrame = false; uint8_t owner = 99;
                require(RT64::wr64DecodeSplitMarker(word(memory, Cursor), word(memory, Cursor + 4),
                    verticalFrame, owner, &separateFrame) && verticalFrame && separateFrame && owner == 0,
                    "Real native packet lost separate-window ownership at decoder");
            }
        }
    }
    for (uint32_t invalid : {3U, 10U, UINT32_MAX}) {
        set_mode(invalid);
        require(mode() == 0 && !vertical() && !separate_windows(), "Invalid saved numeric mode was admitted");
    }
    set_vertical(true);
    require(mode() == 1 && vertical() && !separate_windows(), "Existing vertical setter changed meaning");
    context(memory); wr64_split_screen_frame(memory.data(), Cursor);
    bool verticalFrame = false, separateFrame = true; uint8_t owner = 99;
    require(word(memory, Cursor) == RT64::Wr64SplitMarker && RT64::wr64DecodeSplitMarker(
        word(memory, Cursor), word(memory, Cursor + 4), verticalFrame, owner, &separateFrame) &&
        verticalFrame && !separateFrame, "Original vertical marker inherited separate-window flag");
    set_vertical(false);
    require(mode() == 0 && !vertical() && !separate_windows(), "Horizontal compatibility setter failed");
    for (uint32_t bits : {3U, 4U, 0x01000000U}) {
        verticalFrame = false; separateFrame = false; owner = 99;
        require(!RT64::wr64DecodeSplitMarker(RT64::Wr64SeparateWindowsMarker,
            RT64::Wr64SplitVersion + bits, verticalFrame, owner, &separateFrame) &&
            !verticalFrame && !separateFrame && owner == 99, "Malformed separate marker mutated decoder output");
    }
}
void native_lifecycle() {
    using namespace wr64::split_screen;
    std::vector<uint8_t> memory(0x800000, 0xCD);
    for (int owner : {1, 2}) {
        context(memory); put(memory, 0x801CE624, int16_t(0)); put(memory, 0x801CE62C, int16_t(owner));
        RT64::wr64SeparateWindowsBackend.store(true); set_mode(2);
        require(wr64_split_screen_frame(memory.data(), Cursor) == Cursor + 8, "Separate frame did not begin");
        bool verticalFrame = false, separateFrame = false; uint8_t pauseOwner = 0;
        require(RT64::wr64DecodeSplitMarker(word(memory, Cursor), word(memory, Cursor + 4),
            verticalFrame, pauseOwner, &separateFrame) && pauseOwner == owner && separateFrame,
            "Separate marker lost native pause owner");
        // A change in the UI cannot change a queued packet or close only half
        // of a currently emitted pause/lap ownership bracket.
        set_mode(0);
        require(wr64_split_screen_pause(memory.data(), Cursor + 8, 1) == Cursor + 16 &&
            wr64_split_screen_pause(memory.data(), Cursor + 16, 0) == Cursor + 24,
            "Changing saved mode invalidated an in-flight pause bracket");
        require(wr64_split_screen_lap(memory.data(), Cursor + 24, owner) == Cursor + 32 &&
            wr64_split_screen_lap(memory.data(), Cursor + 32, 0) == Cursor + 40,
            "Changing saved mode invalidated an in-flight lap bracket");
        require(separateFrame && verticalFrame, "Queued frame sampled later UI state");
        for (int next : {0, 1, 2, 3}) {
            // Establish abandoned scopes, then clear through each early-return
            // route: setting off, menu, SP, or unsupported renderer backend.
            RT64::wr64SeparateWindowsBackend.store(true); set_mode(2); context(memory);
            put(memory, 0x801CE62C, int16_t(owner)); wr64_split_screen_frame(memory.data(), Cursor);
            wr64_split_screen_pause(memory.data(), Cursor + 8, 1);
            wr64_split_screen_lap(memory.data(), Cursor + 16, owner);
            if (next == 0) set_mode(0);
            if (next == 1) put(memory, 0x801CE638, int32_t(18));
            if (next == 2) put(memory, 0x800DAB28, int32_t(1));
            if (next == 3) RT64::wr64SeparateWindowsBackend.store(false);
            require(wr64_split_screen_frame(memory.data(), Cursor) == Cursor, "Inactive next frame emitted a marker");
            require(wr64_split_screen_pause(memory.data(), Cursor + 64, 0) == Cursor + 64 &&
                wr64_split_screen_lap(memory.data(), Cursor + 72, 0) == Cursor + 72,
                "Abandoned player ownership leaked into an inactive next frame");
        }
    }
}
void persistence() {
    using namespace wr64::split_screen;
    using recomp::config::Config;
    RT64::wr64SeparateWindowsBackend.store(true);
    Config config("Enhancements", "enhancements", true);
    registered_split_schema(config); config.set_config_directory(profile);
    set_mode(2);
    require(config.load_config() && mode() == 0, "Fresh profile did not apply Horizontal default");
    const auto& option = config.get_config_schema().options.at(0);
    const auto& choices = std::get<recomp::config::ConfigOptionEnum>(option.variant);
    require(choices.options.size() == 3 && choices.default_value == 0, "Missing separate-windows choice or changed default");
    require(choices.options[0].value == 0 && choices.options[0].key == "Horizontal" &&
        choices.options[1].value == 1 && choices.options[1].key == "Vertical" && choices.options[2].value == 2,
        "Existing layout keys changed or mode2 missing");
    const std::string separateKey = choices.options[2].key;
    require(separateKey == "Separate windows (Experimental)", "Separate windows stable saved key changed");
    require(choices.options[2].name == "Separate windows", "Visible choice still contains the Experimental label");
    // Existing profiles keep their original storage key while the radio
    // control uses the separate display name. Reopening and Discard must not
    // silently reset that saved selection during the visible-label rename.
    { std::ofstream file(profile / "enhancements.json");
      file << nlohmann::json{{"split_screen_layout", "Separate windows (Experimental)"},
          {"cloud_coverage", "Extended"}}; }
    set_mode(0);
    require(config.load_config() && mode() == 2, "Legacy separate-window profile did not reload after label rename");
    config.update_option_value("split_screen_layout", 0U); config.revert_temp_config();
    require(mode() == 2, "Discard lost the legacy saved selection after label rename");
    for (uint32_t selected : {2U, 1U, 0U, 2U}) {
        config.update_option_value("split_screen_layout", selected);
        require(mode() == selected, "Actual frontend callback lost selected mode");
        require(config.save_config(), "Layout preference did not save");
        nlohmann::json saved; { std::ifstream file(profile / "enhancements.json"); file >> saved; }
        require(saved.at("split_screen_layout") == choices.options[selected].key, "Saved layout key changed");
        require(saved.at("cloud_coverage") == "Extended", "Layout save changed an unrelated enhancement");
        set_mode((selected + 1) % 3);
        Config reopened("Enhancements", "enhancements", true); registered_split_schema(reopened);
        reopened.set_config_directory(profile);
        require(reopened.load_config() && mode() == selected, "Saved layout did not reach native producer on reload");
    }
    config.update_option_value("split_screen_layout", 0U); config.revert_temp_config();
    require(mode() == 2, "Discard did not restore saved Separate windows");
    RT64::wr64SeparateWindowsBackend.store(false);
    require(config.load_config() && mode() == 2 && !vertical() && !separate_windows(),
        "Unsupported backend lost saved choice or admitted separate presentation");
}
void atlas_geometry() {
    // Production virtual32:9 divides into two16:9 panes. These are geometry
    // checks only; the swapchain/window presentation is tested separately.
    constexpr float height = 1080;
    const float width = height * RT64::Wr64SeparateWindowsAspect;
    const auto layout = RT64::wr64VerticalLayout(true, width, height, height / 240.0f);
    for (int owner : {1, 2}) {
        const auto pane = RT64::wr64VerticalPane(layout, owner);
        require(std::abs((pane.right - pane.left) / height - RT64::Wr64SeparatePlayerAspect) < 0.0001f,
            "Separate player pane lost16:9 geometry");
        const auto mapping = RT64::wr64VerticalWorld(layout, owner);
        require(std::abs(mapping.x(width * .5f) - (pane.left + pane.right) * .5f) < .001f &&
            std::abs(mapping.y(height * (owner == 1 ? .25f : .75f)) - height * .5f) < .001f,
            "Native player camera center did not remain centered in its atlas pane");
    }
    require(RT64::wr64VerticalHalfScissor(0, 0, 424 * 4, 240 * 4) == 0,
        "A shared full-frame transition was claimed as one player");
}
}
namespace wr64::input { void set_multiplayer_enabled(bool value) { multiplayer = value; ++inputCalls; } }
namespace recomp {
std::filesystem::path get_config_path() { return profile; }
const Version& get_project_version() { static const Version version; return version; }
}
int main() {
    try {
        profile = std::filesystem::temp_directory_path() / ("wr64-separate-windows-" +
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(profile);
        native_scope(); native_lifecycle(); persistence(); atlas_geometry();
        std::cout << "PASS: " << checks << " separate-window native lifecycle and persistence checks\n";
    } catch (const std::exception& error) { std::cerr << "FAIL: " << error.what() << '\n'; return 1; }
}
