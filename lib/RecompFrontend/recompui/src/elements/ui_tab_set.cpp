#include "ui_tab_set.h"
#include "ui_utils.h"

namespace recompui {

Tab::Tab(ResourceId rid, Element *parent, int tab_index, std::string_view text, on_change_tab_callback on_select_tab) :
    Element(rid, parent, Events(EventType::Click, EventType::Hover, EventType::Enable, EventType::Focus), "button", false)
{
    this->tab_index = tab_index;
    this->on_select_tab = std::move(on_select_tab);
    set_visible(true);
    set_position(Position::Relative);
    set_margin(0);
    set_padding_top(tab_vertical_padding);
    set_padding_bottom(tab_vertical_padding);
    set_padding_left(tab_horizontal_padding);
    set_padding_right(tab_horizontal_padding);
    set_focusable(true);
    set_tab_index_auto();
    set_cursor(Cursor::Pointer);

    set_color(Color{216, 218, 239, 255});
    set_background_color(theme::color::Transparent);
    set_opacity(1.0f);

    hover_style.set_color(theme::color::WhiteA80);
    checked_style.set_color(Color{255, 157, 191, 255});
    pulsing_style.set_color(theme::color::White);
    pulsing_style.set_background_color(Color{74, 69, 140, 255});

    disabled_style.set_cursor(Cursor::None);
    disabled_style.set_color(theme::color::TextDim);
    disabled_style.set_opacity(0.5f);

    ContextId context = get_current_context();
    label = context.create_element<Label>(this, std::string{text}, theme::Typography::Header3);
    // The USA tabs, including Enhancements and Ghosts, must fit at 4:3.
    label->set_font_size(27.0f);
    label->set_line_height(32.0f);
    label->set_letter_spacing(1.0f);
    set_padding_left(18.0f);
    set_padding_right(18.0f);

    indicator = context.create_element<Element>(this, 0, "div", false);
    indicator->set_display(Display::Block);
    indicator->set_position(Position::Absolute);
    indicator->set_height(5.0f);
    indicator->set_bottom(0.0f);
    indicator->set_left(0.0f);
    indicator->set_right(0.0f);
    indicator->set_background_color(theme::color::Transparent);

    add_style(&hover_style, { hover_state });
    add_style(&checked_style, { checked_state });
    add_style(&pulsing_style, { focus_state });
    add_style(&disabled_style, { disabled_state });
}

void Tab::set_visible(bool is_visible) {
    visible = is_visible;
    set_enabled(visible);
    set_focusable(visible);

    if (visible) {
        set_display(default_display_setting);
    } else {
        set_display(Display::None);
        set_as_primary_focus(false);
    }
}

void Tab::process_event(const Event &e) {
    switch (e.type) {
    case EventType::Click:
        on_select_tab(tab_index);
        break;
    case EventType::Hover:
        set_style_enabled(hover_state, std::get<EventHover>(e.variant).active);
        break;
    case EventType::Enable: {
        bool active = std::get<EventEnable>(e.variant).active;
        set_style_enabled(disabled_state, !active);
        indicator->set_background_color(active && is_selected ? theme::color::Secondary : theme::color::Transparent);
        break;
    }
    case EventType::Focus:
        {
            bool active = std::get<EventFocus>(e.variant).active;
            set_style_enabled(focus_state, active);
            if (active) {
                queue_update();
            }
        }
        break;
    case EventType::Update:
        if (is_style_enabled(focus_state)) {
            pulsing_style.set_color(theme::color::White);
            if (is_selected) {
                indicator->set_background_color(theme::color::Secondary);
            } else {
                indicator->set_background_color(theme::color::Transparent);
            }
            apply_styles();
            queue_update();
        }
        break;
    default:
        break;
    }
}

void Tab::set_selected(bool enable) {
    is_selected = enable;
    set_as_primary_focus(enable);
    set_style_enabled(checked_state, enable);
    indicator->set_background_color(enable ? theme::color::Secondary : theme::color::Transparent);
}

TabSet::TabSet(ResourceId rid, Element *parent) :
    Element(rid, parent, 0, "div", false)
{
    set_display(Display::Flex);
    set_flex_direction(FlexDirection::Row);
    set_justify_content(JustifyContent::FlexStart);
    set_align_items(AlignItems::Stretch);
    set_gap(0.0f);
    set_as_navigation_container(NavigationType::Horizontal);
}

void TabSet::set_change_tab_callback(on_change_tab_callback callback) {
    change_tab_callback = std::move(callback);
}

void TabSet::update_corner_radius() {
    // The header's rounded background does not clip a child's focus background.
    // Tabs touch the modal's left edge, so round the first visible tab itself.
    bool first_visible = true;
    for (Tab* tab : tabs) {
        const bool at_corner = first_visible && tab->get_visible();
        tab->set_border_top_left_radius(at_corner ? theme::border::radius_lg : 0.0f);
        if (tab->get_visible()) {
            first_visible = false;
        }
    }
}

int TabSet::add_tab(std::string_view text) {
    ContextId context = get_current_context();
    Tab *tab = context.create_element<Tab>(this, tabs.size(), text, [this](int tab_index) {
        set_active_tab(tab_index, true);
    });
    tabs.push_back(tab);
    update_corner_radius();
    if (active_tab < 0) {
        active_tab = 0;
        tab->set_selected(true);
    } else {
        tab->set_selected(false);
    }

    return tabs.size() - 1;
}

void TabSet::set_active_tab(int tab_index, bool report_change) {
    if (tab_index >= static_cast<int>(tabs.size())) {
        return;
    }
    if (active_tab != tab_index) {
        active_tab = tab_index;
        for (int i = 0; i < static_cast<int>(tabs.size()); i++) {
            tabs[i]->set_selected(i == active_tab);
        }
        if (report_change && change_tab_callback) {
            change_tab_callback(active_tab);
        }
    }
}

void TabSet::focus_on_active_tab() {
    if (active_tab >= 0 && active_tab < static_cast<int>(tabs.size())) {
        tabs[active_tab]->focus();
    }
};

int TabSet::get_next_tab_in_direction(int index, int direction) {
    if (tabs.size() == 0) {
        return -1;
    }

    int new_index = index + direction;
    while (true) {
        if (new_index < 0) {
            new_index = static_cast<int>(tabs.size()) - 1;
        } else if (new_index >= static_cast<int>(tabs.size())) {
            new_index = 0;
        }

        // Check if wrapped back to the original start index.
        if (new_index == index) {
            // Ensure original index is visible.
            if (tabs[index]->get_visible()) {
                return index;
            }
            return -1;
        }

        if (tabs[new_index]->get_visible()) {
            return new_index;
        }

        new_index += direction;
    }

    return new_index;
}

void TabSet::set_tab_visible(int tab_index, bool is_visible) {
    if (tab_index < 0 || tab_index >= static_cast<int>(tabs.size())) {
        return;
    }
    Tab* tab = tabs[tab_index];
    tab->set_visible(is_visible);
    update_corner_radius();
    // Tab getting hidden is active, switch to next available.
    if (!is_visible && active_tab == tab_index) {
        set_active_tab(get_next_tab_in_direction(tab_index, 1), true);
    }
}

} // namespace recompui
