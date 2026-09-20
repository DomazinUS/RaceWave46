#pragma once

#include <filesystem>

// Kept under the established namespace so diagnostics can use the same CLI
// parser. This branch has one USA runtime and no edition selector or child core.
namespace wr64::editions {
struct Options {
    bool launcher = false; // Compatibility with existing offline startup tests.
    bool launch = false;
    bool windowed = false;
    int seconds = 0;
    std::filesystem::path rom;
    std::filesystem::path runtime;
};
Options parse_options(int argc, char** argv, const std::filesystem::path& default_runtime = {});
Options parse_process_options(int argc, char** argv);
// Existing controller diagnostics distinguish a selector from a game process.
bool is_launcher();
bool child_running();
}
