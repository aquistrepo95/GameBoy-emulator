#include "Timer.hpp"

// respond to operation function
bool Timer :: respond_to_operation(uint16_t address) const {
    if(address >= 0xff04 && address <= 0xff07){
        return true;
    }

    return false;
}

// cycle tick function
bool Timer :: cycle_tick(std::uint32_t cycles) {
    // verify if TIMA overflowed
    bool overflow_interupt = false;

    // cycle loop
    while(cycles > 0) {
        // 4 cycles at a time
        std::uint32_t current_step = (cycles >= 4) ? 4 : cycles;
        cycles -= current_step;

        // get previous frequency signal from internal_timer_div
        bool previous_frequency_signal = verify_TAC_signal();

        // update internal_timer_div
        internal_timer_div += current_step;

        // get current frequency signal from internal_timer_div
        bool current_frequency_signal = verify_TAC_signal();
        
        // check for falling edge detection i.e frequency bit went from 1 to 0
        // update the TIMA register
        if(previous_frequency_signal && !current_frequency_signal) {
            TIMA += 1;

            // if TIMA overflows update it with TMA i.e if TIMA is 0 or greater and update request interupt
            if(TIMA == 0) {
                TIMA = TMA;
                overflow_interupt = true;
            }
        }
    }

    return overflow_interupt;
}

// read from IO function
std::uint8_t Timer :: read_from_IO(std::uint16_t address) {
    switch(address) {
        case 0xff04: return (internal_timer_div >> 8); // upper 8 bits of internal_timer_div
        case 0xff05: return TIMA;
        case 0xff06: return TMA;
        case 0xff07: return TAC;
        default:     return 0xff; // invalid address
    }
}

// write to IO function
void Timer :: write_to_IO(std::uint16_t address, std::uint8_t value) {
    switch(address) {
        case 0xff04: internal_timer_div = 0; break; // writing to this register resets it
        case 0xff05: TIMA = value; break;
        case 0xff06: TMA  = value; break;
        case 0xff07: TAC  = value & 0x07; break; // only lower 3 bits are writable
        default:     break; // invalid address
    }
}