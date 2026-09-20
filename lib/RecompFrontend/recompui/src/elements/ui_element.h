#pragma once

#include "ui_style.h"
#include "../core/ui_context.h"

#include "recomp.h"
#include <ultramodern/ultra64.h>

#include <unordered_set>
#include <variant>

namespace recompui {
class Document;

struct UICallback {
    ContextId context;
    PTR(void) callback;
    PTR(void) userdata;
};

using ElementValue = std::variant<uint32_t, float, double, std::monostate>;

// Defines how navigation works within the focusable children of an element, or between navigation containers.
// This makes controller/arrow navigation a lot more intuitive and reliable than guessing.
enum class NavigationType {
    None,
    // Navigating automatically based on distance and input direction.
    // It is almost always better to specify a direction.
    Auto,
    // Children are arranged in a vertical list.
    Vertical,
    // Children are arranged in a horizontal list.
    Horizontal,

    // The next two types are for grid layouts.
    // They behave like the base direction but preserve the index when navigating across the other axis.
    // For example, you can set the wrapper element around rows to GridCol, and each row to GridRow,
    // and the focusable elements within each row will keep their column index when navigating up/down.

    // Grid navigation: Vertical grouping of elements
    GridCol,
    // Grid navigation: Horizontal grouping of elements
    GridRow
};

class ContextId;
class RecompNav;

class Element : public Style, public Rml::EventListener {
    friend ContextId create_context(const std::filesystem::path& path);
    friend ContextId create_context();
    friend class ContextId; // To allow ContextId to call the handle_event method directly.
    friend class Document; // For navigation needs access to more properties than other elements should be able to.
    friend class RecompNav; // Same as above.
private:
    Rml::Element *base = nullptr;
    Rml::ElementPtr base_owning = {};
    uint32_t events_enabled = 0;
    std::vector<Style *> styles;
    std::vector<uint32_t> styles_counter;
    std::unordered_set<std::string_view> style_active_set;
    std::unordered_multimap<std::string_view, uint32_t> style_name_index_map;
    std::vector<UICallback> callbacks;
    Element *parent = nullptr;
    std::vector<Element *> children;
    std::string id;
    std::string debug_id = "";
    bool shim = false;
    bool enabled = true;
    bool disabled_attribute = false;
    bool disabled_from_parent = false;
    bool can_set_text = false;

    bool is_nav_container = false;
    bool is_nav_wrapping = false;
    NavigationType nav_type = NavigationType::Auto;
    bool is_primary_focus = false;

    std::vector<Element *> nav_children;

    void add_child(Element *child);
    void register_event_listeners(uint32_t events_enabled);
    void apply_style(Style *style);
    void propagate_disabled(bool disabled);
    void handle_event(const Event &e);
    void set_id(const std::string& new_id);
    void set_as_root_document(NavigationType nav_type = NavigationType::Vertical);

    // Style overrides.
    virtual void set_property(Rml::PropertyId property_id, const Rml::Property &property) override;

    // Handled by Document
    virtual bool handle_navigation_event(Rml::Event &event) { return false; };

    // Rml::EventListener overrides.
    void ProcessEvent(Rml::Event &event) override final;

    Element *get_nav_parent();
    void get_all_focusable_children(Element *nav_parent);
    void build_navigation(Element *nav_parent, Element *cur_focus_element);
protected:
    // Use of this method in inherited classes is discouraged unless it's necessary.
    void set_attribute(const Rml::String &attribute_key, const Rml::String &attribute_value);
    void remove_property(Rml::PropertyId property_id) override;
    virtual void process_event(const Event &e);
    virtual ElementValue get_element_value() { return std::monostate{}; }
    virtual void set_input_value(const ElementValue&) {}
    virtual std::string_view get_type_name() { return "Element"; }
public:
    // Used for backwards compatibility with legacy UI elements.
    Element(ResourceId rid, Rml::Element *base);

    // Used to actually construct elements.
    Element(ResourceId rid, Element* parent, uint32_t events_enabled = 0, Rml::String base_class = "div", bool can_set_text = false);
    virtual ~Element();
    void clear_children();
    bool remove_child(ResourceId child, bool remove_from_context = true);
    bool remove_child(Element *child, bool remove_from_context = true) { return remove_child(child->get_resource_id(), remove_from_context); }
    void set_parent(Element *new_parent);
    Element *get_parent() const { return parent; }
    void add_style(Style *style, std::string_view style_name);
    void add_style(Style *style, const std::initializer_list<std::string_view> &style_names);
    Element get_element_with_tag_name(std::string_view tag_name);
    void set_enabled(bool enabled);
    bool is_enabled() const;
    virtual void set_text(std::string_view text);
    // Only use if you can ensure text is directly from a trusted source. Sets inner rml contents which can create new elements.
    void set_text_unsafe(std::string_view text);
    std::string get_input_text();
    void set_input_text(std::string_view text);
    void set_src(std::string_view src);
    void set_style_enabled(std::string_view style_name, bool enabled);
    bool is_style_enabled(std::string_view style_name);
    void apply_styles();
    bool is_element() override { return true; }
    float get_absolute_left();
    float get_absolute_top();
    // Left relative to offset parent.
    float get_offset_left();
    // Top relative to offset parent.
    float get_offset_top();
    float get_scroll_left();
    float get_scroll_top();
    float get_client_left();
    float get_client_top();
    float get_client_width();
    float get_client_height();
    float get_dp_to_pixel_ratio();
    void enable_focus();
    bool focus();
    void blur();
    void queue_update();
    void register_callback(ContextId context, PTR(void) callback, PTR(void) userdata);
    uint32_t get_input_value_u32();
    float get_input_value_float();
    double get_input_value_double();
    void set_input_value_u32(uint32_t val) { set_input_value(val); }
    void set_input_value_float(float val) { set_input_value(val); }
    void set_input_value_double(double val) { set_input_value(val); }
    const std::string& get_id() { return id; }
    bool is_pseudo_class_set(Rml::String pseudo_class);
    void scroll_into_view(bool smooth = false);

    void set_debug_id(const std::string& new_debug_id) { debug_id = new_debug_id; }
    const std::string& get_debug_id() const { return debug_id; }
    const std::string& get_debug_id_or_id() const { return debug_id.empty() ? id : debug_id; }

    // Marks an element as a container around navigatable elements.
    // It tells the navigation system how directional input should be handled within this element's focusable children.
    void set_as_navigation_container(NavigationType nav_type);
    // Sets if the navigation container should wrap when reaching the end of its children.
    void set_nav_wrapping(bool wrapping);
    // Within a group of navigatable elements, if the parent is navigated to, this one will be prioritized.
    // Note: Going across the same nav types (like from one Horizontal to another) will override this.
    // This is more used to decide which element to focus on when any element could be picked,
    // like vertically navigating to the selected tab in a tab list.
    void set_as_primary_focus(bool is_primary_focus = true);

    Element *select_add_option(std::string_view text, std::string_view value);
    void select_set_selection(std::string_view option_value);

    std::vector<Element *> *get_nav_children() { return &nav_children; }

    enum class CanFocus { No, Yes, NoAndNoChildren };
    CanFocus is_focusable();
};

void queue_ui_callback(recompui::ResourceId resource, const Event& e, const UICallback& callback);

} // namespace recompui
