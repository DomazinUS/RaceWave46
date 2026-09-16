#include "recomp.h"
#include "wr64_championship_preview.h"
#include "common/rt64_wr64_ultrawide.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
void func_i3_802C6344(uint8_t*, recomp_context*);
void baseline_func_i3_802C6344(uint8_t*, recomp_context*);
void regenerated_func_i3_802C6344(uint8_t*, recomp_context*);
void native_rectangle(uint8_t*, recomp_context*);
void native_number(uint8_t*, recomp_context*);
void native_time(uint8_t*, recomp_context*);
void native_string(uint8_t*, recomp_context*);
}

namespace {
unsigned assertions = 0, scenarios = 0;
std::string context;
void require(bool condition, const char* reason) {
    ++assertions;
    if (!condition) { std::cerr << context << ": " << reason << '\n'; std::exit(1); }
}
constexpr uint32_t Output = 0x80020000, Stack = 0x80100000;
constexpr uint32_t Segment1 = 0x80400000, Viewport = Segment1 + 0x6F728;
constexpr uint32_t Segment8 = 0x80300000, Depth = Segment8 + 0x4E418;
constexpr uint32_t ExpansionBytes = 536;
using Packet = std::array<uint32_t, 2>;
using Packets = std::vector<Packet>;
using Function = void (*)(uint8_t*, recomp_context*);
void put(uint8_t* rdram, uint32_t address, uint32_t value) { MEM_W(0, S32(address)) = value; }
uint32_t get(uint8_t* rdram, uint32_t address) { return MEM_W(0, S32(address)); }
Packet fill(int left, int top, int right, int bottom) {
    return {0xF6000000U | (uint32_t(right * 4) << 12) | uint32_t(bottom * 4),
        uint32_t(left * 4) << 12 | uint32_t(top * 4)};
}
Packet translate(Packet p, int delta) {
    for (auto& word : p) word = (word & ~0x00FFF000U) | (((((word >> 12) & 0xFFF) + delta * 4) & 0xFFF) << 12);
    return p;
}
struct Glyph {
    uint32_t font, code;
    int32_t x, y;
    std::array<uint32_t, 14> style;
    bool operator==(const Glyph&) const = default;
};
struct Call {
    uint32_t kind;
    std::array<uint32_t, 13> args{};
    std::vector<Glyph> glyphs;
    bool operator==(const Call&) const = default;
};
std::vector<Call> calls;
std::vector<Glyph> replayGlyphs;
void capture(uint32_t kind, uint8_t* rdram, recomp_context* ctx, Function replay = nullptr) {
    Call call{kind, {uint32_t(ctx->r5), uint32_t(ctx->r6), uint32_t(ctx->r7)}};
    // Only arguments consumed by this native producer are meaningful; the
    // remaining caller stack slots may contain stale display-list cursors.
    const size_t count = kind == 3 ? 13 : kind == 1 ? 5 : kind == 2 ? 6 : kind == 7 ? 8 : 4;
    for (size_t i = 3; i < count; ++i) call.args[i] = MEM_W((i + 1) * 4, ctx->r29);
    if (replay) {
        recomp_context native = *ctx;
        native.f_odd = &native.f0.u32h;
        native.r4 = S32(Output + 0x8000);
        native.r29 = S32(Stack - 0x1000);
        MEM_W(0x10, native.r29) = call.args[3];
        replayGlyphs.clear();
        replay(rdram, &native);
        call.glyphs = replayGlyphs;
    }
    calls.push_back(call);
    if (kind == 7) native_rectangle(rdram, ctx);
    else {
        put(rdram, uint32_t(ctx->r4), 0x7F000000 | kind);
        put(rdram, uint32_t(ctx->r4) + 4, 0);
        ctx->r2 = ADD32(ctx->r4, 8);
    }
}
}

extern "C" {
void func_80094338(uint8_t* rdram, recomp_context* ctx) { capture(1, rdram, ctx); }
void func_801E3EE0(uint8_t* rdram, recomp_context* ctx) { capture(2, rdram, ctx); }
void func_801E946C(uint8_t* rdram, recomp_context* ctx) { capture(3, rdram, ctx); }
void func_801EB00C(uint8_t* rdram, recomp_context* ctx) { capture(4, rdram, ctx, native_number); }
void func_801E8B24(uint8_t* rdram, recomp_context* ctx) { capture(5, rdram, ctx, native_time); }
void func_801E9858(uint8_t* rdram, recomp_context* ctx) { capture(6, rdram, ctx, native_string); }
void func_801E7C58(uint8_t* rdram, recomp_context* ctx) { capture(7, rdram, ctx); }
void func_801E80B0(uint8_t* rdram, recomp_context* ctx) {
    Glyph glyph{uint32_t(ctx->r5), uint32_t(ctx->r6), int32_t(ctx->r7), MEM_W(0x10, ctx->r29)};
    for (int i = 0; i < 14; ++i) glyph.style[i] = MEM_W(0x14 + i * 4, ctx->r29);
    replayGlyphs.push_back(glyph);
    ctx->r2 = ADD32(ctx->r4, 8);
}
void func_800CA210(uint8_t* rdram, recomp_context* ctx) {
    // Intercept only the original libc decimal conversion. Native number
    // alignment, proportional widths, string conversion and glyphs still run.
    require(ctx->r6 <= 999, "Native points formatter received an invalid fixture value");
    const auto value = std::to_string(uint32_t(ctx->r6));
    for (size_t i = 0; i < value.size(); ++i) MEM_B(i,ctx->r4) = value[i];
    MEM_B(value.size(),ctx->r4) = 0;
    ctx->r2 = value.size();
}
void do_break(uint32_t) { std::abort(); }
void switch_error(const char*, uint32_t, uint32_t) { std::abort(); }
}

namespace {
constexpr uint32_t Frame = Segment8 + 0x4E4E0;
std::array<Packet,13> depthFixture() {
    // Actual IPS descriptor 0x972A4 selects [0x819A6C,0x81C4F2), decoded
    // into segment8+0x47000 (0x7628 bytes). Construct the guarded fields;
    // unrelated command-state payloads remain deliberately synthetic.
    constexpr uint8_t ops[]={0x03,0xB6,0xB7,0xBB,0xE7,0xBA,0xFC,0xB9,0xFE,0xFF,0xF7,0xF6,0xB8};
    std::array<Packet,13> result{};
    for(size_t i=0;i<result.size();++i) result[i]={uint32_t(ops[i])<<24|uint32_t(i),0x12003400U+uint32_t(i)};
    result[0]={0x03800010,0x0804E408};
    result[8]={0xFE000000,0x00700000};
    result[9]={0xFF1001A7,0x00700000};
    result[11]=fill(31,63,179,166);
    result[12]={0xB8000000,0};
    return result;
}
std::array<Packet,41> frameFixture() {
    constexpr uint8_t ops[]={0xFD,0xF5,0xE6,0xF3,0xE7,0xF5,0xF2,0xE4,0xB3,0xB2};
    std::array<Packet,41> result{};
    for(size_t i=0;i<40;++i) result[i]={uint32_t(ops[i%10])<<24|uint32_t(i),0x23004500U+uint32_t(i)};
    result[3][0]=0xF4000003;
    result[13][0]=0xF400000D;
    constexpr uint32_t textures[]={0x08047008,0x080473B8,0x08047768,0x080479E0};
    for(int band=0;band<4;++band) {
        result[band*10][1]=textures[band];
        result[band*10+8]={0xB3000000,band<2?0U:0x0CE00000U};
    }
    result[7]={0xE42E00FC,0x000700F0}; // top [28,184) x [60,63)
    result[17]={0xE42E02A8,0x0007029C}; // bottom [28,184) x [167,170)
    result[27]={0xE507C29C,0x000700FC}; // left [28,31) x [63,167)
    result[37]={0xE52DC29C,0x002D00FC}; // right [180,183) x [63,167)
    result[9]={0xB2000000,0x04000400};
    result[19]={0xB2000000,0x04000400};
    result[29]={0xB2000000,0xFC000400};
    result[39]={0xB2000000,0xFC000400};
    result[40]={0xB8000000,0};
    return result;
}
Packet rectangleX(Packet p,int left,int right) {
    p[0]=(p[0]&~0x00FFF000U)|(uint32_t(right*4)<<12);
    p[1]=(p[1]&~0x00FFF000U)|(uint32_t(left*4)<<12);
    return p;
}
double rectangleLeft(const Packet& p) { return double((p[1]>>12)&0xFFF)/4.0; }
double rectangleRight(const Packet& p) { return double((p[0]>>12)&0xFFF)/4.0; }
double sourceU(const Packet& rect,const Packet& st,const Packet& step,double screenX) {
    return double(int16_t(st[1]>>16))/32.0+
        (screenX-rectangleLeft(rect))*double(int16_t(step[1]>>16))/1024.0;
}
Packets expandedFrameFixture() {
    const auto original=frameFixture();
    Packets result;
    for(size_t band=0;band<4;++band) {
        const size_t base=band*10;
        result.insert(result.end(),original.begin()+base,original.begin()+base+7);
        if(band<2) {
            // Native four-pixel caps keep their relation to the vertical strips.
            // The 148-pixel center alone fills the added 104-pixel gap.
            for(const auto& slice : {std::array<int,4>{28,32,0,1024},
                                    {32,284,4,601},{284,288,152,1024}}) {
                result.push_back(rectangleX(original[base+7],slice[0],slice[1]));
                auto st=original[base+8]; st[1]=(st[1]&0xFFFFU)|(uint32_t(slice[2]*32)<<16);
                result.push_back(st);
                auto step=original[base+9]; step[1]=(step[1]&0xFFFFU)|(uint32_t(slice[3])<<16);
                result.push_back(step);
            }
        } else {
            result.push_back(band==3?translate(original[base+7],104):original[base+7]);
            result.push_back(original[base+8]);result.push_back(original[base+9]);
        }
    }
    return result;
}
void checkCapSampling(const Packets& emitted,size_t first) {
    const auto native=frameFixture();
    for(size_t band=0;band<2;++band) {
        const size_t left=first+band*16+7,middle=left+3,right=left+6;
        const size_t old=band*10+7;
        require(rectangleLeft(emitted[left])==28 && rectangleRight(emitted[right])==288,
            "Horizontal border lost its native left or expanded right bound");
        require(rectangleRight(emitted[left])==rectangleLeft(emitted[middle]) &&
            rectangleRight(emitted[middle])==rectangleLeft(emitted[right]),
            "Horizontal border slices leave a gap or overlap");
        for(int pixel=0;pixel<4;++pixel) {
            const double leftX=28+pixel,rightX=284+pixel;
            require(sourceU(emitted[left],emitted[left+1],emitted[left+2],leftX)==
                sourceU(native[old],native[old+1],native[old+2],leftX),
                "Left bevel sampling changed from the native cap");
            require(sourceU(emitted[right],emitted[right+1],emitted[right+2],rightX)==
                sourceU(native[old],native[old+1],native[old+2],rightX-104),
                "Right bevel sampling is not the original cap translated by 104 pixels");
        }
        // The audited native texture's dark/bright/bright/transparent end is
        // texels152..155. Its first texel must sit directly above the right side.
        const auto& vertical=emitted[first+49];
        require(rectangleLeft(emitted[right])==rectangleLeft(vertical) &&
            sourceU(emitted[right],emitted[right+1],emitted[right+2],rectangleLeft(vertical))==152,
            "Right horizontal cap does not join the vertical border at native texel152");
        require(sourceU(emitted[middle],emitted[middle+1],emitted[middle+2],32)==4 &&
            std::abs(sourceU(emitted[middle],emitted[middle+1],emitted[middle+2],284)-152)<0.125,
            "Stretched center does not span the texture between the native caps");
    }
}
void checkOldStretchFailure() {
    const auto original=frameFixture();
    const auto rect=rectangleX(original[7],28,288);
    auto step=original[9];step[1]=0x02660400;
    require(sourceU(rect,original[8],step,284)==153.5 &&
        sourceU(original[7],original[8],original[9],180)==152,
        "Negative control no longer demonstrates the old cap misalignment");
}
struct Settings {
    int state=8,mode=30,players=1,course=0,difficulty=0,round=0,variant=0,buffer=0;
    int sequence=2,count=0,mapFlag=1,flash=0,fault=0;
    int titleSequence=1,titleFlag=1;
};
struct Result {
    Packets packets;
    std::vector<Call> calls;
    std::vector<uint32_t> preserved;
    std::array<uint32_t,6> fade{};
    bool operator==(const Result&) const = default;
};
std::vector<uint32_t> preserved(uint8_t* rdram) {
    std::vector<uint32_t> result;
    for(auto region : {std::array<uint32_t,2>{0x800D4000,0x8000},{0x800EAB00,0x200},
        {0x801C1F00,0x1000},{0x801CB300,0x100},{0x80198300,0x100},{0x801CE5F0,0x130},
        {0x802C6F90,0xA0},{Viewport,16},{Depth,104},{Frame,328},{0x80226D70,0x140},
        {0x80200000,0x2000},{0x80223938,4}})
        for(uint32_t offset=0;offset<region[1];offset+=4) result.push_back(get(rdram,region[0]+offset));
    return result;
}
void seed(uint8_t* rdram,const Settings& s) {
    put(rdram,0x801CE638,s.state);
    put(rdram,0x800DAB24,s.mode);
    put(rdram,0x802C7028,s.titleSequence);
    put(rdram,0x80223938,s.titleFlag);
    MEM_H(0,S32(0x801CE60C))=int16_t(s.players);
    put(rdram,0x800D8170,s.course);
    put(rdram,0x801CB330,s.course);
    put(rdram,0x801CB334,s.round);
    put(rdram,0x801CB338,s.difficulty);
    put(rdram,0x800D48DC,(s.course+1)%4);
    put(rdram,0x802C6F64,s.sequence);
    put(rdram,0x802C6F68,s.count);
    put(rdram,0x802C6F6C,s.sequence==2?255:0);
    put(rdram,0x802C6F70,s.sequence==2?170:0);
    put(rdram,0x802C6F80,s.mapFlag);
    put(rdram,0x802C6F84,s.sequence==2);
    put(rdram,0x802C6F8C,s.variant);
    put(rdram,0x802C6FE0,s.flash);
    MEM_H(0,S32(0x800DAB68))=int16_t(s.variant==2);
    MEM_H(0,S32(0x802C7024))=0x7654;
    put(rdram,0x801CE704,s.course%4);
    put(rdram,0x801CE5F8,0x00200000);
    put(rdram,0x80151948,s.buffer);
    for(int i=0;i<3;++i) put(rdram,0x801542C0+i*4,0x80160000+i*0x40000);
    put(rdram,0x801CE6B4,Segment1&0x1FFFFFFF);
    put(rdram,0x801CE6D0,Segment8&0x1FFFFFFF);
    put(rdram,0x801518B8,Output);
    constexpr uint32_t vp[]={0x028001E0,0x01FF0000,0x01A401CC,0x01FF0000};
    for(int i=0;i<4;++i) put(rdram,Viewport+i*4,vp[i]);
    auto depth=depthFixture();
    auto frame=frameFixture();
    if(s.fault==1) depth[12][0]=0xDEADBEEF;
    if(s.fault==2) depth[9][0]=0xFF10013F; // outdated 320-pixel asset
    if(s.fault==3) depth[8][1]=0x002A0000; // unused original depth address
    if(s.fault==4) frame[40][1]=1;
    if(s.fault==5) frame[37][0]+=0x4000;
    if(s.fault==6) frame[19][1]=0xFC000400;
    if(s.fault==7) frame[12][0]=0xDEADBEEF;
    if(s.fault==8) put(rdram,Viewport+8,0x01A801CC);
    if(s.fault==9) put(rdram,0x801CE6D0,0xFFFFFFFF);
    if(s.fault==10) put(rdram,0x801518B8,0xA0020000);
    if(s.fault==11) put(rdram,0x801518B8,Output-0x5F00);
    for(size_t i=0;i<depth.size();++i) {put(rdram,Depth+uint32_t(i*8),depth[i][0]);put(rdram,Depth+uint32_t(i*8+4),depth[i][1]);}
    for(size_t i=0;i<frame.size();++i) {put(rdram,Frame+uint32_t(i*8),frame[i][0]);put(rdram,Frame+uint32_t(i*8+4),frame[i][1]);}
    for(int i=0;i<9;++i) {
        put(rdram,0x800DAA34+i*4,20+i);
        put(rdram,0x802C6F90+i*4,30+i);
        put(rdram,0x801C1FF0+i*60,65321+i*101);
        put(rdram,0x801C22C0+i*20,20543+i*13);
        put(rdram,0x801C23B0+i*20,76543+i*53);
        for(int table=0;table<6;++table) for(int transparent=0;transparent<2;++transparent)
            put(rdram,0x800DB5B0+table*0x48+i*8+transparent*4,0x08000000+table*0x1000+i*0x100+transparent*0x40);
    }
    for(int i=0;i<4;++i) {
        put(rdram,0x801CB340+i*4,35+i*12);
        put(rdram,0x802C6FD4+i*4,6+i);
        put(rdram,0x802C6F50+i*4,0x08002000+i*0x1000);
        for(int race=0;race<10;++race) MEM_H(i*20+race*2,S32(0x800EABBC))=int16_t(2+i*10+race);
    }
    for(uint32_t address : {0x802C6FF0U,0x802C6FFCU,0x802C7008U}) {
        const char missing[]="-'--@---";
        for(int i=0;i<9;++i) MEM_B(i,gpr(S32(address)))=missing[i];
    }
    for(int i=0;i<0x84;++i) MEM_B(i,S32(0x80226D70))=int8_t(6+(i*5)%7);
    put(rdram,0x80226E24,0x3F800000);
}
Result run(int version,const Settings& s) {
    static std::vector<uint8_t> memory(8*1024*1024);
    std::fill(memory.begin(),memory.end(),0);
    uint8_t* rdram=memory.data();
    seed(rdram,s);
    const auto before=preserved(rdram);
    recomp_context ctx{};
    ctx.f_odd=&ctx.f0.u32h;
    ctx.r29=S32(Stack);ctx.r31=S32(0x80001100);ctx.r4=S32(Output);ctx.r16=0x12345678;
    const Function functions[]={baseline_func_i3_802C6344,func_i3_802C6344,regenerated_func_i3_802C6344};
    calls.clear();
    functions[version](rdram,&ctx);
    require(uint32_t(ctx.r29)==Stack && uint32_t(ctx.r31)==0x80001100 && ctx.r16==0x12345678,
        "Native caller stack, return address, or saved register changed");
    const uint32_t end=uint32_t(ctx.r2);
    require(end>=Output && end<Output+0x6000 && (end-Output)%8==0,"Invalid native output cursor");
    Result result{{},calls,preserved(rdram)};
    require(result.preserved==before,"Preview mutated camera, model, records, viewport, or source assets");
    for(uint32_t cursor=Output;cursor<end;cursor+=8) result.packets.push_back({get(rdram,cursor),get(rdram,cursor+4)});
    int i=0;for(uint32_t address : {0x802C6F64U,0x802C6F68U,0x802C6F6CU,0x802C6F70U,0x802C6F80U,0x802C6F84U})
        result.fade[i++]=get(rdram,address);
    return result;
}
Packets normalize(const Packets& packets,bool active) {
    Packets result;
    unsigned enable=0,align=0,viewports=0,depth=0,frame=0,backing=0,scissor=0;
    int offset=0;
    for(size_t i=0;i<packets.size();++i) {
        auto p=packets[i];
        if(p==Packet{0x00525464,0x10000064}) {++enable;continue;}
        if(p[0]==0x64000007) {
            require(i+1<packets.size() && p[1]==0x800,"Viewport alignment header/origin changed");
            p=packets[++i];
            require(uint16_t(p[0])==0 && p[1]==0,"Viewport Y or reserved alignment fields changed");
            offset=int16_t(p[0]>>16);
            require(offset==(align==0?208:0),"Championship preview offset/reset differs from +52 pixels");
            ++align;continue;
        }
        if(p==Packet{0x03800010,0x0106F728} && offset) {
            require((420+offset)/4==157,"Map center did not move from 105 to 157");
            ++viewports;
        }
        if(active && p==frameFixture()[0]) {
            const auto expected=expandedFrameFixture();
            require(expected.size()==52 && i+expected.size()<=packets.size(),"Inline frame is truncated");
            for(size_t j=0;j<expected.size();++j) {
                require(packets[i+j]==expected[j],"Frame changed texture state, UVs, Y, left edge, or border width");
            }
            checkCapSampling(packets,i);
            i+=expected.size()-1;result.push_back({0x06000000,0x0804E4E0});++frame;continue;
        }
        if(active && p==depthFixture()[0]) {
            const auto original=depthFixture();
            require(i+12<=packets.size(),"Inline depth clear is truncated");
            for(size_t j=0;j<12;++j) {
                auto expected=original[j];
                if(j==11) expected=fill(31,63,283,166);
                require(packets[i+j]==expected,"Depth clear altered state/address/stride/Y/left beyond right edge");
            }
            i+=11;result.push_back({0x06000000,0x0804E418});++depth;continue;
        }
        if(p==fill(31,63,285,168)) {p=fill(31,63,181,168);++backing;}
        if(p==Packet{0xED07C0FC,0x0047029C}) {p[1]=0x002D029C;++scissor;}
        result.push_back(p);
    }
    require(offset==0 && enable==(active?1U:0U) && align==(active?2U:0U) && viewports==(active?1U:0U),
        "Viewport translation leaked or failed to activate");
    require(frame==(active?1U:0U) && depth==frame && backing==frame && scissor==frame,
        "The preview frame/depth/backing/scissor did not expand together");
    return result;
}
void compare(const Settings& s,bool active) {
    context="case "+std::to_string(scenarios)+" course "+std::to_string(s.course)+" seq "+std::to_string(s.sequence)+" fault "+std::to_string(s.fault);
    auto before=run(0,s),after=run(1,s),recipe=run(2,s);
    require(after==recipe,"Checked-in producer differs from TOML regeneration");
    require(after.packets.size()==before.packets.size()+(active?ExpansionBytes/8:0),"Expansion exceeded the 536-byte command budget");
    require(after.calls==before.calls,"Championship record columns, glyphs, frames, or backing arguments changed");
    require(after.fade==before.fade,"Original title wait/fade/map visibility/skip animation changed");
    after.packets=normalize(after.packets,active);
    require(after==before,"Map geometry, opaque/translucent order, restoration, or unrelated content changed");
    ++scenarios;
}
void checkAtomicFailures(bool enabled) {
    std::vector<uint8_t> memory(8*1024*1024);
    for(int fault=0;fault<15;++fault) {
        context="atomic "+std::to_string(fault);
        std::fill(memory.begin(),memory.end(),0);
        uint8_t* rdram=memory.data();
        Settings s;s.course=5;s.difficulty=2;
        seed(rdram,s);
        recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;ctx.r29=S32(Stack);ctx.r4=S32(Output);
        baseline_func_i3_802C6344(rdram,&ctx);
        const uint32_t end=uint32_t(ctx.r2);
        wr64_championship_preview_prepare(rdram,Output);
        if(fault>=1 && fault<=5) {
            const Packet targets[]={{0x06000000,0x0804E4E0},{0x06000000,0x0804E418},
                {0x03800010,0x0106F728},{0xED07C0FC,0x002D029C},fill(31,63,181,168)};
            bool found=false;
            for(uint32_t cursor=Output;cursor<end;cursor+=8) if(Packet{get(rdram,cursor),get(rdram,cursor+4)}==targets[fault-1]) {
                put(rdram,cursor+4,get(rdram,cursor+4)^1);found=true;break;
            }
            require(found,"Atomic fixture did not find its exact native target");
        }
        if(fault==6) put(rdram,0x801CE638,5);
        if(fault==7) put(rdram,0x800DAB24,62);
        if(fault>=9 && fault<=12) {
            uint32_t first=0,frame=0,depth=0;
            for(uint32_t cursor=Output;cursor<end;cursor+=8) {
                const Packet p{get(rdram,cursor),get(rdram,cursor+4)};
                if(p==Packet{0x06000000,0x0106F628}) first=cursor;
                if(p==Packet{0x06000000,0x0804E4E0}) frame=cursor;
                if(p==Packet{0x06000000,0x0804E418}) depth=cursor;
            }
            require(first && frame && depth,"Atomic ordering fixture could not locate native display-list calls");
            if(fault==9) put(rdram,first+4,0x0804E4E0);
            if(fault==10) {put(rdram,frame+4,0x0804E418);put(rdram,depth+4,0x0804E4E0);}
            if(fault==11 || fault==12) put(rdram,first+4,fault==11?Output&0x1FFFFFFF:Output);
        }
        if(fault==13) put(rdram,0x802C7028,0);
        if(fault==14) put(rdram,0x80223938,0);
        auto before=memory;
        const uint32_t updated=wr64_championship_preview_finish(fault==8?rdram+0x100:rdram,end);
        if(enabled && fault==0) require(updated==end+ExpansionBytes,"Valid atomic rewrite failed to activate");
        else require(updated==end && memory==before,"Rejected rewrite partially modified emitted output or memory");
        before=memory;
        require(wr64_championship_preview_finish(rdram,updated)==updated && memory==before,
            "Finished scope could be applied twice");
    }
}
void checkTailCapacity(bool enabled) {
    std::vector<uint8_t> memory(8*1024*1024);
    for(int overflow : {0,1}) {
        context="tail reserve boundary "+std::to_string(overflow);
        std::fill(memory.begin(),memory.end(),0);
        uint8_t* rdram=memory.data();
        seed(rdram,Settings{});
        put(rdram,0x801518B8,Output-0x4000); // 0x2000 bytes remain in the native pool
        recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;ctx.r29=S32(Stack);ctx.r4=S32(Output);
        baseline_func_i3_802C6344(rdram,&ctx);
        const uint32_t nativeEnd=uint32_t(ctx.r2);
        const uint32_t end=Output+0x2000-ExpansionBytes-0x800+overflow*8;
        require(end>=nativeEnd,"Capacity boundary fixture is smaller than native output");
        const Packet restore{get(rdram,nativeEnd-8),get(rdram,nativeEnd-4)};
        // Extra harmless commands before the original final scissor model a
        // fully occupied builder; preserve the exact ending command contract.
        for(uint32_t at=nativeEnd-8;at<end-8;at+=8) {put(rdram,at,0xE7000000);put(rdram,at+4,0);}
        put(rdram,end-8,restore[0]);put(rdram,end-4,restore[1]);
        for(uint32_t at=end;at<Output+0x2000+16;at+=4) put(rdram,at,0x2468ACE0);
        Packets original;
        for(uint32_t at=Output;at<end;at+=8) original.push_back({get(rdram,at),get(rdram,at+4)});
        const auto before=memory;
        wr64_championship_preview_prepare(rdram,Output);
        const uint32_t updated=wr64_championship_preview_finish(rdram,end);
        const bool active=enabled && !overflow;
        require(updated==end+(active?ExpansionBytes:0),"Exact capacity boundary or reserved tail was miscalculated");
        Packets after;
        for(uint32_t at=Output;at<updated;at+=8) after.push_back({get(rdram,at),get(rdram,at+4)});
        require(normalize(after,active)==original,"Capacity handling changed commands beyond the scoped expansion");
        auto expected=before;
        if(active) std::memcpy(expected.data()+(Output&0x1FFFFFFF),memory.data()+(Output&0x1FFFFFFF),updated-Output);
        require(memory==expected,"Capacity handling wrote into tail reserve, neighboring pool data, or source memory");
    }
}
}
int main(int argc,char**) {
    const bool enabled=argc==1;
    checkOldStretchFailure();
    for(float aspect : {4.0f/3.0f,16.0f/9.0f,21.0f/9.0f,32.0f/9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for(int course=0;course<9;++course) for(int difficulty=0;difficulty<3;++difficulty)
            for(int variant : {0,2}) for(int flag : {0,1}) {
                Settings s;s.course=course;s.difficulty=difficulty;s.variant=variant;s.mapFlag=flag;
                s.buffer=(course+difficulty)%3;s.round=course%7;s.flash=course&1;s.mode=30+(course&1);
                compare(s,enabled);
            }
        for(int sequence : {0,1}) for(int count : {0,1,9,18,19}) {
            Settings s;s.sequence=sequence;s.count=count;s.mapFlag=0;s.course=5;s.difficulty=2;
            compare(s,enabled);
        }
        for(int fault=1;fault<=11;++fault) {Settings s;s.fault=fault;compare(s,false);}
        for(int stat : {4,5,10}) {Settings s;s.state=stat;compare(s,false);}
        for(int mode : {10,62}) {Settings s;s.mode=mode;compare(s,false);}
        {Settings s;s.players=2;compare(s,false);}
        {Settings s;s.titleSequence=0;compare(s,false);}
        {Settings s;s.titleFlag=0;compare(s,false);}
    }
    checkAtomicFailures(enabled);
    checkTailCapacity(enabled);
    std::cout<<"Passed "<<scenarios<<" native Championship map cases, 15 atomic cases and 2 capacity boundaries, "<<assertions
        <<" assertions; feature "<<(enabled?"enabled":"disabled")<<".\n";
}
