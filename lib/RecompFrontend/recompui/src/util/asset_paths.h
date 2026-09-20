#pragma once

#include <algorithm>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

namespace recompui::asset_paths {

// RmlUi's URL parser treats a colon as the start of a protocol. Its native
// Windows path convention uses a pipe for the drive separator until JoinPath
// converts it back for filesystem access. Keep UTF-8 and the trailing slash
// so relative images resolve within this directory, including portable builds.
inline std::string directorySourceUrl(const std::filesystem::path& directory) {
    const auto utf8 = directory.generic_u8string();
    std::string source(reinterpret_cast<const char*>(utf8.data()), utf8.size());
    std::replace(source.begin(), source.end(), ':', '|');
    if (!source.empty() && source.back() != '/') source.push_back('/');
    return source;
}

// The renderer also accepts virtual ?/... image names registered from memory.
// Those never refer to files. Ordinary sources reach here after RmlUi has
// resolved their path; u8path preserves non-ASCII installation directories on
// Windows rather than interpreting UTF-8 bytes through the ANSI code page.
inline bool readFileTexture(std::string_view source, std::vector<char>& bytes) {
    bytes.clear();
    if (source.empty() || source.front() == '?') return false;
    try {
        std::ifstream stream(std::filesystem::u8path(source.begin(), source.end()),
            std::ios::binary | std::ios::ate);
        if (!stream) return false;
        const auto length = stream.tellg();
        // TextureCache reads a four-byte PNG/DDS signature before decoding.
        if (length < std::streampos(4)) return false;
        const auto count = static_cast<std::streamoff>(length);
        if (count > (std::numeric_limits<std::streamsize>::max)() ||
            static_cast<std::uintmax_t>(count) > bytes.max_size()) return false;
        bytes.resize(static_cast<size_t>(count));
        stream.seekg(0, std::ios::beg);
        stream.read(bytes.data(), static_cast<std::streamsize>(count));
        if (!stream || stream.gcount() != count) {
            bytes.clear();
            return false;
        }
        return true;
    } catch (const std::exception&) {
        bytes.clear();
        return false;
    }
}

} // namespace recompui::asset_paths
