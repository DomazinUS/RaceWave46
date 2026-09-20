#pragma once
// Keyboard acquisition and controller-open safety are redirected. Drop frees
// are counted before forwarding to SDL. Virtual input and frontend logic stay real.
#include <SDL.h>
#include <filesystem>
#include <list>
#include <chrono>
#include <algorithm>
#include <cmath>
const Uint8* wr64_test_keyboard_state(int* count);
SDL_Keymod wr64_test_keymod_state();
SDL_GameController* wr64_test_open_virtual_controller(int index);
void wr64_test_free(void* memory);
#define SDL_GetKeyboardState wr64_test_keyboard_state
#define SDL_GetModState wr64_test_keymod_state
#define SDL_GameControllerOpen wr64_test_open_virtual_controller
#define SDL_free wr64_test_free
