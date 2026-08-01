#ifndef SYSTEM_BUS_HPP
#define SYSTEM_BUS_HPP
#include <cstdint>

class SystemBus {
    public:
        // virtual destructor
        virtual ~SystemBus() = default;

        // this function will return true if the object(IO) is responsible for the memory address
        virtual bool respond_to_operation(std::uint16_t address) const  = 0;

        // read or write to IO devices
        virtual std::uint8_t read_from_IO(std::uint16_t address) = 0;
        virtual void write_to_IO(std::uint16_t address, std::uint8_t value) = 0;

};


#endif // SYSTEM_BUS_HPP