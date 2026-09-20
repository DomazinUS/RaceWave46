// Experimental water pass: keep native clip/UV/color evaluation and carry the
// matching presentation-time world position through perspective interpolation.
#define DYNAMIC_RENDER_PARAMS
#define VSMain Wr64BaseVSMain
#include "RasterVS.hlsl"
#undef VSMain

ByteAddressBuffer wr64WorldPositions : register(t27, space0);
ByteAddressBuffer wr64WaterAdjacency : register(t68, space0);

cbuffer Wr64ReflectionVertexParams : register(b25, space0) {
    float4 wr64Camera;
    uint wr64DebugView;
    float wr64Strength;
    uint wr64Enabled;
    uint wr64SmoothNormals;
};

float3 wr64ReflectionNormal(uint vertexId) {
    if (wr64Enabled == 0 || wr64SmoothNormals == 0) return 0;
    uint2 header = wr64WaterAdjacency.Load2(vertexId * 8);
    float3 normal = 0;
    // CPU adjacency crosses welded native VTX batches. Geometry is evaluated
    // here from the same presentation positions as the raster and ray scene.
    for (uint i = 0; i < min(header.y, 64u); ++i) {
        uint3 face = wr64WaterAdjacency.Load3(header.x + i * 12);
        float3 a = asfloat(wr64WorldPositions.Load3(face.x * 16));
        float3 b = asfloat(wr64WorldPositions.Load3(face.y * 16));
        float3 c = asfloat(wr64WorldPositions.Load3(face.z * 16));
        float3 area = cross(b - a, c - a);
        // The tagged water is a height field; orient all winding consistently.
        if (area.y < 0) area = -area;
        if (all(isfinite(area))) normal += area;
    }
    float lengthSquared = dot(normal, normal);
    return lengthSquared > 1e-12f && all(isfinite(normal))
        ? normal * rsqrt(lengthSquared) : float3(0, 0, 0);
}

void VSMain(float4 position : POSITION, float2 uv : TEXCOORD, float4 color : COLOR,
    uint vertexId : SV_VertexID, out float4 clip : SV_POSITION,
    out float2 outUV : TEXCOORD0, out float4 smoothColor : COLOR0,
    out float4 flatColor : COLOR1, out float3 worldPosition : TEXCOORD1,
    out float3 reflectionNormal : TEXCOORD2) {
    RasterVS(getRenderParams(), position, uv, color, clip, outUV, smoothColor, flatColor);
    worldPosition = asfloat(wr64WorldPositions.Load3(vertexId * 16));
    reflectionNormal = wr64ReflectionNormal(vertexId);
}
