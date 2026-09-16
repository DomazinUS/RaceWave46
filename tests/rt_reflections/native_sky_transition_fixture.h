#pragma once
// Recorded native cloud transitions, not the current user video or a course capture.
// Exact source: canary-sky-bracket-r4-20260728/wr64-sky-events-tiles-140555.txt
// under the outer repository collection root. Material/topology provenance is
// documented in native_sky_archive_fixture.h. VTX records contain previous
// position (position minus velocity), current position, previous and current
// UVs from the matched draw's
// seven original segment-6 source vertices 060001C0..06000220.
// Source SHA256: e62224422e592968ac495fc803856bc16ca2cf75836efbf59db05d623f0ab807
// Tests separately replay current production smart-UV policy: when the native
// UV delta exceeds 20 or position delta exceeds 1000, current UVs are held while
// positions still interpolate. Cameras and texture pixels in GPU tests are
// synthetic, and must not be described as captured from these events.
namespace NativeSkyTransitionFixture {
struct Frame {
    unsigned frame;
    float previousPositions[7][3], currentPositions[7][3];
    float previousTexcoords[7][2], currentTexcoords[7][2];
};
constexpr Frame Frames[] = {
    { 174,
        {
            { 2235.0000f, 400.0000f, 3061.0000f },
            { -1019.0000f, 400.0000f, -691.0000f },
            { 1981.0000f, 400.0000f, -691.0000f },
            { 3481.0000f, 400.0000f, 1907.0000f },
            { 1981.0000f, 400.0000f, 4505.0000f },
            { -1019.0000f, 400.0000f, 4505.0000f },
            { -2519.0000f, 400.0000f, 1907.0000f },
        },
        {
            { 2822.0000f, 400.0000f, 3482.0000f },
            { 2561.0000f, 400.0000f, -812.0000f },
            { 5561.0000f, 400.0000f, -812.0000f },
            { 7061.0000f, 400.0000f, 1786.0000f },
            { 5561.0000f, 400.0000f, 4384.0000f },
            { 2561.0000f, 400.0000f, 4384.0000f },
            { 1061.0000f, 400.0000f, 1786.0000f },
        },
        {
            { -5.7969f, -1.5156f },
            { -79.1562f, -74.7656f },
            { -11.5312f, -74.7656f },
            { 22.2812f, -24.0469f },
            { -11.5312f, 26.6719f },
            { -79.1562f, 26.6719f },
            { -112.9688f, -24.0469f },
        },
        {
            { 11.0000f, -4.7500f },
            { 5.7500f, -79.4531f },
            { 66.0312f, -79.4531f },
            { 96.1719f, -34.2500f },
            { 66.0312f, 10.9531f },
            { 5.7500f, 10.9531f },
            { -24.3750f, -34.2500f },
        },
    },
    { 182,
        {
            { 2794.0000f, 400.0000f, 3608.0000f },
            { 2465.0000f, 400.0000f, -733.0000f },
            { 5465.0000f, 400.0000f, -733.0000f },
            { 6965.0000f, 400.0000f, 1865.0000f },
            { 5465.0000f, 400.0000f, 4463.0000f },
            { 2465.0000f, 400.0000f, 4463.0000f },
            { 965.0000f, 400.0000f, 1865.0000f },
        },
        {
            { 2149.0000f, 400.0000f, 4753.0000f },
            { -520.0000f, 400.0000f, 3899.0000f },
            { 2480.0000f, 400.0000f, 3899.0000f },
            { 3980.0000f, 400.0000f, 6497.0000f },
            { 2480.0000f, 400.0000f, 9095.0000f },
            { -520.0000f, 400.0000f, 9095.0000f },
            { -2020.0000f, 400.0000f, 6497.0000f },
        },
        {
            { 10.2344f, -4.4375f },
            { 3.9062f, -76.6719f },
            { 61.5469f, -76.6719f },
            { 90.3594f, -33.4375f },
            { 61.5469f, 9.7812f },
            { 3.9062f, 9.7812f },
            { -24.9062f, -33.4375f },
        },
        {
            { -3.9219f, 14.0156f },
            { -56.0625f, -0.4375f },
            { 2.5469f, -0.4375f },
            { 31.8594f, 43.5312f },
            { 2.5469f, 87.5000f },
            { -56.0625f, 87.5000f },
            { -85.3750f, 43.5312f },
        },
    },
};
}
