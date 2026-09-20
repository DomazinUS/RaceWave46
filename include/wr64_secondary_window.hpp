#pragma once

namespace wr64::window {
// Call on the primary window's UI thread. Player 2's HWND stays alive until
// process exit so a concurrent renderer can never retain a destroyed handle.
void update_secondary_window(void* primary_handle);
}
