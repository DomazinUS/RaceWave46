#include "wr64_game_rumble.hpp"
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

namespace {
bool input_ready = true;
std::array<bool, 2> output{};
void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(1); }
}
wr64::rumble::BoatSample boat() {
    wr64::rumble::BoatSample sample;
    sample.active = true;
    sample.racer = 2;
    return sample;
}

void event_contract() {
    using wr64::rumble::MotorState;
    MotorState state;
    auto sample = boat();
    sample.collision[1] = 0.01f;
    state.submit(sample);
    require(state.intensity() == 255 && state.decay() == 9, "Collision onset must request255/decay9");
    state.tick();
    require(!state.on() && state.intensity() == 246, "First255-unit duty tick does not reach256");
    state.tick();
    require(state.on() && state.intensity() == 237, "Second impact tick must enable the motor");
    state.submit(sample);
    require(state.intensity() == 237, "A sustained collision must not retrigger the impact");
    for (int i = 0; i < 70; ++i) state.tick();
    require(state.intensity() == 0 && !state.on(), "Impact must decay completely");
    sample.collision = {};
    state.submit(sample);
    sample.collision[2] = -1.0f;
    state.submit(sample);
    require(state.intensity() == 255, "A cleared collision must rearm the next impact");

    state.reset(); sample = boat(); sample.pressed = 0x8000; sample.speed = 5.0f;
    state.submit(sample);
    require(state.intensity() == 200 && state.decay() == 6, "Low-speed A press must request200/decay6");
    state.reset(); sample.pressed = 0x2000;
    state.submit(sample);
    require(state.intensity() == 200, "Z shares the verified low-speed engine event");
    state.reset(); sample.pressed = 0x4000;
    state.submit(sample);
    require(state.intensity() == 0, "B does not produce the A/Z event");
    state.reset(); sample.pressed = 0x8000; sample.speed = 5.01f;
    state.submit(sample);
    require(state.intensity() == 0, "Engine event speed boundary must be inclusive5");
    sample.speed = 1.0f; sample.animation = 7;
    state.submit(sample);
    require(state.intensity() == 0, "Boarding animation suppresses the low-speed engine event");

    state.reset(); sample = boat(); sample.sea_contacts = 1; sample.acceleration = {-2.0f, 4.0f, 123.0f};
    state.submit(sample);
    require(state.intensity() == 171 && state.decay() == 9,
        "Contact intensity must be50+121=171; Z coefficient is zero");
    sample.acceleration = {0.1f, 0.0f, 0.0f};
    state.submit(sample);
    require(state.intensity() == 171, "Weaker request must preserve the pending intensity and decay");
    state.reset(); sample.acceleration = {0.1f, 0.0f, 0.0f}; state.submit(sample);
    require(state.intensity() == 2 && state.decay() == 1, "Contact intensity truncates rather than rounds");
    state.reset(); sample.acceleration = {0.0f, 50.0f, 0.0f}; state.submit(sample);
    require(state.intensity() == 255 && state.decay() == 13, "Contact intensity saturates at255");
    state.reset(); sample.sea_contacts = 0; state.submit(sample);
    require(state.intensity() == 0, "Airborne acceleration alone must not rumble");
    sample.sea_contacts = 1; sample.collision[0] = 1.0f; state.submit(sample);
    require(state.intensity() == 255 && state.decay() == 9, "Impact has priority over acceleration");
    sample.active = false; state.submit(sample);
    require(!state.on() && state.intensity() == 0, "Inactive state must clear pending motor output");
    sample.active = true; state.submit(sample); sample.racer = 3; state.submit(sample);
    require(state.intensity() == 255, "Ownership change must reset the impact edge latch");
    sample.speed = std::numeric_limits<float>::quiet_NaN(); state.submit(sample);
    require(!state.on() && state.intensity() == 0, "Invalid physics values must stop safely");
}

void clock_contract() {
    wr64::rumble::DutyClock clock;
    require(clock.advance(0) == 0, "Clock must initialize without a made-up tick");
    require(clock.advance(16'666'666) == 0, "Sub-frame time must accumulate");
    require(clock.advance(16'666'667) == 1, "Fractional60Hz boundary lost");
    require(clock.advance(50'000'000) == 2, "Three motor ticks per50ms native game update");
    clock.reset(); clock.advance(0);
    unsigned ticks = 0;
    for (uint64_t t = 1'000'000; t <= 1'000'000'000; t += 1'000'000) ticks += clock.advance(t);
    require(ticks == 60, "One-second1000Hz host loop must yield exactly60motor ticks");
    require(clock.advance(11'000'000'000) == 6, "Long-stall catch-up must stay bounded");
    require(clock.advance(1) == 0, "Backward clock input must reset its timebase");
    // First16 duty decisions for the independently derived native engine
    // request200/decay6. Checks pulse placement, not just average intensity.
    auto sample = boat(); sample.pressed = 0x8000;
    wr64::rumble::MotorState motor; motor.submit(sample);
    for (char expected : std::string("0110110110101010")) {
        motor.tick();
        require(motor.on() == (expected == '1'), "Engine duty waveform differs from native decisions");
    }
}

template<class T> void word(std::vector<uint8_t>& memory, uint32_t address, T value) {
    static_assert(sizeof(T)==4); std::memcpy(memory.data()+(address&0x7FFFFF),&value,4);
}
void half(std::vector<uint8_t>& memory, uint32_t address, int16_t value) {
    std::memcpy(memory.data()+((address&0x7FFFFF)^2),&value,2);
}
void adapter_contract() {
    std::vector<uint8_t> memory(8*1024*1024);
    word(memory,0x801CE638,1); word(memory,0x801CE648,1); half(memory,0x801CE624,-1);
    word(memory,0x800DAB28,2); word(memory,0x80154344,2); word(memory,0x801982F0,4);
    // Opposite physical port ordering and nonzero selected racers catch an
    // accidental assumption that human boats always occupy slots0/1.
    word(memory,0x80154330,1); word(memory,0x80154334,0);
    word(memory,0x800D48DC,3); word(memory,0x800D48E0,2);
    const uint32_t p1=0x80192690+3*0x1718, p2=0x80192690+2*0x1718;
    half(memory,p1+0xB58,int16_t(0xA000)); word(memory,p1+0xB90,4.0f);
    word(memory,p2+0x15BC,1.0f); word(memory,p2+0xC78,5);
    auto samples=wr64::rumble::read_usa_samples(memory.data());
    require(samples[1].active && samples[1].racer==3 && samples[1].pressed==0xA000 && samples[1].speed==4,
        "USA reader lost selected racer, port mapping or halfword lane");
    require(samples[0].active && samples[0].racer==2 && samples[0].collision[2]==1 && samples[0].sea_contacts==5,
        "Second player read wrong USA boat stride/fields");
    half(memory,0x801CE624,0); samples=wr64::rumble::read_usa_samples(memory.data());
    require(!samples[0].active && !samples[1].active,"Pause must suppress both players");
    half(memory,0x801CE624,-1); word(memory,0x801CE648,2);
    require(!wr64::rumble::read_usa_samples(memory.data())[0].active,"Attract/demo controller must not rumble");
    word(memory,0x801CE648,1); half(memory,0x800D4964,1);
    require(!wr64::rumble::read_usa_samples(memory.data())[0].active,"Auto control must not rumble");
    half(memory,0x800D4964,0); half(memory,p2+0x1446,-1);
    require(!wr64::rumble::read_usa_samples(memory.data())[0].active,"Manual-to-AI rider state must not rumble");
    half(memory,p2+0x1446,0); word(memory,0x800D48E0,1000);
    require(!wr64::rumble::read_usa_samples(memory.data())[0].active,"Invalid racer must not read outside boat array");
    word(memory,0x800D48E0,2); word(memory,0x80154330,3);
    require(!wr64::rumble::read_usa_samples(memory.data())[1].active,"Unsupported host port must remain absent");
    require(!wr64::rumble::read_usa_samples(nullptr)[0].active,"Null RDRAM should stop");

    wr64_game_rumble_sample(memory.data()); wr64_game_rumble_set_enabled(false); wr64_game_rumble_update();
    require(!output[0] && !output[1],"Disabling must clear both motor requests");
    wr64_game_rumble_set_enabled(true); input_ready=false; wr64_game_rumble_update();
    require(!output[0] && !output[1],"Uninitialized host must stay silent");
    wr64_game_rumble_reset(); input_ready=true;
}
}
namespace wr64::input {
bool ready(){return input_ready;}
void set_rumble(int controller,bool enabled){require(controller>=0&&controller<2,"Invalid output port");output[controller]=enabled;}
}
int main(){event_contract();clock_contract();adapter_contract();std::cout<<"Gameplay rumble event, duty and USA adapter contracts passed\n";}
