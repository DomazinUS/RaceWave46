#include "recomp.h"
#include "wr64_split_screen.hpp"
#include "common/rt64_wr64_split_marker.h"
#include "common/rt64_wr64_vertical_split.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
unsigned assertions=0, cases=0;
void require(bool condition,const char* message) {
    ++assertions;
    if (!condition) throw std::runtime_error(message);
}
void close(float actual,float expected,const char* message) {
    require(std::isfinite(actual) && std::abs(actual-expected)<0.002f,message);
}
[[noreturn]] void unexpected_font_branch() noexcept {
    std::cerr<<"Lap fixture entered an unrelated font animation or rectangle path.\n";
    std::abort();
}
constexpr uint32_t Pool=0x80300000, Output=Pool+0x100, Stack=0x80600000;
constexpr uint32_t Dynamic=0x80400000, CursorPointer=0x80100000;
constexpr uint32_t Boat0=0x801C2938+0x378*2, Boat1=0x801C2938+0x378*3;
uint32_t word(const uint8_t* rdram,uint32_t address) {
    uint32_t result;std::memcpy(&result,rdram+(address&0x7FFFFF),4);return result;
}
void word(uint8_t* rdram,uint32_t address,uint32_t value) { MEM_W(0,S32(address))=value; }
void string(uint8_t* rdram,uint32_t address,const std::string& value) {
    for (size_t i=0;i<=value.size();++i) MEM_B(0,S32(address+uint32_t(i)))=i<value.size()?value[i]:0;
}
struct Glyph {
    uint32_t cursor,font,code;
    int x,y;
    uint32_t scale;
    std::array<int16_t,12> positions;
    bool same_image(const Glyph& other) const {
        return font==other.font && code==other.code && x==other.x && y==other.y &&
            scale==other.scale && positions==other.positions;
    }
};
std::vector<Glyph> glyphs;
struct Run {
    std::vector<uint8_t> memory;
    std::vector<Glyph> output;
    std::vector<std::array<uint32_t,2>> packets;
};
std::vector<uint8_t> fixture(int players,int lap0,int lap1,int activeMask,bool trigger) {
    std::vector<uint8_t> memory(0x800000);
    auto* rdram=memory.data();
    word(rdram,0x800DAB28,players);word(rdram,0x800DAB24,40);
    word(rdram,0x801CE638,1);word(rdram,0x801518B8,Pool);
    MEM_H(0,S32(0x801CE624))=-1;
    word(rdram,0x801CE5F8,Dynamic);
    word(rdram,0x800D48DC,2);word(rdram,0x800D48E0,3);
    word(rdram,0x801CE728,3);
    word(rdram,Boat0,lap0);word(rdram,Boat1,lap1);
    word(rdram,Boat0+0x308,trigger && (activeMask&1));
    word(rdram,Boat1+0x308,trigger && (activeMask&2));
    word(rdram,0x80228B60,!trigger && (activeMask&1)?1:0);
    word(rdram,0x80228B64,!trigger && (activeMask&2)?1:0);
    const float singleScale=1.3f;
    std::memcpy(rdram+(0x80227A54&0x7FFFFF),&singleScale,4);
    string(rdram,0x802279F8,"LAP");string(rdram,0x802279FC,"%d");
    string(rdram,0x80227A00,"FINAL");string(rdram,0x80227A08,"LAP");
    // Constructed proportional advances; no texture/font assets are copied.
    for (int i=0;i<40;++i) MEM_B(0,S32(0x80226D70+i))=16;
    MEM_B(0,S32(0x80226D70+10))=17; // A
    MEM_B(0,S32(0x80226D70+18))=8;  // I
    MEM_B(0,S32(0x80226D70+21))=15; // L
    MEM_B(0,S32(0x80226D70+23))=18; // N
    for (uint32_t address=0x80227744;address<0x80227764;++address)
        MEM_B(0,S32(address))=uint8_t(address*13);
    return memory;
}
}
extern "C" {
void func_801FAEB8(uint8_t*,recomp_context*);
void baseline_func_801FAEB8(uint8_t*,recomp_context*);
void native_emit_font(uint8_t*,recomp_context*);
void func_801E80B0(uint8_t* rdram,recomp_context* ctx) {
    Glyph glyph{uint32_t(ctx->r4),uint32_t(ctx->r5),uint32_t(ctx->r6),
        int32_t(ctx->r7),MEM_W(0x10,ctx->r29),uint32_t(MEM_W(0x48,ctx->r29)),{}};
    require(MEM_W(0x14,ctx->r29)==2,"Lap announcement stopped using the shaded vertex-font path");
    const uint32_t first=word(rdram,0x80228A40);
    native_emit_font(rdram,ctx);
    require(word(rdram,0x80228A40)==first+4,"Native glyph producer did not emit four vertices");
    for (unsigned i=0;i<4;++i) for (unsigned xyz=0;xyz<3;++xyz)
        glyph.positions[i*3+xyz]=MEM_H(0,S32(Dynamic+0x40+16*(first+i)+xyz*2));
    glyphs.push_back(glyph);
}
void func_800CA210(uint8_t* rdram,recomp_context* ctx) {
    string(rdram,uint32_t(ctx->r4),std::to_string(int32_t(ctx->r6)));
    ctx->r2=1;
}
int32_t wr64_menu_half_extension() {return 0;}
void wr64_menu_promote_waku_rect(uint8_t*,uint32_t,int32_t,int32_t) {
    unexpected_font_branch();
}
void func_801E9D6C(uint8_t*,recomp_context*) {unexpected_font_branch();}
void func_801EA0B0(uint8_t*,recomp_context*) {unexpected_font_branch();}
void func_801EA3EC(uint8_t*,recomp_context*) {unexpected_font_branch();}
void func_801EA730(uint8_t*,recomp_context*) {unexpected_font_branch();}
void func_801EAA6C(uint8_t*,recomp_context*) {unexpected_font_branch();}
void func_801EADB0(uint8_t*,recomp_context*) {unexpected_font_branch();}
void do_break(uint32_t) {std::abort();}
void switch_error(const char*,uint32_t,uint32_t) {std::abort();}
}
namespace wr64::input {void set_multiplayer_enabled(bool) {}}
namespace {
Run run(std::vector<uint8_t> memory,bool enabled,bool legacy=false) {
    auto* rdram=memory.data();
    wr64::split_screen::set_vertical(enabled);
    const auto begin=wr64_split_screen_frame(rdram,Output);
    word(rdram,CursorPointer,begin);
    recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;
    ctx.r29=S32(Stack);ctx.r4=S32(CursorPointer);
    glyphs.clear();
    (legacy?baseline_func_801FAEB8:func_801FAEB8)(rdram,&ctx);
    require(uint32_t(ctx.r29)==Stack,"Lap producer failed to restore its native stack");
    Run result{std::move(memory),glyphs,{}};
    rdram=result.memory.data();
    for (uint32_t address=Output;address<word(rdram,CursorPointer);address+=8)
        result.packets.push_back({word(rdram,address),word(rdram,address+4)});
    return result;
}
void scope_image(const Run& result,int players,bool enabled) {
    RT64::Wr64LapScope scope;
    bool vertical=false;uint8_t pause=0;
    uint32_t calls=10;
    std::vector<std::pair<uint32_t,size_t>> renderedGlyphs;
    for (size_t i=0;i<result.packets.size();++i) {
        const auto& p=result.packets[i];
        if (RT64::wr64DecodeSplitMarker(p[0],p[1],vertical,pause)) continue;
        if (RT64::wr64DecodeLapMarker(p[0],p[1],vertical,calls,scope)) continue;
        if ((p[0]>>24)==0xBF) {
            const uint32_t address=Output+uint32_t(i)*8;
            auto glyph=std::upper_bound(result.output.begin(),result.output.end(),address,
                [](uint32_t a,const Glyph& g){return a<g.cursor;});
            require(glyph!=result.output.begin(),"Native triangle has no captured glyph");
            --glyph;
            renderedGlyphs.push_back({calls,size_t(glyph-result.output.begin())});
            ++calls;
        }
    }
    require(scope.openOwner==0,"Native lap output leaves its ownership scope open");
    require(renderedGlyphs.size()==result.output.size()*2,"Native shaded glyph did not produce its expected triangle pair");
    for (const auto& [call,index]:renderedGlyphs) {
        const auto& glyph=result.output[index];
        const int expected=enabled && players==2?(glyph.y==40?1:2):0;
        require(RT64::wr64LapOwner(scope,call)==expected,
            "A native lap glyph triangle was not attributed to its actual player");
    }
    require(RT64::wr64LapOwner(scope,9)==0 && RT64::wr64LapOwner(scope,calls)==0,
        "Lap ownership escaped into preceding HUD or following shared UI");
}
void layout_image(const Run& result) {
    using namespace RT64;
    for (const std::array<float,2> size:{std::array<float,2>{960,720},{1280,720},
            {1260,540},{1920,540},{1921,1081}}) {
        const auto layout=wr64VerticalLayout(true,size[0],size[1],size[1]/240);
        for (const auto& glyph:result.output) {
            const int owner=glyph.y==40?1:2;
            const auto mapping=wr64VerticalAnnouncement(layout,owner,owner==1?-4.0f:6.0f);
            const auto pane=wr64VerticalPane(layout,owner);
            const float n=layout.nativeScale;
            close(mapping.x(layout.width*0.5f),(pane.left+pane.right)*0.5f,
                "Lap announcement still anchors to the full screen instead of its owner's pane");
            close(mapping.y(float(glyph.y)*n),layout.height*0.5f-24*n*layout.hudScale,
                "The two native lap rows do not map to the same destination height");
            const float width=(glyph.positions[3]-glyph.positions[0])*n;
            const float height=(glyph.positions[7]-glyph.positions[1])*n;
            close(mapping.x(width)-mapping.x(0),width*layout.hudScale,"Lap glyph horizontal size changed");
            close(mapping.y(height)-mapping.y(0),height*layout.hudScale,"Lap glyph vertical size changed");
            const float sourceLeft=layout.width*0.5f+(glyph.positions[0]-212)*n;
            const float sourceRight=layout.width*0.5f+(glyph.positions[3]-212)*n;
            require(mapping.x(sourceLeft)>=pane.left && mapping.x(sourceRight)<=pane.right,
                "Lap announcement overlaps the other player's pane");
        }
    }
}
void native_cases() {
    for (int players:{1,2}) for (int lap0:{1,2,3}) for (int lap1:{2,3})
    for (int mask:{0,1,2,3}) for (bool trigger:{false,true}) {
        const auto source=fixture(players,lap0,lap1,mask,trigger);
        const auto horizontal=run(source,false);
        const auto vertical=run(source,true);
        const auto original=run(source,false,true);
        require(horizontal.packets==original.packets,
            "Disabled lap hooks changed the original display-list bytes");
        scope_image(horizontal,players,false);scope_image(vertical,players,true);
        require(horizontal.output.size()==vertical.output.size(),"Vertical mode changed the number of native lap glyphs");
        size_t expectedGlyphs=0;
        for (int player=0;player<players;++player) if (mask&(1<<player))
            expectedGlyphs+=(player==0?lap0:lap1)<3?4:8;
        require(vertical.output.size()==expectedGlyphs,"Native lap trigger selected the wrong player's message");
        for (size_t i=0;i<horizontal.output.size();++i) {
            const auto& glyph=vertical.output[i];
            require(glyph.same_image(horizontal.output[i]),"Vertical mode changed native glyph content, size or coordinates");
            require(glyph.font==0,"Lap message switched its native font");
            require(glyph.y==(players==1?70:glyph.y<100?40:150),"Lap glyph lost the native player row");
            require(glyph.positions[0]==glyph.x && glyph.positions[1]==glyph.y,
                "Native emitted glyph origin differs from the announcement coordinates");
            require(glyph.positions[3]>glyph.positions[0] && glyph.positions[7]>glyph.positions[1],
                "Native glyph fixture produced an empty or reversed rectangle");
        }
        for (uint32_t address:{Boat0+0x308,Boat1+0x308,0x80228B60U,0x80228B64U,
                              0x80228B68U,0x80228B6CU,0x80228B70U,0x80228B74U})
            require(word(horizontal.memory.data(),address)==word(vertical.memory.data(),address),
                "Presentation change altered native lap timing or trigger state");
        if (players==1) require(horizontal.packets==vertical.packets,
            "One-player lap display-list bytes changed when Vertical was selected");
        else {
            std::vector<std::array<uint32_t,2>> normalized;
            for (const auto& packet:vertical.packets)
                if (packet[0]!=RT64::Wr64SplitMarker && packet[0]!=RT64::Wr64SplitLapMarker)
                    normalized.push_back(packet);
            require(normalized==horizontal.packets,"Vertical mode altered a native lap display-list command");
            layout_image(vertical);
        }
        for (int player=0;player<players;++player) {
            const uint32_t timer=0x80228B60+4*player;
            require(word(vertical.memory.data(),timer)==((mask&(1<<player))&&trigger?39:0),
                "Native announcement timer no longer starts at 40 and decrements once per update");
        }
        ++cases;
    }
}
void malformed_scopes() {
    using namespace RT64;
    const auto decode=[](Wr64LapScope& s,uint32_t owner,uint32_t call,bool vertical=true) {
        return wr64DecodeLapMarker(Wr64SplitLapMarker,Wr64SplitVersion|owner,vertical,call,s);
    };
    Wr64LapScope scope;
    require(decode(scope,1,10,false) && scope.openOwner==0 && wr64LapOwner(scope,10)==0,
        "Horizontal workload acquired vertical lap ownership");
    require(decode(scope,0,10) && scope.openOwner==0,"An unmatched end opened a lap range");
    require(decode(scope,1,10) && wr64LapOwner(scope,11)==0,
        "An unfinished lap range was treated as renderable");
    require(decode(scope,2,12) && decode(scope,0,15) && wr64LapOwner(scope,11)==0 &&
        wr64LapOwner(scope,12)==2 && wr64LapOwner(scope,14)==2 && wr64LapOwner(scope,15)==0,
        "Nested/abandoned lap metadata leaked into unrelated calls");
    for (const auto packet:{std::array<uint32_t,2>{Wr64SplitPauseMarker,Wr64SplitVersion|1},
                           {Wr64SplitLapMarker,Wr64SplitVersion|3},
                           {Wr64SplitLapMarker,0x02000001},{Wr64SplitLapMarker,0x01000005}}) {
        auto before=scope;
        require(!wr64DecodeLapMarker(packet[0],packet[1],true,20,scope) &&
            scope.openOwner==before.openOwner && scope.first[0]==before.first[0] &&
            scope.last[0]==before.last[0] && scope.first[1]==before.first[1] && scope.last[1]==before.last[1],
            "Malformed or unrelated metadata changed lap ownership");
    }
    scope={};
    require(wr64LapOwner(scope,12)==0,"Reset workload inherited a preceding lap owner");
    for (const int owner:{-1,0,3}) {
        auto memory=fixture(2,2,2,0,false);auto* rdram=memory.data();
        wr64::split_screen::set_vertical(true);
        const auto cursor=wr64_split_screen_frame(rdram,Output);
        const auto before=memory;
        require(wr64_split_screen_lap(rdram,cursor,owner)==cursor && memory==before,
            "Unmatched or invalid native lap owner changed the display list");
    }
    auto memory=fixture(2,2,2,0,false);auto* rdram=memory.data();
    wr64::split_screen::set_vertical(true);
    const auto start=wr64_split_screen_frame(rdram,Output);
    const auto open=wr64_split_screen_lap(rdram,start,2);
    require(open==start+8,"Valid native lap scope did not open");
    wr64::split_screen::set_vertical(false);
    require(wr64_split_screen_lap(rdram,open,0)==open+8,
        "An already queued lap scope could not close after the setting changed");
    wr64::split_screen::set_vertical(true);
    wr64_split_screen_frame(rdram,Output);
    wr64_split_screen_lap(rdram,Output+8,1);
    word(rdram,0x801CE638,4);
    wr64_split_screen_frame(rdram,Output+16);
    const auto before=memory;
    require(wr64_split_screen_lap(rdram,Output+16,0)==Output+16 && memory==before,
        "A later menu inherited an abandoned native lap scope");
    for (int owner:{0,1,2,3}) {
        const auto off=wr64VerticalAnnouncement(wr64VerticalLayout(false,1280,720,3),owner,6);
        require(off.scale==1 && off.dx==0 && off.dy==0,"Disabled announcement mapping changed screen coordinates");
    }
}
}
int main() {
    try {
        native_cases();
        malformed_scopes();
        std::cout<<"Passed "<<cases<<" native lap replay cases and "<<assertions<<" assertions.\n";
    } catch (const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
