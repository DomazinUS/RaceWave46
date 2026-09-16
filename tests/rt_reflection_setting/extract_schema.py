"""Compile actual frontend RT registrations and callbacks with real Config."""
from pathlib import Path
import re
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / "src/wr64_frontend.cpp").read_text()

# Check placement against all production option registrations, including rows
# this fixture does not compile. Conditional child controls stay with parents.
option_order = [match.group(1).strip() for match in re.finditer(
    r'enhancementsConfig\.add_(?:bool|enum|number)_option\(\s*("[^"\n]+"|\w+)', source)]
for parent, child in (("water_reflections", "rt_reflection_distance"),
                      ("shadow_method", "rt_shadow_samples")):
    parent_key, child_key = f'"{parent}"', f'"{child}"'
    assert option_order.count(parent_key) == option_order.count(child_key) == 1
    assert option_order.index(child_key) == option_order.index(parent_key) + 1, (
        f"{child} must appear directly below {parent}")


def balanced(start, opening, closing):
    position = source.index(opening, start)
    depth, quoted, escaped = 0, False, False
    while position < len(source):
        c = source[position]
        if quoted:
            if escaped:
                escaped = False
            elif c == "\\":
                escaped = True
            elif c == '"':
                quoted = False
        elif c == '"':
            quoted = True
        elif c == opening:
            depth += 1
        elif c == closing:
            depth -= 1
            if depth == 0:
                return source[start:position + 1]
        position += 1
    raise AssertionError("Unterminated production source")


registrations = []
for method, option in (("add_enum_option", "water_reflections"),
                       ("add_bool_option", "rt_sky_reflections"),
                       ("add_enum_option", "sky_reflection_method"),
                       ("add_number_option", "raster_sky_strength"),
                       ("add_enum_option", "shadow_method"),
                       ("add_enum_option", "raster_shadow_distance"),
                       ("add_number_option", "rt_reflection_distance"),
                       ("add_number_option", "rt_shadow_samples"),
                       ("add_enum_option", "split_screen_layout"),
                       ("add_option_change_callback", "rt_reflection_distance"),
                       ("add_option_change_callback", "raster_sky_strength"),
                       ("add_option_change_callback", "rt_shadow_samples"),
                       ("add_option_change_callback", "rt_sky_reflections"),
                       ("add_option_change_callback", "sky_reflection_method"),
                       ("add_option_change_callback", "shadow_method"),
                       ("add_option_change_callback", "raster_shadow_distance"),
                       ("add_option_change_callback", "water_reflections")):
    start = source.index(f'enhancementsConfig.{method}("{option}"')
    registrations.append((start, balanced(start, "(", ")") + ";"))
# Keep production order: dependent options must exist before load callbacks.
registrations = [text for _, text in sorted(registrations)]
bridges = [balanced(source.index(signature), "{", "}") for signature in
           ("void applyWaterReflections(uint32_t mode)", "void applyRayTracedShadows(bool enabled)",
            "void applyShadowMethod(uint32_t method)",
            "void applySkyReflections(bool enabled)",
            "void applySkyReflectionMethod(uint32_t method)",
            "void updateSkyReflectionControls(recomp::config::Config& config)",
            "bool migrateReflectionProfile(nlohmann::json& profile)",
            "bool loadReflectionProfile(recomp::config::Config& config)",
            "void applyRasterSkyStrength(double percent)",
            "void applyReflectionDistance(double percent)", "void applyShadowSamples(double samples)")]
diagnostics = [balanced(source.index("struct RTReflectionDiagnosticLog"), "{", "}") + ";"]
for signature in ("RTReflectionDiagnosticLog& rtReflectionDiagnosticLog()",
                  "void writeRTReflectionDiagnostic(const char* stage, const char* details)",
                  "void initializeRTReflectionDiagnostic()"):
    diagnostics.append(balanced(source.index(signature), "{", "}"))
output.write_text("\n".join([
    '#include "librecomp/config.hpp"', '#include "librecomp/game.hpp"',
    '#include "wr64_diagnostic_policy.h"',
    '#include "common/rt64_wr64_rt_diagnostics.h"', '#include <cstdio>', '#include <cstdlib>',
    '#include "common/rt64_wr64_rt_settings.h"',
    '#include "wr64_enhancement_controls.hpp"',
    '#include <chrono>', '#include <fstream>', '#include <mutex>',
    'using wr64::frontend::update_enhancement_controls;',
    'wr64::frontend::EnhancementAvailability enhancement_controls_available{true, true};',
    *diagnostics, *bridges,
    'void registered_reflection_schema(recomp::config::Config& enhancementsConfig) {',
    *registrations, '}']))
