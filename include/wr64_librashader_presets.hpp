#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <json/json.hpp>

namespace wr64::librashader {

constexpr const char* PresetOptionId = "librashader_preset";
constexpr uint32_t OffValue = 0u;

struct Preset {
    // Saved in the settings profile; must stay stable across releases.
    std::string id;
    // Text on the choice itself; the name below is the full shader name.
    std::string label;
    std::string name;
    std::string description;
    // Relative to the shader directory.
    std::string path;
};

// UTF-8 manifest text to a path, without C++20's deprecated u8path.
inline std::filesystem::path utf8_path(const std::string& text) {
#if defined(__cpp_char8_t)
    return std::filesystem::path(std::u8string(text.begin(), text.end()));
#else
    return std::filesystem::u8path(text);
#endif
}

inline bool valid_preset_id(const std::string& id) {
    if (id.empty() || id.size() > 64) return false;
    for (const char c : id) {
        const bool allowed = (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-';
        if (!allowed) return false;
    }
    // "off" is the saved key of the disabled choice.
    return id != "off";
}

inline bool valid_preset_path(const std::string& path) {
    if (path.empty() || path.find('\\') != std::string::npos) return false;
    const std::filesystem::path relative = utf8_path(path);
    if (relative.is_absolute() || relative.has_root_name() || relative.extension() != ".slangp") return false;
    for (const auto& part : relative) {
        if (part == "..") return false;
    }
    return true;
}

// Invalid entries are skipped and reported, so one bad entry cannot hide the rest.
inline std::vector<Preset> parse_presets(const nlohmann::json& manifest, std::vector<std::string>& errors) {
    std::vector<Preset> presets;
    if (!manifest.is_object() || manifest.value("schema_version", 0) != 1) {
        errors.emplace_back("unsupported shader manifest");
        return presets;
    }

    const auto list = manifest.find("presets");
    if (list == manifest.end() || !list->is_array()) {
        errors.emplace_back("shader manifest has no preset list");
        return presets;
    }

    std::unordered_set<std::string> ids;
    for (const auto& entry : *list) {
        if (!entry.is_object()) {
            errors.emplace_back("shader preset entry is not an object");
            continue;
        }

        Preset preset;
        preset.id = entry.value("id", std::string{});
        preset.label = entry.value("label", std::string{});
        preset.name = entry.value("name", std::string{});
        preset.description = entry.value("description", std::string{});
        preset.path = entry.value("path", std::string{});
        if (!valid_preset_id(preset.id) || preset.label.empty() || preset.name.empty() ||
            !valid_preset_path(preset.path)) {
            errors.emplace_back("invalid shader preset entry '" + preset.id + "'");
            continue;
        }

        if (!ids.insert(preset.id).second) {
            errors.emplace_back("duplicate shader preset id '" + preset.id + "'");
            continue;
        }

        presets.push_back(std::move(preset));
    }

    return presets;
}

inline std::vector<Preset> load_presets(const std::filesystem::path& shader_directory, std::vector<std::string>& errors) {
    std::ifstream stream(shader_directory / "presets.json");
    if (!stream) {
        errors.emplace_back("shader manifest not found");
        return {};
    }

    const nlohmann::json manifest = nlohmann::json::parse(stream, nullptr, false);
    if (manifest.is_discarded()) {
        errors.emplace_back("shader manifest is not valid JSON");
        return {};
    }

    std::vector<Preset> presets = parse_presets(manifest, errors);
    std::vector<Preset> installed;
    for (Preset& preset : presets) {
        if (std::filesystem::is_regular_file(shader_directory / utf8_path(preset.path))) {
            installed.push_back(std::move(preset));
        }
        else {
            errors.emplace_back("shader preset file missing for '" + preset.id + "'");
        }
    }

    return installed;
}

// Menu values: 0 is Off, preset N in the manifest is N + 1.
inline const Preset* preset_for_value(const std::vector<Preset>& presets, uint32_t value) {
    return (value == OffValue || value > presets.size()) ? nullptr : &presets[value - 1];
}

struct ControlState {
    bool library_loaded = false;
    std::string library_message;
    // Set by the renderer when the selected preset could not be compiled or run.
    std::string preset_error;
};

// Short status shown under the preset list; empty while the selection works.
inline std::string preset_status(const std::vector<Preset>& presets, uint32_t value, const ControlState& state) {
    if (!state.library_loaded) {
        return "Unavailable: " + state.library_message;
    }

    const Preset* preset = preset_for_value(presets, value);
    if (preset == nullptr || state.preset_error.empty()) return "";
    return "Could not load " + preset->name + "; showing the unfiltered image. " + state.preset_error;
}

// Plain-text summary of the selected preset for the description column; empty for Off.
inline std::string preset_summary(const std::vector<Preset>& presets, uint32_t value) {
    const Preset* preset = preset_for_value(presets, value);
    if (preset == nullptr) return "";

    return preset->description.empty() ? preset->name : preset->name + ": " + preset->description;
}

// The description column renders RML, and manifest text must not inject markup.
inline std::string escape_markup(const std::string& text) {
    std::string escaped;
    escaped.reserve(text.size());
    for (const char c : text) {
        switch (c) {
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '&': escaped += "&amp;"; break;
            case '"': escaped += "&quot;"; break;
            default: escaped += c; break;
        }
    }
    return escaped;
}

} // namespace wr64::librashader
