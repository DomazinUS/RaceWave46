#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "wr64_input.hpp"
#include "librecomp/game.hpp"
#include "wr64_launcher_input.hpp"
#include "wr64_shared_input_settings.hpp"
#include "recompinput/recompinput.h"
#include "recompinput/profiles.h"
#include "recompinput/input_events.h"
#include "recompinput/input_binding.h"
#include "recompui/config.h"
#include "config/ui_config_page_controls.h"
#include "composites/ui_assign_players_modal.h"
#include "json.h"
#include "ultramodern/ultra64.h"

#undef SDL_GameControllerOpen
#undef SDL_free
namespace {
std::array<Uint8, SDL_NUM_SCANCODES> keys{};
SDL_Keymod modifiers = KMOD_NONE;
bool ui_captures = false, ui_suspended = false;
bool ui_phase = false;
int cursor_queries = 0, fullscreen_toggles = 0, drop_batches = 0;
int freed_test_drops = 0;
std::set<void*> queued_drop_allocations;
std::unique_ptr<recomp::config::Config> general_config;
int ui_event_count = 0, open_count = 0;
int assignment_opens = 0;
std::vector<SDL_GameController*> retired_controllers;
std::set<SDL_JoystickID> virtual_ids;
std::map<std::filesystem::path, std::string> config_storage;

void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(std::string(message) + ": " + SDL_GetError());
}
void near(float value, float expected, const char* message) {
    require(std::fabs(value - expected) < 0.0002F, message);
}
void set_strengths(double p1, double p2) {
    auto& config = recompui::config::get_general_config();
    // This is the setter used by ConfigPageOptionsMenu's actual slider callback.
    config.set_option_value("rumble_strength", p1);
    config.set_option_value("rumble_strength_p2", p2);
}

void check_general_config() {
    namespace general = recompui::config::general;
    const std::filesystem::path directory{WR64_TEST_GENERAL_CONFIG_DIR};
    std::filesystem::create_directories(directory);
    const auto path = directory / "general.json";
    // The old schema must continue to use P1's strength for every device.
    auto& original = recompui::config::create_general_tab({});
    original.update_option_value("rumble_strength", 61.0);
    require(!original.has_option("rumble_strength_p2") && general::get_rumble_strength(1) == 61.0,
        "Single-strength frontend compatibility changed");
    {
        std::ofstream stream(path);
        stream << nlohmann::json{{"rumble_strength", 63.0}, {"future_setting", "preserve"}};
        require(stream.good(), "Could not write isolated legacy settings");
    }
    auto& config = recompui::config::create_general_tab({.has_player_two_rumble_strength = true});
    config.set_config_directory(directory);
    require(config.load_config(), "Actual General config could not load legacy settings");
    require(general::get_rumble_strength() == 63.0 && general::get_rumble_strength(0) == 63.0 &&
        general::get_rumble_strength(1) == 25.0,
        "Legacy player-one strength was lost or new P2 did not use the 25% default");
    set_strengths(71.0, 18.0);
    require(config.save_config(), "Could not save independent General strengths");
    nlohmann::json saved;
    { std::ifstream stream(path); stream >> saved; }
    require(saved.at("rumble_strength") == 71.0 && saved.at("rumble_strength_p2") == 18.0 &&
        saved.at("future_setting") == "preserve", "Saved General settings lost a player or unrelated key");
    set_strengths(0.0, 0.0);
    require(config.load_config() && general::get_rumble_strength(0) == 71.0 &&
        general::get_rumble_strength(1) == 18.0, "Config reload did not republish both motor strengths");

    nlohmann::json launcher = saved;
    nlohmann::json usa{{"unrelated", 7}, {"rumble_strength_p2", 3}};
    wr64::editions::merge_general_input_settings(launcher, usa, true);
    require(usa.at("rumble_strength") == 71.0 && usa.at("rumble_strength_p2") == 18.0 &&
        usa.at("unrelated") == 7, "Launcher did not transfer both strengths to USA");
    usa["rumble_strength"] = 38.0; usa["rumble_strength_p2"] = 82.0;
    wr64::editions::merge_general_input_settings(usa, launcher, true);
    require(launcher.at("rumble_strength") == 38.0 && launcher.at("rumble_strength_p2") == 82.0,
        "USA player settings did not return to the launcher");
    nlohmann::json shindou{{"rumble_strength", 4.0}, {"rumble_strength_p2", 9.0}};
    wr64::editions::merge_general_input_settings(launcher, shindou, false);
    require(shindou.at("rumble_strength") == 38.0 && shindou.at("rumble_strength_p2") == 9.0,
        "USA-only P2 setting was copied into Shindou");
    shindou["rumble_strength"] = 45.0;
    wr64::editions::merge_general_input_settings(shindou, launcher, false);
    require(launcher.at("rumble_strength") == 45.0 && launcher.at("rumble_strength_p2") == 82.0,
        "Returning from Shindou overwrote USA's saved P2 strength");
    wr64::editions::merge_general_input_settings(nlohmann::json{{"rumble_strength", 50.0}}, launcher, true);
    require(launcher.at("rumble_strength_p2") == 82.0,
        "A legacy settings transfer erased the independent P2 value");
    set_strengths(25.0, 25.0);
}

int SDLCALL isolated_events(void*, SDL_Event* event) {
    switch (event->type) {
    case SDL_JOYDEVICEADDED: case SDL_CONTROLLERDEVICEADDED:
        return SDL_JoystickIsVirtual(event->cdevice.which) == SDL_TRUE;
    case SDL_JOYDEVICEREMOVED: case SDL_CONTROLLERDEVICEREMOVED:
        return virtual_ids.contains(event->cdevice.which);
    case SDL_JOYBUTTONDOWN: case SDL_JOYBUTTONUP:
        return virtual_ids.contains(event->jbutton.which);
    case SDL_JOYAXISMOTION:
        return virtual_ids.contains(event->jaxis.which);
    case SDL_CONTROLLERBUTTONDOWN: case SDL_CONTROLLERBUTTONUP:
        return virtual_ids.contains(event->cbutton.which);
    case SDL_CONTROLLERAXISMOTION:
        return virtual_ids.contains(event->caxis.which);
    // SDL video is not initialized, so these are only our injected action
    // events. Physical controllers remain filtered by virtual device identity.
    case SDL_KEYDOWN: case SDL_KEYUP: case SDL_TEXTINPUT:
    case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEWHEEL: case SDL_DROPBEGIN: case SDL_DROPFILE:
    case SDL_DROPTEXT: case SDL_DROPCOMPLETE:
        return 1;
    default: return 0;
    }
}

struct Pad {
    const char* name;
    bool dual_sense = false;
    SDL_JoystickID id = -1;
    SDL_Joystick* joystick = nullptr;
    int rumble_calls = 0;
    Uint16 last_low = 0, last_high = 0;

    static int SDLCALL rumble(void* userdata, Uint16 low, Uint16 high) {
        auto& pad = *static_cast<Pad*>(userdata);
        ++pad.rumble_calls;
        pad.last_low = low;
        pad.last_high = high;
        return 0;
    }

    void attach() {
        last_low = last_high = 0; // This is a newly attached physical device.
        SDL_VirtualJoystickDesc desc{};
        desc.version = SDL_VIRTUAL_JOYSTICK_DESC_VERSION;
        desc.type = SDL_JOYSTICK_TYPE_GAMECONTROLLER;
        desc.naxes = SDL_CONTROLLER_AXIS_MAX;
        desc.nbuttons = SDL_CONTROLLER_BUTTON_MAX;
        desc.button_mask = (1U << SDL_CONTROLLER_BUTTON_MAX) - 1U;
        desc.axis_mask = (1U << SDL_CONTROLLER_AXIS_MAX) - 1U;
        desc.name = name;
        if (dual_sense) {
            desc.vendor_id = 0x054c;
            desc.product_id = 0x0ce6;
        } else {
            desc.vendor_id = 0x045e;
            desc.product_id = 0x028e;
        }
        desc.userdata = this;
        desc.Rumble = rumble;
        const int index = SDL_JoystickAttachVirtualEx(&desc);
        require(index >= 0 && SDL_JoystickIsVirtual(index), "Could not attach a virtual pad");
        id = SDL_JoystickGetDeviceInstanceID(index);
        virtual_ids.insert(id);
        joystick = SDL_JoystickOpen(index);
        require(joystick != nullptr, "Could not open test virtual joystick");
        require(SDL_IsGameController(index), "Virtual joystick is not recognized as game controller");
        axis(SDL_CONTROLLER_AXIS_TRIGGERLEFT, -32768);
        axis(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, -32768);
    }

    void button(SDL_GameControllerButton button, bool pressed) {
        require(SDL_JoystickSetVirtualButton(joystick, button, pressed ? 1 : 0) == 0,
            "Could not set virtual button");
    }
    void axis(SDL_GameControllerAxis axis, Sint16 value) {
        require(SDL_JoystickSetVirtualAxis(joystick, axis, value) == 0, "Could not set virtual axis");
    }
    void check_type() const {
        auto* controller = recompinput::get_controller_from_joystick_id(id);
        require(controller != nullptr, "Virtual controller was not opened by the frontend");
        const auto actual = SDL_GameControllerGetType(controller);
        require(dual_sense ? actual == SDL_CONTROLLER_TYPE_PS5 : actual == SDL_CONTROLLER_TYPE_XBOX360,
            "Real SDL controller classification does not match the haptic test endpoint");
    }
    void require_strength(Uint16 strength) const {
        require(last_high == strength && last_low == (dual_sense ? strength : 0),
            "Virtual motor channels or assigned strength were incorrect");
    }
    void detach() {
        int index = -1;
        for (int i = 0; i < SDL_NumJoysticks(); ++i) {
            if (SDL_JoystickGetDeviceInstanceID(i) == id) index = i;
        }
        require(index >= 0 && SDL_JoystickIsVirtual(index), "Lost test virtual device identity");
        // Keep controller handle for cleanup: RecompFrontend removes its map
        // entry on hotplug but does not itself close this SDL handle there.
        SDL_GameController* controller = recompinput::get_controller_from_joystick_id(id);
        require(SDL_JoystickDetachVirtual(index) == 0, "Could not detach virtual pad");
        recompinput::handle_events();
        wr64::input::poll();
        require(recompinput::get_controller_from_joystick_id(id) == nullptr,
            "Removed virtual pad remains in RecompFrontend state");
        if (controller) {
            if (recompinput::players::is_single_player_mode()) SDL_GameControllerClose(controller);
            else retired_controllers.push_back(controller);
        }
        SDL_JoystickClose(joystick);
        joystick = nullptr;
        virtual_ids.erase(id);
    }
};

void check_live_ps5_strength(Pad& legacy, Pad& ps5, size_t ps5_player) {
    legacy.check_type(); ps5.check_type();
    set_strengths(25.0, 25.0);
    wr64::input::set_rumble(0, true); wr64::input::set_rumble(1, true);
    for (int i = 0; i < 6; ++i) wr64::input::update_rumble();
    auto& config = recompui::config::get_general_config();
    for (double percent : {25.0, 100.0, 0.0}) {
        // No save/reload or programmatic visual-update helper: the live UI
        // setter must publish the assigned player's atomic value immediately.
        config.set_option_value(ps5_player == 0 ? "rumble_strength" : "rumble_strength_p2", percent);
        require(recompui::config::general::get_rumble_strength(ps5_player) == percent &&
            recompui::config::general::get_rumble_strength(1 - ps5_player) == 25.0,
            "Live strength edit was not independently published for the selected player");
        wr64::input::update_rumble();
        ps5.require_strength(Uint16(percent * 65535 / 100));
        legacy.require_strength(Uint16(25.0 * 65535 / 100));
    }
    std::printf("PS5 player %zu: live 25/100/0%% edits, both channels, other player unchanged passed.\n",
        ps5_player + 1);
}

void check_rumble_watchdog(Pad& a, Pad& b, Uint16 strength_a, Uint16 strength_b,
    const char* mode) {
    // SDL can suppress duplicate driver callbacks while still renewing the
    // deadline. Keep the actual envelope saturated and check its observable
    // lifetime instead of requiring one callback per identical command.
    for (const auto [cadence, interval] : std::array<std::pair<int, Uint32>, 3>{
        std::pair{30, 33u}, std::pair{60, 16u}, std::pair{120, 8u}}) {
        const auto require_strengths = [&] {
            a.require_strength(strength_a);
            b.require_strength(strength_b);
        };
        require(strength_a != 0 && strength_b != 0, "Watchdog fixture requires active motors");
        require_strengths();
        const Uint64 started = SDL_GetTicks64();
        do {
            SDL_Delay(interval);
            wr64::input::update_rumble();
            // Refresh before pumping so scheduler delays cannot falsely fail
            // a healthy sender: this checks renewal, not host scheduling.
            SDL_JoystickUpdate();
            require_strengths();
        } while (SDL_GetTicks64() - started < 120);

        const int calls_a = a.rumble_calls, calls_b = b.rumble_calls;
        // No frontend/host rumble update occurs here. SDL services virtual
        // expiration when pumped; this is not a physical hardware stall test.
        SDL_Delay(75);
        require_strengths();
        require(a.rumble_calls == calls_a && b.rumble_calls == calls_b,
            "Virtual SDL expiration unexpectedly occurred without its update pump");
        SDL_JoystickUpdate();
        require(a.last_low == 0 && b.last_low == 0 && a.last_high == 0 && b.last_high == 0 &&
            a.rumble_calls > calls_a && b.rumble_calls > calls_b,
            "SDL did not expire both motors after host rumble refreshes stopped");
        wr64::input::update_rumble();
        require_strengths();
        std::printf("Renewable rumble: %s, approximately %d Hz, stable strength and SDL expiry passed.\n",
            mode, cadence);
    }
}

void tick() {
    SDL_JoystickUpdate();
    recompinput::handle_events();
    wr64::input::poll();
}
void process_ui() {
    ui_phase = true;
    wr64::input::process_pending_ui();
    ui_phase = false;
}
struct Input { std::uint16_t buttons; float x, y; };
Input read(int player = 0) {
    Input value{};
    require(wr64::input::get(player, &value.buttons, &value.x, &value.y), "Player is not connected");
    return value;
}

void check_multiplayer(Pad& a, Pad& b) {
    auto neutral = [](int player) {
        const auto value = read(player);
        require(value.buttons == 0 && value.x == 0 && value.y == 0,
            "Unconfirmed/lost assignment leaked gameplay input");
    };
    auto host_tick = [] { tick(); process_ui(); wr64::input::update_rumble(); };
    auto key_event = [](SDL_Scancode key) {
        SDL_Event event{}; event.type = SDL_KEYDOWN; event.key.keysym.scancode = key;
        require(SDL_PushEvent(&event) == 1, "Could not inject isolated assignment key");
    };
    auto confirm = [&](bool commit = true) {
        require(recompinput::playerassignment::met_assignment_requirements(), "Two devices were not assigned");
        if (commit) recompinput::playerassignment::commit_player_assignment();
        for (auto* pad : {&a, &b}) {
            for (int button = 0; button < SDL_CONTROLLER_BUTTON_MAX; ++button)
                pad->button(SDL_GameControllerButton(button), false);
            for (int axis = 0; axis < SDL_CONTROLLER_AXIS_MAX; ++axis)
                pad->axis(SDL_GameControllerAxis(axis), axis >= SDL_CONTROLLER_AXIS_TRIGGERLEFT ? -32768 : 0);
        }
        keys.fill(0);
        host_tick();
        require(!ui_captures && !recompinput::playerassignment::is_active(),
            "Confirmed assignment kept the game blocked");
        require(recompinput::players::get_number_of_assigned_players() == 2,
            "Assignment did not commit exactly two players");
    };
    auto assign_pads = [&] {
        a.button(SDL_CONTROLLER_BUTTON_A, true); host_tick();
        b.button(SDL_CONTROLLER_BUTTON_A, true); host_tick();
        confirm();
    };
    auto reserved_p2 = [] {
        uint16_t buttons = 0x1234; float x = .25f, y = -.25f;
        require(wr64::input::get(1, &buttons, &x, &y) && buttons == 0 && x == 0 && y == 0,
            "SP return did not preserve the neutral reserved P2 port");
    };

    a.attach(); b.attach(); host_tick();
    a.check_type(); b.check_type();
    keys.fill(0);
    wr64::input::set_multiplayer_enabled(true);
    neutral(0); neutral(1); // Native request already prevents shared controls.
    host_tick();
    require(!recompinput::players::is_single_player_mode() && assignment_opens == 1 && ui_captures,
        "Native 2P request did not open assignment on the host thread");
    const int events_before_mouse = ui_event_count;
    SDL_Event mouse{}; mouse.type = SDL_MOUSEMOTION;
    require(SDL_PushEvent(&mouse) == 1, "Could not inject isolated mouse event");
    host_tick();
    require(ui_event_count > events_before_mouse, "Assignment blocked mouse access to Cancel");
    a.button(SDL_CONTROLLER_BUTTON_A, true); tick();
    require(!recompinput::players::get_player_is_assigned(0, true),
        "SDL event handling mutated the assignment before the UI callback");
    wr64::input::update_rumble();
    require(!recompinput::players::get_player_is_assigned(0, true),
        "The SDL host tick mutated assignment/UI state");
    process_ui();
    require(!recompinput::playerassignment::met_assignment_requirements(),
        "A single pad satisfied the two-player requirement");
    recompinput::playerassignment::commit_player_assignment();
    require(recompinput::playerassignment::is_active(), "Partial assignment was committed");
    neutral(0); neutral(1);
    b.button(SDL_CONTROLLER_BUTTON_A, true); host_tick();
    recompinput::playerassignment::add_keyboard_player(); // Cannot exceed the two-port limit.
    recompinput::playerassignment::commit_player_assignment();
    require(ui_captures, "Committing assignment directly mutated the modal before its queued UI close");
    wr64::input::update_rumble();
    require(ui_captures, "SDL host tick closed the assignment modal");
    process_ui(); wr64::input::update_rumble();
    require(!ui_captures, "UI callback did not close the completed assignment");
    neutral(0); neutral(1); // Held Confirm must not select or accelerate.
    confirm(false);
    require(recompinput::players::get_player(0).controller == recompinput::get_controller_from_joystick_id(a.id) &&
        recompinput::players::get_player(1).controller == recompinput::get_controller_from_joystick_id(b.id),
        "Physical controllers were not assigned in the chosen order");
    a.button(SDL_CONTROLLER_BUTTON_A, true); b.button(SDL_CONTROLLER_BUTTON_X, true);
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 26214); b.axis(SDL_CONTROLLER_AXIS_LEFTX, -19661);
    keys[SDL_SCANCODE_SPACE] = 1; keys[SDL_SCANCODE_D] = 1;
    host_tick();
    auto first = read(0), second = read(1);
    require(first.buttons == 0x8000 && second.buttons == 0x4000,
        "Controller buttons or keyboard input crossed assigned player ports");
    near(first.x, (26214.f / 32768.f - .05f) / .95f, "P1 analog included P2/keyboard input");
    near(second.x, -(19661.f / 32768.f - .05f) / .95f, "P2 analog included P1/keyboard input");
    std::array<OSContPad, 4> native_pads{};
    osContGetReadData(native_pads.data());
    require(native_pads[0].button == 0x8000 && native_pads[1].button == 0x4000 &&
        native_pads[0].stick_x > 0 && native_pads[1].stick_x < 0 &&
        native_pads[2].err_no == 8 && native_pads[3].err_no == 8,
        "Real libultra bridge did not retain independent physical port mapping from startup");
    wr64::input::set_rumble(0, true); wr64::input::update_rumble();
    require(a.last_high > 0 && b.last_high == 0, "P1 rumble reached the wrong controller");
    recompinput::reset_rumble();
    wr64::input::set_rumble(1, true); wr64::input::update_rumble();
    require(a.last_high == 0 && b.last_high > 0, "P2 rumble reached the wrong controller");
    set_strengths(70.0, 20.0);
    wr64::input::set_rumble(0, true); wr64::input::set_rumble(1, true);
    for (int i = 0; i < 6; ++i) wr64::input::update_rumble();
    require(a.last_high == uint16_t(70.0 * 65535 / 100) && b.last_high == uint16_t(20.0 * 65535 / 100),
        "Assigned motors did not apply independent player strengths");
    check_rumble_watchdog(a, b, uint16_t(70.0 * 65535 / 100), uint16_t(20.0 * 65535 / 100),
        "independent P1/P2");
    check_live_ps5_strength(a, b, 1);
    set_strengths(0.0, 80.0); wr64::input::update_rumble();
    require(a.last_high == 0 && b.last_high == uint16_t(80.0 * 65535 / 100),
        "Muting P1 or changing P2 strength affected the wrong assigned motor");
    set_strengths(40.0, 0.0); wr64::input::update_rumble();
    require(a.last_high == uint16_t(40.0 * 65535 / 100) && b.last_high == 0,
        "Muting P2 affected P1 motor strength");
    set_strengths(25.0, 25.0);

    keys.fill(0); a.button(SDL_CONTROLLER_BUTTON_A, false);
    b.detach();
    neutral(0); neutral(1); // A missing P2 suppresses P1 before the first read.
    host_tick();
    require(assignment_opens == 2 && ui_captures && a.last_high == 0,
        "Hotplug loss did not stop rumble and reopen assignment");
    b.attach(); host_tick(); assign_pads();
    b.button(SDL_CONTROLLER_BUTTON_X, true); host_tick();
    require(read(1).buttons == 0x4000, "Reconnected P2 did not use its new physical handle");
    require(a.last_high == 0 && b.last_high == 0, "A previous motor envelope migrated after reassignment");

    // Device type follows the physical controller, while the slider follows
    // its newly assigned player. Reverse the assignment through real events.
    b.button(SDL_CONTROLLER_BUTTON_X, false); host_tick();
    wr64::input::request_multiplayer_assignment(); host_tick();
    b.button(SDL_CONTROLLER_BUTTON_A, true); host_tick();
    a.button(SDL_CONTROLLER_BUTTON_A, true); host_tick(); confirm();
    require(recompinput::players::get_player(0).controller == recompinput::get_controller_from_joystick_id(b.id) &&
        recompinput::players::get_player(1).controller == recompinput::get_controller_from_joystick_id(a.id),
        "Reverse assignment did not move the PS5 endpoint to player one");
    check_live_ps5_strength(a, b, 0);
    set_strengths(25.0, 25.0);
    // The next cancellation check combines this held B with keyboard A.
    b.button(SDL_CONTROLLER_BUTTON_X, true); host_tick();

    wr64::input::request_multiplayer_assignment(); host_tick();
    key_event(SDL_SCANCODE_ESCAPE); host_tick();
    require(recompinput::playerassignment::was_cancelled() &&
        recompinput::players::is_single_player_mode() && !ui_captures,
        "Escape before assignment did not close the modal and restore SP");
    recompinput::playerassignment::commit_player_assignment();
    require(recompinput::playerassignment::was_cancelled(),
        "A stale Confirm event overrode the cancelled assignment");
    reserved_p2();
    const int cancelled_opens = assignment_opens;
    for (int i = 0; i < 4; ++i) { wr64::input::set_multiplayer_enabled(true); host_tick(); }
    require(assignment_opens == cancelled_opens, "Native 2P publication reopened a cancelled prompt");
    keys[SDL_SCANCODE_SPACE] = 1; host_tick();
    require((read().buttons & 0xC000) == 0xC000, "Cancel did not restore keyboard/all-controller aggregation");
    keys.fill(0);
    wr64::input::request_multiplayer_assignment(); host_tick();
    a.button(SDL_CONTROLLER_BUTTON_BACK, true); host_tick();
    require(recompinput::players::is_single_player_mode() && !ui_captures,
        "Controller Back could not cancel before two devices were assigned");
    a.button(SDL_CONTROLLER_BUTTON_BACK, false); host_tick();

    // A single keyboard plus a controller uses the existing SP keyboard bindings
    // on first use and removes every unused device profile from the other port.
    wr64::input::request_multiplayer_assignment(); host_tick();
    key_event(SDL_SCANCODE_SPACE); host_tick();
    a.button(SDL_CONTROLLER_BUTTON_A, true); host_tick(); confirm();
    keys[SDL_SCANCODE_SPACE] = 1; keys[SDL_SCANCODE_D] = 1;
    a.button(SDL_CONTROLLER_BUTTON_X, true); a.axis(SDL_CONTROLLER_AXIS_LEFTX, -19661);
    host_tick(); first = read(0); second = read(1);
    require(first.buttons == 0x8000 && second.buttons == 0x4000,
        "Keyboard/controller assignment did not isolate buttons");
    near(first.x, 1.f, "First-use keyboard player did not inherit the existing mapping");
    near(second.x, -(19661.f / 32768.f - .05f) / .95f, "Keyboard input leaked into the controller player");
    const int keyboard_profile = recompinput::profiles::get_input_profile_for_player(0, recompinput::InputDevice::Keyboard);
    recompinput::profiles::set_input_binding(keyboard_profile, recompinput::GameInput::A, 0,
        recompinput::InputField::keyboard(SDL_SCANCODE_Z));
    wr64::input::request_multiplayer_assignment(); host_tick();
    keys.fill(0); key_event(SDL_SCANCODE_SPACE); host_tick();
    a.button(SDL_CONTROLLER_BUTTON_A, true); host_tick(); confirm();
    keys[SDL_SCANCODE_SPACE] = 1; host_tick();
    require(read(0).buttons == 0, "Reassignment overwrote a saved/custom MP keyboard binding");
    keys[SDL_SCANCODE_SPACE] = 0; keys[SDL_SCANCODE_Z] = 1; host_tick();
    require(read(0).buttons == 0x8000, "Custom MP keyboard binding did not survive reassignment");

    wr64::input::set_multiplayer_enabled(false); host_tick();
    require(recompinput::players::is_single_player_mode() && !ui_captures,
        "Native 1P return did not restore the original input mode");
    reserved_p2();
    keys.fill(0); keys[SDL_SCANCODE_SPACE] = 1; host_tick();
    require(read().buttons & 0x8000, "MP keyboard edits changed the SP profile");
    const int opens_before_transient = assignment_opens;
    wr64::input::set_multiplayer_enabled(true);
    wr64::input::set_multiplayer_enabled(false); host_tick();
    require(assignment_opens == opens_before_transient, "A superseded native request opened a stale modal");
    keys.fill(0); a.detach(); b.detach(); host_tick();
    for (auto* controller : retired_controllers) SDL_GameControllerClose(controller);
    retired_controllers.clear();
}

void run(bool explicit_ps5_optout) {
    check_general_config();
    SDL_SetMainReady();
    // Prevent physical-controller backends from opening user devices. The open
    // provider below additionally rejects every non-virtual controller.
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI, "0");
    SDL_SetHint(SDL_HINT_JOYSTICK_RAWINPUT, "0");
    SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");
    SDL_SetHint(SDL_HINT_DIRECTINPUT_ENABLED, "0");
    SDL_SetHint("SDL_JOYSTICK_WGI", "0");
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    SDL_SetEventFilter(isolated_events, nullptr);
    if (explicit_ps5_optout) {
        require(SDL_setenv(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE, "0", 1) == 0,
            "Could not set the test process's explicit PS5 rumble opt-out");
    }
    const char* environment_hint = SDL_getenv(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE);
    const std::string expected_hint = environment_hint ? environment_hint : "1";
    wr64::input::initialize();
    const char* actual_hint = SDL_GetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE);
    require(actual_hint != nullptr && actual_hint == expected_hint,
        "PS5 enhanced-report hint default did not preserve the user's environment override");
    std::printf("Real SDL PS5 rumble hint: %s (%s) passed.\n", actual_hint,
        explicit_ps5_optout ? "explicit process opt-out preserved" : "application default/user value");
    require(wr64::input::ready() && recompinput::players::is_single_player_mode(),
        "Host did not select the Shindou single-player mode");
    ultramodern::input::set_callbacks({wr64::input::poll, wr64::input::get,
        wr64::input::set_rumble, wr64::input::get_connected_device_info});
    std::array<uint8_t, 1024> rdram{};
    uint8_t pattern = 0;
    constexpr int32_t status_address = static_cast<int32_t>(0x80000100u);
    require(osContInit(rdram.data(), 0, &pattern, status_address) == 0 && pattern == 3,
        "Real osContInit did not reserve both player ports at boot");
    const auto* statuses = reinterpret_cast<const OSContStatus*>(rdram.data() + 0x100);
    require(statuses[0].err_no == 0 && statuses[1].err_no == 0 &&
        statuses[2].err_no == 8 && statuses[3].err_no == 8,
        "Native startup status could alias or expose the wrong physical ports");
    std::array<OSContPad, 4> startup_pads{};
    osContGetReadData(startup_pads.data());
    require(startup_pads[1].err_no == 0 && startup_pads[1].button == 0 &&
        startup_pads[1].stick_x == 0 && startup_pads[1].stick_y == 0,
        "SP P2 was not neutral through the actual libultra bridge");
    // Mirrors config::finalize's defaults load, with isolated in-memory JSON.
    require(!recompinput::profiles::load_controls_config("virtual-controls"), "Unexpected user settings");
    tick();
    Input value = read();
    require(value.buttons == 0 && value.x == 0 && value.y == 0, "Initial state was not neutral");
    require(wr64::editions::controls_released(), "Neutral input did not release the launcher barrier");

    Pad a{"WR64 test legacy pad"}, b{"WR64 test DualSense", true};
    a.attach(); b.attach(); tick();
    a.check_type(); b.check_type();
    require(open_count == 2, "Actual hotplug event path did not open both virtual pads");
    require(!recompinput::players::get_player_is_assigned(0), "SP test unexpectedly needed assignment");
    a.button(SDL_CONTROLLER_BUTTON_A, true);
    b.button(SDL_CONTROLLER_BUTTON_X, true);
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 26214); // approximately +.8
    b.axis(SDL_CONTROLLER_AXIS_LEFTX, -19661); // approximately -.6
    tick(); value = read();
    require((value.buttons & 0xC000) == 0xC000, "Two-pad button OR aggregation failed");
    near(value.x, ((26214.0F - 19661.0F) / 32768.0F - .05F) / .95F,
        "Signed half-axis aggregation/deadzone differs from Shindou");
    require(ui_event_count > 0, "Actual event code did not forward virtual events to UI");
    require(!wr64::editions::controls_released(), "Held virtual buttons/stick bypassed the launcher barrier");

    std::uint16_t p2_buttons = 0x1234; float p2_x = .25F, p2_y = -.25F;
    require(wr64::input::get(1, &p2_buttons, &p2_x, &p2_y) &&
        p2_buttons == 0 && p2_x == 0 && p2_y == 0, "Reserved SP P2 was not neutral");

    // Active general settings feed the real per-axis deadzone routine.
    general_config->update_option_value("joystick_deadzone", 25.0);
    value = read(); near(value.x, 0, "Live deadzone change was not applied");
    general_config->update_option_value("joystick_deadzone", 5.0);
    keys[SDL_SCANCODE_SPACE] = 1; keys[SDL_SCANCODE_D] = 1;
    tick(); value = read();
    require(value.buttons & 0x8000, "Keyboard A mapping was not read");
    near(value.x, 1.0F, "Keyboard plus controller clamp failed");
    ui_captures = true; value = read();
    require(value.buttons == 0 && value.x == 0 && value.y == 0, "UI capture did not suppress all game input");
    ui_captures = false; keys.fill(0);

    // Actual profiles: save/reload a changed button mapping through JSON.
    int profile = recompinput::profiles::get_sp_controller_profile_index();
    const auto previous = recompinput::profiles::get_input_binding(profile, recompinput::GameInput::A, 0);
    recompinput::profiles::set_input_binding(profile, recompinput::GameInput::A, 0,
        recompinput::InputField::controller_digital(SDL_CONTROLLER_BUTTON_Y));
    require(recompinput::profiles::save_controls_config("virtual-controls"), "Profile serialization failed");
    recompinput::profiles::set_input_binding(profile, recompinput::GameInput::A, 0, previous);
    require(recompinput::profiles::load_controls_config("virtual-controls"), "Profile reload failed");
    tick(); value = read();
    require(!(value.buttons & 0x8000), "Persisted remap was not restored");
    a.button(SDL_CONTROLLER_BUTTON_Y, true); tick(); value = read();
    require(value.buttons & 0x8000, "Restored mapping did not drive actual virtual input");

    // Run the actual envelope into SDL's virtual Rumble callback on both pads.
    wr64::input::set_rumble(0, true);
    for (int i = 0; i < 6; ++i) wr64::input::update_rumble();
    require(a.rumble_calls > 0 && b.rumble_calls > 0 && a.last_high > 0 && b.last_high > 0,
        "SP rumble did not reach both virtual pads");
    a.require_strength(Uint16(25.0 * 65535 / 100));
    b.require_strength(Uint16(25.0 * 65535 / 100));
    require(a.last_high == static_cast<Uint16>(25 * 0xFFFF / 100), "Rumble strength setting was ignored");
    set_strengths(40.0, 90.0); wr64::input::update_rumble();
    require(a.last_high == uint16_t(40.0 * 65535 / 100) && b.last_high == a.last_high,
        "P2 strength changed single-player controller aggregation");
    check_rumble_watchdog(a, b, uint16_t(40.0 * 65535 / 100), uint16_t(40.0 * 65535 / 100),
        "single-player aggregation");
    set_strengths(25.0, 25.0);
    wr64::input::set_rumble(0, false);
    for (int i = 0; i < 80; ++i) wr64::input::update_rumble();
    require(a.last_high == 0 && b.last_high == 0, "Rumble decay did not stop virtual motors");

    // The shared launcher keeps pumping SDL behind its child process. With
    // background events enabled, real virtual-pad presses and releases must
    // update device state without queuing hidden-menu actions or cursor work.
    tick();
    const int queued_before_suspend = ui_event_count;
    const int cursor_before_suspend = cursor_queries;
    const int fullscreen_before_suspend = fullscreen_toggles;
    const int drops_before_suspend = drop_batches;
    const int opens_before_suspend = open_count;
    ui_suspended = true;
    a.button(SDL_CONTROLLER_BUTTON_A, false);
    a.button(SDL_CONTROLLER_BUTTON_Y, false);
    b.button(SDL_CONTROLLER_BUTTON_X, false);
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, -32768);
    b.axis(SDL_CONTROLLER_AXIS_LEFTX, 0);
    tick();
    a.button(SDL_CONTROLLER_BUTTON_A, true);
    a.button(SDL_CONTROLLER_BUTTON_Y, true);
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 32767);
    tick();
    require(ui_event_count == queued_before_suspend,
        "Suspended controller buttons/releases/axes reached the hidden UI");
    b.detach();
    require(recompinput::get_controller_from_joystick_id(b.id) == nullptr,
        "Suspension lost the actual device-remove event");
    b.attach(); tick();
    require(open_count == opens_before_suspend + 1 &&
        recompinput::get_controller_from_joystick_id(b.id) != nullptr,
        "Suspension lost the actual device-add event");

    auto push = [](SDL_Event event) {
        require(SDL_PushEvent(&event) == 1, "Could not enqueue a regression action");
    };
    SDL_Event action{};
    action.type = SDL_KEYDOWN;
    action.key.keysym.scancode = SDL_SCANCODE_F11;
    action.key.keysym.sym = SDLK_F11;
    push(action);
    action.type = SDL_KEYUP; push(action);
    action = {}; action.type = SDL_TEXTINPUT; action.text.text[0] = 'a'; push(action);
    action = {}; action.type = SDL_MOUSEMOTION; action.motion.xrel = 12; push(action);
    action = {}; action.type = SDL_MOUSEBUTTONDOWN; action.button.button = SDL_BUTTON_LEFT; push(action);
    action.type = SDL_MOUSEBUTTONUP; push(action);
    action = {}; action.type = SDL_MOUSEWHEEL; action.wheel.y = 1; push(action);
    action = {}; action.type = SDL_DROPBEGIN; push(action);
    for (const Uint32 kind : {Uint32(SDL_DROPFILE), Uint32(SDL_DROPTEXT)}) {
        action = {}; action.type = kind;
        action.drop.file = SDL_strdup("synthetic-launcher-suspension-drop");
        require(action.drop.file != nullptr, "Could not allocate test drop payload");
        queued_drop_allocations.insert(action.drop.file);
        push(action);
    }
    action = {}; action.type = SDL_DROPCOMPLETE; push(action);
    tick();
    require(ui_event_count == queued_before_suspend,
        "Suspended keyboard/mouse/text actions reached the hidden UI");
    require(fullscreen_toggles == fullscreen_before_suspend && drop_batches == drops_before_suspend,
        "Suspension still invoked fullscreen or file-drop actions");
    require(queued_drop_allocations.empty() && freed_test_drops == 2,
        "Suspended drop payloads were not released exactly once");
    require(cursor_queries == cursor_before_suspend,
        "Suspended event pumping still attempted cursor visibility/capture updates");

    // Discard releases during suspension too. The first deliberate fresh press
    // after resuming must immediately navigate the launcher normally again.
    a.button(SDL_CONTROLLER_BUTTON_A, false);
    a.button(SDL_CONTROLLER_BUTTON_Y, false);
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 0);
    tick();
    require(wr64::editions::controls_released(), "Released virtual controls kept the launcher blocked");
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 2000); tick();
    require(wr64::editions::controls_released(), "Minor stick drift blocked launcher recovery");
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 25000); tick();
    require(!wr64::editions::controls_released(), "Held stick bypassed the launcher barrier");
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 0);
    a.axis(SDL_CONTROLLER_AXIS_TRIGGERLEFT, 32767); tick();
    require(!wr64::editions::controls_released(), "Held trigger bypassed the launcher barrier");
    a.axis(SDL_CONTROLLER_AXIS_TRIGGERLEFT, -32768); tick();
    require(wr64::editions::controls_released(), "Released trigger kept the launcher blocked");
    keys[SDL_SCANCODE_SPACE] = 1;
    require(!wr64::editions::controls_released(), "Held keyboard key bypassed the launcher barrier");
    keys.fill(0);
    b.button(SDL_CONTROLLER_BUTTON_START, true); tick();
    require(!wr64::editions::controls_released(), "Newly attached held pad bypassed the launcher barrier");
    b.detach(); tick();
    require(wr64::editions::controls_released(), "Removed held pad kept the launcher blocked");
    b.attach(); tick();
    require(wr64::editions::controls_released(), "Neutral reconnect blocked launcher recovery");
    require(ui_event_count == queued_before_suspend && cursor_queries == cursor_before_suspend,
        "Release-barrier hotplug generated suspended menu or cursor work");
    ui_suspended = false;
    tick();
    require(ui_event_count == queued_before_suspend,
        "Suspended actions leaked into the UI after resuming");
    a.button(SDL_CONTROLLER_BUTTON_Y, true); tick();
    require(ui_event_count > queued_before_suspend && cursor_queries > cursor_before_suspend,
        "Fresh controller input did not resume after suspension");
    action = {}; action.type = SDL_KEYDOWN;
    action.key.keysym.scancode = SDL_SCANCODE_F11;
    action.key.keysym.sym = SDLK_F11; push(action); tick();
    require(fullscreen_toggles == fullscreen_before_suspend + 1,
        "Fresh keyboard action did not resume after suspension");
    a.button(SDL_CONTROLLER_BUTTON_A, true);
    b.button(SDL_CONTROLLER_BUTTON_X, true);
    a.axis(SDL_CONTROLLER_AXIS_LEFTX, 26214);
    b.axis(SDL_CONTROLLER_AXIS_LEFTX, -19661);
    tick();

    b.detach(); tick(); value = read();
    require(!(value.buttons & 0x4000), "Removed pad still contributed button B");
    near(value.x, (26214.0F / 32768.0F - .05F) / .95F, "Removed pad still contributed axis input");
    b.attach(); b.button(SDL_CONTROLLER_BUTTON_X, true); tick(); value = read();
    require(value.buttons & 0x4000, "Reconnected virtual pad did not resume P1 input");
    require(open_count == 5, "Reconnect did not traverse the actual hotplug open path");
    a.detach(); b.detach(); tick(); value = read();
    require(value.buttons == 0 && value.x == 0 && value.y == 0, "All-pad disconnect was not neutral");
    keys[SDL_SCANCODE_SPACE] = 1; tick(); value = read();
    require(value.buttons == 0x8000, "Keyboard-only P1 failed after disconnect");
    keys.fill(0);
    check_multiplayer(a, b);
    wr64::input::shutdown(); SDL_Quit();
}
}

void wr64_test_free(void* memory) {
    if (queued_drop_allocations.erase(memory)) ++freed_test_drops;
    SDL_free(memory);
}
const Uint8* wr64_test_keyboard_state(int* count) { *count = keys.size(); return keys.data(); }
SDL_Keymod wr64_test_keymod_state() { return modifiers; }
SDL_GameController* wr64_test_open_virtual_controller(int index) {
    require(SDL_JoystickIsVirtual(index), "Attempt to open a physical controller was blocked");
    ++open_count;
    return SDL_GameControllerOpen(index);
}
namespace recomp {
std::filesystem::path get_config_path() { return "wr64-no-user-settings"; }
const Version& get_project_version() { static Version version; return version; }
}
namespace ultramodern {
std::chrono::steady_clock::duration time_since_start() { return std::chrono::steady_clock::now().time_since_epoch(); }
bool is_game_started() { return true; }
void quit() { throw std::runtime_error("Unexpected quit event"); }
void send_si_message() {}
}
namespace recompui {
ConfigPageControls* controls_page = nullptr;
void ConfigPageControls::force_update() { require(ui_phase, "Controls refresh escaped the UI callback"); }
void AssignPlayersModal::open() {
    require(ui_phase, "Assignment modal opened outside the UI callback");
    ++assignment_opens; ui_captures = true;
}
void AssignPlayersModal::close() {
    require(ui_phase, "Assignment modal closed outside the UI callback");
    ui_captures = false;
}
bool is_context_capturing_input() { return ui_captures; }
bool is_input_suspended() { return ui_suspended; }
void queue_event(const SDL_Event&) { ++ui_event_count; }
void open_quit_game_prompt() {}
void activate_mouse() {}
bool get_cursor_visible() { ++cursor_queries; return true; }
void process_game_started() {}
void drop_files(const std::list<std::filesystem::path>&) { ++drop_batches; }
namespace config {
recomp::config::Config& create_config_tab(const std::string& name, const std::string& id, bool confirm) {
    require(id == "general", "Unexpected UI config in the isolated controller test");
    general_config = std::make_unique<recomp::config::Config>(name, id, confirm);
    return *general_config;
}
recomp::config::Config& get_config(const std::string& id) {
    require(id == "general" && general_config != nullptr, "General config is not initialized");
    return *general_config;
}
namespace graphics { void toggle_fullscreen() { ++fullscreen_toggles; } }
}
}
namespace recompinput {
bool read_json_with_backups(const std::filesystem::path& path, nlohmann::json& out) {
    auto found = config_storage.find(path);
    if (found == config_storage.end()) return false;
    out = nlohmann::json::parse(found->second);
    return true;
}
bool save_json_with_backups(const std::filesystem::path& path, const nlohmann::json& data) {
    config_storage[path] = data.dump();
    return true;
}
}
int main(int argc, char** argv) {
    try {
        run(argc == 2 && std::string(argv[1]) == "--ps5-rumble-disabled");
        std::puts("Actual RecompFrontend + SDL virtual controller integration passed.");
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "Virtual controller integration failed: %s\n", error.what());
        return 1;
    }
}
