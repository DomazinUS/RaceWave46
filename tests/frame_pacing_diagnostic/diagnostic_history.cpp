#include "common/rt64_wr64_diagnostic_history.h"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

namespace fs = std::filesystem;
static unsigned checks = 0;
static void check(bool success) {
    ++checks;
    if (!success) { std::cerr << "FAIL history check " << checks << '\n'; std::exit(1); }
}
static void write(const fs::path &path, const std::string &data) { std::ofstream(path) << data; }
static std::string read(const fs::path &path) {
    std::ifstream file(path);
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}
int main() {
    const auto root = fs::temp_directory_path() / ("wr64-diagnostic-history-" +
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    check(fs::create_directory(root));
    const auto active = root / "frame-pacing.log";
    std::error_code error;
    check(RT64::wr64ArchiveDiagnosticSession(active, error) && !error && !fs::exists(active));
    for (int session = 1; session <= 12; ++session) {
        const auto content = "gameplay session " + std::to_string(session);
        write(active, content);
        check(RT64::wr64ArchiveDiagnosticSession(active, error) && !error);
        check(read(active) == content);
        for (int prior = 1; prior <= std::min(8, session); ++prior) {
            check(read(root / ("frame-pacing.log.previous-" + std::to_string(prior))) ==
                "gameplay session " + std::to_string(session - prior + 1));
        }
    }
    check(std::distance(fs::directory_iterator(root), fs::directory_iterator()) == 9);

    const auto blocked = root / "blocked.log";
    write(blocked, "critical gameplay trace");
    check(fs::create_directory(root / "blocked.log.previous-1"));
    check(!RT64::wr64ArchiveDiagnosticSession(blocked, error) && bool(error));
    check(read(blocked) == "critical gameplay trace");

    const auto invalid = root / "directory.log";
    check(fs::create_directory(invalid));
    check(!RT64::wr64ArchiveDiagnosticSession(invalid, error) && bool(error));
    check(fs::is_directory(invalid));

    // Remove only individual files and known empty fixture directories, avoiding
    // recursive removal or any path derived from a runtime profile.
    for (const auto &entry : fs::directory_iterator(root)) {
        if (entry.is_regular_file()) check(fs::remove(entry.path()));
    }
    check(fs::remove(root / "blocked.log.previous-1"));
    check(fs::remove(invalid));
    check(fs::remove(root));
    std::cout << "PASS: " << checks << " diagnostic session preservation checks\n";
}
