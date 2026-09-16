// Opt-in, read-only sun diagnostics. WR64_SUN_OUTPUT_TRACE names a CSV file.
// Unlike RECT_TRACK, every rendered output is retained, including outputs with
// no native sun commands. Native, prepared and issued rows distinguish a game
// cull from a renderer transform/clip/target problem without changing either.
#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <string>
#include <unordered_map>

namespace RT64 {
    inline const std::string &wr64SunOutputTracePath() {
        static const std::string value = [] {
            const char *path = std::getenv("WR64_SUN_OUTPUT_TRACE");
            return path ? std::string(path) : std::string();
        }();
        return value;
    }

    inline bool wr64SunOutputTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        const auto &path = wr64SunOutputTracePath();
        return !path.empty() && path[0] != '0';
    }

    inline bool wr64SunOutputTexture(uint64_t hash) {
        // Include Dolphin Park's distinct disk for its horizontal-edge checks.
        // This predicate only selects diagnostic rows; drawing and pairing use
        // their existing identities and remain independent of the trace.
        return hash == 0x8A399FACE63FE583ULL || hash == 0x329E604758F9E8BCULL ||
            hash == 0xB82E909F647A31ADULL || hash == 0x79185A8F164D1366ULL;
    }

    struct Wr64SunOutputRow {
        uint64_t output = 0, workload = 0, submission = 0, present = 0;
        double timeMs = 0;
        float weight = 1, prevWeight = 0;
        bool previousMatched = false, overrideOutput = false;
        uint32_t fbpair = 0, projection = 0, call = 0, instance = 0;
        uint64_t hash = 0, target = 0, pipeline = 0;
        uint32_t colorAddress = 0, depthAddress = 0;
        uint32_t fbWidth = 0, fbHeight = 0, targetWidth = 0, targetHeight = 0;
        uint32_t allocatedWidth = 0, allocatedHeight = 0, samples = 0;
        uint32_t sampleWidth = 0, sampleHeight = 0;
        bool tileCopy = false, rawTMEM = false, tileValid = false;
        bool pairFound = false, lerpFound = false, wide = false;
        float scaleX = 0, scaleY = 0;
        std::array<int32_t, 4> raw{}, previous{}, chosen{}, nativeScissor{}, scissor{};
        std::array<float, 4> viewport{}, uv{}, prim{};
        uint32_t otherModeH = 0, otherModeL = 0, combinerH = 0, combinerL = 0;
    };

    struct Wr64SunOutputContext {
        Wr64SunOutputRow output;
        std::unordered_map<uint32_t, Wr64SunOutputRow> prepared;
    };

    inline Wr64SunOutputContext &wr64SunOutputContext() {
        static thread_local Wr64SunOutputContext context;
        return context;
    }

    inline void wr64SunOutputWrite(const char *event, const Wr64SunOutputRow &r) {
        if (!wr64SunOutputTraceArmed()) return;
        static std::mutex mutex;
        const std::lock_guard<std::mutex> lock(mutex);
        static FILE *file = [] {
            const char *path = wr64SunOutputTracePath().c_str();
            FILE *f = std::fopen(path, "wb");
            if (!f) {
                std::fprintf(stderr, "[sun-output] Could not open %s\n", path);
                return f;
            }
            std::fprintf(f, "event,output,time_ms,workload,submission,present,weight,prev_weight,previous_matched,override_output,fbpair,projection,call,instance,hash,target,pipeline,color_address,depth_address,fb_width,fb_height,target_width,target_height,allocated_width,allocated_height,samples,sample_width,sample_height,tile_copy,raw_tmem,tile_valid,pair_found,lerp_found,wide,scale_x,scale_y,raw_ulx,raw_uly,raw_lrx,raw_lry,prev_ulx,prev_uly,prev_lrx,prev_lry,chosen_ulx,chosen_uly,chosen_lrx,chosen_lry,native_sci_ulx,native_sci_uly,native_sci_lrx,native_sci_lry,scissor_left,scissor_top,scissor_right,scissor_bottom,viewport_left,viewport_top,viewport_width,viewport_height,u1,v1,u2,v2,prim_r,prim_g,prim_b,prim_a,othermode_h,othermode_l,combiner_h,combiner_l\n");
            std::fflush(f);
            std::fprintf(stderr, "[sun-output] Recording every sun output to %s\n", path);
            return f;
        }();
        if (!file) return;
        static uint64_t rows = 0;
        if (rows >= 500000) return;
        std::fprintf(file, "%s,%llu,%.3f,%llu,%llu,%llu,%.9g,%.9g,%u,%u,%u,%u,%u,%u,%016llX,%016llX,%016llX,%08X,%08X,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%.9g,%.9g",
            event, (unsigned long long)r.output, r.timeMs,
            (unsigned long long)r.workload, (unsigned long long)r.submission, (unsigned long long)r.present,
            double(r.weight), double(r.prevWeight), unsigned(r.previousMatched), unsigned(r.overrideOutput),
            r.fbpair, r.projection, r.call, r.instance, (unsigned long long)r.hash,
            (unsigned long long)r.target, (unsigned long long)r.pipeline, r.colorAddress, r.depthAddress,
            r.fbWidth, r.fbHeight, r.targetWidth, r.targetHeight, r.allocatedWidth, r.allocatedHeight,
            r.samples, r.sampleWidth, r.sampleHeight, unsigned(r.tileCopy), unsigned(r.rawTMEM),
            unsigned(r.tileValid), unsigned(r.pairFound), unsigned(r.lerpFound), unsigned(r.wide),
            double(r.scaleX), double(r.scaleY));
        for (const auto *rect : { &r.raw, &r.previous, &r.chosen, &r.nativeScissor, &r.scissor })
            for (int32_t v : *rect) std::fprintf(file, ",%d", v);
        for (float v : r.viewport) std::fprintf(file, ",%.9g", double(v));
        for (float v : r.uv) std::fprintf(file, ",%.9g", double(v));
        for (float v : r.prim) std::fprintf(file, ",%.9g", double(v));
        std::fprintf(file, ",%08X,%08X,%08X,%08X\n", r.otherModeH, r.otherModeL, r.combinerH, r.combinerL);
        if ((++rows % 32) == 0 || event[0] == 'o') std::fflush(file);
    }

    inline void wr64SunOutputBegin(float weight, float previousWeight, bool matched, bool overrideOutput) {
        if (!wr64SunOutputTraceArmed()) return;
        static std::atomic<uint64_t> sequence{0};
        auto &context = wr64SunOutputContext();
        context.prepared.clear();
        context.output = {};
        context.output.output = sequence.fetch_add(1, std::memory_order_relaxed) + 1;
        context.output.timeMs = std::chrono::duration<double, std::milli>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        context.output.weight = weight;
        context.output.prevWeight = previousWeight;
        context.output.previousMatched = matched;
        context.output.overrideOutput = overrideOutput;
        wr64SunOutputWrite("output", context.output);
    }

    inline void wr64SunOutputPrepared(uint32_t instance, Wr64SunOutputRow row) {
        if (!wr64SunOutputTraceArmed()) return;
        row.instance = instance;
        wr64SunOutputContext().prepared[instance] = row;
        wr64SunOutputWrite("prepared", row);
    }

    inline void wr64SunOutputIssued(uint32_t instance, bool emptyScissor) {
        if (!wr64SunOutputTraceArmed()) return;
        const auto &rows = wr64SunOutputContext().prepared;
        const auto it = rows.find(instance);
        if (it != rows.end()) wr64SunOutputWrite(emptyScissor ? "skip_empty_scissor" : "issued", it->second);
    }
}
