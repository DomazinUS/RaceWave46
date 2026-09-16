//
// RT64
//

#include "../../../../include/wr64_diagnostic_policy.h"

#include "rt64_present_queue.h"
#include "wr64_forensic.h"

#include "common/rt64_thread.h"
#include "common/rt64_wr64_stall_probe.h"
#include "common/rt64_wr64_frametime_probe.h"
#include "common/rt64_wr64_present_meter.h"
#include "common/rt64_wr64_present_pacing.h"
#include "common/rt64_wr64_frame_pacing_diagnostic.h"
#include "common/rt64_wr64_ultrawide.h"
#include "common/rt64_wr64_cpu_logo.h"
#include "common/rt64_wr64_separate_windows.h"
#include "rhi/rt64_render_hooks.h"

#include <atomic>
#include <chrono>
#include <cstdlib>

#include "rt64_workload_queue.h"
#include "rt64_wr64_cadence_trace.h"

namespace RT64 {
    // THE DRAIN'S TWO CONSTANTS. Kept here, next to the only code that reads
    // them, rather than in a header nothing else includes.
    //
    // ONE FRAME. The drain rate does not change how much motion is given up to
    // recover a slot of phase - that is fixed at one batch's worth by the
    // arithmetic - it only changes how concentrated it is. One frame is the
    // smallest step available: a single duplicated frame at the target rate,
    // 11.1 ms of hold instead of 5.6. Two would clear a backlog in half the
    // time and double the step, and the time saved is a quarter of a second on
    // an event that happens about once per race, so it buys nothing worth the
    // visibility.
    // [WR64] Was the PREVIOUS present event interpolated?
//
// Read and written only on the present thread, so a plain bool is enough - the
// skip decision below and threadPresent that sets it are the same thread.
//
// It has to be the previous event because the skip decision is taken under the
// cursor lock, before threadPresent runs the framebuffer scan that decides
// whether interpolation is possible for THIS event. One event of lag is fine:
// a dropout lasts several events, so the very first one presents normally - one
// frame, harmless - and every one after it is handled.
//
// Starts true so the first present of a session behaves exactly as before.
static bool wr64PrevPresentInterpolated = true;

static constexpr int32_t Wr64PresentDrainFrames = 1;

    // AND A FLOOR, so a short batch is never touched. At one there is nothing
    // to give up; at two, giving one up would halve the period rather than
    // shave it, which is a step the size of the bug this replaces.
    static constexpr int32_t Wr64PresentDrainFloor = 2;

    // PresentQueue

    PresentQueue::PresentQueue() {
        reset();
    }

    PresentQueue::~PresentQueue() {
        presentThreadRunning = false;
        cursorCondition.notify_all();

        if (presentThread != nullptr) {
            presentThread->join();
            delete presentThread;
        }

        presentIdCondition.notify_all();
    }

    void PresentQueue::reset() {
        threadCursor = 0;
        writeCursor = 0;
        barrierCursor = 0;
        presentId = 0;
    }

    void PresentQueue::advanceToNextPresent() {
        int nextWriteCursor = (writeCursor + 1) % presents.size();

        // Stall the thread until the barrier is lifted if we're trying to write on a present being used by the GPU.
        bool waitForBarrier;
        do {
            const std::scoped_lock lock(cursorMutex);
            waitForBarrier = (nextWriteCursor == barrierCursor);
        } while (waitForBarrier);

        // Modify the cursor and notify anything waiting on the queue.
        {
            const std::scoped_lock lock(cursorMutex);
            writeCursor = nextWriteCursor;
        }

        cursorCondition.notify_all();
    }

    void PresentQueue::repeatLastPresent() {
        {
            const std::scoped_lock lock(cursorMutex);
            threadCursor = previousWriteCursor();
        }

        cursorCondition.notify_all();
    }

    uint32_t PresentQueue::previousWriteCursor() const {
        if (writeCursor > 0) {
            return writeCursor - 1;
        }
        else {
            return uint32_t(presents.size()) - 1;
        }
    }

    void PresentQueue::waitForIdle() {
        std::unique_lock<std::mutex> threadLock(threadMutex);
    }

    void PresentQueue::waitForPresentId(uint64_t waitId) {
        std::unique_lock<std::mutex> presentLock(presentIdMutex);
        presentIdCondition.wait(presentLock, [&]() {
            return (waitId <= presentId) || !presentThreadRunning;
        });
    }

    void PresentQueue::setup(const External &ext) {
        this->ext = ext;

        viRenderer = std::make_unique<VIRenderer>();

        presentThreadRunning = true;
        presentThread = new std::thread(&PresentQueue::threadLoop, this);
    }

    void PresentQueue::releaseSecondaryOutput() {
        // Called only on the present thread, after completed command-list use.
        // Drop descriptor/framebuffer references before releasing DXGI images.
        secondaryViRenderer.reset();
        secondaryFramebuffers.clear();
        secondaryDrawSemaphores.clear();
        secondaryAcquiredSemaphore.reset();
        secondarySwapChain.reset();
        secondaryWindowHandle = 0;
        secondarySwapChainValid = false;
        secondaryRetryBlocked = false;
    }

    bool PresentQueue::prepareSecondaryOutput(bool displayedRace) {
#ifdef _WIN32
        const uintptr_t handle = wr64SecondaryWindowHandle.load(std::memory_order_acquire);
        const bool backend = ext.createdGraphicsAPI == UserConfiguration::GraphicsAPI::D3D12 &&
            wr64SeparateWindowsBackend.load(std::memory_order_acquire);
        if (!backend || handle == 0) {
            releaseSecondaryOutput();
            return false;
        }
        if (secondaryWindowHandle != handle) {
            releaseSecondaryOutput();
            secondaryWindowHandle = handle;
        }
        if (wr64SecondaryWindowClosed.load(std::memory_order_acquire)) {
            // The host hides, but retains, this HWND. Reopening can reuse its
            // swapchain; closing it must immediately restore both primary views.
            secondaryRetryBlocked = false;
            return false;
        }
        if (!displayedRace) secondaryRetryBlocked = false;
        const bool drawable = wr64SecondaryWindowDrawable.load(std::memory_order_acquire);
        if (!secondarySwapChain) {
            // Menus do not create a second output. A creation failure is latched
            // until another race/close/backend transition, not retried per frame.
            if (!displayedRace || !drawable || secondaryRetryBlocked) return false;
            RenderSwapChainDesc desc;
            desc.renderWindow = reinterpret_cast<RenderWindow>(handle);
            desc.format = RenderFormat::B8G8R8A8_UNORM;
            desc.textureCount = 3;
            desc.enablePresentWait = false;
            desc.maxFrameLatency = 1;
            secondarySwapChain = ext.presentGraphicsWorker->commandQueue->createSwapChain(desc);
            if (!secondarySwapChain || secondarySwapChain->isEmpty()) {
                releaseSecondaryOutput();
                secondaryWindowHandle = handle;
                secondaryRetryBlocked = true;
                return false;
            }
            secondarySwapChain->setVsyncEnabled(false);
            secondaryAcquiredSemaphore = ext.device->createCommandSemaphore();
            secondaryViRenderer = std::make_unique<VIRenderer>();
            secondarySwapChainValid = true;
        }
        if (!secondarySwapChainValid) {
            releaseSecondaryOutput();
            secondaryWindowHandle = handle;
            secondaryRetryBlocked = displayedRace;
            return false;
        }
        // Minimize never acquires/resizes the secondary chain and never waits
        // for that monitor. The primary continues showing Player 1.
        if (!drawable) return true;
        if (secondarySwapChain->needsResize()) {
            // Flush retained command-list references before rebuilding images.
            ext.presentGraphicsWorker->commandList->begin();
            ext.presentGraphicsWorker->commandList->end();
            ext.presentGraphicsWorker->execute();
            ext.presentGraphicsWorker->wait();
            secondaryFramebuffers.clear();
            secondarySwapChainValid = secondarySwapChain->resize();
            if (!secondarySwapChainValid) return false;
        }
        const uint32_t count = secondarySwapChain->getTextureCount();
        if (secondaryFramebuffers.empty()) {
            for (uint32_t i = 0; i < count; ++i) {
                const RenderTexture *texture = secondarySwapChain->getTexture(i);
                secondaryFramebuffers.emplace_back(ext.device->createFramebuffer(RenderFramebufferDesc(&texture, 1)));
            }
        }
        while (secondaryDrawSemaphores.size() < count)
            secondaryDrawSemaphores.emplace_back(ext.device->createCommandSemaphore());
        return !secondarySwapChain->isEmpty();
#else
        releaseSecondaryOutput();
        return false;
#endif
    }

    void PresentQueue::threadPresent(const Present &present, bool &swapChainValid, int pendingPresents) {
        FramebufferManager &fbManager = ext.sharedResources->framebufferManager;
        RenderTargetManager &targetManager = ext.sharedResources->renderTargetManager;
        const bool usingMSAA = (targetManager.multisampling.sampleCount > 1);
        hlslpp::float2 resolutionScale;
        EnhancementConfiguration::Presentation::Mode presentationMode;
        bool removeBlackBorders;
        UserConfiguration::RefreshRate refreshRate;
        UserConfiguration::Filtering filtering;
        bool wr64ExpandAspect;
        uint32_t viOriginalRate;
        uint32_t targetRate;
        uint32_t swapChainRate;
        {
            std::scoped_lock<std::mutex> configurationLock(ext.sharedResources->configurationMutex);
            resolutionScale = ext.sharedResources->resolutionScale;
            presentationMode = ext.sharedResources->enhancementConfig.presentation.mode;
            removeBlackBorders = ext.sharedResources->enhancementConfig.presentation.removeBlackBorders;
            refreshRate = ext.sharedResources->userConfig.refreshRate;
            filtering = ext.sharedResources->userConfig.filtering;
            wr64ExpandAspect = ext.sharedResources->userConfig.aspectRatio != UserConfiguration::AspectRatio::Original;
            viOriginalRate = ext.sharedResources->viOriginalRate;
            targetRate = ext.sharedResources->targetRate;
            swapChainRate = ext.sharedResources->swapChainRate;
        }

        RenderTarget *colorTarget = nullptr;
        bool scratchColorTarget = false;
        int32_t framesToPresent = 1;
        bool lockedWorkloadMutex = false;
        InterpolatedFrameCounters &frameCounters = ext.sharedResources->interpolatedFrames[ext.sharedResources->interpolatedFramesIndex];
        uint32_t tracePresentFbAddress = 0;
        uint32_t tracePresentFbWidth = 0;
        uint32_t tracePresentFbSiz = 0;
        bool tracePresentFbModified = false;
        bool tracePresentFbInterpolationEnabled = false;
        int32_t traceFramesToPresentInitial = 1;
        int32_t tracePresentLoopIterations = 0;
        int32_t traceSubmittedFrames = 0;

        // [WR64] Fail safe. The real value is written further down, once the
        // framebuffer scan has decided. Defaulting to true here means any path
        // that never reaches that point - no visible VI, no framebuffer - leaves
        // the skip decision exactly as R3 wrote it, rather than latching the
        // extra skip on a stale false.
        wr64PrevPresentInterpolated = true;

        // PRESENT METER. Plain locals, deliberately: the loop below runs at the
        // display rate and nothing in the meter is called from inside it. No
        // mutex, no function call, two clock readings per interpolated frame and
        // only when the meter is armed. The totals are handed over once, at the
        // end of this function.
        const bool wr64PmArmed = wr64PresentMeterArmed();
        // The R7 framebuffer scan's own counters, mirrored out to function scope
        // so the row can say WHY a present event went flat and not only that it
        // did. They stay zero when the scan never ran, which is itself an answer.
        uint32_t wr64PmScanFired = 0;
        uint32_t wr64PmScanWalked = 0;
        uint32_t wr64PmScanSize = 0;
        uint32_t wr64PmViAddress = 0;
        int64_t wr64PmFrameWaitUs = 0;
        int64_t wr64PmFirstFrameWaitUs = 0;
        uint32_t wr64PmFrameWaits = 0;
        uint32_t wr64PmFrameWaitsBlocked = 0;
        std::chrono::steady_clock::time_point wr64PmWaitStart{};
        bool wr64PmWaited = false;

        // Set when this batch gave up a frame to recover phase. Read in the loop
        // to complete the counter on the final iteration.
        bool wr64Draining = false;

        // TODO: There's a possible race condition interactions that can happen while the workload
        // queue is rendering extra frames and the present event is processed while it's generating
        // interpolated frames. When the framebuffer manager or the render target manager maps are
        // modified while the present queue is retrieving the framebuffer or the target. These can
        // likely be solved by locking the access to the managers during modification.
        
        // Perform any external write operations indicated by the event.
        if (!present.fbOperations.empty()) {
            const std::scoped_lock lock(screenFbChangePoolMutex);
            {
                RenderWorkerExecution workerExecution(ext.presentGraphicsWorker);
                fbManager.performOperations(ext.presentGraphicsWorker, &screenFbChangePool, nullptr, ext.shaderLibrary, nullptr,
                    present.fbOperations, targetManager, resolutionScale, 0, 0, nullptr);
            }
        }

        // Present the VI specified by the event.
        // Attempt to find the matching framebuffer for the VI based on the origin address.
        // If that fails, we look at the shared storage.
        if (present.screenVI.visible()) {
            Framebuffer *viFb = nullptr;
            if (!viewRDRAM) {
                viFb = fbManager.find(present.screenVI.fbAddress());
            }

            Framebuffer *presentFb = viFb;
            
            // Show the framebuffer the debugger has requested instead.
            if (present.debuggerFramebuffer.view) {
                Framebuffer *candidateFb = fbManager.find(present.debuggerFramebuffer.address);
                if (candidateFb != nullptr) {
                    presentFb = candidateFb;
                }
            }
            
            // R7 instrumentation. R6 established that the stutter is this loop
            // running to the end without ever taking the branch that switches
            // interpolation back on, which leaves every framebuffer flagged off and
            // makes the workload thread skip interpolation on the following native
            // frame. The counters below record what the loop actually saw, so the
            // reason is read out of the log rather than reasoned about: how many
            // addresses the workload published, how many of those this loop reached,
            // which addresses they were, and what address the video interface was
            // pointing at when it did not match any of them. Nothing here changes
            // what the loop does; every added statement is a counter or a store.
            uint32_t scanVectorSize = static_cast<uint32_t>(ext.sharedResources->colorImageAddressVector.size());
            uint32_t scanEntriesWalked = 0;
            uint32_t scanFbNull = 0;
            uint32_t scanCleared = 0;
            uint32_t scanSkipBufferingHit = 0;
            uint32_t scanFired = 0;
            uint32_t scanFiredIndex = 0;
            const uint32_t scanViAddress = present.screenVI.fbAddress();
            const uint32_t scanPresentAddress = (presentFb != nullptr) ? presentFb->addressStart : 0;
            uint32_t scanEntry[4] = { 0, 0, 0, 0 };

            if ((presentFb != nullptr) && (viFb != nullptr)) {
                for (uint32_t colorAddress : ext.sharedResources->colorImageAddressVector) {
                    // Recorded before anything can reject the address, so the list in
                    // the log is the list the loop was handed and not a filtered one.
                    if (scanEntriesWalked < 4) {
                        scanEntry[scanEntriesWalked] = colorAddress;
                    }

                    scanEntriesWalked++;

                    Framebuffer *colorFb = fbManager.find(colorAddress);
                    if (colorFb == nullptr) {
                        scanFbNull++;
                        continue;
                    }

                    // Always default to interpolation being disabled for all modified framebuffers.
                    colorFb->interpolationEnabled = false;
                    scanCleared++;
                    
                    // When the skip buffering option is on, we check the video history to find if any of the framebuffers that
                    // were drawn in this frame have been previously used for presentation. This is ignored when the debugger
                    // has forced viewing a particular framebuffer.
                    if (!present.debuggerFramebuffer.view && (presentationMode == EnhancementConfiguration::Presentation::Mode::SkipBuffering)) {
                        for (size_t h = 0; h < viHistory.history.size(); h++) {
                            const VIHistory::Present &entry = viHistory.history[h];
                            if ((colorFb->addressStart == entry.vi.fbAddress()) && (colorFb->width == entry.fbWidth) && (colorFb->siz == entry.vi.fbSiz()) && entry.vi.compatibleWith(present.screenVI)) {
                                presentFb = colorFb;
                                scanSkipBufferingHit++;
                                break;
                            }
                        }
                    }

                    // Present early (or games that behave like it) will make it so that the presented image is a color image
                    // that the workload modified. We run a basic check to see if that holds true to indicate it was presented
                    // so interpolation is possible.
                    if (colorFb == presentFb) {
                        tracePresentFbModified = true;
                        presentFb->interpolationEnabled = true;
                        // One based on purpose, so that zero unambiguously means the
                        // branch was never taken rather than meaning the first entry.
                        scanFired = 1;
                        scanFiredIndex = scanEntriesWalked;
                        break;
                    }
                }

                // R7. The loop closed on the line above and the workload mutex further
                // down has not been taken yet, so nothing is written to the log while a
                // lock is held. Present events arrive at the game's own twenty per
                // second, the same rate as the workload side counters R6 already
                // carries, so this costs what those cost.
                {
                    uint64_t scanDetail = 0;
                    scanDetail |= static_cast<uint64_t>(scanVectorSize & 0xFF);
                    scanDetail |= static_cast<uint64_t>(scanEntriesWalked & 0xFF) << 8;
                    scanDetail |= static_cast<uint64_t>(scanFbNull & 0xFF) << 16;
                    scanDetail |= static_cast<uint64_t>(scanCleared & 0xFF) << 24;
                    scanDetail |= static_cast<uint64_t>(scanSkipBufferingHit & 0xFF) << 32;
                    scanDetail |= static_cast<uint64_t>(scanFired & 0xFF) << 40;
                    scanDetail |= static_cast<uint64_t>(scanFiredIndex & 0xFF) << 48;

                    const uint64_t scanAddresses = (static_cast<uint64_t>(scanViAddress) << 32) | static_cast<uint64_t>(scanPresentAddress);
                    const uint64_t scanEntries01 = (static_cast<uint64_t>(scanEntry[0]) << 32) | static_cast<uint64_t>(scanEntry[1]);
                    const uint64_t scanEntries23 = (static_cast<uint64_t>(scanEntry[2]) << 32) | static_cast<uint64_t>(scanEntry[3]);
                    wr64StallProbeMarkEvent("present-fb-scan", scanDetail);
                    wr64StallProbeMarkEvent("present-fb-vi-drawn", scanAddresses);
                    wr64StallProbeMarkEvent("present-fb-entries-01", scanEntries01);
                    if (scanEntriesWalked > 2) {
                        wr64StallProbeMarkEvent("present-fb-entries-23", scanEntries23);
                    }

                    // The miss is the whole reason this build exists, so it is written
                    // out the moment it occurs together with the recent history behind
                    // it, rather than waiting and hoping that some later hitch reaches
                    // back far enough to include it. The four markers above are already
                    // in the ring at this point, so the dump carries them without
                    // repeating them.
                    //
                    // Every miss gets its one line, so the count in the log is the true
                    // count. Only the surrounding history is capped, because if misses
                    // turn out to be common rather than rare then dumping a few dozen
                    // lines of history behind every one of them would both bury the log
                    // and start costing enough time on this thread to change the very
                    // thing being measured. Forty windows is far more than needed to
                    // read the pattern.
                    if (scanFired == 0) {
                        static std::atomic<uint64_t> scanMissCounter(0);
                        const uint64_t scanMissIndex = scanMissCounter.fetch_add(1, std::memory_order_relaxed);
                        wr64StallProbeReport("present-fb-scan-miss", 0.0, scanDetail);

                        if (scanMissIndex < 40) {
                            wr64StallProbeDumpContext(wr64StallProbeNowMs());
                        }
                        else if (scanMissIndex == 40) {
                            wr64StallProbeReport("present-fb-scan-miss-history-capped", 0.0, scanMissIndex);
                        }
                    }
                }

                // PRESENT METER. Copied out while the scan's own locals are still
                // in scope. Reads only; the scan is R7's and is untouched.
                wr64PmScanFired = scanFired;
                wr64PmScanWalked = scanEntriesWalked;
                wr64PmScanSize = scanVectorSize;
                wr64PmViAddress = scanViAddress;

                tracePresentFbAddress = presentFb->addressStart;
                tracePresentFbWidth = presentFb->width;
                tracePresentFbSiz = presentFb->siz;
                tracePresentFbInterpolationEnabled = presentFb->interpolationEnabled;
                // [WR64] For the NEXT event's skip decision. See
                // wr64PrevPresentInterpolated.
                wr64PrevPresentInterpolated = presentFb->interpolationEnabled;
                if (presentFb->interpolationEnabled) {
                    framesToPresent = frameCounters.count;

                    // Recover accumulated phase gradually by presenting one fewer interpolated
                    // frame while a backlog remains. Skipping an entire native tick makes a much
                    // larger visible step. The batch-size floor prevents this correction from
                    // halving a two-frame batch or removing the only frame of a one-frame batch.
                    if ((pendingPresents > 0) && (framesToPresent > Wr64PresentDrainFloor)) {
                        framesToPresent -= Wr64PresentDrainFrames;
                        wr64Draining = true;
                    }
                }
                else {
                    lockedWorkloadMutex = true;
                    // Held all the way down to the unlock at the end of this block, so
                    // only the acquisition is timed here. This is the mutex the draw
                    // side takes to publish a workload, so a long wait here means the
                    // present thread is queued behind the draw thread.
                    {
                        WR64StallProbeHot workloadLockProbe("present-workload-lock", 0);
                        ext.sharedResources->workloadMutex.lock();
                    }
                }

                RenderTargetKey colorTargetKey(presentFb->addressStart, presentFb->width, presentFb->siz, Framebuffer::Type::Color);
                colorTarget = &targetManager.get(colorTargetKey, true);
                if (!colorTarget->isEmpty()) {
                    // If a depth framebuffer is about to be shown, convert it to color.
                    if (presentFb->isLastWriteDifferent(Framebuffer::Type::Color)) {
                        RenderTargetKey otherColorTargetKey(presentFb->addressStart, presentFb->width, presentFb->siz, presentFb->lastWriteType);
                        RenderTarget &otherColorTarget = targetManager.get(otherColorTargetKey, true);
                        if (!otherColorTarget.isEmpty()) {
                            const FixedRect &r = presentFb->lastWriteRect;
                            RenderWorkerExecution workerExecution(ext.presentGraphicsWorker);
                            colorTarget->copyFromTarget(ext.presentGraphicsWorker, &otherColorTarget, r.left(false), r.top(false), r.width(false, true), r.height(false, true), ext.shaderLibrary);
                        }
                    }
                }
                else {
                    colorTarget = nullptr;
                }

                if (!present.paused && (viHistory.top().vi != present.screenVI)) {
                    viHistory.pushVI(present.screenVI, viFb->width);
                }
            }
            else {
                uint32_t fbAddress = present.screenVI.fbAddress();

                // R7. The other side of the same decision. Reaching here means the
                // framebuffer manager had nothing at the address the video interface
                // is pointing at, so the scan above never ran and no interpolation
                // flag was touched either way. Recorded so that a run with no scan
                // lines is distinguishable from a run that took this path instead.
                wr64StallProbeMarkEvent("present-fb-rdram-path", static_cast<uint64_t>(fbAddress));

                // Use a scratch framebuffer to upload the RAM to the render target.
                hlslpp::uint2 fbSize = present.screenVI.fbSize();
                scratchFb.addressStart = fbAddress;
                scratchFb.width = fbSize.x;
                scratchFb.height = fbSize.y;
                scratchFb.siz = present.screenVI.fbSiz();

                lockedWorkloadMutex = true;
                // Same mutex as above, taken on the scratch path instead. Separate
                // label so a dump says which of the two branches was running.
                {
                    WR64StallProbeHot workloadLockProbe("present-workload-lock-scratch", 1);
                    ext.sharedResources->workloadMutex.lock();
                }

                RenderTargetKey colorTargetKey(fbAddress, scratchFb.width, scratchFb.siz, Framebuffer::Type::Color);
                colorTarget = &targetManager.get(colorTargetKey, true);
                scratchColorTarget = true;
                {
                    // Reallocates the render target whenever the VI size changes.
                    // Steady state is a no op, so anything landing here at all is a
                    // resolution change the game made mid race.
                    WR64StallProbeHot scratchResizeProbe("present-scratch-resize", (uint64_t(scratchFb.width) << 32) | uint64_t(scratchFb.height));
                    colorTarget->resize(ext.presentGraphicsWorker, scratchFb.width, scratchFb.height);
                }
                colorTarget->resolutionScale = { 1.0f, 1.0f };
                colorTarget->downsampleMultiplier = 1;

                scratchFb.nativeTarget.resetBufferHistory();

                {
                    // Whole frame of RAM read back into a render target, plus a
                    // synchronous worker execution around it. This is the fallback
                    // present path and it costs a full framebuffer upload every time
                    // it runs.
                    WR64StallProbeHot scratchUploadProbe("present-scratch-upload", uint64_t(scratchFb.width) * uint64_t(scratchFb.height));
                    RenderWorkerExecution workerExecution(ext.presentGraphicsWorker);
                    colorTarget->clearColorTarget(ext.presentGraphicsWorker);
                    FramebufferChange *colorFbChange = scratchFb.readChangeFromBytes(ext.presentGraphicsWorker, scratchFbChangePool, Framebuffer::Type::Color,
                        G_IM_FMT_RGBA, present.storage.data(), 0, scratchFb.height, ext.shaderLibrary);

                    if (colorFbChange != nullptr) {
                        colorTarget->copyFromChanges(ext.presentGraphicsWorker, *colorFbChange, scratchFb.width, scratchFb.height, 0, ext.shaderLibrary);
                    }
                }

                scratchFbChangePool.reset();

                if (!present.paused && (viHistory.top().vi != present.screenVI)) {
                    viHistory.pushVI(present.screenVI, fbSize.x);
                }
            }
        }

        // Create the framebuffers if necessary.
        if (swapChainFramebuffers.empty()) {
            uint32_t textureCount = ext.swapChain->getTextureCount();
            swapChainFramebuffers.resize(textureCount);
            for (uint32_t i = 0; i < textureCount; i++) {
                const RenderTexture *swapChainTexture = ext.swapChain->getTexture(i);
                swapChainFramebuffers[i] = ext.device->createFramebuffer(RenderFramebufferDesc(&swapChainTexture, 1));
            }
        }
        
        traceFramesToPresentInitial = framesToPresent;

        // How many frames this batch intends to show. Pairs with workload-batch on the
        // producer side: if the producer says nine and this says one, the loss is on
        // the present side, and if both say one the period never had nine frames in it
        // to begin with. detail is framesToPresent.
        wr64StallProbeMarkEvent("present-batch", uint64_t(framesToPresent));

        for (int32_t i = 0; i < framesToPresent; i++) {
            tracePresentLoopIterations++;
            uint32_t frameCountersNextPresented = 0;
            if ((framesToPresent > 1) && (usingMSAA || (i > 0))) {
                // Stall until the interpolated color target is available.
                const uint32_t targetIndex = usingMSAA ? i : (i - 1);
                // The present thread parks here until the workload thread has finished
                // rendering interpolated frame targetIndex. R4 caught whole native
                // periods with no instrumented work anywhere in the window, and this
                // was the largest uninstrumented wait left on this thread.
                //
                // Declared before the lock deliberately. Destruction is reverse order,
                // so the lock is released first and a report writes to the log after
                // the mutex is free, instead of holding it through an fflush while the
                // producer is trying to take it.
                //
                // Floor rather than the hot threshold. The presenter follows the
                // producer one frame behind, so this wait is where it sits for
                // most of every frame period by design. At the 0.5 ms hot floor
                // it would record 180 times a second and push the useful entries
                // out of the dump window. Seven milliseconds is above its healthy
                // cost and below the hitch threshold, so it stays quiet while the
                // cadence holds and names itself the moment the presenter parks
                // here longer than a frame.
                //
                // PRESENT METER. The stamp is taken BEFORE the probe and before
                // the lock, so no clock reading happens while interpolatedMutex
                // is held - that is the one mutex the producer takes, and a
                // measurement that stalls the producer would manufacture the
                // artifact it is hunting.
                wr64PmWaited = wr64PmArmed;
                if (wr64PmWaited) {
                    wr64PmWaitStart = std::chrono::steady_clock::now();
                }

                WR64StallProbeGate interpolatedWaitProbe("present-interpolated-wait", 7.0, uint64_t(i));
                std::unique_lock<std::mutex> interpolatedLock(ext.sharedResources->interpolatedMutex);
                ext.sharedResources->interpolatedCondition.wait(interpolatedLock, [&]() {
                    return (frameCounters.available > targetIndex) || ((frameCounters.available == targetIndex) && frameCounters.skipped);
                });

                // Do not present any more frames after this one after reaching the last available frame if the workload was skipped.
                if ((frameCounters.available == targetIndex) && frameCounters.skipped) {
                    framesToPresent = std::min(int(frameCounters.available), i + 1);
                    frameCountersNextPresented = frameCounters.count;
                }
                else if (wr64Draining && (i == (framesToPresent - 1))) {
                    // THE TRAP THIS AVOIDS. The producer waits on
                    //     prevFrameCounters.presented > targetIndex
                    // for targetIndex 0..count-2, so its last target needs
                    // presented >= count-1. A presenter that simply stops early
                    // leaves presented at count-2 and the producer blocks
                    // FOREVER. That is why frameReduction was a real mechanism
                    // and not a one-line edit.
                    //
                    // Completing the counter is what the two paths either side of
                    // this one already do - the skipped-workload branch above and
                    // the framesToPresent == 1 branch below both assign
                    // frameCounters.count outright. The target that was not shown
                    // is simply reused; nothing is reading it.
                    frameCountersNextPresented = frameCounters.count;
                }
                else {
                    frameCountersNextPresented = frameCounters.presented + 1;
                }

                if (i < framesToPresent) {
                    uint32_t targetIndex = usingMSAA ? i : (i - 1);
                    colorTarget = ext.sharedResources->interpolatedColorTargets[targetIndex].get();
                }
                else {
                    colorTarget = nullptr;
                }
            }
            else if (framesToPresent == 1) {
                frameCountersNextPresented = frameCounters.count;
            }

            // PRESENT METER. Closed HERE rather than immediately after the wait
            // returns, because interpolatedLock is still held at that point and
            // is released only by the closing brace above. What lands inside the
            // measured interval besides the wait itself is a handful of integer
            // reads and one pointer fetch, and taking a clock reading under that
            // mutex to avoid them would cost the producer far more than they do.
            if (wr64PmWaited) {
                const int64_t wr64PmWaitUs = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::steady_clock::now() - wr64PmWaitStart).count();
                if (wr64PmFrameWaits == 0) {
                    wr64PmFirstFrameWaitUs = wr64PmWaitUs;
                }
                wr64PmFrameWaitUs += wr64PmWaitUs;
                wr64PmFrameWaits++;
                // 100 us is well above the cost of taking an uncontended lock and
                // finding the predicate already true, and well below any real wait.
                if (wr64PmWaitUs > 100) {
                    wr64PmFrameWaitsBlocked++;
                }
                wr64PmWaited = false;
            }

            uint32_t swapChainIndex = 0;
            uint32_t secondarySwapChainIndex = 0;
            bool secondaryPresentFrame = false;
            const bool presentFrame = (i < framesToPresent) && swapChainValid;
            if (presentFrame) {
                // Blocks when every swap chain image is still owned by the compositor.
                // Normally instant with three images at 180 Hz. A floor of 3 ms rather
                // than the shared hot floor because a little blocking here is ordinary
                // and recording it every frame would recycle the ring.
                WR64StallProbeGate acquireProbe("present-acquire-texture", 3.0, uint64_t(i));
                swapChainValid = ext.swapChain->acquireTexture(acquiredSemaphore.get(), &swapChainIndex);
            }

            if (presentFrame && swapChainValid) {
                const bool displayedSeparateRace = wr64SeparateDisplayedRace(
                    ext.createdGraphicsAPI == UserConfiguration::GraphicsAPI::D3D12,
                    scratchColorTarget, colorTarget && colorTarget->wr64SeparateWindows);
                wr64SecondaryRaceActive.store(displayedSeparateRace, std::memory_order_release);
                const bool secondaryReady = prepareSecondaryOutput(displayedSeparateRace);
                if (secondaryReady && wr64SecondaryWindowDrawable.load(std::memory_order_acquire) &&
                    !wr64SecondaryWindowClosed.load(std::memory_order_acquire) &&
                    !secondarySwapChain->isEmpty()) {
                    // D3D12 acquire selects the current back buffer; no monitor
                    // wait is introduced for this optional output.
                    secondaryPresentFrame = secondarySwapChain->acquireTexture(
                        secondaryAcquiredSemaphore.get(), &secondarySwapChainIndex);
                    secondarySwapChainValid = secondaryPresentFrame;
                }
                // Draw the framebuffer with the VI renderer.
                RenderTexture *swapChainTexture = ext.swapChain->getTexture(swapChainIndex);
                RenderFramebuffer *swapChainFramebuffer = swapChainFramebuffers[swapChainIndex].get();
                RenderCommandList *commandList = ext.presentGraphicsWorker->commandList.get();
                commandList->begin();
                commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(swapChainTexture, RenderTextureLayout::COLOR_WRITE));
                
                VIRenderer::RenderParams renderParams;
                if (colorTarget != nullptr) {
                    renderParams.device = ext.device;
                    renderParams.commandList = commandList;
                    renderParams.swapChain = ext.swapChain;
                    renderParams.shaderLibrary = ext.shaderLibrary;
                    renderParams.textureFormat = colorTarget->format;
                    renderParams.resolutionScale = colorTarget->resolutionScale;
                    // WR64: CPU-written frames (e.g. the boot logo) have no workload-rendered
                    // content, so the aspect-widened presentation scale derived from the last
                    // workload configuration anamorphically flattens them. When the gate is
                    // enabled, present scratch-sourced frames at their native VI aspect by
                    // stripping the aspect component from the presentation scale.
                    // ★ VALIDATED FIX, COMPILED IN. No environment variable.
                    constexpr bool scratchNativeAspectEnabled = true;
                    hlslpp::float2 presentationResolutionScale = ext.sharedResources->resolutionScale;
                    if (scratchNativeAspectEnabled && scratchColorTarget) {
                        presentationResolutionScale.x = presentationResolutionScale.y;
                    }

                    // CPU-written scratch frames have no current workload configuration. Derive
                    // their scale from the swap chain and VI framebuffer, avoiding stale aspect
                    // or scale values from the previous workload. The native widescreen image
                    // maps to the complete window.
                    constexpr bool scratchFillEnabled = true;
                    // WR64_PRESENT_FILL (EXP-023): apply the same swapchain/VI-derived
                    // presentation scale to ALL presents, not just scratch ones. Combined
                    // with WR64_NATIVE_WIDE (uniform {mult,mult} render scale), the whole
                    // frame is one consistent space stretched ~0.63% to fill the window.
                    // ★ VALIDATED FIX, COMPILED IN. No environment variable.
                    constexpr bool presentFillEnabled = true;
                    if (presentFillEnabled || (scratchFillEnabled && scratchColorTarget)) {
                        const hlslpp::uint2 scratchFbSize = present.screenVI.fbSize();
                        const uint32_t swapWidth = ext.swapChain->getWidth();
                        const uint32_t swapHeight = ext.swapChain->getHeight();
                        if ((scratchFbSize.x > 0) && (scratchFbSize.y > 0) && (swapWidth > 0) && (swapHeight > 0)) {
                            // USA policy: the scene aspect stops at 16:9/32:9.
                            // Match presentation to those limits during free
                            // resize instead of squeezing or stretching it.
                            // Only the exact CPU boot image keeps its native
                            // presentation. Other scratch images include menu
                            // composites and must retain their existing policy.
                            const auto extent = wr64CpuAwarePresentationExtent(float(swapWidth), float(swapHeight),
                                wr64ExpandAspect, scratchColorTarget, present.wr64CpuBootLogo);
                            presentationResolutionScale.x = extent.width / float(scratchFbSize.x);
                            presentationResolutionScale.y = extent.height / float(scratchFbSize.y);
                        }
                    }
                    renderParams.presentationResolutionScale = presentationResolutionScale;
                    renderParams.downsamplingScale = 1;
                    renderParams.filtering = filtering;
                    renderParams.vi = &present.screenVI;
                    renderParams.removeBlackBorders = removeBlackBorders;
                    if (displayedSeparateRace) {
                        // Closed/failed secondary output falls back to the full
                        // 32:9 composite. Each explicit region ignores env crops.
                        const bool separatePrimary = secondaryReady && secondarySwapChainValid &&
                            !wr64SecondaryWindowClosed.load(std::memory_order_acquire);
                        renderParams.outputRegion = wr64SeparatePresentRegion(separatePrimary ? 1U : 0U);
                    }

                    const bool useDownsampling = (colorTarget->downsampleMultiplier > 1);
                    if (useDownsampling) {
                        colorTarget->downsampleTarget(ext.presentGraphicsWorker, ext.shaderLibrary);
                        renderParams.texture = colorTarget->downsampledTexture.get();
                        renderParams.textureWidth = colorTarget->width / colorTarget->downsampleMultiplier;
                        renderParams.textureHeight = colorTarget->height / colorTarget->downsampleMultiplier;
                        renderParams.downsamplingScale = colorTarget->downsampleMultiplier;
                    }
                    else {
                        colorTarget->resolveTarget(ext.presentGraphicsWorker, ext.shaderLibrary);
                        renderParams.texture = colorTarget->getResolvedTexture();
                        renderParams.textureWidth = colorTarget->width;
                        renderParams.textureHeight = colorTarget->height;
                    }
                }

                if (secondaryPresentFrame) {
                    RenderTexture *texture = secondarySwapChain->getTexture(secondarySwapChainIndex);
                    commandList->barriers(RenderBarrierStage::GRAPHICS,
                        RenderTextureBarrier(texture, RenderTextureLayout::COLOR_WRITE));
                    commandList->setFramebuffer(secondaryFramebuffers[secondarySwapChainIndex].get());
                    commandList->clearColor();
                    if (displayedSeparateRace && renderParams.texture != nullptr) {
                        commandList->barriers(RenderBarrierStage::GRAPHICS,
                            RenderTextureBarrier(renderParams.texture, RenderTextureLayout::SHADER_READ));
                        auto secondaryParams = renderParams;
                        secondaryParams.swapChain = secondarySwapChain.get();
                        secondaryParams.outputRegion = wr64SeparatePresentRegion(2U);
                        secondaryViRenderer->render(secondaryParams);
                    }
                    // Non-race frames deliberately leave Player 2 black. Native
                    // menus and the host UI continue only on the primary output.
                    commandList->barriers(RenderBarrierStage::NONE,
                        RenderTextureBarrier(texture, RenderTextureLayout::PRESENT));
                }
                
                commandList->setFramebuffer(swapChainFramebuffer);
                commandList->clearColor();

                if (renderParams.texture != nullptr) {
                    commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(renderParams.texture, RenderTextureLayout::SHADER_READ));
                    viRenderer->render(renderParams);
                }

                RenderHookDraw *drawHook = GetRenderHookDraw();
                if (drawHook != nullptr) {
                    drawHook(commandList, swapChainFramebuffer);
                }

                {
                    const std::scoped_lock lock(inspectorMutex);
                    if (inspector != nullptr) {
                        inspector->draw(commandList);
                    }
                    
                    commandList->barriers(RenderBarrierStage::NONE, RenderTextureBarrier(swapChainTexture, RenderTextureLayout::PRESENT));
                    commandList->end();
                    const RenderCommandList *commandList = ext.presentGraphicsWorker->commandList.get();
                    RenderCommandSemaphore *waitSemaphores[] = { acquiredSemaphore.get(), secondaryAcquiredSemaphore.get() };
                    RenderCommandSemaphore *signalSemaphores[] = { drawSemaphores[swapChainIndex].get(),
                        secondaryPresentFrame ? secondaryDrawSemaphores[secondarySwapChainIndex].get() : nullptr };
                    const uint32_t outputCount = secondaryPresentFrame ? 2U : 1U;
                    ext.presentGraphicsWorker->commandQueue->executeCommandLists(&commandList, 1,
                        waitSemaphores, outputCount, signalSemaphores, outputCount, ext.presentGraphicsWorker->commandFence.get());
                    // Both views sampled the same immutable target in this list.
                    // Retire interpolation/workload counters only after both end.
                    ext.presentGraphicsWorker->wait();
                }
            }

            if (lockedWorkloadMutex) {
                ext.sharedResources->workloadMutex.unlock();
                lockedWorkloadMutex = false;
            }
            
            if (frameCountersNextPresented > 0) {
                {
                    std::unique_lock<std::mutex> interpolatedLock(ext.sharedResources->interpolatedMutex);
                    frameCounters.presented = frameCountersNextPresented;
                }

                ext.sharedResources->interpolatedCondition.notify_all();
            }

            // As soon as we're done with the first render target, we notify the workload queue it can proceed.
            if (i == 0) {
                notifyPresentId(present);
            }

            if (presentFrame && swapChainValid) {
                const bool pacingDiagnostic = wr64FramePacingDiagnosticEnabled();
                double swapWaitMs = 0.0;
                // DXGI supplies display cadence when VSync owns the requested
                // rate. A second CPU timer can miss that same display deadline,
                // particularly after borderless fullscreen changes flip mode.
                const bool displayPaced = wr64PresentUsesDisplayPacing(
                    ext.createdGraphicsAPI == UserConfiguration::GraphicsAPI::D3D12,
                    ext.swapChain->isVsyncEnabled(), presentWaitEnabled, targetRate, swapChainRate);
                if (!displayPaced && (presentTimestamp != Timestamp()) && (targetRate > 0) && (targetRate > viOriginalRate)) {
                    // Deliberate sleep to hold the cadence. At 180 Hz it is meant to be
                    // up to about 5.5 ms, so the floor is set above that: it only lands
                    // in the ring if the sleep overshot its own target.
                    WR64StallProbeGate paceProbe("present-pace-sleep", 9.0, uint64_t(targetRate));
                    Timer::preciseSleepUntil(presentTimestamp + std::chrono::nanoseconds(1'000'000'000 / targetRate));
                }

                if (presentWaitEnabled) {
                    // Vsync style wait on the previous present. Also blocks by design,
                    // so it gets its own floor for the same reason as the pacing sleep.
                    WR64StallProbeGate presentWaitProbe("present-swapchain-wait", 7.0);
                    const Timestamp waitStart = pacingDiagnostic ? Timer::current() : Timestamp();
                    ext.swapChain->wait();
                    if (pacingDiagnostic) {
                        swapWaitMs = std::chrono::duration<double, std::milli>(Timer::current() - waitStart).count();
                    }
                }

                RenderCommandSemaphore *waitSemaphore = drawSemaphores[swapChainIndex].get();
                const Timestamp previousPresentTimestamp = presentTimestamp;
                presentTimestamp = Timer::current();
                traceSubmittedFrames++;
                swapChainValid = ext.swapChain->present(swapChainIndex, &waitSemaphore, 1);
                if (secondaryPresentFrame) {
                    RenderCommandSemaphore *secondaryWait = secondaryDrawSemaphores[secondarySwapChainIndex].get();
                    secondarySwapChainValid = secondarySwapChain->present(secondarySwapChainIndex, &secondaryWait, 1);
                }
                if (pacingDiagnostic) {
                    const double presentMs = std::chrono::duration<double, std::milli>(Timer::current() - presentTimestamp).count();
                    const double intervalMs = (previousPresentTimestamp != Timestamp())
                        ? std::chrono::duration<double, std::milli>(presentTimestamp - previousPresentTimestamp).count() : 0.0;
                    wr64RecordFramePacingPresent({intervalMs, presentMs, swapWaitMs,
                        ext.swapChain->getWidth(), ext.swapChain->getHeight(), swapChainRate,
                        targetRate, viOriginalRate, uint32_t(pendingPresents), displayPaced,
                        ext.createdGraphicsAPI == UserConfiguration::GraphicsAPI::D3D12,
                        swapChainValid, uint32_t(traceFramesToPresentInitial), uint32_t(framesToPresent)});
                }
                // Frame-time probe: one atomic increment and one store, immediately
                // after the frame is handed to the swap chain. Dormant unless
                // WR64_FRAMETIME_PROBE names a file.
                wr64FrameTimeMark();
                WR64_DIAGNOSTIC_LOG(wr64_forensic_set_present(present.presentId););
                WR64_DIAGNOSTIC_LOG(wr64_forensic_set_output(traceSubmittedFrames););
                WR64_DIAGNOSTIC_LOG(wr64_forensic_record(WR64_FORENSIC_PRESENT,
                    1, present.presentId, present.workloadId,
                    traceSubmittedFrames, swapChainIndex,
                    uint64_t(swapChainValid), uint64_t(targetRate),
                    uint64_t(viOriginalRate)););

                // Ground truth for "a hitch actually reached the screen". Every other
                // probe measures a suspect; this one measures the symptom, so a report
                // here with no accompanying operation report means the cost is in code
                // that is still uninstrumented.
                wr64StallProbeMarkInterval("present-interval");
                presentProfiler.logAndRestart();
            }
        }

        if (wr64CadenceTraceEnabled()) {
            WR64CadenceTraceRow traceRow;
            traceRow.event = "present";
            traceRow.presentId = present.presentId;
            traceRow.workloadId = present.workloadId;
            traceRow.viAddress = present.screenVI.fbAddress();
            traceRow.viOriginalRate = viOriginalRate;
            traceRow.targetRate = targetRate;
            traceRow.paused = present.paused;
            traceRow.counterCount = frameCounters.count;
            traceRow.counterAvailable = frameCounters.available;
            traceRow.counterSkipped = frameCounters.skipped;
            traceRow.presentFramebufferAddress = tracePresentFbAddress;
            traceRow.presentFramebufferWidth = tracePresentFbWidth;
            traceRow.presentFramebufferSiz = tracePresentFbSiz;
            traceRow.presentFramebufferModified = tracePresentFbModified;
            traceRow.presentFramebufferInterpolationEnabled = tracePresentFbInterpolationEnabled;
            traceRow.framesToPresentInitial = traceFramesToPresentInitial;
            traceRow.framesToPresentFinal = framesToPresent;
            traceRow.presentLoopIterations = tracePresentLoopIterations;
            traceRow.submittedFrames = traceSubmittedFrames;
            traceRow.swapChainValid = swapChainValid;
            wr64WriteCadenceTrace(traceRow);
        }

        // PRESENT METER. One call, at the end, with what the loop accumulated.
        //
        // The three counter fields are read UNDER interpolatedMutex. The producer
        // writes them, so reading them bare would be a data race - benign on x86
        // for aligned 32-bit words, but a measurement that races the thing it
        // measures is not worth defending. Once per present event, about twenty a
        // second, uncontended: the cost is nothing and the read is honest. No
        // clock is read here, so nothing times anything while the mutex is held.
        if (wr64PmArmed) {
            uint32_t wr64PmCount = 0;
            uint32_t wr64PmAvailable = 0;
            uint32_t wr64PmPresented = 0;
            {
                std::scoped_lock<std::mutex> wr64PmLock(ext.sharedResources->interpolatedMutex);
                wr64PmCount = frameCounters.count;
                wr64PmAvailable = frameCounters.available;
                wr64PmPresented = frameCounters.presented;
            }

            wr64PresentMeterFrames(uint32_t(framesToPresent), uint32_t(traceSubmittedFrames),
                wr64PmFrameWaitUs, wr64PmFirstFrameWaitUs, wr64PmFrameWaits,
                wr64PmFrameWaitsBlocked, wr64PmCount, wr64PmAvailable, wr64PmPresented,
                tracePresentFbInterpolationEnabled, present.screenVI.visible(),
                wr64PmScanFired, wr64PmScanWalked, wr64PmScanSize, wr64PmViAddress,
                tracePresentFbAddress);
        }
    }

    void PresentQueue::skipInterpolation() {
        {
            std::unique_lock<std::mutex> interpolatedLock(ext.sharedResources->interpolatedMutex);
            InterpolatedFrameCounters &frameCounters = ext.sharedResources->interpolatedFrames[ext.sharedResources->interpolatedFramesIndex];
            frameCounters.presented = frameCounters.count;
        }

        ext.sharedResources->interpolatedCondition.notify_all();
    }

    void PresentQueue::notifyPresentId(const Present &present) {
        {
            std::scoped_lock<std::mutex> cursorLock(presentIdMutex);
            presentId = present.presentId;
        }

        presentIdCondition.notify_all();
    }
    
    void PresentQueue::threadAdvanceBarrier() {
        std::scoped_lock<std::mutex> cursorLock(cursorMutex);
        barrierCursor = (barrierCursor + 1) % presents.size();
    }

    void PresentQueue::threadLoop() {
        Thread::setCurrentThreadName("RT64 Present");
        wr64StallProbeNameThread("present");

        // Create the semaphore the acquire method will use.
        acquiredSemaphore = ext.device->createCommandSemaphore();

        // Create as many semaphores to signal as textures there are.
        while (drawSemaphores.size() < ext.swapChain->getTextureCount()) {
            drawSemaphores.emplace_back(ext.device->createCommandSemaphore());
        }

        // Since the swap chain might not need a resize right away, detect present wait.
        presentWaitEnabled = ext.device->getCapabilities().presentWait;

        int processCursor = -1;
        bool skipPresent = false;
        uint32_t displayTimingRate = UINT32_MAX;
        const bool displayTiming = ext.device->getCapabilities().displayTiming;
        bool swapChainValid = !ext.swapChain->needsResize();

        // PRESENT METER. The presenter's own period, carried across iterations so
        // the header never has to read a clock. Stamped after the forensic pause
        // check below, so a paused debugger does not read as a starved presenter.
        const bool wr64PmLoopArmed = wr64PresentMeterArmed();
        std::chrono::steady_clock::time_point wr64PmLastCycle{};
        bool wr64PmHaveCycle = false;

        // How many present events were already queued behind the one being taken.
        // Zero on all but three of the 4,708 events in the recorded run; the fix
        // above turns on exactly this number, so the meter records it on every row
        // and the run says whether it ever creeps past one.
        int wr64PendingPresents = 0;

        while (presentThreadRunning) {
            WR64_DIAGNOSTIC_LOG(wr64_forensic_wait_if_paused(););

            // PRESENT METER. Both stamps sit OUTSIDE the cursorMutex scope. The
            // game thread takes that mutex to queue a present event, so timing
            // from inside it would put a clock reading on the game's path.
            const std::chrono::steady_clock::time_point wr64PmEventStart =
                wr64PmLoopArmed ? std::chrono::steady_clock::now()
                                : std::chrono::steady_clock::time_point{};
            {
                std::unique_lock<std::mutex> cursorLock(cursorMutex);
                cursorCondition.wait(cursorLock, [&]() {
                    return (writeCursor != threadCursor) || !presentThreadRunning;
                });

                if (presentThreadRunning) {
                    processCursor = threadCursor;
                    threadCursor = (threadCursor + 1) % presents.size();

                    // Treat one- or two-event backlogs as transient phase differences, including
                    // the 20-to-30 Hz race-finish transition. Dropping at those depths discards
                    // a complete native tick despite the producer arriving on time.
                    // Skip only at depth three: the four-slot ring then retains a free slot and
                    // advanceToNextPresent supplies back-pressure when the ring fills. The gradual
                    // phase drain above prevents a sustained backlog from adding display latency.
                    wr64PendingPresents =
                        (writeCursor - threadCursor + int(presents.size())) % int(presents.size());
                    skipPresent = (wr64PendingPresents > 2);

                    // [WR64] WITHOUT INTERPOLATION, A BACKLOG IS NOT MOTION.
                    //
                    // The threshold above is R3's and it is right for the
                    // interpolated case: a queued event is nine frames of real
                    // motion covering a whole 20 Hz tick, and discarding one is
                    // the micro-stutter this line was written to stop.
                    //
                    // When interpolation is off the event is ONE frame.
                    // framesToPresent is initialised to 1 and only raised to
                    // frameCounters.count inside `if (interpolationEnabled)`, so
                    // a backlog of four costs four swap-chain frames and clears
                    // in 4 x 5.6 ms - four native frames, 200 ms of game time,
                    // shown in under 17 ms. The whole picture runs at roughly
                    // twelve times speed for a sixth of a second. That is the
                    // whole-screen glitch in WHOLE_SCREEN_GLITCH_20260801.md,
                    // measured from capture-20260801-165931.
                    //
                    // This is exactly what the pre-R1 line did for every case:
                    //     skipPresent = (writeCursor != threadCursor)
                    // R1 and R3 raised the threshold to stop discarding ticks,
                    // which is worth doing when a tick is nine frames of motion
                    // and worth nothing when it is one. Restoring the old
                    // behaviour HERE ONLY costs nothing that was not already
                    // being lost, and adds no latency - a skip shortens the
                    // queue, it does not lengthen it.
                    //
                    // The interpolated path is untouched, byte for byte.
                    if (!wr64PrevPresentInterpolated && (wr64PendingPresents > 0)) {
                        skipPresent = true;
                    }
                }
            }
            const int64_t wr64PmEventWaitUs = wr64PmLoopArmed
                ? std::chrono::duration_cast<std::chrono::microseconds>(
                      std::chrono::steady_clock::now() - wr64PmEventStart).count()
                : 0;

            if (processCursor >= 0) {
                std::unique_lock<std::mutex> threadLock(threadMutex);
                const bool needsResize = ext.swapChain->needsResize() || !swapChainValid;
                if (needsResize) {
                    // Drains the graphics worker, rebuilds the swap chain and drops
                    // every cached framebuffer. Expected at startup and on a real
                    // window change; a spurious one mid race would be a whole frame.
                    WR64StallProbe resizeProbe("present-swapchain-resize");
                    ext.presentGraphicsWorker->commandList->begin();
                    ext.presentGraphicsWorker->commandList->end();
                    ext.presentGraphicsWorker->execute();
                    ext.presentGraphicsWorker->wait();
                    swapChainValid = ext.swapChain->resize();
                    swapChainFramebuffers.clear();

                    if (swapChainValid) {
                        ext.sharedResources->setSwapChainSize(ext.swapChain->getWidth(), ext.swapChain->getHeight());
                        
                        // Texture count could've changed after resize, so new semaphores are needed.
                        while (drawSemaphores.size() < ext.swapChain->getTextureCount()) {
                            drawSemaphores.emplace_back(ext.device->createCommandSemaphore());
                        }
                    }
                }

                // detectWindowMoved runs on every present, 180 times a second. If it
                // ever returns true spuriously, detectRefreshRate behind it is a
                // display mode query, which is not something to run mid frame.
                {
                    WR64StallProbeHot movedProbe("present-window-moved-check");
                    if (needsResize || ext.appWindow->detectWindowMoved()) {
                        movedProbe.setDetail(1);
                        WR64StallProbe refreshProbe("present-detect-refresh-rate");
                        ext.appWindow->detectRefreshRate();
                        ext.sharedResources->setSwapChainRate(std::min(ext.appWindow->getRefreshRate(), displayTimingRate));
                    }
                }

                if (displayTiming) {
                    uint32_t newDisplayTimingRate = ext.swapChain->getRefreshRate();
                    if (newDisplayTimingRate == 0) {
                        newDisplayTimingRate = UINT32_MAX;
                    }

                    if (newDisplayTimingRate != displayTimingRate) {
                        ext.sharedResources->setSwapChainRate(std::min(ext.appWindow->getRefreshRate(), newDisplayTimingRate));
                        displayTimingRate = newDisplayTimingRate;
                    }
                }

                skipPresent = skipPresent || ext.swapChain->isEmpty();

                Present &present = presents[processCursor];

                // Measure waiting for the producer to publish the first frame of a batch.
                // Timestamp outside the probe scope without acquiring an additional lock.
                const std::chrono::steady_clock::time_point wr64PmWorkloadStart =
                    wr64PmLoopArmed ? std::chrono::steady_clock::now()
                                    : std::chrono::steady_clock::time_point{};
                {
                    // Present thread parked until the workload it needs has been
                    // built. This going long means the cost is upstream on the draw
                    // side, not here, which narrows the search by half.
                    WR64StallProbeHot workloadWaitProbe("present-workload-wait", present.workloadId);
                    ext.workloadQueue->waitForWorkloadId(present.workloadId);
                }
                const int64_t wr64PmWorkloadWaitUs = wr64PmLoopArmed
                    ? std::chrono::duration_cast<std::chrono::microseconds>(
                          std::chrono::steady_clock::now() - wr64PmWorkloadStart).count()
                    : 0;

                if (!presentThreadRunning) {
                    continue;
                }

                // PRESENT METER. Opened after the shutdown check above, so every
                // row that is opened is also closed.
                if (wr64PmLoopArmed) {
                    const std::chrono::steady_clock::time_point wr64PmNow =
                        std::chrono::steady_clock::now();
                    const int64_t wr64PmCycleUs = wr64PmHaveCycle
                        ? std::chrono::duration_cast<std::chrono::microseconds>(
                              wr64PmNow - wr64PmLastCycle).count()
                        : 0;
                    wr64PmLastCycle = wr64PmNow;
                    wr64PmHaveCycle = true;
                    wr64PresentMeterBegin(present.presentId, present.workloadId,
                        wr64PmEventWaitUs, wr64PmWorkloadWaitUs, wr64PmCycleUs,
                        skipPresent, uint32_t(wr64PendingPresents));
                }

                if (skipPresent) {
                    // A whole queued present dropped without showing anything. Costs a
                    // full native period of output when it happens. R4 could not see
                    // this path at all, so it stayed on the suspect list purely because
                    // nothing ruled it out. detail is the workload that was thrown away.
                    wr64StallProbeMarkEvent("present-skip", present.workloadId);
                    skipInterpolation();
                    notifyPresentId(present);
                }
                else {
                    threadPresent(present, swapChainValid, wr64PendingPresents);
                }

                // PRESENT METER. The event is finished; write its row.
                wr64PresentMeterEnd();

                if (!present.paused) {
                    if (!present.fbOperations.empty()) {
                        const std::scoped_lock lock(screenFbChangePoolMutex);
                        screenFbChangePool.release(present.fbOperations.front().writeChanges.id);
                        present.fbOperations.clear();
                    }

                    threadAdvanceBarrier();
                }

                processCursor = -1;
            }
        }

        // Transition the active swap chain render target out of the present state to avoid live references to the resource.
        wr64SecondaryRaceActive.store(false, std::memory_order_release);
        uint32_t swapChainIndex = 0;
        if (!ext.swapChain->isEmpty() && ext.swapChain->acquireTexture(acquiredSemaphore.get(), &swapChainIndex)) {
            RenderTexture *swapChainTexture = ext.swapChain->getTexture(swapChainIndex);
            ext.presentGraphicsWorker->commandList->begin();
            ext.presentGraphicsWorker->commandList->barriers(RenderBarrierStage::NONE, RenderTextureBarrier(swapChainTexture, RenderTextureLayout::COLOR_WRITE));
            ext.presentGraphicsWorker->commandList->end();

            const RenderCommandList *commandList = ext.presentGraphicsWorker->commandList.get();
            RenderCommandSemaphore *waitSemaphore = acquiredSemaphore.get();
            ext.presentGraphicsWorker->commandQueue->executeCommandLists(&commandList, 1, &waitSemaphore, 1, nullptr, 0, ext.presentGraphicsWorker->commandFence.get());
            ext.presentGraphicsWorker->wait();
        }
        releaseSecondaryOutput();
    }
};
