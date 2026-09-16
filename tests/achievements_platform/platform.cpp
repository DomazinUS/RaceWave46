#include "wr64_achievements_platform.hpp"
#include <cstdio>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

namespace p = wr64::achievements::platform;
static size_t checks = 0;
static void require(bool success, const char* message) {
    ++checks;
    if (!success) throw std::runtime_error(message);
}
static std::string bytes(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(input), {});
}
static void write(const std::filesystem::path& path, const std::string& data) {
#ifdef _WIN32
    HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
    require(file != INVALID_HANDLE_VALUE, "Fixture encrypted file could not be opened");
    DWORD written = 0;
    const bool success = WriteFile(file, data.data(), DWORD(data.size()), &written, nullptr) &&
        written == data.size() && SetEndOfFile(file);
    CloseHandle(file);
    require(success, "Fixture encrypted file write failed");
#else
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    output.write(data.data(), data.size());
    require(bool(output), "Fixture file write failed");
#endif
}
static void invalid_requests() {
    // All of these are rejected before WinHttpOpen: no external requests.
    const std::vector<std::string> urls{
        "", "http://retroachievements.org/dorequest.php", "https://example.com/",
        "https://retroachievements.org.example.com/", "https://retroachievements.org:444/",
        "https://name@retroachievements.org/", "https://name:password@retroachievements.org/",
        "https://retroachievements.org@other.org/", "https://127.0.0.1/",
        "https://retroachievements.org/#fragment", "https://retroachievements.org/\r\nX: test",
        "https://retroachievements.org.", std::string("https://retroachievements.org/") + std::string(1, '\0') + "test",
        "https://retroachievements.org/" + std::string(8192, 'x'), std::string("https://\xFF")};
    for (const auto& url : urls)
        require(p::http_request(url, "", "", "WR64Fixture/1").status == -1, "Unsafe URL was not rejected locally");
    const std::string valid = "https://retroachievements.org/dorequest.php";
    require(p::http_request(valid, "", "", "").status == -1, "Empty agent accepted");
    require(p::http_request(valid, "", "", "agent\r\nInjected: yes").status == -1, "Header newline accepted");
    require(p::http_request(valid, "x=1", "text/plain\r\nInjected: yes", "test").status == -1, "Content header newline accepted");
    require(p::http_request(valid, "x=1", std::string(1, char(255)), "test").status == -1, "Malformed UTF-8 header accepted");
    require(p::http_request(valid, std::string(1024 * 1024 + 1, 'x'), "", "test").status == -1, "Oversized POST accepted");
}
static void credentials(const std::filesystem::path& root) {
    require(!root.empty(), "Synthetic fixture directory required");
#ifdef _WIN32
    const auto directory = root / ("synthetic-platform-" + std::to_string(GetCurrentProcessId()) + "-" + std::to_string(GetTickCount64()));
    const auto path = directory / "retroachievements.credentials";
    require(!p::load_credentials(directory), "Missing store returned credentials");
    const p::Credentials first{"WR64-Synthetic-Fixture-User", "SYNTHETIC-TOKEN-NOT-A-REAL-ACCOUNT-0123456789"};
    const p::Credentials second{"WR64-Second-Synthetic-User", "SYNTHETIC-REPLACEMENT-TOKEN-NOT-REAL-9876543210"};
    require(p::save_credentials(directory, first), "DPAPI synthetic save failed");
    auto loaded = p::load_credentials(directory);
    require(loaded && loaded->username == first.username && loaded->token == first.token, "DPAPI roundtrip mismatch");
    p::erase_secret(loaded->token);
    const auto encrypted = bytes(path);
    require(!encrypted.empty() && encrypted.size() <= 65536, "Encrypted size bound failed");
    require(encrypted.find(first.username) == std::string::npos && encrypted.find(first.token) == std::string::npos,
        "Plaintext credential persisted");
    require(p::save_credentials(directory, second), "Atomic replacement failed");
    loaded = p::load_credentials(directory);
    require(loaded && loaded->username == second.username && loaded->token == second.token, "Replacement roundtrip mismatch");
    p::erase_secret(loaded->token);
    const auto saved = bytes(path);
    for (const p::Credentials bad : {p::Credentials{"", "test"}, p::Credentials{"user", ""},
        p::Credentials{"user\nheader", "token"}, p::Credentials{"user", "token\r\n"},
        p::Credentials{std::string(257, 'x'), "token"}, p::Credentials{"user", std::string(8193, 'x')}}) {
        require(!p::save_credentials(directory, bad), "Invalid credentials accepted");
        require(bytes(path) == saved, "Rejected save modified existing encrypted credentials");
    }
    HANDLE lock = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    require(lock != INVALID_HANDLE_VALUE, "Fixture could not lock destination");
    const bool locked_saved = p::save_credentials(directory, first);
    CloseHandle(lock);
    require(!locked_saved && bytes(path) == saved, "Failed atomic replacement modified old store");
    for (const auto& entry : std::filesystem::directory_iterator(directory))
        require(entry.path().filename() == path.filename(), "Temporary credential file was not removed");
    auto corrupt = saved;
    corrupt[corrupt.size() / 2] ^= 0x55;
    write(path, corrupt);
    require(!p::load_credentials(directory), "Corrupt DPAPI ciphertext accepted");
    write(path, "WR64RA1-invalid-plaintext");
    require(!p::load_credentials(directory), "Plaintext credential fallback accepted");
    write(path, std::string(65537, 'x'));
    require(!p::load_credentials(directory), "Oversized encrypted store accepted");
    write(path, "");
    require(!p::load_credentials(directory), "Empty credential file accepted");
    require(p::save_credentials(directory, first), "Recovery from invalid store failed");
    p::remove_credentials(directory);
    require(!std::filesystem::exists(path) && !p::load_credentials(directory), "Credential removal failed");
    p::remove_credentials(directory);
    require(!p::save_credentials({}, first), "Empty credential directory accepted");
    require(!p::load_credentials({}), "Empty credential directory returned store");
    require(std::filesystem::remove(directory), "Synthetic fixture directory was not empty");
#else
    require(!p::save_credentials(root, {"synthetic", "synthetic-token"}), "Non-Windows plaintext fallback enabled");
    require(!p::load_credentials(root), "Non-Windows store unexpectedly available");
#endif
    std::string synthetic = "synthetic-secret";
    p::erase_secret(synthetic);
    require(synthetic.empty(), "Secret erase left a logical value");
}
int main(int argc, char** argv) { try {
    require(argc == 2, "Synthetic fixture output root required");
    invalid_requests(); credentials(argv[1]);
    std::printf("PASS achievements platform: %zu checks; local URL/header rejection, synthetic DPAPI, atomic replacement, malformed store rejection. No network requests.\n", checks);
    return 0;
} catch (const std::exception& error) {
    std::fprintf(stderr, "FAIL: %s\n", error.what()); return 1;
} }
