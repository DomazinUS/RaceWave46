#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif
#include "recomp.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include "common/rt64_wr64_rt_shadow.h"
#include "common/rt64_wr64_rt_view.h"
#include "common/rt64_wr64_raster_sky_scope.h"
#include "common/rt64_wr64_raster_shadow_scope.h"
#include <bit>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

extern "C" void func_801ECB98(uint8_t*, recomp_context*);
extern "C" void func_i15_802C6CAC(uint8_t*, recomp_context*);
extern "C" void func_8008E4B0(uint8_t*, recomp_context*);
extern "C" void ending_native_viewport_prefix(uint8_t*, recomp_context*);
// Only unrelated audio, transition and matrix side effects are stubbed. Native
// state writes, preset copies and viewport/scissor emission execute verbatim.
#define STUB(name) extern "C" void name(uint8_t*, recomp_context*) {}
STUB(func_8009684C)
STUB(func_80096960)
STUB(func_800C21F4)
STUB(func_800C1F60)
STUB(func_801E6A4C)
STUB(FadeTransition_SetProps)
STUB(func_8004C998)
STUB(func_8004C1D0)
STUB(wr64_sunny_sky_cloud_camera)
STUB(wr64_watercraft_preview_viewport)
extern "C" uint32_t wr64_watercraft_preview_scissor(uint32_t value) { return value; }
extern "C" void wr64_two_player_preview_viewport(uint8_t*, recomp_context*, uint32_t) {}
extern "C" void wr64_two_player_preview_scissor(uint8_t*, recomp_context*, uint32_t) {}
static uint32_t borders = 0;
extern "C" uint32_t wr64_experimental_viewport_borders() { return borders; }
static unsigned checks = 0;
static void require(bool okay, const char* message) {
    ++checks;
    if (!okay) { std::cerr << "FAIL: " << message << '\n'; std::exit(1); }
}
struct Fixture {
    std::vector<uint8_t> ram = std::vector<uint8_t>(0x800000);
    void word(uint32_t address, uint32_t value) {
        std::memcpy(ram.data() + (address & 0x7fffff), &value, 4);
    }
    uint32_t word(uint32_t address) const {
        uint32_t value; std::memcpy(&value, ram.data() + (address & 0x7fffff), 4); return value;
    }
    void real(uint32_t address, float value) { word(address, std::bit_cast<uint32_t>(value)); }
    float real(uint32_t address) const { return std::bit_cast<float>(word(address)); }
    void call(void(*function)(uint8_t*, recomp_context*), uint32_t argument=0) {
        recomp_context ctx{}; ctx.r29 = gpr(int64_t(int32_t(0x807f0000))); ctx.r4 = gpr(int64_t(int32_t(argument)));
        function(ram.data(), &ctx);
    }
};

int main() {
    using namespace RT64;
    Fixture fixture;
    fixture.call(func_801ECB98);
    const uint32_t course=fixture.word(0x800d8170), players=fixture.word(0x800dab28),
        phase=fixture.word(0x801ce638), mode=fixture.word(0x800dab24);
    require(course==7 && players==1 && phase==21 && mode==102,
        "actual native award entry identifies Southern Island ending context");
    require(fixture.word(0x800d8174)==5 && fixture.word(0x80227c80)==8,
        "native ending keeps authored difficulty and camera, without a test shortcut");
    require(wr64RTEndingScope(course,players,phase,mode), "native entry admitted");
    fixture.call(func_i15_802C6CAC);
    require(fixture.word(0x800dab24)==103 && wr64RTEndingScope(course,players,phase,103),
        "native ending exit/fade retains coverage");

    Wr64RTSettings all{}; all.reflections=true; all.skyReflections=true; all.shadows=true; all.rasterSky=false;
    for (uint32_t endingMode:{102U,103U}) {
        const auto scopes=wr64WaterEffectScopes(all,true,course,players,phase,endingMode,0,false);
        require(scopes.rayScene && scopes.objects && scopes.raySky && !scopes.menu && !scopes.twoPlayer,
            "all selected RT effects reach actual ending through shared settings policy");
        require(wr64RTShadowScope(all.shadows,scopes.rayScene,course,players,phase,endingMode),
            "ending ray shadows enabled");
        require(wr64RasterShadowScope(true,course,players,phase,endingMode,false),
            "ending raster shadows share world eligibility");
        require(!wr64RTReflectionScope(false,course,players,phase,endingMode) &&
            !wr64RTShadowScope(false,true,course,players,phase,endingMode),
            "Original options remain disabled in ending");
        const auto failed=wr64WaterEffectScopes(all,false,course,players,phase,endingMode,0,false);
        require(!failed.rayScene && !failed.objects && !failed.raySky, "startup failure still falls back");
    }
    // Exhaustive neighborhood catches stale course IDs in other menus/phases.
    for (uint32_t c=0;c<11;++c) for(uint32_t p=0;p<4;++p)
        for(uint32_t ph=0;ph<24;++ph) for(uint32_t m=0;m<106;++m) {
            const bool ending=c==course && p==players && ph==phase && (m==102 || m==103);
            require(wr64RTEndingScope(c,p,ph,m)==ending, "ending domain is exact");
            const bool existing=p==1 && c<=8 && (ph==1 || (ph==8 && (m==30 || m==31)) ||
                (c==0 && ph==0 && m>=2 && m<=4));
            require(wr64RTReflectionScope(true,c,p,ph,m)==(existing||ending),
                "existing scenes unchanged and only native ending added");
        }
    // Distinct synthetic presets detect selecting course7 instead of the native
    // dedicated ending preset. Native init_world itself supplies the oracle.
    for(uint32_t preset:{7U,10U}) for(uint32_t i=0;i<3;++i) {
        const uint32_t address=0x800d9964+preset*0x110;
        fixture.word(address+i*4, 180+preset+i);
        fixture.word(address+0xc+i*4, 30+preset+i);
        fixture.real(address+0xac+i*4, i==1 ? 85.0f : float(preset*3+i));
    }
    fixture.call(func_8008E4B0);
    const auto light=wr64RTShadowReadLight(fixture.ram.data(),fixture.ram.size(),course,players,true);
    require(light.valid,"native ending light valid");
    float length=0;
    for(uint32_t i=0;i<3;++i) { const auto v=fixture.real(0x801cb058+0xac+i*4);length+=v*v; }
    length=std::sqrt(length);
    for(uint32_t i=0;i<3;++i) {
        require(fixture.word(0x801cb058+i*4)==fixture.word(0x800da404+i*4),
            "native init_world actually selects dedicated award colors");
        require(light.diffuse[i]==float(fixture.word(0x801cb058+i*4))/255 &&
            light.ambient[i]==float(fixture.word(0x801cb058+0xc+i*4))/255 &&
            std::abs(light.toLight[i]-fixture.real(0x801cb058+0xac+i*4)/length)<1e-6f,
            "renderer normalized light agrees with native initialization");
    }
    fixture.word(0x801ce638,1); fixture.call(func_8008E4B0);
    const auto raceLight=wr64RTShadowReadLight(fixture.ram.data(),fixture.ram.size(),course,players);
    require(raceLight.valid && raceLight.diffuse!=light.diffuse, "ordinary Southern Island preset preserved");
    for(uint32_t i=0;i<3;++i) require(raceLight.diffuse[i]==float(fixture.word(0x801cb058+i*4))/255,
        "native race light still selected outside ending");
    require(!wr64RTShadowReadLight(fixture.ram.data(),fixture.ram.size(),1,1,true).valid,
        "ending light cannot leak to other courses");
    // Native ROM preset10: white diffuse, dark ambient, upper-positive-Z light.
    for(uint32_t i=0;i<3;++i) {
        fixture.word(0x800da404+i*4,255);fixture.word(0x800da410+i*4,64);
        fixture.real(0x800da4b0+i*4,i==0?0.0f:85.0f);
    }
    const auto authored=wr64RTShadowReadLight(fixture.ram.data(),fixture.ram.size(),7,1,true);
    require(authored.valid && authored.toLight[0]==0 && authored.toLight[1]>0.7f && authored.toLight[2]>0.7f,
        "actual authored award light passes validity checks");

    fixture.word(0x801ce638,21);
    for(borders=0;borders<=1;++borders) {
        constexpr uint32_t commands=0x80400000;
        fixture.call(ending_native_viewport_prefix,commands);
        WR64RTViewDomain domain; domain.perspective=true;
        domain.scale[0]=domain.translate[0]=212; domain.scale[1]=domain.translate[1]=120;
        bool viewportFound=false,scissorFound=false;
        for(uint32_t a=commands;a<commands+0x200;a+=8) {
            const auto w0=fixture.word(a),w1=fixture.word(a+4);
            if(w0==0x03800010) viewportFound=w1==0x800da8c0;
            if((w0>>24)==0xed) {
                scissorFound=true;
                domain.scissor[0]=(w0>>12)&0xfff;domain.scissor[1]=w0&0xfff;
                domain.scissor[2]=(w1>>12)&0xfff;domain.scissor[3]=w1&0xfff;
            }
        }
        require(viewportFound&&scissorFound,"native ending uses full A8C0 world viewport and emits scissor");
        require(wr64RTEndingWorldView(true,domain),"native bordered and borderless world both select waterless shadows");
        require(!wr64RTEndingWorldView(false,domain),"waterless scene fallback is ending-only");
        auto changed=domain;changed.scale[1]=-120;
        require(wr64RTEndingWorldView(true,changed),"renderer Y-axis convention supported");
        changed=domain;changed.translate[1]=60;require(!wr64RTEndingWorldView(true,changed),"split view excluded");
        changed=domain;changed.perspective=false;require(!wr64RTEndingWorldView(true,changed),"banner orthographic view excluded");
        changed=domain;changed.menuModelPreview=true;require(!wr64RTEndingWorldView(true,changed),"rider-preview view excluded");
        changed=domain;changed.scissor[0]++;require(!wr64RTEndingWorldView(true,changed),"other inset scissor excluded");
        changed=domain;changed.scale[2]=std::numeric_limits<float>::quiet_NaN();
        require(!wr64RTEndingWorldView(true,changed),"invalid matrix viewport excluded");
    }
    std::cout<<"PASS "<<checks<<" ending native state/light/viewport checks\n";
}
