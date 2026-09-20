// Included only inside the bounded RSP fixture. Keep the ordinary64x64 suite
// and its historical trace unchanged. Screen/world mapping has already been
// scaled to the requested target; material texture dimensions stay native.
if (largeRaster) {
    beforeDrawRecord = nullptr;
    const auto savedLargeParams = params[2];
    const auto savedLargeRdp = rdp[2];
    std::unique_ptr<RenderTexture> gradients[2];
    std::unique_ptr<RenderTextureView> gradientViews[2];
    for (uint32_t t = 0; t < 2; ++t) {
        Pixels texels(64 * 256, 0);
        for (uint32_t y = 0; y < 64; ++y) for (uint32_t x = 0; x < 4; ++x) {
            const size_t p = y * 256 + x * 4;
            texels[p] = uint8_t(t ? 220 - y * 2 : 20 + y * 3);
            texels[p + 1] = uint8_t(t ? 40 + y * 3 : 60);
            texels[p + 2] = uint8_t(t ? 30 : 200 - y * 2);
            texels[p + 3] = 255;
        }
        gradients[t] = device->createTexture(RenderTextureDesc::Texture2D(4, 64, 1, RenderFormat::R8G8B8A8_UNORM));
        require(gradients[t] != nullptr, "Large fixture gradient texture allocation failed");
        gradientViews[t] = gradients[t]->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
        require(gradientViews[t] != nullptr, "Large fixture gradient view allocation failed");
        auto source = upload(texels.data(), texels.size(), 0);
        worker.commandList->begin();
        worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(gradients[t].get(), RenderTextureLayout::COPY_DEST));
        worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(gradients[t].get()),
            RenderTextureCopyLocation::PlacedFootprint(source, RenderFormat::R8G8B8A8_UNORM, 4, 64, 1, 64));
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderTextureBarrier(gradients[t].get(), RenderTextureLayout::SHADER_READ));
        worker.commandList->end(); worker.execute(); worker.wait();
        textures.setTexture(t, gradients[t].get(), RenderTextureLayout::SHADER_READ, gradientViews[t].get());
    }
    interop::RDPTile tiles[2]{};
    interop::GPUTile gpuTiles[2]{};
    for (uint32_t t = 0; t < 2; ++t) {
        tiles[t].fmt = 0; tiles[t].siz = 2; tiles[t].stride = 8;
        tiles[t].shifts = tiles[t].shiftt = 1;
        tiles[t].masks = 4; tiles[t].maskt = 64;
        tiles[t].lrs = 12; tiles[t].lrt = 252;
        tiles[t].cms = tiles[t].cmt = 2;
        tiles[t].nativeSampler = NATIVE_SAMPLER_CLAMP_CLAMP;
        gpuTiles[t].ulScale = gpuTiles[t].tcScale = hlslpp::float2(1, 1);
        gpuTiles[t].textureIndex = t;
        gpuTiles[t].textureDimensions = hlslpp::float3(4, 64, 1);
    }
    common.setBuffer(common.RDPTiles, upload(tiles, sizeof(tiles), RenderBufferFlag::STORAGE), sizeof(tiles), RenderBufferStructuredView(sizeof(interop::RDPTile)));
    common.setBuffer(common.GPUTiles, upload(gpuTiles, sizeof(gpuTiles), RenderBufferFlag::STORAGE), sizeof(gpuTiles), RenderBufferStructuredView(sizeof(interop::GPUTile)));
    params[2].ccL = 0xFC22FFFF; params[2].ccH = 0x1FFCFA38;
    params[2].omL = 0x0F0A4000; params[2].omH = 0x00982C3F;
    params[2].flags.usesTexture0 = params[2].flags.usesTexture1 = 1;
    params[2].flags.cms0 = params[2].flags.cmt0 = params[2].flags.cms1 = params[2].flags.cmt1 = 2;
    params[2].flags.nativeSampler0 = params[2].flags.nativeSampler1 = NATIVE_SAMPLER_CLAMP_CLAMP;
    params[2].flags.linearFiltering = 1;
    renderIndices[2].rdpTileCount = 2;
    rdp[2].envColor = hlslpp::float4(.5f, .5f, .5f, .5f);
    fill(renderParamsBuffer, params, sizeof(params));
    fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
    fill(rdpParamsBuffer, rdp, sizeof(rdp));

    // The actor sits toward the directional light but outside water reflection
    // rays, so the same pixels exercise both the full native backdrop lookup
    // and the16-ray soft-shadow kernel in the unoptimized productionSkyPSMS.
    float largeWorld[12][4]; std::memcpy(largeWorld, world, sizeof(largeWorld));
    const float actor[3][4] = {{-40,20,-30,1}, {40,20,-30,1}, {0,20,-5,1}};
    std::memcpy(largeWorld + 4, actor, sizeof(actor));
    RT64Tests::VulkanRSPWorldFixture fullScreen(device.get(), faces.get(), 27, largeWorld, 12, 4, {{6,3,1,17}});
    fullScreen.bindReflection(common);
    beforeDrawRecord = [&]() { fullScreen.record(worker); };
    reflection = Params{};
    reflection.skyBackdrop[0] = 9; reflection.skyBackdrop[1] = 2;
    reflection.skyBackdrop[2] = 4; reflection.skyBackdrop[3] = 1;
    std::memcpy(reflection.skyBackdropCamera, reflection.skyCamera, sizeof(reflection.skyCamera));
    require(pipelines.prepare(device.get(), layout.get(), ms, false, true), "Large fixture sky pipeline missing");
    std::printf("Large raster %ux%u: native two-tile backdrop reference then unchanged productionSkyPSMS.\n", Width, Height);
    const auto nativeBackdrop = render(0, 0, 2, 9, 12);
    const auto reflectedBackdrop = render(1, 4);
    size_t compared = 0, mismatches = 0; int maximumError = 0;
    for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
        const size_t p = (size_t(y) * Width + x) * 4;
        int error = 0;
        for (uint32_t c = 0; c < 3; ++c) error = std::max(error, std::abs(int(nativeBackdrop[p + c]) - int(reflectedBackdrop[p + c])));
        maximumError = std::max(maximumError, error); mismatches += error > 2; ++compared;
    }
    std::printf("Large raster backdrop: %zu/%zu within2, maximum channel error%d.\n", compared - mismatches, compared, maximumError);
    require(mismatches == 0 && maximumError <= 2, "Large-raster native backdrop and reflection disagree");
    const auto skyOnly = render(1, 0);
    reflection.shadowOptions[0] = 1; reflection.shadowOptions[1] = .5f; reflection.shadowOptions[2] = 30000;
    reflection.shadowLight[1] = .8f; reflection.shadowLight[2] = -.6f; reflection.shadowLight[3] = .55f;
    reflection.sceneOptions[1] = 1; reflection.qualityOptions[1] = 16;
    // Missing broad-phase bounds intentionally evaluates the full ray bundle.
    const auto skyAndShadows = render(1, 0);
    size_t darker = 0;
    for (size_t p = 0; p < skyOnly.size(); p += 4) {
        darker += skyAndShadows[p] < skyOnly[p] || skyAndShadows[p + 1] < skyOnly[p + 1] || skyAndShadows[p + 2] < skyOnly[p + 2];
        require(skyAndShadows[p + 3] == skyOnly[p + 3], "Large-raster shadows changed native alpha coverage");
    }
    require(darker > size_t(Width) * Height / 4, "Large-raster16-ray shadow fixture lacks a positive visible shadow effect");
    require(render(1, 0) == skyAndShadows, "Large-raster backdrop plus soft shadows are unstable across identical submissions");
    fullScreen.verifyPositions(worker);
    std::printf("Large raster PASS: %zu shadow-darkened pixels with productionSkyPSMS+16 actor rays.\n", darker);
    beforeDrawRecord = nullptr;
    params[2] = savedLargeParams; rdp[2] = savedLargeRdp;
    common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
    common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
    for (uint32_t t = 0; t < 2; ++t) textures.setTexture(t, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
}
