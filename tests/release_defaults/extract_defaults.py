"""Compile actual startup/default producers without creating frontend windows."""
from pathlib import Path
import re
import sys

root, output = map(Path, sys.argv[1:3])


def function(text, name):
    match = re.search(r"^[\w:<>, &*]+\b" + name + r"\([^;]*?\)\s*\{", text, re.M)
    assert match, name
    start = text.index("{", match.start())
    depth = 1
    position = start + 1
    # These selected functions contain no unmatched braces inside literals.
    while depth:
        depth += (text[position] == "{") - (text[position] == "}")
        position += 1
    return text[match.start():position]


parts = [r'''
#include "wr64_editions.hpp"
#include "wr64_graphics_config.hpp"
#include "librecomp/config.hpp"
#include "common/rt64_wr64_ultrawide.h"
#include "common/rt64_wr64_separate_windows.h"
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#include <shellapi.h>
#endif
''']
editions = (root / "src/wr64_editions.cpp").read_text()
parts += ["namespace wr64::editions { namespace {", function(editions, "executable_path"), "}",
    function(editions, "parse_options"), function(editions, "parse_process_options"), "}"]
shims = (root / "src/recomp_shims.cpp").read_text()
parts += ["constexpr float kNativePerspectiveAspect = 4.0f / 3.0f;", function(shims, "parse_experimental_3d_aspect")]
renderer = (root / "src/rt64_renderer.cpp").read_text()
parts += [function(renderer, name) for name in
    ("wr64_presentation_rate_override", "wr64_requested_graphics_api", "apply_presentation_override")]
frontend = (root / "src/wr64_frontend.cpp").read_text()
constant = re.search(r"constexpr double DefaultWaveRoundnessPercent\s*=\s*[^;]+;", frontend)
assert constant
parts += [constant.group(), function(frontend, "initialWaveRoundnessPercent")]

# Read the actual form registration expressions rather than inventing a test
# default GraphicsConfig. Mapping/application is the production inline helper.
graphics = (root / "lib/RecompFrontend/recompui/src/config/ui_config_tab_graphics.cpp").read_text()
general = (root / "lib/RecompFrontend/recompui/src/config/ui_config_tab_general.cpp").read_text()
sound = (root / "lib/RecompFrontend/recompui/src/config/ui_config_tab_sound.cpp").read_text()


def registration(source, namespace, option, method):
    match = re.search(r"config\." + method + r"\(\s*" + namespace +
                      r"::options::" + option + r",.*?\);", source, re.S)
    assert match, option
    return match.group().replace(f"{namespace}::options::{option}", f'"{option}"')


parts.append(function(graphics, "get_framerate_text"))
graphics_enums = ("res_option", "ar_option", "rr_option", "msaa_option", "hr_option",
                  "api_option", "hpfb_option", "wm_option", "ds_option")
parts += ["void registered_graphics_schema(recomp::config::Config& config) {",
          "using EnumOptionVector = const std::vector<recomp::config::ConfigOptionEnumOption>;",
          re.search(r"enum class DownsamplingOption\s*\{.*?\};", graphics, re.S).group(),
          graphics[graphics.index("        #if defined(_WIN32)"):
                   graphics.index("        static EnumOptionVector graphics_api_options")]]
parts += re.findall(r"static EnumOptionVector \w+\s*=\s*\{.*?\n\s*\};", graphics, re.S)
parts += [registration(graphics, "graphics", option, "add_enum_option") for option in graphics_enums]
parts += [registration(graphics, "graphics", "rr_manual_value", "add_number_option"),
          registration(graphics, "graphics", "developer_mode", "add_bool_option")]
for method in ("on_json_parse_option", "on_json_serialize_option"):
    statement = re.search(r"config\." + method + r"\(graphics::options::ds_option,.*?\}\);", graphics, re.S)
    assert statement, method
    parts.append(statement.group().replace("graphics::options::ds_option", '"ds_option"'))
parts.append("}")
defaults = []
for option in graphics_enums:
    defaults.append(f'    config.{option} = decltype(config.{option})(std::get<uint32_t>(schema.get_option_value("{option}")));')
parts += ["ultramodern::renderer::GraphicsConfig registered_graphics_defaults() {",
    '    recomp::config::Config schema("Graphics", "graphics", true); registered_graphics_schema(schema);',
    "    ultramodern::renderer::GraphicsConfig config{};", *defaults,
    '    config.rr_manual_value = int(std::get<double>(schema.get_option_value("rr_manual_value")));',
    '    config.developer_mode = std::get<bool>(schema.get_option_value("developer_mode"));',
    "    return config;\n}"]
parts += ["void registered_general_schema(recomp::config::Config& config) {",
    "using EnumOptionVector = const std::vector<recomp::config::ConfigOptionEnumOption>;",
    "constexpr bool player_two_rumble_strength = true;",
    re.search(r"enum class BackgroundInputMode\s*\{.*?\};", general, re.S).group(),
    re.search(r"static EnumOptionVector background_input_options\s*=\s*\{.*?\};", general, re.S).group(),
    registration(general, "general", "background_input_mode", "add_enum_option"),
    registration(general, "general", "debug_mode", "add_bool_option")]
parts += [registration(general, "general", option, "add_percent_number_option") for option in
          ("rumble_strength", "rumble_strength_p2", "joystick_deadzone")]
for option in ("gameplay_rumble", "show_ghost"):
    statement = re.search(r'generalConfig\.add_bool_option\("' + option + r'".*?\);', frontend, re.S)
    assert statement, option
    parts.append(statement.group().replace("generalConfig.", "config."))
parts += ["}", "void registered_sound_schema(recomp::config::Config& config) {",
          registration(sound, "sound", "main_volume", "add_percent_number_option"), "}"]
for option in ("gameplay_rumble", "show_ghost"):
    registration = re.search(r'generalConfig\.add_bool_option\("' + option + r'".*?\);', frontend, re.S)
    assert registration, option
    value = re.search(r",\s*(true|false)\s*\);$", registration.group())
    assert value, option
    parts.append(f"bool registered_{option}_default() {{ return {value[1]}; }}")
hud_vector = re.search(r"static EnumOptionVector hud_ratio_mode_options\s*=\s*\{.*?\n\s*\};", graphics, re.S)
hud_registration = re.search(r"config\.add_enum_option\(\s*graphics::options::hr_option,.*?\n\s*\);", graphics, re.S)
assert hud_vector and hud_registration
parts += ["void registered_hud_schema(recomp::config::Config& config) {",
    hud_vector.group().replace("static EnumOptionVector", "const std::vector<recomp::config::ConfigOptionEnumOption>"),
    hud_registration.group().replace("graphics::options::hr_option", '"hr_option"'), "}"]

# Replay the actual workload aspect block with lightweight input containers.
# The geometry and mode formulas are production code, not a test reimplementation.
workload = (root / "lib/rt64/src/hle/rt64_workload_queue.cpp").read_text()
start = workload.index("        const float wr64DisplayAspect =")
end = workload.index("        // Build the resolution scale vector", start)
block = workload[start:end]
parts.append(r'''
std::array<float,3> released_workload_aspect(uint32_t width,uint32_t height,
    RT64::UserConfiguration::AspectRatio ratioMode,
    RT64::UserConfiguration::AspectRatio extRatioMode,float target) {
    using namespace RT64;
    const bool separateWindows = false; // This fixture covers the primary-window startup path.
    struct Resources { uint32_t swapChainWidth,swapChainHeight; UserConfiguration userConfig; } resources{width,height};
    resources.userConfig.extAspectTarget=target;
    struct Extension { Resources* sharedResources; } ext{&resources};
    struct Workload { float aspectRatioSource=424.0f/240.0f,aspectRatioTarget=0,extAspectPercentage=0; } workloadConfig;
''')
parts += [block, "return {wr64SceneAspect,workloadConfig.aspectRatioTarget,workloadConfig.extAspectPercentage};\n}"]
output.write_text("\n".join(parts))
