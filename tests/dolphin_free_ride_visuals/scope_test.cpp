#include "common/rt64_wr64_rt_two_player_assets.h"
#include "common/rt64_wr64_rt_scope.h"
#include "common/rt64_wr64_rt_shadow.h"
#include "common/rt64_wr64_planar_reflection_math.h"
#include "common/rt64_wr64_far_water_distance.h"
#include "common/rt64_wr64_water_roundness.h"
#include "common/rt64_wr64_dolphin_sun_edge.h"
#include "common/rt64_wr64_wave_distance.h"
#include <bit>
#include <cstdlib>
#include <iostream>
#include <vector>

unsigned checks=0;
void require(bool v,const char* why) { ++checks;if(!v){std::cerr<<"FAIL "<<why<<'\n';std::exit(1);} }
int main() {
    using namespace RT64;
    std::vector<uint8_t> ram(0x800000),other(0x800000);
    for(unsigned course=0;course<=8;++course) {
        wr64RTPublishTwoPlayerAssets(ram.data(),course);
        for(unsigned candidate=0;candidate<=10;++candidate) {
            require(wr64RTTwoPlayerAssetsReady(ram.data(),candidate)==(candidate==course),"publication leaked across course");
            require(!wr64RTTwoPlayerAssetsReady(other.data(),candidate),"publication leaked across RAM identity");
        }
    }
    wr64RTPublishTwoPlayerAssets(ram.data(),9);
    require(!wr64RTTwoPlayerAssetsReady(ram.data(),8),"invalid publication did not revoke old owner");
    wr64RTPublishTwoPlayerAssets(ram.data(),0);
    wr64RTPublishTwoPlayerAssets(nullptr,0);
    require(!wr64RTTwoPlayerAssetsReady(ram.data(),0),"load reset retained Dolphin ownership");
    for(unsigned course=0;course<=10;++course) for(unsigned players=0;players<=3;++players)
      for(unsigned phase=0;phase<=10;++phase) for(unsigned mode=0;mode<=64;++mode)
       for(bool loaded:{false,true}) for(bool selected:{false,true}) {
        const bool scene=course<=8&&players==2&&phase==1&&mode>=40&&mode<=45;
        const bool enhanced=scene&&loaded&&selected;
        require(wr64RTTwoPlayerReflectionScope(selected,course,players,phase,mode,loaded)==enhanced,"reflection admission ignored scene/loaded gate");
        require(wr64RTTwoPlayerShadowScope(selected,loaded,course,players,phase,mode)==enhanced,"shadow admission differs from loaded reflection domain");
        require(wr64NativeSplitWaterScope(course,players,phase,mode,loaded)==(scene&&(course!=0||loaded)),"split roundness admission changed established courses");
        const bool single=players==1&&course<=8&&(phase==1||(phase==8&&(mode==30||mode==31))||(course==0&&phase==0&&mode>=2&&mode<=4));
        require(wr64RTReflectionScope(selected,course,players,phase,mode)==(selected&&single),"one-player reflection policy changed");
        for(unsigned view=0;view<2;++view)
          require(wr64FarWaterDistanceScope(course,players,phase,mode,view,view,3,view,loaded)==((single||(scene&&(course!=0||loaded)))&&view<players),"far sheet did not retain per-view loaded scope");
        if(players==2) require(wr64DolphinSunEdgeScope(course,players,phase,mode)==Wr64DolphinSunEdgeScope::None,"1P parked/exit policy escaped into 2P");
       }
    auto put=[&](uint32_t offset,uint32_t value){std::memcpy(ram.data()+offset,&value,4);};
    for(unsigned course=0;course<=8;++course) {
        const unsigned preset=0xD9964+course*0x110;
        for(unsigned i=0;i<3;++i) {
            put(preset+i*4,150+i);put(preset+0xC+i*4,30+i);
            put(preset+0xAC+i*4,std::bit_cast<uint32_t>(i==1?85.0f:0.0f));
        }
        // Sunset additionally validates two native sine-table entries.
        put(0x154350+56*4,std::bit_cast<uint32_t>(float(std::sin(56.0*2.0*std::acos(-1.0)/4096.0))));
        put(0x154350+1080*4,std::bit_cast<uint32_t>(float(std::cos(56.0*2.0*std::acos(-1.0)/4096.0))));
        put(0x154350+0x800,std::bit_cast<uint32_t>(0.70710677f));
        put(0x154350+0x3800,std::bit_cast<uint32_t>(-0.70710677f));
        const auto one=wr64RTShadowReadLight(ram.data(),ram.size(),course,1);
        const auto two=wr64RTTwoPlayerShadowReadLight(ram.data(),ram.size(),course,2,true);
        require(one.valid&&two.valid&&one.toLight==two.toLight&&one.diffuse==two.diffuse&&one.ambient==two.ambient,"2P light differs from authored 1P policy");
        require(!wr64RTTwoPlayerShadowReadLight(ram.data(),ram.size(),course,2,false).valid,"unvalidated 2P light accepted");
        put(0x192458,uint32_t(-77));
        require(wr64ReadPlanarWaterDatum(ram.data(),ram.size(),course,2,true).height==-77,"shared native water datum not read");
        require(!wr64ReadPlanarWaterDatum(ram.data(),ram.size(),course,2,false).valid,"unvalidated planar datum accepted");
    }
    for(unsigned type:{0u,1u,2u,6u,99u}) require(!wr64FarWaterDistanceScope(0,2,1,40,1,1,type,1,true),"invalid camera type accepted");
    require(!wr64FarWaterDistanceScope(0,2,1,40,1,1,3,0,true),"wrong camera owner accepted");
    require(!wr64FarWaterDistanceScope(0,2,1,40,1,2,3,2,true),"invalid camera selector accepted");
    // Consumer ownership test for the native shared 16-ring sheet. The source
    // bytes are opaque fixture data: this checks sealed identity/reuse, not
    // wave simulation or mesh reconstruction.
    put(0xD8170,0);put(0xDAB28,2);put(0x1CE638,1);put(0xDAB24,40);
    put(0x1CE64C,1);put(0x192494,16);put(0x223930,0);put(0x223934,1);
    put(0x227C80+0x10C,3);put(0x227C80+0x10C+0xE8,1);
    Wr64WaveDistancePacket packet;
    packet.ram=ram.data();packet.pool=0x11F8E8;
    auto &snapshot=packet.snapshot;
    snapshot.valid=true;snapshot.course=0;snapshot.players=2;snapshot.phase=1;
    snapshot.raceMode=40;snapshot.sea=1;snapshot.rings=16;snapshot.view=0;snapshot.camera=0;
    packet.nativeVertices.resize(817*16,0x5A);
    const uint32_t source=packet.pool+(snapshot.sourceAddress&0xFFFFFF);
    std::memcpy(ram.data()+source,packet.nativeVertices.data(),packet.nativeVertices.size());
    std::vector<Wr64WaveDistancePacket> packets{packet};
    const auto pair=wr64ConsumeWaveDistance(ram.data(),ram.size(),packet.pool,&packets);
    require(pair[0].valid&&pair[1].valid&&pair[1].producerSealed&&pair[1].view==1&&pair[1].camera==1,"authenticated Dolphin shared sheet lost second camera");
    require(pair[0].sourceAddress==pair[1].sourceAddress,"shared sheet changed source identity");
    ram[source]^=1;
    const auto stale=wr64ConsumeWaveDistance(ram.data(),ram.size(),packet.pool,&packets);
    require(!stale[0].valid&&!stale[1].valid,"stale source reused across either camera");
    std::cout<<"PASS "<<checks<<" loaded visual and unchanged-domain checks\n";
}
