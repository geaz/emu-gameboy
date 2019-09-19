#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include "cartridge.h"

class Memory
{
    public:
        Memory(Cartridge& cartridge);
        
        uint32_t getSize();
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

    private:
        Cartridge& cartridge;
        // The gameboy is able to address 16bit memory room
        // Thats why the memory is always of size 0x10000 (Highest Adress 0xFFFF)
        // The cartridge gets mapped into 0x0100 - 0x3FFF (larger cartridges use bank switching)
        // Remaining mapping here: http://gameboy.mongenel.com/dmg/asmmemmap.html
        uint32_t memorySize = 0x10000;
        uint8_t memory[0x10000]; 
};

#endif // MEMORY_H