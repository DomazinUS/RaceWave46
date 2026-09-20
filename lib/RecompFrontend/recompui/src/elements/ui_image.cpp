#include "ui_image.h"

#include <cassert>

namespace recompui {

    Image::Image(ResourceId rid, Element *parent, std::string_view src) : Element(rid, parent, 0, "img") {
        set_src(src);
    }

};