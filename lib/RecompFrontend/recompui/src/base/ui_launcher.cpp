#include "recompui/recompui.h"
#include "recompui/config.h"
#include "recompui/program_config.h"
#include "base/ui_launcher.h"
#include "composites/ui_mod_menu.h"
#include "util/file.h"
#include "librecomp/game.hpp"
#include "ultramodern/ultramodern.hpp"
#include "nfd.h"
#include <filesystem>
#include "elements/ui_svg.h"
#include "elements/ui_config_page.h"
#include "ui_utils.h"

namespace Constants {
    constexpr float option_height = 136.0f;
    constexpr float option_padding = 8.0f;
    constexpr float option_height_inner = option_height - (option_padding * 2.0f);

    constexpr float max_menu_width = 1440.0f - 64.0f;
    constexpr float header_height = 96.0f+16.0f;
    constexpr float footer_height = 96.0f+16.0f;
    constexpr float max_body_height = option_height * 4.5f;
}

// TODO: Store somewhere else and have base game register/initialize.
extern std::vector<recomp::GameEntry> supported_games;

static std::string generate_thumbnail_src_for_game(const std::string& game_id) {
    return "?/game/" + game_id + "/thumb";
}

// TODO: Used in multiple places, should be combined.
static std::string generate_thumbnail_src_for_mod(const std::string &mod_id) {
    return "?/mods/" + mod_id + "/thumb";
}

namespace recompui {
    using on_select_option_t = std::function<void(const std::string &id)>;

    class GameModeOption : public Element {
    protected:
        std::string mode_id;
        on_select_option_t on_select_option = nullptr;
        Image *thumbnail_image = nullptr;
        Element *body_container = nullptr;
        Label *name_label = nullptr;

        Style hover_style;
        Style pulsing_style;
        bool selected = false;

        bool instant_scroll = false;
        
        void process_event(const Event& e) override {
            switch (e.type) {
            case EventType::Focus:
                set_style_enabled(focus_state, std::get<EventFocus>(e.variant).active);
                scroll_into_view(!instant_scroll);
                instant_scroll = false;
                queue_update();
                break;
            case EventType::Hover:
                set_style_enabled(hover_state, std::get<EventHover>(e.variant).active);
                break;
            case EventType::Update:
                if (is_style_enabled(focus_state)) {
                    pulsing_style.set_color(recompui::get_pulse_color(750));
                    apply_styles();
                    queue_update();
                }
                break;
            case EventType::Click:
                on_select_option(mode_id);
                break;
            default:
                break;
            }
        }
        std::string_view get_type_name() override { return "GameModeOption"; }
    public:
        GameModeOption(ResourceId rid, Element* parent, on_select_option_t on_select_option, const std::string &mode_id, const std::string &name, const std::string &thumbnail) : Element(rid, parent, Events(EventType::Update, EventType::Click, EventType::Hover, EventType::Focus)) {
            ContextId context = get_current_context();
            this->on_select_option = on_select_option;
            this->mode_id = mode_id;

            set_display(Display::Flex);
            set_flex_direction(FlexDirection::Row);
            set_width(100.0f, Unit::Percent);
            set_height(Constants::option_height);
            set_padding(Constants::option_padding);
            set_border_left_width(2.0f);
            set_border_color(theme::color::Transparent);
            set_background_color(theme::color::Transparent);
            set_cursor(Cursor::Pointer);
            set_color(theme::color::Text);
            set_focusable(true);
            set_tab_index_auto();

            hover_style.set_background_color(theme::color::Elevated);
            pulsing_style.set_color(theme::color::SecondaryA80);

            {
                thumbnail_image = context.create_element<Image>(this, thumbnail);
                thumbnail_image->set_width(Constants::option_height_inner);
                thumbnail_image->set_height(Constants::option_height_inner);
                thumbnail_image->set_min_width(Constants::option_height_inner);
                thumbnail_image->set_min_height(Constants::option_height_inner);

                body_container = context.create_element<Element>(this);
                body_container->set_display(Display::Flex);
                body_container->set_flex_direction(FlexDirection::Column);
                body_container->set_justify_content(JustifyContent::Center);
                body_container->set_align_items(AlignItems::FlexStart);
                body_container->set_width_auto();
                body_container->set_margin_left(16.0f);
                body_container->set_padding_top(8.0f);
                body_container->set_padding_bottom(8.0f);
                body_container->set_height(Constants::option_height_inner);
                body_container->set_max_height(Constants::option_height_inner);
                body_container->set_overflow_y(Overflow::Hidden);

                {
                    name_label = context.create_element<Label>(body_container, name, theme::Typography::Header2);
                } // body_container
            } // this

            add_style(&hover_style, hover_state);
            add_style(&pulsing_style, { focus_state });
        };

        const std::string& get_mode_id() const {
            return mode_id;
        }

        void instant_focus_and_scroll() {
            instant_scroll = true;
            focus();
        }
    };

    class GameModeMenu : public Element {
    protected:
        Element *wrapper = nullptr;
        recompui::Element *body;
        std::vector<GameModeOption *> game_mode_options;
        //! Hack: Can't focus until a delayed update from when the options are cleared. Options get cleared then this is set to true.
        bool queue_make_options;
        //! Hack: If it isn't queued it just won't scroll into view when reopening the menu.
        int queue_scroll_into_view = 0;

        std::u8string game_id;
        std::string game_display_name = "";
        std::span<const char> game_thumbnail;
        std::string cur_game_mode_id = "";
        std::unordered_set<std::string> loaded_thumbnails;

        void process_event(const Event& e) override {
            switch (e.type) {
            case EventType::Update:
                {
                    if (queue_make_options) {
                        make_options();
                        queue_make_options = false;
                        //! Hack: Wait two updates.
                        queue_scroll_into_view = 2;
                        queue_update();
                    } else if (queue_scroll_into_view) {
                        queue_scroll_into_view--;
                        if (queue_scroll_into_view == 0) {
                            for (auto option : game_mode_options) {
                                if (option->get_mode_id() == cur_game_mode_id) {
                                    option->scroll_into_view(false);
                                    break;
                                }
                            }
                        } else {
                            queue_update();
                        }
                    }
                }
                break;
            case EventType::MenuAction: {
                auto& action = std::get<EventMenuAction>(e.variant);
                if (action.action == MenuAction::Toggle || action.action == MenuAction::Back) {
                    get_launcher_menu()->hide_game_mode_menu();
                }
                break;
            }
            default:
                break;
            }
        }
        std::string_view get_type_name() override { return "GameModeMenu"; }
    public:
        GameModeMenu(ResourceId rid, Element* parent) : Element(rid, parent, Events(EventType::MenuAction), "div", false) {
            set_display(Display::Flex);
            set_align_items(AlignItems::Center);
            set_justify_content(JustifyContent::Center);
            set_position(Position::Absolute);
            set_left(0.0f);
            set_top(0.0f);
            set_height(100.0f, Unit::Percent);
            set_width(100.0f, Unit::Percent);
            set_background_color(theme::color::ModalOverlay);

            auto context = get_current_context();
            wrapper = context.create_element<Element>(this);
            wrapper->set_position(Position::Relative);
            wrapper->set_height_auto();
            wrapper->set_width(100.0f, Unit::Percent);
            wrapper->set_max_width(Constants::max_menu_width);
            wrapper->set_as_navigation_container(NavigationType::Vertical);

            auto header = context.create_element<Element>(wrapper);
            header->set_display(Display::Flex);
            header->set_align_items(AlignItems::Center);
            header->set_justify_content(JustifyContent::Center);
            header->set_height(Constants::header_height);
            header->set_width(100.0f, Unit::Percent);
            header->set_gap(16.0f);

            auto body_wrapper = context.create_element<Element>(wrapper);
            body_wrapper->set_position(Position::Relative);
            body_wrapper->set_height_auto();
            body_wrapper->set_max_height(Constants::max_body_height);
            body_wrapper->set_width(100.0f, Unit::Percent);
            body_wrapper->set_overflow_y(Overflow::Scroll);

            body = context.create_element<Element>(body_wrapper);
            body->set_position(Position::Relative);
            body->set_height_auto();
            body->set_width(100.0f, Unit::Percent);
            body->set_as_navigation_container(NavigationType::Vertical);

            auto footer = context.create_element<Element>(wrapper);
            footer->set_display(Display::Flex);
            footer->set_justify_content(JustifyContent::SpaceBetween);
            footer->set_align_items(AlignItems::Center);
            footer->set_height(Constants::footer_height);
            footer->set_width(100.0f, Unit::Percent);
            footer->set_as_navigation_container(NavigationType::Horizontal);

            // header
            {
                context.create_element<Label>(header, "Select Game Mode", theme::Typography::Header3);
            }

            // footer
            {
                auto footer_left = context.create_element<Element>(footer);
                footer_left->set_flex_grow(1.0f);
                footer_left->set_flex_shrink(1.0f);
                footer_left->set_flex_basis_auto();
                footer_left->set_display(Display::Flex);
                footer_left->set_flex_direction(FlexDirection::Row);
                footer_left->set_justify_content(JustifyContent::FlexStart);
                footer_left->set_align_items(AlignItems::Center);
                {
                    auto back_button = context.create_element<Button>(
                        footer_left,
                        "Go back",
                        ButtonStyle::Basic,
                        ButtonSize::Medium
                    );
                    back_button->set_width_auto();
                    back_button->set_white_space(WhiteSpace::Nowrap);
                    back_button->add_pressed_callback([]() {
                        get_launcher_menu()->hide_game_mode_menu();
                    });
                }
            }
        };

        ~GameModeMenu() {
            clear_loaded_thumbnails();
        }

        void clear_loaded_thumbnails() {
            for (const std::string& thumbnail : loaded_thumbnails) {
                recompui::release_image(thumbnail);
            }

            loaded_thumbnails.clear();
        }

        void hide() {
            display_hide();
            clear_loaded_thumbnails();
        }

        void on_select_game_mode(const std::string &game_mode_mod_id) {
            cur_game_mode_id = game_mode_mod_id;
            on_start_game_mode();
        }

        void on_start_game_mode() {
            get_launcher_menu()->hide_game_mode_menu();
            recomp::start_game(this->game_id, this->cur_game_mode_id);
            recompui::hide_all_contexts();
        }

        void make_options() {
            clear_loaded_thumbnails();

            auto context = get_current_context();
            on_select_option_t on_select_game_mode_cb = [this](const std::string &id) {
                this->on_select_game_mode(id);
            };

            cur_game_mode_id.clear();
            std::string prev_game_mode_id = recomp::mods::get_latest_game_mode_id();
            bool found_previous = false;

            std::string game_thumbnail_name = generate_thumbnail_src_for_game((const char *)(this->game_id.c_str()));
            if (!game_thumbnail.empty()) {
                std::vector<char> game_thumbnail_bytes(this->game_thumbnail.data(), this->game_thumbnail.data() + this->game_thumbnail.size());
                recompui::queue_image_from_bytes_file(game_thumbnail_name, game_thumbnail_bytes);
                loaded_thumbnails.emplace(game_thumbnail_name);
            }

            auto normal_game_option = context.create_element<GameModeOption>(body, on_select_game_mode_cb, std::string{}, game_display_name, game_thumbnail_name);
            game_mode_options.push_back(normal_game_option);
            
            auto mod_id = get_game_mod_id();
            std::vector<recomp::mods::ModDetails> mods = recomp::mods::get_all_mod_details(mod_id);
            for (const auto &mod : mods) {
                if (mod.custom_gamemode && (recomp::mods::is_mod_enabled(mod.mod_id) || recomp::mods::is_mod_auto_enabled(mod.mod_id))) {
                    const std::vector<char>& mod_thumbnail = recomp::mods::get_mod_thumbnail(mod.mod_id);
                    std::string mod_thumbnail_name = generate_thumbnail_src_for_mod(mod.mod_id);
                    if (!mod_thumbnail.empty()) {
                        recompui::queue_image_from_bytes_file(mod_thumbnail_name, mod_thumbnail);
                        loaded_thumbnails.emplace(mod_thumbnail_name);
                    }

                    GameModeOption *mod_game_option = context.create_element<GameModeOption>(body, on_select_game_mode_cb, mod.mod_id, mod.display_name, mod_thumbnail_name);
                    game_mode_options.push_back(mod_game_option);
                    if (mod.mod_id == prev_game_mode_id) {
                        found_previous = true;
                        mod_game_option->instant_focus_and_scroll();
                    }
                }
            }

            // Failsafe if previous mode wasn't found (mod removed or id changed).
            if (found_previous == false || prev_game_mode_id.empty()) {
                normal_game_option->instant_focus_and_scroll();
                cur_game_mode_id.clear();
            }
            else {
                cur_game_mode_id = std::move(prev_game_mode_id);
            }
        }

        void show(const std::u8string &game_id, const std::string &game_display_name, std::span<const char> game_thumbnail) {
            this->game_id = game_id;
            this->game_display_name = game_display_name;
            this->game_thumbnail = game_thumbnail;

            display_show();

            body->clear_children();
            game_mode_options.clear();

            //! Hack: Can't make options until next update otherwise focus doesn't work.
            queue_make_options = true;
            queue_update();
        }
    };

    GameOptionsMenu::GameOptionsMenu(
        ResourceId rid, Element* parent, std::u8string game_id, std::string mod_game_id, std::string game_display_name, std::span<const char> game_thumbnail, GameOptionsMenuLayout layout
    ) : Element(rid, parent, 0, "div", false),
        game_id(game_id),
        mod_game_id(mod_game_id),
        game_display_name(game_display_name),
        game_thumbnail(game_thumbnail),
        layout(layout)
    {
        rom_valid = recomp::is_rom_valid(game_id);

        set_position(Position::Absolute);
        set_display(Display::Flex);
        set_height_auto();
        set_width(50.0f, Unit::Percent);
        set_flex_direction(FlexDirection::Column);
        set_gap(8.0f);
        set_align_items(AlignItems::Center);

        set_as_navigation_container(NavigationType::Vertical);
        set_nav_wrapping(true);

        switch (layout) {
            case GameOptionsMenuLayout::Left:
                set_left(24.0f);
                set_bottom(24.0f);
                break;
            case GameOptionsMenuLayout::Center:
                set_left(50.0f, Unit::Percent);
                set_bottom(25.0f, Unit::Percent);
                set_translate_2D(-50.0f, 0.0f, Unit::Percent);
                break;
            case GameOptionsMenuLayout::Right:
                set_right(24.0f);
                set_bottom(24.0f);
                break;
        }
    }

    void GameOptionsMenu::select_rom(std::function<void(bool)> callback) {
        recompui::file::open_file_dialog([this, callback](bool success, const std::filesystem::path& path) {
            if (success) {
                recomp::RomValidationError rom_error = recomp::select_rom(path, this->game_id);
                switch (rom_error) {
                    case recomp::RomValidationError::Good:
                        callback(true);
                        return;
                    case recomp::RomValidationError::FailedToOpen:
                        recompui::message_box("Failed to open ROM file.");
                        break;
                    case recomp::RomValidationError::NotARom:
                        recompui::message_box("This is not a valid ROM file.");
                        break;
                    case recomp::RomValidationError::IncorrectRom:
                        recompui::message_box("This ROM is not the correct game.");
                        break;
                    case recomp::RomValidationError::NotYet:
                        recompui::message_box("This game isn't supported yet.");
                        break;
                    case recomp::RomValidationError::IncorrectVersion:
                        recompui::message_box(
                                "This ROM is the correct game, but the wrong version.\nThis project requires the NTSC-U N64 version of the game.");
                        break;
                    case recomp::RomValidationError::OtherError:
                        recompui::message_box("An unknown error has occurred.");
                        break;
                }
            }
            callback(false);
        });
    }

    GameOption *GameOptionsMenu::add_option(const std::string& title, std::function<void()> callback) {
        auto context = get_current_context();
        auto option = context.create_element<GameOption>(this, title, callback, layout);
        options.push_back(option);
        return option;
    }

    GameOption *GameOptionsMenu::add_start_game_or_load_rom_option(const std::string& load_rom_title, const std::string& start_game_title) {
        GameOption *option = add_option(rom_valid ? start_game_title : load_rom_title, nullptr);
        option->set_as_primary_focus(true);

        auto context = get_current_context();
        context.set_autofocus_element(option);

        option->set_callback([this, option, start_game_title]() {
            if (this->rom_valid) {
                recompui::update_game_mod_id(this->mod_game_id);
                if (recomp::mods::game_mode_count(this->mod_game_id, false) > 0) {
                    get_launcher_menu()->show_game_mode_menu(this->game_id, this->game_display_name, this->game_thumbnail);
                } else {
                    recomp::start_game(this->game_id, {});
                    recompui::hide_all_contexts();
                }
            } else {
                select_rom([this, option, start_game_title](bool success) {
                    if (success) {
                        this->rom_valid = true;

                        recompui::ContextId ui_context = recompui::get_launcher_context_id();
                        bool opened = ui_context.open_if_not_already();
                        option->set_title(start_game_title);
                        if (opened) {
                            ui_context.close();
                        }
                    }
                });
            }
        });

        start_game_option = option;
        return option;
    }

    GameOption *GameOptionsMenu::add_setup_controls_option(const std::string& title) {
        return add_option(title, [this]() {
            recompui::update_game_mod_id(this->mod_game_id);
            recompui::config::set_tab(recompui::config::controls::id);
            recompui::hide_all_contexts();
            recompui::config::open();
        });
    }

    GameOption *GameOptionsMenu::add_settings_option(const std::string& title) {
        return add_option(title, [this]() {
            recompui::update_game_mod_id(this->mod_game_id);
            recompui::config::set_tab(recompui::config::general::id);
            recompui::hide_all_contexts();
            recompui::config::open();
        });
    }

    GameOption *GameOptionsMenu::add_mods_option(const std::string& title) {
        return add_option(title, [this]() {
            recompui::update_game_mod_id(this->mod_game_id);
            recompui::config::set_tab(recompui::config::mods::id);
            recompui::hide_all_contexts();
            recompui::config::open();
        });
    }

    GameOption *GameOptionsMenu::add_exit_option(const std::string& title) {
        return add_option(title, []() {
            ultramodern::quit();
        });
    }

    LauncherMenu::LauncherMenu(ResourceId rid, Document* parent, ContextId context) : Element(rid, parent, 0, "div", false) {
        set_position(Position::Relative);
        set_width(100.0f, Unit::Percent);
        set_height(100.0f, Unit::Percent);
        set_background_color(theme::color::Background1);

        background_wrapper = context.create_element<Element>(this, 0, "div", false);
        background_wrapper->set_position(Position::Absolute);
        background_wrapper->set_top(0);
        background_wrapper->set_left(0);
        background_wrapper->set_height(100.0f, Unit::Percent);
        background_wrapper->set_width(100.0f, Unit::Percent);

        {
            default_title_wrapper = context.create_element<Element>(this, 0, "div", false);
            default_title_wrapper->set_position(Position::Absolute);
            default_title_wrapper->set_top(25.0f, Unit::Percent);
            default_title_wrapper->set_left(50.0f, Unit::Percent);
            default_title_wrapper->set_translate_2D(-50.0f, -50.0f, Unit::Percent);
            default_title_wrapper->set_width_auto();
            default_title_wrapper->set_height_auto();
            Label *title = context.create_element<Label>(default_title_wrapper, programconfig::get_program_name(), theme::Typography::Header1);
            title->set_color(theme::color::Primary);
        }

        menu_container = context.create_element<Element>(this, 0, "div", false);
        menu_container->set_position(Position::Absolute);
        menu_container->set_top(24.0f);
        menu_container->set_right(24.0f);
        menu_container->set_bottom(24.0f);
        menu_container->set_left(24.0f);

        version_label = context.create_element<Label>(this, "v" + recomp::get_project_version().to_string(), LabelStyle::Small);
        version_label->set_color(theme::color::White);
        version_label->set_position(Position::Absolute);
        version_label->set_bottom(4.0f);
        version_label->set_left(4.0f);
    }

    void LauncherMenu::remove_default_title() {
        if (default_title_wrapper != nullptr) {
            remove_child(default_title_wrapper, true);
            default_title_wrapper = nullptr;
        }
    }

    GameOptionsMenu *LauncherMenu::init_game_options_menu(std::u8string game_id, std::string mod_game_id, std::string game_display_name, std::span<const char> game_thumbnail, GameOptionsMenuLayout layout) {
        if (game_options_menu != nullptr) {
            menu_container->remove_child(game_options_menu, false);
        }
        auto context = get_current_context();
        game_options_menu = context.create_element<GameOptionsMenu>(menu_container, game_id, mod_game_id, game_display_name, game_thumbnail, layout);
        recompui::update_game_mod_id(mod_game_id);
        return game_options_menu;
    }

    Svg *LauncherMenu::set_launcher_background_svg(const std::string& svg_path) {
        auto context = get_current_context();
        if (background_svg != nullptr) {
            background_wrapper->clear_children();
            background_svg = nullptr;
        }
        background_svg = context.create_element<Svg>(background_wrapper, svg_path);
        background_svg->set_position(Position::Absolute);
        background_svg->set_top(50.0f, Unit::Percent);
        background_svg->set_left(0);
        background_svg->set_height_auto();
        background_svg->set_width(100.0f, Unit::Percent);
        background_svg->set_translate_2D(0.0f, -50.0f, Unit::Percent);
        return background_svg;
    }

    void LauncherMenu::show_game_mode_menu(std::u8string game_id, std::string game_display_name, std::span<const char> game_thumbnail) {
        game_options_menu->display_hide();
        auto context = get_current_context();
        if (game_mode_menu == nullptr) {
            game_mode_menu = context.create_element<GameModeMenu>(this);
        }
        game_mode_menu->show(game_id, game_display_name, game_thumbnail);
    }

    void LauncherMenu::hide_game_mode_menu() {
        if (game_mode_menu != nullptr) {
            game_mode_menu->hide();
        }

        game_options_menu->display_show();
        auto start_opt = game_options_menu->get_start_game_option();
        if (start_opt != nullptr) {
            start_opt->focus();
        }
    }

    static ContextId launcher_context;
    static LauncherMenu *launcher_menu = nullptr;
    static std::function<void(LauncherMenu *menu)> launcher_init_callback = nullptr;
    static std::function<void(LauncherMenu *menu)> launcher_update_callback = nullptr;
    
    ContextId get_launcher_context_id() {
        return launcher_context;
    }
    
    LauncherMenu *get_launcher_menu() {
        return launcher_menu;
    }

    void register_launcher_init_callback(std::function<void(LauncherMenu *menu)> callback) {
        launcher_init_callback = callback;
    }

    void register_launcher_update_callback(std::function<void(LauncherMenu *menu)> callback) {
        launcher_update_callback = callback;
    }

    void default_launcher_init_callback(LauncherMenu *menu) {
        auto game_options_menu = menu->init_game_options_menu(supported_games[0].game_id, supported_games[0].mod_game_id, supported_games[0].display_name, supported_games[0].thumbnail_bytes, GameOptionsMenuLayout::Center);
        recompui::update_game_mod_id(supported_games[0].mod_game_id);
        game_options_menu->add_default_options();
    }
    
    void init_launcher_menu() {
        launcher_context = create_context();
        launcher_context.open();
        launcher_menu = launcher_context.create_element<LauncherMenu>(launcher_context.get_root_element(), launcher_context);
        if (launcher_init_callback == nullptr) {
            default_launcher_init_callback(launcher_menu);
        } else {
            launcher_init_callback(launcher_menu);
        }
        launcher_context.close();
    }

    void update_launcher_menu() {
        launcher_context.open();
        if (launcher_update_callback) {
            launcher_update_callback(launcher_menu);
        }
        launcher_context.close();
    }
}
