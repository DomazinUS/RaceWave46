#include "ui_config_page_controls.h"
#include "composites/ui_assign_players_modal.h"
#include "elements/ui_button.h"
#include "elements/ui_label.h"
#include "elements/ui_toggle.h"
#include "elements/ui_container.h"
#include "elements/ui_binding_button.h"
#include "elements/ui_select.h"
#include "elements/ui_svg.h"
#include "recompinput/profiles.h"
#include "recompui/config.h"
#include <algorithm>
#include <cmath>

namespace recompui {

ConfigPageControls *controls_page = nullptr;

const std::string_view active_state_style_name = "cont_opt_active";

// Separating this out, may be a good component later to expose.
class ScrollBuffer : public Element {
protected:
    std::string_view get_type_name() override { return "ScrollBuffer"; }
public:
    ScrollBuffer(ResourceId rid, Element *parent, float buffer_amount) : Element(rid, parent, 0, "div", false) {
        set_position(Position::Absolute);
        set_inset(-buffer_amount);
        set_pointer_events(PointerEvents::None);
    }
};

GameInputRow::GameInputRow(
    ResourceId rid,
    Element *parent,
    const GameInputContext &input_ctx,
    std::function<void()> on_active_callback,
    on_bind_click_callback on_bind_click,
    on_clear_or_reset_callback on_clear_or_reset
) : Element(rid, parent, Events(EventType::Hover, EventType::Focus), "div", false) {
    this->input_id = input_ctx.input_id;
    this->on_active_callback = on_active_callback;

    set_display(Display::Flex);
    set_position(Position::Relative);
    set_flex_direction(FlexDirection::Row);
    set_align_items(AlignItems::Center);
    set_justify_content(JustifyContent::SpaceBetween);
    set_width(100.0f, Unit::Percent);
    // Have to set height here for the scroll buffer to work.
    // Otherwise it fails to calculate the correct size (RmlUI issue)
    set_height(64.0f);

    set_padding_top(4.0f);
    set_padding_right(16.0f);
    set_padding_bottom(4.0f);
    set_padding_left(GameInputRow::left_padding);
    set_border_radius(theme::border::radius_sm);
    set_background_color(theme::color::Transparent);

    active_style.set_background_color(theme::color::ElevatedSoft);
    add_style(&active_style, active_state_style_name);

    recompui::ContextId context = get_current_context();

    set_debug_id("GameInputRow (" + input_ctx.name + ")");

    auto label = context.create_element<Label>(this, input_ctx.name, theme::Typography::LabelMD);
    label->set_color(theme::color::Primary);
    label->set_flex_grow(2.0f);
    label->set_flex_shrink(1.0f);
    label->set_flex_basis(300.0f);
    label->set_height_auto();
    // TODO: whitespace nowrap impl

    auto bindings_container = context.create_element<Element>(this, 0, "div", false);
    {
        bindings_container->set_display(Display::Flex);
        bindings_container->set_position(Position::Relative);
        bindings_container->set_flex_grow(2.0f);
        bindings_container->set_flex_shrink(1.0f);
        bindings_container->set_flex_basis(400.0f);
        bindings_container->set_flex_direction(FlexDirection::Row);
        bindings_container->set_align_items(AlignItems::Center);
        bindings_container->set_justify_content(JustifyContent::SpaceBetween);
        bindings_container->set_width(100.0f, Unit::Percent);
        bindings_container->set_height(56.0f);
        bindings_container->set_padding_right(12.0f);
        bindings_container->set_padding_left(4.0f);
        bindings_container->set_gap(4.0f);

        for (size_t i = 0; i < recompinput::num_bindings_per_input; i++) {
            BindingButton *binding_button = context.create_element<BindingButton>(bindings_container, "");
            binding_button->add_pressed_callback([this, i, on_bind_click]() {
               on_bind_click(this->input_id, i);
            });
            binding_button->set_debug_id("BindingButton (" + input_ctx.name + " Binding " + std::to_string(i) + ")");
            binding_buttons.push_back(binding_button);
        }
        binding_buttons[0]->set_as_primary_focus(true);
    }

    if (input_ctx.clearable) {
        auto clear_button = context.create_element<IconButton>(this, "icons/Trash.svg", ButtonStyle::Danger, IconButtonSize::Large);
        clear_button->add_pressed_callback([this, on_clear_or_reset]() {
            on_clear_or_reset(this->input_id, false);
        });
    } else {
        auto reset_button = context.create_element<IconButton>(this, "icons/Reset.svg", ButtonStyle::Warning, IconButtonSize::Large);
        reset_button->add_pressed_callback([this, on_clear_or_reset]() {
            on_clear_or_reset(this->input_id, true);
        });
    }

    bindings.resize(recompinput::num_bindings_per_input);
    for (size_t i = 0; i < recompinput::num_bindings_per_input; i++) {
        bindings[i] = recompinput::InputField();
    }

    scroll_buffer = context.create_element<ScrollBuffer>(this, 16.0f);
}

GameInputRow::~GameInputRow() {
}

void GameInputRow::update_bindings(BindingList &new_bindings) {
    for (size_t i = 0; i < new_bindings.size(); i++) {
        binding_buttons[i]->set_is_binding(false);

        // skip update if no changes
        if (
            new_bindings[i].input_id == bindings[i].input_id &&
            new_bindings[i].input_type == bindings[i].input_type) {
            continue;
        }

        binding_buttons[i]->set_binding(new_bindings[i].to_string());
        bindings[i] = new_bindings[i];
    }
}

void GameInputRow::process_event(const Event &e) {
    switch (e.type) {
    case EventType::Hover:
        {
            bool hover_active = std::get<EventHover>(e.variant).active;
            set_style_enabled(active_state_style_name, hover_active);
            if (hover_active && on_active_callback) {
                on_active_callback();
            }
        }
        break;
    case EventType::Focus:
        {
            bool focus_active = std::get<EventFocus>(e.variant).active;
            set_style_enabled(active_state_style_name, focus_active);
            if (focus_active && on_active_callback) {
                on_active_callback();
            }
            scroll_buffer->scroll_into_view();
        }
        break;
    default:
        break;
    }
}

void GameInputRow::focus_on_first_binding() {
    if (binding_buttons.size() > 0) {
        binding_buttons[0]->focus();
    }
}

ConfigPageControls::ConfigPageControls(ResourceId rid, Element *parent) : ConfigPage(rid, parent) {
    controls_page = this;

    multiplayer_enabled = recompinput::players::is_single_player_mode() == false;
    this->max_num_players = multiplayer_enabled ? recompinput::players::get_max_number_of_players() : 1;
    multiplayer_view_mappings = !multiplayer_enabled;

    set_selected_player(selected_player);

    // A game may have requested multiplayer before this lazy page exists,
    // including a cancelled assignment whose retry must remain available.
    force_update();

    set_as_navigation_container(NavigationType::Vertical);
    set_debug_id("ConfigPageControls");

    render_all();
}

ConfigPageControls::~ConfigPageControls() {
    controls_page = nullptr;
}

void ConfigPageControls::create_game_input_contexts() {
    game_input_sections.n64.contexts.clear();
    game_input_sections.menu.contexts.clear();
    game_input_sections.other.clear();

    for (int i = 0; i < static_cast<int>(recompinput::GameInput::COUNT); i++) {
        recompinput::GameInput input = static_cast<recompinput::GameInput>(i);
        if (recompinput::get_game_input_disabled(input)) {
            continue;
        }

        GameInputContext input_ctx = {
            recompinput::get_game_input_name(input),
            recompinput::get_game_input_description(input),
            input,
            recompinput::get_game_input_clearable(input)
        };

        if (recompinput::get_game_input_is_menu(input)) {
            game_input_sections.menu.contexts.push_back(input_ctx);
        } else {
            game_input_sections.n64.contexts.push_back(input_ctx);
        }
    }

    // TODO: fetch other (e.g. mod) inputs to game_input_sections.other
}

void ConfigPageControls::process_event(const Event &e) {
    switch (e.type) {
    case EventType::Update:
        if (awaiting_binding && !recompinput::binding::is_binding()) {
            awaiting_binding = false;
            update_control_mappings();

            if (awaiting_binding_for_menu_action_button) {
                config::get_config_modal()->render_menu_actions();
            }
        }
        if (last_update_index != update_index) {
            last_update_index = update_index;
            render_all();
        }
        queue_update();
        break;
    default:
        break;
    }
}

namespace {
std::function<void()> player_assignment_callback;
std::function<uint32_t()> player_assignment_available;
}

void set_player_assignment_callback(std::function<void()> callback, std::function<uint32_t()> available) {
    player_assignment_callback = std::move(callback);
    player_assignment_available = std::move(available);
    if (controls_page) controls_page->force_update();
}

void ConfigPageControls::force_update() {
    const uint32_t requested = player_assignment_available ? player_assignment_available() : 0;
    const bool enabled = !recompinput::players::is_single_player_mode() || requested > 1;
    max_num_players = enabled ? std::max(uint32_t(recompinput::players::get_max_number_of_players()), requested) : 1;
    if (enabled != multiplayer_enabled) {
        multiplayer_enabled = enabled;
        multiplayer_view_mappings = !enabled;
        selected_player = 0;
        set_current_profile_index();
    }
    if (multiplayer_enabled && multiplayer_view_mappings) {
        const auto device = recompinput::players::get_player_input_device(selected_player);
        if (!recompinput::players::get_player_is_assigned(selected_player) ||
            device == recompinput::InputDevice::COUNT ||
            recompinput::profiles::get_input_profile_for_player(selected_player, device) != selected_profile_index) {
            // A reconnection/assignment may change the device while its old
            // profile is being edited. Return to the cards before accepting
            // another binding into that stale profile.
            multiplayer_view_mappings = false;
        }
    }
    update_index++;
}

void ConfigPageControls::render_all() {
    render_header();
    render_body();
    render_footer();
}

void ConfigPageControls::render_header() {
    recompui::ContextId context = get_current_context();
    add_header();
    header->set_as_navigation_container(NavigationType::Horizontal);
    auto header_left = header->get_left();
    auto header_right = header->get_right();
    header_left->clear_children();
    header_right->clear_children();
    header_elements = {};
    keyboard_toggle = nullptr;

    // The supplied manual layout puts device selection and reset above the
    // mapping list. Keep the two-player assignment/profile workflow here too.
    if (!multiplayer_enabled) {
        keyboard_toggle = context.create_element<IconToggle>(header_left, "icons/Cont.svg", "icons/Keyboard.svg", ToggleSize::Large);
        keyboard_toggle->set_checked(single_player_show_keyboard_mappings);
        keyboard_toggle->add_checked_callback([this](bool checked) {
            single_player_show_keyboard_mappings = checked;
            update_control_mappings();
        });
    } else if (multiplayer_view_mappings) {
        header_elements.left.profile_name_label = context.create_element<Label>(header_left,
            "Editing: " + recompinput::profiles::get_input_profile_name(selected_profile_index), LabelStyle::Normal);
        auto go_back = context.create_element<Button>(header_right, "Go back", ButtonStyle::Tertiary);
        header_elements.right.go_back_button = go_back;
        go_back->add_pressed_callback([this]() {
            multiplayer_view_mappings = false;
            queue_selected_player_profile_edit_focus = true;
            force_update();
        });
    } else {
        auto assign = context.create_element<Button>(header_right, "Assign players", ButtonStyle::Primary);
        header_elements.right.assign_players_button = assign;
        assign->set_debug_id("AssignPlayersButton");
        assign->add_pressed_callback([]() {
            if (player_assignment_callback) {
                player_assignment_callback();
                return;
            }
            if (!recompinput::players::has_enough_players_assigned()) {
                recompinput::playerassignment::start();
            }
            AssignPlayersModal::open();
        });
        assign->set_as_primary_focus(true);
    }

    if (should_show_mappings()) {
        auto reset = context.create_element<Button>(header_right, "Reset to defaults", ButtonStyle::Warning);
        reset->add_pressed_callback([this]() {
            recompinput::profiles::reset_profile_bindings(selected_profile_index, get_player_input_device());
            update_control_mappings();
        });
    }
}

bool ConfigPageControls::should_show_mappings() {
    return (multiplayer_enabled && multiplayer_view_mappings) || !multiplayer_enabled;
}

void ConfigPageControls::render_body() {
    recompui::ContextId context = get_current_context();

    if (should_show_mappings()) {
        body->get_right()->set_display(Display::Flex);
        render_body_mappings();
    } else {
        body->get_right()->set_display(Display::None);
        render_body_players();
    }
}

void ConfigPageControls::render_body_mappings() {
    recompui::ContextId context = get_current_context();
    body->set_as_navigation_container(NavigationType::Horizontal);

    description_container = nullptr;
    controller_board = nullptr;
    controller_board_caption = nullptr;
    visual_input_nodes.clear();
    visual_binding_labels.clear();
    body->get_left()->set_flex_basis(42.0f, Unit::Percent);
    body->get_right()->set_flex_basis(58.0f, Unit::Percent);

    // left side
    {
        render_control_mappings();
    }

    // right side
    {
        body->get_right()->clear_children();
        render_controller_board();
        update_control_mappings();
    }
}

namespace {

// Fit the manual's controller diagram as a single composition, including its
// binding glyphs, instead of letting narrow windows distort or crop the buttons.
class ManualControllerCanvas : public Element {
    Element *drawing = nullptr;
    float previous_scale = -1.0f;
protected:
    std::string_view get_type_name() override { return "ManualControllerCanvas"; }
    void process_event(const Event &event) override {
        if (event.type == EventType::Update) {
            const float width = drawing->get_client_width();
            const float height = drawing->get_client_height();
            if (width > 0.0f && height > 0.0f) {
                const float scale = std::max(0.01f, std::min(get_client_width() / width, get_client_height() / height));
                if (std::abs(scale - previous_scale) > 0.001f) {
                    drawing->set_scale_2D(scale, scale);
                    previous_scale = scale;
                }
            }
            queue_update();
        }
    }
public:
    ManualControllerCanvas(ResourceId rid, Element *parent) : Element(rid, parent, Events(EventType::Update), "div", false) {
        set_position(Position::Relative);
        set_width(100.0f, Unit::Percent);
        set_height(100.0f, Unit::Percent);
        set_min_height(0.0f);
        set_flex_grow(1.0f);
        set_flex_shrink(1.0f);
        set_flex_basis(0.0f);
        set_overflow(Overflow::Hidden);
        set_pointer_events(PointerEvents::None);
        drawing = get_current_context().create_element<Element>(this, 0, "div", false);
        drawing->set_position(Position::Absolute);
        drawing->set_left(50.0f, Unit::Percent);
        drawing->set_top(50.0f, Unit::Percent);
        drawing->set_width(640.0f);
        drawing->set_height(500.0f);
        drawing->set_translate_2D(-50.0f, -50.0f, Unit::Percent);
        queue_update();
    }
    Element *get_drawing() { return drawing; }
};

} // namespace

void ConfigPageControls::render_controller_board() {
    auto context = get_current_context();
    auto right = body->get_right();
    right->set_flex_direction(FlexDirection::Column);
    right->set_min_width(0.0f);
    right->set_min_height(0.0f);
    right->set_padding(14.0f);
    right->set_background_color(Color{151, 167, 168, 255});

    controller_board = context.create_element<Element>(right, 0, "div", false);
    controller_board->set_debug_id("ManualControllerBoard");
    controller_board->set_display(Display::Flex);
    controller_board->set_flex_direction(FlexDirection::Column);
    controller_board->set_flex_grow(1.0f);
    controller_board->set_min_height(0.0f);
    controller_board->set_min_width(0.0f);
    controller_board->set_width(100.0f, Unit::Percent);
    controller_board->set_height(100.0f, Unit::Percent);
    controller_board->set_padding(12.0f);
    controller_board->set_border_width(3.0f);
    controller_board->set_border_radius(22.0f);
    controller_board->set_border_color(Color{101, 96, 172, 255});
    controller_board->set_background_color(Color{248, 250, 249, 255});

    controller_board_caption = context.create_element<Label>(controller_board, "", theme::Typography::LabelSM);
    controller_board_caption->set_color(theme::color::Primary);
    controller_board_caption->set_text_align(TextAlign::Center);
    controller_board_caption->set_height(26.0f);
    controller_board_caption->set_flex_shrink(0.0f);

    auto canvas = context.create_element<ManualControllerCanvas>(controller_board);
    auto drawing = canvas->get_drawing();
    auto svg_at = [&](const std::string &asset, float x, float y, float width, float height, Color color) {
        auto svg = context.create_element<Svg>(drawing, asset);
        svg->set_position(Position::Absolute);
        svg->set_left(x);
        svg->set_top(y);
        svg->set_width(width);
        svg->set_height(height);
        svg->set_image_color(color);
        return svg;
    };
    auto caption_at = [&](const std::string &text, float x, float y, float width) {
        auto label = context.create_element<Label>(drawing, text, theme::Typography::LabelXS);
        label->set_position(Position::Absolute);
        label->set_left(x);
        label->set_top(y);
        label->set_width(width);
        label->set_text_align(TextAlign::Center);
        label->set_color(theme::color::Primary);
        label->set_font_size(15.0f);
        label->set_line_height(19.0f);
    };
    auto node_at = [&](recompinput::GameInput input, const std::string &label, float x, float y, float size,
                       Color tint, const std::string &asset = "", float rotation = 0.0f) {
        if (!game_input_sections.get_context_by_input_id(input)) return;
        auto node = context.create_element<Element>(drawing, 0, "div", false);
        node->set_debug_id("ManualVisualInput " + recompinput::get_game_input_enum_name(input));
        node->set_position(Position::Absolute);
        node->set_left(x - size * 0.5f);
        node->set_top(y - size * 0.5f);
        node->set_width(size);
        node->set_height(size);
        node->set_border_width(3.0f);
        node->set_border_color(theme::color::Transparent);
        node->set_border_radius(size * 0.5f);
        if (!asset.empty()) {
            auto svg = context.create_element<Svg>(node, asset);
            svg->set_position(Position::Absolute);
            svg->set_inset(0.0f);
            svg->set_width(100.0f, Unit::Percent);
            svg->set_height(100.0f, Unit::Percent);
            svg->set_image_color(tint);
            if (rotation != 0.0f) svg->set_rotation(rotation);
        }
        auto title = context.create_element<Label>(node, label, theme::Typography::LabelXS);
        title->set_position(Position::Absolute);
        title->set_top(5.0f);
        title->set_width(100.0f, Unit::Percent);
        title->set_font_size(12.0f);
        title->set_line_height(14.0f);
        title->set_letter_spacing(0.0f);
        title->set_text_align(TextAlign::Center);
        title->set_color(theme::color::Text);
        auto binding = context.create_element<Label>(node, "", theme::Typography::LabelMD);
        binding->set_position(Position::Absolute);
        binding->set_top(size > 55.0f ? 24.0f : 20.0f);
        binding->set_width(100.0f, Unit::Percent);
        binding->set_text_align(TextAlign::Center);
        binding->set_font_family("promptfont");
        binding->set_font_weight(400);
        binding->set_font_size(size > 55.0f ? 25.0f : 21.0f);
        binding->set_line_height(26.0f);
        binding->set_letter_spacing(0.0f);
        binding->set_white_space(WhiteSpace::Nowrap);
        binding->set_color(theme::color::Text);
        visual_input_nodes[input] = node;
        visual_binding_labels[input] = binding;
    };

    using Input = recompinput::GameInput;
    const Color gray{118, 125, 128, 255};
    const Color pink{238, 78, 163, 255};
    const Color yellow{246, 194, 4, 255};
    const Color blue{63, 88, 178, 255};
    const Color green{51, 180, 121, 255};
    const Color red{243, 56, 82, 255};
    svg_at("icons/VizMap/DPad.svg", 38.0f, 59.0f, 174.0f, 174.0f, gray);
    caption_at("D-PAD", 45.0f, 242.0f, 160.0f);
    node_at(Input::DPAD_UP, "UP", 125, 87, 52, gray, "icons/VizMap/DPadArrow.svg");
    node_at(Input::DPAD_DOWN, "DOWN", 125, 206, 52, gray, "icons/VizMap/DPadArrow.svg", 180);
    node_at(Input::DPAD_LEFT, "LEFT", 66, 146, 52, gray, "icons/VizMap/DPadArrow.svg", -90);
    node_at(Input::DPAD_RIGHT, "RIGHT", 184, 146, 52, gray, "icons/VizMap/DPadArrow.svg", 90);

    node_at(Input::START, "START", 280, 86, 58, red, "icons/VizMap/ButtonSmall.svg");
    node_at(Input::B, "B", 361, 101, 72, green, "icons/VizMap/ButtonLarge.svg");
    node_at(Input::A, "A", 418, 163, 80, blue, "icons/VizMap/ButtonLarge.svg");
    node_at(Input::C_UP, "C UP", 540, 64, 65, yellow, "icons/VizMap/ButtonMedium.svg");
    node_at(Input::C_LEFT, "C LEFT", 487, 125, 65, yellow, "icons/VizMap/ButtonMedium.svg");
    node_at(Input::C_RIGHT, "C RIGHT", 593, 125, 65, yellow, "icons/VizMap/ButtonMedium.svg");
    node_at(Input::C_DOWN, "C DOWN", 540, 186, 65, yellow, "icons/VizMap/ButtonMedium.svg");

    svg_at("icons/VizMap/ButtonLarge.svg", 230.0f, 249.0f, 190.0f, 190.0f, pink);
    caption_at("CONTROL STICK", 225.0f, 226.0f, 200.0f);
    node_at(Input::Y_AXIS_POS, "UP", 325, 280, 54, pink, "icons/VizMap/DPadArrow.svg");
    node_at(Input::Y_AXIS_NEG, "DOWN", 325, 408, 54, pink, "icons/VizMap/DPadArrow.svg", 180);
    node_at(Input::X_AXIS_NEG, "LEFT", 262, 344, 54, pink, "icons/VizMap/DPadArrow.svg", -90);
    node_at(Input::X_AXIS_POS, "RIGHT", 388, 344, 54, pink, "icons/VizMap/DPadArrow.svg", 90);

    node_at(Input::L, "L", 87, 433, 70, gray, "icons/VizMap/ButtonLarge.svg");
    node_at(Input::Z, "Z", 325, 470, 50, gray, "icons/VizMap/ButtonMedium.svg");
    node_at(Input::R, "R", 555, 433, 70, gray, "icons/VizMap/ButtonLarge.svg");

    description_container = context.create_element<Label>(controller_board, "Select a mapping to see its control on the diagram.", theme::Typography::Body);
    description_container->set_height(42.0f);
    description_container->set_flex_shrink(0.0f);
    description_container->set_font_size(16.0f);
    description_container->set_line_height(20.0f);
    description_container->set_text_align(TextAlign::Center);
    description_container->set_color(theme::color::Primary);
}

void ConfigPageControls::update_controller_board(const PlayerBindings &bindings) {
    if (controller_board_caption) {
        const std::string device = get_player_input_device() == recompinput::InputDevice::Keyboard ? "KEYBOARD" : "CONTROLLER";
        controller_board_caption->set_text("PLAYER " + std::to_string(selected_player + 1) + " / " + device + " MAPPINGS");
    }
    for (const auto &[input, label] : visual_binding_labels) {
        std::string text;
        auto found = bindings.find(input);
        if (found != bindings.end()) {
            for (const auto &binding : found->second) {
                if (binding.is_empty()) continue;
                if (!text.empty()) text += " ";
                const auto glyph = binding.to_string();
                text += glyph == recompinput::unknown_device_input ? "?" : glyph;
            }
        }
        label->set_text(text);
    }
}

void ConfigPageControls::render_body_players() {
    recompui::ContextId context = get_current_context();
    body->set_as_navigation_container(NavigationType::Horizontal);
    body->set_max_height(100.0f, Unit::Percent);

    auto body_left = body->get_left();
    body->get_right()->clear_children();
    description_container = nullptr;
    controller_board = nullptr;
    controller_board_caption = nullptr;
    visual_input_nodes.clear();
    visual_binding_labels.clear();
    body_left->set_flex_basis(100.0f, Unit::Percent);
    body_left->clear_children();
    player_cards.clear();

    body_left->set_display(Display::Block);
    // Top/bottom padding is within the player cards so that controller nav puts them more into view.
    body_left->set_padding_top(0.0f);
    body_left->set_padding_bottom(0.0f);
    body_left->set_padding_right(64.0f);
    body_left->set_padding_left(64.0f);
    body_left->set_as_navigation_container(NavigationType::GridCol);
    body_left->set_position(Position::Relative);
    body_left->set_height_auto();
    body_left->set_max_height(100.0f, Unit::Percent);
    body_left->set_overflow_y(Overflow::Auto);

    bool make_fakes = max_num_players > 4;

    recompui::Element *player_grid = nullptr;
    // Grid supports groups of 4
    for (int i = 0; i < max_num_players; i += 4) {
        player_grid = context.create_element<Element>(body_left, 0, "div", false);
        player_grid->set_as_navigation_container(NavigationType::GridRow);
        player_grid->set_display(Display::Flex);
        player_grid->set_flex_direction(FlexDirection::Row);
        player_grid->set_justify_content(JustifyContent::Center);
        player_grid->set_align_items(AlignItems::Center);
        player_grid->set_width(100.0f, Unit::Percent);
        player_grid->set_height_auto();
        player_grid->set_gap(64.0f);
        // Remove extra margin already added as padding from player cards.
        // The player cards still need the padding for controller nav visibility.
        player_grid->set_margin_bottom(-64.0f);

        for (int j = i; j < i + 4; j++) {
            if (!make_fakes && j >= max_num_players) {
                break;
            }

            if (make_fakes && j >= 4 && j >= max_num_players) {
                auto fake = context.create_element<Element>(player_grid);
                fake->set_width(PlayerCard::static_player_card_size, Unit::Dp);
                continue;
            }

            auto player_card = context.create_element<PlayerCard>(
                player_grid,
                j,
                false
            );
            player_card->set_on_select_profile_callback([this](int player_index, int profile_index) {
                this->on_select_player_profile(player_index, profile_index);
            });
            player_card->set_on_edit_profile_callback([this](int player_index) {
                this->on_edit_player_profile(player_index);
            });
            player_cards.push_back(player_card);
            if (i == 0 && j == 0) {
                player_card->set_as_primary_focus(true);
            }
        }
    }

    // Retain 64px bottom margin on the last row.
    if (player_grid != nullptr) {
        player_grid->set_margin_bottom(0.0f);
    }

    if (queue_selected_player_profile_edit_focus) {
        queue_selected_player_profile_edit_focus = false;
        if (selected_player >= 0 && selected_player < static_cast<int>(player_cards.size())) {
            player_cards[selected_player]->focus_on_edit_profile_button();
        }
    }
}

void ConfigPageControls::on_select_player_profile(int player_index, int profile_index) {
    auto& assigned_player = recompinput::players::get_player(player_index);
    recompinput::InputDevice device = recompinput::players::get_player_input_device(player_index);
    if (device != recompinput::InputDevice::COUNT) {
        recompinput::profiles::set_input_profile_for_player(player_index, profile_index, device);
    }
}

void ConfigPageControls::on_edit_player_profile(int player_index) {
    selected_player = player_index;
    recompinput::InputDevice device = recompinput::players::get_player_input_device(player_index);
    if (device != recompinput::InputDevice::COUNT) {
        selected_profile_index = recompinput::profiles::get_input_profile_for_player(player_index, device);
        multiplayer_view_mappings = true;
        queue_first_game_input_row_focus = true;
        force_update();
    }
}

void ConfigPageControls::render_footer() {
    hide_footer();
}

void ConfigPageControls::render_control_mappings() {
    recompui::ContextId context = get_current_context();

    auto body_left = body->get_left();
    body_left->clear_children();

    body_left->set_display(Display::Block);
    body_left->set_padding(0.0f);
    body_left->set_as_navigation_container(NavigationType::Vertical);
    body_left->set_position(Position::Relative);
    body_left->set_height(100.0f, Unit::Percent);
    body_left->set_max_height(100.0f, Unit::Percent);
    body_left->set_overflow_y(Overflow::Auto);
    
    {
        auto body_left_scroll = context.create_element<Element>(body_left, 0, "div", false);
        body_left_scroll->set_display(Display::Block);
        body_left_scroll->set_width(100.0f, Unit::Percent);
        body_left_scroll->set_max_height(100.0f, Unit::Percent);
        body_left_scroll->set_overflow_y(Overflow::Scroll);
        body_left_scroll->set_as_navigation_container(NavigationType::GridCol);
        body_left_scroll->set_padding_left(8.0f);
        body_left_scroll->set_padding_right(8.0f);
        body_left_scroll->set_debug_id("Mappings Scroll Container");

        game_input_rows.clear();

        create_game_input_contexts();
        set_current_profile_index();

        rows_wrappers.clear();
        for (auto *section : game_input_sections.get_all_sections()) {
            if (section->contexts.size() == 0) {
                continue;
            }
            GameInputRowsWrapper *section_wrapper = context.create_element<GameInputRowsWrapper>(
                body_left_scroll, section->name, section == &game_input_sections.menu);
            rows_wrappers.push_back(section_wrapper);

            for (auto &input_ctx : section->contexts) {
                recompinput::GameInput input_id = input_ctx.input_id;
                GameInputRow *row = context.create_element<GameInputRow>(
                    static_cast<Element*>(section_wrapper),
                    input_ctx,
                    [this, input_id]() {
                        this->on_option_hover(input_id);
                    },
                    [this](recompinput::GameInput game_input, int input_index) {
                        this->on_bind_click(game_input, input_index);
                    },
                    [this](recompinput::GameInput game_input, bool reset) {
                        this->on_clear_or_reset_game_input(game_input, reset);
                    }
                );
                game_input_rows.push_back(row);
                row->set_as_navigation_container(NavigationType::GridRow);
            }
        }
    }

    update_control_mappings();
    if (queue_first_game_input_row_focus && game_input_rows.size() > 0) {
        game_input_rows[0]->focus_on_first_binding();
        queue_first_game_input_row_focus = false;
    }
}

void ConfigPageControls::set_current_profile_index() {
    if (!multiplayer_enabled) {
        selected_profile_index = single_player_show_keyboard_mappings
            ? recompinput::profiles::get_sp_keyboard_profile_index()
            : recompinput::profiles::get_sp_controller_profile_index();
    }
}

void ConfigPageControls::update_control_mappings() {
    if (!multiplayer_enabled) {
        selected_player = 0;
        set_current_profile_index();
    } else if (!multiplayer_view_mappings) {
        return;
    }

    // Decide section visibility, reset margins
    for (auto *wrapper : rows_wrappers) {
        wrapper->set_margin_top(0.0f);
        wrapper->set_margin_bottom(0.0f);
        if (wrapper->is_menu) {
            if (get_player_input_device() == recompinput::InputDevice::Keyboard) {
                wrapper->display_hide();
            } else {
                wrapper->display_show();
            }
            break;
        }
    }

    recompui::GameInputRowsWrapper *first = nullptr;
    recompui::GameInputRowsWrapper *last = nullptr;
    for (auto *wrapper : rows_wrappers) {
        bool visible = wrapper->get_display() != Display::None;
        if (visible) {
            if (first == nullptr) {
                first = wrapper;
            }
            last = wrapper;
        }
    }

    // Need to use margins here instead of padding on the scroll parent.
    // RmlUI scroll areas weren't accounting for the bottom padding and this was the only way
    // to circumvent that.
    if (first != nullptr) {
        first->set_margin_top(8.0f);
    }
    if (last != nullptr) {
        last->set_margin_bottom(8.0f);
    }

    PlayerBindings game_input_bindings;
    for (auto *ctx : game_input_sections.get_all_contexts()) {
        game_input_bindings[ctx->input_id] = {};

        for (int j = 0; j < recompinput::num_bindings_per_input; j++) {
            game_input_bindings[ctx->input_id].push_back(recompinput::profiles::get_input_binding(selected_profile_index, ctx->input_id, j));
        }
    }

    for (size_t i = 0; i < game_input_rows.size(); i++) {
        game_input_rows[i]->update_bindings(
            game_input_bindings.at(game_input_rows[i]->get_input_id())
        );
    }
    update_controller_board(game_input_bindings);
}

recompinput::InputDevice ConfigPageControls::get_player_input_device() {
    if (multiplayer_enabled) {
        return recompinput::players::get_player_input_device(this->selected_player);
    }

    return single_player_show_keyboard_mappings
        ? recompinput::InputDevice::Keyboard
        : recompinput::InputDevice::Controller;
}

void ConfigPageControls::on_bind_click(recompinput::GameInput game_input, int input_index) {
    recompinput::InputDevice device = get_player_input_device();

    recompinput::binding::start_scanning(this->selected_player, game_input, input_index, device);
    awaiting_binding = true;
    awaiting_binding_for_menu_action_button = get_game_input_is_menu(game_input);
}

void ConfigPageControls::on_clear_or_reset_game_input(recompinput::GameInput game_input, bool reset) {
    if (!reset) {
        recompinput::profiles::clear_input_binding(selected_profile_index, game_input);
    } else {
        recompinput::InputDevice device = get_player_input_device();
        recompinput::profiles::reset_input_binding(selected_profile_index, device, game_input);
    }
    update_control_mappings();
}

void ConfigPageControls::set_selected_player(int player) {
    selected_player = player;
}

void ConfigPageControls::on_option_hover(recompinput::GameInput input_id) {
    for (const auto &[input, node] : visual_input_nodes) {
        node->set_border_color(input == input_id ? theme::color::Secondary : theme::color::Transparent);
        node->set_scale_2D(input == input_id ? 1.12f : 1.0f, input == input_id ? 1.12f : 1.0f);
    }
    if (description_container) {
        GameInputContext *ctx = game_input_sections.get_context_by_input_id(input_id);
        if (ctx != nullptr) {
            description_container->set_text(ctx->description.empty() ? ctx->name : ctx->name + ": " + ctx->description);
        } else {
            description_container->set_text("");
        }
    }
}


} // namespace recompui
