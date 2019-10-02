#pragma once
#ifndef MMU_H
#define MMU_H

#include "../cartridge.h"
#include "io_register_flags.h"

namespace GGB::Hardware
{
    class Mmu
    {
        public:
            Mmu(Cartridge& cartridge);

            uint8_t read(const uint16_t address, const bool ppuAccess = false) const;
            void write(const uint16_t address, const uint8_t value);
            void rawWrite(const uint16_t address, const uint8_t value);
            void executeDmaTransfer(const uint8_t value);

            uint8_t readIORegister(const Enums::IO_REGISTER reg) const;
            bool readIORegisterBit(const Enums::IO_REGISTER reg, const uint8_t flag) const;
            void writeIORegisterBit(const Enums::IO_REGISTER reg, const uint8_t flag, const bool value);

            Enums::LCD_MODE readLcdMode() const;
            void writeLcdMode(const Enums::LCD_MODE lcdMode);

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
}

#endif // MMU_H