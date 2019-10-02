#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "timer.h"
#include "input.h"
#include "cartridge.h"
#include "video/ppu.h"
#include "memory/mmu.h"

namespace GGB
{
    class GameBoy
    {
        public:
            GameBoy(Hardware::Cartridge& cartridge);
            
            void process();

            Hardware::Cartridge& cartridge;
            Hardware::Mmu mmu;
            Hardware::Cpu cpu;
            Hardware::Ppu ppu;
            Hardware::Input input;
            Hardware::Timer timer;
    };
}

#endif // GAMEBOY_H