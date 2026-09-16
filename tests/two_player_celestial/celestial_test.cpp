#include "recomp.h"
#include "wr64_two_player_celestial.hpp"
#include "wr64_two_player_celestial_draw.h"
#include "common/rt64_wr64_rt_celestial.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

extern "C" {
void baseline_func_80089E24(uint8_t*,recomp_context*);
void baseline_func_80089F28(uint8_t*,recomp_context*);
void baseline_func_80089C08(uint8_t*,recomp_context*);
void baseline_func_80089DEC(uint8_t*,recomp_context*);
void func_8008D94C(uint8_t*,recomp_context*);
void func_8008CFEC(uint8_t*,recomp_context*);
void func_8008D454(uint8_t*,recomp_context*);
void func_8008BD2C(uint8_t*,recomp_context*);
void func_80051538(uint8_t*,recomp_context*);
void baseline_func_80051538(uint8_t*,recomp_context*);
}
namespace {
using Ram=std::vector<uint8_t>;
constexpr uint32_t Records=0x1C4170, RecordBytes=0x288, Stack=0x807FF000, Pool=0x80300000;
unsigned checks=0,scenarios=0; uint64_t accesses=0;
unsigned drawScenarios=0,keptRectangles=0,clippedRectangles=0,droppedRectangles=0,washes=0;
unsigned rtBodyComparisons=0; float rtMaxCenterError=0;
using LensPair=std::array<float,2>;
bool enabled=true;
Ram rom;
void require(bool condition,const char* message) {
    ++checks;if(!condition){std::cerr<<"FAIL "<<message<<'\n';std::exit(1);}
}
void put(Ram& r,uint32_t a,uint32_t v){std::memcpy(r.data()+(a&0x7FFFFF),&v,4);}
uint32_t get(const Ram& r,uint32_t a){uint32_t v;std::memcpy(&v,r.data()+(a&0x7FFFFF),4);return v;}
void real(Ram& r,uint32_t a,float v){put(r,a,std::bit_cast<uint32_t>(v));}
void matrix(Ram& r,uint32_t address,const std::array<float,16>& values){
    auto* rdram=r.data();
    for(unsigned i=0;i<16;++i){
        const int32_t fixed=int32_t(values[i]*65536.0f);
        MEM_H(0,S32(address+i*2))=fixed>>16;
        MEM_H(0,S32(address+32+i*2))=fixed&0xFFFF;
    }
}
Ram initial(unsigned course,float yawDelta=0,float pitch=0,unsigned swap=0,
    LensPair lenses={60.0f,60.0f}){
    Ram r(0x800000);
    // Private original code/data supplies the original projection constants,
    // native angles and course tables; nothing is emitted to disk.
    for(uint32_t i=0;i<0x800EB000-0x80046800;++i)r[(0x46800+i)^3]=rom[0x1000+i];
    put(r,0x800D8170,course);put(r,0x800DAB28,2);put(r,0x800DAB2C,0);
    put(r,0x80223930,swap);put(r,0x80223934,swap^1);put(r,0x801518B8,Pool);
    for(unsigned i=0;i<4096;++i)real(r,0x80154350+i*4,float(std::sin(double(i)*6.283185307179586/4096)));
    for(unsigned p=0;p<2;++p){
        const unsigned index=p^swap;
        const float yaw=((course==0?5.0f:315.0f)+yawDelta-30.0f*p)*3.14159265358979323846f/180;
        const float cy=std::cos(yaw),sy=std::sin(yaw),cp=std::cos(pitch),sp=std::sin(pitch);
        const std::array<float,3> eye{float(p*700),41.75f,float(p*300)};
        const std::array<float,3> forward{cy*cp,sp,sy*cp},right{sy,0,-cy},up{-cy*sp,cp,-sy*sp};
        std::array<float,16> view{},projection{};
        for(unsigned i=0;i<3;++i){
            view[i*4]=right[i];view[i*4+1]=up[i];view[i*4+2]=-forward[i];
            view[12]-=eye[i]*view[i*4];view[13]-=eye[i]*view[i*4+1];view[14]-=eye[i]*view[i*4+2];
        }
        // Retain the exact original fixture at 60 degrees. The other values
        // are lens inputs only: the actual native producer independently
        // computes its celestial centers from the encoded fixed matrix below.
        const float focal=lenses[p]==60.0f?1.7320508f:
            1.0f/std::tan(lenses[p]*3.14159265358979323846f/360.0f);
        view[15]=1;projection[0]=focal/(424.0f/240.0f);projection[5]=focal;
        projection[10]=-1;projection[11]=-1;projection[14]=-2;
        matrix(r,Pool+0xE008+index*64,projection);matrix(r,Pool+0xE088+index*64,view);
        const uint32_t camera=0x80227C80+index*0x10C;
        for(unsigned i=0;i<3;++i)real(r,camera+0x4C+i*4,eye[i]);
        real(r,camera+0xF0,cy);real(r,camera+0xF4,sy);
        real(r,camera+0x80,p==0?20.0f:120.0f);
    }
    std::fill(r.begin()+Records,r.begin()+Records+RecordBytes,0x35);
    return r;
}
recomp_context context(){
    recomp_context ctx{};ctx.r29=S32(Stack);ctx.r16=0xBAAD;ctx.r4=0xCAFE;
    ctx.f2.d=123.5;return ctx;
}
void originalProject(Ram& r,unsigned course){
    auto ctx=context();ctx.f_odd=&ctx.f0.u32h;
    if(course==0||course==2){baseline_func_80089E24(r.data(),&ctx);baseline_func_80089F28(r.data(),&ctx);}
    else{baseline_func_80089C08(r.data(),&ctx);baseline_func_80089DEC(r.data(),&ctx);}
    require(uint32_t(ctx.r29)==Stack,"original native producer balances stack");
}
std::array<float,16> decodeMatrix(Ram& r,uint32_t address){
    auto* rdram=r.data();std::array<float,16> out{};
    for(unsigned i=0;i<16;++i)out[i]=float(MEM_H(0,S32(address+i*2)))+
        float(uint16_t(MEM_H(0,S32(address+32+i*2))))/65536.0f;
    return out;
}
RT64::Wr64RTCelestialSnapshot rtSnapshot(Ram& r,unsigned course){
    // Patterned IA16 alpha stands in for the loaded texture contents. Original
    // ROM data still supplies every authored angle, size, height and tint.
    std::array<uint32_t,16> segments{};segments[1]=0x80500000;segments[8]=0x80600000;
    for(const auto& texture:std::array<std::array<uint32_t,2>,3>{{
        {0x604400,1024},{0x604C00,1024},{0x5102B0,16}}})
        for(uint32_t i=0;i<texture[1];++i)r[(texture[0]+i*2+1)^3]=uint8_t(1+i%255);
    return RT64::wr64RTCelestialReadSnapshot(r.data(),r.size(),segments,course,2,true);
}
void checkRtProjection(Ram& r,unsigned course,unsigned view,
    const RT64::Wr64RTCelestialSnapshot& snapshot){
    require(snapshot.count==(course==0?1u:(course==2?2u:18u)),"Enhanced 2P RT snapshot contains authored sky bodies");
    const auto index=get(r,0x80223930+view*4);
    const auto projection=decodeMatrix(r,Pool+0xE008+index*64);
    const auto camera=decodeMatrix(r,Pool+0xE088+index*64);
    const uint32_t eyeAddress=0x80227C80+index*0x10C+0x4C;
    std::array<float,3> eye{};
    for(unsigned c=0;c<3;++c)eye[c]=std::bit_cast<float>(get(r,eyeAddress+c*4));
    for(unsigned i=0;i<snapshot.count;++i){
        const uint32_t address=(course==0||course==2)?0x801C4170:(i<16?0x801C4278+i*24:0x801C4188);
        const float x=std::bit_cast<float>(get(r,address)),y=std::bit_cast<float>(get(r,address+4));
        // Primary native culling is intentionally absent from RT; compare all
        // bodies retained by the actual per-player native producer.
        if(std::bit_cast<float>(get(r,address+20))<.5f||(x==-64.0f&&y==-64.0f))continue;
        auto one=snapshot;one.count=1;one.bodies[0]=snapshot.bodies[i];
        const auto projected=RT64::wr64RTCelestialProject(one,camera,projection,eye);
        if(projected.count!=1)std::cerr<<"course="<<course<<" view="<<view<<" body="<<i<<" x="<<x<<" y="<<y<<" offset="<<std::bit_cast<float>(get(r,address+12))<<","<<std::bit_cast<float>(get(r,address+16))<<"\n";
        require(projected.count==1,"native-visible 2P body retained by RT projection");
        const float expectedX=x+std::bit_cast<float>(get(r,address+12));
        // Preserve the established 1P RT chart convention in this extension.
        // Native ROM has 239 here, whereas the existing RT chart uses 240;
        // its constant one-pixel bias is independent of camera or split view.
        const uint64_t nativeOriginBits=(uint64_t(get(r,0x800EAB48))<<32)|get(r,0x800EAB4C);
        const float nativeOrigin=float(std::bit_cast<double>(nativeOriginBits));
        require(nativeOrigin==239.0f,"native celestial vertical origin fixture");
        const float expectedY=y-std::bit_cast<float>(get(r,address+16))+(240.0f-nativeOrigin);
        const auto& rect=projected.records[0].rect;
        const float error=std::max(std::fabs((rect[0]+rect[2])*.5f-expectedX),
            std::fabs((rect[1]+rect[3])*.5f-expectedY));
        rtMaxCenterError=std::max(rtMaxCenterError,error);
        if(error>=.05f)std::cerr<<"course="<<course<<" view="<<view<<" body="<<i<<" native="<<expectedX<<","<<expectedY<<" rt="<<(rect[0]+rect[2])*.5f<<","<<(rect[1]+rect[3])*.5f<<" error="<<error<<"\n";
        require(error<.05f,"RT full 424x240 chart matches native per-player celestial center");
        ++rtBodyComparisons;
    }
}
void checkCase(unsigned course,float yaw,float pitch,unsigned swap,
    LensPair lenses={60.0f,60.0f}){
    ++scenarios;auto r=initial(course,yaw,pitch,swap,lenses);
    const auto snapshot=rtSnapshot(r,course);
    std::array<std::array<uint8_t,RecordBytes>,2> output{};
    for(unsigned view=0;view<2;++view){
        put(r,0x800DAB2C,view);
        const auto before=r;
        auto expected=r;put(expected,0x80223930,get(r,0x80223930+view*4));originalProject(expected,course);
        auto ctx=context();ctx.f_odd=&ctx.f0.u32h;const auto contextBefore=ctx;
        require(wr64_two_player_celestial_begin(r.data(),&ctx)==1,"eligible projection did not begin");
        require(wr64_two_player_celestial_view()==view,"wrong scoped view");
        require(std::memcmp(&ctx,&contextBefore,sizeof(ctx))==0,"projection changed caller context");
        require(get(r,0x80223930)==get(before,0x80223930)&&get(r,0x80223934)==get(before,0x80223934),"camera globals changed");
        require(std::memcmp(r.data()+Records,expected.data()+Records,RecordBytes)==0,"per-view records differ from independent native baseline");
        checkRtProjection(r,course,view,snapshot);
        require(std::equal(r.begin(),r.begin()+Records,before.begin()),"projection modified state below records");
        require(std::equal(r.begin()+Records+RecordBytes,r.begin()+((Stack-0x400)&0x7FFFFF),before.begin()+Records+RecordBytes),"projection modified world/fog state");
        std::copy_n(r.begin()+Records,RecordBytes,output[view].begin());
        require(wr64_two_player_celestial_begin(r.data(),&ctx)==0,"nested begin corrupted snapshot");
        // A draw may alter temporary native records. End must restore every
        // byte, including a scope whose output was culled or skipped.
        std::fill(r.begin()+Records,r.begin()+Records+RecordBytes,0xA5);
        wr64_two_player_celestial_end(r.data());
        require(std::memcmp(r.data()+Records,before.data()+Records,RecordBytes)==0,"shared records not restored");
        require(wr64_two_player_celestial_view()==2,"projection scope leaked");
        require(wr64_two_player_celestial_camera_address(r.data(),0x80223930)==0x80223930,"camera hook active outside scope");
        // The later lens-flare draw performs a second projection in the same
        // frame. It must reproduce this view without an extra state update.
        require(wr64_two_player_celestial_begin(r.data(),&ctx)==1,"second draw failed to begin");
        require(std::memcmp(r.data()+Records,output[view].data(),RecordBytes)==0,"second projection advanced or changed celestial state");
        wr64_two_player_celestial_end(r.data());
    }
    if(yaw==0)require(output[0]!=output[1],"different player cameras produced identical visible records");
}
void reject(Ram r){
    const auto before=r;auto ctx=context();ctx.f_odd=&ctx.f0.u32h;const auto saved=ctx;
    require(wr64_two_player_celestial_begin(r.data(),&ctx)==0,"invalid state activated celestial projection");
    require(r==before&&std::memcmp(&ctx,&saved,sizeof(ctx))==0,"rejected projection changed state");
}
using Words=std::vector<uint32_t>;
Words commands(const Ram& r,uint32_t begin,uint32_t end){
    require(end>=begin&&end-begin<0x1800&&(end&7)==0,"native celestial display-list budget");
    Words out;for(uint32_t a=begin;a<end;a+=4)out.push_back(get(r,a));return out;
}
uint32_t nativeDraw(Ram& r,uint32_t cursor,unsigned course,bool overlay){
    auto ctx=context();ctx.f_odd=&ctx.f0.u32h;ctx.r4=S32(cursor);
    if(overlay){func_8008BD2C(r.data(),&ctx);ctx.r4=ctx.r2;baseline_func_80051538(r.data(),&ctx);}
    else if(course==0||course==2)func_8008D94C(r.data(),&ctx);
    else{func_8008CFEC(r.data(),&ctx);ctx.r4=ctx.r2;func_8008D454(r.data(),&ctx);}
    require(uint32_t(ctx.r29)==Stack,"native celestial consumer stack unbalanced");return uint32_t(ctx.r2);
}
void compareMapping(const Words& raw,const Words& result,unsigned view){
    const uint32_t top=view*480,bottom=top+480;
    require(result.size()>=8,"scoped celestial scissors missing");
    require(result[0]==0xE7000000&&result[1]==0&&result[2]==(0xED000000|top)&&result[3]==(0x006A0000|bottom),"wrong opening half-scissor");
    const size_t tail=result.size()-4;
    require(result[tail]==0xE7000000&&result[tail+1]==0&&result[tail+2]==(0xED000000|top)&&result[tail+3]==(0x006A0000|bottom),"wrong restored half-scissor");
    size_t at=4;
    for(size_t i=0;i<raw.size();){
        const uint32_t op=raw[i]>>24;
        require(op!=0xE5,"unexpected flipped celestial rectangle");
        if(op==0xE4){
            require(i+6<=raw.size()&&raw[i+2]==0xB3000000&&raw[i+4]==0xB2000000,"native texture rectangle packet changed");
            const int offset=view?240:-240;
            const int lower=int(raw[i]&4095)+offset,upper=int(raw[i+1]&4095)+offset;
            const int clippedUpper=std::max(upper,int(top)),clippedLower=std::min(lower,int(bottom));
            if(clippedUpper<clippedLower){
                require(at+6<=tail,"mapped rectangle missing");
                require((result[at]&~4095u)==(raw[i]&~4095u)&&(result[at+1]&~4095u)==(raw[i+1]&~4095u),"mapping changed horizontal sprite coordinates");
                require((result[at]&4095)==unsigned(clippedLower)&&(result[at+1]&4095)==unsigned(clippedUpper),"sprite has wrong vertical offset/half clipping");
                require(result[at+2]==raw[i+2]&&result[at+4]==raw[i+4]&&result[at+5]==raw[i+5],"mapping changed sprite texture scale");
                require((result[at+3]>>16)==(raw[i+3]>>16),"mapping changed texture S");
                const int expectedT=int(int16_t(raw[i+3]))+int(std::trunc(double(clippedUpper-upper)*int16_t(raw[i+5])/128.0));
                require(uint16_t(result[at+3])==uint16_t(expectedT),"top clipping did not advance original texture T correctly");
                ++keptRectangles;if(clippedUpper!=upper||clippedLower!=lower)++clippedRectangles;at+=6;
            }else ++droppedRectangles;
            i+=6;
        }else{
            require(at+2<=tail,"native material command lost");
            if(op==0xED)require(result[at]==(0xED000000|top)&&result[at+1]==(0x006A0000|bottom),"native scissor escaped owning view");
            else require(result[at]==raw[i]&&result[at+1]==raw[i+1],"native material/color/texture command changed");
            i+=2;at+=2;
        }
    }
    require(at==tail,"unexpected extra celestial commands");
}
void checkDraw(unsigned course,uint32_t pool,float pitch,LensPair lenses={60.0f,60.0f}){
    ++drawScenarios;auto r=initial(course,0,pitch,0,lenses);
    std::memcpy(r.data()+((pool+0xE008)&0x7FFFFF),r.data()+((Pool+0xE008)&0x7FFFFF),256);
    put(r,0x801518B8,pool);put(r,0x800D47E0,0);put(r,0x800D47FC,37);
    bool previousWash=false;
    for(unsigned view=0;view<2;++view)for(bool overlay:{false,true}){
        if(overlay&&course!=0&&course!=2)continue;
        put(r,0x800DAB2C,view);const auto before=r;
        auto expected=r;put(expected,0x80223930,get(r,0x80223930+view*4));originalProject(expected,course);
        const uint32_t cursor=pool+0x1000;
        const auto nativeEnd=nativeDraw(expected,cursor,course,overlay);
        const auto raw=commands(expected,cursor,nativeEnd);
        auto ctx=context();ctx.f_odd=&ctx.f0.u32h;const auto saved=ctx;
        const uint32_t end=overlay?wr64_two_player_sun_overlay(r.data(),&ctx,cursor):wr64_two_player_celestial_draw(r.data(),&ctx,cursor);
        require(std::memcmp(&saved,&ctx,sizeof(ctx))==0,"consumer wrapper changed parent context");
        require(std::memcmp(before.data()+Records,r.data()+Records,RecordBytes)==0,"consumer leaked projected records");
        require(wr64_two_player_celestial_view()==2,"consumer leaked projection scope");
        require(get(before,0x80223930)==get(r,0x80223930)&&get(before,0x80223934)==get(r,0x80223934),"consumer changed camera globals");
        compareMapping(raw,commands(r,cursor,end),view);
        if(overlay){
            const bool visible=get(expected,0x800D47E0)!=0;
            if(visible)++washes;
            require(std::memcmp(r.data()+0xD47E0,before.data()+0xD47E0,28)==0,"per-view wash changed shared enable/color state");
            const uint32_t expectedScroll=view&&(previousWash||visible)?36:37;
            require(get(r,0x800D47FC)==expectedScroll,"wash scroll did not advance once across both views");
            previousWash=visible;
        }
        auto expectedState=before;put(expectedState,0x800D47FC,get(r,0x800D47FC));
        const uint32_t listOffset=cursor&0x7FFFFF,stackOffset=Stack&0x7FFFFF;
        require(std::equal(r.begin(),r.begin()+listOffset,expectedState.begin()),"consumer changed game state before display list");
        require(std::equal(r.begin()+listOffset+0x1820,r.begin()+stackOffset-0x400,expectedState.begin()+listOffset+0x1820),"consumer changed game state after display list");
        require(std::equal(r.begin()+stackOffset,r.end(),expectedState.begin()+stackOffset),"consumer changed state above native stack");
    }
}
void checkLensConsumers(){
    // Both equal and deliberately different lenses protect camera-slot
    // ownership: choosing player one's matrix for player two must fail even
    // when the two views share their course's authored celestial snapshot.
    for(const LensPair lenses:std::array<LensPair,6>{{
        {60.0f,70.0f},{70.0f,60.0f},{70.0f,70.0f},
        {60.0f,80.0f},{80.0f,60.0f},{80.0f,80.0f}}}){
        const unsigned firstComparison=rtBodyComparisons;
        for(unsigned course:{0u,2u,6u})
            for(float yaw:{-100.0f,0.0f,65.0f,180.0f})
                for(float pitch:{-0.2f,0.0f,0.3f})
                    for(unsigned swap:{0u,1u})checkCase(course,yaw,pitch,swap,lenses);
        require(rtBodyComparisons>firstComparison+100,
            "widened lens pair lacks native-visible RT celestial comparisons");
        for(unsigned course:{0u,2u,6u})
            for(uint32_t pool:{0x8011F8E8u,0x801388D0u})
                for(float pitch:{-0.35f,0.0f,0.4f})checkDraw(course,pool,pitch,lenses);
    }
    // Establish that these fixtures exercise a real native projection change,
    // rather than vacuously comparing the same culled records at every lens.
    auto original=initial(2);originalProject(original,2);
    for(float lens:{70.0f,80.0f}){
        auto widened=initial(2,0,0,0,{lens,lens});originalProject(widened,2);
        require(std::memcmp(original.data()+Records,widened.data()+Records,RecordBytes)!=0,
            "native celestial records did not respond to widened lens");
    }
}
void checkDrawGuards(){
    auto r=initial(2);put(r,0x801518B8,0x8011F8E8);auto ctx=context();ctx.f_odd=&ctx.f0.u32h;
    auto rejectDraw=[&](uint32_t cursor){
        const auto before=r;const auto saved=ctx;
        require(wr64_two_player_celestial_draw(r.data(),&ctx,cursor)==cursor,"body capacity/state guard failed");
        require(wr64_two_player_sun_overlay(r.data(),&ctx,cursor)==cursor,"overlay capacity/state guard failed");
        require(r==before&&std::memcmp(&saved,&ctx,sizeof(ctx))==0,"rejected celestial draw changed state");
        require(wr64_two_player_celestial_view()==2,"rejected draw leaked scope");
    };
    for(uint32_t cursor:{0x8011F8E7u,0x8011F8E9u,0x801238D0u,0x807FFFF8u})rejectDraw(cursor);
    for(unsigned players:{0u,1u,3u}){put(r,0x800DAB28,players);rejectDraw(0x801208E8);}
    put(r,0x800DAB28,2);enabled=false;rejectDraw(0x801208E8);enabled=true;
    put(r,0x800D8170,1);rejectDraw(0x801208E8);put(r,0x800D8170,2);
    put(r,0x800DAB2C,2);rejectDraw(0x801208E8);put(r,0x800DAB2C,0);
    require(!wr64_two_player_sun_skip_shared_wash(r.data()),"empty shared wash incorrectly suppressed");
    put(r,0x800D47E0,1);require(!wr64_two_player_sun_skip_shared_wash(r.data()),"transition wash incorrectly suppressed");
    put(r,0x800D47E0,2);require(wr64_two_player_sun_skip_shared_wash(r.data()),"stale global sun wash not suppressed");
}
void checkWashPairLifecycle(){
    for(unsigned disruption=0;disruption<4;++disruption){
        auto r=initial(2);uint32_t pool=0x8011F8E8;
        std::memcpy(r.data()+((pool+0xE008)&0x7FFFFF),r.data()+((Pool+0xE008)&0x7FFFFF),256);
        put(r,0x801518B8,pool);put(r,0x800D47E0,0);put(r,0x800D47FC,37);put(r,0x800E62C4,100);
        // P1 faces the sun; P2 faces away. Only a valid P1/P2 pair may carry
        // P1's visible-wash flag into P2's single scroll advance.
        real(r,0x80227C80+0x10C+0xF0,-0.7071068f);
        real(r,0x80227C80+0x10C+0xF4,0.7071068f);
        auto oracle=r;originalProject(oracle,2);nativeDraw(oracle,pool+0x1000,2,true);
        require(get(oracle,0x800D47E0)==2,"P1-only wash control is not visible");
        auto ctx=context();ctx.f_odd=&ctx.f0.u32h;
        wr64_two_player_sun_overlay(r.data(),&ctx,pool+0x1000);
        require(get(r,0x800D47FC)==37,"P1 advanced wash scroll early");
        if(disruption==1){
            const auto before=r;
            const uint32_t invalid=pool+0x5FF8;
            require(wr64_two_player_sun_overlay(r.data(),&ctx,invalid)==invalid&&r==before,"room-rejected P1 draw changed RAM");
        }
        if(disruption==2)put(r,0x800E62C4,101);
        if(disruption==3){
            pool=0x801388D0;
            std::memcpy(r.data()+((pool+0xE008)&0x7FFFFF),r.data()+((Pool+0xE008)&0x7FFFFF),256);
            put(r,0x801518B8,pool);
        }
        put(r,0x800DAB2C,1);
        wr64_two_player_sun_overlay(r.data(),&ctx,pool+0x1000);
        const uint32_t expected=disruption?37:36;
        require(get(r,0x800D47FC)==expected,"stale P1 wash flag crossed a rejected draw, frame or buffer change");
        wr64_two_player_sun_overlay(r.data(),&ctx,pool+0x1000);
        require(get(r,0x800D47FC)==expected,"consumed P1 wash flag advanced a repeated P2 draw");
    }
}
}
extern "C" uint32_t wr64_sunny_detail_active(uint8_t*){return enabled;}
// These accepted 1P enhancements reject real players==2 in production.
extern "C" float wr64_dolphin_sun_effects(uint8_t* rdram,float){require(MEM_W(0,S32(0x800DAB28))==2,"1P effects stub used outside 2P fixture");return -1;}
extern "C" uint32_t wr64_dolphin_sun_begin(uint8_t*,float,float){return 0;}
extern "C" void wr64_dolphin_sun_packet(uint8_t*,uint32_t,uint32_t){require(false,"1P native sun metadata emitted in 2P");}
extern "C" float wr64_sun_half_extension(){return 0;}
extern "C" float wr64_sun_record_window_limit(){return 1024;}
extern "C" float wr64_sun_logical_width(){return 424;}
extern "C" uint32_t wr64_sun_logical_width_bits(){return std::bit_cast<uint32_t>(424.0f);}
extern "C" int32_t wr64_sun_logical_right_edge(){return 423;}
extern "C" int32_t wr64_sun_horizontal_cull_limit(){return 552;}
extern "C" float wr64_sun_wash_edge(int32_t,float,double,uint32_t,uint32_t,int32_t){return -1;}
extern "C" uint32_t wr64_experimental_viewport_borders(){return 0;}
extern "C" void func_8008A0E0(uint8_t*,recomp_context*){require(false,"unexpected non-Sunset sun effect");}
extern "C" int32_t wr64_sun_right_exit_probe(uint32_t,int32_t,float){return 0;}
extern "C" int32_t wr64_sun_right_exit_keep(uint32_t,uint32_t){return 0;}
extern "C" int32_t wr64_sun_dolphin_exit_keep(uint32_t,uint32_t){return 0;}
extern "C" void* wr64_test_address(uint8_t* r,uint64_t address,unsigned width,const char*,int){
    ++accesses;const uint32_t a=uint32_t(address);
    require(a>=0x80000000&&a<=0x80800000-width,"native RDRAM access outside allocation");return r+(a&0x7FFFFF);
}
int main(int argc,char**argv){
    require(argc==2,"private ROM argument required");std::ifstream file(argv[1],std::ios::binary);rom.assign(std::istreambuf_iterator<char>(file),{});
    require(rom.size()==0x800000,"wrong ROM size");
    for(unsigned course:{0u,2u,6u})for(float yaw:{-100.0f,0.0f,65.0f,180.0f})for(float pitch:{-0.2f,0.0f,0.3f})for(unsigned swap:{0u,1u})checkCase(course,yaw,pitch,swap);
    for(unsigned course:{0u,2u,6u})for(uint32_t pool:{0x8011F8E8u,0x801388D0u})for(float pitch:{-0.35f,0.0f,0.4f})checkDraw(course,pool,pitch);
    checkLensConsumers();
    require(rtBodyComparisons>100,"both-player native RT celestial comparison coverage");
    std::cout<<"RT celestial comparisons "<<rtBodyComparisons<<", max center error "<<rtMaxCenterError<<" native pixels\n";
    require(keptRectangles>10&&clippedRectangles>0&&droppedRectangles>0&&washes>0,"missing visible/clipped/culled native consumer coverage");
    checkDrawGuards();
    checkWashPairLifecycle();
    auto r=initial(2);enabled=false;reject(r);enabled=true;
    for(unsigned course:{1u,3u,4u,5u,7u,8u,9u}){auto c=r;put(c,0x800D8170,course);reject(c);}
    for(unsigned players:{0u,1u,3u}){auto c=r;put(c,0x800DAB28,players);reject(c);}
    for(unsigned view:{2u,0xFFFFFFFFu}){auto c=r;put(c,0x800DAB2C,view);reject(c);}
    auto c=r;put(c,0x80223930,2);reject(c);c=r;put(c,0x801518B8,0);reject(c);
    auto ctx=context();require(!wr64_two_player_celestial_begin(nullptr,&ctx)&&!wr64_two_player_celestial_begin(r.data(),nullptr),"null arguments rejected");
    std::cout<<"PASS "<<scenarios<<" producer + "<<drawScenarios<<" consumer scenarios, "<<checks<<" assertions, "<<accesses<<" checked accesses; rectangles kept/clipped/dropped "<<keptRectangles<<'/'<<clippedRectangles<<'/'<<droppedRectangles<<" washes "<<washes<<"\n";
}
