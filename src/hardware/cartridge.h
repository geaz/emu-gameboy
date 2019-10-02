#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

namespace GGB
{
    namespace Enums
    {
        enum class CARTRIDGE_FLAG
        {
            TYPE = 0x0147,
            SWITCH_BANK_TRIGGER_START = 0x2000,
            SWITCH_BANK_TRIGGER_END = 0x3FFF,
            SWITCHABLE_BANK_START = 0x4000,
            SWITCHABLE_BANK_END = 0x7FFF
        };

        enum class CARTRIDGE_TYPE
        {
            ROM = 0x0,
            MBC1 = 0x1
        };
    }

    namespace Hardware
    {
        class Cartridge
        {
            public:
                Cartridge() { };
                Cartridge(std::string path);

                uint8_t read(uint16_t address);
                void selectRomBank(const uint8_t bankNr);

                std::string cartridgePath;
                bool supported = false;
                long cartridgeSize;

            private:
                char* cartridgeData;
                uint8_t selectedBankNr = 1;
        };
    }
}

#endif // CARTRIDGE_H