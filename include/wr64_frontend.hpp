#pragma once


union SDL_Event;
namespace recomp { struct GameEntry; }
namespace ultramodern::renderer { enum class GraphicsApi; }

namespace wr64::frontend {

// Hand the game to recompui's launcher. REQUIRED, and required BEFORE
// recomp::start: recompui externs a global std::vector<recomp::GameEntry> and
// its default launcher callback indexes element [0] four times without a size
// check, from inside RT64's init hook.
void register_game(const recomp::GameEntry& entry);

// Everything recompui demands of a host, in one place. Must be called BEFORE
// recomp::start(): that reaches RT64's setup, which fires recompui's init hook,
// which builds the UI and throws if any of this is missing.
void configure();

// Pump events, once per frame. recompinput::handle_events() does this when the
// UI is up - it owns SDL_PollEvent and feeds the UI, controller hotplug and
// player assignment from it. If the UI failed to start, this drains SDL itself
// so the window still closes.
void pump();

// Opens the settings modal if it is closed, closes it if it is open. Does
// nothing rather than throwing when the UI is not up, because this is called
// from a key handler.
void toggle_settings();
// Reload the selected edition's files when its child process returns.
void reload_edition_settings();
// Renderer requests are applied by pump(), on the SDL window-owning thread.
void request_fullscreen(bool fullscreen);
void toggle_fullscreen();
// Queue a display refresh-rate description update for the UI thread.
void report_display_refresh_rate(unsigned int refresh_rate);
void report_multisampling_support(unsigned int sample_counts, bool sample_positions);
// Report the device actually created, separately from the saved next-launch choice.
void report_graphics_api(ultramodern::renderer::GraphicsApi active_api,
    ultramodern::renderer::GraphicsApi startup_selection, bool ray_tracing_supported);
void report_graphics_reconfiguration(bool succeeded,
    ultramodern::renderer::GraphicsApi restored_selection);

// True once configure() has succeeded.
bool ready();

} // namespace wr64::frontend
