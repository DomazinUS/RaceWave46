//
// RT64
//

#include "rt64_transform_processor.h"

#include <cmath>

#include "common/rt64_math.h"
#include "common/rt64_wr64_celestial_identity.h"
#include "hle/rt64_game_frame.h"
#include "hle/rt64_workload_queue.h"

namespace RT64 {
    // TransformProcessor
    
    TransformProcessor::TransformProcessor() { }

    TransformProcessor::~TransformProcessor() { }

    void TransformProcessor::setup(RenderWorker *worker) {
        bufferUploader = std::make_unique<BufferUploader>(worker->device);
    }

    void TransformProcessor::process(const ProcessParams &p) {
        for (uint32_t w : p.curFrame->workloads) {
            Workload &workload = p.workloadQueue->workloads[w];
            DrawData &drawData = workload.drawData;
            const bool prevFrameValid = (p.prevFrame != nullptr) && p.curFrame->frameMap.workloads[w].mapped;
            auto &lerpWorldTransforms = drawData.lerpWorldTransforms;
            auto &invTWorldTransforms = drawData.invTWorldTransforms;
            auto &prevWorldTransforms = drawData.prevWorldTransforms;
            lerpWorldTransforms.clear();
            invTWorldTransforms.clear();
            prevWorldTransforms.clear();

            hlslpp::float4x4 prevMatrix, curMatrix, invMatrix, invTMatrix;

            // Match with the previous frame and interpolate the transforms.
            if (prevFrameValid) {
                const GameFrameMap::WorkloadMap &workloadMap = p.curFrame->frameMap.workloads[w];
                const DrawData &prevDrawData = p.workloadQueue->workloads[workloadMap.prevWorkloadIndex].drawData;
                for (size_t t = 0; t < drawData.worldTransforms.size(); t++) {
                    const GameFrameMap::TransformMap &transformMap = workloadMap.transforms[t];
                    if (transformMap.mapped) {
                        const hlslpp::float4x4 &prevTransform = prevDrawData.worldTransforms[workloadMap.transforms[t].prevTransformIndex];
                        const hlslpp::float4x4 &curTransform = drawData.worldTransforms[t];
                        prevMatrix = transformMap.rigidBody.lerp(p.prevFrameWeight, prevTransform, curTransform, true);
                        curMatrix = transformMap.rigidBody.lerp(p.curFrameWeight, prevTransform, curTransform, true);
                        invMatrix = hlslpp::inverse(curMatrix);
                        invTMatrix = hlslpp::transpose(invMatrix);
                        lerpWorldTransforms.emplace_back(curMatrix);
                        invTWorldTransforms.emplace_back(invTMatrix);
                        prevWorldTransforms.emplace_back(prevMatrix);
                    }
                    else {
                        invMatrix = hlslpp::inverse(drawData.worldTransforms[t]);
                        invTMatrix = hlslpp::transpose(invMatrix);
                        lerpWorldTransforms.emplace_back(drawData.worldTransforms[t]);
                        invTWorldTransforms.emplace_back(invTMatrix);
                        prevWorldTransforms.emplace_back(drawData.worldTransforms[t]);
                    }
                }
            }
            // Copy as normal and just generate the inverse of the transforms.
            else {
                for (size_t t = 0; t < drawData.worldTransforms.size(); t++) {
                    invMatrix = hlslpp::inverse(drawData.worldTransforms[t]);
                    invTMatrix = hlslpp::transpose(invMatrix);
                    invTWorldTransforms.push_back(invTMatrix);
                }
            }

            workload.wr64DolphinSunOutputRects.clear();
            for (const auto &pair : workload.wr64DolphinSunPairs) {
                // Both native endpoints are owned copies. Use the queue's
                // actual output weight, including its weight-one camera cuts,
                // without quarter-pixel or native-pixel quantization.
                workload.wr64DolphinSunOutputRects.emplace(pair.key,
                    wr64DolphinSunInterpolate(pair, p.curFrameWeight));
            }

            // WR64 celestial rects. Same convention as the matrices above:
            // blended = lerp(prev, cur, curFrameWeight), rebuilt per output
            // frame. On a camcut-suppressed frame the queue forces the weight
            // to 1, so the blended rect IS the current rect - a snap - with no
            // extra machinery here. Pairs only exist when the pairing pass in
            // GameFrame::match made them this tick, so with no sun on screen
            // this loop runs zero times.
            workload.wr64CelestialLerpRects.clear();
            if (prevFrameValid) {
                for (const Workload::Wr64CelestialRectPair &e : workload.wr64CelestialPrevRects) {
                    FixedRect blended = e.curRect;
                    blended.ulx = int32_t(std::lround(double(e.prevRect.ulx) + double(e.curRect.ulx - e.prevRect.ulx) * double(p.curFrameWeight)));
                    blended.uly = int32_t(std::lround(double(e.prevRect.uly) + double(e.curRect.uly - e.prevRect.uly) * double(p.curFrameWeight)));
                    blended.lrx = int32_t(std::lround(double(e.prevRect.lrx) + double(e.curRect.lrx - e.prevRect.lrx) * double(p.curFrameWeight)));
                    blended.lry = int32_t(std::lround(double(e.prevRect.lry) + double(e.curRect.lry - e.prevRect.lry) * double(p.curFrameWeight)));
                    workload.wr64CelestialLerpRects.emplace(e.key, blended);
                }
            }
            // R14: the no-previous-frame output. Exactly one output frame
            // per tick reaches here with prevFrameValid false, and it used
            // to leave the map empty - so the renderer drew the RAW rect
            // (the capture's lerp_found=0 row, one per tick, every tick).
            // For a rect whose raw position sits away from the blend path -
            // the pinned text exit - that raw draw is a full-step pop at
            // 20 Hz on exactly the letters the user watches. The pairs are
            // on the workload regardless of the previous frame, so serve
            // the blend's STARTING point (weight 0, the prev side) instead:
            // continuous with the interpolated frames that follow.
            else {
                for (const Workload::Wr64CelestialRectPair &e : workload.wr64CelestialPrevRects) {
                    workload.wr64CelestialLerpRects.emplace(e.key, e.prevRect);
                }
            }
        }
    }
    
    void TransformProcessor::upload(const ProcessParams &p) {
        uploads.clear();

        for (uint32_t w : p.curFrame->workloads) {
            const bool prevFrameValid = (p.prevFrame != nullptr);
            Workload &workload = p.workloadQueue->workloads[w];
            const DrawData &drawData = workload.drawData;
            DrawBuffers &drawBuffers = workload.drawBuffers;
            const interop::float4x4 *worldMatrices = prevFrameValid ? drawData.lerpWorldTransforms.data() : drawData.worldTransforms.data();
            const interop::float4x4 *prevWorldMatrices = prevFrameValid ? drawData.prevWorldTransforms.data() : drawData.worldTransforms.data();
            const interop::float4x4 *invTWorldMatrices = drawData.invTWorldTransforms.data();
            std::pair<size_t, size_t> uploadRange = { 0, drawData.worldTransforms.size() };
            uploads.emplace_back(BufferUploader::Upload{ worldMatrices, uploadRange, sizeof(interop::float4x4), RenderBufferFlag::STORAGE, { }, &drawBuffers.worldTransformsBuffer });
            uploads.emplace_back(BufferUploader::Upload{ prevWorldMatrices, uploadRange, sizeof(interop::float4x4), RenderBufferFlag::STORAGE, { }, &drawBuffers.prevWorldTransformsBuffer });
            uploads.emplace_back(BufferUploader::Upload{ invTWorldMatrices, uploadRange, sizeof(interop::float4x4), RenderBufferFlag::STORAGE, { }, &drawBuffers.invTWorldTransformsBuffer });
        }

        bufferUploader->submit(p.worker, uploads);
    }
};
