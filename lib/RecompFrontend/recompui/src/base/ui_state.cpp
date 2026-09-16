#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <SDL_video.h>
#else
#include <SDL2/SDL_video.h>
#endif
#include <chrono>

#include "rt64_render_hooks.h"
#include "../../../../rt64/src/common/rt64_wr64_separate_windows.h"

#include "concurrentqueue.h"

#include "RmlUi/Core.h"
#include "RmlUi/Debugger.h"
#include "RmlUi/Core/RenderInterfaceCompatibility.h"
#include "RmlUi/../../Source/Core/Elements/ElementLabel.h"
#include "RmlUi_Platform_SDL.h"

#include "recompui/recompui.h"
#include "recompui/config.h"
#include "recompui/program_config.h"
#include "recompinput/recompinput.h"
#include "recompinput/profiles.h"

#include "librecomp/game.hpp"

#include "base/ui_launcher.h"
#include "composites/ui_mod_menu.h"
#include "composites/ui_mod_installer.h"
#include "composites/ui_assign_players_modal.h"
#include "renderer/ui_renderer.h"
#include "rml_hacks/ui_rml_hacks.hpp"
#include "rml_elements/ui_rml_elements.h"
#include "util/file.h"

static std::atomic_bool cursor_enabled = true;

void recompui::open_quit_game_prompt() {
    recompui::open_choice_prompt(
        "Are you sure you want to quit?",
        "Any progress since your last save will be lost.",
        "Quit",
        "Cancel",
        []() {
            ultramodern::quit();
        },
        []() {},
        recompui::ButtonStyle::Danger,
        recompui::ButtonStyle::Tertiary,
        true
    );
}

static std::string primary_font = "";
static std::string primary_font_family = "";
void recompui::register_primary_font(const std::string& font_filename, const std::string& font_family) {
    primary_font = font_filename;
    primary_font_family = font_family;
}

const std::string& recompui::get_primary_font_family() {
    return primary_font_family;
}

static std::vector<std::string> extra_fonts;
void recompui::register_extra_font(const std::string& font_filename) {
    extra_fonts.push_back(font_filename);
}

bool recompui::get_cursor_visible() {
    return cursor_enabled.load();
}
void recompui::set_cursor_visible(bool visible) {
    cursor_enabled.store(visible);
}

static bool can_focus(Rml::Element* element) {
    return element->GetOwnerDocument() != nullptr && element->GetProperty(Rml::PropertyId::TabIndex)->Get<Rml::Style::TabIndex>() != Rml::Style::TabIndex::None;
}

//! Copied from lib\RmlUi\Source\Core\Elements\ElementLabel.cpp
// Get the first descending element whose tag name matches one of tags.
static Rml::Element* TagMatchRecursive(const Rml::StringList& tags, Rml::Element* element)
{
	const int num_children = element->GetNumChildren();

	for (int i = 0; i < num_children; i++)
	{
		Rml::Element* child = element->GetChild(i);

		for (const Rml::String& tag : tags)
		{
			if (child->GetTagName() == tag)
				return child;
		}

		Rml::Element* matching_element = TagMatchRecursive(tags, child);
		if (matching_element)
			return matching_element;
	}

	return nullptr;
}

Rml::Element* get_target(Rml::ElementDocument* document, Rml::Element* element) {
    // Labels can have targets, so check if this element is a label.
    if (element->GetTagName() == "label") {
        Rml::ElementLabel* labelElement = (Rml::ElementLabel*)element;
        const Rml::String target_id = labelElement->GetAttribute<Rml::String>("for", "");

        if (target_id.empty())
        {
            const Rml::StringList matching_tags = {"button", "input", "textarea", "progress", "progressbar", "select"};

            return TagMatchRecursive(matching_tags, element);
        }
        else
        {
            Rml::Element* target = labelElement->GetElementById(target_id);
            if (target != element)
                return target;
        }

        return nullptr;
    }
    // Return the element directly if no target exists.
    return element;
}

namespace recompui {
    class UiEventListener : public Rml::EventListener {
        event_handler_t* handler_;
        Rml::String param_;
    public:
        UiEventListener(event_handler_t* handler, Rml::String&& param) : handler_(handler), param_(std::move(param)) {}
        void ProcessEvent(Rml::Event& event) override {
            handler_(param_, event);
        }
    };

    class UiEventListenerInstancer : public Rml::EventListenerInstancer {
        std::unordered_map<Rml::String, event_handler_t*> handler_map_;
        std::unordered_map<Rml::String, UiEventListener> listener_map_;
    public:
        Rml::EventListener* InstanceEventListener(const Rml::String& value, Rml::Element* element) override {
            // Check if a listener has already been made for the full event string and return it if so.
            auto find_listener_it = listener_map_.find(value);
            if (find_listener_it != listener_map_.end()) {
                return &find_listener_it->second;
            }

            // No existing listener, so check if a handler has been registered for this event type and create a listener for it if so.
            size_t delimiter_pos = value.find(':');
            Rml::String event_type = value.substr(0, delimiter_pos);
            auto find_handler_it = handler_map_.find(event_type);
            if (find_handler_it != handler_map_.end()) {
                // A handler was found, create a listener and return it.
                Rml::String event_param = value.substr(std::min(delimiter_pos, value.size()));
                return &listener_map_.emplace(value, UiEventListener{ find_handler_it->second, std::move(event_param) }).first->second;
            }

            return nullptr;
        }

        void register_event(const Rml::String& value, event_handler_t* handler) {
            handler_map_.emplace(value, handler);
        }
    };
}

void recompui::register_event(UiEventListenerInstancer& listener, const std::string& name, event_handler_t* handler) {
    listener.register_event(name, handler);
}

Rml::Element* find_autofocus_element(Rml::Element* start) {
    Rml::Element* cur_element = start;
    Rml::Element* first_found = nullptr;

    while (cur_element) {
        if (cur_element->HasAttribute("autofocus")) {
            break;
        }
        cur_element = RecompRml::FindNextTabElement(cur_element, true);
        // Track the first element that was found to know when we've wrapped around.
        if (!first_found) {
            first_found = cur_element;
        }
        // Stop searching if we found the first element again.
        else {
            if (cur_element == first_found) {
                // Return the first tab element as there was nothing marked with autofocus.
                return first_found;
            }
        }
    }

    return cur_element;
}

struct ContextDetails {
    recompui::ContextId context;
    Rml::ElementDocument* document;
};

class UIState {
    bool mouse_is_active_changed = false;
    std::vector<ContextDetails> shown_contexts{};
public:
    bool mouse_is_active_initialized = false;
    bool mouse_is_active = false;
    bool cont_is_active = false;
    bool await_stick_return_x = false;
    bool await_stick_return_y = false;
    int last_active_mouse_position[2] = {0, 0};
    std::unique_ptr<SystemInterface_SDL> system_interface;
    recompui::RmlRenderInterface_RT64 render_interface;
    Rml::Context* context;
    recompui::UiEventListenerInstancer event_listener_instancer;

    UIState(const UIState& rhs) = delete;
    UIState& operator=(const UIState& rhs) = delete;
    UIState(UIState&& rhs) = delete;
    UIState& operator=(UIState&& rhs) = delete;

    UIState(SDL_Window* window, plume::RenderInterface* interface, plume::RenderDevice* device) {

        system_interface = std::make_unique<SystemInterface_SDL>();
        system_interface->SetWindow(window);
        render_interface.init(interface, device);

        Rml::SetSystemInterface(system_interface.get());
        Rml::SetRenderInterface(render_interface.get_rml_interface());
        Rml::Factory::RegisterEventListenerInstancer(&event_listener_instancer);

        Rml::Initialise();

        recompui::register_custom_elements();

        // Apply the hack to replace RmlUi's default color parser with one that conforms to HTML5 alpha parsing for SASS compatibility
        recompui::apply_color_hack();

        int width, height;
        SDL_GetWindowSizeInPixels(window, &width, &height);
        
        context = Rml::CreateContext("main", Rml::Vector2i(width, height));

        Rml::Debugger::Initialise(context);
        {
            struct FontFace {
                const char* filename;
                bool fallback_face;
            };
            FontFace font_faces[] = {
                {"NotoEmoji-Regular.ttf", true},
                {"promptfont/promptfont.ttf", false},
            };

            for (const FontFace& face : font_faces) {
                auto font = recompui::file::get_asset_path(face.filename);
                Rml::LoadFontFace(font.string(), face.fallback_face);
            }

            if (primary_font.empty()) {
                throw std::runtime_error("No primary font was registered with recompui::register_primary_font");
            }

            auto primary_font_path = recompui::file::get_asset_path(primary_font.c_str());
            Rml::LoadFontFace(primary_font_path.string(), false);

            for (const auto& extra_font : extra_fonts) {
                auto extra_font_path = recompui::file::get_asset_path(extra_font.c_str());
                Rml::LoadFontFace(extra_font_path.string(), false);
            }
        }
    }

    void create_menus() {
        recompui::init_styling(recompui::file::get_asset_path("recomp.rcss"));
        recompui::init_launcher_menu();
        recompui::init_prompt_context();
        recompui::AssignPlayersModal::init();
        recompui::config::init_modal();
    }

    void unload() {
        render_interface.reset();
    }

    void update_primary_input(bool mouse_moved, bool non_mouse_interacted) {
        mouse_is_active_changed = false;
        if (non_mouse_interacted) {
            // controller newly interacted with
            if (mouse_is_active) {
                mouse_is_active = false;
                mouse_is_active_changed = true;
            }
        }
        else if (mouse_moved) {
            // mouse newly interacted with
            if (!mouse_is_active) {
                mouse_is_active = true;
                mouse_is_active_changed = true;
            }
        }

        if (mouse_moved || non_mouse_interacted) {
            mouse_is_active_initialized = true;
        }

        if (mouse_is_active_initialized) {
            recompui::set_cursor_visible(mouse_is_active);
        }

        Rml::ElementDocument* current_document = top_mouse_document();
        if (current_document == nullptr) {
            return;
        }

        // TODO is this needed?
        Rml::Element* window_el = current_document->GetElementById("window");
        if (window_el != nullptr) {
            if (mouse_is_active) {
                if (!window_el->HasAttribute("mouse-active")) {
                    window_el->SetAttribute("mouse-active", true);
                }
            }
            else if (window_el->HasAttribute("mouse-active")) {
                window_el->RemoveAttribute("mouse-active");
            }
        }
    }

    void update_focus(bool mouse_moved, bool non_mouse_interacted) {
        Rml::ElementDocument* current_document = top_mouse_document();

        if (current_document == nullptr) {
            return;
        }

        // If non mouse input was used and nothing is focused then focus on the last hovered element or the autofocus element.
        if (cont_is_active || non_mouse_interacted) {
            auto top_context = top_mouse_context();
            if (non_mouse_interacted && top_context != recompui::ContextId::null()) {
                top_context.open();
                auto focused_el = top_context.get_focused_element();
                // Check if not focused or focused element is not focusable.
                if (focused_el == nullptr || focused_el->is_focusable() != recompui::Element::CanFocus::Yes) {
                    auto recompui_doc = top_context.get_root_element();
                    auto last_hovered = recompui_doc->get_last_focusable_hovered_element();
                    if (last_hovered && last_hovered->is_focusable() == recompui::Element::CanFocus::Yes) {
                        last_hovered->focus();
                    } else {
                        Rml::Element* element = find_autofocus_element(current_document);
                        if (element != nullptr) {
                            element->Focus();
                        }
                    }
                }
                top_context.close();
            }
            return;
        }

        // If there was mouse motion, get the current hovered element (or its target if it points to one) and focus that if applicable.
        if (mouse_is_active) {
            if (mouse_is_active_changed) {
                Rml::Element* focused = current_document->GetFocusLeafNode();
                if (focused) focused->Blur();
            }
        }
    }

    void show_context(recompui::ContextId context) {
        if (std::find_if(shown_contexts.begin(), shown_contexts.end(), [context](auto& c){ return c.context == context; }) != shown_contexts.end()) {
            recompui::message_box("Attemped to show the same context twice");
            assert(false);
        }
        Rml::ElementDocument* document = context.get_document();
        shown_contexts.push_back(ContextDetails{
            .context = context,
            .document = document
        });

        // auto& on_show = context.on_show;
        // if (on_show) {
        //     context.open();
        //     on_show();
        //     context.close();
        // }

        document->PullToFront();
        document->Show();

        if (!mouse_is_active) {
            recompui::Element* default_element = context.get_autofocus_element();
            if (default_element != nullptr) {
                default_element->focus();
            }
        }
    }

    void try_restore_focus() {
        recompui::ContextId top_context = top_mouse_context();
        if (top_context == recompui::ContextId::null()) {
            return;
        }

        recompui::Element* last_focused = top_context.get_last_focused_element();
        if (last_focused != nullptr && last_focused->is_focusable() == recompui::Element::CanFocus::Yes) {
            last_focused->focus();
            return;
        }

        recompui::Element* autofocus_element = top_context.get_autofocus_element();
        if (autofocus_element != nullptr) {
            autofocus_element->focus();
            return;
        }
    }

    void hide_context(recompui::ContextId context) {
        auto remove_it = std::remove_if(shown_contexts.begin(), shown_contexts.end(), [context](auto& c) { return c.context == context; });
        if (remove_it == shown_contexts.end()) {
            recompui::message_box("Attemped to hide a context that isn't shown");
            assert(false);
        }
        shown_contexts.erase(remove_it, shown_contexts.end());

        context.get_document()->Hide();
    }
    
    void hide_all_contexts() {
        for (auto& context : shown_contexts) {
            context.document->Hide();
        }

        shown_contexts.clear();
    }

    bool is_context_shown(recompui::ContextId context) {
        return std::find_if(shown_contexts.begin(), shown_contexts.end(), [context](auto& c){ return c.context == context; }) != shown_contexts.end();
    }

    bool is_context_capturing_input() {
        return std::find_if(shown_contexts.begin(), shown_contexts.end(), [](auto& c){ return c.context.captures_input(); }) != shown_contexts.end();
    }

    bool is_context_capturing_mouse() {
        return std::find_if(shown_contexts.begin(), shown_contexts.end(), [](auto& c){ return c.context.captures_mouse(); }) != shown_contexts.end();
    }

    bool is_any_context_shown() {
        return !shown_contexts.empty();
    }

    Rml::ElementDocument* top_input_document() {
        // Iterate backwards and stop at the first context that takes input.
        for (auto it = shown_contexts.rbegin(); it != shown_contexts.rend(); it++) {
            if (it->context.captures_input()) {
                return it->document;
            }
        }
        return nullptr;
    }

    Rml::ElementDocument* top_mouse_document() {
        // Iterate backwards and stop at the first context that takes input.
        for (auto it = shown_contexts.rbegin(); it != shown_contexts.rend(); it++) {
            if (it->context.captures_mouse()) {
                return it->document;
            }
        }
        return nullptr;
    }

    recompui::ContextId top_mouse_context() {
        // Iterate backwards and stop at the first context that takes input.
        for (auto it = shown_contexts.rbegin(); it != shown_contexts.rend(); it++) {
            if (it->context.captures_mouse()) {
                return it->context;
            }
        }
        return recompui::ContextId::null();
    }

    void update_contexts() {
        for (auto& context_details : shown_contexts) {
            context_details.context.open();
            context_details.context.process_updates();
            context_details.context.close();
        }
    }
};

std::unique_ptr<UIState> ui_state;
std::recursive_mutex ui_state_mutex{};
static bool renderer_reconfiguration = false;
static std::function<void()> ui_frame_callback;

void recompui::begin_renderer_reconfiguration() {
    std::lock_guard lock{ui_state_mutex};
    renderer_reconfiguration = true;
}

void recompui::end_renderer_reconfiguration() {
    std::lock_guard lock{ui_state_mutex};
    renderer_reconfiguration = false;
}

void recompui::register_ui_frame_callback(std::function<void()> callback) {
    std::lock_guard lock{ui_state_mutex};
    ui_frame_callback = std::move(callback);
}

// TODO make this not be global
extern SDL_Window* window;

void recompui::get_window_size(int& width, int& height) {
    SDL_GetWindowSizeInPixels(window, &width, &height);
}

inline const std::string read_file_to_string(std::filesystem::path path) {
    std::ifstream stream = std::ifstream{path};
    std::ostringstream ss;
    ss << stream.rdbuf();
    return ss.str(); 
}

void init_hook(plume::RenderInterface* interface, plume::RenderDevice* device) {
    std::lock_guard lock{ui_state_mutex};
    if (renderer_reconfiguration && ui_state) {
        ui_state->render_interface.rebind_device(interface, device);
        return;
    }
#if defined(__linux__)
    std::locale::global(std::locale::classic());
#endif
    ui_state = std::make_unique<UIState>(window, interface, device);
    ui_state->create_menus();
}

moodycamel::ConcurrentQueue<SDL_Event> ui_event_queue{};
static std::atomic_bool input_suspended = false;
static std::atomic_bool input_reset_requested = false;

void recompui::set_input_suspended(bool suspended) {
    if (input_suspended.exchange(suspended) != suspended) {
        // Reset on the render thread, which owns RmlUi and its repeat state.
        // This may be called by an option callback already holding its mutex.
        input_reset_requested.store(true);
    }
}

bool recompui::is_input_suspended() {
    return input_suspended.load();
}

void recompui::queue_event(const SDL_Event& event) {
    if (!is_input_suspended()) ui_event_queue.enqueue(event);
}

bool recompui::try_deque_event(SDL_Event& out) {
    return ui_event_queue.try_dequeue(out);
}

recompui::MenuAction recompui::menu_action_mapping::menu_action_from_rml_key(const Rml::Input::KeyIdentifier& key) {
    auto it = recompui::menu_action_mapping::rml_key_to_action.find(key);
    if (it != recompui::menu_action_mapping::rml_key_to_action.end()) {
        return it->second.action;
    }
    return recompui::MenuAction::None;
}

recompinput::GameInput recompui::menu_action_mapping::game_input_from_menu_action(const MenuAction& action) {
    for (auto &action_pair : recompui::menu_action_mapping::rml_key_to_action) {
        if (action_pair.second.action == action) {
            return action_pair.second.input;
        }
    }
    return recompinput::GameInput::COUNT;
}

bool recompui::menu_action_mapping::is_sdl_input_fake_mapped(int32_t sdl_key) {
    return sdl_key == static_cast<int32_t>(SDL_SCANCODE_F15) ||
            sdl_key == static_cast<int32_t>(SDL_SCANCODE_F16) ||
            sdl_key == static_cast<int32_t>(SDL_SCANCODE_F17);
}

// Extends RmlSDL::ConvertKey for some extra mapping slots
Rml::Input::KeyIdentifier convert_sdl_to_rml(int sdl_key) {
    Rml::Input::KeyIdentifier identifier = RmlSDL::ConvertKey(sdl_key);
    if (identifier == Rml::Input::KeyIdentifier::KI_UNKNOWN) {
        switch (sdl_key) {
            case SDLK_F15: return Rml::Input::KI_F15;
            case SDLK_F16: return Rml::Input::KI_F16;
            case SDLK_F17: return Rml::Input::KI_F17;
            case SDLK_F18: return Rml::Input::KI_F18;
            case SDLK_F19: return Rml::Input::KI_F19;
            case SDLK_F20: return Rml::Input::KI_F20;
            case SDLK_F21: return Rml::Input::KI_F21;
            case SDLK_F22: return Rml::Input::KI_F22;
            case SDLK_F23: return Rml::Input::KI_F23;
            case SDLK_F24: return Rml::Input::KI_F24;
        }
    }
    return identifier;
}

bool check_menu_button_pressed(int profile_index, recompinput::GameInput input, int32_t event_button) {
    auto menuBinding0 = recompinput::profiles::get_input_binding(profile_index, input, 0);
    auto menuBinding1 = recompinput::profiles::get_input_binding(profile_index, input, 1);
    if ((menuBinding0.input_type != recompinput::InputType::None && event_button == menuBinding0.input_id) ||
        (menuBinding1.input_type != recompinput::InputType::None && event_button == menuBinding1.input_id)) {
        return true;
    }
    return false;
}

int cont_button_to_key(SDL_ControllerButtonEvent& button) {
    int player1_profile = recompinput::profiles::get_input_profile_for_player(0, recompinput::InputDevice::Controller);

    for (const auto& mapping_pair : recompui::menu_action_mapping::rml_key_to_action) {
        const auto& mapping = mapping_pair.second;
        if (check_menu_button_pressed(player1_profile, mapping.input, button.button)) {
            return mapping.sdl;
        }
    }

    switch (button.button) {
        case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP:
            return SDLK_UP;
        case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            return SDLK_DOWN;
        case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            return SDLK_LEFT;
        case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            return SDLK_RIGHT;
    }

    return 0;
}


int cont_axis_to_key(SDL_ControllerAxisEvent& axis, float value) {
    switch (axis.axis) {
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY:
        if (value < 0) return SDLK_UP;
        return SDLK_DOWN;
    case SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX:
        if (value >= 0) return SDLK_RIGHT;
        return SDLK_LEFT;
    }
    return 0;
}

void apply_background_input_mode() {
    static bool initialized = false;
    static bool last_input_mode = false;

    // Native Player 2 focus counts as foreground gameplay without changing
    // the saved background-input preference. Other applications remain subject
    // to that preference as soon as this window loses focus.
    bool cur_input_mode = recompui::config::general::get_background_input_mode_enabled() ||
        RT64::wr64SecondaryWindowFocused.load();

    if (!initialized || last_input_mode != cur_input_mode) {
        SDL_SetHint(
            SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,
            cur_input_mode ? "1" : "0"
        );
        initialized = true;
    }
    last_input_mode = cur_input_mode;
}

bool recompui::get_cont_active() {
    return ui_state->cont_is_active;
}

void recompui::set_cont_active(bool active) {
    ui_state->cont_is_active = active;
}

void recompui::activate_mouse() {
    ui_state->update_primary_input(true, false);
    ui_state->update_focus(true, false);
}

void draw_hook(plume::RenderCommandList* command_list, plume::RenderFramebuffer* swap_chain_framebuffer) {

    apply_background_input_mode();

    // Return early if the ui context has been destroyed already.
    if (!ui_state) {
        return;
    }

    // Return to the launcher if no menu is open and the game isn't started.
    if (!recompui::is_any_context_shown() && !ultramodern::is_game_started()) {
        recompui::show_context(recompui::get_launcher_context_id(), "");
    }

    std::lock_guard lock{ ui_state_mutex };

    if (ui_frame_callback) {
        ui_frame_callback();
    }

    SDL_Event cur_event{};

    bool mouse_moved = false;
    bool mouse_clicked = false;
    bool non_mouse_interacted = false;
    bool cont_interacted = false;
    bool kb_interacted = false;

    bool config_was_open = recompui::is_context_shown(recompui::config::get_config_context_id());

    using clock = std::chrono::system_clock;

    // TODO move these into a more appropriate place.
    constexpr clock::duration start_repeat_delay = std::chrono::milliseconds{500};
    constexpr clock::duration repeat_rate = std::chrono::milliseconds{50};
    static clock::time_point next_repeat_time = {};
    static int latest_controller_key_pressed = SDLK_UNKNOWN;

    auto discard_suspended_input = [&]() {
        const bool reset = input_reset_requested.exchange(false);
        const bool suspended = recompui::is_input_suspended();
        if (reset || suspended) {
            while (recompui::try_deque_event(cur_event)) {}
            latest_controller_key_pressed = SDLK_UNKNOWN;
            next_repeat_time = {};
            ui_state->await_stick_return_x = false;
            ui_state->await_stick_return_y = false;
        }
        return reset || suspended;
    };
    bool suppress_actions = discard_suspended_input();

    bool all_input_is_disabled = recompinput::all_input_disabled();

    while (!suppress_actions && recompui::try_deque_event(cur_event)) {
        // An option may suspend the UI from inside this very event loop.
        if (discard_suspended_input()) { suppress_actions = true; break; }
        bool context_capturing_input = recompui::is_context_capturing_input();
        bool context_capturing_mouse = recompui::is_context_capturing_mouse();

        // Handle up button events even when input is disabled to avoid missing them during binding.
        if (cur_event.type == SDL_EventType::SDL_CONTROLLERBUTTONUP) {
            int sdl_key = cont_button_to_key(cur_event.cbutton);
            if (sdl_key == latest_controller_key_pressed) {
                latest_controller_key_pressed = SDLK_UNKNOWN;
            }
        }

        if (!all_input_is_disabled) {
            bool is_mouse_input = false;
            // Implement some additional behavior for specific events on top of what RmlUi normally does with them.
            switch (cur_event.type) {
            case SDL_EventType::SDL_MOUSEMOTION: {
                int *last_mouse_pos = ui_state->last_active_mouse_position;

                if (!ui_state->mouse_is_active) {
                    float xD = cur_event.motion.x - last_mouse_pos[0];
                    float yD = cur_event.motion.y - last_mouse_pos[1];
                    if (sqrt(xD * xD + yD * yD) < 100) {
                        break;
                    }
                }
                last_mouse_pos[0] = cur_event.motion.x;
                last_mouse_pos[1] = cur_event.motion.y;

                // if controller is the primary input, don't use mouse movement to allow cursor to reactivate
                if (recompui::get_cont_active()) {
                    break;
                }
            }
            // fallthrough
            case SDL_EventType::SDL_MOUSEBUTTONDOWN:
                mouse_moved = true;
                mouse_clicked = true;
                is_mouse_input = true;
                break;
                
            case SDL_EventType::SDL_MOUSEBUTTONUP:
            case SDL_EventType::SDL_MOUSEWHEEL:
                is_mouse_input = true;
                break;
                
            case SDL_EventType::SDL_CONTROLLERBUTTONDOWN: {
                int sdl_key = cont_button_to_key(cur_event.cbutton);
                if (context_capturing_input && sdl_key) {
                    ui_state->context->ProcessKeyDown(convert_sdl_to_rml(sdl_key), 0);
                    latest_controller_key_pressed = sdl_key;
                    next_repeat_time = clock::now() + start_repeat_delay;
                }
                non_mouse_interacted = true;
                cont_interacted = true;
                break;
            }
            case SDL_EventType::SDL_KEYDOWN:
                // Exclude the ESC key from triggering keyboard mode.
                if (cur_event.key.keysym.scancode != SDL_Scancode::SDL_SCANCODE_ESCAPE) {
                    non_mouse_interacted = true;
                    kb_interacted = true;

                    if (cur_event.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_F8) {
                        if (recompui::config::general::get_debug_mode_enabled()) {
                            Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
                        }
                    }
                }

                break;
            case SDL_EventType::SDL_USEREVENT:
                if (cur_event.user.code == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) {
                    ui_state->await_stick_return_y = true;
                } else if (cur_event.user.code == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) {
                    ui_state->await_stick_return_x = true;
                }
                break;
            case SDL_EventType::SDL_CONTROLLERAXISMOTION:
                SDL_ControllerAxisEvent* axis_event = &cur_event.caxis;
                if (axis_event->axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY && axis_event->axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) {
                    break;
                }

                float axis_value = axis_event->value * (1 / 32768.0f);
                bool* await_stick_return = axis_event->axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY
                        ? &ui_state->await_stick_return_y
                        : &ui_state->await_stick_return_x;
                if (fabsf(axis_value) > 0.5f) {
                    if (!*await_stick_return) {
                        *await_stick_return = true;
                        non_mouse_interacted = true;
                        int sdl_key = cont_axis_to_key(cur_event.caxis, axis_value);
                        if (context_capturing_input && sdl_key) {
                            ui_state->context->ProcessKeyDown(convert_sdl_to_rml(sdl_key), 0);
                            latest_controller_key_pressed = sdl_key;
                            next_repeat_time = clock::now() + start_repeat_delay;
                        }
                    }
                    non_mouse_interacted = true;
                    cont_interacted = true;
                }
                else if (*await_stick_return && fabsf(axis_value) < 0.15f) {
                    *await_stick_return = false;
                    // Stop pressing the current key if the axis that was released was the one triggering key presses.
                    int sdl_key = cont_axis_to_key(cur_event.caxis, axis_value);
                    if (sdl_key == latest_controller_key_pressed) {
                        latest_controller_key_pressed = SDLK_UNKNOWN;
                    }
                }
                break;
            }

            // Send the event to RmlUi if this type of event is being captured.
            if (is_mouse_input) {
                if (context_capturing_mouse) {
                    RmlSDL::InputEventHandler(ui_state->context, cur_event);
                }
            }
            else {
                if (context_capturing_input) {
                    RmlSDL::InputEventHandler(ui_state->context, cur_event);
                }
            }
        }

        // If the config menu isn't open and the game has been started and either the escape key or select button are pressed, open the config menu.
        if (!config_was_open && ultramodern::is_game_started()) {
            bool open_config = false;

            switch (cur_event.type) {
            case SDL_EventType::SDL_KEYDOWN:
                if (cur_event.key.keysym.scancode == SDL_Scancode::SDL_SCANCODE_ESCAPE) {
                    open_config = true;
                }
                break;
            case SDL_EventType::SDL_CONTROLLERBUTTONDOWN: {
                SDL_ControllerButtonEvent* button_event = &cur_event.cbutton;
                SDL_JoystickID joystick_id = button_event->which;
                int profile_index;
                if (recompinput::players::is_single_player_mode()) {
                    profile_index = recompinput::profiles::get_sp_controller_profile_index();
                }
                else {
                    auto controller = recompinput::get_controller_from_joystick_id(joystick_id);
                    profile_index = recompinput::profiles::get_controller_profile_index_from_sdl_controller(controller);
                }

                if (check_menu_button_pressed(profile_index, recompinput::GameInput::TOGGLE_MENU, cur_event.cbutton.button)) {
                    open_config = true;
                }
                break;
            }
            }

            if (open_config) {
                recompui::config::open();
            }
        }
    } // end dequeue event loop

    suppress_actions = discard_suspended_input() || suppress_actions;

    // Handle controller key repeats.
    if (!suppress_actions && latest_controller_key_pressed != SDLK_UNKNOWN) {
        clock::time_point now = clock::now();
        if (now >= next_repeat_time) {
            ui_state->context->ProcessKeyDown(convert_sdl_to_rml(latest_controller_key_pressed), 0);
            next_repeat_time += repeat_rate;
        }
    }

    suppress_actions = discard_suspended_input() || suppress_actions;
    if (!suppress_actions) {
        if (cont_interacted || kb_interacted || mouse_clicked) {
            recompui::set_cont_active(cont_interacted);
        }
        ui_state->update_primary_input(mouse_moved, non_mouse_interacted);
        ui_state->update_focus(mouse_moved, non_mouse_interacted);
    }

    // Keep the selector visible while waiting for released controls on return.
    // Only interaction is suspended; rendering must not become a black screen.

    if (recompui::is_any_context_shown()) {
        if (recompui::is_context_shown(recompui::get_launcher_context_id())) {
            recompui::update_launcher_menu();
        }

        ui_state->update_contexts();

        int width = swap_chain_framebuffer->getWidth();
        int height = swap_chain_framebuffer->getHeight();

        // Scale the UI based on the window size with 1080 vertical resolution as the reference point.
        ui_state->context->SetDensityIndependentPixelRatio((height) / 1080.0f);

        ui_state->render_interface.start(command_list, width, height);

        static int prev_width = 0;
        static int prev_height = 0;

        if (prev_width != width || prev_height != height) {
            ui_state->context->SetDimensions({ width, height });
        }
        prev_width = width;
        prev_height = height;

        ui_state->context->Update();
        ui_state->context->Render();
        ui_state->render_interface.end(command_list, swap_chain_framebuffer);
    }
}

void deinit_hook() {
    std::lock_guard lock {ui_state_mutex};
    if (!ui_state) return;
    if (renderer_reconfiguration) {
        // Application::end joins both rendering workers before this hook.
        // Invalidate Rml's native handles while their old device still exists.
        auto* adapter = ui_state->render_interface.get_rml_interface();
        Rml::ReleaseCompiledGeometry(adapter);
        Rml::ReleaseTextures(adapter);
        ui_state->render_interface.release_device_resources();
        return;
    }
    recompui::destroy_all_contexts();
    Rml::Debugger::Shutdown();
    Rml::Shutdown();
    ui_state->unload();
    ui_state.reset();
}

void recompui::set_render_hooks() {
    RT64::SetRenderHooks(init_hook, draw_hook, deinit_hook);
}

void recompui::message_box(const char* msg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, recompui::programconfig::get_program_name().data(), msg, nullptr);
    printf("[ERROR] %s\n", msg);
}

void recompui::show_context(ContextId context, std::string_view param) {
    ContextId prev_context = recompui::try_close_current_context();
    {
        std::lock_guard lock{ ui_state_mutex };

        // TODO call the context's on_show callback with the param.
        ui_state->show_context(context);
    }
    if (prev_context != ContextId::null()) {
        prev_context.open();
    }
}

void recompui::hide_context(ContextId context) {
    bool restore_focus = false;
    if (context == ui_state->top_mouse_context()) {
        restore_focus = true;
    }

    ContextId prev_context = recompui::try_close_current_context();
    {
        std::lock_guard lock{ ui_state_mutex };

        ui_state->hide_context(context);
    }
    if (prev_context != ContextId::null()) {
        prev_context.open();
    }

    if (restore_focus) {
        ui_state->try_restore_focus();
    }
}

void recompui::hide_all_contexts() {
    std::lock_guard lock{ui_state_mutex};

    if (ui_state) {
        ui_state->hide_all_contexts();
    }
}

bool recompui::is_context_shown(ContextId context) {
    std::lock_guard lock{ui_state_mutex};

    if (!ui_state) {
        return false;
    }

    return ui_state->is_context_shown(context);
}

bool recompui::is_context_capturing_input() {
    std::lock_guard lock{ui_state_mutex};

    if (!ui_state) {
        return false;
    }

    return ui_state->is_context_capturing_input();
}

bool recompui::is_context_capturing_mouse() {
    std::lock_guard lock{ui_state_mutex};

    if (!ui_state) {
        return false;
    }

    return ui_state->is_context_capturing_mouse();
}

bool recompui::is_any_context_shown() {
    std::lock_guard lock{ui_state_mutex};

    if (!ui_state) {
        return false;
    }

    return ui_state->is_any_context_shown();
}

Rml::ElementDocument* recompui::load_document(const std::filesystem::path& path) {
    std::lock_guard lock{ui_state_mutex};

    return ui_state->context->LoadDocument(path.string());
}

Rml::ElementDocument* recompui::create_empty_document() {
    std::lock_guard lock{ui_state_mutex};

    return ui_state->context->CreateDocument();
}

void recompui::queue_image_from_bytes_file(const std::string &src, const std::vector<char> &bytes) {
    ui_state->render_interface.queue_image_from_bytes_file(src, bytes);
}

void recompui::queue_image_from_bytes_rgba32(const std::string &src, const std::vector<char> &bytes, uint32_t width, uint32_t height) {
    ui_state->render_interface.queue_image_from_bytes_rgba32(src, bytes, width, height);
}

void recompui::release_image(const std::string &src) {
    Rml::ReleaseTexture(src);
}

void recompui::drop_files(const std::list<std::filesystem::path> &file_list) {
    // Prevent mod installation after the game has started.
    if (ultramodern::is_game_started()) {
        return;
    }

    recompui::config::set_tab(recompui::config::mods::id);
    recompui::hide_all_contexts();
    recompui::config::open();

    recompui::open_notification("Installing Mods", "Please Wait");
    // TODO: Needs a progress callback and a prompt for every mod that needs to be confirmed to be overwritten.
    // TODO: Run this on a background thread and use the callbacks to advance the state instead of blocking.
    ModInstaller::Result result;
    ModInstaller::start_mod_installation(file_list, nullptr, result);

    recompui::close_prompt();

    if (!result.error_messages.empty()) {
        std::string error_label = std::accumulate(result.error_messages.begin(), result.error_messages.end(), std::string{},
            [](const std::string &lhs, const std::string &rhs)
            {
                return lhs.empty() ? rhs : lhs + '\n' + rhs;
            });

        recompui::open_info_prompt("Error Installing Mods", error_label, "OK", {}, recompui::ButtonStyle::Tertiary);
        std::vector<std::string> dummy_error_messages{};
        ModInstaller::cancel_mod_installation(result, dummy_error_messages);
        return;
    }

    std::vector<ModInstaller::Confirmation> confirmations{};

    for (const ModInstaller::Installation& pending_install : result.pending_installations) {
        if (pending_install.needs_overwrite_confirmation) {
            // Get the mod details for the current mod at this file path.
            std::string old_mod_id = recomp::mods::get_mod_id_from_filename(pending_install.mod_file.filename());
            std::optional<recomp::mods::ModDetails> old_mod_details = {};

            if (!old_mod_id.empty()) {
                old_mod_details = recomp::mods::get_details_for_mod(old_mod_id);
            }

            if (old_mod_details) {
                confirmations.emplace_back(ModInstaller::Confirmation {
                    .old_display_name = old_mod_details->display_name,
                    .new_display_name = pending_install.display_name,
                    .old_mod_id = old_mod_details->mod_id,
                    .new_mod_id = pending_install.mod_id,
                    .old_version = old_mod_details->version,
                    .new_version = pending_install.mod_version
                });
            }
            else {
                confirmations.emplace_back(ModInstaller::Confirmation {
                    .old_display_name = "?",
                    .new_display_name = pending_install.display_name,
                    .old_mod_id = "",
                    .new_mod_id = pending_install.mod_id,
                    .old_version = recomp::Version{0, 0, 0, ""},
                    .new_version = pending_install.mod_version
                });
            }
        }
    }

    if (confirmations.empty()) {
        std::vector<std::string> error_messages{};
        ModInstaller::finish_mod_installation(result, error_messages);
        ContextId old_context = recompui::try_close_current_context();
        recompui::update_mod_list();
        if (old_context != ContextId::null()) {
            old_context.open();
        }
        // TODO show errors
    }
    else {
        std::string prompt_text = std::accumulate(confirmations.begin(), confirmations.end(), std::string{},
            [](const std::string &cur_text, const ModInstaller::Confirmation &confirmation)
            {
                std::string new_text{};
                if (confirmation.old_display_name == confirmation.new_display_name) {
                    new_text = confirmation.old_display_name + " (" + confirmation.old_version.to_string() + " -> " + confirmation.new_version.to_string() + ")";
                }
                else {
                    new_text =
                        confirmation.old_display_name + " (" + confirmation.old_version.to_string() + ") -> " +
                        confirmation.new_display_name + " (" + confirmation.new_version.to_string() + ")";
                }
                return cur_text.empty() ? new_text : cur_text + '\n' + new_text;
            });

        // open prompt where confirm finishes the mod installation with the overwritten files
        recompui::open_choice_prompt("Overwrite Mods?",
            prompt_text,
            "Overwrite",
            "Cancel",
            [result]() {
                std::vector<std::string> error_messages{};
                recomp::mods::close_mods();
                ModInstaller::finish_mod_installation(result, error_messages);
                ContextId old_context = recompui::try_close_current_context();
                recompui::update_mod_list();
                if (old_context != ContextId::null()) {
                    old_context.open();
                }
                // TODO show errors
            },
            [result]() {
                std::vector<std::string> error_messages{};
                ModInstaller::cancel_mod_installation(result, error_messages);
                // TODO show errors
            },
            recompui::ButtonStyle::Success,
            recompui::ButtonStyle::Danger,
            true
        );
    }
}
