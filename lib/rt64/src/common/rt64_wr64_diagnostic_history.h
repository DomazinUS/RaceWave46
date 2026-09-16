#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <filesystem>
#include <string>
#include <system_error>

namespace RT64 {
// Preserve evidence before a new launch truncates the active diagnostic. Copy
// instead of moving: a failure leaves the active file available for inspection.
inline bool wr64ArchiveDiagnosticSession(const std::filesystem::path &active,
    std::error_code &error) noexcept {
        if (!WR64_DIAGNOSTIC_ENABLED) return true;
    try {
        error.clear();
        const auto history = [&](unsigned int index) {
            auto path = active;
            path += ".previous-" + std::to_string(index);
            return path;
        };
        const bool hasActive = std::filesystem::exists(active, error);
        if (error || !hasActive) return !error;
        if (!std::filesystem::is_regular_file(active, error)) {
            if (!error) error = std::make_error_code(std::errc::invalid_argument);
            return false;
        }
        for (unsigned int index = 7; index > 0; --index) {
            const auto source = history(index);
            const bool exists = std::filesystem::exists(source, error);
            if (error) return false;
            if (exists) {
                std::filesystem::copy_file(source, history(index + 1),
                    std::filesystem::copy_options::overwrite_existing, error);
                if (error) return false;
            }
        }
        std::filesystem::copy_file(active, history(1),
            std::filesystem::copy_options::overwrite_existing, error);
        return !error;
    } catch (...) {
        error = std::make_error_code(std::errc::io_error);
        return false;
    }
}
} // namespace RT64
