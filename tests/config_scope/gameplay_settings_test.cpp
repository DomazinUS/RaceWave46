#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "librecomp/game.hpp"
#include "wr64_gameplay_settings.hpp"

namespace fs = std::filesystem;
using Json = nlohmann::json;
using recomp::config::Config;

namespace {
fs::path default_directory;
unsigned checks = 0;

void require(bool condition, const char* description) {
    ++checks;
    if (!condition) throw std::runtime_error(description);
}

void write_json(const fs::path& path, const Json& value) {
    fs::create_directories(path.parent_path());
    std::ofstream file(path);
    file << value.dump(2);
    require(file.good(), "fixture JSON writes");
}

std::string bytes(const fs::path& path) {
    std::ifstream file(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(file), {});
}

Json read_json(const fs::path& path) { return Json::parse(bytes(path)); }

void add_schema(Config& general) {
    general.add_bool_option("gameplay_rumble", "Gameplay rumble", "", true);
    general.add_bool_option("show_ghost", "Show Time Trial ghost", "", true);
    general.add_number_option("rumble_strength", "Rumble strength", "", 0, 100, 1, 0, true, 25);
}

void check_values(Config& general, bool rumble, bool ghost) {
    require(std::get<bool>(general.get_option_value("gameplay_rumble")) == rumble,
        "rumble choice preserved");
    require(std::get<bool>(general.get_option_value("show_ghost")) == ghost,
        "ghost choice preserved");
}

void exercise_case(const fs::path& root, const Json& legacy, const Json* initial,
    bool expected_rumble, bool expected_ghost, bool broken_primary = false) {
    fs::create_directories(root);
    const auto legacy_file = root / "enhancements.json";
    write_json(legacy_file, legacy);
    const auto legacy_bytes = bytes(legacy_file);
    const auto general_file = root / "general.json";
    if (initial) {
        write_json(broken_primary ? fs::path(general_file.string() + ".bak") : general_file, *initial);
        if (broken_primary) { std::ofstream file(general_file); file << "{ malformed"; }
    }

    Config general("General", "general", false);
    general.set_config_directory(root);
    add_schema(general);
    bool published_rumble = true;
    bool published_ghost = true;
    general.add_option_change_callback("gameplay_rumble", [&](auto value, auto, auto) {
        published_rumble = std::get<bool>(value);
    });
    general.add_option_change_callback("show_ghost", [&](auto value, auto, auto) {
        published_ghost = std::get<bool>(value);
    });

    require(wr64::frontend::load_general_gameplay_settings(general, read_json(legacy_file)),
        "migration succeeds");
    check_values(general, expected_rumble, expected_ghost);
    require(published_rumble == expected_rumble && published_ghost == expected_ghost,
        "runtime callbacks publish migrated choices");
    if (initial && initial->contains("unknown")) {
        require(general.get_json_config().at("unknown") == initial->at("unknown"),
            "unknown General JSON preserved in memory");
        // With no migration needed, the original primary may still be malformed;
        // the valid .bak remains the authority until the normal save.
        const auto primary = Json::parse(bytes(general_file), nullptr, false);
        const auto persisted = primary.is_object() ? primary : read_json(general_file.string() + ".bak");
        require(persisted.at("unknown") == initial->at("unknown"),
            "unknown General JSON preserved on disk");
    }
    require(bytes(legacy_file) == legacy_bytes, "legacy Enhancements file is unchanged");

    require(general.load_config(), "finalize reload succeeds");
    check_values(general, expected_rumble, expected_ghost);
    require(general.save_config(), "normal tab-close save succeeds");
    const auto saved = bytes(general_file);
    const auto backup = bytes(general_file.string() + ".bak");
    Json reversed = legacy;
    reversed["gameplay_rumble"] = !expected_rumble;
    reversed["show_ghost"] = !expected_ghost;
    require(wr64::frontend::load_general_gameplay_settings(general, reversed),
        "second migration succeeds");
    check_values(general, expected_rumble, expected_ghost);
    require(bytes(general_file) == saved && bytes(general_file.string() + ".bak") == backup,
        "migration is idempotent and explicit General values stay authoritative");
    require(bytes(legacy_file) == legacy_bytes, "legacy remains unchanged after reload");
}

void run(const fs::path& root) {
    default_directory = root / "unused-global-profile";
    unsigned case_id = 0;
    const auto next = [&] { return root / std::to_string(case_id++); };
    for (const bool rumble : {false, true}) for (const bool ghost : {false, true}) {
        Json legacy = {{"gameplay_rumble", rumble}, {"show_ghost", ghost}, {"water_reflections", "Rasterized"}};
        exercise_case(next(), legacy, nullptr, rumble, ghost);
        Json absent = {{"rumble_strength", 42}, {"unknown", {{"future", {1, 2, 3}}}}};
        exercise_case(next(), legacy, &absent, rumble, ghost);
        exercise_case(next(), legacy, &absent, rumble, ghost, true);
        Json invalid = absent;
        invalid["gameplay_rumble"] = "false";
        invalid["show_ghost"] = 0;
        exercise_case(next(), legacy, &invalid, rumble, ghost);
        Json one_explicit = absent;
        one_explicit["gameplay_rumble"] = !rumble;
        exercise_case(next(), legacy, &one_explicit, !rumble, ghost);
        one_explicit = absent;
        one_explicit["show_ghost"] = !ghost;
        exercise_case(next(), legacy, &one_explicit, rumble, !ghost);
        for (const bool current_rumble : {false, true}) for (const bool current_ghost : {false, true}) {
            Json explicit_values = absent;
            explicit_values["gameplay_rumble"] = current_rumble;
            explicit_values["show_ghost"] = current_ghost;
            exercise_case(next(), legacy, &explicit_values, current_rumble, current_ghost);
        }
    }
    for (const Json legacy : {Json::object(), Json{{"gameplay_rumble", "false"}, {"show_ghost", 0}}, Json(nullptr)}) {
        exercise_case(next(), legacy, nullptr, true, true);
        Json absent = {{"unknown", "retained"}};
        exercise_case(next(), legacy, &absent, true, true);
    }

    // Valid JSON with an invalid root must be rejected without overwriting it.
    for (const Json invalid : {Json(7), Json::array(), Json(nullptr)}) {
        const auto directory = next();
        const auto file = directory / "general.json";
        write_json(file, invalid);
        const auto original = bytes(file);
        Config general("General", "general", false);
        general.set_config_directory(directory);
        add_schema(general);
        require(!wr64::frontend::load_general_gameplay_settings(general, Json::object()),
            "nonobject General profile rejected");
        require(bytes(file) == original, "rejected General profile untouched");
    }

    // A directory override that is itself a file must report the final save error.
    const auto blocked_directory = next();
    { std::ofstream file(blocked_directory); file << "not a directory"; }
    Config blocked("General", "general", false);
    blocked.set_config_directory(blocked_directory);
    add_schema(blocked);
    require(!wr64::frontend::load_general_gameplay_settings(blocked, Json::object()),
        "fresh-profile write failure propagates");
    require(!fs::exists(default_directory), "isolated tests never access global profiles");
}
} // namespace

namespace recomp {
fs::path get_config_path() { return default_directory; }
const Version& get_project_version() { static const Version version; return version; }
}

int main(int argc, char** argv) {
    try {
        if (argc != 2) throw std::runtime_error("expected isolated test root");
        const auto nonce = std::chrono::steady_clock::now().time_since_epoch().count();
        run(fs::absolute(argv[1]) / std::to_string(nonce));
        std::cout << "PASS: " << checks << " gameplay settings migration checks\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
