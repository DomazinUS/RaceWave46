#pragma once

namespace wr64::achievements_ui {
// Register before recompui::config::finalize(). Creates content lazily through
// the native settings tab lifecycle; no account or network state lives here.
void register_tab();
// Call from the existing UI render-thread frame callback, including gameplay.
void update();
}
