//
// RT64
//

#include <algorithm>
#include <cassert>
#include <memory.h>
#include <stdio.h>

#include "common/rt64_common.h"
#include "common/rt64_wr64_stall_probe.h"
#include "gbi/rt64_f3d.h"

#include "rt64_vi.h"

namespace RT64 {
    // VI
    
    hlslpp::float4 VI::viewRectangle() const {
        return { 0.0f, 0.0f, 1.0f, 1.0f };
    }

    hlslpp::float4 VI::cropRectangle() const {
        return { 0.0f, 0.0f, 1.0f, 1.0f };
    }

    float VI::gamma() const {
        const float GammaCorrection = 1.0f / 2.2f;
        return status.gammaEnable ? GammaCorrection : 1.0f;
    }

    bool VI::compatibleWith(const VI &vi) const {
        return
            (width == vi.width) &&
            (hRegion.hStart == vi.hRegion.hStart) &&
            (hRegion.hEnd == vi.hRegion.hEnd) &&
            (vRegion.vStart == vi.vRegion.vStart) &&
            (vRegion.vEnd == vi.vRegion.vEnd) &&
            (xTransform.xScale == vi.xTransform.xScale) &&
            (xTransform.xOffset == vi.xTransform.xOffset) &&
            (yTransform.yScale == vi.yTransform.yScale) &&
            (yTransform.yOffset == vi.yTransform.yOffset);
    }

    bool VI::visible() const {
        return (status.type != VI_STATUS_TYPE_BLANK) && (hRegion.hStart > 0);
    }

    bool VI::operator!=(const VI &rhs) const {
        return
            (status.word != rhs.status.word) ||
            (origin != rhs.origin) ||
            (width != rhs.width) ||
            (intr != rhs.intr) ||
            (vCurrentLine != rhs.vCurrentLine) ||
            (burst.word != rhs.burst.word) ||
            (vSync != rhs.vSync) ||
            (hSync.word != rhs.hSync.word) ||
            (leap.word != rhs.leap.word) ||
            (hRegion.word != rhs.hRegion.word) ||
            (vRegion.word != rhs.vRegion.word) ||
            (vBurst.word != rhs.vBurst.word) ||
            (xTransform.word != rhs.xTransform.word) ||
            (yTransform.word != rhs.yTransform.word);
    }

    uint8_t VI::fbSiz() const {
        switch (status.type) {
        case VI_STATUS_TYPE_16_BIT:
            return G_IM_SIZ_16b;
        case VI_STATUS_TYPE_32_BIT:
            return G_IM_SIZ_32b;
        case VI_STATUS_TYPE_BLANK:
        default:
            return 0;
        }
    }

    uint32_t VI::fbAddress() const {
        uint8_t siz = fbSiz();

        // Estimate the origin is off by one or two rows.
        if (siz >= G_IM_SIZ_16b) {
            const bool interlacedStep = status.serrate && (vCurrentLine & 0x1);
            const uint32_t rowBytes = width * (1U << (siz - 1));
            const uint32_t rowCount = interlacedStep ? 2 : 1;
            const uint32_t rowOffset = rowBytes * rowCount;
            if (origin >= rowOffset) {
                return origin - rowOffset;
            }
        }

        return origin;
    }

    hlslpp::uint2 VI::fbSize() const {
        hlslpp::uint2 size = { width, 0 };
        
        // In interlaced without deflickering, the stride of the framebuffer is usually double of 
        // what its actual row size is. We detect for such a case and return half the width.
        if (status.serrate) {
            const float estimatedWidth = (hRegion.hEnd - hRegion.hStart) / xScaleFloat();
            const float interlacedTolerance = 1.875f;
            if (estimatedWidth < (width / interlacedTolerance)) {
                size.x = width / 2;
            }
        }

        // We can make a close estimate of the height the framebuffer will use by using the width
        // that was just fixed to eliminate interlacing.
        size.y = lround(float(vRegion.vEnd - vRegion.vStart) / (2.0f * yScaleFloat() * (float(size.x) / float(width))));

        if ((size.x > 0) && (size.y > 0)) {
            // Most of the time, the height is missing a few rows because the framebuffer is offset
            // at the origin and an extra row is left at the end to account for filtering.
            // We add two extra rows to whatever result we get and try to get the closest clean
            // multiplier of the specified Division factor.
            const uint32_t ExtraRows = 2;
            const uint32_t Divisor = 4;
            size.y += ExtraRows;
            size.y = lround(float(size.y) / Divisor) * Divisor;
            return size;
        } else {
            return hlslpp::uint2(0, 0);
        }
    }

    float VI::xScaleFloat() const {
        return (1024.0f / xTransform.xScale);
    }

    float VI::xOffsetFloat() const {
        return xTransform.xOffset / 1024.0f;
    }

    float VI::yScaleFloat() const {
        return (1024.0f / yTransform.yScale);
    }

    float VI::yOffsetFloat() const {
        return yTransform.yOffset / 1024.0f;
    }

    // VIHistory

    VIHistory::VIHistory() {
        factorCursor = 0;
        history.fill({});
        factors.fill(0);

        // One line per history object, written while the object is being built.
        // That happens during start up and never during a race, so the file write
        // here cannot show up as a stall in the middle of gameplay.
        //
        // It exists so that a run log proves which rule the binary actually
        // contains, rather than that having to be taken on trust from whatever the
        // build script claimed it compiled. detail carries the slot count.
        if (wr64StallProbeEnabled()) {
            wr64StallProbeReport("vi-history-lru-active", 0.0, static_cast<uint64_t>(history.size()));
        }
    }

    void VIHistory::pushVI(const VI &vi, uint32_t fbWidth) {
        // The history is ordered newest first: slot 0 is the most recent present.
        //
        // What this replaces advanced a cursor by one and overwrote whatever slot
        // it landed on, so the history remembered the last N *presents*. That is
        // the wrong thing for it to remember. Every lookup made against this
        // history searches it for a framebuffer address, and the game shows the
        // same small set of addresses over and over, so a stretch of presents that
        // bounces A, B, A spends two of three slots on one address and evicts the
        // third. The address evicted that way is frequently the one the very next
        // lookup asks for, and a failed lookup switches interpolation off for that
        // frame, which is a visible stutter.
        //
        // Keying on the address instead makes a repeat a move to front, costing no
        // slot at all, so the history remembers the last N *distinct* buffers. An
        // entry can now only be dropped by a buffer that has genuinely never been
        // seen before, which is the only circumstance in which dropping one is the
        // right thing to do.
        //
        // Nothing outside this file depends on the ordering. The two searches that
        // read this array both walk it from 0 to size() - 1 and take the first
        // entry that matches, so they go from an arbitrary rotation to a
        // deterministic newest first, which is strictly the better of the two.
        const uint32_t incomingAddress = vi.fbAddress();
        const size_t oldestIndex = history.size() - 1;
        size_t insertIndex = oldestIndex;
        bool addressAlreadyHeld = false;
        for (size_t i = 0; i < history.size(); i++) {
            // visible() is false for a zeroed slot, so the empty tail of a freshly
            // constructed history can never be matched, not even by an incoming
            // address of zero.
            if (history[i].vi.visible() && (history[i].vi.fbAddress() == incomingAddress)) {
                insertIndex = i;
                addressAlreadyHeld = true;
                break;
            }
        }

        if (!addressAlreadyHeld) {
            const Present &dropped = history[oldestIndex];
            if (dropped.vi.visible()) {
                // A live entry actually fell off the end, meaning the game presented
                // a buffer it has not touched within the last HistoryCapacity
                // distinct buffers. Past the first few frames of a run this should
                // never happen at all, so finding one of these inside a hitch dump
                // is the signal that the slot count is still too small.
                //
                // Ring only, no file write and no flush. This function runs with the
                // workload mutex held, and blocking I/O under that mutex would
                // manufacture exactly the stalls this probe exists to measure.
                wr64StallProbeMarkEvent("vi-history-evict", static_cast<uint64_t>(dropped.vi.fbAddress()));
            }
        }

        // Shift everything above the insertion point down one place and write the
        // new entry at the front. When the address was already held this is a pure
        // move to front and nothing at all is lost.
        for (size_t i = insertIndex; i > 0; i--) {
            history[i] = history[i - 1];
        }

        Present &entry = history[0];
        entry.vi = vi;
        entry.fbWidth = fbWidth;
    }

    void VIHistory::pushFactor(uint32_t factor) {
        factorCursor = (factorCursor + 1) % factors.size();
        factors[factorCursor] = factor;
    }

    uint32_t VIHistory::logicalRateFromFactors() {
        if ((factors[0] != 0) && std::all_of(factors.begin(), factors.end(), [&](uint32_t factor) { return factor == factors[0]; })) {
            const uint32_t FullRate = 60; // TODO: PAL support.
            return FullRate / factors[0];
        }
        else {
            return 0;
        }
    }

    const VIHistory::Present &VIHistory::top() const {
        // Slot 0 is the newest entry under the ordering established by pushVI, so
        // this keeps returning the most recent present exactly as it always did.
        return history[0];
    }
};