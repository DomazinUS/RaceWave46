#include "common/rt64_wr64_hud_anchor.h"
#include "common/rt64_wr64_banner_anchor.h"
#include "common/rt64_wr64_ultrawide.h"
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unordered_set>

using namespace RT64;
static size_t checks = 0;
static void require(bool ok, const char *message) {
    ++checks;
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
static void near(float a, float b, const char *message) {
    require(std::abs(a-b) < 0.001f, message);
}

struct Banner {
    int32_t projection = 2;
    uint64_t texture = Wr64MaxPowerTexture;
    uint16_t width = 144, height = 20;
    uint32_t triangles = 2, tiles = 1;
    uint8_t textureOn = 1;
    uint32_t combinerH = 0xFF33FFFF, combinerL = 0xFC121824;
    uint32_t modeH = 0x00082CFF, modeL = 0x00504240;
    bool matches() const {
        return wr64BannerAnchorMatch(projection, texture, width, height,
            triangles, tiles, textureOn, combinerH, combinerL, modeH, modeL);
    }
};

// Negative control: the old composer's exact byte hash and finite emission
// table. The captured E3B35A5A1E8A3123 MAX POWER entry checks byte widths/order.
template<typename T> static void mix(uint64_t &h, T value) {
    for (size_t i = 0; i < sizeof(T); ++i) {
        h = (h ^ uint8_t(uint64_t(value) >> (8*i))) * 1099511628211ULL;
    }
}
static uint64_t oldSignature(const Banner &b, uint32_t pair, uint32_t projection,
    uint32_t call, int32_t rectWidth, int32_t rectHeight) {
    uint64_t h = 14695981039346656037ULL;
    mix(h,pair); mix(h,projection); mix(h,call); mix(h,uint32_t(b.projection));
    mix(h,b.triangles); mix(h,rectWidth); mix(h,rectHeight); mix(h,b.tiles);
    mix(h,b.textureOn); mix(h,b.combinerH); mix(h,b.combinerL);
    mix(h,b.modeH); mix(h,b.modeL); mix(h,b.texture); mix(h,b.width); mix(h,b.height);
    return h;
}

int main() {
    wr64TwoPFrameRenderWorkload(false);
    const FixedRect target(214*4,42*4,230*4,54*4);
    // Native DrawStatus puts target immediately below its 8x10 arrow (y32..42).
    // All five states must take the arrow's existing -18px correction.
    const std::array<uint64_t,5> targets = {0x5009956E5CCCD2A2ULL,
        0x0FB5914E291DA6BAULL,0x83428B1A568E7E20ULL,
        0xCF3E0D0EE9A5E075ULL,0xF0CBDEEB5EBD7CE6ULL};
    for (auto hash : targets) {
        int32_t dx=0,dy=0;
        require(wr64HudAnchorOffsetForRect(3,target,hash,dx,dy), "advancement target glyph was not recognized");
        require(dx==0 && dy==-72, "target must follow its arrow's existing translation");
        require(wr64HudUltrawideAnchor(target,hash)==0, "rank must stay centered");
        for (float aspect : {4.0f/3,16.0f/9,21.0f/9,32.0f/9}) {
            const float expansion=wr64UltrawideExpansion(aspect);
            const auto layout=wr64UltrawideLayout(3*expansion,3,424);
            near(layout.position(214*3*expansion)-layout.width/2,6,
                "target changed its position relative to center");
            near((42+dy/4.0f)*3,(32+10-18)*3,"target detached vertically from arrow");
            near(layout.extent(16*3*expansion),48,"target glyph resized");
        }
        require(!wr64HudAnchorOffsetForRect(2,target,hash,dx,dy),"orthographic shared glyph must remain untouched");
        require(!wr64HudAnchorOffsetForRect(3,FixedRect(120*4,140*4,136*4,152*4),hash,dx,dy),
            "select-font menu use must remain untouched");
        require(!wr64HudAnchorOffsetForRect(3,FixedRect(214*4,60*4,230*4,72*4),hash,dx,dy),
            "shared glyph below rank box must remain untouched");
    }
    int32_t dx=0,dy=0;
    require(!wr64HudAnchorOffsetForRect(3,target,0x1234,dx,dy),"unknown glyph at target position was claimed");
    require(!wr64HudAnchorOffsetForRect(3,target,0xA96DAD369EB6FD77ULL,dx,dy),
        "digit zero is not an advancement target and must not be added");

    std::array<Banner,2> banners{};
    banners[1].texture=Wr64PowerUpTexture; banners[1].width=128;
    std::unordered_set<uint64_t> oldTable;
    for (const auto &b : banners) for (bool small : {false,true})
        for (uint32_t pair=0;pair<3;++pair) for (uint32_t pr=0;pr<6;++pr)
            for (uint32_t call=0;call<4;++call)
                oldTable.insert(oldSignature(b,pair,pr,call,small?10:424,small?10:240));
    require(oldTable.size()==288,"old signature enumeration changed");
    require(oldTable.count(0xE3B35A5A1E8A3123ULL)==1,
        "negative-control hash does not reproduce captured MAX POWER signature");
    size_t formerlyRejected=0;
    for (const auto &b : banners) for (bool small : {false,true})
        for (uint32_t pair=0;pair<5;++pair) for (uint32_t pr=0;pr<12;++pr)
            for (uint32_t call=0;call<12;++call) {
                formerlyRejected += oldTable.count(oldSignature(b,pair,pr,call,small?10:424,small?10:240))==0;
                require(b.matches(),"banner correction depended on emission order or rectangle form");
                int half=0; bool placeable=false;
                wr64BannerAnchorOffset(206,dx,dy,half,placeable);
                require(dx==44 && dy==76,"native single-player banner translation changed");
            }
    require(formerlyRejected==2592,"negative control failed to expose formerly missed banners");
    for (const auto &b : banners) {
        for (unsigned mutation=0;mutation<12;++mutation) {
            auto bad=b;
            switch(mutation) {
                case 0: bad.projection=1; break;
                case 1: bad.projection=3; break;
                case 2: bad.texture^=1; break;
                case 3: ++bad.width; break;
                case 4: ++bad.height; break;
                case 5: ++bad.triangles; break;
                case 6: ++bad.tiles; break;
                case 7: bad.textureOn=0; break;
                case 8: bad.combinerH^=1; break;
                case 9: bad.combinerL^=1; break;
                case 10: bad.modeH^=1; break;
                case 11: bad.modeL^=1; break;
            }
            require(!bad.matches(),"unrelated texture, geometry or render state matched banner");
        }
        for(float aspect : {4.0f/3,16.0f/9,21.0f/9,32.0f/9}) {
            const float expansion=wr64UltrawideExpansion(aspect);
            const auto layout=wr64UltrawideLayout(3*expansion,3,424);
            int half=0; bool placeable=false;
            wr64BannerAnchorOffset(206,dx,dy,half,placeable);
            const float bannerX=layout.position((404+dx/4.0f)*3*expansion,1);
            const float meterX=layout.position((404+11)*3*expansion,1);
            near(bannerX,meterX,"banner and meter must share right anchor at every aspect");
            near(layout.extent(b.width*.7f*3*expansion),b.width*.7f*3,"settled banner scale changed");
        }
    }
    // Reuse the established per-half banner transform lookup. Matching changes
    // must not reinstate the old shared +19px which crossed the player seam.
    wr64TwoPFrameRenderWorkload(true);
    for (float worldY : {96.0f,206.0f,-1.0f}) {
        int half=0; bool placeable=false;
        wr64BannerAnchorOffset(worldY,dx,dy,half,placeable);
        require(dx==Wr64TwoPHudDxRight4,"two-player horizontal offset changed");
        require(dy==(placeable?wr64TwoPHudDy4(half):0),"two-player banner left its own HUD half");
    }
    wr64TwoPFrameRenderWorkload(false);
    std::cout << checks << " HUD identity checks passed; " << formerlyRejected
        << " previously rejected banner emission sites covered\n";
}
