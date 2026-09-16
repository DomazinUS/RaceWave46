// Rasterize the native sky into a per-view directional texture once for the
// current presentation. Native material sampling has explicit derivatives.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64UnusedRasterPSMain
#include "RasterPS.hlsl"
#undef PSMain
#include "Wr64WaterParams.hlsli"

ByteAddressBuffer wr64Positions : register(t27, space0);
ByteAddressBuffer wr64Texcoords : register(t30, space0);
ByteAddressBuffer wr64Colors : register(t31, space0);
ByteAddressBuffer wr64Indices : register(t35, space0);
#include "Wr64RasterSkyLookup.hlsli"

float4 PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0) : SV_TARGET0 {
    const float pi = 3.14159265358979323846f;
    const float longitude = (uv.x - 0.5f) * (2 * pi);
    const float latitude = (0.5f - uv.y) * pi;
    const float cosLatitude = cos(latitude);
    float3 direction = float3(sin(longitude) * cosLatitude, sin(latitude), cos(longitude) * cosLatitude);
    float4 color;
    Wr64SkyLookupDiagnostic diagnostic;
    if (!wr64SkyColor(direction, color, diagnostic) || !all(isfinite(color))) return 0;
    // Interpolate premultiplied color so transparent fan boundaries do not
    // introduce dark seams when the water samples between capture texels.
    return float4(color.rgb * color.a, color.a);
}
