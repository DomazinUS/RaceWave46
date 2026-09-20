#include "recomp.h"
#include "wr64_sunny_sky.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

extern "C" {
void func_8008FB74(uint8_t*, recomp_context*);
void baseline_func_8008FB74(uint8_t*, recomp_context*);
void actual_cloud_vertex(uint8_t*, recomp_context*);
void baseline_bottom_vertex(uint8_t*, recomp_context*);
}
namespace {
using Ram = std::vector<uint8_t>;
using Command = std::pair<uint32_t,uint32_t>;
constexpr uint32_t RamSize=0x800000, Stack=0x807FF000, Gp=0x80500000, Dynamic=0x801C43F8, Stride=0x3630;
constexpr int16_t WaveBoundary[7][2]={{0,0},{-2000,-1000},{0,-2000},{2000,-1000},{2000,1000},{0,2000},{-2000,1000}};
bool active=false;
unsigned checks=0, scenarios=0, cloudCalls=0, bottomCalls=0;
int currentCourse=1;
uint64_t accesses=0;
uint32_t cloudCamera=0, cloudDestination=0;
std::vector<uint8_t> rom;
void require(bool value, const char* message) {
    ++checks;
    if(!value) { std::cerr<<"FAIL course "<<currentCourse<<": "<<message<<'\n'; std::exit(1); }
}
void put(uint8_t* rdram,uint32_t address,uint32_t value) { MEM_W(0,S32(address))=value; }
uint32_t get(uint8_t* rdram,uint32_t address) { return MEM_W(0,S32(address)); }
void pf(uint8_t* rdram,uint32_t address,float value) { put(rdram,address,std::bit_cast<uint32_t>(value)); }
void copy(uint8_t* rdram,uint32_t address,const std::vector<uint8_t>& data,size_t offset,size_t size) {
    require(offset+size<=data.size() && (address&0x7FFFFF)+size<=RamSize,"ROM copy out of range");
    for(size_t n=0;n<size;++n) MEM_B(n,S32(address))=data[offset+n];
}
uint32_t be(size_t address) {
    require(address+4<=rom.size(),"ROM read out of range");
    return uint32_t(rom[address])<<24|uint32_t(rom[address+1])<<16|uint32_t(rom[address+2])<<8|rom[address+3];
}
std::vector<uint8_t> mio(size_t start,size_t end) {
    require(be(start)==0x4D494F30,"MIO signature");
    const size_t size=be(start+4); size_t packed=start+be(start+8),raw=start+be(start+12),bits=start+16;
    unsigned mask=0,word=0; std::vector<uint8_t> out;
    while(out.size()<size) {
        if(!mask) { require(bits<end,"MIO bit range");word=rom[bits++];mask=128; }
        if(word&mask) { require(raw<end,"MIO literal range");out.push_back(rom[raw++]); }
        else {
            require(packed+2<=end,"MIO packed range");
            unsigned token=unsigned(rom[packed])<<8|rom[packed+1];packed+=2;
            unsigned count=(token>>12)+3,back=(token&4095)+1;
            require(back<=out.size() && out.size()+count<=size,"MIO bounds");
            while(count--) out.push_back(out[out.size()-back]);
        }
        mask>>=1;
    }
    return out;
}
Ram initial(int players,int view,int buffer,int sea=0,int course=1) {
    Ram ram(RamSize,0); auto* rdram=ram.data();
    copy(rdram,0x80046800,rom,0x1000,0x800DFFA8-0x80046800);
    put(rdram,0x800D8170,course);put(rdram,0x800DAB28,players);put(rdram,0x800DAB2C,view);
    put(rdram,0x801CE638,1);put(rdram,0x801CE64C,sea);put(rdram,0x8011F8E0,buffer);
    // Deliberately request the embedded fog animation: enhanced 2P rendering
    // must leave it dormant just as the stock two-player path does.
    MEM_B(0,S32(0x800D9888))=1;put(rdram,0x801C1FD0,1);
    put(rdram,0x80223930,0);put(rdram,0x80223934,1);
    // The native bottom producer consumes seven boundary indices from each
    // player's existing wave vertices; use distinct synthetic boundaries to
    // make wrong-player inputs fail even if the output slot is correct.
    constexpr uint32_t WaveDynamic=0x80300000;
    put(rdram,0x801518B8,WaveDynamic);
    put(rdram,0x80192458,uint32_t(-300));
    pf(rdram,0x801924B4,2048.0f);pf(rdram,0x801924C0,8192.0f);
    put(rdram,0x80192498,10);
    for(unsigned n=0;n<7;++n) {
        put(rdram,0x80192460+n*4,n);
        for(unsigned p=0;p<2;++p) {
            const uint32_t v=WaveDynamic+(p?0x170D8:0x13D68)+n*16;
            MEM_H(0,S32(v))=WaveBoundary[n][0]+p*900;
            MEM_H(4,S32(v))=WaveBoundary[n][1]+p*700;
        }
    }
    for(unsigned i=0;i<4096;++i) pf(rdram,0x80154350+i*4,float(std::sin(i*6.2831853071795864769/4096)));
    for(unsigned i=0;i<2;++i) {
        const uint32_t camera=0x80227C80+i*0x10C;
        pf(rdram,camera+0x4C,100.0f+i*150.0f);pf(rdram,camera+0x50,75.0f);pf(rdram,camera+0x54,200.0f);
        pf(rdram,camera+0x64,i?0.6f:0.0f);pf(rdram,camera+0x68,-0.2f);pf(rdram,camera+0x6C,i?-0.8f:-1.0f);
        pf(rdram,camera+0x70,0.0f);pf(rdram,camera+0x74,1.0f);pf(rdram,camera+0x78,0.0f);
        pf(rdram,camera+0x88,72.0f);pf(rdram,camera+0x94,10.0f);pf(rdram,camera+0x9C,1.0f);
        pf(rdram,camera+0xF0,i?0.6f:0.0f);pf(rdram,camera+0xF4,i?-0.8f:-1.0f);
        copy(rdram,0x801CB058+i*0x110,rom,0x800D9964-0x80045800+course*0x110,0x110);
        put(rdram,0x801CB058+i*0x110+0xB8,190+i*30);
        put(rdram,0x801CB058+i*0x110+0xBC,200+i*20);
        put(rdram,0x801CB058+i*0x110+0xC0,210+i*10);
    }
    // The actual native 2P sky transfer list contains both background textures
    // and the cloud texture already; no additional DMA is required for clouds.
    const uint32_t list=be(0x800DC108+course*4-0x80045800);
    for(size_t a=list-0x80045800;be(a+8);a+=16) {
        require(be(a+8)==1 || (course==0 && be(a+8)==3),"unexpected sky transfer flag");
        auto data=mio(be(a),be(a+4));copy(rdram,0x80400000+be(a+12),data,0,data.size());
    }
    if(course==1) require(std::memcmp(rdram+0x400000,rdram+0x400200,512)==0,"Sunny background pair differs");
    require(std::any_of(rdram+0x407400,rdram+0x408400,[](auto v){return v!=0;}),"cloud texture missing");
    return ram;
}
std::vector<Command> run(Ram& ram,bool patched) {
    recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;ctx.r29=S32(Stack);ctx.r4=S32(Gp);
    cloudCalls=0;bottomCalls=0;
    (patched?func_8008FB74:baseline_func_8008FB74)(ram.data(),&ctx);
    require(uint32_t(ctx.r29)==Stack,"unbalanced sky stack");
    require(cloudCalls==1,"cloud animation helper called more than once per view");
    require(bottomCalls==1,"bottom producer called more than once per view");
    require(uint32_t(ctx.r2)>=Gp && uint32_t(ctx.r2)<Gp+4096,"display list budget");
    std::vector<Command> result;
    for(uint32_t p=Gp;p<uint32_t(ctx.r2);p+=8) result.emplace_back(get(ram.data(),p),get(ram.data(),p+4));
    return result;
}
std::vector<Command> cameraCommands(const std::vector<Command>& commands) {
    std::vector<Command> result;
    for(auto c:commands) if((c.first>>24)==0xED || (c.first>>24)==3 || (c.first>>24)==1 || c.first==0xBC001806) result.push_back(c);
    return result;
}
bool has(const std::vector<Command>& commands,uint32_t first,uint32_t second) {
    return std::find(commands.begin(),commands.end(),Command(first,second))!=commands.end();
}
void checkFrame(int view,int buffer,int sea,bool enabled,int course=1) {
    currentCourse=course;
    ++scenarios;auto baseline=initial(2,view,buffer,sea,course),changed=baseline;
    active=enabled;auto original=run(baseline,false);auto result=run(changed,true);
    require(cameraCommands(original)==cameraCommands(result),"viewport/scissor/projection changed");
    require(get(changed.data(),0x800DAB28)==2 && get(changed.data(),0x800DAB2C)==unsigned(view),"game player state changed");
    if(!enabled) { require(baseline==changed && original==result,"disabled mode differs from native");return; }
    const bool bottom=sea!=1;
    const Command bottomList{0x06000000,view?0x01010430:0x010103F0};
    require(!has(original,0x06000000,0x010103F0) && !has(original,0x06000000,0x01010430),"native 2P unexpectedly has a seabed underlay");
    require(has(result,bottomList.first,bottomList.second)==bottom,"restored seabed draw/sea-mode gate incorrect");
    require(has(result,0xFD10000F,0x08001400)==bottom,"restored seabed texture missing");
    if(bottom) {
        const auto bed=std::find(result.begin(),result.end(),bottomList);
        const auto sky=std::find(result.begin(),result.end(),Command{0x06000000,0x01010330});
        require(bed<sky,"seabed must be drawn before sky state and transparent waves");
        require(has(result,0xB900031D,course==4?0xCB024000:0x0F0A4000),"native seabed render state changed");
        if(course==4) require(has(result,0xB7000000,0x00010204),"Drake seabed fog geometry mode missing");
    }
    require(cloudCamera==unsigned(view),"clouds used other player's camera");
    require(cloudDestination==Dynamic+buffer*Stride+0x1C0+view*0x70,"cloud helper wrote wrong buffer");
    require(has(result,0xFD100000,0x08000200),"second backdrop texture not loaded");
    require(has(result,0xFC22FFFF,0x1FFCFA38),"native two-texture combiner missing");
    require(std::memcmp(baseline.data()+0x1CB058,changed.data()+0x1CB058,0x220)==0,"extra fog/lighting simulation update");
    require(get(baseline.data(),0x801924C4)==get(changed.data(),0x801924C4) &&
        get(baseline.data(),0x801924C8)==get(changed.data(),0x801924C8),"extra cloud scrolling tick");
    const bool clouds=sea!=1 && sea!=2;
    require(has(result,0xFD700000,0x08007400)==clouds,"cloud sea-mode gate changed");
    if(clouds) {
        require(has(result,0x06000000,view?0x01010478:0x01010470),"wrong cloud draw-list entry");
        if(view) require(has(result,0x04000E6F,0x06000230),"second cloud vertex slot not selected");
        require(has(result,0xFA000000,view?0xDCDCDC00:0xBEC8D200),"wrong cloud color record");
    }
    // Compare with the actual native helper invoked independently for this
    // camera. It writes exactly seven vertices into the same reserved slot.
    auto expected=initial(2,view,buffer,sea,course);
    recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;ctx.r29=S32(Stack);
    ctx.r4=view;ctx.r5=S32(Dynamic+buffer*Stride+0x1C0+view*0x70);
    actual_cloud_vertex(expected.data(),&ctx);
    const auto vertex=(Dynamic+buffer*Stride+0x1C0+view*0x70)&0x7FFFFF;
    require(std::memcmp(expected.data()+vertex,changed.data()+vertex,112)==0,"cloud geometry differs from native camera helper");
    // Invoke the original bottom helper directly for the selected player. Its
    // output must match, including that player's wave boundary and UV mapping.
    ctx={};ctx.f_odd=&ctx.f0.u32h;ctx.r29=S32(Stack);ctx.r4=view;
    const uint32_t bottomAddress=Dynamic+buffer*Stride+view*0x70;
    ctx.r5=S32(bottomAddress);baseline_bottom_vertex(expected.data(),&ctx);
    const uint32_t bedOffset=bottomAddress&0x7FFFFF;
    require(std::memcmp(expected.data()+bedOffset,changed.data()+bedOffset,112)==0,"bottom differs from native per-player producer");
    for(unsigned n=0;n<7;++n) {
        auto* rdram=changed.data();
        require(MEM_H(2,S32(bottomAddress+n*16))==-300,"bottom plane must be below wave surface");
        if(n) {
            require(MEM_H(0,S32(bottomAddress+n*16))==WaveBoundary[n][0]+view*900,"wrong player X boundary source");
            require(MEM_H(4,S32(bottomAddress+n*16))==WaveBoundary[n][1]+view*700,"wrong player Z boundary source");
        }
    }
    if(view) require(std::all_of(changed.begin()+((Dynamic+buffer*Stride)&0x7FFFFF),
        changed.begin()+((Dynamic+buffer*Stride+0x70)&0x7FFFFF),[](auto v){return v==0;}),"second view overwrote first bottom slot");
    require(std::memcmp(baseline.data()+0x300000,changed.data()+0x300000,0x20000)==0,"bottom restoration changed source wave vertices");
    bool visible=false;
    for(unsigned i=0;i<7;++i) visible|=changed[(vertex+15+i*16)^3]!=0;
    require(visible,"native cloud vertices all transparent");
    if(view) require(std::all_of(changed.begin()+((Dynamic+buffer*Stride+0x1C0)&0x7FFFFF),
        changed.begin()+((Dynamic+buffer*Stride+0x230)&0x7FFFFF),[](auto v){return v==0;}),"second view overwrote first cloud buffer");
}
}
extern "C" uint32_t wr64_sunny_detail_active(uint8_t*) { return active; }
extern "C" void func_8004C1D0(uint8_t* rdram,recomp_context* ctx) {
    ++cloudCalls;cloudCamera=uint32_t(ctx->r4);cloudDestination=uint32_t(ctx->r5);actual_cloud_vertex(rdram,ctx);
}
extern "C" void wr64_forensic_capture_sky(uint8_t*,uint32_t phase,uint32_t,uint32_t) { if(phase==0) ++bottomCalls; }
extern "C" void func_8008CFEC(uint8_t*,recomp_context*) { require(false,"unexpected celestial helper"); }
extern "C" void func_8008D454(uint8_t*,recomp_context*) { require(false,"unexpected celestial helper"); }
extern "C" void func_8008D94C(uint8_t*,recomp_context*) { require(false,"unexpected celestial helper"); }
extern "C" void func_8008DFD0(uint8_t*,recomp_context*) { require(false,"unexpected celestial helper"); }
extern "C" void _nsqrtf(uint8_t*,recomp_context* ctx) { require(std::isfinite(ctx->f12.fl)&&ctx->f12.fl>=0,"invalid native sqrt input");ctx->f0.fl=std::sqrt(ctx->f12.fl); }
extern "C" void wr64_watercraft_preview_viewport(uint8_t*,recomp_context*) { require(false,"unexpected preview viewport"); }
extern "C" uint32_t wr64_experimental_viewport_borders() { return 0; }
extern "C" uint32_t wr64_watercraft_preview_scissor(uint32_t value) { return value; }
extern "C" void do_break(uint32_t) { require(false,"native break"); }
extern "C" void* wr64_test_address(uint8_t* rdram,uint64_t address,unsigned size,const char*,int) {
    ++accesses;uint32_t a=uint32_t(address);require((a&0x7FFFFF)+size<=RamSize,"native RDRAM access overflow");return rdram+(a&0x7FFFFF);
}
int main(int argc,char** argv) {
    require(argc==2,"private ROM argument missing");std::ifstream file(argv[1],std::ios::binary);rom.assign(std::istreambuf_iterator<char>(file),{});
    require(rom.size()==0x800000 && be(0)==0x80371240,"invalid ROM");
    // Confirm skipping the native cloud list's first command reaches its
    // original six-triangle fan, with no hidden state initialization omitted.
    require(be(0x106500)==0x04000E6F && be(0x106504)==0x060001C0,"cloud list first load changed");
    for(unsigned i=0;i<6;++i) require(be(0x106508+i*8)==0xBF000000,"cloud triangle list changed");
    require(be(0x106538)==0xB8000000,"cloud list end changed");
    for(unsigned p=0;p<2;++p) {
        const size_t list=0x106480+p*0x40;
        require(be(list)==0x04000E6F && be(list+4)==0x06000000+p*0x70,"bottom display-list vertex slot changed");
        for(unsigned i=0;i<6;++i) require(be(list+8+i*8)==0xBF000000,"bottom six-triangle fan changed");
        require(be(list+0x38)==0xB8000000,"bottom display-list end changed");
    }
    for(int course=0;course<=8;++course) for(int buffer:{0,1}) for(int view:{0,1}) for(int sea:{0,1,2})
        for(bool enabled:{false,true}) checkFrame(view,buffer,sea,enabled,course);
    active=false;auto original=initial(1,0,0),changed=original;
    require(run(original,false)==run(changed,true) && original==changed,"one-player result changed");
    std::cout<<"PASS "<<scenarios+1<<" native sky scenarios, "<<checks<<" assertions, "<<accesses<<" checked accesses.\n";
    return 0;
}
