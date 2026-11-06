#include "wr64_editions.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
namespace fs = std::filesystem;
unsigned assertions = 0;

void require(bool value, const char* message) {
    ++assertions;
    if (!value) throw std::runtime_error(message);
}

wr64::editions::Options parse(std::vector<std::string> values, const fs::path& runtime = "/profile") {
    std::vector<char*> arguments;
    for (auto& value : values) arguments.push_back(value.data());
    return wr64::editions::parse_options(int(arguments.size()), arguments.data(), runtime);
}

bool rejects(std::vector<std::string> values) {
    try { parse(std::move(values)); }
    catch (const std::runtime_error&) { return true; }
    return false;
}

void setup_options() {
    const auto normal = parse({"game"});
    require(!normal.check_rom && normal.import_rom.empty(), "Setup mode is on without an option");

    const auto check = parse({"game", "--check-rom"});
    require(check.check_rom && check.import_rom.empty() && !check.launch, "--check-rom was not parsed");

    const auto import = parse({"game", "--runtime-dir", "/data/profile", "--import-rom", "/doc/my rom.z64"});
    require(import.import_rom == fs::path("/doc/my rom.z64"), "--import-rom lost its path");
    require(import.runtime == fs::absolute("/data/profile"), "--runtime-dir no longer applies to ROM setup");
    require(!import.check_rom && !import.launch, "--import-rom also selected another mode");

    require(rejects({"game", "--import-rom"}), "--import-rom without a path was accepted");
    require(rejects({"game", "--check-rom", "--import-rom", "rom.z64"}), "Both setup options were accepted");
    require(rejects({"game", "--check-rom", "--launch"}), "ROM setup was combined with --launch");
    require(rejects({"game", "--import-rom", "a.z64", "--rom", "b.z64"}), "ROM setup was combined with --rom");
    require(rejects({"game", "--check-rom", "--seconds", "5"}), "ROM setup was combined with a timed run");
}

#ifdef __linux__
void set(const char* name, const char* value) {
    if (value) setenv(name, value, 1);
    else unsetenv(name);
}

void linux_runtime_directory() {
    set("XDG_DATA_HOME", "/home/player/.var/app/example/data");
    set("HOME", "/home/player");
    require(wr64::editions::default_runtime_directory() == "/home/player/.var/app/example/data/racewave46",
        "XDG_DATA_HOME was not used");
    set("XDG_DATA_HOME", "relative/data");
    require(wr64::editions::default_runtime_directory() == "/home/player/.local/share/racewave46",
        "A relative XDG_DATA_HOME was not ignored as the specification requires");
    set("XDG_DATA_HOME", nullptr);
    require(wr64::editions::default_runtime_directory() == "/home/player/.local/share/racewave46",
        "The XDG default was not used without XDG_DATA_HOME");
    set("HOME", nullptr);
    require(wr64::editions::default_runtime_directory().empty(), "A profile was invented without HOME");

    char name[] = "game";
    char* arguments[] = {name};
    set("XDG_DATA_HOME", "/xdg");
    const auto process = wr64::editions::parse_process_options(1, arguments);
    require(process.runtime == "/xdg/racewave46", "The process default profile is not the XDG directory");
}
#endif
}

int main() {
    try {
        setup_options();
#ifdef __linux__
        linux_runtime_directory();
#endif
        std::cout << assertions << " ROM setup command-line assertions passed\n";
        return EXIT_SUCCESS;
    }
    catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
