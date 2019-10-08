#include "debugger.h"

namespace GGB
{
    Debugger::Debugger(Hardware::Cartridge& cartridge, Hardware::Mmu& mmu, 
                Hardware::Cpu& cpu, Hardware::Apu& apu)
        : cartridge(cartridge), mmu(mmu), cpu(cpu), apu(apu) { }

    void Debugger::cycle()
    {
        wave3Right[channel3SampleCount++] = (float)(apu.waveChannel.currentSample - 8) / 8;
        if(channel3SampleCount > 1000000) channel3SampleCount = 0; 
    }
}