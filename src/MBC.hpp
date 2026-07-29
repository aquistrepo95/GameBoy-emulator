#ifndef MBC_HPP
#define MBC_HPP
#include <cstdint>
#include "MBC_bus.hpp"

class MBC1 : public MBC_bus{
    private:
        std::uint8_t  two_bit_register  = 0; // 2 bit register
        std::uint8_t  five_bit_register = 1; // 5 bit register
        std::uint8_t bank_mode_register = 0; // rom mode = 0 || eram mode = 1

        void calculate_offsets();

    public:    
        // pass the rom_size and eram_size variables from MBC_bus
        using MBC_bus :: MBC_bus;

        // function to find banks
        void calculate_and_find_banks(std::uint16_t address, std::uint8_t value) override;

};


#endif // MBC_HPP