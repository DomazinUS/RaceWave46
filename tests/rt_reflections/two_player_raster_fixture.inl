// Isolated no-AS test of two independently owned raster reflection, sky and
// shadow targets. Native RSP half-viewports are mapped into horizontal/vertical
// panes before the production planar helper, exactly as in endFramebuffers.
void verifyTwoPlayerRaster(RenderDevice *device, FixtureWorker &worker, const std::string &prefix) {
    constexpr uint32_t W=64,H=64,Map=128;
    std::vector<std::unique_ptr<RenderBuffer>> buffers;
    auto upload=[&](const void *data,size_t bytes,RenderBufferFlags flags) {
        auto b=device->createBuffer(RenderBufferDesc::UploadBuffer((flags&RenderBufferFlag::CONSTANT)?
            (bytes+255)&~uint64_t(255):bytes,flags));
        require(b!=nullptr,"Two-player raster allocation failed");fill(b.get(),data,bytes);
        auto *p=b.get();buffers.push_back(std::move(b));return p;
    };
    SamplerLibrary samplers;fillSamplers(device,samplers.nearest,RenderFilter::NEAREST);
    fillSamplers(device,samplers.linear,RenderFilter::LINEAR);
    FramebufferRendererDescriptorCommonSet prototype(samplers,false,device);
    FramebufferRendererDescriptorTextureSet textures(device,1);
    FramebufferRendererDescriptorFramebufferSet framebufferSet(device);
    require(prototype.SceneBVH==0,"Raster-only fixture layout declares an AS");
    RenderPipelineLayoutBuilder builder;builder.begin(false,true);
    builder.addPushConstant(0,0,sizeof(interop::RasterParams),RenderShaderStageFlag::VERTEX|RenderShaderStageFlag::PIXEL);
    builder.addDescriptorSet(prototype);builder.addDescriptorSet(textures);builder.addDescriptorSet(textures);
    builder.addDescriptorSet(framebufferSet);builder.end();auto layout=builder.create(device);
    require(layout!=nullptr,"Two-player raster layout failed");

    float world[12][4]={{-5,0,5,1},{5,0,5,1},{5,0,-5,1},{-5,0,-5,1},
        {-5,0,5,1},{5,0,5,1},{5,0,-5,1},{-5,0,-5,1},
        {-2.5f,1,2.5f,1},{2.5f,1,2.5f,1},{2.5f,1,-2.5f,1},{-2.5f,1,-2.5f,1}};
    float screen[12][4]={{0,0,.5f,1},{64,0,.5f,1},{64,32,.5f,1},{0,32,.5f,1},
        {0,32,.5f,1},{64,32,.5f,1},{64,64,.5f,1},{0,64,.5f,1}};
    float uv[12][2]{},colors[12][4];for(auto &v:colors)for(float &c:v)c=1;
    const uint32_t indices[]={0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11};
    auto *faces=upload(indices,sizeof(indices),RenderBufferFlag::INDEX|RenderBufferFlag::STORAGE);
    auto *screens=upload(screen,sizeof(screen),RenderBufferFlag::VERTEX);
    auto *uvs=upload(uv,sizeof(uv),RenderBufferFlag::VERTEX|RenderBufferFlag::STORAGE);
    auto *shades=upload(colors,sizeof(colors),RenderBufferFlag::VERTEX|RenderBufferFlag::STORAGE);
    interop::FrameParams frame{};interop::FramebufferParams fb{};
    fb.resolution=hlslpp::float2(W,H);fb.resolutionScale=hlslpp::float2(1,1);
    const interop::RenderIndices ri[]={{0,0,0,1,0},{1,12,0,0,0},{0,6,0,1,0},{2,0,0,0,0},{2,6,0,0,0}};
    interop::RenderParams rp[3]{};interop::RDPParams rdp[3]{};
    for(auto &p:rp) {
        p.ccL=(8u<<20)|(31u<<15)|(7u<<12)|(7u<<9)|(8u<<5)|31u;
        p.ccH=(8u<<28)|(8u<<24)|(7u<<21)|(7u<<18)|(3u<<15)|(7u<<12)|(3u<<9)|(3u<<6)|(7u<<3)|3u;
        p.flags.NoN=1;p.flags.smoothShade=1;
    }
    rp[0].ccL=0xFCFFFFFF;rp[0].ccH=0xFFFCF279;rp[0].omL=0x005049D8;rp[0].omH=0x00082CFF;
    rp[0].flags.usesTexture0=1;rp[0].flags.nativeSampler0=NATIVE_SAMPLER_CLAMP_CLAMP;
    rp[0].flags.cms0=rp[0].flags.cmt0=2;
    rdp[0].primColor=hlslpp::float4(1,1,1,1);rdp[2].primColor=hlslpp::float4(1,.05f,.9f,1);
    interop::RDPTile tile{};tile.shifts=tile.shiftt=1;tile.lrs=tile.lrt=63*4;tile.cms=tile.cmt=2;
    tile.fmt=0;tile.siz=3;tile.stride=256;tile.nativeSampler=NATIVE_SAMPLER_CLAMP_CLAMP;
    interop::GPUTile gpuTile{};gpuTile.ulScale=gpuTile.tcScale=hlslpp::float2(1,1);gpuTile.textureDimensions=hlslpp::float3(W,H,1);
    auto *frameBuffer=upload(&frame,sizeof(frame),RenderBufferFlag::CONSTANT);
    auto *fbBuffer=upload(&fb,sizeof(fb),RenderBufferFlag::CONSTANT);
    auto *indicesBuffer=upload(ri,sizeof(ri),RenderBufferFlag::STORAGE);
    auto *rpBuffer=upload(rp,sizeof(rp),RenderBufferFlag::STORAGE);
    auto *tileBuffer=upload(&tile,sizeof(tile),RenderBufferFlag::STORAGE);
    auto *gpuTileBuffer=upload(&gpuTile,sizeof(gpuTile),RenderBufferFlag::STORAGE);
    Pixels texels(W*H*4);for(size_t p=0;p<texels.size();p+=4){texels[p]=51;texels[p+1]=102;texels[p+2]=153;texels[p+3]=128;}
    auto texture=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
    auto textureView=texture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
    auto *texUpload=upload(texels.data(),texels.size(),0);
    textures.setTexture(0,texture.get(),RenderTextureLayout::SHADER_READ,textureView.get());
    worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(texture.get(),RenderTextureLayout::COPY_DEST));
    worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(texture.get()),
        RenderTextureCopyLocation::PlacedFootprint(texUpload,RenderFormat::R8G8B8A8_UNORM,W,H,1,W));
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(texture.get(),RenderTextureLayout::SHADER_READ));
    worker.commandList->end();worker.execute();worker.wait();
    framebufferSet.setBuffer(framebufferSet.FbParams,fbBuffer,sizeof(fb));
    const RenderInputSlot slots[]={RenderInputSlot(0,16),RenderInputSlot(1,8),RenderInputSlot(2,16)};
    const RenderVertexBufferView vertices[]={RenderVertexBufferView(screens->at(0),sizeof(screen)),
        RenderVertexBufferView(uvs->at(0),sizeof(uv)),RenderVertexBufferView(shades->at(0),sizeof(colors))};
    const RenderIndexBufferView index(faces->at(0),sizeof(indices),RenderFormat::R32_UINT);
    struct View {
        FramebufferRenderer::Wr64RTView rt;
        RenderBuffer *worldBuffer=nullptr,*rdpBuffer=nullptr;
        Params params;float world[12][4]{};interop::RDPParams rdp[3]{};
        hlslpp::float2 scale,offset;
    } views[2];
    auto bindCommon=[&](FramebufferRendererDescriptorCommonSet &c,RenderBuffer *params,RenderBuffer *positions,RenderBuffer *materials) {
        c.setBuffer(c.FrParams,frameBuffer,sizeof(frame));c.setBuffer(c.RtParams,params,sizeof(Params));
        c.setBuffer(c.instanceRDPParams,materials,sizeof(rdp),RenderBufferStructuredView(sizeof(rdp[0])));
        c.setBuffer(c.RDPTiles,tileBuffer,sizeof(tile),RenderBufferStructuredView(sizeof(tile)));
        c.setBuffer(c.GPUTiles,gpuTileBuffer,sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
        c.setBuffer(c.instanceRenderIndices,indicesBuffer,sizeof(ri),RenderBufferStructuredView(sizeof(ri[0])));
        c.setBuffer(c.DynamicRenderParams,rpBuffer,sizeof(rp),RenderBufferStructuredView(sizeof(rp[0])));
        c.setBuffer(c.posBuffer,positions,sizeof(world));c.setBuffer(c.indexBuffer,faces,sizeof(indices));
        c.setBuffer(c.genTexCoordBuffer,uvs,sizeof(uv));c.setBuffer(c.shadedColBuffer,shades,sizeof(colors));
    };
    for(uint32_t v=0;v<2;++v) {
        auto &s=views[v];auto &rt=s.rt;std::memcpy(s.world,world,sizeof(world));std::memcpy(s.rdp,rdp,sizeof(rdp));
        for(auto &point:s.world)point[0]+=100*v;
        s.rdp[1].primColor=v?hlslpp::float4(.1f,.8f,.2f,1):hlslpp::float4(.8f,.2f,.1f,1);
        s.worldBuffer=upload(s.world,sizeof(s.world),RenderBufferFlag::STORAGE);s.rdpBuffer=upload(s.rdp,sizeof(s.rdp),RenderBufferFlag::STORAGE);
        rt.paramsBuffer=device->createBuffer(RenderBufferDesc::UploadBuffer((sizeof(Params)+255)&~uint64_t(255),RenderBufferFlag::CONSTANT));
        rt.rasterReflectionParamsBuffer=device->createBuffer(RenderBufferDesc::UploadBuffer(256,RenderBufferFlag::CONSTANT));
        rt.rasterShadowParamsBuffer=device->createBuffer(RenderBufferDesc::UploadBuffer(256,RenderBufferFlag::CONSTANT));
        require(rt.paramsBuffer&&rt.rasterReflectionParamsBuffer&&rt.rasterShadowParamsBuffer,"Per-view constants missing");
        rt.descriptor=std::make_unique<FramebufferRendererDescriptorCommonSet>(samplers,false,device);
        auto &c=*rt.descriptor;require(c.SceneBVH==0,"Per-view raster descriptor declares AS");
        bindCommon(c,rt.paramsBuffer.get(),s.worldBuffer,s.rdpBuffer);
        require(rt.rasterReflectionTarget.ensure(&worker,Map,Map)&&rt.rasterShadowTarget.ensure(&worker,Map)&&rt.rasterSkyTarget.ensure(&worker,64,32),
            "Per-view raster target creation failed");
        c.setBuffer(c.wr64RasterReflectionParams,rt.rasterReflectionParamsBuffer.get(),sizeof(rt.rasterReflectionParams));
        c.setBuffer(c.wr64RasterShadowParams,rt.rasterShadowParamsBuffer.get(),sizeof(rt.rasterShadowParams));
        c.setTexture(c.wr64RasterReflectionColor,rt.rasterReflectionTarget.color(),RenderTextureLayout::SHADER_READ);
        c.setTexture(c.wr64RasterShadowMap,rt.rasterShadowTarget.color(),RenderTextureLayout::SHADER_READ);
        c.setTexture(c.wr64RasterSky,rt.rasterSkyTarget.texture(),RenderTextureLayout::SHADER_READ);
    }
    require(views[0].rt.descriptor->get()!=views[1].rt.descriptor->get()&&views[0].rt.paramsBuffer!=views[1].rt.paramsBuffer&&
        views[0].worldBuffer!=views[1].worldBuffer&&views[0].rt.rasterReflectionTarget.color()!=views[1].rt.rasterReflectionTarget.color()&&
        views[0].rt.rasterShadowTarget.color()!=views[1].rt.rasterShadowTarget.color()&&views[0].rt.rasterSkyTarget.texture()!=views[1].rt.rasterSkyTarget.texture(),
        "Two raster views alias mutable allocations");
    auto bind=[&](uint32_t v) {
        worker.commandList->setGraphicsPipelineLayout(layout.get());worker.commandList->setGraphicsDescriptorSet(views[v].rt.descriptor->get(),0);
        worker.commandList->setGraphicsDescriptorSet(textures.get(),1);worker.commandList->setGraphicsDescriptorSet(textures.get(),2);
        worker.commandList->setGraphicsDescriptorSet(framebufferSet.get(),3);worker.commandList->setVertexBuffers(0,vertices,3,slots);
        worker.commandList->setIndexBuffer(&index);
    };
    auto pane=[&](bool vertical,uint32_t v) {return vertical?RenderRect(v*W/2,0,(v+1)*W/2,H):RenderRect(0,v*H/2,W,(v+1)*H/2);};
    size_t submissions=0,positivePixels=0,isolatedPixels=0,projectionPixels=0,tidePixels=0;
    for(uint32_t samples:{1u,4u}) {
        const RenderMultisampling ms(samples);for(auto &p:rp)p.flags.sampleCount=samples==1?0:2;fill(rpBuffer,rp,sizeof(rp));
        Wr64RasterReflectionPipelines planarPipelines[4];Wr64RasterSkyPipelines skyPipelines;
        Wr64RasterShadowPipelines shadowPipelines[2];
        for(uint32_t i=0;i<4;++i)require(planarPipelines[i].prepare(device,layout.get(),ms,false,false,
            i&1?Wr64RasterReflectionSkyMode::RasterSky:Wr64RasterReflectionSkyMode::SkyOff,(i&2)!=0),"Planar combination PSO failed");
        require(skyPipelines.prepare(device,layout.get(),ms,false,false),"Raster sky PSO failed");
        for(uint32_t i=0;i<2;++i)require(shadowPipelines[i].prepare(device,layout.get(),ms,false,false,
            i?Wr64RasterShadowWaterMode::RasterSky:Wr64RasterShadowWaterMode::Native),"Raster shadow PSO failed");
        ShaderLibrary nativeLibrary(false,false);fillSamplers(device,nativeLibrary.samplerLibrary.nearest,RenderFilter::NEAREST);
        fillSamplers(device,nativeLibrary.samplerLibrary.linear,RenderFilter::LINEAR);
        RasterShaderUber nativeShaders(device,RenderShaderFormat::DXIL,ms,&nativeLibrary,1);
        PipelineCreation creation{};creation.device=device;creation.pipelineLayout=layout.get();creation.vertexShader=nativeShaders.vertexShader.get();
        creation.pixelShader=nativeShaders.pixelShader.get();creation.alphaBlend=true;creation.NoN=true;creation.multisampling=ms;
        auto native=RasterShader::createPipeline(creation);require(native!=nullptr,"Independent native PSO failed");nativeShaders.waitForPipelineCreation();
        FramebufferRenderer submitter(&worker,false,UserConfiguration::GraphicsAPI::D3D12,&nativeLibrary);
        submitter.rendererPipelineLayout=layout.get();submitter.descTextureSet=std::make_unique<FramebufferRendererDescriptorTextureSet>(device,1);
        submitter.descTextureSet->setTexture(0,texture.get(),RenderTextureLayout::SHADER_READ,textureView.get());
        submitter.descCommonSet=std::make_unique<FramebufferRendererDescriptorCommonSet>(samplers,false,device);
        Params disabled{};auto *nativeParams=upload(&disabled,sizeof(disabled),RenderBufferFlag::CONSTANT);
        bindCommon(*submitter.descCommonSet,nativeParams,views[0].worldBuffer,views[0].rdpBuffer);
        for(uint32_t i=0;i<3;++i){submitter.vertexInputSlots[i]=slots[i];submitter.indexedVertexViews[i]=vertices[i];}submitter.indexBufferView=index;
        FramebufferRenderer::Framebuffer output;output.viewport=RenderViewport(0,0,W,H);
        output.descRealFbSet=std::make_unique<FramebufferRendererDescriptorFramebufferSet>(device);
        output.descDummyFbSet=std::make_unique<FramebufferRendererDescriptorFramebufferSet>(device);
        RenderTarget colorTarget(0,Framebuffer::Type::Color,ms,false),depthTarget(0,Framebuffer::Type::Depth,ms,false);
        require(colorTarget.resize(&worker,W,H)&&depthTarget.resize(&worker,W,H),"Two-player output target failed");
        RenderFramebufferStorage storage;storage.setup(device,RenderFramebufferKey{},&colorTarget,&depthTarget);
        for(auto *set:{output.descRealFbSet.get(),output.descDummyFbSet.get()}) {
            set->setBuffer(set->FbParams,fbBuffer,sizeof(fb));
            set->setTexture(set->gBackgroundDepth,depthTarget.texture.get(),RenderTextureLayout::DEPTH_READ,depthTarget.textureView.get());
        }
        auto resolved=device->createTexture(RenderTextureDesc::Texture2D(W,H,1,RenderFormat::R8G8B8A8_UNORM));
        auto readback=device->createBuffer(RenderBufferDesc::ReadbackBuffer(W*H*4));
        // effects: objects=1, sky=2, shadows=4. Failure is per view, not global.
        auto render=[&](bool vertical,uint32_t effects,uint32_t failed=0,bool reverse=false,float cameraShift=0,bool blobs=false,uint32_t covered=3,
            float planeY=0,bool fixedObjectHeight=false) {
            for(uint32_t v=0;v<2;++v) {
                auto &s=views[v];auto &rt=s.rt;const bool ready=(failed&(1u<<v))==0;
                s.scale=vertical?hlslpp::float2(.5f,2):hlslpp::float2(1,1);
                s.offset=vertical?hlslpp::float2(v?.5f:-.5f,v?1.f:-1.f):hlslpp::float2(0,0);
                const float center=100.f*v+(v==0?cameraShift:0);
                float nativeRows[4][4]={{.2f,0,0,-.2f*center},{0,0,.2f,0},{0,-.05f,0,.5f+.05f*planeY},{0,0,0,1}};
                const float vpScale[]={32,16,1},vpTranslate[]={32,v?48.f:16.f,0},fbSize[]={64,64};
                const float scale[]={float(s.scale.x),float(s.scale.y)},offset[]={float(s.offset.x),float(s.offset.y)};
                const auto clip=wr64BuildPlanarD3DClipProjection(nativeRows,vpScale,vpTranslate,fbSize,scale,offset);
                const auto mirror=wr64BuildPlanarReflectionProjection(clip.rows,planeY);require(clip.valid&&mirror.valid,"Split planar rows rejected");
                std::memcpy(rt.rasterReflectionParams.reflectedRows,mirror.rows,sizeof(mirror.rows));
                std::memcpy(rt.rasterReflectionParams.plane,mirror.clipPlane,sizeof(mirror.clipPlane));
                rt.rasterReflectionParams.options[0]=(effects&1)&&ready?1.f:0.f;rt.rasterReflectionParams.options[1]=1;
                rt.rasterReflectionParams.options[2]=0;rt.rasterReflectionParams.options[3]=.5f;
                // The same raw native half viewport, followed by horizontal or
                // vertical presentation, must equal the independently written pane.
                const auto rectangle=pane(vertical,v);
                for(uint32_t corner=0;corner<4;++corner) {
                    float p[]={world[corner][0]+center,planeY,world[corner][2],1},c[4]{};
                    for(uint32_t r=0;r<4;++r)for(uint32_t k=0;k<4;++k)c[r]+=clip.rows[r][k]*p[k];
                    const float expectedX=(corner==1||corner==2)?float(rectangle.right):float(rectangle.left);
                    const float expectedY=corner>=2?float(rectangle.bottom):float(rectangle.top);
                    require(std::abs((c[0]/c[3]*.5f+.5f)*W-expectedX)<.0001f&&
                        std::abs((.5f-c[1]/c[3]*.5f)*H-expectedY)<.0001f,"RSP viewport conversion misplaced one player");
                }
                s.params=Params{};s.params.enabled=ready&&effects?1u:0u;s.params.camera[0]=center;s.params.camera[1]=10+planeY;s.params.camera[2]=0;
                s.params.shadowLight[1]=1;s.params.shadowLight[3]=.18f;
                std::memcpy(&rt.params,&s.params,sizeof(s.params));rt.prepared=ready;rt.traceReflections=false;
                rt.rasterReflections=(effects&1)!=0;rt.rasterSky=(effects&2)!=0;rt.rasterShadows=(effects&4)!=0;
                rt.shadowWaterSelected=ready;rt.shadowMapRecorded=ready&&(effects&4);rt.reflectionCaptureRecorded=ready&&(effects&1);
                rt.racerShadowCasters=1u<<v;rt.rasterShadowRacers=(covered&(1u<<v))?1u<<v:0;
                rt.nativeShadowDraws={{3+v,1u<<v}};
                auto &map=rt.rasterShadowParams;map={};map.lightRows[0][0]=.2f;map.lightRows[0][3]=-.2f*center;
                map.lightRows[1][2]=.2f;map.lightRows[2][1]=-.05f;map.lightRows[2][3]=.5f+.05f*planeY;map.lightRows[3][3]=1;
                map.options[0]=1.f/Map;map.options[1]=.001f;map.options[2]=.18f;map.options[3]=.5f;map.light[1]=1;map.light[3]=ready&&(effects&4)?1.f:0.f;
                fill(rt.paramsBuffer.get(),&s.params,sizeof(s.params));fill(rt.rasterReflectionParamsBuffer.get(),&rt.rasterReflectionParams,sizeof(rt.rasterReflectionParams));
                fill(rt.rasterShadowParamsBuffer.get(),&map,sizeof(map));
                // Camera-relative water coordinates follow the current native
                // presentation; physical object coordinates stay fixed.
                for(uint32_t i=0;i<8;++i)s.world[i][0]=world[i][0]+center;
                for(uint32_t i=0;i<12;++i)s.world[i][1]=world[i][1]+((fixedObjectHeight&&i>=8)?0:planeY);
                fill(s.worldBuffer,s.world,sizeof(s.world));
            }
            // Both owners are uploaded before recording any command. All six
            // captures and both pane draws share one execute/wait lifetime.
            worker.commandList->begin();
            for(uint32_t n=0;n<2;++n) {
                const uint32_t v=reverse?1-n:n;auto &rt=views[v].rt;
                auto clear=[&](RenderTexture *color,RenderTexture *depth,RenderFramebuffer *framebuffer,uint32_t w,uint32_t h,RenderColor colorValue) {
                    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(color,RenderTextureLayout::COLOR_WRITE));
                    if(depth)worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(depth,RenderTextureLayout::DEPTH_WRITE));
                    worker.commandList->setFramebuffer(framebuffer);worker.commandList->clearColor(0,colorValue);
                    if(depth)worker.commandList->clearDepth(true,1);bind(v);worker.commandList->setViewports(RenderViewport(0,0,float(w),float(h)));
                    worker.commandList->setScissors(RenderRect(0,0,w,h));
                };
                auto finish=[&](RenderTexture *color) {worker.commandList->setFramebuffer(nullptr);
                    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(color,RenderTextureLayout::SHADER_READ));};
                clear(rt.rasterReflectionTarget.color(),rt.rasterReflectionTarget.depth(),rt.rasterReflectionTarget.framebuffer(),Map,Map,RenderColor(0,0,0,0));
                worker.commandList->setPipeline(planarPipelines[0].capture(false));interop::RasterParams push{};push.screenScale=hlslpp::float2(1,1);push.renderIndex=1;
                worker.commandList->setGraphicsPushConstants(0,&push);worker.commandList->drawIndexedInstanced(6,1,12,0,0);finish(rt.rasterReflectionTarget.color());
                clear(rt.rasterShadowTarget.color(),rt.rasterShadowTarget.depth(),rt.rasterShadowTarget.framebuffer(),Map,Map,RenderColor(1,1,1,1));
                worker.commandList->setPipeline(shadowPipelines[0].capture());worker.commandList->setGraphicsPushConstants(0,&push);
                worker.commandList->drawIndexedInstanced(6,1,12,0,0);finish(rt.rasterShadowTarget.color());
                clear(rt.rasterSkyTarget.texture(),nullptr,rt.rasterSkyTarget.framebuffer(),64,32,
                    v?RenderColor(.08f,.4f,.72f,.8f):RenderColor(.72f,.4f,.08f,.8f));finish(rt.rasterSkyTarget.texture());
            }
            for(uint32_t v=0;v<2;++v)submitter.wr64RTViews[v]=std::move(views[v].rt);
            submitter.instanceDrawCallVector.clear();submitter.instanceDrawCallVector.resize(5);submitter.wr64RTDrawViews={1,0,2,1,2};
            for(uint32_t v=0;v<2;++v) {
                auto &call=submitter.instanceDrawCallVector[v?2:0];call.type=InstanceDrawCall::Type::IndexedTriangles;call.triangles={};
                const bool ready=(failed&(1u<<v))==0;const RenderPipeline *pipeline=native.get();
                if(ready&&effects) {
                    if(effects&1)pipeline=planarPipelines[((effects&2)?1:0)|((effects&4)?2:0)].get(false,false,false);
                    else if(effects&4)pipeline=shadowPipelines[(effects&2)?1:0].getWater((effects&2)?Wr64RasterShadowWaterMode::RasterSky:Wr64RasterShadowWaterMode::Native,false,false,false);
                    else pipeline=skyPipelines.get(false,false,false);
                }
                call.triangles.pipeline=pipeline;call.triangles.screenScale=views[v].scale;call.triangles.screenOffset=views[v].offset;
                call.triangles.scissor=pane(vertical,v);call.triangles.faceCount=2;call.triangles.indexStart=v*6;
                auto &blob=submitter.instanceDrawCallVector[3+v];blob.type=call.type;blob.triangles=call.triangles;blob.triangles.pipeline=native.get();
                const auto rectangle=pane(vertical,v);blob.triangles.scissor=RenderRect(rectangle.left+2,rectangle.top+2,rectangle.left+6,rectangle.top+6);
            }
            const RenderTextureBarrier outputBarriers[]={{colorTarget.texture.get(),RenderTextureLayout::COLOR_WRITE},{depthTarget.texture.get(),RenderTextureLayout::DEPTH_WRITE}};
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,outputBarriers,2);worker.commandList->setFramebuffer(storage.colorDepthWrite.get());
            worker.commandList->clearColor(0,RenderColor(.7f,.5f,.3f,0));worker.commandList->clearDepth(true,1);
            RasterScene scene;scene.instanceIndices=reverse?std::vector<uint32_t>{2,0}:std::vector<uint32_t>{0,2};
            if(blobs){scene.instanceIndices.push_back(3);scene.instanceIndices.push_back(4);}bool depthState=false;
            submitter.submitRasterScene(&worker,output,&storage,scene,depthState);worker.commandList->setFramebuffer(nullptr);
            RenderTexture *source=colorTarget.texture.get();
            if(samples>1) {const RenderTextureBarrier b[]={{source,RenderTextureLayout::RESOLVE_SOURCE},{resolved.get(),RenderTextureLayout::RESOLVE_DEST}};
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,b,2);worker.commandList->resolveTexture(resolved.get(),source);source=resolved.get();}
            worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(source,RenderTextureLayout::COPY_SOURCE));
            D3D12_TEXTURE_COPY_LOCATION dst{};dst.pResource=static_cast<D3D12Buffer*>(readback.get())->d3d;dst.Type=D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
            dst.PlacedFootprint.Footprint={DXGI_FORMAT_R8G8B8A8_UNORM,W,H,1,W*4};D3D12_TEXTURE_COPY_LOCATION src{};
            src.pResource=static_cast<D3D12Texture*>(source)->d3d;src.Type=D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            static_cast<D3D12CommandList*>(worker.commandList.get())->d3d->CopyTextureRegion(&dst,0,0,0,&src,nullptr);
            worker.commandList->end();worker.execute();worker.wait();++submissions;
            Pixels result(W*H*4);const RenderRange range(0,result.size()),noWrite(0,0);const void *mapped=readback->map(0,&range);
            require(mapped!=nullptr,"Two-player raster readback failed");std::memcpy(result.data(),mapped,result.size());readback->unmap(0,&noWrite);
            for(uint32_t v=0;v<2;++v)views[v].rt=std::move(submitter.wr64RTViews[v]);return result;
        };
        auto equalPane=[&](const Pixels &a,const Pixels &b,bool vertical,uint32_t v,const char *why) {
            const auto r=pane(vertical,v);for(int y=r.top;y<r.bottom;++y)for(int x=r.left;x<r.right;++x) {
                const size_t p=(y*W+x)*4;require(std::memcmp(a.data()+p,b.data()+p,4)==0,why);++isolatedPixels;
            }
        };
        for(bool vertical:{false,true}) {
            const auto original=render(vertical,0);std::array<Pixels,8> outcomes;
            for(uint32_t effects=0;effects<8;++effects) {
                const auto both=outcomes[effects]=render(vertical,effects);
                require(render(vertical,effects,0,true)==both,"Reversing raster capture/pane order changed output");
                for(uint32_t v=0;v<2;++v) {
                    const auto failed=render(vertical,effects,1u<<v);
                    equalPane(failed,original,vertical,v,"Failed raster view did not restore its exact native pane");
                    equalPane(failed,both,vertical,1-v,"Failed raster view changed the healthy player's pane");
                    if(effects) {size_t changed=0;const auto r=pane(vertical,v);
                        for(int y=r.top+2;y<r.bottom-2;++y)for(int x=r.left+2;x<r.right-2;++x) {
                            const size_t p=(y*W+x)*4;if(std::memcmp(both.data()+p,original.data()+p,3)!=0)++changed;
                            require(both[p+3]==original[p+3],"Raster effect changed native coverage in one pane");
                        }
                        require(changed>40,"Raster combination lacks a visible positive control in one pane");positivePixels+=changed;
                    }
                }
                const auto moved=render(vertical,effects,0,false,1);
                equalPane(moved,both,vertical,1,"Moving only player one contaminated player two's raster resources");
                if(effects&5)require(moved!=both,"Physical object/shadow capture failed to respond to player-one camera movement");
                require(render(vertical,effects)==both,"Returning the camera did not restore exact two-pane output");
            }
            // Individual switches must contribute in the all-three mode too.
            for(uint32_t bit:{1u,2u,4u})require(outcomes[7]!=outcomes[7^bit],"An all-raster component silently had no effect");
            // Southern Island uses negative native sea offsets. Translating
            // geometry and cameras with that datum must preserve the image;
            // alternate levels so neither owner can reuse a stale zero plane.
            const auto movedReference=render(vertical,7,0,false,1);
            for(float height:{-100.f,-150.f,-125.f,0.f}) {
                const auto translated=render(vertical,7,0,false,0,false,3,height);
                require(translated==outcomes[7],"Shared nonzero sea datum changed raster composition or split projection");
                const auto moved=render(vertical,7,0,false,1,false,3,height);
                require(moved==movedReference,"Moving one camera at nonzero tide changed capture projection");
                equalPane(moved,translated,vertical,1,"Changing tide and moving player one contaminated player two");
                tidePixels+=W*H*2;
            }
            // Also move only the sea/cameras past stationary geometry. Above
            // the Y=1 object, both captures must become empty and its shadow
            // must disappear; lowering the plane restores both physical effects.
            const auto submerged=render(vertical,7,0,false,0,false,3,2,true);
            for(size_t p=0;p<submerged.size();++p)require(std::abs(int(submerged[p])-int(outcomes[2][p]))<=(p%4==3?0:1),
                "Rising tide retained a submerged object's reflection or shadow in one pane");
            require(render(vertical,7,0,false,0,false,3,-2,true)==outcomes[7],
                "Lowering tide failed to restore an emerged object's reflection and shadow");
            require(render(vertical,7)==outcomes[7],"Returning to the original sea datum retained stale per-view state");
            tidePixels+=W*H*3;
            // Full-frame per-owner capture uses half its image. Positive pixels
            // must still occupy the central projected quarter of the right pane.
            for(uint32_t v=0;v<2;++v) {
                const auto r=pane(vertical,v);const uint32_t x=(r.left+r.right)/2,y=(r.top+r.bottom)/2;
                const size_t p=(y*W+x)*4;require(outcomes[1][p+v]>original[p+v]+2,"Object capture sampled the wrong player's color or empty half");
                const uint32_t left=uint32_t(r.left)+(r.right-r.left)/8,top=uint32_t(r.top)+(r.bottom-r.top)/8;
                const size_t q=(top*W+left)*4;require(std::memcmp(outcomes[1].data()+q,original.data()+q,4)==0,"Planar projection stretched object footprint over a whole pane");++projectionPixels;
            }
            const auto nativeBlobs=render(vertical,0,0,false,0,true);
            const auto noBlobs=render(vertical,7);require(render(vertical,7,0,false,0,true)==noBlobs,"Recorded per-view map failed to replace covered native blobs");
            for(uint32_t v=0;v<2;++v) {
                const auto fallback=render(vertical,7,1u<<v,false,0,true);
                equalPane(fallback,nativeBlobs,vertical,v,"Map failure hid the failed player's native blob");
                equalPane(fallback,noBlobs,vertical,1-v,"Map failure re-enabled the healthy player's native blob");
                const auto uncovered=render(vertical,7,0,false,0,true,3u^(1u<<v));
                equalPane(uncovered,noBlobs,vertical,1-v,"One uncovered racer changed another view's blob decision");
                const auto r=pane(vertical,v);const size_t p=((r.top+3)*W+r.left+3)*4;
                require(std::memcmp(uncovered.data()+p,nativeBlobs.data()+p,4)==0,"Uncovered racer did not retain native blob");
            }
            writePPM(prefix+"-raster-2p-"+(vertical?"vertical-":"horizontal-")+std::to_string(samples)+"x.ppm",outcomes[7]);
        }
        const RenderTexture *retained[2][3]{};const RenderDescriptorSet *descriptors[2]{};
        for(uint32_t v=0;v<2;++v) {
            submitter.wr64RTViews[v]=std::move(views[v].rt);auto &rt=submitter.wr64RTViews[v];
            retained[v][0]=rt.rasterReflectionTarget.color();retained[v][1]=rt.rasterSkyTarget.texture();retained[v][2]=rt.rasterShadowTarget.color();
            descriptors[v]=rt.descriptor->get();rt.rasterReflectors={{12,6,1}};rt.rasterShadowCasters={{12,6,1}};
            rt.reflectionPlaneValid=true;rt.waterDraws={v?2u:0u};rt.nativeRaceView=v+1;
        }
        submitter.resetFramebuffers(&worker,false,1,ms);require(submitter.wr64RTDrawViews.empty(),"Reset retained stale raster view ownership");
        for(uint32_t v=0;v<2;++v) {
            auto &rt=submitter.wr64RTViews[v];require(!rt.prepared&&!rt.params.enabled&&!rt.rasterReflections&&!rt.rasterSky&&!rt.rasterShadows&&
                !rt.reflectionCaptureRecorded&&!rt.shadowMapRecorded&&!rt.reflectionPlaneValid&&rt.rasterReflectors.empty()&&rt.rasterShadowCasters.empty()&&
                rt.waterDraws.empty()&&rt.nativeShadowDraws.empty()&&!rt.rasterShadowRacers,"Production reset retained active raster state");
            require(rt.descriptor->get()==descriptors[v]&&rt.rasterReflectionTarget.color()==retained[v][0]&&rt.rasterSkyTarget.texture()==retained[v][1]&&
                rt.rasterShadowTarget.color()==retained[v][2],"Production reset lost separate fenced raster targets");
            require(!rt.scene.prepared()&&!rt.scene.buildRecorded()&&!rt.scene.accelerationStructure(),"Raster-only fixture acquired a ray scene");
            views[v].rt=std::move(rt);
        }
    }
    std::printf("two-player raster: submissions%zu positive_pixels%zu isolated_pixels%zu projection_controls%zu tide_pixels%zu; horizontal+vertical 1x+4x; actual submission/reset; no AS allocation/build/binding\n",
        submissions,positivePixels,isolatedPixels,projectionPixels,tidePixels);
}
