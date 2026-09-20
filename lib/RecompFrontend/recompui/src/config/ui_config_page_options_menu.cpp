#include "ui_config_page_options_menu.h"


namespace recompui {

ConfigPageOptionsMenu::ConfigPageOptionsMenu(
    ResourceId rid,
    Element *parent,
    recomp::config::Config *config,
    bool is_internal
) : ConfigPage(rid, parent, Events(EventType::Hover, EventType::Update, EventType::MenuAction)),
    config(config),
    is_internal(is_internal)
{
    ContextId context = recompui::get_current_context();
    set_as_navigation_container(NavigationType::Vertical);

    render_config_options();
    description_container = context.create_element<Element>(body->get_right(), 0, "p", true);
    description_container->set_typography(theme::Typography::Body);
    description_container->set_color(theme::color::Text);
    description_container->set_line_height(28.0f);
    description_container->set_padding(8.0f);
    set_description_text("");

    if (config->requires_confirmation) {
        add_footer();
        render_confirmation_footer();
    }
}

void ConfigPageOptionsMenu::set_description_text(const std::string &text) {
    if (description_container) {
        if (is_internal) {
            description_container->set_text_unsafe(text);
        } else {
            description_container->set_text(text);
        }
    }
}

ConfigOptionElement* ConfigPageOptionsMenu::get_element_from_option_id(const std::string &option_id) {
    for (auto *element : config_option_elements) {
        if (element->get_option_id() == option_id) {
            return element;
        }
    }
    return nullptr;
}

void ConfigPageOptionsMenu::perform_option_render_updates() {
    using ConfigOptionUpdateType = recomp::config::ConfigOptionUpdateType;
    queue_update();

    auto options_updates = config->get_config_option_updates();
    bool has_updates = !options_updates.empty();
    for (auto &option_update : options_updates) {
        size_t option_index = option_update.option_index;
        auto schema = config->get_config_schema();
        std::string &option_id = schema.options[option_index].id;
        ConfigOptionElement* element = get_element_from_option_id(option_id);
        if (element == nullptr) {
            printf("Failed to update conf option: '%s'\n", option_id.c_str());
            continue;
        }
        for (auto &update_type :option_update.updates) {
            switch (update_type) {
                case ConfigOptionUpdateType::Disabled: {
                    element->update_disabled();
                    break;
                }
                case ConfigOptionUpdateType::Hidden: {
                    element->update_hidden();
                    break;
                }
                case ConfigOptionUpdateType::EnumDetails: {
                    ConfigOptionEnum *enum_element = static_cast<ConfigOptionEnum*>(element);
                    enum_element->update_enum_details();
                    break;
                }
                case ConfigOptionUpdateType::EnumDisabled: {
                    ConfigOptionEnum *enum_element = static_cast<ConfigOptionEnum*>(element);
                    enum_element->update_enum_disabled();
                    break;
                }
                case ConfigOptionUpdateType::Value: {
                    element->update_value();
                    break;
                }
                case ConfigOptionUpdateType::Description: {
                    if (description_container && description_option_id == option_id) {
                        set_description_text(config->get_option(option_index).description);
                    }
                    break;
                }
            }
        }
    }

    config->clear_config_option_updates();
}

void ConfigPageOptionsMenu::process_event(const Event &e) {
    switch (e.type) {
    case EventType::Hover: {
        bool active = std::get<EventHover>(e.variant).active;
        if (!active) {
            set_description_text("");
        }
        break;
    }
    case EventType::Update: {
        if (apply_button != nullptr) {
            bool apply_enabled = this->apply_button->is_enabled();
            bool is_dirty = config->is_dirty();
            if (apply_enabled != is_dirty) {
                apply_button->set_enabled(is_dirty);
            }
        }
        perform_option_render_updates();
        break;
    }
    case EventType::MenuAction: {
        auto action = std::get<EventMenuAction>(e.variant).action;
        if (action == MenuAction::Apply) {
            if (config->requires_confirmation) {
                config->save_config();
            }
        }
        break;
    }
    default:
        assert(false && "Unknown event type.");
        break;
    }
}

void ConfigPageOptionsMenu::render_confirmation_footer() {
    ContextId context = recompui::get_current_context();
    footer->set_as_navigation_container(NavigationType::Horizontal);

    apply_button = context.create_element<Button>(footer->get_right(), "Apply", ButtonStyle::Secondary);
    apply_button->set_enabled(false);
    apply_button->set_as_primary_focus();
    apply_button->add_pressed_callback([this]() {
        this->config->save_config();
        this->apply_button->set_enabled(this->config->is_dirty());
    });
}

void ConfigPageOptionsMenu::on_set_option_value(const std::string &option_id, recomp::config::ConfigValueVariant value) {
    config->set_option_value(option_id, value);
    if (config->requires_confirmation && apply_button != nullptr) {
        apply_button->set_enabled(config->is_dirty());
    }
}

void ConfigPageOptionsMenu::render_config_options() {
    ContextId context = recompui::get_current_context();
    Element *body_left = get_body()->get_left();
    body_left->clear_children();
    body_left->set_padding(0.0f);

    body_left->set_display(Display::Block);
    body_left->set_position(Position::Relative);
    body_left->set_height(100.0f, Unit::Percent);
    {
        auto body_left_scroll = context.create_element<Element>(body_left, 0, "div", false);
        body_left_scroll->set_display(Display::Block);
        body_left_scroll->set_width(100.0f, Unit::Percent);
        body_left_scroll->set_min_height(100.0f, Unit::Percent);
        body_left_scroll->set_max_height(100.0f, Unit::Percent);
        body_left_scroll->set_padding(16.0f);
        body_left_scroll->set_overflow_y(Overflow::Auto);
        body_left_scroll->set_as_navigation_container(NavigationType::Vertical);

        config_option_elements.clear();
        bound_on_option_hover = [this](const std::string &option_id) {
            this->on_option_hover(option_id);
        };
        bound_set_option_value = [this](const std::string &option_id, recomp::config::ConfigValueVariant value) {
            this->on_set_option_value(option_id, value);
        };
        auto schema = config->get_config_schema();
        for (size_t i = 0; i < schema.options.size(); i++) {
            auto &config_option = schema.options[i];
            ConfigOptionElement *element = nullptr;
            switch (config_option.type) {
                case recomp::config::ConfigOptionType::Enum: {
                    element = context.create_element<ConfigOptionEnum>(
                        body_left_scroll,
                        config_option.id,
                        i,
                        config,
                        bound_set_option_value,
                        bound_on_option_hover
                    );
                    break;
                }
                case recomp::config::ConfigOptionType::Number: {
                    element = context.create_element<ConfigOptionNumber>(
                        body_left_scroll,
                        config_option.id,
                        i,
                        config,
                        bound_set_option_value,
                        bound_on_option_hover
                    );
                    break;
                }
                case recomp::config::ConfigOptionType::String: {
                    element = context.create_element<ConfigOptionString>(
                        body_left_scroll,
                        config_option.id,
                        i,
                        config,
                        bound_set_option_value,
                        bound_on_option_hover
                    );
                    break;
                }
                case recomp::config::ConfigOptionType::Bool: {
                    element = context.create_element<ConfigOptionBool>(
                        body_left_scroll,
                        config_option.id,
                        i,
                        config,
                        bound_set_option_value,
                        bound_on_option_hover
                    );
                    break;
                }
                default: {
                    assert(false && "Unknown config option type");
                }
            };
            element->update_disabled();
            element->update_hidden();
            config_option_elements.push_back(element);
        }
    }
}

void ConfigPageOptionsMenu::on_option_hover(const std::string &option_id) {
    if (description_container) {
        description_option_id = option_id;
        set_description_text(config->get_option(option_id).description);
    }
}

} // namespace recompui
