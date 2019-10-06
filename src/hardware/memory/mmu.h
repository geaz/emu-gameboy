#pragma once
#ifndef MMU_H
#define MMU_H

#include "../cartridge.h"
#include "io_register_flags.h"

namespace GGB
{
    namespace Constants
    {
        const uint32_t MEM_SIZE = 0x10000;
    }

    namespace Hardware
    {
        class Mmu
        {
            public:
                Mmu(Cartridge& cartridge);

                uint8_t read(const uint16_t address, const bool ppuAccess = false) const;
                void write(const uint16_t address, const uint8_t value);
                void rawWrite(const uint16_t address, const uint8_t value);
                void executeDmaTransfer(const uint8_t value);

                uint8_t readIORegister(const uint16_t reg, const bool ppuAccess = false) const;
                bool readIORegisterBit(const uint16_t reg, const uint8_t flag, const bool ppuAccess = false) const;
                void writeIORegisterBit(const uint16_t reg, const uint8_t flag, const bool value);

                Enums::LCD_MODE readLcdMode() const;
                void writeLcdMode(const Enums::LCD_MODE lcdMode);

            private:
                Cartridge& cartridge;
                // Because the mode gets rapidly read
                // we also save it in this variable for faster access
                Enums::LCD_MODE currentPpuMode = Enums::LCD_MODE::HBLANK;
                // The gameboy is able to address 16bit memory room
                // Thats why the memory is always of size 0x10000 (Highest Adress 0xFFFF)
                // The cartridge gets mapped into 0x0100 - 0x3FFF (larger cartridges use bank switching)
                // Remaining mapping here: http://bgb.bircd.org/pandocs.htm#memorymap
                uint8_t memory[Constants::MEM_SIZE]; 
        };
    }
}

#endif // MMU_H