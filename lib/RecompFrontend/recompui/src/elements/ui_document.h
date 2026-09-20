#pragma once
#include "core/ui_context.h"
#include "elements/ui_element.h"

namespace recompui {
    class Element;
    class ContextId;

    class Document : public Element {
    friend class ContextId;
    protected:
        std::string_view get_type_name() override { return "Document"; }
        void process_event(const Event &e) override;
    public:
        Document(ResourceId rid, Rml::Element *base);
        // Signifies that a new element has gained focus, and the document should update it.
        // The currently focused element is not obtainable until the end of focus event processing,
        // so this queues an update to check what is currently in focus.
        void report_focused_element();
        void report_hovered_element(Element* element);
        void report_removed_element(Element* element);
        Element* get_last_focused_element() { return last_focused; }
        Element* get_last_focusable_hovered_element() { return last_focusable_hovered; }
    private:
        virtual bool handle_navigation_event(Rml::Event &event) override;
        Element *last_focused = nullptr;
        Element *last_focusable_hovered = nullptr;
        bool update_last_focused = false;
    };

} // namespace recompui
