#include "recomp.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

extern "C" {
void baseline_animal_draw(uint8_t*,recomp_context*);
void func_800ADF90(uint8_t*,recomp_context*);
void func_800916B4(uint8_t*,recomp_context*);
void func_8009D96C(uint8_t*,recomp_context*);
void SysMain_GfxInitBuffers(uint8_t*,recomp_context*);
}
namespace {
using Ram=std::vector<uint8_t>;
using Fn=void(*)(uint8_t*,recomp_context*);
constexpr uint32_t Size=0x800000,Stack=0x807FE000,Pool=0x8011F8E8,List=Pool+0x100;
constexpr uint32_t Actors=0x801CF060,RecordSize=0xBC,Dynamic=0x801C43F8,Counter=0x801D06B8;
bool ready=false; unsigned cases=0,checks=0,draws=0;uint64_t accesses=0;
unsigned visible=12;
void require(bool good,const char* why){++checks;if(!good){std::cerr<<"FAIL case "<<cases<<": "<<why<<'\n';std::exit(1);}}
void put(Ram& r,uint32_t a,uint32_t v){auto* rdram=r.data();MEM_W(0,S32(a))=v;}
uint32_t get(const Ram& r,uint32_t a){auto* rdram=const_cast<uint8_t*>(r.data());return MEM_W(0,S32(a));}
void num(Ram& r,uint32_t a,float v){put(r,a,std::bit_cast<uint32_t>(v));}
void context(recomp_context& c,uint32_t list=List){c={};c.f_odd=&c.f0.u32h;c.r29=S32(Stack);c.r4=S32(list);c.r31=0x800055AA;}
Ram initial(unsigned buffer=0,unsigned count=12){
    Ram r(Size,0);put(r,0x800DAB28,2);put(r,0x800DAB2C,0);put(r,0x800D8170,1);
    put(r,0x8011F8E0,buffer);put(r,0x801518B8,Pool);put(r,0x800E62C4,77);
    put(r,0x800E62C8,count);put(r,Counter,99);put(r,0x800E62C0,0);
    for(unsigned view=0;view<2;++view){
        uint32_t e=0x801CB058+view*0x110;
        for(unsigned o:{0u,4u,8u,0xCu,0x10u,0x14u,0x48u,0x4Cu,0x50u,0x54u,0xCCu,0xD0u,0xD4u,0xD8u,0xDCu,0xE0u})put(r,e+o,40+view*70+o%20);
        put(r,e+0x78,100+view*50);put(r,e+0x7C,3000+view*100);
        for(unsigned o:{0xACu,0xB0u,0xB4u,0xFCu,0x100u,0x104u})num(r,e+o,o%3==0?1.0f:0.25f+view*0.125f);
    }
    constexpr uint32_t types[]={3,4,7,8,9};
    for(unsigned i=0;i<count;++i){
        const auto a=Actors+i*RecordSize;put(r,a,types[i%5]);put(r,a+0x78,10+i);
        num(r,a+0xC,i==0?9000.0f:100.0f+i*30);num(r,a+0x10,50+i);num(r,a+0x14,300+i*15);
        num(r,a+0x18,0);num(r,a+0x1C,90);num(r,a+0x20,0);
    }
    // The native end-of-pass sweep must clear this unused record exactly once.
    put(r,Actors+29*RecordSize,0xFFFF);
    return r;
}
uint32_t run(Ram& ram,Fn fn,uint32_t start=List){
    recomp_context c;context(c,start);fn(ram.data(),&c);
    require(uint32_t(c.r29)==Stack,"native/replay stack changed");return uint32_t(c.r2);
}
bool equalRange(const Ram& a,const Ram& b,uint32_t start,uint32_t length){
    const auto off=start&0x7FFFFF;return std::equal(a.begin()+off,a.begin()+off+length,b.begin()+off);
}
void verifyReplay(unsigned buffer,unsigned count){
    ++cases;visible=count;ready=false;auto base=initial(buffer,count),enhanced=base;
    draws=0;const auto baseEnd=run(base,baseline_animal_draw);require(draws==count,"baseline did not dispatch visible species");
    draws=0;ready=true;const auto end=run(enhanced,func_800ADF90);
    require(end==baseEnd&&base==enhanced,"P1 native pass changed by capture hooks");
    require(draws==count,"P1 species animation did not run once");
    require(get(enhanced,Counter)==count,"native world matrix count incorrect");
    require(get(enhanced,Actors+29*RecordSize)==0,"native unused actor cleanup missing");
    require(get(enhanced,0x800E62C0)==1,"native per-frame toggle did not run once");
    if(count)require(std::bit_cast<float>(get(enhanced,Actors+0xC))==8000.0f,"native world wrapping did not run");
    const auto body=List+0x30,bodyBytes=end-body;
    require(bodyBytes==count*24,"controlled native-matrix species body differs");
    const auto destination=end+0x100;put(enhanced,0x800DAB2C,1);auto expected=enhanced;
    if(!bodyBytes){
        const auto before=enhanced;
        require(run(enhanced,func_800ADF90,destination)==destination&&enhanced==before,"empty capture emitted commands or ran animation");
        return;
    }
    const auto setupEnd=run(expected,func_800916B4,destination);
    require(setupEnd==destination+0x30,"Sunny view setup is not exactly six commands");
    std::copy(expected.begin()+(body&0x7FFFFF),expected.begin()+(end&0x7FFFFF),expected.begin()+(setupEnd&0x7FFFFF));
    const auto before=enhanced;const auto replayEnd=run(enhanced,func_800ADF90,destination);
    require(replayEnd==setupEnd+bodyBytes,"P2 replay length wrong");
    require(draws==count,"P2 repeated species animation/draw callback");
    require(equalRange(before,enhanced,Actors,30*RecordSize),"P2 changed animal state");
    require(get(before,Counter)==get(enhanced,Counter),"P2 reset/incremented shared matrix counter");
    require(get(before,0x800E62C0)==get(enhanced,0x800E62C0),"P2 repeated native frame toggle");
    require(equalRange(before,enhanced,Dynamic+buffer*0x3630+0x5D0,0x3000),"P2 overwrote P1 world/part matrices");
    require(equalRange(expected,enhanced,destination,replayEnd-destination),"P2 commands do not match native per-view setup + P1 body");
    for(uint32_t a=0;a<Size;++a)if(before[a]!=enhanced[a]){
        const uint32_t address=0x80000000+a,dyn=Dynamic+buffer*0x3630;
        require((address>=destination&&address<replayEnd)||(address>=Stack-0x100&&address<Stack)||
                (address>=dyn+0x35E8&&address<dyn+0x3600)||(address>=dyn+0x3618&&address<dyn+0x3630),
                "P2 replay changed unrelated RAM, P1 lights, camera or physics");
    }
    for(uint32_t o:{0x35E8u,0x3618u})require(equalRange(expected,enhanced,Dynamic+buffer*0x3630+o,0x18),"P2 lighting differs from native setup");
    const auto consumed=enhanced;require(run(enhanced,func_800ADF90,replayEnd+0x80)==replayEnd+0x80,"second P2 call reused consumed capture");
    require(enhanced==consumed,"consumed P2 capture changed memory");
}
void rejected(unsigned kind){
    ++cases;visible=2;ready=true;auto r=initial(0,2);const auto end=run(r,func_800ADF90);
    put(r,0x800DAB2C,1);uint32_t dest=end+0x100;
    if(kind==0)put(r,0x800E62C4,78);
    if(kind==1)put(r,0x8011F8E0,1);
    if(kind==2)put(r,0x801518B8,Pool+0x18FE8);
    if(kind==3)dest=end-8;
    if(kind==4)dest=Pool+0x6000-0x800-0x30-48+8;
    if(kind==5)put(r,0x800D8170,8);
    const auto before=r;const auto count=draws;
    require(run(r,func_800ADF90,dest)==dest,"invalid replay did not return input cursor");
    require(r==before&&draws==count,"invalid replay changed RAM or native actor state");
}
void firstViewCapacity(){
    // Full gull (184), distant gull (24), and an unused unsupported record
    // conservatively reserved at 184 bytes until native end-of-pass cleanup.
    constexpr uint32_t maximumBody=184+24+184;
    constexpr uint32_t exact=Pool+0x6000-0x800-0x30-maximumBody;
    ++cases;visible=2;ready=true;auto r=initial(0,2),baseline=r;
    const auto expected=run(baseline,baseline_animal_draw,exact);
    require(run(r,func_800ADF90,exact)==expected&&r==baseline,"P1 exact budget boundary did not retain native behavior");
    ++cases;r=initial(0,2);const auto before=r;const auto calls=draws;
    require(run(r,func_800ADF90,exact+8)==exact+8,"P1 budget overflow did not skip optional pass");
    require(r==before&&draws==calls,"P1 budget overflow changed actor state, matrices or RAM");
    put(r,0x800DAB2C,1);const auto secondBefore=r;
    require(run(r,func_800ADF90)==List&&r==secondBefore,"P1 capacity skip retained a stale P2 capture");
}
void penguinCapacity(){
    ++cases;visible=1;ready=true;auto r=initial(0,1);
    put(r,Actors,13);put(r,Actors+29*RecordSize,0);
    constexpr uint32_t exact=Pool+0x6000-0x800-0x30-192;
    auto baseline=r;
    require(run(r,func_800ADF90,exact)==run(baseline,baseline_animal_draw,exact)&&r==baseline,
        "penguin exact 192-byte body reserve rejected");
    ++cases;r=initial(0,1);put(r,Actors,13);put(r,Actors+29*RecordSize,0);
    auto before=r;const auto calls=draws;
    require(run(r,func_800ADF90,exact+8)==exact+8&&r==before&&draws==calls,
        "penguin 8-byte overflow was not rejected before native writes");
    ++cases;r=initial(0,28);visible=28;
    for(unsigned i=0;i<30;++i)put(r,Actors+i*RecordSize,i<28?13:0);
    before=r;
    require(run(r,func_800ADF90)==List&&r==before&&draws==calls,
        "penguin matrix reserve overflow did not skip before native writes");
}
}
extern "C" uint32_t wr64_sunny_animals_ready(uint8_t*){return ready;}
namespace wr64::sunny_detail { void note_diagnostic(const char*){} }
extern "C" void func_800ADE14(uint8_t*,recomp_context* c){c->r2=uint32_t(c->r4)<visible?1:0;}
namespace {
void species(uint8_t* rdram,recomp_context* c){
    ++draws;const auto actor=Actors+uint32_t(c->r5)*RecordSize;
    MEM_W(0x78,S32(actor))+=1;
    c->r6=std::bit_cast<uint32_t>(0.2f);func_8009D96C(rdram,c);
    const auto list=uint32_t(c->r2);
    MEM_W(0,S32(list))=0x06000000;MEM_W(4,S32(list))=0x08060000;
    MEM_W(8,S32(list))=0xE7000000;MEM_W(12,S32(list))=0;c->r2=S32(list+16);
}
}
#define SPECIES(name) extern "C" void name(uint8_t* r,recomp_context* c){species(r,c);}
SPECIES(func_8009DB90) SPECIES(func_8009DC10) SPECIES(func_8009E794) SPECIES(func_8009E814)
SPECIES(func_8009F398) SPECIES(func_8009FCB0) SPECIES(func_800A063C) SPECIES(func_800A10E4)
SPECIES(func_800A16F0) SPECIES(func_800A1CFC) SPECIES(func_800A2308) SPECIES(func_800A28F4)
extern "C" void wr64_ghost_begin_dolphin_draw(uint8_t*,recomp_context*,int){}
extern "C" void wr64_ghost_end_dolphin_draw(uint8_t*,recomp_context*){}
extern "C" void do_break(uint32_t){require(false,"native division break");}
extern "C" void switch_error(const char*,uint32_t,uint32_t){require(false,"native switch outside valid species");}
extern "C" void* wr64_test_address(uint8_t* r,uint64_t at,unsigned width,const char*,int){
    ++accesses;const auto a=uint32_t(at);require(a>=0x80000000&&a<=0x80800000-width,"native memory access outside RDRAM");return r+(a&0x7FFFFF);
}
int main(){
    ++cases;auto allocation=initial();recomp_context allocator;context(allocator);
    for(unsigned expected:{1u,0u,1u}){
        SysMain_GfxInitBuffers(allocation.data(),&allocator);
        require(get(allocation,0x8011F8E0)==expected,"native buffer index differs");
        require(get(allocation,0x801518B8)==Pool+expected*0x18FE8,"native pool provenance differs from capacity guard");
        require(get(allocation,0x80151944)==get(allocation,0x801518B8),"native display-list cursor is not pool start");
    }
    for(unsigned buffer=0;buffer<2;++buffer)for(unsigned count:{0u,2u,12u})verifyReplay(buffer,count);
    for(unsigned kind=0;kind<6;++kind)rejected(kind);
    firstViewCapacity();
    penguinCapacity();
    ++cases;visible=2;ready=true;auto boundary=initial(0,2);const auto sourceEnd=run(boundary,func_800ADF90);
    put(boundary,0x800DAB2C,1);const auto sourceBytes=sourceEnd-List-0x30;
    const auto destination=Pool+0x6000-0x800-0x30-sourceBytes;
    recomp_context c;context(c,destination);const auto originalContext=c;
    func_800ADF90(boundary.data(),&c);
    require(uint32_t(c.r2)==Pool+0x5800,"exact capacity boundary rejected");
    const auto result=c.r2;c.r2=originalContext.r2;
    require(std::memcmp(&c,&originalContext,sizeof(c))==0,"P2 helper altered registers besides return cursor");
    c.r2=result;
    // Disabled and 1P/other-scope behavior remains the untouched native function.
    ++cases;visible=2;ready=false;auto baseline=initial(0,2),r=baseline;put(baseline,0x800DAB2C,1);put(r,0x800DAB2C,1);
    require(run(r,func_800ADF90)==run(baseline,baseline_animal_draw)&&r==baseline,"Original fallback differs from native");
    // P2 with no preceding P1 pass must not use a stale cached body.
    ++cases;ready=true;auto absent=initial(0,2);put(absent,0x800DAB2C,1);const auto before=absent;
    require(run(absent,func_800ADF90)==List&&absent==before,"P2 without current P1 capture changed memory");
    std::cout<<"PASS "<<cases<<" scenarios, "<<checks<<" checks, "<<accesses<<" checked native accesses\n";
}
