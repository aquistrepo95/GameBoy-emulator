#ifndef MBC_BUS_HPP
#define MBC_BUS_HPP
#include "types.hpp"

class MBC_bus {
    protected:
        // offset values
        u32 lower_bound_offset = 0x0000;
        u32 upper_bound_offset = 0x4000;
        u32 eram_offset        = 0x0000;
        
        // eram available or not
        bool eram_enabled = false;

        // current cartridge rom and eram sizes
        u32 rom_size  = 0;
        u32 eram_size = 0;

    public:
        // destructor
        virtual ~MBC_bus() = default;

        // calculate the offsets and find the banks
        virtual void calculate_and_find_banks(u16 address, u8 value) = 0;

        // setters for rom and ram size
        void set_rom_size(u32 rom_size)  {this->rom_size = rom_size;}
        void set_ram_size(u32 eram_size) {this->eram_size = eram_size;} 
        u32 get_eram_size() {return eram_size;}

        // getters for the MMU
        u32 get_rom_lower_offset() const {return lower_bound_offset;}
        u32 get_rom_upper_offset() const {return upper_bound_offset;}
        u32 get_eram_offset() const {return eram_offset;}
        bool get_eram_enabled() const {return eram_enabled;}
};


#endif // MBC_BUS_HPP