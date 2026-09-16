#include "common/rt64_wr64_frame_pacing_diagnostic.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace {
    using namespace RT64;
    using namespace RT64::Wr64FramePacingDiagnosticDetail;
    std::mutex rowsMutex;
    std::vector<std::string> rows;
    unsigned checks = 0;

    void expect(bool okay, const char *message) {
        ++checks;
        if (!okay) { std::cerr << "FAIL: " << message << '\n'; std::exit(1); }
    }
    void capture(const char *kind, const char *text) noexcept {
        try { std::lock_guard lock(rowsMutex); rows.push_back(std::string(kind) + " " + text); }
        catch (...) { std::abort(); }
    }
    bool contains(const std::string &text, const char *part) { return text.find(part) != std::string::npos; }
    Wr64FramePacingRenderSample renderSample() {
        Wr64FramePacingRenderSample sample;
        sample.width = 1280; sample.height = 720; sample.viOriginalRate = 20;
        sample.targetRate = 180; sample.samples = 4; sample.reflections = true; sample.shadows = true;
        return sample;
    }
    Wr64FramePacingPresentSample presentSample() {
        Wr64FramePacingPresentSample sample;
        sample.width = 1280; sample.height = 720; sample.viOriginalRate = 20;
        sample.targetRate = 60; sample.refreshRate = 180; sample.success = true;
        sample.d3d12 = true; sample.displayPaced = false;
        sample.batchFrames = 3; sample.framesToPresent = 3;
        return sample;
    }

    void renderAggregates() {
        rows.clear();
        RenderWindow window;
        auto sample = renderSample();
        sample.gpuMs = 2;
        window.add(sample, 0, capture);
        sample.gpuMs = 4; sample.width = 2560; sample.height = 1440;
        window.add(sample, 1000, capture);
        expect(rows.empty(), "no immediate I/O at a configuration transition");
        sample.gpuMs = 10;
        window.add(sample, 2000, capture);
        expect(rows.size() == 1, "one render row at two seconds");
        expect(contains(rows[0], "passes=3"), "all GPU passes counted");
        expect(contains(rows[0], "config_changes=1"), "mixed configuration explicitly identified");
        expect(contains(rows[0], "backing_max=2560x1440"), "largest real backing target preserved");
        expect(contains(rows[0], "gpu_avg_ms=5.333 gpu_max_ms=10.000"), "GPU average and maximum correct");
        expect(contains(rows[0], "budget_ms=5.556 gpu_over_budget=1"), "native interpolation budget overshoot counted");
        expect(contains(rows[0], "rt_reflections=1 rt_shadows=1"), "render effect scopes reported");
        expect(!window.started && window.count == 0, "completed window reset");
        window.add(sample, 2001, capture);
        window.add(sample, 4000, capture);
        expect(rows.size() == 1, "next window does not reuse old start time");
        window.add(sample, 4001, capture);
        expect(rows.size() == 2, "next window flushes independently");
    }

    void presentAggregates() {
        rows.clear();
        PresentWindow window;
        auto sample = presentSample();
        sample.intervalMs = 0; sample.presentMs = 0.1; sample.swapWaitMs = 0.2;
        window.add(sample, 0, capture);
        sample.intervalMs = 16; sample.presentMs = 0.2; sample.swapWaitMs = 0.4; sample.pendingPresents = 2;
        window.add(sample, 1000, capture);
        sample.intervalMs = 34; sample.presentMs = 0.3; sample.swapWaitMs = 0.6;
        sample.success = false; sample.framesToPresent = 2;
        window.add(sample, 2000, capture);
        expect(rows.size() == 1, "one present row at two seconds");
        expect(contains(rows[0], "attempts=3"), "failed presentation attempts remain in report");
        expect(contains(rows[0], "interval_samples=2 interval_avg_ms=25.000 interval_max_ms=34.000"), "unavailable first interval excluded");
        expect(contains(rows[0], "present_avg_ms=0.200 present_max_ms=0.300"), "Present duration separate from frame interval");
        expect(contains(rows[0], "swap_wait_avg_ms=0.400 swap_wait_max_ms=0.600"), "swapchain wait duration separately recorded");
        expect(contains(rows[0], "intervals_over_1_5_budget=1 pending_max=2"), "slow present interval and queue peak detected");
        expect(contains(rows[0], "batch_frames=3..3 frames_to_present=2..3 failures=1"), "present counts and failure count retained");

        rows.clear();
        window = {};
        sample = presentSample(); sample.intervalMs = 16;
        window.add(sample, 0, capture);
        sample.width = 2560; sample.height = 1440; sample.intervalMs = 200;
        window.add(sample, 500, capture);
        expect(rows.empty(), "fullscreen transition cannot force per-frame output");
        sample.intervalMs = 17;
        window.add(sample, 2000, capture);
        expect(rows.size() == 1 && contains(rows[0], "config_changes=1 output=2560x1440"), "fullscreen transition tagged with latest output size");
        expect(contains(rows[0], "interval_samples=2 interval_avg_ms=16.500 interval_max_ms=17.000"), "mode transition interval not misidentified as steady-state stutter");
    }

    void invalidAndInactive() {
        rows.clear();
        Metric metric;
        metric.add(-1); metric.add(std::numeric_limits<double>::infinity());
        metric.add(std::numeric_limits<double>::quiet_NaN()); metric.add(0, false);
        expect(metric.count == 0 && metric.average() == 0, "invalid timer values cannot poison averages");
        metric.add(0); metric.add(2);
        expect(metric.count == 2 && metric.average() == 1 && metric.maximum == 2, "zero-duration GPU/call sample allowed");
        expect(budgetMs(0, 20) == 50 && budgetMs(0, 0) == 0, "original-rate and unknown-rate budgets handled");
        RenderWindow render;
        PresentWindow present;
        for (unsigned i = 0; i < 10000; ++i) {
            render.add(renderSample(), double(i), nullptr);
            present.add(presentSample(), double(i), nullptr);
        }
        expect(rows.empty() && !render.started && !present.started, "inactive aggregation has no output or history mutation");
        setWr64FramePacingDiagnosticSink(nullptr);
        expect(!wr64FramePacingDiagnosticEnabled(), "sink disabled status published");
        wr64RecordFramePacingRender(renderSample());
        wr64RecordFramePacingPresent(presentSample());
        expect(rows.empty(), "disabled public hooks do not call sink");

        setWr64FramePacingDiagnosticSink(capture);
        SessionWindow<RenderWindow> state;
        state.resetForSession();
        state.window.add(renderSample(), 0, capture);
        expect(state.window.count == 1, "test session populated");
        setWr64FramePacingDiagnosticSink(nullptr);
        setWr64FramePacingDiagnosticSink(capture);
        state.resetForSession();
        expect(!state.window.started && state.window.count == 0, "same callback reinstalled starts fresh generation");
        setWr64FramePacingDiagnosticSink(nullptr);

        render.add(renderSample(), 100, capture);
        render.add(renderSample(), 50, capture);
        expect(render.startMs == 50 && render.count == 1, "clock rewind discards stale interval without fabricated output");
        present.add(presentSample(), std::numeric_limits<double>::quiet_NaN(), capture);
        expect(!present.started, "invalid clock cannot initialize a window");
    }

    void rateBoundAndConcurrency() {
        rows.clear();
        auto exercise = [](bool isRender) {
            RenderWindow render;
            PresentWindow present;
            auto rs = renderSample(); auto ps = presentSample();
            for (unsigned i = 0; i <= 10000; ++i) {
                // Alternate configurations on every frame. This must not turn
                // configuration evidence into per-frame file traffic.
                rs.width = i % 2 ? 2560 : 1280;
                ps.width = i % 2 ? 2560 : 1280;
                if (isRender) render.add(rs, double(i), capture);
                else present.add(ps, double(i), capture);
            }
        };
        std::thread producer(exercise, true), presenter(exercise, false);
        producer.join(); presenter.join();
        expect(rows.size() == 8, "independent producer windows each emit only four times in ten seconds");
        unsigned renders = 0, presents = 0;
        for (const auto &row : rows) {
            renders += row.rfind("render ", 0) == 0;
            presents += row.rfind("present ", 0) == 0;
            expect(contains(row, "config_changes=2000"), "rapid configuration changes remain bounded and visible");
        }
        expect(renders == 4 && presents == 4, "render/present metrics never share an aggregation window");
    }
}

int main() {
    renderAggregates();
    presentAggregates();
    invalidAndInactive();
    rateBoundAndConcurrency();
    std::cout << "PASS: " << checks << " frame-pacing aggregation/reset/concurrency checks\n";
}
