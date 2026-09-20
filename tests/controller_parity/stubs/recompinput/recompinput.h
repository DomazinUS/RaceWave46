#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include "SDL.h"
namespace recompinput {
enum class GameInput { A, B, START, COUNT };
enum class InputDevice { Controller, Keyboard };
struct InputField { int input_id = 0; };
struct Player { SDL_GameController* controller = nullptr; bool keyboard_enabled = false; };
constexpr size_t num_bindings_per_input = 2;
void poll_inputs();
void update_rumble();
void reset_rumble();
void set_rumble(int controller, bool enabled);
void set_game_input_description(GameInput input, const char* description);
namespace players {
void set_single_player_mode(bool enabled);
bool is_single_player_mode();
void set_player_count_range(std::size_t minimum, std::size_t maximum);
bool get_player_is_assigned(int controller);
const Player& get_player(int controller);
size_t get_number_of_assigned_players();
}
namespace playerassignment {
void start();
void stop();
bool was_cancelled();
bool is_active();
void process_pending_ui();
}
}
