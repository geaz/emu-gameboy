#pragma once
#ifndef MMU_H
#define MMU_H

#include <vector>
#include <chrono>
#include <functional>
#include "../cartridge.hpp"
#include "../../ggb_enums.hpp"
#include "../../ggb_constants.hpp"

namespace GGB
{
    namespace Hardware
    {
        struct MemoryWriteEvent
        {
            uint16_t address;
            uint8_t value;
            std::chrono::time_point<std::chrono::high_resolution_clock> eventTime;
        };

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

                void registerOnAddrWrite(std::function<void (MemoryWriteEvent)> eventFunc);

            private:
                Cartridge& cartridge;
                std::vector<std::function<void (MemoryWriteEvent)>> eventFuncList;
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