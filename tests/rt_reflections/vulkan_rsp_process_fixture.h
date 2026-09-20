// Included inside the headless fixture namespace. This is RSPProcess, the
// production screen-position/color/UV producer, rather than just RSPWorld.
extern "C" {
    extern const char RSPProcessCSBlobSPIRV[];
    extern const size_t RSPProcessCSBlobSPIRV_size;
}

void verifyVulkanRSPProcess(RenderDevice *device, FixtureWorker &worker, VulkanValidation &validation) {
    constexpr uint32_t Count = 16, Records = 260;
    struct Viewport { float scale[3], translate[3]; };
    struct Fog { float mul, offset; };
    struct Light { float dir[3], color[3], colorCopy[3]; uint32_t kc, kl, kq; };
    struct LookAt { float x[3], y[3]; };
    struct Input {
        std::unique_ptr<RenderBuffer> upload, buffer;
        std::unique_ptr<RenderBufferFormattedView> view;
        size_t bytes;
    };
    RSPProcessDescriptorSet descriptors(device);
    std::vector<Input> inputs;
    inputs.reserve(26);
    auto input = [&](uint32_t binding, const void *data, size_t bytes, RenderFormat format, uint32_t stride = 0) {
        Input value;
        value.bytes = bytes;
        value.upload = device->createBuffer(RenderBufferDesc::UploadBuffer(bytes));
        value.buffer = device->createBuffer(RenderBufferDesc::DefaultBuffer(bytes,
            format == RenderFormat::UNKNOWN ? RenderBufferFlag::STORAGE : RenderBufferFlag::FORMATTED));
        fill(value.upload.get(), data, bytes);
        if (format != RenderFormat::UNKNOWN) {
            value.view = value.buffer->createBufferFormattedView(format);
            descriptors.setBuffer(binding, value.buffer.get(), bytes, value.view.get());
        }
        else descriptors.setBuffer(binding, value.buffer.get(), RenderBufferStructuredView(stride));
        inputs.push_back(std::move(value));
    };
    std::array<float, Count * 3> positions{}, velocities{};
    std::array<float, Count * 2> texcoords{}, tcVelocities{};
    std::array<uint8_t, Count * 4> colors{};
    std::array<uint16_t, Count> viewIndices{}, worldIndices{}, fogIndices{}, lightIndices{}, lookIndices{};
    std::array<uint8_t, Count> lightCounts{};
    std::array<Viewport, Records> viewports{};
    std::array<Fog, Records> fogs{};
    std::array<Light, Records> lights{};
    std::array<LookAt, Records> lookAts{};
    std::array<std::array<float, 16>, Records> views{}, worlds{};
    for (uint32_t r = 0; r < Records; ++r) {
        views[r] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
        worlds[r] = views[r];
        viewports[r] = {{1,1,1},{0,0,0}};
    }
    views[257][0] = views[257][5] = views[257][10] = .5f;
    worlds[1][0] = 2;
    worlds[258][0] = 3;
    worlds[1][5] = worlds[258][5] = 1.5f;
    viewports[257] = {{100,200,1},{10,20,0}};
    fogs[257] = {51,25.5f};
    lights[257] = {{-1,0,0},{.5f,.25f,.125f},{},0,0,0};
    lights[258] = {{0,0,0},{.1f,.2f,.3f},{},0,0,0};
    lookAts[257] = {{1,0,0},{0,1,0}};
    for (uint32_t i = 0; i < Count; ++i) {
        positions[i * 3] = .05f * (int(i) - 8);
        positions[i * 3 + 1] = .02f * i;
        positions[i * 3 + 2] = .3f + .01f * i;
        velocities[i * 3] = .02f;
        velocities[i * 3 + 1] = -.01f;
        velocities[i * 3 + 2] = .005f;
        // Stay away from acos' singular +/-1 endpoints so the independent CPU
        // texgen oracle tests typed inputs, not implementation-specific rounding.
        colors[i * 4] = uint8_t(i & 1 ? -96 : 96);
        colors[i * 4 + 1] = 64;
        colors[i * 4 + 2] = uint8_t(-32);
        colors[i * 4 + 3] = uint8_t(129 + i * 7);
        viewIndices[i] = i & 1 ? 257 : 0;
        worldIndices[i] = i & 2 ? 258 : 1;
        fogIndices[i] = i & 4 ? 258 : 0;
        lightIndices[i] = 257;
        lightCounts[i] = i & 2 ? 2 : 0;
        lookIndices[i] = i & 4 ? uint16_t((257 << 2) | (i & 8 ? 3 : 1)) : 0;
        texcoords[i * 2] = i & 4 ? 65536.f : .25f * i;
        texcoords[i * 2 + 1] = i & 4 ? 32768.f : -.125f * i;
        tcVelocities[i * 2] = .125f;
        tcVelocities[i * 2 + 1] = -.25f;
    }
    input(descriptors.srcPos, positions.data(), sizeof(positions), RenderFormat::R32_FLOAT);
    input(descriptors.srcVel, velocities.data(), sizeof(velocities), RenderFormat::R32_FLOAT);
    input(descriptors.srcTc, texcoords.data(), sizeof(texcoords), RenderFormat::R32_FLOAT);
    input(descriptors.srcTcVel, tcVelocities.data(), sizeof(tcVelocities), RenderFormat::R32_FLOAT);
    input(descriptors.srcCol, colors.data(), sizeof(colors), RenderFormat::R8_UINT);
    auto normalView = inputs.back().buffer->createBufferFormattedView(RenderFormat::R8_SINT);
    descriptors.setBuffer(descriptors.srcNorm, inputs.back().buffer.get(), sizeof(colors), normalView.get());
    input(descriptors.srcViewProjIndices, viewIndices.data(), sizeof(viewIndices), RenderFormat::R16_UINT);
    input(descriptors.srcWorldIndices, worldIndices.data(), sizeof(worldIndices), RenderFormat::R16_UINT);
    input(descriptors.srcFogIndices, fogIndices.data(), sizeof(fogIndices), RenderFormat::R16_UINT);
    input(descriptors.srcLightIndices, lightIndices.data(), sizeof(lightIndices), RenderFormat::R16_UINT);
    input(descriptors.srcLightCounts, lightCounts.data(), sizeof(lightCounts), RenderFormat::R8_UINT);
    input(descriptors.srcLookAtIndices, lookIndices.data(), sizeof(lookIndices), RenderFormat::R16_UINT);
    input(descriptors.rspViewportVector, viewports.data(), sizeof(viewports), RenderFormat::UNKNOWN, sizeof(Viewport));
    input(descriptors.rspFogVector, fogs.data(), sizeof(fogs), RenderFormat::UNKNOWN, sizeof(Fog));
    input(descriptors.rspLightVector, lights.data(), sizeof(lights), RenderFormat::UNKNOWN, sizeof(Light));
    input(descriptors.rspLookAtVector, lookAts.data(), sizeof(lookAts), RenderFormat::UNKNOWN, sizeof(LookAt));
    input(descriptors.viewProjTransforms, views.data(), sizeof(views), RenderFormat::UNKNOWN, sizeof(views[0]));
    input(descriptors.worldTransforms, worlds.data(), sizeof(worlds), RenderFormat::UNKNOWN, sizeof(worlds[0]));
    const std::array<uint32_t, Count * 4> fieldInfo{};
    const std::array<float, Count * 4> fields{};
    const uint32_t faceIndex = 0;
    input(descriptors.wr64WaterFieldInfo, fieldInfo.data(), sizeof(fieldInfo), RenderFormat::UNKNOWN, 16);
    input(descriptors.wr64WaterFieldPrevPosShiftX, fields.data(), sizeof(fields), RenderFormat::UNKNOWN, 16);
    input(descriptors.wr64WaterFieldPrevTcShiftZ, fields.data(), sizeof(fields), RenderFormat::UNKNOWN, 16);
    input(descriptors.wr64WaterFieldFaceIndices, &faceIndex, sizeof(faceIndex), RenderFormat::UNKNOWN, 4);
    const uint32_t outputBindings[] = {descriptors.dstPos, descriptors.dstTc, descriptors.dstCol};
    const uint32_t outputComponents[] = {4, 2, 4};
    std::array<std::unique_ptr<RenderBuffer>, 3> outputs, readbacks;
    for (uint32_t i = 0; i < 3; ++i) {
        const uint32_t stride = outputComponents[i] * sizeof(float), bytes = Count * stride;
        outputs[i] = device->createBuffer(RenderBufferDesc::DefaultBuffer(bytes, RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS));
        readbacks[i] = device->createBuffer(RenderBufferDesc::ReadbackBuffer(bytes));
        descriptors.setBuffer(outputBindings[i], outputs[i].get(), RenderBufferStructuredView(stride));
    }
    struct Constants { uint32_t start, count; float previous, current; } constants{0, Count, 0, 1};
    RenderPipelineLayoutBuilder builder;
    builder.begin();
    builder.addPushConstant(0, 0, sizeof(constants), RenderShaderStageFlag::COMPUTE);
    builder.addDescriptorSet(descriptors);
    builder.end();
    auto layout = builder.create(device);
    auto shader = device->createShader(RSPProcessCSBlobSPIRV, RSPProcessCSBlobSPIRV_size, "CSMain", RenderShaderFormat::SPIRV);
    auto pipeline = device->createComputePipeline(RenderComputePipelineDesc(layout.get(), shader.get(), 64, 1, 1));
    require(pipeline && static_cast<VulkanComputePipeline *>(pipeline.get())->vk, "Actual RSPProcess pipeline creation failed");
    require(validation.errors == 0 && validation.warnings == 0, "RSPProcess pipeline creation emitted validation messages");
    for (float weight : {0.f, .5f, 1.f}) {
        constants.current = weight;
        constants.previous = 1 - weight;
        worker.commandList->begin();
        std::vector<RenderBufferBarrier> barriers;
        for (auto &value : inputs) barriers.emplace_back(value.buffer.get(), RenderBufferAccess::WRITE);
        worker.commandList->barriers(RenderBarrierStage::COPY, barriers);
        for (auto &value : inputs) worker.commandList->copyBufferRegion(value.buffer->at(0), value.upload->at(0), value.bytes);
        for (auto &value : barriers) value.accessBits = RenderBufferAccess::READ;
        for (auto &value : outputs) barriers.emplace_back(value.get(), RenderBufferAccess::WRITE);
        worker.commandList->barriers(RenderBarrierStage::COMPUTE, barriers);
        worker.commandList->setComputePipelineLayout(layout.get());
        worker.commandList->setPipeline(pipeline.get());
        worker.commandList->setComputePushConstants(0, &constants);
        worker.commandList->setComputeDescriptorSet(descriptors.get(), 0);
        worker.commandList->dispatch(1, 1, 1);
        require(validation.errors == 0 && validation.warnings == 0, "RSPProcess descriptors failed validation; no commands submitted");
        for (uint32_t i = 0; i < 3; ++i) {
            worker.commandList->barriers(RenderBarrierStage::COPY, RenderBufferBarrier(outputs[i].get(), RenderBufferAccess::READ));
            worker.commandList->copyBufferRegion(readbacks[i]->at(0), outputs[i]->at(0), Count * outputComponents[i] * sizeof(float));
        }
        worker.commandList->end();
        require(validation.errors == 0 && validation.warnings == 0, "RSPProcess command recording failed validation");
        worker.execute();
        worker.wait();
        require(validation.errors == 0 && validation.warnings == 0, "RSPProcess execution emitted validation messages");
        for (uint32_t output = 0; output < 3; ++output) {
            const RenderRange read(0, Count * outputComponents[output] * sizeof(float)), noWrite(0, 0);
            const auto *actual = static_cast<const float *>(readbacks[output]->map(0, &read));
            require(actual, "RSPProcess output map failed");
            for (uint32_t i = 0; i < Count; ++i) {
                const auto &vp = viewports[viewIndices[i]];
                const float viewScale = i & 1 ? .5f : 1.f;
                const float worldScale[3] = {i & 2 ? 3.f : 2.f, 1.5f, 1.f};
                float transformed[3];
                for (uint32_t c = 0; c < 3; ++c) transformed[c] = (positions[i * 3 + c] - velocities[i * 3 + c] * (1 - weight)) * worldScale[c] * viewScale;
                float expected[4]{};
                if (output == 0) {
                    for (uint32_t c = 0; c < 3; ++c) expected[c] = transformed[c] * (c == 1 ? -1 : 1) * vp.scale[c] + vp.translate[c];
                    expected[3] = 1;
                }
                else if (output == 1) {
                    if (i & 4) {
                        const float normals[2] = {float(i & 1 ? -96 : 96) / 127.f, 64.f / 127.f};
                        for (uint32_t c = 0; c < 2; ++c) {
                            const float generated = i & 8 ? std::acos(-normals[c]) * 325.94932f : (normals[c] + 1) * 512;
                            expected[c] = texcoords[i * 2 + c] / 65536 * generated;
                        }
                    }
                    else for (uint32_t c = 0; c < 2; ++c) expected[c] = texcoords[i * 2 + c] - tcVelocities[i * 2 + c] * (1 - weight);
                }
                else {
                    for (uint32_t c = 0; c < 3; ++c) expected[c] = i & 2 ? lights[258].color[c] + (i & 1 ? (96.f / 127.f) * lights[257].color[c] : 0) : colors[i * 4 + c] / 255.f;
                    expected[3] = i & 4 ? (std::max(transformed[2], 0.f) * 51 + 25.5f) / 255 : colors[i * 4 + 3] / 255.f;
                }
                for (uint32_t c = 0; c < outputComponents[output]; ++c) {
                    const float value = actual[i * outputComponents[output] + c];
                    if (!std::isfinite(value) || std::abs(value - expected[c]) > 0.0002f)
                        std::fprintf(stderr, "RSP mismatch output=%u vertex=%u component=%u weight=%.2f got=%.9f expected=%.9f\n", output, i, c, weight, value, expected[c]);
                    require(std::isfinite(value) && std::abs(value - expected[c]) <= 0.0002f, "RSPProcess output disagrees with initialized native inputs");
                }
            }
            readbacks[output]->unmap(0, &noWrite);
        }
        std::printf("RSPProcess weight=%.1f: 16 positions/colors/UVs, unsigned and signed byte views, 16-bit indices above255, fog/light/texgen passed\n", weight);
    }
}
