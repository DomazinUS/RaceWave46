#pragma once

namespace wr64::composer {

void initialize(void* game_window);
void update();
void toggle();
void shutdown();
bool keyboard_captured();
void wait_if_frozen();

} // namespace wr64::composer
