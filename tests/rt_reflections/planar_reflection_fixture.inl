// Included in raster_gpu.cpp's anonymous namespace, before its RT capability
// gate. This fixture creates no AS descriptor, AS-input buffer or ray scene.
void verifyPlanarReflections(RenderDevice *device, FixtureWorker &worker, const std::string &prefix) {
    constexpr uint32_t W=64,H=64,Map=128;
    std::vector<std::unique_ptr<RenderBuffer>> buffers;
    auto upload=[&](const void *data,size_t bytes,RenderBufferFlags flags) {
        auto buffer=device->createBuffer(RenderBufferDesc::UploadBuffer(
            (flags&RenderBufferFlag::CONSTANT)?(bytes+255)&~uint64_t(255):bytes,flags));
        require(buffer!=nullptr,"Planar fixture allocation failed");fill(buffer.get(),data,bytes);
        auto *result=buffer.get();buffers.push_back(std::move(buffer));return result;
    };
    SamplerLibrary samplers;fillSamplers(device,samplers.nearest,RenderFilter::NEAREST);
    fillSamplers(device,samplers.linear,RenderFilter::LINEAR);
    FramebufferRendererDescriptorCommonSet common(samplers,false,device);
    FramebufferRendererDescriptorTextureSet textures(device,1);
    FramebufferRendererDescriptorFramebufferSet framebufferSet(device);
    require(common.SceneBVH==0,"Planar fixture contains an AS descriptor");
    RenderPipelineLayoutBuilder builder;builder.begin(false,true);
    builder.addPushConstant(0,0,sizeof(interop::RasterParams),RenderShaderStageFlag::VERTEX|RenderShaderStageFlag::PIXEL);
    builder.addDescriptorSet(common);builder.addDescriptorSet(textures);builder.addDescriptorSet(textures);
    builder.addDescriptorSet(framebufferSet);builder.end();auto layout=builder.create(device);
    require(layout!=nullptr,"Planar fixture layout failed");

    // A top-down orthographic camera gives independently known footprints:
    // reflected camera is below Y=0, so the Y=1 red quad hides the Y=2 green
    // quad. The Y=-1 blue quad would be nearest but must be plane-clipped.
    float world[16][4]={{-5,0,5,1},{5,0,5,1},{5,0,-5,1},{-5,0,-5,1},
        {-2.5f,1,2.5f,1},{2.5f,1,2.5f,1},{2.5f,1,-2.5f,1},{-2.5f,1,-2.5f,1},
        {-2.5f,2,2.5f,1},{2.5f,2,2.5f,1},{2.5f,2,-2.5f,1},{-2.5f,2,-2.5f,1},
        {-2.5f,-1,2.5f,1},{2.5f,-1,2.5f,1},{2.5f,-1,-2.5f,1},{-2.5f,-1,-2.5f,1}};
    float screen[16][4]={{0,0,.5f,1},{64,0,.5f,1},{64,64,.5f,1},{0,64,.5f,1}};
    for(uint32_t i=4;i<16;++i)std::copy(screen[i%4],screen[i%4]+4,screen[i]);
    float uv[16][2]{};float colors[16][4];for(auto &v:colors)for(float &c:v)c=1;
    uint32_t indices[24]={0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15};
    auto *positions=upload(world,sizeof(world),RenderBufferFlag::STORAGE);
    auto *faces=upload(indices,sizeof(indices),RenderBufferFlag::INDEX|RenderBufferFlag::STORAGE);
    auto *screens=upload(screen,sizeof(screen),RenderBufferFlag::VERTEX);
    auto *uvs=upload(uv,sizeof(uv),RenderBufferFlag::VERTEX|RenderBufferFlag::STORAGE);
    auto *shades=upload(colors,sizeof(colors),RenderBufferFlag::VERTEX|RenderBufferFlag::STORAGE);
    interop::FrameParams frame{};interop::FramebufferParams fb{};
    fb.resolution=hlslpp::float2(W,H);fb.resolutionScale=hlslpp::float2(1,1);
    interop::RenderIndices ri[4]={{0,0,0,1,0},{1,6,0,0,0},{2,12,0,0,0},{3,18,0,0,0}};
    interop::RenderParams rp[4]{};interop::RDPParams rdp[4]{};
    for(auto &p:rp) {
        p.ccL=(8u<<20)|(31u<<15)|(7u<<12)|(7u<<9)|(8u<<5)|31u;
        p.ccH=(8u<<28)|(8u<<24)|(7u<<21)|(7u<<18)|(3u<<15)|(7u<<12)|(3u<<9)|(3u<<6)|(7u<<3)|3u;
        p.flags.NoN=1;p.flags.smoothShade=1;
    }
    rp[0].ccL=0xFCFFFFFF;rp[0].ccH=0xFFFCF279;rp[0].omL=0x005049D8;rp[0].omH=0x00082CFF;
    rp[0].flags.usesTexture0=1;rp[0].flags.nativeSampler0=NATIVE_SAMPLER_CLAMP_CLAMP;
    rp[0].flags.cms0=rp[0].flags.cmt0=2;
    rdp[0].primColor=hlslpp::float4(1,1,1,1);rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,1);
    rdp[2].primColor=hlslpp::float4(.1f,.8f,.2f,1);rdp[3].primColor=hlslpp::float4(.1f,.2f,.8f,1);
    rdp[1].blendColor=hlslpp::float4(0,0,0,.5f);
    interop::RDPTile tile{};tile.shifts=tile.shiftt=1;tile.lrs=tile.lrt=63*4;tile.cms=tile.cmt=2;
    tile.fmt=0;tile.siz=3;tile.stride=256;tile.nativeSampler=NATIVE_SAMPLER_CLAMP_CLAMP;
    interop::GPUTile gpuTile{};gpuTile.ulScale=gpuTile.tcScale=hlslpp::float2(1,1);gpuTile.textureDimensions=hlslpp::float3(W,H,1);
    Params reflection{};reflection.enabled=1;reflection.smoothNormals=0;reflection.camera[1]=10;
    Wr64RasterReflectionParams planar{};
    const float ordinaryRows[4][4]={{.2f,0,0,0},{0,0,.2f,0},{0,-.05f,0,.5f},{0,0,0,1}};
    const auto mirrored=wr64BuildPlanarReflectionProjection(ordinaryRows,0);
    require(mirrored.valid,"Planar production math rejected fixture camera");
    std::memcpy(planar.reflectedRows,mirrored.rows,sizeof(mirrored.rows));
    std::memcpy(planar.plane,mirrored.clipPlane,sizeof(mirrored.clipPlane));
    planar.options[0]=1;planar.options[1]=1;planar.options[2]=2;
    auto *planarBuffer=upload(&planar,sizeof(planar),RenderBufferFlag::CONSTANT);
    auto *reflectionBuffer=upload(&reflection,sizeof(reflection),RenderBufferFlag::CONSTANT);
    auto *rpBuffer=upload(rp,sizeof(rp),RenderBufferFlag::STORAGE);
    auto *rdpBuffer=upload(rdp,sizeof(rdp),RenderBufferFlag::STORAGE);
    common.setBuffer(common.FrParams,upload(&frame,sizeof(frame),RenderBufferFlag::CONSTANT),sizeof(frame));
    common.setBuffer(common.RtParams,reflectionBuffer,sizeof(reflection));
    common.setBuffer(common.wr64RasterReflectionParams,planarBuffer,sizeof(planar));
    common.setBuffer(common.DynamicRenderParams,rpBuffer,sizeof(rp),RenderBufferStructuredView(sizeof(rp[0])));
    common.setBuffer(common.instanceRenderIndices,upload(ri,sizeof(ri),RenderBufferFlag::STORAGE),sizeof(ri),RenderBufferStructuredView(sizeof(ri[0])));
    common.setBuffer(common.instanceRDPParams,rdpBuffer,sizeof(rdp),RenderBufferStructuredView(sizeof(rdp[0])));
    common.setBuffer(common.RDPTiles,upload(&tile,sizeof(tile),RenderBufferFlag::STORAGE),sizeof(tile),RenderBufferStructuredView(sizeof(tile)));
    common.setBuffer(common.GPUTiles,upload(&gpuTile,sizeof(gpuTile),RenderBufferFlag::STORAGE),sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
    common.setBuffer(common.posBuffer,positions,sizeof(world));common.setBuffer(common.indexBuffer,faces,sizeof(indices));
    common.setBuffer(common.genTexCoordBuffer,uvs,sizeof(uv));common.setBuffer(common.shadedColBuffer,shades,sizeof(colors));
    framebufferSet.setBuffer(framebufferSet.FbParams,upload(&fb,sizeof(fb),RenderBufferFlag::CONSTANT),sizeof(fb));
    Pixels waterTexels(W*H*4);
    auto waterTexture=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
    auto waterView=waterTexture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
    auto *waterUpload=upload(waterTexels.data(),waterTexels.size(),0);
    textures.setTexture(0,waterTexture.get(),RenderTextureLayout::SHADER_READ,waterView.get());
    auto setWaterAlpha=[&](uint8_t alpha) {
        for(size_t p=0;p<waterTexels.size();p+=4){waterTexels[p]=51;waterTexels[p+1]=102;waterTexels[p+2]=153;waterTexels[p+3]=alpha;}
        fill(waterUpload,waterTexels.data(),waterTexels.size());worker.commandList->begin();
        worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::COPY_DEST));
        worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(waterTexture.get()),
            RenderTextureCopyLocation::PlacedFootprint(waterUpload,RenderFormat::R8G8B8A8_UNORM,W,H,1,W));
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
    };
    const RenderInputSlot slots[]={RenderInputSlot(0,16),RenderInputSlot(1,8),RenderInputSlot(2,16)};
    const RenderVertexBufferView vertices[]={RenderVertexBufferView(screens->at(0),sizeof(screen)),
        RenderVertexBufferView(uvs->at(0),sizeof(uv)),RenderVertexBufferView(shades->at(0),sizeof(colors))};
    const RenderIndexBufferView index(faces->at(0),sizeof(indices),RenderFormat::R32_UINT);
    auto bind=[&]() {
        worker.commandList->setGraphicsPipelineLayout(layout.get());worker.commandList->setGraphicsDescriptorSet(common.get(),0);
        worker.commandList->setGraphicsDescriptorSet(textures.get(),1);worker.commandList->setGraphicsDescriptorSet(textures.get(),2);
        worker.commandList->setGraphicsDescriptorSet(framebufferSet.get(),3);
        worker.commandList->setVertexBuffers(0,vertices,3,slots);worker.commandList->setIndexBuffer(&index);
    };
    auto copy=[&](RenderTexture *source,RenderBuffer *destination,DXGI_FORMAT format,uint32_t w,uint32_t h,uint32_t bytes) {
        worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(source,RenderTextureLayout::COPY_SOURCE));
        D3D12_TEXTURE_COPY_LOCATION dst{};dst.pResource=static_cast<D3D12Buffer*>(destination)->d3d;
        dst.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;dst.PlacedFootprint.Footprint={format,w,h,1,w*bytes};
        D3D12_TEXTURE_COPY_LOCATION src{};src.pResource=static_cast<D3D12Texture*>(source)->d3d;src.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        static_cast<D3D12CommandList*>(worker.commandList.get())->d3d->CopyTextureRegion(&dst,0,0,0,&src,nullptr);
    };
    Wr64RasterReflectionTarget captureTarget;
    require(captureTarget.ensure(&worker,Map,Map),"Planar color/depth target creation failed");
    auto *initialColor=captureTarget.color();auto *initialDepth=captureTarget.depth();
    require(captureTarget.ensure(&worker,Map,Map)&&captureTarget.color()==initialColor&&captureTarget.depth()==initialDepth,
        "Same-sized planar target lost its retained allocation");
    common.setTexture(common.wr64RasterReflectionColor,captureTarget.color(),RenderTextureLayout::SHADER_READ);
    auto mapReadback=device->createBuffer(RenderBufferDesc::ReadbackBuffer(Map*Map*8));
    Wr64RasterReflectionPipelines pipelines;Wr64RasterSkyPipelines nativePipelines;
    auto capture=[&](const std::vector<uint32_t> &draws,bool culling=false) {
        fill(planarBuffer,&planar,sizeof(planar));fill(rpBuffer,rp,sizeof(rp));fill(rdpBuffer,rdp,sizeof(rdp));
        worker.commandList->begin();const RenderTextureBarrier barriers[]={{captureTarget.color(),RenderTextureLayout::COLOR_WRITE},
            {captureTarget.depth(),RenderTextureLayout::DEPTH_WRITE}};
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,barriers,2);
        worker.commandList->setFramebuffer(captureTarget.framebuffer());worker.commandList->clearColor(0,RenderColor(0,0,0,0));
        worker.commandList->clearDepth(true,1);bind();worker.commandList->setPipeline(pipelines.capture(culling));
        worker.commandList->setViewports(RenderViewport(0,0,Map,Map));worker.commandList->setScissors(RenderRect(0,0,Map,Map));
        interop::RasterParams push{};push.screenScale=hlslpp::float2(1,1);
        for(uint32_t draw:draws) {push.renderIndex=draw;worker.commandList->setGraphicsPushConstants(0,&push);
            worker.commandList->drawIndexedInstanced(6,1,draw*6,0,0);}
        worker.commandList->setFramebuffer(nullptr);copy(captureTarget.color(),mapReadback.get(),DXGI_FORMAT_R16G16B16A16_FLOAT,Map,Map,8);
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(captureTarget.color(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
        std::vector<float> result(Map*Map*4);const RenderRange range(0,result.size()*2),noWrite(0,0);
        const auto *mapped=static_cast<const uint16_t*>(mapReadback->map(0,&range));require(mapped,"Planar capture readback failed");
        for(size_t i=0;i<result.size();++i){result[i]=rasterSkyHalf(mapped[i]);require(std::isfinite(result[i]),"Nonfinite planar capture output");}
        mapReadback->unmap(0,&noWrite);return result;
    };
    size_t composedPixels=0,changedByWaves=0,captureChecks=0;int maximumError=0;
    for(uint32_t samples:{1u,4u}) {
        const RenderMultisampling ms(samples);
        require(pipelines.prepare(device,layout.get(),ms,false,false),"Planar production PSOs failed");
        require(nativePipelines.prepare(device,layout.get(),ms,false,false),"Native-water reference PSOs failed");
        for(auto &p:rp)p.flags.sampleCount=samples==1?0:2;
        setWaterAlpha(128);const auto nearMap=capture({1});const auto farMap=capture({2});
        for(uint32_t y=4;y<Map-4;++y)for(uint32_t x=4;x<Map-4;++x) {
            const bool inside=x>=36&&x<92&&y>=36&&y<92;
            const bool outside=x<28||x>=100||y<28||y>=100;
            const size_t p=(y*Map+x)*4;
            if(inside) {require(nearMap[p+3]==1&&std::abs(nearMap[p]-.8f)<.001f&&std::abs(nearMap[p+1]-.2f)<.001f,
                "Mirrored capture has wrong projection/color/alpha");++captureChecks;}
            if(outside)require(nearMap[p+3]==0,"Planar capture leaked beyond object footprint");
        }
        require(capture({1,2})==nearMap&&capture({2,1})==nearMap,"Planar object occlusion depends on draw order");
        require(capture({1,3})==nearMap,"Below-water geometry contaminated reflection");
        rp[1].flags.culling=1;const auto culledA=capture({1},true);
        for(uint32_t f:{6u,9u})std::swap(indices[f+1],indices[f+2]);fill(faces,indices,sizeof(indices));
        const auto culledB=capture({1},true);
        require((culledA==nearMap)!=(culledB==nearMap),"Mirrored native culling did not select exactly one winding");
        rp[1].flags.culling=0;require(capture({1})==nearMap,"Two-sided planar geometry depended on winding");
        for(uint32_t f:{6u,9u})std::swap(indices[f+1],indices[f+2]);fill(faces,indices,sizeof(indices));
        rp[1].omL=1;rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,0);
        require(capture({1,2})==farMap,"Transparent native cutout blocked the object behind it");
        rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,1);
        require(capture({1,2})==nearMap,"Covered native cutout lost its reflection");rp[1].omL=0;
        planar.options[3]=1.5f;require(capture({1,2})==farMap,"Plane clip bias did not reject submerged geometry");planar.options[3]=0;
        require(capture({1})==nearMap,"Clipping restoration changed a retained capture");
        auto target=device->createTexture(RenderTextureDesc::ColorTarget(W,H,RenderFormat::R8G8B8A8_UNORM,ms));
        auto depth=device->createTexture(RenderTextureDesc::DepthTarget(W,H,RenderFormat::D32_FLOAT,ms));
        auto resolved=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
        auto readback=device->createBuffer(RenderBufferDesc::ReadbackBuffer(W*H*4));
        const RenderTexture *attachments[]={target.get()};auto framebuffer=device->createFramebuffer(RenderFramebufferDesc(attachments,1,depth.get()));
        auto draw=[&](bool enabled,bool reference=false,bool compare=false,bool write=false,bool coverage=false,float depthClear=1.f) {
            planar.options[0]=enabled?1.f:0.f;reflection.enabled=reference?0:1;
            fill(planarBuffer,&planar,sizeof(planar));fill(reflectionBuffer,&reflection,sizeof(reflection));fill(rpBuffer,rp,sizeof(rp));
            worker.commandList->begin();const RenderTextureBarrier barriers[]={{target.get(),RenderTextureLayout::COLOR_WRITE},{depth.get(),RenderTextureLayout::DEPTH_WRITE}};
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,barriers,2);worker.commandList->setFramebuffer(framebuffer.get());
            worker.commandList->clearColor(0,RenderColor(.7f,.5f,.3f,0));worker.commandList->clearDepth(true,depthClear);bind();
            worker.commandList->setPipeline(reference?nativePipelines.get(compare,write,coverage):pipelines.get(compare,write,coverage));
            worker.commandList->setViewports(RenderViewport(0,0,W,H));worker.commandList->setScissors(RenderRect(0,0,W,H));
            interop::RasterParams push{};push.screenScale=hlslpp::float2(1,1);worker.commandList->setGraphicsPushConstants(0,&push);
            worker.commandList->drawIndexedInstanced(6,1,0,0,0);worker.commandList->setFramebuffer(nullptr);RenderTexture *source=target.get();
            if(samples>1) {const RenderTextureBarrier barriers2[]={{target.get(),RenderTextureLayout::RESOLVE_SOURCE},{resolved.get(),RenderTextureLayout::RESOLVE_DEST}};
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,barriers2,2);worker.commandList->resolveTexture(resolved.get(),target.get());source=resolved.get();}
            copy(source,readback.get(),DXGI_FORMAT_R8G8B8A8_UNORM,W,H,4);worker.commandList->end();worker.execute();worker.wait();
            Pixels result(W*H*4);const RenderRange range(0,result.size()),noWrite(0,0);const void *mapped=readback->map(0,&range);
            require(mapped,"Planar water readback failed");std::memcpy(result.data(),mapped,result.size());readback->unmap(0,&noWrite);return result;
        };
        for(uint8_t alpha:{uint8_t(0),uint8_t(64),uint8_t(128),uint8_t(255)}) {
            setWaterAlpha(alpha);
            for(uint32_t flags=0;flags<8;++flags) {
                const bool cmp=flags&1,write=flags&2,cvg=flags&4;
                const auto native=draw(false,true,cmp,write,cvg),off=draw(false,false,cmp,write,cvg),on=draw(true,false,cmp,write,cvg);
                require(off==native,"Planar Off differs from the independent native-water PSO");
                require(draw(false,false,cmp,write,cvg)==off,"Turning planar reflections Off did not restore exact native output");
                planar.options[1]=0;require(draw(true,false,cmp,write,cvg)==off,"Zero planar strength changed native water");planar.options[1]=1;
                for(uint32_t y=3;y<H-3;++y)for(uint32_t x=3;x<W-3;++x) {
                    const size_t p=(y*W+x)*4;require(on[p+3]==off[p+3],"Planar reflection changed native coverage");
                    const bool inside=x>=20&&x<44&&y>=20&&y<44;
                    const bool outside=x<12||x>=52||y<12||y>=52;
                    if(outside)for(uint32_t c=0;c<3;++c)require(on[p+c]==off[p+c],"Empty capture darkened or colored native water");
                    if(inside) {
                        const double px=-5+(x+.5)*10/W,pz=5-(y+.5)*10/H;
                        const double angle=std::pow(1-10/std::sqrt(px*px+pz*pz+100),5);
                        const double weight=.08+.35*angle,a=alpha/255.;
                        const double nativeRGB[]={.2,.4,.6},objectRGB[]={nearMap[(Map/2*Map+Map/2)*4],nearMap[(Map/2*Map+Map/2)*4+1],nearMap[(Map/2*Map+Map/2)*4+2]};
                        // Compare the final framebuffer contribution. Keeping
                        // background and native alpha cancels the destination.
                        for(uint32_t c=0;c<3;++c) {
                            const int expected=int(std::lround(off[p+c]+255*a*weight*(objectRGB[c]-nativeRGB[c])));
                            const int error=std::abs(int(on[p+c])-expected);maximumError=std::max(maximumError,error);
                            require(error<=2,"Planar water differs from independent angular/alpha composition oracle");
                        }
                        ++composedPixels;
                    }
                }
                if(cmp)require(draw(true,false,cmp,write,cvg,.25f)==draw(false,false,cmp,write,cvg,.25f),"Planar water bypassed native depth rejection");
            }
        }
        setWaterAlpha(128);const auto flat=draw(true);require(draw(true)==flat,"Repeated planar water pass changed output");
        for(uint32_t v=0;v<4;++v)world[v][1]=world[v][0]*.25f;fill(positions,world,sizeof(world));
        planar.options[2]=0;const auto unbentWaves=draw(true);planar.options[2]=2;
        const auto waved=draw(true);for(size_t p=0;p<waved.size();p+=4)if(std::abs(int(waved[p])-int(unbentWaves[p]))>3)++changedByWaves;
        require(waved!=unbentWaves,"Wave normals changed only angular intensity, without distorting reflection coordinates");
        require(capture({1})==nearMap,"Wave motion moved the reflected camera or capture plane");
        for(uint32_t v=0;v<4;++v)world[v][1]=0;fill(positions,world,sizeof(world));
        require(draw(true)==flat,"Flat water restoration changed planar output");
        planar.reflectedRows[0][3]=.2f;const auto shifted=capture({1});require(shifted!=nearMap,"Camera translation left capture stationary");
        planar.reflectedRows[0][3]=0;require(capture({1})==nearMap,"Camera return did not restore exact capture");
        planar.reflectedRows[3][3]=-1;const auto behind=draw(true);require(behind==draw(false),"Behind-camera capture sampled reflected color");
        planar.reflectedRows[3][3]=1;require(draw(true)==flat,"Horizon guard restoration changed water output");
        writePPM(prefix+"-planar-"+std::to_string(samples)+"x.ppm",flat);
    }
    require(changedByWaves>100,"Wave-distortion positive control was too weak");
    std::printf("planar raster: capture_pixels%zu composition_pixels%zu wave_changed%zu max_error%d; no AS descriptor/allocation/build/binding\n",
        captureChecks,composedPixels,changedByWaves,maximumError);
}
