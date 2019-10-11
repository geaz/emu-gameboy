#include "debugger.hpp"

#include "ggb_enums.hpp"
#include "screens/string_helper.hpp"

namespace GGB
{
    Debugger::Debugger(Hardware::Cartridge& cartridge, Hardware::Mmu& mmu, 
                Hardware::Cpu& cpu, Hardware::Apu& apu)
        : cartridge(cartridge), mmu(mmu), cpu(cpu), apu(apu) { }

    void Debugger::cycle()
    {
        updateWaves();
    }

    void Debugger::updateWaves()
    {
        square1Left[sampleCount] = (float)(apu.square1DataLeft[sampleCount] - 8) / 8;
        square1Right[sampleCount] = (float)(apu.square1DataRight[sampleCount] - 8) / 8;
        square2Left[sampleCount] = (float)(apu.square2DataLeft[sampleCount] - 8) / 8;
        square2Right[sampleCount] = (float)(apu.square2DataRight[sampleCount] - 8) / 8;
        waveLeft[sampleCount] = (float)(apu.waveDataLeft[sampleCount] - 8) / 8;
        waveRight[sampleCount] = (float)(apu.waveDataRight[sampleCount] - 8) / 8;
        noiseLeft[sampleCount] = (float)(apu.noiseDataLeft[sampleCount] - 8) / 8;
        noiseRight[sampleCount] = (float)(apu.noiseDataRight[sampleCount] - 8) / 8;

        sampleCount++;
        if(sampleCount == Const::AudioBufferFrames) sampleCount = 0;
    }
}