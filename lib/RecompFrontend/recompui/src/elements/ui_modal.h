#pragma once

#include "recompui/recompui.h"
#include "elements/ui_element.h"
#include "elements/ui_document.h"
#include "elements/ui_config_page.h"
#include "elements/ui_tab_set.h"

#include "recompinput/recompinput.h"

namespace recompui {

    class Modal;

    enum class ModalType {
        Fullscreen,
        Prompt
    };

    enum class TabCloseContext {
        TabChange,
        ModalClose,
    };

    namespace tab_callbacks {
        using create_contents_t = std::function<void(recompui::ContextId context, Element* parent)>;
        using can_close_t = std::function<bool(TabCloseContext close_context)>;
        using on_close_t = std::function<void(TabCloseContext close_context)>;
    } 

    struct TabCallbacks {
        tab_callbacks::create_contents_t create_contents;
        tab_callbacks::can_close_t can_close = nullptr;
        tab_callbacks::on_close_t on_close = nullptr;
    };

    class TabContext {
    public:
        std::string name;
        const std::string id;
        TabContext(const std::string &name, const std::string &id, TabCallbacks &&callbacks) : name(name), id(id), callbacks(std::move(callbacks)) {};
        virtual ~TabContext() = default;

        void create_contents(recompui::ContextId context, Element* parent) {
            callbacks.create_contents(context, parent);
        }

        bool can_close(TabCloseContext close_context) { return callbacks.can_close ? callbacks.can_close(close_context) : true; }
        void on_close(TabCloseContext close_context) { if (callbacks.on_close) callbacks.on_close(close_context); }
    protected:
        TabCallbacks callbacks;
    };

    class TabbedModal;

    struct MenuActionCallback {
        std::function<void()> callback;
        std::string description;
    };

    class Modal : public Element {
        friend class TabbedModal;
    protected:
        bool is_open = false;
        Element *modal_element = nullptr;
        ConfigHeaderFooter *header = nullptr;
        Element *modal_overlay = nullptr;
        Element *body = nullptr;
        Element *menu_actions_wrapper = nullptr;
        ModalType modal_type;
        std::function<void()> on_close_callback;
        std::unordered_map<MenuAction, MenuActionCallback> menu_action_callbacks;

        recompinput::InputDevice last_input_device = recompinput::InputDevice::COUNT;
        int last_input_profile = -1;

        virtual void process_event(const Event &e) override;
        std::string_view get_type_name() override { return "Modal"; }

    public:
        recompui::ContextId modal_root_context;
        Modal(ResourceId rid, Document *parent, recompui::ContextId modal_root_context, ModalType modal_type);
        static Modal *create_modal(ModalType modal_type = ModalType::Fullscreen);
        virtual ~Modal();
        virtual void open();
        virtual bool close();
        bool is_open_now() const { return is_open; }

        ConfigHeaderFooter *get_header() { return header; }
        Element *get_body() { return body; }

        void set_on_close_callback(std::function<void()> callback);
        // Adds a callback for MenuAction events. Description is shown under the modal if provided.
        void set_menu_action_callback(MenuAction action, std::function<void()> callback, std::string description = "");
        void remove_menu_action_callback(MenuAction action);
        void render_menu_actions();
    };

    class TabbedModal : public Modal {
    protected:
        std::vector<TabContext> tab_contexts;
        TabSet *tabs = nullptr;
        int previous_tab_index = -1;
        int current_tab_index = -1;
        virtual void process_event(const Event &e) override;
        std::string_view get_type_name() override { return "TabbedModal"; }
        void on_tab_change(int tab_index);
        void navigate_tab_direction(int direction);
        void initialize_tab(TabContext &tab_context);
    public:
        virtual void open() override;
        virtual bool close() override;
        TabbedModal(ResourceId rid, Document *parent, recompui::ContextId modal_root_context, ModalType modal_type);
        static TabbedModal *create_modal(ModalType modal_type = ModalType::Fullscreen);
        void add_tab(TabContext &&tab_context);
        void add_tab(
            const std::string &name,
            const std::string &id,
            tab_callbacks::create_contents_t create_contents,
            tab_callbacks::can_close_t can_close = nullptr,
            tab_callbacks::on_close_t on_close = nullptr
        );
        void set_selected_tab(int tab_index);
        void set_selected_tab(const std::string &id);
        Element *get_active_tab() { return tabs != nullptr ? static_cast<Tab*>(tabs->get_active_tab_element()) : nullptr; }
        void set_tab_visible(const std::string &id, bool is_visible);
    };
} // namespace recompui
