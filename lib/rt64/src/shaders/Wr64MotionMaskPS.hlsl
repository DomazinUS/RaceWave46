#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64MotionBasePSMain
#include "RasterPS.hlsl"
#undef PSMain

void PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1,
    float4 currentClip : TEXCOORD1, float4 previousClip : TEXCOORD2,
    bool frontFace : SV_IsFrontFace, out float4 motion : SV_TARGET0) {
    float4 nativeColor, nativeAlpha;
    if (!RasterPS(getRenderParams(), position, uv, smoothColor, flatColor,
        frontFace, nativeColor, nativeAlpha)) discard;
    if (!all(isfinite(currentClip)) || !all(isfinite(previousClip)) ||
        currentClip.w <= 0.01 || previousClip.w <= 0.01) discard;
    // NDC motion is independent of native VI scaling. Resolve converts it to
    // physical target pixels, including the real output aspect ratio.
    float2 flow = (currentClip.xy / currentClip.w - previousClip.xy / previousClip.w) * float2(0.5, -0.5);
    // Normalize only the blur exposure when a native interpolation pair clamps
    // its first previous weight. The actual native geometry keeps its weights.
    float timeScale = gConstants.padding.z == 1 ? asfloat(gConstants.padding.y) : 1;
    if (!isfinite(timeScale) || timeScale <= 0) discard;
    flow *= timeScale;
    // Teleports/cuts are not a blur source. Paused/static geometry is zero.
    if (!all(isfinite(flow)) || length(flow) > 0.20) discard;
    // Keep actor identity separate from native alpha without another target.
    // Rider and craft parts share an identity; other racers remain occluders.
    uint actor = max(1u, gConstants.padding.x);
    motion = float4(flow, position.z, float(actor * 2) + saturate(nativeAlpha.a));
}
