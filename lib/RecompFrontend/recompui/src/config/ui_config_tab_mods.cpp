#include "recompui/config.h"
#include "recompinput/players.h"
#include "recompinput/profiles.h"
#include "composites/ui_mod_menu.h"
#include "elements/ui_element.h"
#include "librecomp/game.hpp"

namespace recompui {

void config::create_mods_tab(const std::string &name) {
    config::create_tab(
        name,
        config::mods::id,
        [](ContextId context, Element* parent) {
            context.create_element<ModMenu>(parent);
        }
    );

    recompui::update_mod_list(false);
}

} // namespace recompui
