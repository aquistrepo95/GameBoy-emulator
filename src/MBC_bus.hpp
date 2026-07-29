#ifndef MBC_BUS_HPP
#define MBC_BUS_HPP
#include <cstdint>


class MBC_bus {
    protected:
        // offset values
        std::uint32_t lower_bound_offset = 0x0000;
        std::uint32_t upper_bound_offset = 0x4000;
        std::uint32_t eram_offset        = 0x0000;
        
        // eram available or not
        bool eram_enabled = false;

        // current cartridge rom and eram sizes
        std::uint32_t rom_size  = 0;
        std::uint32_t eram_size = 0;

    public:
        // destructor
        virtual ~MBC_bus() = default;

        // calculate the offsets and find the banks
        virtual void calculate_and_find_banks(std::uint16_t address, std::uint8_t value) = 0;

        // setters for rom and ram size
        void set_rom_size(std::uint32_t rom_size)  {this->rom_size = rom_size;}
        void set_ram_size(std::uint32_t eram_size) {this->eram_size = eram_size;} 
        std::uint32_t get_eram_size() {return eram_size;}

        // getters for the MMU
        std::uint32_t get_rom_lower_offset() const {return lower_bound_offset;}
        std::uint32_t get_rom_upper_offset() const {return upper_bound_offset;}
        std::uint32_t get_eram_offset() const {return eram_offset;}
        bool get_eram_enabled() const {return eram_enabled;}
};


#endif // MBC_BUS_HPP