#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace RT64 {
    namespace Wr64DiagnosticSkyShader {
        constexpr size_t MaxBytes = 16 * 1024 * 1024;

        inline bool flag(const char *value) {
            return value && value[0] == '1' && value[1] == '\0';
        }

        [[noreturn]] inline void fail(const char *reason, const char *file = "none") {
            std::fprintf(stderr, "[d3d12-diagnostic] sky_shader_override_error=1 reason=%s file=%s\n", reason, file);
            std::fflush(stderr);
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            std::_Exit(1);
        }

        inline uint32_t word(const std::vector<uint8_t> &bytes, size_t offset) {
            return uint32_t(bytes[offset]) | (uint32_t(bytes[offset + 1]) << 8) |
                (uint32_t(bytes[offset + 2]) << 16) | (uint32_t(bytes[offset + 3]) << 24);
        }

        // Structural checks only; DXC and the driver validate the DXIL program.
        inline bool validContainer(const std::vector<uint8_t> &bytes) {
            if (bytes.size() < 36 || bytes.size() > MaxBytes || std::memcmp(bytes.data(), "DXBC", 4) ||
                word(bytes, 20) != 1 || word(bytes, 24) != bytes.size()) return false;
            const uint32_t count = word(bytes, 28);
            if (count == 0 || count > 256 || size_t(count) * 4 > bytes.size() - 32) return false;
            const size_t tableEnd = 32 + size_t(count) * 4;
            std::array<std::array<size_t, 2>, 256> ranges{};
            bool dxil = false;
            for (uint32_t i = 0; i < count; ++i) {
                const size_t start = word(bytes, 32 + size_t(i) * 4);
                if ((start & 3) || start < tableEnd || start > bytes.size() - 8) return false;
                const size_t size = word(bytes, start + 4);
                if (size > bytes.size() - start - 8) return false;
                const size_t end = start + 8 + size;
                for (uint32_t j = 0; j < i; ++j)
                    if (start < ranges[j][1] && end > ranges[j][0]) return false;
                ranges[i] = {start, end};
                if (std::memcmp(bytes.data() + start, "DXIL", 4) == 0) {
                    if (dxil || size < 28) return false;
                    const size_t program = start + 8;
                    // This override replaces PSMain compiled as ps_6_5 only.
                    if (word(bytes, program) != 0x65 || uint64_t(word(bytes, program + 4)) * 4 != size ||
                        std::memcmp(bytes.data() + program + 8, "DXIL", 4)) return false;
                    const size_t bitcodeOffset = word(bytes, program + 16);
                    const size_t bitcodeSize = word(bytes, program + 20);
                    if (bitcodeOffset < 16 || bitcodeOffset > size - 8 || bitcodeSize < 4 ||
                        bitcodeSize > size - 8 - bitcodeOffset ||
                        word(bytes, program + 8 + bitcodeOffset) != 0xDEC04342) return false;
                    dxil = true;
                }
            }
            return dxil;
        }

        inline uint64_t fingerprint(const std::vector<uint8_t> &bytes) {
            uint64_t hash = 14695981039346656037ull;
            for (uint8_t byte : bytes) hash = (hash ^ byte) * 1099511628211ull;
            return hash;
        }

        struct Request { bool enabled = false; std::filesystem::path directory; };

        inline const Request &request() {
            static const Request value = [] {
                Request result;
                if (!flag(std::getenv("WR64_D3D12_DIAGNOSTICS"))) return result;
#ifdef _WIN32
                const wchar_t *directory = _wgetenv(L"WR64_D3D12_SKY_SHADER_DIR");
#else
                const char *directory = std::getenv("WR64_D3D12_SKY_SHADER_DIR");
#endif
                if (!directory || !directory[0]) return result;
                if (flag(std::getenv("WR64_D3D12_DIAGNOSTIC_NO_SKY"))) fail("conflicts_with_no_sky");
                try { result.directory = directory; }
                catch (...) { fail("invalid_directory"); }
                result.enabled = true;
                return result;
            }();
            return value;
        }

        struct Pair { std::vector<uint8_t> single, ms; };

        inline std::vector<uint8_t> read(const std::filesystem::path &directory, const char *filename) {
            try {
                std::ifstream file(directory / filename, std::ios::binary | std::ios::ate);
                if (!file) fail("cannot_open", filename);
                const auto length = file.tellg();
                if (length < 36 || length > std::streamoff(MaxBytes)) fail("invalid_size", filename);
                std::vector<uint8_t> bytes(static_cast<size_t>(length));
                file.seekg(0);
                if (!file.read(reinterpret_cast<char *>(bytes.data()), std::streamsize(bytes.size())))
                    fail("cannot_read", filename);
                if (!validContainer(bytes)) fail("invalid_dxil_container", filename);
                return bytes;
            }
            catch (...) { fail("file_read_exception", filename); }
        }

        inline const Pair &pair(const std::filesystem::path &directory) {
            static const Pair value = [&] {
                Pair result;
                result.single = read(directory, "sky-single.dxil");
                result.ms = read(directory, "sky-ms.dxil");
                return result;
            }();
            return value;
        }
    }

    inline const std::vector<uint8_t> *wr64D3D12DiagnosticSkyShader(bool dxil, bool world, bool sky, bool ms) {
        if (!dxil || world) return nullptr;
        const auto &request = Wr64DiagnosticSkyShader::request();
        if (!request.enabled || !sky) return nullptr;
        const auto &pair = Wr64DiagnosticSkyShader::pair(request.directory);
        const auto &bytes = ms ? pair.ms : pair.single;
        std::fprintf(stderr, "[d3d12-diagnostic] sky_shader_override=1 variant=%s file=%s bytes=%zu fnv64=%016llx\n",
            ms ? "ms" : "single", ms ? "sky-ms.dxil" : "sky-single.dxil", bytes.size(),
            static_cast<unsigned long long>(Wr64DiagnosticSkyShader::fingerprint(bytes)));
        std::fflush(stderr);
        return &bytes;
    }
}
