// Included in the existing headless raster probe after production PSO/target setup.
// This is synthetic GPU coverage of resource ownership and submission lifetime;
// it does not run FramebufferRenderer's private CPU course classifier or the game.
{
    struct ViewResources {
        FramebufferRenderer::Wr64RTView rt;
        std::unique_ptr<RenderBuffer> positions;
        RenderBuffer *worldUpload = nullptr, *paramsUpload = nullptr, *rdpUpload = nullptr;
        Params params;
        uint32_t casterFlags = 0;
        float world[16][4] = {};
        interop::RDPParams rdp[4] = {};
    } views[2];
    for (uint32_t view = 0; view < 2; ++view) {
        auto &v = views[view];
        std::memcpy(v.world, world, sizeof(world));
        std::memcpy(v.rdp, rdp, sizeof(rdp));
        v.params.enabled = 1;
        v.params.camera[0] = view * 100.0f;
        for (auto &vertex : v.world) vertex[0] += view * 100.0f;
        if (view == 1) v.rdp[1].primColor = hlslpp::float4(.02f, 1, .05f, 1);
        v.positions = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(world),
            RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS | RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
        require(v.positions != nullptr, "Two-player world buffer allocation failed");
        v.worldUpload = upload(v.world, sizeof(v.world), 0);
        static_assert(sizeof(Params) == sizeof(v.rt.params), "Fixture/production constant layouts differ");
        v.rt.paramsBuffer = device->createBuffer(RenderBufferDesc::UploadBuffer(
            (sizeof(v.params) + 255) & ~uint64_t(255), RenderBufferFlag::CONSTANT));
        require(v.rt.paramsBuffer != nullptr, "Per-view parameter allocation failed");
        v.paramsUpload = v.rt.paramsBuffer.get();
        v.rdpUpload = upload(v.rdp, sizeof(v.rdp), RenderBufferFlag::STORAGE);
        v.rt.descriptor = std::make_unique<FramebufferRendererDescriptorCommonSet>(samplers, true, device.get());
        auto &c = *v.rt.descriptor;
        c.setBuffer(c.FrParams, upload(&frame, sizeof(frame), RenderBufferFlag::CONSTANT), sizeof(frame));
        c.setBuffer(c.instanceRDPParams, v.rdpUpload, sizeof(v.rdp), RenderBufferStructuredView(sizeof(interop::RDPParams)));
        c.setBuffer(c.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
        c.setBuffer(c.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
        c.setBuffer(c.instanceRenderIndices, renderIndicesBuffer, sizeof(renderIndices), RenderBufferStructuredView(sizeof(interop::RenderIndices)));
        c.setBuffer(c.DynamicRenderParams, renderParamsBuffer, sizeof(params), RenderBufferStructuredView(sizeof(interop::RenderParams)));
        c.setBuffer(c.RtParams, v.paramsUpload, sizeof(v.params));
        c.setBuffer(c.posBuffer, v.positions.get(), sizeof(v.world));
        c.setBuffer(c.genTexCoordBuffer, uvBuffer, sizeof(uv));
        c.setBuffer(c.shadedColBuffer, colorBuffer, sizeof(colors));
        c.setBuffer(c.indexBuffer, faces.get(), sizeof(indices));
        c.setBuffer(c.wr64WaterAdjacency, upload(emptyAdjacency.data(), sizeof(emptyAdjacency), RenderBufferFlag::STORAGE), sizeof(emptyAdjacency));
        c.setBuffer(c.wr64SkyCapture, skyCapture.get(), SkyCaptureBytes);
    }
    require(views[0].paramsUpload != views[1].paramsUpload &&
        views[0].rt.descriptor->get() != views[1].rt.descriptor->get() &&
        views[0].positions.get() != views[1].positions.get(),
        "Two views share mutable GPU resources");

    // Use the actual embedded native shaders for fallback, through the same
    // production PSO creator, with this fixture's production descriptor layout.
    ShaderLibrary nativeLibrary(false, false);
    fillSamplers(device.get(), nativeLibrary.samplerLibrary.nearest, RenderFilter::NEAREST);
    fillSamplers(device.get(), nativeLibrary.samplerLibrary.linear, RenderFilter::LINEAR);
    RasterShaderUber nativeShaders(device.get(), shaderFormat, ms, &nativeLibrary, 1);
    PipelineCreation nativeCreation{};
    nativeCreation.device = device.get();
    nativeCreation.pipelineLayout = layout.get();
    nativeCreation.vertexShader = nativeShaders.vertexShader.get();
    nativeCreation.pixelShader = nativeShaders.pixelShader.get();
    nativeCreation.alphaBlend = true;
    nativeCreation.NoN = true;
    nativeCreation.multisampling = ms;
    auto nativePipeline = RasterShader::createPipeline(nativeCreation);
    require(nativePipeline != nullptr, "Native fallback PSO creation failed");
    // The production wait joins its workers AND releases the embedded shader
    // objects, so create this compatible-layout PSO before calling it.
    nativeShaders.waitForPipelineCreation();

    FramebufferRenderer submitter(&worker, false, graphicsAPI, &nativeLibrary);
    submitter.rendererPipelineLayout = layout.get();
    submitter.descTextureSet = std::make_unique<FramebufferRendererDescriptorTextureSet>(device.get(), 2);
    submitter.descTextureSet->setTexture(0, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
    submitter.descTextureSet->setTexture(1, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
    // P2 uses draw index 2, but the same blue water instance as P1. Draw index
    // 3 is a native-only overlay using the red caster material; after P2's green
    // descriptor this makes failure to restore the native set measurable.
    renderIndices[2] = {0, 0, 0, 0, 0};
    renderIndices[3] = {1, 0, 0, 0, 0};
    fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
    auto &base = *submitter.descCommonSet;
    base.setBuffer(base.FrParams, upload(&frame, sizeof(frame), RenderBufferFlag::CONSTANT), sizeof(frame));
    base.setBuffer(base.instanceRDPParams, rdpParamsBuffer, sizeof(rdp), RenderBufferStructuredView(sizeof(interop::RDPParams)));
    base.setBuffer(base.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
    base.setBuffer(base.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
    base.setBuffer(base.instanceRenderIndices, renderIndicesBuffer, sizeof(renderIndices), RenderBufferStructuredView(sizeof(interop::RenderIndices)));
    base.setBuffer(base.DynamicRenderParams, renderParamsBuffer, sizeof(params), RenderBufferStructuredView(sizeof(interop::RenderParams)));
    for (uint32_t i = 0; i < 3; ++i) {
        submitter.vertexInputSlots[i] = inputSlots[i];
        submitter.indexedVertexViews[i] = vertexBuffers[i];
    }
    submitter.indexBufferView = indexView;
    FramebufferRenderer::Framebuffer submittedFramebuffer;
    submittedFramebuffer.viewport = RenderViewport(0, 0, float(Width), float(Height));
    submittedFramebuffer.descRealFbSet = std::make_unique<FramebufferRendererDescriptorFramebufferSet>(device.get());
    submittedFramebuffer.descDummyFbSet = std::make_unique<FramebufferRendererDescriptorFramebufferSet>(device.get());
    RenderTarget submittedColor(0, Framebuffer::Type::Color, ms, false);
    RenderTarget submittedDepth(0, Framebuffer::Type::Depth, ms, false);
    require(submittedColor.resize(&worker, Width, Height) && submittedDepth.resize(&worker, Width, Height),
        "Actual submission target setup failed");
    RenderFramebufferStorage submittedStorage, depthOnlyStorage;
    submittedStorage.setup(device.get(), RenderFramebufferKey{}, &submittedColor, &submittedDepth);
    depthOnlyStorage.setup(device.get(), RenderFramebufferKey{}, nullptr, &submittedDepth);
    for (auto *set : {submittedFramebuffer.descRealFbSet.get(), submittedFramebuffer.descDummyFbSet.get()}) {
        set->setBuffer(set->FbParams, upload(&fb, sizeof(fb), RenderBufferFlag::CONSTANT), sizeof(fb));
        set->setTexture(set->gBackgroundDepth, submittedDepth.texture.get(), RenderTextureLayout::DEPTH_READ, submittedDepth.textureView.get());
    }

    size_t submissions = 0;
    auto renderViews = [&](bool vertical, uint32_t failedMask, bool nativeOnly, bool reverse = false, bool nativeOverlay = false) {
        bool ready[2] = {};
        // All mutable uploads and descriptor writes for BOTH players precede
        // command-list recording. No per-view execute/wait hides aliasing.
        for (uint32_t view = 0; view < 2; ++view) {
            auto &v = views[view];
            std::memcpy(&v.rt.params, &v.params, sizeof(v.params));
            fill(v.paramsUpload, &v.rt.params, sizeof(v.rt.params));
            fill(v.worldUpload, v.world, sizeof(v.world));
            fill(v.rdpUpload, v.rdp, sizeof(v.rdp));
            const std::vector<Wr64RTSceneGeometry> geometry = failedMask & (1u << view) ?
                std::vector<Wr64RTSceneGeometry>{} : std::vector<Wr64RTSceneGeometry>{{6, 3, 1, v.casterFlags}};
            ready[view] = v.rt.prepared = v.rt.scene.prepare(device.get(), v.positions.get(), faces.get(), 14, 27, geometry);
            require(ready[view] == ((failedMask & (1u << view)) == 0), "Per-view scene preparation failed unexpectedly");
            if (ready[view]) {
                auto &c = *v.rt.descriptor;
                c.setAccelerationStructure(c.SceneBVH, v.rt.scene.accelerationStructure());
                c.setBuffer(c.interleavedRasters, v.rt.scene.geometryBuffer(), v.rt.scene.geometryBufferSize(), RenderBufferStructuredView(16));
                c.setBuffer(c.wr64FenceProxy, v.rt.scene.proxyBuffer(), v.rt.scene.proxyBufferSize());
            }
            else require(!v.rt.scene.prepared() && !v.rt.scene.accelerationStructure(), "Failed view retained an available old scene");
        }
        if (ready[0] && ready[1]) require(
            views[0].rt.scene.accelerationStructure() != views[1].rt.scene.accelerationStructure() &&
            views[0].rt.scene.geometryBuffer() != views[1].rt.scene.geometryBuffer(), "Two prepared views alias acceleration data");

        worker.commandList->begin();
        for (auto &v : views) {
            worker.commandList->barriers(RenderBarrierStage::COPY, RenderBufferBarrier(v.positions.get(), RenderBufferAccess::WRITE));
            worker.commandList->copyBufferRegion(v.positions->at(0), v.worldUpload->at(0), sizeof(v.world));
            if (v.rt.scene.prepared()) require(v.rt.scene.recordBuild(&worker), "Could not record one of the two AS builds");
        }
        for (uint32_t view = 0; view < 2; ++view) submitter.wr64RTViews[view] = std::move(views[view].rt);
        submitter.instanceDrawCallVector.clear();
        submitter.instanceDrawCallVector.resize(5);
        submitter.wr64RTDrawViews = {1, 0, 2, 0, 0};
        auto &clear = submitter.instanceDrawCallVector[4];
        clear.type = InstanceDrawCall::Type::FillRect;
        clear.clearRect.rect = RenderRect(0, 0, Width, Height);
        clear.clearRect.depth = .25f;
        RasterScene depthScene;
        depthScene.instanceIndices = {4};
        bool depthState = false;
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,
            RenderTextureBarrier(submittedDepth.texture.get(), RenderTextureLayout::DEPTH_WRITE));
        worker.commandList->setFramebuffer(depthOnlyStorage.colorDepthWrite.get());
        require(static_cast<D3D12CommandList *>(worker.commandList.get())->activeGraphicsPipelineLayout == nullptr,
            "Depth-only submission did not begin before any graphics layout");
        submitter.submitRasterScene(&worker, submittedFramebuffer, &depthOnlyStorage, depthScene, depthState);
        require(static_cast<D3D12CommandList *>(worker.commandList.get())->activeGraphicsPipelineLayout == nullptr,
            "Native depth-only clear bound a graphics descriptor/layout");
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS, RenderBufferBarrier(skyCapture.get(), RenderBufferAccess::WRITE));
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
            RenderTextureBarrier(submittedColor.texture.get(), RenderTextureLayout::COLOR_WRITE));
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
            RenderTextureBarrier(submittedDepth.texture.get(), RenderTextureLayout::DEPTH_READ));
        worker.commandList->setFramebuffer(submittedStorage.colorWriteDepthRead.get());
        depthState = true;
        worker.commandList->clearColor(0, RenderColor(0, 0, 0, 0));
        for (uint32_t view = 0; view < 2; ++view) {
            const uint32_t x = vertical ? view * Width / 2 : 0;
            const uint32_t y = vertical ? 0 : view * Height / 2;
            const uint32_t width = vertical ? Width / 2 : Width;
            const uint32_t height = vertical ? Height : Height / 2;
            auto &call = submitter.instanceDrawCallVector[view ? 2 : 0];
            call.type = InstanceDrawCall::Type::IndexedTriangles;
            call.triangles = {};
            call.triangles.pipeline = nativeOnly || !ready[view] ? nativePipeline.get() : pipelines.get(false, false, false);
            call.triangles.screenScale = vertical ? hlslpp::float2(.5f, 1) : hlslpp::float2(1, .5f);
            call.triangles.screenOffset = vertical ? hlslpp::float2(view ? .5f : -.5f, 0) : hlslpp::float2(0, view ? -.5f : .5f);
            call.triangles.scissor = RenderRect(x, y, x + width, y + height);
            call.triangles.faceCount = 2;
        }
        RasterScene colorScene;
        colorScene.instanceIndices = reverse ? std::vector<uint32_t>{2, 0} : std::vector<uint32_t>{0, 2};
        if (nativeOverlay) {
            auto &call = submitter.instanceDrawCallVector[3];
            call.type = InstanceDrawCall::Type::IndexedTriangles;
            call.triangles = {};
            call.triangles.pipeline = nativePipeline.get();
            call.triangles.screenScale = hlslpp::float2(1, 1);
            call.triangles.scissor = RenderRect(Width - 8, Height - 8, Width, Height);
            call.triangles.faceCount = 2;
            colorScene.instanceIndices.push_back(3);
        }
        submitter.submitRasterScene(&worker, submittedFramebuffer, &submittedStorage, colorScene, depthState);
        RenderTexture *source = submittedColor.texture.get();
        if (samples > 1) {
            const RenderTextureBarrier resolve[] = {{submittedColor.texture.get(), RenderTextureLayout::RESOLVE_SOURCE},
                {resolved.get(), RenderTextureLayout::RESOLVE_DEST}};
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, nullptr, 0, resolve, 2);
            worker.commandList->resolveTexture(resolved.get(), submittedColor.texture.get());
            source = resolved.get();
        }
        worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(source, RenderTextureLayout::COPY_SOURCE));
        D3D12_TEXTURE_COPY_LOCATION dst{};
        dst.pResource = static_cast<D3D12Buffer *>(readback.get())->d3d;
        dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        dst.PlacedFootprint.Footprint = {DXGI_FORMAT_R8G8B8A8_UNORM, Width, Height, 1, Width * 4};
        D3D12_TEXTURE_COPY_LOCATION src{};
        src.pResource = static_cast<D3D12Texture *>(source)->d3d;
        src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        static_cast<D3D12CommandList *>(worker.commandList.get())->d3d->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
        worker.commandList->end();
        worker.execute(); worker.wait(); ++submissions;
        deviceStatus("After two-view single submission");
        Pixels pixels(Width * Height * 4);
        const RenderRange read(0, pixels.size()), noWrite(0, 0);
        const void *mapped = readback->map(0, &read);
        require(mapped != nullptr, "Two-view readback mapping failed");
        std::memcpy(pixels.data(), mapped, pixels.size());
        readback->unmap(0, &noWrite);
        for (uint32_t view = 0; view < 2; ++view) views[view].rt = std::move(submitter.wr64RTViews[view]);
        return pixels;
    };
    auto compareView = [&](const Pixels &actual, const Pixels &expected, bool vertical, uint32_t view, const char *message) {
        for (uint32_t y = 0; y < Height; ++y) for (uint32_t x = 0; x < Width; ++x) {
            if ((vertical ? x / (Width / 2) : y / (Height / 2)) != view) continue;
            const size_t p = (y * Width + x) * 4;
            require(std::memcmp(actual.data() + p, expected.data() + p, 4) == 0, message);
        }
    };
    for (bool vertical : {false, true}) {
        const auto native = renderViews(vertical, 0, true);
        const auto both = renderViews(vertical, 0, false);
        for (uint32_t view = 0; view < 2; ++view) {
            const uint32_t x = vertical ? (view * 2 + 1) * Width / 4 : Width / 2;
            const uint32_t y = vertical ? Height / 2 : (view * 2 + 1) * Height / 4;
            const size_t p = (y * Width + x) * 4;
            require(nearByte(native[p], 26) && nearByte(native[p + 1], 51) && nearByte(native[p + 2], 178),
                "Native half-view water differs from the original blue material");
            require(both[p + view] > native[p + view] + 10 && both[p + 2] < native[p + 2] - 8,
                "A view did not reflect its independently colored scene");
            const auto failed = renderViews(vertical, 1u << view, false);
            compareView(failed, native, vertical, view, "Failed scene did not restore its native view exactly");
            compareView(failed, both, vertical, 1 - view, "One failed view changed the healthy RT view");
        }
        require(renderViews(vertical, 0, false, true) == both, "Reversing view draw order changed the two-view result");
        const auto overlay = renderViews(vertical, 0, false, false, true);
        for (uint32_t y = 0; y < Height; ++y) for (uint32_t x = 0; x < Width; ++x) {
            const size_t p = (y * Width + x) * 4;
            if (x >= Width - 8 && y >= Height - 8)
                require(nearByte(overlay[p], 255) && nearByte(overlay[p + 1], 13) && nearByte(overlay[p + 2], 5),
                    "Native draw after P2 retained the green RT-owned material descriptor");
            else require(std::memcmp(overlay.data() + p, both.data() + p, 4) == 0,
                "Native descriptor restoration changed pixels outside its scissor");
        }
        // A mismatched P2 camera must miss the translated green geometry while
        // P1 remains unchanged. This catches shared/overwritten constants.
        views[1].params.camera[0] = 0;
        const auto wrongCamera = renderViews(vertical, 0, false);
        compareView(wrongCamera, both, vertical, 0, "Changing P2 camera altered P1");
        require(wrongCamera != both, "P2 camera constants did not affect the GPU result");
        views[1].params.camera[0] = 100;
        // Rebuild only P2's caster away from the ray path; this catches a shared
        // AS and a stale scene carried over from the preceding presentation.
        for (uint32_t i = 4; i < 7; ++i) views[1].world[i][0] += 1000;
        const auto missingCaster = renderViews(vertical, 0, false);
        compareView(missingCaster, both, vertical, 0, "Changing P2 acceleration geometry altered P1");
        compareView(missingCaster, native, vertical, 1, "P2 retained a stale hit after its caster moved");
        for (uint32_t i = 4; i < 7; ++i) views[1].world[i][0] -= 1000;
        for (uint32_t present = 0; present < 4; ++present)
            require(renderViews(vertical, 0, false, present % 2 != 0) == both,
                "Fenced resource reuse changed a later two-view presentation");
        require(renderViews(vertical, 0, true) == native, "RT deactivation changed the native split-screen output");
        writePPM(outputPrefix + "-two-player-" + (vertical ? "vertical-" : "horizontal-") + std::to_string(samples) + "x.ppm", both);
        std::printf("Two-player %ux %s: distinct red/green hits; exact independent fallback, camera/AS isolation and repeated presentations.\n",
            samples, vertical ? "vertical" : "horizontal");
    }
    // Actual submitRasterScene: each viewport's water-softness pass consumes
    // only its own caster AS and parameters in the same command submission.
    {
        const Params savedShadowParams[2]={views[0].params,views[1].params};
        float savedShadowWorld[2][16][4];
        for(uint32_t view=0;view<2;++view) {
            auto& v=views[view];std::memcpy(savedShadowWorld[view],v.world,sizeof(v.world));
            const float shift=float(view)*100;
            const float tri[3][4]={{shift-6,5,-10,1},{shift+6,5,-10,1},{shift,5,10,1}};
            std::memcpy(v.world[4],tri,sizeof(tri));v.casterFlags=1;
            v.params.strength=0;v.params.shadowLight[1]=1;v.params.shadowLight[3]=.55f;
            v.params.shadowOptions[0]=1;v.params.shadowOptions[1]=.5f;v.params.shadowOptions[2]=100;
        }
        size_t shadowSamples=0,softEdges=0;
        for(bool vertical:{false,true}) {
            for(auto& v:views)v.params.debugView=5;
            const auto mask=renderViews(vertical,0,false);
            require(renderViews(vertical,0,false,true)==mask,"Water scenery shadows changed with two-view draw order");
            for(auto& v:views)v.params.debugView=0;
            const auto shaded=renderViews(vertical,0,false);
            for(auto& v:views)v.params.shadowOptions[0]=0;
            const auto lit=renderViews(vertical,0,false);
            for(auto& v:views)v.params.shadowOptions[0]=1;
            for(uint32_t y=2;y<Height-2;++y)for(uint32_t x=2;x<Width-2;++x) {
                const uint32_t vw=vertical?Width/2:Width,vh=vertical?Height:Height/2;
                const uint32_t lx=x%vw,ly=y%vh;
                if(lx<2||lx>=vw-2||ly<2||ly>=vh-2)continue;
                const double px=(lx+.5)*10/vw-5,pz=5-(ly+.5)*10/vh;
                uint32_t hits=0;
                for(uint32_t pair=0;pair<4;++pair)for(double sign:{-1.0,1.0}) {
                    const double r=6*std::sqrt((pair+.5)/4),a=pair*3.14159265358979323846*(3-std::sqrt(5.0));
                    const double hx=px+sign*r*std::cos(a),hz=pz-sign*r*std::sin(a),t=(hz+10)/20;
                    hits+=t>=0&&t<=1&&std::abs(hx)<=6*(1-t);
                }
                const size_t p=(y*Width+x)*4;const double coverage=hits/8.0,q=1-.28*coverage;
                require(std::abs(mask[p]-255*(1-coverage))<=1,"Two-player scenery soft mask disagreed with independent rays");
                for(uint32_t c=0;c<3;++c)require(std::abs(shaded[p+c]-q*lit[p+c])<=2,"Two-player soft water used another view's attenuation");
                require(shaded[p+3]==lit[p+3],"Two-player soft water changed native alpha/coverage");
                softEdges+=hits>0&&hits<8;++shadowSamples;
            }
            for(uint32_t i=4;i<7;++i)views[1].world[i][0]+=1000;
            const auto moved=renderViews(vertical,0,false);
            compareView(moved,shaded,vertical,0,"P2 scenery-shadow AS update changed P1");
            compareView(moved,lit,vertical,1,"P2 scenery shadow retained a moved caster");
            for(uint32_t i=4;i<7;++i)views[1].world[i][0]-=1000;
            require(renderViews(vertical,0,false)==shaded,"Two-player scenery kernel did not restore exact stationary output");
        }
        require(softEdges>1000,"Two-player scenery fixture did not exercise soft edges in both viewports");
        for(uint32_t view=0;view<2;++view) {
            views[view].params=savedShadowParams[view];views[view].casterFlags=0;
            std::memcpy(views[view].world,savedShadowWorld[view],sizeof(views[view].world));
        }
        std::printf("Two-player %ux scenery water: analytic%zu fractional%zu, both splits, independent AS and unchanged native coverage.\n",samples,shadowSamples,softEdges);
    }
    // Other courses add projected sun/glow and moon/star payloads. Exercise
    // their production sky PS in both owners, including one view looking away
    // and a transition back to a course with no celestial bodies. The native
    // projector/snapshot fixtures separately establish the authored values.
    const Params beforeCelestial[2] = {views[0].params, views[1].params};
    for (auto &v : views) for (uint32_t i = 4; i < 7; ++i) v.world[i][0] += 1000;
    require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
        "Two-player celestial sky pipeline missing");
    auto fillCelestial = [&](uint32_t view, bool stars) {
        auto &p = views[view].params;
        p = beforeCelestial[view];
        p.sky[3] = p.skyBackdrop[3] = 0;
        p.celestialProjection[0][0] = 64;
        p.celestialProjection[0][1] = 32;
        p.celestialProjection[1][1] = 96;
        p.celestialProjection[1][2] = -64;
        p.celestialProjection[2][1] = 1;
        p.celestialInfo[0] = stars ? 18 : 2;
        for (auto &vector : p.celestialAlpha) for (auto &word : vector) word = 0xffffffffu;
        for (uint32_t i = 0; i < p.celestialInfo[0]; ++i) {
            auto &body = p.celestial[i];
            const bool star = stars && i < 16;
            const float x = star ? 3.f + (i % 4) * 15.f : 16.f + view * 8.f;
            const float y = star ? 3.f + (i / 4) * 15.f : 16.f;
            const float extent = star ? 5.f : 24.f;
            body.bounds[0] = x; body.bounds[1] = y;
            body.bounds[2] = x + extent; body.bounds[3] = y + extent;
            body.uv[2] = body.uv[3] = star ? 4.f : 32.f;
            body.color[0] = view ? .35f : 1.f;
            body.color[1] = .7f; body.color[2] = view ? 1.f : .15f;
            body.color[3] = i + 1 == p.celestialInfo[0] ? 1.f : .45f;
            body.meta[0] = star ? 2048 : i + 1 == p.celestialInfo[0] ? 0 : 1024;
            body.meta[1] = body.meta[2] = star ? 4 : 32;
        }
    };
    auto changedInView = [&](const Pixels &a, const Pixels &b, bool vertical, uint32_t view) {
        size_t changed = 0;
        for (uint32_t y = 0; y < Height; ++y) for (uint32_t x = 0; x < Width; ++x) {
            if ((vertical ? x / (Width / 2) : y / (Height / 2)) != view) continue;
            changed += std::memcmp(a.data() + (y * Width + x) * 4,
                b.data() + (y * Width + x) * 4, 4) != 0;
        }
        return changed;
    };
    for (bool vertical : {false, true}) for (bool stars : {false, true}) {
        for (uint32_t view = 0; view < 2; ++view) fillCelestial(view, stars);
        const auto bodies = renderViews(vertical, 0, false);
        views[0].params.celestialInfo[0] = views[1].params.celestialInfo[0] = 0;
        const auto empty = renderViews(vertical, 0, false);
        for (uint32_t view = 0; view < 2; ++view) {
            require(changedInView(bodies, empty, vertical, view) > 50,
                "A player did not receive its sun/glow or moon/star reflection payload");
            fillCelestial(view, stars);
        }
        require(renderViews(vertical, 0, false, true) == bodies,
            "Celestial reflection changed with draw order or course reentry");
        // P2's own projector looks away. Its reflection must clear while P1
        // remains identical; no per-view draw/submit wait is added to the test.
        views[1].params.celestialProjection[0][1] += 1000;
        const auto away = renderViews(vertical, 0, false);
        compareView(away, bodies, vertical, 0, "P2 celestial projection changed P1");
        compareView(away, empty, vertical, 1, "P2 retained bodies outside its own chart");
        fillCelestial(1, stars);
        views[1].params.celestialInfo[0] = 0;
        const auto absent = renderViews(vertical, 0, false);
        compareView(absent, bodies, vertical, 0, "Empty P2 body list changed P1");
        compareView(absent, empty, vertical, 1, "Empty P2 body list retained old bodies");
    }
    for (uint32_t view = 0; view < 2; ++view) {
        views[view].params = beforeCelestial[view];
        for (uint32_t i = 4; i < 7; ++i) views[view].world[i][0] -= 1000;
    }
    require(pipelines.prepare(device.get(), layout.get(), ms, false),
        "Could not restore two-player stable pipeline after celestial checks");
    renderViews(false, 0, false);
    std::printf("Two-player %ux: independent sun/glow and18-body moon/star payloads, both splits, per-view look-away and course reset passed.\n", samples);
    std::printf("Two-player %ux: %zu single-submit presentations, each with both views prepared before recording.\n", samples, submissions);

    // Transfer the just-used, fenced resources into the actual renderer, then
    // execute its production per-presentation reset. No synthetic reset helper
    // stands in for clearing the second owner's stale draw/scene state.
    FramebufferRenderer renderer(&worker, false, graphicsAPI, &nativeLibrary);
    const RenderDescriptorSet *descriptorBefore[2] = {};
    RenderBuffer *paramsBefore[2] = {};
    const RenderAccelerationStructure *asBefore[2] = {};
    for (uint32_t view = 0; view < 2; ++view) {
        renderer.wr64RTViews[view] = std::move(views[view].rt);
        auto &rt = renderer.wr64RTViews[view];
        descriptorBefore[view] = rt.descriptor->get();
        paramsBefore[view] = rt.paramsBuffer.get();
        asBefore[view] = rt.scene.accelerationStructure();
        require(rt.prepared && rt.scene.prepared() && asBefore[view], "Lifecycle source view was not prepared");
        rt.projection = view + 5;
        rt.nativeRaceView = view + 1;
        rt.framebuffer = 3;
        rt.scopeSeen = rt.skyScopeSeen = true;
        rt.waterDraws = {view + 1};
        rt.nativeWaterPipelines = {nativePipeline.get()};
        rt.shoreDraws = {view + 3};
        rt.nativeShorePipelines = {nativePipeline.get()};
        rt.geometry = {{6, 3, 1}};
        rt.waterIndices = {0, 1, 2};
    }
    renderer.wr64RTDrawViews = {1, 2, 1, 0};
    renderer.resetFramebuffers(&worker, false, 1.0f, ms);
    require(renderer.wr64RTDrawViews.empty(), "Production reset retained per-draw view ownership");
    for (uint32_t view = 0; view < 2; ++view) {
        auto &rt = renderer.wr64RTViews[view];
        require(!rt.prepared && !rt.scopeSeen && !rt.skyScopeSeen && !rt.params.enabled &&
            rt.projection == UINT32_MAX && rt.framebuffer == UINT32_MAX && rt.nativeRaceView == 0,
            "Production reset retained active state in one view");
        require(!rt.scene.prepared() && !rt.scene.buildRecorded() && !rt.scene.accelerationStructure() &&
            rt.waterDraws.empty() && rt.nativeWaterPipelines.empty() && rt.shoreDraws.empty() &&
            rt.nativeShorePipelines.empty() && rt.geometry.empty() && rt.waterIndices.empty(),
            "Production reset retained classified geometry or fallback draws");
        require(rt.descriptor->get() == descriptorBefore[view] && rt.paramsBuffer.get() == paramsBefore[view],
            "Production reset discarded the fenced per-view resource owner");
        require(rt.scene.prepare(device.get(), views[view].positions.get(), faces.get(), 14, 27, {{6, 3, 1}}),
            "A cleared scene could not prepare its next presentation");
        require(rt.scene.accelerationStructure() == asBefore[view], "Scene reset discarded reusable AS allocations");
    }
    require(descriptorBefore[0] != descriptorBefore[1] && paramsBefore[0] != paramsBefore[1] && asBefore[0] != asBefore[1],
        "Production reset conflated the two retained GPU owners");
    std::printf("Two-player %ux: actual FramebufferRenderer::resetFramebuffers clears both views and preserves separate reusable allocations.\n", samples);
}
