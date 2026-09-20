#pragma once

#include "ui_element.h"
#include "ui_label.h"

namespace recompui {

    using on_change_tab_callback = std::function<void(int tab_index)>;

    class Tab : public Element {
    private:
        Style hover_style;
        Style checked_style;
        Style pulsing_style;
        Style disabled_style;
        int tab_index;
        bool is_selected = false;
        on_change_tab_callback on_select_tab;
        Element *label = nullptr;
        Element *indicator = nullptr;

        bool visible = true;

        static constexpr float tab_vertical_padding = 20.0f;
        static constexpr float tab_horizontal_padding = 24.0f;
        static constexpr recompui::Display default_display_setting = Display::Block;
    protected:
        std::string_view get_type_name() override { return "Tab"; }
        virtual void process_event(const Event &e) override;
    public:
        Tab(ResourceId rid, Element *parent, int tab_index, std::string_view text, on_change_tab_callback on_select_tab);
        void set_selected(bool selected);
        void set_visible(bool is_visible);
        bool get_visible() { return visible; }
    };

    class TabSet : public Element {
    private:
        std::vector<Tab *> tabs;
        on_change_tab_callback change_tab_callback;
        int active_tab = -1;
        void update_corner_radius();
    protected:
        std::string_view get_type_name() override { return "TabSet"; }
    public:
        TabSet(ResourceId rid, Element *parent);
        void set_change_tab_callback(on_change_tab_callback callback);
        int add_tab(std::string_view text);
        void set_active_tab(int tab_index, bool report_change = true);
        void focus_on_active_tab();
        Element *get_active_tab_element() const { return active_tab >= 0 && active_tab < static_cast<int>(tabs.size()) ? tabs[active_tab] : nullptr; };
        int get_active_tab() const { return active_tab; }
        void set_tab_visible(int tab_index, bool is_visible);
        int get_next_tab_in_direction(int index, int direction);
    };

} // namespace recompui
