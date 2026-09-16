// Reuse the existing private-ROM native harness and all-eight-course checks.
// No game asset bytes are stored in this fixture.
#define main sunny_detail_unused_main
#include "../sunny_two_player_detail/sunny_two_player_detail_test.cpp"
#undef main

extern "C" void func_8006AC84(uint8_t*, recomp_context*);
extern "C" void reference_func_80071E70(uint8_t*, recomp_context*);
namespace {
std::array<float, 3> capturedSpawn{};
unsigned spawnCalls = 0;
Ram dolphinInitial(int players = 2, int mode = 40, int phase = 1, int subtype = 1) {
    auto ram = initial(0, players, mode, phase);
    put(ram.data(), 0x801CE608, subtype);
    return ram;
}

void testDolphin(bool requested) {
    scenario = "Dolphin native loading and SetCourse requested=" + std::to_string(requested); ++scenarios;
    auto ram = dolphinInitial(); auto* rdram = ram.data();
    wr64::sunny_detail::set_diagnostic_sink(nullptr);
    wr64::sunny_detail::set_enabled(requested);
    require(wr64_dolphin_free_ride_available(rdram), "authentic Dolphin metadata not admitted");
    require(get(rdram, 0x800DC698) == get(rdram, 0x800DC6BC), "Dolphin gameplay transfer differs by player mode");
    auto oldQueue = ram, newQueue = ram;
    assetCalls.clear(); run(baseline_unk_game_load, oldQueue); const auto oldCalls = assetCalls;
    assetCalls.clear(); run(unk_game_load, newQueue);
    require(oldCalls == assetCalls && oldQueue == newQueue, "Dolphin load queue or native state changed");
    wr64_sunny_detail_begin_load(rdram);
    require(!wr64_sunny_detail_active(rdram), "Dolphin admitted before native shape transfer");
    require(wr64_sunny_detail_course_players(rdram, 2) == 2, "course descriptors changed before assets loaded");

    const uint32_t nativeShape = get(rdram, 0x800DC514), fullShape = get(rdram, 0x800DC4F0);
    require(get(rdram, fullShape + 8) == 5 && get(rdram, fullShape + 24) == 0,
        "Dolphin should have a single shape transfer and no common record");
    const auto decodedShape = independentMio(get(rdram, fullShape), get(rdram, fullShape + 4));
    require(decodedShape.size() == 0x2BE00 && decodedShape.size() < 0x30000,
        "Dolphin shape exceeds original graphics arena");
    const auto beforeShape = ram;
    transfers.clear(); run(func_80095A28, ram, nativeShape);
    require(transfers.size() == 1, "Dolphin incorrectly loaded Sunny common bank");
    require(bytes(rdram, Base, decodedShape.size()) == decodedShape, "native Dolphin shape decoder mismatch");
    require(get(rdram, 0x800D45E8) == get(const_cast<uint8_t*>(beforeShape.data()), 0x800D45E8) &&
        get(rdram, 0x801CE6E8) == get(const_cast<uint8_t*>(beforeShape.data()), 0x801CE6E8),
        "Dolphin modified absent common/segment14 bank");
    require(std::equal(ram.begin() + ((Base + 0x2BE00) & 0x7FFFFF), ram.begin() + ((Base + 0x40000) & 0x7FFFFF),
        beforeShape.begin() + ((Base + 0x2BE00) & 0x7FFFFF)), "Dolphin shape overwrote arena gap or gameplay data");
    const uint32_t data = get(rdram, 0x800DC6BC);
    require(std::find(oldCalls.begin(), oldCalls.end(), data) != oldCalls.end(), "native queue omitted Dolphin gameplay data");
    transfers.clear(); run(func_80095A28, ram, data);
    require(transfers.size() == 1 && transfers[0].destination == DataBase, "Dolphin data moved");
    require(bytes(rdram, DataBase, get(rdram, data + 4) - get(rdram, data)) ==
        std::vector<uint8_t>(rom.begin() + get(rdram, data), rom.begin() + get(rdram, data + 4)),
        "Dolphin collision/route data changed during native load");
    require(wr64_sunny_detail_course_players(rdram, 2) == 2, "course selected before matching textures");

    const uint32_t textureBase = get(rdram, 0x800D45F0), fullTexture = get(rdram, 0x800DC0E4);
    auto expected = bytes(rdram, textureBase, 0x8400);
    unsigned duplicated = 0;
    for (unsigned i = 0; i < 7; ++i) {
        const uint32_t entry = fullTexture + i * 16, flag = get(rdram, entry + 8), offset = get(rdram, entry + 12);
        auto decoded = independentMio(get(rdram, entry), get(rdram, entry + 4));
        require(flag == 1 || flag == 3, "unexpected Dolphin texture transfer flag");
        require(offset + decoded.size() <= expected.size(), "Dolphin texture exceeds native bank");
        std::copy(decoded.begin(), decoded.end(), expected.begin() + offset);
        if (flag == 3) {
            // Actual loader 80095BDC duplicates 0x1000 bytes at offset+0x2000.
            require(offset + 0x3000 <= expected.size(), "native texture duplication exceeds bank");
            std::copy_n(expected.begin() + offset, 0x1000, expected.begin() + offset + 0x2000);
            ++duplicated;
        }
    }
    require(duplicated == 2, "Dolphin native flag3 coverage missing");
    const auto tail = bytes(rdram, textureBase + 0x8400, 64);
    transfers.clear(); run(func_80095A28, ram, get(rdram, 0x800DC108));
    require(transfers.size() == 7, "Dolphin texture transfer count changed");
    require(bytes(rdram, textureBase, 0x8400) == expected, "native Dolphin texture/duplication output mismatch");
    require(bytes(rdram, textureBase + 0x8400, 64) == tail, "Dolphin textures overwrite following bank");
    require(wr64_sunny_detail_water_active(rdram), "full Dolphin material not active");
    require(wr64_sunny_detail_course_players(rdram, 2) == 1, "Dolphin real descriptors not selected");
    require(wr64_sunny_detail_course_players(rdram, 1) == 1 && wr64_sunny_detail_course_players(rdram, 3) == 3,
        "local player selector changed unrelated value");
    require(!RT64::wr64RTTwoPlayerAssetsReady(rdram, 0), "renderer enabled before SetCourse applied visual roots");

    auto nativeSingle = ram, nativeVS = ram, changed = ram;
    put(nativeSingle.data(), 0x800DAB28, 1);
    run(reference_func_80071E70, nativeSingle);
    run(baseline_func_80071E70, nativeVS);
    run(func_80071E70, changed);
    if (changed != nativeSingle) {
        unsigned shown = 0;
        for (uint32_t p = 0; p < RamSize && shown < 12; p += 4) {
            const uint32_t address = p + 0x80000000U;
            if (get(changed.data(), address) == get(nativeSingle.data(), address)) continue;
            std::cerr << "SetCourse difference " << std::hex << address << " native="
                << get(nativeSingle.data(), address) << " changed=" << get(changed.data(), address) << std::dec << '\n'; ++shown;
        }
    }
    require(changed == nativeSingle, "Dolphin SetCourse differs from authored tables with native 2P object filtering");
    require(changed != nativeVS, "Dolphin still uses unused VS descriptor stubs");
    require(get(changed.data(), 0x800DAB28) == 2 && get(changed.data(), 0x801CE608) == 1,
        "Dolphin SetCourse changed actual two-player identity");
    // Replay the complete native placement builder against the actual course
    // descriptors. Capture only its final matrix-construction boundary.
    auto spawned = changed;
    put(spawned.data(), 0x801982F0, 2);
    put(spawned.data(), 0x800D48DC, 0); put(spawned.data(), 0x800D48E0, 1);
    std::array<std::array<float, 3>, 2> positions{};
    spawnCalls = 0;
    for (uint32_t rider = 0; rider < 2; ++rider) {
        recomp_context ctx{}; ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(Stack); ctx.r4 = rider; ctx.r5 = S32(0x807FE000);
        func_8006AC84(spawned.data(), &ctx);
        require(uint32_t(ctx.r29) == Stack, "Dolphin native spawn stack unbalanced");
        positions[rider] = capturedSpawn;
    }
    require(spawnCalls == 2, "Dolphin spawn builder failed to place both riders");
    double separation2 = 0;
    for (unsigned axis = 0; axis < 3; ++axis) {
        require(std::isfinite(positions[0][axis]) && std::isfinite(positions[1][axis]), "Dolphin spawn is nonfinite");
        const double d = positions[0][axis] - positions[1][axis]; separation2 += d * d;
    }
    require(separation2 > 16 * 16 && separation2 < 512 * 512, "Dolphin riders overlap or spawn far apart");
    require(RT64::wr64RTTwoPlayerAssetsReady(changed.data(), 0), "renderer did not receive Dolphin loaded marker");
    require(!RT64::wr64RTTwoPlayerAssetsReady(rdram, 0), "renderer marker leaked to different RDRAM instance");
    for (bool setting : {false, true}) {
        wr64::sunny_detail::set_enabled(setting);
        require(wr64_sunny_detail_water_active(changed.data()), "resident Dolphin changes with scenery toggle");
        auto retry = changed; run(func_80071E70, retry);
        require(retry == changed, "Dolphin retry changed loaded setup");
    }
    for (uint32_t p : {0x800DAB28U, 0x801CE638U, 0x801CE608U, 0x800DAB24U, 0x800D8170U}) {
        auto outside = changed;
        put(outside.data(), p, p == 0x800DAB28 ? 1 : p == 0x800DAB24 ? 39 : p == 0x800D8170 ? 1 : 0);
        require(wr64_sunny_detail_course_players(outside.data(), 2) == 2, "Dolphin descriptor override leaked out of scope");
    }
}

void testDolphinRejection() {
    scenario = "Dolphin metadata and lifecycle rejection"; ++scenarios;
    require(!wr64_dolphin_free_ride_available(nullptr), "null metadata admitted");
    for (uint32_t address : {0x800DC4F0U, 0x800DC514U, 0x800DC698U, 0x800DC6BCU,
        0x800DC0E4U, 0x800DC108U, 0x800DCE3CU, 0x800DCE60U, 0x800D5470U,
        0x800DC1B4U, 0x800DC354U, 0x800DB7E8U, 0x800DBC68U, 0x800DC53CU,
        0x800D699CU, 0x800D69CCU, 0x800D69FCU, 0x800D6A2CU,
        0x800D6B1CU, 0x800D6B4CU, 0x800D6B7CU, 0x800D6BACU}) {
        auto bad = dolphinInitial();
        put(bad.data(), address, get(bad.data(), address) ^ 0x100);
        require(!wr64_dolphin_free_ride_available(bad.data()), "malformed Dolphin metadata admitted in menu");
        wr64::sunny_detail::set_enabled(true); wr64_sunny_detail_begin_load(bad.data());
        require(wr64_sunny_detail_assets(bad.data(), 0x800DC350) == 0x800DC350,
            "malformed Dolphin metadata redirected native transfer");
    }
    for (int players : {1, 2}) for (int subtype : {0, 1, 2, 4}) for (int mode : {7, 39, 40, 41, 45, 46}) {
        auto ram = dolphinInitial(players, mode, 1, subtype);
        wr64::sunny_detail::set_enabled(false); wr64_sunny_detail_begin_load(ram.data());
        const bool eligible = players == 2 && subtype == 1 && mode == 40;
        require(wr64_sunny_detail_assets(ram.data(), 0x800DC350) == (eligible ? 0x800DC1B0U : 0x800DC350U),
            "Dolphin initial load scope incorrect");
    }
    wr64_sunny_detail_begin_load(nullptr);
    require(!wr64_sunny_detail_active(nullptr) && wr64_sunny_detail_course_players(nullptr, 2) == 2,
        "Dolphin stale latch survived reset");
}
}

extern "C" void SysUtils_MatrixLookAt(uint8_t* rdram, recomp_context* ctx) {
    ++spawnCalls;
    for (unsigned axis = 0; axis < 3; ++axis)
        capturedSpawn[axis] = std::bit_cast<float>(get(rdram, uint32_t(ctx->r29) + 0x20 + axis * 4));
}

int main(int argc, char** argv) {
    require(argc == 2, "pass private USA Rev1 ROM");
    std::ifstream input(argv[1], std::ios::binary); require(bool(input), "cannot open private ROM");
    rom.assign(std::istreambuf_iterator<char>(input), {});
    require(rom.size() >= 0x800000 && be32(rom, 0) == 0x80371240, "invalid native ROM image");
    testDolphin(false); testDolphin(true); testDolphinRejection();
    testAllRaceCourses();
    std::cout << "PASS " << scenarios << " scenarios, " << assertions << " assertions, " << nativeAccesses
        << " checked native memory accesses; Dolphin full load, exact authored SetCourse, all eight race courses preserved.\n";
}
