// Actual native vertex projection creates sample-frequency depth on a sloped
// actor. A color gradient makes loss of blur observable inside the silhouette.
#define DYNAMIC_RENDER_PARAMS
#include "RasterVS.hlsl"
void ActorPSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1,
    out float4 color : SV_TARGET0) {
    color = float4(smoothColor.rgb, 1);
}
