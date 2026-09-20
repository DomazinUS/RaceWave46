#include "base/ui_game_option.h"
#include "ui_utils.h"

namespace recompui {
    GameOption::GameOption(
        ResourceId rid,
        Element* parent,
        const std::string& title,
        std::function<void()> callback,
        GameOptionsMenuLayout layout
    ) : Element(rid, parent, Events(EventType::Click, EventType::Hover, EventType::Enable, EventType::Focus), "button", false),
        title(title),
        callback(callback)
    {
        set_opacity(1.0f);
        set_cursor(Cursor::Pointer);
        enable_focus();
        set_display(Display::Flex);
        set_position(Position::Relative);
        set_align_items(AlignItems::Center);
        switch (layout) {
            case GameOptionsMenuLayout::Left:
                set_justify_content(JustifyContent::FlexStart);
                break;
            case GameOptionsMenuLayout::Center:
                set_justify_content(JustifyContent::Center);
                break;
            case GameOptionsMenuLayout::Right:
                set_justify_content(JustifyContent::FlexEnd);
                break;
        }
        set_height_auto();

        disabled_style.set_tab_index_none();
        disabled_style.set_cursor(Cursor::None);
        
        auto context = get_current_context();
        label = context.create_element<Label>(this, title, theme::Typography::LabelLG);
        set_styles();
    }

    void GameOption::set_styles() {
        set_width(100.0f, Unit::Percent);
        set_padding(16.0f);
        set_border_radius(theme::border::radius_sm);
        set_background_color(theme::color::Transparent);
        set_color(theme::color::TextDim);

        hover_style.set_background_color(theme::color::Elevated);
        hover_style.set_color(theme::color::TextActive);
        focus_style.set_background_color(theme::color::Elevated);
        focus_style.set_color(theme::color::TextActive);
    
        disabled_style.set_opacity(0.5f);
        disabled_style.set_background_color(theme::color::Transparent);
        hover_disabled_style.set_opacity(0.5f);
        hover_disabled_style.set_background_color(theme::color::Transparent);

        add_style(&hover_style, hover_state);
        add_style(&focus_style, focus_state);
        add_style(&disabled_style, disabled_state);
        add_style(&hover_disabled_style, { hover_state, disabled_state });
    }

    void GameOption::process_event(const Event &e) {
        switch (e.type) {
        case EventType::Click:
            if (is_enabled()) {
                callback();
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
        case EventType::Focus: {
            bool active = std::get<EventFocus>(e.variant).active;
            set_style_enabled(focus_state, active);
            if (active) {
                queue_update();
            }
            break;
        }
        case EventType::Update:
            if (is_style_enabled(focus_state)) {
                recompui::Color pulse_color = recompui::get_pulse_color(750);
                focus_style.set_color(pulse_color);
                apply_styles();
                queue_update();
            }
            break;
        default:
            assert(false && "Unknown event type.");
            break;
        }
    }

    void GameOption::set_title(const std::string& new_title) {
        title = new_title;
        label->set_text(new_title);
    }

    void GameOption::set_callback(std::function<void()> new_callback) {
        callback = new_callback;
    }
}
