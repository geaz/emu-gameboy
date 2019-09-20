#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

class Cartridge
{
    public:
        Cartridge() { };
        Cartridge(std::string path);

        uint8_t read(uint16_t address);

        std::string cartridgePath;
        long cartridgeSize;

    private:
        char* cartridgeData;
};

#endif // CARTRIDGE_H