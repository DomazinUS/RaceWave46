#pragma once

#include "config/ui_config_option.h"
#include "elements/ui_config_page.h"
#include "elements/ui_modal.h"
#include "elements/ui_button.h"
#include "librecomp/config.hpp"
#include "librecomp/mods.hpp"

namespace recompui {
    class ConfigPageOptionsMenu : public ConfigPage {
    protected:
        recomp::config::Config *config;
        bool is_internal = false;

        std::vector<ConfigOptionElement*> config_option_elements;
        Element *description_container = nullptr;
        std::string description_option_id = "";
        Button *apply_button = nullptr;

        virtual void process_event(const Event &e) override;
        std::string_view get_type_name() override { return "ConfigPageOptionsMenu"; }
    private:
        on_option_hover_t bound_on_option_hover;
        set_option_value_t bound_set_option_value;

        void render_config_options();
        void render_confirmation_footer();
        void on_option_hover(const std::string &option_id);
        void on_set_option_value(const std::string &option_id, recomp::config::ConfigValueVariant value);
        ConfigOptionElement* get_element_from_option_id(const std::string &option_id);
        void perform_option_render_updates();
        void set_description_text(const std::string &text);
    public:
        ConfigPageOptionsMenu(
            ResourceId rid,
            Element *parent,
            recomp::config::Config *config,
            bool is_internal = false
        );
        virtual ~ConfigPageOptionsMenu() = default;
    };
} // namespace recompui
