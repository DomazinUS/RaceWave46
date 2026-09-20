#include "ui_pseudo_border.h"
#include "ui_utils.h"

namespace recompui {

    PseudoBorder::PseudoBorder(ResourceId rid, Element *parent, bool inset, float border_width, float border_outset_distance) : Element(rid, parent) {
        if (border_width > 0) {
            set_border_width(border_width);
        } else {
            set_border_width(theme::border::width);
            border_width = theme::border::width;
        }

        set_position(Position::Absolute);
        set_pointer_events(PointerEvents::None);
        if (inset) {
            set_inset(border_width);
        } else {
            set_inset(-(border_width + border_outset_distance));
        }
    }

    FocusBorder::FocusBorder(ResourceId rid, Element *parent, bool extra_dist) : PseudoBorder(rid, parent, false, theme::border::width * 2.0f, theme::border::width * 2.0f * (extra_dist ? 2.0f : 1.0f)) {
        set_border_color(theme::color::PrimaryL, 0);
    }

    void FocusBorder::process_event(const Event &e) {
        switch (e.type) {
        case EventType::Update: {
            if (get_parent()->is_style_enabled(focus_state)) {
                set_border_color(theme::color::Secondary);
            } else {
                set_border_color(theme::color::PrimaryL, 0);
            }
            
            queue_update();
            break;
        }
        default:
            break;
        }
    }

} // namespace recompui
