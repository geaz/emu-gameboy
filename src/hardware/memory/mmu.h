#pragma once
#ifndef MMU_H
#define MMU_H

#include "../cartridge.h"
#include "../../ggb_enums.h"
#include "../../ggb_constants.h"

namespace GGB
{
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

                bool readIORegisterBit(const uint16_t reg, const uint8_t flag, const bool ppuAccess = false) const;
                void writeIORegisterBit(const uint16_t reg, const uint8_t flag, const bool value);

                Enum::LcdMode readLcdMode() const;
                void writeLcdMode(const Enum::LcdMode lcdMode);

            private:
                Cartridge& cartridge;
                // Because the mode gets rapidly read
                // we also save it in this variable for faster access
                Enum::LcdMode currentPpuMode = Enum::LcdMode::HBlank;
                // The gameboy is able to address 16bit memory room
                // Thats why the memory is always of size 0x10000 (Highest Adress 0xFFFF)
                // The cartridge gets mapped into 0x0100 - 0x3FFF (larger cartridges use bank switching)
                // Remaining mapping here: http://bgb.bircd.org/pandocs.htm#memorymap
                uint8_t memory[Const::MemorySize]; 
        };
    }
}

#endif // MMU_H