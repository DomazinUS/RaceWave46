#pragma once

#include "librecomp/config.hpp"
#include "elements/ui_element.h"
#include "elements/ui_label.h"
#include "elements/ui_radio.h"
#include "elements/ui_text_input.h"
#include "elements/ui_slider.h"
#include "elements/ui_toggle.h"

namespace recompui {
    using set_option_value_t = std::function<void(const std::string &option_id, recomp::config::ConfigValueVariant value)>;
    using on_option_hover_t = std::function<void(const std::string &option_id)>;

    class ConfigOptionElement : public Element {
    protected:
        std::string option_id;
        size_t option_index;
        const recomp::config::Config *config;
        set_option_value_t set_option_value;
        on_option_hover_t on_hover;
        Label *name_label = nullptr;

        recomp::config::ConfigValueVariant get_value();
        bool get_disabled();
        bool get_hidden();

        virtual void process_event(const Event &e) override;
        std::string_view get_type_name() override { return "ConfigOptionElement"; }
    public:
        ConfigOptionElement(
            ResourceId rid,
            Element *parent,
            std::string option_id,
            size_t option_index,
            const recomp::config::Config *config,
            set_option_value_t set_option_value,
            on_option_hover_t on_hover
        );
        virtual ~ConfigOptionElement() = default;
        // required overrides
        virtual void update_value() = 0;
        virtual void update_disabled() = 0;
        void update_hidden();
        const std::string &get_option_id() { return option_id; }
    };

class ConfigOptionEnum : public ConfigOptionElement {
protected:
    Radio *radio = nullptr;
    Label *details_label = nullptr;

    std::string_view get_type_name() override { return "ConfigOptionEnum"; }
public:
    ConfigOptionEnum(
        ResourceId rid,
        Element *parent,
        std::string option_id,
        size_t option_index,
        const recomp::config::Config *config,
        set_option_value_t set_option_value,
        on_option_hover_t on_hover
    );

    void update_value() override;
    void update_disabled() override;

    void update_enum_details();
    void update_enum_disabled();
};

class ConfigOptionNumber : public ConfigOptionElement {
protected:
    Slider *slider = nullptr;

    std::string_view get_type_name() override { return "ConfigOptionNumber"; }
public:
    ConfigOptionNumber(
        ResourceId rid,
        Element *parent,
        std::string option_id,
        size_t option_index,
        const recomp::config::Config *config,
        set_option_value_t set_option_value,
        on_option_hover_t on_hover
    );

    void update_value() override;
    void update_disabled() override;
};

class ConfigOptionString : public ConfigOptionElement {
protected:
    TextInput *text_input = nullptr;

    std::string_view get_type_name() override { return "ConfigOptionString"; }
public:
    ConfigOptionString(
        ResourceId rid,
        Element *parent,
        std::string option_id,
        size_t option_index,
        const recomp::config::Config *config,
        set_option_value_t set_option_value,
        on_option_hover_t on_hover
    );

    void update_value() override;
    void update_disabled() override;
};

class ConfigOptionBool : public ConfigOptionElement {
protected:
    Toggle *toggle = nullptr;

    std::string_view get_type_name() override { return "ConfigOptionBool"; }
public:
    ConfigOptionBool(
        ResourceId rid,
        Element *parent,
        std::string option_id,
        size_t option_index,
        const recomp::config::Config *config,
        set_option_value_t set_option_value,
        on_option_hover_t on_hover
    );

    void update_value() override;
    void update_disabled() override;
};

} // namespace recompui
