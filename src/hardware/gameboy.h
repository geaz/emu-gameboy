#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "memory.h"
#include "cartridge.h"

class Gameboy
{
    public:
        Gameboy(Cartridge& cartridge);
        void process();

        Cartridge& cartridge;
        Memory memory;
        Cpu cpu;
};

#endif // GAMEBOY_H