#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "ppu.h"
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
        Ppu ppu;
};

#endif // GAMEBOY_H