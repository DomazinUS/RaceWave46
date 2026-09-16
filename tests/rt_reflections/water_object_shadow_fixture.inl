// Included in the established actor fixture so both actor and scenery use
// the production water PSOs, descriptor layout, AS and alpha composition.
{
    const Params sceneryStart=reflection;
    float sceneryWorld[16][4];std::memcpy(sceneryWorld,world,sizeof(world));
    auto rectangleCoverage=[&](uint32_t x,uint32_t y,uint32_t rays) {
        const double px=(x+.5)*40/Width-20,pz=20-(y+.5)*40/Height;
        uint32_t hits=0;
        for(uint32_t pair=0;pair<rays/2;++pair)for(double sign:{-1.0,1.0}) {
            const double r=6*std::sqrt((pair+.5)/(rays/2));
            const double angle=pair*3.14159265358979323846*(3-std::sqrt(5.0));
            const double hx=px+4.5*.75+sign*r*std::cos(angle),hz=pz-sign*r*std::sin(angle);
            hits+=hx>=-2&&hx<=2&&hz>=-20&&hz<=20;
        }
        return hits/double(rays);
    };
    size_t sceneryComparisons=0,sceneryEdges=0,actorWins=0,sceneryWins=0,overlapControl=0,centerMissEdges=0;
    int sceneryMaskMax=0,sceneryColorMax=0;
    bool sceneryCorrect=true;
    for(uint32_t quality:{4u,8u,12u,16u}) {
        const uint32_t sceneryRays=quality<=8?4u:8u;
        reflection.qualityOptions[1]=float(quality);
        setNativeWaterAlpha(255);clearDestination=RenderColor(0,0,0,0);
        prepareSoft(0,true);
        const auto sceneMask=render(1,5),sceneColor=render(1,0);
        require(render(1,5)==sceneMask&&render(1,0)==sceneColor,"Stationary scenery surface shadows changed between frames");
        reflection.camera[0]+=13;reflection.camera[2]+=7;
        require(render(1,5)==sceneMask,"Camera movement rotated or jittered the scenery water kernel");
        reflection.camera[0]-=13;reflection.camera[2]-=7;
        prepareSoft(17,true);const auto combinedMask=render(1,5),combinedColor=render(1,0);
        for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
            const size_t p=(y*Width+x)*4;
            const double coverage=rectangleCoverage(x,y,sceneryRays),actor=actorCoverage(x,y,0,7.5,quality);
            const double sceneQ=1-.28*coverage,actorQ=1-.18*actor,q=std::min(sceneQ,actorQ);
            const double hx=(x+.5)*40/Width-20+4.5*.75;
            sceneryEdges+=coverage>0&&coverage<1;
            centerMissEdges+=coverage>0&&(hx<-2||hx>2);
            actorWins+=actorQ<sceneQ;sceneryWins+=sceneQ<actorQ;
            overlapControl+=std::abs(q-sceneQ*actorQ)>.02;
            const int maskError=int(std::ceil(std::max(std::abs(sceneMask[p]-255*(1-coverage)),
                std::abs(combinedMask[p]-255*(1-std::max(coverage,actor))))));
            sceneryMaskMax=std::max(sceneryMaskMax,maskError);sceneryCorrect &= maskError<=1;
            for(uint32_t c=0;c<3;++c) {
                const int e=int(std::ceil(std::max(std::abs(sceneColor[p+c]-sceneQ*softNativeWater[p+c]),
                    std::abs(combinedColor[p+c]-q*softNativeWater[p+c]))));
                sceneryColorMax=std::max(sceneryColorMax,e);sceneryCorrect &= e<=2;
            }
            sceneryCorrect &= sceneColor[p+3]==softNativeWater[p+3]&&combinedColor[p+3]==softNativeWater[p+3];
            ++sceneryComparisons;
        }
        // A reflective object lacking physical caster permission must neither
        // fill the edge nor change the actor's exact accepted mask.
        prepareBeamScene({{6,6,1,1},{12,6,2,17},{18,6,3,0}});
        const auto reflectionOnlyMask=render(1,5);
        prepareSoft();require(render(1,5)==reflectionOnlyMask,"Reflection-only scenery polluted the water-shadow layer");
    }
    require(sceneryCorrect&&sceneryEdges>1000&&centerMissEdges>1000&&actorWins>100&&sceneryWins>100&&overlapControl>500,
        "Scenery soft edges, physical permissions or bounded actor/scenery overlap disagreed with independent rays");
    reflection.qualityOptions[1]=0;prepareSoft(0,true);
    writePPM(prefix+"scenery-soft-mask.ppm",render(1,5));
    writePPM(prefix+"scenery-soft-water.ppm",render(1,0));
    const auto sceneStationary=render(1,5);
    for(uint32_t v=12;v<16;++v)world[v][0]+=200;
    rebuildPositions();require(shadowWhite(render(1,5)),"Scenery water shadow retained an earlier object's AS position");
    for(uint32_t v=12;v<16;++v)world[v][0]-=200;
    rebuildPositions();require(render(1,5)==sceneStationary,"Restoring scenery changed its deterministic water kernel");
    size_t alphaComparisons=0;
    for(uint8_t alpha:{uint8_t(0),uint8_t(64),uint8_t(179),uint8_t(255)})for(float strength:{0.f,.275f,.55f}) {
        setNativeWaterAlpha(alpha);clearDestination=RenderColor(.8f,.4f,.2f,1);
        reflection.shadowOptions[0]=0;const auto lit=render(1,0);
        reflection.shadowOptions[0]=1;reflection.shadowLight[3]=strength;const auto shaded=render(1,0);
        if(strength==0)require(shaded==lit,"Zero scenery strength changed exact native water transmission");
        for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
            const size_t p=(y*Width+x)*4;const double q=1-.28*(strength/.55)*rectangleCoverage(x,y,8);
            for(uint32_t c=0;c<3;++c)require(std::abs(shaded[p+c]-q*lit[p+c])<=2,
                "Scenery water strength/alpha failed independent native-transmission composition");
            require(shaded[p+3]==lit[p+3],"Scenery water changed native framebuffer coverage");++alphaComparisons;
        }
    }
    // The settled rider overlay remains exact even when a remote scenery
    // caster is present. Return original positions and actor settings.
    reflection=sceneryStart;std::memcpy(world,sceneryWorld,sizeof(world));
    softQuad(12,198,202,5,-20,20);prepareSoft(17,true);setNativeWaterAlpha(255);clearDestination=RenderColor(0,0,0,0);
    require(render(1,5)==softSurfaceMask&&render(1,0)==softWater,
        "A remote scenery caster changed the exact accepted actor-only water result");
    std::memcpy(world,sceneryWorld,sizeof(world));prepareSoft();reflection=sceneryStart;
    std::printf("%ux scenery water: analytic%zu edges%zu center-miss%zu actor-wins%zu scenery-wins%zu overlap-control%zu alpha%zu mask-error%d color-error%d.\n",
        samples,sceneryComparisons,sceneryEdges,centerMissEdges,actorWins,sceneryWins,overlapControl,alphaComparisons,sceneryMaskMax,sceneryColorMax);
}
