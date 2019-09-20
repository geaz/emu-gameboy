#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include "cartridge.h"
#include "memory_flags.h"

class Memory
{
    public:
        Memory(Cartridge& cartridge);

        void write(const uint16_t address, const uint8_t value);
        uint8_t read(const uint16_t address, const bool debugAccess = false) const;

        uint8_t readIORegister(const IORegister reg) const;
        uint8_t readIORegisterBit(const IORegister reg, const uint8_t bitNr) const;
        void writeIORegisterBit(const IORegister reg, const uint8_t bitNr, const bool value);

        uint32_t getSize() const;

    private:
        Cartridge& cartridge;
        // The gameboy is able to address 16bit memory room
        // Thats why the memory is always of size 0x10000 (Highest Adress 0xFFFF)
        // The cartridge gets mapped into 0x0100 - 0x3FFF (larger cartridges use bank switching)
        // Remaining mapping here: http://bgb.bircd.org/pandocs.htm#memorymap
        uint32_t memorySize = 0x10000;
        uint8_t memory[0x10000]; 
};

#endif // MEMORY_H