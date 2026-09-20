#include "util/asset_paths.h"
#include "RmlUi/Core/URL.h"
#include "RmlUi/Core/SystemInterface.h"
#include "RmlUi/Core/StringUtilities.h"
#include "LogDefault.h"
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <stdexcept>

namespace {
std::vector<std::string> logged_errors;
void check(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
std::string utf8(const std::filesystem::path& path) {
    const auto text = path.generic_u8string();
    return {reinterpret_cast<const char*>(text.data()), text.size()};
}
}

// Only logging is replaced: no graphics backend, window or device is created.
// URL parsing, path joining and binary reads are the production implementations.
namespace Rml {
void Log::Message(Log::Type type, const char* format, ...) {
    char message[4096];
    va_list args;
    va_start(args, format);
    std::vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    if (type == Log::LT_ERROR || type == Log::LT_ASSERT) logged_errors.emplace_back(message);
}
bool LogDefault::LogMessage(Log::Type type, const String& message) {
    if (type == Log::LT_ERROR || type == Log::LT_ASSERT) logged_errors.push_back(message);
    return true;
}
bool Assert(const char* message, const char*, int) {
    throw std::runtime_error(message);
}
}

int main(int argc, char** argv) {
    try {
        check(argc == 2, "Provide an isolated test output directory.");
        namespace fs = std::filesystem;
        using namespace recompui::asset_paths;
        Rml::SystemInterface system;
        Rml::URL parsed;

        // Prove this fixture detects the original Windows source-URL failure.
        check(!parsed.SetURL("D:\\Wave Race\\assets\\"), "Raw Windows source URL unexpectedly accepted.");
        check(!logged_errors.empty(), "Malformed Windows URL was not reported.");
        logged_errors.clear();

        const fs::path drive_path = fs::u8path(u8"D:/Wave Race recomp/assets espa\u00e7o \u6ce2");
        const auto drive_source = directorySourceUrl(drive_path);
        check(drive_source.starts_with("D|/"), "Drive colon was not normalized.");
        check(drive_source.back() == '/', "Directory source is missing its trailing slash.");
        check(directorySourceUrl(drive_path / "") == drive_source, "Existing trailing slash changed resolution.");
        check(parsed.SetURL(drive_source), "Normalized drive URL rejected.");
        check(parsed.GetPath() == drive_source, "RmlUi lost the normalized drive directory.");
        std::string joined;
        system.JoinPath(joined, Rml::StringUtilities::Replace(parsed.GetPath(), '|', ':'), "manual/logo.png");
        check(joined == utf8(drive_path / "manual/logo.png"), "Drive path did not resolve to the asset directory.");
        system.JoinPath(joined, Rml::StringUtilities::Replace(parsed.GetPath(), '|', ':'), "manual/../logo.png");
        check(joined == utf8(drive_path / "logo.png"), "Parent segment was not resolved by real RmlUi JoinPath.");
#ifdef _WIN32
        const fs::path native_drive = fs::u8path(u8"D:\\Wave Race recomp\\assets espa\u00e7o \u6ce2\\");
        check(directorySourceUrl(native_drive) == drive_source, "Native Windows backslashes were not normalized.");
#endif

        const fs::path output = fs::absolute(fs::u8path(argv[1])).lexically_normal();
        const auto unique = std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        const fs::path fixture = output / ("frontend-assets-" + unique);
        check(!fs::exists(fixture), "Refusing to overwrite an existing test fixture.");
        const fs::path asset_dir = fixture / fs::u8path(u8"assets espa\u00e7o \u6ce2");
        fs::create_directories(asset_dir);
        const fs::path image = asset_dir / fs::u8path(u8"imagem \u00e1.png");
        const std::vector<char> expected{char(0x89), 'P', 'N', 'G', '\r', '\n', 0, char(0xff), 'x'};
        {
            std::ofstream stream(image, std::ios::binary);
            stream.write(expected.data(), expected.size());
            check(bool(stream), "Could not write isolated binary fixture.");
        }
        const auto source = directorySourceUrl(asset_dir);
        check(parsed.SetURL(source), "Actual spaced/Unicode directory URL rejected.");
        system.JoinPath(joined, Rml::StringUtilities::Replace(parsed.GetPath(), '|', ':'), utf8(image.filename()));
        std::vector<char> bytes;
        check(readFileTexture(joined, bytes) && bytes == expected, "Production helper did not read exact Unicode-path bytes.");
        check(!readFileTexture(utf8(asset_dir / "missing.png"), bytes) && bytes.empty(), "Missing file retained stale image bytes.");
        bytes = expected;
        check(!readFileTexture("?/game/thumbnail", bytes) && bytes.empty(), "Virtual image key was treated as a file.");
        bytes = expected;
        check(!readFileTexture("", bytes) && bytes.empty(), "Empty source retained stale bytes.");
        const fs::path truncated = asset_dir / "short.png";
        {
            std::ofstream stream(truncated, std::ios::binary);
            stream.write("PNG", 3);
        }
        check(!readFileTexture(utf8(truncated), bytes) && bytes.empty(), "Short file could reach decoder's four-byte signature read.");
        check(logged_errors.empty(), "Valid asset URLs produced RmlUi parser errors.");

        // Remove only the exact files/directories created above, non-recursively.
        fs::remove(image);
        fs::remove(truncated);
        fs::remove(asset_dir);
        fs::remove(fixture);
        std::cout << "Production asset path/read helpers and real RmlUi URL/JoinPath passed.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
