#include "recomp.h"
#include "wr64_sunny_water.hpp"
#include <algorithm>
#include <bit>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

extern "C" void Draw_WaterEffects(uint8_t*, recomp_context*);
extern "C" void baseline_Draw_WaterEffects(uint8_t*, recomp_context*);
namespace {
using Ram = std::vector<uint8_t>;
using Fn = void(*)(uint8_t*, recomp_context*);
constexpr uint32_t RamSize=0x800000, List=0x80500000, Limit=List+0x1000, Stack=0x807FF000;
bool enabled=false;
unsigned checks=0, runs=0;
uint64_t accesses=0;
void require(bool valid, const char* message) {
    ++checks;
    if(!valid) { std::cerr<<"FAIL: "<<message<<'\n'; std::exit(1); }
}
void put(Ram& ram,uint32_t at,uint32_t value) { uint8_t* rdram=ram.data(); MEM_W(0,S32(at))=value; }
uint32_t get(const Ram& ram,uint32_t at) { return *reinterpret_cast<const uint32_t*>(ram.data()+(at&0x7fffff)); }
Ram initial(unsigned players,unsigned view,unsigned grid,unsigned course=1) {
    Ram r(RamSize,0);
    put(r,0x800D8170,course); put(r,0x800DAB28,players); put(r,0x800DAB2C,view); put(r,0x801CE64C,grid);
    for(unsigned p=0;p<2;++p) {
        const uint32_t environment=0x801CB058+p*0x110;
        put(r,environment+0x108,std::bit_cast<uint32_t>(p?96.0f:192.0f));
        put(r,environment+0x88,60+p*25);put(r,environment+0x8C,80+p*25);
        put(r,environment+0x90,100+p*25);put(r,environment+0x94,255);
        put(r,environment+0x98,350+p*20);put(r,environment+0x9C,950+p*20);
    }
    uint8_t* rdram=r.data(); MEM_H(0,S32(0x800D9890))=160; MEM_B(0,S32(0x800D9894))=1;
    // Sentinels prove the draw does not mutate physics, camera or either mesh.
    std::fill(r.begin()+0x220000,r.begin()+0x230000,0x35);
    return r;
}
std::vector<uint32_t> render(Fn fn,Ram& ram) {
    const auto before=ram;
    recomp_context ctx{}; ctx.f_odd=&ctx.f0.u32h; ctx.r4=S32(List); ctx.r29=S32(Stack);
    fn(ram.data(),&ctx); ++runs;
    const uint32_t end=uint32_t(ctx.r2);
    require(end>=List && end<=Limit && (end-List)%8==0,"display-list bounds/alignment");
    require(std::equal(ram.begin(),ram.begin()+(List&0x7fffff),before.begin()),"draw modified game state before display list");
    require(uint32_t(ctx.r29)==Stack,"unbalanced native draw stack");
    require(std::equal(ram.begin()+(Limit&0x7fffff),ram.begin()+((Stack-0x78)&0x7fffff),before.begin()+(Limit&0x7fffff)),"draw modified game state after display list");
    require(std::equal(ram.begin()+(Stack&0x7fffff),ram.end(),before.begin()+(Stack&0x7fffff)),"draw modified game state above stack");
    std::vector<uint32_t> words;
    for(uint32_t p=List;p<end;p+=4) words.push_back(get(ram,p));
    return words;
}
bool command(const std::vector<uint32_t>& words,uint32_t a,uint32_t b) {
    for(size_t i=0;i+1<words.size();i+=2) if(words[i]==a&&words[i+1]==b) return true;
    return false;
}
}
// Load/state guards are tested with the production loader in sunny_two_player_detail.
// This fixture isolates the native renderer's behavior for either resolved gate result.
extern "C" uint32_t wr64_sunny_detail_water_active(uint8_t*) { return enabled; }
extern "C" void* wr64_test_address(uint8_t* r,uint64_t at,unsigned width,const char*,int) {
    const uint32_t addr=uint32_t(at); ++accesses;
    require(addr>=0x80000000 && addr<=0x80800000-width,"native RDRAM access outside allocation");
    return r+(addr&0x7fffff);
}
extern "C" void do_break(uint32_t) { require(false,"native renderer break"); }
int main() {
    for(unsigned course=1;course<=8;++course) for(unsigned view=0;view<2;++view) for(unsigned grid : {0u,1u,2u}) {
        enabled=false;
        auto a=initial(2,view,grid,course),b=a;
        const auto original=render(baseline_Draw_WaterEffects,a);
        require(original==render(Draw_WaterEffects,b),"disabled material must be byte-identical to native 2P");
        require(command(original,0xFD100000,0x08000400),"native 2P RGBA16 texture missing");
        const uint32_t geometry=grid==1?0x010082F0:(view?0x0100E680:0x0100D258);
        require(command(original,0x06000000,geometry),"native two-player wave list missing");
        enabled=true;
        auto c=initial(2,view,grid,course);
        const auto enhanced=render(Draw_WaterEffects,c);
        require(command(enhanced,0xFD180000,0x08000400),"enhanced RGBA32 texture missing");
        require(command(enhanced,0xB900031D,(course==4 && grid!=1)?0xC81049D8:0x005049D8),"native translucent water mode missing");
        require(command(enhanced,0x06000000,geometry),"enhancement replaced per-player geometry");
        require(!command(enhanced,0x06000000,0x0100B590),"enhancement incorrectly selected 1P mesh");
        require(original!=enhanced,"enhancement has no native rendering effect");
        auto d=initial(1,view,grid,course);
        // Native 1P has one luminance record. Supply this view's native value to
        // the independent baseline oracle; the enhanced path must select that
        // existing record itself, without changing the shared RAM.
        if(view) put(d,0x801CB160,get(d,0x801CB270));
        const auto one=render(baseline_Draw_WaterEffects,d);
        // Only sea mode 0 changes its final geometry address. Mode 1 uses the
        // common native mesh; mode 2 already selects per-player meshes in 1P.
        auto expected=one;
        if(grid==0) expected.back()=geometry;
        require(enhanced==expected,"material does not exactly match native 1P rendering");
        if(course==4) require(command(enhanced,0xB7000000,0x00010205),"Drake fog geometry mode missing");
    }
    enabled=false;
    auto a=initial(1,0,0),b=a;
    require(render(baseline_Draw_WaterEffects,a)==render(Draw_WaterEffects,b),"1P native behavior changed");
    require(wr64_sunny_water_material_players(a.data(),7)==7,"inactive hook must preserve its input");
    enabled=true;
    require(wr64_sunny_water_material_players(nullptr,7)==7,"null activation must retain native material");
    put(a,0x800DAB2C,2);
    require(wr64_sunny_water_material_players(a.data(),7)==7,"invalid player must retain native material");
    put(a,0x800DAB2C,1);
    require(wr64_sunny_water_environment(a.data(),0x80000000)==0x80000000,"unrelated load base changed");
    std::cout<<"PASS "<<runs<<" native draws, "<<checks<<" checks, "<<accesses<<" checked memory accesses\n";
}
