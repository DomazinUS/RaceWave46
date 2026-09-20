// Included only in the --sky-methods-only fixture. The extra opt-in keeps the
// existing sky-method and default RT regression runs unchanged.
if (selected("--raster-shadow-combinations")) {
    const Params savedReflection = reflection;
    const RenderPipeline *savedOverride = pipelineOverride;
    require(reflection.shadowOptions[0] == 0, "Shadow combinations require the original RT shadow effect disabled");
    Wr64RasterShadowParams mappedShadow{};
    // Explicit synthetic map projection, separate from production camera math:
    // water x/z in [-5,5] occupies the central half of the map, at depth .5.
    mappedShadow.lightRows[0][0] = .1f;
    mappedShadow.lightRows[1][2] = .1f;
    mappedShadow.lightRows[2][1] = -.01f;
    mappedShadow.lightRows[2][3] = .5f;
    mappedShadow.lightRows[3][3] = 1;
    mappedShadow.options[0] = 1.f / 1024;
    mappedShadow.options[1] = .001f;
    mappedShadow.options[2] = .18f;
    mappedShadow.light[1] = 1;
    auto mappedShadowBuffer = device->createBuffer(RenderBufferDesc::UploadBuffer(256, RenderBufferFlag::CONSTANT));
    require(mappedShadowBuffer != nullptr, "Combined shadow constant buffer allocation failed");
    common.setBuffer(common.wr64RasterShadowParams, mappedShadowBuffer.get(), sizeof(mappedShadow));
    Wr64RasterShadowTarget mappedTarget;
    require(mappedTarget.ensure(&worker), "Combined shadow target allocation failed");
    common.setTexture(common.wr64RasterShadowMap, mappedTarget.color(), RenderTextureLayout::SHADER_READ);
    worker.commandList->begin();
    const RenderTextureBarrier mapTargets[] = {
        {mappedTarget.color(), RenderTextureLayout::COLOR_WRITE},
        {mappedTarget.depth(), RenderTextureLayout::DEPTH_WRITE}
    };
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS, nullptr, 0, mapTargets, 2);
    worker.commandList->setFramebuffer(mappedTarget.framebuffer());
    // Constant near occluder isolates composition compatibility. Actual caster
    // capture/depth ordering is exercised by the separate no-AS shadow fixture.
    worker.commandList->clearColor(0, RenderColor(0, 0, 0, 0));
    worker.commandList->clearDepth(true, 1.f);
    worker.commandList->setFramebuffer(nullptr);
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS,
        RenderTextureBarrier(mappedTarget.color(), RenderTextureLayout::SHADER_READ));
    worker.commandList->end(); worker.execute(); worker.wait();

    struct ShadowCombination {
        Wr64RasterShadowWaterMode mode;
        const char *name;
        const RenderPipeline *reference;
    };
    const ShadowCombination combinations[] = {
        {Wr64RasterShadowWaterMode::RasterSky, "raster-sky", rasterPipelines.get(false, false, false)},
        {Wr64RasterShadowWaterMode::RTObjects, "RT-objects", pipelines.get(false, false, false)},
        {Wr64RasterShadowWaterMode::RTSky, "RT-objects-and-sky", fullSkyPipelines.get(false, false, false)},
        {Wr64RasterShadowWaterMode::RTObjectsRasterSky, "RT-objects-raster-sky", mixedPipelines.get(false, false, false)},
        {Wr64RasterShadowWaterMode::RTSkyOnly, "RT-sky-only", skyOnlyPipelines.get(false, false, false)}
    };
    Wr64RasterShadowPipelines combinationPipelines;
    size_t compatiblePasses = 0, attenuatedPixels = 0;
    for (const auto &combination : combinations) {
        require(combination.reference != nullptr, "Original combination reference PSO is missing");
        require(combinationPipelines.prepare(device.get(), layout.get(), ms, false, true, combination.mode),
            "Combined raster-shadow water PSO preparation failed");
        const auto *wrapped = awaitAsyncPipeline(combination.name, [&]() {
            return combinationPipelines.getWater(combination.mode, false, false, false);
        });
        for (uint32_t view = 0; view < 2; ++view) {
            selectView(view);
            const auto reference = methodWater(combination.reference);
            mappedShadow.light[3] = 0; mappedShadow.options[2] = .18f;
            fill(mappedShadowBuffer.get(), &mappedShadow, sizeof(mappedShadow));
            require(methodWater(wrapped) == reference, "Disabled mapped shadow changed an original reflection method");
            ++compatiblePasses;
            mappedShadow.light[3] = 1; mappedShadow.options[2] = 0;
            fill(mappedShadowBuffer.get(), &mappedShadow, sizeof(mappedShadow));
            require(methodWater(wrapped) == reference, "Zero-strength mapped shadow changed an original reflection method");
            ++compatiblePasses;
            mappedShadow.options[2] = .18f;
            fill(mappedShadowBuffer.get(), &mappedShadow, sizeof(mappedShadow));
            const auto shadowed = methodWater(wrapped);
            size_t changed = 0;
            for (size_t pixel = 0; pixel < size_t(Width) * Height; ++pixel) {
                const size_t p = pixel * 4;
                bool darker = false;
                for (size_t channel = 0; channel < 3; ++channel) {
                    require(int(shadowed[p + channel]) <= int(reference[p + channel]) + 1,
                        "Mapped water shadow brightened an existing reflection method");
                    darker |= int(reference[p + channel]) - int(shadowed[p + channel]) >= 2;
                }
                require(shadowed[p + 3] == reference[p + 3], "Combined mapped shadow changed native coverage");
                changed += darker ? 1 : 0;
            }
            require(changed > size_t(Width) * Height / 2, "Mapped shadow had no substantial visible effect with this reflection method");
            attenuatedPixels += changed;
            require(methodWater(wrapped) == shadowed, "Repeated combined shadow draw changed its pixels");
            mappedShadow.light[3] = 0;
            fill(mappedShadowBuffer.get(), &mappedShadow, sizeof(mappedShadow));
            require(methodWater(wrapped) == reference, "Disabling mapped shadows failed exact reflection restoration");
            ++compatiblePasses;
            std::printf("Raster-shadow combination %ux %s view%u: exact disabled/zero-strength/restored output; %zu attenuated pixels.\n",
                samples, combination.name, view, changed);
        }
    }
    combinationPipelines.waitForPending();
    reflection = savedReflection; pipelineOverride = savedOverride;
    fill(reflectionBuffer, &reflection, sizeof(reflection));
    std::printf("Raster-shadow combinations %ux: five reflection methods, %zu exact compatibility passes, %zu attenuated pixels across two views.\n",
        samples, compatiblePasses, attenuatedPixels);
}
