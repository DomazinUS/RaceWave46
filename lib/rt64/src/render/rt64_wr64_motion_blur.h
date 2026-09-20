#pragma once

#include <memory>
#include "common/rt64_plume.h"
#include "common/rt64_wr64_rt_startup.h"

namespace RT64 {
    struct RenderWorker;
    struct RenderTarget;
    struct ShaderLibrary;

    // All methods are renderer-thread owned. Shader compilation runs on the
    // cache worker. The owner must drain GPU users before reset/destruction.
    class Wr64MotionBlur {
        struct Impl;
        std::unique_ptr<Impl> impl_;
    public:
        Wr64MotionBlur();
        ~Wr64MotionBlur();
        Wr64RTPrewarmStatus prewarm(RenderDevice *device, const RenderPipelineLayout *rendererLayout,
            const RenderMultisampling &multisampling, bool hdr);
        bool prepare(RenderDevice *device, const RenderPipelineLayout *rendererLayout,
            const RenderMultisampling &multisampling, bool hdr);
        const RenderPipeline *getMask(bool culling, bool NoN) const;
        // Called after the previous workload's worker.wait(), before this
        // workload records any blur draws; old target views may be retired.
        bool ensureTargets(RenderWorker *worker, RenderTarget *colorTarget,
            RenderTarget *depthTarget, const ShaderLibrary *shaderLibrary);
        bool beginMask(RenderWorker *worker, const ShaderLibrary *shaderLibrary);
        RenderFramebuffer *maskFramebuffer() const;
        void finishMask(RenderWorker *worker);
        // Reduces the completed native mask into four racer-specific tile
        // guides before filtering. Active extent may be smaller than backing;
        // radius must not exceed the 16-pixel guide tile size.
        bool resolve(RenderWorker *worker, const float options[4]);
        void waitForPending();
        void reset();
    };
}
