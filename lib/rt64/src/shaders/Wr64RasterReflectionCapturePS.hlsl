// This pass contains only admitted opaque/coverage-cutout physical geometry.
// The depth attachment orders reflected objects; alpha distinguishes empty sky.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64ReflectionUnusedPSMain
#include "RasterPS.hlsl"
#undef PSMain

float4 PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1,
    bool frontFace : SV_IsFrontFace) : SV_TARGET0 {
    float4 color, alpha;
    // Reflection reverses orientation. Match both native PS culling and the
    // capture PSO's mirrored cull mode, retaining native texture/fog/coverage.
    if (!RasterPS(getRenderParams(), position, uv, smoothColor, flatColor,
        !frontFace, color, alpha) || !all(isfinite(color.rgb))) discard;
    return float4(color.rgb, 1);
}
