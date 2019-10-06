#pragma once
#ifndef GGBDEBUGGER_H
#define GGBDEBUGGER_H

#include "hardware/memory/mmu.h"
#include "hardware/audio/apu.h"
#include "hardware/cartridge.h"
#include "hardware/cpu.h"

namespace GGB
{
    class Debugger
    {
        public:
            Debugger(
                Hardware::Cartridge& cartridge, 
                Hardware::Mmu& mmu, 
                Hardware::Cpu& cpu, 
                Hardware::Apu& apu);

            void cycle();

            Hardware::Cartridge& cartridge;
            Hardware::Mmu& mmu;
            Hardware::Cpu& cpu; 
            Hardware::Apu& apu;

            float channel3Samples[100000];
            
        private:            
            uint32_t channel3SampleCount = 0;
    };
}

#endif // GGBDEBUGGER_H