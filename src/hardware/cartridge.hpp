#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

namespace GGB
{
    namespace Hardware
    {
        class Cartridge
        {
            public:
                Cartridge() { };
                Cartridge(const std::string path);

                uint8_t read(const uint16_t address);
                void selectRomBank(const uint8_t bankNr);

                long cartridgeSize;
                bool supported = false;
                std::string cartridgePath;

            private:
                char* cartridgeData;
                uint8_t selectedBankNr = 1;
        };
    }
}

#endif // CARTRIDGE_H