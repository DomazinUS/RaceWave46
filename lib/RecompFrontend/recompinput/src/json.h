#pragma once
#include <filesystem>
#include <fstream>
#include "json/json.hpp"

namespace recompinput {
    bool read_json(std::ifstream input_file, nlohmann::json& json_out);
    bool read_json_with_backups(const std::filesystem::path& path, nlohmann::json& json_out);
    bool save_json_with_backups(const std::filesystem::path& path, const nlohmann::json& json_data);
}
