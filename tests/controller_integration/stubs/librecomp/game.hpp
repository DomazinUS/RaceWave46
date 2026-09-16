#pragma once
#include <filesystem>
#include <string>
namespace recomp {
std::filesystem::path get_config_path();
struct Version { std::string to_string() const { return "0.0.0-test"; } };
const Version& get_project_version();
}
