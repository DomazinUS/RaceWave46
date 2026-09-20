#include "wr64_split_screen.hpp"
#include "common/rt64_wr64_split_marker.h"
#include "common/rt64_wr64_viewport_pair.h"
#include "common/rt64_wr64_vertical_split.h"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

void registered_split_schema(recomp::config::Config&);

namespace {
unsigned assertions=0, markerCases=0,pauseCases=0;
bool multiplayer=false;
unsigned multiplayerCalls=0;
std::filesystem::path profileDirectory;
void require(bool condition,const char* message) {
    ++assertions;
    if (!condition) throw std::runtime_error(message);
}
void close(float actual,float expected,const char* message) {
    require(std::isfinite(actual) && std::abs(actual-expected)<0.001f,message);
}
template<class T> void put(std::vector<uint8_t>& bytes,uint32_t address,T value) {
    const auto offset=(address&0x7FFFFFU)^(sizeof(T)==2?2U:0U);
    std::memcpy(bytes.data()+offset,&value,sizeof(value));
}
constexpr uint32_t Pool=0x80300000, Cursor=Pool+0x100, Player=0x800DAB28;
struct NativeCase {
    bool enabled=true;
    int32_t players=2,state=1,mode=40;
    int16_t pause=-1,owner=0;
    uint32_t pool=Pool,cursor=Cursor;
};
void marker_case(const NativeCase& input,bool emits,uint8_t expectedOwner=0) {
    std::vector<uint8_t> memory(0x800000,0xCD);
    put(memory,Player,input.players);
    put(memory,0x801CE638,input.state);
    put(memory,0x800DAB24,input.mode);
    put(memory,0x801518B8,input.pool);
    put(memory,0x801CE624,input.pause);
    put(memory,0x801CE62C,input.owner);
    auto expected=memory;
    if (emits) {
        put(expected,input.cursor,RT64::Wr64SplitMarker);
        put(expected,input.cursor+4,RT64::Wr64SplitVersion|uint32_t(expectedOwner));
    }
    wr64::split_screen::set_vertical(input.enabled);
    const auto calls=multiplayerCalls;
    const auto end=wr64_split_screen_frame(memory.data(),input.cursor);
    require(end==input.cursor+(emits?8U:0U),"Native marker changed the wrong display-list cursor");
    require(memory==expected,"Native marker changed game memory outside its eight-byte metadata packet");
    require(multiplayerCalls==calls+1 && multiplayer==(input.players==2),
        "Player input routing must follow the native player count independently of layout activation");
    if (emits) {
        bool vertical=false;uint8_t owner=0xCC;
        uint32_t word0,word1;
        std::memcpy(&word0,memory.data()+(input.cursor&0x7FFFFF),4);
        std::memcpy(&word1,memory.data()+((input.cursor+4)&0x7FFFFF),4);
        require(RT64::wr64DecodeSplitMarker(word0,word1,vertical,owner) && vertical && owner==expectedOwner,
            "Native marker was not accepted by the real RSP metadata decoder");
    }
    ++markerCases;
}
void native_marker_contract() {
    require(!wr64::split_screen::vertical(),"Vertical split must default off before a profile is loaded");
    const auto inputCalls=multiplayerCalls;
    require(wr64_split_screen_frame(nullptr,Cursor)==Cursor && multiplayerCalls==inputCalls,
        "A missing native memory context must remain inert");
    for (const bool enabled:{false,true}) for (const int players:{1,2,3})
    for (const int state:{0,1,4,8,10,18}) for (const int mode:{39,40,41,42,43,44,45,46}) {
        NativeCase c;c.enabled=enabled;c.players=players;c.state=state;c.mode=mode;
        marker_case(c,enabled && players==2 && state==1 && mode>=40 && mode<=45);
    }
    for (const int16_t pause:{int16_t(-1),int16_t(0),int16_t(1),int16_t(3)})
    for (const int16_t owner:{int16_t(-1),int16_t(0),int16_t(1),int16_t(2),int16_t(3)}) {
        NativeCase c;c.pause=pause;c.owner=owner;
        marker_case(c,true,pause>=0 && (owner==1 || owner==2)?uint8_t(owner):0);
    }
    for (const uint32_t cursor:{Pool,Pool+0x57F8,Pool+0x5800,Pool-8,Pool+1,Pool+0x6000}) {
        NativeCase c;c.cursor=cursor;
        marker_case(c,cursor==Pool || cursor==Pool+0x57F8);
    }
    for (const uint32_t pool:{0U,0x00300000U,0xA0300000U,Pool+1,0x807FA000U,0x807FA008U,0x80800000U}) {
        NativeCase c;c.pool=pool;c.cursor=pool;
        marker_case(c,pool==0x807FA000U);
    }
    // Ordinary NOOPs, unknown versions and invalid owner3 must not mutate the
    // caller's previous workload metadata. These are decode gates, not a CRC.
    for (const auto packet:std::array<std::array<uint32_t,2>,7>{{
        {0,0},{RT64::Wr64SplitMarker,0},{RT64::Wr64SplitMarker,0x02000000U},
        {RT64::Wr64SplitMarker,RT64::Wr64SplitVersion|3U},
        {RT64::Wr64SplitMarker,RT64::Wr64SplitVersion|4U},
        {RT64::Wr64SplitMarker^1U,RT64::Wr64SplitVersion},
        {RT64::Wr64SplitMarker|0x01000000U,RT64::Wr64SplitVersion}}}) {
        bool vertical=false;uint8_t owner=0x7A;
        require(!RT64::wr64DecodeSplitMarker(packet[0],packet[1],vertical,owner) && !vertical && owner==0x7A,
            "Unrelated commands or unsupported metadata changed the workload layout");
    }
    wr64::split_screen::set_vertical(false);
    require(!wr64::split_screen::vertical(),"Disabling the enhancement must restore subsequent horizontal frames");
}
std::vector<uint8_t> paused_frame(bool enabled,int16_t owner=1) {
    std::vector<uint8_t> memory(0x800000,0xCD);
    put(memory,Player,int32_t(2));put(memory,0x801CE638,int32_t(1));
    put(memory,0x800DAB24,int32_t(40));put(memory,0x801518B8,Pool);
    put(memory,0x801CE624,int16_t(0));put(memory,0x801CE62C,owner);
    wr64::split_screen::set_vertical(enabled);
    require(wr64_split_screen_frame(memory.data(),Cursor)==Cursor+(enabled?8:0),
        "Pause fixture could not establish its native frame boundary");
    return memory;
}
void pause_command(std::vector<uint8_t>& memory,uint32_t cursor,int begin,bool emits,uint32_t owner=0) {
    auto expected=memory;
    if (emits) {
        put(expected,cursor,RT64::Wr64SplitPauseMarker);
        put(expected,cursor+4,RT64::Wr64SplitVersion|owner);
    }
    const auto calls=multiplayerCalls;
    const auto end=wr64_split_screen_pause(memory.data(),cursor,begin);
    require(end==cursor+(emits?8:0),"Pause boundary returned an incorrect native cursor");
    require(memory==expected,"Pause scope changed label/dimmer data or game state outside its own metadata");
    require(multiplayerCalls==calls,"Pause metadata unexpectedly changed controller routing");
    ++pauseCases;
}
void pause_scope_contract() {
    require(wr64_split_screen_pause(nullptr,Cursor,1)==Cursor,"Missing memory activated a pause scope");
    for (const bool enabled:{false,true}) for (const int16_t owner:
        {int16_t(-1),int16_t(0),int16_t(1),int16_t(2),int16_t(3)}) {
        auto memory=paused_frame(enabled,owner);
        const bool begins=enabled && (owner==1 || owner==2);
        // Cursor+0x80 stands after the native global dimmer; its preceding
        // commands remain byte-identical under the memory comparison.
        pause_command(memory,Cursor+0x80,1,begins,begins?uint32_t(owner):0);
        wr64::split_screen::set_vertical(false);
        pause_command(memory,Cursor+0x100,0,begins);
        pause_command(memory,Cursor+0x108,0,false);
    }
    // Starting pause changes the owner after the earlier frame marker was
    // emitted. The exact draw scope must use that new owner in the same frame.
    {
        auto memory=paused_frame(true,0);
        put(memory,0x801CE62C,int16_t(2));
        pause_command(memory,Cursor+0x80,1,true,2);
        pause_command(memory,Cursor+0x100,0,true);
    }
    for (const uint32_t cursor:{Pool+0x5800,Pool+0x5808,Pool-8,Pool+1}) {
        auto memory=paused_frame(true);
        const bool begins=cursor==Pool+0x5800;
        pause_command(memory,cursor,1,begins,begins?1:0);
        pause_command(memory,Pool+0x5FF8,0,begins);
    }
    // An abandoned scope, including an end beyond the allocated pool, must
    // not leak into another workload, a disabled setting or a full-screen menu.
    for (const int nextState:{1,4,18}) for (const bool nextEnabled:{false,true}) {
        auto memory=paused_frame(true);
        pause_command(memory,Cursor+0x80,1,true,1);
        pause_command(memory,Pool+0x6000,0,false);
        put(memory,0x801CE638,int32_t(nextState));
        wr64::split_screen::set_vertical(nextEnabled);
        const bool active=nextEnabled && nextState==1;
        require(wr64_split_screen_frame(memory.data(),Cursor)==Cursor+(active?8:0),
            "New frame did not re-evaluate its own race/layout gate");
        pause_command(memory,Cursor+0x200,0,false);
        pause_command(memory,Cursor+0x208,1,active,active?1:0);
        pause_command(memory,Cursor+0x210,0,active);
    }
    wr64::split_screen::set_vertical(false);
}
void rect_equal(const RT64::Wr64VerticalRect& a,const RT64::Wr64VerticalRect& b,const char* message) {
    close(a.left,b.left,message);close(a.top,b.top,message);
    close(a.right,b.right,message);close(a.bottom,b.bottom,message);
}
void composition_contract(const RT64::Wr64VerticalLayout& layout,const RT64::Wr64VerticalAffine& affine) {
    for (const std::array<float,4> source: {std::array<float,4>{1,1,0,0}, {0.4f,0.2f,0.1f,-0.2f},
        {1.3f,0.7f,-0.6f,0.3f}}) {
        auto actual=source;
        RT64::wr64VerticalCompose(layout,affine,actual[0],actual[1],actual[2],actual[3]);
        for (const float q:{-1.0f,0.0f,0.75f,1.0f}) {
            const float originalX=(source[0]*q+source[2]-1.0f/layout.width+1)*layout.width*0.5f;
            const float originalY=(1-(source[1]*q+source[3]+1.0f/layout.height))*layout.height*0.5f;
            const float resultX=(actual[0]*q+actual[2]-1.0f/layout.width+1)*layout.width*0.5f;
            const float resultY=(1-(actual[1]*q+actual[3]+1.0f/layout.height))*layout.height*0.5f;
            require(std::abs(resultX-affine.x(originalX))<0.003f &&
                std::abs(resultY-affine.y(originalY))<0.003f,
                "Raster composition disagrees with pixel-space mapping or rescales the half-pixel convention");
        }
    }
}
void layout_contract() {
    using namespace RT64;
    const float nan=std::numeric_limits<float>::quiet_NaN(),inf=std::numeric_limits<float>::infinity();
    for (const auto dimensions:std::array<std::array<float,4>,10>{{
        {0,240,1,0},{424,0,1,0},{1,240,1,0},{424,1,1,0},{424,240,0,0},
        {424,240,-1,0},{nan,240,1,0},{424,inf,1,0},{424,240,nan,0},{424,240,1,-1}}}) {
        const auto l=wr64VerticalLayout(true,dimensions[0],dimensions[1],dimensions[2],dimensions[3]);
        require(!l.active,"Invalid framebuffer geometry activated vertical rendering");
    }
    const auto disabled=wr64VerticalLayout(false,1920,1080,4.5f);
    require(!disabled.active,"Disabled layout activated from merely valid two-player geometry");
    for (const int half:{0,1,2,3}) {
        const auto world=wr64VerticalWorld(disabled,half),hud=wr64VerticalHud(disabled,half,1,1);
        close(world.scale,1,"Disabled world changed size");close(world.x(73),73,"Disabled world moved X");
        close(world.y(49),49,"Disabled world moved Y");close(hud.scale,1,"Disabled HUD changed size");
    }
    std::array<float,4> unchanged{0.6f,0.8f,0.2f,-0.1f},source=unchanged;
    wr64VerticalCompose(disabled,{2,7,11},unchanged[0],unchanged[1],unchanged[2],unchanged[3]);
    require(unchanged==source,"Disabled rendering did not retain its exact shader transform");

    for (const auto dimensions: {std::array<float,2>{1280,720},{1260,540},{3440,1440},
        {1920,540},{1921,1081},{2559,1080},{3841,1080},{424,240}}) {
        const float w=dimensions[0],h=dimensions[1],n=h/240;
        for (const float extension:{0.0f,std::max(0.0f,(w-424*n)*0.5f)}) {
            const auto layout=wr64VerticalLayout(true,w,h,n,extension);
            require(layout.active,"Valid race geometry failed to activate");
            const auto left=wr64VerticalPane(layout,1),right=wr64VerticalPane(layout,2);
            require(left.right==right.left && left.left==0 && right.right==w &&
                left.top==0 && right.top==0 && left.bottom==h && right.bottom==h,
                "Vertical panes overlap or leave a gap");
            require((left.right-left.left)+(right.right-right.left)==w &&
                std::abs((left.right-left.left)-(right.right-right.left))<=1,
                "Odd framebuffer width must assign the spare column exactly once");
            require(layout.hudScale>0 && layout.hudScale<=1 && layout.hudScale*424*n<=left.right+0.001f,
                "HUD fit enlarged a glyph or exceeded the narrower pane");
            for (const int half:{1,2}) {
                const auto pane=wr64VerticalPane(layout,half);
                const auto world=wr64VerticalWorld(layout,half);
                const float cy=h*(half==1?0.25f:0.75f),cx=(pane.left+pane.right)*0.5f;
                close(world.x(w*0.5f),cx,"Player camera is not centered in its own vertical pane");
                close(world.y(cy),h*0.5f,"Player camera is not vertically centered");
                close(world.x(w*0.5f+9)-world.x(w*0.5f),18,"World X scale changed camera geometry");
                close(world.y(cy+9)-world.y(cy),18,"World Y scale differs from X");
                const Wr64VerticalRect originalHalf{0,h*(half-1)*0.5f,w,h*half*0.5f};
                rect_equal(wr64VerticalClip(wr64VerticalMapRect(world,originalHalf),pane),pane,
                    "Mapped world does not fill precisely its own vertical pane");
                composition_contract(layout,world);
                for (const int ax:{-1,0,1}) for (const int ay:{-1,0,1}) {
                    const auto hud=wr64VerticalHud(layout,half,ax,ay);
                    const float sourceX=w*0.5f+ax*(212*n+extension);
                    const float sourceY=h*(half-1)*0.5f+(ay+1)*h*0.25f;
                    const float targetX=ax<0?pane.left:ax>0?pane.right:cx;
                    const float targetY=ay<0?0:ay>0?h:h*0.5f;
                    close(hud.x(sourceX),targetX,"Complete HUD group lost its requested horizontal anchor");
                    close(hud.y(sourceY),targetY,"Complete HUD group lost its requested vertical anchor");
                    close(hud.x(sourceX+12)-hud.x(sourceX),hud.y(sourceY+12)-hud.y(sourceY),
                        "HUD transformation distorted a square glyph");
                    close(hud.x(sourceX+24)-hud.x(sourceX+12),hud.x(sourceX+12)-hud.x(sourceX),
                        "Adjacent glyph spacing changed within a HUD group");
                    composition_contract(layout,hud);
                }
                for (const float dx:{-w*0.125f,0.0f,w*0.125f}) {
                    const float pointX=w*0.5f+dx,pointY=cy+h*0.1f;
                    const auto marker=wr64VerticalMarker(layout,half,pointX,pointY);
                    close(marker.x(pointX),world.x(pointX),"Opponent marker detached from its projected world X");
                    close(marker.y(pointY),world.y(pointY),"Opponent marker detached from its projected world Y");
                    const auto ring=wr64VerticalMapRect(marker,{pointX-10,pointY-10,pointX+10,pointY+10});
                    const auto face=wr64VerticalMapRect(marker,{pointX-5,pointY-5,pointX+5,pointY+5});
                    close(ring.left+ring.right,face.left+face.right,"Opponent portrait separated horizontally from ring");
                    close(ring.top+ring.bottom,face.top+face.bottom,"Opponent portrait separated vertically from ring");
                    close(ring.right-ring.left,ring.bottom-ring.top,"Opponent ring became an ellipse");
                    close(ring.right-ring.left,(face.right-face.left)*2,"Opponent marker pieces use inconsistent scales");
                    composition_contract(layout,marker);
                }
                const auto outside=wr64VerticalClip({pane.right+1,-7,pane.right+10,-2},pane);
                require(outside.right==outside.left && outside.bottom==outside.top,
                    "Fully clipped content emitted a negative or nonempty rectangle");
                require(outside.left>=pane.left && outside.right<=pane.right &&
                    outside.top>=pane.top && outside.bottom<=pane.bottom,
                    "Even an empty hardware scissor must remain within its own pane");
            }
            for (const auto role:{Wr64VerticalViewport::Signal,Wr64VerticalViewport::Indicator}) {
                const float y1=role==Wr64VerticalViewport::Signal?26.0f:28.0f;
                const float y2=role==Wr64VerticalViewport::Signal?146.0f:138.0f;
                const auto first=wr64VerticalAuxiliary(layout,role,1,y1);
                const auto second=wr64VerticalAuxiliary(layout,role,2,y2);
                close(first.y(y1*n),second.y(y2*n),
                    "The two players' secondary HUD models have different destination heights");
                close(first.y(y1*n),y1*n*2,
                    "Secondary HUD model did not retain the first player's native placement");
                for (const int half:{1,2}) {
                    const auto pane=wr64VerticalPane(layout,half);
                    const auto& mapping=half==1?first:second;
                    const float sourceY=(half==1?y1:y2)*n;
                    close(mapping.x(w*0.5f),(pane.left+pane.right)*0.5f,
                        "Secondary HUD model is not centered in its player's pane");
                    close(mapping.scale,layout.hudScale,
                        "Secondary HUD model grew with the world instead of retaining the HUD scale");
                    close(mapping.x(20*n)-mapping.x(0),mapping.y(sourceY+20*n)-mapping.y(sourceY),
                        "Secondary HUD model was stretched along one axis");
                    composition_contract(layout,mapping);
                }
                close(first.x(20*n)-first.x(0),second.x(20*n)-second.x(0),
                    "The two players' secondary HUD models have different sizes");
            }
            for (const auto role:{Wr64VerticalViewport::Shared,Wr64VerticalViewport::World}) {
                const auto invalid=wr64VerticalAuxiliary(layout,role,1,26);
                require(invalid.scale==1 && invalid.dx==0 && invalid.dy==0,
                    "An unrelated viewport inherited the auxiliary HUD transform");
            }
            for (const int half:{-1,0,3}) {
                const auto invalid=wr64VerticalWorld(layout,half);
                require(invalid.scale==1 && invalid.dx==0 && invalid.dy==0,
                    "Unknown player identity inherited a preceding viewport transform");
                const auto auxiliary=wr64VerticalAuxiliary(layout,Wr64VerticalViewport::Indicator,half,138);
                require(auxiliary.scale==1 && auxiliary.dx==0 && auxiliary.dy==0,
                    "Unknown player identity inherited an auxiliary HUD transform");
            }
        }
    }
}
void classification_contract() {
    using namespace RT64;
    const std::array<FixedRect,2> originals{{{0,0,1696,480},{0,480,1696,960}}};
    for (int player=0;player<2;++player) {
        const auto& source=originals[player];
        require(wr64VerticalHalfScissor(source.ulx,source.uly,source.lrx,source.lry)==player+1,
            "Exact corrected native half failed player classification");
        require(wr64ViewportRectsEqual(source,source) && !wr64ViewportRectsEqual(source,originals[1-player]),
            "Native interpolation scissor identity cross-matched the two players");
        for (int edge=0;edge<4;++edge) for (int change:{-1,1}) {
            std::array<int32_t,4> mutated{source.ulx,source.uly,source.lrx,source.lry};mutated[edge]+=change;
            require(wr64VerticalHalfScissor(mutated[0],mutated[1],mutated[2],mutated[3])==0,
                "Approximate or unrelated scissor was guessed to be a player view");
        }
    }
    for (const std::array<int32_t,4> rect: {std::array<int32_t,4>{0,0,1696,960},
        {32,48,1660,480},{0,0,848,960},{848,0,1696,960},{0,0,0,0}})
        require(wr64VerticalHalfScissor(rect[0],rect[1],rect[2],rect[3])==0,
            "Shared HUD, full-frame dimmer or already mapped pane selected a native camera");
    for (const std::array<int32_t,4> rect: {std::array<int32_t,4>{32,476,1660,480},{32,912,1660,916}}) {
        require(wr64VerticalCoverageStrip(rect[0],rect[1],rect[2],rect[3],0x5F505240,0xFFFFFFFF),
            "Actual IPS-selected horizontal coverage cleanup was not identified");
        for (int edge=0;edge<4;++edge) {
            auto changed=rect;changed[edge]+=4;
            require(!wr64VerticalCoverageStrip(changed[0],changed[1],changed[2],changed[3],0x5F505240,0xFFFFFFFF),
                "A different fill rectangle was treated as obsolete horizontal coverage");
        }
        require(!wr64VerticalCoverageStrip(rect[0],rect[1],rect[2],rect[3],0x00504240,0xFFFFFFFF) &&
            !wr64VerticalCoverageStrip(rect[0],rect[1],rect[2],rect[3],0x5F505240,0),
            "Normal color fill or a different render mode was dropped as coverage cleanup");
    }
    struct View {float cy;int half;Wr64VerticalViewport role;};
    const std::array<View,6> views{{
        {60,1,Wr64VerticalViewport::World},{180,2,Wr64VerticalViewport::World},
        {26,1,Wr64VerticalViewport::Signal},{146,2,Wr64VerticalViewport::Signal},
        {28,1,Wr64VerticalViewport::Indicator},{138,2,Wr64VerticalViewport::Indicator}}};
    for (const auto& view:views) for (const float scaleY:{-120.0f,120.0f}) {
        int half=0;
        require(wr64VerticalViewport(212,scaleY,212,view.cy,half)==view.role && half==view.half,
            "Actual USA viewport metadata did not identify its camera or secondary HUD model");
        for (int field=0;field<4;++field) {
            std::array<float,4> changed{212,scaleY,212,view.cy};changed[field]+=0.25f;
            half=2;
            require(wr64VerticalViewport(changed[0],changed[1],changed[2],changed[3],half)==
                Wr64VerticalViewport::Shared && half==0,
                "Unrecognized viewport inherited another player's model classification");
        }
    }
    for (const float y:{0.0f,66.0f,120.0f,176.0f,240.0f,
        std::numeric_limits<float>::quiet_NaN()}) {
        int half=2;
        require(wr64VerticalViewport(212,-120,212,y,half)==Wr64VerticalViewport::Shared && half==0,
            "Shared or obsolete viewport was classified as a current two-player camera");
    }
}
void persistence_contract() {
    namespace fs=std::filesystem;
    profileDirectory=fs::current_path()/("isolated-vertical-profile-"+
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    recomp::config::Config config("Enhancements","enhancements",true);
    registered_split_schema(config);
    config.set_config_directory(profileDirectory);
    wr64::split_screen::set_vertical(true);
    require(config.load_config() && !wr64::split_screen::vertical(),
        "A fresh profile did not apply the real Horizontal default callback");
    const auto path=profileDirectory/"enhancements.json";
    config.update_option_value("split_screen_layout",1u);
    require(wr64::split_screen::vertical(),"Vertical UI selection did not reach the native producer setting");
    require(config.save_config(),"Actual Config could not persist Vertical selection");
    nlohmann::json saved;
    {std::ifstream f(path);f>>saved;}
    require(saved.at("split_screen_layout")=="Vertical","Stored setting does not use the actual schema's stable name");
    wr64::split_screen::set_vertical(false);
    recomp::config::Config reopened("Enhancements","enhancements",true);
    registered_split_schema(reopened);reopened.set_config_directory(profileDirectory);
    require(reopened.load_config() && wr64::split_screen::vertical(),
        "A new Config object did not reload saved Vertical behavior");
    reopened.update_option_value("split_screen_layout",0u);
    require(!wr64::split_screen::vertical(),"Horizontal UI selection did not stop new vertical frames");
    reopened.revert_temp_config();
    require(wr64::split_screen::vertical(),"Discard did not restore the persisted Vertical selection");
    reopened.update_option_value("split_screen_layout",0u);
    require(reopened.save_config(),"Actual Config could not persist Horizontal selection");
    wr64::split_screen::set_vertical(true);
    require(config.load_config() && !wr64::split_screen::vertical(),
        "Horizontal selection did not survive configuration reload");
}
}
namespace wr64::input {
void set_multiplayer_enabled(bool enabled) {multiplayer=enabled;++multiplayerCalls;}
}
namespace recomp {
std::filesystem::path get_config_path() {return profileDirectory;}
const Version& get_project_version() {static const Version version;return version;}
}
int main() {
    try {
        native_marker_contract();
        pause_scope_contract();
        layout_contract();
        classification_contract();
        persistence_contract();
        std::cout<<"Passed "<<markerCases<<" native metadata cases, "<<pauseCases<<
            " pause boundary cases and "<<assertions<<" vertical split assertions.\n";
    } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
