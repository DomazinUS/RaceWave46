#include "recomp.h"
#include <algorithm>
#include <bit>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

extern "C" {
void native_buoy_matrices(uint8_t*,recomp_context*);
void baseline_buoy_detail(uint8_t*,recomp_context*);
void enhanced_buoy_detail(uint8_t*,recomp_context*);
void native_twilight_segments(uint8_t*,recomp_context*);
void native_twilight_animation_update(uint8_t*,recomp_context*);
}
namespace {
using Ram=std::vector<uint8_t>;
using Command=std::pair<uint32_t,uint32_t>;
using Fn=void(*)(uint8_t*,recomp_context*);
constexpr uint32_t Size=0x800000,Stack=0x807FE000,List=0x8011F9E8,Pool=0x80400000,DisplayPool=0x8011F8E8;
constexpr uint32_t Buoy=0x801AEE20,Visibility=0x801C0840,Indices=0x801C0B40,Count=0x801BB120;
unsigned checks=0,cases=0;uint64_t accesses=0;bool active=false;
void require(bool good,const char* text) {++checks;if(!good){std::cerr<<"FAIL case "<<cases<<": "<<text<<'\n';std::exit(1);}}
void put(Ram& ram,uint32_t at,uint32_t value){auto* rdram=ram.data();MEM_W(0,S32(at))=value;}
uint32_t get(Ram& ram,uint32_t at){auto* rdram=ram.data();return MEM_W(0,S32(at));}
void number(Ram& ram,uint32_t at,float value){put(ram,at,std::bit_cast<uint32_t>(value));}
void context(recomp_context& c){c={};c.f_odd=&c.f0.u32h;c.r29=S32(Stack);}
Ram initial(unsigned players,unsigned view,unsigned total=2,unsigned course=1){
    Ram ram(Size,0);auto* rdram=ram.data();
    put(ram,0x800DAB28,players);put(ram,0x800DAB2C,view);put(ram,Count,total);
    put(ram,0x800D8170,course);put(ram,0x801AE948,Pool);put(ram,0x80192458,3);
    put(ram,0x801518B8,DisplayPool);
    for(unsigned i=0;i<total;++i){
        const uint32_t b=Buoy+i*0x104;
        number(ram,b,100+i*120);number(ram,b+4,20);number(ram,b+8,200+i*100);
        number(ram,b+0x60,110+i*120);number(ram,b+0x64,20);number(ram,b+0x68,210+i*100);
        put(ram,b+0x98,i%2);put(ram,b+0x9C,0);put(ram,b+0xC8,1);
        MEM_H(0,S32(Visibility+i*2))=i;MEM_B(0,S32(Indices+i))=0xFE;
    }
    for(unsigned p=0;p<2;++p){
        const uint32_t camera=0x80227C80+p*0x10C;
        number(ram,camera+0x4C,500+p*100);number(ram,camera+0x50,80);number(ram,camera+0x54,700-p*50);
    }
    return ram;
}
void matrices(Ram& ram,unsigned view){
    recomp_context c;context(c);c.r2=S32(Buoy);c.r4=get(ram,Count);c.r9=S32(Visibility);c.r13=0;c.r16=0;
    c.r22=S32(0x80227C80+view*0x10C);c.r30=S32(Buoy);c.f24.fl=0;c.f26.fl=1;
    native_buoy_matrices(ram.data(),&c);
    require(uint32_t(c.r29)==Stack,"native matrix stack imbalance");
}
std::vector<Command> draw(Ram& ram,Fn fn,uint32_t start=List){
    put(ram,Stack+0x550,start);
    recomp_context c;context(c);c.r12=S32(Indices);c.r16=0;c.r17=S32(0xE7000000);c.r20=0x01020040;
    c.r23=0x2000;c.r30=S32(Buoy);c.r31=0x06000000;c.r10=S32(0xB900031D);
    fn(ram.data(),&c);const auto end=get(ram,Stack+0x550);
    require(end>=start&&end<=start+0x1000&&(end-start)%8==0,"native detail list exceeds budget");
    std::vector<Command> out;for(uint32_t at=start;at<end;at+=8)out.emplace_back(get(ram,at),get(ram,at+4));return out;
}
bool has(const std::vector<Command>& c,uint32_t a,uint32_t b){return std::find(c.begin(),c.end(),Command{a,b})!=c.end();}
void preservePhysics(const Ram& before,const Ram& after,bool allowMatrices){
    for(unsigned i=0;i<Size;++i) if(before[i]!=after[i]){
        const uint32_t p=0x80000000+i;
        bool allowed=(p>=Stack-0x100&&p<Stack+0x600)||(p>=List&&p<List+0x1000);
        if(allowMatrices) allowed|=(p>=Pool+0x95C0&&p<Pool+0xA1C0)||(p>=Indices&&p<Indices+12);
        require(allowed,"changed physics, buoy positions, camera or unrelated state");
    }
}
void test(unsigned players,unsigned view,bool enable,unsigned course=1){
    ++cases;active=enable;auto ram=initial(players,view,2,course);const auto input=ram;matrices(ram,view);preservePhysics(input,ram,true);
    auto* rdram=ram.data();
    for(unsigned i=0;i<2;++i){
        require(MEM_BU(0,S32(Indices+i))==i,"native matrix slot assignment changed");
        const uint32_t matrix=Pool+0x9BC0+view*0x300+i*64;
        require(std::any_of(ram.begin()+(matrix&0x7FFFFF),ram.begin()+(matrix&0x7FFFFF)+64,[](auto b){return b!=0;}),"native tail matrix was not prepared");
    }
    auto baseline=ram,enhanced=ram;
    const auto orig=draw(baseline,baseline_buoy_detail),result=draw(enhanced,enhanced_buoy_detail);
    preservePhysics(ram,enhanced,false);
    if(!enable||players==1) require(result==orig&&baseline==enhanced,"Original/1P draw differs from native");
    if(enable||players==1){
        for(uint32_t root:{0x0102AE38u,0x0102AD90u,0x01029C88u,0x01029BE0u}) require(has(result,0x06000000,root),"full L/R tail or letter model missing");
        for(unsigned i=0;i<2;++i)require(has(result,0x01020040,0x05009BC0+view*0x300+i*64),"wrong player's native tail matrix used");
        auto single=ram;put(single,0x800DAB28,1);
        require(result==draw(single,baseline_buoy_detail),"enhanced detail is not exact native 1P pass");
    }else require(result.empty(),"native 2P should omit detail pass");
}
void testTwilightSegments(){
    constexpr uint32_t common=0x802F0000,commonBytes=0x16488;
    for(unsigned scroll=0;scroll<64;scroll+=4)for(unsigned frame=0;frame<3;++frame){
        ++cases;auto ram=initial(2,0,0,6);auto* rdram=ram.data();
        put(ram,0x801CE6B0+14*4,common&0x1FFFFFFF);
        put(ram,0x801C0CBC,scroll);put(ram,0x801C0CC0,frame);
        std::vector<Command> first;
        for(unsigned view=0;view<2;++view){
            put(ram,0x800DAB2C,view);const auto before=ram;
            const auto commands=draw(ram,native_twilight_segments);
            require(commands.size()==3,"Twilight must bind exactly three animated texture segments");
            const std::vector<Command> expected{
                {0xBC002406,common+0xF478+scroll*64},
                {0xBC002806,common+0x11480+scroll*64},
                {0xBC002C06,common+0x13488+frame*4096}};
            require(commands==expected,"native Twilight texture address or segment differs");
            for(const auto& [cmd,address]:commands)
                require(address>=common&&address+4096<=common+commonBytes,"animated texture's full4096-byte upload escapes resident common bank");
            require(get(ram,0x801C0CBC)==scroll&&get(ram,0x801C0CC0)==frame,"drawing a view advanced texture animation");
            preservePhysics(before,ram,false);
            if(view==0)first=commands;else require(commands==first,"both views must share the same native animation phase");
        }
        auto single=ram;put(single,0x800DAB28,1);
        require(draw(single,native_twilight_segments)==first,"native texture bindings differ between1P and2P");
    }
    // Execute the actual isolated native counter update, once before drawing
    // both views. Rendering must never become a second animation tick.
    ++cases;auto ram=initial(2,0,0,6);put(ram,0x801CE6B0+14*4,common&0x1FFFFFFF);
    put(ram,0x801C0CBC,60);put(ram,0x801C0CC4,18);put(ram,0x801C0CC0,1);
    recomp_context ctx;context(ctx);native_twilight_animation_update(ram.data(),&ctx);
    require(get(ram,0x801C0CBC)==0&&get(ram,0x801C0CC4)==0&&get(ram,0x801C0CC0)==0,"native animation wrap changed");
    const auto first=draw(ram,native_twilight_segments);put(ram,0x800DAB2C,1);
    require(draw(ram,native_twilight_segments)==first,"second view changed animation after native update");
    require(get(ram,0x801C0CBC)==0&&get(ram,0x801C0CC4)==0&&get(ram,0x801C0CC0)==0,"render advanced wrapped animation");
    ++cases;auto other=initial(2,0,0,1);
    require(draw(other,native_twilight_segments).empty(),"non-Twilight course gained animated texture bindings");
}
}
extern "C" uint32_t wr64_sunny_detail_active(uint8_t*){return active;}
extern "C" void do_break(uint32_t){require(false,"native break");}
extern "C" void* wr64_test_address(uint8_t* r,uint64_t at,unsigned width,const char*,int){
    ++accesses;uint32_t a=uint32_t(at);require(a>=0x80000000&&a<=0x80800000-width,"native access outside RDRAM");return r+(a&0x7FFFFF);
}
int main(){
    for(unsigned course=1;course<=8;++course){
        for(unsigned view=0;view<2;++view)for(bool enable:{false,true})test(2,view,enable,course);
        test(1,0,false,course);
    }
    testTwilightSegments();
    for(int reject=0;reject<3;++reject)for(unsigned view=0;view<2;++view){
        ++cases;active=true;auto ram=initial(2,view,1);auto* rdram=ram.data();
        if(reject==0)MEM_H(0,S32(Visibility))=-1;
        if(reject==1)put(ram,Buoy+0x9C,1);
        if(reject==2)put(ram,Buoy+0xC8,0);
        const auto before=ram;const auto result=draw(ram,enhanced_buoy_detail);preservePhysics(before,ram,false);
        for(auto cmd:result)require(cmd.first!=0x06000000&&cmd.first!=0x01020040,"culled/disabled/noncheckpoint buoy gained tail geometry");
        if(reject==0){
            const auto input=ram;matrices(ram,view);
            require(std::equal(ram.begin()+(Pool&0x7FFFFF),ram.begin()+(Pool&0x7FFFFF)+0xA200,input.begin()+(Pool&0x7FFFFF)),"culled buoy gained matrix work");
        }
    }
    for(unsigned view=0;view<2;++view){
        ++cases;active=true;auto empty=initial(2,view,0);
        require(draw(empty,enhanced_buoy_detail).empty(),"zero buoys must not add empty detail pass");
        ++cases;auto full=initial(2,view,12);matrices(full,view);
        const auto result=draw(full,enhanced_buoy_detail);
        require(result.size()==3+12*7,"twelve native matrix slots must all render exactly once");
        require(has(result,0x01020040,0x05009BC0+view*0x300+11*64),"last prepared native matrix slot missing");
        const uint32_t lastStart=DisplayPool+0x6000-0x800-uint32_t(result.size()*8);
        auto nearEnd=full;
        require(draw(nearEnd,enhanced_buoy_detail,lastStart)==result,"exact native DL budget unnecessarily drops valid detail");
        auto overEnd=full;
        require(draw(overEnd,enhanced_buoy_detail,lastStart+8).empty(),"insufficient native DL tail must fall back");
        ++cases;auto tooMany=initial(2,view,13);matrices(tooMany,view);
        require(draw(tooMany,enhanced_buoy_detail).empty(),"unprepared thirteenth matrix slot must never be consumed");
    }
    std::cout<<"PASS "<<cases<<" native buoy scenarios across eight VS courses, "<<checks<<" checks, "<<accesses<<" checked accesses\n";
}
