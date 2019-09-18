#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include "cartridge.h"

class Memory
{
    public:
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

    private:
        Cartridge& cartridge;
};

#endif // MEMORY_H