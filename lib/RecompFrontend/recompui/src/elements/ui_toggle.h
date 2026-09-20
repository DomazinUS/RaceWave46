#pragma once

#include "ui_element.h"
#include "ui_svg.h"

namespace recompui {

    enum class ToggleSize {
        Medium,
        Large,
        Default = Large
    };

    struct ToggleColorTheme {
        theme::color border;
        theme::color bg_hover;
        theme::color floater;
        theme::color floater_disabled;
    };

    struct ToggleStyleGroup {
        Style normal; // not used for unchecked state
        Style hover;
        Style focus;
        Style disabled;
    };

    class Toggle : public Element {
    protected:
        Element *floater;
        Element *inner_border;
        Element *focus_border;
        float floater_left = 0.0f;
        std::chrono::high_resolution_clock::duration last_time;
        std::list<std::function<void(bool)>> checked_callbacks;

        struct {
            ToggleStyleGroup unchecked;
            ToggleStyleGroup unchecked_floater;
            ToggleStyleGroup unchecked_inner_border;
            ToggleStyleGroup checked;
            ToggleStyleGroup checked_floater;
            ToggleStyleGroup checked_inner_border;
        } style_groups;

        bool checked = false;
        ToggleSize size = ToggleSize::Default;

        virtual const ToggleColorTheme &get_toggle_color_theme_unchecked();
        virtual const ToggleColorTheme &get_toggle_color_theme_checked();

        void set_toggle_colors(bool for_checked);

        virtual void set_checked_internal(bool checked, bool animate, bool setup, bool trigger_callbacks);
        void set_all_style_enabled(std::string_view style_name, bool enabled);
        float floater_left_target() const;

        // Element overrides.
        virtual void process_event(const Event &e) override;
        std::string_view get_type_name() override { return "Toggle"; }
    public:
        Toggle(ResourceId rid, Element *parent, ToggleSize size = ToggleSize::Default);
        void set_checked(bool checked);
        bool is_checked() const;
        void add_checked_callback(std::function<void(bool)> callback);
    };

    class IconToggle : public Toggle {
    protected:
        Svg *icon_svg_left;
        Svg *icon_svg_right;

        Style icon_disabled_style;

        // This being an override doesn't apply because it is called during Toggle's constructor.
        // So set_toggle_colors(false) gets called in IconToggle's constructor in order for this to be applied properly.
        const ToggleColorTheme &get_toggle_color_theme_unchecked() override;

        void set_checked_internal(bool checked, bool animate, bool setup, bool trigger_callbacks) override;

        // Element overrides.
        std::string_view get_type_name() override { return "IconToggle"; }
    public:
        IconToggle(ResourceId rid, Element *parent, std::string_view icon_src_left, std::string_view icon_src_right, ToggleSize size = ToggleSize::Default);
    };

} // namespace recompui
