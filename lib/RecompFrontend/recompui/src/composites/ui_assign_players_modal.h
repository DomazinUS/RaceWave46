#pragma once

#include "recompinput/recompinput.h"
#include "elements/ui_element.h"
#include "elements/ui_document.h"
#include "elements/ui_svg.h"
#include "elements/ui_button.h"
#include "ui_player_card.h"

namespace recompui {

class AssignPlayersModal : public Element {
protected:
    bool is_open = false;
    bool was_assigning = false;
    Element* modal_overlay = nullptr;
    Element* player_elements_wrapper = nullptr;
    Element* fake_focus_button = nullptr;
    std::vector<PlayerCard*> player_elements = {};

    Button* keep_players_button = nullptr;
    Button* retry_button = nullptr;
    Button* confirm_button = nullptr;

    virtual void process_event(const Event &e) override;
    std::string_view get_type_name() override { return "AssignPlayersModal"; }
private:
    void init_pending_state();
    void create_player_elements();
    void set_fake_focus_enabled(bool enabled);
    void lock_focus(bool lock);
public:
    AssignPlayersModal(ResourceId rid, Document *parent);
    virtual ~AssignPlayersModal();
    static void init();
    // Pass false to force player assignment.
    static void open();
    static void close();
};

} // namespace recompui
