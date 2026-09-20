#include "recompui/config.h"
#include "recompinput/players.h"
#include "recompinput/profiles.h"
#include "elements/ui_element.h"
#include "ui_config_page_controls.h"
#include "librecomp/game.hpp"

namespace recompui {

void config::create_controls_tab(const std::string &name) {
    config::create_tab(
        name,
        config::controls::id,
        [](ContextId context, Element* parent) {
            context.create_element<ConfigPageControls>(parent);
        },
        nullptr,
        [](TabCloseContext close_context) {
            // Save the current control mappings when closing the controls tab.
            recompinput::profiles::save_controls_config(recomp::get_config_path() / (config::controls::id + ".json"));
        }
    );
}

} // namespace recompui
