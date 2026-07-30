#include "Timer.hpp"

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