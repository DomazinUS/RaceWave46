#pragma once
#include "common/rt64_plume.h"
#include "common/rt64_wr64_rt_startup.h"
#include "rt64_render_worker.h"

namespace RT64 {
    struct alignas(16) Wr64RasterReflectionParams {
        float reflectedRows[4][4]{};
        float plane[4]{};   // unit plane normal.xyz, signed offset
        float options[4]{}; // enabled, strength, wave distortion in world units, clip bias
    };
    static_assert(sizeof(Wr64RasterReflectionParams) == 96);
    enum class Wr64RasterReflectionSkyMode { SkyOff, RasterSky, RTSkyOnly };
    class Wr64RasterReflectionPipelineCache;
    class Wr64RasterReflectionPipelines {
        std::unique_ptr<Wr64RasterReflectionPipelineCache> cache_;
    public:
        Wr64RasterReflectionPipelines();
        ~Wr64RasterReflectionPipelines();
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &samples, bool hdr, bool async = true,
            Wr64RasterReflectionSkyMode sky = Wr64RasterReflectionSkyMode::SkyOff, bool rasterShadows = false);
        const RenderPipeline *capture(bool nativeCulling);
        const RenderPipeline *get(bool compare, bool write, bool coverageAdd);
        Wr64RTPrewarmStatus prewarm();
        void waitForPending();
        void reset(); // Caller must ensure GPU/layout users are idle.
    };
    class Wr64RasterReflectionTarget {
        RenderDevice *device_ = nullptr;
        uint32_t width_ = 0, height_ = 0;
        std::unique_ptr<RenderTexture> color_, depth_;
        std::unique_ptr<RenderFramebuffer> framebuffer_;
    public:
        bool ensure(RenderWorker *worker, uint32_t width, uint32_t height);
        RenderTexture *color() const { return color_.get(); }
        RenderTexture *depth() const { return depth_.get(); }
        RenderFramebuffer *framebuffer() const { return framebuffer_.get(); }
        uint32_t width() const { return width_; }
        uint32_t height() const { return height_; }
        void reset(); // Existing GPU users must be idle before recreation/reset.
    };
}
