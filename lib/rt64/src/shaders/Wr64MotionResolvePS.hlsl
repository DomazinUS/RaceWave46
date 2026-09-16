// Short, object-masked gather. This runs before all HUD overlays. There is no
// history color accumulation, so camera cuts cannot leave a persistent trail.
#include "shared/rt64_wr64_motion_tiles.h"
Texture2D<float4> sceneColor : register(t0);
Texture2D<float4> actorGuide0 : register(t3);
Texture2D<float4> actorGuide1 : register(t4);
Texture2D<float4> actorGuide2 : register(t5);
Texture2D<float4> actorGuide3 : register(t6);
#ifdef MULTISAMPLING
Texture2DMS<float4> motionTexture : register(t1);
Texture2DMS<float> sceneDepth : register(t2);
#else
Texture2D<float4> motionTexture : register(t1);
Texture2D<float> sceneDepth : register(t2);
#endif
[[vk::push_constant]] cbuffer MotionOptions : register(b0) {
    float4 options; // target width, target height, max radius pixels, shutter
};
int2 bounded(int2 p) { return clamp(p, 0, int2(options.xy) - 1); }
struct MotionSample {
    float2 flow;
    float depth;
    float coverage;
    uint actor;
};
uint actorOf(float4 m) { return uint(floor(m.w * 0.5)); }
float coverageOf(float4 m) { return saturate(m.w - float(actorOf(m) * 2)); }
MotionSample flowAt(int2 p) {
    MotionSample result = (MotionSample)0;
    if (any(p < 0) || any(p >= int2(options.xy))) return result;
#ifdef MULTISAMPLING
    uint width, height, samples; motionTexture.GetDimensions(width, height, samples);
    result.depth = 1;
    // Mask depth is interpolated at the pixel center, whereas native MSAA
    // depth is evaluated at each covered sample. Comparing the two rejects
    // the same sloped surface. Use exactly the native covered sample depths.
    [loop] for (uint s = 0; s < samples; ++s) {
        float4 m = motionTexture.Load(p, s);
        float d = sceneDepth.Load(p, s);
        if (coverageOf(m) > 0 && d <= result.depth) {
            result.depth = d;
            result.actor = actorOf(m);
        }
    }
    float coverage = 0;
    [loop] for (uint s = 0; s < samples; ++s) {
        float4 m = motionTexture.Load(p, s);
        if (actorOf(m) != result.actor) continue;
        float a = coverageOf(m);
        result.flow += m.xy * a; coverage += a;
    }
    if (coverage > 0) result.flow /= coverage;
    result.coverage = coverage / samples;
#else
    float4 m = motionTexture.Load(int3(p, 0));
    result.flow = m.xy;
    result.depth = sceneDepth.Load(int3(p, 0));
    result.coverage = coverageOf(m);
    result.actor = actorOf(m);
#endif
    return result;
}
float depthAt(int2 p) {
#ifdef MULTISAMPLING
    uint width, height, samples; sceneDepth.GetDimensions(width, height, samples);
    float d = 1;
    [loop] for (uint s = 0; s < samples; ++s) d = min(d, sceneDepth.Load(bounded(p), s));
    return d;
#else
    return sceneDepth.Load(int3(bounded(p), 0));
#endif
}
MotionSample actorAt(int2 p, uint actor) {
    MotionSample r = (MotionSample)0;
    r.actor = actor; r.depth = 1;
    if (any(p < 0) || any(p >= int2(options.xy))) return r;
#ifdef MULTISAMPLING
    uint width, height, samples; motionTexture.GetDimensions(width, height, samples);
    [loop] for (uint s = 0; s < samples; ++s) {
        float4 m = motionTexture.Load(p, s);
        float a = actorOf(m) == actor ? coverageOf(m) : 0;
        if (a <= 0) continue;
        r.flow += m.xy * a; r.coverage += a;
        r.depth = min(r.depth, sceneDepth.Load(p, s));
    }
    if (r.coverage > 0) r.flow /= r.coverage;
    r.coverage /= samples;
#else
    float4 m = motionTexture.Load(int3(p, 0));
    if (actorOf(m) == actor) {
        r.flow = m.xy; r.coverage = coverageOf(m);
        r.depth = sceneDepth.Load(int3(p, 0));
    }
#endif
    return r;
}
bool visibleMotion(MotionSample center, MotionSample source, float destDepth) {
    // Adjacent points of one sloped rider/craft need not share depth. Preserve
    // their motion unless a nearer, uncovered foreground sample is present.
    if (center.coverage > 0 && center.actor == source.actor &&
        destDepth + 0.000002 >= center.depth) return true;
    return destDepth + 0.000002 >= source.depth;
}
MotionSample actorSample(float2 p, uint actor, MotionSample center, float destDepth,
    out float3 actorColor, out float3 backgroundColor,
    out float backgroundCoverage, out float backgroundDepth) {
    // Interpolate native coverage continuously instead of switching a moving
    // limb on/off when a rounded sample crosses its silhouette. Color is
    // accumulated under that same coverage, not filtered with unrelated scene
    // corners and then multiplied by the silhouette a second time.
    // The native scene is already MSAA-resolved; this cannot reconstruct the
    // individual colors hidden inside a partially covered native pixel.
    int2 q = int2(floor(p)); float2 f = frac(p);
    MotionSample r = (MotionSample)0; r.actor = actor; r.depth = 1;
    actorColor = 0; backgroundColor = 0;
    backgroundCoverage = 0; backgroundDepth = 1;
    [unroll] for (uint y = 0; y < 2; ++y) [unroll] for (uint x = 0; x < 2; ++x) {
        float w = (x ? f.x : 1 - f.x) * (y ? f.y : 1 - f.y);
        if (w <= 0) continue;
        const int2 corner = q + int2(x, y);
        MotionSample m = actorAt(corner, actor);
        const float3 color = sceneColor.Load(int3(bounded(corner), 0)).rgb;
        const float rawActorCoverage = m.coverage;
        float a = rawActorCoverage * w;
        // Gate each covered corner before combining depths or colors. A
        // nearer actor corner must not admit a different, occluded corner.
        if (a > 0 && visibleMotion(center, m, destDepth)) {
            r.flow += m.flow * a; r.coverage += a;
            actorColor += color * a;
            r.depth = min(r.depth, m.depth);
        }
        // Use the original mask complement: rejecting an occluded actor does
        // not reveal background in the same corner. Preserve foreground depth
        // independently for the uncovered portion of each source corner.
        const float b = (1 - rawActorCoverage) * w;
        if (b > 0 && center.coverage > 0 && center.actor == actor) {
            const float d = depthAt(corner);
            if (d + 0.000002 >= center.depth) {
                backgroundColor += color * b;
                backgroundCoverage += b;
                backgroundDepth = min(backgroundDepth, d);
            }
        }
    }
    if (r.coverage > 0) { r.flow /= r.coverage; actorColor /= r.coverage; }
    if (backgroundCoverage > 0) backgroundColor /= backgroundCoverage;
    return r;
}
float4 guideAt(int2 tile, uint lane) {
    if (any(tile < 0) || any(tile >= (int2(options.xy) + WR64_MOTION_TILE_SIZE - 1) / WR64_MOTION_TILE_SIZE)) return 0;
    if (lane == 0) return actorGuide0.Load(int3(tile, 0));
    if (lane == 1) return actorGuide1.Load(int3(tile, 0));
    if (lane == 2) return actorGuide2.Load(int3(tile, 0));
    return actorGuide3.Load(int3(tile, 0));
}
float2 velocity(MotionSample m) {
    float2 v = m.flow * options.xy * options.w;
    float l = length(v);
    return v * min(1, options.z / max(l, 1e-5));
}
float4 PSMain(float4 position : SV_POSITION) : SV_TARGET0 {
    int2 p = int2(position.xy);
    if (options.z <= 0 || options.w <= 0) discard;
    // Broad phase reads a tiny per-racer tile map, never 32 full-resolution
    // MSAA neighborhoods at every empty sky/water pixel. The radius is capped
    // to one tile so a 3x3 neighborhood covers the complete shutter segment.
    float4 guides[4]; bool nearby = false;
    [unroll] for (uint lane = 0; lane < 4; ++lane) {
        guides[lane] = 0; float best = 0;
        [unroll] for (int y = -1; y <= 1; ++y) [unroll] for (int x = -1; x <= 1; ++x) {
            float4 g = guideAt(p / WR64_MOTION_TILE_SIZE + int2(x, y), lane);
            float speed = dot(g.xy * options.xy, g.xy * options.xy);
            if (coverageOf(g) > 0 && speed > best) { guides[lane] = g; best = speed; }
        }
        nearby = nearby || best > 0;
    }
    if (!nearby) discard;
    float4 base = sceneColor.Load(int3(p, 0));
    MotionSample center = flowAt(p);
    float destDepth = depthAt(p);
    float3 delta = 0; float totalCoverage = 0;
    const uint taps = 12;
    [loop] for (uint lane = 0; lane < 4; ++lane) {
        uint actor = 1u << lane;
        if (coverageOf(guides[lane]) <= 0) continue;
        MotionSample guide = (MotionSample)0;
        guide.flow = guides[lane].xy;
        // Native center flow takes over continuously at the silhouette. It
        // follows individual articulated parts instead of the fastest racer.
        float centerCoverage = center.actor == actor ? center.coverage : 0;
        guide.flow = lerp(guide.flow, center.flow, centerCoverage);
        float2 v = velocity(guide); float speed = length(v);
        if (speed < 0.00001) continue;
        [loop] for (uint i = 0; i < taps; ++i) {
            float t = float(i) / (taps - 1);
            float2 q = float2(p) + v * t;
            float3 actorColor, backgroundColor;
            float backgroundCoverage, backgroundDepth;
            MotionSample m = actorSample(q, actor, center, destDepth,
                actorColor, backgroundColor, backgroundCoverage, backgroundDepth);
            float2 sv = velocity(m); float sourceSpeed = length(sv);
            float coherence = saturate(dot(sv, v) / max(sourceSpeed * speed, 1e-8));
            coherence *= saturate(sourceSpeed / speed);
            coherence *= saturate(sourceSpeed - speed * t + 1);
            const float actorWeight = m.coverage * coherence;
            const float backgroundWeight = centerCoverage > 0 && backgroundDepth + 0.000002 >= center.depth ?
                backgroundCoverage * centerCoverage : 0;
            if (actorWeight > 0) {
                delta += (actorColor - base.rgb) * actorWeight;
                totalCoverage += actorWeight;
            }
            if (backgroundWeight > 0) {
                delta += (backgroundColor - base.rgb) * backgroundWeight;
                totalCoverage += backgroundWeight;
            }
        }
    }
    if (totalCoverage <= 0) discard;
    return float4(base.rgb + delta / max(float(taps), totalCoverage), base.a);
}
