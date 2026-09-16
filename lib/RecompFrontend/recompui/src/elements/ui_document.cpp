#include "elements/ui_document.h"
#include "recompui/recompui.h"

// This define shows debug output for the navigation process.
// Utilize Element->debug_id to set readable names for your elements.
// #define RECOMPUI_NAV_DEBUG

#ifdef RECOMPUI_NAV_DEBUG
#include <iostream>
#endif

// For debugging purposes. Each doc gets a unique number.
static int doc_counter = 0;

namespace recompui {
    // struct for helping with rml element position comparisons.
    // GetAbsoluteOffset has some overhead so calculating this once per element is ideal.
    struct RmlPosSize {
        Rml::Vector2f position;
        Rml::Vector2f bottom_right;
    
        RmlPosSize(Rml::Element *element) {
            position = element->GetAbsoluteOffset();
            bottom_right = position + element->GetBox().GetSize();
        }
    
        float get_distance_axis(const RmlPosSize& other, bool horizontal) const {
            if (horizontal) {
                float dx_1 = std::abs(position.x - other.bottom_right.x);
                float dx_2 = std::abs(bottom_right.x - other.position.x);
                return std::min(dx_1, dx_2);
            } else {
                float dy_1 = std::abs(position.y - other.bottom_right.y);
                float dy_2 = std::abs(bottom_right.y - other.position.y);
                return std::min(dy_1, dy_2);
            }
        }
    
        float get_distance(const RmlPosSize& other) const {
            return std::min(get_distance_axis(other, true), get_distance_axis(other, false));
        }
    
        bool can_navigate_to_using_direction(const RmlPosSize& other, NavDirection dir) const {
            switch (dir) {
                case NavDirection::Up:    return is_below(other);
                case NavDirection::Down:  return is_above(other);
                case NavDirection::Left:  return is_right_of(other);
                case NavDirection::Right: return is_left_of(other);
            }
            return false;
        }
    
        // The following 4 funcs return true if this element is completely on one side of the other, not overlapping.
        bool is_left_of(const RmlPosSize& other) const  { return bottom_right.x <= other.position.x; }
        bool is_right_of(const RmlPosSize& other) const { return position.x >= other.bottom_right.x; }
        bool is_above(const RmlPosSize& other) const    { return bottom_right.y <= other.position.y; }
        bool is_below(const RmlPosSize& other) const    { return position.y >= other.bottom_right.y; }
    };

    static NavigationType get_effective_nav_type(NavigationType nav_type) {
        switch (nav_type) {
            default:
            case NavigationType::Auto:
            case NavigationType::Horizontal:
            case NavigationType::Vertical:
                return nav_type;
            case NavigationType::GridRow:
                return NavigationType::Horizontal;
            case NavigationType::GridCol:
                return NavigationType::Vertical;
        }
    }

    static bool is_grid_nav_type(NavigationType nav_type) {
        return nav_type == NavigationType::GridCol || nav_type == NavigationType::GridRow;
    }

    // Compare two nav types, Grid types are considered equal to their base direction.
    static bool are_nav_types_equal(NavigationType nav_type1, NavigationType nav_type2) {
        return get_effective_nav_type(nav_type1) == get_effective_nav_type(nav_type2);
    }

    // Class that contains the context for performing navigation.
    class RecompNav {
    public:
        // Element that was focused before navigating.
        Element *original_focused_element = nullptr;
        // Navigation directional value: -1 for up/left, 1 for down/right.
        int nav_dir_value;
        // In this case, only used to represent whether navigating vertically or horizontally.
        NavigationType nav_dir_type;
        NavDirection nav_direction;

        RecompNav(Document *doc, int key_identifier) {
            switch (key_identifier) {
                case Rml::Input::KI_UP:    nav_dir_value = -1; nav_dir_type = NavigationType::Vertical;   nav_direction = NavDirection::Up;    break;
                case Rml::Input::KI_DOWN:  nav_dir_value =  1; nav_dir_type = NavigationType::Vertical;   nav_direction = NavDirection::Down;  break;
                case Rml::Input::KI_LEFT:  nav_dir_value = -1; nav_dir_type = NavigationType::Horizontal; nav_direction = NavDirection::Left;  break;
                case Rml::Input::KI_RIGHT: nav_dir_value =  1; nav_dir_type = NavigationType::Horizontal; nav_direction = NavDirection::Right; break;
            }
            auto ctx = get_current_context();
            original_focused_element = ctx.get_focused_element();
            // Reset and rebuild navigation tree.
            doc->nav_children.clear();
            doc->build_navigation(doc, original_focused_element);
        };

        #ifdef RECOMPUI_NAV_DEBUG
        // Prints an element's debug id (or id if not set) after indenting based on its depth in the navigation tree.
        void print_debug_id(Element *el, std::string indent_str = "- ") {
            std::string indent = "";
            Element *cur = el;
            while (cur != nullptr) {
                indent += indent_str;
                cur = cur->get_nav_parent();
            }
            std::string id = el->debug_id.empty() ? el->id : el->debug_id;
            std::cout << indent << id << "\n";
        }
        #endif

        static int get_element_index(Element *el, std::vector<Element *> elements) {
            for (int i = 0; i < static_cast<int>(elements.size()); i++) {
                if (el == elements[i]) {
                    return i;
                }
            }
            return -1;
        }

        static Element *try_get_element_at_index(int index, std::vector<Element *> &elements) {
            if (index < 0 || index >= static_cast<int>(elements.size())) {
                return nullptr;
            }
            return elements[index];
        }

        // Use nav_direction to filter elements that match that direction, then pick the closest.
        Element *get_element_in_nav_direction(Element *this_element, std::vector<Element *> &elements) {
            if (elements.empty()) {
                return nullptr;
            }

            // Should this be original_focused_element?
            RmlPosSize this_pos_size(this_element->base);

            // Alternative idea: compare distances/directions from the original focused element, instead of where we have unwrapped to.
            // RmlPosSize this_pos_size(original_focused_element->base);

            std::vector<std::pair<Element *, RmlPosSize>> elements_in_direction;
            for (auto &element : elements) {
                if (element == this_element) {
                    continue;
                }
                auto element_box = element->base->GetBox();
                RmlPosSize element_pos_size(element->base);
                if (this_pos_size.can_navigate_to_using_direction(element_pos_size, nav_direction)) {
                    elements_in_direction.emplace_back(element, element_pos_size);
                }
            }
            
            Element *closest = nullptr;
            float closest_distance = std::numeric_limits<float>::max();
            float closest_distance_other_axis = std::numeric_limits<float>::max();

            for (auto &[element, element_pos_size] : elements_in_direction) {
                float distance = this_pos_size.get_distance_axis(element_pos_size, nav_dir_type == NavigationType::Horizontal);
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest = element;
                    closest_distance_other_axis = this_pos_size.get_distance_axis(element_pos_size, nav_dir_type != NavigationType::Horizontal);
                } else if (distance == closest_distance) {
                    float other_axis_distance = this_pos_size.get_distance_axis(element_pos_size, nav_dir_type != NavigationType::Horizontal);
                    if (other_axis_distance < closest_distance_other_axis) {
                        closest_distance_other_axis = other_axis_distance;
                        closest_distance = distance;
                        closest = element;
                    }
                }
            }

            return closest;
        }

        // Try to navigate in the given direction, and if it isn't possible then try from the element's nav parent.
        Element *unwind_nav_in_direction(
            Element *this_element,
            int retained_grid_index = -1
        ) {
            #ifdef RECOMPUI_NAV_DEBUG
            print_debug_id(this_element, "↑ ");
            #endif

            Element *nav_parent = this_element->get_nav_parent();
            if (nav_parent == nullptr) {
                return this_element;
            }

            int cur_element_index = get_element_index(this_element, nav_parent->nav_children);
            if (cur_element_index == -1) {
                throw std::runtime_error("This should never ever ever happen. Element not found in its parent's nav children.");
            }

            // Process grid navigation if retained_grid_index is valid and grid navs are different.
            if (
                retained_grid_index >= 0 &&
                is_grid_nav_type(nav_parent->nav_type) &&
                is_grid_nav_type(this_element->nav_type) &&
                this_element->nav_type != nav_parent->nav_type
            ) {
                // Note: This does not handle wrapping or jumping across multiple rows/columns.
                // For example, if you were on the first row and tried to go down but the element was disabled,
                // the natural expectation would be to go to the next row at the same column. We can't do that because
                // we don't have any disabled/unavailable elements within the nav parent > nav children tree.
                // This could be added.
                Element *next_el = try_get_element_at_index(cur_element_index + nav_dir_value, nav_parent->nav_children);
                if (next_el != nullptr) {
                    int safe_index = std::clamp(retained_grid_index, 0, static_cast<int>(next_el->nav_children.size()) - 1);
                    return next_el->nav_children[safe_index];
                }
            }

            // Going in the direction of the container.
            if (are_nav_types_equal(nav_dir_type, nav_parent->nav_type)) {
                Element *next_el = try_get_element_at_index(cur_element_index + nav_dir_value, nav_parent->nav_children);
                if (next_el != nullptr) {
                    // Pick element in the same list and navigated to the next/previous index.
                    return next_el;
                }

                if (nav_parent->is_nav_wrapping && nav_parent->nav_type == nav_dir_type) {
                    // Wrap around in the same list.
                    if (nav_dir_value == 1) {
                        return nav_parent->nav_children[0];
                    } else {
                        return nav_parent->nav_children[nav_parent->nav_children.size() - 1];
                    }
                }

                // Left this element's list.
                return unwind_nav_in_direction(nav_parent);
            }

            // Not going in the direction of the container, but the container is a grid nav type
            if (is_grid_nav_type(nav_parent->nav_type)) {
                return unwind_nav_in_direction(nav_parent, cur_element_index);
            }

            if (nav_parent->nav_type == NavigationType::Auto) {
                auto next_element = get_element_in_nav_direction(this_element, nav_parent->nav_children);
                if (next_element != nullptr) {
                    return next_element;
                }
            }

            return unwind_nav_in_direction(nav_parent);
        }

        static Element *get_closest_element(Element *this_element, std::vector<Element *> &elements) {
            if (elements.empty()) {
                return nullptr;
            }

            RmlPosSize this_pos_size(this_element->base);
            Element *closest = nullptr;
            float closest_distance = std::numeric_limits<float>::max();
            for (auto &element : elements) {
                if (element == this_element) {
                    continue;
                }

                RmlPosSize element_pos_size(element->base);
                float distance = this_pos_size.get_distance(element_pos_size);
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest = element;
                }
            }

            return closest;
        }

        // Using the result of unwind_nav_in_direction, navigate through nav children until finding an element without children.
        // This tries to go in the same nav direction, or respects primary focus if the nav types differ.
        // Otherwise, it picks the element closest to the original focused element.
        Element *dive_nav_from_direction(Element *this_element) {
            #ifdef RECOMPUI_NAV_DEBUG
            print_debug_id(this_element, "↓ ");
            #endif
            // Exit when at the bottom.
            if (this_element->nav_children.size() == 0) {
                #ifdef RECOMPUI_NAV_DEBUG
                print_debug_id(this_element, "■ ");
                #endif
                return this_element;
            }

            if (are_nav_types_equal(this_element->nav_type, nav_dir_type)) {
                if (nav_dir_value == 1) {
                    return dive_nav_from_direction(this_element->nav_children[0]);
                } else {
                    return dive_nav_from_direction(this_element->nav_children[this_element->nav_children.size() - 1]);
                }
            } else {
                for (auto &child : this_element->nav_children) {
                    if (child->is_primary_focus) {
                        return dive_nav_from_direction(child);
                    }
                }

                return dive_nav_from_direction(get_closest_element(original_focused_element, this_element->nav_children));
            }
        }
    };

    Document::Document(ResourceId rid, Rml::Element *base) : Element(rid, base) {
        this->shim = false;
        set_width(100.0f, Unit::Percent);
        set_height(100.0f, Unit::Percent);

        is_nav_container = true;
        this->nav_type = NavigationType::Vertical;

        set_debug_id("Document #" + std::to_string(doc_counter++));

        register_event_listeners(
            recompui::Events(
                recompui::EventType::Update,
                recompui::EventType::Navigate,
                recompui::EventType::Focus));
    }

    void Document::process_event(const Event &e) {
        switch (e.type) {
            case recompui::EventType::Update: {
                if (update_last_focused) {
                    Element *cur_focus = get_current_context().get_focused_element();
                    if (cur_focus != nullptr) {
                        last_focused = cur_focus;
                    }
                    update_last_focused = false;
                }
                break;
            }
            default:
                break;
        }
    }

    void Document::report_focused_element() {
        if (update_last_focused == false) {
            update_last_focused = true;
            queue_update();
        }
    }

    void Document::report_hovered_element(Element* element) {
        if (element->is_focusable() == Element::CanFocus::Yes) {
            last_focusable_hovered = element;
        }
    }

    void Document::report_removed_element(Element* element) {
        if (last_focused == element) {
            last_focused = nullptr;
        }

        if (last_focusable_hovered == element) {
            last_focusable_hovered = nullptr;
        }
    }

    bool Document::handle_navigation_event(Rml::Event &event) {
        if (
            event.GetId() == Rml::EventId::Keydown &&
            event.GetPhase() == Rml::EventPhase::Bubble &&
            event.IsPropagating()
        ) {
            int key_identifier = event.GetParameter<int>("key_identifier", Rml::Input::KI_UNKNOWN);
            if (
                key_identifier != Rml::Input::KI_LEFT &&
                key_identifier != Rml::Input::KI_RIGHT &&
                key_identifier != Rml::Input::KI_UP &&
                key_identifier != Rml::Input::KI_DOWN
            ) {
                return false;
            }

            RecompNav nav_context(this, key_identifier);

            if (nav_context.original_focused_element == nullptr) {
                return false;
            }

            #ifdef RECOMPUI_NAV_DEBUG
            std::cout << "\nNAV START\n";
            #endif

            Element *next_top_element = nav_context.unwind_nav_in_direction(nav_context.original_focused_element);
            if (next_top_element == nullptr) {
                return false;
            }

            #ifdef RECOMPUI_NAV_DEBUG
            nav_context.print_debug_id(next_top_element, "→ ");
            #endif

            Element *doc_as_element = static_cast<Element *>(this);
            if (doc_as_element == next_top_element) {
                event.StopPropagation();
                return true;
            }

            Element *next_bottom_element = nav_context.dive_nav_from_direction(next_top_element);
            if (next_bottom_element == nullptr) {
                return false;
            }

            #ifdef RECOMPUI_NAV_DEBUG
            nav_context.print_debug_id(next_bottom_element, "→ ");
            #endif

            event.StopPropagation();
            next_bottom_element->focus();
            report_focused_element();

            return true;
        } else {
            return false;
        }
    }
} // namespace recompui
