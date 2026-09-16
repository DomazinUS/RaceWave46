#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <atomic>

namespace RT64 {
    using Wr64RTDiagnosticSink = void (*)(const char* stage, const char* details);
    inline std::atomic<Wr64RTDiagnosticSink> wr64RTDiagnosticSink{nullptr};

    inline void setWr64RTDiagnosticSink(Wr64RTDiagnosticSink sink) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        wr64RTDiagnosticSink.store(sink, std::memory_order_release);
    }

    inline bool wr64RTDiagnosticEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        return wr64RTDiagnosticSink.load(std::memory_order_acquire) != nullptr;
    }

    // Metadata only; the frontend owns file I/O and the shared session limit.
    inline void wr64RTDiagnostic(const char* stage, const char* details) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (auto sink = wr64RTDiagnosticSink.load(std::memory_order_acquire)) {
            sink(stage, details);
        }
    }
}
