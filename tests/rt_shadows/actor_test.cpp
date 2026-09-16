#include "common/rt64_wr64_rt_actor_shadow.h"

#include <cstdlib>
#include <iostream>

static unsigned checks = 0;
static void require(bool value, const char *message) {
    ++checks;
    if (!value) { std::cerr << message << '\n'; std::exit(1); }
}

int main() {
    using namespace RT64;
    // Independently enumerate the original nineteen-by-four allocation, then
    // probe every byte around it, all segment aliases, and excluded blob slots.
    std::array<uint32_t, 76> matrices{};
    for (uint32_t component = 0; component < 19; ++component)
        for (uint32_t racer = 0; racer < 4; ++racer)
            matrices[component * 4 + racer] = 0x0300E108u + component * 256 + racer * 64;
    for (uint32_t address = 0x0300D000; address < 0x03011000; ++address) {
        uint32_t expected = 0;
        for (uint32_t i = 0; i < matrices.size(); ++i) if (address == matrices[i]) expected = 1u << (i % 4);
        require(wr64RTActorRacerMask(address) == expected, "Actor matrix boundary/stride classification");
    }
    for (uint32_t segment = 0; segment < 256; ++segment)
        require(wr64RTActorRacerMask((segment << 24) | 0xE108) == (segment == 3 ? 1u : 0u), "Segment alias admitted");
    for (uint32_t racer = 0; racer < 4; ++racer) {
        uint32_t mask = 0;
        for (uint32_t component = 0; component < 19; ++component)
            require(wr64RTAccumulateActorRacer(mask, matrices[component * 4 + racer]), "Same racer component rejected");
        require(mask == (1u << racer), "Wrong racer identity");
        require(!wr64RTAccumulateActorRacer(mask, matrices[(racer + 1) % 4]), "Mixed racers admitted");
        require(!wr64RTAccumulateActorRacer(mask, 0x0300F808 + racer * 64), "Native blob admitted as actor");
        require(!wr64RTAccumulateActorRacer(mask, 0x02000A40), "Static world matrix admitted as actor");
    }

    const std::array<std::array<float, 16>, 4> transforms{{
        {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},
        {0,0,-1,0, 0,2,0,0, 1,0,0,0, 8192,-32,32768,1},
        {.5f,.2f,-.4f,0, -.3f,1.2f,.8f,0, .7f,-.9f,.1f,0, -5000,200,-8000,1},
        {-1,.25f,0,0, .125f,.5f,0,0, 0,0,2,0, 65536,32768,-65536,1}
    }};
    const std::array<std::array<float, 3>, 4> positions{{ {0,0,0}, {80,60,-45}, {-24,37,19}, {8192,-32768,65536} }};
    const std::array<std::array<float, 3>, 4> velocities{{ {0,0,0}, {42,-17,11}, {-65,34,5}, {16384,-65535,131071} }};
    for (const auto &matrix : transforms) {
        Wr64RTActorShadowBounds bounds;
        for (size_t i = 0; i < positions.size(); ++i) {
            require(bounds.include(positions[i], velocities[i], matrix), "Finite actor point rejected");
            for (uint32_t step = 0; step <= 64; ++step) {
                const float weight = float(step) / 64;
                std::array<float, 3> position{};
                for (uint32_t component = 0; component < 3; ++component)
                    position[component] = positions[i][component] - velocities[i][component] * (1 - weight);
                for (uint32_t axis = 0; axis < 3; ++axis) {
                    // Match shader float arithmetic separately from helper's
                    // double endpoints; test fused and unfused evaluations.
                    const float result = position[0] * matrix[axis] + position[1] * matrix[4+axis] +
                        position[2] * matrix[8+axis] + matrix[12+axis];
                    const float fused = std::fma(position[0], matrix[axis], std::fma(position[1], matrix[4+axis],
                        std::fma(position[2], matrix[8+axis], matrix[12+axis])));
                    require(result >= bounds.minimum[axis] && result <= bounds.maximum[axis], "Interpolated actor escaped bounds");
                    require(fused >= bounds.minimum[axis] && fused <= bounds.maximum[axis], "Fused GPU actor escaped bounds");
                }
            }
        }
    }
    for (uint32_t fault = 0; fault < 4; ++fault) {
        Wr64RTActorShadowBounds bounds;
        auto matrix = transforms[0]; auto position = positions[0]; auto velocity = velocities[0];
        if (fault == 0) position[1] = std::numeric_limits<float>::quiet_NaN();
        if (fault == 1) velocity[2] = std::numeric_limits<float>::infinity();
        if (fault == 2) matrix[12] = std::numeric_limits<float>::infinity();
        if (fault == 3) { matrix[0] = std::numeric_limits<float>::max(); position[0] = 10; }
        require(!bounds.include(position, velocity, matrix) && !bounds.reliable, "Malformed actor remained bounded");
        require(!bounds.include(positions[0], velocities[0], transforms[0]), "Later valid point revived unreliable bounds");
    }
    Wr64RTActorShadowBounds empty;
    require(!empty.populated, "Empty bounds reported geometry");
    empty.invalidate();
    require(!empty.reliable && !empty.include(positions[0], velocities[0], transforms[0]), "Explicit fail-open lost");
    std::cout << checks << " actor identity/presentation bound checks passed.\n";
}
