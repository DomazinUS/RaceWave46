#include "common/rt64_wr64_hud_anchor.h"
#include "common/rt64_wr64_celestial_identity.h"
#include "common/rt64_wr64_vertical_split.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace RT64 {
struct Projection { enum class Type { None, Perspective, Orthographic, Rectangle }; Type type = Type::Rectangle; };
struct Call { struct { FixedRect rect, scissorRect; } callDesc; };
}
#include "renderer_anchor.inc"
using namespace RT64;
static unsigned checks = 0;
static void require(bool ok, const char *text) { ++checks; if (!ok) { std::fprintf(stderr,"FAIL %s\n",text);std::exit(1); } }
static bool equal(const FixedRect &a, const FixedRect &b) { return a.ulx==b.ulx && a.uly==b.uly && a.lrx==b.lrx && a.lry==b.lry; }
static FixedRect halfScissor(int half) { return {0, half==2?480:0, 1696, half==1?480:960}; }
int main() {
    Projection projection;
    const uint64_t effects[] = {Wr64CelestialSunGlow, Wr64CelestialSunDisk, Wr64CelestialSunFlare, Wr64CelestialTcStar};
    wr64TwoPFrameActiveRef() = true;
    for (uint64_t texture : effects) for (int half=1;half<=2;++half) {
        // Actual native Sunset disk/glow are 48px squares. The prior renderer
        // adds -4px P1 / +6px P2 while their rectangle lies in the HUD box.
        const int top=half==1?36:156;
        for (int x : {18,19,20,21,355,356,357,358}) {
            Call call{{FixedRect(x*4,top*4,(x+48)*4,(top+48)*4),halfScissor(half)}};
            const bool oldMatches=x>=20 && x<=356;
            auto old=applyOldAnchor(projection,call,texture,call.callDesc.rect,false);
            require(old.uly-call.callDesc.rect.uly==(oldMatches?(half==1?-16:24):0),"old edge bob reproduced");
            // The predicate uses native bounds, whereas the rectangle being
            // anchored is already interpolated. Every subframe must retain it.
            for (int blendShift : {-11,-7,-1,0,3,9,12}) {
                auto blended=call.callDesc.rect;
                blended.ulx+=blendShift; blended.lrx+=blendShift;
                blended.uly+=blendShift; blended.lry+=blendShift;
                require(equal(applyProductionAnchor(projection,call,texture,blended,false),blended),"celestial subframe unchanged");
                require(equal(applyProductionAnchor(projection,call,texture,blended,true),
                    applyOldAnchor(projection,call,texture,blended,true)),"vertical scene mapping unchanged");
            }
        }
        // World-relative motion across thirds and all four inset boundaries
        // never becomes HUD anchoring, including smaller star/moon rectangles.
        for (int size : {2,4,24,48}) for (int x=0;x<424;x+=7) for(int y=half==1?0:120;y<(half==1?120:240);y+=13) {
            Call c{{FixedRect(x*4,y*4,(x+size)*4,(y+size)*4),halfScissor(half)}};
            require(equal(applyProductionAnchor(projection,c,texture,c.callDesc.rect,false),c.callDesc.rect),"scene effect never anchors");
        }
    }
    // Real HUD text and track-marker semantics are untouched in both layouts.
    for (uint64_t texture : {0x123ULL,0x900F997EFF175036ULL,Wr64CelestialDpText}) for(int half=1;half<=2;++half) {
        for(int x : {20,40,147,350}) {
            const int y=half==1?20:130;
            Call c{{FixedRect(x*4,y*4,(x+8)*4,(y+12)*4),halfScissor(half)}};
            require(equal(applyProductionAnchor(projection,c,texture,c.callDesc.rect,false),
                applyOldAnchor(projection,c,texture,c.callDesc.rect,false)),"ordinary HUD retains offsets");
        }
    }
    for(bool twoPlayer : {false,true}) for(uint64_t texture : effects) {
        wr64TwoPFrameActiveRef()=twoPlayer;
        for(auto clip : {FixedRect(0,0,1696,960),FixedRect(1,0,1696,480),FixedRect(0,0,1692,480)}) {
            Call c{{FixedRect(80,144,272,336),clip}};
            require(equal(applyProductionAnchor(projection,c,texture,c.callDesc.rect,false),
                applyOldAnchor(projection,c,texture,c.callDesc.rect,false)),"full and partial scissors unchanged");
        }
        if(!twoPlayer) {
            Call c{{FixedRect(80,144,272,336),halfScissor(1)}};
            require(equal(applyProductionAnchor(projection,c,texture,c.callDesc.rect,false),
                applyOldAnchor(projection,c,texture,c.callDesc.rect,false)),"single-player unchanged");
        }
    }
    std::printf("PASS celestial HUD separation: %u checks\n",checks);
}
