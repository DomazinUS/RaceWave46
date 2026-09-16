#include "base_rcss.h"
#include "recompui/recompui.h"
#include "elements/ui_theme.h"

static std::string base_rcss;

static const std::string base_rcss_end = R"(
*, *:before, *:after {
  box-sizing: border-box;
}

div, p, h1 { display: block; }

em { font-style: italic; }
strong { font-weight: bold; }
select { text-align: left; }

p { text-align: left; }

input.text,
input.password,
select,
textarea {
  height: auto;
}

input.radio {
  flex: 0;
  width: 0dp;
  nav-up: auto;
  nav-right: auto;
  nav-down: auto;
  nav-left: auto;
  tab-index: auto;
  focus: auto;
}

input.checkbox {
  width: 20dp;
  height: 20dp;
  nav-up: auto;
  nav-right: auto;
  nav-down: auto;
  nav-left: auto;
  tab-index: auto;
  focus: auto;
}

scrollbarvertical, scrollbarhorizontal {
  margin: 0;
  border: 0;
}
scrollbarvertical slidertrack, scrollbarhorizontal slidertrack {
  background: #a8e3e4;
  opacity: 1;
}
scrollbarvertical sliderbar, scrollbarhorizontal sliderbar {
  border-radius: 5dp;
  background: #00b3b6;
  opacity: 1;
}
scrollbarvertical sliderbar:hover:not(:active), scrollbarhorizontal sliderbar:hover:not(:active) {
  background: #ee4ea3;
}
scrollbarvertical sliderbar:active, scrollbarhorizontal sliderbar:active {
  background: #ee4ea3;
}
scrollbarvertical sliderarrowdec, scrollbarvertical sliderarrowinc, scrollbarhorizontal sliderarrowdec, scrollbarhorizontal sliderarrowinc {
  width: 0;
  height: 0;
}

scrollbarvertical {
  width: 12dp;
}
scrollbarvertical slidertrack {
  width: 12dp;
}
scrollbarvertical sliderbar {
  width: 12dp;
}

scrollbarhorizontal {
  height: 12dp;
}
scrollbarhorizontal slidertrack {
  height: 12dp;
}
scrollbarhorizontal sliderbar {
  height: 12dp;
}
)";

const std::string &recompui::get_base_rcss() {
    if (!base_rcss.empty()) {
        return base_rcss;
    }
    auto &body_preset = recompui::theme::get_typography_preset(recompui::theme::Typography::Body);
    auto body_rcss =
        "body {\n"
        "  width: 100%;\n"
        "  height: 100%;\n"
        "  color: Text;\n"
        "  font-size: " + std::to_string(static_cast<int>(body_preset.font_size)) + "dp;\n"
        "  letter-spacing: " + std::to_string(static_cast<int>(body_preset.letter_spacing)) + "dp;\n"
        "  line-height: " + std::to_string(static_cast<int>(body_preset.line_height)) + "dp;\n"
        "  font-style: " + (body_preset.font_style == recompui::FontStyle::Normal ? "normal" : "italic") + ";\n"
        "  font-weight: " + std::to_string(body_preset.font_weight) + ";\n"
        "  font-family: \"" + recompui::get_primary_font_family() + "\";\n"
        "}\n";

    base_rcss = body_rcss + "\n" + base_rcss_end;

    return base_rcss;
}
