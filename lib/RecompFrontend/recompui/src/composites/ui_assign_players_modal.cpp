#include "ui_assign_players_modal.h"
#include "elements/ui_label.h"
#include "elements/ui_container.h"
#include "recompui.h"
#include "ultramodern/ultramodern.hpp"

namespace recompui {

recompui::ContextId assign_players_modal_context;
AssignPlayersModal* assign_players_modal_instance = nullptr;

namespace localstyles {
    namespace padding {
        static const float horizontal = 20.0f;
        static const float footer_vertical = 20.0f;
        static const float header_vertical = 16.0f;
    }

    namespace gap {
        static const float horizontal = 12.0f;
        static const float vertical = 20.0f;
    }
}

static void set_button_side_styles(Element *el) {
    el->set_align_items(AlignItems::Center);
    el->set_width_auto();
    el->set_height_auto();
    el->set_flex_basis_auto();
    el->set_gap(localstyles::gap::horizontal);
}

AssignPlayersModal::AssignPlayersModal(ResourceId rid, Document *parent) : Element(rid, parent, Events(EventType::MenuAction), "div", false) {
    assign_players_modal_instance = this;
    recompui::ContextId context = get_current_context();
    
    set_display(Display::Flex);
    set_flex_direction(FlexDirection::Column);
    set_background_color(theme::color::Transparent);
    set_display(Display::None);
    set_as_navigation_container(NavigationType::Auto);
    set_debug_id("AssignPlayersModal");

    modal_overlay = context.create_element<Element>(this);
    modal_overlay->set_background_color(theme::color::BGOverlay);
    modal_overlay->set_position(Position::Absolute);
    modal_overlay->set_top(0);
    modal_overlay->set_right(0);
    modal_overlay->set_bottom(0);
    modal_overlay->set_left(0);

    Element* modal_whole_page_wrapper = context.create_element<Element>(this);
    modal_whole_page_wrapper->set_display(Display::Flex);
    modal_whole_page_wrapper->set_position(Position::Absolute);
    modal_whole_page_wrapper->set_top(0);
    modal_whole_page_wrapper->set_right(0);
    modal_whole_page_wrapper->set_bottom(0);
    modal_whole_page_wrapper->set_left(0);
    modal_whole_page_wrapper->set_align_items(AlignItems::Center);
    modal_whole_page_wrapper->set_justify_content(JustifyContent::Center);

    Element* modal = context.create_element<Element>(modal_whole_page_wrapper);
    modal->set_display(Display::Flex);
    modal->set_position(Position::Relative);
    modal->set_flex(1.0f, 1.0f);
    modal->set_flex_basis(100, Unit::Percent);
    modal->set_flex_direction(FlexDirection::Column);
    modal->set_width(100, Unit::Percent);
    modal->set_gap(localstyles::gap::vertical);
    modal->set_max_width(700, Unit::Dp);
    modal->set_height_auto();
    modal->set_margin_auto();
    modal->set_border_width(theme::border::width);
    modal->set_border_radius(theme::border::radius_lg);
    modal->set_border_color(theme::color::Border);
    modal->set_background_color(theme::color::ModalOverlay);
    modal->set_color(theme::color::Text);

    fake_focus_button = context.create_element<Element>(modal, 0, "button", false);
    fake_focus_button->set_position(Position::Absolute);
    fake_focus_button->set_width(0, Unit::Dp);
    fake_focus_button->set_height(0, Unit::Dp);
    fake_focus_button->set_opacity(0);
    fake_focus_button->enable_focus();

    auto header = context.create_element<Element>(modal, 0, "div", false);
    header->set_display(Display::Block);
    header->set_width(100, Unit::Percent);
    header->set_height_auto();
    header->set_padding_top(localstyles::padding::header_vertical);
    header->set_padding_left(localstyles::padding::horizontal);
    header->set_padding_right(localstyles::padding::horizontal);

    context.create_element<Label>(header, "Assign Players", theme::Typography::Header3);

    player_elements_wrapper = context.create_element<Element>(modal, 0, "div", false);
    player_elements_wrapper->set_width(100, Unit::Percent);
    player_elements_wrapper->set_padding_left(localstyles::padding::horizontal);
    player_elements_wrapper->set_padding_right(localstyles::padding::horizontal);
    player_elements_wrapper->set_padding_top(0);
    player_elements_wrapper->set_padding_bottom(0);

    Element* footer = context.create_element<Element>(modal, 0, "div", false);
    footer->set_display(Display::Flex);
    footer->set_position(Position::Relative);
    footer->set_flex_direction(FlexDirection::Row);
    footer->set_as_navigation_container(NavigationType::Horizontal);
    footer->set_align_items(AlignItems::Center);
    footer->set_justify_content(JustifyContent::SpaceBetween);
    footer->set_width(100.0f, Unit::Percent);
    footer->set_height_auto();

    footer->set_padding_top(0);
    footer->set_padding_bottom(localstyles::padding::footer_vertical);
    footer->set_padding_left(localstyles::padding::horizontal);
    footer->set_padding_right(localstyles::padding::horizontal);

    auto left = context.create_element<Container>(footer, FlexDirection::Row, JustifyContent::FlexStart, 0);
    set_button_side_styles(left);
    keep_players_button = context.create_element<Button>(left, "Keep players", ButtonStyle::Tertiary);
    keep_players_button->set_debug_id("KeepPlayersButton");
    keep_players_button->add_pressed_callback([]() {
        if (recompinput::playerassignment::is_active()) recompinput::playerassignment::cancel_and_close_modal();
        else recompinput::playerassignment::stop_and_close_modal();
    });
    keep_players_button->set_enabled(false);

    auto right = context.create_element<Container>(footer, FlexDirection::Row, JustifyContent::FlexEnd, 0);
    retry_button = context.create_element<Button>(right, "Retry", ButtonStyle::Warning);
    retry_button->set_debug_id("RetryPlayerAssignmentButton");
    retry_button->set_enabled(false);
    retry_button->add_pressed_callback([this](){
        this->set_fake_focus_enabled(true);
        this->fake_focus_button->focus();
        recompinput::playerassignment::start();
        this->init_pending_state();
    });

    confirm_button = context.create_element<Button>(right, "Confirm", ButtonStyle::Primary);
    confirm_button->set_debug_id("ConfirmPlayerAssignmentButton");
    confirm_button->set_enabled(false);
    confirm_button->add_pressed_callback(recompinput::playerassignment::commit_player_assignment);
    set_button_side_styles(right);
}

AssignPlayersModal::~AssignPlayersModal() {
    assign_players_modal_instance = nullptr;
}

void AssignPlayersModal::set_fake_focus_enabled(bool enabled) {
    fake_focus_button->set_enabled(enabled);
    fake_focus_button->set_focusable(enabled);
}

void AssignPlayersModal::init_pending_state() {
    if (recompinput::playerassignment::is_active()) {
        keep_players_button->set_text("Cancel (Esc / Back)");
        keep_players_button->set_display(Display::Flex);
        keep_players_button->set_enabled(true);
        retry_button->set_enabled(false);
        retry_button->set_text("Retry");
        confirm_button->set_display(Display::Flex);
    } else {
        keep_players_button->set_text("Keep players");
        keep_players_button->set_display(Display::Flex);
        retry_button->set_enabled(true);
        retry_button->set_text("Reassign");

        if (recompinput::players::has_enough_players_assigned()) {
            keep_players_button->set_enabled(true);
            keep_players_button->focus();
        } else {
            keep_players_button->set_enabled(false);
            retry_button->focus();
        }

        confirm_button->set_display(Display::None);
    }
}

void AssignPlayersModal::lock_focus(bool lock) {
    if (lock) {
        // Force focus on fake button until min player count is hit.
        if (!fake_focus_button->is_enabled()) {
            set_fake_focus_enabled(true);
        }
        fake_focus_button->focus();
    } else {
        Element *fake_focus_as_element = static_cast<Element*>(fake_focus_button);
        // Remove fake focus button if focus is elsewhere.
        if (fake_focus_button->is_enabled() && fake_focus_as_element != get_current_context().get_focused_element()) {
            set_fake_focus_enabled(false);
        }
    }
}

void AssignPlayersModal::process_event(const Event &e) {
    if (!is_open) {
        return;
    }
    if (e.type == EventType::Update) {
        if (player_elements.empty() || player_elements.size() != recompinput::players::get_max_number_of_players()) {
            create_player_elements();
        }

        for (size_t i = 0; i < recompinput::players::get_max_number_of_players(); i++) {
            player_elements[i]->update_assignment_player_card();
        }

        if (recompinput::playerassignment::is_active()) {
            bool met_assignment_reqs = recompinput::playerassignment::met_assignment_requirements();
            lock_focus(!met_assignment_reqs);
            confirm_button->set_enabled(met_assignment_reqs);
            retry_button->set_enabled(met_assignment_reqs);
        } else {
            lock_focus(false);
        }

        queue_update();
    } else if (e.type == EventType::MenuAction) {
        auto& action = std::get<EventMenuAction>(e.variant);
        switch (action.action) {
            case MenuAction::Back: {
                if (recompinput::playerassignment::is_active()) {
                    recompinput::playerassignment::cancel_and_close_modal();
                    break;
                }
                ContextId context = get_current_context();
                Element *close_as_element = static_cast<Element*>(keep_players_button);
                if (context.get_focused_element() == close_as_element) {
                    recompinput::playerassignment::stop_and_close_modal();
                } else {
                    keep_players_button->focus();
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}

void AssignPlayersModal::create_player_elements() {
    player_elements_wrapper->clear_children();
    player_elements.clear();
    recompui::ContextId context = get_current_context();

    Element *row_wrapper = nullptr;

    int max_players = static_cast<int>(recompinput::players::get_max_number_of_players());

    bool should_scroll = max_players > 12;
    if (should_scroll) {
        player_elements_wrapper->set_overflow_y(Overflow::Auto);
        player_elements_wrapper->set_max_height(
            PlayerCard::assign_player_card_size * 3.5f + localstyles::gap::vertical * 2 + localstyles::gap::vertical * 2);
        player_elements_wrapper->set_padding_top(localstyles::gap::vertical);
        player_elements_wrapper->set_padding_bottom(localstyles::gap::vertical);
        player_elements_wrapper->set_border_top_width(theme::border::width);
        player_elements_wrapper->set_border_bottom_width(theme::border::width);
        player_elements_wrapper->set_border_color(theme::color::Border);
    } else {
        player_elements_wrapper->set_max_height(1080); // Arbitrary large number to disable max height.
        player_elements_wrapper->set_overflow_y(Overflow::Auto);
        player_elements_wrapper->set_padding_top(0);
        player_elements_wrapper->set_padding_bottom(0);
        player_elements_wrapper->set_border_top_width(0);
        player_elements_wrapper->set_border_bottom_width(0);
        player_elements_wrapper->set_border_color(theme::color::Transparent);
    }

    for (int i = 0; i < max_players; i++) {
        if (i % 4 == 0) {
            row_wrapper = context.create_element<Element>(player_elements_wrapper, 0, "div", false);
            row_wrapper->set_display(Display::Flex);
            row_wrapper->set_flex_direction(FlexDirection::Row);
            row_wrapper->set_justify_content(JustifyContent::SpaceBetween);
            row_wrapper->set_align_items(AlignItems::Center);
            row_wrapper->set_width(100.0f, Unit::Percent);
            row_wrapper->set_gap(localstyles::gap::horizontal);
            row_wrapper->set_as_navigation_container(NavigationType::Horizontal);
            row_wrapper->set_debug_id("PlayerCardRowWrapper" + std::to_string(i / 4));
        }
        
        PlayerCard* player_element = context.create_element<PlayerCard>(row_wrapper, i, true);
        if (should_scroll) {
            // Padding ensures that when focused via controller nav the card is fully visible.
            // Negative margin collapses the extra space.
            player_element->set_margin_top(-localstyles::gap::vertical);
            player_element->set_padding_top(localstyles::gap::vertical);
            player_element->set_padding_bottom(localstyles::gap::vertical);
        } else if (i + 4 < max_players) {
            player_element->set_padding_bottom(localstyles::gap::vertical);
        }
        player_elements.push_back(player_element);
    }

    if (max_players > 4 && max_players % 4 != 0) {
        // Add empty cards to keep grid alignment.
        int num_fakes = 4 - (max_players % 4);
        for (int i = 0; i < num_fakes; i++) {
            auto fake = context.create_element<Element>(row_wrapper);
            fake->set_width(PlayerCard::assign_player_card_size);
        }
    }
}

void AssignPlayersModal::open() {
    if (assign_players_modal_instance == nullptr) {
        return;
    }

    ContextId prev_context = try_close_current_context();
    if (!recompui::is_context_shown(assign_players_modal_context)) {
        recompui::show_context(assign_players_modal_context, "");
    }
    
    assign_players_modal_context.open();
    assign_players_modal_instance->modal_overlay->set_background_color(
        ultramodern::is_game_started() ? theme::color::Transparent : theme::color::BGOverlay);
    assign_players_modal_instance->is_open = true;
    assign_players_modal_instance->set_display(Display::Block);
    assign_players_modal_instance->create_player_elements();
    assign_players_modal_instance->init_pending_state();
    assign_players_modal_instance->queue_update();
    assign_players_modal_context.close();

    if (prev_context != ContextId::null()) {
        prev_context.open();
    }
}

void AssignPlayersModal::close() {
    if (assign_players_modal_instance == nullptr) {
        return;
    }

    if (recompui::is_context_shown(assign_players_modal_context)) {
        assign_players_modal_instance->set_display(Display::None);
        recompui::hide_context(assign_players_modal_context);
    }

    assign_players_modal_instance->is_open = false;
}

void AssignPlayersModal::init() {
    assign_players_modal_context = recompui::create_context();
    assign_players_modal_context.open();
    assign_players_modal_context.create_element<AssignPlayersModal>(assign_players_modal_context.get_root_element());
    assign_players_modal_context.close();
}

} // namespace recompui
