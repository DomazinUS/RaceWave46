#define wr64_experimental_viewport_borders legacy_fixture_viewport_borders
#include "native_roundness_support.inc"
#undef wr64_experimental_viewport_borders
#include "native_water_producer.viewport.inc"
#include "common/rt64_wr64_native_water_distance.h"
#include <exception>
#ifdef _WIN32
#include <crtdbg.h>
#include <windows.h>
#endif

extern "C" void func_8004F9E0(uint8_t*, recomp_context*);
extern "C" void func_80050204(uint8_t*, recomp_context*);

struct ProducerDraw {
    std::vector<float> posFloats, velFloats;
    std::vector<uint32_t> vertexSegmentedAddresses, faceIndices;
    std::vector<uint16_t> viewProjIndices, worldIndices;
    std::array<RT64::Wr64NativeWaterDistanceView, 3> wr64NativeWaterDistance{};
};

static double faceArea(const ProducerDraw &draw, uint32_t face) {
    double p[3][2]{};
    for (uint32_t c = 0; c < 3; ++c) for (uint32_t axis = 0; axis < 2; ++axis)
        p[c][axis] = draw.posFloats[draw.faceIndices[face * 3 + c] * 3 + axis * 2];
    return (p[1][0]-p[0][0])*(p[2][1]-p[0][1])-(p[1][1]-p[0][1])*(p[2][0]-p[0][0]);
}

static void preserveNative(const ProducerDraw &native, const ProducerDraw &draw) {
    require(native.faceIndices == draw.faceIndices && native.vertexSegmentedAddresses == draw.vertexSegmentedAddresses &&
        native.viewProjIndices == draw.viewProjIndices && native.worldIndices == draw.worldIndices, "Native topology or ownership changed");
    const size_t primaryEnd = native.faceIndices.size() - 36;
    for (size_t v = 0; v < native.vertexSegmentedAddresses.size(); ++v) {
        require(native.posFloats[v*3+1] == draw.posFloats[v*3+1], "Native wave/tide Y changed");
        if (v < primaryEnd) for (uint32_t axis = 0; axis < 3; ++axis)
            require(native.posFloats[v*3+axis] == draw.posFloats[v*3+axis], "Native primary position changed");
    }
}

static int runProducer(int argc, char **argv) {
    require(argc == 3, "Private ROM and RAM arguments required");
    std::ifstream input(argv[1], std::ios::binary);
    rom.assign(std::istreambuf_iterator<char>(input), {});
    require(wr64::rom_patch::apply_if_unpatched(rom), "ROM patch failed");
    std::ifstream archiveInput(argv[2], std::ios::binary);
    Ram archived{std::istreambuf_iterator<char>(archiveInput), {}};
    require(archived.size() == RamSize, "Native input archive missing");
    uint32_t cases = 0, modes = 0, nativeDegenerateCases = 0, nativeMixedCases = 0, fallbacks = 0;
    for (uint32_t players : {1U, 2U}) for (uint32_t sea : {0U, 1U, 2U}) for (uint32_t view = 0; view < players; ++view) {
        if (players == 1 && sea == 0) continue; // Existing dense12-ring suite owns this sheet.
        for (uint32_t heading = 0; heading < 8; ++heading) for (int center : {0, 9000}) {
            currentCourse = 1; active = false;
            auto ram = archived; auto *rdram = ram.data();
            put(rdram, 0x800DAB28, players); put(rdram, 0x800DAB2C, view); put(rdram, 0x801CE64C, sea);
            put(rdram, 0x801518B8, 0x80300000); put(rdram, 0x8011F8E0, 0);
            recomp_context init{}; init.f_odd = &init.f0.u32h; init.r29 = S32(Stack);
            func_8004F9E0(rdram, &init);
            for (uint32_t p = 0; p < 2; ++p) {
                put(rdram, 0x80192420 + p*0x1C, center + p*256); put(rdram, 0x80192424 + p*0x1C, center - p*256);
                pf(rdram, 0x80227C80 + p*0x10C + 0xF0, float(std::cos(heading*3.141592653589793/4)));
                pf(rdram, 0x80227C80 + p*0x10C + 0xF4, float(std::sin(heading*3.141592653589793/4)));
            }
            const uint32_t producerView = sea == 1 ? 0 : view;
            recomp_context produce{}; produce.f_odd = &produce.f0.u32h; produce.r29 = S32(Stack);
            produce.r4 = producerView; produce.r5 = S32(0x80300000 + (producerView ? 0x170D8 : 0x13D68));
            func_80050204(rdram, &produce);

            // Native draw setup is independent of wave simulation. Use its
            // shipped source viewports/triangles, then read actual producer bytes.
            auto drawRam = initial(players, view, 0, sea, 1);
            Decoder decoder(drawRam, 0); decoder.decode(run(drawRam, false)); decoder.calls.clear(); decoder.decode(nativeWater(drawRam));
            ProducerDraw native;
            for (const auto &call : decoder.calls) for (uint32_t source : call.sources) {
                if(RT64::wr64FarWaterSourceOwner(call.domain) != (players == 2 ? int32_t(view+1) : 0)) {
                    const auto &d=call.domain;
                    std::cerr<<"REJECT_VIEW players="<<players<<" sea="<<sea<<" view="<<view<<" perspective="<<d.perspective<<" scale="<<d.scale[0]<<","<<d.scale[1]<<","<<d.scale[2]<<" translate="<<d.translate[0]<<","<<d.translate[1]<<","<<d.translate[2]<<" scissor="<<d.scissor[0]<<","<<d.scissor[1]<<","<<d.scissor[2]<<","<<d.scissor[3]<<"\n";
                }
                require(RT64::wr64FarWaterSourceOwner(call.domain) == (players == 2 ? int32_t(view+1) : 0), "Actual source viewport rejected");
                const uint32_t v = uint32_t(native.faceIndices.size());
                native.faceIndices.push_back(v); native.vertexSegmentedAddresses.push_back(source);
                native.viewProjIndices.push_back(uint16_t(7+view)); native.worldIndices.push_back(3);
                const gpr address = gpr(S32(0x80300000 + (source & 0xFFFFFF)));
                for (uint32_t axis = 0; axis < 3; ++axis) {
                    native.posFloats.push_back(float(MEM_H(axis*2, address))); native.velFloats.push_back(0);
                }
            }
            const uint32_t triangles = uint32_t(native.faceIndices.size()/3), owner = players == 2 ? view+1 : 0;
            require(triangles == (sea == 1 ? 1548U : 612U), "Unexpected native water topology");
            bool zero = false, positive = false, negative = false;
            for (uint32_t t = triangles-12; t < triangles; ++t) {
                const double area = faceArea(native, t); zero |= std::abs(area) < 1e-5; positive |= area > 1e-5; negative |= area < -1e-5;
            }
            nativeDegenerateCases += zero; nativeMixedCases += positive && negative;
            const Ram preservedRam = ram;
            ProducerDraw original;
            for (uint32_t mode = 0; mode < 6; ++mode) {
                auto draw = native;
                require(RT64::wr64ExtendNativeWaterFan(draw, 0, triangles, 7+view, owner, mode), "Actual native producer fan rejected");
                preserveNative(native, draw);
                const auto &metadata = draw.wr64NativeWaterDistance[owner];
                if (!mode) {
                    require(native.posFloats == draw.posFloats && native.velFloats == draw.velFloats, "Original native bytes changed");
                    require(metadata.coherent == !(zero || (positive && negative)), "Native degeneracy metadata incorrect");
                    original = draw;
                } else {
                    require(metadata.coherent, "Expanded fan incoherent");
                    for (uint32_t t = triangles-12; t < triangles; ++t) require(faceArea(draw, t) < -1e-5, "Expanded native fan folded");
                    if (!original.wr64NativeWaterDistance[owner].coherent) {
                        require(RT64::wr64FinalizeNativeWaterDistance(draw, original), "Native overlap fallback did not execute");
                        for (const auto &v : metadata.vertices) for (uint32_t axis : {0U, 2U})
                            require(draw.velFloats[v.vertex*3+axis] == v.velocity[axis], "Interpolated through native overlapping wedge");
                        ++fallbacks;
                    }
                }
                ++modes;
            }
            require(ram == preservedRam, "Renderer distance helper changed native RAM");
            ++cases;
        }
    }
    require(nativeDegenerateCases > 0 && nativeMixedCases > 0 && fallbacks > 0, "Native defect fixtures did not execute");
    std::cout << "PASS: " << cases << " native producer cases, " << modes << " modes, " << nativeDegenerateCases
        << " degenerate cases, " << nativeMixedCases << " mixed-winding cases, " << fallbacks << " temporal fallbacks, "
        << checks << " checks, " << accesses << " checked native accesses\n";
    return 0;
}

int main(int argc, char **argv) {
#ifdef _WIN32
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    for (int type : {_CRT_WARN, _CRT_ERROR, _CRT_ASSERT}) {
        _CrtSetReportMode(type, _CRTDBG_MODE_FILE); _CrtSetReportFile(type, _CRTDBG_FILE_STDERR);
    }
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#endif
    std::set_terminate([] { std::cerr << "Unhandled native producer test exception\n"; std::_Exit(99); });
    try { return runProducer(argc, argv); }
    catch (const std::exception &e) { std::cerr << "ERROR " << e.what() << '\n'; return 98; }
    catch (...) { std::cerr << "ERROR unknown exception\n"; return 97; }
}
