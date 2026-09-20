#include "wr64_texture_packs.hpp"

#include <cstdio>
#include <mutex>

#include "librecomp/mods.hpp"
#include "recompui/renderer.h"

namespace wr64::texture_packs {

void register_mod_types() {
    static std::once_flag registration;
    std::call_once(registration, [] {
        const auto texture_content = recomp::mods::register_mod_content_type({
            .content_filename = "rt64.json",
            .allow_runtime_toggle = true,
            .on_enabled = [](recomp::mods::ModContext& context, const recomp::mods::ModHandle& mod) {
                recompui::renderer::enable_texture_pack(context, mod);
            },
            .on_disabled = [](recomp::mods::ModContext&, const recomp::mods::ModHandle& mod) {
                recompui::renderer::disable_texture_pack(mod);
            },
            .on_reordered = [](recomp::mods::ModContext&) {
                recompui::renderer::trigger_texture_pack_update();
            }
        });
        // Container extensions omit the dot. RTZ can use its filename as its
        // mod identity, while NRM's existing registration also accepts textures.
        if (!recomp::mods::register_mod_container_type("rtz", {texture_content}, false)) {
            std::fprintf(stderr, "[textures] Failed to register the RTZ texture-pack format.\n");
        }
    });
}

}
