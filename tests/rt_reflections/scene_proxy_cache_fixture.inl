// The production scene helper owns these caches. GPU ray queries check both
// current AS geometry and the exact private vertex bytes seen by the shader;
// counters additionally verify that unchanged payloads avoid CPU uploads.
{
    auto makeProxy = [](float x, uint32_t draw) {
        Wr64RTFenceProxy proxy;
        proxy.drawIndex = draw;
        proxy.triangles.resize(3);
        proxy.triangles[0].position = {x - 1, -1, 3, 1};
        proxy.triangles[1].position = {x + 1, -1, 3, 1};
        proxy.triangles[2].position = {x, 1, 3, 1};
        for (uint32_t i = 0; i < 3; ++i) {
            proxy.triangles[i].uv = {float(i) + .25f, float(i) + .75f};
            proxy.triangles[i].padding = {float(i) + 10.0f, float(i) + 20.0f};
            proxy.triangles[i].shade = {.1f + i * .1f, .4f, .7f, 1};
        }
        return proxy;
    };
    auto expectVertex = [&](const Result &hit, const Wr64RTFenceVertex &vertex) {
        require(std::memcmp(hit.proxyWords, &vertex, sizeof(vertex)) == 0,
            "GPU private-proxy vertex payload differs from current input");
    };
    const std::vector<Wr64RTSceneGeometry> nativeGeometry{{0, 3, 88}};
    const std::vector<Wr64RTFenceProxy> originalProxies{makeProxy(0, 201), makeProxy(5, 202)};
    Wr64RTScene cachedViews[2];
    auto prepareCached = [&](uint32_t view, const std::vector<Wr64RTFenceProxy> &proxies, bool reused) {
        auto &active = cachedViews[view];
        require(active.prepare(device.get(), positions.get(), faces.get(), 6, 6, nativeGeometry, proxies),
            active.lastError().c_str());
        require(active.stats().proxyPayloadReused == reused, "Unexpected private-proxy cache match");
        require((active.stats().proxyUploadBytes == 0) == reused,
            "Private-proxy upload did not agree with expected payload reuse");
    };
    auto expectOriginal = [&](const std::array<Result, 4> &hits, uint32_t draw0, uint32_t draw1) {
        expectHit(hits[0], 1, draw0, 0);
        expectHit(hits[1], 2, draw1, 3);
        expectHit(hits[2], 0, 88, 0);
        expectMiss(hits[3]);
        expectVertex(hits[0], originalProxies[0].triangles[0]);
        expectVertex(hits[1], originalProxies[1].triangles[0]);
    };

    prepareCached(0, originalProxies, false);
    require(cachedViews[0].stats().proxyGeometryCount == 2 &&
        cachedViews[0].stats().proxyTriangleCount == 2, "Wrong initial proxy counts");
    const auto cold = executeScene(cachedViews[0]);
    expectOriginal(cold, 201, 202);
    RenderBuffer *firstProxyBuffer = cachedViews[0].proxyBuffer();
    prepareCached(0, originalProxies, true);
    require(cachedViews[0].proxyBuffer() == firstProxyBuffer, "Exact cache hit replaced its upload allocation");
    auto hits = executeScene(cachedViews[0]);
    require(std::memcmp(hits.data(), cold.data(), sizeof(hits)) == 0,
        "Exact cache hit changed ray-query results or private vertex bytes");

    // Current draw/material ownership is independent of immutable geometry.
    auto changed = originalProxies;
    changed[0].drawIndex = 501;
    changed[1].drawIndex = 502;
    prepareCached(0, changed, true);
    expectOriginal(executeScene(cachedViews[0]), 501, 502);
    cachedViews[0].reset();
    require(!cachedViews[0].prepared() && !cachedViews[0].accelerationStructure() &&
        !cachedViews[0].proxyBuffer(), "Reset exposed a previous active scene");
    prepareCached(0, changed, true);
    expectOriginal(executeScene(cachedViews[0]), 501, 502);

    // Each full-vertex component participates in identity. Position changes
    // must also reach the rebuilt AS rather than just its shader attribute SRV.
    for (auto &vertex : changed[0].triangles) vertex.position[0] += 15.0f;
    prepareCached(0, changed, false);
    hits = executeScene(cachedViews[0]);
    expectMiss(hits[0]);
    expectHit(hits[3], 1, 501, 0);
    expectVertex(hits[3], changed[0].triangles[0]);
    for (uint32_t component = 0; component < 3; ++component) {
        if (component == 0) changed[0].triangles[0].uv[0] = std::nextafter(changed[0].triangles[0].uv[0], 1.0f);
        if (component == 1) changed[0].triangles[0].shade[3] = .125f;
        if (component == 2) changed[0].triangles[0].padding[1] = -0.0f;
        prepareCached(0, changed, false);
        hits = executeScene(cachedViews[0]);
        expectHit(hits[3], 1, 501, 0);
        expectVertex(hits[3], changed[0].triangles[0]);
        prepareCached(0, changed, true);
        expectVertex(executeScene(cachedViews[0])[3], changed[0].triangles[0]);
    }
    std::swap(changed[0], changed[1]);
    prepareCached(0, changed, false);
    hits = executeScene(cachedViews[0]);
    expectHit(hits[1], 1, 502, 0);
    expectHit(hits[3], 2, 501, 3);
    expectVertex(hits[1], changed[0].triangles[0]);
    expectVertex(hits[3], changed[1].triangles[0]);

    // Identical concatenated bytes with different geometry boundaries cannot
    // reuse stale ranges or primitive-local addressing.
    prepareCached(0, originalProxies, false);
    auto grouped = originalProxies;
    grouped[0].triangles.insert(grouped[0].triangles.end(), grouped[1].triangles.begin(), grouped[1].triangles.end());
    grouped.resize(1);
    prepareCached(0, grouped, false);
    hits = executeScene(cachedViews[0]);
    expectHit(hits[0], 1, 201, 0);
    expectHit(hits[1], 1, 201, 0, 1);
    expectVertex(hits[1], originalProxies[1].triangles[0]);
    prepareCached(0, originalProxies, false);
    expectOriginal(executeScene(cachedViews[0]), 201, 202);

    // Both owners prepare before either executes, so an incorrectly shared
    // upload/cache cannot be hidden by a wait between the players' prepares.
    prepareCached(1, originalProxies, false);
    changed = originalProxies;
    for (auto &vertex : changed[0].triangles) vertex.position[0] += 15.0f;
    prepareCached(0, changed, false);
    require(cachedViews[0].proxyBuffer() != cachedViews[1].proxyBuffer() &&
        cachedViews[0].geometryBuffer() != cachedViews[1].geometryBuffer() &&
        cachedViews[0].accelerationStructure() != cachedViews[1].accelerationStructure(),
        "Independent player scenes share mutable payload or AS resources");
    expectOriginal(executeScene(cachedViews[1]), 201, 202);
    hits = executeScene(cachedViews[0]);
    expectMiss(hits[0]);
    expectHit(hits[3], 1, 201, 0);
    expectVertex(hits[3], changed[0].triangles[0]);
    prepareCached(1, originalProxies, true);
    expectOriginal(executeScene(cachedViews[1]), 201, 202);

    // A cached static stream must not freeze changing native world vertices.
    for (auto &vertex : vertices) vertex[0] += 5.0f;
    prepareCached(1, originalProxies, true);
    hits = executeScene(cachedViews[1]);
    expectMiss(hits[2]);
    expectHit(hits[3], 0, 88, 0);
    expectHit(hits[0], 1, 201, 0);
    for (auto &vertex : vertices) vertex[0] -= 5.0f;

    // Removal/empty data must stop participating in traversal immediately.
    prepareCached(0, {originalProxies[1]}, false);
    hits = executeScene(cachedViews[0]);
    expectMiss(hits[0]);
    expectHit(hits[1], 1, 202, 0);
    expectVertex(hits[1], originalProxies[1].triangles[0]);
    prepareCached(0, {}, false);
    require(cachedViews[0].stats().proxyGeometryCount == 0 &&
        cachedViews[0].proxyBufferSize() == sizeof(Wr64RTFenceVertex),
        "Empty proxy scene retained active geometry or lacks its safe SRV record");
    hits = executeScene(cachedViews[0]);
    expectMiss(hits[0]);
    expectMiss(hits[1]);
    expectHit(hits[2], 0, 88, 0);
    prepareCached(0, {}, true);
    expectMiss(executeScene(cachedViews[0])[0]);
    prepareCached(0, originalProxies, false);
    expectOriginal(executeScene(cachedViews[0]), 201, 202);

    // Reject malformed input on every occurrence. Accepted later proxies must
    // use their original input ordinal when remapping draw indices.
    for (uint32_t fault = 0; fault < 7; ++fault) {
        auto malformed = originalProxies;
        auto &bad = malformed[0].triangles;
        if (fault == 0) bad[0].position[0] = std::numeric_limits<float>::quiet_NaN();
        if (fault == 1) bad[0].uv[1] = std::numeric_limits<float>::infinity();
        if (fault == 2) bad[0].shade[2] = std::numeric_limits<float>::quiet_NaN();
        if (fault == 3) bad[0].position[3] = 0;
        if (fault == 4) bad.resize(2);
        if (fault == 5) bad.clear();
        if (fault == 6) bad.resize(24579, originalProxies[0].triangles[0]);
        for (uint32_t repeat = 0; repeat < 2; ++repeat) {
            malformed[1].drawIndex = 700 + repeat;
            prepareCached(0, malformed, false);
            require(cachedViews[0].stats().rejectedGeometryCount == 1 &&
                cachedViews[0].stats().proxyGeometryCount == 1, "Malformed proxy acceptance changed");
            hits = executeScene(cachedViews[0]);
            expectMiss(hits[0]);
            expectHit(hits[1], 1, 700 + repeat, 0);
            expectVertex(hits[1], originalProxies[1].triangles[0]);
        }
    }
    prepareCached(0, originalProxies, false);
    expectOriginal(executeScene(cachedViews[0]), 201, 202);
    prepareCached(0, originalProxies, true);
    expectOriginal(executeScene(cachedViews[0]), 201, 202);
    require(!cachedViews[0].prepare(device.get(), positions.get(), faces.get(), 6, 6, {}),
        "Entirely empty scene unexpectedly prepared");
    require(!cachedViews[0].prepared() && !cachedViews[0].accelerationStructure(),
        "Entirely empty scene exposed a previous AS");
    prepareCached(0, originalProxies, true);
    expectOriginal(executeScene(cachedViews[0]), 201, 202);
    std::puts("Proxy cache GPU checks: exact reuse, draw remap, reset, position/UV/shade/padding changes, range boundaries, separate players, moving native geometry, removal/restoration and repeated invalid inputs passed.");
}
