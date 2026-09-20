#include "wr64_manual_frontend.hpp"
#include "wr64_manual_settings_theme.hpp"

#ifdef WR64_ENABLE_FRONTEND
#include <array>
#include <stdexcept>
#include "RmlUi/Core/PropertyDictionary.h"
#include "RmlUi/Core/StyleSheetSpecification.h"
#include "recompui/recompui.h"
#include "base/ui_launcher.h"
#include "base/ui_game_option.h"
#include "elements/ui_label.h"
#include "elements/ui_image.h"
#include "librecomp/game.hpp"

extern std::vector<recomp::GameEntry> supported_games;

namespace wr64::manual_frontend {
namespace {
using namespace recompui;
constexpr Color Green{0, 126, 133, 255};
constexpr Color Paper{236, 246, 240, 255};
constexpr Color Ink{22, 27, 27, 255};
constexpr Color Blue{54, 78, 163, 255};
constexpr Color Pink{236, 79, 166, 255};
constexpr Color Yellow{255, 203, 5, 255};
constexpr Color Coral{251, 111, 83, 255};

// Preserve the supplied composition: cover the window without stretching it,
// and crop equally on both sides so its central rider remains the focal point.
class ManualBackdrop final : public Element {
protected:
    std::string_view get_type_name() override { return "ManualBackdrop"; }
public:
    ManualBackdrop(ResourceId rid, Element* parent) : Element(rid, parent, 0, "div", false) {
        set_debug_id("manual-illustrated-backdrop");
        set_position(Position::Absolute);
        set_inset(0.0f);
        set_width(100.0f, Unit::Percent);
        set_height(100.0f, Unit::Percent);
        set_image_color(Color{255, 255, 255, 255});
        set_pointer_events(PointerEvents::None);

        // RmlUi performs cover fitting during its first layout/render pass and
        // on every resize. No queued update or initial letterboxed frame is
        // needed. A property source lets native relative texture loading find
        // the same assets directory used by ordinary Image elements.
        Rml::PropertyDictionary properties;
        if (!Rml::StyleSheetSpecification::ParsePropertyDeclaration(properties, "decorator",
                "image(\"manual/WaveRace_Recompiled.png\" cover center center)")) {
            throw std::runtime_error("Could not initialize the manual backdrop decorator.");
        }
        auto source = Rml::MakeShared<Rml::PropertySource>(
            get_current_context().get_document()->GetSourceURL(), 0, "manual backdrop");
        for (const auto& [id, value] : properties.GetProperties()) {
            Rml::Property property = value;
            property.source = source;
            Style::set_property(id, property);
        }
        apply_styles();
    }
};

void create_history_card(ContextId context, Element* container) {
    auto card = context.create_element<Element>(container);
    card->set_debug_id("manual-history-card");
    card->set_position(Position::Absolute);
    card->set_left(1.2f, Unit::Percent);
    card->set_top(1.5f, Unit::Percent);
    card->set_width(35.6f, Unit::Percent);
    card->set_max_height(82.0f, Unit::Percent);
    card->set_padding(28.0f);
    card->set_display(Display::Flex);
    card->set_flex_direction(FlexDirection::Column);
    card->set_gap(16.0f);
    card->set_background_color(Color{32, 30, 37, 218});
    card->set_border_width(2.0f);
    card->set_border_color(Color{229, 180, 107, 210});
    card->set_border_radius(14.0f);
    card->set_color(Paper);
    card->set_overflow_y(Overflow::Auto);

    const auto label = [&](const char* id, const char* text, float size, float line, Color color) {
        auto result = context.create_element<Label>(card, text, LabelStyle::Normal);
        result->set_debug_id(id);
        result->set_font_size(size);
        result->set_line_height(line);
        result->set_font_weight(400);
        result->set_letter_spacing(0.0f);
        result->set_white_space(WhiteSpace::Preline);
        result->set_color(color);
        result->set_flex_shrink(0.0f);
        return result;
    };
    const Color gold{255, 218, 151, 255};
    auto eyebrow = label("manual-history-eyebrow", "NINTENDO 64  /  1996", 18.0f, 22.0f, gold);
    eyebrow->set_letter_spacing(2.0f);
    auto heading = label("manual-history-title", "Wave Race 64", 42.0f, 46.0f, Paper);
    heading->set_font_weight(700);
    label("manual-history-intro",
        "Nintendo's jet-ski racer made the water part of the challenge: rolling waves, shifting conditions and buoy-lined courses that rewarded precision as much as speed.",
        22.0f, 29.0f, Paper);
    auto dates_title = label("manual-history-dates-title", "AROUND THE WORLD", 18.0f, 22.0f, gold);
    dates_title->set_letter_spacing(1.5f);
    label("manual-history-dates",
        "Japan  /  27 September 1996\nUSA  /  04 November 1996\nEurope  /  29 April 1997",
        22.0f, 30.0f, Paper);
    auto versions_title = label("manual-history-versions-title", "REGIONAL EDITIONS", 18.0f, 22.0f, gold);
    versions_title->set_letter_spacing(1.5f);
    label("manual-history-versions",
        "Western releases renamed Japan's Milky Lake to Drake Lake and Cool Wave to Glacier Coast; Europe also offered English and German text.\n\n"
        "Japan's Shindou edition (18 July 1997) added Rumble Pak support and dolphin ghosts for Time Trials, alongside changes to music and sound effects.",
        22.0f, 29.0f, Paper);
    auto divider = context.create_element<Element>(card);
    divider->set_height(1.0f);
    divider->set_flex_shrink(0.0f);
    divider->set_background_color(Color{229, 180, 107, 120});
    label("manual-history-tribute",
        "This recompilation is a tribute to Wave Race 64 on its 30th anniversary, celebrating three decades of racing the waves.",
        22.0f, 29.0f, gold);
}

}

void configure_theme() {
    configure_settings_theme();
}

void create_launcher(recompui::LauncherMenu* menu) {
    using namespace recompui;
    auto context = get_current_context();
    menu->remove_default_title();
    menu->set_background_color(Green);
    auto background = menu->get_background_container();
    background->clear_children();
    background->set_overflow(Overflow::Hidden);
    background->set_pointer_events(PointerEvents::None);
    context.create_element<ManualBackdrop>(background);
    auto container = menu->get_menu_container();
    container->set_inset(0.0f);
    create_history_card(context, container);

    auto title = context.create_element<Image>(container, "manual/RaceWave46_logo_noBackground.png");
    title->set_debug_id("manual-title-logo");
    title->set_position(Position::Absolute);
    // Small signature above the bottom-left version label. Preserve the
    // supplied PNG's native proportions (about 104 px wide at 720p).
    title->set_left(6.0f);
    title->set_bottom(28.0f);
    title->set_width(156.0f);
    title->set_height(156.0f * 822.0f / 1914.0f);
    title->set_image_color(Color{255, 255, 255, 255});
    title->set_pointer_events(PointerEvents::None);

    auto anniversary = context.create_element<Image>(container, "manual/WaveRace64_30th_Anniversary.png");
    anniversary->set_debug_id("manual-anniversary-logo");
    anniversary->set_position(Position::Absolute);
    anniversary->set_right(6.0f, Unit::Percent);
    anniversary->set_top(3.2f, Unit::Percent);
    // Fit the logo above the menu while preserving its aspect ratio; cap its width
    // so ultrawide layouts retain room for the menu rows.
    anniversary->set_width(36.0f, Unit::Percent);
    anniversary->set_max_width(720.0f);
    anniversary->set_height_auto();
    anniversary->set_image_color(Color{255, 255, 255, 255});
    anniversary->set_pointer_events(PointerEvents::None);

    const auto& entry = supported_games.front();
    auto options = menu->init_game_options_menu(entry.game_id, entry.mod_game_id,
        entry.display_name, entry.thumbnail_bytes, GameOptionsMenuLayout::Right);
    options->set_debug_id("manual-menu-options");
    options->set_right(6.0f, Unit::Percent);
    options->set_bottom(7.0f, Unit::Percent);
    options->set_width(44.0f, Unit::Percent);
    options->set_gap(14.0f);
    options->add_start_game_or_load_rom_option("Select USA ROM", "Start Game");
    options->add_setup_controls_option("Setup controls");
    options->add_settings_option("Settings");
    options->add_exit_option("Exit");

    constexpr std::array<Color, 4> borders{Pink, Pink, Yellow, Coral};
    constexpr std::array<Color, 4> dots{Blue, Pink, Yellow, Color{55, 181, 126, 255}};
    for (size_t i = 0; i < options->get_options().size(); ++i) {
        auto option = options->get_options()[i];
        option->set_debug_id("manual-option-" + std::to_string(i));
        option->set_height(84.0f);
        option->set_padding(16.0f);
        option->set_padding_top(12.0f);
        option->set_padding_bottom(12.0f);
        option->set_padding_left(24.0f);
        option->set_padding_right(18.0f);
        option->set_border_radius(24.0f);
        option->set_border_width(3.0f);
        option->set_border_color(borders[i]);
        option->set_background_color(Paper);
        option->set_color(Ink);
        // RecompFrontend reapplies base styles on blur; give it an explicit
        // identity transform so a previously selected row shrinks back.
        option->set_scale_2D(1.0f, 1.0f);
        option->set_gap(20.0f);
        option->hover_style.set_background_color(Color{224, 245, 253, 255});
        option->hover_style.set_color(Blue);
        option->hover_style.set_border_color(Blue);
        option->hover_style.set_border_width(5.0f);
        option->hover_style.set_padding_top(10.0f);
        option->hover_style.set_padding_bottom(10.0f);
        option->hover_style.set_scale_2D(1.02f, 1.03f);
        // A selected card is visibly larger, with a heavy blue outline and
        // a warm paper fill. Scale around the centre without reflowing rows.
        option->focus_style.set_background_color(Color{255, 244, 190, 255});
        option->focus_style.set_color(Blue);
        option->focus_style.set_border_color(Blue);
        option->focus_style.set_border_width(7.0f);
        option->focus_style.set_padding_top(8.0f);
        option->focus_style.set_padding_bottom(8.0f);
        option->focus_style.set_scale_2D(1.04f, 1.06f);
        auto text = option->get_label();
        // GameOption pulses its inherited text colour while focused. Keep
        // dark manual ink on paper; the blue border marks controller focus.
        text->set_color(i == 0 ? Blue : Ink);
        text->set_font_size(36.0f);
        text->set_line_height(43.0f);
        text->set_letter_spacing(3.0f);
        text->set_white_space(WhiteSpace::Nowrap);
        text->set_pointer_events(PointerEvents::None);
        auto dot = context.create_element<Element>(option);
        dot->set_width(54.0f);
        dot->set_height(54.0f);
        dot->set_flex_shrink(0.0f);
        // RmlUi's radius property uses lengths; a percentage was ignored and
        // made these badges square in the native frontend.
        dot->set_border_radius(27.0f);
        dot->set_background_color(dots[i]);
        dot->set_pointer_events(PointerEvents::None);
    }
}
}
#endif
