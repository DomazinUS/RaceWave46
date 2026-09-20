#pragma once
#include <chrono>
namespace ultramodern {
std::chrono::steady_clock::duration time_since_start();
bool is_game_started();
void quit();
void send_si_message();
void measure_input_latency();
}
