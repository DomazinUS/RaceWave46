// Exact jc7_jumpdai striped quad (source38..41) and top triangle46..48.
// The source arrays match the current US ROM (native audit). SetCrsObj adds
// 180 to course heading45, so the stationary object's actual yaw is225.
{
    FixtureWorldPipelines rampPipelines(shaderFormat);
    require(rampPipelines.prepare(device.get(),layout.get(),ms,false),"Ramp world PSO preparation failed");
    pipelineOverride=rampPipelines.get(false,false,false,false,true,true);
    require(pipelineOverride!=nullptr,"Ramp world PSO is absent");
    const float nativeRamp[7][3]={{0,-50,265},{0,-75,265},{150,-75,115},{150,-50,115},
        {-150,-50,115},{0,-50,265},{150,-50,115}};
    const uint32_t rampFaces[15]={0,1,2,0,2,3,4,5,6,7,8,9,7,9,10};std::memcpy(indices,rampFaces,sizeof(rampFaces));
    const float corners[4][4]={{0,0,.5f,1},{float(Width),0,.5f,1},{float(Width),float(Height),.5f,1},{0,float(Height),.5f,1}};
    std::memcpy(screen,corners,sizeof(corners));
    for(uint32_t q=0;q<3;++q) {
        params[q]=params[1];params[q].omL=0;params[q].omH=0x00082cff;params[q].flags.sampleCount=samples==1?0:2;
        renderIndices[q]={};renderIndices[q].instanceIndex=q;renderIndices[q].faceIndicesStart=q==0?0:q==1?6:9;
        rdp[q].primColor=hlslpp::float4(.75f,.4f,.2f,1);
    }
    for(uint32_t v=0;v<7;++v){colors[v][0]=colors[v][1]=colors[v][2]=1;colors[v][3]=0;uv[v][0]=uv[v][1]=0;}
    fill(screenBuffer,screen,sizeof(screen));fill(colorBuffer,colors,sizeof(colors));fill(uvBuffer,uv,sizeof(uv));
    fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
    fill(indexUpload,indices,sizeof(indices));
    worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::COPY,RenderBufferBarrier(faces.get(),RenderBufferAccess::WRITE));
    worker.commandList->copyBufferRegion(faces->at(0),indexUpload->at(0),sizeof(indices));worker.commandList->end();worker.execute();worker.wait();
    reflection=Params{};reflection.shadowOptions[0]=1;reflection.shadowOptions[1]=.5f;reflection.shadowOptions[2]=30000;
    reflection.shadowLight[1]=reflection.shadowLight[2]=1;reflection.shadowLight[3]=.55f;
    reflection.sceneOptions[1]=1;clearDestination=RenderColor(0,0,0,0);
    auto prepareRamp=[&](bool cap,bool external=false) {
        std::vector<Wr64RTSceneGeometry> geometry={{0,6,0,1}};if(cap)geometry.push_back({6,3,1,1});if(external)geometry.push_back({9,6,2,1});
        require(scene.prepare(device.get(),positions.get(),faces.get(),16,54,geometry),"Ramp AS prepare failed");
        common.setAccelerationStructure(common.SceneBVH,scene.accelerationStructure());
        common.setBuffer(common.interleavedRasters,scene.geometryBuffer(),scene.geometryBufferSize(),RenderBufferStructuredView(16));
        common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());rebuildPositions();
    };
    for(double heading:{45.0,225.0})for(float translated:{0.f,32768.f}) {
    const double yaw=heading*3.14159265358979323846/180;
    const double cs=std::cos(yaw),sn=std::sin(yaw);
    float baseRamp[7][4];
    for(uint32_t v=0;v<7;++v) {
        baseRamp[v][0]=float(cs*nativeRamp[v][0]+sn*nativeRamp[v][2]-641+translated);
        baseRamp[v][1]=nativeRamp[v][1]+translated;baseRamp[v][2]=float(-sn*nativeRamp[v][0]+cs*nativeRamp[v][2]+3733+translated);baseRamp[v][3]=1;
    }
    std::vector<Pixels> masks,colorsByPose;std::vector<int> poseValues;
    size_t minimumDark=Width*Height,maximumDark=0;double maximumDot=0;
    for(int ulps:{-4,-2,-1,0,1,2,4}) {
        std::memcpy(world,baseRamp,sizeof(baseRamp));
        // A row-transform perturbation bounded to single float ULPs; the
        // duplicate cap vertex moves with the lip so its volume stays closed.
        for(uint32_t v=0;v<7;++v)if(nativeRamp[v][0]!=0)for(int step=0;step<std::abs(ulps);++step) {
            const bool positive=(ulps>0)==(nativeRamp[v][0]>0);
            world[v][0]=std::nextafter(world[v][0],positive?std::numeric_limits<float>::infinity():-std::numeric_limits<float>::infinity());
        }
        const double ax=world[1][0]-world[0][0],ay=world[1][1]-world[0][1],az=world[1][2]-world[0][2];
        const double bx=world[2][0]-world[0][0],by=world[2][1]-world[0][1],bz=world[2][2]-world[0][2];
        const double nx=ay*bz-az*by,ny=az*bx-ax*bz,nz=ax*by-ay*bx;
        const double dot=(ny+nz)/std::sqrt(nx*nx+ny*ny+nz*nz)/std::sqrt(2.0);
        maximumDot=std::max(maximumDot,std::abs(dot));
        prepareRamp(false);const auto bare=render(1,5);size_t bareDark=0;
        for(size_t p=0;p<bare.size();p+=4)bareDark+=bare[p]<128;
        require(bareDark==0,"Isolated native ramp skirt self-shadowed without its cap");
        prepareRamp(true);const auto mask=render(1,5),color=render(1,0),native=render(0,0);
        require(render(1,5)==mask,"Identical ramp pose changed between GPU submissions");
        size_t dark=0;for(size_t p=0;p<mask.size();p+=4)dark+=mask[p]<128;
        minimumDark=std::min(minimumDark,dark);maximumDark=std::max(maximumDark,dark);
        const double delta=world[2][0]-baseRamp[2][0];
        std::printf("Ramp %ux heading%.0f translation%.0f ulps%+d deltaX%.9f normalizedNdotL%+.12g bare%zu capdark%zu centerRGB%u/%u.\n",
            samples,heading,translated,ulps,delta,dot,bareDark,dark,unsigned(center(color)[0]),unsigned(center(native)[0]));
        masks.push_back(mask);colorsByPose.push_back(color);poseValues.push_back(ulps);
        if(ulps>=-1&&ulps<=1)writePPM(outputPrefix+"-heading"+std::to_string(int(heading))+"-offset"+std::to_string(int(translated))+"-ramp-"+std::to_string(samples)+"x-ulp"+std::to_string(ulps)+".ppm",color);
    }
    size_t oneUlpChanged=0;for(size_t p=0;p<masks[2].size();p+=4)oneUlpChanged+=masks[2][p]!=masks[4][p];
    std::printf("Ramp %ux heading%.0f translation%.0f summary: min-dark%zu max-dark%zu one-ULP-side-change%zu maximum-abs-normalized-dot%.12g.\n",
        samples,heading,translated,minimumDark,maximumDark,oneUlpChanged,maximumDot);
    if(selected("--ramp-repro-baseline"))require(minimumDark<100&&maximumDark>3000&&oneUlpChanged>3000,
        "Accepted shader did not reproduce the native ramp's whole-face one-ULP flash");
    else {
        require(oneUlpChanged==0&&maximumDark==0,"Native ramp shadow still flips across bounded float pose noise");
        for(const auto& mask:masks)require(mask==masks[3],"Ramp tangent tie changed within its finite precision neighborhood");
    }
    // Preserve a genuinely neighboring caster just .4-.6 units outside the
    // face. Keeping the native winding must not disable tangent shadow rays.
    std::memcpy(world,baseRamp,sizeof(baseRamp));
    const float outward=heading==45?1.f:-1.f,faceX=baseRamp[0][0];
    const float zlo=std::min(baseRamp[0][2],baseRamp[2][2])-1000;
    const float zhi=std::max(baseRamp[0][2],baseRamp[2][2])+1000;
    const float ext[4][4]={{faceX+outward*.4f,-49+translated,zlo,1},{faceX+outward*.6f,-49+translated,zlo,1},
        {faceX+outward*.6f,-49+translated,zhi,1},{faceX+outward*.4f,-49+translated,zhi,1}};
    std::memcpy(world+7,ext,sizeof(ext));prepareRamp(false,true);
    const auto externalMask=render(1,5);size_t externalDark=0;
    for(size_t p=0;p<externalMask.size();p+=4)externalDark+=externalMask[p]<128;
    require(externalDark>3500,"Stable tangent bias erased a distinct nearby physical caster");
    // A clearly backlit orientation is outside the rounding-sized tie and
    // must still flip toward the light, allowing its cap to shade the lip.
    const double backlitHeading=heading+(heading==45?5:-5),backlitYaw=backlitHeading*3.14159265358979323846/180;
    const double bc=std::cos(backlitYaw),bs=std::sin(backlitYaw);
    for(uint32_t v=0;v<7;++v) {
        world[v][0]=float(bc*nativeRamp[v][0]+bs*nativeRamp[v][2]-641+translated);
        world[v][1]=nativeRamp[v][1]+translated;
        world[v][2]=float(-bs*nativeRamp[v][0]+bc*nativeRamp[v][2]+3733+translated);world[v][3]=1;
    }
    prepareRamp(true);const auto backlitMask=render(1,5);size_t backlitDark=0;
    for(size_t p=0;p<backlitMask.size();p+=4)backlitDark+=backlitMask[p]<128;
    require(backlitDark>3000,"Tangent stability correction suppressed a clearly backlit native ramp face");
    std::printf("Ramp %ux heading%.0f translation%.0f controls: external-close%zu backlit%zu.\n",samples,heading,translated,externalDark,backlitDark);
    }
    pipelineOverride=nullptr;
}
