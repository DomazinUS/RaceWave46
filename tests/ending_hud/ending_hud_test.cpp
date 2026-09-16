#include "common/rt64_wr64_hud_motion.h"
#include "common/rt64_wr64_ultrawide.h"
#include "common/rt64_wr64_celestial_identity.h"
#include "wr64_render_provenance.h"
#include "wr64_menu_layout.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <crtdbg.h>
#endif
extern "C" {
#include "recomp.h"
#include "funcs.h"
void do_break(uint32_t) { std::abort(); }
void switch_error(const char*, uint32_t, uint32_t) { std::abort(); }
void ending_test_baseline_draw(uint8_t*,recomp_context*);
void ending_test_baseline_update(uint8_t*,recomp_context*);
uint32_t wr64_experimental_viewport_borders() { return 1; }
int32_t wr64_sun_horizontal_cull_limit() { return 424; }
void func_800481E0(uint8_t*,recomp_context*) {}
void func_80048A88(uint8_t*,recomp_context*) {}
void func_800484C8(uint8_t*,recomp_context*) {}
void SysUtils_MtxToMtxF(uint8_t*,recomp_context*) {}
void SysUtils_MatrixAffineMultiply(uint8_t*,recomp_context*) {}
void SysUtils_MtxFToMtx(uint8_t*,recomp_context*) {}
void func_800C489C(uint8_t*,recomp_context*) {}
void osVirtualToPhysical_recomp(uint8_t*,recomp_context* c) {
    // clearZBuffer passes its native KSEG0 Z buffer, without a TLB mapping.
    if(uint32_t(c->r4)!=0x80700000u)std::abort();
    c->r2=uint32_t(c->r4)&0x1fffffffu;
}
void func_801E4FE8(uint8_t*,recomp_context* c) { c->r2=c->r4; }
void func_800CA210(uint8_t* rdram,recomp_context* c) {
    // Native ending uses sprintf only for decimal rank/point strings. Preserve
    // the ABI and string bytes; drawing those bytes uses the complete native font.
    std::string format;
    for(uint32_t i=0;i<20;++i) { char x=char(MEM_BU(i,c->r5)); if(!x)break;format+=x; }
    if(format!="%d") {std::cerr<<"Unsupported native format "<<format<<"\n";std::abort();}
    const auto text=std::to_string(int32_t(c->r6));
    for(size_t i=0;i<=text.size();++i) MEM_B(i,c->r4)=i==text.size()?0:text[i];
    c->r2=text.size();
}
}
using namespace RT64;
static uint64_t checks=0,frames=0,rectangles=0,fills=0,partialWarmupClaims=0;
static uint32_t maxRowBytes=0,maxFrameCommands=0,maxFrameRows=0;
static void require(bool b,const char* why) {++checks;if(!b){std::cerr<<"FAIL: "<<why<<" after "<<checks<<" checks\n";std::exit(1);}}
static uint32_t word(const std::vector<uint8_t>&r,uint32_t a){a&=0x1fffffff;require(a+4<=r.size(),"read bounded");uint32_t v;std::memcpy(&v,r.data()+a,4);return v;}
static int16_t half(const std::vector<uint8_t>&r,uint32_t a){a=(a&0x1fffffff)^2;require(a+2<=r.size(),"halfword read bounded");int16_t v;std::memcpy(&v,r.data()+a,2);return v;}
static void put(std::vector<uint8_t>&r,uint32_t a,uint32_t v){a&=0x1fffffff;require(a+4<=r.size(),"write bounded");std::memcpy(r.data()+a,&v,4);}
static std::vector<uint8_t> read(const char*path){std::ifstream f(path,std::ios::binary);require(bool(f),"private input opens");return {std::istreambuf_iterator<char>(f),{}};}
static recomp_context context(){recomp_context c{};c.r29=S32(0x807ff000);return c;}
struct Row {uint32_t address,begin,end,content,x,y;};
static std::vector<Row> rows;
static Row pending{};
extern "C" void ending_test_row_begin(uint8_t* rdram,recomp_context*c){pending={uint32_t(c->r22),uint32_t(c->r20),0,uint32_t(MEM_W(4,c->r22)),uint32_t(MEM_W(8,c->r22)),uint32_t(MEM_W(12,c->r22))};}
extern "C" void ending_test_row_end(uint8_t*,recomp_context*c){pending.end=uint32_t(c->r20);if(pending.end>pending.begin)rows.push_back(pending);}
// The native full-frame prologue retains its low other-mode high-byte flags.
// The 2D producers then set each documented field with native BA/B9 masks.
struct State {uint32_t combH=0,combL=0,modeH=0xff,modeL=0,texture=0,color=0,depth=0x700000;std::array<int32_t,4>scissor{0,0,1696,960};};
struct TargetEvent {const char*name;uint32_t address,command,value;State state;Wr64HudMotion motion{};};
static std::vector<TargetEvent> targetEvents;
struct Rect {std::array<int32_t,4>r;uint32_t address;int16_t s,t,dx,dy;bool fill;State state;Wr64HudMotion motion;};
static uint32_t physical(const std::vector<uint8_t>&r,uint32_t a){if(a>=0x80000000)return a&0x1fffffff;auto seg=a>>24;return seg?(word(r,0x801ce6b0+seg*4)&0x1fffffff)+(a&0xffffff):a;}
static void parse(const std::vector<uint8_t>&ram,uint32_t start,uint32_t end,State& state,std::vector<Rect>&out,uint64_t seq,int depth=0){
    require(depth<12,"display list recursion bounded");start=physical(ram,start);end=end?physical(ram,end):start+4096;
    for(uint32_t a=start;a<end;a+=8){auto w=word(ram,a),v=word(ram,a+4);auto op=w>>24;
        if(op==0xb8)return;
        if(op==0x06){parse(ram,v,0,state,out,seq,depth+1);continue;}
        if(op==0xfc){state.combH=v;state.combL=w;}
        if(op==0xba||op==0xb9){const auto shift=(w>>8)&255,len=w&255;require(shift<32&&len<33,"othermode valid");uint32_t mask=len==32?~0u:((1u<<len)-1u)<<shift;auto&field=op==0xba?state.modeH:state.modeL;field=(field&~mask)|(v&mask);}
        if(op==0xfd)state.texture=v;
        if(op==0xed)state.scissor={int32_t((w>>12)&4095),int32_t(w&4095),int32_t((v>>12)&4095),int32_t(v&4095)};
        if(op==0xfe||op==0xff){(op==0xfe?state.depth:state.color)=v&0x1fffffff;
            targetEvents.push_back({op==0xfe?"depth_image":"color_image",a,w,v,state});}
        if(w==0x03800010u&&v>=0x07001280u&&v<0x070012c0u)
            targetEvents.push_back({"preview_viewport",a,w,v,state});
        if(op==0xe4||op==0xf6||w==0x64000002||w==0x64000003){
            Rect q{};q.address=a;q.state=state;q.fill=op==0xf6||w==0x64000003;q.motion=wr64HudLookup(seq,a,ram.data());
            if(w==0x64000002||w==0x64000003){auto ul=word(ram,a+8),lr=word(ram,a+12);q.r={int16_t(ul>>16),int16_t(ul),int16_t(lr>>16),int16_t(lr)};if(!q.fill){auto st=word(ram,a+16),d=word(ram,a+20);q.s=int16_t(st>>16);q.t=int16_t(st);q.dx=int16_t(d>>16);q.dy=int16_t(d);a+=16;}else a+=8;}
            else {q.r={int32_t((v>>12)&4095),int32_t(v&4095),int32_t((w>>12)&4095),int32_t(w&4095)};if(!q.fill){auto st=word(ram,a+12),d=word(ram,a+20);q.s=int16_t(st>>16);q.t=int16_t(st);q.dx=int16_t(d>>16);q.dy=int16_t(d);a+=16;}}
            // Match the interpreter's actual quarter-pixel FixedRect, including
            // the inclusive native fill/copy edge and upper-left floor.
            const auto cycle=(state.modeH>>20)&3u;
            if(cycle==2||cycle==3){q.r[0]&=~3;q.r[1]&=~3;q.r[2]|=3;q.r[3]|=3;if(!q.fill&&cycle==2)q.dx>>=2;}
            if(q.fill&&state.color==state.depth){
                targetEvents.push_back({"depth_clear",q.address,w,v,state,q.motion});
                require(cycle==3,"native depth clear uses fill cycle");
            }else if(q.r[2]>q.r[0]&&q.r[3]>q.r[1])out.push_back(q);
        }
    }
}
static std::vector<Rect> draw(std::vector<uint8_t>&ram,bool compareBaseline=false){
    std::vector<uint8_t> baselineRam;if(compareBaseline)baselineRam=ram;
    rows.clear();auto c=context();c.r4=S32(0x80500000);func_i15_802C602C(ram.data(),&c);require(uint32_t(c.r2)>=0x80500000&&uint32_t(c.r2)<0x80540000,"native command bound");
    if(compareBaseline){auto b=context();b.r4=S32(0x80500000);ending_test_baseline_draw(baselineRam.data(),&b);require(ram==baselineRam,"ownership hooks preserve every native RAM byte");require(std::memcmp(&b,&c,sizeof(c))==0,"ownership hooks preserve complete native register context");}
    maxFrameRows=std::max(maxFrameRows,uint32_t(rows.size()));for(const auto&r:rows)maxRowBytes=std::max(maxRowBytes,r.end-r.begin);
    wr64_note_gfx_task(1,2,0x80500000,3,4);uint32_t t,ra;auto seq=wr64_claim_gfx_task(0x80500000,3,4,&t,&ra);require(seq!=0,"claimed task");
    maxFrameCommands=std::max(maxFrameCommands,uint32_t(wr64HudClaimed.commands.size()));
    State state;state.color=word(ram,0x801542c0+word(ram,0x80151948)*4)&0x1fffffff;
    targetEvents.clear();targetEvents.push_back({"inherited_color",0,0,state.color,state});
    std::vector<Rect> out;parse(ram,0x80500000,uint32_t(c.r2),state,out,seq);++frames;return out;
}
static void emitTargets(std::ofstream&csv,int variant,int tick){
    bool redirected=false,cleared=false,restored=false;int previews=0;const auto inherited=targetEvents.front().state.color;
    for(const auto&e:targetEvents){
        const std::string name=e.name;
        if(name=="color_image"&&e.state.color==e.state.depth)redirected=true;
        if(name=="depth_clear"){require(redirected,"depth clear follows color redirection");cleared=true;}
        if(name=="color_image"&&cleared&&e.state.color==inherited)restored=true;
        if(name=="preview_viewport"){
            require(restored&&e.state.color==inherited&&e.state.color!=e.state.depth,"all previews follow restored original color destination");
            require(e.state.scissor==std::array<int32_t,4>{0,0,1696,960},"all preview calls inherit full screen scissor");++previews;
        }
        csv<<variant<<','<<tick<<','<<e.name<<','<<e.address<<','<<e.command<<','<<e.value<<','<<e.state.color<<','<<e.state.depth;
        for(auto v:e.state.scissor)csv<<','<<v;
        csv<<','<<e.motion.kind<<','<<e.motion.content<<','<<e.motion.generation<<','<<e.motion.part<<'\n';
    }
    if(cleared)require(previews==4,"depth clear separates panel from all four previews");
}
static void emit(std::ofstream& csv,int variant,int tick,const std::vector<Rect>&rs){
    size_t warm=0;for(size_t i=0;i<rs.size();++i){const auto&q=rs[i];++rectangles;if(q.fill)++fills;
        bool oldClaim=!q.fill&&wr64CelestialDpStripState(q.state.combH,q.state.combL,q.state.modeH,q.state.modeL,q.r[1]);warm+=oldClaim;
        const auto&m=q.motion;
        require(m.kind==3&&m.generation,"every ending native rectangle carries authenticated ending ownership");
        const float offset=(q.r[1]&3)?(q.dy>>5)/32.f:0;
        const float u1=q.s/32.f,v1=q.t/32.f+offset;
        // RDP::drawRect uses FixedRect::width/height(true, true): both ends
        // round upward, including a fractional upper edge on ranking glyphs.
        const int32_t width=(((q.r[2]+3)>>2)-((q.r[0]+3)>>2))*4;
        const int32_t height=(((q.r[3]+3)>>2)-((q.r[1]+3)>>2))*4;
        const float u2=u1+float((int32_t(q.dx)*width)>>7)/32.f,v2=v1+float((int32_t(q.dy)*height)>>7)/32.f;
        csv<<variant<<','<<tick<<','<<i<<','<<q.address<<','<<q.fill<<','<<q.state.texture<<','<<q.state.combH<<','<<q.state.combL<<','<<q.state.modeH<<','<<q.state.modeL;
        for(auto v:q.r)csv<<','<<v;for(auto v:q.state.scissor)csv<<','<<v;
        csv<<','<<q.dx<<','<<q.dy<<','<<u1<<','<<v1<<','<<u2<<','<<v2<<','<<m.kind<<','<<m.slot<<','<<m.content<<','<<m.part<<','<<m.generation<<','<<m.context<<','<<m.age<<','<<m.x<<','<<m.y<<','<<oldClaim<<'\n';
    }if(warm>0&&warm<rs.size())++partialWarmupClaims;
}
int main(int argc,char**argv){
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);_set_abort_behavior(0,_WRITE_ABORT_MSG|_CALL_REPORTFAULT);
#endif
    require(argc==4,"archive ROM output arguments");const auto archive=read(argv[1]),rom=read(argv[2]);require(archive.size()==0x800000&&rom.size()>=0x1d1400,"private input sizes");
    std::ofstream csv(argv[3]);require(bool(csv),"open packet CSV");csv<<std::setprecision(9)<<"variant,frame,call,address,fill,texture,combiner_h,combiner_l,othermode_h,othermode_l,ulx,uly,lrx,lry,scissor_ulx,scissor_uly,scissor_lrx,scissor_lry,dsdx,dtdy,u1,v1,u2,v2,kind,slot,content,part,generation,context,age,x,y,old_warmup_claim\n";
    std::ofstream viewports(std::filesystem::path(argv[3]).parent_path()/"ending-viewports.csv");require(bool(viewports),"open viewport CSV");
    viewports<<"variant,frame,panel_x,panel_y,rank,scale_x,scale_y,scale_z,translate_x,translate_y,translate_z\n";
    std::ofstream targets(std::filesystem::path(argv[3]).parent_path()/"ending-framebuffers.csv");require(bool(targets),"open framebuffer topology CSV");
    targets<<"variant,frame,event,command_address,opcode,value,color_image,depth_image,scissor_ulx,scissor_uly,scissor_lrx,scissor_lry,motion_kind,motion_content,motion_generation,motion_part\n";
    for(int variant=0;variant<2;++variant){auto ram=archive;wr64UltrawidePublishAspect(variant?32.f/9.f:16.f/9.f);
        for(size_t i=0;i<0x1800;++i)ram[(0x2c5800+i)^3]=rom[0x1cfb60+i];
        put(ram,0x800dab24,102);put(ram,0x800dab28,1);put(ram,0x800d8170,7);put(ram,0x801ce638,21);put(ram,0x801ce63c,0);put(ram,0x801cb338,2);put(ram,0x800d48dc,0);put(ram,0x801c2c70,0);put(ram,0x801ce5f8,0x80400000);
        for(int i=0;i<4;++i){put(ram,0x800da9dc+i*4,i);put(ram,0x800da9b0+i*4,i);put(ram,0x801cb340+i*4,100-i*20);}
        auto c=context();func_i15_802C5CE8(ram.data(),&c);
        // Replay each native row identity through the full screen, including
        // births, both crop edges, the former warm-up band, and the final table.
        for(int content=0;content<=10;++content){if(content==8||content==9)continue;
            for(int i=0;i<10;++i)put(ram,0x802c6e80+i*16,0);
            c=context();c.r4=content;func_i15_802C5EE4(ram.data(),&c);
            require(word(ram,0x802c6e8c)==235,"native row birth y235");
            for(int tick=0;tick<145;++tick){int y=235-tick*2;if(content==10)y=std::max(25,y);put(ram,0x802c6e8c,uint32_t(y));put(ram,0x802c6e80,1);
                auto rs=draw(ram,tick==0||tick==17||tick==106||tick==144);emit(csv,variant*11+content,tick,rs);emitTargets(targets,variant*11+content,tick);
            }
        }
        // Reproduce the reported whole-panel pop using the real scheduler,
        // then follow every round panel until its final visible pixel exits.
        for(int content=0;content<8;++content){
            c=context();func_i15_802C5CE8(ram.data(),&c);
            c=context();c.r4=content;func_i15_802C5EE4(ram.data(),&c);
            put(ram,0x802c6e8c,3);auto oldRam=ram;
            int oldLastVisible=0,newLastVisible=0,oldRetireY=0,newRetireY=0;
            for(int tick=0;tick<20;++tick){
                const bool oldWasLive=word(oldRam,0x802c6e80)!=0,newWasLive=word(ram,0x802c6e80)!=0;
                c=context();ending_test_baseline_update(oldRam.data(),&c);
                c=context();func_i15_802C5800(ram.data(),&c);
                const int y=int32_t(word(ram,0x802c6e8c));
                const auto oldRects=draw(oldRam),newRects=draw(ram);
                const auto visibleBottom=[](const std::vector<Rect>&rects){int edge=0;for(const auto&q:rects)
                    if(q.motion.slot==0&&!q.fill&&q.state.combH==0xff2fffffu&&q.state.combL==0xfc119623u&&q.dx==728)
                        edge=std::max(edge,q.r[3]/4);return edge;};
                const int oldBottom=visibleBottom(oldRects),newBottom=visibleBottom(newRects);
                if(oldBottom>0)oldLastVisible=oldBottom;if(newBottom>0)newLastVisible=newBottom;
                if(oldWasLive&&!word(oldRam,0x802c6e80))oldRetireY=int32_t(word(oldRam,0x802c6e8c));
                if(newWasLive&&!word(ram,0x802c6e80))newRetireY=y;
                if(y>=-31)require(word(ram,0x802c6e80)==1&&newBottom==y+32,"round bottom clips continuously through final pixel");
                if(y<=-33)require(!word(ram,0x802c6e80)&&newBottom==0,"fully exited round is retired");
                if(oldWasLive&&word(oldRam,0x802c6e80))require(int32_t(word(oldRam,0x802c6e8c))==y,"native scrolling speed unchanged");
            }
            require(oldRetireY==-13&&oldLastVisible==21,"baseline reproduces 21px whole-panel disappearance");
            require(newRetireY==-33&&newLastVisible==1,"fixed row survives until bottom exits top");
        }
        // Unsupported rows/contexts retain the native comparison. Ranking content
        // 10 never uses this correction; its own stop/fade choreography stays native.
        put(ram,0x802c6e80,1);put(ram,0x802c6e84,0);put(ram,0x802c6e8c,uint32_t(-13));
        require(wr64_ending_panel_retire(ram.data(),0x802c6e80,1)==0,"supported partly visible row survives");
        for(auto [address,value]:std::array<std::pair<uint32_t,uint32_t>,8>{{
            {0x800dab24,3},{0x800dab28,2},{0x800d8170,0},{0x801ce638,1},
            {0x802c6e80,0},{0x802c6e80,2},{0x802c6e84,9},{0x802c6e84,10}}}){
            auto saved=word(ram,address);put(ram,address,value);
            require(wr64_ending_panel_retire(ram.data(),0x802c6e80,1)==1,"unrelated retirement remains native");put(ram,address,saved);
        }
        for(uint32_t row:{0x802c6e70u,0x802c6e84u,0x802c6f20u})
            require(wr64_ending_panel_retire(ram.data(),row,1)==1,"unrecognized row pointer unchanged");
        // Also run the complete native scheduler, including overlapping rows,
        // slot reuse, retirement, final table arrival, and its stopped state.
        c=context();func_i15_802C5CE8(ram.data(),&c);
        auto oldSchedule=ram;
        std::array<int,11> oldBirths{},newBirths{};oldBirths.fill(-1);newBirths.fill(-1);
        bool sawOverlap=false,sawTotal=false,sawStoppedTotal=false;
        for(int tick=0;tick<1800;++tick){c=context();ending_test_baseline_update(oldSchedule.data(),&c);
            c=context();func_i15_802C5800(ram.data(),&c);auto rs=draw(ram,tick%100==0);
            // Spawn requests/timers, final-table fade, and next-scene readiness
            // must remain at the same native ticks despite later row retirement.
            for(uint32_t a:{0x802c6d68u,0x802c6d6cu,0x802c6dd4u,0x802c6dd8u,0x802c6ddcu,0x802c6df0u,0x802c6df4u})
                require(word(ram,a)==word(oldSchedule,a),"spawn/fade/scene timing unchanged");
            sawOverlap|=rows.size()>1;
            for(const auto&q:rs){require(q.motion.kind==3&&q.motion.generation,"complete native sequence authenticates each rectangle");sawTotal|=q.motion.content==10;}
            int occupied=0;
            for(int slot=0;slot<10;++slot){auto row=0x802c6e80+slot*16;
                for(int source=0;source<2;++source){const auto&r=source?ram:oldSchedule;auto&births=source?newBirths:oldBirths;
                    if(word(r,row)&&word(r,row+4)<=10&&births[word(r,row+4)]<0)births[word(r,row+4)]=tick;}
                if(!word(ram,row))continue;++occupied;
                if(word(ram,row+4)==10){
                    require(word(oldSchedule,row)==word(ram,row)&&word(oldSchedule,row+4)==10&&word(oldSchedule,row+12)==word(ram,row+12),"ranking state and movement unchanged");
                    const auto x=int32_t(word(ram,row+8)),y=int32_t(word(ram,row+12));sawStoppedTotal|=y==25;
                    const auto dynamic=word(ram,0x801ce5f8);
                    for(int rank=0;rank<4;++rank){const uint32_t vp=dynamic+0x1280+rank*16;
                        require(half(ram,vp+8)==(x+58)*4&&half(ram,vp+10)==(y+67+rank*32)*4,"native ranking viewport follows current panel position");
                        viewports<<variant<<','<<tick<<','<<x<<','<<y<<','<<rank;
                        for(int offset:{0,2,4,8,10,12}){const auto value=half(ram,vp+offset);require(value==half(oldSchedule,vp+offset),"ranking native viewport unchanged");viewports<<','<<value;}
                        viewports<<'\n';
                    }
                }
            }
            require(occupied<10,"extended retirement leaves free spawn slots");
        }
        require(oldBirths==newBirths,"every round and ranking table spawns at native tick");
        require(sawOverlap&&sawTotal&&sawStoppedTotal,"native scheduler reaches overlap and stationary total table");
        require(!rows.empty()&&!wr64HudClaimed.commands.empty(),"final native row and commands remain available");
        const auto finalRow=rows.front();
        const std::array<std::pair<uint32_t,uint32_t>,4> wrongContexts{{{0x800dab24,100},{0x800dab28,2},{0x800d8170,0},{0x801ce638,1}}};
        for(auto [address,value]:wrongContexts){const auto saved=word(ram,address);put(ram,address,value);
            wr64_ending_hud_draw(ram.data(),finalRow.address,finalRow.begin,finalRow.end);
            require(wr64HudPending.empty(),"other native contexts cannot claim ending rows");put(ram,address,saved);
        }
        wr64_ending_hud_draw(ram.data(),finalRow.address+4,finalRow.begin,finalRow.end);
        require(wr64HudPending.empty(),"unaligned row cannot claim ending commands");
        const auto command=wr64HudClaimed.commands.front();const auto before=command.motion;
        const auto original=word(ram,command.address);put(ram,command.address,original^1);
        require(wr64HudLookup(wr64HudClaimed.sequence,command.address,ram.data()).kind==0,"overwritten native command loses authentication");
        put(ram,command.address,original);
        c=context();func_i15_802C5CE8(ram.data(),&c);c=context();c.r4=10;func_i15_802C5EE4(ram.data(),&c);put(ram,0x802c6e8c,25);
        const auto after=draw(ram).front().motion;
        require(after.generation!=before.generation&&!wr64HudContinuous(before,after),"new ending session breaks previous panel interpolation");
    }
    require(rectangles>10000&&fills>0,"all rectangle and final-table fill paths exercised");require(partialWarmupClaims>0,"old warm-up classifier partially claims native ending bars");
    std::cout<<"Ending native frames="<<frames<<" rectangles="<<rectangles<<" fills="<<fills<<" partial warm-up claims="<<partialWarmupClaims<<" max row bytes="<<maxRowBytes<<" max frame commands="<<maxFrameCommands<<" max frame rows="<<maxFrameRows<<" checks="<<checks<<'\n';
}
