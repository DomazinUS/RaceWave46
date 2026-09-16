#include "native_roundness_support.inc"
#include "common/rt64_wr64_native_water_distance.h"
#include "common/rt64_wr64_water_roundness.h"
#include <chrono>
#include <limits>

struct FanDraw {
    std::vector<float> posFloats,velFloats;
    std::vector<uint32_t> vertexSegmentedAddresses,faceIndices;
    std::vector<uint16_t> viewProjIndices,worldIndices;
    std::array<RT64::Wr64NativeWaterDistanceView,3> wr64NativeWaterDistance{};
};

// The native command decoder supplies every triangle/source identity. Embed
// its boundary on a circle to isolate far coverage from wave simulation.
// This is an independent convex planar control, not a second scaler.
static FanDraw fixture(Decoder &decoder,uint32_t view,bool split=true) {
    FanDraw draw;
    for(const auto &call:decoder.calls) {
        require(RT64::wr64RTNativeRaceView(call.domain)==(split?view+1:0),"Wrong source viewport owner");
        if(split) require(RT64::wr64FarWaterSourceOwner(call.domain)==int32_t(view+1),"Actual split viewport rejected by distance routing");
        for(uint32_t source:call.sources) {
            draw.faceIndices.push_back(uint32_t(draw.faceIndices.size()));
            draw.vertexSegmentedAddresses.push_back(source);
            draw.viewProjIndices.push_back(uint16_t(7+view));draw.worldIndices.push_back(3);
        }
    }
    const uint32_t triangles=uint32_t(draw.faceIndices.size()/3),primary=triangles-12;
    std::map<std::pair<uint32_t,uint32_t>,uint32_t> edges;
    std::set<uint32_t> innerKeys;
    for(uint32_t t=0;t<primary;++t) for(uint32_t c=0;c<3;++c) {
        uint32_t a=draw.vertexSegmentedAddresses[t*3+c],b=draw.vertexSegmentedAddresses[t*3+(c+1)%3];
        innerKeys.insert(a);++edges[std::minmax(a,b)];
    }
    std::map<uint32_t,std::set<uint32_t>> boundary;
    for(auto [edge,count]:edges) if(count==1){boundary[edge.first].insert(edge.second);boundary[edge.second].insert(edge.first);}
    std::vector<uint32_t> cycle;uint32_t current=boundary.begin()->first,previous=UINT32_MAX;
    do {
        cycle.push_back(current);require(cycle.size()<=boundary.size(),"Native boundary not a cycle");
        const auto &neighbours=boundary.at(current);
        require(neighbours.size()==2,"Native boundary branching");
        uint32_t next=*neighbours.begin();if(next==previous)next=*neighbours.rbegin();
        previous=current;current=next;
    }while(current!=cycle.front());
    require(cycle.size()==boundary.size(),"Disconnected native boundary");
    std::map<uint32_t,std::array<float,2>> points;
    constexpr double pi=3.14159265358979323846;
    for(size_t i=0;i<cycle.size();++i)points[cycle[i]]={float(768*std::cos(2*pi*i/cycle.size())),float(768*std::sin(2*pi*i/cycle.size()))};
    std::map<uint32_t,std::set<uint32_t>> fanNeighbours;
    for(uint32_t t=primary;t<triangles;++t)for(uint32_t c=0;c<3;++c) {
        uint32_t a=draw.vertexSegmentedAddresses[t*3+c],b=draw.vertexSegmentedAddresses[t*3+(c+1)%3];
        if(!innerKeys.count(a)&&innerKeys.count(b))fanNeighbours[a].insert(b);
        if(!innerKeys.count(b)&&innerKeys.count(a))fanNeighbours[b].insert(a);
    }
    require(fanNeighbours.size()==6,"Native sheet lacks six private outer points");
    for(const auto &[key,neighbours]:fanNeighbours) {
        double x=0,z=0;for(uint32_t n:neighbours){x+=points.at(n)[0];z+=points.at(n)[1];}
        double length=std::hypot(x,z);require(length>0,"Degenerate fan direction");
        points[key]={float(2304*x/length),float(2304*z/length)};
    }
    for(uint32_t key:draw.vertexSegmentedAddresses) {
        const auto point=points[key];
        draw.posFloats.insert(draw.posFloats.end(),{point[0]+float(view*900),float(innerKeys.count(key)&&!boundary.count(key)?25:0),point[1]+float(view*700)});
        draw.velFloats.insert(draw.velFloats.end(),{48,2,-16});
    }
    return draw;
}
static double area(const FanDraw &draw,uint32_t triangle,float alpha=1) {
    double p[3][2];for(uint32_t c=0;c<3;++c)for(uint32_t a=0;a<2;++a){uint32_t v=draw.faceIndices[triangle*3+c];p[c][a]=draw.posFloats[v*3+a*2]-(1-alpha)*draw.velFloats[v*3+a*2];}
    return(p[1][0]-p[0][0])*(p[2][1]-p[0][1])-(p[1][1]-p[0][1])*(p[2][0]-p[0][0]);
}
static void preserve(const FanDraw &before,const FanDraw &after) {
    require(before.faceIndices==after.faceIndices&&before.vertexSegmentedAddresses==after.vertexSegmentedAddresses&&before.viewProjIndices==after.viewProjIndices&&before.worldIndices==after.worldIndices,"Far coverage changed source topology/ownership");
    const size_t primary=(before.faceIndices.size()/3-12)*3;
    for(size_t v=0;v<before.vertexSegmentedAddresses.size();++v) {
        require(before.posFloats[v*3+1]==after.posFloats[v*3+1],"Far coverage changed wave/tide Y");
        if(v<primary)for(uint32_t a=0;a<3;++a)require(before.posFloats[v*3+a]==after.posFloats[v*3+a],"Far coverage changed near-field position");
    }
}
static float getWr64WaterLaplacianStrength(){return 0;}
static void dispatch() {
    struct W {bool wr64RtReflectionScope=false,wr64RasterSkyScope=false,wr64RasterShadowScope=false,wr64RasterReflectionScope=false,wr64SplitWaterRoundnessScope=false;std::array<bool,2>wr64FarWaterDistanceViewScope{};std::array<uint32_t,2>wr64FarWaterDistanceViewModes{};struct {bool valid=false;uint32_t mode=0;}wr64WaveDistanceSnapshot;};
    for(uint32_t current=0;current<6;++current)for(uint32_t previous=0;previous<6;++previous)for(uint32_t view=0;view<2;++view) {
        W workload;workload.wr64FarWaterDistanceViewModes[view]=current;
        std::vector<W>workloads(1);workloads[0].wr64FarWaterDistanceViewModes[view]=previous;
        struct{std::vector<uint32_t>workloads;}prevFrame{{0}};
        struct{int targetRate=0;bool raytracingEnabled=false;}workloadConfig;
        struct{bool wr64RTSupported=false,wr64RasterSkySupported=false;}renderer;
        const auto*framebufferRenderer=&renderer;
        using RT64::wr64SplitWaterRoundnessMatching;
#include "roundness_matching.inc"
        require(requiresFrameMatching==bool(current||previous),"Native-rate mode transition skips matching");
    }
}
int main(int argc,char **argv) {
    require(argc==2,"Private ROM path required");std::ifstream input(argv[1],std::ios::binary);rom.assign(std::istreambuf_iterator<char>(input),{});
    require(wr64::rom_patch::apply_if_unpatched(rom),"Shipped ROM patch failed");dispatch();
    RT64::WR64RTViewDomain full;full.perspective=true;full.scale[0]=full.translate[0]=212;full.scale[1]=full.translate[1]=120;full.scissor[2]=1696;full.scissor[3]=960;
    require(RT64::wr64FarWaterSourceOwner(full)==0,"Full patched viewport rejected");
    auto menu=full;menu.menuWaterPreview=true;require(RT64::wr64FarWaterSourceOwner(menu)<0,"Menu viewport admitted");
    auto crop=full;crop.scissor[3]=480;require(RT64::wr64FarWaterSourceOwner(crop)<0,"Partial full-camera viewport admitted");
    const auto started=std::chrono::steady_clock::now();uint32_t nativeScenarios=0,transitions=0;
    for(unsigned course=0;course<=8;++course) for(unsigned sea:{0U,1U,2U}) {
        currentCourse=int(course);active=false;auto ram=initial(1,0,0,int(sea),int(course?course:1));put(ram.data(),0x800D8170,course);
        Decoder decoder(ram,0);decoder.decode(nativeWater(ram));
        uint32_t faces=0;for(const auto &call:decoder.calls) {
            faces+=uint32_t(call.sources.size()/3);
        }
        std::cout<<"ONE_PLAYER course="<<course<<" sea="<<sea<<" native_triangles="<<faces<<"\n";
        if(faces==1548||faces==612) {
            auto draw=fixture(decoder,0,false);const auto original=draw;
            require(RT64::wr64ExtendNativeWaterFan(draw,0,faces,7,0,5),"Native one-player alternate sheet rejected");preserve(original,draw);
        }else require(faces==876,"Unknown one-player water topology");
    }

    for(unsigned course=1;course<=8;++course)for(unsigned view:{0u,1u})for(unsigned sea:{0u,1u,2u})for(bool enhanced:{false,true}) {
        currentCourse=int(course);active=enhanced;
        auto ram=initial(2,int(view),0,int(sea),int(course));Decoder decoder(ram,0);
        decoder.decode(run(ram,enhanced));decoder.calls.clear();decoder.decode(nativeWater(ram));
        auto native=fixture(decoder,view);const uint32_t triangles=uint32_t(native.faceIndices.size()/3);
        require(triangles==(sea==1?1548U:612U),"Unexpected native fan topology");
        for(uint32_t mode=0;mode<6;++mode) {
            auto extended=native;require(RT64::wr64ExtendNativeWaterFan(extended,0,triangles,view+7,view+1,mode),"Actual native fan rejected");
            preserve(native,extended);
            if(!mode)require(native.posFloats==extended.posFloats&&native.velFloats==extended.velFloats,"Original native fan changed bytes");
            for(uint32_t t=triangles-12;t<triangles;++t)require(area(native,t)*area(extended,t)>0,"Extended native fan folded");
            const auto once=extended;require(!RT64::wr64ExtendNativeWaterFan(extended,0,triangles,view+7,view+1,mode),"Duplicate fan extended twice");require(once.posFloats==extended.posFloats,"Duplicate fan mutation");
            auto roundedNative=native,roundedExtended=extended;
            auto a=RT64::wr64RoundNativeSplitWater(roundedNative,0,triangles,view+7,view+1,.5f);
            auto b=RT64::wr64RoundNativeSplitWater(roundedExtended,0,triangles,view+7,view+1,.5f);
            require(a.applied&&b.applied,"Distance interferes with Wave Roundness");
            for(size_t v=0;v<native.posFloats.size()/3;++v)require(roundedNative.posFloats[v*3+1]==roundedExtended.posFloats[v*3+1],"Wave Roundness result depends on distance");
        }
        if(course==1&&enhanced)for(uint32_t prevMode=0;prevMode<6;++prevMode)for(uint32_t curMode=0;curMode<6;++curMode) {
            auto previous=native,current=native;
            for(size_t v=0;v<current.posFloats.size()/3;++v){current.posFloats[v*3]+=48;current.posFloats[v*3+1]+=2;current.posFloats[v*3+2]-=16;}
            require(RT64::wr64ExtendNativeWaterFan(previous,0,triangles,view+7,view+1,prevMode)&&RT64::wr64ExtendNativeWaterFan(current,0,triangles,view+7,view+1,curMode),"Mode endpoints rejected");
            auto baseline=current;
            bool changed=RT64::wr64FinalizeNativeWaterDistance(current,previous);
            require(changed==bool(curMode||prevMode),"Default finalizer mutated Original");
            for(const auto &v:current.wr64NativeWaterDistance[view+1].vertices)for(uint32_t a:{0U,2U})
                require(std::abs((current.posFloats[v.vertex*3+a]-current.velFloats[v.vertex*3+a])-previous.posFloats[v.vertex*3+a])<.002,"Previous committed endpoint not reproduced");
            for(float alpha:{0.f,.125f,.5f,.875f,1.f})for(uint32_t t=triangles-12;t<triangles;++t)
                require(area(native,t)*area(current,t,alpha)>0,"Fractional mode transition folds native fan");
            auto disconnected=baseline;RT64::wr64FinalizeNativeWaterDistance(disconnected,previous,false);
            for(const auto &v:disconnected.wr64NativeWaterDistance[view+1].vertices)for(uint32_t a:{0U,2U})require(disconnected.velFloats[v.vertex*3+a]==v.velocity[a],"Course change borrowed old fan endpoints");
            auto changedCamera=baseline;changedCamera.wr64NativeWaterDistance[view+1].cameraIndex=1;
            RT64::wr64FinalizeNativeWaterDistance(changedCamera,previous);
            for(const auto &v:changedCamera.wr64NativeWaterDistance[view+1].vertices)for(uint32_t a:{0U,2U})require(changedCamera.velFloats[v.vertex*3+a]==v.velocity[a],"Changed camera borrowed former selector endpoints");
            const auto once=current;RT64::wr64FinalizeNativeWaterDistance(current,previous);require(once.velFloats==current.velFloats,"Finalizer not idempotent");++transitions;
        }
        if(course==1&&enhanced) {
            struct W {FanDraw drawData;uint32_t wr64RtCourse=1;};
            struct P {bool mapped=false;uint32_t prevTransformIndex=0;};
            struct M {bool mapped=true;uint32_t prevWorkloadIndex=0;std::vector<P>viewProjections;};
            std::vector<W> entries(3);entries[0].drawData=native;entries[1].drawData=native;entries[2].drawData=native;
            for(float &v:entries[1].drawData.posFloats)v+=7000;
            require(RT64::wr64ExtendNativeWaterFan(entries[0].drawData,0,triangles,view+7,view+1,1),"Previous mapped fixture rejected");
            require(RT64::wr64ExtendNativeWaterFan(entries[2].drawData,0,triangles,view+7,view+1,5),"Current mapped fixture rejected");
            entries[0].drawData.wr64NativeWaterDistance[view+1].projection=99;
            M mapped;mapped.viewProjections.resize(9);mapped.viewProjections[view+7]={true,99};
            for(uint32_t fault=0;fault<7;++fault) {
                auto frames=entries;auto map=mapped;
                if(fault==1)map.mapped=false;
                if(fault==2)map.prevWorkloadIndex=UINT32_MAX;
                if(fault==3)map.viewProjections[view+7].mapped=false; // renderer camera-cut result
                if(fault==4)map.viewProjections[view+7].prevTransformIndex=88;
                if(fault==5)frames[0].wr64RtCourse=2;
                if(fault==6)map.viewProjections.clear();
                require(RT64::wr64FinalizeMappedNativeWaterDistance(frames,2,map),"Mapped/fallback finalizer did not run");
                for(const auto &v:frames[2].drawData.wr64NativeWaterDistance[view+1].vertices)for(uint32_t a:{0U,2U}) {
                    const float expected=fault? v.velocity[a] : v.position[a]-frames[0].drawData.posFloats[v.vertex*3+a];
                    require(std::abs(frames[2].drawData.velFloats[v.vertex*3+a]-expected)<.002,"Ordinal/history/projection/camera-cut match leaked into fan");
                }
                require(frames[0].drawData.posFloats==entries[0].drawData.posFloats&&frames[1].drawData.posFloats==entries[1].drawData.posFloats,"History frame mutated");
            }
        }
        for(uint32_t fault=0;fault<5;++fault) {
            auto bad=native;if(fault==0)bad.faceIndices.back()=UINT32_MAX;if(fault==1)bad.viewProjIndices.back()=99;
            if(fault==2)bad.posFloats.back()=std::numeric_limits<float>::infinity();if(fault==3)bad.worldIndices.back()=4;if(fault==4)bad.vertexSegmentedAddresses.back()=0;
            const auto before=bad;require(!RT64::wr64ExtendNativeWaterFan(bad,0,triangles,view+7,view+1,5),"Malformed native fan admitted");require(before.posFloats==bad.posFloats&&before.velFloats==bad.velFloats,"Rejected fan partially mutated");
        }
        ++nativeScenarios;
    }
    std::cout<<"PASS: "<<nativeScenarios<<" native course/view/material/sea cases, "<<transitions<<" transitions, "<<checks<<" checks in "<<std::chrono::duration<double>(std::chrono::steady_clock::now()-started).count()<<"s\n";
}
