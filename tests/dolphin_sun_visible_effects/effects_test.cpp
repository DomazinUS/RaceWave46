// Execute the native wash gate, alpha arithmetic, flare chain, and wash
// display-list producer. Synthetic records isolate visibility from rendering.
#include "recomp.h"
#include "wr64_ultrawide.hpp"
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
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <crtdbg.h>
#endif

extern "C" {
void func_8008BD2C(uint8_t*, recomp_context*);
void before_func_8008BD2C(uint8_t*, recomp_context*);
void regenerated_func_8008BD2C(uint8_t*, recomp_context*);
void func_80051538(uint8_t*, recomp_context*);
void before_func_80051538(uint8_t*, recomp_context*);
void regenerated_func_80051538(uint8_t*, recomp_context*);
}
using Function = void (*)(uint8_t*, recomp_context*);
static unsigned checks = 0, cases = 0, unchanged = 0, continued = 0, delegated = 0;
static bool borders = true;
static std::string description;
static void require(bool condition, const char* message) {
    ++checks;
    if (!condition) {
        std::cerr << message << ": " << description << '\n';
        std::exit(1);
    }
}
extern "C" uint32_t wr64_experimental_viewport_borders() { return borders; }
extern "C" void func_8008A0E0(uint8_t* rdram, recomp_context* ctx) {
    require(MEM_W(0, S32(0x800D8170)) == 7 && MEM_W(0, S32(0x801CE638)) == 21,
        "unexpected course-specific sun delegation");
    ctx->r2 = ctx->r4;
    ++delegated;
}

struct Result {
    std::array<uint32_t, 8> state{};
    std::array<uint8_t, 0x140> records{};
    std::vector<uint32_t> flares;
    std::array<uint64_t, 32> gpr{};
    bool operator==(const Result&) const = default;
    int enabled() const { return int(state[0]); }
    int alpha() const { return int(state[5] >> 16); }
};

struct Replay {
    std::vector<uint8_t> memory = std::vector<uint8_t>(8 * 1024 * 1024);
    void number(uint32_t address, float value) {
        uint8_t* rdram = memory.data();
        MEM_W(0, S32(address)) = std::bit_cast<uint32_t>(value);
    }
    void constant(uint32_t address, double value) {
        uint8_t* rdram = memory.data();
        SD(std::bit_cast<uint64_t>(value), 0, S32(address));
    }
    Replay() {
        uint8_t* rdram = memory.data();
        MEM_B(0, S32(0x800DA624)) = 150;
        MEM_B(1, S32(0x800DA624)) = 127;
        MEM_B(2, S32(0x800DA624)) = 128;
        constant(0x800EAB98, 0.7);
        // Flare sizes and record coordinates are fixture values. The native
        // producer still computes and emits every flare command itself.
        for (uint32_t p = 0x801C41A0; p < 0x801C42A0; p += 4) number(p, 4.0f);
    }
    std::vector<uint32_t> commands(uint32_t end) {
        uint8_t* rdram = memory.data();
        require(end >= 0x80500000 && end < 0x80502000 && (end & 7) == 0,
            "invalid native display-list cursor");
        std::vector<uint32_t> result;
        for (uint32_t p = 0x80500000; p < end; p += 4) result.push_back(MEM_W(0, S32(p)));
        return result;
    }
    Result run(Function function, int course, float facing, float center, float y, float height, int mode, int radius, int players = 1) {
        uint8_t* rdram = memory.data();
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r31 = S32(0x80654320);
        ctx.r4 = S32(0x80500000);
        std::memset(rdram + 0x700000 - 0x200, 0, 0x400);
        std::memset(rdram + 0x500000, 0xA5, 0x2000);
        // Nonzero sentinels expose accidental writes or stale alpha changes.
        for (int i = 0; i < 8; ++i) MEM_W(i * 4, S32(0x800D47E0)) = 0x007B0035;
        MEM_W(0, S32(0x800D47E0)) = 0;
        MEM_W(0, S32(0x800D8170)) = course;
        MEM_W(0, S32(0x800DAB28)) = players;
        MEM_W(course * 4, S32(0x800D9944)) = radius;
        MEM_W(0, S32(0x801CE638)) = mode;
        MEM_W(0, S32(0x80223930)) = 1; // Exercise selected camera stride 268.
        number(0x80227D00 + 268, height);
        const std::array<float, 6> record{center - 12, y + 12, 1, 12, 12, facing};
        for (int i = 0; i < 6; ++i) number(0x801C4170 + i * 4, record[i]);
        std::array<uint8_t, 0x140> recordsBefore{};
        std::memcpy(recordsBefore.data(), rdram + 0x1C4170, recordsBefore.size());
        function(rdram, &ctx);
        require(uint32_t(ctx.r29) == 0x80700000 && uint32_t(ctx.r31) == 0x80654320,
            "native producer failed to restore stack or return register");
        Result result;
        for (int i = 0; i < 8; ++i) result.state[i] = MEM_W(i * 4, S32(0x800D47E0));
        std::memcpy(result.records.data(), rdram + 0x1C4170, result.records.size());
        require(result.records == recordsBefore, "wash producer changed sun or flare records");
        result.flares = commands(uint32_t(ctx.r2));
        std::memcpy(result.gpr.data(), &ctx.r0, 32 * sizeof(uint64_t));
        return result;
    }
    std::vector<uint32_t> draw(Function function, const Result& result, unsigned scroll) {
        uint8_t* rdram = memory.data();
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r4 = S32(0x80500000);
        std::memset(rdram + 0x500000, 0xA5, 0x2000);
        for (int i = 0; i < 8; ++i) MEM_W(i * 4, S32(0x800D47E0)) = result.state[i];
        MEM_W(0, S32(0x800D47FC)) = scroll;
        function(rdram, &ctx);
        require(MEM_W(0, S32(0x800D47FC)) == (result.enabled() ? ((scroll - 1) & 127) : scroll),
            "native wash texture scrolling changed");
        return commands(uint32_t(ctx.r2));
    }
};

static bool effectsEnabled = false;
static uint64_t outputDigest = 14695981039346656037ull;
static void digest(const void* data, size_t size) {
    const auto* bytes = static_cast<const uint8_t*>(data);
    for (size_t i=0; i<size; ++i) { outputDigest ^= bytes[i]; outputDigest *= 1099511628211ull; }
}
static unsigned positiveFlares = 0, positiveWash = 0, lowCameraVisible = 0, outside = 0;
static float factorAt(float height) { return std::clamp((height-20.0f)/100.0f,0.0f,1.0f); }
static float coverageAt(float x, float y) {
    const float left = std::max(0.0f,x-12), right = std::min(wr64_sun_logical_width(),x+12);
    const float top = std::max(0.0f,y-12), bottom = std::min(240.0f,y+12);
    return std::max(0.0f,right-left)/24.0f * (std::max(0.0f,bottom-top)/24.0f);
}
static int nativePowerAlpha(float base, float facing, int power, float factor) {
    volatile float result = base;
    for (int i=0; i<power; ++i) result = result*facing;
    result = result*factor;
    return int(result);
}
static std::vector<uint32_t> withoutAlpha(std::vector<uint32_t> words) {
    for (size_t i=0; i+1<words.size(); i+=2)
        if ((words[i]>>24)==0xFA || (words[i]>>24)==0xFB) words[i+1] &= 0xFFFFFF00u;
    return words;
}
static std::vector<unsigned> flareAlphas(const Result& result) {
    std::vector<unsigned> values;
    for (size_t i=0;i+1<result.flares.size();i+=2)
        if ((result.flares[i]>>24)==0xFA) values.push_back(result.flares[i+1]&255u);
    return values;
}
static Result compareEffects(Replay& replay, int course, int players, int phase,
    float facing, float x, float y, float height, int radius=12) {
    description = "width="+std::to_string(wr64_sun_logical_width())+" course="+std::to_string(course)+
        " players="+std::to_string(players)+" phase="+std::to_string(phase)+" facing="+std::to_string(facing)+
        " x="+std::to_string(x)+" y="+std::to_string(y)+" height="+std::to_string(height);
    const auto before=replay.run(before_func_8008BD2C,course,facing,x,y,height,phase,radius,players);
    const auto after=replay.run(func_8008BD2C,course,facing,x,y,height,phase,radius,players);
    const auto regenerated=replay.run(regenerated_func_8008BD2C,course,facing,x,y,height,phase,radius,players);
    digest(after.state.data(),sizeof(after.state));
    digest(after.records.data(),sizeof(after.records));
    digest(after.gpr.data(),sizeof(after.gpr));
    digest(after.flares.data(),after.flares.size()*sizeof(uint32_t));
    require(after==regenerated,"durable native hook recipe differs from checked-in source");
    const bool admitted=effectsEnabled && course==0 && players==1 && phase==1 && radius==12 &&
        facing>=0 && facing<=1 && x>=-128 && x<=4096 && y>=-128 && y<240;
    if (!admitted) {
        require(after==before,"effects adjustment changed explicit opt-out or unrelated scene");
        ++unchanged;
    }
    else {
        const float expectedFactor=std::max(factorAt(height),0.35f)*coverageAt(x,y);
        require(std::abs(wr64_dolphin_sun_effects(replay.memory.data(),factorAt(height))-expectedFactor)<0.000001f,
            "effective factor differs from visible XY overlap");
        require(after.records==before.records,"projected disk or flare records changed");
        require(withoutAlpha(after.flares)==withoutAlpha(before.flares),"native flare command, RGB, texture, position or UV changed");
        for (int i : {1,6,7}) require(after.state[i]==before.state[i],"unrelated wash state changed");
        for (int i : {2,3,4,5}) require((after.state[i]&65535)==(before.state[i]&65535),"bytes beside wash fields changed");
        require(bool(after.enabled())==(facing>0 && expectedFactor>0),"wash cutoff does not follow visible native disk");
        if (after.enabled()) {
            const int expectedAlpha=nativePowerAlpha(150,facing,4,expectedFactor);
            require(after.alpha()==expectedAlpha,"actual wash arithmetic not native facing^4 times single XY factor");
            require((after.state[2]>>16)==245 && (after.state[3]>>16)==255 && (after.state[4]>>16)==215,"native wash RGB changed");
            if (after.alpha()>0) ++positiveWash;
        }
        const auto alphas=flareAlphas(after);
        for (unsigned alpha:alphas) {
            require(alpha==unsigned(nativePowerAlpha(160,facing,2,expectedFactor)),"actual flare prim alpha not native facing^2 factor");
            if (alpha) ++positiveFlares;
        }
        if (expectedFactor==0) {
            require(!after.enabled(),"fully invisible disk retains screen wash");
            require(std::all_of(alphas.begin(),alphas.end(),[](unsigned a){return a==0;}),"fully invisible disk retains positive flare alpha");
            ++outside;
        }
        if (height<=20 && facing>=0.8f && (y==0 || y==-4) && x==wr64_sun_logical_width()/2) {
            require(after.enabled() && after.alpha()>0,"low-camera partly visible disk has no positive wash");
            require(!alphas.empty() && std::any_of(alphas.begin(),alphas.end(),[](unsigned a){return a>0;}),"low-camera partly visible disk has no actual positive flare prim alpha");
            ++lowCameraVisible;
        }
        if (factorAt(height)==1 && coverageAt(x,y)==1 && facing>0.7f)
            require(after==before,"fully visible native factor one changed its native results");
    }
    for (bool borderMode : {false,true}) {
        borders=borderMode;
        const auto nativeDraw=replay.draw(before_func_80051538,after,63);
        const auto checkedDraw=replay.draw(func_80051538,after,63);
        const auto regeneratedDraw=replay.draw(regenerated_func_80051538,after,63);
        require(nativeDraw==checkedDraw && checkedDraw==regeneratedDraw,"screen-wash packet geometry, UV, colors or state implementation changed");
        if (!after.enabled()) require(checkedDraw.empty(),"disabled screen wash emits a packet");
    }
    ++cases;
    return after;
}

int main(int argc,char**argv) {
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX|SEM_NOOPENFILEERRORBOX);
    _set_error_mode(_OUT_TO_STDERR);
    for (int type:{_CRT_WARN,_CRT_ERROR,_CRT_ASSERT}) {
        _CrtSetReportMode(type,_CRTDBG_MODE_FILE); _CrtSetReportFile(type,_CRTDBG_FILE_STDERR);
    }
#endif
    require(argc==2,"expected gate mode argument");
    effectsEnabled=std::string(argv[1])=="enabled" || std::string(argv[1])=="default";
    Replay replay;
    for (float aspect:{4.0f/3,16.0f/9,21.0f/9,32.0f/9}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        const float width=wr64_sun_logical_width();
        for (float height:{0.0f,20.0f,30.0f,70.0f,120.0f,200.0f})
            for (float facing:{0.0f,0.49f,0.69f,0.8f,1.0f})
                for (float y:{-13.0f,-12.0f,-4.0f,0.0f,4.0f,12.0f,70.0f,235.0f})
                    compareEffects(replay,0,1,1,facing,width/2,y,height);
        for (float x:{-12.0f,-4.0f,0.0f,4.0f,width-4,width,width+4,width+12})
            for (float y:{-12.0f,-4.0f,0.0f,12.0f})
                compareEffects(replay,0,1,1,0.69f,x,y,120);
        // Other courses, native opening phases, and two-player versions.
        for (int course=0;course<9;++course) for (int players:{1,2}) for (int phase:{0,1,2})
            for (float y:{-4.0f,40.0f}) for (float height:{0.0f,120.0f})
                compareEffects(replay,course,players,phase,0.8f,width/2,y,height,course?24:12);
        for (float facing:{-1.0f,-0.25f,1.25f})
            compareEffects(replay,0,1,1,facing,width/2,0,0);
        for (float y:{-129.0f,240.0f}) compareEffects(replay,0,1,1,.8f,width/2,y,20);
        compareEffects(replay,0,1,1,.8f,width/2,0,20,24);
        if (effectsEnabled) {
            const auto diagonal=compareEffects(replay,0,1,1,.69f,width+4,-4,120);
            require(diagonal.enabled() && diagonal.alpha()==3,"diagonal corner applies coverage twice or loses native wash alpha=3");
            int priorWash=256, priorFlare=256;
            for(int quarter=64;quarter>=-64;--quarter) {
                const auto state=compareEffects(replay,0,1,1,.8f,width/2,quarter*.25f,0);
                const int wash=state.enabled()?state.alpha():0;
                const auto alphas=flareAlphas(state);
                const int flare=alphas.empty()?0:*std::max_element(alphas.begin(),alphas.end());
                require(wash<=priorWash && flare<=priorFlare,"visible effects brighten while exiting the top");
                priorWash=wash; priorFlare=flare;
            }
            require(priorWash==0 && priorFlare==0,"top exit does not end at zero");
            priorWash=0; priorFlare=0;
            for(int quarter=-64;quarter<=64;++quarter) {
                const auto state=compareEffects(replay,0,1,1,.8f,width/2,quarter*.25f,0);
                const int wash=state.enabled()?state.alpha():0;
                const auto alphas=flareAlphas(state);
                const int flare=alphas.empty()?0:*std::max_element(alphas.begin(),alphas.end());
                require(wash>=priorWash && flare>=priorFlare,"visible effects dim while reentering from the top");
                priorWash=wash; priorFlare=flare;
            }
            require(priorWash>0 && priorFlare>0,"top entry does not restore positive effects");
        }
    }
    if(effectsEnabled) require(lowCameraVisible>=16 && positiveWash>100 && positiveFlares>100 && outside>100,"insufficient native visible-effect coverage");
    std::cout<<"PASS "<<(effectsEnabled ? "enabled" : argv[1])<<": "<<cases<<" actual native replay cases, "<<unchanged<<" exact protected/default comparisons, "
        <<positiveFlares<<" positive native flare packets, "<<positiveWash<<" positive washes, "<<lowCameraVisible
        <<" low-camera partial-disk positive cases, "<<outside<<" outside-disk zero cases, "<<checks<<" checks; output digest "<<std::hex<<outputDigest<<".\n";
}

