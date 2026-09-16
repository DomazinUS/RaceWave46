#pragma once

#include "ui_element.h"
#include "ui_label.h"

namespace recompui {

    class Span : public Element {
    protected:
        std::string_view get_type_name() override { return "Span"; }
    public:
        Span(ResourceId rid, Element *parent);
        Span(ResourceId rid, Element *parent, const std::string &text);
    };

} // namespace recompui