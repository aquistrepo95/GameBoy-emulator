#include "EmulatorClock.hpp" 


EmulatorClock :: EmulatorClock(Timer& t) : timer(t) {}


bool EmulatorClock :: cycle_tick(std::uint32_t cycles) {
    total_cycles += cycles;

    bool overflow_interupt = timer.cycle_tick(cycles);

    // add PPU and APU here

    return overflow_interupt;
}