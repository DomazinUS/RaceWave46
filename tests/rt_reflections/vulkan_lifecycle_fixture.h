// Mirrors FramebufferRenderer's stable/sky/world startup prewarm collection.
// A poll queues all fixed-state PSOs, and the layout remains alive until every
// compiler worker completes. No game workload is submitted during this phase.
void prewarmLifecyclePipelines(FixtureWaterPipelines &water, FixtureWorldPipelines &world,
    RenderDevice *device, const RenderPipelineLayout *layout, const RenderMultisampling &ms,
    uint32_t generation) {
    const auto start = std::chrono::steady_clock::now();
    size_t polls = 0;
    for (;;) {
        bool pending = false;
        auto collect = [&](Wr64RTPrewarmStatus status) {
            if (status == Wr64RTPrewarmStatus::Failed) throw std::runtime_error("Lifecycle prewarm reported a failed production PSO");
            pending |= status == Wr64RTPrewarmStatus::Pending;
        };
        for (bool sky : {false, true}) {
            if (!water.prepare(device, layout, ms, false, sky, true)) throw std::runtime_error("Lifecycle water prewarm configuration failed");
            collect(water.prewarm());
        }
        if (!world.prepare(device, layout, ms, false, true)) throw std::runtime_error("Lifecycle world prewarm configuration failed");
        collect(world.prewarm());
        ++polls;
        if (!pending) break;
        if (std::chrono::steady_clock::now() - start > std::chrono::seconds(120))
            throw std::runtime_error("Lifecycle production prewarm exceeded 120 seconds");
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    water.waitForPending();
    world.waitForPending();
    std::printf("Lifecycle generation%u: %ux stable/sky/world prewarm ready before draw; polls%zu elapsed_ms%.3f\n",
        generation, ms.sampleCount, polls,
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count());
}
