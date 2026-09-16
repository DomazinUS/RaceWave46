#include "native_roundness_support.inc"
#include "common/rt64_wr64_water_roundness.h"
#include "common/rt64_wr64_far_water_distance.h"
#include <map>
#include <set>
#include <limits>

struct RoundedDraw {
    std::vector<float> posFloats;
    std::vector<uint32_t> vertexSegmentedAddresses,faceIndices;
    std::vector<uint16_t> viewProjIndices,worldIndices;
};
static void sameExceptHeight(const RoundedDraw &a,const RoundedDraw &b) {
    require(a.faceIndices==b.faceIndices&&a.vertexSegmentedAddresses==b.vertexSegmentedAddresses&&
        a.viewProjIndices==b.viewProjIndices&&a.worldIndices==b.worldIndices,"Roundness changed topology/source/camera/world ownership");
    for(size_t i=0;i<a.posFloats.size();++i)if(i%3!=1)require(a.posFloats[i]==b.posFloats[i],"Roundness moved the native XZ lattice");
}
static float matchingStrength=0;
static float getWr64WaterLaplacianStrength(){return matchingStrength;}
static bool matching(bool scope,float strength,int targetRate=0,bool raytracing=false,
    bool rtScope=false,bool rtSupported=false,bool rasterScope=false,bool rasterSupported=false,
    std::array<bool,2> cameraScopes={}) {
    struct { bool wr64RtReflectionScope,wr64RasterSkyScope,wr64RasterShadowScope,
        wr64RasterReflectionScope,wr64SplitWaterRoundnessScope;
        std::array<bool,2> wr64FarWaterDistanceViewScope{};
        std::array<uint32_t,2> wr64FarWaterDistanceViewModes{};
        struct { bool valid = false; uint32_t mode = 0; } wr64WaveDistanceSnapshot; }
        workload{rtScope,rasterScope,false,false,scope};
    workload.wr64FarWaterDistanceViewScope=cameraScopes;
    struct {int targetRate;bool raytracingEnabled;} workloadConfig{targetRate,raytracing};
    struct {bool wr64RTSupported,wr64RasterSkySupported;} renderer{rtSupported,rasterSupported};
    const auto *framebufferRenderer=&renderer;
    std::vector<decltype(workload)> workloads;
    struct {std::vector<uint32_t> workloads;} prevFrame;
    matchingStrength=strength;
    using RT64::wr64SplitWaterRoundnessMatching;
#include "roundness_matching.inc"
    return requiresFrameMatching;
}
static void matchingAdmission() {
    // Execute the production queue gate with a real one-player native-camera
    // scope. Neither an interpolated refresh rate, a distance override nor a
    // supported reflection/shadow pass may be needed for Wave Roundness.
    for(unsigned course=0;course<=9;++course)for(unsigned phase:{0u,1u,4u,8u,10u})
    for(unsigned mode:{2u,3u,4u,7u,30u,31u,40u,41u,44u,45u})for(unsigned type:{0u,3u,4u,5u,6u}) {
        const bool scope=RT64::wr64FarWaterDistanceScope(course,1,phase,mode,0,0,type,0);
        for(bool apiSupported:{false,true}) {
            require(matching(false,.5f,0,false,false,apiSupported,false,apiSupported,{scope,false})==scope,
                "One-player native-rate Original-effects Roundness is not admitted");
            require(!matching(false,0,0,false,false,apiSupported,false,apiSupported,{scope,false}) &&
                !matching(false,std::numeric_limits<float>::quiet_NaN(),0,false,false,apiSupported,false,apiSupported,{scope,false}),
                "One-player zero/invalid strength added matching work");
        }
    }
    require(matching(false,.5f,0,false,false,false,false,false,{false,true}),
        "Second captured native camera failed to request Roundness matching");
    for(unsigned course=0;course<=9;++course)for(unsigned players=0;players<=3;++players)
    for(unsigned phase:{0u,1u,4u,8u,10u})for(unsigned mode=0;mode<=65;++mode) {
        const bool expected=course>=1&&course<=8&&players==2&&phase==1&&mode>=40&&mode<=45;
        const bool scope=RT64::wr64NativeSplitWaterScope(course,players,phase,mode);
        require(scope==expected,"Native race snapshot includes menu/1P or excludes real split race");
        // targetRate=0 and every rendering effect disabled: exercise exactly
        // the renderer branch that used to bypass Wave Roundness entirely.
        require(matching(scope,.5f)==expected,"Native-rate Original-effects Roundness is not admitted");
        require(!matching(scope,0)&&!matching(scope,std::numeric_limits<float>::quiet_NaN()),
            "Zero/invalid strength must not add matching work");
    }
    for(unsigned bits=0;bits<64;++bits) {
        const int target=(bits&1)?60:0;
        const bool rtEnabled=bits&2,rtScope=bits&4,rtSupported=bits&8,rasterScope=bits&16,rasterSupported=bits&32;
        const bool established=target>0||rtEnabled||(rtScope&&rtSupported)||(rasterScope&&rasterSupported);
        require(matching(false,.5f,target,rtEnabled,rtScope,rtSupported,rasterScope,rasterSupported)==established,
            "Roundness changed established matching outside native two-player races");
        require(matching(true,0,target,rtEnabled,rtScope,rtSupported,rasterScope,rasterSupported)==established,
            "Zero Roundness changed established matching");
    }
}
int main(int argc,char **argv) {
    matchingAdmission();
    if(argc==2 && std::string(argv[1])=="--matching-only") {
        std::cout<<"PASS production Wave Roundness matching gate: one-player native cameras, both API capability states, split scopes and existing matching reasons.\n";
        return 0;
    }
    require(argc==2,"Private ROM path required");
    std::ifstream input(argv[1],std::ios::binary);rom.assign(std::istreambuf_iterator<char>(input),{});
    require(wr64::rom_patch::apply_if_unpatched(rom),"Apply shipped ROM patch in memory");
    size_t tested=0,changed=0;
    for(unsigned course=1;course<=8;++course)for(unsigned view:{0u,1u})for(unsigned buffer:{0u,1u})
    for(unsigned sea:{0u,1u,2u})for(bool enhanced:{false,true}) {
        currentCourse=int(course);active=enhanced;
        auto ram=initial(2,int(view),int(buffer),int(sea),int(course));
        Decoder decoder(ram,0);decoder.decode(run(ram,enhanced));decoder.calls.clear();decoder.decode(nativeWater(ram));
        RoundedDraw original;
        uint32_t owner=0;
        for(const auto &call:decoder.calls) {
            const uint32_t found=RT64::wr64RTNativeRaceView(call.domain);
            require(found==view+1,"Actual original/enhanced native water belongs to expected view");owner=found;
            for(uint32_t source:call.sources) {
                const uint32_t index=uint32_t(original.faceIndices.size());
                original.faceIndices.push_back(index);original.vertexSegmentedAddresses.push_back(source);
                original.viewProjIndices.push_back(uint16_t(view+7));original.worldIndices.push_back(3);
                // Keep actual native index/source topology. Controlled endpoint
                // heights isolate the filter from the separate wave simulation.
                original.posFloats.insert(original.posFloats.end(),{float(source&65535),0,float((source>>8)&255)});
            }
        }
        const uint32_t triangles=uint32_t(original.faceIndices.size()/3);
        require(triangles==(sea==1?1548u:612u),"Actual native water topology changed");
        const uint32_t primary=triangles-12;
        std::map<uint32_t,std::set<uint32_t>> neighbours;
        std::map<std::pair<uint32_t,uint32_t>,unsigned> edges;
        for(uint32_t t=0;t<primary;++t)for(unsigned c=0;c<3;++c) {
            const uint32_t a=original.vertexSegmentedAddresses[t*3+c],b=original.vertexSegmentedAddresses[t*3+(c+1)%3];
            neighbours[a].insert(b);neighbours[b].insert(a);++edges[std::minmax(a,b)];
        }
        std::set<uint32_t> boundary;
        for(auto [edge,count]:edges)if(count==1){boundary.insert(edge.first);boundary.insert(edge.second);}
        uint32_t peak=0;
        for(const auto &entry:neighbours)if(!boundary.count(entry.first)){peak=entry.first;break;}
        require(peak!=0,"Native grid has no interior peak control");
        for(size_t v=0;v<original.vertexSegmentedAddresses.size();++v)
            if(original.vertexSegmentedAddresses[v]==peak)original.posFloats[v*3+1]=100;
        for(float strength:{0.f,.5f,1.f}) {
            auto rounded=original;
            const auto result=RT64::wr64RoundNativeSplitWater(rounded,0,triangles,view+7,owner,strength);
            require(result.applied==(strength>0),"Native split sheet unexpectedly rejected/zero strength mutated");
            sameExceptHeight(original,rounded);
            if(strength==0)require(rounded.posFloats==original.posFloats,"Zero strength is not byte-identical native geometry");
            if(strength>0) {
                require(result.logicalVertices==(sea==1?817u:331u)&&result.boundaryVertices==(sea==1?96u:60u),"Unexpected native logical/boundary topology");
                changed+=result.changedVertices;
                for(size_t v=0;v<original.vertexSegmentedAddresses.size();++v) {
                    const uint32_t key=original.vertexSegmentedAddresses[v];
                    double expected=0;
                    if(key==peak)expected=100*(1-strength);
                    else if(neighbours[peak].count(key)&&!boundary.count(key))expected=100*strength/6;
                    if(v>=size_t(primary)*3||boundary.count(key))expected=original.posFloats[v*3+1];
                    require(std::abs(double(rounded.posFloats[v*3+1])-expected)<1e-5,"Frozen six-neighbour endpoint/seam/boundary oracle mismatch");
                }
            }
        }
        for(unsigned fault=0;fault<5;++fault) {
            auto malformed=original;
            uint32_t faultOwner=owner,faultProjection=view+7;
            if(fault==0)malformed.posFloats[4]=std::numeric_limits<float>::infinity();
            if(fault==1)malformed.faceIndices.back()=UINT32_MAX;
            if(fault==2)malformed.worldIndices[2]=4;
            if(fault==3)faultOwner=0;
            if(fault==4)faultProjection+=1;
            const auto before=malformed;
            require(!RT64::wr64RoundNativeSplitWater(malformed,0,triangles,faultProjection,faultOwner,.5f).applied,"Malformed water accepted");
            require(malformed.posFloats==before.posFloats,"Rejected sheet partially changed height");
        }
        // Duplicate a native source with a contradictory decoded endpoint.
        auto alias=original;size_t duplicate=1;
        while(duplicate<alias.vertexSegmentedAddresses.size()&&alias.vertexSegmentedAddresses[duplicate]!=alias.vertexSegmentedAddresses[0])++duplicate;
        require(duplicate<size_t(primary)*3,"Actual native repeated source missing");
        alias.posFloats[duplicate*3+1]+=1;const auto beforeAlias=alias;
        require(!RT64::wr64RoundNativeSplitWater(alias,0,triangles,view+7,owner,.5f).applied&&alias.posFloats==beforeAlias.posFloats,
            "Conflicting source alias must be rejected without mutations");
        ++tested;
    }
    std::printf("PASS water roundness: %zu actual native course/view/buffer/sea/Original-Enhanced cases, %u checks, %zu changed physical heights.\n",tested,checks,changed);
}
