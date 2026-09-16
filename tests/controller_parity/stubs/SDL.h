#pragma once
#include <cstdint>
constexpr std::uint32_t SDL_INIT_GAMECONTROLLER = 0x00002000U;
constexpr std::uint32_t SDL_INIT_EVENTS = 0x00004000U;
int SDL_Init(std::uint32_t flags);
int SDL_InitSubSystem(std::uint32_t flags);
enum SDL_HintPriority { SDL_HINT_DEFAULT, SDL_HINT_NORMAL, SDL_HINT_OVERRIDE };
inline constexpr const char* SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE = "SDL_JOYSTICK_HIDAPI_PS5_RUMBLE";
int SDL_SetHintWithPriority(const char* name, const char* value, SDL_HintPriority priority);
const char* SDL_GetError();
struct SDL_GameController { bool attached = true; };
constexpr int SDL_TRUE = 1;
int SDL_GameControllerGetAttached(SDL_GameController* controller);
