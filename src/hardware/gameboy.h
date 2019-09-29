#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "timer.h"
#include "cartridge.h"
#include "video/ppu.h"
#include "memory/mmu.h"

enum Button
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    A,
    B,
    START,
    SELECT
};

class Gameboy
{
    public:
        Gameboy(Cartridge& cartridge);
        
        void process();
        void pressButton(Button button);

        Cartridge& cartridge;
        Mmu mmu;
        Cpu cpu;
        Ppu ppu;
        Timer timer;
};

#endif // GAMEBOY_H