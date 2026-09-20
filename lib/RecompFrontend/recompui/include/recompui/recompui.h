#pragma once
#include <memory>
#include <string>
#include <string_view>
#include <list>

#include "SDL.h"
#include "RmlUi/Core.h"

#include "recompinput/recompinput.h"

#include "../src/util/hsv.h"
#include "../src/elements/ui_button.h"
#include "../src/elements/ui_theme.h"
#include "../src/elements/ui_types.h"

#include "../src/core/ui_context.h"
#include "../src/base/ui_launcher.h"

namespace Rml {
    class ElementDocument;
    class EventListenerInstancer;
    class Context;
    class Event;
}

namespace recompui {
    // Required! Make sure to set the font-family in your rcss to this font's family.
    // the font-family will typically will not be in the filename.
    void register_primary_font(const std::string& font_filename, const std::string& font_family);
    const std::string& get_primary_font_family();
    // Any extra fonts to load after the primary font.
    void register_extra_font(const std::string& font_filename);
    void update_game_mod_id(const std::string &game_mod_id);
    const std::string &get_game_mod_id();

    // Use this to customize the launcher menu after it's created.
    // If set, you will need to initialize the launcher's options, by calling
    // `menu->init_game_options_menu`, and then adding options to it.
    void register_launcher_init_callback(std::function<void(LauncherMenu *menu)> callback);

    // Use this to update the launcher each frame.
    void register_launcher_update_callback(std::function<void(LauncherMenu *menu)> callback);

    // Change only the graphics device while preserving documents and settings.
    // The host must stop the old presentation workers before their deinit hook,
    // and leave normal UI/input processing suspended until the new setup ends.
    void begin_renderer_reconfiguration();
    void end_renderer_reconfiguration();

    // Runs on the UI render thread before input and document updates, including
    // frames with no visible menu or suspended input. Register before startup.
    void register_ui_frame_callback(std::function<void()> callback);

    class UiEventListenerInstancer;

    using event_handler_t = void(const std::string& param, Rml::Event&);

    void queue_event(const SDL_Event& event);
    bool try_deque_event(SDL_Event& out);
    // Suspend a host UI while another process owns interaction. Device hotplug
    // remains active; queued actions and held-key repeats are discarded.
    void set_input_suspended(bool suspended);
    bool is_input_suspended();

    std::unique_ptr<UiEventListenerInstancer> make_event_listener_instancer();
    void register_event(UiEventListenerInstancer& listener, const std::string& name, event_handler_t* handler);

    void show_context(ContextId context, std::string_view param);
    void hide_context(ContextId context);
    void hide_all_contexts();
    bool is_context_shown(ContextId context);
    bool is_context_capturing_input();
    bool is_context_capturing_mouse();
    bool is_any_context_shown();
    ContextId try_close_current_context();

    ContextId get_launcher_context_id();

    void init_styling(const std::filesystem::path& rcss_file);
    void init_prompt_context();
    void open_choice_prompt(
        const std::string& header_text,
        const std::string& content_text,
        const std::string& confirm_label_text,
        const std::string& cancel_label_text,
        std::function<void()> confirm_action,
        std::function<void()> cancel_action,
        ButtonStyle confirm_variant = ButtonStyle::Success,
        ButtonStyle cancel_variant = ButtonStyle::Danger,
        bool focus_on_cancel = true
    );
    void open_info_prompt(
        const std::string& header_text,
        const std::string& content_text,
        const std::string& okay_label_text,
        std::function<void()> okay_action,
        ButtonStyle okay_variant = ButtonStyle::Danger
    );
    void open_notification(
        const std::string& header_text,
        const std::string& content_text
    );
    void close_prompt();
    bool is_prompt_open();
    void update_mod_list(bool scan_mods = true);
    void process_game_started();

    void apply_color_hack();
    void get_window_size(int& width, int& height);
    void open_quit_game_prompt();
    bool get_cursor_visible();
    void set_cursor_visible(bool visible);
    void update_supported_options();

    bool get_cont_active(void);
    void set_cont_active(bool active);
    void activate_mouse();

    void message_box(const char* msg);

    void set_render_hooks();

    Rml::ElementPtr create_custom_element(Rml::Element* parent, std::string tag);
    Rml::ElementDocument* load_document(const std::filesystem::path& path);
    Rml::ElementDocument* create_empty_document();
    Rml::Element* get_child_by_tag(Rml::Element* parent, const std::string& tag);

    void queue_image_from_bytes_rgba32(const std::string &src, const std::vector<char> &bytes, uint32_t width, uint32_t height);
    void queue_image_from_bytes_file(const std::string &src, const std::vector<char> &bytes);
    void release_image(const std::string &src);

    void drop_files(const std::list<std::filesystem::path> &file_list);

    namespace menu_action_mapping {
        struct key_map {
            // End result menu action
            const MenuAction action;
            // Mapped input from controller
            const recompinput::GameInput input;
            // SDL key code from controller -> keyboard
            const int sdl;
            // RML key identifier passed to rmlui
            const Rml::Input::KeyIdentifier rml;
        };

        static const key_map accept =    { MenuAction::Accept,   recompinput::GameInput::ACCEPT_MENU,    SDLK_RETURN, Rml::Input::KI_RETURN };
        static const key_map apply =     { MenuAction::Apply,    recompinput::GameInput::APPLY_MENU,     SDLK_f,      Rml::Input::KI_F };
        static const key_map back =      { MenuAction::Back,     recompinput::GameInput::BACK_MENU,      SDLK_F15,    Rml::Input::KI_F15 };
        static const key_map toggle =    { MenuAction::Toggle,   recompinput::GameInput::TOGGLE_MENU,    SDLK_ESCAPE, Rml::Input::KI_ESCAPE };
        static const key_map tab_left =  { MenuAction::TabLeft,  recompinput::GameInput::TAB_LEFT_MENU,  SDLK_F16,    Rml::Input::KI_F16 };
        static const key_map tab_right = { MenuAction::TabRight, recompinput::GameInput::TAB_RIGHT_MENU, SDLK_F17,    Rml::Input::KI_F17 };

        static const std::unordered_map<Rml::Input::KeyIdentifier, key_map> rml_key_to_action {
            { accept.rml, accept },
            { apply.rml, apply },
            { back.rml, back },
            { toggle.rml, toggle },
            { tab_left.rml, tab_left },
            { tab_right.rml, tab_right }
        };

        MenuAction menu_action_from_rml_key(const Rml::Input::KeyIdentifier& key);
        // Returns a GameInput for a given MenuAction.
        // GameInput::COUNT returned if no mapping exists.
        recompinput::GameInput game_input_from_menu_action(const MenuAction& action);

        // The ultra high F keys are used to give RmlUi unique keys for menu actions that can be invoked from controllers.
        // This allows you to check if InputField.input_id is one of those (e.g. hiding hints). 
        bool is_sdl_input_fake_mapped(int32_t sdl_key);
    };
}
