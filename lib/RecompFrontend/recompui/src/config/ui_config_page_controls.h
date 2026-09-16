#pragma once
#include <functional>

#include "elements/ui_config_page.h"
#include "recompinput/recompinput.h"
#include "recompinput/input_binding.h"
#include "elements/ui_button.h"
#include "elements/ui_label.h"
#include "elements/ui_icon_button.h"
#include "elements/ui_binding_button.h"
#include "elements/ui_pill_button.h"
#include "elements/ui_toggle.h"
#include "elements/ui_modal.h"
#include "composites/ui_player_card.h"

namespace recompui {

struct GameInputContext {
    std::string name;
    std::string description;
    recompinput::GameInput input_id;
    bool clearable;
};

struct GameInputSection {
    std::string name;
    std::vector<GameInputContext> contexts = {};
    GameInputSection(const std::string &name) : name(name) {}
};

using BindingList = std::vector<recompinput::InputField>;
// Receives which GameInput to be bound to, and the index of the binding that was clicked
using on_bind_click_callback = std::function<void(recompinput::GameInput, int)>;
// Player index, GameInput to be bound to, and the index of the binding that is being assigned
using on_player_bind_callback = std::function<void(int, recompinput::GameInput, int)>;

using on_clear_or_reset_callback = std::function<void(recompinput::GameInput, bool)>;

// One single row of a game input mapping
class GameInputRow : public Element {
protected:
    recompinput::GameInput input_id;
    BindingList bindings;
    Element *scroll_buffer = nullptr;

    int active_binding_index = -1;
    bool is_binding = false;

    std::vector<BindingButton*> binding_buttons = {};

    Style active_style;
    std::function<void()> on_active_callback;

    virtual void process_event(const Event &e) override;
    std::string_view get_type_name() override { return "GameInputRow"; }
public:
    GameInputRow(
        ResourceId rid,
        Element *parent,
        const GameInputContext &input_ctx,
        std::function<void()> on_active_callback,
        on_bind_click_callback on_bind_click,
        on_clear_or_reset_callback on_clear_or_reset
    );
    virtual ~GameInputRow();
    void update_bindings(BindingList &new_bindings);
    recompinput::GameInput get_input_id() const { return input_id; }
    void focus_on_first_binding();
    static constexpr float left_padding = 20.0f;
};

class GameInputRowsWrapper : public Element {
protected:
    std::string_view get_type_name() override { return "GameInputRowsWrapper"; }
public:
    bool is_menu;
    GameInputRowsWrapper(ResourceId rid, Element *parent, const std::string &name, bool is_menu = false) : Element(rid, parent, 0, "div", false), is_menu(is_menu) {
        set_display(Display::Block);
        if (!name.empty()) {
            auto context = get_current_context();
            Label *section_label = context.create_element<Label>(this, name, theme::Typography::LabelSM);
            section_label->set_margin_top(24.0f);
            section_label->set_margin_left(GameInputRow::left_padding);
            section_label->set_margin_bottom(8.0f);
            section_label->set_color(theme::color::PrimaryL);
        }
    }
};

using PlayerBindings = std::map<recompinput::GameInput, BindingList>;

class ConfigPageControls : public ConfigPage {
protected:
    // for tracking forced updates to entire page (major changes like player reassignment or singleplayer mode)
    int last_update_index = 0;
    int update_index = 0;

    int selected_player = 0;
    int selected_profile_index = -1;
    size_t max_num_players;

    bool multiplayer_enabled;
    bool multiplayer_view_mappings;

    bool single_player_show_keyboard_mappings = false;

    bool awaiting_binding = false;
    bool awaiting_binding_for_menu_action_button = false;

    bool queue_first_game_input_row_focus = false;
    bool queue_selected_player_profile_edit_focus = false;

    struct {
        GameInputSection n64 = GameInputSection("");
        GameInputSection menu = GameInputSection("Menu Inputs");
        std::vector<GameInputSection> other;

        std::vector<GameInputSection *> get_all_sections() {
            std::vector<GameInputSection *> all_sections = {
                &n64,
                &menu
            };
            for (auto &section : other) {
                all_sections.push_back(&section);
            }
            return all_sections;
        }

        std::vector<GameInputContext *> get_all_contexts() {
            std::vector<GameInputContext *> all_contexts;
            for (auto *section : get_all_sections()) {
                for (auto &ctx : section->contexts) {
                    all_contexts.push_back(&ctx);
                }
            }
            return all_contexts;
        }

        GameInputContext *get_context_by_input_id(recompinput::GameInput input_id) {
            for (auto *section : get_all_sections()) {
                for (auto &ctx : section->contexts) {
                    if (ctx.input_id == input_id) {
                        return &ctx;
                    }
                }
            }
            return nullptr;
        }
    } game_input_sections;

    std::vector<PlayerCard*> player_cards;
    std::vector<GameInputRowsWrapper*> rows_wrappers;
    std::vector<GameInputRow*> game_input_rows;
    IconToggle *keyboard_toggle;
    Element *description_container = nullptr;
    Element *controller_board = nullptr;
    Label *controller_board_caption = nullptr;
    std::map<recompinput::GameInput, Element*> visual_input_nodes;
    std::map<recompinput::GameInput, Label*> visual_binding_labels;
    on_player_bind_callback on_player_bind;
    Element *nav_up_element = nullptr;
    Element *first_nav_element = nullptr;

    struct {
        struct {
            Label *profile_name_label = nullptr;
            std::string current_profile_name = "";
        } left;

        struct {
            Button *go_back_button = nullptr;
            Button *assign_players_button = nullptr;
        } right;
    } header_elements;

    virtual void process_event(const Event &e) override;
    std::string_view get_type_name() override { return "ConfigPageControls"; }
private:
    void on_option_hover(recompinput::GameInput index);
    void on_bind_click(recompinput::GameInput game_input, int input_index);
    void on_clear_or_reset_game_input(
        recompinput::GameInput game_input,
        bool reset = false
    );

    void on_select_player_profile(int player_index, int profile_index);
    void on_edit_player_profile(int player_index);

    void create_game_input_contexts();

    void set_current_profile_index();

    void render_all();

    void render_header();
    void render_body();
    void render_body_players();
    void render_body_mappings();
    void render_control_mappings();
    void render_controller_board();
    void update_controller_board(const PlayerBindings &bindings);
    void render_footer();

    bool should_show_mappings();

    recompinput::InputDevice get_player_input_device();
public:
    ConfigPageControls(ResourceId rid, Element *parent);
    virtual ~ConfigPageControls();
    
    void force_update();

    void update_control_mappings();
    void set_selected_player(int player);
};

extern ConfigPageControls *controls_page;

// Optional host routing for games which change player count at runtime.
void set_player_assignment_callback(std::function<void()> callback,
                                   std::function<uint32_t()> requested_players);

} // namespace recompui
