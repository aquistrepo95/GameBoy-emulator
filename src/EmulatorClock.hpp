#ifndef EMULATORCLOCK_HPP
#define EMULATORCLOCK_HPP
#include "Timer.hpp"
#include "PPU.hpp"
#include "APU.hpp"


class EmulatorClock {
    private:

        std::uint64_t total_cycles = 0;
        Timer& timer;
        //PPU& ppu;
        //APU& apu; // define these later i.e I havent written PPU and APU classes yet

    public:

    EmulatorClock(Timer& timer); // add ppu and apu shortly
    bool cycle_tick(std::uint32_t cycles);
};



#endif // EMULATORCLOCK_HPP