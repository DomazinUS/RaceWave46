#include "ui_svg.h"

#include <cassert>

namespace recompui {

    Svg::Svg(ResourceId rid, Element *parent, std::string_view src) : Element(rid, parent, 0, "svg") {
        set_src(src);
    }

};
