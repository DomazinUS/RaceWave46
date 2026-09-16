#pragma once

// Exact GPU inputs from the user's Dolphin Park opening capture, 2026-09-11.
// Runtime file SHA256 7abceea91fe3448e38d1095ca0822367c374609da58a3c20b7da53d99752cf02.
// Frames straddle the reported color switch. Positions/UVs/shade and camera
// are generated presentation values, and ray is captured at pixel (672,608).
// Test gradient texture pixels are synthetic; no archived image is substituted.
namespace NativeBackdropCrossingFixture {
struct Frame { unsigned elapsedMs, workload; float camera[3], ray[3]; float vertices[7][10]; };
constexpr unsigned Indices[18] = {0,1,6,1,2,6,2,3,6,3,4,6,4,5,6,5,0,6};
constexpr Frame Frames[2] = {
    {5321, 111,
     {5584.91895f, 50.9585228f, 5394.4834f},
     {-0.702062309f, 0.463143438f, -0.540931165f}, {
        {3710.33325f, 0.f, 3320.f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {5210.3335f, 0.f, 3320.f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {5960.3335f, 0.f, 4618.f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {5210.3335f, 0.f, 5916.f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {3710.33325f, 0.f, 5916.f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {2960.33325f, 0.f, 4618.f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {8272.22266f, 2304.f, 7252.3335f, 1.f, 2.f, 319.f, 0.f, 0.f, 0.f, 1.f},
    }},
    {5357, 112,
     {5546.80469f, 50.3037186f, 5366.15869f},
     {-0.714269757f, 0.430252343f, -0.551997721f}, {
        {3661.22217f, 0.f, 3285.77783f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {5161.22217f, 0.f, 3285.77783f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {5911.22217f, 0.f, 4583.77783f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {5161.22217f, 0.f, 5881.77783f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {3661.22217f, 0.f, 5881.77783f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {2911.22217f, 0.f, 4583.77783f, 1.f, 2.f, 0.f, 0.f, 0.f, 0.f, 1.f},
        {8226.f, 2304.f, 7214.11133f, 1.f, 2.f, 319.f, 0.f, 0.f, 0.f, 1.f},
    }},
};
}
