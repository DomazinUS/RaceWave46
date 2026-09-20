#pragma once

#include "recompui/recompui.h"
#include "elements/ui_element.h"
#include "elements/ui_label.h"
#include "base/ui_launcher_common.h"

namespace recompui {
    class GameOption : public Element {
    private:
        std::string title;
        std::function<void()> callback;
    protected:
        Label *label;
        void set_styles();
        std::string_view get_type_name() override { return "GameOption"; }
        virtual void process_event(const Event& e) override;
    public:
        GameOption(ResourceId rid, Element* parent, const std::string& title, std::function<void()> callback, GameOptionsMenuLayout layout);
        void set_title(const std::string& new_title);
        void set_callback(std::function<void()> new_callback);
        Label* get_label() { return label; }
        // These are public so you can modify them.
        Style hover_style;
        Style focus_style;
        Style disabled_style;
        Style hover_disabled_style;
    };
}
