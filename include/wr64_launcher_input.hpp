#pragma once

#include <cmath>
#include "SDL.h"

namespace wr64::editions {
// Called on the SDL event thread after pumping. A held game button must be
// released before the selector can accept a new action after the child exits.
inline bool controls_released() {
    int key_count = 0;
    const Uint8* keys = SDL_GetKeyboardState(&key_count);
    for (int key = 0; key < key_count; ++key) if (keys[key]) return false;
    if (SDL_GetMouseState(nullptr, nullptr) != 0) return false;
    for (int index = 0; index < SDL_NumJoysticks(); ++index) {
        auto* controller = SDL_GameControllerFromInstanceID(SDL_JoystickGetDeviceInstanceID(index));
        if (!controller || !SDL_GameControllerGetAttached(controller)) continue;
        for (int button = 0; button < SDL_CONTROLLER_BUTTON_MAX; ++button) {
            if (SDL_GameControllerGetButton(controller, SDL_GameControllerButton(button))) return false;
        }
        for (int axis = 0; axis < SDL_CONTROLLER_AXIS_MAX; ++axis) {
            if (std::abs(int(SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis(axis)))) > 8192)
                return false;
        }
    }
    return true;
}
}
