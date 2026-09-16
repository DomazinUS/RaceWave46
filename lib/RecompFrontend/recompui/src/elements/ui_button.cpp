#include "ui_button.h"
#include "ui_label.h"
#include "ui_pseudo_border.h"

#include <cassert>

// #define RECOMPUI_BUTTON_DEBUG

namespace recompui {

    Button::Button(ResourceId rid, Element *parent, const std::string &text, ButtonStyle style, ButtonSize size) : Element(rid, parent, Events(EventType::Click, EventType::Hover, EventType::Enable, EventType::Focus), "button", false) {
        this->style = style;
        this->size = size;
        // Borders add width to the button, so this subtracts from the base size to bring it back to the expected size.
        float float_size_internal = static_cast<float>(size) - (theme::border::width * 2.0f);

        float base_padding = 24.0f;
        switch (size) {
            case ButtonSize::Small:
                base_padding = 12.0f;
                break;
            case ButtonSize::Medium:
                base_padding = 12.0f;
                break;
            case ButtonSize::Large:
            default:
                base_padding = 24.0f;
                break;
        }

        const float button_padding_internal = base_padding - (theme::border::width * 2.0f);

        enable_focus();

        set_display(Display::Flex);
        set_position(Position::Relative);
        set_flex_direction(FlexDirection::Row);
        set_align_items(AlignItems::Center);
        set_justify_content(JustifyContent::Center);

        set_padding_right(button_padding_internal);
        set_padding_left(button_padding_internal);

        set_width_auto();
        set_height(float_size_internal);
        set_min_height(float_size_internal);
        set_max_height(float_size_internal);

        set_border_width(theme::border::width);
        set_border_radius(theme::border::radius_md);

        ContextId context = get_current_context();

        auto focus_border = context.create_element<FocusBorder>(this, true);
        focus_border->set_border_radius(theme::border::radius_md + theme::border::width * 4.0f);

        switch (size) {
            case ButtonSize::Small: {
                label = context.create_element<Label>(this, text, LabelStyle::Annotation);
                break;
            }
            case ButtonSize::Medium:
                label = context.create_element<Label>(this, text, LabelStyle::Small);
                break;
            case ButtonSize::Large:
            default:
                label = context.create_element<Label>(this, text, LabelStyle::Normal);
                break;
        }

        set_cursor(Cursor::Pointer);
        set_color(theme::color::Text);
        set_tab_index(TabIndex::Auto);
        hover_style.set_color(theme::color::Text);
        focus_style.set_color(theme::color::Text);
        disabled_style.set_color(theme::color::TextDim, 128);
        hover_disabled_style.set_color(theme::color::Text, 128);

        apply_button_style(style);

#ifdef RECOMPUI_BUTTON_DEBUG
        set_debug_id(get_id() + "(" + text + ")" + get_id());
        label->set_debug_id(get_debug_id() + " > Label");
#endif
    }

    void Button::process_event(const Event &e) {
        switch (e.type) {
        case EventType::Click:
            if (is_enabled()) {
                for (const auto &function : pressed_callbacks) {
                    function();
                }
            }
            break;
        case EventType::Hover: 
            set_style_enabled(hover_state, std::get<EventHover>(e.variant).active && is_enabled());
            break;
        case EventType::Enable:
            {
                bool enable_active = std::get<EventEnable>(e.variant).active;
                set_style_enabled(disabled_state, !enable_active);
                if (enable_active) {
                    set_cursor(Cursor::Pointer);
                    set_focusable(true);
                }
                else {
                    set_cursor(Cursor::None);
                    set_focusable(false);
                }
            }
            break;
        case EventType::Focus:
            set_style_enabled(focus_state, std::get<EventFocus>(e.variant).active);
            break;
        case EventType::Update:
            break;
        default:
            assert(false && "Unknown event type.");
            break;
        }
    }

    void Button::add_pressed_callback(std::function<void()> callback) {
        pressed_callbacks.emplace_back(callback);
    }

    void Button::apply_button_style(ButtonStyle new_style) {
        style = new_style;
        switch (style) {
        case ButtonStyle::Primary: {
            apply_theme_style(theme::color::Primary);
            break;
        }
        case ButtonStyle::Secondary: {
            apply_theme_style(theme::color::Secondary);
            break;
        }
        case ButtonStyle::Tertiary: {
            apply_theme_style(theme::color::Elevated);
            break;
        }
        case ButtonStyle::Success: {
            apply_theme_style(theme::color::Success);
            break;
        }
        case ButtonStyle::Warning: {
            apply_theme_style(theme::color::Warning);
            break;
        }
        case ButtonStyle::Danger: {
            apply_theme_style(theme::color::Danger);
            break;
        }
        case ButtonStyle::Basic: {
            apply_theme_style(theme::color::Elevated, true);
            break;
        }
        default:
            assert(false && "Unknown button style.");
            break;
        }
    }

    void Button::apply_theme_style(recompui::theme::color color, bool is_basic) {
        uint8_t border_opacity = is_basic ? 0 : 255;
        uint8_t background_opacity = is_basic ? 0 : 26;
        uint8_t background_hover_opacity = 77;
        uint8_t border_hover_opacity = is_basic ? background_hover_opacity : 255;

        if (color == theme::color::Elevated) {
            background_hover_opacity = theme::get_theme_color(theme::color::Elevated).a;
            if (is_basic) {
                border_hover_opacity = background_hover_opacity;
            } else {
                background_opacity = theme::get_theme_color(theme::color::ElevatedSoft).a;
                border_opacity = theme::get_theme_color(theme::color::ElevatedBorder).a;
                border_hover_opacity = theme::get_theme_color(theme::color::ElevatedBorderHard).a;
            }
        }

        set_border_color(color, border_opacity);
        set_background_color(color, background_opacity);
        hover_style.set_border_color(color, border_hover_opacity);
        hover_style.set_background_color(color, background_hover_opacity);
        focus_style.set_border_color(color, border_hover_opacity);
        focus_style.set_background_color(color, background_hover_opacity);
        disabled_style.set_border_color(color, border_opacity / 4);
        disabled_style.set_background_color(color, background_opacity / 4);
        hover_disabled_style.set_border_color(color, border_hover_opacity / 4);
        hover_disabled_style.set_background_color(color, background_hover_opacity / 4);

        // Printed action cards: solid yellow reset, blue primary actions and
        // readable dark text for the mint/pink/success variants.
        if (color == theme::color::Warning) {
            set_background_color(Color{255, 203, 5, 255});
            set_border_color(Color{255, 203, 5, 255});
            hover_style.set_background_color(Color{255, 222, 95, 255});
            focus_style.set_background_color(Color{255, 222, 95, 255});
            hover_style.set_border_color(theme::color::Primary);
            focus_style.set_border_color(theme::color::Primary);
        } else if (color == theme::color::Primary) {
            set_background_color(theme::color::Primary);
            set_color(theme::color::White);
            hover_style.set_background_color(theme::color::PrimaryD);
            focus_style.set_background_color(theme::color::PrimaryD);
            hover_style.set_color(theme::color::White);
            focus_style.set_color(theme::color::White);
        } else {
            focus_style.set_border_color(theme::color::Secondary);
        }

        add_style(&hover_style, hover_state);
        add_style(&focus_style, focus_state);
        add_style(&disabled_style, disabled_state);
        add_style(&hover_disabled_style, { hover_state, disabled_state });
    }

    void Button::set_text(std::string_view text) {
        label->set_text(text);
    }
};
