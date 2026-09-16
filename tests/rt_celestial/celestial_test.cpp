#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif
#include "recomp.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include "common/rt64_wr64_rt_celestial.h"
#include <algorithm>
#include <bit>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

extern "C" void func_8008962C(uint8_t *, recomp_context *);
extern "C" float wr64_sun_half_extension() { return 0.0f; }
extern "C" float wr64_sun_record_window_limit() { return 1000000.0f; }
static std::array<float,16> view{}, projection{};
static unsigned checks = 0;
static void require(bool condition, const char *message) {
    checks++;
    if (!condition) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
extern "C" void SysUtils_MtxToMtxF(uint8_t *rdram, recomp_context *ctx) {
    require(uint32_t(ctx->r4) == 0x8040E008 || uint32_t(ctx->r4) == 0x8040E088, "native matrix address");
    const auto &matrix = uint32_t(ctx->r4) == 0x8040E008 ? projection : view;
    for (uint32_t i=0;i<16;i++) { MEM_W(i*4,ctx->r5) = std::bit_cast<uint32_t>(matrix[i]); }
}
struct Fixture {
    std::vector<uint8_t> ram = std::vector<uint8_t>(0x800000);
    std::array<uint32_t,16> segments{};
    void word(uint32_t address,uint32_t value) { std::memcpy(ram.data()+(address&0x7fffff),&value,4); }
    void real(uint32_t address,float value) { word(address,std::bit_cast<uint32_t>(value)); }
    void dbl(uint32_t address,double value) {
        const uint64_t bits = std::bit_cast<uint64_t>(value); word(address,uint32_t(bits>>32)); word(address+4,uint32_t(bits));
    }
    float get(uint32_t address) const { float value=0;std::memcpy(&value,ram.data()+(address&0x7fffff),4);return value; }
    Fixture() {
        word(0x801518B8,0x80400000);
        for (uint32_t i=0;i<4096;i++) { real(0x80154350+i*4,float(std::sin(double(i)*6.283185307179586/4096.0))); }
        for(uint32_t a:{0x800EAAF0U,0x800EAAF8U,0x800EAB00U}) { dbl(a,1000); }
        dbl(0x800EAB08,.001);dbl(0x800EAB10,-.001);dbl(0x800EAB18,.001);
        dbl(0x800EAB20,1000000);dbl(0x800EAB28,-1000000);dbl(0x800EAB30,-1000000);
        dbl(0x800EAB38,0);dbl(0x800EAB40,0);dbl(0x800EAB48,240);
        const std::array<float,8> angles{157.5f,202.5f,257.5f,292.5f,315,337.5f,315,315};
        for(uint32_t i=0;i<angles.size();i++) { real(0x800EAB6C+i*4,angles[i]); }
        word(0x800D9924,120);word(0x800D992C,15);word(0x800D9944,12);word(0x800D994C,24);
        for(uint32_t i=0;i<16;i++) {
            word(0x800DA628+i*4,i%2);
            for(uint32_t c=0;c<4;c++) { word(0x800DA6A8+i*16+c*4,20+i*4+c); }
        }
        segments[1]=0x10000;segments[8]=0x300000;
        for(const auto &texture:std::array<std::array<uint32_t,3>,3>{{{0x304400,1024,0},{0x304C00,1024,73},{0x202B0,16,91}}}) {
            for(uint32_t i=0;i<texture[1];i++) {
                ram[(texture[0]+i*2)^3]=uint8_t(i^0xab);
                ram[(texture[0]+i*2+1)^3]=uint8_t(i+texture[2]);
            }
        }
    }
};
static void camera(float yaw,float pitch,float roll,const std::array<float,3>& eye) {
    const float cy=std::cos(yaw),sy=std::sin(yaw),cp=std::cos(pitch),sp=std::sin(pitch),cr=std::cos(roll),sr=std::sin(roll);
    const std::array<float,3> forward{cy*cp,sp,sy*cp},right{sy,0,-cy},up{-cy*sp,cp,-sy*sp};
    view.fill(0);
    for(uint32_t i=0;i<3;i++) {
        view[i*4]=right[i]*cr+up[i]*sr;view[i*4+1]=up[i]*cr-right[i]*sr;view[i*4+2]=-forward[i];
        view[12]-=eye[i]*view[i*4];view[13]-=eye[i]*view[i*4+1];view[14]-=eye[i]*view[i*4+2];
    }
    view[15]=1;
    projection.fill(0);projection[0]=1.7320508f/(424.0f/240.0f);projection[5]=1.7320508f;
    projection[10]=-1;projection[11]=-1;projection[14]=-2;
}
int main() {
    Fixture fixture;
    using namespace RT64;
    const auto sunset=wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,2,1);
    const auto dolphin=wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,0,1);
    const auto twilight=wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,6,1);
    require(sunset.count==2&&dolphin.count==1&&twilight.count==18,"native body counts");
    require(sunset.bodies[0].texture==1&&sunset.bodies[1].texture==0,"glow then disk");
    require(twilight.bodies[16].texture==0&&twilight.bodies[17].texture==0,"both moon passes retained");
    require(twilight.bodies[16].color[3]==110/255.0f&&twilight.bodies[17].color[3]==1,"moon native alpha");
    // Native RSP setSegment keeps raw KSEG addresses. Actual archived sky
    // commands bind segment8=80316800 while the native RAM table has00316800.
    // Both cached/uncached aliases must resolve to the identical texture bytes.
    for(uint32_t alias:{0x80000000U,0xa0000000U}) {
        auto rawSegments=fixture.segments;rawSegments[1]|=alias;rawSegments[8]|=alias;
        for(uint32_t course:{0U,2U,6U}) {
            const auto physical=wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,course,1);
            const auto raw=wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),rawSegments,course,1);
            require(raw.count==physical.count&&raw.count>0,"raw KSEG segment bindings preserve native celestial bodies");
            require(raw.alphaWords==physical.alphaWords,"raw KSEG and physical aliases yield identical native alpha atlas");
            for(uint32_t i=0;i<raw.count;i++) {
                require(raw.bodies[i].cosAzimuth==physical.bodies[i].cosAzimuth&&
                    raw.bodies[i].sinAzimuth==physical.bodies[i].sinAzimuth&&
                    raw.bodies[i].color==physical.bodies[i].color&&raw.bodies[i].texture==physical.bodies[i].texture,
                    "raw KSEG bindings preserve original body identity and colors");
            }
        }
    }
    for(uint32_t i=0;i<16;i++) {
        require(twilight.bodies[i].halfWidth==(i%2?2.0f:1.0f),"native star size table");
        require(twilight.bodies[i].texelStep==(i%2?1.0f:2.0f),"native star texture step");
        for(uint32_t c=0;c<4;c++) { require(twilight.bodies[i].color[c]==float(20+i*4+c)/255.0f,"native per-star tint"); }
    }
    const uint32_t unusualIndex=uint32_t((257.5f/360.0f)*4096.0f)&0xfff;
    require(twilight.bodies[11].sinAzimuth==fixture.get(0x80154350+unusualIndex*4),"native nonuniform star azimuth");
    require(dolphin.bodies[0].texelStep*24==31.96875f&&sunset.bodies[0].texelStep*48==31.25f,"native endpoint quantization");
    for(uint32_t i=0;i<2064;i++) {
        const uint8_t actual=uint8_t((i<2048?sunset:twilight).alphaWords[i/4]>>((i%4)*8));
        const uint8_t expected=i<1024?uint8_t(i):i<2048?uint8_t(i-1024+73):uint8_t(i-2048+91);
        require(actual==expected,"native IA alpha byte endian and slot packing");
    }
    require(wr64RTCelestialReadSnapshot(nullptr,0x800000,fixture.segments,2,1).count==0,"null RAM rejected");
    require(wr64RTCelestialReadSnapshot(fixture.ram.data(),0x7fffff,fixture.segments,2,1).count==0,"truncated RAM rejected");
    for(uint32_t c:{1U,3U,4U,5U,7U,8U,9U,UINT32_MAX}) {
        require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,c,1).count==0,"course scope");
    }
    require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,2,2).count==0,"two player scope defaults to native");
    for(uint32_t course:{2U,6U}) {
        const auto one=wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,course,1);
        const auto two=wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,course,2,true);
        require(two.count==one.count&&two.count>0&&two.alphaWords==one.alphaWords&&
            two.constrainForward==one.constrainForward,"Enhanced 2P retains the full original sky snapshot and alpha atlas");
        for(uint32_t i=0;i<one.count;++i) {
            const auto& a=one.bodies[i];const auto& b=two.bodies[i];
            require(a.cosAzimuth==b.cosAzimuth&&a.sinAzimuth==b.sinAzimuth&&a.heightPixels==b.heightPixels&&
                a.radius==b.radius&&a.halfWidth==b.halfWidth&&a.halfHeight==b.halfHeight&&
                a.texelStep==b.texelStep&&a.color==b.color&&a.texture==b.texture,
                "both views share authored bodies without camera-dependent projected records");
        }
    }
    for(uint32_t course:{0U,1U,3U,4U,5U,7U,8U,9U,UINT32_MAX}) {
        require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,course,2,true).count==0,
            "Enhanced 2P celestial snapshots stay limited to restored Sunset and Twilight systems");
    }
    for(uint32_t players:{0U,3U,4U,UINT32_MAX}) {
        require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),fixture.segments,2,players,true).count==0,
            "Enhanced flag never admits unsupported player counts");
    }
    auto badSegments=fixture.segments;badSegments[8]=UINT32_MAX-64;
    require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),badSegments,2,1).count==0,"segment overflow rejected");
    badSegments[8]=0;
    require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),badSegments,2,1).count==0,"missing segment rejected");
    badSegments=fixture.segments;badSegments[8]++;
    require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),badSegments,2,1).count==0,"misaligned IA segment rejected");
    for(uint32_t alias:{0U,0x80000000U,0xa0000000U}) {
        badSegments=fixture.segments;badSegments[8]=alias|0x7fb800;
        require(wr64RTCelestialReadSnapshot(fixture.ram.data(),fixture.ram.size(),badSegments,2,1).count==0,
            "aliased texture crossing end of eight MiB RAM rejected after normalization");
    }
    // A target viewport may widen its primary projection, but the private
    // celestial chart must keep the native projection. Reconstruct identical
    // physical directions through three different viewport/projection pairs.
    camera(315*3.14159265358979323846f/180,0,0,{0,0,0});
    const auto nativeProjection=projection;
    const auto nativeChart=wr64RTCelestialProject(sunset,view,nativeProjection,{0,0,0});
    require(nativeChart.count==2,"aspect fixture has native sun layers");
    const auto &nativeRect=nativeChart.records[1].rect;
    const float centerX=(nativeRect[0]+nativeRect[2])*.5f,centerY=(nativeRect[1]+nativeRect[3])*.5f;
    auto chartPoint=[](const Wr64RTCelestialProjection &chart,const std::array<float,3>& ray) {
        std::array<float,3> homogeneous{};
        for(uint32_t row=0;row<3;row++)for(uint32_t c=0;c<3;c++)homogeneous[row]+=chart.projectionRows[row][c]*ray[c];
        return std::array<float,2>{homogeneous[0]/homogeneous[2],homogeneous[1]/homogeneous[2]};
    };
    unsigned enlargedControls=0;
    for(float aspect:{16.0f/9.0f,21.0f/9.0f,32.0f/9.0f}) {
        auto targetProjection=nativeProjection;
        targetProjection[0]/=aspect/(424.0f/240.0f);
        const float targetHeight=1080,targetWidth=targetHeight*aspect;
        const auto fixed=wr64RTCelestialProject(sunset,view,nativeProjection,{0,0,0});
        const auto wrong=wr64RTCelestialProject(sunset,view,targetProjection,{0,0,0});
        for(float fraction:{-.9f,.9f,1.1f}) {
            const float px=centerX+fraction*24,py=centerY;
            const float cameraX=(px/212.0f-1)/nativeProjection[0];
            const float cameraY=(1-py/120.0f)/nativeProjection[5];
            const float displayX=(cameraX*targetProjection[0]+1)*targetWidth*.5f;
            const float displayY=(1-cameraY*targetProjection[5])*targetHeight*.5f;
            const float recoveredX=(displayX/(targetWidth*.5f)-1)/targetProjection[0];
            const float recoveredY=(1-displayY/(targetHeight*.5f))/targetProjection[5];
            std::array<float,3> ray{};
            for(uint32_t c=0;c<3;c++) { ray[c]=view[c*4]*recoveredX+view[c*4+1]*recoveredY-view[c*4+2]; }
            const auto point=chartPoint(fixed,ray);
            require(std::fabs(point[0]-px)<.0001f&&std::fabs(point[1]-py)<.0001f,"16:9/21:9/32:9 preserve physical chart directions");
            const bool inside=point[0]>=nativeRect[0]&&point[0]<nativeRect[2]&&point[1]>=nativeRect[1]&&point[1]<nativeRect[3];
            require(inside==(std::fabs(fraction)<1),"same angular sun footprint at every target aspect");
            if(fraction>1&&aspect>2) {
                const auto wrongPoint=chartPoint(wrong,ray);
                const bool wrongInside=wrongPoint[0]>=wrong.records[1].rect[0]&&wrongPoint[0]<wrong.records[1].rect[2];
                require(wrongInside,"negative control exposes adjusted-projection horizontal stretching");
                enlargedControls++;
            }
        }
    }
    require(enlargedControls==2,"both ultrawide negative controls exercised");
    float maxError=0;unsigned cases=0,offscreen=0;
    for(bool constrain:{false,true}) for(float angle:{5.0f,22.5f,135.0f,257.5f,315.0f})
        for(float yawOffset:{-1.2f,-.5f,0.0f,.7f,1.3f}) for(float pitch:{-.3f,0.0f,.4f})
        for(float roll:{-.2f,0.0f,.3f}) for(float translation:{0.0f,4250.0f}) {
            const float radians=angle*3.14159265358979323846f/180.0f;
            const float yaw=radians+yawOffset;
            const std::array<float,3> eye{translation,41.75f,translation*.7f};
            camera(yaw,pitch,roll,eye);
            const uint32_t index=uint32_t((angle/360.0f)*4096.0f)&0xfff;
            Wr64RTCelestialSnapshot input;
            input.count=1;input.constrainForward=constrain;
            auto& body=input.bodies[0];body.cosAzimuth=fixture.get(0x80154350+((index+1024)&0xfff)*4);
            body.sinAzimuth=fixture.get(0x80154350+index*4);body.heightPixels=90;
            body.halfWidth=body.halfHeight=12;body.texelStep=1.5f;
            const auto actual=wr64RTCelestialProject(input,view,projection,eye);
            uint8_t *rdram=fixture.ram.data();
            fixture.word(0x800D8170,constrain?2:0);
            fixture.real(0x80227D70,std::cos(yaw));fixture.real(0x80227D74,std::sin(yaw));
            for(uint32_t c=0;c<3;c++) { fixture.real(0x80227CCC+c*4,eye[c]); }
            recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;ctx.r29=static_cast<gpr>(S32(0x80700000));ctx.r7=static_cast<gpr>(S32(0x801C4170));
            ctx.r6=std::bit_cast<uint32_t>(body.heightPixels);ctx.f12.fl=body.radius;ctx.f14.fl=angle;
            func_8008962C(rdram,&ctx);
            require(actual.count==1,"front hemisphere retained including primary offscreen positions");
            const float expectedX=fixture.get(0x801C4170)+fixture.get(0x801C417C);
            const float expectedY=fixture.get(0x801C4174)-fixture.get(0x801C4180);
            const float actualX=(actual.records[0].rect[0]+actual.records[0].rect[2])*.5f;
            const float actualY=(actual.records[0].rect[1]+actual.records[0].rect[3])*.5f;
            const float error=std::max(std::fabs(expectedX-actualX),std::fabs(expectedY-actualY));
            maxError=std::max(maxError,error);require(error<.01f,"independent native projection agrees within .01 pixel");
            offscreen+=expectedX<0||expectedX>424||expectedY<0||expectedY>240;cases++;
            // Rows use directions: eye translation must cancel from lookup.
            const std::array<float,4> ray{std::cos(yaw),0,std::sin(yaw),0};
            std::array<float,3> chart{};
            for(uint32_t row=0;row<3;row++)for(uint32_t c=0;c<4;c++)chart[row]+=actual.projectionRows[row][c]*ray[c];
            require(chart[2]>0&&std::isfinite(chart[0]/chart[2])&&std::isfinite(chart[1]/chart[2]),"finite directional chart rows");
        }
    require(offscreen>100,"unculled native offscreen coverage exercised");
    camera(315*3.14159265358979323846f/180,0,0,{0,0,0});
    auto invalid=sunset;invalid.count=21;
    require(wr64RTCelestialProject(invalid,view,projection,{0,0,0}).count==0,"oversized body count rejected");
    auto badView=view;badView[0]=std::numeric_limits<float>::quiet_NaN();
    require(wr64RTCelestialProject(sunset,badView,projection,{0,0,0}).count==0,"NaN view rejected");
    auto badProjection=projection;badProjection[5]=std::numeric_limits<float>::infinity();
    require(wr64RTCelestialProject(sunset,view,badProjection,{0,0,0}).count==0,"infinite projection rejected");
    require(wr64RTCelestialProject(sunset,view,projection,{0,std::numeric_limits<float>::quiet_NaN(),0}).count==0,"nonfinite eye rejected");
    badView=view;badView[2]=badView[10]=0;
    require(wr64RTCelestialProject(sunset,badView,projection,{0,0,0}).count==0,"undefined horizontal camera rejected");
    for(unsigned kind=0;kind<6;kind++) {
        invalid=sunset;
        for(auto &body:invalid.bodies) {
            if(kind==0)body.halfWidth=0;
            if(kind==1)body.halfHeight=std::numeric_limits<float>::infinity();
            if(kind==2)body.texelStep=0;
            if(kind==3)body.texture=3;
            if(kind==4)body.color[0]=std::numeric_limits<float>::quiet_NaN();
            if(kind==5)body.heightPixels=std::numeric_limits<float>::quiet_NaN();
        }
        require(wr64RTCelestialProject(invalid,view,projection,{0,0,0}).count==0,"invalid body rejected");
    }
    camera(135*3.14159265358979323846f/180,0,0,{0,0,0});
    require(wr64RTCelestialProject(sunset,view,projection,{0,0,0}).count==0,"rear hemisphere rejected");
    std::cout<<"PASS "<<checks<<" checks; "<<cases<<" independent native camera cases, "<<offscreen
        <<" offscreen; max center error "<<maxError<<" native pixels.\n";
}
