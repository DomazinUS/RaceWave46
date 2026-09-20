#pragma once

#include "librecomp/config.hpp"

namespace wr64::frontend {

// These controls now live in General. Preserve an explicit General choice and
// import the former Enhancements value only when no valid choice exists yet.
inline bool load_general_gameplay_settings(recomp::config::Config& general,
    const nlohmann::json& legacy) {
    const auto copy_legacy_choices = [&](nlohmann::json& profile) {
        bool changed = false;
        for (const char* key : {"gameplay_rumble", "show_ghost"}) {
            const auto current = profile.find(key);
            if (current != profile.end() && current->is_boolean()) continue;
            const auto previous = legacy.find(key);
            if (previous != legacy.end() && previous->is_boolean()) {
                profile[key] = *previous;
                changed = true;
            }
        }
        return changed;
    };

    bool found_profile = false;
    bool changed = false;
    nlohmann::json migrated;
    if (!general.load_config([&](nlohmann::json& profile) {
        found_profile = true;
        if (!profile.is_object()) return false;
        changed = copy_legacy_choices(profile);
        if (changed) migrated = profile;
        return true;
    })) return false;

    if (found_profile) {
        // Keep unrelated JSON exactly as loaded, including backup recovery.
        return !changed || general.save_config_json(migrated);
    }

    // A missing profile skips Config's validator and loads schema defaults.
    // Import the two legacy choices explicitly, then verify the final save;
    // Config's automatic default save does not report a write failure.
    migrated = general.get_json_config();
    for (const char* key : {"gameplay_rumble", "show_ghost"}) {
        const auto previous = legacy.find(key);
        if (previous != legacy.end() && previous->is_boolean()) {
            migrated[key] = *previous;
            general.set_option_value(key, previous->get<bool>());
        }
    }
    return general.save_config_json(migrated);
}

} // namespace wr64::frontend
