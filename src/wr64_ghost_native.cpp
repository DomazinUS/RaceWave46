#include "wr64_diagnostic_policy.h"
#include "wr64_ghost_native.h"
#include "wr64_ghost.hpp"
#include "librecomp/addresses.hpp"
#include "librecomp/game.hpp"
#include "ultramodern/ultramodern.hpp"

#include <array>
#include <atomic>
#include <bit>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Existing USA Rev1 functions. No Shindou native function or asset is included.
extern "C" {
void Mio0_Decompress(uint8_t*,recomp_context*);
void func_80096048(uint8_t*,recomp_context*); // native animal asset relocation
void func_800AC098(uint8_t*,recomp_context*); // synchronous render-actor enqueue
void func_8009FCB0(uint8_t*,recomp_context*); // native dolphin display-list builder
}
namespace {
using namespace wr64::ghost;
constexpr std::uint32_t kBoat=0x80192690,kBoatStride=0x1718;
constexpr std::uint32_t kCheck=0x801C2938,kCheckStride=0x378;
constexpr std::uint32_t kAnimalGL=0x801CE780,kAnimalLoad=0x801CE7D8;
constexpr std::uint32_t kDolphinIndex=0x801CE768,kCpuSegment8=0x801CE6D0;
constexpr std::uint32_t kAnimalCount=0x800E62CC;
constexpr std::uint32_t kGfxPool=0x801518B8,kGfxPoolBytes=0x6000;
constexpr std::size_t kDolphinBytes=0xC21C,kScratchBytes=0x1000;
struct NativeState {
    uint8_t* rdram=nullptr;
    void* allocation=nullptr;
    std::uint32_t base=0,staging=0,scratch=0;
    std::array<uint8_t,44> header{};
    bool resident=false;
    int queued_actor=-1;
    bool drawing=false,discard_draw=false;
    std::uint32_t saved_segment=0,draw_start=0,original_gp=0,identity_generation=0;
    Vec3 last_position{};
    bool identity_continuous=false;
    std::array<uint8_t,44> saved_header{};
    std::array<uint8_t,2> saved_index{};
    bool trace_eligible=false,trace_finished=false,smoke_announced=false;
    Course trace_course{};
    std::uint32_t trace_samples=0,draws=0,smoke_tick=0,stamped_parts=0;
} native;
std::atomic_bool storage_ready=false;

void initialize_ghost_storage() {
    if (!storage_ready.load(std::memory_order_relaxed)) {
        // Native callbacks execute after init_saving. Bind automatic storage
        // before begin_run so a saved ghost is ready on the first race frame.
        initialize_storage(ultramodern::get_save_file_path());
        storage_ready.store(true,std::memory_order_release);
    }
}

bool option(const char* name) {
    const char* value=std::getenv(name);
    return value && value[0]=='1' && value[1]=='\0';
}
bool trace_enabled() {static const bool enabled=WR64_DIAGNOSTIC_ENABLED && option("WR64_GHOST_TRACE");return enabled;}
bool smoke_enabled() {static const bool enabled=WR64_DIAGNOSTIC_ENABLED && option("WR64_GHOST_RENDER_SMOKE");return enabled;}

gpr guest(std::uint32_t address) {return static_cast<gpr>(static_cast<std::int32_t>(address));}
std::uint32_t physical(std::uint32_t address) {return address&0x1FFFFFFF;}
std::uint32_t word(uint8_t* rdram,std::uint32_t address) {return MEM_W(0,guest(address));}
float number(uint8_t* rdram,std::uint32_t address) {return std::bit_cast<float>(word(rdram,address));}
void put(uint8_t* rdram,std::uint32_t address,std::uint32_t value) {MEM_W(0,guest(address))=value;}
void put_float(uint8_t* rdram,std::uint32_t address,float value) {put(rdram,address,std::bit_cast<std::uint32_t>(value));}
Vec3 vector(uint8_t* rdram,std::uint32_t address) {return {number(rdram,address),number(rdram,address+4),number(rdram,address+8)};}
void put_vector(uint8_t* rdram,std::uint32_t address,Vec3 v) {
    put_float(rdram,address,v.x);put_float(rdram,address+4,v.y);put_float(rdram,address+8,v.z);
}
Course course(uint8_t* rdram) {
    return {int(word(rdram,0x800D8170)),int(word(rdram,0x801CB338)),MEM_H(0,guest(0x800DAB68))!=0};
}
bool eligible(uint8_t* rdram) {
    // A native attract demonstration can share game_stat=1. Require the live
    // single-player time-attack race family as well as the gameplay mode. The
    // finish/fade modes41–44 retain the race renderer and post-goal tail.
    const auto mode=word(rdram,0x800DAB24);
    return mode>=40 && mode<=44 && word(rdram,0x801CE620)==0 &&
        word(rdram,0x800DAB28)==1 && word(rdram,0x801CE638)==1;
}
template<std::size_t N> struct SavedBytes {
    uint8_t* address;
    std::array<uint8_t,N> saved;
    SavedBytes(uint8_t* rdram,std::uint32_t guest):address(rdram+physical(guest)) {
        std::memcpy(saved.data(),address,N);
    }
    ~SavedBytes() {std::memcpy(address,saved.data(),N);}
};
void private_context(recomp_context& copy,const recomp_context* ctx) {
    copy=*ctx;
    // Rebind the self-pointer only after the copy reaches its final storage.
    // Returning a copied context could leave this pointing into the caller or
    // an elided/non-elided temporary, corrupting odd FP registers in FR0/FR1.
    copy.f_odd=copy.mips3_float_mode ? &copy.f1.u32l : &copy.f0.u32h;
    // Descriptor and callee stack belong to our allocated block. Native helper
    // calls cannot overwrite the caller's guest stack or live registers.
    copy.r29=std::int32_t(native.scratch+kScratchBytes-16);
}
bool ensure_model(uint8_t* rdram,const recomp_context* ctx) {
    if(native.resident && native.rdram==rdram)return true;
    // Runtime ROM bytes are the user's validated USA image. The transfer table
    // is also USA data; the model is never embedded, extracted, or persisted.
    const auto rom=recomp::get_rom();
    const auto start=word(rdram,0x800DB4A8),end=word(rdram,0x800DB4AC);
    if(start>=end || end>rom.size() || end-start>0x20000 || end-start<16 ||
       rom[start]!='M' || rom[start+1]!='I' || rom[start+2]!='O' || rom[start+3]!='0')return false;
    const auto expanded=(std::uint32_t(rom[start+4])<<24)|(std::uint32_t(rom[start+5])<<16)|
        (std::uint32_t(rom[start+6])<<8)|rom[start+7];
    if(expanded!=kDolphinBytes || word(rdram,0x800DCE18)!=expanded)return false;
    if(!native.allocation) {
        const std::size_t model_aligned=(expanded+63)&~std::size_t(63);
        const std::size_t compressed_aligned=(end-start+63)&~std::size_t(63);
        native.allocation=recomp::alloc(rdram,model_aligned+compressed_aligned+kScratchBytes+64);
        if(!native.allocation)return false;
        native.rdram=rdram;
        const auto offset=static_cast<uint8_t*>(native.allocation)-rdram;
        native.base=0x80000000u+std::uint32_t((offset+63)&~std::ptrdiff_t(63));
        native.staging=native.base+std::uint32_t(model_aligned);
        native.scratch=native.staging+std::uint32_t(compressed_aligned);
    }
    // do_rom_read takes a PI bus address, unlike the transfer table's raw ROM
    // offsets. Match the runtime's own DMA callers (librecomp/src/pi.cpp).
    recomp::do_rom_read(rdram,std::int32_t(native.staging),recomp::rom_base+start,end-start);
    recomp_context call;private_context(call,ctx);
    call.r4=std::int32_t(native.staging);call.r5=std::int32_t(native.base);
    Mio0_Decompress(rdram,&call);
    {
        SavedBytes<44> save_header(rdram,kAnimalGL);
        SavedBytes<8> save_load(rdram,kAnimalLoad);
        SavedBytes<4> save_segment(rdram,kCpuSegment8);
        // Native relocation takes a physical CPU segment base; its helper adds
        // KSEG0 itself (USA800940B8–C0). Display-list pointers remain segment8.
        put(rdram,kCpuSegment8,physical(native.base));
        put(rdram,kAnimalLoad,0);put(rdram,kAnimalLoad+4,0x08000000);
        private_context(call,ctx);call.r4=std::int32_t(native.base);call.r5=0;
        func_80096048(rdram,&call);
        std::memcpy(native.header.data(),rdram+physical(kAnimalGL),native.header.size());
        native.resident=word(rdram,kAnimalGL)==6;
        const auto animation=word(rdram,kAnimalGL+4);
        native.resident=native.resident && animation>=native.base && animation<native.base+expanded;
        // Preserve the original USA texture, material and vertex bytes.
    }
    set_dolphin_resident(native.resident);
    if(native.resident)WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,"[ghost] USA dolphin resident in recomp heap at %08X (%u bytes)\n",native.base,expanded));
    return native.resident;
}
void command(uint8_t* rdram,std::uint32_t& gp,std::uint32_t first,std::uint32_t second) {
    put(rdram,gp,first);put(rdram,gp+4,second);gp+=8;
}
void stamp_part_identity(uint8_t* rdram,std::uint32_t& gp) {
    // The native builder emits model matrices in stable body-part
    // order. Actor queue positions and segment-6 matrix addresses can change;
    // an explicit per-part identity must therefore belong to this host ghost.
    constexpr unsigned max_commands=256,max_parts=16;
    const auto start=native.draw_start;
    native.stamped_parts=0;
    if(gp<start || (gp-start)%8 || (gp-start)/8>max_commands)return;
    const auto count=(gp-start)/8;
    std::array<std::array<std::uint32_t,2>,max_commands> commands{};
    unsigned parts=0;
    for(unsigned i=0;i<count;++i) {
        commands[i]={word(rdram,start+i*8),word(rdram,start+i*8+4)};
        if((commands[i][0]>>24)==1)++parts;
    }
    if(!parts || parts>max_parts)return;
    // USA GfxPool.dList is3072 commands at offset0, matching Dynamic.glist.
    // Preserve room for our two final segment/extended-address restore commands.
    const auto pool=word(rdram,kGfxPool);
    const auto extra=parts*16+8+16;
    if(start<pool || gp<pool || gp-pool>kGfxPoolBytes || extra>kGfxPoolBytes-(gp-pool))return;
    // Match the established native dolphin final-matrix interpolation recipe.
    // The two-command gEXMatrixGroup encoding is declared in rt64_extended_gbi.h.
    constexpr std::uint32_t interpolate=(1u<<3)|(1u<<5)|(1u<<7)|(1u<<9)|
        (1u<<11)|(1u<<13)|(1u<<15)|(2u<<24);
    gp=start;unsigned part=0;
    for(unsigned i=0;i<count;++i) {
        if((commands[i][0]>>24)==1) {
            const auto id=0x57F00000u|((native.identity_generation&0xFFFu)<<8)|part;
            command(rdram,gp,0x6400000C,id);
            command(rdram,gp,interpolate|(part==0 ? 1u : 0u),0);
            ++part;
        }
        command(rdram,gp,commands[i][0],commands[i][1]);
    }
    command(rdram,gp,0x6400000D,1); // Pop only our model-group scope.
    native.stamped_parts=parts;
}
}

extern "C" void wr64_ghost_after_init_hover(uint8_t* rdram,recomp_context* ctx) {
    // Runtime marks itself Running before initializing saving; this native
    // callback runs afterward and safely publishes that initialization to UI.
    initialize_ghost_storage();
    (void)ctx;
    native.queued_actor=-1;
    native.identity_continuous=false;
    native.trace_finished=false;native.trace_samples=native.smoke_tick=0;
    native.smoke_announced=false;
    if(eligible(rdram) && word(rdram,0x800DAB24)==40)begin_run(course(rdram));
    else end_run();
    if(trace_enabled()) {
        const auto c=course(rdram);
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,"[ghost:trace] init eligible=%d course=%d difficulty=%d reverse=%d\n",
            eligible(rdram),c.index,c.difficulty,c.reverse));
    }
}
extern "C" void wr64_ghost_after_hover_glist(uint8_t* rdram,recomp_context* ctx) {
    initialize_ghost_storage();
    native.queued_actor=-1;
    Frame f;f.course=course(rdram);f.eligible=eligible(rdram);
    const auto player=word(rdram,0x800D48DC);
    if(player>=4)f.eligible=false;
    if(f.eligible) {
        const auto boat=kBoat+player*kBoatStride,check=kCheck+player*kCheckStride;
        f.paused=word(rdram,0x801CE648)==0;
        f.retired=word(rdram,check+0x2EC)!=0;
        f.finished=word(rdram,check+0x2F4)!=0;
        f.elapsed_ms=word(rdram,check+0x19C);
        f.position=vector(rdram,boat+0x44);f.forward=vector(rdram,boat+0x6C);
        f.up=vector(rdram,boat+0x78);f.left=vector(rdram,boat+0x84);
        // USA Boat.button_trig is +0xB58, also used by native stunt handling.
        f.toggle_visibility=(MEM_HU(0,guest(boat+0xB58))&0x20)!=0;
    }
    const auto before=status();
    observe(f);
    const auto current=status();
    if(trace_enabled()) {
        if(f.eligible!=native.trace_eligible || f.course!=native.trace_course) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,"[ghost:trace] eligibility=%d course=%d difficulty=%d reverse=%d mode=%u kind=%u players=%u\n",
                f.eligible,f.course.index,f.course.difficulty,f.course.reverse,
                word(rdram,0x800DAB24),word(rdram,0x801CE620),word(rdram,0x800DAB28)));
            native.trace_eligible=f.eligible;native.trace_course=f.course;
        }
        if(f.eligible && f.finished && !native.trace_finished)
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,"[ghost:trace] goal samples=%u exact_ms=%u savable=%d\n",before.recorded_samples,f.elapsed_ms,current.can_save));
        if(current.recorded_samples!=native.trace_samples &&
           (current.recorded_samples==1 || current.recorded_samples%200==0))
            std::fprintf(stderr,"[ghost:trace] captured=%u playback=%d paused=%d full=%d invalid=%d\n",
                current.recorded_samples,current.playback_active,f.paused,current.recording_full,current.recording_invalid);
        native.trace_samples=current.recorded_samples;native.trace_finished=f.finished;
    }
    auto pose=render_pose();
    if(!pose.valid && f.eligible && current.visible && smoke_enabled()) {
        // Opt-in diagnostic visualization only: these positions never enter
        // observe(), best-run selection, either Pak slot, or native race data.
        if(!f.paused)++native.smoke_tick;
        const float phase=float(native.smoke_tick)*0.05f;
        const float ahead=100.0f+80.0f*std::sin(phase);
        pose={true,{f.position.x+200*f.left.x+ahead*f.forward.x,
                    f.position.y+ahead*f.forward.y,
                    f.position.z+200*f.left.z+ahead*f.forward.z},
            f.forward,f.up,(native.smoke_tick*2)%16,native.smoke_tick};
        if(!native.smoke_announced) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,"[ghost:smoke] synthetic render preview active; no synthetic recording or save data\n"));
            native.smoke_announced=true;
        }
    }
    if(!pose.valid || !ensure_model(rdram,ctx)) {
        native.identity_continuous=false;return;
    }
    const auto count=word(rdram,kAnimalCount);
    if(count>=30) {native.identity_continuous=false;return;} // Preserve scene actors.
    const float dx=pose.position.x-native.last_position.x,dy=pose.position.y-native.last_position.y,
        dz=pose.position.z-native.last_position.z;
    // The renderer's normal-dolphin continuity guard is150 world units. A retry,
    // visibility gap, or larger teleport gets a fresh identity, preventing a
    // cross-course or catch-up interpolation streak.
    if(!native.identity_continuous || dx*dx+dy*dy+dz*dz>150.0f*150.0f)++native.identity_generation;
    native.last_position=pose.position;native.identity_continuous=true;
    const auto descriptor=native.scratch;
    put(rdram,descriptor,6);put(rdram,descriptor+4,0);
    put(rdram,descriptor+8,pose.animation_frame);
    const float offset=float(std::int32_t(word(rdram,0x800D4948)));
    put_vector(rdram,descriptor+0xC,{pose.position.x+pose.forward.x*offset,
        pose.position.y+pose.forward.y*offset,pose.position.z+pose.forward.z*offset});
    put_vector(rdram,descriptor+0x18,pose.forward);put_vector(rdram,descriptor+0x24,pose.up);
    put_float(rdram,descriptor+0x30,0.1f); // USA native dolphin scale80068490.
    recomp_context call;private_context(call,ctx);call.r4=std::int32_t(descriptor);call.r5=1;
    func_800AC098(rdram,&call);
    if(word(rdram,kAnimalCount)==count+1)native.queued_actor=int(count);
}
extern "C" void wr64_ghost_begin_dolphin_draw(uint8_t* rdram,recomp_context* ctx,int actor_index) {
    if(!native.resident || native.rdram!=rdram || actor_index!=native.queued_actor)return;
    native.drawing=true;
    std::memcpy(native.saved_header.data(),rdram+physical(kAnimalGL),native.saved_header.size());
    std::memcpy(native.saved_index.data(),rdram+(physical(kDolphinIndex)^2),native.saved_index.size());
    native.saved_segment=word(rdram,kCpuSegment8);
    std::memcpy(rdram+physical(kAnimalGL),native.header.data(),native.header.size());
    MEM_H(0,guest(kDolphinIndex))=0;
    put(rdram,kCpuSegment8,physical(native.base));
    auto gp=std::uint32_t(ctx->r4);
    native.original_gp=gp;
    const auto pool=word(rdram,kGfxPool);
    // The verified live USA draw emits six matrices and six lists. If the native
    // pool has less than a conservative2KiB remainder, build into our private
    // scratch and discard this ghost draw. No asynchronous renderer references
    // that scratch; the scene's display-list pointer remains unchanged.
    native.discard_draw=gp<pool || gp-pool>kGfxPoolBytes-0x800;
    if(native.discard_draw)gp=native.scratch+0x100;
    // F3D gEXEnable; gEXSetRDRAMExtended(true); gSPSegment(8, KSEG0).
    // RT64's extended address path recognizes this high bit after segment
    // lookup, preserving the >=16MiB allocation instead of the 24-bit DMA mask.
    command(rdram,gp,0x00525464,0x10000064);
    command(rdram,gp,0x6400002C,1);
    command(rdram,gp,0xBC002006,native.base);
    native.draw_start=gp;
    ctx->r4=std::int32_t(gp);
}
extern "C" void wr64_ghost_end_dolphin_draw(uint8_t* rdram,recomp_context* ctx) {
    if(!native.drawing)return;
    auto gp=std::uint32_t(ctx->r2);
    if(native.discard_draw)gp=native.original_gp;
    else {
        stamp_part_identity(rdram,gp);
        command(rdram,gp,0xBC002006,native.saved_segment);
        command(rdram,gp,0x6400002C,0);
    }
    ctx->r2=std::int32_t(gp);
    put(rdram,kCpuSegment8,native.saved_segment);
    std::memcpy(rdram+physical(kAnimalGL),native.saved_header.data(),native.saved_header.size());
    std::memcpy(rdram+(physical(kDolphinIndex)^2),native.saved_index.data(),native.saved_index.size());
    native.drawing=false;
    if(native.discard_draw) {native.identity_continuous=false;return;}
    ++native.draws;
    if(trace_enabled() && (native.draws==1 || native.draws%120==0))
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,"[ghost:trace] dolphin draw=%u actor=%d model=%08X parts=%u identity=%08X\n",
            native.draws,native.queued_actor,native.base,native.stamped_parts,
            0x57F00000u|((native.identity_generation&0xFFFu)<<8)));
}
extern "C" void wr64_ghost_draw_dolphin(uint8_t* rdram,recomp_context* ctx) {
    wr64_ghost_begin_dolphin_draw(rdram,ctx,int(ctx->r5));
    func_8009FCB0(rdram,ctx);
    wr64_ghost_end_dolphin_draw(rdram,ctx);
}
extern "C" void wr64_ghost_native_reset(void) {
    storage_ready.store(false,std::memory_order_release);
    if(native.allocation && native.rdram)recomp::free(native.rdram,native.allocation);
    native={};set_dolphin_resident(false);
}
extern "C" void wr64_ghost_native_forget(void) {
    storage_ready.store(false,std::memory_order_release);
    native={};set_dolphin_resident(false);
}
extern "C" int wr64_ghost_native_storage_ready(void) {
    return storage_ready.load(std::memory_order_acquire);
}
