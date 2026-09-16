#include "common/rt64_wr64_rt_beam.h"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>

static unsigned checks = 0;
static void require(bool value, const char *message) {
    ++checks;
    if (!value) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
int main() {
    using namespace RT64;
    // Decode the actual four F3DWAVE quad words independently of the helper.
    constexpr uint32_t quads[] = {0x0f00050a,0x00141905,0x230f0a1e,0x14231e19};
    for (int family = 0; family < 2; ++family) {
        const uint32_t base = family ? 0x0102c838 : 0x0102bfe8;
        std::array<uint32_t,24> sources{};
        for (unsigned q = 0; q < 4; ++q) {
            uint32_t v[4];
            for (unsigned i = 0; i < 4; ++i) v[i] = base + ((quads[q] >> (24-8*i)) & 255) / 5 * 16;
            const unsigned corners[] = {0,1,2,0,2,3};
            for (unsigned i = 0; i < 6; ++i) sources[q*6+i] = v[corners[i]];
        }
        require(wr64RTTwilightBeamSourceFamily(sources.data(),sources.size()) == family,"native quad source family");
        auto changed = sources;
        for (unsigned face = 0; face < 8; ++face) {
            std::rotate(changed.begin()+face*3,changed.begin()+face*3+1,changed.begin()+face*3+3);
        }
        require(wr64RTTwilightBeamSourceFamily(changed.data(),24) == family,"cyclic face rotation");
        for (unsigned corner = 0; corner < 24; ++corner) {
            changed = sources; ++changed[corner];
            require(wr64RTTwilightBeamSourceFamily(changed.data(),24) == -1,"unaligned vertex rejected");
            changed = sources; changed[corner] = (family ? 0x0102bfe8 : 0x0102c838) + (sources[corner]-base);
            require(wr64RTTwilightBeamSourceFamily(changed.data(),24) == -1,"mixed family rejected");
        }
        changed = sources; std::swap(changed[0],changed[1]);
        require(wr64RTTwilightBeamSourceFamily(changed.data(),24) == -1,"reversed face rejected");
        changed = sources; std::copy_n(changed.begin()+3,3,changed.begin());
        require(wr64RTTwilightBeamSourceFamily(changed.data(),24) == -1,"duplicated face rejected");
        for (unsigned count = 0; count < 30; ++count) {
            if (count != 24) require(wr64RTTwilightBeamSourceFamily(sources.data(),count) == -1,"bounded count");
        }
    }
    require(wr64RTTwilightBeamSourceFamily(nullptr,24) == -1,"null source guard");
    auto material = [](uint32_t ccL=0xfc127e24, uint32_t ccH=0xfffff3f9,
        uint32_t omL=0x005049d8,uint32_t omH=0x00082cff,uint32_t geometry=0x2205,
        uint32_t tris=8,uint32_t tiles=1) {
        return wr64RTTwilightBeamMaterial(ccL,ccH,omL,omH,geometry,tris,tiles);
    };
    require(material(),"native beam material");
    require(material(0xfc127e24,0xfffff3f9,0x005049d8,0x00082c3f),"inherited dither variation");
    for (unsigned bit = 0; bit < 32; ++bit) {
        require(!material(0xfc127e24^(1U<<bit)),"exact combiner low");
        require(!material(0xfc127e24,0xfffff3f9^(1U<<bit)),"exact combiner high");
        require(!material(0xfc127e24,0xfffff3f9,0x005049d8^(1U<<bit)),"exact blender and alpha mode");
    }
    for (uint32_t invalid : {0x00182cffU,0x0008acffU,0x00080cffU,0x00002cffU})
        require(!material(0xfc127e24,0xfffff3f9,0x005049d8,invalid),"unsupported texture/cycle mode");
    for (uint32_t invalid : {0x2204U,0x2201U,0x0205U,0x3205U,0x22205U,0x12205U,0x42205U})
        require(!material(0xfc127e24,0xfffff3f9,0x005049d8,0x82cff,invalid),"unsupported geometry mode");
    require(!material(0xfc127e24,0xfffff3f9,0x005049d8,0x82cff,0x2205,7),"complete prism required");
    require(!material(0xfc127e24,0xfffff3f9,0x005049d8,0x82cff,0x2205,8,2),"single texture required");
    std::cout << "PASS " << checks << " native Twilight beam identity checks\n";
}
