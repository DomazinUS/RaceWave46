#include "ui_span.h"

#include <cassert>

namespace recompui {

    Span::Span(ResourceId rid, Element *parent) : Element(rid, parent, 0, "span", true) {
        set_font_style(FontStyle::Normal);
    }

    Span::Span(ResourceId rid, Element *parent, const std::string &text) : Span(rid, parent) {
        set_text(text);
    }

};
