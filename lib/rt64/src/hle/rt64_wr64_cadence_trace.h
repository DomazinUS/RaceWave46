//
// Wave Race 64 cadence diagnostics.
//
// This file is intentionally header-only so both RT64 queue threads can emit
// correlated rows without adding a new build-system source entry. It is inert
// unless WR64_CADENCE_TRACE is explicitly enabled.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>

namespace RT64 {
    struct WR64CadenceTraceRow {
        const char *event = "";
        uint64_t presentId = 0;
        uint64_t workloadId = 0;
        uint32_t viAddress = 0;
        uint32_t viOriginalRate = 0;
        uint32_t targetRate = 0;
        bool paused = false;
        bool requiresFrameMatching = false;
        bool displayRateAboveOriginal = false;
        uint32_t targetAddress = 0;
        uint32_t targetWidth = 0;
        uint32_t targetSiz = 0;
        int32_t targetPairIndex = -1;
        bool targetFound = false;
        bool generateInterpolatedFrames = false;
        uint32_t displayFrames = 0;
        uint32_t transformGroupCount = 0;
        uint32_t articulatedGroupCount = 0;
        uint32_t selectorGroupCount = 0;
        uint32_t courseMapGroupCount = 0;
        uint32_t counterCount = 0;
        uint32_t counterAvailable = 0;
        bool counterSkipped = false;
        uint32_t framebufferPairCount = 0;
        uint32_t presentFramebufferAddress = 0;
        uint32_t presentFramebufferWidth = 0;
        uint32_t presentFramebufferSiz = 0;
        bool presentFramebufferModified = false;
        bool presentFramebufferInterpolationEnabled = false;
        int32_t framesToPresentInitial = 0;
        int32_t framesToPresentFinal = 0;
        int32_t presentLoopIterations = 0;
        int32_t submittedFrames = 0;
        bool swapChainValid = false;
    };

    inline bool wr64CadenceTraceEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_CADENCE_TRACE");
            return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
        }();
        return enabled;
    }

    inline const std::filesystem::path &wr64CadenceTracePath() {
        static const std::filesystem::path path = []() {
            const char *value = std::getenv("WR64_CADENCE_TRACE_PATH");
            if ((value != nullptr) && (value[0] != '\0')) {
                return std::filesystem::path(value);
            }
            return std::filesystem::path(".diagnostics") / "wr64-cadence-trace.csv";
        }();
        return path;
    }

    inline void wr64WriteCadenceTrace(const WR64CadenceTraceRow &row) {
        if (!wr64CadenceTraceEnabled()) {
            return;
        }

        static std::mutex traceMutex;
        const std::scoped_lock lock(traceMutex);
        const std::filesystem::path &path = wr64CadenceTracePath();
        if (!path.parent_path().empty()) {
            std::error_code error;
            std::filesystem::create_directories(path.parent_path(), error);
        }

        bool writeHeader = true;
        {
            std::error_code error;
            writeHeader = !std::filesystem::exists(path, error) ||
                (std::filesystem::file_size(path, error) == 0);
        }

        std::ofstream output(path, std::ios::out | std::ios::app);
        if (!output.is_open()) {
            return;
        }

        if (writeHeader) {
            output << "event,present_id,workload_id,vi_address,vi_original_rate,target_rate,paused,requires_frame_matching,display_rate_above_original,"
                "target_address,target_width,target_siz,target_pair_index,target_found,generate_interpolated_frames,display_frames,"
                "transform_group_count,articulated_group_count,selector_group_count,course_map_group_count,"
                "counter_count,counter_available,counter_skipped,framebuffer_pair_count,present_fb_address,present_fb_width,present_fb_siz,"
                "present_fb_modified,present_fb_interpolation_enabled,frames_to_present_initial,frames_to_present_final,present_loop_iterations,"
                "submitted_frames,swap_chain_valid\n";
        }

        output << row.event << ','
            << row.presentId << ',' << row.workloadId << ',' << row.viAddress << ','
            << row.viOriginalRate << ',' << row.targetRate << ','
            << int(row.paused) << ',' << int(row.requiresFrameMatching) << ',' << int(row.displayRateAboveOriginal) << ','
            << row.targetAddress << ',' << row.targetWidth << ',' << row.targetSiz << ',' << row.targetPairIndex << ',' << int(row.targetFound) << ','
            << int(row.generateInterpolatedFrames) << ',' << row.displayFrames << ','
            << row.transformGroupCount << ',' << row.articulatedGroupCount << ',' << row.selectorGroupCount << ',' << row.courseMapGroupCount << ','
            << row.counterCount << ',' << row.counterAvailable << ',' << int(row.counterSkipped) << ',' << row.framebufferPairCount << ','
            << row.presentFramebufferAddress << ',' << row.presentFramebufferWidth << ',' << row.presentFramebufferSiz << ','
            << int(row.presentFramebufferModified) << ',' << int(row.presentFramebufferInterpolationEnabled) << ','
            << row.framesToPresentInitial << ',' << row.framesToPresentFinal << ',' << row.presentLoopIterations << ','
            << row.submittedFrames << ',' << int(row.swapChainValid) << '\n';
    }
}
