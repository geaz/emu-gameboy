#include "apu.h"
#include <iostream>
#include <algorithm>

namespace GGB::Hardware
{
    Apu::Apu(Mmu& mmu) : mmu(mmu), waveChannel(mmu)
    {         
        outputFile.open ("test.txt");

        for(int i = 0; i < Const::AudioBufferFrames; i++)
        {
            waveDataLeft[i] = 0;
            waveDataRight[i] = 0;
        }
    }

    void Apu::cycle(uint8_t cycles)
    {
        cycleCount += cycles;
        cycleCountLength += cycles;
        
        if(mmu.lastWriteEvent.eventTime != lastRelevantMemoryEvent.eventTime
            && mmu.lastWriteEvent.address == Const::AddrRegChannel3Data
            && mmu.lastWriteEvent.value & Const::FlagChannelRestart)
        {
            lastRelevantMemoryEvent = mmu.lastWriteEvent;
            waveChannel.restart();
        }

        if(mmu.readIORegisterBit(Const::AddrRegChannel3On, Const::FlagChannel3On))
            waveChannel.start();
        else
            waveChannel.stop();

        while(cycleCountLength >= Const::Cycles256Hz)
        {
            waveChannel.lengthTick();
            cycleCountLength -= Const::Cycles256Hz;
        }
        waveChannel.cycle(cycles);

        auto test = Const::CyclesAudioSample;
        while(cycleCount >= Const::CyclesAudioSample)
        {
            waveBufferLeft[sampleCounter] = waveChannel.currentSample;
            waveBufferRight[sampleCounter] = waveChannel.currentSample;

          //outputFile << std::to_string((float)(waveBufferLeft[sampleCounter] - 8) / 8) << " " << std::to_string((float)(waveBufferRight[sampleCounter] - 8) / 8) << " ";  
            
            sampleCounter++;

            if(sampleCounter == Const::AudioBufferFrames)
            {
                std::copy(waveBufferLeft, waveBufferLeft + Const::AudioBufferFrames, waveDataLeft);
                std::copy(waveBufferRight, waveBufferRight + Const::AudioBufferFrames, waveDataRight);
                sampleCounter = 0;
            }
            cycleCount -= Const::CyclesAudioSample;
        }
    }
}