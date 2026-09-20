#include "librecomp/config.hpp"
#include "recompui/config.h"
#include <algorithm>
#include <atomic>
#include <cmath>

namespace recompui {

static bool created_sound_config = false;
// The SDL callback must not read the mutable configuration map or take a lock.
static std::atomic<double> main_volume_percent{100.0};
static_assert(std::atomic<double>::is_always_lock_free);

namespace config {
    recomp::config::Config &get_sound_config() {
        if (!created_sound_config) {
            throw std::runtime_error("sound config has not been created yet. Call create_sound_tab() first.");
        }
        return config::get_config(config::sound::id);
    }

    double sound::get_main_volume() {
        return main_volume_percent.load(std::memory_order_relaxed);
    }

    recomp::config::Config &create_sound_tab(const std::string &name) {
        created_sound_config = true;
        recomp::config::Config &config = recompui::config::create_config_tab(name, sound::id, false);

        config.add_percent_number_option(
            sound::options::main_volume,
            "Main Volume",
            "Controls the main volume of the game.",
            100.0
        );
        config.add_option_change_callback(sound::options::main_volume,
            [](recomp::config::ConfigValueVariant value, recomp::config::ConfigValueVariant,
                recomp::config::OptionChangeContext) {
                const double percent = std::get<double>(value);
                main_volume_percent.store(std::isfinite(percent) ? std::clamp(percent, 0.0, 100.0) : 100.0,
                    std::memory_order_relaxed);
            });

        return config;
    }
} // namespace config
} // namespace recompui
