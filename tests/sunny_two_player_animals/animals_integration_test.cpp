#include "recomp.h"
#include "wr64_sunny_animals_load.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

extern "C" {
void func_8009684C(uint8_t*,recomp_context*);
void Mio0_Decompress(uint8_t*,recomp_context*);
void func_80096048(uint8_t*,recomp_context*);
void func_800AC184(uint8_t*,recomp_context*);
void func_800ADF90(uint8_t*,recomp_context*);
void baseline_animal_draw(uint8_t*,recomp_context*);
void func_800ADE14(uint8_t*,recomp_context*);
void SysMain_GfxInitBuffers(uint8_t*,recomp_context*);
}
namespace {
using Ram=std::vector<uint8_t>;using Fn=void(*)(uint8_t*,recomp_context*);
constexpr uint32_t Actor=0x801CF060,Dynamic=0x801C43F8,Size=0x800000,Stack=0x807FE000;
unsigned checks=0;uint64_t accesses=0;std::vector<uint8_t> rom;bool active=true;
void require(bool v,const char* why){++checks;if(!v){std::cerr<<"FAIL "<<why<<'\n';std::exit(1);}}
void put(Ram& r,uint32_t a,uint32_t v){auto* rdram=r.data();MEM_W(0,S32(a))=v;}
uint32_t get(const Ram& r,uint32_t a){auto* rdram=const_cast<uint8_t*>(r.data());return MEM_W(0,S32(a));}
void number(Ram& r,uint32_t a,float v){put(r,a,std::bit_cast<uint32_t>(v));}
void prepare(recomp_context& c){c={};c.r29=S32(Stack);c.f_odd=&c.f0.u32h;}
uint32_t call(Ram& r,Fn fn,uint32_t a=0,uint32_t b=0){recomp_context c;prepare(c);c.r4=S32(a);c.r5=b;fn(r.data(),&c);require(uint32_t(c.r29)==Stack,"native stack balance");return uint32_t(c.r2);}
bool same(const Ram& a,const Ram& b,uint32_t p,uint32_t n){const auto o=p&0x7FFFFF;return std::equal(a.begin()+o,a.begin()+o+n,b.begin()+o);}
Ram load(){
    Ram r(Size);auto* rdram=r.data();
    for(uint32_t a=0x80046800;a<0x800F0000;++a)rdram[(a&0x7FFFFF)^3]=rom[a-0x80045800];
    put(r,0x800D8170,1);put(r,0x800DAB28,2);put(r,0x801CE638,1);
    put(r,0x800D48DC,0);put(r,0x800D48E0,1);put(r,0x80223930,0);put(r,0x80223934,1);
    put(r,0x80192460,0);put(r,0x800D4640,0x12345678);
    for(unsigned i=0;i<4096;++i)number(r,0x80154350+i*4,float(std::sin(i*6.2831853071795864769/4096)));
    for(unsigned p=0;p<2;++p){const auto a=0x80192690+p*0x1718;number(r,a+0x44,100.0f+500*p);number(r,a+0x48,15);number(r,a+0x4C,-400.0f-200*p);number(r,a+0x5C,1);number(r,a+0x64,1);}
    recomp_context c;prepare(c);c.r4=0x08060000;c.r5=3;c.r6=2;func_8009684C(rdram,&c);
    put(r,0x801CE6D0,0x00316800);
    for(unsigned slot=0;slot<2;++slot){
        const auto start=get(r,0x800DB538+slot*16),end=get(r,0x800DB53C+slot*16),destination=0x80316800+get(r,0x800DB544+slot*16);
        require(start<end&&end<=rom.size(),"native asset transfer bounds");
        for(uint32_t i=0;i<end-start;++i)rdram[(0x2A0000+i)^3]=rom[start+i];
        call(r,Mio0_Decompress,0x802A0000,destination);call(r,func_80096048,destination,slot);
    }
    require(wr64_sunny_animals_ready(rdram),"real native parsed assets rejected by production readiness");
    return r;
}
void environment(Ram& r){
    for(unsigned view=0;view<2;++view){
        const auto e=0x801CB058+view*0x110;
        for(unsigned o:{0u,4u,8u,0xCu,0x10u,0x14u,0x48u,0x4Cu,0x50u,0x54u,0xCCu,0xD0u,0xD4u,0xD8u,0xDCu,0xE0u})put(r,e+o,50+view*30);
        put(r,e+0x78,100);put(r,e+0x7C,4000);
        for(unsigned o:{0xACu,0xB0u,0xB4u,0xFCu,0x100u,0x104u})number(r,e+o,0.5f);
    }
}
void exercise(const Ram& loaded,unsigned buffer){
    auto r=loaded;put(r,0x8011F8E0,buffer^1);call(r,SysMain_GfxInitBuffers);
    const auto pool=get(r,0x801518B8),list=get(r,0x80151944);
    require(pool==0x8011F8E8+buffer*0x18FE8&&list==pool,"actual native double-buffer allocator disagrees with guard");
    call(r,func_800AC184);require(get(r,0x800E62C8)==12,"native initializer did not publish Sunny roster");
    environment(r);put(r,0x800DAB2C,0);put(r,0x800E62C4,91);
    auto* rdram=r.data();MEM_H(0,S32(0x801CE624))=-1;
    unsigned liveFish=0,liveGulls=0;
    for(unsigned i=0;i<30;++i){const auto type=get(r,Actor+i*0xBC);liveFish+=type>=7&&type<=9;liveGulls+=type==3||type==4;}
    require(liveFish==6&&liveGulls==5,"native initialized species roster differs");
    // Exercise native culling from four real camera headings; select one that
    // sees both species rather than replacing the visibility result.
    constexpr float dirs[][2]={{1,0},{0,1},{-1,0},{0,-1}};
    unsigned visibleFish=0,visibleGulls=0;int heading=-1;
    for(int h=0;h<4;++h){
        number(r,0x80227C80+0x4C,100);number(r,0x80227C80+0x54,-400);
        number(r,0x80227C80+0xF0,dirs[h][0]);number(r,0x80227C80+0xF4,dirs[h][1]);
        unsigned fish=0,gulls=0;
        for(unsigned i=0;i<30;++i){const auto type=get(r,Actor+i*0xBC);if(!call(r,func_800ADE14,i))continue;fish+=type>=7&&type<=9;gulls+=type==3||type==4;}
        if(fish&&gulls){visibleFish=fish;visibleGulls=gulls;heading=h;break;}
    }
    require(heading>=0,"native cameras never see both fish and gulls");
    auto baseline=r;const auto before=r;const auto expectedEnd=call(baseline,baseline_animal_draw,list);
    const auto end=call(r,func_800ADF90,list);
    require(end==expectedEnd&&r==baseline,"capture changed actual native species rendering/animation");
    const auto body=list+0x30;require(end>body,"actual native animal pass emitted no geometry");
    unsigned fishCalls=0,gullCalls=0;
    for(auto p=body;p<end;p+=8)if(get(r,p)==0x06000000){const auto address=get(r,p+4);fishCalls+=address>=0x08065A00&&address<=0x08065E00;gullCalls+=address>=0x080617F0&&address<=0x08061B38;}
    require(fishCalls>0&&gullCalls>0,"actual native fish/gull model calls missing");
    unsigned fishTicks=0,gullTicks=0;
    for(unsigned i=0;i<30;++i){const auto a=Actor+i*0xBC,type=get(before,a);if(get(before,a+0x78)==get(r,a+0x78))continue;fishTicks+=type>=7&&type<=9;gullTicks+=type==3;}
    require(fishTicks>0&&gullTicks>0,"real native animation did not advance both species");
    require(get(r,0x801D06B8)>0&&get(r,0x801D06B8)<=64,"native matrices exceed Sunny maximum");
    put(r,0x800DAB2C,1);number(r,0x80227C80+0x10C+0xF0,-dirs[heading][0]);number(r,0x80227C80+0x10C+0xF4,-dirs[heading][1]);
    const auto p1=r;const auto destination=end+0x200;const auto replayEnd=call(r,func_800ADF90,destination);
    require(replayEnd==destination+0x30+end-body,"real species P2 replay length differs");
    require(std::equal(r.begin()+(body&0x7FFFFF),r.begin()+(end&0x7FFFFF),r.begin()+((destination+0x30)&0x7FFFFF)),"real species body was not replayed exactly");
    require(same(p1,r,Actor,30*0xBC),"P2 ticked actual native animal animation/state again");
    require(same(p1,r,Dynamic+buffer*0x3630+0x5D0,0x3000),"P2 overwrote actual native animated matrices");
    require(get(p1,0x800E62C0)==get(r,0x800E62C0)&&get(p1,0x801D06B8)==get(r,0x801D06B8),"P2 repeated native phase/counter updates");
    std::cout<<"Buffer "<<buffer<<": native visible fish="<<visibleFish<<" gulls="<<visibleGulls<<", model calls="<<fishCalls<<"/"<<gullCalls<<", body="<<end-body<<" bytes, matrices="<<get(r,0x801D06B8)<<'\n';
}
}
extern "C" uint32_t wr64_sunny_detail_active(uint8_t*){return active;}
namespace wr64::sunny_detail { void note_diagnostic(const char*){} }
extern "C" uint32_t wr64_diagnostic_giant_penguin_enabled(){return 0;}
extern "C" void wr64_ghost_begin_dolphin_draw(uint8_t*,recomp_context*,int){}
extern "C" void wr64_ghost_end_dolphin_draw(uint8_t*,recomp_context*){}
#define UNEXPECTED(name) extern "C" void name(uint8_t*,recomp_context*){require(false,"unexpected non-Sunny native call: " #name);}
UNEXPECTED(func_8009DB90) UNEXPECTED(func_8009DC10) UNEXPECTED(func_8009F398) UNEXPECTED(func_8009FCB0)
UNEXPECTED(func_800A063C) UNEXPECTED(func_800A2308) UNEXPECTED(func_800A28F4)
UNEXPECTED(func_800C123C) UNEXPECTED(func_800C1B64) UNEXPECTED(func_800962F0) UNEXPECTED(func_800965B8) UNEXPECTED(func_800964CC)
extern "C" void switch_error(const char*,uint32_t,uint32_t){require(false,"unexpected native switch");}
extern "C" void do_break(uint32_t){require(false,"native division break");}
extern "C" void* wr64_test_address(uint8_t* r,uint64_t address,unsigned size,const char*,int){
    ++accesses;const auto a=uint32_t(address);require(a>=0x80000000&&a<=0x80800000-size,"native RDRAM access outside memory");return r+(a&0x7FFFFF);
}
int main(int argc,char** argv){
    require(argc==2,"private ROM argument");std::ifstream file(argv[1],std::ios::binary);rom.assign(std::istreambuf_iterator<char>(file),{});
    require(rom.size()==Size,"private ROM size");const auto loaded=load();
    exercise(loaded,0);exercise(loaded,1);
    std::cout<<"PASS actual native assets, initialization, camera culling, species animation, world matrices and P2 replay; "<<checks<<" checks, "<<accesses<<" native accesses\n";
}
