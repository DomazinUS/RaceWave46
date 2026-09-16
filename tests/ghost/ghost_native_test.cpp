#include "wr64_ghost_native.h"
#include "wr64_ghost.hpp"
#include "librecomp/addresses.hpp"
#include "librecomp/game.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <span>
#include <string_view>
#include <vector>

namespace {
std::vector<uint8_t> rom;
std::filesystem::path runtime_save_base;
bool allocated=false,freed=false,expect_ghost=false;
int checks=0,draw_calls=0;
std::uint32_t model_base=0;
std::uint32_t previous_identity=0;
void require(bool ok,const char* text) {++checks;if(!ok)throw std::runtime_error(text);}
gpr guest(std::uint32_t address) {return static_cast<gpr>(static_cast<std::int32_t>(address));}
std::uint32_t get(uint8_t* rdram,std::uint32_t address) {return MEM_W(0,guest(address));}
void put(uint8_t* rdram,std::uint32_t address,std::uint32_t value) {MEM_W(0,guest(address))=value;}
void flt(uint8_t* rdram,std::uint32_t address,float value) {put(rdram,address,std::bit_cast<std::uint32_t>(value));}
void half(uint8_t* rdram,std::uint32_t address,std::uint16_t value) {MEM_H(0,guest(address))=value;}
}
namespace ultramodern {std::filesystem::path get_save_file_path(){return runtime_save_base;}}
namespace recomp {
std::span<const uint8_t> get_rom(){return rom;}
void* alloc(uint8_t* rdram,std::size_t bytes) {
    require(!allocated,"one shared model allocation");
    require(bytes<0x20000,"bounded model/staging/private-stack allocation");
    allocated=true;return rdram+0x01000010;
}
void free(uint8_t* rdram,void* memory) {
    require(memory==rdram+0x01000010,"free exact owned allocation");allocated=false;freed=true;
}
}
#include "runtime_rom_read_test.inc"
extern "C" {
void Mio0_Decompress(uint8_t*,recomp_context*);
void wr64_ghost_test_check_context(recomp_context* ctx) {
    require(ctx->f_odd==(ctx->mips3_float_mode ? &ctx->f1.u32l : &ctx->f0.u32h),
        "private context owns its FR0/FR1 odd-register pointer");
    *ctx->f_odd^=0x1A2B3C4D;
}
void switch_error(const char*,uint32_t,uint32_t){throw std::runtime_error("unexpected native jump table");}
void func_800961B8(uint8_t*,recomp_context*){throw std::runtime_error("unexpected bird relocation");}
void func_800962F0(uint8_t*,recomp_context*){throw std::runtime_error("unexpected orca relocation");}
void func_800963CC(uint8_t*,recomp_context*){throw std::runtime_error("unexpected fish relocation");}
void func_800964CC(uint8_t*,recomp_context*){throw std::runtime_error("unexpected penguin relocation");}
void func_8009FCB0(uint8_t* rdram,recomp_context* ctx) {
    ++draw_calls;
    if(expect_ghost) {
        require(MEM_H(0,guest(0x801CE768))==0,"ghost binds valid native model slot");
        require(get(rdram,0x801CE780)==6,"USA dolphin has six display lists");
        model_base=get(rdram,0x801CE6D0)+0x80000000;
        require(model_base>=0x81000000,"CPU model in owned extended heap");
        const auto animations=get(rdram,0x801CE784);
        require(animations>=model_base && animations<model_base+0xC21C,"native animation pointer relocated");
        for(int i=0;i<8;++i) {
            const auto sequence=get(rdram,animations+i*4);
            require(sequence>=model_base && sequence<model_base+0xC21C,"all eight native animation dictionaries relocated");
        }
        for(int i=0;i<6;++i) {
            const auto list=get(rdram,0x801CE788+i*4);
            require((list>>24)==8,"native model display list remains in segment8");
            const auto offset=list&0xFFFFFF;
            require(offset<0xC21C,"native display list bounded by model allocation");
        }
        const auto gp=std::uint32_t(ctx->r4);
        require(get(rdram,gp-24)==0x00525464 && get(rdram,gp-20)==0x10000064,"extended opcode enable before draw");
        require(get(rdram,gp-16)==0x6400002C && get(rdram,gp-12)==1,"extended memory enabled before draw");
        require(get(rdram,gp-8)==0xBC002006 && get(rdram,gp-4)==model_base,"RSP segment8 high-bit address");
        for(unsigned part=0;part<5;++part) {
            put(rdram,gp+part*16,0x01020040);put(rdram,gp+part*16+4,0x06000610+part*64);
            put(rdram,gp+part*16+8,0x06000000);put(rdram,gp+part*16+12,get(rdram,0x801CE788));
        }
        ctx->r2=std::int32_t(gp+80);
    } else ctx->r2=ctx->r4;
}
}
int main(int argc,char** argv) {
    try {
        require(!wr64_ghost_native_storage_ready(),"Pak readiness is false before native initialization");
        const bool smoke_mode=argc==3 && std::string_view(argv[2])=="--smoke";
        const bool autosave_mode=argc==4 && std::string_view(argv[2])=="--autosave";
        require(argc==2 || smoke_mode || autosave_mode,"explicit local USA ROM path and valid test mode required");
        std::ifstream input(argv[1],std::ios::binary);
        rom.assign(std::istreambuf_iterator<char>(input),{});
        require(rom.size()>=0x3E8EE0 && rom[0]==0x80 && rom[3]==0x40,"canonical big-endian USA ROM");
        std::vector<uint8_t> memory(32*1024*1024);auto* rdram=memory.data();
        // Main segment uses ROM offset=VRAM-0x80045800. No asset is emitted.
        for(std::size_t i=0x1000;i<0xB0000;++i)MEM_B(i,guest(0x80045800))=rom[i];
        put(rdram,0x800DAB24,40);put(rdram,0x801CE620,0);put(rdram,0x800DAB28,1);
        put(rdram,0x801CE638,1);put(rdram,0x801CE648,3);put(rdram,0x800D48DC,0);
        put(rdram,0x801CB338,0);half(rdram,0x800DAB68,0);
        put(rdram,0x801518B8,0x80210000);
        constexpr auto boat=0x80192690u,check=0x801C2938u;
        flt(rdram,boat+0x74,1);flt(rdram,boat+0x7C,1);flt(rdram,boat+0x84,1);
        put(rdram,0x801CE6D0,0x316800);half(rdram,0x801CE768,1);
        std::array<uint8_t,44> original_header;original_header.fill(0xA5);
        std::memcpy(rdram+0x1CE780,original_header.data(),44);
        std::array<uint8_t,8> original_load;original_load.fill(0x3C);
        std::memcpy(rdram+0x1CE7D8,original_load.data(),8);
        recomp_context ctx{};ctx.r29=std::int32_t(0x80200000);ctx.r4=0x11223344;ctx.r16=0x55667788;
        ctx.f_odd=&ctx.f0.u32h;
        std::array<uint8_t,0x1000> stack;stack.fill(0xBD);std::memcpy(rdram+0x1FF000,stack.data(),stack.size());
        if(autosave_mode) {
            const std::filesystem::path parent(argv[3]);
            require(parent.is_absolute(),"native persistence fixture parent must be absolute");
            std::filesystem::create_directories(parent);
            const auto fixture=parent/("native-"+std::to_string(
                std::chrono::steady_clock::now().time_since_epoch().count()));
            require(std::filesystem::create_directory(fixture),"native persistence uses a fresh isolated profile");
            runtime_save_base=fixture/"native-profile.bin";
            const auto saved=fixture/"native-profile.ghosts"/"course-1-difficulty-0-reverse-0.bin";
            put(rdram,0x800D8170,1);put(rdram,check+0x2F4,0);put(rdram,check+0x2EC,0);
            flt(rdram,boat+0x44,10);
            wr64_ghost_after_init_hover(rdram,&ctx);
            require(wr64_ghost_native_storage_ready() && wr64::ghost::status().autosave_ready,
                "native init binds automatic storage from the runtime save basename");
            require(!wr64::ghost::status().best.available && !std::filesystem::exists(saved),
                "fresh native Time Trial has no prior persistent ghost");
            put(rdram,0x800E62CC,3);wr64_ghost_after_hover_glist(rdram,&ctx);
            put(rdram,check+0x19C,123457);put(rdram,check+0x2F4,1);
            flt(rdram,boat+0x44,20);put(rdram,0x800DAB24,42);
            wr64_ghost_after_hover_glist(rdram,&ctx);
            require(wr64::ghost::status().best.finish_ms==123457 &&
                wr64::ghost::status().best.samples==2 && std::filesystem::file_size(saved)==wr64::ghost::kFileBytes,
                "actual native finish writes the complete ghost before Retry or shutdown");

            // Reset every host/native session reference. Only the runtime save
            // basename and isolated disk file survive; no manual storage APIs
            // initialize, save, or select this ghost in either session.
            wr64::ghost::reset_session();wr64_ghost_native_reset();
            require(!wr64_ghost_native_storage_ready() && !wr64::ghost::status().best.available,
                "session reset discards the native and host RAM selection");
            put(rdram,0x800DAB24,40);put(rdram,check+0x2F4,0);put(rdram,check+0x19C,0);
            flt(rdram,boat+0x44,900);
            wr64_ghost_after_init_hover(rdram,&ctx);
            require(wr64::ghost::status().best.finish_ms==123457 && wr64::ghost::status().best.samples==2,
                "first native race initialization reloads the matching persistent ghost");
            put(rdram,0x800E62CC,3);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(wr64::ghost::render_pose().valid && wr64::ghost::render_pose().position.x==110 &&
                get(rdram,0x800E62CC)==4 && wr64::ghost::status().recorded_samples==1,
                "first restarted native frame queues the saved trajectory alongside a fresh player recording");

            wr64::ghost::reset_session();wr64_ghost_native_reset();
            put(rdram,0x800E62CC,3);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(wr64_ghost_native_storage_ready() && wr64::ghost::status().autosave_ready &&
                wr64::ghost::status().best.finish_ms==123457 && wr64::ghost::render_pose().position.x==110 &&
                get(rdram,0x800E62CC)==4,
                "native frame fallback also initializes and restores persistent playback");
            wr64_ghost_native_reset();wr64::ghost::reset_session();
            std::cout<<checks<<" native automatic-persistence checks passed; isolated profile: "<<fixture<<'\n';
            return 0;
        }
        if(smoke_mode) {
            put(rdram,0x800D8170,1);put(rdram,check+0x2F4,0);put(rdram,check+0x2EC,0);
            wr64_ghost_after_init_hover(rdram,&ctx);
            require(wr64_ghost_native_storage_ready(),"native init publishes save readiness to frontend");
            put(rdram,0x800E62CC,3);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(get(rdram,0x800E62CC)==4,"diagnostic preview shares actual native enqueue path");
            require(!wr64::ghost::status().can_save && wr64::ghost::status().recorded_samples==1,
                "synthetic preview never becomes a completed or extra recorded trajectory");
            auto draw=ctx;draw.r4=std::int32_t(0x80210000);draw.r5=3;expect_ghost=true;
            wr64_ghost_draw_dolphin(rdram,&draw);
            require(draw_calls==1,"diagnostic preview shares production dolphin draw bracket");
            wr64_ghost_native_reset();
            std::cout<<checks<<" native diagnostic-preview checks passed; no Pak operations.\n";
            return 0;
        }
        for(int course=0;course<9;++course) {
            ctx.mips3_float_mode=course%2;
            ctx.f_odd=ctx.mips3_float_mode ? &ctx.f1.u32l : &ctx.f0.u32h;
            const auto preserved=ctx;
            put(rdram,0x800DAB24,40);put(rdram,0x800D8170,course);put(rdram,check+0x2F4,0);put(rdram,check+0x2EC,0);
            wr64_ghost_after_init_hover(rdram,&ctx);
            require(wr64_ghost_native_storage_ready(),"native init publishes save readiness to frontend");
            put(rdram,0x800E62CC,3);wr64_ghost_after_hover_glist(rdram,&ctx);
            flt(rdram,boat+0x44,10);put(rdram,check+0x19C,123457);put(rdram,check+0x2F4,1);
            put(rdram,0x800DAB24,42); // Finish state retains the shared race renderer.
            wr64_ghost_after_hover_glist(rdram,&ctx);
            require(wr64::ghost::status().best.finish_ms==123457,"native exact finish-time mapping");
            put(rdram,0x800DAB24,43);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(wr64::ghost::status().best.samples==3,"finish/fade race modes preserve post-goal tail");
            put(rdram,0x800DAB24,40);put(rdram,check+0x2F4,0);wr64_ghost_after_init_hover(rdram,&ctx);
            put(rdram,0x800E62CC,3);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(wr64::ghost::status().dolphin_resident,"model resident on every TT course");
            require(get(rdram,0x800E62CC)==4,"ghost appended without replacing normal actors");
            const auto actor=0x801CF060+3*0xBC;
            require(get(rdram,actor)==6 && get(rdram,actor+0xB8)==1,"native render descriptor consumed synchronously");
            require(std::memcmp(&ctx,&preserved,sizeof(ctx))==0,"capture and helper calls preserve all native registers");
            require(std::memcmp(rdram+0x1FF000,stack.data(),stack.size())==0,"capture does not touch caller guest stack");
            auto draw=ctx;draw.r4=std::int32_t(0x80210000);draw.r5=3;expect_ghost=true;
            wr64_ghost_draw_dolphin(rdram,&draw);
            require(draw.r2==guest(0x802100D0),"display-list return accounts for five scoped part identities");
            const auto identity=get(rdram,0x8021001C);
            require((identity&0xFFF00000)==0x57F00000 && identity!=previous_identity,"new run gets new reserved ghost identity");
            previous_identity=identity;
            for(unsigned part=0;part<5;++part) {
                const auto at=0x80210018+part*32;
                require(get(rdram,at)==0x6400000C && get(rdram,at+4)==identity+part,"body parts retain distinct stable identities");
                require(get(rdram,at+8)==(0x0200AAA8u|(part==0 ? 1u : 0u)) && get(rdram,at+12)==0,"only first part pushes the interpolation scope");
                require(get(rdram,at+16)==0x01020040 && get(rdram,at+20)==0x06000610+part*64 &&
                    get(rdram,at+24)==0x06000000,"native matrix and geometry commands retained in order");
            }
            require(get(rdram,0x802100B8)==0x6400000D && get(rdram,0x802100BC)==1,"prior matrix-group scope restored");
            require(get(rdram,0x802100C0)==0xBC002006 && get(rdram,0x802100C4)==0x316800,"RSP segment restored after ghost");
            require(get(rdram,0x802100C8)==0x6400002C && get(rdram,0x802100CC)==0,"extended addressing scope closed");
            if(course==0) {
                // Compare the original textures against a fresh in-memory
                // decompression of the same USA model. No asset is emitted.
                const auto start=get(rdram,0x800DB4A8),end=get(rdram,0x800DB4AC);
                recomp::do_rom_read(rdram,guest(0x80500000),recomp::rom_base+start,end-start);
                recomp_context decode{};decode.r29=guest(0x80700000);decode.f_odd=&decode.f0.u32h;
                decode.r4=guest(0x80500000);decode.r5=guest(0x80600000);Mio0_Decompress(rdram,&decode);
                require(std::memcmp(rdram+(model_base&0x1FFFFFFF)+0xA90,rdram+0x600A90,0x1D80)==0,
                    "all 3776 dolphin texels retain the original USA color and alpha bytes");
                require(std::memcmp(rdram+(model_base&0x1FFFFFFF),rdram+0x600000,0xA90)==0,"private model preserves original vertex data");
            }
            require(get(rdram,0x801CE6D0)==0x316800 && MEM_H(0,guest(0x801CE768))==1,"CPU model bindings restored");
            require(std::memcmp(rdram+0x1CE780,original_header.data(),44)==0 &&
                    std::memcmp(rdram+0x1CE7D8,original_load.data(),8)==0,"normal animal state byte-identical");
            put(rdram,0x800E62CC,8);wr64_ghost_after_hover_glist(rdram,&ctx);
            draw.r4=guest(0x80210000);draw.r5=8;wr64_ghost_draw_dolphin(rdram,&draw);
            require(get(rdram,0x8021001C)==identity,"ghost part identity survives a different native actor queue index");
            half(rdram,boat+0xB58,0x10);put(rdram,0x800E62CC,8);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(wr64::ghost::status().visible,"N64 R0x10 does not toggle the Shindou-style ghost");
            half(rdram,boat+0xB58,0x20);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(!wr64::ghost::status().visible,"N64 L0x20 native edge hides the ghost");
            wr64_ghost_after_hover_glist(rdram,&ctx);half(rdram,boat+0xB58,0);
            require(wr64::ghost::status().visible,"next native L edge restores visibility");
            wr64::ghost::set_visible(false);wr64_ghost_after_hover_glist(rdram,&ctx);
            wr64::ghost::set_visible(true);put(rdram,0x800E62CC,8);wr64_ghost_after_hover_glist(rdram,&ctx);
            draw.r4=guest(0x80210000);draw.r5=8;wr64_ghost_draw_dolphin(rdram,&draw);
            require(get(rdram,0x8021001C)!=identity,"visibility gaps cut interpolation history");
            put(rdram,0x80216000,0x13579BDF);draw.r4=guest(0x80215FF8);draw.r5=8;
            wr64_ghost_draw_dolphin(rdram,&draw);
            require(draw.r2==guest(0x80215FF8) && get(rdram,0x80216000)==0x13579BDF,
                "insufficient native display-list capacity discards ghost without crossing pool boundary");
            put(rdram,0x800E62CC,30);wr64_ghost_after_hover_glist(rdram,&ctx);
            require(get(rdram,0x800E62CC)==30,"full native actor queue is preserved");
            expect_ghost=false;draw.r4=std::int32_t(0x80220000);draw.r5=0;
            wr64_ghost_draw_dolphin(rdram,&draw);require(draw.r2==draw.r4,"normal dolphin draw delegated unchanged");
        }
        put(rdram,0x800DAB24,7);wr64_ghost_after_hover_glist(rdram,&ctx);
        require(!wr64::ghost::status().recording && !wr64::ghost::render_pose().valid,"attract mode excluded");
        wr64_ghost_native_reset();require(freed && !wr64::ghost::status().dolphin_resident,"owned model freed on stopped-runtime reset");
        require(!wr64_ghost_native_storage_ready(),"native reset clears Pak readiness");
        wr64_ghost_after_hover_glist(rdram,&ctx);
        require(wr64_ghost_native_storage_ready(),"native frame also publishes readiness");
        wr64_ghost_native_forget();
        require(!wr64_ghost_native_storage_ready(),"post-runtime forget clears readiness without using RDRAM");
        std::cout<<checks<<" native adapter checks passed using existing USA decompressor, relocator, and render queue; renderer boundary stubbed.\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
