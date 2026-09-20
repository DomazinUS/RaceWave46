#pragma once

// Archived geometry/UV fixture, not a current-course gameplay capture.
// Sources under the repository collection root (outside this worktree):
//   canary-sky-bracket-r4-20260728/wr64-sky-events-tiles-140555.txt, lines 1-12
//   canary-sky-bracket-r4-20260728/wr64-sky-bracket-tiles.csv, frame 127
//   canary-sky-bracket-r4-20260728/wr64-sky-tiles-140555.csv, frame 127
//
// Provenance is the R4 event writer's traversal of the matched draw's own
// face indices, selected by FC11C223/FF87FFFF + 00504240/00882C3F and six
// triangles. The paired R4C row identifies call 2, world transform 2, seven
// unique vertices, six triangles, and no repair/injection. These vertices
// actually have segment-6 addresses 060001C0..06000220. A historical comment
// claiming that source-1 0102CD18 was this six-triangle family is not the
// provenance used here. This is not the earlier transform-1-only probe.
//
// The event contains positions, UVs, world matrices and view-projection, but
// NOT texture pixels, primitive color, or vertex shade/alpha. The topology and
// radial-alpha rule below are separately native-code-derived from:
//   canary-sky-call-identity-r2-20260728/.forensics/capture-20260728-034653/rdram.bin
// Segment 1 base 00228E10 + DL 00010470 points to G_VTX 04000E6F/060001C0
// followed by six BF fan triangles (indices encoded multiplied by five).
// Native function 8004C1D0, instructions 8004C860..8004C904, computes radial
// alpha with constants 800D4738/800D473C; these are NOT logged frame-127 RGBA.
// Tests using synthetic texture/color must identify those inputs as such.
// Do not label this a captured Sunset Bay
// texture/material fixture: the log does not record the course.

namespace NativeSkyArchiveFixture {
    constexpr unsigned Frame = 127;
    constexpr unsigned VertexCount = 7;
    constexpr unsigned RecordedTriangleCount = 6;
    constexpr unsigned NativeFanIndices[18] = {0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1};
    constexpr float NativeAlphaSlope = -.055f, NativeAlphaIntercept = 450.f;
    constexpr float Positions[VertexCount][3] = {
        {4060, 400, 4317}, {793, 400, 585}, {3793, 400, 585},
        {5293, 400, 3183}, {3793, 400, 5781}, {793, 400, 5781},
        {-707, 400, 3183}
    };
    constexpr float Texcoords[VertexCount][2] = {
        {-4.0156f, -.2969f}, {-62.8906f, -58.5469f}, {-8.8281f, -58.5469f},
        {18.2031f, -18.f}, {-8.8281f, 22.5469f}, {-62.8906f, 22.5469f},
        {-89.9219f, -18.f}
    };
    // Matrix is row-major, row-vector convention: clip = worldPosition * VP.
    constexpr double ViewProjection[4][4] = {
        {.729452, .100596, -.821525, -.820511},
        {.041912, 2.513706, -.223145, -.222870},
        {-1.154783, .154794, -.527033, -.526382},
        {2028.197754, -1292.826660, 6244.891113, 6257.169922}
    };
    // Derived from the rounded logged VP, not a separately captured eye:
    // solve camera*VP columns x,y,w = 0 (world matrix is identity).
    constexpr double DerivedCamera[3] = {4616.205723271132, 41.76122689325365, 4673.820577366591};
    // Least-squares UV map using coordinates relative to Positions[0].
    // Maximum absolute residual across both UV components is .003609 texels.
    constexpr double RelativeUVMap[2][3] = {
        {.018020880286587587, .00000003013475620796714, -4.016317452102449},
        {.00000023617879444482137, .015607118477956688, -.30050884405771133}
    };
    constexpr unsigned TextureWidth = 64, TextureHeight = 32;
    constexpr unsigned Format = 3, Size = 2; // IA16, as recorded in tile log.
    constexpr unsigned WrapS = 64, WrapT = 32; // Decoded periods, not N64 mask bit counts.
    constexpr float ShiftScaleS = 1, ShiftScaleT = 1;
    constexpr unsigned AddressModeS = 0, AddressModeT = 0; // Wrap.
    constexpr unsigned TileULS = 0, TileULT = 0, TileLRS = 252, TileLRT = 124;
    constexpr unsigned ColorCombiner[2] = {0xFC11C223, 0xFF87FFFF};
    constexpr unsigned OtherMode[2] = {0x00504240, 0x00882C3F};
}
