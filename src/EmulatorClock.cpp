#include "EmulatorClock.hpp" 


EmulatorClock :: EmulatorClock(Timer& t) : timer(t) {}


bool EmulatorClock :: cycle_tick(u32 cycles) {
    total_cycles += cycles;

    bool overflow_interupt = timer.cycle_tick(cycles);

    // add PPU and APU here

    return overflow_interupt;
}