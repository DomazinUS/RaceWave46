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
    // Setup helpers for external launchers. Both exit before any window,
    // renderer or game thread exists.
    bool check_rom = false;
    std::filesystem::path import_rom;
};
Options parse_options(int argc, char** argv, const std::filesystem::path& default_runtime = {});
Options parse_process_options(int argc, char** argv);
// Profile directory used when --runtime-dir is absent. Windows keeps the
// portable .runtime beside the executable; Linux follows the XDG base
// directory specification ($XDG_DATA_HOME/racewave46).
std::filesystem::path default_runtime_directory();
// Existing controller diagnostics distinguish a selector from a game process.
bool is_launcher();
bool child_running();
}
