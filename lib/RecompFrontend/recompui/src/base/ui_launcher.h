#pragma once

#include "recompui/recompui.h"
#include "elements/ui_element.h"
#include "elements/ui_document.h"
#include "elements/ui_label.h"
#include "base/ui_game_option.h"
#include "base/ui_launcher_common.h"
#include "elements/ui_svg.h"

namespace recompui {
    class GameOption;

    class GameOptionsMenu : public Element {
    private:
        void select_rom(std::function<void(bool)> callback);
    protected:
        std::vector<GameOption *> options;
        GameOption *start_game_option = nullptr;
        std::u8string game_id;
        std::string mod_game_id;
        std::string game_display_name;
        std::span<const char> game_thumbnail;
        bool rom_valid = false;
        GameOptionsMenuLayout layout;

        std::string_view get_type_name() override { return "GameOptionsMenu"; }
    public:
        GameOptionsMenu(ResourceId rid, Element* parent, std::u8string game_id, std::string mod_game_id, std::string game_display_name, std::span<const char> game_thumbnail, GameOptionsMenuLayout layout = GameOptionsMenuLayout::Center);

        GameOption *add_option(const std::string& title, std::function<void()> callback);

        GameOption *add_start_game_or_load_rom_option(const std::string& load_rom_title = "Load ROM", const std::string& start_game_title = "Start Game");
        GameOption *add_setup_controls_option(const std::string& title = "Controls");
        GameOption *add_settings_option(const std::string& title = "Settings");
        GameOption *add_mods_option(const std::string& title = "Mods");
        GameOption *add_exit_option(const std::string& title = "Exit");

        GameOption *get_start_game_option() { return start_game_option; }
    
        void add_default_options() {
            add_start_game_or_load_rom_option();
            add_setup_controls_option();
            add_settings_option();
            add_mods_option();
            add_exit_option();
        }

        std::vector<GameOption *> &get_options() { return options; }
    };

    class GameModeMenu;

    class LauncherMenu : public Element {
    protected:
        std::string_view get_type_name() override { return "LauncherMenu"; }
        Element *background_wrapper;
        Svg *background_svg = nullptr;
        Element *menu_container;
        Label *version_label;
        Element *default_title_wrapper;
        GameOptionsMenu *game_options_menu = nullptr;
        GameModeMenu *game_mode_menu = nullptr;
    public:
        LauncherMenu(ResourceId rid, Document* parent, ContextId context);
        GameOptionsMenu *init_game_options_menu(std::u8string game_id, std::string mod_game_id, std::string game_display_name, std::span<const char> game_thumbnail, GameOptionsMenuLayout layout = GameOptionsMenuLayout::Center);
        GameOptionsMenu *get_game_options_menu() { return game_options_menu; }
        Element *get_background_wrapper() { return background_wrapper; }
        GameModeMenu *get_game_mode_menu() { return game_mode_menu; }
        void show_game_mode_menu(std::u8string game_id, std::string game_display_name, std::span<const char> game_thumbnail);
        void hide_game_mode_menu();
        void remove_default_title();
        Svg *set_launcher_background_svg(const std::string& svg_path);
        Element *get_background_container() { return background_wrapper; }
        Element *get_menu_container() { return menu_container; }
    };

    LauncherMenu *get_launcher_menu();
    void init_launcher_menu();
    void update_launcher_menu();
} // namespace recompui
