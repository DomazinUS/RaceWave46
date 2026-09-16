#include "wr64_renderer.hpp"

#ifndef WR64_ENABLE_RT64

namespace wr64::renderer {
namespace {

class HeadlessRenderer final : public ultramodern::renderer::RendererContext {
public:
    HeadlessRenderer() {
        setup_result = ultramodern::renderer::SetupResult::Success;
        chosen_api = ultramodern::renderer::GraphicsApi::Auto;
    }

    bool valid() override { return true; }
    bool update_config(
        const ultramodern::renderer::GraphicsConfig&,
        const ultramodern::renderer::GraphicsConfig&) override {
        return true;
    }
    void enable_instant_present() override {}
    // Same new pure virtual the RT64 context grew. Headless renders
    // nothing, so there is nothing to do with a dummy workload either.
    void send_dummy_workload(uint32_t) override {}
    void send_dl(const OSTask*) override {}
    void update_screen() override {}
    void shutdown() override {}
    uint32_t get_display_framerate() const override { return 60; }
    float get_resolution_scale() const override { return 1.0F; }
};

} // namespace

std::unique_ptr<ultramodern::renderer::RendererContext> create_render_context(
    uint8_t*, ultramodern::renderer::WindowHandle, bool) {
    return std::make_unique<HeadlessRenderer>();
}

} // namespace wr64::renderer

#endif
