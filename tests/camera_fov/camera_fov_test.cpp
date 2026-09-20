#include "wr64_camera_fov.hpp"
#include "../../lib/rt64/src/common/rt64_wr64_rt_two_player_assets.h"
#include "recomp.h"
#include <array>
#include <bit>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

extern "C" {
void baseline_camera(uint8_t*, recomp_context*);
void func_801E11B4(uint8_t*, recomp_context*);
void SysUtils_MtxToMtxF(uint8_t*, recomp_context*);
}
namespace {
using Ram = std::vector<uint8_t>;
constexpr uint32_t Pool = 0x80300000, Camera = 0x80227C80, Stack = 0x807FF000;
unsigned checks = 0, scenarios = 0;
uint64_t nativeAccesses = 0;
void require(bool ok, const char* why) {
    ++checks;
    if (!ok) { std::cerr << "FAIL: " << why << '\n'; std::exit(1); }
}
void put(Ram& ram, uint32_t a, uint32_t v) { std::memcpy(ram.data() + (a & 0x7FFFFF), &v, 4); }
uint32_t get(const Ram& ram, uint32_t a) { uint32_t v; std::memcpy(&v,ram.data()+(a&0x7FFFFF),4);return v; }
uint32_t bits(float v) { return std::bit_cast<uint32_t>(v); }
void real(Ram& ram,uint32_t a,float v) { put(ram,a,bits(v)); }
Ram initial(unsigned players=2) {
    Ram r(0x800000);
    put(r,0x800DAB28,players);put(r,0x800DAB24,41);put(r,0x800D8170,1);
    put(r,0x801CE638,1);put(r,0x801518B8,Pool);
    put(r,0x80223930,0);put(r,0x80223934,1);
    for(unsigned i=0;i<4096;++i) real(r,0x80154350+i*4,float(std::sin(i*6.283185307179586/4096)));
    for(unsigned i=0;i<2;++i) {
        const uint32_t c=Camera+i*0x10C;
        put(r,c,4);put(r,c+0xE8,i);put(r,c+0xEC,1);
        real(r,c+0x4C,float(i*75));real(r,c+0x50,20);real(r,c+0x54,10);
        real(r,c+0x7C,float(i*75));real(r,c+0x80,20);real(r,c+0x84,-100);
        real(r,c+0x70,0);real(r,c+0x74,1);real(r,c+0x78,0);
        real(r,c+0x88,i?55:60);real(r,c+0x9C,10);real(r,c+0xA0,4096);
    }
    return r;
}
void build(Ram& ram, unsigned slot, bool baseline=false, uint32_t pool=Pool) {
    recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;
    ctx.r4=S32(pool);ctx.r5=S32(Camera+slot*0x10C);ctx.r29=S32(Stack);
    ctx.r16=0xBEEF;ctx.r31=0xCAFE;
    (baseline ? baseline_camera : func_801E11B4)(ram.data(), &ctx);
    require(uint32_t(ctx.r29)==Stack && ctx.r16==0xBEEF && ctx.r31==0xCAFE,"native stack and callee-saved registers preserved");
}
std::array<float,16> projection(Ram& ram,unsigned slot,uint32_t pool=Pool) {
    recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;
    ctx.r4=S32(pool+0xE008+slot*64);ctx.r5=S32(0x80400000);
    SysUtils_MtxToMtxF(ram.data(),&ctx);
    std::array<float,16> m{};
    for(unsigned i=0;i<16;++i)m[i]=std::bit_cast<float>(get(ram,0x80400000+i*4));
    return m;
}
void poolTransitions() {
    // Use the actual two native graphics pool bases, as initialization builds
    // both before normal per-frame updates select the live pool at 801518B8.
    const std::array<uint32_t,2> pools{0x8011F8E8,0x801388D0};
    auto r=initial();
    wr64::camera_fov::set_extra_degrees(10);
    for(unsigned frame=0;frame<8;++frame) {
        const uint32_t live=pools[frame%2],inactive=pools[(frame+1)%2];
        put(r,0x801518B8,live);
        const auto otherBefore=std::array<uint32_t,2>{get(r,Camera+0x88),get(r,Camera+0x10C+0x88)};
        for(unsigned slot=0;slot<2;++slot) {
            auto original=r,expected=r;
            build(original,slot,true,live);
            real(expected,Camera+slot*0x10C+0x88,slot?65:70);
            build(expected,slot,true,live);
            build(r,slot,false,live);
            require(projection(r,slot,live)==projection(expected,slot,live),"alternating live pool gets current widened per-camera lens");
            build(r,slot,false,inactive);build(original,slot,true,inactive);
            require(projection(r,slot,inactive)==projection(original,slot,inactive),"inactive initialization pool retains original lens");
        }
        require(get(r,Camera+0x88)==otherBefore[0] && get(r,Camera+0x10C+0x88)==otherBefore[1],"pool transitions never mutate either camera lens");
    }
    put(r,0x801518B8,Pool);build(r,0);build(r,1);
    const auto first=projection(r,0),second=projection(r,1);
    real(r,Camera+0x10C+0x88,65);build(r,1);
    require(projection(r,0)==first && projection(r,1)!=second,"changing P2 preset leaves P1 matrix unchanged");
    wr64::camera_fov::set_extra_degrees(0);
    for(auto pool:pools)for(unsigned slot=0;slot<2;++slot) {
        put(r,0x801518B8,pool);auto expected=r;build(expected,slot,true,pool);build(r,slot,false,pool);
        require(projection(r,slot,pool)==projection(expected,slot,pool),"Original restored in both alternating pools without stale cached lens");
    }
}
void nativeScenario(unsigned players,unsigned slot,float original,float extra,float nearPlane,float farPlane,float xshift,float yshift,unsigned course=1,bool loaded=false) {
    ++scenarios;
    auto start=initial(players);
    put(start,0x800D8170,course);
    put(start,0x80223930,slot);put(start,0x80223934,slot^1);
    const uint32_t c=Camera+slot*0x10C;
    real(start,c+0x88,original);real(start,c+0x9C,nearPlane);real(start,c+0xA0,farPlane);
    real(start,c+0x94,xshift);real(start,c+0x98,yshift);
    auto vanilla=start,actual=start,expected=start;
    RT64::wr64RTPublishTwoPlayerAssets(loaded?actual.data():nullptr,course);
    wr64::camera_fov::set_extra_degrees(0);build(vanilla,slot,true);build(actual,slot);
    require(actual==vanilla,"Original is byte-identical to unhooked native camera builder across all RAM");
    wr64::camera_fov::set_extra_degrees(extra);
    actual=start;
    RT64::wr64RTPublishTwoPlayerAssets(loaded?actual.data():nullptr,course);
    real(expected,c+0x88,original+extra);build(expected,slot,true);real(expected,c+0x88,original);
    build(actual,slot);
    require(actual==expected,"enabled output exactly matches native builder given independently widened lens");
    require(get(actual,c+0x88)==bits(original),"authored native lens is never mutated");
    require(std::memcmp(actual.data()+((Pool+0xE088+slot*64)&0x7FFFFF),
        vanilla.data()+((Pool+0xE088+slot*64)&0x7FFFFF),64)==0,"view matrix preserves camera position and orientation");
    auto originalMatrix=projection(vanilla,slot),widerMatrix=projection(actual,slot);
    require(widerMatrix[0]<originalMatrix[0] && widerMatrix[5]<originalMatrix[5],"wider lens reduces both native focal terms");
    require(widerMatrix[10]==originalMatrix[10] && widerMatrix[11]==originalMatrix[11] &&
        widerMatrix[14]==originalMatrix[14] && widerMatrix[15]==originalMatrix[15],"near and far clipping depth terms unchanged");
    const float radians=(original+extra)*3.14159265358979323846f/180;
    require(std::fabs(widerMatrix[5]-1/std::tan(radians*.5f))<.012f,"native quantized sine table uses full vertical degrees");
    const auto firstMatrix=widerMatrix;
    for(unsigned i=0;i<12;++i)build(actual,slot);
    require(projection(actual,slot)==firstMatrix && get(actual,c+0x88)==bits(original),"repeated frames do not accumulate extra FOV");
    // Restoring Original on the same RAM rebuilds the native lens immediately.
    wr64::camera_fov::set_extra_degrees(0);build(actual,slot);
    require(projection(actual,slot)==originalMatrix,"live return to Original restores exact original projection");
    RT64::wr64RTPublishTwoPlayerAssets(nullptr,0);
}
void exclusions() {
    auto r=initial();const auto original=bits(60.0f);
    wr64::camera_fov::set_extra_degrees(10);
    for(bool loaded:{false,true}) {
    RT64::wr64RTPublishTwoPlayerAssets(loaded?r.data():nullptr,0);
    for(unsigned players=0;players<4;++players)for(unsigned course=0;course<11;++course)
        for(unsigned phase=0;phase<12;++phase)for(unsigned mode=0;mode<104;++mode) {
        put(r,0x800DAB28,players);put(r,0x800D8170,course);put(r,0x801CE638,phase);put(r,0x800DAB24,mode);
        const bool eligible=(players==1||players==2)&&course<=8&&(players!=2||course!=0||loaded)&&phase==1&&mode>=40&&mode<=44;
        require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==(eligible?bits(70):original),"game state and menu/replay exclusion");
    }
    }
    RT64::wr64RTPublishTwoPlayerAssets(nullptr,0);
    r=initial();put(r,0x800D8170,0);
    const auto otherRam=r;
    RT64::wr64RTPublishTwoPlayerAssets(otherRam.data(),0);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==original,"another RAM owner's Dolphin assets do not admit FOV");
    RT64::wr64RTPublishTwoPlayerAssets(r.data(),1);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==original,"another course's assets do not admit Dolphin FOV");
    RT64::wr64RTPublishTwoPlayerAssets(r.data(),0);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==bits(70),"authenticated loaded Dolphin assets admit FOV");
    RT64::wr64RTPublishTwoPlayerAssets(nullptr,0);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==original,"course unload immediately restores Dolphin admission fallback");
    r=initial();const auto saved=r;
    for(unsigned mode=0;mode<10;++mode) {
        put(r,Camera,mode);
        require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==(mode==4?bits(70):original),"only initialized follow camera type4 admitted");
    }
    r=saved;
    for(auto address:std::array<uint32_t,7>{0,Camera-4,Camera+4,Camera+0x218,0x80227C81,0x80800000,0xFFFFFFFF})
        require(wr64_camera_fov_lens(r.data(),address,Pool,original)==original,"unknown camera pointer rejected");
    for(auto address:std::array<uint32_t,6>{0,Pool+4,Pool+8,0x8011F8E8,0x80800000,0xFFFFFFFF})
        require(wr64_camera_fov_lens(r.data(),Camera,address,original)==original,"inactive or malformed graphics pool rejected");
    for(auto index:std::array<uint32_t,4>{1,2,4,0xFFFFFFFF}) {
        put(r,Camera+0xE8,index);
        require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==original,"camera matrix slot mismatch rejected");
    }
    r=saved;put(r,0x80223934,0);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==original,"duplicate player mapping rejected");
    r=saved;put(r,0x80223930,2);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==original,"invalid active player mapping rejected");
    r=saved;put(r,0x800DAB28,1);put(r,0x80223930,1);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,original)==original,"inactive one-player camera rejected");
    r=saved;
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,bits(61))==bits(61),"stale loaded lens argument rejected");
    for(float invalid:std::array<float,8>{-1,0,.5f,121,180,std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()}) {
        real(r,Camera+0x88,invalid);
        require(wr64_camera_fov_lens(r.data(),Camera,Pool,bits(invalid))==bits(invalid),"invalid native lens remains untouched");
    }
    r=saved;real(r,Camera+0x88,115);
    require(wr64_camera_fov_lens(r.data(),Camera,Pool,bits(115))==bits(120),"defensive final lens bound");
    wr64::camera_fov::set_extra_degrees(0);
    require(wr64_camera_fov_lens(nullptr,0,0,0x7FC12345)==0x7FC12345,"Original preserves exact exceptional bits without RAM");
    wr64::camera_fov::set_extra_degrees(10);
    require(wr64_camera_fov_lens(nullptr,Camera,Pool,original)==original,"null RAM leaves argument untouched");
    wr64::camera_fov::set_extra_degrees(-1);require(wr64::camera_fov::extra_degrees()==0,"negative setting bound");
    wr64::camera_fov::set_extra_degrees(99);require(wr64::camera_fov::extra_degrees()==10,"upper setting bound");
    r=saved;
    wr64::camera_fov::set_extra_degrees(20);
    require(wr64::camera_fov::extra_degrees()==10 && wr64_camera_fov_lens(r.data(),Camera,Pool,original)==bits(70),
        "legacy experimental maximum clamps to ten extra degrees in the native lens");
    wr64::camera_fov::set_extra_degrees(std::numeric_limits<double>::infinity());require(wr64::camera_fov::extra_degrees()==0,"nonfinite setting bound");
}
}
extern "C" void* wr64_test_address(uint8_t* rdram,uint64_t address,unsigned bytes,const char* file,int line) {
    ++nativeAccesses;const uint32_t a=uint32_t(address);
    if(a<0x80000000 || a>0x80800000-bytes || (a&(bytes-1))) {
        std::cerr<<"Invalid native memory "<<std::hex<<a<<std::dec<<" at "<<file<<':'<<line<<'\n';std::exit(1);
    }
    return rdram+(a&0x7FFFFF);
}
extern "C" void _nsqrtf(uint8_t*,recomp_context* ctx) {ctx->f0.fl=std::sqrt(ctx->f12.fl);}
int main() {
    exclusions();
    poolTransitions();
    for(unsigned players:{1u,2u})for(unsigned slot:{0u,1u})for(float original:{45.0f,55.0f,60.0f,75.0f})
        for(float extra:{5.0f,10.0f}) {
            nativeScenario(players,slot,original,extra,10,4096,0,0);
            nativeScenario(players,slot,original,extra,32,16384,2,-3);
        }
    for(unsigned slot:{0u,1u})for(float original:{45.0f,55.0f,60.0f,75.0f})for(float extra:{5.0f,10.0f}) {
        nativeScenario(2,slot,original,extra,10,4096,0,0,0,true);
        nativeScenario(2,slot,original,extra,32,16384,2,-3,0,true);
    }
    std::cout<<"PASS "<<checks<<" assertions, "<<scenarios<<" complete native camera scenarios, "<<nativeAccesses<<" checked native accesses\n";
}
