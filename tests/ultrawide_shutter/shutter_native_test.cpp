// Execute the USA producers against a user-supplied ROM in isolated memory.
// No game, graphics device, profile, save file, or ROM output is created.
#include "recomp.h"
#include "common/rt64_wr64_shutter.h"
#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <set>
#include <stdexcept>
#include <vector>

extern "C" {
void SysUtils_TaylorSeries(uint8_t*,recomp_context*);
void FadeTransition_SetProps(uint8_t*,recomp_context*);
void func_801E74BC(uint8_t*,recomp_context*);
void func_801E76C0(uint8_t*,recomp_context*);
void func_801E7908(uint8_t*,recomp_context*);
void func_800C37F4(uint8_t*,recomp_context*) {} // Sound has no bearing on the transition.
void func_801E7C58(uint8_t*,recomp_context*) { std::abort(); } // Non-shutter fade path.
void switch_error(const char*,uint32_t,uint32_t) { std::abort(); }
}

static unsigned checks=0;
static void require(bool value,const char* reason) {
    ++checks;
    if(!value) throw std::runtime_error(reason);
}
static std::vector<uint8_t> readFile(const char* path) {
    std::ifstream input(path,std::ios::binary);
    require(bool(input),"input file could not be opened");
    return {std::istreambuf_iterator<char>(input),{}};
}
static uint32_t be(const std::vector<uint8_t>& bytes,size_t offset,size_t count) {
    require(offset+count<=bytes.size(),"ROM/IPS read bounds");
    uint32_t result=0;
    while(count--) result=(result<<8)|bytes[offset++];
    return result;
}
static void applyIps(std::vector<uint8_t>& rom,const std::vector<uint8_t>& ips) {
    require(ips.size()>8 && std::equal(ips.begin(),ips.begin()+5,"PATCH"),"IPS signature");
    size_t cursor=5;
    for(;;) {
        uint32_t offset=be(ips,cursor,3);cursor+=3;
        if(offset==0x454F46) break;
        uint32_t count=be(ips,cursor,2);cursor+=2;
        if(count) {
            require(cursor+count<=ips.size(),"IPS data bounds");
            if(offset+count>rom.size()) rom.resize(offset+count);
            std::copy_n(ips.begin()+cursor,count,rom.begin()+offset);cursor+=count;
        } else {
            count=be(ips,cursor,2);cursor+=2;
            const uint8_t value=uint8_t(be(ips,cursor++,1));
            if(offset+count>rom.size()) rom.resize(offset+count);
            std::fill_n(rom.begin()+offset,count,value);
        }
    }
}
struct Matrix { double a[4][4]{}; };
static Matrix readMatrix(uint8_t* rdram,int32_t address) {
    Matrix result;
    for(int i=0;i<16;++i) {
        const int32_t hi=MEM_H(i*2,address);
        const uint32_t lo=MEM_HU(32+i*2,address);
        result.a[i/4][i%4]=double(hi)+double(lo)/65536.0;
    }
    return result;
}
static Matrix interpolate(const Matrix& from,const Matrix& to,double weight) {
    Matrix result;
    for(int i=0;i<4;++i) for(int j=0;j<4;++j)
        result.a[i][j]=from.a[i][j]+(to.a[i][j]-from.a[i][j])*weight;
    return result;
}
static double clipX(double x,double y,const Matrix& model,const Matrix& projection) {
    double input[4]={x,y,0,1},world[4]={},clip[4]={};
    for(int j=0;j<4;++j) for(int i=0;i<4;++i) world[j]+=input[i]*model.a[i][j];
    for(int j=0;j<4;++j) for(int i=0;i<4;++i) clip[j]+=world[i]*projection.a[i][j];
    require(std::isfinite(clip[0]) && clip[3]>0,"finite front-facing native projection");
    return clip[0]/clip[3];
}
static double outputX(double x,double y,const Matrix& model,const Matrix& projection,
                      double width,bool fixed) {
    const float expansion=float(width/424.0);
    // These are the renderer's full-wide viewport and world-FOV correction.
    const double ndc=clipX(x,y,model,projection)/expansion;
    const float halfPixel=0.5f/float(width);
    const auto mapping=fixed ? RT64::wr64UsaShutterMapping(1,halfPixel,halfPixel,expansion)
                            : RT64::Wr64UsaShutterMapping{1,halfPixel};
    // Subtract the deliberately retained raster origin for geometric comparisons.
    return width*0.5*(ndc*mapping.scale+(mapping.offset-halfPixel)+1);
}
struct DrawData {
    std::vector<uint32_t> faceIndices,vertexSegmentedAddresses,worldIndices;
    std::vector<uint32_t> worldTransformSegmentedAddresses{0x07001340};
};
struct GameCall {
    struct { uint32_t faceIndicesStart=0; } meshDesc;
    struct { uint32_t triangleCount=0; } callDesc;
};
// Inspect native F3DWAVE vertex/triangle commands, using their production bit layout.
// Other commands do not alter the source positions or matrix address identity.
struct NativeLists {
    const std::vector<uint8_t>& rom;
    uint8_t* rdram;
    DrawData data;
    std::array<uint32_t,64> cache{};
    uint32_t projection=0,model=0,commands=0;
    std::set<uint32_t>& observedBanks;
    uint32_t word(uint32_t address) {
        if(address>>24==1) return be(rom,0xF6090+(address&0xFFFFFF),4);
        require(address>=0x80400000 && address<0x80401000,"dynamic display list address");
        return uint32_t(MEM_W(0,int32_t(address)));
    }
    void triangle(uint32_t indices) {
        require(projection==0x07001300 && model==0x07001340,"native emitted matrix addresses");
        for(int shift:{16,8,0}) {
            const uint32_t index=((indices>>shift)&255)/5;
            require(index<cache.size() && cache[index]<data.vertexSegmentedAddresses.size(),"native vertex cache reference");
            data.faceIndices.push_back(cache[index]);
        }
    }
    void run(uint32_t address,uint32_t limit=0,unsigned depth=0) {
        require(depth<8,"display list nesting bounds");
        while(!limit || address<limit) {
            require(++commands<1000,"native display list termination");
            const uint32_t w0=word(address),w1=word(address+4);address+=8;
            switch(w0>>24) {
            case 0x01: if((w0>>16)&1) projection=w1;else model=w1;break;
            case 0x04: {
                const uint32_t count=(w0>>9)&127,dst=((w0>>16)&255)/5;
                require(dst+count<=cache.size(),"native vertex load bounds");
                for(uint32_t i=0;i<count;++i) {
                    const uint32_t source=w1+i*16;
                    require(RT64::wr64UsaShutterVertex(source),"native list loaded outside original shutter geometry");
                    cache[dst+i]=uint32_t(data.vertexSegmentedAddresses.size());
                    data.vertexSegmentedAddresses.push_back(source);data.worldIndices.push_back(0);
                    for(uint32_t base:{0x0105A7A8U,0x0105B3D8U,0x0105C008U,0x0105CC38U})
                        if(source>=base && source<base+0x240) observedBanks.insert(base);
                }
                break;
            }
            case 0x06: run(w1,0,depth+1);if((w0>>16)&1)return;break;
            case 0xBF: triangle(w1);break;
            case 0xB8: return;
            default: break;
            }
        }
    }
};

int main(int argc,char** argv) {
    try {
        require(argc==3,"usage: shutter_native_test original-USA-ROM widescreen-IPS");
        auto rom=readFile(argv[1]);
        require(rom.size()>=0x800000 && be(rom,0,4)==0x80371240,"canonical big-endian USA image");
        applyIps(rom,readFile(argv[2]));
        const auto originalPatchedImage=rom;
        require(be(rom,0xF6090+0x6F008,2)==848 && be(rom,0xF6090+0x6F010,2)==848,
                "actual IPS USA viewport is centred at212 with212 scale");
        std::vector<uint8_t> memory(8*1024*1024);auto* rdram=memory.data();
        auto load=[&](uint32_t offset,uint32_t physical,uint32_t size) {
            require(offset+size<=rom.size() && physical+size<=memory.size(),"isolated native load bounds");
            for(uint32_t i=0;i<size;++i) memory[(physical+i)^3]=rom[offset+i];
        };
        load(0x1000,0x46800,0xA85D0);load(0xA95D0,0x1DAFA0,0x4C000);
        recomp_context ctx{};ctx.f_odd=&ctx.f0.u32h;ctx.r29=int32_t(0x807F0000);
        SysUtils_TaylorSeries(rdram,&ctx);
        MEM_W(0,int32_t(0x801CE5F8))=int32_t(0x80300000);
        constexpr int32_t state=int32_t(0x80228A10);
        std::set<uint32_t> observedBanks;
        unsigned nativeFrames=0,oldCoverageFailures=0;
        for(int kind:{4,5}) for(int meshFamily:{0,1}) {
            ctx.r4=kind;ctx.r5=meshFamily;ctx.r6=0;FadeTransition_SetProps(rdram,&ctx);
            Matrix previous{};
            int frame=0;
            for(;frame<20;++frame) {
                ctx.r4=state;(kind==4?func_801E74BC:func_801E76C0)(rdram,&ctx);
                const Matrix projection=readMatrix(rdram,int32_t(0x80301300));
                const Matrix model=readMatrix(rdram,int32_t(0x80301340));
                const int phase=MEM_H(2,state);
                // The surrounding native frame code supplies these draw gates.
                MEM_H(4,state)=1;MEM_H(0x20,state)=2;MEM_H(0x26,state)=2;
                ctx.r4=int32_t(0x80400000);func_801E7908(rdram,&ctx);
                require(uint32_t(ctx.r2)==0x80400050,"native shutter emits its original ten top-level commands");
                NativeLists lists{rom,rdram,{}, {},0,0,0,observedBanks};
                lists.cache.fill(UINT32_MAX);lists.run(0x80400000,uint32_t(ctx.r2));
                GameCall call;call.callDesc.triangleCount=uint32_t(lists.data.faceIndices.size()/3);
                require(call.callDesc.triangleCount==32,"complete original cover and edge triangle topology");
                require(RT64::wr64UsaShutterCall(lists.data,call),"production classifier accepts native-emitted geometry");
                if(frame==0) previous=model;
                for(int subframe=0;subframe<=8;++subframe) {
                    const Matrix interpolated=interpolate(previous,model,subframe/8.0);
                    for(double width:{424.0,556.5,848.0}) {
                        const double expansion=width/424.0;
                        const double tail=outputX(0,0,interpolated,projection,width,true);
                        require(kind==4 ? tail>=width : tail<=0,"finite original trailing edge entered viewport during transition");
                        for(uint32_t vertex:lists.data.faceIndices) {
                            const size_t offset=0xF6090+(lists.data.vertexSegmentedAddresses[vertex]&0xFFFFFF);
                            const double x=int16_t(be(rom,offset,2)),y=int16_t(be(rom,offset+2,2));
                            const double native=outputX(x,y,interpolated,projection,424,true);
                            const double mapped=outputX(x,y,interpolated,projection,width,true);
                            require(std::abs(mapped-native*expansion)<0.0002,
                                    "original geometry/animation no longer follows normalized USA viewport coordinates");
                        }
                        // Closure is the initial kind4 frame and the final kind5 frame.
                        if((kind==4 && frame==0) || (kind==5 && phase==2 && subframe==8)) {
                            const double seam=outputX(3200,0,interpolated,projection,width,true);
                            require(std::min(tail,seam)<=0 && std::max(tail,seam)>=width,"closed original cover must span entire viewport");
                            const double oldSeam=outputX(3200,0,interpolated,projection,width,false);
                            if(kind==4 ? oldSeam>0 : oldSeam<width) ++oldCoverageFailures;
                        }
                    }
                }
                previous=model;++nativeFrames;
                if(phase==2 && MEM_H(8,state)>=1)break;
            }
            require(frame==10,"native ten-frame movement plus one held frame retained");
            ctx.r4=state;(kind==4?func_801E74BC:func_801E76C0)(rdram,&ctx);
            ctx.r4=int32_t(0x80400000);func_801E7908(rdram,&ctx);
            require(uint32_t(ctx.r2)==0x80400000,"completed native transition stops emitting meshes");
        }
        require(observedBanks.size()==4,"both native animation texture phases and mesh families covered");
        require(oldCoverageFailures>0,"negative control must reproduce old ultrawide endpoint gaps");
        require(rom==originalPatchedImage,"shutter correction must not alter any ROM geometry or asset byte");
        std::printf("PASS: %u checks; %u native USA frames, both directions, four meshes, 9 interpolation samples/frame, 16:9/21:9/32:9; %u old endpoint gaps reproduced\n",
                    checks,nativeFrames,oldCoverageFailures);
        return 0;
    } catch(const std::exception& error) {
        std::fprintf(stderr,"FAIL: %s\n",error.what());return 1;
    }
}
