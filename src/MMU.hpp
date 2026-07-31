#ifndef MMU_HPP
#define MMU_HPP
#include <array>
#include <vector>
#include <cstdint>
#include <memory>
#include <string>
#include <functional>
#include "system_bus.hpp"
#include "MBC_bus.hpp"

class MMU{
    private:
        // boot rom mapped i.e nintento logo
        bool boot_rom_mapped = true;

        // memory allocation for cartridge
        std::vector<std::uint8_t> rom_bank; // rom
        std::vector<std::uint8_t> eram_bank; //external ram 

        // save path .sav
        std::string active_save_path;

        // memory allocation for gameboy internal components
        std::array<std::uint8_t, 0x1fff + 1> wram{}; // 8kb wram
        std::array<std::uint8_t, 0x7f> hram{}; // 127 hram
        std::uint8_t ie{}; // 8bit interrupt enable register

        // IO device vector
        std::vector<std::reference_wrapper<SystemBus>> IO_devices;

        // pointer to the MBC
        std::unique_ptr<MBC_bus> mbc1;

    public:
        //constructor
        MMU() = default;

        // disable the boot ROM
        void disable_bootROM();

        // find the RAM size
        std::uint32_t find_eram_size(std::string active_save_path, std::uint8_t ram_size_header);

        // load the game ROM
        void load_ROM(const char*);

        // stop and save the ram state
        void save_eram();

        // getter and setter(read and write)
        std::uint8_t read_from_bytes(std::uint16_t address);
        void write_to_bytes(std::uint16_t address, std::uint8_t value);

        // function to add IO to IO_devices
        void add_IO_devices(SystemBus& IO_device) {
            IO_devices.push_back(std::ref(IO_device));
        }

};

#endif //MMU_HPP