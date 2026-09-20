// Headless tests of the production native actor-motion VS/PS, resolve shader,
// asynchronous PSOs and color/depth resource manager. No game or window.
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <thread>
#include <vector>
#include "plume_d3d12.h"
#include "render/rt64_descriptor_sets.h"
#include "render/rt64_render_target.h"
#include "render/rt64_shader_library.h"
#include "render/rt64_wr64_motion_blur.h"
#include "shared/rt64_frame_params.h"
#include "shared/rt64_framebuffer_params.h"
#include "shared/rt64_raster_params.h"
#include "shared/rt64_rdp_params.h"
#include "shared/rt64_render_indices.h"
#include "shared/rt64_render_params.h"
using namespace plume;
using namespace RT64;
namespace {
constexpr uint32_t W=64,H=64;
size_t checks=0;
void require(bool ok,const char *message) { ++checks;if(!ok)throw std::runtime_error(message); }
void fill(RenderBuffer *b,const void *p,size_t n) {
    const RenderRange empty(0,0);void *out=b->map(0,&empty);require(out!=nullptr,"Upload map failed");
    std::memcpy(out,p,n);const RenderRange written(0,n);b->unmap(0,&written);
}
std::vector<uint8_t> fileBytes(const std::string &path) {
    std::ifstream f(path,std::ios::binary);require(bool(f),"Fixture DXIL missing");
    return {std::istreambuf_iterator<char>(f),std::istreambuf_iterator<char>()};
}
void samplers(RenderDevice *device,SamplerSet &set,RenderFilter filter) {
    std::unique_ptr<RenderSampler> *entries[]={&set.wrapWrap,&set.wrapMirror,&set.wrapClamp,
        &set.mirrorWrap,&set.mirrorMirror,&set.mirrorClamp,&set.clampWrap,&set.clampMirror,&set.clampClamp};
    const RenderTextureAddressMode modes[]={RenderTextureAddressMode::WRAP,RenderTextureAddressMode::MIRROR,RenderTextureAddressMode::CLAMP};
    for(uint32_t i=0;i<9;++i){RenderSamplerDesc d;d.minFilter=d.magFilter=filter;d.addressU=modes[i/3];d.addressV=modes[i%3];d.addressW=RenderTextureAddressMode::CLAMP;*entries[i]=device->createSampler(d);}
}
struct MotionDraw { float matrix[16]={};float scale[4]={32,32,.5f,1};float translate[4]={32,32,.5f,0}; };
static_assert(sizeof(MotionDraw)==96,"Production motion draw layout changed");
}
int main(int argc,char **argv) {
    std::setvbuf(stdout,nullptr,_IONBF,0);
    try {
        require(argc>1,"Pass fixture DXIL directory");const std::string directory=argv[1];
        D3D12Interface rhi;require(rhi.isValid(),"D3D12 unavailable");auto device=rhi.createDevice("");require(bool(device),"Device unavailable");
        RenderWorker worker(device.get(),"Headless actor motion tests",RenderCommandListType::DIRECT);
        ShaderLibrary library(false,true);
        samplers(device.get(),library.samplerLibrary.nearest,RenderFilter::NEAREST);
        samplers(device.get(),library.samplerLibrary.linear,RenderFilter::LINEAR);
        FramebufferRendererDescriptorCommonSet common(library.samplerLibrary,true,device.get());
        FramebufferRendererDescriptorTextureSet textures(device.get(),1);
        FramebufferRendererDescriptorFramebufferSet fbset(device.get());
        RenderPipelineLayoutBuilder lb;lb.begin(false,true);
        lb.addPushConstant(0,0,sizeof(interop::RasterParams),RenderShaderStageFlag::VERTEX|RenderShaderStageFlag::PIXEL);
        lb.addDescriptorSet(common);lb.addDescriptorSet(textures);lb.addDescriptorSet(textures);lb.addDescriptorSet(fbset);lb.end();
        auto layout=lb.create(device.get());require(bool(layout),"Native raster layout failed");
        std::vector<std::unique_ptr<RenderBuffer>> buffers;
        auto upload=[&](const void *p,size_t n,RenderBufferFlags flags) {
            auto b=device->createBuffer(RenderBufferDesc::UploadBuffer((flags&RenderBufferFlag::CONSTANT)?(n+255)&~size_t(255):n,flags));
            require(bool(b),"Upload allocation failed");fill(b.get(),p,n);auto *raw=b.get();buffers.push_back(std::move(b));return raw;
        };
        float screen[4][4]={{24,24,.5f,1},{40,24,.5f,1},{40,40,.5f,1},{24,40,.5f,1}};
        float world[4][4]={},velocity[4][4]={},uv[4][2]={},color[4][4];
        for(uint32_t i=0;i<4;++i){world[i][0]=(screen[i][0]-32)/32;world[i][1]=(32-screen[i][1])/32;world[i][3]=1;velocity[i][0]=.25f;for(float &v:color[i])v=1;}
        uint32_t indices[]={0,1,2,0,2,3};MotionDraw history;history.matrix[0]=history.matrix[5]=history.matrix[10]=history.matrix[15]=1;
        auto screenBuffer=upload(screen,sizeof(screen),RenderBufferFlag::VERTEX);
        auto uvBuffer=upload(uv,sizeof(uv),RenderBufferFlag::VERTEX);
        auto colorBuffer=upload(color,sizeof(color),RenderBufferFlag::VERTEX);
        auto worldBuffer=upload(world,sizeof(world),RenderBufferFlag::STORAGE);
        auto velocityBuffer=upload(velocity,sizeof(velocity),RenderBufferFlag::STORAGE);
        auto historyBuffer=upload(&history,sizeof(history),RenderBufferFlag::STORAGE);
        auto indexBuffer=upload(indices,sizeof(indices),RenderBufferFlag::INDEX);
        interop::FrameParams frame{};interop::FramebufferParams framebuffer{};
        framebuffer.resolution=hlslpp::float2(W,H);framebuffer.resolutionScale=hlslpp::float2(1,1);
        interop::RenderIndices renderIndex{};interop::RDPParams rdp{};rdp.primColor=hlslpp::float4(.95f,.8f,.1f,1);
        interop::RenderParams rp{};
        rp.ccL=(8u<<20)|(31u<<15)|(7u<<12)|(7u<<9)|(8u<<5)|31u;
        rp.ccH=(8u<<28)|(8u<<24)|(7u<<21)|(7u<<18)|(3u<<15)|(7u<<12)|(3u<<9)|(3u<<6)|(7u<<3)|3u;
        rp.flags.NoN=1;rp.flags.smoothShade=1;rp.omH=0x00082cff;
        auto rpBuffer=upload(&rp,sizeof(rp),RenderBufferFlag::STORAGE);
        auto rdpBuffer=upload(&rdp,sizeof(rdp),RenderBufferFlag::STORAGE);
        common.setBuffer(common.FrParams,upload(&frame,sizeof(frame),RenderBufferFlag::CONSTANT),sizeof(frame));
        fbset.setBuffer(fbset.FbParams,upload(&framebuffer,sizeof(framebuffer),RenderBufferFlag::CONSTANT),sizeof(framebuffer));
        common.setBuffer(common.instanceRenderIndices,upload(&renderIndex,sizeof(renderIndex),RenderBufferFlag::STORAGE),sizeof(renderIndex),RenderBufferStructuredView(sizeof(renderIndex)));
        common.setBuffer(common.instanceRDPParams,rdpBuffer,sizeof(rdp),RenderBufferStructuredView(sizeof(rdp)));
        common.setBuffer(common.DynamicRenderParams,rpBuffer,sizeof(rp),RenderBufferStructuredView(sizeof(rp)));
        common.setBuffer(common.posBuffer,worldBuffer,sizeof(world));
        common.setBuffer(common.velBuffer,velocityBuffer,sizeof(velocity));
        common.setBuffer(common.wr64MotionDraws,historyBuffer,sizeof(history),RenderBufferStructuredView(sizeof(history)));
        const RenderInputSlot slots[]={RenderInputSlot(0,16),RenderInputSlot(1,8),RenderInputSlot(2,16)};
        const RenderVertexBufferView vb[]={RenderVertexBufferView(screenBuffer->at(0),sizeof(screen)),RenderVertexBufferView(uvBuffer->at(0),sizeof(uv)),RenderVertexBufferView(colorBuffer->at(0),sizeof(color))};
        const RenderIndexBufferView ib(indexBuffer->at(0),sizeof(indices),RenderFormat::R32_UINT);
        interop::RasterParams push{};push.screenScale=hlslpp::float2(1,1);
        auto vsBytes=fileBytes(directory+"/fixture-vs.dxil"),psBytes=fileBytes(directory+"/fixture-ps.dxil");
        auto fixtureVS=device->createShader(vsBytes.data(),vsBytes.size(),"VSMain",RenderShaderFormat::DXIL);
        auto fixturePS=device->createShader(psBytes.data(),psBytes.size(),"PSMain",RenderShaderFormat::DXIL);
        auto nativeVSBytes=fileBytes(directory+"/native-actor-vs.dxil"),nativePSBytes=fileBytes(directory+"/native-actor-ps.dxil");
        auto nativeActorVS=device->createShader(nativeVSBytes.data(),nativeVSBytes.size(),"VSMain",RenderShaderFormat::DXIL);
        auto nativeActorPS=device->createShader(nativePSBytes.data(),nativePSBytes.size(),"ActorPSMain",RenderShaderFormat::DXIL);
        RenderPipelineLayoutBuilder flb;flb.begin();flb.addPushConstant(0,0,16,RenderShaderStageFlag::PIXEL);flb.end();auto fixtureLayout=flb.create(device.get());
        auto execute=[&](){worker.commandList->end();worker.execute();worker.wait();require(SUCCEEDED(static_cast<D3D12Device*>(device.get())->d3d->GetDeviceRemovedReason()),"Motion test removed the GPU device");};
        auto readback=[&](RenderTexture *target,RenderFormat format,uint32_t bytes,RenderMultisampling ms,uint32_t width=W,uint32_t height=H) {
            auto resolved=device->createTexture(RenderTextureDesc::Texture2D(width,height,1,format));
            const uint32_t rowPitch=(width*bytes+255u)&~255u;
            auto output=device->createBuffer(RenderBufferDesc::ReadbackBuffer(rowPitch*height));
            worker.commandList->begin();RenderTexture *source=target;
            if(ms.sampleCount>1){worker.commandList->barriers(RenderBarrierStage::GRAPHICS,{RenderTextureBarrier(target,RenderTextureLayout::RESOLVE_SOURCE),RenderTextureBarrier(resolved.get(),RenderTextureLayout::RESOLVE_DEST)});worker.commandList->resolveTexture(resolved.get(),target);source=resolved.get();}
            worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(source,RenderTextureLayout::COPY_SOURCE));
            D3D12_TEXTURE_COPY_LOCATION dst{};dst.pResource=static_cast<D3D12Buffer*>(output.get())->d3d;dst.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
            dst.PlacedFootprint.Footprint={bytes==4?DXGI_FORMAT_R8G8B8A8_UNORM:DXGI_FORMAT_R32G32B32A32_FLOAT,width,height,1,rowPitch};
            D3D12_TEXTURE_COPY_LOCATION src{};src.pResource=static_cast<D3D12Texture*>(source)->d3d;src.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            static_cast<D3D12CommandList*>(worker.commandList.get())->d3d->CopyTextureRegion(&dst,0,0,0,&src,nullptr);execute();
            std::vector<uint8_t> data(width*height*bytes);const RenderRange range(0,size_t(rowPitch)*height);const void *ptr=output->map(0,&range);require(ptr!=nullptr,"Motion readback failed");for(uint32_t y=0;y<height;++y)std::memcpy(data.data()+size_t(y)*width*bytes,static_cast<const uint8_t*>(ptr)+size_t(y)*rowPitch,size_t(width)*bytes);const RenderRange none(0,0);output->unmap(0,&none);return data;
        };
        Wr64MotionBlur motion;
        const bool benchmarkOnly=argc>2&&std::strcmp(argv[2],"--benchmark-only")==0;
        for(uint32_t samples:{1u,4u}) {
            if(benchmarkOnly&&samples!=4)continue;
            RenderMultisampling ms(samples);rp.flags.sampleCount=samples==1?0:2;fill(rpBuffer,&rp,sizeof(rp));
            auto start=std::chrono::steady_clock::now();Wr64RTPrewarmStatus status;
            do{status=motion.prewarm(device.get(),layout.get(),ms,false);if(status==Wr64RTPrewarmStatus::Pending)std::this_thread::sleep_for(std::chrono::milliseconds(1));require(std::chrono::steady_clock::now()-start<std::chrono::seconds(120),"Motion prewarm timed out");}while(status==Wr64RTPrewarmStatus::Pending);
            require(status==Wr64RTPrewarmStatus::Ready,"Production motion PSOs failed");const auto *maskPSO=motion.getMask(false,true);require(maskPSO!=nullptr,"Motion mask variant missing");
            RenderTarget scene(0,Framebuffer::Type::Color,ms,false),depth(0,Framebuffer::Type::Depth,ms,false);scene.resize(&worker,W,H);depth.resize(&worker,W,H);
            const RenderTexture *attachment=scene.texture.get();auto fixtureFB=device->createFramebuffer(RenderFramebufferDesc(&attachment,1,depth.texture.get()));
            RenderGraphicsPipelineDesc fd;fd.pipelineLayout=fixtureLayout.get();fd.vertexShader=fixtureVS.get();fd.pixelShader=fixturePS.get();fd.renderTargetCount=1;fd.renderTargetFormat[0]=scene.format;fd.renderTargetBlend[0]=RenderBlendDesc::Copy();fd.depthTargetFormat=RenderFormat::D32_FLOAT;fd.depthEnabled=true;fd.depthWriteEnabled=true;fd.depthFunction=RenderComparisonFunction::ALWAYS;fd.multisampling=ms;
            auto fixturePSO=device->createGraphicsPipeline(fd);require(fixturePSO&&static_cast<D3D12GraphicsPipeline*>(fixturePSO.get())->d3d,"Fixture pipeline failed");
            const RenderInputElement nativeElements[]={RenderInputElement("POSITION",0,0,RenderFormat::R32G32B32A32_FLOAT,0,0),RenderInputElement("TEXCOORD",0,1,RenderFormat::R32G32_FLOAT,1,0),RenderInputElement("COLOR",0,2,RenderFormat::R32G32B32A32_FLOAT,2,0)};
            auto nativeDesc=fd;nativeDesc.pipelineLayout=layout.get();nativeDesc.vertexShader=nativeActorVS.get();nativeDesc.pixelShader=nativeActorPS.get();nativeDesc.depthFunction=RenderComparisonFunction::LESS_EQUAL;
            nativeDesc.inputSlots=slots;nativeDesc.inputSlotsCount=3;nativeDesc.inputElements=nativeElements;nativeDesc.inputElementsCount=3;
            auto nativeActorPSO=device->createGraphicsPipeline(nativeDesc);require(nativeActorPSO&&static_cast<D3D12GraphicsPipeline*>(nativeActorPSO.get())->d3d,"Native actor depth fixture pipeline failed");
            fbset.setTexture(fbset.gBackgroundDepth,depth.texture.get(),RenderTextureLayout::DEPTH_READ,depth.textureView.get());
            float fixture[4]={0,.6f,24,40};
            auto drawSource=[&]() {
                worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::GRAPHICS,{RenderTextureBarrier(scene.texture.get(),RenderTextureLayout::COLOR_WRITE),RenderTextureBarrier(depth.texture.get(),RenderTextureLayout::DEPTH_WRITE)});
                worker.commandList->setFramebuffer(fixtureFB.get());worker.commandList->setGraphicsPipelineLayout(fixtureLayout.get());worker.commandList->setGraphicsPushConstants(0,fixture);worker.commandList->setPipeline(fixturePSO.get());worker.commandList->setViewports(RenderViewport(0,0,W,H));worker.commandList->setScissors(RenderRect(0,0,W,H));worker.commandList->setVertexBuffers(0,nullptr,0,nullptr);worker.commandList->setIndexBuffer(nullptr);worker.commandList->drawInstanced(3,1,0,0);execute();
            };
            auto bindNative=[&]() {
                worker.commandList->setGraphicsPipelineLayout(layout.get());worker.commandList->setGraphicsDescriptorSet(common.get(),0);worker.commandList->setGraphicsDescriptorSet(textures.get(),1);worker.commandList->setGraphicsDescriptorSet(textures.get(),2);worker.commandList->setGraphicsDescriptorSet(fbset.get(),3);worker.commandList->setGraphicsPushConstants(0,&push);worker.commandList->setVertexBuffers(0,vb,3,slots);worker.commandList->setIndexBuffer(&ib);
            };
            auto drawMask=[&]() {bindNative();worker.commandList->setPipeline(maskPSO);worker.commandList->drawIndexedInstanced(6,1,0,0,0);};
            if(benchmarkOnly) {
                constexpr uint32_t benchmarkWidth=1696,benchmarkHeight=960;
                RenderTarget full(0,Framebuffer::Type::Color,ms,false),fullDepth(0,Framebuffer::Type::Depth,ms,false);
                full.resize(&worker,benchmarkWidth,benchmarkHeight);fullDepth.resize(&worker,benchmarkWidth,benchmarkHeight);
                const RenderTexture *fullAttachment=full.texture.get();auto fullFB=device->createFramebuffer(RenderFramebufferDesc(&fullAttachment,1,fullDepth.texture.get()));
                fbset.setTexture(fbset.gBackgroundDepth,fullDepth.texture.get(),RenderTextureLayout::DEPTH_READ,fullDepth.textureView.get());
                for(uint32_t i=0;i<4;++i){const float clipW=1+.018f*(screen[i][1]-32);screen[i][2]=.5f+.5f*(clipW-1)/clipW;screen[i][3]=clipW;world[i][0]=(screen[i][0]-32)/32*clipW;world[i][1]=(32-screen[i][1])/32*clipW;world[i][2]=clipW-1;velocity[i][0]=.25f*clipW;color[i][0]=(i==0||i==3)?.1f:.9f;color[i][1]=i<2?.2f:.8f;}history.matrix[11]=1;
                fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));fill(colorBuffer,color,sizeof(color));fill(historyBuffer,&history,sizeof(history));
                const float fullOptions[4]={benchmarkWidth,benchmarkHeight,12,.5f};
                auto drawFullSource=[&]() {
                    worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::GRAPHICS,{RenderTextureBarrier(full.texture.get(),RenderTextureLayout::COLOR_WRITE),RenderTextureBarrier(fullDepth.texture.get(),RenderTextureLayout::DEPTH_WRITE)});worker.commandList->setFramebuffer(fullFB.get());worker.commandList->clearColor(0,RenderColor(.04f,.1f,.2f,1));worker.commandList->clearDepth();worker.commandList->setViewports(RenderViewport(0,0,benchmarkWidth,benchmarkHeight));worker.commandList->setScissors(RenderRect(0,0,benchmarkWidth,benchmarkHeight));bindNative();worker.commandList->setPipeline(nativeActorPSO.get());worker.commandList->drawIndexedInstanced(6,1,0,0,0);execute();
                };
                for(uint32_t iteration=0;iteration<4;++iteration) {
                    drawFullSource();
                    require(motion.ensureTargets(&worker,&full,&fullDepth,&library),"Full-resolution benchmark preparation failed");
                    const auto begin=std::chrono::steady_clock::now();
                    worker.commandList->begin();require(motion.beginMask(&worker,&library),"Full-resolution benchmark capture failed");drawMask();motion.finishMask(&worker);require(motion.resolve(&worker,fullOptions),"Full-resolution benchmark resolve failed");execute();
                    const double elapsed=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-begin).count();
                    std::printf("MOTION_BENCHMARK width=%u height=%u samples=%u iteration=%u warm=%u record_submit_gpu_drain_ms=%.3f\n",benchmarkWidth,benchmarkHeight,samples,iteration,unsigned(iteration!=0),elapsed);
                }
                drawFullSource();const auto fullNative=readback(full.texture.get(),full.format,4,ms,benchmarkWidth,benchmarkHeight);
                uint64_t previousDifference=0;
                for(float displacement:{0.f,.1f,.25f,.5f,1.f,2.f}) {
                    for(uint32_t i=0;i<4;++i)velocity[i][0]=2*displacement/benchmarkWidth*screen[i][3];
                    fill(velocityBuffer,velocity,sizeof(velocity));drawFullSource();
                    require(motion.ensureTargets(&worker,&full,&fullDepth,&library),"Full-resolution subpixel preparation failed");
                    worker.commandList->begin();require(motion.beginMask(&worker,&library),"Full-resolution subpixel capture failed");drawMask();motion.finishMask(&worker);
                    const float subpixelOptions[4]={benchmarkWidth,benchmarkHeight,12,1};require(motion.resolve(&worker,subpixelOptions),"Full-resolution subpixel resolve failed");execute();
                    const auto image=readback(full.texture.get(),full.format,4,ms,benchmarkWidth,benchmarkHeight);uint64_t difference=0;size_t changed=0;bool alpha=true,local=true;
                    for(uint32_t y=0;y<benchmarkHeight;++y)for(uint32_t x=0;x<benchmarkWidth;++x){const size_t p=(size_t(y)*benchmarkWidth+x)*4;bool pixel=false;for(uint32_t c=0;c<3;++c){const uint32_t d=uint32_t(std::abs(int(image[p+c])-int(fullNative[p+c])));difference+=d;pixel|=d!=0;}changed+=pixel;alpha&=image[p+3]==fullNative[p+3];local&=!pixel||(x>=630&&x<=1062&&y>=358&&y<=602);}
                    std::printf("MOTION_SUBPIXEL width=%u height=%u samples=%u displacement=%.2f changed=%zu absolute_rgb_difference=%llu alpha=%u local=%u\n",benchmarkWidth,benchmarkHeight,samples,double(displacement),changed,static_cast<unsigned long long>(difference),unsigned(alpha),unsigned(local));
                    require(alpha&&local,"Full-resolution subpixel blur changed native alpha or an unswept region");
                    if(displacement==0)require(image==fullNative,"Zero full-resolution motion changed native pixels");
                    else require(changed>0&&difference>=previousDifference,"Full-resolution subpixel motion switched off or decreased instead of fading continuously");
                    previousDifference=difference;
                }
                motion.waitForPending();motion.reset();std::printf("PASS: %zu full-resolution motion benchmark checks; wall time includes command recording, submission and GPU completion.\n",checks);return 0;
            }
            auto mask=device->createTexture(RenderTextureDesc::ColorTarget(W,H,RenderFormat::R32G32B32A32_FLOAT,ms));
            const RenderTexture *maskAttachment=mask.get();auto maskFB=device->createFramebuffer(RenderFramebufferDesc(&maskAttachment,1,depth.texture.get(),true));
            auto renderMask=[&]() {
                fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));fill(historyBuffer,&history,sizeof(history));fill(screenBuffer,screen,sizeof(screen));fill(rdpBuffer,&rdp,sizeof(rdp));
                worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::GRAPHICS,{RenderTextureBarrier(mask.get(),RenderTextureLayout::COLOR_WRITE),RenderTextureBarrier(depth.texture.get(),RenderTextureLayout::DEPTH_READ)});worker.commandList->setFramebuffer(maskFB.get());worker.commandList->setViewports(RenderViewport(0,0,W,H));worker.commandList->setScissors(RenderRect(0,0,W,H));worker.commandList->clearColor(0,RenderColor(0,0,0,0));drawMask();execute();return readback(mask.get(),RenderFormat::R32G32B32A32_FLOAT,16,ms);
            };
            auto rawCenterFlow=[&](const std::vector<uint8_t>&bytes){std::array<float,4> f{};std::memcpy(f.data(),&bytes[(32*W+32)*16],16);return f;};
            auto centerFlow=[&](const std::vector<uint8_t>&bytes){auto f=rawCenterFlow(bytes);if(f[3]>0)f[3]-=2*std::floor(f[3]*.5f);return f;};
            drawSource();const auto native=readback(scene.texture.get(),scene.format,4,ms);
            auto expectedFlow=[&](float x,float y,float alpha,const char *name) {const auto f=centerFlow(renderMask());std::printf("%ux motion mask %s: %.6f %.6f depth%.6f alpha%.6f\n",samples,name,f[0],f[1],f[2],f[3]);require(std::abs(f[0]-x)<.0002f&&std::abs(f[1]-y)<.0002f&&std::abs(f[3]-alpha)<.001f,name);};
            expectedFlow(.125f,0,1,"native world velocity");
            for(uint32_t actor=1;actor<=4;++actor){push.padding.x=actor;const auto packed=rawCenterFlow(renderMask());require(std::abs(packed[3]-(2*actor+1))<.001f,"Motion mask lost the native racer identity");}push.padding.x=0;
            // Short first intervals at native-pair boundaries have the same
            // exposure as ordinary presentations after blur-only correction.
            for(float fraction:{1.f,.8f,.6f,.4f,.2f}) {
                for(auto &v:velocity)v[0]=.25f*fraction;
                const float scale=1/fraction;uint32_t bits;std::memcpy(&bits,&scale,4);push.padding.y=bits;push.padding.z=1;
                expectedFlow(.125f,0,1,"native-pair timing normalization");
            }
            push.padding.y=0;expectedFlow(0,0,0,"explicit camera-cut timing suppression");push.padding.y=0;push.padding.z=0;for(auto &v:velocity)v[0]=.25f;
            // Native opaque blenders output alpha1 regardless of primitive
            // alpha. Use the native alpha blender for fractional-mask cases.
            rp.omL=0x005049d8;fill(rpBuffer,&rp,sizeof(rp));
            for(float alpha:{0.f,179.f/255,1.f}){rdp.primColor.w=alpha;expectedFlow(.125f,0,alpha,"native mask alpha");}rdp.primColor.w=1;
            rp.omL=0;fill(rpBuffer,&rp,sizeof(rp));
            for(auto &v:velocity)v[0]=0;expectedFlow(0,0,1,"stationary actor");
            history.matrix[12]=-.25f;expectedFlow(.125f,0,1,"previous camera translation");
            history.matrix[12]=0;history.matrix[0]=.5f;
            const auto projected=centerFlow(renderMask());require(std::abs(projected[0]-.00390625f)<.0002f,"Previous projection was not evaluated at the current receiver");
            history.matrix[0]=1;for(auto &v:velocity)v[0]=.25f;
            history.matrix[3]=.5f; // Previous clip W varies across the actor.
            const double currentX=.5/32,currentY=-.5/32,previousX=currentX-.25,previousW=1+.5*previousX;
            expectedFlow(float((currentX-previousX/previousW)*.5),float((-currentY+currentY/previousW)*.5),1,"perspective previous clip W");
            history.matrix[3]=0;history.scale[0]=16;history.translate[0]=36;
            expectedFlow(float((32.5-(previousX*16+36))/64),0,1,"native viewport scale and translation");
            history.scale[0]=32;history.translate[0]=32;
            for(uint32_t invalid=0;invalid<5;++invalid){const auto saved=history;const float savedV=velocity[0][0];
                if(invalid==0)history.scale[3]=0;
                if(invalid==1)history.matrix[15]=.001f;
                if(invalid==2)history.matrix[15]=std::numeric_limits<float>::quiet_NaN();
                if(invalid==3)for(auto &v:velocity)v[0]=std::numeric_limits<float>::infinity();
                if(invalid==4)for(auto &v:velocity)v[0]=2;
                const auto f=centerFlow(renderMask());require(f[0]==0&&f[1]==0,"Invalid/cut/teleported history generated motion");
                history=saved;for(auto &v:velocity)v[0]=savedV;
            }
            for(auto &v:screen)v[3]=.001f;const auto nearClip=centerFlow(renderMask());require(nearClip[3]==0,"Current near-plane crossing produced a motion mask");for(auto &v:screen)v[3]=1;
            for(auto &v:world)v[2]=std::numeric_limits<float>::quiet_NaN();const auto invalidWorld=centerFlow(renderMask());require(invalidWorld[0]==0&&invalidWorld[1]==0,"Invalid world position generated motion");for(auto &v:world)v[2]=0;
            const float validOptions[4]={W,H,8,1};
            auto resolve=[&](const float *options,bool hud=false) {
                fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));fill(historyBuffer,&history,sizeof(history));fill(rdpBuffer,&rdp,sizeof(rdp));drawSource();
                require(motion.ensureTargets(&worker,&scene,&depth,&library),"Motion resource preparation failed");
                worker.commandList->begin();require(motion.beginMask(&worker,&library),"Production scene copy/mask begin failed");drawMask();motion.finishMask(&worker);require(motion.resolve(&worker,options),"Production motion resolve failed");
                if(hud){worker.commandList->setFramebuffer(fixtureFB.get());RenderRect r(28,28,36,36);worker.commandList->clearColor(0,RenderColor(1,0,1,1),&r,1);}
                execute();return readback(scene.texture.get(),scene.format,4,ms);
            };
            for(auto &v:velocity)v[0]=0;require(resolve(validOptions)==native,"Stationary resolve changed native pixels");
            for(auto &v:velocity)v[0]=.25f;
            const auto blurred=resolve(validOptions);require(resolve(validOptions)==blurred,"Repeated motion frame was unstable");
            for(uint32_t actor:{1u,2u,4u,8u}){push.padding.x=actor;require(resolve(validOptions)==blurred,"Native racer tile guide lane lost or changed identical motion");}push.padding.x=0;
            size_t changed=0,trailing=0;bool bounded=true,alphaSame=true;
            for(uint32_t y=0;y<H;++y)for(uint32_t x=0;x<W;++x){const size_t p=(y*W+x)*4;const bool diff=std::memcmp(&blurred[p],&native[p],3)!=0;changed+=diff;trailing+=diff&&x<24&&y>=24&&y<40;bounded&=!diff||(x>=16&&x<=40&&y>=22&&y<=41);alphaSame&=blurred[p+3]==native[p+3];}
            std::printf("%ux motion resolve: changed%zu trailing%zu alpha-preserved%u\n",samples,changed,trailing,unsigned(alphaSame));
            require(changed>100&&trailing>50&&bounded&&alphaSame,"Moving actor lacks bounded outside-mask trailing coverage or altered native alpha");
            const float radius12[4]={W,H,12,1};
            for(uint32_t displacement:{2u,4u,8u,12u}) {
                for(auto &v:velocity)v[0]=float(displacement)/32;
                const auto smallMotion=resolve(radius12);size_t trail=0;bool footprint=true;
                for(uint32_t y=0;y<H;++y)for(uint32_t x=0;x<W;++x){const size_t p=(y*W+x)*4;const bool diff=std::memcmp(&smallMotion[p],&native[p],3)!=0;trail+=diff&&x<24;footprint&=!diff||(x>=24-displacement&&x<=40&&y>=24&&y<40);}
                std::printf("%ux motion displacement%u radius12: trailing%zu\n",samples,displacement,trail);
                require(trail==16*displacement&&footprint,"Fixed-radius guide search missed short motion or changed unswept pixels");
            }
            for(auto &v:velocity)v[0]=.25f;
            {
                // One fully covered actor pixel over a constant background has
                // an independent linear exposure oracle. Source RGB at its edge
                // is already bilinearly mixed, so coverage must not be squared.
                float wideScreen[4][4],wideWorld[4][4];std::memcpy(wideScreen,screen,sizeof(screen));std::memcpy(wideWorld,world,sizeof(world));
                fixture[2]=31;fixture[3]=32;for(uint32_t i=0;i<4;++i){screen[i][0]=(i==0||i==3)?31.f:32.f;world[i][0]=(screen[i][0]-32)/32;}
                fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));drawSource();const auto thinNative=readback(scene.texture.get(),scene.format,4,ms);const auto thinBlur=resolve(validOptions);
                double maximumError=0;size_t samplesCompared=0;bool linearExposure=true;
                for(uint32_t x=22;x<34;++x){const size_t p=(32*W+x)*4;double expected[3]={};
                    for(uint32_t tap=0;tap<12;++tap){const double q=x+8.0*tap/11;const uint32_t left=uint32_t(std::floor(q)),right=left+1;const double fraction=q-left;for(uint32_t c=0;c<3;++c)expected[c]+=(1-fraction)*thinNative[(32*W+left)*4+c]+fraction*thinNative[(32*W+right)*4+c];}
                    for(uint32_t c=0;c<3;++c){const double error=std::abs(thinBlur[p+c]-expected[c]/12);maximumError=std::max(maximumError,error);linearExposure&=error<=1.1;++samplesCompared;}
                }
                std::printf("%ux thin actor linear exposure: comparisons%zu max_channel_error%.6f\n",samples,samplesCompared,maximumError);require(linearExposure,"Thin actor edge coverage was multiplied twice or exposure is not linear");
                fixture[2]=24;fixture[3]=40;std::memcpy(screen,wideScreen,sizeof(screen));std::memcpy(world,wideWorld,sizeof(world));fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));
            }
            // Independent 1D shutter integral: native mask coverage is linearly
            // interpolated at each of 12 taps, including partial edge coverage.
            bool integration=true;size_t compared=0;
            for(uint32_t x=18;x<40;++x){const size_t p=(32*W+x)*4;double expected[3]={};
                for(uint32_t i=0;i<12;++i){const double q=x+8.0*i/11;const int l=int(std::floor(q)),r=l+1;const double f=q-l;
                    const double leftWeight=(x>=24|| (l>=24&&l<40))?1-f:0;
                    const double rightWeight=(x>=24|| (r>=24&&r<40))?f:0;
                    for(uint32_t c=0;c<3;++c)expected[c]+=native[p+c]+leftWeight*(native[(32*W+l)*4+c]-native[p+c])+rightWeight*(native[(32*W+r)*4+c]-native[p+c]);
                }for(uint32_t c=0;c<3;++c)integration&=std::abs(blurred[p+c]-expected[c]/12)<=1.1;++compared;
            }require(integration&&compared==22,"Production blur disagreed with analytic 12-tap horizontal integration");
            rp.omL=0x005049d8;fill(rpBuffer,&rp,sizeof(rp));
            for(float alpha:{0.f,179.f/255,1.f}){rdp.primColor.w=alpha;const auto pixels=resolve(validOptions);bool same=true;for(size_t p=3;p<pixels.size();p+=4)same&=pixels[p]==native[p];require(same,"Mask coverage modified destination alpha");if(alpha==0)require(pixels==native,"Zero-alpha actor changed scene");}rdp.primColor.w=1;
            rp.omL=0;fill(rpBuffer,&rp,sizeof(rp));
            float noBlur[4]={W,H,0,1};require(resolve(noBlur)==native,"Zero radius changed native image");noBlur[2]=8;noBlur[3]=0;require(resolve(noBlur)==native,"Zero shutter changed native image");
            fixture[0]=1;drawSource();const auto occluderNative=readback(scene.texture.get(),scene.format,4,ms);const auto occluded=resolve(validOptions);bool protectedPixels=true;
            for(uint32_t y=20;y<44;++y)for(uint32_t x=18;x<23;++x){const size_t p=(y*W+x)*4;protectedPixels&=std::memcmp(&occluded[p],&occluderNative[p],4)==0;}require(protectedPixels,"Motion blurred across a nearer solid occluder");fixture[0]=0;
            {
                // A different stationary racer covers the middle of a moving
                // one. Its own mask identity must not inherit the rear velocity.
                float rearScreen[4][4],rearWorld[4][4],rearVelocity[4][4];std::memcpy(rearScreen,screen,sizeof(screen));std::memcpy(rearWorld,world,sizeof(world));std::memcpy(rearVelocity,velocity,sizeof(velocity));
                fixture[0]=4;drawSource();const auto twoNative=readback(scene.texture.get(),scene.format,4,ms);
                require(motion.ensureTargets(&worker,&scene,&depth,&library),"Two-racer preparation failed");worker.commandList->begin();require(motion.beginMask(&worker,&library),"Two-racer source capture failed");push.padding.x=1;drawMask();execute();
                for(uint32_t i=0;i<4;++i){screen[i][0]=(i==0||i==3)?28.f:36.f;screen[i][2]=.25f;world[i][0]=(screen[i][0]-32)/32;for(float &v:velocity[i])v=0;}
                fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));
                worker.commandList->begin();worker.commandList->setFramebuffer(motion.maskFramebuffer());worker.commandList->setViewports(RenderViewport(0,0,W,H));worker.commandList->setScissors(RenderRect(0,0,W,H));push.padding.x=2;drawMask();motion.finishMask(&worker);require(motion.resolve(&worker,validOptions),"Two-racer resolve failed");execute();
                const auto twoOutput=readback(scene.texture.get(),scene.format,4,ms);bool stationaryFront=true;size_t rearTrail=0;
                for(uint32_t y=24;y<40;++y)for(uint32_t x=16;x<40;++x){const size_t p=(y*W+x)*4;const bool differs=std::memcmp(&twoOutput[p],&twoNative[p],4)!=0;if(x>=28&&x<36)stationaryFront&=!differs;if(x<24)rearTrail+=differs;}
                std::printf("%ux two native racers: stationary-front%u rear-trail%zu\n",samples,unsigned(stationaryFront),rearTrail);require(stationaryFront&&rearTrail>50,"A different foreground racer inherited rear motion or suppressed its visible trail");
                fixture[0]=0;push.padding.x=0;std::memcpy(screen,rearScreen,sizeof(screen));std::memcpy(world,rearWorld,sizeof(world));std::memcpy(velocity,rearVelocity,sizeof(velocity));fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));
            }
            const auto hud=resolve(validOptions,true);bool hudPreserved=true;for(uint32_t y=28;y<36;++y)for(uint32_t x=28;x<36;++x){const size_t p=(y*W+x)*4;hudPreserved&=hud[p]==255&&hud[p+1]==0&&hud[p+2]==255&&hud[p+3]==255;}require(hudPreserved,"Post-resolve HUD sentinel was filtered");
            {
                // Previously all depth fixtures were constant. The real native
                // actor produces sloped per-sample depths while a pixel shader's
                // SV_POSITION.z is evaluated at the pixel center. Comparing it
                // with the MINIMUM MSAA sample rejects the actor's own surface.
                float savedScreen[4][4],savedWorld[4][4],savedVelocity[4][4],savedColors[4][4];
                std::memcpy(savedScreen,screen,sizeof(screen));std::memcpy(savedWorld,world,sizeof(world));std::memcpy(savedVelocity,velocity,sizeof(velocity));std::memcpy(savedColors,color,sizeof(color));const auto savedHistory=history;
                for(uint32_t slope=0;slope<2;++slope) {
                    size_t minimumInterior=9999,maximumInterior=0;bool allPhases=true,allOccluders=true;
                    for(uint32_t phase=0;phase<8;++phase) {
                        const float shift=float(phase)/8-.4375f;
                        history=savedHistory;history.matrix[11]=1;
                        for(uint32_t i=0;i<4;++i) {
                            const float x=(i==0||i==3?24.f:40.f)+shift,y=(i<2?24.f:40.f)+shift*.375f;
                            const float clipW=1+.018f*(y-32)+(slope?.011f*(x-32):0);
                            screen[i][0]=x;screen[i][1]=y;screen[i][2]=.5f+.5f*(clipW-1)/clipW;screen[i][3]=clipW;
                            world[i][0]=(x-32)/32*clipW;world[i][1]=(32-y)/32*clipW;world[i][2]=clipW-1;world[i][3]=1;
                            velocity[i][0]=.25f*clipW;velocity[i][1]=velocity[i][2]=velocity[i][3]=0;
                            color[i][0]=(i==0||i==3)?.1f:.9f;color[i][1]=i<2?.2f:.8f;color[i][2]=.2f;color[i][3]=1;
                        }
                        fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));fill(colorBuffer,color,sizeof(color));fill(historyBuffer,&history,sizeof(history));
                        fixture[0]=3;drawSource();
                        worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::GRAPHICS,{RenderTextureBarrier(scene.texture.get(),RenderTextureLayout::COLOR_WRITE),RenderTextureBarrier(depth.texture.get(),RenderTextureLayout::DEPTH_WRITE)});
                        worker.commandList->setFramebuffer(fixtureFB.get());worker.commandList->setViewports(RenderViewport(0,0,W,H));worker.commandList->setScissors(RenderRect(0,0,W,H));bindNative();worker.commandList->setPipeline(nativeActorPSO.get());worker.commandList->drawIndexedInstanced(6,1,0,0,0);execute();
                        const auto source=readback(scene.texture.get(),scene.format,4,ms);
                        require(motion.ensureTargets(&worker,&scene,&depth,&library),"Sloped actor resource preparation failed");
                        worker.commandList->begin();require(motion.beginMask(&worker,&library),"Sloped actor capture failed");drawMask();motion.finishMask(&worker);require(motion.resolve(&worker,validOptions),"Sloped actor resolve failed");execute();
                        const auto output=readback(scene.texture.get(),scene.format,4,ms);size_t interior=0;bool occluder=true;
                        for(uint32_t y=27;y<37;++y)for(uint32_t x=27;x<37;++x){const size_t p=(y*W+x)*4;interior+=std::memcmp(&source[p],&output[p],3)!=0;}
                        for(uint32_t y=20;y<44;++y)for(uint32_t x=18;x<23;++x){const size_t p=(y*W+x)*4;occluder&=std::memcmp(&source[p],&output[p],4)==0;}
                        minimumInterior=std::min(minimumInterior,interior);maximumInterior=std::max(maximumInterior,interior);allPhases&=interior>=95;allOccluders&=occluder;
                        std::printf("%ux sloped native actor slope%u phase%u: moving-interior%zu/100 occluder%u\n",samples,slope,phase,interior,unsigned(occluder));
                    }
                    require(allPhases&&minimumInterior>=95&&maximumInterior-minimumInterior<=5,"Sloped native actor blur broke up across subpixel presentations");
                    require(allOccluders,"Sloped native actor blur crossed a nearer solid occluder");
                }
                history=savedHistory;fixture[0]=0;std::memcpy(screen,savedScreen,sizeof(screen));std::memcpy(world,savedWorld,sizeof(world));std::memcpy(velocity,savedVelocity,sizeof(velocity));std::memcpy(color,savedColors,sizeof(color));
                fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));fill(colorBuffer,color,sizeof(color));fill(historyBuffer,&history,sizeof(history));
            }
            require(motion.prepare(device.get(),layout.get(),ms,false)&&motion.getMask(false,true)==maskPSO,"Ready motion configuration did not retain its PSO");
            // A new frame/target cannot resolve stale mask data.
            require(motion.ensureTargets(&worker,&scene,&depth,&library),"Repeated target preparation failed");worker.commandList->begin();require(!motion.resolve(&worker,validOptions),"Prepared empty frame reused stale motion mask");execute();
            for(uint32_t replacement=0;replacement<20;++replacement) {
                // Repeat some dimensions with distinct color/depth objects as
                // well as exceeding the old 16-target retention limit.
                const uint32_t width=W+replacement/2;
                RenderTarget replacedColor(0,Framebuffer::Type::Color,ms,false),replacedDepth(0,Framebuffer::Type::Depth,ms,false);
                replacedColor.resize(&worker,width,H);replacedDepth.resize(&worker,width,H);
                const RenderTexture *colorAttachment=replacedColor.texture.get();
                auto replacedFB=device->createFramebuffer(RenderFramebufferDesc(&colorAttachment,1,replacedDepth.texture.get()));
                worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::GRAPHICS,{RenderTextureBarrier(replacedColor.texture.get(),RenderTextureLayout::COLOR_WRITE),RenderTextureBarrier(replacedDepth.texture.get(),RenderTextureLayout::DEPTH_WRITE)});
                worker.commandList->setFramebuffer(replacedFB.get());worker.commandList->clearColor(0,RenderColor(.1f,.2f,.3f,.6f));worker.commandList->clearDepth();execute();
                require(motion.ensureTargets(&worker,&replacedColor,&replacedDepth,&library),"Repeated native target replacement exhausted or reused stale resources");
                worker.commandList->begin();require(motion.beginMask(&worker,&library),"Replacement target capture failed");motion.finishMask(&worker);
                const float replacedOptions[4]={float(width),H,8,1};require(motion.resolve(&worker,replacedOptions),"Replacement target resolve failed");execute();
            }
            {
                // Native targets retain a larger allocation when the active
                // framebuffer shrinks. Flow and resolve coverage must follow
                // the active viewport, with no write into the unused border.
                constexpr uint32_t backingWidth=128,backingHeight=96,activeWidth=64,activeHeight=48;
                RenderTarget grown(0,Framebuffer::Type::Color,ms,false),grownDepth(0,Framebuffer::Type::Depth,ms,false);
                grown.resize(&worker,backingWidth,backingHeight);grownDepth.resize(&worker,backingWidth,backingHeight);
                const RenderTexture *grownAttachment=grown.texture.get();auto grownFB=device->createFramebuffer(RenderFramebufferDesc(&grownAttachment,1,grownDepth.texture.get()));
                worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::GRAPHICS,{RenderTextureBarrier(grown.texture.get(),RenderTextureLayout::COLOR_WRITE),RenderTextureBarrier(grownDepth.texture.get(),RenderTextureLayout::DEPTH_WRITE)});
                worker.commandList->setFramebuffer(grownFB.get());worker.commandList->setGraphicsPipelineLayout(fixtureLayout.get());worker.commandList->setGraphicsPushConstants(0,fixture);worker.commandList->setPipeline(fixturePSO.get());worker.commandList->setViewports(RenderViewport(0,0,backingWidth,backingHeight));worker.commandList->setScissors(RenderRect(0,0,backingWidth,backingHeight));worker.commandList->setVertexBuffers(0,nullptr,0,nullptr);worker.commandList->setIndexBuffer(nullptr);worker.commandList->drawInstanced(3,1,0,0);execute();
                const auto grownNative=readback(grown.texture.get(),grown.format,4,ms,backingWidth,backingHeight);
                for(uint32_t i=0;i<4;++i){screen[i][1]=(i<2?24.f:40.f)*float(H)/activeHeight;world[i][1]=(32-screen[i][1])/32;velocity[i][0]=.125f;}
                fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));
                fbset.setTexture(fbset.gBackgroundDepth,grownDepth.texture.get(),RenderTextureLayout::DEPTH_READ,grownDepth.textureView.get());
                require(motion.ensureTargets(&worker,&grown,&grownDepth,&library),"Grown target preparation failed");
                worker.commandList->begin();require(motion.beginMask(&worker,&library),"Grown target capture failed");worker.commandList->setViewports(RenderViewport(0,0,activeWidth,activeHeight));worker.commandList->setScissors(RenderRect(0,0,activeWidth,activeHeight));drawMask();motion.finishMask(&worker);
                const float activeOptions[4]={activeWidth,activeHeight,8,1};require(motion.resolve(&worker,activeOptions),"Active viewport was rejected within grown native backing");execute();
                const auto activeBlur=readback(grown.texture.get(),grown.format,4,ms,backingWidth,backingHeight);
                auto *nativeMask=const_cast<D3D12Texture*>(static_cast<D3D12Framebuffer*>(motion.maskFramebuffer())->colorTargets[0]);
                const auto actualMask=readback(nativeMask,RenderFormat::R32G32B32A32_FLOAT,16,ms,backingWidth,backingHeight);
                size_t actualCoverage=0;float fminX=999,fmaxX=-999;uint32_t minX=999,minY=999,maxX=0,maxY=0;
                for(uint32_t y=0;y<backingHeight;++y)for(uint32_t x=0;x<backingWidth;++x){float m[4];std::memcpy(m,&actualMask[(y*backingWidth+x)*16],16);if(m[3]>0){++actualCoverage;minX=std::min(minX,x);maxX=std::max(maxX,x);minY=std::min(minY,y);maxY=std::max(maxY,y);fminX=std::min(fminX,m[0]);fmaxX=std::max(fmaxX,m[0]);}}
                std::printf("Grown native mask coverage%zu bounds%u,%u..%u,%u flow%.7f..%.7f\n",actualCoverage,minX,minY,maxX,maxY,fminX,fmaxX);
                size_t activeTrailing=0;bool untouchedBorder=true,extent=true;
                for(uint32_t y=0;y<backingHeight;++y)for(uint32_t x=0;x<backingWidth;++x){const size_t p=(y*backingWidth+x)*4;const bool diff=std::memcmp(&activeBlur[p],&grownNative[p],4)!=0;untouchedBorder&=!diff||(x<activeWidth&&y<activeHeight);extent&=!diff||(x>=20&&x<=40&&y>=22&&y<=41);activeTrailing+=diff&&x<24;}
                std::printf("%ux active64x48/backing128x96 motion: trailing%zu border-preserved%u\n",samples,activeTrailing,unsigned(untouchedBorder));
                require(activeTrailing==64&&untouchedBorder&&extent,"Blur used backing dimensions for flow or modified its inactive border");
                for(uint32_t i=0;i<4;++i){screen[i][1]=i<2?24.f:40.f;world[i][1]=(32-screen[i][1])/32;velocity[i][0]=.25f;}
                fill(screenBuffer,screen,sizeof(screen));fill(worldBuffer,world,sizeof(world));fill(velocityBuffer,velocity,sizeof(velocity));
            }
        }
        motion.waitForPending();motion.reset();std::printf("PASS: %zu production motion shader/resource checks at 1x/4x MSAA.\n",checks);return 0;
    }catch(const std::exception &e){std::fprintf(stderr,"FAIL after %zu checks: %s\n",checks,e.what());return 1;}
}
