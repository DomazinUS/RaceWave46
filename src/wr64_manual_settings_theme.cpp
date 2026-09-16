#include "wr64_manual_settings_theme.hpp"

#ifdef WR64_ENABLE_FRONTEND
#include "elements/ui_theme.h"

namespace wr64::manual_frontend {
void configure_settings_theme() {
    using C = recompui::theme::color;
    using recompui::Color;
    using recompui::theme::set_theme_color;
    const Color paper{252, 253, 252, 255};
    const Color ink{25, 29, 29, 255};
    const Color blue{54, 78, 163, 255};
    const Color pink{238, 78, 163, 255};
    const Color teal{0, 179, 182, 255};
    const Color mint{226, 243, 233, 255};
    set_theme_color(C::Background1, Color{0, 76, 83, 255});
    set_theme_color(C::Background2, mint);
    set_theme_color(C::Background3, Color{224, 244, 252, 255});
    set_theme_color(C::BGOverlay, Color{0, 76, 83, 248});
    set_theme_color(C::ModalOverlay, paper);
    set_theme_color(C::BGShadow, mint);
    set_theme_color(C::BGShadow2, Color{223, 238, 234, 255});
    set_theme_color(C::Text, ink);
    set_theme_color(C::TextActive, ink);
    set_theme_color(C::TextDim, Color{81, 89, 89, 255});
    set_theme_color(C::TextInactive, Color{91, 99, 99, 255});
    const C text_alpha[]{C::TextA5, C::TextA20, C::TextA30, C::TextA50, C::TextA80};
    const unsigned char alpha[]{13, 51, 77, 128, 204};
    for (unsigned i = 0; i < 5; ++i) set_theme_color(text_alpha[i], Color{25, 29, 29, alpha[i]});
    auto family = [](C base, Color value, Color light, Color dark) {
        using recompui::theme::set_theme_color;
        set_theme_color(base, value);
        set_theme_color(static_cast<C>(static_cast<int>(base) + 1), light);
        set_theme_color(static_cast<C>(static_cast<int>(base) + 2), dark);
        const unsigned char opacity[]{13, 51, 77, 128, 204};
        for (int i = 0; i < 5; ++i) {
            value.a = opacity[i];
            set_theme_color(static_cast<C>(static_cast<int>(base) + 3 + i), value);
        }
    };
    family(C::Primary, blue, blue, Color{40, 57, 121, 255});
    family(C::Secondary, pink, Color{250, 146, 192, 255}, Color{173, 29, 101, 255});
    // Inline warning descriptions need dark ink on the pale blue paper.
    // Warning buttons separately use the manual's yellow fill.
    family(C::Warning, Color{0, 130, 145, 255}, teal, Color{0, 97, 109, 255});
    family(C::Danger, Color{221, 83, 66, 255}, Color{251, 111, 83, 255}, Color{166, 43, 28, 255});
    family(C::Success, Color{35, 149, 103, 255}, Color{55, 181, 126, 255}, Color{21, 104, 70, 255});
    set_theme_color(C::Border, teal);
    set_theme_color(C::BorderSoft, Color{168, 215, 193, 255});
    set_theme_color(C::BorderHard, teal);
    set_theme_color(C::BorderSolid, pink);
    set_theme_color(C::Elevated, Color{227, 244, 239, 255});
    set_theme_color(C::ElevatedSoft, Color{241, 244, 243, 255});
    set_theme_color(C::ElevatedBorder, Color{180, 193, 190, 255});
    set_theme_color(C::ElevatedBorderHard, teal);
    recompui::theme::set_border_width(2.0f);
    recompui::theme::set_border_radius_sm(8.0f);
    recompui::theme::set_border_radius_md(16.0f);
    recompui::theme::set_border_radius_lg(24.0f);
}
}
#else
void wr64::manual_frontend::configure_settings_theme() {}
#endif
