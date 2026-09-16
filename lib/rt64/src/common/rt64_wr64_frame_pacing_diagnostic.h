#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>

namespace RT64 {
    // Numeric, bounded evidence only. The frontend owns the file and line cap;
    // neither producer performs per-frame file I/O or allocates a history.
    using Wr64FramePacingDiagnosticSink = void (*)(const char *, const char *) noexcept;
    inline std::atomic<Wr64FramePacingDiagnosticSink> wr64FramePacingDiagnosticSink{nullptr};
    inline std::atomic_uint64_t wr64FramePacingDiagnosticGeneration{0};

    inline void setWr64FramePacingDiagnosticSink(Wr64FramePacingDiagnosticSink sink) noexcept {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        wr64FramePacingDiagnosticSink.store(sink, std::memory_order_release);
        wr64FramePacingDiagnosticGeneration.fetch_add(1, std::memory_order_release);
    }

    inline bool wr64FramePacingDiagnosticEnabled() noexcept {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        return wr64FramePacingDiagnosticSink.load(std::memory_order_acquire) != nullptr;
    }

    struct Wr64FramePacingRenderSample {
        double gpuMs = 0;
        uint32_t width = 0, height = 0, viOriginalRate = 0, targetRate = 0, samples = 1;
        bool reflections = false, shadows = false;
    };

    struct Wr64FramePacingPresentSample {
        double intervalMs = 0, presentMs = 0, swapWaitMs = 0;
        uint32_t width = 0, height = 0, refreshRate = 0, targetRate = 0;
        uint32_t viOriginalRate = 0, pendingPresents = 0;
        bool displayPaced = false, d3d12 = false, success = false;
        uint32_t batchFrames = 0, framesToPresent = 0;
    };

    namespace Wr64FramePacingDiagnosticDetail {
        constexpr double ReportIntervalMs = 2000.0;

        struct Metric {
            double total = 0, maximum = 0;
            uint64_t count = 0;
            void add(double value, bool allowZero = true) noexcept {
                if (!std::isfinite(value) || value < 0 || (!allowZero && value == 0)) return;
                total += value;
                maximum = std::max(maximum, value);
                ++count;
            }
            double average() const noexcept { return count ? total / double(count) : 0; }
        };

        inline double clockMs() noexcept {
            return std::chrono::duration<double, std::milli>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
        }

        inline double budgetMs(uint32_t targetRate, uint32_t nativeRate) noexcept {
            const uint32_t rate = targetRate ? targetRate : nativeRate;
            return rate ? 1000.0 / double(rate) : 0;
        }

        struct RenderWindow {
            bool started = false;
            double startMs = 0;
            Wr64FramePacingRenderSample config{};
            Metric gpu{};
            uint64_t count = 0, overBudget = 0, configChanges = 0;
            uint32_t widthMax = 0, heightMax = 0;

            bool sameConfig(const Wr64FramePacingRenderSample &s) const noexcept {
                return config.width == s.width && config.height == s.height &&
                    config.viOriginalRate == s.viOriginalRate && config.targetRate == s.targetRate &&
                    config.samples == s.samples && config.reflections == s.reflections && config.shadows == s.shadows;
            }

            void report(double nowMs, const char *reason, Wr64FramePacingDiagnosticSink sink) const noexcept {
                if (!sink || !count) return;
                char row[768];
                std::snprintf(row, sizeof(row),
                    "reason=%s span_ms=%.1f passes=%llu config_changes=%llu backing_max=%ux%u native_hz=%u target_hz=%u msaa=%u "
                    "rt_reflections=%u rt_shadows=%u gpu_samples=%llu gpu_avg_ms=%.3f gpu_max_ms=%.3f "
                    "budget_ms=%.3f gpu_over_budget=%llu",
                    reason, std::max(0.0, nowMs - startMs), static_cast<unsigned long long>(count),
                    static_cast<unsigned long long>(configChanges), widthMax, heightMax,
                    config.viOriginalRate, config.targetRate, config.samples,
                    unsigned(config.reflections), unsigned(config.shadows), static_cast<unsigned long long>(gpu.count),
                    gpu.average(), gpu.maximum, budgetMs(config.targetRate, config.viOriginalRate),
                    static_cast<unsigned long long>(overBudget));
                sink("render", row);
            }

            void add(const Wr64FramePacingRenderSample &s, double nowMs, Wr64FramePacingDiagnosticSink sink) noexcept {
                if (!sink || !std::isfinite(nowMs)) return;
                if (started && nowMs < startMs) *this = {};
                if (started && !sameConfig(s)) ++configChanges;
                if (!started) { started = true; startMs = nowMs; config = s; }
                config = s;
                ++count;
                widthMax = std::max(widthMax, s.width); heightMax = std::max(heightMax, s.height);
                gpu.add(s.gpuMs);
                const double budget = budgetMs(s.targetRate, s.viOriginalRate);
                if (budget > 0 && std::isfinite(s.gpuMs) && s.gpuMs > budget) ++overBudget;
                if (nowMs - startMs >= ReportIntervalMs) {
                    report(nowMs, "interval", sink);
                    *this = {};
                }
            }
        };

        struct PresentWindow {
            bool started = false;
            double startMs = 0;
            Wr64FramePacingPresentSample config{};
            Metric interval{}, present{}, swapWait{};
            uint64_t count = 0, failures = 0, longIntervals = 0, configChanges = 0;
            uint32_t pendingMax = 0, batchMin = UINT32_MAX, batchMax = 0;
            uint32_t framesMin = UINT32_MAX, framesMax = 0;

            bool sameConfig(const Wr64FramePacingPresentSample &s) const noexcept {
                return config.width == s.width && config.height == s.height &&
                    config.refreshRate == s.refreshRate && config.targetRate == s.targetRate &&
                    config.viOriginalRate == s.viOriginalRate && config.displayPaced == s.displayPaced &&
                    config.d3d12 == s.d3d12;
            }

            void report(double nowMs, const char *reason, Wr64FramePacingDiagnosticSink sink) const noexcept {
                if (!sink || !count) return;
                char row[1024];
                std::snprintf(row, sizeof(row),
                    "reason=%s span_ms=%.1f attempts=%llu config_changes=%llu output=%ux%u display_hz=%u target_hz=%u native_hz=%u "
                    "d3d12=%u display_paced=%u interval_samples=%llu interval_avg_ms=%.3f interval_max_ms=%.3f "
                    "present_avg_ms=%.3f present_max_ms=%.3f swap_wait_avg_ms=%.3f swap_wait_max_ms=%.3f "
                    "budget_ms=%.3f intervals_over_1_5_budget=%llu pending_max=%u batch_frames=%u..%u "
                    "frames_to_present=%u..%u failures=%llu",
                    reason, std::max(0.0, nowMs - startMs), static_cast<unsigned long long>(count),
                    static_cast<unsigned long long>(configChanges), config.width, config.height,
                    config.refreshRate, config.targetRate, config.viOriginalRate,
                    unsigned(config.d3d12), unsigned(config.displayPaced), static_cast<unsigned long long>(interval.count),
                    interval.average(), interval.maximum, present.average(), present.maximum, swapWait.average(),
                    swapWait.maximum, budgetMs(config.targetRate, config.viOriginalRate),
                    static_cast<unsigned long long>(longIntervals), pendingMax, batchMin, batchMax,
                    framesMin, framesMax, static_cast<unsigned long long>(failures));
                sink("present", row);
            }

            void add(const Wr64FramePacingPresentSample &s, double nowMs, Wr64FramePacingDiagnosticSink sink) noexcept {
                if (!sink || !std::isfinite(nowMs)) return;
                if (started && nowMs < startMs) *this = {};
                const bool changed = started && !sameConfig(s);
                if (changed) ++configChanges;
                if (!started) { started = true; startMs = nowMs; config = s; }
                config = s;
                ++count;
                failures += s.success ? 0 : 1;
                // The interval spanning a fullscreen/configuration transition
                // belongs to neither steady mode. Keep call/wait timing, omit it.
                if (!changed) interval.add(s.intervalMs, false);
                present.add(s.presentMs);
                swapWait.add(s.swapWaitMs);
                const double budget = budgetMs(s.targetRate, s.viOriginalRate);
                if (!changed && budget > 0 && std::isfinite(s.intervalMs) && s.intervalMs > 1.5 * budget) ++longIntervals;
                pendingMax = std::max(pendingMax, s.pendingPresents);
                batchMin = std::min(batchMin, s.batchFrames); batchMax = std::max(batchMax, s.batchFrames);
                framesMin = std::min(framesMin, s.framesToPresent); framesMax = std::max(framesMax, s.framesToPresent);
                if (nowMs - startMs >= ReportIntervalMs) { report(nowMs, "interval", sink); *this = {}; }
            }
        };

        template <typename Window> struct SessionWindow {
            uint64_t generation = UINT64_MAX;
            Window window{};
            void resetForSession() noexcept {
                const uint64_t next = wr64FramePacingDiagnosticGeneration.load(std::memory_order_acquire);
                if (generation != next) { window = {}; generation = next; }
            }
        };
    }

    inline void wr64RecordFramePacingRender(const Wr64FramePacingRenderSample &sample) noexcept {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        const auto sink = wr64FramePacingDiagnosticSink.load(std::memory_order_acquire);
        if (!sink) return;
        static thread_local Wr64FramePacingDiagnosticDetail::SessionWindow<Wr64FramePacingDiagnosticDetail::RenderWindow> state;
        state.resetForSession();
        state.window.add(sample, Wr64FramePacingDiagnosticDetail::clockMs(), sink);
    }

    inline void wr64RecordFramePacingPresent(const Wr64FramePacingPresentSample &sample) noexcept {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        const auto sink = wr64FramePacingDiagnosticSink.load(std::memory_order_acquire);
        if (!sink) return;
        static thread_local Wr64FramePacingDiagnosticDetail::SessionWindow<Wr64FramePacingDiagnosticDetail::PresentWindow> state;
        state.resetForSession();
        state.window.add(sample, Wr64FramePacingDiagnosticDetail::clockMs(), sink);
    }
}
