#pragma once
#include <cstdint>
#include <filesystem>
#include "recompinput.h"
namespace recompinput::profiles {
void initialize_input_bindings();
bool load_controls_config(const std::filesystem::path& path);
bool save_controls_config(const std::filesystem::path& path);
bool get_n64_input(int controller, std::uint16_t* buttons, float* x, float* y);
int get_input_profile_by_key(const std::string& key);
std::string get_mp_keyboard_profile_key(int player);
void set_input_profile_for_player(int player, int profile, InputDevice device);
int get_input_profile_for_player(int player, InputDevice device);
int get_sp_keyboard_profile_index();
void set_input_binding(int profile, GameInput input, size_t binding, InputField value);
InputField& get_input_binding(int profile, GameInput input, size_t binding);
}
