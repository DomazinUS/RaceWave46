#pragma once

#include "json/json.hpp"

namespace wr64::editions {
inline void merge_general_input_settings(const nlohmann::json& source,
    nlohmann::json& destination, bool usa) {
    for (const char* key : {"rumble_strength", "joystick_deadzone", "background_input_mode"}) {
        if (source.contains(key)) destination[key] = source.at(key);
    }
    // Shindou retains its current single-player strength and must not overwrite
    // the USA-only P2 setting when its shared settings return to the launcher.
    if (usa && source.contains("rumble_strength_p2")) {
        destination["rumble_strength_p2"] = source.at("rumble_strength_p2");
    }
}
}
