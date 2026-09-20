#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "librecomp/config.hpp"
#include "librecomp/game.hpp"

namespace fs = std::filesystem;
using namespace recomp::config;
using Json = nlohmann::json;

namespace {
fs::path default_directory;
unsigned assertions = 0;

void require(bool condition, const char* description) {
    ++assertions;
    if (!condition) {
        throw std::runtime_error(description);
    }
}

void write_json(const fs::path& path, const Json& value) {
    fs::create_directories(path.parent_path());
    std::ofstream stream(path);
    stream << value.dump(2);
    require(stream.good(), "fixture JSON writes successfully");
}

Json read_json(const fs::path& path) {
    std::ifstream stream(path);
    Json value;
    stream >> value;
    return value;
}

void add_schema(Config& config) {
    config.add_enum_option("mode", "Resolution", "", {{0, "native"}, {1, "scaled"}}, 0u);
    config.add_number_option("scale", "Scale", "", 1, 8, 1, 0, false, 2);
    config.add_bool_option("curvature", "Wave curvature", "", false);
    config.add_string_option("detail", "Curve detail", "", "normal");
    config.add_option_disable_dependency("scale", "mode", 0u);
    config.add_option_hidden_dependency("detail", "curvature", false);
}

bool has_update(const Config& config, size_t index, ConfigOptionUpdateType type) {
    // The runtime API returns a snapshot from a non-const accessor.
    for (const auto& context : const_cast<Config&>(config).get_config_option_updates()) {
        if (context.option_index == index &&
            std::find(context.updates.begin(), context.updates.end(), type) != context.updates.end()) {
            return true;
        }
    }
    return false;
}

void require_reload_updates(Config& config) {
    for (size_t i = 0; i < config.get_config_schema().options.size(); ++i) {
        require(has_update(config, i, ConfigOptionUpdateType::Value), "reload publishes control values");
        require(has_update(config, i, ConfigOptionUpdateType::Hidden), "reload publishes control visibility");
        require(has_update(config, i, ConfigOptionUpdateType::Disabled), "reload publishes control availability");
    }
}

void run(const fs::path& root) {
    default_directory = root / "shared";
    const fs::path usa = root / "usa";
    const fs::path shindou = root / "shindou";
    const fs::path usa_file = usa / "graphics.json";
    const fs::path shindou_file = shindou / "graphics.json";
    const fs::path default_file = default_directory / "graphics.json";
    write_json(default_file, {{"mode", "native"}, {"scale", 3}, {"curvature", false}});
    write_json(usa_file, {{"mode", "scaled"}, {"scale", 4}, {"curvature", true},
        {"future_option", {{"enabled", true}, {"values", {2, 7}}}}});
    const Json untouched_default = read_json(default_file);
    const Json original_usa = read_json(usa_file);

    Config graphics("Graphics", "graphics", true);
    add_schema(graphics);
    unsigned load_calls = 0;
    unsigned option_load_calls = 0;
    unsigned save_calls = 0;
    unsigned permanent_calls = 0;
    unsigned temporary_calls = 0;
    bool expected_curvature = true;
    graphics.set_load_callback([&] { ++load_calls; });
    graphics.set_save_callback([&] { ++save_calls; });
    graphics.add_option_change_callback("mode", [&](auto, auto, OptionChangeContext context) {
        if (context == OptionChangeContext::Load) {
            ++option_load_calls;
            require(std::get<bool>(graphics.get_option_value("curvature")) == expected_curvature,
                "load callback reads a complete new profile");
        } else if (context == OptionChangeContext::Permanent) {
            ++permanent_calls;
        } else {
            ++temporary_calls;
        }
    });

    graphics.set_config_directory(usa);
    require(graphics.load_config(), "USA profile loads");
    require(graphics.id == "graphics", "profile override preserves config identity");
    require(recomp::get_config_path() == default_directory, "profile override preserves global directory");
    require(std::get<double>(graphics.get_option_value("scale")) == 4, "USA saved values load");
    require(!graphics.is_config_option_disabled(1), "USA resolution enables scale");
    require(!graphics.is_config_option_hidden(3), "USA curvature exposes dependent option");
    require(load_calls == 1 && option_load_calls == 1, "initial load calls both callbacks");
    require(graphics.get_config_option_updates().empty(), "initial construction needs no UI reload updates");

    graphics.update_option_value("mode", 0u);
    graphics.update_option_value("scale", 8.0);
    require(graphics.is_dirty(), "USA changes are pending Apply");
    require(read_json(usa_file) == original_usa, "pending edits do not save USA profile");

    expected_curvature = false;
    graphics.set_config_directory(shindou);
    require(graphics.load_config(), "missing Shindou profile loads schema defaults");
    require(!graphics.is_dirty(), "profile switch clears previous pending edits");
    require(std::get<double>(graphics.get_option_value("scale")) == 2, "missing profile receives default scale");
    require(std::get<double>(graphics.get_temp_option_value("scale")) == 2, "missing profile clears temporary scale");
    require(!std::get<bool>(graphics.get_option_value("curvature")), "missing profile receives default curvature");
    require(load_calls == 2 && option_load_calls == 2, "missing profile invokes load callbacks");
    require(graphics.is_config_option_disabled(1), "missing profile recalculates disabled dependency");
    require(graphics.is_config_option_hidden(3), "missing profile recalculates hidden dependency");
    require_reload_updates(graphics);
    require(fs::exists(shindou_file), "new override directory and original file name are created");
    require(read_json(shindou_file).at("scale") == 2, "new file contains defaults");
    require(!read_json(shindou_file).contains("future_option"), "unknown USA settings do not leak to Shindou");
    require(read_json(usa_file) == original_usa, "switching profiles does not write USA pending edits");
    require(read_json(default_file) == untouched_default, "profile loads do not affect shared settings");

    graphics.clear_config_option_updates();
    graphics.update_option_value("mode", 1u);
    graphics.update_option_value("scale", 6.0);
    graphics.update_option_value("curvature", true);
    graphics.revert_temp_config();
    require(!graphics.is_dirty(), "Discard clears edits for active profile");
    require(std::get<double>(graphics.get_temp_option_value("scale")) == 2, "Discard restores active profile values");
    require(graphics.is_config_option_disabled(1), "Discard restores disabled dependency");
    require(graphics.is_config_option_hidden(3), "Discard restores hidden dependency");
    require(read_json(shindou_file).at("scale") == 2, "Discard leaves active file unchanged");

    graphics.update_option_value("mode", 1u);
    graphics.update_option_value("scale", 6.0);
    require(graphics.save_config(), "Apply saves Shindou profile");
    require(!graphics.is_dirty(), "Apply clears active pending edits");
    require(std::get<double>(graphics.get_option_value("scale")) == 6, "Apply commits active values");
    require(read_json(shindou_file).at("scale") == 6, "Apply writes active profile file");
    require(read_json(usa_file) == original_usa, "Apply does not write other edition");
    require(save_calls == 2, "default save and Apply each call save callback");
    require(temporary_calls > 0 && permanent_calls == 1, "Temporary and Permanent callbacks retain semantics");

    // A fullscreen-style shortcut applies only its own option. Its save must
    // not accept another value still awaiting the Graphics Apply button.
    graphics.update_option_value("scale", 8.0);
    graphics.update_option_value("mode", 0u);
    graphics.apply_option_value("mode");
    require(graphics.save_config_json(graphics.get_json_config()), "single-option shortcut saves applied state");
    require(graphics.is_dirty(), "single-option shortcut preserves unrelated pending edits");
    require(std::get<double>(graphics.get_temp_option_value("scale")) == 8, "shortcut preserves temporary scale");
    require(read_json(shindou_file).at("scale") == 6, "shortcut saves only permanent scale");
    require(read_json(shindou_file).at("mode") == "native", "shortcut saves its newly applied option");
    graphics.revert_temp_config();
    require(std::get<uint32_t>(graphics.get_temp_option_value("mode")) == 0u,
        "Discard retains the already applied shortcut value");

    expected_curvature = true;
    graphics.set_config_directory(usa);
    require(graphics.load_config(), "USA reload restores its saved values");
    require(std::get<double>(graphics.get_option_value("scale")) == 4, "USA values stay independent of Shindou Apply");
    require_reload_updates(graphics);
    graphics.update_option_value("scale", 5.0);
    require(graphics.save_config(), "USA Apply succeeds");
    require(read_json(usa_file).at("future_option") == original_usa.at("future_option"),
        "unknown nested JSON values survive Apply");
    require(read_json(shindou_file).at("scale") == 6, "USA Apply leaves Shindou unchanged");

    // Validation rejection must not replace the current state or discard its edits.
    graphics.update_option_value("scale", 7.0);
    const unsigned loads_before_reject = load_calls;
    require(!graphics.load_config([](Json&) { return false; }), "validation callback can reject a load");
    require(graphics.is_dirty() && std::get<double>(graphics.get_temp_option_value("scale")) == 7,
        "rejected load preserves pending state");
    require(load_calls == loads_before_reject, "rejected load does not invoke load callback");
    graphics.revert_temp_config();

    // Empty override restores the ordinary path for this instance only.
    expected_curvature = false;
    graphics.set_config_directory({});
    require(graphics.load_config(), "empty override restores default root");
    require(std::get<double>(graphics.get_option_value("scale")) == 3, "default profile reloads independently");
    graphics.update_option_value("scale", 7.0);
    require(graphics.save_config(), "default profile can still Apply");
    require(read_json(default_file).at("scale") == 7, "empty override saves to normal location");
    require(read_json(usa_file).at("scale") == 5 && read_json(shindou_file).at("scale") == 6,
        "default Apply leaves edition profiles unchanged");

    Config general("General", "general");
    general.add_bool_option("background_input", "Background input", "", true);
    require(general.load_config(), "separate shared Config still uses normal root");
    general.update_option_value("background_input", false);
    require(general.save_config(), "separate shared Config saves independently");
    require(read_json(default_directory / "general.json").at("background_input") == false,
        "separate shared setting saved under its original identity");
    require(!fs::exists(usa / "general.json") && !fs::exists(shindou / "general.json"),
        "override does not redirect other Config instances");

    fs::create_directories(default_directory / "mod_config");
    Config mod;
    mod.set_id("test-mod");
    mod.set_mod_version("1.0.0");
    mod.add_bool_option("enabled", "Enabled", "", true);
    require(mod.load_config(), "ordinary mod defaults still load");
    require(!fs::exists(default_directory / "mod_config" / "test-mod.json"), "missing mod profile is not auto-saved");
    require(mod.save_config(), "ordinary mod config still saves");
    const auto mod_json = read_json(default_directory / "mod_config" / "test-mod.json");
    require(mod_json.at("storage").at("enabled") == true && mod_json.at("mod_id") == "test-mod",
        "ordinary mod path and metadata remain intact");

    // The production backup path remains active when loading an overridden profile.
    write_json(usa_file.string() + ".bak", {{"mode", "scaled"}, {"scale", 8}, {"curvature", true}});
    { std::ofstream broken(usa_file); broken << "{invalid JSON"; }
    expected_curvature = true;
    graphics.set_config_directory(usa);
    require(graphics.load_config(), "overridden profile recovers a valid backup");
    require(std::get<double>(graphics.get_option_value("scale")) == 8, "backup supplies active profile values");

    // Custom parsers, serializers and validation continue to operate on the profile.
    const fs::path custom_path = root / "custom";
    write_json(custom_path / "custom.json", {{"scale", {{"value", 4}}}, {"unknown", 17}});
    Config custom("Custom", "custom");
    custom.add_number_option("scale", "Scale", "", 1, 8, 1, 0, false, 2);
    unsigned parses = 0;
    unsigned serializes = 0;
    custom.on_json_parse_option("scale", [&](const Json& value) -> ConfigValueVariant {
        ++parses;
        return value.at("value").get<double>();
    });
    custom.on_json_serialize_option("scale", [&](const ConfigValueVariant& value) {
        ++serializes;
        return Json{{"value", std::get<double>(value)}};
    });
    custom.set_config_directory(custom_path);
    require(custom.load_config([](Json& value) { value["scale"]["value"] = 6; return true; }),
        "validator can migrate an overridden profile");
    require(parses == 1 && std::get<double>(custom.get_option_value("scale")) == 6,
        "custom parser sees validator migration");
    require(custom.save_config(), "custom serialization saves overridden profile");
    require(serializes == 1 && read_json(custom_path / "custom.json").at("scale").at("value") == 6,
        "custom serialization retains its representation");
    require(read_json(custom_path / "custom.json").at("unknown") == 17, "custom serialization preserves unknown keys");
}
} // namespace

namespace recomp {
fs::path get_config_path() { return default_directory; }
const Version& get_project_version() { static const Version version; return version; }
}

int main(int argc, char** argv) {
    try {
        if (argc != 2) { throw std::runtime_error("usage: config_scope_test <isolated-test-root>"); }
        const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
        const fs::path root = fs::absolute(argv[1]) / std::to_string(nonce);
        run(root);
        std::cout << "PASS: " << assertions << " config profile assertions\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
