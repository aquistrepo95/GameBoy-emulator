#ifndef TIMER_HPP
#define TIMER_HPP
#include <cstdint>
#include "EmulatorClock.hpp"

class Timer{
    private:
        // internal registers i.e 16-bit internal timer(div 1st 8-bits), TIMA, TMA, TAC
        std::uint16_t internal_timer_div = 0;
        std::uint8_t TIMA = 0;
        std::uint8_t TMA  = 0;
        std::uint8_t TAC  = 0;

        // frequency bits in the internal_timer_div register i.e this will set the frequency of TIMA
        // TAC bits 1-0: 00 = Bit 9, 01 = Bit 3, 10 = Bit 5, 11 = Bit 7 i.e TAC = internal_timer_div bit
        static constexpr std::uint8_t TAC_frequency_bit[4] = {9, 3, 5, 7};

        // check if TAC enable bit is on(i.e bit 3 is 1) and check if frequency bit in the internal timer is set
        bool verify_TAC_signal() const{
            // TAC is disabled
            if((TAC & 0x04) == 0) {return false;}

            // get lowest 2 bits of TAC and verify the whether the bit location is turned on in internal_timer_div
            std::uint8_t bit_shift    = TAC_frequency_bit[(TAC & 0x03)];
            std::uint16_t shifted_bit = 1 << bit_shift;
            return (internal_timer_div & shifted_bit) != 0;
        }

    public:
        Timer() = default;

        bool cycle_tick(std::uint32_t cycles);
};


#endif // TIMER_HPP