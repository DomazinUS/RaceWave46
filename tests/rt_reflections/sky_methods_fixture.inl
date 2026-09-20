// Runs only under --sky-methods-only, using the production scene and raster
// readback above. The default RT fixture does not execute this block.
{
    // A left-side opaque reflector, plus an independent wide sky card. The
    // triangle is in the AS; the sky card deliberately is not.
    const float object[3][4]={{-40,-10,6,1},{0,-10,6,1},{0,60,6,1}};
    const float skyCard[4][4]={{-80,-80,30,1},{80,-80,30,1},{80,80,30,1},{-80,80,30,1}};
    std::memcpy(world+4,object,sizeof(object));std::memcpy(world+7,skyCard,sizeof(skyCard));
    const uint32_t skyFaces[6]={7,8,9,7,9,10};std::memcpy(indices+9,skyFaces,sizeof(skyFaces));
    for(auto &vertex:colors)for(float &channel:vertex)channel=1;
    fill(colorBuffer,colors,sizeof(colors));
    renderIndices[2]={2,9,0,0,0};
    params[0].ccL=0xFCFFFFFF;params[0].ccH=0xFFFCF279;
    params[0].omL=0x005049D8;params[0].omH=0x00082CFF;
    params[0].flags.usesTexture0=1;params[0].flags.nativeSampler0=NATIVE_SAMPLER_CLAMP_CLAMP;
    params[0].flags.cms0=params[0].flags.cmt0=2;params[0].flags.sampleCount=samples==1?0:2;
    params[2]=params[1];params[2].omL=0x00504240;params[2].omH=0x00882C3F;
    rdp[0].primColor=hlslpp::float4(1,1,1,1);rdp[1].primColor=hlslpp::float4(.1f,.9f,.2f,1);
    fill(renderParamsBuffer,params,sizeof(params));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
    for(size_t i=0;i<skyTexels.size();i+=4){skyTexels[i]=26;skyTexels[i+1]=51;skyTexels[i+2]=179;skyTexels[i+3]=128;}
    fill(skyTextureUpload,skyTexels.data(),skyTexels.size());fill(worldUpload,world,sizeof(world));fill(indexUpload,indices,sizeof(indices));
    worker.commandList->begin();
    const RenderBufferBarrier uploads[]={{positions.get(),RenderBufferAccess::WRITE},{faces.get(),RenderBufferAccess::WRITE}};
    worker.commandList->barriers(RenderBarrierStage::COPY,uploads,2,nullptr,0);
    worker.commandList->copyBufferRegion(positions->at(0),worldUpload->at(0),sizeof(world));
    worker.commandList->copyBufferRegion(faces->at(0),indexUpload->at(0),sizeof(indices));
    worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(skyTexture.get(),RenderTextureLayout::COPY_DEST));
    worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(skyTexture.get()),
        RenderTextureCopyLocation::PlacedFootprint(skyTextureUpload,RenderFormat::R8G8B8A8_UNORM,64,64,1,64));
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(skyTexture.get(),RenderTextureLayout::SHADER_READ));
    require(scene.recordBuild(&worker),"Sky-method fixture AS rebuild failed");
    worker.commandList->end();worker.execute();worker.wait();
    reflection=Params{};reflection.enabled=1;reflection.camera[1]=2;reflection.sky[3]=0;
    reflection.skyBackdrop[0]=9;reflection.skyBackdrop[1]=2;reflection.skyBackdrop[2]=2;reflection.skyBackdrop[3]=1;
    clearDestination=RenderColor(.8f,.4f,.2f,1);

    Wr64RasterSkyPipelines rasterPipelines,mixedPipelines,skyOnlyPipelines;
    require(rasterPipelines.prepare(device.get(),layout.get(),ms,false,false),"Raster reference PSO failed");
    require(mixedPipelines.prepare(device.get(),layout.get(),ms,false,false,Wr64SkyWaterMode::CachedSkyWithRTObjects),"Mixed sky/object PSO failed");
    require(skyOnlyPipelines.prepare(device.get(),layout.get(),ms,false,false,Wr64SkyWaterMode::RayTracedSkyOnly),"RT sky-only PSO failed");
    FixtureWaterPipelines fullSkyPipelines(RenderShaderFormat::DXIL);
    require(fullSkyPipelines.prepare(device.get(),layout.get(),ms,false,true),"Original full-RT sky reference PSO failed");
    Wr64RasterSkyTarget cachedSkies[2];
    const hlslpp::float4 skyColors[]={hlslpp::float4(.8f,.2f,.1f,1),hlslpp::float4(.1f,.7f,.9f,.5f)};
    for(uint32_t view=0;view<2;++view) {
        require(cachedSkies[view].ensure(&worker),"Independent sky capture allocation failed");
        rdp[2].primColor=skyColors[view];fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(reflectionBuffer,&reflection,sizeof(reflection));
        worker.commandList->begin();
        const RenderBufferBarrier skyReads[]={{positions.get(),RenderBufferAccess::READ},{faces.get(),RenderBufferAccess::READ}};
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,skyReads,2,nullptr,0);
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(cachedSkies[view].texture(),RenderTextureLayout::COLOR_WRITE));
        worker.commandList->setFramebuffer(cachedSkies[view].framebuffer());worker.commandList->clearColor(0,RenderColor(0,0,0,0));
        worker.commandList->setGraphicsPipelineLayout(layout.get());
        worker.commandList->setGraphicsDescriptorSet(common.get(),0);worker.commandList->setGraphicsDescriptorSet(textures.get(),1);
        worker.commandList->setGraphicsDescriptorSet(textures.get(),2);worker.commandList->setGraphicsDescriptorSet(framebufferSet.get(),3);
        worker.commandList->setPipeline(rasterPipelines.capture());
        worker.commandList->setViewports(RenderViewport(0,0,512,256));worker.commandList->setScissors(RenderRect(0,0,512,256));
        worker.commandList->drawInstanced(3,1,0,0);
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(cachedSkies[view].texture(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
    }
    require(cachedSkies[0].texture()!=cachedSkies[1].texture(),"Two views shared a sky capture texture");
    auto selectView=[&](uint32_t view) {
        reflection.camera[0]=2.f*view;reflection.camera[1]=2;reflection.strength=1;reflection.qualityOptions[2]=1;
        rdp[2].primColor=skyColors[view];fill(rdpParamsBuffer,rdp,sizeof(rdp));
        common.setTexture(common.wr64RasterSky,cachedSkies[view].texture(),RenderTextureLayout::SHADER_READ);
    };
    auto methodWater=[&](const RenderPipeline *method,uint32_t enabled=1) {
        pipelineOverride=method;return render(enabled,0);
    };
    Pixels viewBaseline[2];size_t hitPixels=0,missPixels=0,boostedPixels=0,visibleObjects=0,visibleSkies=0;int maximumMissError=0;
    for(uint32_t view=0;view<2;++view) {
        selectView(view);
        const auto nativeWater=methodWater(pipelines.get(false,false,false),0);
        const auto objectReference=methodWater(pipelines.get(false,false,false));
        const auto fullSkyReference=methodWater(fullSkyPipelines.get(false,false,false));
        const auto skyOnly=methodWater(skyOnlyPipelines.get(false,false,false));
        for(float strength:{0.f,1.f,1.5f,2.f}) {
            // Only the raster reference uses params.strength. Mixed mode keeps
            // object shading at the accepted value and boosts sky independently.
            reflection.strength=strength>0?strength:1;
            const auto cachedReference=methodWater(rasterPipelines.get(false,false,false));
            reflection.strength=1;reflection.qualityOptions[2]=strength;
            const auto mixed=methodWater(mixedPipelines.get(false,false,false));
            if(strength==0)viewBaseline[view]=mixed;
            if(strength==1)require(mixed==viewBaseline[view],"Zero/default mixed sky strength differs from explicit 1.0");
            for(uint32_t y=4;y<Height-4;++y)for(uint32_t x=4;x<Width-4;++x) {
                const double px=-5+(x+.5)*10/Width,pz=5-(y+.5)*10/Height;
                const double distanceRatio=(6-pz)/(pz+10);
                const double hitX=px+(px-2*view)*distanceRatio,hitY=.5+2*distanceRatio;
                // Independent planar intersection with generous triangle/edge
                // margins; avoid classifying a partially covered MSAA boundary.
                const bool hit=hitX<-.75 && hitX>-39 && hitY>-9 && hitY<59+1.75*hitX;
                const bool miss=hitX>.75;
                if(!hit&&!miss)continue;
                const size_t p=(y*Width+x)*4;bool stronger=false,visible=false;
                for(uint32_t c=0;c<4;++c) {
                    if(hit) {
                        require(mixed[p+c]==objectReference[p+c],"Mixed raster sky changed or obscured an RT object hit");
                        require(skyOnly[p+c]==nativeWater[p+c],"RT sky-only colored an object hit instead of retaining native water");
                        if(c<3)visible|=std::abs(int(objectReference[p+c])-int(nativeWater[p+c]))>=3;
                    }
                    else {
                        const int error=std::abs(int(mixed[p+c])-int(cachedReference[p+c]));maximumMissError=std::max(maximumMissError,error);
                        require(error<=2,"Mixed RT miss disagrees with the independently rendered cached sky");
                        require(skyOnly[p+c]==fullSkyReference[p+c],"RT sky-only miss differs from the original native-sky reflection");
                        if(c<3)visible|=std::abs(int(skyOnly[p+c])-int(nativeWater[p+c]))>=3;
                        if(c<3 && strength>1)stronger|=std::abs(int(mixed[p+c])-int(viewBaseline[view][p+c]))>=2;
                    }
                }
                require(mixed[p+3]==nativeWater[p+3],"Independent sky method changed native water coverage");
                if(hit)++hitPixels;else ++missPixels;if(stronger)++boostedPixels;
                if(strength==1 && visible){if(hit)++visibleObjects;else ++visibleSkies;}
            }
            require(methodWater(mixedPipelines.get(false,false,false),0)==nativeWater,"Disabling mixed reflection failed to restore native water");
            require(methodWater(mixedPipelines.get(false,false,false))==mixed,"Repeated mixed pass changed its pixels");
        }
        writePPM(outputPrefix+"-"+std::to_string(samples)+"x-view"+std::to_string(view)+".ppm",viewBaseline[view]);
    }
    require(hitPixels>1000 && missPixels>1000 && boostedPixels>100 && visibleObjects>100 && visibleSkies>100,
        "Sky-method fixture lacks visible hit/miss/strength coverage");
    // Alternate the two independently captured textures and camera uniforms.
    // Every pass must restore the corresponding exact snapshot after the other.
    for(uint32_t view:{0u,1u,0u,1u}) {
        selectView(view);
        require(methodWater(mixedPipelines.get(false,false,false))==viewBaseline[view],"Sky cache/camera leaked across views");
    }
    require(viewBaseline[0]!=viewBaseline[1],"Independent sky views were accidentally identical");
    #include "raster_shadow_combinations_fixture.inl"
    pipelineOverride=nullptr;reflection.strength=1;reflection.qualityOptions[2]=0;
    std::printf("Sky methods %ux: %zu exact object-hit pixels, %zu sky-miss pixels, %zu boosted misses; %zu visible objects/%zu visible sky pixels; max cached color error %d bytes; two independent caches/views restored exactly.\n",
        samples,hitPixels,missPixels,boostedPixels,visibleObjects,visibleSkies,maximumMissError);
}
