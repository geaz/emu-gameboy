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
        
        checkStart();
        checkRestartTrigger();

        while(cycleCountLength >= Const::Cycles256Hz)
        {
            waveChannel.lengthTick();
            cycleCountLength -= Const::Cycles256Hz;
        }

        waveChannel.cycle(cycles);
        
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
}