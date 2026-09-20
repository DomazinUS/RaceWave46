#include "ui_modal.h"
#include "ui_element.h"
#include "ui_document.h"
#include "recompinput/recompinput.h"
#include "recompinput/profiles.h"

namespace recompui {

class ModalOverlay : public Element {
protected:
    Modal *parent_modal;

    void process_event(const Event &e) override {
        if (e.type != EventType::Click) {
            return;
        }

        // parent_modal->close();
    }
    std::string_view get_type_name() override { return "ModalOverlay"; }
public:
    ModalOverlay(ResourceId rid, Modal *parent) : Element(rid, parent, Events(EventType::Click, EventType::Hover, EventType::Enable, EventType::Focus), "div", false) {
        this->parent_modal = parent;

        set_display(Display::Block);
        set_position(Position::Absolute);
        set_top(0);
        set_right(0);
        set_bottom(0);
        set_left(0);
        set_background_color(theme::color::BGOverlay);
    }

    ~ModalOverlay() {
    }
};

constexpr float modal_page_padding = 64.0f;
constexpr float modal_page_base_height = 1080.0f;
constexpr float modal_height = modal_page_base_height - (modal_page_padding * 2.0f);
constexpr float modal_width = modal_page_base_height * 16.0f / 9.0f;

Modal::Modal(
    ResourceId rid,
    Document *parent,
    recompui::ContextId modal_root_context,
    ModalType modal_type
) : Element(rid, parent, Events(EventType::MenuAction), "div", false)
{
    this->modal_root_context = modal_root_context;
    this->modal_type = modal_type;
    recompui::ContextId context = modal_root_context;

    set_display(Display::None);
    set_position(Position::Absolute);
    set_top(0);
    set_right(0);
    set_bottom(0);
    set_left(0);

    modal_overlay = context.create_element<ModalOverlay>(this);

    Element* modal_whole_page_wrapper = context.create_element<Element>(modal_overlay);
    modal_whole_page_wrapper->set_display(Display::Flex);
    modal_whole_page_wrapper->set_position(Position::Absolute);
    modal_whole_page_wrapper->set_top(0);
    modal_whole_page_wrapper->set_right(0);
    modal_whole_page_wrapper->set_bottom(0);
    modal_whole_page_wrapper->set_left(0);
    modal_whole_page_wrapper->set_padding(modal_page_padding);
    modal_whole_page_wrapper->set_align_items(AlignItems::Center);
    modal_whole_page_wrapper->set_justify_content(JustifyContent::Center);

    modal_element = context.create_element<Element>(modal_whole_page_wrapper);
    modal_element->set_display(Display::Flex);
    modal_element->set_position(Position::Relative);
    modal_element->set_flex(1.0f, 1.0f);
    modal_element->set_flex_basis(100, Unit::Percent);
    modal_element->set_flex_direction(FlexDirection::Column);
    modal_element->set_width(100, Unit::Percent);
    modal_element->set_max_width(modal_width);
    modal_element->set_height(100, Unit::Percent);
    modal_element->set_margin_auto();
    modal_element->set_border_width(theme::border::width);
    modal_element->set_border_radius(theme::border::radius_lg);
    modal_element->set_border_color(theme::color::Border);
    modal_element->set_background_color(theme::color::ModalOverlay);
    modal_element->set_as_navigation_container(NavigationType::Vertical);
    modal_element->set_nav_wrapping(true);

    header = context.create_element<ConfigHeaderFooter>(modal_element, true);
    header->set_padding_top(0.0f);
    header->set_padding_bottom(0.0f);
    header->set_padding_left(8.0f);
    header->set_padding_right(8.0f);
    header->set_border_top_left_radius(theme::border::radius_lg);
    header->set_border_top_right_radius(theme::border::radius_lg);
    header->set_background_color(Color{101, 96, 172, 255});
    header->set_border_bottom_width(4.0f);
    header->set_border_bottom_color(theme::color::BorderSoft);

    body = context.create_element<Element>(modal_element);
    body->set_display(Display::Flex);
    body->set_position(Position::Relative);
    body->set_flex_grow(1.0f);
    body->set_flex_shrink(1.0f);
    body->set_flex_basis_auto();
    body->set_flex_direction(FlexDirection::Row);
    body->set_width(100.0f, Unit::Percent);

    set_menu_action_callback(MenuAction::Toggle, [this]() {
        this->close();
    }, "Close");
}

Modal::~Modal() {
}

void Modal::open() {
    if (!recompui::is_context_shown(modal_root_context)) {
        recompui::show_context(modal_root_context, "");
    }

    is_open = true;
    set_display(Display::Block);
}

void TabbedModal::open() {
    Modal::open();

    if (tabs != nullptr) {
        tabs->focus_on_active_tab();
        on_tab_change(tabs->get_active_tab());
    }
}

bool Modal::close() {
    if (recompui::is_context_shown(modal_root_context)) {
        set_display(Display::None);
        recompui::hide_context(modal_root_context);
    }

    is_open = false;

    if (on_close_callback != nullptr) {
        on_close_callback();
    }

    return true;
}

bool TabbedModal::close() {
    if (current_tab_index < tab_contexts.size() && current_tab_index >= 0) {
        if (tab_contexts[current_tab_index].can_close(TabCloseContext::ModalClose)) {
            tab_contexts[current_tab_index].on_close(TabCloseContext::ModalClose);
        } else {
            return false;
        }
    }

    return Modal::close();
}

static std::pair<recompinput::InputDevice, int> get_last_input_info() {
    if (recompinput::players::is_single_player_mode()) {
        if (get_cont_active()) {
            return { recompinput::InputDevice::Controller, recompinput::profiles::get_sp_controller_profile_index() };
        } else {
            return { recompinput::InputDevice::Keyboard, recompinput::profiles::get_sp_keyboard_profile_index() };
        }
    }

    recompinput::InputDevice device = recompinput::players::get_player_input_device(0);
    if (device == recompinput::InputDevice::COUNT) {
        return { recompinput::InputDevice::COUNT, -1 };
    }

    return { device, recompinput::profiles::get_input_profile_for_player(0, device) };
}

void Modal::process_event(const Event &e) {
    switch (e.type) {
        case EventType::Update: {
            if (is_open) {
                bool update_action_labels = false;
                auto [current_device, current_profile] = get_last_input_info();
                if (current_device != last_input_device || current_profile != last_input_profile) {
                    render_menu_actions();
                }
            }
            queue_update();
            break;
        }
        case EventType::MenuAction: {
            auto action = std::get<EventMenuAction>(e.variant).action;
            if (menu_action_callbacks.contains(action)) {
                menu_action_callbacks[action].callback();
                break;
            }

            break;
        }
    }
}

void Modal::set_menu_action_callback(MenuAction action, std::function<void()> callback, std::string description) {
    menu_action_callbacks[action] = { callback, description };
    render_menu_actions();
}

void Modal::remove_menu_action_callback(MenuAction action) {
    menu_action_callbacks.erase(action);
    render_menu_actions();
}

void Modal::render_menu_actions() {
    static const MenuAction menu_action_order[] = {
        MenuAction::Accept,
        MenuAction::Back,
        MenuAction::Toggle,
        MenuAction::TabLeft,
        MenuAction::TabRight,
        MenuAction::Apply,
    };

    ContextId context = get_current_context();
    if (menu_actions_wrapper == nullptr) {
        menu_actions_wrapper = context.create_element<Element>(modal_overlay);
        menu_actions_wrapper->set_position(Position::Absolute);
        menu_actions_wrapper->set_bottom(0);
        menu_actions_wrapper->set_margin_left_auto();
        menu_actions_wrapper->set_margin_right_auto();
        menu_actions_wrapper->set_padding_left(modal_page_padding);
        menu_actions_wrapper->set_padding_right(modal_page_padding);
        menu_actions_wrapper->set_width(100, Unit::Percent);
        menu_actions_wrapper->set_max_width(modal_width + (modal_page_padding * 2.0f));
        menu_actions_wrapper->set_height(modal_page_padding);
        menu_actions_wrapper->set_display(Display::Flex);
        menu_actions_wrapper->set_justify_content(JustifyContent::FlexStart);
        menu_actions_wrapper->set_align_items(AlignItems::Center);
        menu_actions_wrapper->set_gap(32.0f);
    } else {
        menu_actions_wrapper->clear_children();
    }

    auto [current_device, current_profile] = get_last_input_info();
    last_input_device = current_device;
    last_input_profile = current_profile;

    if (last_input_device == recompinput::InputDevice::COUNT) {
        return;
    }
    
    for (auto &action : menu_action_order) {
        auto it = menu_action_callbacks.find(action);
        if (it == menu_action_callbacks.end()) {
            continue;
        }

        recompui::MenuActionCallback &action_info = it->second;
        if (action_info.description.empty()) {
            continue;
        }

        recompinput::GameInput input = menu_action_mapping::game_input_from_menu_action(action);
        if (input == recompinput::GameInput::COUNT) {
            continue;
        }

        std::vector<recompinput::InputField> bound_inputs;
        for (size_t i = 0; i < recompinput::num_bindings_per_input; i++) {
            auto binding = recompinput::profiles::get_input_binding(last_input_profile, input, i);
            if (!binding.is_empty()) {
                if (
                    binding.input_type == recompinput::InputType::Keyboard &&
                    menu_action_mapping::is_sdl_input_fake_mapped(binding.input_id)
                ) {
                    continue;
                }
                bound_inputs.push_back(binding);
            }
        }

        if (bound_inputs.size() == 0) {
            continue;
        }

        auto action_wrapper = context.create_element<Element>(menu_actions_wrapper, 0, "span", false);
        action_wrapper->set_display(Display::Flex);
        action_wrapper->set_flex_direction(FlexDirection::Row);
        action_wrapper->set_align_items(AlignItems::Center);
        action_wrapper->set_gap(4.0f);
        action_wrapper->set_color(theme::color::White);

        auto action_label = context.create_element<Label>(action_wrapper, action_info.description + ":", theme::Typography::LabelSM);
        for (const auto &bound_input : bound_inputs) {
            auto binding_label = context.create_element<Label>(action_wrapper, bound_input.to_string(), theme::Typography::LabelSM);
            binding_label->set_font_family("promptfont");
            binding_label->set_font_style(FontStyle::Normal);;
            binding_label->set_font_weight(400);;
        }
    }
}

void Modal::set_on_close_callback(std::function<void()> callback) {
    on_close_callback = callback;
}

Modal *Modal::create_modal(ModalType modal_type) {
    ContextId new_context = recompui::create_context();
    new_context.open();
    Modal *modal = new_context.create_element<Modal>(new_context.get_root_element(), new_context, modal_type);
    new_context.close();
    return modal;
}

TabbedModal::TabbedModal(
    ResourceId rid,
    Document *parent,
    recompui::ContextId modal_root_context,
    ModalType modal_type
) : Modal(rid, parent, modal_root_context, modal_type)
{
    set_menu_action_callback(MenuAction::Back, [this]() {
        if (this->tabs != nullptr) {
            this->tabs->focus_on_active_tab();
        }
    }, "Back");
    set_menu_action_callback(MenuAction::TabLeft, [this]() {
        this->navigate_tab_direction(-1);
    }, "Previous Tab");
    set_menu_action_callback(MenuAction::TabRight, [this]() {
        this->navigate_tab_direction(1);
    }, "Next Tab");
}

void TabbedModal::process_event(const Event &e) {
    switch (e.type) {
        case EventType::Update: {
            if (previous_tab_index != current_tab_index) {
                body->clear_children();
                if (current_tab_index >= 0 && current_tab_index < tab_contexts.size()) {
                    tab_contexts[current_tab_index].create_contents(modal_root_context, body);
                }
                previous_tab_index = current_tab_index;
            }
            queue_update();
            break;
        }
    }

    Modal::process_event(e);
}

TabbedModal *TabbedModal::create_modal(ModalType modal_type) {
    ContextId new_context = recompui::create_context();
    new_context.open();
    TabbedModal *modal = new_context.create_element<TabbedModal>(new_context.get_root_element(), new_context, modal_type);
    new_context.close();
    return modal;
}

void TabbedModal::navigate_tab_direction(int direction) {
    if (tab_contexts.size() == 0 || tabs == nullptr) {
        return;
    }
    int next_index = tabs->get_next_tab_in_direction(tabs->get_active_tab(), direction);
    set_selected_tab(next_index);
    // Only focus if the tab changed to the intended tab, otherwise the tab change was cancelled.
    if (current_tab_index == next_index) {
        tabs->focus_on_active_tab();
    }
}

void TabbedModal::on_tab_change(int tab_index) {
    if (current_tab_index < tab_contexts.size() && current_tab_index >= 0) {
        if (tab_contexts[current_tab_index].can_close(TabCloseContext::TabChange)) {
            tab_contexts[current_tab_index].on_close(TabCloseContext::TabChange);
            current_tab_index = tab_index;
        } else if (tabs != nullptr) {
            // Revert tab change
            tabs->set_active_tab(current_tab_index, false);
        }
    } else {
        current_tab_index = tab_index;
    }
}

void TabbedModal::set_selected_tab(int tab_index) {
    if (tabs != nullptr) {
        tabs->set_active_tab(tab_index, true);
    }
}

void TabbedModal::set_selected_tab(const std::string &id) {
    if (tabs != nullptr) {
        for (int i = 0; i < tab_contexts.size(); i++) {
            if (tab_contexts[i].id == id) {
                tabs->set_active_tab(i, true);
                break;
            }
        }
    }
}

void TabbedModal::initialize_tab(TabContext &tab_context) {
    ContextId context = get_current_context();
    if (tabs == nullptr) {
        header->set_padding_left(0.0f); // tabs hug to left side
        tabs = context.create_element<TabSet>(header->get_left());
        tabs->set_change_tab_callback([this](int tab_index) {
            this->on_tab_change(tab_index);
        });
    }
    tabs->add_tab(tab_context.name);
}

void TabbedModal::add_tab(TabContext &&tab_context) {
    tab_contexts.emplace_back(std::move(tab_context));
    initialize_tab(tab_contexts.back());
}

void TabbedModal::add_tab(
    const std::string &name,
    const std::string &id,
    tab_callbacks::create_contents_t create_contents,
    tab_callbacks::can_close_t can_close,
    tab_callbacks::on_close_t on_close
) {
    tab_contexts.emplace_back(name, id, TabCallbacks{
        .create_contents = create_contents,
        .can_close = can_close,
        .on_close = on_close
    });
    initialize_tab(tab_contexts.back());
}

void TabbedModal::set_tab_visible(const std::string &id, bool is_visible) {
    if (tabs != nullptr) {
        for (int i = 0; i < tab_contexts.size(); i++) {
            if (tab_contexts[i].id == id) {
                tabs->set_tab_visible(i, is_visible);
                break;
            }
        }
    }
}

} // namespace recompui
