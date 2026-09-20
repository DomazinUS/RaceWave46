#include "recomp.h"
#include "wr64_sunny_detail.hpp"
#include "wr64_sunny_sky.hpp"

namespace {
uint32_t player(uint8_t* rdram) {
    return uint32_t(MEM_W(0, S32(0x800DAB2C)));
}

bool enabled(uint8_t* rdram) {
    return rdram && wr64_sunny_detail_active(rdram) && player(rdram) < 2;
}
}

extern "C" void wr64_sunny_sky_bottom_camera(uint8_t* rdram, recomp_context* ctx) {
    if (!enabled(rdram) || ctx->r4 != 0) return;
    const uint32_t buffer = uint32_t(MEM_W(0, S32(0x8011F8E0)));
    // Across the eight race courses, make_world_glist already calls the native
    // bottom builder once per view,
    // but supplies camera zero because ordinary 2P water is opaque. Reuse that
    // call for the current view, including its native wave-grid inputs. The
    // exact destination check keeps other uses of the native helper untouched.
    if (buffer > 1 || uint32_t(ctx->r5) != 0x801C43F8 + buffer * 0x3630) return;
    const uint32_t view = player(rdram);
    ctx->r4 = view;
    ctx->r5 = ADD32(ctx->r5, view * 7 * 16);
}

extern "C" uint32_t wr64_sunny_sky_bottom_draw(uint8_t* rdram, uint32_t original) {
    // Both authored bottom lists are resident and differ only in the vertex
    // slot (segment 6 +0 or +0x70). Translucent enhanced water must have a
    // bottom under each view instead of exposing the cleared framebuffer.
    return enabled(rdram) && original == 0x010103F0 ? original + player(rdram) * 0x40 : original;
}

extern "C" void wr64_sunny_sky_cloud_camera(uint8_t* rdram, recomp_context* ctx) {
    if (!enabled(rdram)) return;
    // The existing native helper accepts either camera, but its caller always
    // supplied camera zero because only the one-player cloud pass was drawn.
    // Each SOT_DYNAMIC already reserves seven cloud vertices for both views.
    // The native sea-mode checks still suppress clouds indoors/underwater; the
    // course's existing animation parameters and update cadence are preserved.
    const uint32_t view = player(rdram);
    ctx->r4 = view;
    ctx->r5 = ADD32(ctx->r5, view * 7 * 16);
}

extern "C" uint32_t wr64_sunny_sky_material_players(uint8_t* rdram, uint32_t original) {
    // Change only the local material/pass decision, never the game player count.
    return enabled(rdram) ? 1u : original;
}

extern "C" uint32_t wr64_sunny_sky_fog_update(uint8_t* rdram, uint32_t original) {
    // The richer material surrounds a one-player fog simulation block. Drawing
    // it in two views must not start updating that state twice per frame.
    return enabled(rdram) ? 0u : original;
}

extern "C" void wr64_sunny_sky_cloud_color(uint8_t* rdram, recomp_context* ctx) {
    if (enabled(rdram)) ctx->r8 = ADD32(ctx->r8, player(rdram) * 0x110);
}

extern "C" void wr64_sunny_sky_cloud_draw(uint8_t* rdram, recomp_context* ctx) {
    if (!enabled(rdram) || player(rdram) == 0) return;
    // The authored cloud list begins with a camera-zero vertex load. Supply
    // camera one's reserved slot and reuse its six original triangles after
    // that load. This adds one command, without rewriting a shared display list
    // or changing either viewport, scissor, projection or animation cadence.
    MEM_W(0, ctx->r3) = 0x04000E6F;
    MEM_W(4, ctx->r3) = 0x06000230;
    ctx->r3 = ADD32(ctx->r3, 8);
    ctx->r6 = ADD32(ctx->r6, 8);
    ctx->r24 = ADD32(ctx->r24, 8);
}
