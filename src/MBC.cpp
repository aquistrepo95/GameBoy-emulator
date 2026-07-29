#include "MBC.hpp"

void MBC1 :: calculate_offsets() {
    // bank count i.e the number of the bank requested
    std::uint32_t lower_rom = 0;
    std::uint32_t upper_rom = five_bit_register;

    // find the upper ROM bank
    upper_rom |= (two_bit_register << 5);

    // bank_mode_register == 0 i.e ROM mode | == 1 i.e ERAM mode
    if(bank_mode_register == 1) {
        lower_rom |= (two_bit_register << 5);
    }

    // calculate the ROM offsets
    lower_bound_offset = (lower_rom * 0x4000) % rom_size;
    upper_bound_offset = (upper_rom * 0x4000) % rom_size;

    // calculate the ERAM offset
    if(eram_enabled && eram_size > 0) {
        eram_offset = (two_bit_register * 0x2000) % eram_size;
    }
    else{
        eram_offset = 0;
    }
}

void MBC1 :: calculate_and_find_banks(std::uint16_t address, std::uint8_t value) {
    // enable Ram if value is 0x0a
    if(address >= 0x000 && address <= 0x1fff) {
        eram_enabled = ((value & 0x0f) == 0x0a);
    }

    // 5 bits (NB: switchable bank should never be 0)
    else if(address >= 0x2000 && address <= 0x3fff) {
        five_bit_register = value & 0x1f;
        if(five_bit_register == 0x00) {
            five_bit_register = 0x01;
        }
        calculate_offsets();
    }

    // 2 bit value
    else if(address >= 0x4000 && address <= 0x5fff) {
        two_bit_register = value & 0x03;
        calculate_offsets();
    }

    // bank mode i.e rom mode = 0 || eram mode = 1
    else if(address >= 0x6000 && address <= 0x7fff) {
        bank_mode_register = value & 0x01;
        calculate_offsets();
    }
}
