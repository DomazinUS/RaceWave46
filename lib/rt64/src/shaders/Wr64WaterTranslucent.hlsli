#ifndef WR64_WATER_TRANSLUCENT_INCLUDED
#define WR64_WATER_TRANSLUCENT_INCLUDED

// Return premultiplied native beam color and its accumulated opacity. Solid
// traversal is separate: a beam never terminates scenery rays or casts shadows.
float4 wr64TraceTranslucentBeams(RayDesc ray, float solidDistance) {
    if (wr64SceneOptions.x == 0 || !all(isfinite(ray.Origin)) ||
        !all(isfinite(ray.Direction)) || !isfinite(ray.TMin) ||
        !isfinite(ray.TMax) || !isfinite(solidDistance)) return 0;
    ray.TMax = min(ray.TMax, solidDistance);
    if (ray.TMin < 0 || ray.TMax <= ray.TMin) return 0;

    const uint maxLayers = min(wr64SceneOptions.x, 32u);
    uint visited[32];
    float3 accumulated = 0;
    float transmission = 1;
    for (uint layer = 0; layer < maxLayers; layer++) {
        // Closest, not first encountered: acceleration-structure traversal is
        // unordered. Opaque geometry is already represented by solidDistance.
        RayQuery<RAY_FLAG_CULL_OPAQUE | RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES> query;
        query.TraceRayInline(wr64Scene, RAY_FLAG_NONE, 0xff, ray);
        uint selectedGeometry = 0xffffffffu;
        uint selectedPrimitive = 0;
        uint selectedDraw = 0;
        float2 selectedBarycentric = 0;
        float selectedDistance = ray.TMax;
        while (query.Proceed()) {
            if (query.CandidateType() != CANDIDATE_NON_OPAQUE_TRIANGLE) continue;
            uint geometryIndex = query.CandidateGeometryIndex();
            uint4 geometry = wr64Geometry[geometryIndex];
            if ((geometry.w & 4u) == 0) continue;
            bool seen = false;
            for (uint j = 0; j < layer; j++) { seen |= visited[j] == geometryIndex; }
            if (seen) continue;
            float distance = query.CandidateTriangleRayT();
            if (!isfinite(distance) || distance < ray.TMin || distance >= solidDistance ||
                distance > selectedDistance) continue;
            // The only admitted family is one native tapered prism per draw.
            // Its original winding is outward and native back-face culling
            // shows the entry surface, not both entry and exit alpha layers.
            uint primitive = query.CandidatePrimitiveIndex();
            uint3 indices = wr64Indices.Load3((geometry.x + primitive * 3) * 4);
            float3 a = asfloat(wr64Positions.Load3(indices.x * 16));
            float3 b = asfloat(wr64Positions.Load3(indices.y * 16));
            float3 c = asfloat(wr64Positions.Load3(indices.z * 16));
            float3 normal = cross(b - a, c - a);
            if (!all(isfinite(normal)) || dot(normal, normal) <= 1e-12f ||
                dot(ray.Direction, normal) >= 0) continue;
            // Coincident independent prisms follow native overlay order, with
            // the later draw foremost. A shared tessellation edge is one layer.
            if (distance == selectedDistance && selectedGeometry != 0xffffffffu &&
                (geometry.y < selectedDraw || (geometry.y == selectedDraw && primitive >= selectedPrimitive))) continue;
            selectedGeometry = geometryIndex;
            selectedPrimitive = primitive;
            selectedDraw = geometry.y;
            selectedDistance = distance;
            selectedBarycentric = query.CandidateTriangleBarycentrics();
            // Keep traversing without committing: pruning at this distance
            // could hide a coincident prism before its draw-order tie-break.
        }
        if (selectedGeometry == 0xffffffffu) break;
        visited[layer] = selectedGeometry;
        uint4 selected = wr64Geometry[selectedGeometry];
        uint3 indices = wr64Indices.Load3((selected.x + selectedPrimitive * 3) * 4);
        float4 color = wr64NativeColor(selected.y, indices, selectedBarycentric, true, -1);
        if (all(isfinite(color))) {
            accumulated += transmission * color.a * color.rgb;
            transmission *= 1 - color.a;
        }
        if (transmission <= 1.0f / 4096.0f) break;
        // Keep the original ray interval. Even an inclusive TMin set from a
        // reported hit can lose a coincident surface to hardware intersection
        // precision on the next traversal. Selecting the closest unvisited
        // prism preserves ordering without moving that boundary. Deduplication
        // and the layer cap guarantee progress and prevent shared-edge alpha.
    }
    return float4(accumulated, 1 - transmission);
}

// Beam is premultiplied; native scenery/sky are straight color plus opacity.
float4 wr64BeamsOverBackground(float4 beam, float4 background) {
    if (beam.a <= 0) return background;
    float transmittedAlpha = (1 - beam.a) * background.a;
    float alpha = beam.a + transmittedAlpha;
    return float4((beam.rgb + background.rgb * transmittedAlpha) / max(alpha, 1e-8f), alpha);
}

// A beam seen through an otherwise missing reflection still blends over the
// native water. Its alpha must not turn that unknown background into black.
void wr64ReflectBeamsOverNative(float4 beam, float reflectionWeight,
    inout float4 pixelColor, inout float4 pixelAlpha) {
    float reflectedAlpha = saturate(reflectionWeight) * beam.a;
    if (reflectedAlpha <= 0) return;
    float transmittedAlpha = saturate(pixelAlpha.a) * (1 - reflectedAlpha);
    float alpha = reflectedAlpha + transmittedAlpha;
    pixelColor.rgb = (saturate(reflectionWeight) * beam.rgb + pixelColor.rgb * transmittedAlpha) / max(alpha, 1e-8f);
    pixelAlpha.a = alpha;
}

#endif
