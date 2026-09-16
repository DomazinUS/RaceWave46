#pragma once

#include "common/rt64_plume.h"
#include "common/rt64_wr64_rt_startup.h"
#include "rt64_render_worker.h"

namespace RT64 {
    class Wr64RasterSkyPipelineCache;

    enum class Wr64SkyWaterMode { RasterOnly, CachedSkyWithRTObjects, RayTracedSkyOnly };

    // D3D12 sky-method pipelines. RasterOnly needs no ray capability or AS;
    // the two RT modes require the caller to check inline-ray support.
    // Retain native rendering until prewarm() reports the selected mode ready.
    class Wr64RasterSkyPipelines {
        std::unique_ptr<Wr64RasterSkyPipelineCache> cache_;
    public:
        Wr64RasterSkyPipelines();
        ~Wr64RasterSkyPipelines();
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &multisampling, bool hdr, bool async = true,
            Wr64SkyWaterMode mode = Wr64SkyWaterMode::RasterOnly);
        const RenderPipeline *get(bool depthCompare, bool depthWrite, bool coverageAdd);
        const RenderPipeline *capture();
        Wr64RTPrewarmStatus prewarm();
        void waitForPending();
        void reset(); // Caller guarantees GPU idle before layout/result invalidation.
    };

    class Wr64RasterSkyTarget {
        RenderDevice *device_ = nullptr;
        uint32_t width_ = 0, height_ = 0;
        std::unique_ptr<RenderTexture> texture_;
        std::unique_ptr<RenderFramebuffer> framebuffer_;
    public:
        // Recreating or resetting an existing target requires its GPU users idle.
        bool ensure(RenderWorker *worker, uint32_t width = 512, uint32_t height = 256);
        RenderTexture *texture() const { return texture_.get(); }
        RenderFramebuffer *framebuffer() const { return framebuffer_.get(); }
        uint32_t width() const { return width_; }
        uint32_t height() const { return height_; }
        void reset();
    };
}
