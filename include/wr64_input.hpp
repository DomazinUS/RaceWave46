#pragma once

#include "ultramodern/input.hpp"

namespace wr64::input {

// Must run BEFORE recomp::start. Matches Shindou's shared single-player
// keyboard/controller profiles, SDL device handling and virtual accessory.
// Both virtual ports are reserved at boot; SP reads on port two stay neutral.
void initialize();

// Writes the bindings back to disk. Safe to call more than once.
void shutdown();

// True once initialize() has succeeded. When false every callback below
// behaves as if nothing is plugged in, rather than reaching into an
// uninitialised recompinput.
bool ready();

// Called from the host event loop, like Shindou's update_gfx callback.
void update_rumble();

// Native game thread publishes the selected player count without touching SDL/UI.
// The UI frame callback applies transitions and opens the normal assignment modal.
void set_multiplayer_enabled(bool enabled);
bool multiplayer_requested();
// Retry assignment from Controls after cancelling a native two-player request.
void request_multiplayer_assignment();
// Call under the owning UI frame callback, after checking input suspension.
// This never waits for the native-input mutex while holding the UI mutex.
void process_pending_ui();

// ---- ultramodern::input::callbacks_t ------------------------------------
void poll();
bool get(int controller, uint16_t* buttons, float* x, float* y);
void set_rumble(int controller, bool enabled);
ultramodern::input::connected_device_info_t get_connected_device_info(int controller);

} // namespace wr64::input
