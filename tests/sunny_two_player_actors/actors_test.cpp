#include "recomp.h"
#include "wr64_sunny_detail.hpp"
#include "wr64_sunny_actors.h"
#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

extern "C" {
void func_80069594(uint8_t*, recomp_context*);
void baseline_func_80069594(uint8_t*, recomp_context*);
}
namespace {
constexpr uint32_t RamBytes=0x800000, Stack=0x807FF000, Pool=0x8011F8E8, PoolBytes=0x18FE8;
constexpr uint32_t Common=0x802A0000, Racer=0x80192690, Stride=0x1718;
using Ram=std::vector<uint8_t>;
unsigned checks=0, cases=0;
uint64_t accesses=0;
std::vector<uint8_t> rom;
void require(bool good,const char* reason) { ++checks; if(!good){std::cerr<<"FAIL case "<<cases<<": "<<reason<<'\n';std::exit(1);} }
void put(uint8_t* rdram,uint32_t p,uint32_t v){MEM_W(0,S32(p))=v;}
uint32_t get(uint8_t* rdram,uint32_t p){return MEM_W(0,S32(p));}
void number(uint8_t* rdram,uint32_t p,float v){put(rdram,p,std::bit_cast<uint32_t>(v));}
void copy(Ram& ram,uint32_t dest,uint32_t offset,uint32_t size){
    require(offset+size<=rom.size(),"private ROM range"); auto* rdram=ram.data();
    for(uint32_t i=0;i<size;++i)MEM_B(i,gpr(S32(dest)))=rom[offset+i];
}
Ram initial(bool enabled=true,unsigned poolIndex=0,unsigned course=1){
    Ram ram(RamBytes);copy(ram,0x80046800,0x1000,0x800DFFA8-0x80046800);
    // SysMain's exact raw segment-1 transfer; includes the stock shadow's
    // triangle, texture and material. No generated or redistributed assets.
    copy(ram,Common,0xF6090,0x8290);auto* rdram=ram.data();
    put(rdram,0x800D8170,course);put(rdram,0x800DAB24,40);put(rdram,0x800DAB28,2);
    MEM_H(0,S32(0x801CE60C))=2;put(rdram,0x801CE638,1);
    put(rdram,0x800D45E4,0x802D6800);
    put(rdram,0x800D45E8,0x802D6800+get(rdram,0x800DCE3C+course*4));
    put(rdram,0x801518B8,Pool+poolIndex*PoolBytes);put(rdram,0x80151984,Common&0x1FFFFFFF);
    put(rdram,0x801982F0,4);put(rdram,0x800D48DC,0);put(rdram,0x800D48E0,1);
    number(rdram,0x800E92A0,1.0f);number(rdram,0x800E92A4,0.0f);put(rdram,0x80192458,12);
    // Four distinct current world poses over a flat, height-12 native water grid.
    for(unsigned i=0;i<4;++i){
        number(rdram,Racer+i*Stride+0x44,100.0f+128*i);
        number(rdram,Racer+i*Stride+0x48,30.0f+i);
        number(rdram,Racer+i*Stride+0x4C,200.0f+128*i);
        number(rdram,Racer+i*Stride+0x6C,0.0f);
        number(rdram,Racer+i*Stride+0x70,0.0f);
        number(rdram,Racer+i*Stride+0x74,1.0f);
        put(rdram,Racer+i*Stride+0xC78,0);
    }
    wr64::sunny_detail::set_enabled(enabled);wr64_sunny_detail_begin_load(rdram);
    wr64_sunny_detail_assets(rdram,get(rdram,0x800DC514+course*4));
    wr64_sunny_detail_assets(rdram,get(rdram,0x800DC108+course*4));
    return ram;
}
void setup(recomp_context& ctx,uint32_t start,bool fr1=false){
    ctx={};ctx.mips3_float_mode=fr1;ctx.f_odd=fr1?&ctx.f1.u32l:&ctx.f0.u32h;
    ctx.r29=S32(Stack);ctx.r4=S32(start);ctx.r2=0xABCDEF;ctx.r16=0x11223344;ctx.r31=0x88776655;
    ctx.f1.u32l=0x13572468;ctx.f0.u32h=0x24681357;
}
float matrixNumber(uint8_t* rdram,uint32_t p,unsigned n){
    const uint32_t value=(uint32_t(MEM_HU(n*2,gpr(S32(p))))<<16)|MEM_HU(32+n*2,gpr(S32(p)));
    return float(int32_t(value))/65536.0f;
}
void memoryPolicy(const Ram& before,const Ram& after,uint32_t pool,uint32_t start,unsigned first,unsigned second){
    for(uint32_t i=0;i<RamBytes;++i)if(before[i]!=after[i]){
        const uint32_t p=i+0x80000000;
        bool allowed=(p>=Stack-0x200&&p<Stack+0x10)||(p>=start&&p<start+32);
        for(unsigned rider:{first,second})allowed|=p>=pool+0xF808+rider*64&&p<pool+0xF848+rider*64;
        require(allowed,"modified non-render state outside native stack, DL or reserved shadow matrices");
    }
}
void testBothViews(){
    for(unsigned poolIndex=0;poolIndex<2;++poolIndex)for(unsigned first=0;first<4;++first)
    for(unsigned second=0;second<4;++second)if(first!=second)for(unsigned view=0;view<2;++view)
    for(unsigned fr1=0;fr1<2;++fr1){
        ++cases;auto ram=initial(true,poolIndex);auto* rdram=ram.data();
        const auto pool=Pool+poolIndex*PoolBytes,start=pool+0x100;
        put(rdram,0x800D48DC,first);put(rdram,0x800D48E0,second);put(rdram,0x800DAB2C,view);
        auto before=ram;recomp_context ctx;setup(ctx,start,fr1);auto saved=ctx;
        func_80069594(rdram,&ctx);
        require(uint32_t(ctx.r2)==start+32,"both selected racers must emit native shadows");
        saved.r2=ctx.r2;require(std::memcmp(&saved,&ctx,sizeof(ctx))==0,"hook changed caller registers or FP self pointer");
        unsigned offset=0;
        for(unsigned racer:{first,second}){
            require(get(rdram,start+offset)==0x01020040,"native shadow matrix command");
            require(get(rdram,start+offset+4)==0x0300F808+racer*64,"selected racer matrix identity");
            require(get(rdram,start+offset+8)==0x06000000&&get(rdram,start+offset+12)==0x010068B0,"resident native shadow material");
            auto m=pool+0xF808+racer*64;
            require(matrixNumber(rdram,m,12)==100.0f+128*racer&&matrixNumber(rdram,m,14)==200.0f+128*racer,"shadow world position belongs to selected racer");
            require(matrixNumber(rdram,m,13)==12.0f,"shadow uses actual native water height");
            offset+=16;
        }
        memoryPolicy(before,ram,pool,start,first,second);
    }
}
void testSkipAndFallback(){
    // Native crash/submersion guard and degenerate orientation continue to suppress a shadow.
    for(unsigned kind=0;kind<2;++kind){
        ++cases;auto ram=initial();auto* rdram=ram.data();const auto start=Pool+0x100;
        if(kind==0)put(rdram,Racer+Stride+0xC78,4);else number(rdram,Racer+Stride+0x74,0.0f);
        recomp_context ctx;setup(ctx,start);func_80069594(rdram,&ctx);
        require(uint32_t(ctx.r2)==start+16,"native hidden/invalid rider shadow was forced visible");
    }
    for(unsigned rejection=0;rejection<10;++rejection){
        ++cases;auto ram=initial(rejection!=0);auto* rdram=ram.data();uint32_t start=Pool+0x100;
        switch(rejection){
        case 1:put(rdram,0x800DAB2C,2);break;
        case 2:put(rdram,0x800D48E0,0);break;
        case 3:put(rdram,0x800D48E0,4);break;
        case 4:put(rdram,0x801982F0,5);break;
        case 5:put(rdram,0x801518B8,0x80500000);break;
        case 6:start=Pool+0x57E8;break;
        case 7:put(rdram,Common+0x68B0,0);break;
        case 8:put(rdram,0x800D8170,0);break;
        case 9:put(rdram,0x800DAB28,1);MEM_H(0,S32(0x801CE60C))=1;break;
        }
        auto baseline=ram;recomp_context ctx,original;setup(ctx,start);setup(original,start);
        func_80069594(ram.data(),&ctx);baseline_func_80069594(baseline.data(),&original);
        require(ram==baseline,"fallback changed native memory output");
        require(ctx.r2==original.r2&&ctx.r29==original.r29,"fallback changed native result or stack");
    }
}
void testMaterial(){
    ++cases;auto ram=initial();auto* rdram=ram.data();
    require(get(rdram,Common+0x68B0)==0x06000000&&get(rdram,Common+0x68B4)==0x01006840,"native shadow root changed");
    require(get(rdram,Common+0x6870)==0xFD700000&&get(rdram,Common+0x6874)==0x010068F8,"shadow alpha texture reference");
    require(get(rdram,Common+0x6898)==0x0400062F&&get(rdram,Common+0x689C)==0x010068C8,"shadow triangle vertices reference");
    require(get(rdram,Common+0x68A0)==0xBF000000&&get(rdram,Common+0x68A8)==0xB8000000,"shadow triangle and list termination");
    require(0x68F8+32*64<=0x8290&&0x68C8+3*16<=0x8290,"native shadow material points beyond resident bank");
}
void testCoursesAndBudget(){
    // Use each actual course's ROM transfer tables through the production load
    // latch. This is an actor-pass test, not a course-data/gameplay simulation.
    for(unsigned course=1;course<=8;++course)for(unsigned view=0;view<2;++view)
    for(unsigned poolIndex=0;poolIndex<2;++poolIndex){
        ++cases;auto ram=initial(true,poolIndex,course);auto* rdram=ram.data();
        require(wr64_sunny_detail_active(rdram)!=0,"each native VS course must activate through its own ROM tables");
        put(rdram,0x800DAB2C,view);const auto pool=Pool+poolIndex*PoolBytes;
        const auto start=pool+0x6000-0x800-32;
        auto baseline=ram;recomp_context ctx,original;setup(ctx,start);setup(original,start);
        func_80069594(rdram,&ctx);
        if(course==4){
            baseline_func_80069594(baseline.data(),&original);
            require(ram==baseline&&ctx.r2==original.r2,"Drake Lake's native no-shadow path must be retained");
        }else{
            require(uint32_t(ctx.r2)==start+32,"all other VS courses retain both native craft shadows");
            require(uint32_t(ctx.r2)==pool+0x5800,"shadow commands must leave the complete 0x800-byte native tail");
            require(get(rdram,start+12)==0x010068B0&&get(rdram,start+28)==0x010068B0,"course changed shared native shadow material");
            memoryPolicy(baseline,ram,pool,start,0,1);
        }
    }
    for(unsigned invalid:{0u,9u}){
        ++cases;auto ram=initial();auto* rdram=ram.data();put(rdram,0x800D8170,invalid);
        recomp_context ctx;setup(ctx,Pool+0x100);auto before=ram;auto saved=ctx;
        require(wr64_sunny_actor_shadows(rdram,&ctx)==0,"non-VS course must not reuse loaded shadow override");
        require(ram==before&&std::memcmp(&ctx,&saved,sizeof(ctx))==0,"rejected course changed state");
    }
}
}
extern "C" {
void* wr64_test_address(uint8_t* rdram,uint64_t address,unsigned size,const char* file,int line){
    ++accesses;const auto p=uint32_t(address);
    if(p<0x80000000||uint64_t(p)+size>0x80800000||(p&(size-1))){
        std::cerr<<"native address "<<std::hex<<p<<std::dec<<" at "<<file<<':'<<line<<'\n';std::exit(1);
    }
    return rdram+p-0x80000000;
}
void do_break(uint32_t){require(false,"native break");}
}
int main(int argc,char** argv){
    require(argc==2,"pass private USA Rev1 ROM");std::ifstream input(argv[1],std::ios::binary);
    require(bool(input),"open private ROM");rom.assign(std::istreambuf_iterator<char>(input),{});
    testMaterial();testBothViews();testSkipAndFallback();testCoursesAndBudget();
    std::cout<<"PASS "<<cases<<" native actor-shadow cases, "<<checks<<" assertions, "<<accesses
        <<" checked native accesses; eight native VS courses, Drake exclusion, both views/pools, all selected racer pairs, FR0/FR1, pose/water height/material, exact tail budget, fallback, and render-only memory writes. No game or GUI launched.\n";
}
