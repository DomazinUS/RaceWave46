#include "./json.h"
#include "json/json.hpp"
#include "librecomp/files.hpp"

using json = nlohmann::json;

bool recompinput::read_json(std::ifstream input_file, json& json_out) {
    if (!input_file.good()) {
        return false;
    }

    try {
        input_file >> json_out;
    }
    catch (json::parse_error&) {
        return false;
    }
    return true;
}

bool recompinput::read_json_with_backups(const std::filesystem::path& path, json& json_out) {
    // Try reading and parsing the base file.
    if (recompinput::read_json(std::ifstream{path}, json_out)) {
        return true;
    }

    // Try reading and parsing the backup file.
    if (recompinput::read_json(recomp::open_input_backup_file(path), json_out)) {
        return true;
    }

    // Both reads failed.
    return false;
}

bool recompinput::save_json_with_backups(const std::filesystem::path& path, const json& json_data) {
    {
        std::ofstream output_file = recomp::open_output_file_with_backup(path);
        if (!output_file.good()) {
            return false;
        }

        output_file << std::setw(4) << json_data;
    }
    return recomp::finalize_output_file_with_backup(path);
}
