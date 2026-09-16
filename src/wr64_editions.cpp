#include "wr64_editions.hpp"

#include <charconv>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#endif

namespace wr64::editions {
namespace {
#ifdef _WIN32
std::filesystem::path executable_path() {
    std::wstring path(32768, L'\0');
    const auto length = GetModuleFileNameW(nullptr, path.data(), DWORD(path.size()));
    if (length == 0 || length >= path.size()) throw std::runtime_error("Cannot locate the game executable.");
    path.resize(length);
    return path;
}
#endif
}

Options parse_process_options(int argc, char** argv) {
#ifdef _WIN32
    int count = 0;
    auto wide = CommandLineToArgvW(GetCommandLineW(), &count);
    if (!wide) throw std::runtime_error("Cannot read Windows command-line arguments.");
    std::vector<std::string> strings;
    try {
        strings.reserve(count);
        for (int index = 0; index < count; ++index) {
            const int bytes = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wide[index], -1, nullptr, 0, nullptr, nullptr);
            if (bytes <= 0) throw std::runtime_error("Invalid Unicode command-line argument.");
            std::string value(bytes, '\0');
            WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wide[index], -1, value.data(), bytes, nullptr, nullptr);
            value.pop_back();
            strings.push_back(std::move(value));
        }
    } catch (...) { LocalFree(wide); throw; }
    LocalFree(wide);
    std::vector<char*> arguments;
    for (auto& value : strings) arguments.push_back(value.data());
    // A direct EXE launch and a shortcut must use the same portable profile,
    // regardless of the caller's working directory. Explicit CLI paths still
    // resolve from that directory, so existing diagnostic launches retain it.
    return parse_options(count, arguments.data(), executable_path().parent_path() / ".runtime");
#else
    return parse_options(argc, argv);
#endif
}

Options parse_options(int argc, char** argv, const std::filesystem::path& default_runtime) {
    Options result;
    result.runtime = std::filesystem::absolute(default_runtime.empty() ? std::filesystem::path(".runtime") : default_runtime);
    auto argument = [&](int& index) {
        if (++index >= argc) throw std::runtime_error("Missing value after command-line option.");
        return std::string(argv[index]);
    };
    for (int i = 1; i < argc; ++i) {
        const std::string item = argv[i];
        // Older diagnostic scripts use --core; this executable is always the USA core.
        if (item == "--core") continue;
        else if (item == "--launch") { result.launch = true; result.launcher = false; }
        else if (item == "--runtime-dir") result.runtime = std::filesystem::absolute(std::filesystem::u8path(argument(i)));
        else if (item == "--rom") result.rom = std::filesystem::u8path(argument(i));
        else if (item == "--windowed") result.windowed = true;
        else if (item == "--seconds") {
            const auto value = argument(i);
            const auto parsed = std::from_chars(value.data(), value.data() + value.size(), result.seconds);
            if (parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size() || result.seconds < 0)
                throw std::runtime_error("Invalid run duration.");
        }
        else if (i == 1 && !item.starts_with("--")) {
            result.rom = std::filesystem::u8path(item);
            result.launcher = false;
            if (i + 1 < argc && !std::string_view(argv[i + 1]).starts_with("--")) {
                const auto value = argument(i);
                const auto parsed = std::from_chars(value.data(), value.data() + value.size(), result.seconds);
                if (parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size() || result.seconds < 0)
                    throw std::runtime_error("Invalid run duration.");
            }
        }
        else throw std::runtime_error("Unknown option: " + item);
    }
    if (result.seconds > 0) { result.launch = true; result.launcher = false; }
    return result;
}

bool is_launcher() { return false; }
bool child_running() { return false; }
}
