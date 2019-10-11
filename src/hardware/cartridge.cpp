#include <fstream>
#include "cartridge.hpp"
#include "../ggb_constants.hpp"

namespace GGB::Hardware
{
    Cartridge::Cartridge(const std::string path) : cartridgePath(path)
    {
        std::ifstream cartridgeFile;
        cartridgeFile.open(cartridgePath, std::ifstream::binary);
        
        cartridgeFile.seekg(0, cartridgeFile.end);
        cartridgeSize = (unsigned long) cartridgeFile.tellg();
        cartridgeFile.seekg(0, cartridgeFile.beg);

        cartridgeData = new char[cartridgeSize];
        cartridgeFile.read(cartridgeData, cartridgeSize);
        cartridgeFile.close();

        supported = 
            cartridgeData[Const::AddrCartType] >= Const::CartTypeRom 
            && cartridgeData[Const::AddrCartType] <= Const::CartTypeMBC1;
    }

    uint8_t Cartridge::read(uint16_t address)
    {
        if(address >= Const::AddrSwitchBankStart && address <= Const::AddrSwitchBankEnd)
            return (uint8_t)cartridgeData[address + ((selectedBankNr - 1) * 0x4000)];
        else
            return (uint8_t)cartridgeData[address];
    }

    void Cartridge::selectRomBank(const uint8_t bankNr)
    {
        selectedBankNr = bankNr;
    }
}