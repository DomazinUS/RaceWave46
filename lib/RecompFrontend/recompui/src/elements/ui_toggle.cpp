#include "ui_toggle.h"
#include "ui_pseudo_border.h"
#include "ui_utils.h"

#include <cassert>

#include <ultramodern/ultramodern.hpp>

namespace recompui {

    struct ToggleSizing {
        float width;
        float height;
        float floater_width;
        float floater_height;
        float floater_margin;

        ToggleSizing(float width, float height, float floater_margin)
            : width(width), height(height),
              floater_width(height - floater_margin * 2.0f),
              floater_height(height - floater_margin * 2.0f),
              floater_margin(floater_margin) {}

        float left_offset(bool checked) const {
            return checked ? width - floater_width - floater_margin : floater_margin;
        }
    };

    static const ToggleSizing medium_toggle_sizing = ToggleSizing(64.0f, 36.0f, 6.0f);
    static const ToggleSizing large_toggle_sizing = ToggleSizing(144.0f, 72.0f, 8.0f);

    static const ToggleSizing &get_toggle_sizing(ToggleSize size) {
        switch (size) {
            case ToggleSize::Medium:
                return medium_toggle_sizing;
            case ToggleSize::Large:
                return large_toggle_sizing;
            default:
                assert(false && "Invalid toggle size");
        }
    }

    const ToggleColorTheme &Toggle::get_toggle_color_theme_unchecked() {
        static const ToggleColorTheme color_theme = {
            .border = theme::color::BW50,
            .bg_hover = theme::color::WhiteA5,
            .floater = theme::color::TextDim,
            .floater_disabled = theme::color::TextDim
        };

        return color_theme;
    }

    const ToggleColorTheme &Toggle::get_toggle_color_theme_checked() {
        static const ToggleColorTheme color_theme = {
            .border = theme::color::Border,
            .bg_hover = theme::color::SecondaryA20,
            .floater = theme::color::Secondary,
            .floater_disabled = theme::color::SecondaryD
        };

        return color_theme;
    }

    void Toggle::set_toggle_colors(bool for_checked) {
        const ToggleColorTheme &color_theme = for_checked ? get_toggle_color_theme_checked() : get_toggle_color_theme_unchecked();

        ToggleStyleGroup &base_styles = for_checked ? style_groups.checked : style_groups.unchecked;
        ToggleStyleGroup &floater_styles = for_checked ? style_groups.checked_floater : style_groups.unchecked_floater;
        ToggleStyleGroup &inner_border_styles = for_checked ? style_groups.checked_inner_border : style_groups.unchecked_inner_border;

        if (for_checked) {
            base_styles.normal.set_border_color(color_theme.border);
            floater_styles.normal.set_background_color(color_theme.floater);
            inner_border_styles.normal.set_border_color(color_theme.border);
        } else {
            set_border_color(color_theme.border);
            floater->set_background_color(color_theme.floater);
            inner_border->set_border_color(color_theme.border);
        }

        base_styles.hover.set_border_color(color_theme.border);
        inner_border_styles.hover.set_border_color(color_theme.border);
        base_styles.hover.set_background_color(color_theme.bg_hover);

        base_styles.focus.set_border_color(color_theme.border);
        inner_border_styles.focus.set_border_color(color_theme.border);
        base_styles.focus.set_background_color(color_theme.bg_hover);

        base_styles.disabled.set_border_color(color_theme.border, 128);
        inner_border_styles.disabled.set_border_color(color_theme.border, 128);
        floater_styles.disabled.set_background_color(color_theme.floater_disabled, 128);
    }



    Toggle::Toggle(ResourceId rid, Element *parent, ToggleSize size) : Element(rid, parent, Events(EventType::Click, EventType::Focus, EventType::Hover, EventType::Enable), "button") {
        this->size = size;
        const ToggleSizing &sizing = get_toggle_sizing(size);
        enable_focus();

        set_position(Position::Relative);

        set_width(sizing.width);
        set_height(sizing.height);
        set_border_radius(sizing.height * 0.5f);
        set_opacity(0.9f);
        set_cursor(Cursor::Pointer);
        set_background_color(theme::color::Transparent);

        add_style(&style_groups.unchecked.hover, hover_state);
        add_style(&style_groups.unchecked.focus, focus_state);
        add_style(&style_groups.unchecked.disabled, disabled_state);

        add_style(&style_groups.checked.normal, checked_state);
        add_style(&style_groups.checked.hover, { checked_state, hover_state });
        add_style(&style_groups.checked.focus, { checked_state, focus_state });
        add_style(&style_groups.checked.disabled, { checked_state, disabled_state });

        ContextId context = get_current_context();

        focus_border = context.create_element<FocusBorder>(this);
        focus_border->set_border_radius((sizing.height + theme::border::width * 4.0f + theme::border::width * 4.0f) * 0.5f);

        inner_border = context.create_element<PseudoBorder>(this);
        inner_border->set_border_radius((sizing.height - theme::border::width * 2.0f) * 0.5f);

        inner_border->add_style(&style_groups.unchecked_inner_border.hover, hover_state);
        inner_border->add_style(&style_groups.unchecked_inner_border.focus, focus_state);
        inner_border->add_style(&style_groups.unchecked_inner_border.disabled, disabled_state);
        
        inner_border->add_style(&style_groups.checked_inner_border.normal, checked_state);
        inner_border->add_style(&style_groups.checked_inner_border.hover, { checked_state, hover_state });
        inner_border->add_style(&style_groups.checked_inner_border.focus, { checked_state, focus_state });
        inner_border->add_style(&style_groups.checked_inner_border.disabled, { checked_state, disabled_state });

        floater = context.create_element<Element>(this);
        floater->set_position(Position::Absolute);
        floater->set_top(50.0f, Unit::Percent);
        floater->set_translate_2D(0, -50.0f, Unit::Percent);
        floater->set_width(sizing.floater_width);
        floater->set_height(sizing.floater_height);
        floater->set_border_radius(sizing.floater_height * 0.5f);
    
        floater->add_style(&style_groups.unchecked_floater.hover, hover_state);
        floater->add_style(&style_groups.unchecked_floater.focus, focus_state);
        floater->add_style(&style_groups.unchecked_floater.disabled, disabled_state);

        floater->add_style(&style_groups.checked_floater.normal, checked_state);
        floater->add_style(&style_groups.checked_floater.hover, { checked_state, hover_state });
        floater->add_style(&style_groups.checked_floater.focus, { checked_state, focus_state });
        floater->add_style(&style_groups.checked_floater.disabled, { checked_state, disabled_state });

        set_toggle_colors(false);
        set_toggle_colors(true);

        set_checked_internal(false, false, true, false);
    }

    void Toggle::set_all_style_enabled(std::string_view style_name, bool enabled) {
        set_style_enabled(style_name, enabled);
        inner_border->set_style_enabled(style_name, enabled);
        floater->set_style_enabled(style_name, enabled);
    }

    void Toggle::set_checked_internal(bool checked, bool animate, bool setup, bool trigger_callbacks) {
        if (this->checked != checked || setup) {
            this->checked = checked;

            if (animate) {
                last_time = ultramodern::time_since_start();
                queue_update();
            }
            else {
                floater_left = floater_left_target();
            }

            floater->set_left(floater_left, Unit::Dp);

            if (trigger_callbacks) {
                for (const auto &function : checked_callbacks) {
                    function(checked);
                }
            }

            set_all_style_enabled(checked_state, checked);
        }
    }

    float Toggle::floater_left_target() const {
        return get_toggle_sizing(size).left_offset(checked);
    }

    void Toggle::process_event(const Event &e) {
        switch (e.type) {
        case EventType::Click:
            if (is_enabled()) {
                set_checked_internal(!checked, true, false, true);
            }

            break;
        case EventType::Hover: {
            bool hover_active = std::get<EventHover>(e.variant).active && is_enabled();
            set_all_style_enabled(hover_state, hover_active);
            break;
        }
        case EventType::Focus: {
            bool focus_active = std::get<EventFocus>(e.variant).active;
            set_all_style_enabled(focus_state, focus_active);
            queue_update();
            break;
        }
        case EventType::Enable: {
            bool enable_active = std::get<EventEnable>(e.variant).active;
            set_all_style_enabled(disabled_state, !enable_active);
            if (enable_active) {
                set_cursor(Cursor::Pointer);
                set_focusable(true);
            }
            else {
                set_cursor(Cursor::None);
                set_focusable(false);
            }
            break;
        }
        case EventType::Update: {
            std::chrono::high_resolution_clock::duration now = ultramodern::time_since_start();
            float delta_time = std::max(std::chrono::duration<float>(now - last_time).count(), 0.0f);
            last_time = now;
            bool should_queue_update = false;

            constexpr float dp_speed = 740.0f;
            const float target = floater_left_target();
            if (target < floater_left) {
                floater_left += std::max(-dp_speed * delta_time, target - floater_left);
            }
            else {
                floater_left += std::min(dp_speed * delta_time, target - floater_left);
            }

            if (abs(target - floater_left) < 1e-4f) {
                floater_left = target;
            }
            else {
                should_queue_update = true;
            }

            floater->set_left(floater_left, Unit::Dp);

            if (should_queue_update) {
                queue_update();
            }

            break;
        }
        default:
            break;
        }
    }

    void Toggle::set_checked(bool checked) {
        set_checked_internal(checked, false, false, false);
    }

    bool Toggle::is_checked() const {
        return checked;
    }

    void Toggle::add_checked_callback(std::function<void(bool)> callback) {
        checked_callbacks.emplace_back(callback);
    }

    static void style_icon(Svg *svg, const ToggleSizing &sizing, bool left) {
        svg->set_position(Position::Absolute);
        float size = sizing.floater_height - sizing.floater_margin * 2.0f;
        svg->set_width(size);
        svg->set_height(size);
        svg->set_top(50.0f, Unit::Percent);
        svg->set_translate_2D(0, -50.0f, Unit::Percent);
        if (left) {
            svg->set_left(sizing.floater_margin * 2.0f);
        } else {
            svg->set_right(sizing.floater_margin * 2.0f);
        }
        svg->set_image_color(theme::color::Text);
        svg->set_pointer_events(PointerEvents::None);
    }

    const ToggleColorTheme &IconToggle::get_toggle_color_theme_unchecked() {
        static const ToggleColorTheme color_theme = {
            .border = theme::color::Secondary,
            .bg_hover = theme::color::SecondaryA30,
            .floater = theme::color::Secondary,
            .floater_disabled = theme::color::SecondaryD
        };

        return color_theme;
    }

    IconToggle::IconToggle(
        ResourceId rid,
        Element *parent,
        std::string_view icon_src_left,
        std::string_view icon_src_right,
        ToggleSize size
    ) : Toggle(rid, parent, size) {
        const ToggleSizing &sizing = get_toggle_sizing(size);
        set_toggle_colors(false);
        ContextId context = get_current_context();
        icon_svg_left = context.create_element<Svg>(this, icon_src_left);
        style_icon(icon_svg_left, sizing, true);
        icon_svg_right = context.create_element<Svg>(this, icon_src_right);
        style_icon(icon_svg_right, sizing, false);
    }

    void IconToggle::set_checked_internal(bool checked, bool animate, bool setup, bool trigger_callbacks) {
        bool was_checked = this->checked;
        Toggle::set_checked_internal(checked, animate, setup, trigger_callbacks);

        if (setup || was_checked != this->checked) {
            if (this->checked) {
                icon_svg_left->set_opacity(0.5f);
                icon_svg_right->set_opacity(1.0f);
            } else {
                icon_svg_left->set_opacity(1.0f);
                icon_svg_right->set_opacity(0.5f);
            }
        }
    }
};
