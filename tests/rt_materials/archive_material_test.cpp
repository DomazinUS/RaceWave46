#include "common/rt64_wr64_rt_material.h"
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

static unsigned checks = 0;
static void require(bool result, const char *message) {
    ++checks;
    if (!result) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
static uint32_t little32(const uint8_t *p) {
    return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}
static uint64_t little64(const uint8_t *p) { return little32(p) | (uint64_t(little32(p + 4)) << 32); }

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: wr64_rt_material_archive_test <capture-20260728-034653/rdram.bin> <events.bin>\n";
        return 2;
    }
    std::ifstream ramFile(argv[1], std::ios::binary);
    const std::vector<uint8_t> ram((std::istreambuf_iterator<char>(ramFile)), {});
    require(ram.size() == 0x800000, "original word-swapped RAM has eight MiB");
    auto nativeByte = [&](uint32_t address) { return ram[address ^ 3]; };
    struct Texture { const char *name; uint32_t address, texels, transparent; uint64_t hash; };
    // No image data is embedded: addresses, alpha counts and byte hashes were
    // independently measured from native assets matched against named source.
    const Texture textures[] = {
        { "start_pole_txt", 0x29E960, 2048, 468, 0xF1EA72B0963971A6ULL },
        { "check_rope_txt", 0x29D960, 1024, 768, 0x65702109E2C96A24ULL },
        { "start_base_txt", 0x29E160, 1024, 0, 0x02116E97C9666A06ULL },
        { "checker_txt", 0x29C960, 1024, 0, 0x5B6EBCCD003BB620ULL },
        { "start_f1_txt", 0x29A960, 2048, 0, 0x75B20018211B15E4ULL },
        { "start_f2_txt", 0x29B960, 2048, 0, 0xD52DD726854F4F6FULL },
        { "i_palm_4_txt", 0x2DC800, 2048, 1515, 0xB68866C57D05042DULL },
        { "palm_r1_txt", 0x2DD800, 2048, 1325, 0x094B5998EEC31FB4ULL },
        { "palm_r2_txt", 0x2DE800, 2048, 1189, 0x74DA149C6B8F8A88ULL }
    };
    for (const auto &texture : textures) {
        uint64_t hash = 14695981039346656037ULL;
        uint32_t transparent = 0;
        for (uint32_t i = 0; i < texture.texels * 2; ++i) {
            const uint8_t value = nativeByte(texture.address + i);
            hash = (hash ^ value) * 1099511628211ULL;
            if ((i & 1) && !(value & 1)) ++transparent;
        }
        require(hash == texture.hash, "actual complete RGBA16 texture bytes match measured native asset");
        require(transparent == texture.transparent, "actual binary-alpha holes match native asset");
        std::cout << "ASSET " << texture.name << " transparent=" << transparent << '/' << texture.texels << '\n';
    }

    // Read the recorded original DrawCall, not a reconstructed OtherMode state.
    // Original recorder format: eight-byte file header, then 288-byte records.
    // First 128-byte DrawCall blob chunk contains native CC/OtherMode at88/96.
    std::ifstream events(argv[2], std::ios::binary);
    require(bool(events), "matching native event archive is readable");
    events.seekg(8);
    std::array<uint8_t, 288> record{};
    uint32_t found = 0;
    while (events.read(reinterpret_cast<char *>(record.data()), std::streamsize(record.size()))) {
        if (little32(record.data() + 28) != 23 || little64(record.data() + 40) != 1966 ||
            little64(record.data() + 152) != 128) continue;
        const uint64_t tag = little64(record.data() + 144);
        if (uint32_t(tag) != 0) continue;
        const uint32_t draw = uint32_t(tag >> 32);
        if (draw < 56 || draw > 58) continue;
        const uint32_t bit = 1u << (draw - 56);
        require(!(found & bit), "native draw appears once in the selected task");
        found |= bit;
        const auto *data = record.data() + 160;
        require(little32(data + 88) == 0xFC127FFF && little32(data + 92) == 0xFFFFF238,
            "native START combiner matches observed material");
        require(little32(data + 100) == 0x00182CFF, "native START OtherMode.H matches capture");
        const uint32_t expectedMode = draw == 56 ? 0xC8112078 : 0xC8113078;
        require(little32(data + 96) == expectedMode, "native START OtherMode.L matches capture");
        require(little32(data + 40) == (draw == 56 ? 2u : draw == 57 ? 8u : 16u),
            "captured opaque lettering, rope and support triangle counts match");
        require(RT64::wr64RTClassifyMaterial(little32(data + 96)) ==
            (draw == 56 ? RT64::Wr64RTMaterial::Opaque : RT64::Wr64RTMaterial::Cutout),
            "production helper classifies actual captured material correctly");
        if (found == 7) break;
    }
    require(found == 7, "matching archive supplies all three original START draws");
    std::cout << "PASS " << checks << " actual native asset/material checks\n";
}
