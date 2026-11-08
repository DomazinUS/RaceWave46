#include "wr64_librashader_presets.hpp"
#include "common/rt64_wr64_librashader_settings.h"

#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>

namespace {
namespace fs = std::filesystem;
using namespace wr64::librashader;

void check(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

nlohmann::json manifest_with(nlohmann::json presets) {
    return {{"schema_version", 1}, {"presets", std::move(presets)}};
}

nlohmann::json entry(const std::string& id, const std::string& path, const std::string& label = "Label") {
    return {{"id", id}, {"label", label}, {"name", "Name " + id}, {"description", "About " + id}, {"path", path}};
}

void parsing_accepts_valid_entries_and_skips_invalid_ones() {
    std::vector<std::string> errors;
    const auto presets = parse_presets(manifest_with({
        entry("crt-a", "crt/a.slangp"),
        entry("crt-a", "crt/b.slangp"),
        entry("off", "c.slangp"),
        entry("Upper", "d.slangp"),
        entry("escape", "../outside.slangp"),
        entry("absolute", "/etc/passwd.slangp"),
        entry("backslash", "crt\\e.slangp"),
        entry("wrong-type", "crt/f.slang"),
        entry("no-label", "crt/g.slangp", ""),
        entry("sharp", "sharpen/h.slangp"),
    }), errors);
    check(presets.size() == 2, "only the two valid, unique presets are kept");
    check(presets[0].id == "crt-a" && presets[0].label == "Label", "the first preset keeps its menu label");
    check(presets[1].id == "sharp", "the second preset keeps its order");
    check(errors.size() == 8, "each rejected entry is reported");
}

void parsing_rejects_unknown_manifests() {
    std::vector<std::string> errors;
    check(parse_presets(nlohmann::json::array(), errors).empty(), "non-object manifest");
    check(parse_presets({{"schema_version", 2}, {"presets", nlohmann::json::array()}}, errors).empty(), "future schema");
    check(parse_presets({{"schema_version", 1}}, errors).empty(), "missing preset list");
    check(errors.size() == 3, "manifest errors are reported");
}

void menu_values_map_to_presets() {
    std::vector<std::string> errors;
    const auto presets = parse_presets(manifest_with({entry("one", "one.slangp"), entry("two", "two.slangp")}), errors);
    check(preset_for_value(presets, OffValue) == nullptr, "Off has no preset");
    check(preset_for_value(presets, 1)->id == "one", "value 1 is the first preset");
    check(preset_for_value(presets, 2)->id == "two", "value 2 is the second preset");
    check(preset_for_value(presets, 3) == nullptr, "out-of-range values are Off");

    check(preset_summary(presets, OffValue).empty(), "Off has no summary");
    check(preset_summary(presets, 2) == "Name two: About two", "the description column names the shader");
    std::vector<std::string> plain_errors;
    const auto undescribed = parse_presets(manifest_with({
        {{"id", "plain"}, {"label", "Plain"}, {"name", "Plain"}, {"description", ""}, {"path", "plain.slangp"}}
    }), plain_errors);
    check(preset_summary(undescribed, 1) == "Plain", "a shader without a description shows its name only");

    ControlState state{true, "", ""};
    check(preset_status(presets, 1, state).empty(), "a working preset has no status");
    state.preset_error = "compile failed";
    check(preset_status(presets, OffValue, state).empty(), "Off has no status");
    check(preset_status(presets, 1, state).find("compile failed") != std::string::npos, "renderer errors are shown");
    state = {false, "librashader is not installed with the game.", ""};
    check(preset_status(presets, 1, state) == "Unavailable: librashader is not installed with the game.",
        "a missing runtime explains why the option is disabled");
}

void description_text_is_escaped() {
    check(escape_markup("CRT <b>&\"x\"</b>") == "CRT &lt;b&gt;&amp;&quot;x&quot;&lt;/b&gt;", "manifest text cannot add markup");
}

void selection_generation_tracks_preset_changes_only() {
    RT64::setWr64ShaderPreset("a.slangp");
    const auto first = RT64::getWr64ShaderSelection();
    RT64::setWr64ShaderInput(uint32_t(RT64::Wr64ShaderInput::Native));
    RT64::setWr64ShaderPreset("a.slangp");
    const auto same = RT64::getWr64ShaderSelection();
    check(same.presetGeneration == first.presetGeneration, "input changes and repeated presets keep the compiled chain");
    check(same.input == RT64::Wr64ShaderInput::Native, "input is stored");
    RT64::setWr64ShaderInput(7);
    check(RT64::getWr64ShaderSelection().input == RT64::Wr64ShaderInput::Internal, "unknown inputs fall back to Internal");
    RT64::setWr64ShaderPreset({});
    check(RT64::getWr64ShaderSelection().presetGeneration == first.presetGeneration + 1, "a new preset is a new generation");

    const uint64_t revision = RT64::getWr64ShaderStatusRevision();
    RT64::reportWr64ShaderStatus(4, true, "error");
    RT64::reportWr64ShaderStatus(4, true, "error");
    check(RT64::getWr64ShaderStatusRevision() == revision + 1, "identical reports do not wake the UI again");
    check(RT64::getWr64ShaderStatus().message == "error", "status message is stored");
}

std::string read_text(const fs::path& path) {
    std::ifstream stream(path, std::ios::binary);
    check(bool(stream), "cannot read " + path.generic_string());
    std::ostringstream text;
    text << stream.rdbuf();
    return text.str();
}

// Every file a preset loads must be bundled: its passes, their includes, LUT
// textures and referenced presets. This catches an incomplete curated copy.
void check_preset_closure(const fs::path& preset, std::set<fs::path>& visited) {
    if (!visited.insert(fs::weakly_canonical(preset)).second) return;
    check(fs::is_regular_file(preset), "missing preset file " + preset.generic_string());
    const std::string text = read_text(preset);
    const fs::path base = preset.parent_path();
    static const std::regex reference(R"re(^\s*#reference\s+"?([^"\r\n]+?)"?\s*$)re");
    static const std::regex pair(R"re(^\s*([A-Za-z0-9_]+)\s*=\s*"?([^"\r\n]*?)"?\s*$)re");
    std::map<std::string, std::string> values;
    std::istringstream lines(text);
    for (std::string line; std::getline(lines, line);) {
        std::smatch match;
        if (std::regex_match(line, match, reference)) check_preset_closure(base / match[1].str(), visited);
        else if (std::regex_match(line, match, pair)) values[match[1].str()] = match[2].str();
    }

    static const std::regex include(R"re(^\s*#include\s+"([^"]+)")re");
    const std::function<void(const fs::path&)> check_source = [&](const fs::path& source) {
        if (!visited.insert(fs::weakly_canonical(source)).second) return;
        check(fs::is_regular_file(source), "missing shader source " + source.generic_string());
        std::istringstream source_lines(read_text(source));
        for (std::string line; std::getline(source_lines, line);) {
            std::smatch match;
            if (std::regex_search(line, match, include)) check_source(source.parent_path() / match[1].str());
        }
    };

    for (const auto& [key, value] : values) {
        if (std::regex_match(key, std::regex("shader[0-9]+"))) check_source(base / value);
    }

    std::istringstream textures(values["textures"]);
    for (std::string name; std::getline(textures, name, ';');) {
        if (name.empty()) continue;
        check(values.count(name) == 1, "texture " + name + " has no path in " + preset.generic_string());
        const fs::path texture = base / values[name];
        check(fs::is_regular_file(texture), "missing texture " + texture.generic_string());
    }
}

void bundled_manifest_is_complete(const fs::path& shader_directory) {
    std::vector<std::string> errors;
    const auto presets = load_presets(shader_directory, errors);
    for (const auto& error : errors) std::cerr << error << '\n';
    check(errors.empty(), "the bundled manifest loads without errors");
    check(presets.size() == 2, "the bundled manifest lists the two CRT presets");
    check(presets[0].label == "CRT" && presets[1].label == "Fast CRT",
        "the menu choices are Off, CRT and Fast CRT");
    for (const auto& preset : presets) {
        std::set<fs::path> visited;
        check_preset_closure(shader_directory / utf8_path(preset.path), visited);
    }
}
}

int main(int argc, char** argv) {
    try {
        check(argc == 2, "Provide the assets/shaders directory.");
        parsing_accepts_valid_entries_and_skips_invalid_ones();
        parsing_rejects_unknown_manifests();
        menu_values_map_to_presets();
        description_text_is_escaped();
        selection_generation_tracks_preset_changes_only();
        bundled_manifest_is_complete(fs::path(argv[1]));
        std::cout << "librashader preset tests passed\n";
        return 0;
    }
    catch (const std::exception& error) {
        std::cerr << "FAILED: " << error.what() << '\n';
        return 1;
    }
}
