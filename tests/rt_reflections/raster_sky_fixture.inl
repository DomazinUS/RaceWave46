// Included in raster_gpu.cpp's anonymous namespace. This path runs before the
// inline-ray capability gate. It deliberately has no AS object, descriptor,
// build, AS input buffer flag or scene binding; the physical GPU can support RT.
float rasterSkyHalf(uint16_t bits) {
    const int exponent = (bits >> 10) & 31;
    const int mantissa = bits & 1023;
    if(exponent==31) return mantissa ? std::numeric_limits<float>::quiet_NaN() :
        (bits&0x8000 ? -std::numeric_limits<float>::infinity() : std::numeric_limits<float>::infinity());
    const float value = exponent ? std::ldexp(float(1024 + mantissa), exponent - 25) :
        std::ldexp(float(mantissa), -24);
    return bits & 0x8000 ? -value : value;
}

void verifyRasterSky(RenderDevice *device, FixtureWorker &worker, const std::string &prefix) {
    constexpr uint32_t W = 64, H = 64, SkyW = 512, SkyH = 256;
    constexpr double Pi = 3.14159265358979323846;
    std::vector<std::unique_ptr<RenderBuffer>> buffers;
    auto upload = [&](const void *data, size_t bytes, RenderBufferFlags flags) {
        auto buffer = device->createBuffer(RenderBufferDesc::UploadBuffer(
            (flags & RenderBufferFlag::CONSTANT) ? (bytes + 255) & ~uint64_t(255) : bytes, flags));
        require(buffer != nullptr, "Raster sky upload allocation failed");
        fill(buffer.get(), data, bytes);
        auto *result = buffer.get(); buffers.push_back(std::move(buffer)); return result;
    };
    SamplerLibrary samplers;
    fillSamplers(device, samplers.nearest, RenderFilter::NEAREST);
    fillSamplers(device, samplers.linear, RenderFilter::LINEAR);
    FramebufferRendererDescriptorCommonSet common(samplers, false, device);
    FramebufferRendererDescriptorTextureSet textures(device, 1);
    FramebufferRendererDescriptorFramebufferSet framebufferSet(device);
    require(common.SceneBVH == 0, "Raster fixture unexpectedly declares an AS descriptor");
    RenderPipelineLayoutBuilder builder;
    builder.begin(false, true);
    builder.addPushConstant(0, 0, sizeof(interop::RasterParams), RenderShaderStageFlag::VERTEX | RenderShaderStageFlag::PIXEL);
    builder.addDescriptorSet(common); builder.addDescriptorSet(textures);
    builder.addDescriptorSet(textures); builder.addDescriptorSet(framebufferSet); builder.end();
    auto layout = builder.create(device);
    require(layout != nullptr, "Raster-only production layout creation failed");

    float world[16][4] = {{-5,0,5,1},{5,0,5,1},{5,0,-5,1},{-5,0,-5,1},
        {-20,-40,10,1},{40,-40,10,1},{40,40,10,1},{-20,40,10,1}};
    float screen[16][4] = {{0,0,.5f,1},{64,0,.5f,1},{64,64,.5f,1},{0,64,.5f,1}};
    float uv[16][2] = {};
    float colors[16][4]; for (auto &v : colors) for (float &c : v) c = 1;
    uint32_t indices[24] = {0,1,2,0,2,3,4,5,6,4,6,7};
    auto *positions = upload(world, sizeof(world), RenderBufferFlag::STORAGE);
    auto *faces = upload(indices, sizeof(indices), RenderBufferFlag::STORAGE | RenderBufferFlag::INDEX);
    auto *screens = upload(screen, sizeof(screen), RenderBufferFlag::VERTEX);
    auto *uvs = upload(uv, sizeof(uv), RenderBufferFlag::VERTEX | RenderBufferFlag::STORAGE);
    auto *shades = upload(colors, sizeof(colors), RenderBufferFlag::VERTEX | RenderBufferFlag::STORAGE);
    interop::FrameParams frame{};
    interop::FramebufferParams fb{}; fb.resolution = hlslpp::float2(W,H); fb.resolutionScale = hlslpp::float2(1,1);
    interop::RenderIndices ri[2] = {{0,0,0,1,0},{1,6,0,0,0}};
    interop::RenderParams rp[2]{};
    for (auto &p : rp) {
        p.ccL=(8u<<20)|(31u<<15)|(7u<<12)|(7u<<9)|(8u<<5)|31u;
        p.ccH=(8u<<28)|(8u<<24)|(7u<<21)|(7u<<18)|(3u<<15)|(7u<<12)|(3u<<9)|(3u<<6)|(7u<<3)|3u;
        p.flags.NoN=1; p.flags.smoothShade=1;
    }
    // The actual native Sunset water combiner/blender and a standard native
    // alpha-over sky material; constant texture pixels are synthetic inputs.
    rp[0].ccL=0xFCFFFFFF; rp[0].ccH=0xFFFCF279;
    rp[0].omL=0x005049D8; rp[0].omH=0x00082CFF;
    rp[0].flags.usesTexture0=1; rp[0].flags.nativeSampler0=NATIVE_SAMPLER_CLAMP_CLAMP;
    rp[0].flags.cms0=rp[0].flags.cmt0=2;
    rp[1].omL=0x00504240; rp[1].omH=0x00882C3F;
    interop::RDPParams rdp[2]{};
    rdp[0].primColor=hlslpp::float4(1,1,1,1);
    rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,1);
    interop::RDPTile tile{}; tile.shifts=tile.shiftt=1; tile.lrs=tile.lrt=63*4;
    tile.cms=tile.cmt=2; tile.fmt=0; tile.siz=3; tile.stride=256; tile.nativeSampler=NATIVE_SAMPLER_CLAMP_CLAMP;
    interop::GPUTile gpuTile{}; gpuTile.ulScale=gpuTile.tcScale=hlslpp::float2(1,1);
    gpuTile.textureDimensions=hlslpp::float3(W,H,1);
    Params reflection{}; reflection.enabled=1; reflection.sky[3]=0;
    require(reflection.strength==1.f,"Raster sky default strength changed from the original baseline");
    reflection.skyBackdrop[0]=6; reflection.skyBackdrop[1]=1;
    reflection.skyBackdrop[2]=2; reflection.skyBackdrop[3]=1;
    auto *paramsBuffer=upload(&reflection,sizeof(reflection),RenderBufferFlag::CONSTANT);
    auto *rpBuffer=upload(rp,sizeof(rp),RenderBufferFlag::STORAGE);
    auto *rdpBuffer=upload(rdp,sizeof(rdp),RenderBufferFlag::STORAGE);
    auto *riBuffer=upload(ri,sizeof(ri),RenderBufferFlag::STORAGE);
    common.setBuffer(common.FrParams,upload(&frame,sizeof(frame),RenderBufferFlag::CONSTANT),sizeof(frame));
    common.setBuffer(common.RtParams,paramsBuffer,sizeof(reflection));
    common.setBuffer(common.DynamicRenderParams,rpBuffer,sizeof(rp),RenderBufferStructuredView(sizeof(rp[0])));
    common.setBuffer(common.instanceRenderIndices,riBuffer,sizeof(ri),RenderBufferStructuredView(sizeof(ri[0])));
    common.setBuffer(common.instanceRDPParams,rdpBuffer,sizeof(rdp),RenderBufferStructuredView(sizeof(rdp[0])));
    common.setBuffer(common.RDPTiles,upload(&tile,sizeof(tile),RenderBufferFlag::STORAGE),sizeof(tile),RenderBufferStructuredView(sizeof(tile)));
    common.setBuffer(common.GPUTiles,upload(&gpuTile,sizeof(gpuTile),RenderBufferFlag::STORAGE),sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
    common.setBuffer(common.posBuffer,positions,sizeof(world)); common.setBuffer(common.indexBuffer,faces,sizeof(indices));
    common.setBuffer(common.genTexCoordBuffer,uvs,sizeof(uv)); common.setBuffer(common.shadedColBuffer,shades,sizeof(colors));
    framebufferSet.setBuffer(framebufferSet.FbParams,upload(&fb,sizeof(fb),RenderBufferFlag::CONSTANT),sizeof(fb));
    Wr64WaterAdjacency adjacency;
    std::vector<float> xyz; for (const auto &v : world) xyz.insert(xyz.end(),v,v+3);
    require(adjacency.build(16,xyz,std::vector<uint16_t>(16,0),{0,1,2,0,2,3}),"Raster water adjacency failed");
    common.setBuffer(common.wr64WaterAdjacency,upload(adjacency.words.data(),adjacency.words.size()*4,RenderBufferFlag::STORAGE),adjacency.words.size()*4);
    Pixels waterTexels(W*H*4);
    auto waterTexture=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
    auto waterView=waterTexture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
    auto *waterUpload=upload(waterTexels.data(),waterTexels.size(),0);
    textures.setTexture(0,waterTexture.get(),RenderTextureLayout::SHADER_READ,waterView.get());
    auto setWaterAlpha=[&](uint8_t alpha) {
        for (size_t i=0;i<waterTexels.size();i+=4) {waterTexels[i]=26;waterTexels[i+1]=51;waterTexels[i+2]=179;waterTexels[i+3]=alpha;}
        fill(waterUpload,waterTexels.data(),waterTexels.size());
        worker.commandList->begin();
        worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::COPY_DEST));
        worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(waterTexture.get()),
            RenderTextureCopyLocation::PlacedFootprint(waterUpload,RenderFormat::R8G8B8A8_UNORM,W,H,1,W));
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
    };
    Wr64RasterSkyTarget captureTarget;
    require(captureTarget.ensure(&worker),"Raster sky target creation failed");
    require(captureTarget.width()==SkyW && captureTarget.height()==SkyH,"Raster sky default dimensions changed");
    auto *stableTarget=captureTarget.texture();
    require(captureTarget.ensure(&worker) && captureTarget.texture()==stableTarget,"Identical sky size replaced its texture");
    common.setTexture(common.wr64RasterSky,captureTarget.texture(),RenderTextureLayout::SHADER_READ);
    auto skyReadback=device->createBuffer(RenderBufferDesc::ReadbackBuffer(SkyW*SkyH*8));
    auto copyReadback=[&](RenderTexture *source,RenderBuffer *destination,DXGI_FORMAT format,uint32_t w,uint32_t h,uint32_t bpp) {
        worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(source,RenderTextureLayout::COPY_SOURCE));
        D3D12_TEXTURE_COPY_LOCATION dst{};dst.pResource=static_cast<D3D12Buffer*>(destination)->d3d;
        dst.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;dst.PlacedFootprint.Footprint={format,w,h,1,w*bpp};
        D3D12_TEXTURE_COPY_LOCATION src{};src.pResource=static_cast<D3D12Texture*>(source)->d3d;
        src.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        static_cast<D3D12CommandList*>(worker.commandList.get())->d3d->CopyTextureRegion(&dst,0,0,0,&src,nullptr);
    };
    auto bind=[&]() {
        worker.commandList->setGraphicsPipelineLayout(layout.get());
        worker.commandList->setGraphicsDescriptorSet(common.get(),0);worker.commandList->setGraphicsDescriptorSet(textures.get(),1);
        worker.commandList->setGraphicsDescriptorSet(textures.get(),2);worker.commandList->setGraphicsDescriptorSet(framebufferSet.get(),3);
    };
    Wr64RasterSkyPipelines pipelines;
    auto capture=[&]() {
        fill(paramsBuffer,&reflection,sizeof(reflection));fill(rdpBuffer,rdp,sizeof(rdp));
        worker.commandList->begin();
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(captureTarget.texture(),RenderTextureLayout::COLOR_WRITE));
        worker.commandList->setFramebuffer(captureTarget.framebuffer());worker.commandList->clearColor(0,RenderColor(0,0,0,0));
        bind(); worker.commandList->setPipeline(pipelines.capture());
        worker.commandList->setViewports(RenderViewport(0,0,SkyW,SkyH));worker.commandList->setScissors(RenderRect(0,0,SkyW,SkyH));
        worker.commandList->drawInstanced(3,1,0,0);
        copyReadback(captureTarget.texture(),skyReadback.get(),DXGI_FORMAT_R16G16B16A16_FLOAT,SkyW,SkyH,8);
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(captureTarget.texture(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
        std::vector<float> result(SkyW*SkyH*4);const RenderRange range(0,SkyW*SkyH*8),noWrite(0,0);
        const auto *mapped=static_cast<const uint16_t*>(skyReadback->map(0,&range));require(mapped,"Sky readback map failed");
        for(size_t i=0;i<result.size();++i){result[i]=rasterSkyHalf(mapped[i]);require(std::isfinite(result[i]),"Raster capture contains nonfinite pixels");}
        skyReadback->unmap(0,&noWrite);return result;
    };
    size_t capturePixels=0,compositionPixels=0;int maxWaterError=0;
    for(uint32_t samples:{1u,4u}) {
        const RenderMultisampling ms(samples);
        require(pipelines.prepare(device,layout.get(),ms,false,false),"Raster-only production pipelines failed");
        require(pipelines.capture() && pipelines.get(false,false,false),"Raster capture/water pipeline missing");
        rp[0].flags.sampleCount=samples==1?0:2;fill(rpBuffer,rp,sizeof(rp));
        for(float opacity:{0.f,.5f,1.f}) {
            rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,opacity);auto pixels=capture();
            for(uint32_t y=4;y<SkyH-4;y+=4)for(uint32_t x=4;x<SkyW-4;x+=4) {
                double lon=((x+.5)/SkyW-.5)*2*Pi,lat=(.5-(y+.5)/SkyH)*Pi;
                double dx=std::sin(lon)*std::cos(lat),dy=std::sin(lat),dz=std::cos(lon)*std::cos(lat);
                // The asymmetric left/right edge detects longitude-sign
                // mistakes that a centered constant-color card cannot expose.
                bool hit=dz>0 && dx/dz>-1.8 && dx/dz<3.8 && std::abs(dy/dz)<3.8;
                bool miss=dz<=0 || dx/dz<-2.2 || dx/dz>4.2 || std::abs(dy/dz)>4.2;
                if(!hit&&!miss)continue;
                const float expected[]={.8f*opacity,.2f*opacity,.1f*opacity,opacity};size_t p=(y*SkyW+x)*4;
                for(uint32_t c=0;c<4;++c)require(std::abs(pixels[p+c]-(hit?expected[c]:0))<.001f,
                    "Raster sky capture direction/color/premultiplied alpha mismatch");++capturePixels;
            }
            require(capture()==pixels,"Repeated raster capture changed its output");
        }
        rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,1);const auto environment=capture();
        auto target=device->createTexture(RenderTextureDesc::ColorTarget(W,H,RenderFormat::R8G8B8A8_UNORM,ms));
        auto resolved=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
        auto readback=device->createBuffer(RenderBufferDesc::ReadbackBuffer(W*H*4));
        const RenderTexture *attachment[]={target.get()};auto framebuffer=device->createFramebuffer(RenderFramebufferDesc(attachment,1));
        interop::RasterParams push{};push.screenScale=hlslpp::float2(1,1);
        const RenderInputSlot slots[]={RenderInputSlot(0,16),RenderInputSlot(1,8),RenderInputSlot(2,16)};
        const RenderVertexBufferView vertices[]={RenderVertexBufferView(screens->at(0),sizeof(screen)),
            RenderVertexBufferView(uvs->at(0),sizeof(uv)),RenderVertexBufferView(shades->at(0),sizeof(colors))};
        const RenderIndexBufferView index(faces->at(0),sizeof(indices),RenderFormat::R32_UINT);
        auto water=[&](bool enabled,bool smooth) {
            reflection.enabled=enabled;reflection.smoothNormals=smooth;fill(paramsBuffer,&reflection,sizeof(reflection));
            worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(target.get(),RenderTextureLayout::COLOR_WRITE));
            worker.commandList->setFramebuffer(framebuffer.get());worker.commandList->clearColor(0,RenderColor(.8f,.4f,.2f,1));
            bind();worker.commandList->setGraphicsPushConstants(0,&push);worker.commandList->setPipeline(pipelines.get(false,false,false));
            worker.commandList->setViewports(RenderViewport(0,0,W,H));worker.commandList->setScissors(RenderRect(0,0,W,H));
            worker.commandList->setVertexBuffers(0,vertices,3,slots);worker.commandList->setIndexBuffer(&index);worker.commandList->drawIndexedInstanced(6,1,0,0,0);
            RenderTexture *source=target.get();if(samples>1){const RenderTextureBarrier b[]={{target.get(),RenderTextureLayout::RESOLVE_SOURCE},{resolved.get(),RenderTextureLayout::RESOLVE_DEST}};
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,b,2);worker.commandList->resolveTexture(resolved.get(),target.get());source=resolved.get();}
            copyReadback(source,readback.get(),DXGI_FORMAT_R8G8B8A8_UNORM,W,H,4);
            worker.commandList->end();worker.execute();worker.wait();Pixels result(W*H*4);const RenderRange range(0,result.size()),noWrite(0,0);
            const void *mapped=readback->map(0,&range);require(mapped,"Raster water readback failed");std::memcpy(result.data(),mapped,result.size());readback->unmap(0,&noWrite);return result;
        };
        size_t strongerPixels[2]={},clampedPartialPixels=0;
        // Partial sky opacity is essential here: clamping after sky alpha
        // would incorrectly make a boosted translucent sky become opaque.
        for(float skyOpacity:{1.f,.5f}) {
            rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,skyOpacity);capture();
            for(uint8_t alpha:{uint8_t(0),uint8_t(64),uint8_t(128),uint8_t(255)}) {
                setWaterAlpha(alpha);
                for(float height:{.05f,1.f,10.f,100.f}) {
                    reflection.camera[1]=height;reflection.strength=1.f;
                    const auto original=water(false,true);Pixels baseline;
                    uint32_t strengthIndex=0;
                    for(float strength:{1.f,1.5f,2.f}) {
                        reflection.strength=strength;const auto reflected=water(true,true);
                        if(strengthIndex==0)baseline=reflected;
                        for(uint32_t y=4;y<H-4;++y)for(uint32_t x=4;x<W-4;++x) {
                            const double px=-5+(x+.5)*10/W,pz=5-(y+.5)*10/H;
                            const double vx=-px,vy=height,vz=-10-pz,length=std::sqrt(vx*vx+vy*vy+vz*vz);
                            // Lookup points upward and away from camera. Exclude the
                            // finite card edge; all admitted directions see uniform sky.
                            if(std::abs(-vx/-vz)>3.7 || std::abs(vy/-vz)>3.7)continue;
                            const double f0=std::pow((1.333-1)/(1.333+1),2),f=f0+(1-f0)*std::pow(1-vy/length,5);
                            const double weight=std::clamp(f*strength,0.,1.)*skyOpacity;
                            require(std::isfinite(weight)&&weight>=0&&weight<=skyOpacity,
                                "Boosted raster reflection weight is nonfinite or exceeds sky opacity");
                            size_t p=(y*W+x)*4;const double env[]={.8,.2,.1};bool visiblyStronger=false;
                            for(uint32_t c=0;c<3;++c) {
                                const double skyChannel=env[c]*255;
                                const int expected=int(std::lround(original[p+c]*(1-weight)+skyChannel*weight));
                                const int err=std::abs(int(reflected[p+c])-expected);maxWaterError=std::max(maxWaterError,err);
                                require(err<=2,"Raster water strength/Fresnel/native-alpha composition mismatch");
                                require(reflected[p+c]>=std::min(double(original[p+c]),skyChannel)-2 &&
                                    reflected[p+c]<=std::max(double(original[p+c]),skyChannel)+2,
                                    "Boosted raster water escaped the native-water/sky color bounds");
                                if(strengthIndex>0 && f*strength<1) {
                                    const double before=std::abs(baseline[p+c]-skyChannel),after=std::abs(reflected[p+c]-skyChannel);
                                    require(after<=before+2,"Increasing unsaturated strength weakened the reflection");
                                    visiblyStronger|=before-after>=2;
                                }
                            }
                            if(visiblyStronger)++strongerPixels[strengthIndex-1];
                            if(strengthIndex>0 && skyOpacity<1 && f*strength>=1)++clampedPartialPixels;
                            require(reflected[p+3]==original[p+3],"Raster sky altered native water coverage");++compositionPixels;
                        }
                        require(water(false,true)==original,"Strength changed disabled native water");
                        require(water(true,true)==reflected,"Repeated boosted water pass changed output");
                        ++strengthIndex;
                    }
                    reflection.strength=1.f;
                    require(water(true,true)==baseline,"Restoring default strength changed the original raster water baseline");
                }
            }
        }
        require(strongerPixels[0]>100 && strongerPixels[1]>100 && clampedPartialPixels>100,
            "Raster strength fixture missed visible boosts or clamped partial-opacity sky");
        std::printf("Raster-only %ux strength: 1.5x visibly stronger at %zu pixels, 2x at %zu; %zu clamped partial-sky pixels.\n",
            samples,strongerPixels[0],strongerPixels[1],clampedPartialPixels);
        rdp[1].primColor=hlslpp::float4(.8f,.2f,.1f,1);capture();
        reflection.camera[1]=10;setWaterAlpha(128);const auto flat=water(true,true);
        world[1][1]=world[2][1]=2;fill(positions,world,sizeof(world));
        const auto tilted=water(true,true);require(tilted!=flat,"Raster reflection ignored current water geometry/normal");
        world[1][1]=world[2][1]=0;fill(positions,world,sizeof(world));
        require(water(true,true)==flat,"Restoring water plane failed exact output restoration");
        require(capture()==environment,"Water pass leaked state into following sky capture");
        writePPM(prefix+"-"+std::to_string(samples)+"x-water.ppm",flat);
        std::printf("Raster-only %ux: capture and native-water composition passed; no AS resource.\n",samples);
    }
    // The measured native seven-vertex cloud chart is independent of the
    // synthetic directional card above. Only its texture pixels are replaced
    // by white, exposing the original continuous radial-alpha law directly.
    for(uint32_t c=0;c<3;++c)reflection.skyCamera[c]=float(NativeSkyArchiveFixture::DerivedCamera[c]);
    for(uint32_t v=0;v<7;++v){
        std::memcpy(world[v+4],NativeSkyArchiveFixture::Positions[v],3*sizeof(float));world[v+4][3]=1;
        std::memcpy(uv[v+4],NativeSkyArchiveFixture::Texcoords[v],2*sizeof(float));
    }
    for(uint32_t i=0;i<18;++i)indices[i+6]=4+NativeSkyArchiveFixture::NativeFanIndices[i];
    fill(positions,world,sizeof(world));fill(faces,indices,sizeof(indices));fill(uvs,uv,sizeof(uv));
    reflection.sky[0]=6;reflection.sky[1]=1;reflection.sky[2]=6;reflection.sky[3]=1;
    reflection.skyCloudParams[0]=NativeSkyArchiveFixture::NativeAlphaSlope;
    reflection.skyCloudParams[1]=NativeSkyArchiveFixture::NativeAlphaIntercept;reflection.skyCloudParams[2]=1;
    reflection.skyBackdrop[3]=0;
    rp[1]=rp[0];rp[1].ccL=NativeSkyArchiveFixture::ColorCombiner[0];rp[1].ccH=NativeSkyArchiveFixture::ColorCombiner[1];
    rp[1].omL=NativeSkyArchiveFixture::OtherMode[0];rp[1].omH=NativeSkyArchiveFixture::OtherMode[1];
    ri[1].rdpTileCount=1;rdp[1].primColor=hlslpp::float4(1,1,1,1);
    fill(rpBuffer,rp,sizeof(rp));fill(riBuffer,ri,sizeof(ri));
    std::fill(waterTexels.begin(),waterTexels.end(),255);fill(waterUpload,waterTexels.data(),waterTexels.size());
    worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::COPY_DEST));
    worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(waterTexture.get()),
        RenderTextureCopyLocation::PlacedFootprint(waterUpload,RenderFormat::R8G8B8A8_UNORM,W,H,1,W));
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(waterTexture.get(),RenderTextureLayout::SHADER_READ));
    worker.commandList->end();worker.execute();worker.wait();
    const auto cloud=capture();size_t radialPixels=0,partialPixels=0;
    for(uint32_t y=3;y<SkyH/2-3;y+=3)for(uint32_t x=3;x<SkyW-3;x+=3){
        const double latitude=(.5-(y+.5)/SkyH)*Pi;
        const double distance=(400-NativeSkyArchiveFixture::DerivedCamera[1])/std::tan(latitude);
        const double a=std::clamp((450-.055*distance)/255,0.,1.);
        const size_t p=(y*SkyW+x)*4;
        for(uint32_t c=0;c<4;++c)require(std::abs(cloud[p+c]-a)<.002,
            "Raster capture disagrees with archived native cloud radial-alpha law");
        ++radialPixels;if(a>.01&&a<.99)++partialPixels;
    }
    std::printf("Archived native cloud coverage: %zu directions, %zu partial-opacity samples.\n",radialPixels,partialPixels);
    require(radialPixels>5000&&partialPixels>100,"Archived cloud fixture did not cover enough faded directions");
    require(capture()==cloud,"Archived cloud recapture is unstable");
    require(capturePixels>10000&&compositionPixels>50000,"Raster fixture checked too few direction/composition pixels");
    std::printf("Archived native cloud: %zu directions, %zu partial-opacity samples.\n",radialPixels,partialPixels);
    pipelines.waitForPending();pipelines.reset();captureTarget.reset();
    std::printf("Raster sky: %zu directional capture pixels, %zu composition pixels, maximum color error %d bytes.\n",capturePixels,compositionPixels,maxWaterError);
}
