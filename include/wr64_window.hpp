#pragma once

#include "ultramodern/ultramodern.hpp"
#include "wr64_secondary_window.hpp"

namespace wr64::window {

void set_enabled(bool enabled);
ultramodern::gfx_callbacks_t::gfx_data_t create_gfx();
ultramodern::renderer::WindowHandle create_window(
    ultramodern::gfx_callbacks_t::gfx_data_t data);
void update_gfx(ultramodern::gfx_callbacks_t::gfx_data_t data);

} // namespace wr64::window
