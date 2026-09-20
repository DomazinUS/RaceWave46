// Runs before the inline-ray capability gate. The common layout explicitly
// excludes AS descriptors, and this fixture never constructs an RT scene.
void verifyRasterShadows(RenderDevice *device, FixtureWorker &worker, const std::string &prefix) {
    constexpr uint32_t W = 64, H = 64, MapSize = 1024;
    std::vector<std::unique_ptr<RenderBuffer>> buffers;
    auto upload = [&](const void *data, size_t bytes, RenderBufferFlags flags) {
        auto buffer = device->createBuffer(RenderBufferDesc::UploadBuffer(
            (flags & RenderBufferFlag::CONSTANT) ? (bytes + 255) & ~uint64_t(255) : bytes, flags));
        require(buffer != nullptr, "Raster-shadow upload allocation failed");
        fill(buffer.get(), data, bytes);
        auto *result = buffer.get(); buffers.push_back(std::move(buffer)); return result;
    };
    SamplerLibrary samplers;
    fillSamplers(device, samplers.nearest, RenderFilter::NEAREST);
    fillSamplers(device, samplers.linear, RenderFilter::LINEAR);
    FramebufferRendererDescriptorCommonSet common(samplers, false, device);
    FramebufferRendererDescriptorTextureSet textures(device, 1);
    FramebufferRendererDescriptorFramebufferSet framebufferSet(device);
    require(common.SceneBVH == 0, "Raster-shadow fixture declares an AS descriptor");
    RenderPipelineLayoutBuilder builder;
    builder.begin(false, true);
    builder.addPushConstant(0, 0, sizeof(interop::RasterParams), RenderShaderStageFlag::VERTEX | RenderShaderStageFlag::PIXEL);
    builder.addDescriptorSet(common); builder.addDescriptorSet(textures);
    builder.addDescriptorSet(textures); builder.addDescriptorSet(framebufferSet); builder.end();
    auto layout = builder.create(device);
    require(layout != nullptr, "Raster-shadow production layout creation failed");

    // Receiver at y=0. Two coincident footprints at y=1 and y=.5 test real
    // capture depth, draw-order independence and overlapping caster behavior.
    float world[12][4] = {{-1,0,1,1},{1,0,1,1},{1,0,-1,1},{-1,0,-1,1},
        {-.5f,1,.5f,1},{.5f,1,.5f,1},{.5f,1,-.5f,1},{-.5f,1,-.5f,1},
        {-.5f,.5f,.5f,1},{.5f,.5f,.5f,1},{.5f,.5f,-.5f,1},{-.5f,.5f,-.5f,1}};
    float screen[12][4] = {{0,0,.5f,1},{64,0,.5f,1},{64,64,.5f,1},{0,64,.5f,1}};
    for (uint32_t v = 4; v < 12; ++v) std::copy(screen[v % 4], screen[v % 4] + 4, screen[v]);
    float uv[12][2]{};
    float colors[12][4]; for (auto &v : colors) for (float &c : v) c = 1;
    uint32_t indices[18] = {0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11};
    auto *positions = upload(world, sizeof(world), RenderBufferFlag::STORAGE);
    auto *faces = upload(indices, sizeof(indices), RenderBufferFlag::INDEX | RenderBufferFlag::STORAGE);
    auto *screens = upload(screen, sizeof(screen), RenderBufferFlag::VERTEX);
    auto *uvs = upload(uv, sizeof(uv), RenderBufferFlag::VERTEX);
    auto *shades = upload(colors, sizeof(colors), RenderBufferFlag::VERTEX);
    interop::FrameParams frame{};
    interop::FramebufferParams fb{};
    fb.resolution = hlslpp::float2(W,H); fb.resolutionScale = hlslpp::float2(1,1);
    interop::RenderIndices ri[3] = {{0,0,0,1,0},{1,0,0,0,0},{2,6,0,0,0}};
    interop::RenderParams rp[3]{};
    for (auto &p : rp) {
        p.ccL=(8u<<20)|(31u<<15)|(7u<<12)|(7u<<9)|(8u<<5)|31u;
        p.ccH=(8u<<28)|(8u<<24)|(7u<<21)|(7u<<18)|(3u<<15)|(7u<<12)|(3u<<9)|(3u<<6)|(7u<<3)|3u;
        p.flags.NoN=1; p.flags.smoothShade=1;
    }
    // Native water combiner/blender with a synthetic constant RGBA texture.
    rp[0].ccL=0xFCFFFFFF; rp[0].ccH=0xFFFCF279;
    rp[0].omL=0x005049D8; rp[0].omH=0x00082CFF;
    rp[0].flags.usesTexture0=1; rp[0].flags.nativeSampler0=NATIVE_SAMPLER_CLAMP_CLAMP;
    rp[0].flags.cms0=rp[0].flags.cmt0=2;
    interop::RDPParams rdp[3]{};
    rdp[0].primColor=hlslpp::float4(1,1,1,1);
    rdp[1].primColor=hlslpp::float4(.8f,.6f,.4f,1);
    rdp[2].primColor=hlslpp::float4(1,1,1,1);
    rdp[2].blendColor=hlslpp::float4(0,0,0,.5f);
    interop::RDPTile tile{}; tile.shifts=tile.shiftt=1; tile.lrs=tile.lrt=63*4;
    tile.cms=tile.cmt=2; tile.fmt=0; tile.siz=3; tile.stride=256; tile.nativeSampler=NATIVE_SAMPLER_CLAMP_CLAMP;
    interop::GPUTile gpuTile{}; gpuTile.ulScale=gpuTile.tcScale=hlslpp::float2(1,1);
    gpuTile.textureDimensions=hlslpp::float3(W,H,1);
    Params reflection{}; reflection.enabled=0; reflection.smoothNormals=0;
    Wr64RasterShadowParams shadow{};
    // Deliberately explicit fixture projection: x/z span NDC [-1,1], and
    // depth=.5-y*.25 so a point higher toward the light is nearer.
    shadow.lightRows[0][0]=1; shadow.lightRows[1][2]=1;
    shadow.lightRows[2][1]=-.25f; shadow.lightRows[2][3]=.5f; shadow.lightRows[3][3]=1;
    shadow.options[0]=1.f/MapSize; shadow.options[1]=.001f;
    shadow.options[2]=.18f; shadow.options[3]=.55f;
    shadow.light[1]=1; shadow.light[3]=1;
    auto *shadowBuffer=upload(&shadow,sizeof(shadow),RenderBufferFlag::CONSTANT);
    auto *rpBuffer=upload(rp,sizeof(rp),RenderBufferFlag::STORAGE);
    auto *rdpBuffer=upload(rdp,sizeof(rdp),RenderBufferFlag::STORAGE);
    common.setBuffer(common.FrParams,upload(&frame,sizeof(frame),RenderBufferFlag::CONSTANT),sizeof(frame));
    common.setBuffer(common.RtParams,upload(&reflection,sizeof(reflection),RenderBufferFlag::CONSTANT),sizeof(reflection));
    common.setBuffer(common.wr64RasterShadowParams,shadowBuffer,sizeof(shadow));
    common.setBuffer(common.DynamicRenderParams,rpBuffer,sizeof(rp),RenderBufferStructuredView(sizeof(rp[0])));
    common.setBuffer(common.instanceRenderIndices,upload(ri,sizeof(ri),RenderBufferFlag::STORAGE),sizeof(ri),RenderBufferStructuredView(sizeof(ri[0])));
    common.setBuffer(common.instanceRDPParams,rdpBuffer,sizeof(rdp),RenderBufferStructuredView(sizeof(rdp[0])));
    common.setBuffer(common.RDPTiles,upload(&tile,sizeof(tile),RenderBufferFlag::STORAGE),sizeof(tile),RenderBufferStructuredView(sizeof(tile)));
    common.setBuffer(common.GPUTiles,upload(&gpuTile,sizeof(gpuTile),RenderBufferFlag::STORAGE),sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
    common.setBuffer(common.posBuffer,positions,sizeof(world)); common.setBuffer(common.indexBuffer,faces,sizeof(indices));
    framebufferSet.setBuffer(framebufferSet.FbParams,upload(&fb,sizeof(fb),RenderBufferFlag::CONSTANT),sizeof(fb));
    Pixels waterTexels(W*H*4);
    auto waterTexture=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
    auto waterView=waterTexture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
    auto *waterUpload=upload(waterTexels.data(),waterTexels.size(),0);
    textures.setTexture(0,waterTexture.get(),RenderTextureLayout::SHADER_READ,waterView.get());
    auto setWaterAlpha=[&](uint8_t alpha) {
        for(size_t p=0;p<waterTexels.size();p+=4) {
            waterTexels[p]=51;waterTexels[p+1]=102;waterTexels[p+2]=153;waterTexels[p+3]=alpha;
        }
        fill(waterUpload,waterTexels.data(),waterTexels.size());
        worker.commandList->begin();
        worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::COPY_DEST));
        worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(waterTexture.get()),
            RenderTextureCopyLocation::PlacedFootprint(waterUpload,RenderFormat::R8G8B8A8_UNORM,W,H,1,W));
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
    };
    setWaterAlpha(128);
    Wr64RasterShadowTarget captureTarget;
    require(captureTarget.ensure(&worker),"Raster-shadow target creation failed");
    require(captureTarget.size()==MapSize && captureTarget.color() && captureTarget.depth(),"Raster-shadow target dimensions/resources changed");
    auto *stableTarget=captureTarget.color();
    require(captureTarget.ensure(&worker) && captureTarget.color()==stableTarget,"Same-size shadow target was recreated");
    common.setTexture(common.wr64RasterShadowMap,captureTarget.color(),RenderTextureLayout::SHADER_READ);
    auto mapReadback=device->createBuffer(RenderBufferDesc::ReadbackBuffer(MapSize*MapSize*4));
    auto copyReadback=[&](RenderTexture *source,RenderBuffer *destination,DXGI_FORMAT format,uint32_t w,uint32_t h) {
        worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(source,RenderTextureLayout::COPY_SOURCE));
        D3D12_TEXTURE_COPY_LOCATION dst{};dst.pResource=static_cast<D3D12Buffer*>(destination)->d3d;
        dst.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;dst.PlacedFootprint.Footprint={format,w,h,1,w*4};
        D3D12_TEXTURE_COPY_LOCATION src{};src.pResource=static_cast<D3D12Texture*>(source)->d3d;
        src.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        static_cast<D3D12CommandList*>(worker.commandList.get())->d3d->CopyTextureRegion(&dst,0,0,0,&src,nullptr);
    };
    const RenderInputSlot slots[]={RenderInputSlot(0,16),RenderInputSlot(1,8),RenderInputSlot(2,16)};
    const RenderVertexBufferView vertices[]={RenderVertexBufferView(screens->at(0),sizeof(screen)),
        RenderVertexBufferView(uvs->at(0),sizeof(uv)),RenderVertexBufferView(shades->at(0),sizeof(colors))};
    const RenderIndexBufferView index(faces->at(0),sizeof(indices),RenderFormat::R32_UINT);
    auto bind=[&]() {
        worker.commandList->setGraphicsPipelineLayout(layout.get());
        worker.commandList->setGraphicsDescriptorSet(common.get(),0);worker.commandList->setGraphicsDescriptorSet(textures.get(),1);
        worker.commandList->setGraphicsDescriptorSet(textures.get(),2);worker.commandList->setGraphicsDescriptorSet(framebufferSet.get(),3);
        worker.commandList->setVertexBuffers(0,vertices,3,slots);worker.commandList->setIndexBuffer(&index);
    };
    Wr64RasterShadowPipelines pipelines;
    auto capture=[&](unsigned casterCount,bool reverse=false,bool cutout=false,bool includeReceiver=false) {
        fill(shadowBuffer,&shadow,sizeof(shadow));fill(rpBuffer,rp,sizeof(rp));fill(rdpBuffer,rdp,sizeof(rdp));
        worker.commandList->begin();
        const RenderTextureBarrier barriers[]={{captureTarget.color(),RenderTextureLayout::COLOR_WRITE},
            {captureTarget.depth(),RenderTextureLayout::DEPTH_WRITE}};
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,barriers,2);
        worker.commandList->setFramebuffer(captureTarget.framebuffer());
        worker.commandList->clearColor(0,RenderColor(1,1,1,1));worker.commandList->clearDepth();
        bind();worker.commandList->setPipeline(pipelines.capture());
        worker.commandList->setViewports(RenderViewport(0,0,MapSize,MapSize));worker.commandList->setScissors(RenderRect(0,0,MapSize,MapSize));
        interop::RasterParams push{};push.screenScale=hlslpp::float2(1,1);push.renderIndex=2;push.padding.x=cutout?2:0;
        if(includeReceiver) {
            push.renderIndex=1;worker.commandList->setGraphicsPushConstants(0,&push);
            worker.commandList->drawIndexedInstanced(6,1,0,0,0);
            push.renderIndex=2;
        }
        worker.commandList->setGraphicsPushConstants(0,&push);
        for(unsigned i=0;i<casterCount;++i) worker.commandList->drawIndexedInstanced(6,1,6+6*(reverse?casterCount-1-i:i),0,0);
        copyReadback(captureTarget.color(),mapReadback.get(),DXGI_FORMAT_R32_FLOAT,MapSize,MapSize);
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(captureTarget.color(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
        std::vector<float> result(MapSize*MapSize);const RenderRange range(0,result.size()*4),noWrite(0,0);
        const void *mapped=mapReadback->map(0,&range);require(mapped,"Raster-shadow map readback failed");
        std::memcpy(result.data(),mapped,result.size()*4);mapReadback->unmap(0,&noWrite);return result;
    };
    size_t darkWater=0,darkWorld=0,stateVariants=0;int maxWaterError=0,maxWorldError=0;
    for(uint32_t samples:{1u,4u}) {
        const RenderMultisampling ms(samples);
        require(pipelines.prepare(device,layout.get(),ms,false,false,Wr64RasterShadowWaterMode::Native),
            "Raster-shadow synchronous Native pipeline preparation failed");
        require(pipelines.capture() && pipelines.nativeWater(false,false,false) &&
            pipelines.world(false,false,false,false,true,true),"Raster-shadow pipeline missing");
        for(auto &p:rp)p.flags.sampleCount=samples==1?0:2;
        const auto singleMap=capture(1);
        for(uint32_t y=8;y<MapSize-8;y+=8) for(uint32_t x=8;x<MapSize-8;x+=8) {
            const bool inside=x>MapSize/4+8 && x<MapSize*3/4-8 && y>MapSize/4+8 && y<MapSize*3/4-8;
            const bool outside=x<MapSize/4-8 || x>MapSize*3/4+8 || y<MapSize/4-8 || y>MapSize*3/4+8;
            if(inside||outside)require(singleMap[y*MapSize+x]==(inside?.25f:1.f),"Real caster capture projection/depth mismatch");
        }
        require(capture(2)==singleMap && capture(2,true)==singleMap,"Overlapping caster map depends on draw order or blends depth");
        rp[2].omL=1;rdp[2].primColor=hlslpp::float4(1,1,1,0);
        const auto cutoutMap=capture(1,false,true);
        require(std::all_of(cutoutMap.begin(),cutoutMap.end(),[](float d){return d==1.f;}),"Native alpha-threshold caster did not discard");
        require(capture(1)==singleMap,"Opaque caster unexpectedly used the cutout flag");
        rdp[2].primColor=hlslpp::float4(1,1,1,1);
        require(capture(1,false,true)==singleMap,"Covered native alpha-threshold caster disappeared");
        rp[2].omL=0;
        auto target=device->createTexture(RenderTextureDesc::ColorTarget(W,H,RenderFormat::R8G8B8A8_UNORM,ms));
        auto depth=device->createTexture(RenderTextureDesc::DepthTarget(W,H,RenderFormat::D32_FLOAT,ms));
        auto resolved=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
        auto readback=device->createBuffer(RenderBufferDesc::ReadbackBuffer(W*H*4));
        const RenderTexture *attachments[]={target.get()};
        auto framebuffer=device->createFramebuffer(RenderFramebufferDesc(attachments,1,depth.get()));
        auto draw=[&](bool water,bool enabled,bool compare=false,bool write=false,bool cvg=false,
            bool cull=false,bool NoN=true,bool alphaBlend=true,float clearDepth=1.f) {
            shadow.light[3]=enabled?1.f:0.f;fill(shadowBuffer,&shadow,sizeof(shadow));
            rp[1].flags.culling=cull;rp[1].flags.NoN=NoN;fill(rpBuffer,rp,sizeof(rp));
            worker.commandList->begin();
            const RenderTextureBarrier barriers[]={{target.get(),RenderTextureLayout::COLOR_WRITE},{depth.get(),RenderTextureLayout::DEPTH_WRITE}};
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,barriers,2);
            worker.commandList->setFramebuffer(framebuffer.get());
            worker.commandList->clearColor(0,RenderColor(.7f,.5f,.3f,0));worker.commandList->clearDepth(true,clearDepth);
            bind();interop::RasterParams push{};push.screenScale=hlslpp::float2(1,1);push.renderIndex=water?0:1;
            worker.commandList->setGraphicsPushConstants(0,&push);
            const auto *pipeline=water?pipelines.nativeWater(compare,write,cvg):pipelines.world(compare,write,cvg,cull,NoN,alphaBlend);
            require(pipeline,"Requested raster-shadow state variant is missing");worker.commandList->setPipeline(pipeline);
            worker.commandList->setViewports(RenderViewport(0,0,W,H));worker.commandList->setScissors(RenderRect(0,0,W,H));
            worker.commandList->drawIndexedInstanced(6,1,0,0,0);
            RenderTexture *source=target.get();
            if(samples>1) {
                const RenderTextureBarrier resolve[]={{target.get(),RenderTextureLayout::RESOLVE_SOURCE},{resolved.get(),RenderTextureLayout::RESOLVE_DEST}};
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,resolve,2);
                worker.commandList->resolveTexture(resolved.get(),target.get());source=resolved.get();
            }
            copyReadback(source,readback.get(),DXGI_FORMAT_R8G8B8A8_UNORM,W,H);
            worker.commandList->end();worker.execute();worker.wait();Pixels result(W*H*4);
            const RenderRange range(0,result.size()),noWrite(0,0);const void *mapped=readback->map(0,&range);
            require(mapped,"Raster-shadow receiver readback failed");std::memcpy(result.data(),mapped,result.size());readback->unmap(0,&noWrite);return result;
        };
        auto comparePixels=[&](const Pixels &off,const Pixels &on,bool water,bool expectVisible) {
            size_t changed=0;
            for(uint32_t y=2;y<H-2;++y)for(uint32_t x=2;x<W-2;++x) {
                const size_t p=(y*W+x)*4;
                require(off[p+3]==on[p+3],"Raster shadow altered native coverage");
                const bool inner=x>=20&&x<44&&y>=20&&y<44;
                const bool outer=x<12||x>=52||y<12||y>=52;
                for(uint32_t c=0;c<3;++c) {
                    require(on[p+c]<=off[p+c]+1,"Raster shadow brightened a native receiver");
                    if(outer)require(on[p+c]==off[p+c],"Raster shadow leaked outside the captured caster");
                    if(inner&&expectVisible) {
                        const int expected=int(std::lround(off[p+c]*(water?.82f:.45f)));
                        const int error=std::abs(int(on[p+c])-expected);
                        if(water)maxWaterError=std::max(maxWaterError,error);else maxWorldError=std::max(maxWorldError,error);
                        require(error<=2,"Raster-shadow native attenuation mismatch");
                    }
                }
                if(inner&&off[p]>on[p]+3)++changed;
            }
            if(expectVisible)require(changed>400,"Raster shadow had no meaningful positive control");
            if(water)darkWater+=changed;else darkWorld+=changed;
        };
        for(uint8_t alpha:{uint8_t(0),uint8_t(64),uint8_t(128),uint8_t(255)}) {
            setWaterAlpha(alpha);
            for(uint32_t flags=0;flags<8;++flags) {
                const bool cmp=flags&1,write=flags&2,cvg=flags&4;
                const auto off=draw(true,false,cmp,write,cvg),on=draw(true,true,cmp,write,cvg);
                comparePixels(off,on,true,true);++stateVariants;
                require(draw(true,false,cmp,write,cvg)==off,"Shadow Off changed native water output");
                if(cmp)require(draw(true,true,cmp,write,cvg,false,true,true,.25f)==
                    draw(true,false,cmp,write,cvg,false,true,true,.25f),"Raster water ignored native depth rejection");
            }
        }
        setWaterAlpha(128);
        const auto waterOff=draw(true,false),waterOn=draw(true,true);
        for(uint32_t flags=0;flags<64;++flags) {
            const bool cmp=flags&1,write=flags&2,cvg=flags&4,cull=flags&8,NoN=flags&16,alphaBlend=flags&32;
            const auto off=draw(false,false,cmp,write,cvg,cull,NoN,alphaBlend);
            const auto on=draw(false,true,cmp,write,cvg,cull,NoN,alphaBlend);
            // Native culling may reject this winding. A nonculled reference
            // always supplies the positive control for every other state.
            comparePixels(off,on,false,!cull);++stateVariants;
            require(draw(false,false,cmp,write,cvg,cull,NoN,alphaBlend)==off,"Shadow Off changed native world output");
            if(cmp)require(draw(false,true,cmp,write,cvg,cull,NoN,alphaBlend,.25f)==
                draw(false,false,cmp,write,cvg,cull,NoN,alphaBlend,.25f),"World shadow ignored native depth rejection");
        }
        const auto worldOff=draw(false,false),worldOn=draw(false,true);
        const size_t p=(32*W+32)*4;
        require(double(waterOn[p])/waterOff[p]>double(worldOn[p])/worldOff[p]+.2,
            "Water shadow is not weaker than the solid receiver shadow");
        capture(2);
        require(draw(true,true)==waterOn && draw(false,true)==worldOn,"Overlapping casters double-attenuated receivers");
        capture(0);
        require(draw(true,true)==waterOff && draw(false,true)==worldOff,"Empty real capture differs from Shadow Off");
        shadow.light[3]=1;capture(1);
        for(float height:{1.f,1.5f}) {
            for(uint32_t v=0;v<4;++v)world[v][1]=height;fill(positions,world,sizeof(world));
            require(draw(true,true)==draw(true,false),"Water receiver at/above caster was shadowed");
            require(draw(false,true)==draw(false,false),"World receiver at/above caster was shadowed");
        }
        for(uint32_t v=0;v<4;++v)world[v][1]=0;fill(positions,world,sizeof(world));
        require(draw(true,true)==waterOn && draw(false,true)==worldOn,"Restored receiver lost its projected shadow");
        writePPM(prefix+"-"+std::to_string(samples)+"x-water.ppm",waterOn);
        writePPM(prefix+"-"+std::to_string(samples)+"x-world.ppm",worldOn);

        // A visible native receiver also participates in the real depth
        // capture. Wider light framing makes neighboring PCF texels land at
        // different depths on its slope, reproducing the missing flat-quad
        // coverage. These explicit matrices do not use the production fitter.
        float savedWorld[12][4],savedScreen[12][4];uint32_t savedIndices[18];
        std::memcpy(savedWorld,world,sizeof(world));std::memcpy(savedScreen,screen,sizeof(screen));
        std::memcpy(savedIndices,indices,sizeof(indices));const auto savedShadow=shadow;
        struct Slope { float x,z,xExtent,lightScale; };
        const Slope slopes[]={{.5f,.3f,1.f,.125f},{-.5f,-.3f,1.f,.125f},{12.f,.25f,.125f,.5f}};
        struct Placement { float texelX,texelY,origin; };
        const Placement placements[]={{0,0,0},{.375f,.625f,1024.f},{-.3125f,.1875f,-512.f}};
        const float cameras[][2]={{0,0},{5,-3},{-4,2},{.375f,-.25f}};
        size_t slopeSelfPixels=0,slopeGapPixels=0,cameraComparedPixels=0;
        double maximumShadowCentroidDrift=0;
        for(const auto &slope:slopes)for(bool reversed:{false,true})for(const auto &placement:placements) {
            const float origin[3]={placement.origin,placement.origin*.5f,-placement.origin*2.f};
            shadow=savedShadow;
            shadow.lightRows[0][0]=slope.lightScale;
            shadow.lightRows[1][2]=slope.lightScale;
            shadow.lightRows[0][3]=-origin[0]*slope.lightScale+2*placement.texelX/MapSize;
            shadow.lightRows[1][3]=-origin[2]*slope.lightScale-2*placement.texelY/MapSize;
            shadow.lightRows[2][3]=.5f+.25f*origin[1];
            for(uint32_t v=0;v<12;++v) {
                const float x=savedWorld[v][0]*slope.xExtent,z=savedWorld[v][2];
                world[v][0]=x+origin[0];world[v][2]=z+origin[2];
                // Central patch has a genuine small gap. A blanket bias large
                // enough to hide steep-plane acne must not erase this shadow.
                world[v][1]=slope.x*x+slope.z*z+origin[1]+(v>=4?.04f:0.f);
            }
            std::memcpy(indices,savedIndices,sizeof(indices));
            if(reversed)for(uint32_t face=0;face<18;face+=3)std::swap(indices[face],indices[face+1]);
            fill(positions,world,sizeof(world));fill(faces,indices,sizeof(indices));
            const auto selfMap=capture(0,false,false,true);
            // Check several interior map texels against the analytic plane,
            // proving that the sloped receiver was captured, not skipped.
            for(float xFactor:{-.6f,0.f,.6f})for(float z:{-.6f,0.f,.6f}) {
                const float x=xFactor*slope.xExtent;
                const int tx=int((.5f+.5f*slope.lightScale*x)*MapSize+placement.texelX);
                const int ty=int((.5f-.5f*slope.lightScale*z)*MapSize+placement.texelY);
                const float texelX=(2*((tx+.5f-placement.texelX)/MapSize)-1)/slope.lightScale;
                const float texelZ=(1-2*((ty+.5f-placement.texelY)/MapSize))/slope.lightScale;
                const float expected=.5f-.25f*(slope.x*texelX+slope.z*texelZ);
                require(std::abs(selfMap[ty*MapSize+tx]-expected)<.0001f,
                    "Sloped native receiver is missing or misplaced in the actual shadow capture");
            }
            auto setCamera=[&](const float *camera) {
                // Native screen coordinates from an orthographic camera
                // translation; world geometry and the light map stay fixed.
                for(uint32_t v=0;v<4;++v) {
                    screen[v][0]=savedScreen[v][0]+camera[0];
                    screen[v][1]=savedScreen[v][1]+camera[1];
                }
                fill(screens,screen,sizeof(screen));
            };
            for(const auto &camera:cameras) {
                setCamera(camera);
                for(bool water:{false,true}) {
                    const auto off=draw(water,false),on=draw(water,true);
                    size_t acne=0;int maximumError=0;
                    for(uint32_t y=0;y<H;++y)for(uint32_t x=0;x<W;++x) {
                        const float viewX=x+.5f-camera[0],viewY=y+.5f-camera[1];
                        if(viewX<8||viewX>56||viewY<8||viewY>56)continue;
                        const size_t p=(y*W+x)*4;bool changed=false;
                        for(uint32_t c=0;c<4;++c) {
                            const int error=std::abs(int(on[p+c])-int(off[p+c]));
                            maximumError=std::max(maximumError,error);changed|=error!=0;
                        }
                        acne+=changed;++slopeSelfPixels;
                    }
                    if(acne)std::printf("SLOPE ACNE: %ux water=%u slope=(%.3f,%.3f) reverse=%u origin=%.1f light_texels=(%.4f,%.4f) camera=(%.3f,%.3f) pixels=%zu max=%d\n",
                        samples,unsigned(water),slope.x,slope.z,unsigned(reversed),placement.origin,
                        placement.texelX,placement.texelY,camera[0],camera[1],acne,maximumError);
                    require(acne==0,"Captured sloped receiver shadows itself; PCF must compare against the receiver plane at each tap");
                }
            }
            capture(1,false,false,true);
            Pixels stationary[2];
            for(uint32_t cameraIndex=0;cameraIndex<std::size(cameras);++cameraIndex) {
                const auto &camera=cameras[cameraIndex];setCamera(camera);
                for(bool water:{false,true}) {
                    const auto off=draw(water,false),on=draw(water,true);size_t visibleGap=0;
                    double shadowWeight=0,shadowMomentX=0,shadowMomentY=0;
                    if(cameraIndex==0)stationary[water?1:0]=on;
                    for(uint32_t y=0;y<H;++y)for(uint32_t x=0;x<W;++x) {
                        const float viewX=x+.5f-camera[0],viewY=y+.5f-camera[1];
                        if(viewX<8||viewX>56||viewY<8||viewY>56)continue;
                        const size_t p=(y*W+x)*4;
                        const double weight=std::max(0,int(off[p])-int(on[p]));
                        shadowWeight+=weight;shadowMomentX+=weight*(x+.5);shadowMomentY+=weight*(y+.5);
                        const bool inner=viewX>=26&&viewX<38&&viewY>=26&&viewY<38;
                        const bool outer=viewX<10||viewX>54||viewY<10||viewY>54;
                        require(on[p+3]==off[p+3],"Slope/camera correction changed native coverage");
                        for(uint32_t c=0;c<3;++c) {
                            if(inner) {
                                const int expected=int(std::lround(off[p+c]*(water?.82f:.45f)));
                                require(std::abs(int(on[p+c])-expected)<=2,
                                    "Receiver-plane correction erased a genuinely raised caster's small-gap shadow");
                            }
                            if(outer)require(on[p+c]==off[p+c],"Sloped receiver gained shadow outside the raised caster");
                        }
                        if(inner&&off[p]>on[p]+3)++visibleGap;
                        if(cameraIndex==1||cameraIndex==2) {
                            const int referenceX=int(x)-int(camera[0]),referenceY=int(y)-int(camera[1]);
                            const size_t reference=(referenceY*W+referenceX)*4;
                            for(uint32_t c=0;c<4;++c)require(std::abs(int(on[p+c])-int(stationary[water?1:0][reference+c]))<=1,
                                "Shadow moved relative to the world when only the native camera translated");
                            ++cameraComparedPixels;
                        }
                    }
                    require(visibleGap>=100,"Raised caster small-gap positive control was empty");slopeGapPixels+=visibleGap;
                    require(shadowWeight>0,"Raised caster shadow centroid has no positive weight");
                    const double centroidDrift=std::max(std::abs(shadowMomentX/shadowWeight-(32+camera[0])),
                        std::abs(shadowMomentY/shadowWeight-(32+camera[1])));
                    maximumShadowCentroidDrift=std::max(maximumShadowCentroidDrift,centroidDrift);
                    // Subtexel capture placement may quantize an edge by half
                    // a map texel. Its footprint must remain at the analytic
                    // world center across both map and camera translations.
                    require(centroidDrift<=1.0,"Static raised-caster shadow followed camera/light-map shifts instead of its world footprint");
                    if(cameraIndex==0&&!reversed&&placement.origin==0&&slope.x==.5f)
                        writePPM(prefix+"-"+std::to_string(samples)+"x-slope-"+(water?"water":"world")+".ppm",on);
                }
            }
        }
        std::memcpy(world,savedWorld,sizeof(world));std::memcpy(screen,savedScreen,sizeof(screen));
        std::memcpy(indices,savedIndices,sizeof(indices));shadow=savedShadow;
        fill(positions,world,sizeof(world));fill(screens,screen,sizeof(screen));fill(faces,indices,sizeof(indices));
        std::printf("%ux slope shadows: self_pixels=%zu small_gap_pixels=%zu camera_aligned_pixels=%zu maximum_world_footprint_drift=%.6fpx; both slope axes/signs, winding, grazing plane, fractional map positions and rebased world origins passed.\n",
            samples,slopeSelfPixels,slopeGapPixels,cameraComparedPixels,maximumShadowCentroidDrift);
        std::printf("%ux raster shadows: real map depth/cutout/order, native water/world states, coverage, Off and above-caster guards passed.\n",samples);
    }
    require(darkWater>0&&darkWorld>0,"Raster-shadow positive controls were empty");
    std::printf("Raster shadows: states=%zu water_pixels=%zu world_pixels=%zu maximum color error water=%d world=%d.\n",
        stateVariants,darkWater,darkWorld,maxWaterError,maxWorldError);
}
