#pragma once

#include "SDL.h"
#include "chrono"

namespace recompinput {
    constexpr size_t max_num_players_supported = 128;
    constexpr size_t num_bindings_per_input = 2;
    inline const std::string unknown_device_input = "UNKNOWN";
    constexpr float axis_digital_threshold = 0.5f;
}

#include "input_types.h"
#include "input_mapping.h"
#include "players.h"
#include "input_state.h"
#include "promptfont.h"
