#include "wr64_achievements_native.hpp"
#include "wr64_achievements.hpp"
#include "wr64_rom_patch.hpp"
#include "recomp.h"
#include "rc_runtime.h"
#include <array>
#include <csetjmp>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <vector>

static std::size_t checks=0;
static void require(bool yes,const char* why){++checks;if(!yes)throw std::runtime_error(why);}
static std::vector<uint32_t> messages,observed,expected;
static std::size_t message_index=0;
static unsigned gfx_ticks=0;
static std::jmp_buf native_done;
static std::string selected_identity;
namespace wr64::achievements {
void set_game_identity(std::string hash){selected_identity=std::move(hash);}
void native_frame(uint8_t* rdram){uint32_t marker;std::memcpy(&marker,rdram+0x200,4);observed.push_back(marker);}
}
extern "C" void main_thread(uint8_t*,recomp_context*);
extern "C" void osRecvMesg_recomp(uint8_t* rdram,recomp_context* ctx){
    require(uint32_t(ctx->r4)==0x80154130,"Unexpected native receive queue");
    if(message_index==messages.size())std::longjmp(native_done,1);
    const uint32_t marker=uint32_t(message_index+1);
    std::memcpy(rdram+0x200,&marker,4);
    MEM_W(0,ctx->r5)=messages[message_index++];ctx->r2=0;
}
extern "C" void osViSetEvent_recomp(uint8_t*,recomp_context* ctx){
    require(uint32_t(ctx->r4)==0x80154130&&ctx->r5==0x19&&ctx->r6==1,
        "Native VI queue/message or retrace count changed");
}
extern "C" void osSendMesg_recomp(uint8_t*,recomp_context* ctx){if(ctx->r5==0x29)++gfx_ticks;ctx->r2=0;}
#define STUB(name) extern "C" void name(uint8_t*,recomp_context* ctx){ctx->r2=0;}
STUB(func_80047470) STUB(func_800474A0) STUB(func_800474E4) STUB(func_800980C8)
STUB(osCreateMesgQueue_recomp) STUB(osCreateThread_recomp) STUB(osSetEventMesg_recomp)
STUB(osSpTaskYielded_recomp) STUB(osStartThread_recomp) STUB(osWritebackDCacheAll_recomp)
#undef STUB

static void memory_reads(){
    using namespace wr64::achievements::native;
    std::vector<uint8_t> memory(memory_size+16,0xFA);
    for(uint32_t i=0;i<memory_size;++i)memory[i]=uint8_t(i*37+19);
    std::array<uint8_t,70> output{};
    for(uint32_t at:{0u,1u,2u,3u,4u,0x123457u,0x7FFFBFu,0x7FFFFFu})for(uint32_t count:{0u,1u,2u,3u,4u,17u,64u}){
        output.fill(0xBC);const auto copied=read_memory_bytes(memory.data(),memory.size(),at,output.data(),count);
        const auto expected_count=std::min<uint32_t>(count,uint32_t(memory_size)-at);
        require(copied==expected_count,"Physical RAM bound or partial read count wrong");
        for(uint32_t i=0;i<copied;++i)require(output[i]==uint8_t((at+i)*37+19),"RA host-word memory byte mismatch");
        for(uint32_t i=copied;i<output.size();++i)require(output[i]==0xBC,"Memory callback wrote beyond returned bytes");
    }
    for(uint32_t at:{0x800000u,0x80000000u,0xFFFFFFFFu})
        require(!read_memory_bytes(memory.data(),memory.size(),at,output.data(),UINT32_MAX),"Invalid address wrapped into RAM");
    require(!read_memory_bytes(nullptr,memory_size,0,output.data(),1),"Null RAM accepted");
    require(!read_memory_bytes(memory.data(),memory_size,0,nullptr,1),"Null output accepted");
    require(read_memory_bytes(memory.data(),7,2,output.data(),64)==2,"Incomplete host word read beyond backing storage");
    require(read_memory_bytes(memory.data(),memory_size,0x7FFFFF,output.data(),UINT32_MAX)==1,"Request overflow escaped RAM bounds");
}
namespace records {
struct Memory { uint8_t* rdram; bool legacy_unswap; };
static std::vector<uint32_t> triggered;
static uint32_t RC_CCONV peek(uint32_t address, uint32_t count, void* userdata) {
    const auto& input = *static_cast<Memory*>(userdata);
    std::array<uint8_t, 4> bytes{};
    if (count > bytes.size()) return 0;
    if (input.legacy_unswap) {
        if (address >= wr64::achievements::native::memory_size ||
            count > wr64::achievements::native::memory_size - address) return 0;
        for (uint32_t i = 0; i < count; ++i) bytes[i] = input.rdram[(address + i) ^ 3U];
    } else {
        require(wr64::achievements::native::read_memory_bytes(input.rdram,
            wr64::achievements::native::memory_size, address, bytes.data(), count) == count,
            "Official definition operand read failed");
    }
    uint32_t value = 0;
    for (uint32_t i = 0; i < count; ++i) value |= uint32_t(bytes[i]) << (8 * i);
    return value;
}
static void RC_CCONV event(const rc_runtime_event_t* value) {
    if (value->type == RC_RUNTIME_EVENT_ACHIEVEMENT_TRIGGERED) triggered.push_back(value->id);
}
struct Runtime {
    rc_runtime_t value{};
    Runtime() { rc_runtime_init(&value); }
    ~Runtime() { rc_runtime_destroy(&value); }
};
static void official_definitions() {
    // Exact game10617 definitions fetched read-only on 2026-09-14. Only the
    // offline trigger runtime is instantiated: no client, account or server.
    struct Definition { uint32_t id, address, cutoff; const char* text; };
    const Definition definitions[] {
        {118484, 0x1C22D4, 30000, "0x 1c22d4<30000_0x 1c22d4<d0x 1c22d4_0xH1d7dc4=1"},
        {118492, 0x1C202C, 24464, "0x 1c202c<24464_0x 1c202c<d0x 1c202c_0xH1d7dc4=1"}
    };
    for (const auto& definition : definitions) for (uint32_t mode : {0U, 1U, 2U}) {
        std::vector<uint8_t> memory(wr64::achievements::native::memory_size);
        uint8_t* rdram = memory.data();
        const auto guest_record = static_cast<gpr>(int32_t(0x80000000U + definition.address));
        const auto guest_mode = static_cast<gpr>(int32_t(0x801D7DC4U));
        // Actual recompiler MEM_W semantics, including the game's aligned
        // 0x801D7DC4 mode word, rather than bytes tailored to the read helper.
        MEM_W(0, guest_mode) = mode;
        MEM_W(0, guest_record) = definition.cutoff;
        Memory corrected{rdram, false}, legacy{rdram, true};
        require(peek(0x1D7DC4, 1, &corrected) == mode,
            "Official byte gate does not read the native mode word's low byte");
        require(peek(0x1D7DC4, 1, &legacy) == 0, "Legacy unswap negative control changed");
        require(peek(definition.address, 2, &corrected) == definition.cutoff,
            "Official 16-bit record does not match the native stored value");
        Runtime good, old;
        require(rc_runtime_activate_achievement(&good.value, definition.id, definition.text, nullptr, 0) == RC_OK,
            "Official record definition failed to parse");
        require(rc_runtime_activate_achievement(&old.value, definition.id, definition.text, nullptr, 0) == RC_OK,
            "Legacy control definition failed to parse");
        const auto frame = [&](uint32_t record, bool should_trigger) {
            MEM_W(0, guest_record) = record;
            triggered.clear(); rc_runtime_do_frame(&good.value, event, peek, &corrected, nullptr);
            require(triggered.size() == (should_trigger ? 1U : 0U), "Official record transition produced wrong trigger count");
            if (should_trigger) require(triggered.front() == definition.id, "Wrong official record ID triggered");
            triggered.clear(); rc_runtime_do_frame(&old.value, event, peek, &legacy, nullptr);
            require(triggered.empty(), "Legacy unswapping unexpectedly passed the actual mode gate");
        };
        frame(definition.cutoff, false); // initialize delta; no transition
        frame(definition.cutoff, false); // equal record
        frame(definition.cutoff + 1, false); // worse record
        frame(definition.cutoff, false); // decreased, but not below cutoff
        frame(definition.cutoff - 1, mode == 1); // actual qualifying update
        frame(definition.cutoff - 1, false); // no duplicate on later VIs
        std::printf("official definition %u: native mode=%u; corrected trigger=%u; legacy unswap=0\n",
            definition.id, mode, mode == 1 ? 1 : 0);
    }
}
}
static void cadence(){
    for(uint32_t divisor:{1u,2u,3u}){
        std::vector<uint8_t> memory(0x800000);uint8_t* rdram=memory.data();recomp_context ctx{};
        ctx.r29=static_cast<gpr>(int32_t(0x807F0000));
        MEM_W(0,static_cast<gpr>(int32_t(0x800D4618)))=divisor;
        MEM_W(0,static_cast<gpr>(int32_t(0x800D461C)))=divisor;
        messages.clear();observed.clear();expected.clear();message_index=0;gfx_ticks=0;
        for(unsigned i=0;i<60;++i){messages.push_back(0x19);expected.push_back(uint32_t(messages.size()));if(i%3==0)messages.push_back(0xFFFF);}
        if(!setjmp(native_done))main_thread(rdram,&ctx);
        require(observed==expected,"Achievement sampling duplicated, skipped, or evaluated a non-VI native event");
        require(gfx_ticks==60/divisor,"Fixture failed to exercise native rendering divisor");
        std::printf("native VI cadence: %zu achievement calls, %u graphics ticks, divisor %u\n",observed.size(),gfx_ticks,divisor);
    }
}
static void identity(const char* path){
    using namespace wr64::achievements::native;
    std::ifstream stream(path,std::ios::binary);std::vector<uint8_t> original(std::istreambuf_iterator<char>(stream),{});
    require(identify_rom(original)==original_rom_hash,"Original supported USA Rev1 identity rejected");
    game_initialized(original);require(selected_identity==original_rom_hash,"Lifecycle did not publish actual cartridge identity");
    auto swapped=original;for(size_t i=0;i<swapped.size();i+=4)std::swap(swapped[i],swapped[i+3]),std::swap(swapped[i+1],swapped[i+2]);
    require(identify_rom(swapped)==original_rom_hash,"Official N64 hash failed to normalize little-endian cartridge");
    auto patched=original;require(wr64::rom_patch::apply_if_unpatched(patched),"Shipped patch rejected native cartridge");
    patched.resize((patched.size()+3)&~size_t(3));
    require(identify_rom(patched)==original_rom_hash,"Exact persisted patched ROM lost canonical cartridge identity");
    game_initialized(patched);require(selected_identity==original_rom_hash,"Cached-ROM lifecycle identity was not mapped");
    for(auto* rom:{&original,&patched}){
        (*rom)[0x2000]^=1;require(identify_rom(*rom).empty(),"Mutated unsupported image impersonated accepted ROM");
    }
    game_initialized(patched);require(selected_identity.empty(),"Unsupported new image retained previous game identity");
    require(identify_rom({}).empty(),"Empty ROM accepted");patched.resize(64);require(identify_rom(patched).empty(),"Truncated ROM accepted");
}
int main(int argc,char** argv){try{
    require(argc==2,"Private original cartridge path required");records::official_definitions();memory_reads();cadence();identity(argv[1]);
    std::printf("PASS achievements native integration: %zu checks; official record definitions, raw RA memory/bounds, real VI branch, original+cached ROM identities.\n",checks);return 0;
}catch(const std::exception& e){std::fprintf(stderr,"FAIL: %s\n",e.what());return 1;}}
