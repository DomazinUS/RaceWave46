#pragma once
#include <cstdint>

namespace RT64 {
// USA knDynamic.mtxMachineProj and its eight vpResult records. These are
// submitted by race results, points/rankings, records, and tournament results.
// The address pair identifies the model preview independently of slide offset,
// textures, camera position, or other 3D projections sharing its framebuffer.
inline bool wr64MenuModelPreview(uint32_t projection, uint32_t viewport) {
    return projection == 0x07000A40 && viewport >= 0x07001280 &&
        viewport < 0x07001300 && (viewport & 15) == 0;
}
}
