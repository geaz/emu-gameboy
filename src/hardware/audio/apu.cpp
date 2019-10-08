#include "apu.h"
#include <iostream>
#include <algorithm>

namespace GGB::Hardware
{
    Apu::Apu(Mmu& mmu) 
        : mmu(mmu), waveChannel(mmu)
    {         
        outputFile.open ("test.txt");
        memset(waveDataLeft, 0, Const::AudioBufferFrames);
        memset(waveDataRight, 0, Const::AudioBufferFrames);
    }

    void Apu::cycle(uint8_t cycles)
    {
        checkStart();
        checkRestartTrigger();

        cycleLength(cycles);
        cycleEnvelope(cycles);
        cycleSweep(cycles);
        cycleChannels(cycles);
        cycleSamples(cycles);
    }

    void Apu::checkStart()
    {
        bool channel3On = mmu.readIORegisterBit(Const::AddrRegChannel3On, Const::FlagChannel3On) && debugWaveEnabled;
        if(channel3On) waveChannel.start();
        else waveChannel.stop();
    }

    void Apu::checkRestartTrigger()
    {
        if(mmu.lastWriteEvent.eventTime != lastRelevantMemoryEvent.eventTime)
        {
            MemoryWriteEvent writeEvent = mmu.lastWriteEvent;
            if(writeEvent.address == Const::AddrRegChannel3Data && writeEvent.value & Const::FlagChannelRestart)
            {
                lastRelevantMemoryEvent = mmu.lastWriteEvent;
                waveChannel.restart();
            }
        }
    }

    void Apu::cycleLength(uint8_t cycles)
    {        
        cycleCountLength += cycles;
        while(cycleCountLength >= Const::Cycles256Hz)
        {
            waveChannel.lengthTick();
            cycleCountLength -= Const::Cycles256Hz;
        }
    }

    void Apu::cycleEnvelope(uint8_t cycles)
    {        
        cycleCountEnvelope += cycles;
        while(cycleCountEnvelope >= Const::Cycles64Hz)
        {
            cycleCountEnvelope -= Const::Cycles64Hz;
        }
    }

    void Apu::cycleSweep(uint8_t cycles)
    {        
        cycleCountSweep += cycles;
        while(cycleCountSweep >= Const::Cycles128Hz)
        {
            cycleCountSweep -= Const::Cycles128Hz;
        }
    }

    void Apu::cycleChannels(uint8_t cycles)
    {        
        waveChannel.cycle(cycles);
    }

    void Apu::cycleSamples(uint8_t cycles)
    {
        cycleCount += cycles;
        while(cycleCount >= Const::CyclesAudioSample)
        {
            uint8_t volumeReg = mmu.read(Const::AddrRegOutputControl);
            uint8_t volumeLeft = volumeReg & Const::FlagOutputVolume;
            uint8_t volumeRight = (volumeReg >> 4) & Const::FlagOutputVolume;
            
            uint8_t waveOutputLeft = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel3ToOutput1);
            uint8_t waveOutputRight = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel3ToOutput2);


            waveBufferLeft[sampleCounter] = waveOutputLeft ? waveChannel.currentSample : 0;
            waveBufferRight[sampleCounter] = waveOutputRight ? waveChannel.currentSample : 0;

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