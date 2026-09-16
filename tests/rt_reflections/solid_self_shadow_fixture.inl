// Bounded, independently invocable exercise of the shipped solid shadow PSO.
// CPU receiver admission is tested separately against native material records.
{
    FixtureWorldPipelines solidPipelines(shaderFormat);
    require(solidPipelines.prepare(device.get(),layout.get(),ms,false),"Solid receiver pipeline preparation failed");
    pipelineOverride=solidPipelines.get(false,false,false,false,true,true);
    require(pipelineOverride!=nullptr,"Solid receiver pipeline is unavailable");
    const auto primitive=params[1];
    const float normals[4][3]={{0,1,0},{1,0,0},{0,0,1},{.6f,.8f,0}};
    double axisU[3]={},axisV[3]={},axisN[3]={};
    auto makeQuad=[&](uint32_t start,double left,double right,double low,double high,double height,bool reverse=false) {
        const double points[4][2]={{left,high},{right,high},{right,low},{left,low}};
        for(uint32_t v=0;v<4;++v) {
            for(uint32_t c=0;c<3;++c)world[start+v][c]=float(points[v][0]*axisU[c]+points[v][1]*axisV[c]+height*axisN[c]);
            world[start+v][3]=1;
            uv[start+v][0]=4.5f;uv[start+v][1]=.5f;
            colors[start+v][0]=.7f;colors[start+v][1]=.45f;colors[start+v][2]=.2f;
            colors[start+v][3]=0;
        }
        const uint32_t facesForQuad[6]={start,start+1,start+2,start,start+2,start+3};
        const uint32_t reversed[6]={start,start+2,start+1,start,start+3,start+2};
        std::memcpy(indices+(start/4)*6,reverse?reversed:facesForQuad,sizeof(facesForQuad));
    };
    auto bindScene=[&](std::vector<Wr64RTSceneGeometry> geometry) {
        fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
        fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
        fill(indexUpload,indices,sizeof(indices));
        worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::COPY,RenderBufferBarrier(faces.get(),RenderBufferAccess::WRITE));
        worker.commandList->copyBufferRegion(faces->at(0),indexUpload->at(0),sizeof(indices));worker.commandList->end();worker.execute();worker.wait();
        require(scene.prepare(device.get(),positions.get(),faces.get(),16,54,geometry),"Solid fixture AS prepare failed");
        common.setAccelerationStructure(common.SceneBVH,scene.accelerationStructure());
        common.setBuffer(common.interleavedRasters,scene.geometryBuffer(),scene.geometryBufferSize(),RenderBufferStructuredView(16));
        common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
        rebuildPositions();
    };
    auto maskWhite=[&](const Pixels& image) {
        for(size_t p=0;p<image.size();p+=4)if(image[p]!=255||image[p+1]!=255||image[p+2]!=255)return false;
        return true;
    };
    auto analyticCoverage=[&](uint32_t x,uint32_t y,bool actor,uint32_t rays) {
        const double px=(x+.5)*16/Width-8,py=8-(y+.5)*16/Height;
        if(!actor)return double(px>=-2.7&&px<=2.3&&py>=-2.1&&py<=2.8);
        uint32_t hits=0;
        for(uint32_t pair=0;pair<rays/2;++pair)for(double sign:{-1.0,1.0}) {
            const double radius=2.5*std::sqrt((pair+.5)/(rays/2)),a=pair*3.14159265358979323846*(3-std::sqrt(5.0));
            const double hx=px+sign*radius*std::cos(a),hy=py+sign*radius*std::sin(a);
            hits+=hx>=-2.7&&hx<=2.3&&hy>=-2.1&&hy<=2.8;
        }
        return hits/double(rays);
    };
    size_t cases=0,compared=0,softPixels=0,fullPixels=0,clearPixels=0,selfControlPixels=0;
    int maximumMaskError=0,maximumColorError=0;
    for(uint32_t material=0;material<3;++material)for(uint32_t orientation=0;orientation<4;++orientation) {
        for(uint32_t c=0;c<3;++c)axisN[c]=normals[orientation][c];
        const double length=std::sqrt(axisN[0]*axisN[0]+axisN[1]*axisN[1]+axisN[2]*axisN[2]);
        for(auto& n:axisN)n/=length;
        axisU[0]=axisN[1];axisU[1]=-axisN[0];axisU[2]=0;
        const double ul=std::sqrt(axisU[0]*axisU[0]+axisU[1]*axisU[1]);
        if(ul<1e-8){axisU[0]=1;axisU[1]=axisU[2]=0;}else for(auto& u:axisU)u/=ul;
        axisV[0]=axisN[1]*axisU[2]-axisN[2]*axisU[1];
        axisV[1]=axisN[2]*axisU[0]-axisN[0]*axisU[2];
        axisV[2]=axisN[0]*axisU[1]-axisN[1]*axisU[0];
        for(uint32_t q=0;q<4;++q) {
            params[q]=primitive;params[q].omL=0;params[q].omH=0x00082cff;
            params[q].flags.sampleCount=samples==1?0:2;
            renderIndices[q]={};renderIndices[q].instanceIndex=q;renderIndices[q].faceIndicesStart=q*6;
            rdp[q].primColor=hlslpp::float4(.7f,.6f,.4f,1);rdp[q].fogColor=hlslpp::float4(.12f,.35f,.8f,1);
            rdp[q].envColor=hlslpp::float4(.6f,.8f,1,.7f);rdp[q].blendColor=hlslpp::float4(0,0,0,.5f);
        }
        if(material<2) {
            params[0].flags.usesTexture0=1;params[0].flags.nativeSampler0=NATIVE_SAMPLER_CLAMP_CLAMP;
            params[0].flags.cms0=params[0].flags.cmt0=2;params[0].flags.linearFiltering=0;
            params[0].ccL=material?0xFC127FFFu:0xFC127E24u;
            params[0].ccH=material?0xFFFFF238u:0xFFFFF3F9u;
            params[0].omL=material?0xC8112078u:0x00552078u;
            params[0].omH=material?0x0018ACFFu:0x0008ACFFu;
            renderIndices[0].rdpTileCount=1;rdp[0].primColor=hlslpp::float4(1,1,1,0);
        }
        makeQuad(0,-8,8,-8,8,0);makeQuad(4,-2.7,2.3,-2.1,2.8,1.25);
        const float corners[4][4]={{0,0,.5f,1},{float(Width),0,.5f,1},{float(Width),float(Height),.5f,1},{0,float(Height),.5f,1}};
        std::memcpy(screen,corners,sizeof(corners));
        for(uint32_t v=0;v<4;++v)colors[v][3]=material==1?.4f:material==0?1.f:0.f;
        reflection=Params{};reflection.shadowOptions[0]=1;reflection.shadowOptions[1]=.5f;reflection.shadowOptions[2]=100;
        reflection.shadowLight[3]=.55f;for(uint32_t c=0;c<3;++c)reflection.shadowLight[c]=float(axisN[c]);
        reflection.sceneOptions[1]=1;reflection.sceneOptions[2]=1;
        bindScene({{0,6,0,17}});clearDestination=RenderColor(0,0,0,0);
        const auto native=render(0,0);
        require(maskWhite(render(1,5))&&render(1,0)==native,"An isolated native solid receiver shadows its own originating surface");
        for(bool sameDraw:{false,true})for(bool actorCaster:{false,true}) {
            const uint32_t flags=actorCaster?17u:1u;
            auto selectedGeometry=sameDraw?std::vector<Wr64RTSceneGeometry>{{0,12,0,flags}}:
                std::vector<Wr64RTSceneGeometry>{{0,6,0,17},{6,6,1,flags}};
            bindScene(selectedGeometry);
            const auto mask=render(1,5),color=render(1,0);
            require(render(1,5)==mask&&render(1,0)==color,"Solid receiver shadow jittered between identical submissions");
            reflection.camera[0]+=51;reflection.camera[1]-=17;reflection.camera[2]+=33;
            require(render(1,5)==mask,"Moving only the camera changed the world-anchored solid shadow kernel");
            reflection.camera[0]-=51;reflection.camera[1]+=17;reflection.camera[2]-=33;
            for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                const size_t p=(y*Width+x)*4;const double coverage=analyticCoverage(x,y,actorCaster,16),q=1-.55*coverage;
                const int me=int(std::ceil(std::abs(mask[p]-255*(1-coverage))));maximumMaskError=std::max(maximumMaskError,me);
                require(me<=1,"Solid self-shadow visibility disagreed with independent receiver-plane rays");
                for(uint32_t c=0;c<3;++c) {
                    const double fog=material==1?.4*(c==0?.12:c==1?.35:.8)*255:0;
                    const int ce=int(std::ceil(std::abs(color[p+c]-(q*native[p+c]+(1-q)*fog))));
                    maximumColorError=std::max(maximumColorError,ce);
                    require(ce<=2,"Solid self-shadow changed native fog or surface attenuation");
                }
                require(color[p+3]==native[p+3],"Solid self-shadow changed native alpha/coverage");
                softPixels+=coverage>0&&coverage<1;fullPixels+=coverage==1;clearPixels+=coverage==0;
                selfControlPixels+=sameDraw&&coverage>0;++compared;
            }
            reflection.shadowOptions[0]=0;require(render(1,0)==native,"Disabled directional shadow did not restore native rider/craft/scenery output");
            reflection.shadowOptions[0]=1;reflection.shadowLight[3]=0;require(render(1,0)==native,"Zero solid strength did not restore exact native output");
            reflection.shadowLight[3]=.55f;
            // The 1.25-unit gap is deliberately close to the accepted .5 origin
            // bias plus .5 minimum ray distance. Other faces still block.
            makeQuad(4,-2.7,2.3,-2.1,2.8,3);bindScene(selectedGeometry);
            require(render(1,5)==mask,"Changing the positive caster gap changed parallel solid rays");
            makeQuad(4,-2.7,2.3,-2.1,2.8,1.25);bindScene(selectedGeometry);
            if(material==2&&orientation==0&&actorCaster&&sameDraw)writePPM(outputPrefix+"-solid-self-"+std::to_string(samples)+"x.ppm",color);
            ++cases;
        }
        // A distinct cutout part is evaluated through its native alpha predicate,
        // while the receiving rider/craft's own opaque material stays unchanged.
        params[1].omL=Z_UPD|Z_CMP|G_AC_THRESHOLD;params[1].omH=G_TP_PERSP|G_TF_POINT;
        rdp[1].primColor=hlslpp::float4(.7f,.6f,.4f,0);bindScene({{0,6,0,17},{6,6,1,19}});
        require(maskWhite(render(1,5))&&render(1,0)==native,"Rejected native cutout cast a solid self-shadow");
        rdp[1].primColor=hlslpp::float4(.7f,.6f,.4f,1);bindScene({{0,6,0,17},{6,6,1,19}});
        const auto admitted=render(1,5);require(!maskWhite(admitted),"Admitted native cutout failed to cast onto a solid receiver");
        bindScene({{0,6,0,17},{6,6,1,18}});
        require(maskWhite(render(1,5))&&render(1,0)==native,"Native cutout/actor identity bypassed physical caster permission");
    }
    require(cases==48&&softPixels>500&&fullPixels>500&&clearPixels>500&&selfControlPixels>500,
        "Solid self-shadow controls failed to exercise native parts, soft edges and clear geometry");
    std::printf("Solid self %ux: cases%zu analytic pixels%zu soft%zu full%zu clear%zu same-draw-positive%zu mask-error%d color-error%d.\n",
        samples,cases,compared,softPixels,fullPixels,clearPixels,selfControlPixels,maximumMaskError,maximumColorError);
    pipelineOverride=nullptr;
}
