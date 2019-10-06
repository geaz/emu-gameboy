#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "timer.h"
#include "input.h"
#include "clock.h"
#include "cartridge.h"
#include "video/ppu.h"
#include "memory/mmu.h"
#include "audio/apu.h"
#include "../debugger.h"

namespace GGB
{
    class GameBoy
    {
        public:
            GameBoy(Hardware::Cartridge& cartridge);
            
            void process();

            Hardware::Cartridge& cartridge;
            Hardware::Apu apu;
            Hardware::Mmu mmu;
            Hardware::Cpu cpu;
            Hardware::Ppu ppu;
            Hardware::Input input;
            Hardware::Timer timer;
            Hardware::Clock clock;
            Debugger debugger;
    };
}

#endif // GAMEBOY_H