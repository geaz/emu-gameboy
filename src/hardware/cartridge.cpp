#include <fstream>
#include "cartridge.h"

namespace GGB::Hardware
{
    Cartridge::Cartridge(std::string path) : cartridgePath(path)
    {
        using Enums::CARTRIDGE_FLAG;
        using Enums::CARTRIDGE_TYPE;

        std::ifstream cartridgeFile;
        cartridgeFile.open(cartridgePath, std::ifstream::binary);
        
        cartridgeFile.seekg(0, cartridgeFile.end);
        cartridgeSize = (unsigned long) cartridgeFile.tellg();
        cartridgeFile.seekg(0, cartridgeFile.beg);

        cartridgeData = new char[cartridgeSize];
        cartridgeFile.read(cartridgeData, cartridgeSize);
        cartridgeFile.close();

        supported = 
            cartridgeData[(uint16_t)CARTRIDGE_FLAG::TYPE] >= (uint8_t)CARTRIDGE_TYPE::ROM 
            && cartridgeData[(uint16_t)CARTRIDGE_FLAG::TYPE] <= (uint8_t)CARTRIDGE_TYPE::MBC1;
    }

    uint8_t Cartridge::read(uint16_t address)
    {
        using Enums::CARTRIDGE_FLAG;

        if(address >= (uint16_t)CARTRIDGE_FLAG::SWITCHABLE_BANK_START 
        && address <= (uint16_t)CARTRIDGE_FLAG::SWITCHABLE_BANK_END)
            return (uint8_t)cartridgeData[address + ((selectedBankNr - 1) * 0x4000)];
        else
            return (uint8_t)cartridgeData[address];
    }

    void Cartridge::selectRomBank(const uint8_t bankNr)
    {
        selectedBankNr = bankNr;
    }
}