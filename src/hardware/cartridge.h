#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

enum CartridgeFlags
{
    TYPE = 0x0147,
    ROM_SWITCHING_START = 0x2000,
    ROM_SWITCHING_END = 0x3FFF
};

enum CartridgeType
{
    ROM = 0x0,
    MBC1 = 0x1
};

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

        const uint16_t SWITCH_ROM_START = 0x4000;
        const uint16_t SWITCH_ROM_END = 0x7FFF;
};

#endif // CARTRIDGE_H