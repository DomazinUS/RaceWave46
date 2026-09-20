// Standalone comparison of the production matcher with the archived exact mappings.
#define XXH_INLINE_ALL
#include <filesystem>
#include <fstream>
#include <iostream>
#include "gbi/rt64_f3d.h"
#include "common/rt64_wr64_dolphin_texture.h"
using namespace RT64;
namespace fs = std::filesystem;
void require(bool ok, const std::string &message) { if (!ok) throw std::runtime_error(message); }
std::vector<uint8_t> read(const fs::path &p) {
    std::ifstream f(p, std::ios::binary); require(bool(f), "Missing input: " + p.string());
    return {std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()};
}
struct Native {
    std::vector<uint8_t> tmem;
    LoadTile tile{};
    uint32_t width, height, tlut;
};
Native native(const fs::path &dump, const std::string &hash) {
    auto j = json::parse(read(dump / (hash + ".v5.tile.json")));
    Native n;
    n.width = j.at("width"); n.height = j.at("height");
    const auto &t = j.at("tile");
#define FIELD(name) n.tile.name = t.at(#name)
    FIELD(fmt); FIELD(siz); FIELD(line); FIELD(tmem); FIELD(palette); FIELD(cms); FIELD(cmt);
    FIELD(masks); FIELD(maskt); FIELD(shifts); FIELD(shiftt); FIELD(uls); FIELD(ult); FIELD(lrs); FIELD(lrt);
#undef FIELD
    n.tlut = j.at("tlut") == "None" ? 0 : j.at("tlut") == "RGBA16" ? G_TT_RGBA16 : G_TT_IA16;
    n.tmem = read(dump / (hash + ".v5.tmem"));
    return n;
}
std::string match(const Wr64DolphinTextureIndex &index, const Native &n) {
    return index.match(n.tmem.data(), n.tmem.size(), n.width, n.height, n.tlut, n.tile);
}
int main(int argc, char **argv) {
    try {
        require(argc == 4, "Usage: cpu_matcher source_dds_dir native_dump_dir mapping_report");
        const fs::path source = argv[1], dump = argv[2];
        auto report = json::parse(read(argv[3]));
        Wr64DolphinTextureIndex index;
        for (const auto &entry : fs::recursive_directory_iterator(source)) {
            if (entry.is_regular_file()) index.addPath(fs::relative(entry.path(), source).generic_string());
        }
        require(index.size() == 2266, "Expected all 2266 source DDS identities indexed");
        std::unordered_map<std::string, std::string> expected;
        std::unordered_map<int, size_t> formats;
        Native paletteSample;
        bool hasPalette = false;
        for (const auto &m : report.at("matches")) {
            auto hash = m.at("rt64").get<std::string>(), path = m.at("file").get<std::string>();
            auto n = native(dump, hash);
            auto actual = match(index, n);
            require(actual == path, "Exact mapping mismatch " + hash + ": expected " + path + ", got " + actual);
            expected[hash] = path;
            ++formats[m.at("gxFormat").get<int>()];
            if (n.tile.fmt == 2 && n.tile.siz == 1) { paletteSample = n; hasPalette = true; }
        }
        require(expected.size() == 308, "Expected 308 independently generated exact mappings");
        size_t total = 0, hits = 0, misses = 0;
        for (const auto &entry : fs::directory_iterator(dump)) {
            auto name = entry.path().filename().string();
            if (name.size() != 24 || name.substr(16) != ".v5.tmem") continue;
            const auto hash = name.substr(0, 16);
            auto actual = match(index, native(dump, hash));
            auto known = expected.find(hash);
            require(known == expected.end() ? actual.empty() : actual == known->second,
                "Full dump result differs from independent archived report: " + hash);
            ++total; if (actual.empty()) ++misses; else ++hits;
        }
        require(total == 482 && hits == 308 && misses == 174, "Unexpected full dump totals");
        require(hasPalette && !match(index, paletteSample).empty(), "CI8 control must match");
        for (size_t i = 0x800; i < paletteSample.tmem.size(); ++i) paletteSample.tmem[i] ^= 0xFF;
        require(match(index, paletteSample).empty(), "Wrong palette must not match the same CI8 indices");
        auto control = native(dump, expected.begin()->first);
        require(index.match(control.tmem.data(), 4095, control.width, control.height, control.tlut, control.tile).empty(), "Short TMEM must be rejected");
        require(index.match(nullptr, 4096, control.width, control.height, control.tlut, control.tile).empty(), "Null TMEM must be rejected");
        Wr64DolphinTextureIndex ambiguous;
        const auto p = expected.begin()->second;
        ambiguous.addPath(p); ambiguous.addPath("duplicate/" + p);
        require(match(ambiguous, control).empty(), "Duplicate identities must be rejected");
        std::cout << "PASS: indexed 2266 source DDS names; all 308 archived exact mappings reproduced.\n";
        std::cout << "PASS: all 482 native dumps agree: 308 exact matches, 174 retained-native misses.\n";
        for (auto format : {2, 3, 5, 6, 9}) std::cout << "GX format " << format << ": " << formats[format] << " exact matches.\n";
        std::cout << "PASS: CI8 wrong-palette rejection, short/null TMEM rejection, duplicate-name ambiguity rejection.\n";
        return 0;
    } catch (const std::exception &e) { std::cerr << "FAIL: " << e.what() << '\n'; return 1; }
}
