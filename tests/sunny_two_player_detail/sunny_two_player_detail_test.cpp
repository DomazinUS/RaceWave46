#include "recomp.h"
#include "wr64_sunny_detail.hpp"
#include "../../lib/rt64/src/common/rt64_wr64_rt_two_player_assets.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

extern "C" {
void unk_game_load(uint8_t*, recomp_context*);
void baseline_unk_game_load(uint8_t*, recomp_context*);
void func_80095A28(uint8_t*, recomp_context*);
void baseline_func_80095A28(uint8_t*, recomp_context*);
void func_80071E70(uint8_t*, recomp_context*);
void baseline_func_80071E70(uint8_t*, recomp_context*);
}
namespace {
constexpr uint32_t RamSize = 0x800000, Stack = 0x807FF000, Base = 0x802D6800,
    DataBase = 0x80306800, FullSpan = 89880, ReducedSpan = 25880, CommonBytes = 96768;
using Ram = std::vector<uint8_t>;
using Function = void (*)(uint8_t*, recomp_context*);
unsigned assertions = 0, scenarios = 0;
uint64_t nativeAccesses = 0;
std::string scenario;
std::vector<uint8_t> rom;
std::vector<uint32_t> assetCalls;
std::vector<std::string> diagnostics;
struct Transfer { uint32_t start, destination, size; bool operator==(const Transfer&) const = default; };
std::vector<Transfer> transfers;
void require(bool good, const char* message) {
    ++assertions;
    if (!good) { std::cerr << "FAIL " << scenario << ": " << message << '\n'; std::exit(1); }
}
void captureDiagnostic(const char* line) { diagnostics.emplace_back(line); }
void requireDiagnostic(const char* stage, const std::string& fields) {
    require(!diagnostics.empty(), "expected diagnostic was not published");
    require(diagnostics.back().starts_with(std::string(stage)+" "), "incorrect diagnostic stage");
    require(diagnostics.back().find(fields)!=std::string::npos, "diagnostic omitted the native decision fields");
}
void put(uint8_t* rdram, uint32_t p, uint32_t v) { MEM_W(0, S32(p)) = v; }
uint32_t get(uint8_t* rdram, uint32_t p) { return MEM_W(0, S32(p)); }
void putHalf(uint8_t* rdram, uint32_t p, int16_t v) { MEM_H(0, S32(p)) = v; }
void copyBytes(uint8_t* rdram, uint32_t dest, const std::vector<uint8_t>& data, size_t offset, size_t count) {
    require(offset + count <= data.size() && (dest & 0x7FFFFF) + count <= RamSize, "copy outside ROM/RDRAM");
    for (size_t i = 0; i < count; ++i) MEM_B(i, S32(dest)) = data[offset + i];
}
uint32_t be32(const std::vector<uint8_t>& data, size_t p) {
    require(p+4 <= data.size(), "big-endian read out of range");
    return uint32_t(data[p])<<24 | uint32_t(data[p+1])<<16 | uint32_t(data[p+2])<<8 | data[p+3];
}
std::vector<uint8_t> independentMio(uint32_t start, uint32_t end) {
    require(end <= rom.size() && end > start+16, "MIO ROM range invalid");
    require(be32(rom,start) == 0x4D494F30, "MIO magic mismatch");
    const auto size = be32(rom,start+4);
    size_t packed = start+be32(rom,start+8), raw = start+be32(rom,start+12), bits = start+16;
    uint8_t mask=0, word=0;
    std::vector<uint8_t> out; out.reserve(size);
    while(out.size()<size) {
        if (!mask) { require(bits<end,"MIO bits exceed source"); word=rom[bits++]; mask=128; }
        if (word & mask) { require(raw<end,"MIO literal exceeds source"); out.push_back(rom[raw++]); }
        else {
            require(packed+2<=end,"MIO token exceeds source");
            uint16_t token=uint16_t(rom[packed])<<8 | rom[packed+1]; packed+=2;
            unsigned length=(token>>12)+3, back=(token&4095)+1;
            require(back<=out.size() && out.size()+length<=size,"MIO backreference invalid");
            while(length--) out.push_back(out[out.size()-back]);
        }
        mask >>= 1;
    }
    return out;
}
std::vector<uint8_t> bytes(uint8_t* rdram, uint32_t address, size_t count) {
    std::vector<uint8_t> out(count);
    for (size_t i=0;i<count;++i) out[i]=MEM_BU(i,S32(address));
    return out;
}
void run(Function f, Ram& ram, uint32_t argument=0) {
    recomp_context ctx{};
    ctx.f_odd=&ctx.f0.u32h;
    ctx.r29=S32(Stack); ctx.r4=S32(argument);
    f(ram.data(),&ctx);
    require(uint32_t(ctx.r29)==Stack,"native stack not balanced");
}
Ram initial(int course=1, int players=2, int mode=40, int phase=1) {
    Ram ram(RamSize, 0);
    copyBytes(ram.data(),0x80046800,rom,0x1000,0x800DFFA8-0x80046800);
    auto* rdram=ram.data();
    put(rdram,0x800D8170,course); put(rdram,0x800DAB28,players);
    putHalf(rdram,0x801CE60C,int16_t(players));
    put(rdram,0x800DAB24,mode); put(rdram,0x801CE638,phase);
    put(rdram,0x801518B8,0x80500000); put(rdram,0x80151944,0x80500000);
    // Native tables refer to a runtime trigonometric table. Populate the
    // same 4096-entry circle so full SetCourse arithmetic has finite inputs.
    for(unsigned i=0;i<4096;++i) put(rdram,0x80154350+i*4,
        std::bit_cast<uint32_t>(float(std::sin(double(i)*6.2831853071795864769/4096))));
    return ram;
}
void checkEqualOutsideRoots(const Ram& baseline, const Ram& changed, bool enhanced) {
    unsigned changedWords=0;
    for(size_t p=0;p<RamSize;p+=4) {
        if (std::memcmp(baseline.data()+p,changed.data()+p,4)==0) continue;
        if (!(enhanced && p>=0x1C1CD0 && p<0x1C1CE8)) {
            std::cerr<<"unexpected write difference at "<<std::hex<<(p+0x80000000)<<std::dec<<'\n';
            require(false,"native SetCourse changed nonvisual RDRAM");
        }
        ++changedWords;
    }
    require(changedWords==(enhanced?4U:0U),"unexpected number of changed root words");
}
void testLoader(bool enabled) {
    scenario=enabled?"enabled native Sunny loader":"disabled native Sunny loader"; ++scenarios;
    auto ram=initial(); auto before=ram; auto* rdram=ram.data();
    wr64::sunny_detail::set_enabled(enabled);
    diagnostics.clear();
    wr64::sunny_detail::set_diagnostic_sink(captureDiagnostic);
    require(ram==before,"installing diagnostic sink changed native RAM");
    wr64_sunny_detail_begin_load(ram.data());
    requireDiagnostic(enabled?"load-enhanced":"load-original",enabled?
        "requested=1 eligible=1 selected=0":"requested=0 eligible=0 selected=0");
    transfers.clear();
    run(func_80095A28,ram,0x800DC350);
    require(diagnostics.size()==2,"native shape load emitted an unexpected diagnostic count");
    requireDiagnostic(enabled?"asset-enhanced":"asset-original",enabled?"entry=800DC1D0":"entry=800DC350");
    const uint32_t span=enabled?FullSpan:ReducedSpan;
    require(transfers.size()==2,"shape/common loader issued wrong DMA count");
    require(transfers[0].start==(enabled?0x1E5860U:0x241070U),"native loader selected wrong shape ROM");
    require(transfers[1].start==0x257D40,"native loader changed common ROM");
    require(bytes(ram.data(),Base,span)==independentMio(enabled?0x1E5860:0x241070,enabled?0x1EFCF0:0x243540),
        "native MIO output differs from independent decoder");
    require(get(ram.data(),0x800D45E8)==Base+span,"common base did not follow decoded shape size");
    require(get(ram.data(),0x801CE6E8)==((Base+span)&0x1FFFFFFF),"native common physical segment pointer incorrect");
    require(bytes(ram.data(),Base+span,CommonBytes)==independentMio(0x257D40,0x2631D0),
        "common bank was corrupted or overwritten");
    require(std::equal(ram.begin()+((Base+span+CommonBytes)&0x7FFFFF),ram.begin()+(DataBase&0x7FFFFF),
        before.begin()+((Base+span+CommonBytes)&0x7FFFFF)),"graphics overran course-data gap");
    require(std::equal(ram.begin()+(DataBase&0x7FFFFF),ram.begin()+((Base+0x40000)&0x7FFFFF),
        before.begin()+(DataBase&0x7FFFFF)),"shape load touched collision/course-data area");
    transfers.clear(); run(func_80095A28,ram,0x800DC558);
    require(transfers.size()==1 && transfers[0].destination==DataBase && transfers[0].start==0x2A9F70,
        "collision/course-data transfer changed");
    require(bytes(ram.data(),DataBase,0x2B3680-0x2A9F70)==std::vector<uint8_t>(rom.begin()+0x2A9F70,rom.begin()+0x2B3680),
        "collision/course-data bytes changed");
    require(wr64_sunny_detail_water_active(ram.data())==0,"full water material enabled before its texture bank");
    const uint32_t textureBase=get(ram.data(),0x800D45F0);
    auto expectedTextures=bytes(ram.data(),textureBase,0x8400);
    const uint32_t uploads[][3]{
        {0x361A90,0x361BA0,0},{0x361A90,0x361BA0,0x200},
        {enabled?0x3620B0U:0x3684B0U,enabled?0x362DE0U:0x368910U,0xC00},
        {enabled?0x3620B0U:0x3684B0U,enabled?0x362DE0U:0x368910U,0x400},
        {0x36AE80,0x36B5F0,0x1400},{0x36AE80,0x36B5F0,0x4400},
        {0x36E9B0,0x36F2B0,0x7400}};
    for(const auto& upload:uploads) {
        auto payload=independentMio(upload[0],upload[1]);
        require(upload[2]+payload.size()<=expectedTextures.size(),"texture exceeds stock bank capacity");
        std::copy(payload.begin(),payload.end(),expectedTextures.begin()+upload[2]);
    }
    const auto textureTail=bytes(ram.data(),textureBase+0x8400,64);
    transfers.clear(); run(func_80095A28,ram,0x800DBCE4);
    require(transfers.size()==7,"native texture loader changed upload count");
    require(bytes(ram.data(),textureBase,0x8400)==expectedTextures,"native texture bank differs from ordered full/reduced uploads");
    require(bytes(ram.data(),textureBase+0x8400,64)==textureTail,"texture uploads exceeded the stock range");
    require(bool(wr64_sunny_detail_water_active(ram.data()))==enabled,"water material gate disagrees with loaded texture format");
    require(get(ram.data(),0x800DAB28)==2 && MEM_H(0,S32(0x801CE60C))==2,"player count changed during load");
    // Complete native SetCourse runs on exactly the same loaded memory.
    auto baseline=ram, changed=ram;
    run(baseline_func_80071E70,baseline);
    run(func_80071E70,changed);
    require(bool(wr64_sunny_detail_active(changed.data()))==enabled,"render detail gate disagrees with loaded course");
    requireDiagnostic(enabled?"visuals-enhanced":"visuals-original",enabled?
        "shape=802D6800 common=802EC718":"shape=802D6800 common=802DCD18");
    if(enabled) requireDiagnostic("visuals-enhanced", "roots=0D0154D0,0D0131D0,0D015A38,0D0158D8,00000000,00000000");
    checkEqualOutsideRoots(baseline,changed,enabled);
    const uint32_t roots[6]{0x0D0154D0,0x0D0131D0,0x0D015A38,0x0D0158D8,0,0};
    if(enabled) for(unsigned i=0;i<6;++i) require(get(changed.data(),0x801C1CD0+i*4)==roots[i],"full root missing");
    // Existing race remains coherent when the frontend choice changes.
    wr64::sunny_detail::set_enabled(!enabled);
    const auto published=diagnostics.size();
    wr64::sunny_detail::set_diagnostic_sink(nullptr);
    auto resident=ram;
    run(func_80071E70,resident);
    require(bool(wr64_sunny_detail_active(resident.data()))==enabled,"render detail gate changed with a resident setting toggle");
    require(bool(wr64_sunny_detail_water_active(resident.data()))==enabled,"water texture format changed with a resident setting toggle");
    require(resident==changed,"setting toggle changed a resident native course");
    require(diagnostics.size()==published,"removed diagnostic sink still received events");
}
void testQueue() {
    scenario="native load queue and durable begin hook"; ++scenarios;
    auto baseline=initial(), changed=baseline;
    wr64::sunny_detail::set_enabled(true);
    assetCalls.clear(); run(baseline_unk_game_load,baseline); const auto oldCalls=assetCalls;
    assetCalls.clear(); run(unk_game_load,changed);
    require(assetCalls==oldCalls,"native load queue entries changed");
    require(std::find(assetCalls.begin(),assetCalls.end(),0x800DC350)!=assetCalls.end(),"queue omitted Sunny shape");
    require(std::find(assetCalls.begin(),assetCalls.end(),0x800DC558)!=assetCalls.end(),"queue omitted native collision data");
    require(changed==baseline,"native load queue changed RDRAM");
    require(wr64_sunny_detail_assets(changed.data(),0x800DC350)==0x800DC1D0,"begin hook did not latch experiment");
}
void testScopeAndLifecycle() {
    scenario="scope and load lifecycle"; ++scenarios;
    auto ram=initial();
    wr64::sunny_detail::set_enabled(true);
    wr64_sunny_detail_begin_load(ram.data());
    const auto untouched=ram;
    require(wr64_sunny_detail_assets(ram.data(),0x800DC558)==0x800DC558,"collision descriptor redirected");
    require(wr64_sunny_detail_assets(ram.data(),0x800DC360)==0x800DC360,"common descriptor redirected");
    require(wr64_sunny_detail_shape_span(ram.data(),0x800DC1D0,ReducedSpan)==ReducedSpan,
        "span changed before full shape was selected");
    require(wr64_sunny_detail_assets(ram.data(),0x800DC350)==0x800DC1D0,"eligible shape not redirected");
    require(wr64_sunny_detail_shape_span(ram.data(),0x800DC1D0,ReducedSpan)==FullSpan,"full shape span missing");
    require(wr64_sunny_detail_shape_span(ram.data(),0x800DC1E0,ReducedSpan)==ReducedSpan,
        "common entry overwrote retained shape span");
    require(ram==untouched,"selection or span helper wrote native RAM");
    wr64::sunny_detail::set_enabled(false);
    require(wr64_sunny_detail_assets(ram.data(),0x800DC350)==0x800DC1D0,"resident asset choice changed mid-load");
    put(ram.data(),0x800DAB24,42);
    require(wr64_sunny_detail_assets(ram.data(),0x800DC350)==0x800DC1D0,"retry did not retain latched assets");
    put(ram.data(),0x800DAB24,40);
    wr64_sunny_detail_begin_load(ram.data());
    require(wr64_sunny_detail_assets(ram.data(),0x800DC350)==0x800DC350,"next load ignored disabled request");
    wr64::sunny_detail::set_enabled(true);
    require(wr64_sunny_detail_assets(ram.data(),0x800DC350)==0x800DC350,"enable affected already-latched disabled load");
    for(int course=0;course<9;++course) for(int players:{1,2}) {
        scenario="scope course="+std::to_string(course)+" players="+std::to_string(players); ++scenarios;
        auto test=initial(course,players);
        wr64_sunny_detail_begin_load(test.data());
        const auto before=test;
        const bool eligible=course==1 && players==2;
        require(wr64_sunny_detail_assets(test.data(),0x800DC350)==(eligible?0x800DC1D0U:0x800DC350U),
            "asset scope leaked to another course/player count");
        require(test==before,"asset scope check wrote RAM");
    }
    for(int mode:{0,7,10,30,31,41,42,43,44,45,46}) {
        scenario="new-load mode="+std::to_string(mode); ++scenarios;
        auto test=initial(1,2,mode);
        wr64_sunny_detail_begin_load(test.data());
        require(wr64_sunny_detail_assets(test.data(),0x800DC350)==0x800DC350,
            "non-course-load mode created a full-asset latch");
    }
    scenario="null native context"; ++scenarios;
    wr64_sunny_detail_begin_load(nullptr);
    require(wr64_sunny_detail_assets(nullptr,0x800DC350)==0x800DC350,"null RAM redirected assets");
    wr64_sunny_detail_visuals(nullptr);
}
void testRejectedAssets() {
    const uint32_t metadata[]{0x800DC4F4,0x800DC518,0x800DCE40,0x800DCE64,
        0x800DC1D0,0x800DC1D4,0x800DC1D8,0x800DC1DC,0x800DC1E0,0x800DC1F8,
        0x800DC350,0x800DC354,0x800DC358,0x800DC35C,0x800DC360,0x800DC378,
        0x800D5474,0x800D54A4,0x800D5534,0x800D5564,0x800D55F4,0x800D5624};
    wr64::sunny_detail::set_enabled(true);
    wr64::sunny_detail::set_diagnostic_sink(captureDiagnostic);
    for(uint32_t address:metadata) {
        scenario="corrupt recognized asset metadata "+std::to_string(address); ++scenarios;
        auto ram=initial();
        put(ram.data(),address,get(ram.data(),address)^4);
        const auto before=ram;
        diagnostics.clear();
        wr64_sunny_detail_begin_load(ram.data());
        requireDiagnostic("load-unknown-assets","requested=1 eligible=0 selected=0");
        require(wr64_sunny_detail_assets(ram.data(),0x800DC350)==0x800DC350,"unrecognized asset layout accepted");
        requireDiagnostic("asset-original","entry=800DC350");
        require(wr64_sunny_detail_shape_span(ram.data(),0x800DC1D0,ReducedSpan)==ReducedSpan,"rejected layout changed span");
        wr64_sunny_detail_visuals(ram.data());
        requireDiagnostic("visuals-original","eligible=0 selected=0");
        require(ram==before,"rejected asset transaction wrote RAM");
    }
    wr64::sunny_detail::set_diagnostic_sink(nullptr);
}
void testVisualScope() {
    scenario="loaded visual scope";
    auto ram=initial();
    wr64::sunny_detail::set_enabled(true);
    wr64_sunny_detail_begin_load(ram.data());
    run(func_80095A28,ram,0x800DC350);
    run(func_80095A28,ram,0x800DC558);
    auto baseline=ram; run(baseline_func_80071E70,baseline);
    struct Edit { uint32_t address; uint32_t value; bool half; };
    const Edit edits[]{
        {0x800DAB28,1,false},{0x801CE60C,1,true},{0x801CE638,0,false},
        {0x800DAB24,39,false},{0x800DAB24,46,false},{0x800D8170,0,false},
        {0x800D45E8,Base+ReducedSpan,false},{0x800D45E4,Base+4,false}
    };
    const char* reasons[]{"players=1","layout=1","phase=0","mode=39","mode=46","course=0",
        "common=802DCD18","shape=802D6804"};
    wr64::sunny_detail::set_diagnostic_sink(captureDiagnostic);
    unsigned reason=0;
    for(const auto& edit:edits) {
        scenario="visual rejection "+std::to_string(edit.address); ++scenarios;
        auto test=baseline;
        if(edit.half) putHalf(test.data(),edit.address,int16_t(edit.value));
        else put(test.data(),edit.address,edit.value);
        const auto before=test;
        diagnostics.clear();
        wr64_sunny_detail_visuals(test.data());
        require(wr64_sunny_detail_active(test.data())==0,"render detail gate accepted an out-of-scope view");
        requireDiagnostic("visuals-original",reasons[reason++]);
        require(test==before,"visual roots changed outside loaded two-player race");
    }
    wr64::sunny_detail::set_diagnostic_sink(nullptr);
    for(int mode=40;mode<=45;++mode) {
        scenario="resident race mode="+std::to_string(mode); ++scenarios;
        auto before=ram; put(before.data(),0x800DAB24,mode);
        auto native=before, modified=before;
        run(baseline_func_80071E70,native); run(func_80071E70,modified);
        require(wr64_sunny_detail_active(modified.data())==1,"render detail gate rejected a resident race mode");
        checkEqualOutsideRoots(native,modified,true);
    }
    scenario="return to one player native SetCourse"; ++scenarios;
    auto one=ram; put(one.data(),0x800DAB28,1); putHalf(one.data(),0x801CE60C,1);
    wr64_sunny_detail_begin_load(one.data());
    auto old=one, current=one;
    run(baseline_func_80071E70,old); run(func_80071E70,current);
    require(current==old,"one-player SetCourse differs from baseline");
    require(wr64_sunny_detail_assets(one.data(),0x800DC350)==0x800DC350,"one-player load retained stale asset latch");
}
void testAllRaceCourses() {
    constexpr uint32_t rootTables[]{0x800D5470,0x800D54A0,0x800D5530,0x800D5560,0x800D55F0,0x800D5620};
    for (uint32_t course=1; course<=8; ++course) for (bool enabled:{false,true}) {
        scenario="all-course native load course="+std::to_string(course)+" enhanced="+std::to_string(enabled); ++scenarios;
        auto ram=initial(int(course)); auto* rdram=ram.data();
        wr64::sunny_detail::set_diagnostic_sink(nullptr);
        wr64::sunny_detail::set_enabled(enabled);
        auto oldQueue=ram,newQueue=ram;
        assetCalls.clear(); run(baseline_unk_game_load,oldQueue); const auto expectedQueue=assetCalls;
        assetCalls.clear(); run(unk_game_load,newQueue);
        require(assetCalls==expectedQueue && newQueue==oldQueue,"all-course native queue/state changed");
        wr64_sunny_detail_begin_load(rdram);
        require(!RT64::wr64RTTwoPlayerAssetsReady(rdram,course),"RT inherited an earlier course's resident assets");
        const uint32_t shape=get(rdram,0x800DC514+course*4);
        const uint32_t selected=get(rdram,(enabled?0x800DC4F0:0x800DC514)+course*4);
        const uint32_t span=get(rdram,(enabled?0x800DCE3C:0x800DCE60)+course*4);
        const auto shapeBytes=independentMio(get(rdram,selected),get(rdram,selected+4));
        const auto commonBytes=independentMio(get(rdram,selected+16),get(rdram,selected+20));
        require(shapeBytes.size()<=span,"shape payload exceeds native selected span");
        require(span+commonBytes.size()<=0x30000,"full graphics exceed native course arena");
        const auto beforeShape=ram;
        transfers.clear(); run(func_80095A28,ram,shape);
        require(transfers.size()==2,"all-course shape/common DMA count");
        require(bytes(rdram,Base,shapeBytes.size())==shapeBytes,"all-course native shape decode mismatch");
        require(get(rdram,0x800D45E8)==Base+span,"all-course common placement mismatch");
        require(get(rdram,0x801CE6E8)==((Base+span)&0x1FFFFFFF),"all-course segment14 mismatch");
        require(bytes(rdram,Base+span,commonBytes.size())==commonBytes,"all-course native common decode mismatch");
        require(std::equal(ram.begin()+(DataBase&0x7FFFFF),ram.begin()+((Base+0x40000)&0x7FFFFF),
            beforeShape.begin()+(DataBase&0x7FFFFF)),"all-course shapes overwrite course-data arena");
        const uint32_t data=get(rdram,0x800DC6BC+course*4);
        require(std::find(expectedQueue.begin(),expectedQueue.end(),data)!=expectedQueue.end(),"native queue lacks course data");
        transfers.clear(); run(func_80095A28,ram,data);
        require(transfers.size()==1 && transfers[0].destination==DataBase,"all-course data moved");
        require(bytes(rdram,DataBase,get(rdram,data+4)-get(rdram,data))==
            std::vector<uint8_t>(rom.begin()+get(rdram,data),rom.begin()+get(rdram,data+4)),"all-course gameplay dataset changed");
        require(!wr64_sunny_detail_water_active(rdram),"all-course water enabled before matching texture load");
        const uint32_t texture=get(rdram,0x800DC108+course*4);
        const uint32_t textureSelected=get(rdram,(enabled?0x800DC0E4:0x800DC108)+course*4);
        const uint32_t textureBase=get(rdram,0x800D45F0);
        auto expectedTexture=bytes(rdram,textureBase,0x8400);
        for (unsigned record=0;record<7;++record) {
            const uint32_t at=textureSelected+record*16;
            require(get(rdram,at+8)==1,"unexpected texture upload flag");
            const auto decoded=independentMio(get(rdram,at),get(rdram,at+4));
            const uint32_t offset=get(rdram,at+12);
            require(offset+decoded.size()<=expectedTexture.size(),"all-course texture exceeds stock arena");
            std::copy(decoded.begin(),decoded.end(),expectedTexture.begin()+offset);
        }
        const auto textureTail=bytes(rdram,textureBase+0x8400,64);
        transfers.clear(); run(func_80095A28,ram,texture);
        require(transfers.size()==7,"all-course texture upload count changed");
        require(bytes(rdram,textureBase,0x8400)==expectedTexture,"all-course texture ordered output mismatch");
        require(bytes(rdram,textureBase+0x8400,64)==textureTail,"all-course texture overflow");
        require(bool(wr64_sunny_detail_water_active(rdram))==enabled,"all-course texture/material gate mismatch");
        require(!RT64::wr64RTTwoPlayerAssetsReady(rdram,course),"RT enabled before native visual roots were applied");
        auto native=ram,modified=ram;
        run(baseline_func_80071E70,native); run(func_80071E70,modified);
        require(RT64::wr64RTTwoPlayerAssetsReady(modified.data(),course)==enabled,
            "RT resident marker must require the completed Enhanced load for this course");
        require(!RT64::wr64RTTwoPlayerAssetsReady(rdram,course),"copied RAM inherited another native load's RT marker");
        require(bool(wr64_sunny_detail_active(modified.data()))==enabled,"all-course resident gate mismatch");
        for (size_t p=0;p<RamSize;p+=4) {
            if (std::memcmp(native.data()+p,modified.data()+p,4)==0) continue;
            require(enabled && p>=0x1C1CD0 && p<0x1C1CE8,"all-course SetCourse changed gameplay memory");
        }
        for (unsigned i=0;i<6;++i) require(get(modified.data(),0x801C1CD0+i*4)==
            (enabled?get(rdram,rootTables[i]+course*4):get(native.data(),0x801C1CD0+i*4)),"all-course visual root mismatch");
        wr64::sunny_detail::set_enabled(!enabled);
        require(RT64::wr64RTTwoPlayerAssetsReady(modified.data(),course)==enabled,
            "changing the requested setting changed loaded RT assets");
        require(bool(wr64_sunny_detail_active(modified.data()))==enabled,"all-course resident setting toggle changed assets");
        put(modified.data(),0x800D8170,course==8?1:course+1);
        require(!wr64_sunny_detail_active(modified.data()),"course transition reused another track's resident latch");
        require(!RT64::wr64RTTwoPlayerAssetsReady(modified.data(),course==8?1:course+1),
            "new course ID reused another track's resident RT marker before its load began");
        // Each track must fail closed on either table or arena disagreement.
        if(enabled) for(uint32_t address:{selected+4,textureSelected+4,0x800D45EC}) {
            auto malformed=initial(int(course));
            put(malformed.data(),address,get(malformed.data(),address)^0x10000);
            wr64::sunny_detail::set_enabled(true); wr64_sunny_detail_begin_load(malformed.data());
            require(wr64_sunny_detail_assets(malformed.data(),shape)==shape,"malformed course metadata accepted");
        }
    }
}
}
extern "C" {
void* wr64_test_address(uint8_t* rdram,uint64_t address,unsigned size,const char* file,int line) {
    ++nativeAccesses;
    const uint32_t p=uint32_t(address);
    if(p<0x80000000 || uint64_t(p)+size>0x80800000 || (p&(size-1))) {
        std::cerr<<scenario<<": native out-of-range access 0x"<<std::hex<<p<<std::dec<<" size "<<size<<" at "<<file<<':'<<line<<'\n';
        std::exit(1);
    }
    return rdram+(p-0x80000000);
}
void capture_native_asset(uint8_t*,recomp_context* ctx) { assetCalls.push_back(uint32_t(ctx->r4)); }
void func_80097F74(uint8_t* rdram,recomp_context* ctx) {
    transfers.push_back({uint32_t(ctx->r4),uint32_t(ctx->r5),uint32_t(ctx->r6)});
    copyBytes(rdram,uint32_t(ctx->r5),rom,uint32_t(ctx->r4),uint32_t(ctx->r6));
}
void osVirtualToPhysical_recomp(uint8_t*,recomp_context* ctx) { ctx->r2=uint32_t(ctx->r4)&0x1FFFFFFF; }
void osWritebackDCacheAll_recomp(uint8_t*,recomp_context*) {}
void func_80095CE8(uint8_t*,recomp_context*) { require(false,"unexpected flag-4 bank relocation in shape fixture"); }
void func_80096048(uint8_t*,recomp_context*) { require(false,"unexpected flag-7 bank relocation in shape fixture"); }
void func_80096694(uint8_t*,recomp_context*) { require(false,"unexpected flag-10 bank relocation in shape fixture"); }
void func_80093F78(uint8_t*,recomp_context* ctx) { ctx->r2=ctx->r4; }
void func_80093DBC(uint8_t*,recomp_context* ctx) { ctx->r2=ctx->r4; }
void do_break(uint32_t) { require(false,"native break"); }
void switch_error(const char*,uint32_t,uint32_t) { require(false,"native switch dispatch"); }
}
int main(int argc,char** argv) {
    require(argc==2,"pass the private USA Rev1 ROM");
    std::ifstream input(argv[1],std::ios::binary);
    require(bool(input),"cannot open private ROM");
    rom.assign(std::istreambuf_iterator<char>(input),{});
    require(rom.size()>=0x800000 && be32(rom,0)==0x80371240,"invalid native ROM image");
    testQueue(); testLoader(false); testLoader(true);
    testScopeAndLifecycle(); testRejectedAssets(); testVisualScope();
    testAllRaceCourses();
    std::cout<<"PASS "<<scenarios<<" scenarios, "<<assertions<<" assertions, "<<nativeAccesses
        <<" checked native memory accesses; no game, GPU, profiles or files modified.\n";
}

