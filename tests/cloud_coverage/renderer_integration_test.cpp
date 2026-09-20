#include "common/rt64_wr64_cloud_coverage_integration.h"
#include "render/rt64_framebuffer_renderer_call.h"
#include "native_capture_fixture.h"
#include "../rt_reflections/native_sky_archive_fixture.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <limits>
#include <stdexcept>

namespace RT64 {
    void wr64TestActualResetDrawData(DrawData &drawData);
    void wr64TestActualCloudRasterOverride(const DrawData &, const GameCall &,
        const Projection &, InstanceDrawCall &, bool, bool, bool);
    void wr64TestActualDecodeCloudTile(const LoadTile &, const DrawCall &,
        DrawCallTile &, interop::RDPTile &);
    unsigned wr64TestActualEndingCloudPreparation(const uint8_t *, DrawData &, GameCall &, uint32_t);
}

namespace {
    unsigned checks = 0;
    void require(bool value, const char *message) {
        ++checks;
        if (!value) throw std::runtime_error(message);
    }
    constexpr uint32_t NativeCount = 20, First = 3, View = 1;
    struct Fixture { RT64::DrawData draw; RT64::GameCall call{}; };
    Fixture fixture(const CloudCaptureFixtures::Capture &capture, uint32_t sourceBase) {
        Fixture f;
        auto &d = f.draw;
        d.posFloats.assign(NativeCount * 3, 0);
        d.velFloats.assign(NativeCount * 3, 0);
        d.tcFloats.assign(NativeCount * 2, 0);
        d.tcVelFloats.assign(NativeCount * 2, 0);
        d.normColBytes.assign(NativeCount * 4, 255);
        d.worldIndices.assign(NativeCount, 2);
        d.viewProjIndices.assign(NativeCount, 0);
        d.fogIndices.assign(NativeCount, 0);
        d.lightIndices.assign(NativeCount, 0);
        d.lightCounts.assign(NativeCount, 0);
        d.lookAtIndices.assign(NativeCount, 0);
        d.vertexSegmentedAddresses.assign(NativeCount, 0);
        d.wr64WaterProducerKeys.assign(NativeCount, 0);
        d.wr64WaterVertexMask.assign(NativeCount, 0);
        d.wr64WaterFieldInfo.assign(NativeCount * 4, 0);
        d.wr64WaterFieldPrevPosShiftX.assign(NativeCount, hlslpp::float4(0));
        d.wr64WaterFieldPrevTcShiftZ.assign(NativeCount, hlslpp::float4(0));
        d.worldTransforms.assign(3, interop::float4x4::identity());
        d.lerpWorldTransforms = d.worldTransforms;
        d.worldTransformVertexIndices = {0, First, First + 7};
        d.posTransformed.assign(NativeCount, hlslpp::float4(0));
        d.posScreen.assign(NativeCount, hlslpp::float3(0));
        d.viewTransforms.assign(2, interop::float4x4::identity());
        d.rspViewports.assign(2, interop::RSPViewport::identity());
        hlslpp::float4x4 vp, projection;
        for (unsigned r = 0; r < 4; ++r) for (unsigned c = 0; c < 4; ++c) {
            vp[r][c] = float(capture.viewProjection[r][c]);
            projection[r][c] = float(capture.projection[r][c]);
        }
        d.viewTransforms[View] = hlslpp::mul(vp, hlslpp::inverse(projection));
        for (unsigned i = 0; i < 7; ++i) {
            const uint32_t v = First + i;
            for (unsigned c = 0; c < 3; ++c) d.posFloats[v * 3 + c] = float(capture.positions[i][c]);
            for (unsigned c = 0; c < 2; ++c) d.tcFloats[v * 2 + c] = float(capture.texcoords[i][c]);
            d.normColBytes[v * 4 + 3] = uint8_t(std::lround(capture.alpha[i] * 255));
            d.worldIndices[v] = 1;
            d.viewProjIndices[v] = View;
            d.vertexSegmentedAddresses[v] = sourceBase + i * 16;
        }
        // Unrelated indexed triangles precede and follow the actual native fan.
        d.faceIndices = {0, 1, 2};
        for (uint32_t i = 0; i < 6; ++i)
            d.faceIndices.insert(d.faceIndices.end(), {First, First + i + 1, First + (i + 1) % 6 + 1});
        d.faceIndices.insert(d.faceIndices.end(), {17, 18, 19});
        auto &call = f.call;
        call.meshDesc.faceIndicesStart = 3;
        call.callDesc.triangleCount = 6;
        call.callDesc.textureOn = true;
        call.callDesc.tileCount = 1;
        call.callDesc.colorCombiner.L = 0xFC11C223;
        call.callDesc.colorCombiner.H = 0xFF87FFFF;
        call.callDesc.otherMode.L = 0x00504240;
        call.callDesc.otherMode.H = sourceBase == 0x06000230 ? 0x00882CFF : 0x00882C3F;
        // Start with native G_SETTILE fields, then run the actual State::flush
        // conversion. RDPTile stores periods/scales, not the raw mask/shift bits.
        RT64::LoadTile load{};
        load.fmt = NativeSkyArchiveFixture::Format;
        load.siz = NativeSkyArchiveFixture::Size;
        load.line = NativeSkyArchiveFixture::TextureWidth * 2 / 8;
        load.masks = 6; load.maskt = 5;
        load.cms = load.cmt = G_TX_WRAP;
        load.uls = NativeSkyArchiveFixture::TileULS;
        load.ult = NativeSkyArchiveFixture::TileULT;
        load.lrs = NativeSkyArchiveFixture::TileLRS;
        load.lrt = NativeSkyArchiveFixture::TileLRT;
        RT64::DrawCallTile tile{};
        interop::RDPTile rdp{};
        RT64::wr64TestActualDecodeCloudTile(load, call.callDesc, tile, rdp);
        d.callTiles.push_back(tile);
        d.rdpTiles.push_back(rdp);
        return f;
    }
    bool append(Fixture &f) {
        return RT64::wr64AppendCloudCoverage(f.draw, f.call, View, -.055f, 450.0f,
            RT64::wr64CloudCoverageEnabled());
    }
    void rasterCheck(const Fixture &f, bool expected) {
        RT64::Projection projection{};
        projection.type = RT64::Projection::Type::Perspective;
        projection.transformsIndex = View;
        auto draw = [&] {
            RT64::InstanceDrawCall raster;
            raster.type = RT64::InstanceDrawCall::Type::IndexedTriangles;
            raster.triangles.indexStart = f.call.meshDesc.faceIndicesStart;
            raster.triangles.faceCount = f.call.callDesc.triangleCount;
            raster.triangles.vertexTestZ = false;
            raster.triangles.screenScale = {.75f, .875f};
            raster.triangles.screenOffset = {.125f, .25f};
            raster.triangles.scissor = {1, 2, 847, 959};
            return raster;
        };
        auto raster = draw();
        RT64::wr64TestActualCloudRasterOverride(f.draw, f.call, projection, raster, false, false, true);
        require(raster.triangles.faceCount == (expected ? 198U : 6U) &&
            raster.triangles.indexStart == (expected ? f.call.wr64CloudCoverage.faceIndicesStart : 3U),
            "actual final renderer did not select the expected index range");
        require(raster.triangles.scissor.left == 1 && raster.triangles.scissor.bottom == 959 &&
            float(raster.triangles.screenScale.x) == .75f && float(raster.triangles.screenOffset.y) == .25f,
            "raster sidecar changed viewport/scissor mapping");
        if (!expected) return;
        for (int guard = 0; guard < 5; ++guard) {
            raster = draw();
            projection.type = guard == 0 ? RT64::Projection::Type::Orthographic : RT64::Projection::Type::Perspective;
            raster.triangles.vertexTestZ = guard == 1;
            RT64::wr64TestActualCloudRasterOverride(f.draw, f.call, projection, raster, guard == 2, guard == 3, guard != 4);
            require(raster.triangles.faceCount == 6 && raster.triangles.indexStart == 3,
                "final renderer did not preserve a modified/unsupported raster mapping");
        }
    }
    template<class T> bool prefix(const std::vector<T> &before, const std::vector<T> &after) {
        return after.size() >= before.size() && std::equal(before.begin(), before.end(), after.begin());
    }
}

int main(int argc, char **argv) {
    const char *gate = argc > 1 ? argv[1] : "";
#ifdef _WIN32
    _putenv_s("WR64_CLOUD_COVERAGE", std::strcmp(gate, "1") == 0 ? "0" : "1");
#else
    setenv("WR64_CLOUD_COVERAGE", std::strcmp(gate, "1") == 0 ? "0" : "1", 1);
#endif
    try {
        const bool enabled = std::strcmp(gate, "1") == 0;
        require(!RT64::wr64CloudCoverageEnabled(), "default must be Original despite obsolete env override");
        if (gate[0]) RT64::setWr64CloudCoverageMode(uint32_t(std::strtoul(gate, nullptr, 10)));
        require(RT64::wr64CloudCoverageEnabled() == enabled, "saved renderer mode was overridden by environment");
        if (!enabled) {
            auto f = fixture(CloudCaptureFixtures::Captures[0], 0x060001C0);
            const auto before = f.draw;
            require(!append(f), "disabled/default appended geometry");
            require(f.draw.posFloats == before.posFloats && f.draw.tcFloats == before.tcFloats &&
                f.draw.faceIndices == before.faceIndices && f.draw.worldIndices == before.worldIndices &&
                f.draw.normColBytes == before.normColBytes, "disabled/default changed native data");
            require(f.draw.wr64CloudNativeVertexCount == UINT32_MAX &&
                f.call.wr64CloudCoverage.vertexStart == UINT32_MAX && f.call.wr64CloudCoverage.faceCount == 0,
                "disabled/default changed metadata");
            rasterCheck(f, false);
            std::printf("PASS: %u default/disabled renderer integration checks\n", checks);
            return 0;
        }

        {
            auto decoded = fixture(CloudCaptureFixtures::Captures[0], 0x060001C0);
            const auto &tile = decoded.draw.callTiles[0];
            const auto &rdp = decoded.draw.rdpTiles[0];
            require(tile.loadTile.masks == 6 && tile.loadTile.maskt == 5 &&
                rdp.masks == NativeSkyArchiveFixture::WrapS && rdp.maskt == NativeSkyArchiveFixture::WrapT,
                "production tile conversion did not decode mask bits to native periods");
            require(rdp.fmt == NativeSkyArchiveFixture::Format && rdp.siz == NativeSkyArchiveFixture::Size &&
                tile.sampleWidth == NativeSkyArchiveFixture::TextureWidth &&
                tile.sampleHeight == NativeSkyArchiveFixture::TextureHeight,
                "production format/size/sample dimensions disagree with archived native tile");
            require(rdp.cms == NativeSkyArchiveFixture::AddressModeS && rdp.cmt == NativeSkyArchiveFixture::AddressModeT &&
                rdp.shifts == NativeSkyArchiveFixture::ShiftScaleS && rdp.shiftt == NativeSkyArchiveFixture::ShiftScaleT,
                "production address modes/shift scales disagree with archived native tile");
            require(rdp.uls == NativeSkyArchiveFixture::TileULS && rdp.ult == NativeSkyArchiveFixture::TileULT &&
                rdp.lrs == NativeSkyArchiveFixture::TileLRS && rdp.lrt == NativeSkyArchiveFixture::TileLRT,
                "production tile bounds disagree with archived native tile");
            require(rdp.stride == 128 && tile.lineWidth == 64,
                "native IA16 row width did not decode to byte stride");
            auto raw = decoded;
            raw.draw.rdpTiles[0].masks = tile.loadTile.masks;
            raw.draw.rdpTiles[0].maskt = tile.loadTile.maskt;
            require(!append(raw) && raw.draw.vertexCount() == NativeCount &&
                raw.draw.wr64CloudNativeVertexCount == UINT32_MAX,
                "raw6/5 accepted in a decoded RDPTile or rejection mutated native data");
            require(append(decoded) && RT64::wr64CloudCoveragePresentationValid(decoded.draw, decoded.call, View),
                "real decoded64/32 tile was rejected before append or presentation");
        }

        for (const auto &capture : CloudCaptureFixtures::Captures) for (uint32_t base : {0x060001C0U, 0x06000230U}) {
            auto f = fixture(capture, base);
            const auto native = f.draw;
            require(append(f), "actual native fixture failed append/authentication");
            const auto &coverage = f.call.wr64CloudCoverage;
            require(f.draw.vertexCount() == NativeCount + 96 && coverage.faceCount == 198,
                "appended vertex/triangle count differs");
            require(prefix(native.posFloats, f.draw.posFloats) && prefix(native.tcFloats, f.draw.tcFloats) &&
                prefix(native.normColBytes, f.draw.normColBytes) && prefix(native.faceIndices, f.draw.faceIndices) &&
                prefix(native.velFloats, f.draw.velFloats) && prefix(native.tcVelFloats, f.draw.tcVelFloats),
                "native vertex/index/velocity prefix changed");
            require(f.call.callDesc.triangleCount == 6 && f.call.meshDesc.faceIndicesStart == 3,
                "native call classification/range changed");
            require(RT64::wr64RTSkySignature(f.call.callDesc.triangleCount,
                f.call.callDesc.colorCombiner.L, f.call.callDesc.colorCombiner.H,
                f.call.callDesc.otherMode.L, f.call.callDesc.otherMode.H), "reflection signature lost native six triangles");
            require(RT64::wr64CloudCoveragePresentationValid(f.draw, f.call, View), "first/unmatched output rejected annulus");
            rasterCheck(f, true);
            require(f.draw.worldTransformVertexCount(0) == 3 && f.draw.worldTransformVertexCount(1) == 7 &&
                f.draw.worldTransformVertexCount(2) == 10, "appended cloud vertices changed native transform ranges");
            f.draw.worldTransformVertexIndices.push_back(f.draw.vertexCount());
            require(f.draw.worldTransformVertexCount(2) == 10 && f.draw.worldTransformVertexCount(3) == 0,
                "later empty ghost transform exposes cloud suffix or underflows");
            require(f.draw.wr64WaterProducerKeys.size() == f.draw.vertexCount() &&
                f.draw.wr64WaterVertexMask.size() == f.draw.vertexCount() &&
                f.draw.wr64WaterFieldInfo.size() == f.draw.vertexCount() * 4 &&
                f.draw.wr64WaterFieldPrevPosShiftX.size() == f.draw.vertexCount() &&
                f.draw.wr64WaterFieldPrevTcShiftZ.size() == f.draw.vertexCount(), "parallel water streams lost alignment");
            require(f.draw.posTransformed.size() == NativeCount && f.draw.posScreen.size() == NativeCount,
                "native CPU transformed-position archive was rewritten");
            require(!append(f) && f.draw.vertexCount() == NativeCount + 96, "same workload appended twice");
            for (uint32_t v = NativeCount; v < f.draw.vertexCount(); ++v)
                require(f.draw.vertexSegmentedAddresses[v] == 0 && f.draw.wr64WaterProducerKeys[v] == 0 &&
                    f.draw.wr64WaterVertexMask[v] == 0, "synthetic vertex impersonates a native producer");

            // Different native position and scroll velocities exercise actual
            // fractional output. The core holds current geometry fixed while
            // extending the final native velocity chart with the same weights.
            for (uint32_t i = 0; i < 7; ++i) {
                for (uint32_t c = 0; c < 3; ++c) f.draw.velFloats[(First + i) * 3 + c] = float(i * 3 + c) * .125f;
                for (uint32_t c = 0; c < 2; ++c) f.draw.tcVelFloats[(First + i) * 2 + c] = float(i + c) * .0625f;
            }
            const auto nativePosVel = f.draw.velFloats, nativeTcVel = f.draw.tcVelFloats;
            require(RT64::wr64FinalizeCloudCoverageCall(f.draw, f.call, View), "final velocity extension failed");
            require(std::equal(nativePosVel.begin(), nativePosVel.begin() + NativeCount * 3, f.draw.velFloats.begin()) &&
                std::equal(nativeTcVel.begin(), nativeTcVel.begin() + NativeCount * 2, f.draw.tcVelFloats.begin()),
                "annulus finalizer modified native velocities");
            for (uint32_t i = 0; i < 96; ++i) for (float frame : {0.0f, .125f, .5f, .875f, 1.0f}) {
                for (uint32_t c = 0; c < 2; ++c) {
                    double expected = 0;
                    for (uint32_t s = 0; s < 7; ++s)
                        expected += coverage.weights[i][s] * (double(f.draw.tcFloats[(First + s) * 2 + c]) -
                            double(f.draw.tcVelFloats[(First + s) * 2 + c]) * (1 - frame));
                    const double actual = double(f.draw.tcFloats[(NativeCount + i) * 2 + c]) -
                        double(f.draw.tcVelFloats[(NativeCount + i) * 2 + c]) * (1 - frame);
                    require(std::abs(expected - actual) < .002, "fractional annulus UV departed from native weighted chart");
                }
            }
            // Existing sky rebase fix can zero native UV motion late. Added
            // vertices must consume that result rather than keep stale scroll.
            for (uint32_t s = 0; s < 7; ++s) for (uint32_t c = 0; c < 2; ++c)
                f.draw.tcVelFloats[(First + s) * 2 + c] = 0;
            require(RT64::wr64FinalizeCloudCoverageCall(f.draw, f.call, View), "post-rebase finalization failed");
            for (uint32_t i = NativeCount * 2; i < f.draw.tcVelFloats.size(); ++i)
                require(f.draw.tcVelFloats[i] == 0, "UV rebase repair failed to reach added vertices");

            // Execute the actual reset body extracted from production source.
            RT64::wr64TestActualResetDrawData(f.draw);
            require(f.draw.vertexCount() == 0 && f.draw.faceIndices.empty() &&
                f.draw.wr64CloudNativeVertexCount == UINT32_MAX && f.draw.worldTransformVertexCount(0) == 0,
                "actual Workload reset retained cloud range/cap");
        }

        // Both enhanced native race views coexist in one workload. Its single
        // native matching cap must survive two appends, and each annulus must
        // inherit only its own camera/velocity/material streams.
        {
            auto f = fixture(CloudCaptureFixtures::Captures[0], 0x060001C0);
            const auto secondNative = fixture(CloudCaptureFixtures::Captures[1], 0x06000230);
            RT64::GameCall second = secondNative.call;
            second.callDesc.tileIndex = 1;
            second.meshDesc.faceIndicesStart = uint32_t(f.draw.faceIndices.size());
            f.draw.callTiles.push_back(secondNative.draw.callTiles[0]);
            f.draw.rdpTiles.push_back(secondNative.draw.rdpTiles[0]);
            f.draw.viewTransforms.push_back(secondNative.draw.viewTransforms[View]);
            f.draw.rspViewports.push_back(interop::RSPViewport::identity());
            constexpr uint32_t SecondFirst = 10, SecondView = 2;
            for (uint32_t i = 0; i < 7; ++i) {
                const uint32_t dst = SecondFirst + i, src = First + i;
                for (uint32_t c = 0; c < 3; ++c)
                    f.draw.posFloats[dst * 3 + c] = secondNative.draw.posFloats[src * 3 + c];
                for (uint32_t c = 0; c < 2; ++c)
                    f.draw.tcFloats[dst * 2 + c] = secondNative.draw.tcFloats[src * 2 + c];
                for (uint32_t c = 0; c < 4; ++c)
                    f.draw.normColBytes[dst * 4 + c] = secondNative.draw.normColBytes[src * 4 + c];
                f.draw.vertexSegmentedAddresses[dst] = 0x06000230 + i * 16;
                f.draw.viewProjIndices[dst] = SecondView;
                f.draw.worldIndices[dst] = 2;
            }
            for (uint32_t i = 0; i < 6; ++i)
                f.draw.faceIndices.insert(f.draw.faceIndices.end(),
                    {SecondFirst, SecondFirst + i + 1, SecondFirst + (i + 1) % 6 + 1});
            const auto nativePositions = f.draw.posFloats;
            const auto nativeFaces = f.draw.faceIndices;
            require(append(f), "first view in shared workload failed append");
            // A UI change after workload preparation starts must not split
            // two views between Original and Extended.
            RT64::setWr64CloudCoverageMode(0);
            require(RT64::wr64AppendCloudCoverage(f.draw, second, SecondView, -.055f, 450, true),
                "second view in shared workload failed append");
            rasterCheck(f, true);
            require(f.draw.vertexCount() == NativeCount + 192 && f.draw.wr64CloudNativeVertexCount == NativeCount &&
                f.call.wr64CloudCoverage.vertexStart == NativeCount && second.wr64CloudCoverage.vertexStart == NativeCount + 96,
                "two views changed native cap or overlapped suffix ranges");
            require(prefix(nativePositions, f.draw.posFloats) && prefix(nativeFaces, f.draw.faceIndices),
                "shared workload append changed original geometry");
            require(RT64::wr64CloudCoveragePresentationValid(f.draw, f.call, View) &&
                RT64::wr64CloudCoveragePresentationValid(f.draw, second, SecondView) &&
                !RT64::wr64CloudCoveragePresentationValid(f.draw, f.call, SecondView) &&
                !RT64::wr64CloudCoveragePresentationValid(f.draw, second, View), "two views lost camera ownership");
            require(f.draw.worldTransformVertexCount(0) == 3 && f.draw.worldTransformVertexCount(1) == 7 &&
                f.draw.worldTransformVertexCount(2) == 10, "second cloud append changed native transform counts");
            for (uint32_t i = 0; i < 7; ++i) {
                f.draw.velFloats[(First + i) * 3] = 10;
                f.draw.velFloats[(SecondFirst + i) * 3] = -7;
                f.draw.tcVelFloats[(First + i) * 2] = 1;
                f.draw.tcVelFloats[(SecondFirst + i) * 2] = 3;
            }
            require(RT64::wr64FinalizeCloudCoverageCall(f.draw, f.call, View) &&
                RT64::wr64FinalizeCloudCoverageCall(f.draw, second, SecondView), "shared-workload finalization failed");
            for (uint32_t i = 0; i < 96; ++i) {
                const uint32_t a = NativeCount + i, b = NativeCount + 96 + i;
                require(f.draw.viewProjIndices[a] == View && f.draw.viewProjIndices[b] == SecondView &&
                    std::abs(f.draw.velFloats[a * 3] - 10) < .0001f &&
                    std::abs(f.draw.velFloats[b * 3] + 7) < .0001f &&
                    std::abs(f.draw.tcVelFloats[a * 2] - 1) < .0001f &&
                    std::abs(f.draw.tcVelFloats[b * 2] - 3) < .0001f,
                    "one race view inherited the other view's geometry or UV motion");
            }
            require(f.draw.wr64WaterProducerKeys.size() == f.draw.vertexCount() &&
                f.draw.wr64WaterVertexMask.size() == f.draw.vertexCount() &&
                f.draw.wr64WaterFieldInfo.size() == f.draw.vertexCount() * 4 &&
                f.draw.wr64WaterFieldPrevPosShiftX.size() == f.draw.vertexCount() &&
                f.draw.wr64WaterFieldPrevTcShiftZ.size() == f.draw.vertexCount(),
                "two cloud appends misaligned existing parallel streams");
            // The next native workload restores Original; enabling again
            // cannot retrofit that already prepared workload at presentation.
            auto original = fixture(CloudCaptureFixtures::Captures[0], 0x060001C0);
            require(!append(original), "next Original workload retained Extended geometry");
            rasterCheck(original, false);
            const bool originalSnapshot = RT64::wr64CloudCoverageEnabled();
            RT64::setWr64CloudCoverageMode(1);
            require(!RT64::wr64AppendCloudCoverage(original.draw, original.call, View,
                -.055f, 450, originalSnapshot), "UI change retrofitted an Original workload");
            rasterCheck(original, false);
            auto extendedAgain = fixture(CloudCaptureFixtures::Captures[0], 0x060001C0);
            require(append(extendedAgain), "next Extended workload did not resume coverage");
            rasterCheck(extendedAgain, true);
        }

        // ROM-authored Rank1stShow control point: eye(2828,145,1020),
        // target(2396,-65,884), ROM A05C4/A060C, native near32/far4096.
        // Its upper-screen cloud ray has visible native opacity but gets
        // discarded by RasterPS's F3D depth ceiling even after the annulus.
        // Verify the presentation override fixes depth without moving/fading
        // geometry or changing the native packet used by sun/sky matching.
        auto prepareDepth = [] {
            auto f = fixture(CloudCaptureFixtures::Captures[0], 0x060001C0);
            f.call.shaderDesc.otherMode = f.call.callDesc.otherMode;
            interop::RenderParams params{};
            params.omL = f.call.shaderDesc.otherMode.L;
            params.omH = f.call.shaderDesc.otherMode.H;
            f.draw.renderParams.push_back(params);
            f.draw.rdpParams.push_back(f.call.callDesc.rdpParams);
            return f;
        };
        {
            auto f = prepareDepth();
            require(append(f), "ending depth fixture annulus rejected");
            const auto native = f.call.callDesc;
            const auto positions = f.draw.posFloats, uv = f.draw.tcFloats;
            const auto colors = f.draw.normColBytes;
            require(!RT64::wr64CloudCoverageEndingDepth(f.draw, f.call, View, false),
                "ending depth override affected ordinary gameplay/opening");
            require(RT64::wr64CloudCoverageEndingDepth(f.draw, f.call, View, true),
                "authenticated ending cloud depth override rejected");
            require(f.call.shaderDesc.otherMode.zSource() == G_ZS_PRIM &&
                f.draw.renderParams[0].omL == f.call.shaderDesc.otherMode.L &&
                float(f.draw.rdpParams[0].primDepth.x) == .5f &&
                !f.call.shaderDesc.otherMode.zCmp() && !f.call.shaderDesc.otherMode.zUpd(),
                "specialized/dynamic cloud shaders disagree or enabled scene depth");
            require(f.call.callDesc.otherMode.L == native.otherMode.L &&
                f.call.callDesc.otherMode.H == native.otherMode.H &&
                f.call.callDesc.triangleCount == native.triangleCount &&
                f.draw.posFloats == positions && f.draw.tcFloats == uv && f.draw.normColBytes == colors,
                "ending depth override changed native identity, projection, UVs or opacity");
            require(RT64::wr64CloudCoveragePresentationValid(f.draw, f.call, View) &&
                RT64::wr64FinalizeCloudCoverageCall(f.draw, f.call, View),
                "ending depth shader broke annulus matching or interpolation");
            const double vertical = -210.0 / std::sqrt(432.0*432.0+210.0*210.0+136.0*136.0);
            const double rayY = vertical + .92 * std::tan(3.141592653589793/6) * std::sqrt(1-vertical*vertical);
            const double rayDepth = (400.0-145.0)/rayY;
            const double originalDepth = 4096.0/4064.0 - 32.0*4096.0/4064.0/rayDepth;
            require(rayY > 0 && originalDepth > 1022.0/1024.0 && rayDepth < 450.0/.055,
                "authored podium top-edge ray does not reproduce the depth cutoff");
            require(float(f.draw.rdpParams[0].primDepth.x) < 1022.0/1024.0,
                "ending cloud presentation still clips the authored podium ray");
            rasterCheck(f, true);
        }
        for (unsigned reject = 0; reject < 5; ++reject) {
            auto f = prepareDepth();
            if (reject != 0) require(append(f), "negative depth fixture rejected annulus");
            if (reject == 1) f.draw.rdpParams.clear();
            if (reject == 2) f.call.shaderDesc.otherMode.L ^= 1;
            if (reject == 3) f.draw.renderParams[0].omH ^= 1;
            if (reject == 4) f.draw.vertexSegmentedAddresses[First] = 0x06000310; // sun, not cloud
            const auto before = f.call.shaderDesc.otherMode.L;
            require(!RT64::wr64CloudCoverageEndingDepth(f.draw, f.call, View, true) &&
                f.call.shaderDesc.otherMode.L == before,
                "Original, unrelated sun, or malformed shader was depth-overridden");
        }
        {
            std::vector<uint8_t> ram(0x800000);
            auto word = [&](uint32_t address, uint32_t value) { std::memcpy(ram.data()+address, &value, 4); };
            const float slope=-.055f, intercept=450.0f;
            std::memcpy(ram.data()+0xD4738, &slope, 4);
            std::memcpy(ram.data()+0xD473C, &intercept, 4);
            word(0xD8170,7); word(0xDAB28,1); word(0x1CE638,21);
            for (uint32_t mode : {102U,103U,42U,102U}) {
                word(0xDAB24,mode);
                auto f=prepareDepth();
                const auto submitted=RT64::wr64TestActualEndingCloudPreparation(ram.data(),f.draw,f.call,View);
                require(submitted == ((mode==102 || mode==103) ? 1U : 0U),
                    "actual cloud preparation used a stale workload state or failed to submit the new shader");
                require(f.call.callDesc.otherMode.zSource()==G_ZS_PIXEL &&
                    f.call.shaderDesc.otherMode.zSource()==(submitted ? G_ZS_PRIM : G_ZS_PIXEL),
                    "actual cloud preparation changed native identity or selected the wrong depth path");
            }
        }

        const std::function<void(Fixture &)> bad[] = {
            [](Fixture &f) { f.call.callDesc.triangleCount = 7; },
            [](Fixture &f) { f.call.callDesc.colorCombiner.L ^= 1; },
            [](Fixture &f) { f.call.callDesc.textureOn = false; },
            [](Fixture &f) { f.draw.callTiles[0].tileCopyUsed = true; },
            [](Fixture &f) { f.draw.rdpTiles[0].fmt = 0; },
            [](Fixture &f) { f.draw.rdpTiles[0].masks = 5; },
            [](Fixture &f) { f.draw.rdpTiles[0].cms = G_TX_CLAMP; },
            [](Fixture &f) { f.draw.callTiles[0].sampleWidth = 32; },
            [](Fixture &f) { f.draw.vertexSegmentedAddresses[First] = 0x06000000; },
            [](Fixture &f) { f.draw.vertexSegmentedAddresses[First + 2] = 0x06000250; },
            [](Fixture &f) { f.draw.viewProjIndices[First] = 0; },
            [](Fixture &f) { f.draw.worldTransforms[1][0][0] = 2; },
            [](Fixture &f) { f.draw.fogIndices[First] = 1; },
            [](Fixture &f) { f.draw.lightCounts[First] = 1; },
            [](Fixture &f) { f.draw.lookAtIndices[First] = 1; },
            [](Fixture &f) { f.draw.normColBytes[(First + 1) * 4] = 0; },
            [](Fixture &f) { f.draw.faceIndices[4] = First + 2; },
            [](Fixture &f) { f.draw.modifyPosUints = {First << 1, 0}; },
            [](Fixture &f) { f.draw.posFloats[First * 3] = std::numeric_limits<float>::quiet_NaN(); },
            [](Fixture &f) { f.draw.wr64WaterProducerKeys.pop_back(); }
        };
        for (const auto &mutate : bad) {
            auto f = fixture(CloudCaptureFixtures::Captures[0], 0x060001C0);
            mutate(f);
            const auto count = f.draw.vertexCount();
            const auto faces = f.draw.faceIndices.size();
            require(!append(f), "malformed or unrelated native draw was claimed");
            require(f.draw.vertexCount() == count && f.draw.faceIndices.size() == faces &&
                f.draw.wr64CloudNativeVertexCount == UINT32_MAX && !f.call.wr64CloudCoverage.faceCount,
                "rejected candidate mutated streams or native cap");
        }
        std::printf("PASS: %u actual DrawData/GameCall cloud integration checks\n", checks);
        return 0;
    }
    catch (const std::exception &error) {
        std::fprintf(stderr, "FAIL after %u checks: %s\n", checks, error.what());
        return 1;
    }
}
