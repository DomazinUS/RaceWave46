#ifndef WR64_AMBIENT_OCCLUSION_INCLUDED
#define WR64_AMBIENT_OCCLUSION_INCLUDED

// A deliberately short-range contact experiment on selected native shore
// surfaces. It does not relight materials or modify reflected radiance.
bool wr64AOActive() {
    return wr64AOOptions.x == 1 && all(isfinite(wr64AOOptions)) &&
        wr64AOOptions.y > wr64AOOptions.w && wr64AOOptions.y <= 128.0f &&
        wr64AOOptions.z > 0 && wr64AOOptions.w > 0;
}

bool wr64AOBlocked(RayDesc ray, uint receiverDrawIndex, uint receiverFaceIndex) {
    RayQuery<RAY_FLAG_FORCE_NON_OPAQUE | RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES |
        RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH> query;
    query.TraceRayInline(wr64Scene, RAY_FLAG_NONE, 0xff, ray);
    while (query.Proceed()) {
        if (query.CandidateType() != CANDIDATE_NON_OPAQUE_TRIANGLE) continue;
        const uint geometryIndex = query.CandidateGeometryIndex();
        const uint primitiveIndex = query.CandidatePrimitiveIndex();
        const uint4 geometry = wr64Geometry[geometryIndex];
        // Only original physical surfaces occlude ambient light. Private fence
        // volumes approximate a directional shadow, not a solid native object.
        // Reject them before attempting to read original face-index streams.
        if ((geometry.w & 1u) == 0 || (geometry.w & (4u | 8u)) != 0) continue;
        if (geometry.y == receiverDrawIndex &&
            geometry.x + primitiveIndex * 3 == receiverFaceIndex) continue;
        if (wr64CandidateCovered(geometryIndex, primitiveIndex,
            query.CandidateTriangleBarycentrics())) query.CommitNonOpaqueTriangleHit();
    }
    return query.CommittedStatus() == COMMITTED_TRIANGLE_HIT;
}

float wr64AmbientOcclusion(float3 worldPosition, float3 normal,
    uint receiverDrawIndex, uint receiverFaceIndex) {
    if (!wr64AOActive() || !all(isfinite(worldPosition)) || !all(isfinite(normal))) return 0;
    const float lengthSquared = dot(normal, normal);
    if (!isfinite(lengthSquared) || lengthSquared < 1e-12f) return 0;
    normal *= rsqrt(lengthSquared);
    float3 u = float3(normal.y, -normal.x, 0);
    const float uLengthSquared = dot(u, u);
    u = uLengthSquared < 1e-8f ? float3(1, 0, 0) : u * rsqrt(uLengthSquared);
    const float3 v = cross(normal, u);
    // Equal-area disk points lifted into a cosine-weighted hemisphere:
    // r=sqrt((i+.5)/8), angle=i*pi*(3-sqrt(5)), height=sqrt(1-r*r).
    // Fixed in world orientation: no pixel/frame random sequence or history.
    const float3 samples[8] = {
        float3(0.2500000000f, 0.0000000000f, 0.9682458366f),
        float3(-0.3192900902f, 0.2924958774f, 0.9013878189f),
        float3(0.0488724659f, -0.5568765411f, 0.8291561976f),
        float3(0.4024444785f, 0.5249175570f, 0.7500000000f),
        float3(-0.7385351140f, -0.1306364628f, 0.6614378278f),
        float3(0.6996049319f, -0.4450313913f, 0.5590169944f),
        float3(-0.2340041582f, 0.8704838045f, 0.4330127019f),
        float3(-0.4462713077f, -0.8592682468f, 0.2500000000f)
    };
    RayDesc ray;
    ray.Origin = worldPosition + normal * wr64AOOptions.w;
    if (!all(isfinite(ray.Origin))) return 0;
    ray.TMin = wr64AOOptions.w;
    ray.TMax = wr64AOOptions.y;
    float blocked = 0;
    [loop] for (uint i = 0; i < 8; ++i) {
        ray.Direction = u * samples[i].x + v * samples[i].y + normal * samples[i].z;
        blocked += wr64AOBlocked(ray, receiverDrawIndex, receiverFaceIndex) ? 1 : 0;
    }
    return blocked * (1.0f / 8.0f);
}

float wr64AOTransmission(float occlusion) {
    if (occlusion <= 0 || !isfinite(occlusion) || !wr64AOActive()) return 1;
    return 1 - min(wr64AOOptions.z, 0.2f) * saturate(occlusion);
}

#endif
