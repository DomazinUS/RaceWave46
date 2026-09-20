#ifndef RECOMPUI_ELEMENTS_H
#define RECOMPUI_ELEMENTS_H

#include "recompui.h"
#include "RmlUi/Core/Element.h"

#include "ui_rml_color_element.h"

namespace recompui {
    void register_custom_elements();

    Rml::ElementInstancer* get_custom_element_instancer(std::string tag);
}

#endif
