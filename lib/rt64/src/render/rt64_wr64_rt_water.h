#pragma once

#include "rt64_raster_shader.h"
#include "common/rt64_user_configuration.h"
#include "common/rt64_wr64_rt_startup.h"

namespace RT64 {
    class Wr64RTPipelineCache;
    // Lazily built on D3D12 or Vulkan devices that expose inline ray queries.
    class Wr64RTWaterPipelines {
        std::unique_ptr<Wr64RTPipelineCache> cache_;
    public:
        Wr64RTWaterPipelines();
        ~Wr64RTWaterPipelines();
        static bool supported(RenderDevice *device, UserConfiguration::GraphicsAPI api);
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &multisampling, bool hdr, bool nativeSky = false, bool async = false,
            RenderShaderFormat shaderFormat = RenderShaderFormat::DXIL);
        const RenderPipeline *get(bool depthCompare, bool depthWrite, bool coverageAdd) const;
        Wr64RTPrewarmStatus prewarm(); // Queue/poll all variants of the selected configuration.
        void waitForPending();
        void reset(); // Caller guarantees GPU idle before invalidating layout/results.
    };

    // Static shore receivers use the same native raster material with a
    // shadow visibility query. Preserve each draw's fixed pipeline state.
    class Wr64RTWorldShadowPipelines {
        std::unique_ptr<Wr64RTPipelineCache> cache_;
    public:
        Wr64RTWorldShadowPipelines();
        ~Wr64RTWorldShadowPipelines();
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &multisampling, bool hdr, bool async = false,
            RenderShaderFormat shaderFormat = RenderShaderFormat::DXIL);
        const RenderPipeline *get(bool depthCompare, bool depthWrite, bool coverageAdd,
            bool culling, bool NoN, bool alphaBlend);
        Wr64RTPrewarmStatus prewarm();
        void waitForPending();
        void reset(); // Caller guarantees GPU idle before invalidating layout/results.
    };
}
