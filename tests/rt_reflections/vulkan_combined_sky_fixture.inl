// Dedicated bounded replay of numeric opening geometry/material metadata.
// Pixels, sparse texture slots, mip chains and the water quad are synthetic.
// In particular, this is not a capture of the failing Vulkan workload.
{
    auto asFloat = [](uint32_t bits) { float value; std::memcpy(&value, &bits, 4); return value; };
    float combinedWorld[24][4]{};
    float combinedScreen[24][4]{};
    float combinedUV[24][2]{};
    float combinedColors[24][4]{};
    uint32_t combinedFaces[57]{};
    for (uint32_t i = 0; i < 24; ++i) {
        combinedWorld[i][3] = combinedScreen[i][3] = 1;
        combinedColors[i][0] = combinedColors[i][1] = combinedColors[i][2] = combinedColors[i][3] = 1;
    }
    for (const auto &v : OpeningSkyCapture::Vertices) {
        for (uint32_t j = 0; j < 4; ++j) combinedWorld[v.index][j] = asFloat(v.data[j]);
        for (uint32_t j = 0; j < 2; ++j) combinedUV[v.index][j] = asFloat(v.data[4 + j]);
        for (uint32_t j = 0; j < 4; ++j) combinedColors[v.index][j] = asFloat(v.data[6 + j]);
    }
    const float nx = asFloat(OpeningSkyCapture::WaterNormal[0]);
    const float ny = asFloat(OpeningSkyCapture::WaterNormal[1]);
    const float nz = asFloat(OpeningSkyCapture::WaterNormal[2]);
    require(ny > .8f, "Archived opening sample has an unexpected water normal");
    const float cornerOffsets[4][2] = {{-150,150},{150,150},{150,-150},{-150,-150}};
    const float corners[4][2] = {{0,0},{float(Width),0},{float(Width),float(Height)},{0,float(Height)}};
    for (uint32_t i = 0; i < 4; ++i) {
        combinedWorld[i][0] = asFloat(OpeningSkyCapture::WaterCenter[0]) + cornerOffsets[i][0];
        combinedWorld[i][1] = asFloat(OpeningSkyCapture::WaterCenter[1]) - (nx * cornerOffsets[i][0] + nz * cornerOffsets[i][1]) / ny;
        combinedWorld[i][2] = asFloat(OpeningSkyCapture::WaterCenter[2]) + cornerOffsets[i][1];
        combinedScreen[i][0] = corners[i][0]; combinedScreen[i][1] = corners[i][1]; combinedScreen[i][2] = .5f;
    }
    // Two independent geometry records and BLAS ranges remain valid but lie
    // outside every water reflection, isolating the combined sky material path.
    for (uint32_t first : {4u,21u}) for (uint32_t i = 0; i < 3; ++i) {
        combinedWorld[first+i][0] = 200000 + float(first) * 100 + float(i) * 10;
        combinedWorld[first+i][1] = 100 + (i == 2 ? 20.f : 0);
        combinedWorld[first+i][2] = 200000 + (i == 1 ? 20.f : 0);
    }
    const uint32_t waterFaces[6] = {0,1,2,0,2,3};
    std::memcpy(combinedFaces, waterFaces, sizeof(waterFaces));
    combinedFaces[6]=4; combinedFaces[7]=5; combinedFaces[8]=6;
    std::memcpy(combinedFaces + 18, OpeningSkyCapture::BackdropFaces, sizeof(OpeningSkyCapture::BackdropFaces));
    std::memcpy(combinedFaces + 36, OpeningSkyCapture::CloudFaces, sizeof(OpeningSkyCapture::CloudFaces));
    combinedFaces[54]=21; combinedFaces[55]=22; combinedFaces[56]=23;
    auto combinedIndex = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(combinedFaces),
        RenderBufferFlag::INDEX | RenderBufferFlag::STORAGE | RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
    require(combinedIndex != nullptr, "Combined opening index allocation failed");
    auto combinedIndexUpload = upload(combinedFaces, sizeof(combinedFaces), 0);
    auto combinedScreenBuffer = upload(combinedScreen, sizeof(combinedScreen), RenderBufferFlag::VERTEX);
    auto combinedUVBuffer = upload(combinedUV, sizeof(combinedUV), RenderBufferFlag::VERTEX | RenderBufferFlag::STORAGE);
    auto combinedColorBuffer = upload(combinedColors, sizeof(combinedColors), RenderBufferFlag::VERTEX | RenderBufferFlag::STORAGE);
    worker.commandList->begin();
    worker.commandList->barriers(RenderBarrierStage::COPY, RenderBufferBarrier(combinedIndex.get(), RenderBufferAccess::WRITE));
    worker.commandList->copyBufferRegion(combinedIndex->at(0), combinedIndexUpload->at(0), sizeof(combinedFaces));
    worker.commandList->end(); worker.execute(); worker.wait();
    const RenderVertexBufferView combinedVB[] = {
        RenderVertexBufferView(combinedScreenBuffer->at(0), sizeof(combinedScreen)),
        RenderVertexBufferView(combinedUVBuffer->at(0), sizeof(combinedUV)),
        RenderVertexBufferView(combinedColorBuffer->at(0), sizeof(combinedColors))
    };
    const RenderIndexBufferView combinedIB(combinedIndex->at(0), sizeof(combinedFaces), RenderFormat::R32_UINT);
    vertexBufferOverride = combinedVB; indexBufferOverride = &combinedIB;
    common.setBuffer(common.genTexCoordBuffer, combinedUVBuffer, sizeof(combinedUV));
    common.setBuffer(common.shadedColBuffer, combinedColorBuffer, sizeof(combinedColors));
    common.setBuffer(common.indexBuffer, combinedIndex.get(), sizeof(combinedFaces));
    RT64Tests::VulkanRSPWorldFixture combinedProducer(device.get(), combinedIndex.get(), 57, combinedWorld, 24, 4, {{6,3,1},{54,3,1}});
    combinedProducer.bindReflection(common);
    beforeDrawRecord = [&]() { combinedProducer.record(worker); };

    reflection = Params{};
    std::memcpy(reflection.camera, OpeningSkyCapture::Camera, sizeof(reflection.camera));
    std::memcpy(reflection.skyCamera, OpeningSkyCapture::Camera, sizeof(reflection.skyCamera));
    std::memcpy(reflection.skyBackdropCamera, OpeningSkyCapture::Camera, sizeof(reflection.skyBackdropCamera));
    std::memcpy(reflection.sky, OpeningSkyCapture::Sky, sizeof(reflection.sky));
    std::memcpy(reflection.skyBackdrop, OpeningSkyCapture::Backdrop, sizeof(reflection.skyBackdrop));
    std::memcpy(reflection.skyCloudParams, OpeningSkyCapture::CloudParams, sizeof(reflection.skyCloudParams));
    reflection.skyCloudParams[3] = 0;
    std::memcpy(&rdp[2], OpeningSkyCapture::BackdropRDP, sizeof(OpeningSkyCapture::BackdropRDP));
    std::memcpy(&rdp[3], OpeningSkyCapture::CloudRDP, sizeof(OpeningSkyCapture::CloudRDP));
    params[2].ccL = OpeningSkyCapture::BackdropCombiner[0]; params[2].ccH = OpeningSkyCapture::BackdropCombiner[1];
    params[2].omL = OpeningSkyCapture::BackdropOtherMode[0]; params[2].omH = OpeningSkyCapture::BackdropOtherMode[1];
    params[3].ccL = OpeningSkyCapture::CloudCombiner[0]; params[3].ccH = OpeningSkyCapture::CloudCombiner[1];
    params[3].omL = OpeningSkyCapture::CloudOtherMode[0]; params[3].omH = OpeningSkyCapture::CloudOtherMode[1];
    params[2].flags.culling = 1;
    params[2].flags.usesTexture0 = params[2].flags.usesTexture1 = params[3].flags.usesTexture0 = 1;
    params[2].flags.linearFiltering = params[3].flags.linearFiltering = 1;
    params[2].flags.nativeSampler0 = params[2].flags.nativeSampler1 = NATIVE_SAMPLER_CLAMP_CLAMP;
    params[2].flags.cms0 = params[2].flags.cmt0 = params[2].flags.cms1 = params[2].flags.cmt1 = 2;
    params[3].flags.nativeSampler0 = NATIVE_SAMPLER_WRAP_WRAP;
    params[3].flags.cms0 = params[3].flags.cmt0 = 0;
    renderIndices[2] = {2,18,1,2,0}; renderIndices[3] = {3,36,3,1,0};
    fill(renderParamsBuffer, params, sizeof(params)); fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
    fill(rdpParamsBuffer, rdp, sizeof(rdp));
    interop::RDPTile combinedTiles[4]{};
    std::memcpy(&combinedTiles[1], OpeningSkyCapture::Tile1, sizeof(OpeningSkyCapture::Tile1));
    std::memcpy(&combinedTiles[2], OpeningSkyCapture::Tile2, sizeof(OpeningSkyCapture::Tile2));
    std::memcpy(&combinedTiles[3], OpeningSkyCapture::Tile3, sizeof(OpeningSkyCapture::Tile3));
    auto combinedTileBuffer = upload(combinedTiles, sizeof(combinedTiles), RenderBufferFlag::STORAGE);
    common.setBuffer(common.RDPTiles, combinedTileBuffer, sizeof(combinedTiles), RenderBufferStructuredView(sizeof(interop::RDPTile)));

    const uint32_t textureWidths[3] = {4,4,64}, textureHeights[3] = {64,64,32};
    const uint32_t sparseSlots[3] = {17,63,127};
    std::unique_ptr<RenderTexture> combinedTextures[3];
    std::unique_ptr<RenderTextureView> combinedViews[3];
    interop::GPUTile combinedGpuTiles[4]{};
    for (uint32_t t = 0; t < 3; ++t) {
        combinedTextures[t] = device->createTexture(RenderTextureDesc::Texture2D(textureWidths[t], textureHeights[t], 7, RenderFormat::R8G8B8A8_UNORM));
        require(combinedTextures[t] != nullptr, "Combined opening mip texture allocation failed");
        combinedViews[t] = combinedTextures[t]->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
        require(combinedViews[t] != nullptr, "Combined opening mip texture view failed");
        textures.setTexture(sparseSlots[t], combinedTextures[t].get(), RenderTextureLayout::SHADER_READ, combinedViews[t].get());
        textures.setTexture(t+1, combinedTextures[t].get(), RenderTextureLayout::SHADER_READ, combinedViews[t].get());
        auto &tile = combinedGpuTiles[t+1];
        tile.ulScale = tile.tcScale = hlslpp::float2(1,1);
        tile.textureIndex = t+1;
        tile.textureDimensions = hlslpp::float3(float(textureWidths[t]), float(textureHeights[t]), 7);
    }
    auto combinedGpuTileBuffer = upload(combinedGpuTiles, sizeof(combinedGpuTiles), RenderBufferFlag::STORAGE);
    common.setBuffer(common.GPUTiles, combinedGpuTileBuffer, sizeof(combinedGpuTiles), RenderBufferStructuredView(sizeof(interop::GPUTile)));
    auto updateCombinedTexture = [&](uint32_t t, uint8_t alpha) {
        worker.commandList->begin();
        worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(combinedTextures[t].get(), RenderTextureLayout::COPY_DEST));
        for (uint32_t mip = 0; mip < 7; ++mip) {
            const uint32_t w = std::max(1u, textureWidths[t] >> mip), h = std::max(1u, textureHeights[t] >> mip);
            Pixels texels(size_t(h) * 256, 0);
            for (uint32_t y = 0; y < h; ++y) for (uint32_t x = 0; x < w; ++x) {
                const size_t p = size_t(y) * 256 + x * 4;
                if (t == 2) {
                    const uint8_t value = mip ? uint8_t(50 + mip * 20) : uint8_t(125 + (x * 3 + y * 5) % 100);
                    texels[p] = texels[p+1] = texels[p+2] = value;
                }
                else {
                    texels[p] = uint8_t(t ? 210 - y * 2 : 30 + y * 2);
                    texels[p+1] = uint8_t(t ? 130 : 40);
                    texels[p+2] = uint8_t(t ? 20 + y : 180 - y);
                }
                texels[p+3] = alpha;
            }
            auto source = upload(texels.data(), texels.size(), 0);
            worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(combinedTextures[t].get(), mip),
                RenderTextureCopyLocation::PlacedFootprint(source, RenderFormat::R8G8B8A8_UNORM, w, h, 1, 64));
        }
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderTextureBarrier(combinedTextures[t].get(), RenderTextureLayout::SHADER_READ));
        worker.commandList->end(); worker.execute(); worker.wait();
    };
    for (uint32_t t = 0; t < 3; ++t) updateCombinedTexture(t, 255);
    // The archived backdrop tiles share one hash. First run that exact texture
    // sharing pattern before the deliberately distinct ENV-source controls.
    textures.setTexture(2, combinedTextures[0].get(), RenderTextureLayout::SHADER_READ, combinedViews[0].get());
    require(pipelines.prepare(device.get(), layout.get(), ms, false, true), "Combined opening sky PSO missing");
    std::printf("Combined opening %ux%u %ux: archived workload5 native sectors/materials, shared backdrop texture, two-geometry AS; first combined draw next.\n", Width, Height, samples);
    const auto firstCombined = render(1,4);
    require(render(1,4) == firstCombined, "Combined opening first repeated image differs");
    combinedProducer.verifyPositions(worker);
    std::puts("Combined opening base draw PASS; now testing sparse descriptors and independent texture/alpha controls.");
    textures.setTexture(2, combinedTextures[1].get(), RenderTextureLayout::SHADER_READ, combinedViews[1].get());
    for (uint32_t t = 0; t < 3; ++t) combinedGpuTiles[t+1].textureIndex = sparseSlots[t];

    for (uint32_t mipMode : {0u,1u}) {
        for (uint32_t t = 1; t < 4; ++t) combinedGpuTiles[t].flags.hasMipmaps = mipMode;
        fill(combinedGpuTileBuffer, combinedGpuTiles, sizeof(combinedGpuTiles));
        Pixels endpoints[2];
        for (uint32_t endpoint = 0; endpoint < 2; ++endpoint) {
            rdp[2].envColor = hlslpp::float4(float(endpoint),float(endpoint),float(endpoint),1);
            fill(rdpParamsBuffer, rdp, sizeof(rdp));
            updateCombinedTexture(2,255);
            const auto opaqueTexture = render(1,4);
            reflection.sky[3] = 0;
            const auto backdrop = render(1,4);
            reflection.sky[3] = 1;
            updateCombinedTexture(2,0);
            require(render(1,4) == backdrop, "Transparent cloud texture failed to expose exact native two-tile backdrop");
            updateCombinedTexture(2,128);
            const auto halfTexture = render(1,4);
            size_t cloudPixels = 0, compared = 0; int maxError = 0;
            for (size_t p = 0; p < halfTexture.size(); p += 4) {
                bool changed = false;
                for (uint32_t c = 0; c < 3; ++c) {
                    const float expected = backdrop[p+c] + (opaqueTexture[p+c] - float(backdrop[p+c])) * (128.f/255.f);
                    const int error = int(std::ceil(std::abs(halfTexture[p+c] - expected)));
                    maxError = std::max(maxError,error);
                    changed |= std::abs(int(opaqueTexture[p+c]) - int(backdrop[p+c])) > 3;
                    require(error <= 2, "Combined opening cloud texture alpha is not composited over native backdrop");
                }
                cloudPixels += changed; ++compared;
            }
            require(cloudPixels > size_t(Width)*Height/10, "Combined opening fixture has too little positive cloud contribution");
            require(render(1,4) == halfTexture, "Combined opening cloud/backdrop image is unstable");
            endpoints[endpoint] = halfTexture;
            std::printf("Combined opening mip%u ENV%u: %zu alpha-composition pixels, %zu positive cloud pixels, max error%d.\n", mipMode, endpoint, compared, cloudPixels, maxError);
        }
        require(endpoints[0] != endpoints[1], "Combined opening two backdrop textures have no distinct ENV endpoints");
    }
    // Sparse GPU observation verifies that non-affine sector selection really
    // ran, rather than silently using only the finite backdrop fallback.
    readSkyCapture = true; reflection.skyCloudParams[3] = 1;
    const auto observed = render(1,4);
    const uint32_t observedCount = std::min(capturedSkyWords[0], SkyCaptureCapacity);
    size_t sectors = 0, combined = 0;
    for (uint32_t i = 0; i < observedCount; ++i) {
        const size_t p = 4 + size_t(i)*SkyCaptureRecordWords;
        sectors += capturedSkyWords[p+2] == 11 && (capturedSkyWords[p+3]&4) != 0;
        combined += (capturedSkyWords[p+3]&7) == 7;
    }
    require(sectors > 0 && combined > 0, "Combined opening diagnostics did not observe valid cloud sectors and backdrop together");
    readSkyCapture = false; reflection.skyCloudParams[3] = 0;
    require(render(1,4) == observed, "Diagnostic observation changed combined sky colors");
    const auto noShadows = render(1,0);
    reflection.shadowOptions[0]=1; reflection.shadowOptions[1]=.5f; reflection.shadowOptions[2]=30000;
    reflection.shadowLight[0]=.6f; reflection.shadowLight[1]=.8f; reflection.shadowLight[3]=.55f;
    reflection.sceneOptions[1]=1; reflection.qualityOptions[1]=16;
    require(render(1,0) == noShadows, "Combined cloud/backdrop16-ray miss bundle changed the unshadowed result");
    std::puts("Combined opening16-ray shadow miss bundle PASS: same productionSkyPSMS, exact no-caster baseline.");
    std::printf("Combined opening PASS: captured%u samples, accepted sectors%zu, cloud+backdrop%zu; native non-affine UVs, sparse descriptor slots and mip branches verified.\n", observedCount,sectors,combined);
    beforeDrawRecord = nullptr; vertexBufferOverride = nullptr; indexBufferOverride = nullptr;
    common.setBuffer(common.posBuffer, positions.get(), sizeof(world));
    common.setBuffer(common.genTexCoordBuffer, uvBuffer, sizeof(uv));
    common.setBuffer(common.shadedColBuffer, colorBuffer, sizeof(colors));
    common.setBuffer(common.indexBuffer, faces.get(), sizeof(indices));
    common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
    common.setBuffer(common.interleavedRasters, scene.geometryBuffer(), scene.geometryBufferSize(), RenderBufferStructuredView(16));
    common.setBuffer(common.wr64FenceProxy, scene.proxyBuffer(), scene.proxyBufferSize());
    common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
    common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
    for (uint32_t slot : sparseSlots) textures.setTexture(slot, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
    for (uint32_t slot=1;slot<4;++slot) textures.setTexture(slot, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
}
