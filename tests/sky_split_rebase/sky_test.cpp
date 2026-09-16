#include "common/rt64_common.h"
#include "common/rt64_wr64_hud_motion.h"
#include "common/rt64_wr64_dolphin_sun_sprite.h"
#include "hle/rt64_transform_group.h"
#include "shared/rt64_color_combiner.h"
#include "shared/rt64_extra_params.h"
#include "shared/rt64_rdp_params.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <unordered_map>

// DrawCall, GameIndices, GameScene and ModifiedBuffers are extracted unchanged.
// TransformGroup, FixedRect, matrices and shared shader structures are real RT64.
#include "sky_types.inc"
namespace RT64 {
struct GameCall { DrawCall callDesc{}; struct Mesh { uint32_t faceIndicesStart=0; } meshDesc; };
struct Projection {
    enum class Type { None, Perspective, Orthographic, Rectangle, Triangle };
    Type type=Type::Perspective;
    uint32_t transformsIndex=0, gameCallCount=0;
    std::vector<GameCall> gameCalls;
    FixedRect scissorRect;
};
struct FramebufferPair { uint32_t projectionCount=0; std::vector<Projection> projections; };
struct DrawData {
    std::vector<float> posFloats, tcFloats, velFloats, tcVelFloats;
    std::vector<uint32_t> faceIndices, worldTransformGroups;
    std::vector<uint16_t> worldIndices;
    std::vector<TransformGroup> transformGroups;
    std::vector<hlslpp::float4x4> worldTransforms, viewTransforms, projTransforms;
};
struct Workload { DrawData drawData; uint32_t fbPairCount=0; std::vector<FramebufferPair> fbPairs; };
struct WorkloadQueue { std::vector<Workload> workloads; };
}
#include "sky_functions.inc"
using namespace RT64;

static size_t checks=0;
static void check(bool condition,const char* description) {
    ++checks; if(!condition) { std::cerr << "FAIL: " << description << '\n'; std::exit(1); }
}
static constexpr uint32_t Target=2, VerticesPerView=32;
static const uint32_t CloudLocal[]={2,5,9,11,14,17,21};
static std::set<uint32_t> cloud(uint32_t view) {
    std::set<uint32_t> result;
    for(auto v:CloudLocal) result.insert(view*VerticesPerView+v);
    return result;
}
static GameCall& skyCall(WorkloadQueue& q,uint32_t view) {
    return q.workloads[Target].fbPairs[0].projections[view].gameCalls[1];
}
static void setVelocity(WorkloadQueue& q,uint32_t view,float uv,float position=0.0f) {
    auto& d=q.workloads[Target].drawData;
    for(auto v:cloud(view)) {
        d.tcVelFloats[v*2]=uv; d.tcVelFloats[v*2+1]=0;
        d.velFloats[v*3]=position; d.velFloats[v*3+1]=0; d.velFloats[v*3+2]=0;
    }
}
static Workload makeWorkload(bool split,bool vertical) {
    Workload w; w.fbPairCount=1; w.fbPairs.resize(1);
    auto& fb=w.fbPairs[0]; fb.projectionCount=split?2:1; fb.projections.resize(fb.projectionCount);
    auto& d=w.drawData;
    for(uint32_t view=0;view<fb.projectionCount;++view) {
        auto& p=fb.projections[view]; p.transformsIndex=view;
        p.scissorRect=vertical?FixedRect(view*640,0,(view+1)*640,960):
            FixedRect(0,view*480,1280,(view+1)*480);
        if(!split) p.scissorRect=FixedRect(0,0,1280,960);
        const auto& captured=CapturedSkyMaterial[view];
        TransformGroup group; group.matrixId=captured[5];
        group.ordering=G_EX_ORDER_LINEAR; group.texcoordInterpolation=G_EX_COMPONENT_INTERPOLATE;
        group.vertexInterpolation=G_EX_COMPONENT_INTERPOLATE;
        d.transformGroups.push_back(group); d.worldTransformGroups.push_back(view);
        auto world=hlslpp::float4x4::identity(); world[3][0]=float(view*1024+17);
        d.worldTransforms.push_back(world);
        auto camera=hlslpp::float4x4::identity(); camera[3][2]=float(800+view*1234);
        d.viewTransforms.push_back(camera); d.projTransforms.push_back(hlslpp::float4x4::identity());
        for(uint32_t local=0;local<VerticesPerView;++local) {
            const auto v=view*VerticesPerView+local;
            d.posFloats.insert(d.posFloats.end(),{float(v*80),500.0f,float(v*30)});
            d.tcFloats.insert(d.tcFloats.end(),{float(v*4),float(v*7)});
            // Large values on neighboring, non-cloud vertices catch whole-transform freezing.
            d.velFloats.insert(d.velFloats.end(),{1.0f,2.0f,3.0f});
            d.tcVelFloats.insert(d.tcVelFloats.end(),{80.0f+float(v),-34.0f});
            d.worldIndices.push_back(uint16_t(view));
        }
        GameCall background; background.callDesc.triangleCount=1;
        background.callDesc.minWorldMatrix=background.callDesc.maxWorldMatrix=uint16_t(view);
        background.meshDesc.faceIndicesStart=uint32_t(d.faceIndices.size());
        for(auto local:{0U,1U,3U}) d.faceIndices.push_back(view*VerticesPerView+local);
        p.gameCalls.push_back(background);
        GameCall sky; sky.callDesc.triangleCount=captured[0];
        sky.callDesc.minWorldMatrix=sky.callDesc.maxWorldMatrix=uint16_t(view);
        sky.callDesc.colorCombiner.L=captured[1]; sky.callDesc.colorCombiner.H=captured[2];
        sky.callDesc.otherMode.L=captured[3]; sky.callDesc.otherMode.H=captured[4];
        sky.meshDesc.faceIndicesStart=uint32_t(d.faceIndices.size());
        for(uint32_t triangle=0;triangle<6;++triangle) {
            d.faceIndices.push_back(view*VerticesPerView+CloudLocal[0]);
            d.faceIndices.push_back(view*VerticesPerView+CloudLocal[1+triangle]);
            d.faceIndices.push_back(view*VerticesPerView+CloudLocal[1+(triangle+1)%6]);
        }
        p.gameCalls.push_back(sky); p.gameCallCount=2;
    }
    return w;
}
static WorkloadQueue make(bool split=true,bool vertical=false) {
    WorkloadQueue q; q.workloads.resize(Target+1);
    q.workloads[0]=makeWorkload(true,false); // Deliberate untouched workload with the same sky signature.
    q.workloads[Target]=makeWorkload(split,vertical);
    setVelocity(q,0,0.75f,46.0f);
    if(split) setVelocity(q,1,0.75f,46.0f);
    return q;
}
static bool sameMatrices(const std::vector<hlslpp::float4x4>& a,const std::vector<hlslpp::float4x4>& b) {
    return a.size()==b.size() && std::memcmp(a.data(),b.data(),a.size()*sizeof(a[0]))==0;
}
static void unchangedExcept(const WorkloadQueue& before,const WorkloadQueue& after,
                            const std::set<uint32_t>& zeroed) {
    for(size_t w=0;w<before.workloads.size();++w) {
        const auto& a=before.workloads[w]; const auto& b=after.workloads[w];
        check(a.drawData.posFloats==b.drawData.posFloats,"positions changed");
        check(a.drawData.tcFloats==b.drawData.tcFloats,"native texture coordinates changed");
        check(a.drawData.velFloats==b.drawData.velFloats,"position velocities changed");
        check(a.drawData.faceIndices==b.drawData.faceIndices,"triangle indexing changed");
        check(a.drawData.worldIndices==b.drawData.worldIndices,"vertex transform indices changed");
        check(a.drawData.worldTransformGroups==b.drawData.worldTransformGroups,"transform identity mapping changed");
        check(sameMatrices(a.drawData.worldTransforms,b.drawData.worldTransforms),"world matrices changed");
        check(sameMatrices(a.drawData.viewTransforms,b.drawData.viewTransforms),"camera matrices changed");
        check(sameMatrices(a.drawData.projTransforms,b.drawData.projTransforms),"projection matrices changed");
        check(a.drawData.transformGroups.size()==b.drawData.transformGroups.size(),"transform groups changed");
        for(size_t g=0;g<a.drawData.transformGroups.size();++g)
            check(std::memcmp(&a.drawData.transformGroups[g],&b.drawData.transformGroups[g],sizeof(TransformGroup))==0,
                  "transform interpolation settings changed");
        check(a.fbPairCount==b.fbPairCount && a.fbPairs.size()==b.fbPairs.size(),"framebuffer membership changed");
        for(size_t f=0;f<a.fbPairs.size();++f) for(size_t p=0;p<a.fbPairs[f].projections.size();++p) {
            const auto& x=a.fbPairs[f].projections[p]; const auto& y=b.fbPairs[f].projections[p];
            check(std::memcmp(&x.scissorRect,&y.scissorRect,sizeof(FixedRect))==0,"viewport/scissor changed");
            check(x.transformsIndex==y.transformsIndex,"camera transform association changed");
        }
        check(a.drawData.tcVelFloats.size()==b.drawData.tcVelFloats.size(),"UV velocity allocation changed");
        for(size_t i=0;i<a.drawData.tcVelFloats.size();++i) {
            const float expected=(w==Target && zeroed.count(uint32_t(i/2)))?0.0f:a.drawData.tcVelFloats[i];
            check(b.drawData.tcVelFloats[i]==expected,"wrong vertex/workload UV velocity changed");
        }
    }
}
static void flags(const ModifiedBuffers& m,bool changed) {
    check(m.texcoordVelocity==changed,"wrong texture velocity upload marking");
    check(!m.positionVelocity && !m.position && !m.wr64WaterField && !m.wr64WaterCoverage,
          "unrelated upload marked");
}
static void runExpected(WorkloadQueue q,const std::set<uint32_t>& expected) {
    const auto before=q; ModifiedBuffers m;
    wr64SkyTexcoordFixSplitWorkload(q,Target,m);
    flags(m,!expected.empty()); unchangedExcept(before,q,expected);
}
static void sceneGap(bool vertical) {
    auto q=make(true,vertical); setVelocity(q,0,82.0f); setVelocity(q,1,1078.0f);
    const auto before=q;
    GameScene matchedP1; matchedP1.projections.push_back({Target,0,0});
    ModifiedBuffers old;
    // Synthetic post-ID-match state uses historically observed rebase magnitudes.
    // Only P1 has a previous scene, so the old correction runs only for that scene.
    wr64SkyTexcoordFixApply(q,matchedP1,old);
    flags(old,true); unchangedExcept(before,q,cloud(0));
    check(q.workloads[Target].drawData.tcVelFloats[*cloud(1).begin()*2]==1078.0f,
          "old path failed to reproduce the uncorrected second view");
    std::unordered_map<uint32_t,ModifiedBuffers> modified;
    applyLateLoop(q,{Target},modified);
    check(modified.size()==1 && modified.count(Target)==1,"wrong workload selected for upload");
    flags(modified.at(Target),true);
    auto both=cloud(0); const auto second=cloud(1); both.insert(second.begin(),second.end());
    unchangedExcept(before,q,both);
}
static void capturedMaterialRegression() {
    auto q=make();
    check(skyCall(q,0).callDesc.otherMode.H==0x00882C3FU &&
          skyCall(q,1).callDesc.otherMode.H==0x00882CFFU,"captured material difference lost");
    GameScene scene; scene.projections={{Target,0,0},{Target,0,1}};
    std::vector<Wr64SkyBracketLocation> oldFound,found;
    wr64SkyBracketFindAllOldClassifier(q,scene,oldFound,4);
    wr64SkyBracketFindAll(q,scene,found,4);
    check(oldFound.size()==1 && oldFound[0].projectionIndex==0,"old classifier did not reproduce P2 miss");
    check(found.size()==2 && found[1].projectionIndex==1,"current classifier missed captured P2 cloud");
    // Material is captured; velocities are synthetic. P2's U-wrap magnitude
    // comes from the separately executed native cloud producer sequence.
    setVelocity(q,0,82.0f); setVelocity(q,1,-63.96875f); const auto before=q;
    ModifiedBuffers old; wr64SkyTexcoordFixApplyOldClassifier(q,scene,old);
    unchangedExcept(before,q,cloud(0)); flags(old,true);
    ModifiedBuffers current; wr64SkyTexcoordFixApply(q,scene,current);
    auto both=cloud(0); const auto second=cloud(1); both.insert(second.begin(),second.end());
    unchangedExcept(before,q,both); flags(current,true);
    check(G_MDSFT_RGBDITHER==6,"unexpected native RGB dither field");
    for(uint32_t mode=0;mode<4;++mode) {
        auto sample=make(); skyCall(sample,1).callDesc.otherMode.H=0x00882C3FU | (mode<<G_MDSFT_RGBDITHER);
        check(wr64SkyBracketIsExactSkyCall(skyCall(sample,1).callDesc),"RGB dither mode rejected");
        setVelocity(sample,1,82.0f); runExpected(sample,cloud(1));
    }
    for(uint32_t bit=0;bit<32;++bit) {
        if(bit==G_MDSFT_RGBDITHER || bit==G_MDSFT_RGBDITHER+1) continue;
        auto sample=make(); skyCall(sample,1).callDesc.otherMode.H^=1U<<bit;
        check(!wr64SkyBracketIsExactSkyCall(skyCall(sample,1).callDesc),"non-dither material bit accepted");
        setVelocity(sample,1,82.0f); runExpected(sample,{});
    }
}
static void negativeControls() {
    for(int kind=0;kind<22;++kind) {
        auto q=make(); setVelocity(q,1,82.0f); auto& w=q.workloads[Target]; auto& d=w.drawData;
        auto& p=w.fbPairs[0].projections[1]; auto& s=p.gameCalls[1];
        switch(kind) {
        case 0: s.callDesc.triangleCount=5; break;
        case 1: s.callDesc.colorCombiner.L^=1; break;
        case 2: s.callDesc.colorCombiner.H^=1; break;
        case 3: s.callDesc.otherMode.L^=1; break;
        case 4: s.callDesc.otherMode.H^=1; break;
        case 5: s.meshDesc.faceIndicesStart=uint32_t(d.faceIndices.size()); break;
        case 6: d.faceIndices[s.meshDesc.faceIndicesStart]=uint32_t(d.worldIndices.size()); break;
        case 7: d.worldIndices[*cloud(1).begin()]=0; break;
        case 8: s.callDesc.maxWorldMatrix=200; break;
        case 9: s.callDesc.minWorldMatrix=2; break;
        case 10: d.worldTransformGroups[1]=200; break;
        case 11: d.transformGroups[1].matrixId=0x57524302U; break;
        case 12: p.type=Projection::Type::Orthographic; break;
        case 13: p.gameCallCount=1; break;
        case 14: w.fbPairs[0].projectionCount=1; break;
        case 15: w.fbPairCount=0; break;
        case 16: d.tcVelFloats.resize(VerticesPerView*2); break;
        case 17: d.velFloats.resize(VerticesPerView*3); break;
        case 18: d.worldTransforms.resize(1); break;
        case 19: d.worldTransformGroups.resize(1); break;
        case 20: s.meshDesc.faceIndicesStart=0xFFFFFFFFU; break;
        case 21: s.callDesc.minWorldMatrix=0; // Mixed view faces cannot be one cloud.
                 d.worldIndices[*cloud(1).begin()]=0; break;
        }
        runExpected(q,{});
    }
    auto q=make(); setVelocity(q,1,82.0f);
    const auto before=q; ModifiedBuffers m;
    wr64SkyTexcoordFixSplitWorkload(q,99,m); flags(m,false); unchangedExcept(before,q,{});
    // Ignore allocated but inactive framebuffer storage, even if it contains a second view.
    q=make(); setVelocity(q,1,82.0f);
    auto& w=q.workloads[Target]; w.fbPairs.push_back(w.fbPairs[0]);
    w.fbPairs[0].projectionCount=1; runExpected(q,{});
    // Merely allocating both authored groups does not establish two drawn views.
    q=make(); setVelocity(q,0,82.0f); setVelocity(q,1,82.0f);
    auto& onlyP1=q.workloads[Target];
    std::fill(onlyP1.drawData.worldIndices.begin(),onlyP1.drawData.worldIndices.end(),uint16_t(0));
    for(auto& p:onlyP1.fbPairs[0].projections) for(auto& call:p.gameCalls)
        call.callDesc.minWorldMatrix=call.callDesc.maxWorldMatrix=0;
    runExpected(q,{});
}
int main(int argc,char** argv) {
    check(argc==2,"expected test mode");
    if(std::string(argv[1])!="normal") {
        auto q=make(); setVelocity(q,0,82.0f); setVelocity(q,1,1078.0f);
        runExpected(q,{});
        std::cout << "PASS " << checks << " checks: environment bypass " << argv[1] << '\n'; return 0;
    }
    check(wr64SkyTexcoordJumpThreshold()==20.0f,"legacy UV threshold changed");
    check(wr64SkyReanchorThreshold()==1000.0f,"legacy position threshold changed");
    capturedMaterialRegression();
    for(bool vertical:{false,true}) {
        sceneGap(vertical);
        runExpected(make(true,vertical),{});
        for(uint32_t view=0;view<2;++view) {
            for(auto sample:{std::pair<float,float>{20.0f,1000.0f}, {20.01f,46.0f}, {0.75f,1000.01f}}) {
                auto q=make(true,vertical); setVelocity(q,view,sample.first,sample.second);
                runExpected(q,(sample.first>20.0f || sample.second>1000.0f)?cloud(view):std::set<uint32_t>{});
            }
            auto q=make(true,vertical); setVelocity(q,view,82.0f);
            auto& other=q.workloads[Target].fbPairs[0].projections[1-view];
            other.gameCallCount=1; // Other viewport still emits its course background.
            runExpected(q,cloud(view));
        }
    }
    auto one=make(false); setVelocity(one,0,82.0f); runExpected(one,{});
    // Existing single-player protection retains its original behavior.
    auto baseline=one; GameScene scene; scene.projections.push_back({Target,0,0}); ModifiedBuffers m;
    wr64SkyTexcoordFixApply(one,scene,m); flags(m,true); unchangedExcept(baseline,one,cloud(0));
    std::vector<Wr64SkyBracketLocation> locations;
    auto q=make(); GameScene all; all.projections={{99,0,0},{Target,99,0},{Target,0,99},{Target,0,0},{Target,0,1}};
    wr64SkyBracketFindAll(q,all,locations,4);
    check(locations.size()==2 && locations[0].workloadIndex==Target && locations[1].projectionIndex==1,
          "existing indexed finder did not find both valid projections");
    wr64SkyBracketFindAll(q,all,locations,1); check(locations.size()==1,"finder limit ignored");
    negativeControls();
    std::cout << "PASS " << checks << " checks: production indexed sky correction, unmatched P2 regression, "
                 "both split orientations, thresholds, scope, bounds and unchanged cameras/positions\n";
}
