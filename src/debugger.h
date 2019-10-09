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

            char breakPoint[4] = "";

            float square1Left[Const::AudioBufferFrames];
            float square1Right[Const::AudioBufferFrames];
            float square2Left[Const::AudioBufferFrames];
            float square2Right[Const::AudioBufferFrames];
            float waveLeft[Const::AudioBufferFrames];
            float waveRight[Const::AudioBufferFrames];
            float noiseLeft[Const::AudioBufferFrames];
            float noiseRight[Const::AudioBufferFrames];

        private:          
            void updateWaves();

            uint32_t sampleCount = 0;
    };
}

#endif // GGBDEBUGGER_H