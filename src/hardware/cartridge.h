#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>

class Cartridge
{
    public:
        Cartridge() { };
        Cartridge(std::string path);

        char getDataAt(int address);

        std::string cartridgePath;
        unsigned long cartridgeSize;
        char* cartridgeData;
};

#endif // CARTRIDGE_H