#include "recompinput/recompinput.h"
#include "recompinput/players.h"
#include "recompinput/profiles.h"
#include "recompinput/input_events.h"
#include "ultramodern/ultramodern.hpp"
#include "composites/ui_assign_players_modal.h"
#include "config/ui_config_page_controls.h"
#include <atomic>
#include <mutex>
#include <vector>

namespace recompinput {

void Player::button_pressed() {
    last_button_press_timestamp = ultramodern::time_since_start();
}

using players_array = std::array<Player, max_num_players_supported>;
class PlayerArray : public players_array {
private:
    std::atomic_size_t count = 0;
public:
    PlayerArray() : players_array{}, count(0) {}
    PlayerArray(const PlayerArray& other) : players_array(other), count(other.get_count()) {}
    PlayerArray& operator=(const PlayerArray& other) {
        players_array::operator=(other);
        count.store(other.get_count());
        return *this;
    }

    size_t get_count() const {
        return count;
    }

    void add_keyboard_player() {
        if (count < max_num_players_supported) {
            Player &player = (*this)[count++];
            player = Player();
            player.keyboard_enabled = true;
            player.button_pressed();
        }
    }

    void add_controller_player(SDL_GameController* controller) {
        if (count < max_num_players_supported) {
            Player &player = (*this)[count++];
            player = Player();
            player.controller = controller;
            player.button_pressed();
        }
    }

    bool player_is_assigned(int player_index) const {
        return player_index >= 0 && player_index < max_num_players_supported && player_index < count;
    }
};

static struct {
    std::atomic_bool single_player_mode = false;
    std::atomic_bool is_assigning = false;
    std::atomic_bool assignment_cancelled = false;
    std::atomic_size_t min_players = 1;
    std::atomic_size_t max_players = 4;
    PlayerArray players;
    PlayerArray temp_players;

    PlayerArray& get_player_array(bool temp) {
        return temp ? temp_players : players;
    }

    std::atomic_bool queue_close_player_assignment_modal = false;
    std::mutex events_mutex;
    std::vector<SDL_Event> pending_events;
} PlayerState;

size_t players::get_number_of_assigned_players() {
    return PlayerState.players.get_count();
}

size_t players::get_max_number_of_players() {
    if (PlayerState.single_player_mode) {
        return 1;
    }
    return PlayerState.max_players;
}

bool players::is_single_player_mode() {
    return PlayerState.single_player_mode;
}

void players::set_single_player_mode(bool single_player) {
    if (!single_player && single_player != PlayerState.single_player_mode) {
        purge_deferred_controller_profiles();
    }

    PlayerState.single_player_mode = single_player;
}

void players::set_min_number_of_players(size_t min_players) {
    assert(min_players >= 1 && min_players <= PlayerState.max_players);
    PlayerState.min_players = min_players;
}

void players::set_max_number_of_players(size_t max_players) {
    assert(max_players >= PlayerState.min_players && max_players <= recompinput::max_num_players_supported);
    PlayerState.max_players = max_players;
}

void players::set_player_count_range(size_t min_players, size_t max_players) {
    assert(min_players >= 1 && max_players <= recompinput::max_num_players_supported && min_players <= max_players);
    PlayerState.min_players = min_players;
    PlayerState.max_players = max_players;
}

const recompinput::Player& players::get_player(int player_index, bool temp_player) {
    return PlayerState.get_player_array(temp_player)[player_index];
}

bool players::get_player_is_assigned(int player_index, bool temp_player) {
    return PlayerState.get_player_array(temp_player).player_is_assigned(player_index);
}

bool players::has_enough_players_assigned() {
    return PlayerState.players.get_count() >= PlayerState.min_players;
}

InputDevice players::get_player_input_device(int player_index, bool temp_player) {
    auto player_array = PlayerState.get_player_array(temp_player);
    if (!player_array.player_is_assigned(player_index)) {
        return InputDevice::COUNT;
    }

    const auto& assigned_player = player_array[player_index];
    if (assigned_player.controller != nullptr) {
        return InputDevice::Controller;
    } else if (assigned_player.keyboard_enabled) {
        return InputDevice::Keyboard;
    } else {
        return InputDevice::COUNT;
    }
}

// playerassignment start

bool playerassignment::is_active() {
    return PlayerState.is_assigning;
}

void playerassignment::start(void) {
    std::lock_guard lock{PlayerState.events_mutex};
    PlayerState.pending_events.clear();
    PlayerState.assignment_cancelled = false;
    PlayerState.queue_close_player_assignment_modal = false;
    PlayerState.temp_players = PlayerArray{};
    PlayerState.is_assigning = true;
}

void playerassignment::stop(void) {
    PlayerState.is_assigning = false;
}

void playerassignment::stop_and_close_modal() {
    playerassignment::stop();
    PlayerState.queue_close_player_assignment_modal = true;
}

void playerassignment::cancel_and_close_modal() {
    PlayerState.assignment_cancelled = true;
    stop_and_close_modal();
}

bool playerassignment::was_cancelled() {
    return PlayerState.assignment_cancelled;
}

void playerassignment::commit_player_assignment() {
    if (!is_active() || !met_assignment_requirements() ||
        PlayerState.temp_players.get_count() > PlayerState.max_players) return;
    PlayerState.assignment_cancelled = false;
    PlayerState.players = PlayerState.temp_players;
    for (int i = 0; i < players::get_number_of_assigned_players(); i++) {
        Player &player = PlayerState.players[i];
        if (player.controller != nullptr) {
            int cont_profile_index = profiles::get_controller_profile_index_from_sdl_controller(player.controller);
            if (cont_profile_index >= 0) {
                profiles::set_input_profile_for_player(i, cont_profile_index, InputDevice::Controller);
            }
        } else {
            profiles::set_input_profile_for_player(i, profiles::get_or_create_mp_keyboard_profile_index(i), InputDevice::Keyboard);
        }
    }
    // Publish completion only after devices and their profiles are committed.
    stop_and_close_modal();
}

void playerassignment::add_keyboard_player() {
    if (PlayerState.temp_players.get_count() < PlayerState.max_players) {
        PlayerState.temp_players.add_keyboard_player();
    }
}

bool playerassignment::met_assignment_requirements() {
    return PlayerState.temp_players.get_count() >= PlayerState.min_players;
}

bool playerassignment::is_blocking_input() {
    return playerassignment::is_active() && !playerassignment::met_assignment_requirements();
}

bool playerassignment::is_player_currently_assigning(int player_index) {
    return playerassignment::is_active() && player_index == (int)(PlayerState.temp_players.get_count());
}

bool playerassignment::was_keyboard_assigned() {
    size_t num_temp = PlayerState.temp_players.size();
    if (num_temp == 0) {
        return false;
    }

    for (size_t i = 0; i < num_temp; i++) {
        if (PlayerState.temp_players[i].keyboard_enabled) {
            return true;
        }
    }

    return false;
}

std::chrono::steady_clock::duration playerassignment::get_player_time_since_last_button_press(int player_index) {
    if (!PlayerState.temp_players.player_is_assigned(player_index)) {
        return std::chrono::steady_clock::duration::zero();
    }
    return ultramodern::time_since_start() - PlayerState.temp_players[player_index].last_button_press_timestamp;
}

static void process_assignment_event(SDL_Event* event) {
    if (!playerassignment::is_active()) {
        return;
    }

    switch (event->type) {
    case SDL_EventType::SDL_KEYDOWN: {
        SDL_KeyboardEvent* keyevent = &event->key;

        switch (keyevent->keysym.scancode) {
        case SDL_Scancode::SDL_SCANCODE_ESCAPE:
            playerassignment::cancel_and_close_modal();
            return;
        case SDL_Scancode::SDL_SCANCODE_RIGHT:
        case SDL_Scancode::SDL_SCANCODE_LEFT:
        case SDL_Scancode::SDL_SCANCODE_UP:
        case SDL_Scancode::SDL_SCANCODE_DOWN:
            break;
        default:
            if (playerassignment::was_keyboard_assigned()) {
                for (size_t i = 0; i < PlayerState.temp_players.size(); i++) {
                    if (PlayerState.temp_players[i].keyboard_enabled && PlayerState.temp_players[i].controller == nullptr) {
                        PlayerState.temp_players[i].button_pressed();
                    }
                }
            } else {
                playerassignment::add_keyboard_player();
            }
            break;
        }
        break;
    }
    case SDL_EventType::SDL_CONTROLLERBUTTONDOWN: {
        SDL_ControllerButtonEvent* button_event = &event->cbutton;
        SDL_JoystickID joystick_id = button_event->which;
        auto controller = recompinput::get_controller_from_joystick_id(joystick_id);
        if (controller == nullptr || !SDL_GameControllerGetAttached(controller)) break;
        if (button_event->button == SDL_CONTROLLER_BUTTON_BACK) {
            playerassignment::cancel_and_close_modal();
            break;
        }

        bool can_be_mapped = true;
        for (size_t i = 0; i < PlayerState.temp_players.size(); i++) {
            if (PlayerState.temp_players[i].controller == controller) {
                can_be_mapped = false;
                PlayerState.temp_players[i].button_pressed();
                break;
            }
        }

        if (can_be_mapped && PlayerState.temp_players.get_count() < PlayerState.max_players) {
            PlayerState.temp_players.add_controller_player(controller);
        }

        break;
    }
    }
}

void playerassignment::process_sdl_event(SDL_Event* event) {
    if (!PlayerState.is_assigning ||
        (event->type != SDL_KEYDOWN && event->type != SDL_CONTROLLERBUTTONDOWN)) return;
    std::lock_guard lock{PlayerState.events_mutex};
    if (PlayerState.is_assigning) PlayerState.pending_events.push_back(*event);
}

void playerassignment::process_pending_ui() {
    if (!players::is_single_player_mode()) purge_deferred_controller_profiles();
    if (PlayerState.queue_close_player_assignment_modal.exchange(false)) {
        recompui::AssignPlayersModal::close();
        if (recompui::controls_page != nullptr) recompui::controls_page->force_update();
    }
    std::vector<SDL_Event> events;
    {
        std::lock_guard lock{PlayerState.events_mutex};
        events.swap(PlayerState.pending_events);
    }
    for (auto& event : events) process_assignment_event(&event);
}
// player assignment end

}
