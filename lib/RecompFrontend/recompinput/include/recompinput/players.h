#ifndef __RECOMP_INPUT_PLAYER_ASSIGNMENT_H__
#define __RECOMP_INPUT_PLAYER_ASSIGNMENT_H__

#include "recompinput.h"

namespace recompinput {
    struct Player {
        SDL_GameController* controller = nullptr;
        bool keyboard_enabled = false;
        std::chrono::high_resolution_clock::duration last_button_press_timestamp = std::chrono::high_resolution_clock::duration::zero();

        Player() : controller(nullptr), keyboard_enabled(false), last_button_press_timestamp(std::chrono::high_resolution_clock::duration::zero()) {};

        void button_pressed();
    };

    namespace players {
        size_t get_number_of_assigned_players();
        size_t get_max_number_of_players();
        bool is_single_player_mode();
        void set_single_player_mode(bool single_player);
        void set_min_number_of_players(size_t min_players);
        void set_max_number_of_players(size_t max_players);
        void set_player_count_range(size_t min_players, size_t max_players);
        const Player& get_player(int player_index, bool temp_player = false);
        bool get_player_is_assigned(int player_index, bool temp_player = false);
        bool has_enough_players_assigned();
        InputDevice get_player_input_device(int player_index, bool temp_player = false);
    }

    namespace playerassignment {
        bool is_active();
        void start();
        void stop();
        void stop_and_close_modal();
        void cancel_and_close_modal();
        bool was_cancelled();
        // Apply queued device presses and close requests on the owning UI thread.
        void process_pending_ui();
        void commit_player_assignment();
        void add_keyboard_player();
        bool met_assignment_requirements();
        bool is_blocking_input();
        bool is_player_currently_assigning(int player_index);
        bool was_keyboard_assigned();
        std::chrono::steady_clock::duration get_player_time_since_last_button_press(int player_index);

        void process_sdl_event(SDL_Event* event);
    }
}

#endif // __RECOMP_INPUT_PLAYER_ASSIGNMENT_H__
