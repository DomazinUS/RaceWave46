// Wave Race 64 diagnostic render-layer trace and opt-in live Composer.
#pragma once

#include <cstdint>

namespace RT64 {
    struct GameCall;
    struct Projection;
    struct Workload;

    namespace WR64LayerTrace {
        struct ComposerOverride {
            uint64_t signature = 0;
            bool matched = false;
            bool suppress = false;
            uint32_t highlightColor = 0;
            int32_t rectTranslateX = 0;
            int32_t rectTranslateY = 0;
            int32_t rectLeft = 0;
            int32_t rectTop = 0;
            int32_t rectRight = 0;
            int32_t rectBottom = 0;
            int32_t scissorTranslateX = 0;
            int32_t scissorTranslateY = 0;
            int32_t scissorLeft = 0;
            int32_t scissorTop = 0;
            int32_t scissorRight = 0;
            int32_t scissorBottom = 0;
            int32_t viewportLeft = 0;
            int32_t viewportTop = 0;
            int32_t viewportRight = 0;
            int32_t viewportBottom = 0;
        };

        void observeFramebuffer(const Workload &workload, uint32_t framebufferPairIndex,
            uint32_t framebufferWidth, uint32_t framebufferHeight,
            uint32_t targetWidth, uint32_t targetHeight);

        ComposerOverride composerCallOverride(const Workload &workload,
            uint32_t framebufferPairIndex, uint32_t projectionIndex, uint32_t callIndex,
            const Projection &projection, const GameCall &call,
            uint32_t framebufferWidth, uint32_t framebufferHeight,
            uint32_t targetWidth, uint32_t targetHeight);

        uint64_t composerLastNonzeroWorkloadFrame();
        uint64_t composerLastMatchedWorkloadFrame();

        // Pure identity calculation for same-workload layout recognition.
        // Does not observe a call, consult overrides, log, or acquire a lock.
        uint64_t composerCallIdentity(const Workload &workload,
            uint32_t framebufferPairIndex, uint32_t projectionIndex, uint32_t callIndex,
            const Projection &projection, const GameCall &call);
    }
}
