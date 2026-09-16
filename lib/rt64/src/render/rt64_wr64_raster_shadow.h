#pragma once

#include "common/rt64_plume.h"
#include "common/rt64_wr64_rt_startup.h"
#include "rt64_render_worker.h"

namespace RT64 {
    struct alignas(16) Wr64RasterShadowParams {
        float lightRows[4][4]{};
        float options[4]{}; // inverse map size, normalized depth bias, water/solid strength
        float light[4]{};   // world direction toward the light, enabled
    };
    static_assert(sizeof(Wr64RasterShadowParams) == 96);

    enum class Wr64RasterShadowWaterMode { Native, RasterSky, RTObjects, RTSky, RTObjectsRasterSky, RTSkyOnly };
    class Wr64RasterShadowPipelineCache;
    class Wr64RasterShadowPipelines {
        std::unique_ptr<Wr64RasterShadowPipelineCache> cache_;
    public:
        Wr64RasterShadowPipelines();
        ~Wr64RasterShadowPipelines();
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &multisampling, bool hdr, bool async = true,
            Wr64RasterShadowWaterMode mode = Wr64RasterShadowWaterMode::Native);
        const RenderPipeline *capture();
        const RenderPipeline *getWater(Wr64RasterShadowWaterMode mode, bool compare, bool write, bool coverageAdd);
        const RenderPipeline *nativeWater(bool compare, bool write, bool coverageAdd);
        const RenderPipeline *world(bool compare, bool write, bool coverageAdd,
            bool culling, bool NoN, bool alphaBlend);
        Wr64RTPrewarmStatus prewarm();
        void waitForPending();
        void reset(); // GPU users and the old pipeline layout must be idle.
    };

    class Wr64RasterShadowTarget {
        RenderDevice *device_ = nullptr;
        uint32_t size_ = 0;
        std::unique_ptr<RenderTexture> color_, depth_;
        std::unique_ptr<RenderFramebuffer> framebuffer_;
    public:
        bool ensure(RenderWorker *worker, uint32_t size = 1024);
        RenderTexture *color() const { return color_.get(); }
        RenderTexture *depth() const { return depth_.get(); }
        RenderFramebuffer *framebuffer() const { return framebuffer_.get(); }
        uint32_t size() const { return size_; }
        void reset(); // Existing GPU users must be idle before recreation/reset.
    };
}
