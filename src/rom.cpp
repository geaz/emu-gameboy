#include "rom.h"

#include <fstream>

Rom::Rom(std::string path) : romPath(path)
{
    std::ifstream romFile;
    romFile.open(romPath, std::ifstream::binary);
    
    romFile.seekg(0, romFile.end);
    romSize = (unsigned long) romFile.tellg();
    romFile.seekg(0, romFile.beg);

    romData = new char[romSize];
    romFile.read(romData, romSize);
    romFile.close();
}