#include "recomp.h"
#include "wr64_sunny_animals_load.hpp"
#include "wr64_sunny_detail.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

extern "C" {
void func_800AC184(uint8_t*,recomp_context*);
void baseline_animal_init(uint8_t*,recomp_context*);
void func_8009684C(uint8_t*,recomp_context*);
void func_80096048(uint8_t*,recomp_context*);
void Mio0_Decompress(uint8_t*,recomp_context*);
}
namespace {
using Ram=std::vector<uint8_t>;
std::vector<uint8_t> rom;
bool active=false;
unsigned assertions=0;
uint64_t accesses=0;
void require(bool value,const char* message) {
    ++assertions;if(!value) {std::cerr<<"FAIL "<<message<<'\n';std::exit(1);}
}
void put(uint8_t* rdram,uint32_t a,uint32_t v){MEM_W(0,S32(a))=v;}
uint32_t get(uint8_t* rdram,uint32_t a){return MEM_W(0,S32(a));}
void pf(uint8_t* rdram,uint32_t a,float f){put(rdram,a,std::bit_cast<uint32_t>(f));}
uint32_t be(size_t a){require(a+4<=rom.size(),"ROM bounds");return uint32_t(rom[a])<<24|uint32_t(rom[a+1])<<16|uint32_t(rom[a+2])<<8|rom[a+3];}
recomp_context context(){recomp_context c{};c.r29=S32(0x807FF000);return c;}
void configureGate(Ram& ram) {
    wr64::sunny_detail::set_enabled(active);
    wr64_sunny_detail_begin_load(ram.data());
    wr64_sunny_detail_assets(ram.data(),0x800DC350);
    wr64_sunny_detail_assets(ram.data(),0x800DBCE4);
}
Ram initial(int players) {
    Ram ram(0x800000);auto* rdram=ram.data();
    for(uint32_t a=0x80046800;a<0x800F0000;++a) MEM_B(0,S32(a))=rom[a-0x80045800];
    put(rdram,0x800D8170,1);put(rdram,0x800DAB28,players);put(rdram,0x801CE638,1);
    put(rdram,0x800DAB24,40);MEM_H(0,S32(0x801CE60C))=players;
    put(rdram,0x800D45E4,0x802D6800);put(rdram,0x800D45E8,0x802EC718);
    put(rdram,0x800D48DC,0);put(rdram,0x800D48E0,1);put(rdram,0x80223930,0);put(rdram,0x80223934,1);
    put(rdram,0x801518B8,0x80300000);put(rdram,0x80192460,0);
    put(rdram,0x800D4640,0x12345678);
    for(unsigned i=0;i<4096;++i) pf(rdram,0x80154350+i*4,float(std::sin(i*6.2831853071795864769/4096)));
    for(unsigned p=0;p<2;++p) {
        auto a=0x80192690+p*0x1718;
        pf(rdram,a+0x44,100.0f+500*p);pf(rdram,a+0x48,15);pf(rdram,a+0x4C,-400.0f-200*p);
        pf(rdram,a+0x5C,1);pf(rdram,a+0x64,1);
    }
    auto c=context();c.r4=0x08060000;c.r5=3;c.r6=2;func_8009684C(rdram,&c);
    // Execute the real native decompressor, model parser and animation pointer
    // relocation. Never fabricate the parsed fields that the guard validates.
    put(rdram,0x801CE6D0,0x00316800);
    for(unsigned slot=0;slot<2;++slot) {
        const auto start=get(rdram,0x800DB538+slot*16),end=get(rdram,0x800DB53C+slot*16);
        const auto destination=0x80316800+get(rdram,0x800DB544+slot*16);
        for(uint32_t i=0;i<end-start;++i)rdram[(0x2A0000+i)^3]=rom[start+i];
        auto decode=context();decode.r4=S32(0x802A0000);decode.r5=S32(destination);Mio0_Decompress(rdram,&decode);
        auto parse=context();parse.r4=S32(destination);parse.r5=slot;func_80096048(rdram,&parse);
    }
    return ram;
}
void run(Ram& ram,bool patched){configureGate(ram);auto c=context();if(patched)func_800AC184(ram.data(),&c);else baseline_animal_init(ram.data(),&c);require(uint32_t(c.r29)==0x807FF000,"initializer restored stack");}
}
extern "C" uint32_t wr64_diagnostic_giant_penguin_enabled(){return 0;}
extern "C" void switch_error(const char*,uint32_t,uint32_t){require(false,"unexpected native switch");}
extern "C" void do_break(uint32_t){require(false,"native break");}
extern "C" void func_800C123C(uint8_t*,recomp_context*){require(false,"Sunny unexpectedly initializes dolphin audio");}
extern "C" void func_800C1B64(uint8_t*,recomp_context*){require(false,"Sunny unexpectedly calls another course audio");}
extern "C" void func_800962F0(uint8_t*,recomp_context*){require(false,"unexpected orca parser");}
extern "C" void func_800965B8(uint8_t*,recomp_context*){require(false,"unexpected dolphin parser");}
extern "C" void func_800964CC(uint8_t*,recomp_context*){require(false,"unexpected penguin parser");}
extern "C" void* wr64_test_address(uint8_t* rdram,uint64_t address,unsigned size,const char*,int){
    ++accesses;auto a=uint32_t(address);require((a&0x7FFFFF)+size<=0x800000,"native RDRAM bounds");return rdram+(a&0x7FFFFF);
}
int main(int argc,char**argv){
    require(argc==2,"private ROM argument");std::ifstream f(argv[1],std::ios::binary);rom.assign(std::istreambuf_iterator<char>(f),{});
    require(rom.size()==0x800000,"ROM size");
    auto base=initial(2);active=true;configureGate(base);
    std::cout<<"Native animation tables: "<<std::hex<<get(base.data(),0x801CE784)<<", "<<get(base.data(),0x801CE7B0)<<std::dec<<'\n';
    require(get(base.data(),0x801CE784)==0x803797A8 && get(base.data(),0x801CE7B0)==0x8037CD38,"native parsed animation pointers");
    require(!(get(base.data(),0x801CE784)==1 && get(base.data(),0x801CE7B0)==2),"regression: former animation-count guard rejected native loaded assets");
    require(wr64_sunny_animals_ready(base.data()),"native Sunny assets pass validation");
    require(get(base.data(),0x800DB544)==0x60000 && get(base.data(),0x800DB554)==0x62FC0,"native bank placement");
    require(be(0x3ECC64)==0x2FAC && be(0x3EACF4)==0x3580,"private native bank sizes");
    for(uint32_t address:{0x801CE7D8,0x801CE7DC,0x801CE7E0,0x801CE7E4,0x801CE780,0x801CE784,0x801CE7AC,0x801CE7B0,0x801CE788,0x801CE7B4}){
        auto bad=base;put(bad.data(),address,get(bad.data(),address)^1);require(!wr64_sunny_animals_ready(bad.data()),"wrong resident bank rejected");
    }
    for(uint32_t address:{0x800D8170,0x800DAB28,0x801CE638,0x800D45E8}) {
        auto bad=base;put(bad.data(),address,get(bad.data(),address)^1);
        require(!wr64_sunny_animals_ready(bad.data()),"actual course/player/phase/resident-scenery gate rejects ineligible state");
    }
    for(uint32_t mode:{7,39,46,100}) {
        auto bad=base;put(bad.data(),0x800DAB24,mode);
        require(!wr64_sunny_animals_ready(bad.data()),"non-race modes excluded");
    }
    auto off=base,stock=base;active=false;run(off,true);run(stock,false);require(off==stock,"disabled initializer equals original");
    require(get(off.data(),0x800E62C8)==0 && get(off.data(),0x800E62CC)==0,"stock 2P clears animals");
    auto rejected=base;put(rejected.data(),0x801CE7E0,4);auto rejectedStock=rejected;
    active=true;run(rejected,true);run(rejectedStock,false);require(rejected==rejectedStock,"unknown animal bank preserves original initializer");
    auto originalOne=initial(1),checkedOne=originalOne;run(checkedOne,true);run(originalOne,false);
    require(originalOne==checkedOne,"one-player initializer is unchanged even with active gate");
    auto enhanced=base,one=initial(1);active=true;run(enhanced,true);active=false;run(one,false);
    require(get(enhanced.data(),0x800DAB28)==2,"global players retained");
    require(get(enhanced.data(),0x800E62C8)==12 && get(enhanced.data(),0x800E62CC)==12,"native Sunny actor count");
    constexpr uint32_t actors=0x1CF060,bytes=30*0xBC;
    require(std::equal(enhanced.begin()+actors,enhanced.begin()+actors+bytes,one.begin()+actors),"enhanced actor pool matches native 1P");
    unsigned fish=0,gulls=0;
    for(unsigned i=0;i<30;++i){auto id=get(enhanced.data(),0x801CF060+i*0xBC);fish+=id>=7&&id<=9;gulls+=id==3||id==4;require(id==0||id==3||id==4||(id>=7&&id<=9),"only Sunny animal species");}
    require(fish==6 && gulls==5,"native six fish and five gulls");
    std::cout<<"PASS native animal initialization, "<<fish<<" fish, "<<gulls<<" gulls, "<<assertions<<" assertions, "<<accesses<<" checked accesses.\n";
}
