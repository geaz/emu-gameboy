#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "cartridge.h"
#include "video/ppu.h"
#include "memory/mmu.h"

class Gameboy
{
    public:
        Gameboy(Cartridge& cartridge);
        void process();

        Cartridge& cartridge;
        Mmu mmu;
        Cpu cpu;
        Ppu ppu;
};

#endif // GAMEBOY_H