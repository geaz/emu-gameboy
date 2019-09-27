#pragma once
#ifndef MMU_H
#define MMU_H

#include "../cartridge.h"
#include "memory_flags.h"

class Mmu
{
    public:
        Mmu(Cartridge& cartridge);

        uint8_t read(const uint16_t address, const bool ppuAccess = false) const;
        void write(const uint16_t address, const uint8_t value, const bool ppuAccess = false);
        void executeDmaTransfer(const uint8_t value);

        uint8_t readIORegister(const IORegister reg) const;
        uint8_t readIORegisterBit(const IORegister reg, const uint8_t bitNr) const;
        void writeIORegisterBit(const IORegister reg, const uint8_t bitNr, const bool value);

        LCDMode readLcdMode() const;
        void writeLcdMode(const LCDMode lcdMode);

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

#endif // MMU_H