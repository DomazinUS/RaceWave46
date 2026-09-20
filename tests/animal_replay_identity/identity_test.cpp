#include "common/rt64_wr64_animal_replay.h"
#include "common/rt64_wr64_fish_school.h"
#include "common/rt64_wr64_sprite_families.h"
#include "common/rt64_wr64_dolphin_identity.h"
#include "common/rt64_wr64_dolphin_trace.h"
#include "common/rt64_wr64_drake_school.h"
#include "common/rt64_wr64_whale_identity.h"
#include "common/rt64_wr64_duck_identity.h"
#include "hle/rt64_transform_group.h"
#include "shared/rt64_hlsl.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <unordered_map>

// Only the storage touched by the extracted production functions is modeled;
// matrices, rectangles, transform groups and identity classifiers are real RT64.
namespace RT64 {
struct DrawCall {
    uint32_t triangleCount = 2, tileCount = 1, tileIndex = 0, minWorldMatrix = 0;
    struct Mode { uint32_t H, L; } colorCombiner{0xFFFFF238,0xFC127FFF},
        otherMode{0x00182CFF,0xC8113078};
};
struct GameCall { DrawCall callDesc; };
struct Projection {
    enum class Type { Perspective, Orthographic };
    Type type = Type::Perspective;
    uint32_t gameCallCount = 0;
    std::vector<GameCall> gameCalls;
    FixedRect scissorRect;
};
struct FramebufferPair { uint32_t projectionCount = 0; std::vector<Projection> projections; };
struct DrawData {
    std::vector<float> posFloats, tcFloats;
    std::vector<uint8_t> normColBytes;
    std::vector<uint32_t> vertexSegmentedAddresses, worldIndices;
    std::vector<interop::float4x4> worldTransforms;
    std::vector<TransformGroup> transformGroups{TransformGroup{}};
    std::vector<uint32_t> worldTransformGroups, worldTransformSegmentedAddresses,
        worldTransformPhysicalAddresses, worldTransformVertexIndices;
    struct Tile { uint64_t tmemHashOrID; };
    std::vector<Tile> callTiles;
    uint32_t vertexCount() const { return uint32_t(worldIndices.size()); }
    uint32_t worldTransformVertexCount(uint32_t i) const {
        return ((i + 1 < worldTransformVertexIndices.size()) ? worldTransformVertexIndices[i+1]
            : vertexCount()) - worldTransformVertexIndices[i];
    }
};
struct Workload { DrawData drawData; uint32_t fbPairCount = 1;
    std::vector<FramebufferPair> fbPairs{FramebufferPair{}}; uint64_t submissionFrame = 0; };
}
#include "identity_functions.inc"

using namespace RT64;
static size_t checks=0;
static void check(bool value,const char* message) {
    ++checks; if (!value) { std::cerr << message << '\n'; std::exit(1); }
}
static uint32_t id(const Workload& w,uint32_t t) {
    return w.drawData.transformGroups.at(w.drawData.worldTransformGroups.at(t)).matrixId;
}
static const TransformGroup& group(const Workload& w,uint32_t t) {
    return w.drawData.transformGroups.at(w.drawData.worldTransformGroups.at(t));
}
static bool sameGroup(const TransformGroup& a,const TransformGroup& b) {
    return a.matrixId==b.matrixId && a.ordering==b.ordering && a.decompose==b.decompose &&
        a.positionInterpolation==b.positionInterpolation && a.rotationInterpolation==b.rotationInterpolation &&
        a.scaleInterpolation==b.scaleInterpolation && a.skewInterpolation==b.skewInterpolation &&
        a.perspectiveInterpolation==b.perspectiveInterpolation && a.vertexInterpolation==b.vertexInterpolation &&
        a.texcoordInterpolation==b.texcoordInterpolation && a.tileInterpolation==b.tileInterpolation;
}
static Workload make(const std::vector<uint64_t>& textures,bool split,uint64_t frame=1,
    const std::vector<uint32_t>& owners={}) {
    Workload w; w.submissionFrame=frame;
    auto& fb=w.fbPairs[0]; fb.projectionCount=split?2:1; fb.projections.resize(fb.projectionCount);
    for(uint32_t view=0;view<fb.projectionCount;++view) {
        auto& p=fb.projections[view]; p.scissorRect=FixedRect(0,view*480,1280,(view+1)*480);
        for(uint32_t i=0;i<textures.size();++i) {
            const uint32_t owner=owners.empty()?i:owners[i];
            auto& d=w.drawData; const uint32_t t=uint32_t(d.worldTransforms.size());
            auto m=interop::float4x4::identity(); m[3][0]=owner*300.0f+float(frame);
            d.worldTransforms.push_back(m); d.worldTransformGroups.push_back(0);
            d.worldTransformSegmentedAddresses.push_back(0x06000000+i*64);
            d.worldTransformPhysicalAddresses.push_back(0x360000+i*64);
            d.worldTransformVertexIndices.push_back(d.vertexCount());
            for(uint32_t v=0;v<4;++v) {
                d.worldIndices.push_back(t); d.posFloats.insert(d.posFloats.end(),{float(v),float(v&1),0});
                d.tcFloats.insert(d.tcFloats.end(),{float(v),float(v)});
                d.normColBytes.insert(d.normColBytes.end(),{255,255,255,255});
                d.vertexSegmentedAddresses.push_back(0x0A000000+owner*64+v*16);
            }
            DrawCall c; c.tileIndex=uint32_t(d.callTiles.size()); c.minWorldMatrix=t;
            d.callTiles.push_back({textures[i]}); p.gameCalls.push_back({c}); ++p.gameCallCount;
        }
    }
    return w;
}
static Wr64AnimalReplayUses uses(const Workload& w) {
    Wr64AnimalReplayUses u;
    for(uint32_t f=0;f<w.fbPairCount;++f) for(const auto& p:w.fbPairs[f].projections)
        for(const auto& c:p.gameCalls) wr64AnimalReplayRecord(u,c.callDesc.minWorldMatrix,f,
            p.scissorRect,c.callDesc,w.drawData.callTiles[c.callDesc.tileIndex].tmemHashOrID);
    return u;
}
static void rejects() {
    const auto base=make({Wr64FishClownfish},true);
    check(wr64AnimalReplayAliases(base.drawData,uses(base)).size()==1,"exact copies were not aliased");
    auto vertical=base;
    vertical.fbPairs[0].projections[0].scissorRect=FixedRect(0,0,640,960);
    vertical.fbPairs[0].projections[1].scissorRect=FixedRect(640,0,1280,960);
    check(wr64AnimalReplayAliases(vertical.drawData,uses(vertical)).size()==1,
        "vertical split copies were not aliased");
    for(int kind=0;kind<15;++kind) {
        auto w=base; auto& d=w.drawData;
        switch(kind) {
        case 0: w.fbPairs[0].projections[1].scissorRect=FixedRect(0,0,1280,480); break;
        case 1: w.fbPairs[0].projections[1].scissorRect=FixedRect(0,479,1280,960); break;
        case 2: w.fbPairs[0].projections[1].scissorRect=FixedRect(0,0,0,0); break;
        case 3: d.worldTransformSegmentedAddresses[1]+=64; break;
        case 4: d.worldTransformPhysicalAddresses[1]+=64; break;
        case 5: d.worldTransforms[1][3][0]+=1; break;
        case 6: d.posFloats[12]+=1; break;
        case 7: d.tcFloats[8]+=1; break;
        case 8: d.normColBytes[16]=0; break;
        case 9: d.vertexSegmentedAddresses[4]+=16; break;
        case 10: d.posFloats.pop_back(); break;
        case 11: d.callTiles[1].tmemHashOrID=Wr64FishBlueTang; break;
        case 12: w.fbPairs[0].projections[1].gameCalls[0].callDesc.triangleCount=4; break;
        case 13: d.worldTransformPhysicalAddresses[0]=d.worldTransformPhysicalAddresses[1]=0; break;
        case 14: d.worldTransformVertexIndices[1]=d.vertexCount(); break;
        }
        check(wr64AnimalReplayAliases(d,uses(w)).empty(),"near-copy was incorrectly aliased");
    }
    auto u=uses(base); u[1].framebuffer=1;
    check(wr64AnimalReplayAliases(base.drawData,u).empty(),"different framebuffers merged");
    u=uses(base); u[0].ambiguous=true;
    check(wr64AnimalReplayAliases(base.drawData,u).empty(),"ambiguous viewport merged");
}
static void additionalFamilies() {
    using Stamp = void (*)(Workload&);
    struct Family { uint64_t texture; Stamp original, fixed; bool (*ours)(uint32_t); uint32_t segment; bool whaleG1; };
    const Family families[] = {
        {*wr64DolphinTextures().begin(), wr64DolphinStampTransformIdentityBaseline, wr64DolphinStampTransformIdentity, wr64DolphinIsOurs, 0x06000000, false},
        {Wr64DrakeSchoolTexture, wr64DrakeSchoolStampTransformIdentityBaseline, wr64DrakeSchoolStampTransformIdentity, wr64DrakeSchoolIsOurs, 0x06000000, false},
        {*wr64WhaleG1Textures().begin(), wr64WhaleStampTransformIdentityBaseline, wr64WhaleStampTransformIdentity, wr64WhaleIsOurs, 0x03000000, true},
        {*wr64WhaleG2Textures().begin(), wr64WhaleStampTransformIdentityBaseline, wr64WhaleStampTransformIdentity, wr64WhaleIsOurs, 0x06000000, false},
        {Wr64DuckTextureBody, wr64DuckStampTransformIdentityBaseline, wr64DuckStampTransformIdentity, wr64DuckIsOurs, 0x06000000, false}
    };
    uint64_t frame = 9000;
    for (const auto &family : families) {
        auto animal = [&](bool split, uint64_t tick) {
            auto w = make(std::vector<uint64_t>(7, family.texture), split, tick);
            for (uint32_t t = 0; t < w.drawData.worldTransforms.size(); ++t) {
                const uint32_t slot = t % 7;
                w.drawData.worldTransformSegmentedAddresses[t] = family.segment + 0x610 + slot * 64;
                w.drawData.worldTransformPhysicalAddresses[t] = 0x360610 + slot * 64;
                w.drawData.worldTransforms[t][3][0] = float(slot * 10);
            }
            if (family.whaleG1) for (auto &p : w.fbPairs[0].projections) for (auto &c : p.gameCalls)
                c.callDesc.otherMode = {Wr64WhaleG1OtherModeHA, Wr64WhaleG1OtherModeLA};
            return w;
        };
        auto one = animal(false, frame), originalOne = one;
        family.original(originalOne); family.fixed(one);
        for (uint32_t t = 0; t < 7; ++t) {
            check(family.ours(id(one,t)), "native family texture/slot not claimed");
            check(sameGroup(group(one,t),group(originalOne,t)), "single-view identity recipe changed");
        }
        auto split = animal(true, ++frame), originalSplit = split;
        family.original(originalSplit); family.fixed(split);
        for (uint32_t t = 0; t < 7; ++t) {
            check(family.ours(id(split,t)), "replay representative lost family identity");
            check(sameGroup(group(split,t),group(split,t+7)), "P2 replay lost complete family recipe");
            check(id(originalSplit,t+7)==G_EX_ID_AUTO, "old negative control did not reproduce P2 identity rejection");
        }
        auto jump = animal(true, ++frame);
        for (auto &m : jump.drawData.worldTransforms) m[3][0] += 5000;
        family.fixed(jump);
        for (uint32_t t = 0; t < 7; ++t) {
            check(group(jump,t).positionInterpolation==G_EX_COMPONENT_SKIP, "native family continuity guard changed");
            check(sameGroup(group(jump,t),group(jump,t+7)), "P2 did not inherit native continuity snap");
        }
        auto nearCopy = animal(true, ++frame);
        nearCopy.drawData.posFloats[7*4*3] += 1;
        family.fixed(nearCopy);
        check(id(nearCopy,7)==G_EX_ID_AUTO, "different geometry incorrectly reused identity");
        auto overlap = animal(true, ++frame);
        overlap.fbPairs[0].projections[1].scissorRect=overlap.fbPairs[0].projections[0].scissorRect;
        family.fixed(overlap);
        for (uint32_t t = 7; t < 14; ++t) check(id(overlap,t)==G_EX_ID_AUTO, "overlapping draw incorrectly treated as replay");
        frame += 100;
    }
    auto ghost=make({*wr64DolphinTextures().begin()},true,10000);
    ghost.drawData.transformGroups[0].matrixId=0x57F00010;
    wr64DolphinStampTransformIdentity(ghost);
    check(id(ghost,0)==0x57F00010 && id(ghost,1)==0x57F00010, "Time Trial ghost identity changed");
}
int main() {
    rejects();
    const std::vector<uint64_t> partial(3,Wr64FishClownfish);
    auto broken=make(partial,true,10), fixed=broken;
    wr64FishStampTransformIdentityBaseline(broken); wr64FishStampTransformIdentity(fixed);
    for(uint32_t i=0;i<3;++i) {
        check(id(broken,i+3)==G_EX_ID_AUTO,"negative control did not reproduce P2 ordinal failure");
        check(id(fixed,i)==wr64FishSchoolId(0,0,i),"P1 IDs changed");
        check(sameGroup(group(fixed,i),group(fixed,i+3)),"P2 did not inherit full interpolation recipe");
    }
    std::vector<uint64_t> full;
    for(int g=0;g<2;++g) for(auto texture:{Wr64FishClownfish,Wr64FishButterflyfish,Wr64FishBlueTang})
        full.insert(full.end(),3,texture);
    for(uint64_t frame=20;frame<24;++frame) {
        const auto& roster=(frame&1)?partial:full;
        auto w=make(roster,true,frame), original=make(roster,false,frame), baseline=original;
        wr64FishStampTransformIdentity(w); wr64FishStampTransformIdentity(original);
        wr64FishStampTransformIdentityBaseline(baseline);
        std::set<uint32_t> ids;
        for(uint32_t i=0;i<roster.size();++i) {
            check(sameGroup(group(w,i),group(w,i+uint32_t(roster.size()))),"roster change split copies");
            check(id(w,i)==id(original,i),"second view renumbered first view");
            check(id(original,i)==id(baseline,i),"single player ID regression");
            check(sameGroup(group(original,i),group(baseline,i)),"single player interpolation recipe changed");
            check(id(w,i)!=G_EX_ID_AUTO,"valid replay animal left unnamed"); ids.insert(id(w,i));
        }
        check(ids.size()==roster.size(),"distinct fish merged");
    }
    const std::vector<uint64_t> birds{Wr64SeagullFarTexture,Wr64SeagullFarTexture};
    auto birds1=make(birds,true,100);
    wr64SpriteFamilyStampTransformIdentity(birds1);
    const uint32_t a=id(birds1,0),b=id(birds1,1);
    check(a!=b,"different birds merged");
    check(id(birds1,2)==a && id(birds1,3)==b,"bird replay minted extra identities");
    auto birds2=make(birds,true,101,{1,0});
    wr64SpriteFamilyStampTransformIdentity(birds2);
    check(id(birds2,0)==b && id(birds2,1)==a,"bird identity followed recycled matrix slots");
    check(id(birds2,2)==b && id(birds2,3)==a,"bird aliases lost trajectory identities");
    check(birds2.drawData.worldTransforms.size()==4,"replay created phantom remembered birds");
    auto birds3=make({Wr64SeagullFarTexture},true,102,{0});
    wr64SpriteFamilyStampTransformIdentity(birds3);
    check(id(birds3,0)==a && id(birds3,1)==a,"roster shrink lost surviving bird");
    check(birds3.drawData.worldTransforms.size()==3,"missing bird must have exactly one ghost");
    check(group(birds3,2).vertexInterpolation==G_EX_COMPONENT_SKIP,"ghost vertex protection changed");
    auto unrelated=make({0x123456789ULL},true,103);
    wr64FishStampTransformIdentity(unrelated); wr64SpriteFamilyStampTransformIdentity(unrelated);
    check(id(unrelated,0)==G_EX_ID_AUTO && id(unrelated,1)==G_EX_ID_AUTO,"unrelated family changed");
    additionalFamilies();
    std::cout << "PASS " << checks << " checks: production fish/bird/dolphin/Drake-school/whale/duck identities, exact replay guards, "
        "partial schools, two-view copies, shuffled bird slots, ghost carry, and Original controls\n";
}
