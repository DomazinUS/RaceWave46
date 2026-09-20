// One scan produces independent motion guides for all four native racers.
// The resolve never needs to search full-resolution empty background pixels.
#include "shared/rt64_wr64_motion_tiles.h"

#ifdef MULTISAMPLING
Texture2DMS<float4> motionTexture : register(t1);
Texture2DMS<float> sceneDepth : register(t2);
#else
Texture2D<float4> motionTexture : register(t1);
Texture2D<float> sceneDepth : register(t2);
#endif
[[vk::push_constant]] cbuffer MotionOptions : register(b0) {
    float4 options; // active width, active height, radius, shutter
};

void PSMain(float4 position : SV_POSITION,
    out float4 racer0 : SV_TARGET0, out float4 racer1 : SV_TARGET1,
    out float4 racer2 : SV_TARGET2, out float4 racer3 : SV_TARGET3) {
    float4 best[WR64_MOTION_RACER_COUNT];
    float speedSquared[WR64_MOTION_RACER_COUNT];
    [unroll] for (uint lane = 0; lane < WR64_MOTION_RACER_COUNT; ++lane) {
        best[lane] = 0;
        speedSquared[lane] = 0;
    }
    const int2 begin = int2(position.xy) * WR64_MOTION_TILE_SIZE;
    const int2 end = min(begin + WR64_MOTION_TILE_SIZE, int2(options.xy));
    uint sampleCount = 1;
#ifdef MULTISAMPLING
    uint width, height;
    motionTexture.GetDimensions(width, height, sampleCount);
#endif
    [loop] for (int y = begin.y; y < end.y; ++y) {
        [loop] for (int x = begin.x; x < end.x; ++x) {
            [loop] for (uint sample = 0; sample < sampleCount; ++sample) {
#ifdef MULTISAMPLING
                const float4 m = motionTexture.Load(int2(x, y), sample);
#else
                const float4 m = motionTexture.Load(int3(x, y, 0));
#endif
                if (!all(isfinite(m)) || m.w < 2) continue;
                const uint actor = uint(floor(m.w * 0.5));
                const float coverage = saturate(m.w - float(actor * 2));
                if (coverage <= 0 || (actor != 1 && actor != 2 && actor != 4 && actor != 8)) continue;
                const uint lane = actor == 1 ? 0 : actor == 2 ? 1 : actor == 4 ? 2 : 3;
                const float2 pixelFlow = m.xy * options.xy;
                const float speed = dot(pixelFlow, pixelFlow);
                if (!isfinite(speed) || speed <= speedSquared[lane]) continue;
#ifdef MULTISAMPLING
                const float depth = sceneDepth.Load(int2(x, y), sample);
#else
                const float depth = sceneDepth.Load(int3(x, y, 0));
#endif
                if (!isfinite(depth) || depth < 0 || depth > 1) continue;
                speedSquared[lane] = speed;
                // Flow, depth and coverage describe one real covered sample.
                // Never combine a fast limb's flow with unrelated nearer depth.
                best[lane] = float4(m.xy, depth, m.w);
            }
        }
    }
    racer0 = best[0];racer1 = best[1];racer2 = best[2];racer3 = best[3];
}
