#include "recompui/config.h"
#include "elements/ui_modal.h"
#include "elements/ui_icon_button.h"
#include "ui_config_page_options_menu.h"
#include "recompinput/profiles.h"
#include "util/file.h"
#include "librecomp/game.hpp"

static std::vector<std::pair<std::string, recomp::config::Config>> configs;

struct PendingTab {
    std::string name;
    std::string id;
    recompui::TabCallbacks callbacks;
    bool hidden = false;
};
static std::vector<PendingTab> pending_tabs;
static bool loaded_configs = false;

namespace recompui {
    static recompui::TabbedModal *config_modal = nullptr;

    recomp::config::Config &config::get_config(const std::string &id) {
        for (auto &[config_id, config] : configs) {
            if (config_id == id) {
                return config;
            }
        }
        throw std::runtime_error("Could not find config with ID '" + id + "'.");
    }

    static recomp::config::Config *get_config_ptr(const std::string &id) {
        for (auto &[config_id, config] : configs) {
            if (config_id == id) {
                return &config;
            }
        }
        throw std::runtime_error("No config with ID '" + id + "' has been added to the config modal.");
    }

    void config::create_tab(
        const std::string &name,
        const std::string &id,
        tab_callbacks::create_contents_t create_contents,
        tab_callbacks::can_close_t can_close,
        tab_callbacks::on_close_t on_close
    ) {
        pending_tabs.push_back({
            name,
            id,
            TabCallbacks{
                .create_contents = create_contents,
                .can_close = can_close,
                .on_close = on_close
            }
        });
    }

    recomp::config::Config &config::create_config_tab(const std::string &name, const std::string &id, bool requires_confirmation) {
        configs.push_back(std::make_pair(id, recomp::config::Config(name, id, requires_confirmation)));
        recomp::config::Config &new_config = configs.back().second;
        config::create_tab(
            name,
            id,
            // Create contents
            [id](recompui::ContextId context, Element* parent) {
                context.create_element<ConfigPageOptionsMenu>(parent, get_config_ptr(id), true);
            },
            // Can close
            [id, name](TabCloseContext close_context) {
                recomp::config::Config &config = config::get_config(id);
                if (config.requires_confirmation && config.is_dirty()) {
                    recompui::open_choice_prompt(
                        name + " options have unapplied changes.",
                        "Would you like to apply or discard the changes?",
                        "Apply",
                        "Discard",
                        [id, close_context]() {
                            config::get_config(id).save_config();
                            if (close_context == TabCloseContext::ModalClose) {
                                config::close();
                            }
                        },
                        [id, close_context]() {
                            config::get_config(id).revert_temp_config();
                            if (close_context == TabCloseContext::ModalClose) {
                                config::close();
                            }
                        },
                        recompui::ButtonStyle::Success,
                        recompui::ButtonStyle::Danger,
                        true
                    );
                    return false;
                }

                return true;
            },
            // On close
            [id](TabCloseContext close_context) {
                recomp::config::Config &config = config::get_config(id);
                if (!config.requires_confirmation) {
                    config.save_config();
                }
            }
        );
        return new_config;
    }

    void config::finalize() {
        if (loaded_configs) {
            throw std::runtime_error("Configurations have already been loaded.");
        }

        for (auto &[id, config] : configs) {
            config.load_config();
        }

        recompinput::profiles::load_controls_config(recomp::get_config_path() / (config::controls::id + ".json"));

        loaded_configs = true;
    }

    void config::set_tab_visible(const std::string &id, bool is_visible) {
        if (config_modal == nullptr) {
            for (auto &tab : pending_tabs) {
                if (tab.id == id) {
                    tab.hidden = !is_visible;
                    return;
                }
            }
            throw std::runtime_error("No tab with ID '" + id + "' has been added to the config modal.");
        } else {
            config_modal->set_tab_visible(id, is_visible);
        }
    }

    void config::init_modal() {
        if (!loaded_configs) {
            throw std::runtime_error("Configurations have not been loaded. Call recompui::config::finalize() first.");
        }

        if (config_modal != nullptr) {
            throw std::runtime_error("Config modal has already been initialized.");
        }

        config_modal = TabbedModal::create_modal(ModalType::Fullscreen);
        config_modal->modal_root_context.open();
        for (auto &tab : pending_tabs) {
            config_modal->add_tab(tab.name, tab.id, tab.callbacks.create_contents, tab.callbacks.can_close, tab.callbacks.on_close);
            if (tab.hidden) {
                config_modal->set_tab_visible(tab.id, false);
            }
        }
        config_modal->set_selected_tab(0);
        auto header_right = config_modal->get_header()->get_right();
        auto quit_button = config_modal->modal_root_context.create_element<IconButton>(header_right, "icons/Quit.svg", ButtonStyle::Basic);
        quit_button->add_pressed_callback([]() {
            if (ultramodern::is_game_started()) {
                recompui::open_quit_game_prompt();
            } else {
                ultramodern::quit();
            }
        });
        auto close_button = config_modal->modal_root_context.create_element<IconButton>(header_right, "icons/X.svg", ButtonStyle::Basic);
        close_button->add_pressed_callback([]() {
            config::close();
        });

        config_modal->modal_root_context.close();
    }

    ContextId config::get_config_context_id() {
        if (config_modal == nullptr) {
            throw std::runtime_error("Config modal has not been initialized.");
        }
        return config_modal->modal_root_context;
    }

    void config::set_tab(const std::string &id) {
        if (config_modal == nullptr) {
            throw std::runtime_error("No tab with ID '" + id + "' has been added to the config modal.");
        }

        config_modal->set_selected_tab(id);
    }

    void config::open() {
        if (config_modal == nullptr) {
            throw std::runtime_error("Config modal has not been initialized.");
        }

        config_modal->open();
    }

    bool config::close() {
        if (config_modal == nullptr) {
            throw std::runtime_error("Config modal has not been initialized.");
        }

        return config_modal->close();
    }

    recompui::TabbedModal *config::get_config_modal() {
        if (config_modal == nullptr) {
            throw std::runtime_error("Config modal has not been initialized.");
        }

        return config_modal;
    }
}
