#include "wr64_ghost_ui.hpp"
#ifdef WR64_ENABLE_FRONTEND
#include "wr64_ghost.hpp"
#include "wr64_ghost_native.h"
#include "recompui/config.h"
#include "recompui/recompui.h"
#include "elements/ui_button.h"
#include "elements/ui_config_page.h"
#include "elements/ui_container.h"
#include "elements/ui_label.h"
#include <array>
#include <cstdio>
#include <string>

namespace wr64::ghost {
namespace {
using namespace recompui;

std::string describe(const SlotInfo& info) {
    if (!info.available) return "Empty";
    constexpr std::array courses = {"Dolphin Park", "Sunny Beach", "Sunset Bay",
        "Marine Fortress", "Drake Lake", "Port Blue", "Twilight City",
        "Southern Island", "Glacier Coast"};
    const char* course = info.course.index >= 0 && info.course.index < int(courses.size())
        ? courses[info.course.index] : "Unknown course";
    constexpr std::array levels = {"Normal", "Hard", "Expert"};
    const char* level = info.course.difficulty >= 0 && info.course.difficulty < int(levels.size())
        ? levels[info.course.difficulty] : "Unknown difficulty";
    char time[40];
    std::snprintf(time, sizeof(time), "%u:%02u.%03u", info.finish_ms / 60000,
        (info.finish_ms / 1000) % 60, info.finish_ms % 1000);
    return std::string(course) + " / " + level + (info.course.reverse ? " (Reverse)" : "") + " - " + time;
}

class GhostPage final : public ConfigPage {
    Label* current = nullptr;
    Label* feedback = nullptr;
    std::array<Label*, 2> slot_labels{};
    std::array<Button*, 2> save_buttons{};
    std::array<Button*, 2> load_buttons{};
    std::string last_description;
    std::array<std::string, 2> last_slot_descriptions{};
    bool storage_ready = false;

    void refresh() {
        // The start request precedes init_saving. Wait for a native callback
        // after actual runtime initialization, so Store cannot cache a load
        // attempted against an empty pre-game save basename.
        if (!storage_ready && wr64_ghost_native_storage_ready()) {
            const auto result = refresh_slots();
            storage_ready = true;
            if (result != Result::Ok) feedback->set_text(result_message(result));
        }
        const auto state = status();
        std::string description;
        if (state.recording_invalid) description = "This run cannot produce a valid ghost.";
        else if (state.recording_full) description = "Recording reached the ghost time limit.";
        else if (state.recording) description = "Recording this Time Trial run.";
        else description = "Complete a Time Trial race to record a ghost.";
        if (state.best.available) description += "\nBest run: " + describe(state.best);
        if (state.playback_active) description += "\nA ghost is racing this run.";
        if (state.autosave_result == Result::CorruptData)
            description += "\nAutomatic ghost data could not be read. Existing files were preserved.";
        else if (state.autosave_result != Result::Ok)
            description += "\nAutomatic ghost saving is unavailable. This session's best remains available on Retry.";
        // Avoid rebuilding identical text on every UI update.
        if (description != last_description) {
            current->set_text(description);
            last_description = description;
        }
        for (int slot = 0; slot < 2; ++slot) {
            const auto description = "Slot " + std::to_string(slot + 1) + ": " + describe(state.slots[slot]);
            if (description != last_slot_descriptions[slot]) {
                slot_labels[slot]->set_text(description);
                last_slot_descriptions[slot] = description;
            }
            save_buttons[slot]->set_enabled(state.can_save);
            load_buttons[slot]->set_enabled(state.slots[slot].available);
        }
    }

    void save(int slot) {
        auto action = [this, slot] {
            const auto result = save_slot(slot, true);
            feedback->set_text(result == Result::Ok ? "Ghost saved in slot " + std::to_string(slot + 1) + "." : result_message(result));
            refresh();
        };
        const auto state = status();
        if (state.slots[slot].available) {
            open_choice_prompt("Replace saved ghost?", describe(state.slots[slot]),
                "Replace", "Cancel", action, [] {}, ButtonStyle::Warning, ButtonStyle::Secondary, true);
        } else action();
    }

    void process_event(const Event& event) override {
        if (event.type == EventType::Update) { refresh(); queue_update(); }
    }
    std::string_view get_type_name() override { return "Wr64GhostPage"; }

public:
    GhostPage(ResourceId id, Element* parent) : ConfigPage(id, parent, Events(EventType::Update)) {
        auto context = get_current_context();
        // Both ghost panels use the theme's light paper surfaces.
        body->set_color(theme::color::Text);
        auto left = body->get_left();
        left->set_display(Display::Flex);
        left->set_flex_direction(FlexDirection::Column);
        left->set_gap(16);
        left->set_as_navigation_container(NavigationType::Vertical);
        current = context.create_element<Label>(left, "", LabelStyle::Normal);
        for (int slot = 0; slot < 2; ++slot) {
            slot_labels[slot] = context.create_element<Label>(left, "", LabelStyle::Normal);
            auto row = context.create_element<Container>(left, FlexDirection::Row, JustifyContent::FlexStart);
            row->set_gap(12);
            row->set_as_navigation_container(NavigationType::Horizontal);
            save_buttons[slot] = context.create_element<Button>(row, "Save best run", ButtonStyle::Primary, ButtonSize::Large);
            save_buttons[slot]->set_width(360);
            save_buttons[slot]->set_flex_shrink(0);
            save_buttons[slot]->add_pressed_callback([this, slot] { save(slot); });
            load_buttons[slot] = context.create_element<Button>(row, "Race this ghost", ButtonStyle::Secondary, ButtonSize::Large);
            load_buttons[slot]->set_width(360);
            load_buttons[slot]->set_flex_shrink(0);
            load_buttons[slot]->add_pressed_callback([this, slot] {
                const auto result = load_slot(slot);
                feedback->set_text(result == Result::Ok
                    ? "Ghost selected. Start or retry its matching Time Trial course."
                    : result_message(result));
                refresh();
            });
        }
        feedback = context.create_element<Label>(left, "", LabelStyle::Small);
        context.create_element<Label>(body->get_right(),
            "Your fastest completed ghost is saved automatically for each course, difficulty and direction. It returns when you race that course, including after restarting the game.\n\n"
            "These two optional slots let you keep extra ghosts or choose a different opponent for your next run.\n\n"
            "Show Time Trial ghost in General controls its visibility. N64 L also toggles a loaded ghost during a race.", LabelStyle::Normal);
        refresh();
        queue_update();
    }
};
}

void create_ui_tab() {
    recompui::config::create_tab("Time Trial Ghosts", "time_trial_ghosts",
        [](recompui::ContextId context, recompui::Element* parent) {
            context.create_element<GhostPage>(parent);
        });
}
}
#else
namespace wr64::ghost { void create_ui_tab() {} }
#endif
