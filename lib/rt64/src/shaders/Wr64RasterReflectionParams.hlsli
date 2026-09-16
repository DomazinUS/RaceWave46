#ifndef WR64_RASTER_REFLECTION_PARAMS_INCLUDED
#define WR64_RASTER_REFLECTION_PARAMS_INCLUDED
cbuffer Wr64RasterReflectionParams : register(b75, space0) {
    float4 wr64ReflectionRows[4];
    float4 wr64ReflectionPlane;   // unit normal.xyz, signed plane offset
    float4 wr64ReflectionOptions; // enabled, strength, distortion world units, clip bias
};

float4 wr64RasterReflectionClip(float3 worldPosition) {
    const float4 p = float4(worldPosition, 1);
    return float4(dot(wr64ReflectionRows[0], p), dot(wr64ReflectionRows[1], p),
        dot(wr64ReflectionRows[2], p), dot(wr64ReflectionRows[3], p));
}
#endif
