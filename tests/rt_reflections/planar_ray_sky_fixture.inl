// Included only by --planar-ray-sky-only after the common RT fixture setup.
// Real AS visibility + native sky lookup are compared with accepted shaders;
// controlled planar coverage isolates composition from the separately tested
// mirrored capture geometry and camera math.
{
    const float object[3][4]={{-40,-10,6,1},{0,-10,6,1},{0,60,6,1}};
    const float skyCard[4][4]={{-80,-80,30,1},{80,-80,30,1},{80,80,30,1},{-80,80,30,1}};
    std::memcpy(world+4,object,sizeof(object));std::memcpy(world+7,skyCard,sizeof(skyCard));
    const uint32_t skyFaces[6]={7,8,9,7,9,10};std::memcpy(indices+9,skyFaces,sizeof(skyFaces));
    for(auto &vertex:colors)for(float &channel:vertex)channel=1;
    fill(colorBuffer,colors,sizeof(colors));renderIndices[2]={2,9,0,0,0};
    params[0].ccL=0xFCFFFFFF;params[0].ccH=0xFFFCF279;
    params[0].omL=0x005049D8;params[0].omH=0x00082CFF;
    params[0].flags.usesTexture0=1;params[0].flags.nativeSampler0=NATIVE_SAMPLER_CLAMP_CLAMP;
    params[0].flags.cms0=params[0].flags.cmt0=2;params[0].flags.sampleCount=samples==1?0:2;
    params[2]=params[1];params[2].omL=0x00504240;params[2].omH=0x00882C3F;
    rdp[0].primColor=hlslpp::float4(1,1,1,1);
    rdp[1].primColor=hlslpp::float4(.1f,.9f,.2f,1);
    rdp[2].primColor=hlslpp::float4(.8f,.2f,.1f,1);
    fill(renderParamsBuffer,params,sizeof(params));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
    fill(rdpParamsBuffer,rdp,sizeof(rdp));
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
    require(scene.recordBuild(&worker),"Planar/RT-sky fixture scene rebuild failed");
    worker.commandList->end();worker.execute();worker.wait();
    reflection=Params{};reflection.enabled=1;reflection.camera[1]=2;reflection.sky[3]=0;
    reflection.skyBackdrop[0]=9;reflection.skyBackdrop[1]=2;reflection.skyBackdrop[2]=2;reflection.skyBackdrop[3]=1;
    clearDestination=RenderColor(.8f,.4f,.2f,1);

    Wr64RasterReflectionParams planar{};
    planar.reflectedRows[0][0]=.1f;planar.reflectedRows[1][2]=.1f;
    planar.reflectedRows[2][3]=.5f;planar.reflectedRows[3][3]=1;
    planar.plane[1]=1;planar.options[0]=1;planar.options[1]=1;
    auto *planarBuffer=upload(&planar,sizeof(planar),RenderBufferFlag::CONSTANT);
    common.setBuffer(common.wr64RasterReflectionParams,planarBuffer,sizeof(planar));
    Wr64RasterReflectionTarget planarTarget;
    require(planarTarget.ensure(&worker,128,128),"Planar/RT-sky capture target allocation failed");
    common.setTexture(common.wr64RasterReflectionColor,planarTarget.color(),RenderTextureLayout::SHADER_READ);
    auto coverage=[&](float alpha) {
        worker.commandList->begin();
        const RenderTextureBarrier targets[]={{planarTarget.color(),RenderTextureLayout::COLOR_WRITE},
            {planarTarget.depth(),RenderTextureLayout::DEPTH_WRITE}};
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,targets,2);
        worker.commandList->setFramebuffer(planarTarget.framebuffer());
        worker.commandList->clearColor(0,RenderColor(.1f*alpha,.9f*alpha,.2f*alpha,alpha));
        worker.commandList->clearDepth(true,1);worker.commandList->setFramebuffer(nullptr);
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,
            RenderTextureBarrier(planarTarget.color(),RenderTextureLayout::SHADER_READ));
        worker.commandList->end();worker.execute();worker.wait();
    };
    Wr64RasterShadowParams mapped{};
    mapped.lightRows[0][0]=.1f;mapped.lightRows[1][2]=.1f;mapped.lightRows[2][1]=-.01f;
    mapped.lightRows[2][3]=.5f;mapped.lightRows[3][3]=1;
    mapped.options[0]=1.f/1024;mapped.options[1]=.001f;mapped.options[2]=.18f;
    mapped.light[1]=1;mapped.light[3]=1;
    auto *mapBuffer=upload(&mapped,sizeof(mapped),RenderBufferFlag::CONSTANT);
    common.setBuffer(common.wr64RasterShadowParams,mapBuffer,sizeof(mapped));
    Wr64RasterShadowTarget mapTarget;require(mapTarget.ensure(&worker),"Planar/RT-sky shadow map allocation failed");
    common.setTexture(common.wr64RasterShadowMap,mapTarget.color(),RenderTextureLayout::SHADER_READ);
    worker.commandList->begin();
    const RenderTextureBarrier mapTargets[]={{mapTarget.color(),RenderTextureLayout::COLOR_WRITE},{mapTarget.depth(),RenderTextureLayout::DEPTH_WRITE}};
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,nullptr,0,mapTargets,2);
    worker.commandList->setFramebuffer(mapTarget.framebuffer());worker.commandList->clearColor(0,RenderColor(0,0,0,0));
    worker.commandList->clearDepth(true,1);worker.commandList->setFramebuffer(nullptr);
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,RenderTextureBarrier(mapTarget.color(),RenderTextureLayout::SHADER_READ));
    worker.commandList->end();worker.execute();worker.wait();

    Wr64RasterReflectionPipelines planarPipelines[2][2];
    const RenderPipeline *methods[2][2]{};
    for(uint32_t shadow=0;shadow<2;++shadow)for(uint32_t sky=0;sky<2;++sky) {
        auto &p=planarPipelines[shadow][sky];
        require(p.prepare(device.get(),layout.get(),ms,false,true,
            sky?Wr64RasterReflectionSkyMode::RTSkyOnly:Wr64RasterReflectionSkyMode::SkyOff,shadow!=0),
            "Planar/RT-sky pipeline setup failed");
        methods[shadow][sky]=awaitAsyncPipeline("planar-ray-sky",[&](){return p.get(false,false,false);});
    }
    Wr64RasterSkyPipelines acceptedSky;
    require(acceptedSky.prepare(device.get(),layout.get(),ms,false,true,Wr64SkyWaterMode::RayTracedSkyOnly),"Accepted ray-sky setup failed");
    const auto *acceptedSkyPS=awaitAsyncPipeline("accepted-ray-sky",[&](){return acceptedSky.get(false,false,false);});
    Wr64RasterShadowPipelines acceptedMappedSky,acceptedMappedNative;
    require(acceptedMappedSky.prepare(device.get(),layout.get(),ms,false,true,Wr64RasterShadowWaterMode::RTSkyOnly),"Accepted mapped sky setup failed");
    const auto *acceptedMappedSkyPS=awaitAsyncPipeline("accepted-mapped-sky",[&](){return acceptedMappedSky.getWater(Wr64RasterShadowWaterMode::RTSkyOnly,false,false,false);});
    require(acceptedMappedNative.prepare(device.get(),layout.get(),ms,false,true),"Accepted mapped native setup failed");
    const auto *acceptedMappedNativePS=awaitAsyncPipeline("accepted-mapped-native",[&](){return acceptedMappedNative.nativeWater(false,false,false);});
    auto draw=[&](const RenderPipeline *p,uint32_t enabled=1){pipelineOverride=p;return render(enabled,0);};
    size_t occluded=0,visibleSky=0,visibleObjects=0,partitioned=0,shadowedPixels=0;
    Pixels unshadowed[3];
    for(uint32_t shadow=0;shadow<2;++shadow) {
        const auto native=shadow?draw(acceptedMappedNativePS):draw(pipelines.get(false,false,false),0);
        const auto skyReference=draw(shadow?acceptedMappedSkyPS:acceptedSkyPS);
        coverage(0);const auto empty=draw(methods[shadow][1]);
        require(draw(methods[shadow][0])==native,"Empty planar capture changed native water/shadow fallback");
        coverage(1);const auto opaque=draw(methods[shadow][1]);
        require(opaque==draw(methods[shadow][0]),"Opaque planar object double-composed an RT sky layer");
        coverage(.5f);const auto partial=draw(methods[shadow][1]);
        require(draw(methods[shadow][1])==partial,"Repeated planar/RT-sky pass changed pixels");
        for(uint32_t y=4;y<Height-4;++y)for(uint32_t x=4;x<Width-4;++x) {
            const size_t p=(y*Width+x)*4;
            const double px=-5+(x+.5)*10/Width,pz=5-(y+.5)*10/Height;
            const double ratio=(6-pz)/(pz+10),hitX=px*(1+ratio),hitY=.5+2*ratio;
            const bool hit=hitX<-.75&&hitX>-39&&hitY>-9&&hitY<59+1.75*hitX;
            const bool miss=hitX>.75;
            bool skyChanged=false,objectChanged=false,gotDarker=false;
            for(uint32_t c=0;c<4;++c) {
                require(std::abs(int(empty[p+c])-int(skyReference[p+c]))<=1,"Empty planar capture disagrees with accepted RT sky visibility");
                if(hit)require(std::abs(int(empty[p+c])-int(native[p+c]))<=1,"AS object failed to occlude sky behind empty planar coverage");
                if(c<3) {
                    require(std::abs(2*int(partial[p+c])-int(empty[p+c])-int(opaque[p+c]))<=3,
                        "Half-covered planar reflection does not partition object and sky radiance");
                    skyChanged|=std::abs(int(empty[p+c])-int(native[p+c]))>=3;
                    objectChanged|=std::abs(int(opaque[p+c])-int(native[p+c]))>=3;
                    if(shadow) {
                        require(int(opaque[p+c])<=int(unshadowed[1][p+c])+1,"Mapped shadow brightened a planar object reflection");
                        gotDarker|=int(unshadowed[1][p+c])-int(opaque[p+c])>=2;
                    }
                }
            }
            require(empty[p+3]==native[p+3]&&opaque[p+3]==native[p+3]&&partial[p+3]==native[p+3],
                "Planar/RT-sky composition changed native coverage");
            if(hit)++occluded;if(miss&&skyChanged)++visibleSky;if(objectChanged)++visibleObjects;
            ++partitioned;if(gotDarker)++shadowedPixels;
        }
        if(!shadow){unshadowed[0]=empty;unshadowed[1]=opaque;unshadowed[2]=partial;}
        else {
            mapped.light[3]=0;fill(mapBuffer,&mapped,sizeof(mapped));
            require(draw(methods[1][1])==unshadowed[2],"Disabled map failed exact planar/RT-sky restoration");
        }
        writePPM(outputPrefix+"-"+std::to_string(samples)+"x-planar-ray-sky-shadow"+std::to_string(shadow)+".ppm",partial);
    }
    require(occluded>500&&visibleSky>100&&visibleObjects>500&&partitioned>1000&&shadowedPixels>500,
        "Planar/RT-sky fixture lacks substantial visibility/composition/shadow coverage");
    pipelineOverride=nullptr;
    std::printf("Planar + RT sky %ux: %zu AS-occluded sky pixels, %zu visible sky pixels, %zu object pixels, %zu coverage partitions, %zu mapped shadows.\n",
        samples,occluded,visibleSky,visibleObjects,partitioned,shadowedPixels);
}
