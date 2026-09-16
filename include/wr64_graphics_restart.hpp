#pragma once

#include "ultramodern/config.hpp"

namespace wr64::frontend {
inline bool graphics_api_reconfiguration_needed(ultramodern::renderer::GraphicsApi active,
    ultramodern::renderer::GraphicsApi startup, ultramodern::renderer::GraphicsApi selected) {
    using Api = ultramodern::renderer::GraphicsApi;
    return selected == Api::Auto ? startup != Api::Auto : selected != active;
}

enum class GraphicsReconfigurationResult { Applied, Restored, Failed };

// Every failed/partial device is disposed before another device is created.
// Keeping the transaction separate makes recovery ordering testable without
// starting the game or depending on a particular GPU.
template<class Config, class Stop, class Initialize>
GraphicsReconfigurationResult reconfigure_graphics(const Config& requested,
    const Config& previous, Stop stop, Initialize initialize) {
    stop();
    if (initialize(requested)) return GraphicsReconfigurationResult::Applied;
    stop();
    if (initialize(previous)) return GraphicsReconfigurationResult::Restored;
    stop();
    return GraphicsReconfigurationResult::Failed;
}
}
