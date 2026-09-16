#include "wr64_seabed_distance.hpp"
#include "../../lib/rt64/src/common/rt64_wr64_rt_two_player_assets.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

extern "C" {
void func_8004C998(uint8_t*, recomp_context*);
void baseline_bottom_vertex(uint8_t*, recomp_context*);
void native_bottom_packet(uint8_t*, recomp_context*);
void SysUtils_Round(uint8_t*, recomp_context*);
}
namespace {
using Ram = std::vector<uint8_t>;
constexpr uint32_t Stack=0x807FF000, Output=0x801C43F8, Wave=0x80300000, Camera=0x80227C80;
constexpr int16_t Boundary[7][2]={{0,0},{-768,-384},{0,-768},{768,-384},{768,384},{0,768},{-768,384}};
unsigned assertions=0, scenarios=0;
uint64_t accesses=0;
bool enhancedTwoPlayer=true;
std::vector<uint8_t> rom;
void require(bool value, const char* message) {
    ++assertions;
    if(!value) { std::cerr<<"FAIL scenario "<<scenarios<<": "<<message<<'\n'; std::exit(1); }
}
void put(Ram& ram,uint32_t address,uint32_t value) { auto* rdram=ram.data(); MEM_W(0,S32(address))=value; }
uint32_t word(const Ram& ram,uint32_t address) { uint32_t result;std::memcpy(&result,ram.data()+(address&0x7FFFFF),4);return result; }
float real(const Ram& ram,uint32_t address) { return std::bit_cast<float>(word(ram,address)); }
void pf(Ram& ram,uint32_t address,float value) { put(ram,address,std::bit_cast<uint32_t>(value)); }
int16_t half(const Ram& ram,uint32_t address) { int16_t result;std::memcpy(&result,ram.data()+((address^2)&0x7FFFFF),2);return result; }
void ph(Ram& ram,uint32_t address,int16_t value) { auto* rdram=ram.data();MEM_H(0,S32(address))=value; }
Ram initial(unsigned buffer=0,unsigned cameraIndex=0,int centerX=0,int centerZ=0) {
    Ram ram(0x800000,0); auto* rdram=ram.data();
    for(size_t i=0;i<0x800DFFA8-0x80046800;++i) MEM_B(i,S32(0x80046800))=rom[0x1000+i];
    put(ram,0x800D8170,1);put(ram,0x800DAB28,1);put(ram,0x800DAB2C,0);put(ram,0x800DAB24,41);
    put(ram,0x801CE638,1);put(ram,0x801CE64C,0);put(ram,0x8011F8E0,buffer);
    put(ram,0x80223930,cameraIndex);put(ram,0x80223934,1-cameraIndex);
    put(ram,0x801518B8,Wave);put(ram,0x80192458,uint32_t(-300));
    // Actual Sunny values from the archived native gameplay captures.
    pf(ram,0x801924B4,49152.0f);pf(ram,0x801924C0,56755.83984375f);put(ram,0x80192498,10);
    put(ram,0x800D476C,42);put(ram,0x800D4770,6);
    for(unsigned n=0;n<7;++n) {
        put(ram,0x80192460+n*4,n);
        for(unsigned p=0;p<2;++p) {
            const uint32_t at=Wave+(p?0x170D8:0x13D68)+n*16;
            ph(ram,at,int16_t(centerX+Boundary[n][0]));ph(ram,at+4,int16_t(centerZ+Boundary[n][1]));
        }
    }
    for(unsigned i=0;i<2;++i) {
        const uint32_t camera=Camera+i*0x10C;
        put(ram,camera,4);put(ram,camera+0xE8,i);
        pf(ram,camera+0x4C,float(centerX+100));pf(ram,camera+0x50,75.0f);pf(ram,camera+0x54,float(centerZ+200));
        pf(ram,camera+0xF0,0.0f);pf(ram,camera+0xF4,0.0f);
    }
    // Non-position bytes make accidental widening of a write observable.
    const uint32_t out=Output+buffer*0x3630;
    for(unsigned n=0;n<7;++n) {
        ph(ram,out+n*16+6,int16_t(0x6000+n));put(ram,out+n*16+12,0x11223344+n);
    }
    return ram;
}
recomp_context run(Ram& ram,bool patched) {
    recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;
    ctx.r29=S32(Stack);ctx.r4=0;ctx.r5=S32(Output+word(ram,0x8011F8E0)*0x3630);
    ctx.r16=0x12345678;ctx.r19=0x34567890;ctx.f20.u64=0x402123456789ABCD;
    (patched?func_8004C998:baseline_bottom_vertex)(ram.data(),&ctx);
    require(uint32_t(ctx.r29)==Stack && ctx.r16==0x12345678 && ctx.r19==0x34567890 &&
        ctx.f20.u64==0x402123456789ABCD,"native stack and saved registers preserved");
    ctx.f_odd=nullptr;
    return ctx;
}
int nativeRound(Ram& ram,float value) {
    recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;ctx.f12.fl=value;
    SysUtils_Round(ram.data(),&ctx);return int32_t(ctx.r2);
}
float nativeRatio(const Ram& ram,unsigned index=0) {
    const float cameraY=real(ram,Camera+index*0x10C+0x50);
    const float denominator=float(int32_t(word(ram,0x80192458)))-cameraY;
    return denominator==0.0f?1.0f:(real(ram,0x800D4768)-cameraY)/denominator;
}
recomp_context directContext(Ram& ram,unsigned index=0) {
    recomp_context ctx{};ctx.r29=S32(Stack-0x48);ctx.r19=S32(Camera+index*0x10C);
    ctx.f20.fl=nativeRatio(ram,index);put(ram,Stack+4,Output+word(ram,0x8011F8E0)*0x3630);
    return ctx;
}
void identical(Ram input,unsigned mode,const char* message,int loadedCourse=-1,bool foreignOwner=false) {
    ++scenarios;auto changed=input;
    wr64::seabed_distance::set_mode(mode);
    const auto a=run(input,false);
    RT64::wr64RTPublishTwoPlayerAssets(loadedCourse>=0?(foreignOwner?input.data():changed.data()):nullptr,unsigned(loadedCourse));
    const auto b=run(changed,true);
    RT64::wr64RTPublishTwoPlayerAssets(nullptr,0);
    require(input==changed,message);require(std::memcmp(&a,&b,sizeof a)==0,"native register result differs");
}
void expandedRam(Ram baseline,unsigned mode,int loadedCourse=-1) {
    ++scenarios;auto changed=baseline;
    const unsigned view=enhancedTwoPlayer && word(baseline,0x800DAB28)==2 ? word(baseline,0x800DAB2C) : 0;
    const unsigned buffer=word(baseline,0x8011F8E0),index=word(baseline,0x80223930+view*4);
    wr64::seabed_distance::set_mode(mode);
    const auto a=run(baseline,false);
    RT64::wr64RTPublishTwoPlayerAssets(loadedCourse>=0?changed.data():nullptr,unsigned(loadedCourse));
    const auto b=run(changed,true);
    RT64::wr64RTPublishTwoPlayerAssets(nullptr,0);
    require(std::memcmp(&a,&b,sizeof a)==0,"extension changed native registers");
    const uint32_t out=Output+buffer*0x3630+view*0x70, camera=Camera+index*0x10C;
    const float scale=mode==1?1.5f:float(mode),ratio=nativeRatio(baseline,index);
    const int cx=half(baseline,out),cz=half(baseline,out+4);
    if(changed==baseline) {
        std::cerr<<"rejected center="<<cx<<','<<cz<<" cameraType="<<word(baseline,camera)<<" ratio="<<ratio<<" divisors="<<real(baseline,0x801924CC)<<','<<real(baseline,0x801924D0)<<" offsets="<<int32_t(word(baseline,0x800D4774))<<','<<int32_t(word(baseline,0x800D4778))<<'\n';
        for(unsigned i=0;i<7;++i) std::cerr<<i<<": "<<half(baseline,out+i*16)<<','<<half(baseline,out+i*16+4)<<" uv="<<half(baseline,out+i*16+10)<<','<<half(baseline,out+i*16+8)<<'\n';
    }
    require(changed!=baseline,"eligible producer did not extend");
    for(unsigned i=0;i<7;++i) {
        const uint32_t v=out+i*16;
        const int x=nativeRound(baseline,float(cx)+(int(half(baseline,v))-cx)*scale);
        const int z=nativeRound(baseline,float(cz)+(int(half(baseline,v+4))-cz)*scale);
        const float texX=((float(x)-real(baseline,camera+0x4C))*ratio+real(baseline,camera+0x4C))/real(baseline,0x801924CC);
        const float texZ=((float(z)-real(baseline,camera+0x54))*ratio+real(baseline,camera+0x54))/real(baseline,0x801924D0);
        const int s=nativeRound(baseline,texX)+int32_t(word(baseline,0x800D4774));
        const int t=nativeRound(baseline,texZ)+int32_t(word(baseline,0x800D4778));
        require(half(changed,v)==x && half(changed,v+4)==z,"native perimeter distance was not multiplied");
        require(half(changed,v+10)==s && half(changed,v+8)==t,"native texture density mapping changed");
        // Restore only the permitted fields; the complete RDRAM must match.
        for(unsigned o:{0u,4u,8u,10u}) ph(changed,v+o,half(baseline,v+o));
    }
    require(changed==baseline,"write escaped six outer X/Z and S/T fields");
}
void reject(Ram ram,recomp_context ctx,const char* message,unsigned mode=2) {
    ++scenarios;const auto before=ram;const auto saved=ctx;
    wr64::seabed_distance::set_mode(mode);wr64_seabed_distance_finish(ram.data(),&ctx);
    require(ram==before,message);require(std::memcmp(&ctx,&saved,sizeof ctx)==0,"rejection changed registers");
}
Ram twoPlayer(unsigned course,unsigned view,unsigned buffer,bool swapped) {
    auto r=initial(buffer);put(r,0x800D8170,course);put(r,0x800DAB28,2);put(r,0x800DAB2C,view);
    put(r,0x80223930,swapped?1:0);put(r,0x80223934,swapped?0:1);
    for(unsigned p=0;p<2;++p) {
        const unsigned index=word(r,0x80223930+p*4);
        const int cx=p?3500:-2500,cz=p?-4500:1500;
        const uint32_t camera=Camera+index*0x10C;
        put(r,camera,p?3:4);pf(r,camera+0x4C,float(cx+100));pf(r,camera+0x54,float(cz+200));
        pf(r,camera+0x50,p?125.f:50.f);
        for(unsigned n=0;n<7;++n) {
            const uint32_t at=Wave+(p?0x170D8:0x13D68)+n*16;
            ph(r,at,int16_t(cx+Boundary[n][0]));ph(r,at+4,int16_t(cz+Boundary[n][1]));
            const uint32_t out=Output+buffer*0x3630+p*0x70+n*16;
            ph(r,out+6,int16_t(0x6200+p*16+n));put(r,out+12,0xA1020300+p*16+n);
        }
    }
    return r;
}
void worldScopes() {
    for(unsigned course=0;course<9;++course) {
        auto r=initial(course%2,course%2);put(r,0x800D8170,course);
        put(r,Camera+(course%2)*0x10C,course%2?3:4);
        for(unsigned raceMode:{7u,39u,40u,45u,46u}) {
            put(r,0x800DAB24,raceMode);identical(r,0,"All-course race Original parity failed");
            expandedRam(r,2);expandedRam(r,5);
        }
        for(auto phaseMode:std::array<std::array<unsigned,2>,3>{{{8,30},{8,31},{1,7}}}) {
            put(r,0x801CE638,phaseMode[0]);put(r,0x800DAB24,phaseMode[1]);
            put(r,Camera+(course%2)*0x10C,phaseMode[0]==8?5:3);
            identical(r,0,"Introduction Original parity failed");expandedRam(r,2);
        }
    }
    for(unsigned mode:{2u,3u,4u}) {
        auto r=initial();put(r,0x800D8170,0);put(r,0x801CE638,0);put(r,0x800DAB24,mode);
        identical(r,0,"Dolphin opening Original parity failed");expandedRam(r,2);expandedRam(r,5);
    }
    for(unsigned course=1;course<=8;++course) for(unsigned view:{0u,1u}) for(bool swapped:{false,true}) {
        auto r=twoPlayer(course,view,course%2,swapped);
        identical(r,0,"Enhanced two-player Original parity failed");expandedRam(r,2);expandedRam(r,5);
    }
    // Dolphin Free Ride loads the full two-player assets. Exercise the native
    // producer and existing camera/output adapter for each view and buffer;
    // an absent, stale-RAM or other-course asset publication must still reject.
    for(unsigned buffer:{0u,1u})for(unsigned view:{0u,1u})for(bool swapped:{false,true}) {
        auto r=twoPlayer(0,view,buffer,swapped);
        identical(r,0,"Dolphin Free Ride Original parity failed",0);
        expandedRam(r,2,0);expandedRam(r,5,0);
        identical(r,2,"Dolphin Free Ride without loaded full assets expanded");
        identical(r,2,"Dolphin Free Ride accepted another course's assets",4);
        identical(r,2,"Dolphin Free Ride accepted another RAM owner's assets",0,true);
    }
    for(unsigned buffer:{0u,1u}) {
        // Real adapter must use the second view's wave data, camera and +0x70
        // output while preserving the first view's already produced vertices.
        auto r=twoPlayer(4,0,buffer,true);
        wr64::seabed_distance::set_mode(2);run(r,true);
        const auto first=r;put(r,0x800DAB2C,1);run(r,true);
        const uint32_t out=Output+buffer*0x3630;
        require(std::equal(first.begin()+(out&0x7FFFFF),first.begin()+(out&0x7FFFFF)+0x70,
            r.begin()+(out&0x7FFFFF)),"Second-view bottom producer overwrote first-view geometry");
        // Original opaque 2P mode deliberately has no separate bottom for P2.
        // Its unadapted camera-zero fallback must not be expanded as view1.
        enhancedTwoPlayer=false;
        identical(twoPlayer(4,1,buffer,true),2,"Opaque P2 fallback slot was incorrectly expanded");
        identical(twoPlayer(4,1,buffer,true),5,"Opaque P2 fallback slot was incorrectly expanded at5x");
        enhancedTwoPlayer=true;
    }
    auto out=twoPlayer(4,1,0,false);put(out,0x800D8170,0);identical(out,2,"Unsupported two-player Dolphin state expanded");
    out=twoPlayer(4,1,0,false);put(out,0x801CE638,8);put(out,0x800DAB24,30);
    identical(out,2,"Unsupported two-player introduction expanded");
    out=twoPlayer(4,1,0,false);put(out,0x800DAB2C,2);identical(out,2,"Invalid third view expanded");
}
void nativeParametersAndMaterial() {
    // The producer has one UV formula for every sea mode. Its native branch
    // is instead a zero denominator when camera height equals seabed height.
    for(unsigned sea:{0u,1u,2u}) for(unsigned cameraType:{3u,4u,5u}) for(int floor:{-300,0,75}) {
        auto r=initial();put(r,0x800D8170,7);put(r,0x801CE64C,sea);put(r,Camera,cameraType);
        put(r,0x80192458,uint32_t(floor));pf(r,Camera+0x50,75);
        pf(r,0x801924B4,24576);pf(r,0x801924C0,113511.6796875f);
        put(r,0x800D4774,287);put(r,0x800D4778,uint32_t(-333));
        pf(r,0x800D477C,1);pf(r,Camera+0xF0,0.5f);pf(r,Camera+0xF4,-0.25f);
        identical(r,0,"Native sea/texture/height branch Original parity failed");expandedRam(r,2);expandedRam(r,5);
    }
    constexpr uint32_t packets=0x80340000;
    for(unsigned players:{1u,2u}) for(unsigned view=0;view<players;++view)
    for(unsigned sea:{0u,1u,2u}) for(bool detail:{false,true}) {
        ++scenarios;enhancedTwoPlayer=detail;
        auto r=players==2?twoPlayer(4,view,0,false):initial();put(r,0x801CE64C,sea);
        recomp_context c{};c.f_odd=&c.f0.u32h;c.r6=S32(packets);
        c.r11=1;c.r10=S32(0xE7000000);c.r31=0x06000000;
        native_bottom_packet(r.data(),&c);
        unsigned roots=0;uint32_t root=0;
        for(uint32_t p=packets;p<uint32_t(c.r6);p+=8) if(word(r,p)==0x06000000) {++roots;root=word(r,p+4);}
        const bool drawFloor=(players==1 || detail) && sea!=1;
        require(roots==unsigned(drawFloor),"Native seabed material admission differs by sea mode or 2P detail");
        if(drawFloor) require(root==0x010103F0+(players==2?view*0x40:0),"Native floor draw referenced the wrong view's vertex list");
    }
    enhancedTwoPlayer=true;
}
}
extern "C" void* wr64_test_address(uint8_t* ram,uint64_t address,unsigned bytes,const char*,int) {
    ++accesses;const uint32_t at=uint32_t(address);
    require(at>=0x80000000 && at<=0x80800000-bytes && !(at&(bytes-1)),"native RAM access escaped fixture");
    return ram+(at&0x7FFFFF);
}
extern "C" void wr64_forensic_capture_sky(uint8_t*,uint32_t,uint32_t,uint32_t) {}
// Only the detail feature's availability is stubbed. The actual bottom camera
// adapter is linked, selects the native view, and offsets its output by0x70.
extern "C" uint32_t wr64_sunny_detail_active(uint8_t* rdram) {
    return enhancedTwoPlayer && uint32_t(MEM_W(0,S32(0x800DAB28)))==2;
}

int main(int argc,char** argv) {
    require(argc>=2,"private ROM path required");std::ifstream in(argv[1],std::ios::binary);
    rom.assign(std::istreambuf_iterator<char>(in),{});require(rom.size()==0x800000,"private USA Rev1 ROM size");
    for(unsigned buffer:{0u,1u}) for(unsigned index:{0u,1u}) {
        identical(initial(buffer,index),0,"Original is not bit-identical");
        for(unsigned mode:{1u,2u,3u,4u,5u}) for(auto location:std::array<std::array<int,2>,4>{{{0,0},{9920,8868},{-9920,-8868},{18000,17000}}})
            expandedRam(initial(buffer,index,location[0],location[1]),mode);
    }
    for(unsigned value=0;value<=5;++value) {
        wr64::seabed_distance::set_mode(value);
        require(wr64::seabed_distance::mode()==value,"valid mode did not round-trip");
    }
    for(unsigned value:{6u,100u,UINT32_MAX}) {wr64::seabed_distance::set_mode(value);require(wr64::seabed_distance::mode()==0,"invalid mode did not use Original");}
    wr64::seabed_distance::set_mode(0);
    wr64_seabed_distance_finish(reinterpret_cast<uint8_t*>(uintptr_t(1)),reinterpret_cast<recomp_context*>(uintptr_t(1)));
    wr64::seabed_distance::set_mode(2);wr64_seabed_distance_finish(nullptr,nullptr);
    const std::array<std::pair<uint32_t,uint32_t>,9> excluded={{{0x800D8170,9},{0x800DAB28,0},{0x800DAB28,3},{0x800DAB2C,1},
        {0x801CE638,2},{0x801CE638,0},{Camera,6},{Camera+0xE8,1},{Camera,0}}};
    for(auto [address,value]:excluded) for(unsigned mode:{2u,5u}) {
        auto r=initial();put(r,address,value);identical(r,mode,"out-of-scope producer changed");
    }
    auto native=initial();run(native,false);auto baseCtx=directContext(native);
    for(unsigned n=0;n<11;++n) {
        auto r=native;auto c=baseCtx;
        switch(n) {
        case 0:c.r19=1;break;
        case 1:c.r29=1;break;
        case 2:put(r,Stack+4,Output+16);break;
        case 3:put(r,0x8011F8E0,2);break;
        case 4:put(r,0x80223930,2);break;
        case 5:pf(r,0x801924CC,0);break;
        case 6:pf(r,0x801924D0,std::numeric_limits<float>::quiet_NaN());break;
        case 7:c.f20.fl=std::numeric_limits<float>::infinity();break;
        case 8:ph(r,Output+16+2,5);break;
        case 9:ph(r,Output+16+8,int16_t(half(r,Output+16+8)+1));break;
        case 10:pf(r,Camera+0x4C,std::numeric_limits<float>::quiet_NaN());break;
        }
        for(unsigned mode:{2u,5u}) reject(r,c,"malformed producer did not retain native output",mode);
    }
    // Position and UV overflow must retain every original byte, including all
    // earlier staged corners. Preserve internally valid UVs for each fixture.
    for(bool uvOverflow:{false,true}) {
        auto r=initial();
        if(uvOverflow) {pf(r,0x801924B4,64.0f);pf(r,0x801924C0,256.0f);}
        else for(unsigned n=1;n<7;++n) ph(r,Wave+0x13D68+n*16,int16_t(Boundary[n][0]*24));
        run(r,false);auto c=directContext(r);
        for(unsigned mode:{2u,5u}) reject(r,c,"overflow committed a partial seabed",mode);
    }
    // A valid native fan near either signed-position limit still supports 2x,
    // while 5x must retain the complete original fan without wrapped corners.
    for(int center:{-29000,29000}) {
        auto r=initial(0,0,center,0);
        expandedRam(r,2);
        identical(r,5,"5x position limit committed a partial or wrapped fan");
    }
    worldScopes();
    nativeParametersAndMaterial();
    for(int i=2;i<argc;++i) {
        std::ifstream capture(argv[i],std::ios::binary);
        Ram r(std::istreambuf_iterator<char>(capture),{});require(r.size()==0x800000,"native capture RAM size");
        std::cout<<"Archive course="<<word(r,0x800D8170)<<" mode="<<word(r,0x800DAB24)<<
            " phase="<<word(r,0x801CE638)<<" camera="<<word(r,Camera+word(r,0x80223930)*0x10C)<<
            " buffer="<<word(r,0x8011F8E0)<<'\n';
        identical(r,0,"Original changed an archived native frame");
        for(unsigned mode:{1u,2u,3u,4u,5u}) expandedRam(r,mode);
    }
    std::cout<<"PASS "<<scenarios<<" native seabed scenarios, "<<assertions<<" assertions, "<<accesses<<" checked accesses.\n";
}
