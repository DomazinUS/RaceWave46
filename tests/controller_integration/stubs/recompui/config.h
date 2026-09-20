#pragma once
#include <SDL.h>
#include <filesystem>
#include <list>
#include "../../../../lib/RecompFrontend/recompui/include/recompui/config.h"
namespace recompui {
bool is_context_capturing_input();
bool is_input_suspended();
void queue_event(const SDL_Event& event);
void open_quit_game_prompt();
void activate_mouse();
bool get_cursor_visible();
void process_game_started();
void drop_files(const std::list<std::filesystem::path>& files);
namespace config {
namespace graphics { void toggle_fullscreen(); }
}
}
