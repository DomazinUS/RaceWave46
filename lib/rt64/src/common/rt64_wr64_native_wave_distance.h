#pragma once
#include "rt64_wr64_wave_distance.h"
#include <limits>

namespace RT64 {
    // Per native view: no fixed decoded vertex count, no singleton face list,
    // and no assumption that both split views use the same producer table.
    struct Wr64NativeWaveDistanceView {
        bool valid = false;
        uint32_t mode = 0, course = UINT32_MAX, camera = 0, projection = UINT32_MAX, owner = 0, rings = 0, farMode = 0;
        uint32_t players = 0, phase = 0, raceMode = 0, sea = 0;
        int32_t centerX = 0, centerZ = 0;
        double datum = 0, outerScale = 3;
        std::vector<Wr64WaveDistanceVertex> boundary;
        std::vector<uint32_t> primary, sources, faces;
        struct Generated { uint32_t vertex, source, layer; double scale; };
        std::vector<Generated> generated;
    };

    template<typename Draw>
    Wr64NativeWaveDistanceView wr64PlanNativeWaveDistance(const Draw &draw,
        const Wr64WaveDistanceSnapshot &snapshot, uint32_t first, uint32_t triangles,
        uint32_t projection, uint32_t owner) {
        Wr64NativeWaveDistanceView out;
        const uint32_t rings = snapshot.rings, primaryTriangles = 6 * rings * rings;
        if (!snapshot.valid || owner > 2 || snapshot.view != (owner ? owner - 1 : 0) ||
            (rings != 10 && rings != 12 && rings != 16) || triangles != primaryTriangles + 12 ||
            snapshot.nodes.size() != 1 + 3 * rings * (rings + 1)) return out;
        const size_t count = draw.posFloats.size() / 3;
        if (draw.posFloats.size() != count * 3 || draw.velFloats.size() != count * 3 ||
            draw.vertexSegmentedAddresses.size() != count || draw.viewProjIndices.size() != count || draw.worldIndices.size() != count ||
            uint64_t(first) + uint64_t(triangles) * 3 > draw.faceIndices.size()) return out;
        std::map<uint32_t, uint32_t> representatives;
        std::set<uint32_t> primaryPhysical, suffixPhysical, boundarySlots;
        struct Edge { uint32_t a, b, slotA, slotB, count; };
        std::map<std::pair<uint32_t,uint32_t>, Edge> edges;
        std::set<std::array<uint32_t,3>> uniqueFaces;
        uint32_t world = UINT32_MAX;
        const auto slotFor = [&](uint32_t vertex) {
            if (vertex >= count) return UINT32_MAX;
            const uint32_t address = draw.vertexSegmentedAddresses[vertex];
            if (address < snapshot.sourceAddress || (address - snapshot.sourceAddress) % 16) return UINT32_MAX;
            const uint32_t slot = (address - snapshot.sourceAddress) / 16;
            return slot < snapshot.nodes.size() ? slot : UINT32_MAX;
        };
        for (uint32_t f = 0; f < triangles; ++f) {
            std::array<uint32_t,3> slots{}, vertices{};
            for (uint32_t c = 0; c < 3; ++c) {
                const uint32_t v = vertices[c] = draw.faceIndices[first + f * 3 + c];
                if (v >= count || draw.viewProjIndices[v] != projection) return {};
                if (world == UINT32_MAX) world = draw.worldIndices[v];
                if (draw.worldIndices[v] != world) return {};
                for (uint32_t axis = 0; axis < 3; ++axis)
                    if (!std::isfinite(draw.posFloats[v * 3 + axis]) || !std::isfinite(draw.velFloats[v * 3 + axis])) return {};
                if (f >= primaryTriangles) { suffixPhysical.insert(v); continue; }
                const uint32_t slot = slots[c] = slotFor(v);
                if (slot == UINT32_MAX) return {};
                const auto &node = snapshot.nodes[slot];
                const int32_t h = node.rawHeight >= 0 ? node.rawHeight / 256 : (int32_t(node.rawHeight) - 255) / 256;
                const float x = float(int16_t(uint32_t(snapshot.centerX) + uint32_t(int32_t(node.x))));
                const float z = float(int16_t(uint32_t(snapshot.centerZ) + uint32_t(int32_t(node.z))));
                const float y = float(int16_t(uint32_t(snapshot.tide) + uint32_t(node.boundary(rings) ? 0 : h)));
                if (draw.posFloats[v * 3] != x || draw.posFloats[v * 3 + 1] != y || draw.posFloats[v * 3 + 2] != z) return {};
                representatives.emplace(slot, v);
                if (primaryPhysical.insert(v).second && node.boundary(rings)) {
                    boundarySlots.insert(slot);
                    out.boundary.push_back({v, slot, node.key, snapshot.mode ? float(int16_t(uint32_t(snapshot.tide) + uint32_t(h))) : y});
                }
            }
            if (f >= primaryTriangles) continue;
            auto sorted = slots; std::sort(sorted.begin(), sorted.end());
            if (sorted[0] == sorted[1] || sorted[1] == sorted[2] || !uniqueFaces.insert(sorted).second) return {};
            const double area = (double(draw.posFloats[vertices[1] * 3]) - draw.posFloats[vertices[0] * 3]) *
                (double(draw.posFloats[vertices[2] * 3 + 2]) - draw.posFloats[vertices[0] * 3 + 2]) -
                (double(draw.posFloats[vertices[1] * 3 + 2]) - draw.posFloats[vertices[0] * 3 + 2]) *
                (double(draw.posFloats[vertices[2] * 3]) - draw.posFloats[vertices[0] * 3]);
            if (!(area < -1e-3)) return {};
            for (uint32_t c = 0; c < 3; ++c) {
                const uint32_t n = (c + 1) % 3;
                const auto key = std::minmax(slots[c], slots[n]);
                const auto inserted = edges.emplace(key, Edge{vertices[c], vertices[n], slots[c], slots[n], 0});
                if (++inserted.first->second.count > 2) return {};
            }
        }
        if (representatives.size() != snapshot.nodes.size() || boundarySlots.size() != 6 * rings) return {};
        std::map<uint32_t, Edge> next;
        for (const auto &entry : edges) if (entry.second.count == 1) {
            const auto &e = entry.second;
            if (!boundarySlots.count(e.slotA) || !boundarySlots.count(e.slotB) || !next.emplace(e.slotA, e).second) return {};
        }
        if (next.size() != 6 * rings) return {};
        uint32_t slot = next.begin()->first;
        const uint32_t start = slot;
        std::set<uint32_t> visited;
        do {
            if (!visited.insert(slot).second || !next.count(slot)) return {};
            out.sources.push_back(next.at(slot).a); slot = next.at(slot).slotB;
        } while (slot != start);
        if (out.sources.size() != next.size()) return {};

        // The six native fan anchors may be private decoded aliases. Restore
        // every one together with the logical boundary; leave its UV untouched.
        std::set<uint32_t> anchorSlots;
        const size_t originalBoundary = out.boundary.size();
        std::map<uint32_t, uint32_t> outerSources;
        float nativeDatum = 0;
        bool nativeDatumSet = false;
        double minBoundaryRadius = std::numeric_limits<double>::max(), maxOuterRadius = 0;
        for (uint32_t source : out.sources) {
            const double x = double(draw.posFloats[source * 3]) - snapshot.centerX;
            const double z = double(draw.posFloats[source * 3 + 2]) - snapshot.centerZ;
            minBoundaryRadius = std::min(minBoundaryRadius, std::hypot(x, z));
        }
        for (uint32_t v : suffixPhysical) {
            const Wr64WaveDistanceVertex *found = nullptr;
            for (size_t i = 0; i < originalBoundary; ++i) {
                const auto &b = out.boundary[i];
                if (draw.posFloats[v * 3] == draw.posFloats[b.vertex * 3] &&
                    draw.posFloats[v * 3 + 1] == draw.posFloats[b.vertex * 3 + 1] &&
                    draw.posFloats[v * 3 + 2] == draw.posFloats[b.vertex * 3 + 2]) {
                    if (found && found->slot != b.slot) return {};
                    found = &b;
                }
            }
            if (found) {
                anchorSlots.insert(found->slot);
                if (!primaryPhysical.count(v)) { auto alias = *found; alias.vertex = v; out.boundary.push_back(alias); }
            } else {
                if (primaryPhysical.count(v)) return {};
                const uint32_t address = draw.vertexSegmentedAddresses[v];
                if (nativeDatumSet && nativeDatum != draw.posFloats[v * 3 + 1]) return {};
                nativeDatum = draw.posFloats[v * 3 + 1]; nativeDatumSet = true;
                const auto inserted = outerSources.emplace(address, v);
                if (!inserted.second) for (uint32_t axis = 0; axis < 3; ++axis)
                    if (draw.posFloats[v * 3 + axis] != draw.posFloats[inserted.first->second * 3 + axis]) return {};
                maxOuterRadius = std::max(maxOuterRadius, std::hypot(double(draw.posFloats[v * 3]) - snapshot.centerX,
                    double(draw.posFloats[v * 3 + 2]) - snapshot.centerZ));
            }
        }
        if (anchorSlots.size() != 6 || outerSources.size() != 6 || !(minBoundaryRadius > 1)) return {};
        // Circumscribe the already selected native far fan. This preserves its
        // coverage even where native fan corners depend on camera heading.
        out.outerScale = std::max(3.0, maxOuterRadius / minBoundaryRadius);
        if (!std::isfinite(out.outerScale) || out.outerScale > 128) return {};
        out.valid = true; out.mode = snapshot.mode; out.course = snapshot.course; out.camera = snapshot.camera;
        out.players = snapshot.players; out.phase = snapshot.phase; out.raceMode = snapshot.raceMode; out.sea = snapshot.sea;
        out.datum = nativeDatum;
        out.owner = owner; out.projection = projection; out.rings = rings; out.centerX = snapshot.centerX; out.centerZ = snapshot.centerZ;
        for (const auto &entry : representatives) out.primary.push_back(entry.second);
        out.faces.assign(draw.faceIndices.begin() + first, draw.faceIndices.begin() + first + triangles * 3U);
        return out;
    }

    // Validate before native Roundness, commit afterwards. Original only records
    // immutable endpoints for a later mode transition; every draw byte remains
    // unchanged. New rings use the same neutral native material/UV convention.
    template<typename Draw>
    bool wr64CommitNativeWaveDistance(Draw &draw, Wr64NativeWaveDistanceView plan,
        uint32_t farMode, uint32_t &first, uint32_t &triangles) {
        if (!plan.valid || plan.owner > 2 || draw.wr64NativeWaveDistance[plan.owner].valid) return false;
        const size_t count = draw.posFloats.size() / 3;
        if (draw.posFloats.size() != count * 3 || draw.velFloats.size() != count * 3 ||
            draw.tcFloats.size() != count * 2 || draw.tcVelFloats.size() != count * 2 || draw.normColBytes.size() != count * 4 ||
            draw.viewProjIndices.size() != count || draw.worldIndices.size() != count || draw.fogIndices.size() != count ||
            draw.lightIndices.size() != count || draw.lightCounts.size() != count || draw.lookAtIndices.size() != count ||
            draw.vertexSegmentedAddresses.size() != count || draw.wr64WaterProducerKeys.size() != count ||
            draw.wr64WaterFieldInfo.size() != count * 4 || draw.wr64WaterFieldPrevPosShiftX.size() != count ||
            draw.wr64WaterFieldPrevTcShiftZ.size() != count || (!draw.wr64WaterVertexMask.empty() && draw.wr64WaterVertexMask.size() != count)) return false;
        // The native smaller/larger fan already supplies an exact flat-water
        // datum. Keep it even when a storm biases the interior wave median.
        for (uint32_t v : plan.primary) if (v >= count) return false;
        plan.farMode = wr64FarWaterDistanceMode(farMode);
        if (!plan.mode) { draw.wr64NativeWaveDistance[plan.owner] = std::move(plan); return true; }
        const uint32_t boundaryCount = uint32_t(plan.sources.size());
        if (boundaryCount != 6 * plan.rings || count + boundaryCount * 4ULL > UINT32_MAX) return false;
        plan.outerScale = std::max(plan.outerScale, wr64FarWaterRingScale(farMode, 4));
        std::map<uint32_t,float> recovered;
        for (const auto &v : plan.boundary) {
            if (v.vertex >= count || !std::isfinite(v.height)) return false;
            recovered[v.vertex] = v.height;
        }
        struct Vertex { uint32_t source, layer; double scale; float position[3], tc[2]; };
        std::vector<Vertex> generated;
        for (uint32_t layer = 1; layer <= 4; ++layer) {
            const double scale = layer == 4 ? plan.outerScale : wr64WaveRingScale(plan.mode, farMode, layer);
            for (uint32_t source : plan.sources) {
                if (!recovered.count(source)) return false;
                Vertex v{}; v.source = source; v.layer = layer; v.scale = scale;
                v.position[0] = float(plan.centerX + scale * (double(draw.posFloats[source * 3]) - plan.centerX));
                v.position[1] = float(wr64WaveRingHeight(plan.mode, scale, plan.datum, recovered.at(source)));
                v.position[2] = float(plan.centerZ + scale * (double(draw.posFloats[source * 3 + 2]) - plan.centerZ));
                for (uint32_t c = 0; c < 2; ++c) v.tc[c] = float(draw.tcFloats[source * 2 + c] + std::remainder(16.0 - draw.tcFloats[source * 2 + c], 32.0));
                for (float value : v.position) if (!std::isfinite(value)) return false;
                generated.push_back(v);
            }
        }
        const auto ring = [&](uint32_t layer, uint32_t i) { return layer ? uint32_t(count) + (layer - 1) * boundaryCount + i : plan.sources[i]; };
        std::vector<uint32_t> faces(plan.faces.begin(), plan.faces.begin() + 6U * plan.rings * plan.rings * 3U);
        for (uint32_t layer = 0; layer < 4; ++layer) for (uint32_t i = 0; i < boundaryCount; ++i) {
            const uint32_t n = (i + 1) % boundaryCount;
            faces.insert(faces.end(), {ring(layer,n), ring(layer,i), ring(layer+1,n), ring(layer,i), ring(layer+1,i), ring(layer+1,n)});
        }
        const auto position = [&](uint32_t v, uint32_t axis) { return v < count ? double(draw.posFloats[v * 3 + axis]) : double(generated[v - count].position[axis]); };
        for (size_t f = 6U * plan.rings * plan.rings * 3U; f < faces.size(); f += 3) {
            const uint32_t a=faces[f], b=faces[f+1], c=faces[f+2];
            const double area=(position(b,0)-position(a,0))*(position(c,2)-position(a,2))-(position(b,2)-position(a,2))*(position(c,0)-position(a,0));
            if (!(area < -1e-3)) return false;
        }
        if (draw.wr64WaterVertexMask.empty()) draw.wr64WaterVertexMask.assign(count, 0);
        for (const auto &v : plan.boundary) draw.posFloats[v.vertex * 3 + 1] = v.height;
        for (const auto &v : generated) {
            const uint32_t vertex = uint32_t(draw.posFloats.size() / 3), source = v.source;
            plan.generated.push_back({vertex, source, v.layer, v.scale});
            draw.posFloats.insert(draw.posFloats.end(), v.position, v.position+3);
            draw.velFloats.insert(draw.velFloats.end(), {0,0,0});
            draw.tcFloats.insert(draw.tcFloats.end(), v.tc, v.tc+2); draw.tcVelFloats.insert(draw.tcVelFloats.end(), {0,0});
            draw.normColBytes.insert(draw.normColBytes.end(), {0,127,0,draw.normColBytes[source*4+3]});
            draw.viewProjIndices.push_back(draw.viewProjIndices[source]); draw.worldIndices.push_back(draw.worldIndices[source]);
            draw.fogIndices.push_back(draw.fogIndices[source]); draw.lightIndices.push_back(draw.lightIndices[source]);
            draw.lightCounts.push_back(draw.lightCounts[source]); draw.lookAtIndices.push_back(draw.lookAtIndices[source]);
            draw.vertexSegmentedAddresses.push_back(draw.vertexSegmentedAddresses[source]); draw.wr64WaterProducerKeys.push_back(0);
            draw.wr64WaterVertexMask.push_back(6); draw.wr64WaterFieldInfo.insert(draw.wr64WaterFieldInfo.end(), {0,source,v.layer,0});
            draw.wr64WaterFieldPrevPosShiftX.emplace_back(0.0f); draw.wr64WaterFieldPrevTcShiftZ.emplace_back(0.0f);
        }
        first = uint32_t(draw.faceIndices.size()); triangles = uint32_t(faces.size() / 3);
        draw.faceIndices.insert(draw.faceIndices.end(), faces.begin(), faces.end());
        plan.faces = std::move(faces); draw.wr64NativeWaveDistance[plan.owner] = std::move(plan);
        return true;
    }

    template<typename Draw>
    Wr64WaveDistanceSurface wr64NativeWaveSurface(const Draw &draw, const Wr64NativeWaveDistanceView &view) {
        Wr64WaveDistanceSurface out;
        if (!view.valid || (view.rings != 10 && view.rings != 12 && view.rings != 16) ||
            view.faces.size() != (6U * view.rings * view.rings + (view.mode ? 48U * view.rings : 12U)) * 3U) return out;
        uint32_t world = UINT32_MAX;
        for (size_t f = 0; f < view.faces.size(); f += 3) {
            Wr64WaveDistanceSurface::Triangle t{};
            for (uint32_t c=0;c<3;++c) {
                const uint32_t v=view.faces[f+c];
                if (uint64_t(v)*3+2>=draw.posFloats.size() || v>=draw.viewProjIndices.size() || v>=draw.worldIndices.size() || draw.viewProjIndices[v]!=view.projection) return {};
                if (world==UINT32_MAX) world=draw.worldIndices[v];
                if (world!=draw.worldIndices[v]) return {};
                t.x[c]=draw.posFloats[v*3]; t.y[c]=draw.posFloats[v*3+1]; t.z[c]=draw.posFloats[v*3+2];
                if (!std::isfinite(t.x[c]) || !std::isfinite(t.y[c]) || !std::isfinite(t.z[c])) return {};
            }
            const double area=(t.x[1]-t.x[0])*(t.z[2]-t.z[0])-(t.z[1]-t.z[0])*(t.x[2]-t.x[0]);
            // Original native far fans can collapse or overlap at the edge.
            // Ignore only their degenerate/backfacing triangles; never sample
            // an extrapolation or reject the valid primary surface with them.
            if (!(area < -1e-3)) continue;
            t.inverseArea=1.0/area;
            t.minX=std::min({t.x[0],t.x[1],t.x[2]}); t.maxX=std::max({t.x[0],t.x[1],t.x[2]});
            t.minZ=std::min({t.z[0],t.z[1],t.z[2]}); t.maxZ=std::max({t.z[0],t.z[1],t.z[2]});
            out.triangles.push_back(t);
        }
        return out;
    }

    template<typename Workloads, typename Mapping>
    bool wr64FinalizeMappedNativeWaveDistance(Workloads &workloads, uint32_t index, const Mapping &mapping) {
        if (index>=workloads.size()) return false;
        auto &current=workloads[index]; auto &draw=current.drawData;
        const auto *previous=mapping.mapped && mapping.prevWorkloadIndex<workloads.size() ? &workloads[mapping.prevWorkloadIndex] : nullptr;
        bool changed=false;
        for (uint32_t owner=0;owner<3;++owner) {
            const auto &cur=draw.wr64NativeWaveDistance[owner];
            const auto *prev=previous ? &previous->drawData.wr64NativeWaveDistance[owner] : nullptr;
            if (!cur.valid || (!cur.mode && (!prev || !prev->valid || !prev->mode))) continue;
            const size_t count=draw.posFloats.size()/3;
            bool valid=draw.posFloats.size()==count*3 && draw.velFloats.size()==count*3 && draw.tcVelFloats.size()==count*2 &&
                (cur.rings==10 || cur.rings==12 || cur.rings==16) && cur.generated.size()==(cur.mode ? 24U*cur.rings:0U) &&
                cur.faces.size()==(6U*cur.rings*cur.rings+(cur.mode ? 48U*cur.rings:12U))*3U;
            for(const auto &v:cur.boundary) valid=valid && v.vertex<count;
            for(const auto &v:cur.generated) valid=valid && v.vertex<count && v.source<count;
            for(uint32_t v:cur.faces) valid=valid && v<count;
            if(!valid) continue;
            const bool compatible=previous && prev->valid && cur.course==prev->course && cur.camera==prev->camera && cur.rings==prev->rings &&
                cur.players==prev->players && cur.phase==prev->phase && cur.raceMode==prev->raceMode && cur.sea==prev->sea &&
                current.wr64RtCourse==previous->wr64RtCourse && std::abs(int64_t(cur.centerX)-prev->centerX)<=192 && std::abs(int64_t(cur.centerZ)-prev->centerZ)<=192 &&
                cur.projection<mapping.viewProjections.size() && mapping.viewProjections[cur.projection].mapped && mapping.viewProjections[cur.projection].prevTransformIndex==prev->projection;
            const auto surface=compatible ? wr64NativeWaveSurface(previous->drawData,*prev) : Wr64WaveDistanceSurface{};
            const auto finalizeY=[&](uint32_t v) {
                if (uint64_t(v)*3+2>=draw.velFloats.size()) return;
                double height=0;
                // Match the shader's float endpoint, including cancellation
                // when a large far-distance transition changes the extent.
                const double x=double(draw.posFloats[v*3]-draw.velFloats[v*3]), z=double(draw.posFloats[v*3+2]-draw.velFloats[v*3+2]);
                // Two rounded float subtractions can miss a previous outer
                // edge by one ULP. Permit only that bounded arithmetic error,
                // and clamp barycentric weights to the actual triangle. This
                // never continues a wave slope beyond the previous surface.
                const double arithmeticScale=std::max({1.0,std::abs(double(draw.posFloats[v*3])),std::abs(double(draw.posFloats[v*3+2])),
                    std::abs(double(draw.velFloats[v*3])),std::abs(double(draw.velFloats[v*3+2])),std::abs(x),std::abs(z)});
                const double tolerance=2.0*std::numeric_limits<float>::epsilon()*arithmeticScale;
                draw.velFloats[v*3+1]=surface.sample(x,z,height,tolerance)
                    ? float(double(draw.posFloats[v*3+1])-height) : 0.0f;
                if (uint64_t(v)*4<draw.wr64WaterFieldInfo.size()) draw.wr64WaterFieldInfo[v*4]=0;
            };
            // Physical seam aliases share one source point. If ordinary slot
            // matching assigned contradictory X/Z histories, hold that source
            // point instead of tearing a hole between its triangles.
            std::map<uint32_t, std::array<float,2>> boundaryVelocity;
            std::set<uint32_t> inconsistent;
            for (const auto &v:cur.boundary) {
                const std::array<float,2> velocity{draw.velFloats[v.vertex*3],draw.velFloats[v.vertex*3+2]};
                const auto inserted=boundaryVelocity.emplace(v.slot,velocity);
                if (!inserted.second && inserted.first->second!=velocity) inconsistent.insert(v.slot);
            }
            for (const auto &v:cur.boundary) if (inconsistent.count(v.slot)) {
                draw.velFloats[v.vertex*3]=0; draw.velFloats[v.vertex*3+2]=0;
            }
            // Pin generated coverage to the accepted native source motion.
            // Each endpoint owns its mode/far extent; cuts hold current shape.
            for (const auto &v:cur.generated) {
                double scale=v.scale, centerX=cur.centerX, centerZ=cur.centerZ;
                if (compatible && prev->mode) {
                    scale=v.layer==4 ? prev->outerScale : wr64WaveRingScale(prev->mode,prev->farMode,v.layer);
                    centerX=prev->centerX; centerZ=prev->centerZ;
                }
                for (uint32_t axis : {0U,2U}) {
                    const double center=axis==0 ? centerX:centerZ;
                    const double oldSource=double(draw.posFloats[v.source*3+axis]-(compatible ? draw.velFloats[v.source*3+axis]:0.0f));
                    // The previous mesh stores float endpoints. Round the
                    // reconstructed endpoint before subtracting it, otherwise
                    // an irrational enclosing-fan scale can put a stationary
                    // vertex just outside its own previous outer polygon.
                    const float previousPosition=float(center+scale*(oldSource-center));
                    draw.velFloats[v.vertex*3+axis]=compatible ? draw.posFloats[v.vertex*3+axis]-previousPosition : 0.0f;
                }
                draw.tcVelFloats[v.vertex*2]=0; draw.tcVelFloats[v.vertex*2+1]=0;
            }
            // Positive endpoint scales are not enough if native matching gave
            // different aliases incompatible motion. Prove every generated
            // face's quadratic area over the entire presentation interval.
            bool coherent=true;
            const size_t primaryFaces=6U*cur.rings*cur.rings*3U;
            const auto area=[&](size_t f,double t) {
                double x[3],z[3];
                for(uint32_t c=0;c<3;++c) { const auto v=cur.faces[f+c]; x[c]=draw.posFloats[v*3]-t*draw.velFloats[v*3]; z[c]=draw.posFloats[v*3+2]-t*draw.velFloats[v*3+2]; }
                return (x[1]-x[0])*(z[2]-z[0])-(z[1]-z[0])*(x[2]-x[0]);
            };
            if (cur.mode) for(size_t f=primaryFaces;f<cur.faces.size();f+=3) {
                const double a=area(f,0),b=area(f,0.5),c=area(f,1);
                const double quadratic=2*(c+a-2*b),linear=c-a-quadratic;
                coherent=coherent && a < -1e-3 && c < -1e-3;
                if(quadratic<0) { const double t=-linear/(2*quadratic); if(t>0 && t<1) coherent=coherent && area(f,t)<-1e-3; }
            }
            if(!coherent) {
                for(const auto &v:cur.boundary) { draw.velFloats[v.vertex*3]=0; draw.velFloats[v.vertex*3+2]=0; }
                for(const auto &v:cur.generated) { draw.velFloats[v.vertex*3]=0; draw.velFloats[v.vertex*3+2]=0; }
            }
            for(const auto &v:cur.boundary) finalizeY(v.vertex);
            for(const auto &v:cur.generated) finalizeY(v.vertex);
            changed=true;
        }
        return changed;
    }
}
