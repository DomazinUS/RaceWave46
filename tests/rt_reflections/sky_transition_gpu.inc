// Included inside the archived-cloud material fixture. All modified inputs are
// restored before continuing the established raster/sky/shadow/AO suite.
{
    float transitionSavedWorld[16][4], transitionSavedScreen[16][4];
    float transitionSavedUV[16][2], transitionSavedColors[16][4];
    uint32_t transitionSavedIndices[54];
    std::memcpy(transitionSavedWorld, world, sizeof(world));
    std::memcpy(transitionSavedScreen, screen, sizeof(screen));
    std::memcpy(transitionSavedUV, uv, sizeof(uv));
    std::memcpy(transitionSavedColors, colors, sizeof(colors));
    std::memcpy(transitionSavedIndices, indices, sizeof(indices));
    const auto transitionSavedReflection = reflection;
    const auto transitionSavedTexture = skyTexels;
    const auto transitionSavedParams = params[2];
    const auto transitionSavedTile = rdpTile;
    const auto transitionSavedGPU = gpuTile;
    const auto transitionSavedRdp = rdp[2];
    reflection.skyBackdrop[3] = 0;
    reflection.celestialInfo[0] = 0;
    reflection.skyCloudParams[2] = 1;
    reflection.sky[0] = 9; reflection.sky[1] = 2;
    reflection.sky[2] = 6; reflection.sky[3] = 1;
    rdp[2].primColor = hlslpp::float4(.05f, .9f, .1f, 1);
    fill(rdpParamsBuffer, rdp, sizeof(rdp));
    // Native clamped/fog-free cloud combiner, with a synthetic wrapping image.
    // Keep 3-point filtering explicit rather than inheriting a prior fixture's
    // hardware bilinear shortcut.
    params[2].flags.linearFiltering = 0;
    fill(renderParamsBuffer, params, sizeof(params));
    size_t transitionExterior = 0, transitionMissing = 0, transitionCompared = 0;
    int transitionMaxError = 0;
    const float weights[] = {0, .25f, .5f, .75f, 1};
    constexpr float cameraHeight = 40, planeHeight = 400, patchRadius = 700;
    constexpr float cloudScale = (planeHeight - cameraHeight) / cameraHeight;
    auto putWaterLookupPatch = [&](float centerX, float centerZ, float ux, float uz,
        float vx, float vz, float radius) {
        const float signs[4][2] = {{-1,-1},{1,-1},{1,1},{-1,1}};
        for (uint32_t v = 0; v < 4; ++v) {
            const float qx = centerX + radius * (signs[v][0]*ux + signs[v][1]*vx);
            const float qz = centerZ + radius * (signs[v][0]*uz + signs[v][1]*vz);
            world[v][0] = reflection.skyCamera[0] + (qx-reflection.skyCamera[0])/cloudScale;
            world[v][1] = 0;
            world[v][2] = reflection.skyCamera[2] + (qz-reflection.skyCamera[2])/cloudScale;
            world[v][3] = 1;
        }
    };
    auto nativeCloudAlpha = [&](uint32_t x, uint32_t y) {
        const double qx = (2.0 * (x+.5) / Width - 1) * patchRadius * cloudScale;
        const double qz = (2.0 * (y+.5) / Height - 1) * patchRadius * cloudScale;
        return std::clamp((450.0 - .055 * std::hypot(qx,qz)) / 255.0, 0.0, 1.0);
    };
    for (const auto &transition : NativeSkyTransitionFixture::Frames) {
        float maximumPositionDelta = 0, maximumUVDelta = 0;
        for (uint32_t v=0;v<7;++v) {
            float dp=0,du=0;
            for(uint32_t c=0;c<3;++c) { const float d=transition.currentPositions[v][c]-transition.previousPositions[v][c];dp+=d*d; }
            for(uint32_t c=0;c<2;++c) { const float d=transition.currentTexcoords[v][c]-transition.previousTexcoords[v][c];du+=d*d; }
            maximumPositionDelta=std::max(maximumPositionDelta,std::sqrt(dp));
            maximumUVDelta=std::max(maximumUVDelta,std::sqrt(du));
        }
        require(maximumPositionDelta>1000 || maximumUVDelta>20,
            "Recorded transition no longer exercises production smart-UV hold");
        for (float weight : weights) {
            for (uint32_t v=0;v<7;++v) {
                for(uint32_t c=0;c<3;++c)
                    world[7+v][c]=transition.previousPositions[v][c]*(1-weight)+transition.currentPositions[v][c]*weight;
                world[7+v][3]=1;
                // Exactly the shipping smart-UV behavior: tcVel becomes zero,
                // while position velocity remains unchanged.
                std::memcpy(uv[7+v],transition.currentTexcoords[v],sizeof(uv[0]));
                for(uint32_t c=0;c<4;++c)colors[7+v][c]=1;
            }
            reflection.camera[0]=reflection.skyCamera[0]=world[7][0];
            reflection.camera[1]=reflection.skyCamera[1]=cameraHeight;
            reflection.camera[2]=reflection.skyCamera[2]=world[7][2];
            putWaterLookupPatch(world[7][0],world[7][2],1,0,0,1,patchRadius*cloudScale);
            for(auto &b:skyTexels)b=255;
            setSkyTextureAlpha(255);
            fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            refreshFixtureIndices();bindWaterAdjacency();
            const auto transitionNative=render(0,0);
            reflection.skyCloudParams[2]=0;
            const auto finiteTransition=render(1,4);
            reflection.skyCloudParams[2]=1;
            const auto extendedTransition=render(1,4);
            size_t exterior=0,missing=0;int maximumError=0;
            for(uint32_t y=4;y<Height-4;++y)for(uint32_t x=4;x<Width-4;++x) {
                const size_t p=(y*Width+x)*4;
                const double a=nativeCloudAlpha(x,y);
                const double expectedGreen=255*.9*a;
                const int error=int(std::ceil(std::abs(double(extendedTransition[p+1])-expectedGreen)));
                maximumError=std::max(maximumError,error);
                if(a>.1 && finiteTransition[p+1]==0) { ++exterior;missing+=error>2; }
                ++transitionCompared;
            }
            transitionExterior+=exterior;transitionMissing+=missing;
            transitionMaxError=std::max(transitionMaxError,maximumError);
            std::printf("%ux native cloud transition frame%u weight%.2f: exterior%zu missing%zu max-alpha-error%d smartUV-held1.\n",
                samples,transition.frame,double(weight),exterior,missing,maximumError);
            require(exterior>500,"Native transition fixture lacks reflected directions beyond the finite cloud fan");
            if(!skyTransitionBaseline)
                require(missing==0 && maximumError<=2,"A valid non-affine native cloud transition dropped reflected sky coverage");
            require(render(0,0)==transitionNative,"Native cloud transition extension changed disabled water pixels");
        }
    }
    if(skyTransitionBaseline) {
        require(transitionMissing>4000,"Old-library control did not reproduce intermittent native cloud coverage loss");
    }
    else {
        // Actual native RasterPS is the texture/alpha oracle. Radially enlarge
        // this same non-affine seven-vertex fan and its UVs: each triangle now
        // directly rasterizes the proposed extended sector. The original fan
        // remains unmodified while the reflection shader is sampled.
        for(uint32_t y=0;y<Height;++y)for(uint32_t x=0;x<Width;++x) {
            const size_t p=(y*Width+x)*4;
            const double wave=.5+.25*std::cos(x*6.283185307179586/64)+.25*std::sin(y*6.283185307179586/32);
            skyTexels[p]=skyTexels[p+1]=skyTexels[p+2]=uint8_t(std::round(80+175*wave));
        }
        const auto &transition=NativeSkyTransitionFixture::Frames[1];
        const float weight=.5f;
        for(uint32_t v=0;v<7;++v) {
            for(uint32_t c=0;c<3;++c)world[7+v][c]=transition.previousPositions[v][c]*(1-weight)+transition.currentPositions[v][c]*weight;
            std::memcpy(uv[7+v],transition.currentTexcoords[v],sizeof(uv[0]));
        }
        reflection.camera[0]=reflection.skyCamera[0]=world[7][0];
        reflection.camera[2]=reflection.skyCamera[2]=world[7][2];
        putWaterLookupPatch(world[7][0],world[7][2],1,0,0,1,patchRadius*cloudScale);
        float nativeTransitionWorld[7][4],nativeTransitionUV[7][2];
        std::memcpy(nativeTransitionWorld,world+7,sizeof(nativeTransitionWorld));
        std::memcpy(nativeTransitionUV,uv+7,sizeof(nativeTransitionUV));
        size_t nativeTextureComparisons=0;int nativeTextureMaximum=0;
        for(uint8_t textureAlpha : {uint8_t(255),uint8_t(128)}) {
            setSkyTextureAlpha(textureAlpha);
            fill(uvBuffer,uv,sizeof(uv));rebuildPositions();
            const auto reflectedSector=render(1,4);
            for(uint32_t v=0;v<7;++v) {
                if(v>0) {
                    for(uint32_t c=0;c<3;++c)world[7+v][c]=nativeTransitionWorld[0][c]+32*(nativeTransitionWorld[v][c]-nativeTransitionWorld[0][c]);
                    for(uint32_t c=0;c<2;++c)uv[7+v][c]=nativeTransitionUV[0][c]+32*(nativeTransitionUV[v][c]-nativeTransitionUV[0][c]);
                }
                screen[7+v][0]=((world[7+v][0]-reflection.skyCamera[0])/(2*patchRadius*cloudScale)+.5f)*Width;
                screen[7+v][1]=((world[7+v][2]-reflection.skyCamera[2])/(2*patchRadius*cloudScale)+.5f)*Height;
                screen[7+v][2]=.5f;screen[7+v][3]=1;
            }
            fill(uvBuffer,uv,sizeof(uv));fill(screenBuffer,screen,sizeof(screen));rebuildPositions();
            const auto rasterSector=render(0,0,2,9,18);
            size_t positive=0, disagreements=0, rasterBoundaryPixels=0;
            for(uint32_t y=4;y<Height-4;++y)for(uint32_t x=4;x<Width-4;++x) {
                const size_t p=(y*Width+x)*4;const double a=nativeCloudAlpha(x,y);
                positive+=reflectedSector[p+1]>20;
                double nearestEdge=1e20;
                for(uint32_t edge=1;edge<=6;++edge) {
                    const double ex=nativeTransitionWorld[edge][0]-nativeTransitionWorld[0][0];
                    const double ez=nativeTransitionWorld[edge][2]-nativeTransitionWorld[0][2];
                    const double px=x+.5-Width*.5,py=y+.5-Height*.5;
                    if(px*ex+py*ez>=0)nearestEdge=std::min(nearestEdge,std::abs(px*ez-py*ex)/std::hypot(ex,ez));
                }
                // A native MSAA pixel split across two sectors combines two
                // independently evaluated primitive samples; the reflection
                // lookup selects one pixel-center sector. Compare strict
                // material interiors, with the radial seam itself checked
                // independently below on a small continuous lookup patch.
                if(samples>1 && nearestEdge<=.75) { ++rasterBoundaryPixels; continue; }
                for(uint32_t c=0;c<3;++c) {
                    const int error=int(std::ceil(std::abs(double(reflectedSector[p+c])-double(rasterSector[p+c])*a)));
                    nativeTextureMaximum=std::max(nativeTextureMaximum,error);
                    if(error>2) {
                        if(disagreements<12)std::printf("%ux sector material mismatch alpha%u pixel%u,%u c%u: reflected%u native%u radialAlpha%.6f error%d radialEdgePixels%.6f coverage%u.\n",
                            samples,unsigned(textureAlpha),x,y,c,unsigned(reflectedSector[p+c]),unsigned(rasterSector[p+c]),a,error,nearestEdge,unsigned(rasterSector[p+3]));
                        ++disagreements;
                    }
                    require(error<=2,"Extended non-affine cloud texture/alpha disagrees with native per-sector rasterization");
                    ++nativeTextureComparisons;
                }
            }
            require(positive>1000,"Native sector material comparison has insufficient nonzero coverage");
            std::printf("%ux sector material alpha%u disagreements%zu max-error%d mixed-sector-band%zu.\n",samples,unsigned(textureAlpha),disagreements,nativeTextureMaximum,rasterBoundaryPixels);
            require(disagreements==0,"Extended non-affine cloud texture/alpha disagrees with native per-sector rasterization");
            std::memcpy(world+7,nativeTransitionWorld,sizeof(nativeTransitionWorld));
            std::memcpy(uv+7,nativeTransitionUV,sizeof(nativeTransitionUV));
            fill(uvBuffer,uv,sizeof(uv));rebuildPositions();
        }
        setSkyTextureAlpha(255);
        int radialSeamMaximum=0;size_t radialSeamPositive=0;
        for(uint32_t edge=1;edge<=6;++edge) {
            const float dx=world[7+edge][0]-world[7][0],dz=world[7+edge][2]-world[7][2];
            const float len=std::hypot(dx,dz);
            putWaterLookupPatch(world[7][0]+dx*1.15f,world[7][2]+dz*1.15f,-dz/len,dx/len,dx/len,dz/len,2);
            rebuildPositions();const auto seam=render(1,4);
            for(uint32_t y=8;y<Height-8;++y) {
                const size_t p=(y*Width+31)*4,q=p+4;
                radialSeamPositive+=seam[p+1]>10&&seam[q+1]>10;
                for(uint32_t c=0;c<3;++c)radialSeamMaximum=std::max(radialSeamMaximum,std::abs(int(seam[p+c])-int(seam[q+c])));
            }
        }
        require(radialSeamPositive>240 && radialSeamMaximum<=2,
            "Piecewise native cloud extension introduced a discontinuity at a shared radial sector edge");
        putWaterLookupPatch(world[7][0],world[7][2],1,0,0,1,patchRadius*cloudScale);
        rebuildPositions();const auto ordered=render(1,4);
        // The common vertex need not be the first index or the lowest ID.
        for(uint32_t c=0;c<4;++c)std::swap(world[7][c],world[10][c]);
        for(uint32_t c=0;c<2;++c)std::swap(uv[7][c],uv[10][c]);
        for(uint32_t i=9;i<27;++i) { if(indices[i]==7)indices[i]=10;else if(indices[i]==10)indices[i]=7; }
        for(uint32_t f=0;f<6;++f)std::rotate(indices+9+f*3,indices+10+f*3,indices+12+f*3);
        fill(uvBuffer,uv,sizeof(uv));refreshFixtureIndices();
        const auto permuted=render(1,4);bool permutationEqual=true;
        for(size_t p=0;p<ordered.size();++p)permutationEqual&=nearByte(ordered[p],permuted[p],1);
        require(permutationEqual,"Native cloud sector lookup depends on the common vertex ID or face-corner order");
        std::printf("%ux native non-affine cloud sector: texture/alpha comparisons%zu max-error%d; radial pairs%zu max-jump%d; reordered topology passed.\n",
            samples,nativeTextureComparisons,nativeTextureMaximum,radialSeamPositive,radialSeamMaximum);
    }
    std::printf("%ux native cloud transition %s: samples%zu exterior%zu missing%zu max-alpha-error%d.\n",
        samples,skyTransitionBaseline?"OLD-LIBRARY CONTROL":"corrected",transitionCompared,transitionExterior,transitionMissing,transitionMaxError);
    std::memcpy(world,transitionSavedWorld,sizeof(world));
    std::memcpy(screen,transitionSavedScreen,sizeof(screen));
    std::memcpy(uv,transitionSavedUV,sizeof(uv));
    std::memcpy(colors,transitionSavedColors,sizeof(colors));
    std::memcpy(indices,transitionSavedIndices,sizeof(indices));
    reflection=transitionSavedReflection;skyTexels=transitionSavedTexture;
    params[2]=transitionSavedParams;rdpTile=transitionSavedTile;
    gpuTile=transitionSavedGPU;rdp[2]=transitionSavedRdp;
    fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));
    fill(rdpTileBuffer,&rdpTile,sizeof(rdpTile));fill(gpuTileBuffer,&gpuTile,sizeof(gpuTile));
    fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
    setSkyTextureAlpha(255);refreshFixtureIndices();bindWaterAdjacency();
    require(render(1,0)==cloudExtended,"Native transition fixture failed to restore the accepted affine cloud output");
}
