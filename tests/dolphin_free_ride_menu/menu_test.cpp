#include "recomp.h"
#include "wr64_free_ride_menu.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
extern "C" {
void func_i4_802C58F8(uint8_t*, recomp_context*);
void baseline_func_i4_802C58F8(uint8_t*, recomp_context*);
void func_i4_802C6C2C(uint8_t*, recomp_context*);
void baseline_func_i4_802C6C2C(uint8_t*, recomp_context*);
void wr64_free_ride_course_refresh(uint8_t*);
}
using Ram = std::vector<uint8_t>;
bool available = true;
unsigned checks = 0;
void check(bool condition, const char* message) {
    ++checks;
    if (!condition) { std::cerr << message << '\n'; std::exit(1); }
}
extern "C" uint32_t wr64_dolphin_free_ride_available(const uint8_t*) { return available; }
extern "C" void* wr64_test_address(uint8_t* ram, uint64_t address, unsigned width, const char*, int) {
    const auto a = uint32_t(address);
    check(a >= 0x80000000 && a <= 0x80800000-width, "native access outside RDRAM");
    return ram + (a & 0x7FFFFF);
}
void put(Ram& ram, uint32_t a, int32_t v) { *reinterpret_cast<int32_t*>(&ram[a & 0x7FFFFF]) = v; }
int32_t get(Ram& ram, uint32_t a) { return *reinterpret_cast<int32_t*>(&ram[a & 0x7FFFFF]); }
void half(Ram& ram, uint32_t a, int16_t v) { *reinterpret_cast<int16_t*>(&ram[(a & 0x7FFFFF)^2]) = v; }
Ram fixture(int players=2, int kind=1) {
    Ram ram(0x800000);
    put(ram,0x801CE638,5); put(ram,0x801CE608,kind); half(ram,0x801CE60C,players);
    put(ram,0x800DA9D0,1);
    for(int i=0;i<9;++i) put(ram,0x800DAAD8+i*4,i);
    // Authored table shape: four lists of eight course IDs and unlock counts.
    for(int d=0;d<4;++d) {
        put(ram,0x801CB288+d*4,7);
        for(int i=0;i<8;++i) half(ram,0x800EAC14+d*16+i*2,i+1);
    }
    return ram;
}
void run(Ram& ram, void(*f)(uint8_t*,recomp_context*)) {
    recomp_context c{};c.r29=S32(0x807FF000);c.r31=0x12345678;
    f(ram.data(),&c);check(uint32_t(c.r29)==0x807FF000,"stack not restored");
}
void input(Ram& ram, int buttons) { half(ram,0x801CE65A+28*get(ram,0x802C76B0),buttons); }
int main() {
    check(wr64::free_ride::enabled(), "validated Free Ride default must stay on");
    auto ram=fixture(); auto baseline=ram;
    run(ram,func_i4_802C58F8);run(baseline,baseline_func_i4_802C58F8);
    check(get(ram,0x802C7558)==1 && get(ram,0x802C76A4)==0,"Dolphin not unlocked");
    for(int i=1;i<9;++i) {
        check(get(ram,0x802C7558+4*i)==get(baseline,0x802C7558+4*i),"other course availability changed");
        for(int d=0;d<4;++d) check(get(ram,0x802C757C+i*16+d*4)==get(baseline,0x802C757C+i*16+d*4),"other difficulty changed");
    }
    input(ram,0x800);run(ram,func_i4_802C6C2C);check(get(ram,0x800DA9D0)==0,"up from Sunny must select Dolphin");
    input(ram,0x800);run(ram,func_i4_802C6C2C);check(get(ram,0x800DA9D0)==8,"up from Dolphin must wrap");
    input(ram,0x400);run(ram,func_i4_802C6C2C);check(get(ram,0x800DA9D0)==0,"down must wrap to Dolphin");
    input(ram,0x8000);run(ram,func_i4_802C6C2C);
    check(get(ram,0x801CE630)==40 && get(ram,0x800DAB24)==21,"confirm must use native level transition");
    check(get(ram,0x801CE608)==1,"VS kind must remain intact");
    check(get(ram,0x801CB338)==0 && get(ram,0x801CE61C)==1,"Free Ride defaults incorrect");
    // The new row remains available while selecting any existing race course.
    for(int course=1;course<9;++course) {
        auto a=fixture();run(a,func_i4_802C58F8);put(a,0x800DA9D0,course);
        input(a,0x8000);auto b=a;
        run(a,func_i4_802C6C2C);run(b,baseline_func_i4_802C6C2C);
        check(a==b,"existing VS course confirmation changed");
    }
    for(int players:{1,2}) for(int kind:{0,1,4,11}) for(bool valid:{false,true}) {
        if(players==2 && kind==1 && valid) continue;
        available=valid; auto a=fixture(players,kind);auto b=a;
        run(a,func_i4_802C58F8);run(b,baseline_func_i4_802C58F8);
        check(a==b,"unrelated menu initialization changed");
        input(a,0x8000);input(b,0x8000);
        run(a,func_i4_802C6C2C);run(b,baseline_func_i4_802C6C2C);
        check(a==b,"unrelated confirmation changed");
    }
    available=true;
    wr64::free_ride::set_enabled(false);
    auto disabled=fixture(); auto native=disabled;
    run(disabled,func_i4_802C58F8);run(native,baseline_func_i4_802C58F8);
    check(disabled==native,"OFF must restore native course menu");
    input(disabled,0x800);input(native,0x800);
    run(disabled,func_i4_802C6C2C);run(native,baseline_func_i4_802C6C2C);
    check(disabled==native && get(disabled,0x800DA9D0)==8,"OFF navigation must skip Dolphin");
    // Toggle in the settings overlay while Course Select is already open.
    wr64::free_ride::set_enabled(true);
    input(disabled,0);run(disabled,func_i4_802C6C2C);
    check(get(disabled,0x802C7558)==1 && get(disabled,0x802C76A4)==0,"ON did not refresh open menu");
    put(disabled,0x800DA9D0,0);wr64::free_ride::set_enabled(false);
    input(disabled,0x8000);run(disabled,func_i4_802C6C2C);
    check(get(disabled,0x800DA9D0)==1 && get(disabled,0x802C7558)==0,"OFF must deselect and lock Dolphin");
    check(get(disabled,0x801CE630)!=40,"disabled highlighted Dolphin entered a level");
    // A loaded Free Ride continues unchanged when the preference changes.
    auto live=fixture();put(live,0x801CE638,1);put(live,0x800DAB24,44);
    put(live,0x800DA9D0,0);auto saved=live;
    wr64_free_ride_course_refresh(live.data());
    check(live==saved,"OFF altered a running session");
    wr64::free_ride::set_enabled(true);
    std::cout << "PASS native menu unlock/navigation/confirm and exclusion checks: " << checks << '\n';
}
