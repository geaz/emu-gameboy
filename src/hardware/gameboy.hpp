#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.hpp"
#include "timer.hpp"
#include "input.hpp"
#include "clock.hpp"
#include "cartridge.hpp"
#include "video/ppu.hpp"
#include "memory/mmu.hpp"
#include "audio/apu.hpp"
#include "../debugger.hpp"

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