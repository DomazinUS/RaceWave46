// Driver PSO compilation only: no window, swapchain, command submission,
// framebuffer, ROM or game. Links the actual embedded production DXIL.
#include <array>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "plume_d3d12.h"
#include "render/rt64_descriptor_sets.h"
#include "render/rt64_raster_shader.h"
#include "shared/rt64_raster_params.h"
using namespace plume;
using namespace RT64;
#define WR64_BLOB(name) extern "C" { extern const char name[]; extern const size_t name##_size; }
WR64_BLOB(Wr64WaterReflectionVSBlobDXIL)
WR64_BLOB(Wr64WaterReflectionPSMSBlobDXIL)
WR64_BLOB(Wr64WaterSkyReflectionPSMSBlobDXIL)
WR64_BLOB(Wr64WorldShadowVSBlobDXIL)
WR64_BLOB(Wr64WorldShadowPSMSBlobDXIL)

static void fillSamplers(RenderDevice* device,SamplerSet& set,RenderFilter filter) {
    std::unique_ptr<RenderSampler>* entries[]={&set.wrapWrap,&set.wrapMirror,&set.wrapClamp,
        &set.mirrorWrap,&set.mirrorMirror,&set.mirrorClamp,&set.clampWrap,&set.clampMirror,&set.clampClamp};
    const RenderTextureAddressMode modes[]={RenderTextureAddressMode::WRAP,RenderTextureAddressMode::MIRROR,RenderTextureAddressMode::CLAMP};
    for(uint32_t i=0;i<9;++i) {
        RenderSamplerDesc d;d.minFilter=filter;d.magFilter=filter;
        d.addressU=modes[i/3];d.addressV=modes[i%3];d.addressW=RenderTextureAddressMode::CLAMP;
        d.mipLODBias=-.25f;d.anisotropyEnabled=filter==RenderFilter::LINEAR;
        *entries[i]=device->createSampler(d);
    }
}
int main(int argc,char** argv) {
    std::setvbuf(stdout,nullptr,_IONBF,0);
    try {
        // Optional unused root constant gives a different PSO cache key without
        // deleting the user's global driver cache. This does not guarantee the
        // driver's internal shader-code cache is cold; label it accordingly.
        bool signatureVariant=false;
        for(int i=1;i<argc;++i)signatureVariant |= std::strcmp(argv[i],"--signature-variant")==0;
        D3D12Interface renderInterface;auto device=renderInterface.createDevice("");
        if(!device)throw std::runtime_error("No D3D12 device");
        SamplerLibrary samplers;fillSamplers(device.get(),samplers.nearest,RenderFilter::NEAREST);
        fillSamplers(device.get(),samplers.linear,RenderFilter::LINEAR);
        FramebufferRendererDescriptorCommonSet common(samplers,true);
        FramebufferRendererDescriptorTextureSet textures;
        FramebufferRendererDescriptorFramebufferSet framebuffer;
        RenderPipelineLayoutBuilder builder;builder.begin(false,true);
        builder.addPushConstant(0,0,sizeof(interop::RasterParams),RenderShaderStageFlag::VERTEX|RenderShaderStageFlag::PIXEL);
        builder.addDescriptorSet(common);builder.addDescriptorSet(textures);builder.addDescriptorSet(textures);builder.addDescriptorSet(framebuffer);
        if(signatureVariant)builder.addPushConstant(31,31,4,RenderShaderStageFlag::PIXEL);
        builder.end();auto layout=builder.create(device.get());
        if(!layout)throw std::runtime_error("No production-equivalent pipeline layout");
        const auto start=std::chrono::steady_clock::now();
        auto elapsed=[&](){return std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count();};
        std::printf("pso timing: signature_variant=%u sky_dxil_bytes=%zu stable_dxil_bytes=%zu world_dxil_bytes=%zu; no GPU work submitted\n",
            unsigned(signatureVariant),Wr64WaterSkyReflectionPSMSBlobDXIL_size,Wr64WaterReflectionPSMSBlobDXIL_size,Wr64WorldShadowPSMSBlobDXIL_size);
        struct Family {const char* name;const char* vs;size_t vsSize;const char* ps;size_t psSize;};
        const Family families[]={
            {"sky",Wr64WaterReflectionVSBlobDXIL,Wr64WaterReflectionVSBlobDXIL_size,Wr64WaterSkyReflectionPSMSBlobDXIL,Wr64WaterSkyReflectionPSMSBlobDXIL_size},
            {"stable",Wr64WaterReflectionVSBlobDXIL,Wr64WaterReflectionVSBlobDXIL_size,Wr64WaterReflectionPSMSBlobDXIL,Wr64WaterReflectionPSMSBlobDXIL_size},
            {"world",Wr64WorldShadowVSBlobDXIL,Wr64WorldShadowVSBlobDXIL_size,Wr64WorldShadowPSMSBlobDXIL,Wr64WorldShadowPSMSBlobDXIL_size}};
        std::vector<std::unique_ptr<RenderPipeline>> pipelines;
        for(const auto& family:families) {
            const double familyStart=elapsed();
            auto vs=device->createShader(family.vs,family.vsSize,"VSMain",RenderShaderFormat::DXIL);
            auto ps=device->createShader(family.ps,family.psSize,"PSMain",RenderShaderFormat::DXIL);
            if(!vs||!ps)throw std::runtime_error("Production shader creation failed");
            PipelineCreation c{};c.device=device.get();c.pipelineLayout=layout.get();c.vertexShader=vs.get();c.pixelShader=ps.get();
            c.alphaBlend=true;c.culling=false;c.NoN=true;c.usesHDR=false;c.multisampling=RenderMultisampling(4);
            const uint32_t variants=std::strcmp(family.name,"world")==0?3u:8u;
            for(uint32_t i=0;i<variants;++i) {
                c.zCmp=(i&1)!=0;c.zUpd=(i&2)!=0;c.cvgAdd=(i&4)!=0;
                if(variants==3){c.zCmp=i!=0;c.zUpd=i!=0;c.culling=i!=0;c.alphaBlend=i==2;}
                const double begin=elapsed();std::printf("%.3fms begin family=%s samples=4 variant=%u\n",begin,family.name,i);
                auto pipeline=RasterShader::createPipeline(c);
                const double duration=elapsed()-begin;
                std::printf("%.3fms finish family=%s variant=%u duration_ms=%.3f success=%u\n",elapsed(),family.name,i,duration,unsigned(bool(pipeline)));
                if(!pipeline)throw std::runtime_error("Production PSO creation failed");
                pipelines.push_back(std::move(pipeline));
            }
            std::printf("family=%s total_ms=%.3f variants=%u\n",family.name,elapsed()-familyStart,variants);
        }
        std::printf("PASS: %zu PSOs, total_ms=%.3f; no commands submitted, no game process\n",pipelines.size(),elapsed());
        return 0;
    }
    catch(const std::exception& e){std::fprintf(stderr,"FAIL: %s\n",e.what());return 1;}
}
