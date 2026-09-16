#include "ui_mod_menu.h"
#include "ui_utils.h"
#include "recompui/recompui.h"
#include "recompui/config.h"
#include "util/file.h"
#include "renderer.h"
#include "elements/ui_modal.h"
#include "elements/ui_button.h"
#include "config/ui_config_page_options_menu.h"

#include "librecomp/mods.hpp"

#include <string>

#ifdef WIN32
#include <shellapi.h>
#endif

// TODO:
// - Set up navigation.
// - Add hover and active state for mod entries.

namespace recompui {

static std::string generate_thumbnail_src_for_mod(const std::string &mod_id) {
    return "?/mods/" + mod_id + "/thumb";
}

static bool is_mod_enabled_or_auto(const std::string &mod_id) {
    return recomp::mods::is_mod_enabled(mod_id) || recomp::mods::is_mod_auto_enabled(mod_id);
}

Modal *mod_config_modal = nullptr;
void create_mod_config_modal() {
    if (mod_config_modal == nullptr) {
        mod_config_modal = Modal::create_modal(ModalType::Fullscreen);
    }
}

// ModEntryView
constexpr float modEntryHeight = 120.0f;
constexpr float modEntryPadding = 4.0f;

extern const std::string mod_tab_id;
const std::string mod_tab_id = "#tab_mods";

ModEntryView::ModEntryView(ResourceId rid, Element *parent) : Element(rid, parent, Events(EventType::Update)) {
    ContextId context = get_current_context();

    set_display(Display::Flex);
    set_flex_direction(FlexDirection::Row);
    set_width(100.0f, Unit::Percent);
    set_height_auto();
    set_padding(modEntryPadding);
    set_border_left_width(6.0f);
    set_border_color(recompui::theme::color::WhiteA5);
    set_background_color(recompui::theme::color::WhiteA5);
    set_cursor(Cursor::Pointer);
    set_color(theme::color::Text);

    checked_style.set_border_color(theme::color::BorderSolid);
    checked_style.set_color(theme::color::White);
    checked_style.set_background_color(theme::color::Primary);
    hover_style.set_border_color(theme::color::BorderHard);
    hover_style.set_background_color(theme::color::PrimaryA20);
    checked_hover_style.set_border_color(theme::color::Secondary);
    checked_hover_style.set_background_color(theme::color::PrimaryD);
    pulsing_style.set_border_color(theme::color::SecondaryA80);

    {
        thumbnail_image = context.create_element<Image>(this, "");
        thumbnail_image->set_width(modEntryHeight);
        thumbnail_image->set_height(modEntryHeight);
        thumbnail_image->set_min_width(modEntryHeight);
        thumbnail_image->set_min_height(modEntryHeight);
        thumbnail_image->set_background_color(theme::color::BGOverlay);


        body_container = context.create_element<Element>(this);
        body_container->set_width_auto();
        body_container->set_margin_left(16.0f);
        body_container->set_padding_top(8.0f);
        body_container->set_padding_bottom(8.0f);
        body_container->set_max_height(modEntryHeight);
        body_container->set_overflow_y(Overflow::Hidden);

        {
            name_label = context.create_element<Label>(body_container, LabelStyle::Normal);
            description_label = context.create_element<Label>(body_container, LabelStyle::Small);
            description_label->set_margin_top(4.0f);
            description_label->set_color(theme::color::TextDim);
        } // body_container
    } // this

    add_style(&checked_style, checked_state);
    add_style(&hover_style, hover_state);
    add_style(&checked_hover_style, { checked_state, hover_state });
    add_style(&pulsing_style, { focus_state });
}

ModEntryView::~ModEntryView() {

}

void ModEntryView::set_mod_details(const recomp::mods::ModDetails &details) {
    name_label->set_text(details.display_name);
    description_label->set_text(details.short_description);
}

void ModEntryView::set_mod_thumbnail(const std::string &thumbnail) {
    thumbnail_image->set_src(thumbnail);
}

void ModEntryView::set_mod_enabled(bool enabled) {
    mod_enabled = enabled;
    // Dimming the whole row also washes out its selection and focus feedback.
    thumbnail_image->set_opacity(enabled ? 1.0f : 0.5f);
    update_content_colors();
}

void ModEntryView::set_selected(bool selected) {
    set_style_enabled(checked_state, selected);
    update_content_colors();
}

void ModEntryView::update_content_colors() {
    const bool selected = is_style_enabled(checked_state);
    name_label->set_color(selected ? theme::color::White :
        (mod_enabled ? theme::color::Text : theme::color::TextDim));
    description_label->set_color(selected ? theme::color::White : theme::color::TextDim);
}

void ModEntryView::set_focused(bool focused) {
    set_style_enabled(focus_state, focused);
}

void ModEntryView::process_event(const Event &e) {
    switch (e.type) {
    case EventType::Update:
        if (is_style_enabled(focus_state)) {
            // Keep the title readable while the focus outline pulses.
            pulsing_style.set_border_color(recompui::get_pulse_color(750));
            apply_styles();
            queue_update();
        }

        break;
    default:
        break;
    }
}

// ModEntryButton

ModEntryButton::ModEntryButton(ResourceId rid, Element *parent, uint32_t mod_index) : Element(rid, parent, Events(EventType::Click, EventType::Hover, EventType::Focus, EventType::Drag)) {
    this->mod_index = mod_index;

    set_drag(Drag::Drag);
    enable_focus();

    ContextId context = get_current_context();
    view = context.create_element<ModEntryView>(this);
}

ModEntryButton::~ModEntryButton() {

}

void ModEntryButton::set_mod_selected_callback(std::function<void(uint32_t)> callback) {
    selected_callback = callback;
}

void ModEntryButton::set_mod_drag_callback(std::function<void(uint32_t, EventDrag)> callback) {
    drag_callback = callback;
}

void ModEntryButton::set_mod_details(const recomp::mods::ModDetails &details) {
    view->set_mod_details(details);
}

void ModEntryButton::set_mod_thumbnail(const std::string &thumbnail) {
    view->set_mod_thumbnail(thumbnail);
}

void ModEntryButton::set_mod_enabled(bool enabled) {
    view->set_mod_enabled(enabled);
}

void ModEntryButton::set_selected(bool selected) {
    view->set_selected(selected);
    set_as_primary_focus(selected);
}

void ModEntryButton::set_focused(bool focused) {
    view->set_focused(focused);
    view->queue_update();
    if (focused) {
        scroll_into_view();
    }
}

void ModEntryButton::process_event(const Event& e) {
    switch (e.type) {
    case EventType::Focus:
        selected_callback(mod_index);
        set_focused(std::get<EventFocus>(e.variant).active);
        break;
    case EventType::Hover:
        view->set_style_enabled(hover_state, std::get<EventHover>(e.variant).active);
        break;
    case EventType::Drag:
        drag_callback(mod_index, std::get<EventDrag>(e.variant));
        break;
    default:
        break;
    }
}

// ModEntrySpacer

void ModEntrySpacer::check_height_distance() {
    constexpr float tolerance = 0.01f;
    if (abs(target_height - height) < tolerance) {
        height = target_height;
        set_height(height, Unit::Dp);
    }
    else {
        queue_update();
    }
}

void ModEntrySpacer::process_event(const Event &e) {
    switch (e.type) {
    case EventType::Update: {
        std::chrono::high_resolution_clock::duration now = ultramodern::time_since_start();
        float delta_time = std::max(std::chrono::duration<float>(now - last_time).count(), 0.0f);
        constexpr float dp_speed = 1000.0f;
        last_time = now;

        if (target_height < height) {
            height += std::max(-dp_speed * delta_time, target_height - height);
        }
        else {
            height += std::min(dp_speed * delta_time, target_height - height);
        }

        set_height(height, Unit::Dp);
        check_height_distance();
        break;
    }
    default:
        break;
    }
}

ModEntrySpacer::ModEntrySpacer(ResourceId rid, Element *parent) : Element(rid, parent) {
    set_border_width(theme::border::width);
    set_border_color(recompui::theme::color::Transparent);
}

void ModEntrySpacer::set_target_height(float target_height, bool animate_to_target) {
    this->target_height = target_height;

    if (animate_to_target) {
        last_time = ultramodern::time_since_start();
        check_height_distance();
    }
    else {
        height = target_height;
        set_height(target_height, Unit::Dp);
    }
}

void ModEntrySpacer::set_active(bool active) {
    this->active = active;
    if (active) {
        set_border_color(recompui::theme::color::PrimaryL);
        set_background_color(recompui::theme::color::PrimaryL, 255/4);
    } else {
        set_border_color(recompui::theme::color::Transparent);
        set_background_color(recompui::theme::color::Transparent);
    }
}

recompui::ModMenu* mod_menu = nullptr;
static std::string current_game_mod_id = "";


// ModMenu

void ModMenu::refresh_mods(bool scan_mods) {
    for (const std::string &thumbnail : loaded_thumbnails) {
        recompui::release_image(thumbnail);
    }

    // Prevent scanning mods after starting the game.
    if (scan_mods && !ultramodern::is_game_started()) {
        recomp::mods::scan_mods();
    }
    mod_details = recomp::mods::get_all_mod_details(game_mod_id);
    create_mod_list();
}

void ModMenu::open_mods_folder() {
    std::filesystem::path mods_directory = recomp::mods::get_mods_directory();
#if defined(WIN32)
    std::wstring path_wstr = mods_directory.wstring();
    ShellExecuteW(NULL, L"open", path_wstr.c_str(), NULL, NULL, SW_SHOWDEFAULT);
#elif defined(__linux__)
    std::string command = "xdg-open \"" + mods_directory.string() + "\" &";
    std::system(command.c_str());
#elif defined(__APPLE__)
    std::string command = "open \"" + mods_directory.string() + "\"";
    std::system(command.c_str());
#else
    static_assert(false, "Not implemented for this platform.");
#endif
}

void ModMenu::open_install_dialog() {
    recompui::file::open_file_dialog_multiple([](bool success, const std::list<std::filesystem::path>& paths) {
        if (success) {
            ContextId old_context = recompui::try_close_current_context();

            recompui::drop_files(paths);

            if (old_context != ContextId::null()) {
                old_context.open();
            }
        }
    });
}

void ModMenu::mod_toggled(bool enabled) {
    if (active_mod_index >= 0) {
        recomp::mods::enable_mod(mod_details[active_mod_index].mod_id, enabled);
        
        // Refresh enabled status for all mods in case one of them got auto-enabled due to being a dependency.
        for (size_t i = 0; i < mod_entry_buttons.size(); i++) {
            mod_entry_buttons[i]->set_mod_enabled(is_mod_enabled_or_auto(mod_details[i].mod_id));
        }
    }
}

void ModMenu::mod_selected(uint32_t mod_index) {
    if (active_mod_index >= 0) {
        mod_entry_buttons[active_mod_index]->set_selected(false);
    }

    active_mod_index = mod_index;

    if (active_mod_index >= 0) {
        std::string thumbnail_src = generate_thumbnail_src_for_mod(mod_details[mod_index].mod_id);
        const recomp::config::ConfigSchema &config_schema = recomp::mods::get_mod_config_schema(mod_details[active_mod_index].mod_id);
        bool toggle_checked = is_mod_enabled_or_auto(mod_details[mod_index].mod_id);
        bool auto_enabled = recomp::mods::is_mod_auto_enabled(mod_details[mod_index].mod_id);
        recomp::mods::DeprecationStatus deprecation_status = recomp::mods::get_mod_deprecation_status(mod_details[mod_index].mod_id);
        bool deprecated = recomp::mods::is_mod_deprecated(mod_details[mod_index].mod_id, mod_details[mod_index].version);
        bool toggle_enabled = !auto_enabled && !deprecated && (mod_details[mod_index].runtime_toggleable || !ultramodern::is_game_started());
        bool configure_enabled = !config_schema.options.empty();
        mod_details_panel->set_mod_details(mod_details[mod_index], thumbnail_src, toggle_checked, toggle_enabled, auto_enabled || deprecated, configure_enabled, deprecation_status);
        mod_entry_buttons[active_mod_index]->set_selected(true);
    }
}

void ModMenu::mod_dragged(uint32_t mod_index, EventDrag drag) {
    constexpr float spacer_height = modEntryHeight + modEntryPadding * 2.0f;

    switch (drag.phase) {
    case DragPhase::Start: {
        float this_top = get_absolute_top();
        float this_left = get_absolute_left();
        for (size_t i = 0; i < mod_entry_buttons.size(); i++) {
            mod_entry_middles[i] = mod_entry_buttons[i]->get_offset_top();
        }

        // When the drag phase starts, we make the floating mod details visible and store the relative coordinate of the
        // mouse cursor. Instantly hide the real element and use a spacer in its place that will stay on the same size as
        // long as the cursor is hovering over this slot.
        float width = mod_entry_buttons[mod_index]->get_client_width();
        float height = mod_entry_buttons[mod_index]->get_client_height();
        float left = mod_entry_buttons[mod_index]->get_absolute_left();
        float top = mod_entry_buttons[mod_index]->get_absolute_top();
        mod_entry_buttons[mod_index]->set_display(Display::None);
        mod_entry_buttons[mod_index]->set_focused(false);
        mod_entry_floating_view->set_display(Display::Flex);
        mod_entry_floating_view->set_mod_details(mod_details[mod_index]);
        mod_entry_floating_view->set_mod_thumbnail(generate_thumbnail_src_for_mod(mod_details[mod_index].mod_id));
        mod_entry_floating_view->set_mod_enabled(is_mod_enabled_or_auto(mod_details[mod_index].mod_id));
        // Moves the mod with the cursor, commenting out in case it is preferred over keeping it aligned.
        // mod_entry_floating_view->set_left(left - this_left, Unit::Px);
        mod_entry_floating_view->set_left(0, Unit::Px);
        mod_entry_floating_view->set_top(top - this_top, Unit::Px);
        mod_entry_floating_view->set_width(width, Unit::Px);
        mod_entry_floating_view->set_height(height, Unit::Px);
        mod_drag_start_coordinates[0] = drag.x;
        mod_drag_start_coordinates[1] = drag.y;
        mod_drag_view_coordinates[0] = left;
        mod_drag_view_coordinates[1] = top;

        mod_drag_target_index = mod_index;
        mod_entry_spacers[mod_drag_target_index]->set_target_height(spacer_height, false);
        mod_entry_spacers[mod_drag_target_index]->set_active(true);
        mod_entry_spacers[mod_entry_spacers.size() - 1]->set_target_height(spacer_height, false);
        break;
    }
    case DragPhase::Move: {
        float this_top = get_absolute_top();
        float this_left = get_absolute_left();
        float scroll_top = list_scroll_container->get_scroll_top();

        float delta_x = drag.x - mod_drag_start_coordinates[0];
        float delta_y = drag.y - mod_drag_start_coordinates[1];
        // Moves the mod with the cursor, commenting out in case it is preferred over keeping it aligned.
        // mod_entry_floating_view->set_left(mod_drag_view_coordinates[0] + delta_x - this_left, Unit::Px);
        mod_entry_floating_view->set_left(0, Unit::Px);
        mod_entry_floating_view->set_top(mod_drag_view_coordinates[1] + delta_y - this_top, Unit::Px);

        uint32_t closest = 0;
        float best_distance = std::numeric_limits<float>::max();
        float y_pos = mod_drag_view_coordinates[1] + delta_y + scroll_top - this_top;
        for (uint32_t i = 0; static_cast<size_t>(i) < mod_entry_middles.size(); i++) {
            float new_distance = abs(y_pos - mod_entry_middles[i]);
            if (new_distance < best_distance) {
                best_distance = new_distance;
                closest = i;
            } else {
                break;
            }
        }

        uint32_t new_index = closest;

        if (mod_drag_target_index != new_index) {
            uint32_t extra_space = (mod_drag_target_index > mod_index) ? 1 : 0;
            mod_entry_spacers[mod_drag_target_index + extra_space]->set_target_height(0.0f, true);
            mod_entry_spacers[mod_drag_target_index + extra_space]->set_active(false);
            mod_drag_target_index = new_index;
            extra_space = (mod_drag_target_index > mod_index) ? 1 : 0;
            mod_entry_spacers[new_index + extra_space]->set_target_height(spacer_height, true);
            mod_entry_spacers[new_index + extra_space]->scroll_into_view(true);
            mod_entry_spacers[new_index + extra_space]->set_active(true);
        }

        break;
    }
    case DragPhase::End: {
        // Dragging has ended, hide the floating view.
        mod_entry_buttons[mod_index]->set_display(Display::Block);
        mod_entry_buttons[mod_index]->set_selected(false);
        uint32_t extra_space = (mod_drag_target_index > mod_index) ? 1 : 0;
        mod_entry_spacers[mod_drag_target_index + extra_space]->set_target_height(0.0f, false);
        mod_entry_spacers[mod_drag_target_index + extra_space]->set_active(false);
        mod_entry_floating_view->set_display(Display::None);

        // Re-order the mods and update all the details on the menu.
        recomp::mods::set_mod_index(game_mod_id, mod_details[mod_index].mod_id, mod_drag_target_index);
        mod_details = recomp::mods::get_all_mod_details(game_mod_id);
        for (size_t i = 0; i < mod_entry_buttons.size(); i++) {
            mod_entry_buttons[i]->set_mod_details(mod_details[i]);
            mod_entry_buttons[i]->set_mod_thumbnail(generate_thumbnail_src_for_mod(mod_details[i].mod_id));
            mod_entry_buttons[i]->set_mod_enabled(is_mod_enabled_or_auto(mod_details[i].mod_id));
        }

        mod_selected(mod_drag_target_index);
        if (mod_drag_target_index < mod_entry_buttons.size() - 1) {
            mod_entry_buttons[mod_drag_target_index]->scroll_into_view(true);
        } else {
            // Make sure if placed last it will be visible after the drag ends.
            mod_entry_spacers[mod_entry_spacers.size() - 1]->scroll_into_view(true);
        }
        mod_entry_spacers[mod_entry_spacers.size() - 1]->set_target_height(0, false);

        break;
    }
    default:
        break;
    }
}

bool ModMenu::handle_special_config_options(const recomp::config::ConfigOption& option, const recomp::config::ConfigValueVariant& config_value) {
    if (recompui::renderer::is_texture_pack_enable_config_option(option, true)) {
        if (option.type == recomp::config::ConfigOptionType::Enum) {
            if (std::holds_alternative<uint32_t>(config_value)) {
                mod_hd_textures_enabled_changed(std::get<uint32_t>(config_value));
            }
        }
        else if (option.type == recomp::config::ConfigOptionType::Bool) {
            if (std::holds_alternative<bool>(config_value)) {
                mod_hd_textures_enabled_changed(std::get<bool>(config_value) ? 1 : 0);
            }
        }
        return true;
    }

    return false;
}

void ModMenu::mod_configure_requested() {
    if (active_mod_index >= 0) {
        // Record the context that was open when this function was called and close it.
        ContextId prev_context = recompui::get_current_context();
        prev_context.close();

        ContextId modal_context = mod_config_modal->modal_root_context;
        modal_context.open();

        mod_config_modal->set_on_close_callback([this]() {
            auto mod_config = recomp::mods::get_mod_config(this->mod_details[this->active_mod_index].mod_id);
            mod_config->save_config();
            mod_menu->get_mod_configure_button()->focus();

            auto schema = mod_config->get_config_schema();
            for (const auto &option : schema.options) {
                if (handle_special_config_options(option, mod_config->get_option_value(option.id))) {
                    break;
                }
            }
        });

        auto config_header = mod_config_modal->get_header();
        auto header_left = config_header->get_left();
        header_left->set_padding(16.0f);
        header_left->set_padding_left(20.0f);
        header_left->set_gap(24.0f);
        header_left->set_flex_grow(1.0f);
        header_left->set_flex_shrink(1.0f);
        header_left->set_flex_basis(100.0f, Unit::Percent);
        header_left->clear_children();
        auto back_button = modal_context.create_element<Button>(
            header_left,
            "Back",
            ButtonStyle::Secondary,
            ButtonSize::Medium
        );
        back_button->add_pressed_callback([]() {
            mod_config_modal->close();
        });

        mod_config_modal->set_menu_action_callback(MenuAction::Back, [back_button]() {
            ContextId modal_context = mod_config_modal->modal_root_context;
            if (modal_context.get_focused_element() == static_cast<Element*>(back_button)) {
                // If the back button is already focused, just close the modal.
                mod_config_modal->close();
            } else {
                back_button->focus();
            }
        });

        // Title
        modal_context.create_element<Label>(
            header_left,
            mod_details[active_mod_index].display_name,
            theme::Typography::Header3
        );

        auto body = mod_config_modal->get_body();
        body->clear_children();

        auto mod_config = modal_context.create_element<ConfigPageOptionsMenu>(
            body,
            recomp::mods::get_mod_config(mod_details[active_mod_index].mod_id),
            false
        );


        modal_context.close();
        // Needed, unsure why. Might be due to the button press event needing to finish.
        prev_context.open();
        mod_config_modal->open();
        back_button->focus();
    }
}

void ModMenu::mod_enum_option_changed(const std::string &id, uint32_t value) {
    if (active_mod_index >= 0) {
        recomp::mods::set_mod_config_value(mod_details[active_mod_index].mod_id, id, value);
    }
}

void ModMenu::mod_string_option_changed(const std::string &id, const std::string &value) {
    if (active_mod_index >= 0) {
        recomp::mods::set_mod_config_value(mod_details[active_mod_index].mod_id, id, value);
    }
}

void ModMenu::mod_number_option_changed(const std::string &id, double value) {
    if (active_mod_index >= 0) {
        recomp::mods::set_mod_config_value(mod_details[active_mod_index].mod_id, id, value);
    }
}

void ModMenu::mod_hd_textures_enabled_changed(uint32_t value) {
    if (active_mod_index >= 0) {
        if (value) {
            recompui::renderer::secondary_enable_texture_pack(mod_details[active_mod_index].mod_id);
        }
        else {
            recompui::renderer::secondary_disable_texture_pack(mod_details[active_mod_index].mod_id);
        }
    }
}

void ModMenu::create_mod_list() {
    ContextId context = get_current_context();
    
    // Clear the contents of the list scroll.
    list_scroll_container->clear_children();
    mod_entry_buttons.clear();
    mod_entry_spacers.clear();

    // Create the child elements for the list scroll.
    for (size_t mod_index = 0; mod_index < mod_details.size(); mod_index++) {
        const std::vector<char> &thumbnail = recomp::mods::get_mod_thumbnail(mod_details[mod_index].mod_id);
        std::string thumbnail_name = generate_thumbnail_src_for_mod(mod_details[mod_index].mod_id);
        if (!thumbnail.empty()) {
            recompui::queue_image_from_bytes_file(thumbnail_name, thumbnail);
            loaded_thumbnails.emplace(thumbnail_name);
        }

        ModEntrySpacer *spacer = context.create_element<ModEntrySpacer>(list_scroll_container);
        mod_entry_spacers.emplace_back(spacer);

        ModEntryButton *mod_entry = context.create_element<ModEntryButton>(list_scroll_container, mod_index);
        mod_entry->set_mod_selected_callback([this](uint32_t mod_index){ mod_selected(mod_index); });
        mod_entry->set_mod_drag_callback([this](uint32_t mod_index, recompui::EventDrag drag){ mod_dragged(mod_index, drag); });
        mod_entry->set_mod_details(mod_details[mod_index]);
        mod_entry->set_mod_thumbnail(thumbnail_name);
        mod_entry->set_mod_enabled(is_mod_enabled_or_auto(mod_details[mod_index].mod_id));
        mod_entry_buttons.emplace_back(mod_entry);
    }

    // Add two extra spacers at the bottom.
    ModEntrySpacer *spacer = context.create_element<ModEntrySpacer>(list_scroll_container);
    mod_entry_spacers.emplace_back(spacer);
    ModEntrySpacer *spacer2 = context.create_element<ModEntrySpacer>(list_scroll_container);
    mod_entry_spacers.emplace_back(spacer2);

    mod_entry_middles.resize(mod_entry_buttons.size());

    bool mods_available = !mod_details.empty();
    body_container->set_display(mods_available ? Display::Flex : Display::None);
    body_empty_container->set_display(mods_available ? Display::None : Display::Flex);
    if (mods_available) {
        mod_selected(0);
    }
}

void ModMenu::process_event(const Event &e) {
    if (e.type == EventType::Update) {
        if (mods_dirty) {
            refresh_mods(mod_scan_queued);
            mods_dirty = false;
            mod_scan_queued = false;
        }
        if (ultramodern::is_game_started()) {
            install_mods_button->set_enabled(false);
            refresh_button->set_enabled(false);
        }
        if (active_mod_index != -1) {        
            bool auto_enabled = recomp::mods::is_mod_auto_enabled(mod_details[active_mod_index].mod_id);
            bool deprecated = recomp::mods::is_mod_deprecated(mod_details[active_mod_index].mod_id, mod_details[active_mod_index].version);
            bool toggle_enabled = !auto_enabled && !deprecated && (mod_details[active_mod_index].runtime_toggleable || !ultramodern::is_game_started());
            if (!toggle_enabled) {
                mod_details_panel->disable_toggle();
            }
        }
    }
}

ModMenu::ModMenu(ResourceId rid, Element *parent) : Element(rid, parent) {
    if (current_game_mod_id.empty()) {
        throw std::runtime_error("ModMenu created before game mod ID was set. call update_game_mod_id() first.");
    }

    game_mod_id = current_game_mod_id;
    mod_menu = this;

    ContextId context = get_current_context();

    set_display(Display::Flex);
    set_position(Position::Relative);
    set_flex(1.0f, 1.0f, 100.0f);
    set_flex_direction(FlexDirection::Column);
    set_align_items(AlignItems::Center);
    set_justify_content(JustifyContent::FlexStart);
    set_width(100.0f, Unit::Percent);
    set_height(100.0f, Unit::Percent);
    
    {
        body_container = context.create_element<Container>(this, FlexDirection::Row, JustifyContent::FlexStart);
        body_container->set_as_navigation_container(NavigationType::Horizontal);
        body_container->set_flex(1.0f, 1.0f, 100.0f);
        body_container->set_width(100.0f, Unit::Percent);
        body_container->set_height(100.0f, Unit::Percent);
        {
            list_container = context.create_element<Container>(body_container, FlexDirection::Column, JustifyContent::Center);
            list_container->set_as_navigation_container(NavigationType::Vertical);
            list_container->set_as_primary_focus(true);
            list_container->set_display(Display::Block);
            list_container->set_flex_basis(100.0f);
            list_container->set_align_items(AlignItems::Center);
            list_container->set_height(100.0f, Unit::Percent);
            list_container->set_background_color(theme::color::BGShadow);
            list_container->set_border_bottom_left_radius(16.0f);
            {
                list_scroll_container = context.create_element<ScrollContainer>(list_container, ScrollDirection::Vertical);
            } // list_container

            mod_details_panel = context.create_element<ModDetailsPanel>(body_container);
            mod_details_panel->set_mod_toggled_callback([this](bool enabled){ mod_toggled(enabled); });
            mod_details_panel->set_mod_configure_pressed_callback([this](){ mod_configure_requested(); });
        } // body_container
        
        body_empty_container = context.create_element<Container>(this, FlexDirection::Column, JustifyContent::SpaceBetween);
        body_empty_container->set_flex(1.0f, 1.0f, 100.0f);
        body_empty_container->set_display(Display::None);
        {
            context.create_element<Element>(body_empty_container);
            context.create_element<Label>(body_empty_container, "You have no mods. Go get some!", LabelStyle::Large);
            context.create_element<Element>(body_empty_container);
        } // body_empty_container

        footer_container = context.create_element<Container>(this, FlexDirection::Row, JustifyContent::FlexStart);
        footer_container->set_as_navigation_container(NavigationType::Horizontal);
        footer_container->set_width(100.0f, recompui::Unit::Percent);
        footer_container->set_align_items(recompui::AlignItems::Center);
        footer_container->set_background_color(theme::color::BGShadow);
        footer_container->set_border_top_width(theme::border::width);
        footer_container->set_border_top_color(theme::color::BorderSoft);
        footer_container->set_padding(20.0f);
        footer_container->set_gap(20.0f);
        footer_container->set_border_bottom_left_radius(16.0f);
        footer_container->set_border_bottom_right_radius(16.0f);
        {
            Button* configure_button = mod_details_panel->get_configure_button();
            install_mods_button = context.create_element<Button>(footer_container, "Install Mods", recompui::ButtonStyle::Primary);
            install_mods_button->add_pressed_callback([this](){ open_install_dialog(); });

            Element* footer_spacer = context.create_element<Element>(footer_container);
            footer_spacer->set_flex(1.0f, 0.0f);

            refresh_button = context.create_element<IconButton>(footer_container, "icons/Reset.svg", recompui::ButtonStyle::Secondary, recompui::IconButtonSize::XLarge);
            refresh_button->add_pressed_callback([this](){ refresh_mods(true); });

            mods_folder_button = context.create_element<Button>(footer_container, "Open Mods Folder", recompui::ButtonStyle::Tertiary);
            mods_folder_button->add_pressed_callback([this](){ open_mods_folder(); });
        } // footer_container
    } // this
    
    mod_entry_floating_view = context.create_element<ModEntryView>(this);
    mod_entry_floating_view->set_display(Display::None);
    mod_entry_floating_view->set_position(Position::Absolute);
    mod_entry_floating_view->set_selected(true);

    context.close();
    create_mod_config_modal();
    context.open();
    
    refresh_mods(false);
}

ModMenu::~ModMenu() {
    mod_menu = nullptr;
}


void update_mod_list(bool scan_mods) {
    if (mod_menu) {
        recompui::ContextId ui_context = recompui::config::get_config_context_id();
        bool opened = ui_context.open_if_not_already();

        mod_menu->set_mods_dirty(scan_mods);
        mod_menu->queue_update();

        if (opened) {
            ui_context.close();
        }
    }
}

void update_game_mod_id(const std::string &game_mod_id) {
    current_game_mod_id = game_mod_id;
}

const std::string &get_game_mod_id() {
    return current_game_mod_id;
}

void process_game_started() {
    if (mod_menu) {
        recompui::ContextId ui_context = recompui::config::get_config_context_id();
        bool opened = ui_context.open_if_not_already();

        mod_menu->queue_update();

        if (opened) {
            ui_context.close();
        }
    }
}

void focus_mod_configure_button() {
    Element* configure_button = mod_menu->get_mod_configure_button();
    if (configure_button) {
        configure_button->focus();
    }
}

} // namespace recompui
