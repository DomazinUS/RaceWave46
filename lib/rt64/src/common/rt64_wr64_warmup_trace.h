// Read-only banner diagnostics. WR64_WARMUP_TRACE names a CSV file; default OFF.
// Capture the entire native banner band, including untagged/unknown textures.
// Filtering by the interpolation fingerprint here would hide the missed calls
// this trace exists to find. No texture pixels, ROM data or game state is changed.
#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <string>

namespace RT64 {
    inline const std::string &wr64WarmupTracePath() {
        static const std::string path = [] {
            const char *value = std::getenv("WR64_WARMUP_TRACE");
            return value ? std::string(value) : std::string();
        }();
        return path;
    }

    inline bool wr64WarmupTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        return !wr64WarmupTracePath().empty();
    }

    inline bool wr64WarmupTraceCandidate(int32_t top, int32_t bottom, uint32_t nativeKind) {
        return nativeKind == 1 || (top <= 880 && bottom >= 780);
    }

    struct Wr64WarmupTraceRow {
        uint64_t workload = 0, submission = 0, present = 0, key = 0, texture = 0;
        uint32_t fbpair = 0, projection = 0, call = 0, instance = 0, drawType = 0;
        uint32_t triangleCount = 0, tileCount = 0, rawVertexStart = 0;
        uint32_t sampleWidth = 0, sampleHeight = 0;
        bool tileValid = false, tileCopy = false, rawTmem = false;
        uint32_t combinerH = 0, combinerL = 0, otherModeH = 0, otherModeL = 0;
        int32_t dsdx = 0, dtdy = 0;
        uint64_t generation = 0;
        uint32_t kind = 0, slot = 0, part = 0, content = 0, age = 0, context = 0;
        int32_t nativeX = 0, nativeY = 0;
        bool pairFound = false, lerpFound = false, uvValid = false, outputValid = false;
        std::array<int32_t, 4> raw{}, chosen{}, previous{}, current{}, nativeScissor{}, outputScissor{};
        std::array<float, 4> uv{}, viewport{};
        uint32_t fbWidth = 0, fbHeight = 0, targetWidth = 0, targetHeight = 0;
        float scaleX = 0, scaleY = 0;
    };

    class Wr64WarmupTraceWriter {
        static constexpr uint64_t MaxRows = 200000;
        static constexpr uint64_t FlushRows = 256;
        std::mutex mutex;
        std::array<char, 65536> buffer{};
        FILE *file = nullptr;
        uint64_t rows = 0;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    public:
        Wr64WarmupTraceWriter() {
            file = std::fopen(wr64WarmupTracePath().c_str(), "wb");
            if (!file) {
                std::fprintf(stderr, "[warmup-trace] Could not open diagnostic CSV.\n");
                return;
            }
            std::setvbuf(file, buffer.data(), _IOFBF, buffer.size());
            std::fputs("row,time_ms,workload,submission,present,key,fbpair,projection,call,instance,draw_type,triangle_count,tile_count,raw_vertex_start,texture,sample_width,sample_height,tile_valid,tile_copy,raw_tmem,combiner_h,combiner_l,othermode_h,othermode_l,dsdx,dtdy,generation,kind,slot,part,content,age,context,native_x,native_y,pair_found,lerp_found,uv_valid,output_valid,raw_ulx,raw_uly,raw_lrx,raw_lry,chosen_ulx,chosen_uly,chosen_lrx,chosen_lry,prev_ulx,prev_uly,prev_lrx,prev_lry,cur_ulx,cur_uly,cur_lrx,cur_lry,native_sci_ulx,native_sci_uly,native_sci_lrx,native_sci_lry,out_sci_left,out_sci_top,out_sci_right,out_sci_bottom,u1,v1,u2,v2,viewport_x,viewport_y,viewport_width,viewport_height,fb_width,fb_height,target_width,target_height,scale_x,scale_y\n", file);
            std::fflush(file);
        }

        ~Wr64WarmupTraceWriter() {
            if (file) std::fclose(file);
        }

        void write(const Wr64WarmupTraceRow &r) {
            const std::lock_guard<std::mutex> lock(mutex);
            if (!file || rows >= MaxRows) return;
            const double ms = std::chrono::duration<double, std::milli>(
                std::chrono::steady_clock::now() - start).count();
            std::fprintf(file, "%llu,%.3f,%llu,%llu,%llu,%016llX,%u,%u,%u,%u,%u,%u,%u,%u,%016llX,%u,%u,%u,%u,%u,%08X,%08X,%08X,%08X,%d,%d,%llu,%u,%u,%u,%u,%u,%u,%d,%d,%u,%u,%u,%u",
                (unsigned long long)++rows, ms,
                (unsigned long long)r.workload, (unsigned long long)r.submission,
                (unsigned long long)r.present, (unsigned long long)r.key,
                r.fbpair, r.projection, r.call, r.instance, r.drawType,
                r.triangleCount, r.tileCount, r.rawVertexStart, (unsigned long long)r.texture,
                r.sampleWidth, r.sampleHeight, unsigned(r.tileValid), unsigned(r.tileCopy), unsigned(r.rawTmem),
                r.combinerH, r.combinerL, r.otherModeH, r.otherModeL, r.dsdx, r.dtdy,
                (unsigned long long)r.generation, r.kind, r.slot, r.part, r.content, r.age,
                r.context, r.nativeX, r.nativeY, unsigned(r.pairFound), unsigned(r.lerpFound),
                unsigned(r.uvValid), unsigned(r.outputValid));
            for (const auto *rect : { &r.raw, &r.chosen, &r.previous, &r.current, &r.nativeScissor, &r.outputScissor }) {
                for (int32_t value : *rect) std::fprintf(file, ",%d", value);
            }
            for (const auto *values : { &r.uv, &r.viewport }) {
                for (float value : *values) std::fprintf(file, ",%.9g", double(value));
            }
            std::fprintf(file, ",%u,%u,%u,%u,%.9g,%.9g\n",
                r.fbWidth, r.fbHeight, r.targetWidth, r.targetHeight, double(r.scaleX), double(r.scaleY));
            if ((rows % FlushRows == 0) || rows == MaxRows) std::fflush(file);
        }
    };

    inline void wr64WarmupTraceWrite(const Wr64WarmupTraceRow &row) {
        if (!wr64WarmupTraceArmed()) return;
        static Wr64WarmupTraceWriter writer;
        writer.write(row);
    }
}
