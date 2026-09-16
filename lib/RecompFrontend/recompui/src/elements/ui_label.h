#pragma once

#include "ui_element.h"

namespace recompui {

    enum class LabelStyle {
        Annotation,
        Small,
        Normal,
        Large
    };

    class Label : public Element {
    protected:
        std::string_view get_type_name() override { return "Label"; }
    public:
        Label(ResourceId rid, Element *parent, LabelStyle label_style);
        Label(ResourceId rid, Element *parent, const std::string &text, LabelStyle label_style);
        Label(ResourceId rid, Element *parent, theme::Typography typography);
        Label(ResourceId rid, Element *parent, const std::string &text, theme::Typography typography);
    };

} // namespace recompui
