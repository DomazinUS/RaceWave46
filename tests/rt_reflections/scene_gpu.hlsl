// Synthetic geometry only. Exercises the actual scene helper's descriptor layout.
RaytracingAccelerationStructure scene : register(t26);
StructuredBuffer<uint4> geometry : register(t40);
ByteAddressBuffer proxyVertices : register(t41);
struct ProbeResult {
    uint4 identity;
    float4 values;
    uint4 proxyWords[3];
};
RWStructuredBuffer<ProbeResult> output : register(u0);

[numthreads(4, 1, 1)]
void CSMain(uint3 id : SV_DispatchThreadID) {
    RayDesc ray;
    ray.Origin = float3(id.x * 5.0f, 0.0f, 0.0f);
    ray.Direction = float3(0.0f, 0.0f, 1.0f);
    ray.TMin = 0.01f;
    ray.TMax = 20.0f;
    RayQuery<RAY_FLAG_FORCE_OPAQUE | RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES> query;
    query.TraceRayInline(scene, RAY_FLAG_NONE, 0xff, ray);
    while (query.Proceed()) {}
    ProbeResult result;
    result.identity = uint4(0, 0xffffffff, 0xffffffff, 0xffffffff);
    result.values = 0;
    result.proxyWords[0] = 0;
    result.proxyWords[1] = 0;
    result.proxyWords[2] = 0;
    if (query.CommittedStatus() == COMMITTED_TRIANGLE_HIT) {
        uint g = query.CommittedGeometryIndex();
        uint4 metadata = geometry[g];
        result.identity = uint4(1, g, metadata.y, metadata.x);
        result.values = float4(query.CommittedTriangleBarycentrics(),
            query.CommittedRayT(), query.CommittedPrimitiveIndex());
        if (metadata.w & 8) {
            uint address = (metadata.x + query.CommittedPrimitiveIndex() * 3) * 48;
            result.proxyWords[0] = proxyVertices.Load4(address);
            result.proxyWords[1] = proxyVertices.Load4(address + 16);
            result.proxyWords[2] = proxyVertices.Load4(address + 32);
        }
    }
    output[id.x] = result;
}
