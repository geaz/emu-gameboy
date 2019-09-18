#include "cartridge.h"

#include <fstream>

Cartridge::Cartridge(std::string path) : cartridgePath(path)
{
    std::ifstream cartridgeFile;
    cartridgeFile.open(cartridgePath, std::ifstream::binary);
    
    cartridgeFile.seekg(0, cartridgeFile.end);
    cartridgeSize = (unsigned long) cartridgeFile.tellg();
    cartridgeFile.seekg(0, cartridgeFile.beg);

    cartridgeData = new char[cartridgeSize];
    cartridgeFile.read(cartridgeData, cartridgeSize);
    cartridgeFile.close();
}

uint8_t Cartridge::getDataAt(uint16_t address)
{
    return (uint8_t) cartridgeData[address];
}