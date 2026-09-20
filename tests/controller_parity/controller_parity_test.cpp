// Compile the real host input adapter with controlled external APIs. This tests
// its boundary contract; SDL hardware and RecompFrontend aggregation are not
// reimplemented here. No controller is opened and no settings file is written.
#include <array>
#include <cstdio>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "SDL.h"
#include "wr64_input.hpp"
#include "recompinput/profiles.h"
#include "composites/ui_assign_players_modal.h"
#include "config/ui_config_page_controls.h"

namespace {
struct Fixture {
    bool sdl_failure = false;
    bool single_player = false;
    std::array<bool, 2> assigned{};
    std::array<recompinput::Player, 2> players{};
    std::array<std::array<int, 2>, 2> player_profiles{{{1, 0}, {1, 0}}};
    bool assigning = false, cancelled = false;
    bool controls_released = true;
    int assignment_opens = 0, assignment_closes = 0, rumble_resets = 0;
    int sdl_init_calls = 0;
    int ps5_hint_calls = 0;
    int subsystem_calls = 0;
    std::uint32_t subsystem_flags = 0;
    int bindings_calls = 0;
    int loads = 0;
    int saves = 0;
    int polls = 0;
    int rumble_updates = 0;
    int input_calls = 0;
    int assigned_queries = 0;
    int profile_port = -1;
    std::size_t min_players = 0;
    std::size_t max_players = 0;
    std::uint16_t profile_buttons = 0xA010;
    float profile_x = -0.625F;
    float profile_y = 0.875F;
    bool profile_result = true;
    std::filesystem::path loaded_path;
    std::filesystem::path saved_path;
    std::vector<std::pair<int, bool>> motors;
    std::array<std::string, 3> descriptions;
} fixture;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

void expect_disconnected(int port) {
    std::uint16_t buttons = 0x1357;
    float x = 0.25F, y = -0.75F;
    int input_calls = fixture.input_calls;
    require(!wr64::input::get(port, &buttons, &x, &y), "Disconnected port accepted input");
    require(buttons == 0x1357 && x == 0.25F && y == -0.75F,
        "Disconnected port changed caller output");
    require(fixture.input_calls == input_calls, "Disconnected port reached profile input");
    const auto device = wr64::input::get_connected_device_info(port);
    require(device.connected_device == ultramodern::input::Device::None &&
        device.connected_pak == ultramodern::input::Pak::None,
        "Disconnected port advertised a device or Pak");
}

void expect_passthrough() {
    std::uint16_t buttons = 0xFFFF;
    float x = 1.0F, y = 1.0F;
    require(wr64::input::get(0, &buttons, &x, &y) == fixture.profile_result,
        "Adapter changed profile success result");
    require(buttons == fixture.profile_buttons && x == fixture.profile_x && y == fixture.profile_y,
        "Adapter changed the profile button or analog values");
    require(fixture.profile_port == 0, "Adapter used the wrong profile port");
}

void expect_neutral_p2() {
    uint16_t buttons = 0x1234; float x = .25f, y = -.75f;
    require(wr64::input::get(1, &buttons, &x, &y) && buttons == 0 && x == 0 && y == 0,
        "Reserved SP port two was not neutral");
    const auto device = wr64::input::get_connected_device_info(1);
    require(device.connected_device == ultramodern::input::Device::Controller &&
        device.connected_pak == ultramodern::input::Pak::RumblePak,
        "Native startup did not discover reserved virtual port two");
}

void check_uninitialized_callbacks() {
    require(!wr64::input::ready(), "Input unexpectedly ready before initialize");
    expect_disconnected(0);
    expect_disconnected(1);
    wr64::input::poll();
    wr64::input::set_rumble(0, true);
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    wr64::input::shutdown();
    require(fixture.polls == 0 && fixture.motors.empty() && fixture.rumble_updates == 0 &&
        fixture.saves == 0, "Uninitialized callback reached an external API");
}

void check_initialized_callbacks() {
    wr64::input::initialize();
    require(wr64::input::ready(), "Successful SDL initialization did not activate input");
    require(fixture.sdl_init_calls == 1 && fixture.ps5_hint_calls == 1 && fixture.subsystem_calls == 1,
        "Shindou SDL initialization sequence was not called once");
    require(fixture.subsystem_flags == (SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS),
        "Shindou controller and event subsystems were not requested");
    require(fixture.bindings_calls == 1 && fixture.single_player,
        "Single-player profiles were not initialized");
    require(fixture.min_players == 1 && fixture.max_players == 2,
        "Expected Shindou player count range 1..2");
    const auto expected_path = std::filesystem::path(WR64_TEST_CONFIG_DIR) / "controls.json";
    require(fixture.loads == 1 && fixture.loaded_path == expected_path,
        "Controls were not loaded from the registered config directory");
    require(fixture.descriptions[0] == "Accelerate" &&
        fixture.descriptions[1] == "Brake and reverse" && fixture.descriptions[2] == "Pause",
        "Expected Shindou game-input descriptions");

    wr64::input::initialize();
    require(fixture.sdl_init_calls == 1 && fixture.ps5_hint_calls == 1 && fixture.bindings_calls == 1 && fixture.loads == 1,
        "Repeated initialize reset input or settings");

    // No device is assigned. Shindou still connects virtual port one, even if
    // the keyboard is the only source. RecompFrontend supplies aggregation.
    expect_passthrough();
    require(fixture.assigned_queries == 0, "Single-player input required an assignment");
    const auto device = wr64::input::get_connected_device_info(0);
    require(device.connected_device == ultramodern::input::Device::Controller &&
        device.connected_pak == ultramodern::input::Pak::RumblePak,
        "Port one must advertise a virtual controller and Rumble Pak");

    // Startup reserves P2, but stale multiplayer assignments cannot drive it.
    fixture.assigned[1] = true;
    for (int port : {-1, 2, 3}) expect_disconnected(port);
    expect_neutral_p2();

    // UI suppression is resolved by RecompFrontend. The host must pass its
    // neutral result through rather than reading another keyboard/controller.
    fixture.profile_buttons = 0;
    fixture.profile_x = fixture.profile_y = 0.0F;
    expect_passthrough();
    fixture.profile_result = false;
    expect_passthrough();
    fixture.profile_result = true;

    wr64::input::poll();
    require(fixture.polls == 1, "Poll was not delegated to RecompFrontend");
    wr64::input::set_rumble(0, true);
    wr64::input::set_rumble(0, false);
    for (int port : {-1, 1, 2, 3}) wr64::input::set_rumble(port, true);
    require(fixture.motors == std::vector<std::pair<int, bool>>{{0, true}, {0, false}},
        "Rumble did not follow the same connected-port contract");
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    require(fixture.rumble_updates == 1, "Host did not delegate the rumble envelope update");

    wr64::input::shutdown();
    require(fixture.saves == 1 && fixture.saved_path == expected_path,
        "Controls were not saved through the profile API at the config path");
}

void check_multiplayer_transitions() {
    wr64::input::set_multiplayer_enabled(true);
    require(wr64::input::multiplayer_requested() && fixture.single_player,
        "Native request performed a host-thread mode mutation");
    std::uint16_t buttons = 0xFFFF; float x = 1, y = 1;
    require(wr64::input::get(1, &buttons, &x, &y) && buttons == 0 && x == 0 && y == 0,
        "Pending 2P request did not reserve a neutral second port");
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    require(!fixture.single_player && fixture.assigning && fixture.min_players == 2 &&
        fixture.max_players == 2 && fixture.assignment_opens == 1,
        "Host did not request exactly two assigned players");
    for (int tick = 0; tick < 4; ++tick) {
        wr64::input::set_multiplayer_enabled(true);
        wr64::input::process_pending_ui(); wr64::input::update_rumble();
    }
    require(fixture.assignment_opens == 1, "Repeated native publications reopened assignment");
    fixture.assigned = {true, true};
    SDL_GameController first{}, second{};
    fixture.players[0].controller = &first;
    fixture.players[1].controller = &second;
    fixture.assigning = false;
    fixture.controls_released = false;
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    require(wr64::input::get(1, &buttons, &x, &y) && buttons == 0 && x == 0 && y == 0,
        "Held assignment confirmation leaked into gameplay");
    fixture.controls_released = true;
    wr64::input::update_rumble();
    require(fixture.player_profiles[0][1] == -1 && fixture.player_profiles[1][1] == -1,
        "Unused keyboard profiles could drive both controller players");
    require(wr64::input::get(1, &buttons, &x, &y) && fixture.profile_port == 1,
        "Assigned second port did not reach its own profile");
    second.attached = false;
    require(wr64::input::get(1, &buttons, &x, &y) && buttons == 0 && x == 0 && y == 0,
        "Detached P2 did not become neutral before host reassignment");
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    require(fixture.assigning && fixture.assignment_opens == 2,
        "Lost assigned device did not request reassignment");
    fixture.cancelled = true; fixture.assigning = false;
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    require(fixture.single_player && fixture.min_players == 1, "Cancel did not restore SP mode");
    expect_neutral_p2();
    for (int tick = 0; tick < 4; ++tick) {
        wr64::input::set_multiplayer_enabled(true);
        wr64::input::process_pending_ui(); wr64::input::update_rumble();
    }
    require(fixture.assignment_opens == 2, "Cancelled request reopened without explicit retry");
    wr64::input::request_multiplayer_assignment();
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    require(fixture.assigning && fixture.assignment_opens == 3, "Controls retry did not reopen 2P assignment");
    wr64::input::set_multiplayer_enabled(false);
    wr64::input::process_pending_ui(); wr64::input::update_rumble();
    require(fixture.single_player && !fixture.assigning && !wr64::input::multiplayer_requested(),
        "Leaving 2P did not close assignment and restore aggregation");
    expect_passthrough();
    expect_neutral_p2();
}
}

int SDL_Init(std::uint32_t flags) {
    require(flags == 0, "Shindou starts SDL without enabling a subsystem");
    ++fixture.sdl_init_calls;
    return 0;
}
int SDL_InitSubSystem(std::uint32_t flags) {
    require(fixture.ps5_hint_calls == 1, "PS5 rumble default was not set before controller enumeration");
    ++fixture.subsystem_calls;
    fixture.subsystem_flags = flags;
    return fixture.sdl_failure ? -1 : 0;
}
int SDL_SetHintWithPriority(const char* name, const char* value, SDL_HintPriority priority) {
    require(fixture.sdl_init_calls == 1 && fixture.subsystem_calls == 0,
        "PS5 rumble hint must be configured after SDL_Init and before subsystem enumeration");
    require(std::string(name) == SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE && std::string(value) == "1" &&
        priority == SDL_HINT_DEFAULT, "PS5 rumble default must preserve explicit user hint priority");
    ++fixture.ps5_hint_calls;
    return SDL_TRUE;
}
const char* SDL_GetError() { return "controlled SDL failure"; }
int SDL_GameControllerGetAttached(SDL_GameController* controller) { return controller && controller->attached; }

namespace recompui {
ConfigPageControls* controls_page = nullptr;
void ConfigPageControls::force_update() {}
void AssignPlayersModal::open() { ++fixture.assignment_opens; }
void AssignPlayersModal::close() { ++fixture.assignment_closes; }
}

namespace wr64::editions {
bool controls_released() { return fixture.controls_released; }
}

namespace recomp {
std::filesystem::path get_config_path() { return WR64_TEST_CONFIG_DIR; }
}
namespace recompinput {
void poll_inputs() { ++fixture.polls; }
void update_rumble() { ++fixture.rumble_updates; }
void reset_rumble() { ++fixture.rumble_resets; }
void set_rumble(int controller, bool enabled) { fixture.motors.emplace_back(controller, enabled); }
void set_game_input_description(GameInput input, const char* description) {
    fixture.descriptions.at(static_cast<std::size_t>(input)) = description;
}
namespace players {
void set_single_player_mode(bool enabled) { fixture.single_player = enabled; }
bool is_single_player_mode() { return fixture.single_player; }
void set_player_count_range(std::size_t minimum, std::size_t maximum) {
    fixture.min_players = minimum;
    fixture.max_players = maximum;
}
bool get_player_is_assigned(int controller) {
    ++fixture.assigned_queries;
    return controller >= 0 && controller < 2 && fixture.assigned[controller];
}
const Player& get_player(int controller) { return fixture.players.at(controller); }
size_t get_number_of_assigned_players() { return fixture.assigned[0] + fixture.assigned[1]; }
}
namespace playerassignment {
void start() { fixture.assigning = true; fixture.cancelled = false; }
void stop() { fixture.assigning = false; }
bool was_cancelled() { return fixture.cancelled; }
bool is_active() { return fixture.assigning; }
void process_pending_ui() {}
}
namespace profiles {
int get_input_profile_by_key(const std::string&) { return 0; }
std::string get_mp_keyboard_profile_key(int player) { return "keyboard_" + std::to_string(player); }
void set_input_profile_for_player(int player, int profile, InputDevice device) {
    fixture.player_profiles.at(player).at(static_cast<size_t>(device)) = profile;
}
int get_input_profile_for_player(int player, InputDevice device) {
    return fixture.player_profiles.at(player).at(static_cast<size_t>(device));
}
int get_sp_keyboard_profile_index() { return 0; }
void set_input_binding(int, GameInput, size_t, InputField) {}
InputField& get_input_binding(int, GameInput, size_t) { static InputField field; return field; }
void initialize_input_bindings() { ++fixture.bindings_calls; }
bool load_controls_config(const std::filesystem::path& path) {
    ++fixture.loads;
    fixture.loaded_path = path;
    return true;
}
bool save_controls_config(const std::filesystem::path& path) {
    ++fixture.saves;
    fixture.saved_path = path;
    return true;
}
bool get_n64_input(int controller, std::uint16_t* buttons, float* x, float* y) {
    ++fixture.input_calls;
    fixture.profile_port = controller;
    *buttons = fixture.profile_buttons;
    *x = fixture.profile_x;
    *y = fixture.profile_y;
    return fixture.profile_result;
}
}
}

int main(int argc, char** argv) {
    try {
        check_uninitialized_callbacks();
        if (argc == 2 && std::string(argv[1]) == "--sdl-failure") {
            fixture.sdl_failure = true;
            wr64::input::initialize();
            check_uninitialized_callbacks();
            require(fixture.bindings_calls == 0 && fixture.loads == 0,
                "Failed SDL initialization proceeded into profiles");
        } else {
            check_initialized_callbacks();
            check_multiplayer_transitions();
        }
        std::puts("Controller adapter parity checks passed.");
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "Controller parity failure: %s\n", error.what());
        return 1;
    }
}
