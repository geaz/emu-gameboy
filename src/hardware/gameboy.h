#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "timer.h"
#include "input.h"
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
        Input input;
        Timer timer;

        const uint8_t DISPLAY_WIDTH = 166;
        const uint8_t DISPLAY_HEIGHT = 144;
};

#endif // GAMEBOY_H