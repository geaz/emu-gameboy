#include "apu.h"
#include <iostream>
#include <algorithm>

namespace GGB::Hardware
{
    Apu::Apu(Mmu& mmu) 
        : mmu(mmu), 
        squareChannel1(mmu, square1Parameters),
        squareChannel2(mmu, square2Parameters),
        waveChannel(mmu),
        noiseChannel(mmu)
    {         
        outputFile.open ("test.txt");
        memset(square2DataLeft, 0, Const::AudioBufferFrames);
        memset(square2DataRight, 0, Const::AudioBufferFrames);
        memset(waveDataLeft, 0, Const::AudioBufferFrames);
        memset(waveDataRight, 0, Const::AudioBufferFrames);
    }

    void Apu::cycle(const uint8_t cycles)
    {
        checkWaveStart();
        checkRestartTrigger();

        cycleLength(cycles);
        cycleEnvelope(cycles);
        cycleSweep(cycles);
        cycleChannels(cycles);
        cycleSamples(cycles);
    }

    void Apu::checkWaveStart()
    {
        bool channel3On = mmu.readIORegisterBit(Const::AddrRegChannel3On, Const::FlagChannel3On);
        if(channel3On) waveChannel.start();
        else waveChannel.stop();
    }

    void Apu::checkRestartTrigger()
    {
        if(mmu.lastWriteEvent.eventTime != lastRelevantMemoryEvent.eventTime)
        {
            MemoryWriteEvent writeEvent = mmu.lastWriteEvent;            
            if(writeEvent.address == Const::AddrRegChannel1Data && writeEvent.value & Const::FlagChannelRestart)
            {
                lastRelevantMemoryEvent = mmu.lastWriteEvent;
                squareChannel1.restart();
            }
            else if(writeEvent.address == Const::AddrRegChannel2Data && writeEvent.value & Const::FlagChannelRestart)
            {
                lastRelevantMemoryEvent = mmu.lastWriteEvent;
                squareChannel2.restart();
            }
            else if(writeEvent.address == Const::AddrRegChannel3Data && writeEvent.value & Const::FlagChannelRestart)
            {
                lastRelevantMemoryEvent = mmu.lastWriteEvent;
                waveChannel.restart();
            }
            else if(writeEvent.address == Const::AddrRegChannel4Data && writeEvent.value & Const::FlagChannelRestart)
            {
                lastRelevantMemoryEvent = mmu.lastWriteEvent;
                noiseChannel.restart();
            }
        }
    }

    void Apu::cycleLength(const uint8_t cycles)
    {        
        cycleCountLength += cycles;
        while(cycleCountLength >= Const::Cycles256Hz)
        {
            squareChannel1.lengthTick();
            squareChannel2.lengthTick();
            waveChannel.lengthTick();
            noiseChannel.lengthTick();
            cycleCountLength -= Const::Cycles256Hz;
        }
    }

    void Apu::cycleEnvelope(const uint8_t cycles)
    {        
        cycleCountEnvelope += cycles;
        while(cycleCountEnvelope >= Const::Cycles64Hz)
        {
            squareChannel1.envelopeTick();
            squareChannel2.envelopeTick();
            noiseChannel.envelopeTick();
            cycleCountEnvelope -= Const::Cycles64Hz;
        }
    }

    void Apu::cycleSweep(const uint8_t cycles)
    {        
        cycleCountSweep += cycles;
        while(cycleCountSweep >= Const::Cycles128Hz)
        {
            squareChannel1.sweepTick();
            cycleCountSweep -= Const::Cycles128Hz;
        }
    }

    void Apu::cycleChannels(const uint8_t cycles)
    {        
        squareChannel1.cycle(cycles);
        squareChannel2.cycle(cycles);
        waveChannel.cycle(cycles);
        noiseChannel.cycle(cycles);
    }

    void Apu::cycleSamples(const uint8_t cycles)
    {
        cycleCount += cycles;
        while(cycleCount >= Const::CyclesAudioSample)
        {
            uint8_t volumeReg = mmu.read(Const::AddrRegOutputControl);
            float volumeLeft = (float)(volumeReg & Const::FlagOutputVolume) / 7;
            float volumeRight = (float)((volumeReg >> 4) & Const::FlagOutputVolume) / 7;
            
            uint8_t square1OutputLeft = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel1ToOutput1) && debugSquare1Enabled;
            uint8_t square1OutputRight = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel1ToOutput2) && debugSquare1Enabled;
            square1BufferLeft[sampleCounter] = square1OutputLeft ? squareChannel1.currentSample * volumeLeft : 0;
            square1BufferRight[sampleCounter] = square1OutputRight ? squareChannel1.currentSample * volumeRight : 0;

            uint8_t square2OutputLeft = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel2ToOutput1) && debugSquare2Enabled;
            uint8_t square2OutputRight = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel2ToOutput2) && debugSquare2Enabled;
            square2BufferLeft[sampleCounter] = square2OutputLeft ? squareChannel2.currentSample * volumeLeft : 0;
            square2BufferRight[sampleCounter] = square2OutputRight ? squareChannel2.currentSample * volumeRight : 0;

            uint8_t waveOutputLeft = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel3ToOutput1) && debugWaveEnabled;
            uint8_t waveOutputRight = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel3ToOutput2) && debugWaveEnabled;
            waveBufferLeft[sampleCounter] = waveOutputLeft ? waveChannel.currentSample * volumeLeft : 0;
            waveBufferRight[sampleCounter] = waveOutputRight ? waveChannel.currentSample * volumeRight : 0;

            uint8_t noiseOutputLeft = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel4ToOutput1) && debugWaveEnabled;
            uint8_t noiseOutputRight = mmu.readIORegisterBit(Const::AddrRegChannelControl, Const::FlagChannel4ToOutput2) && debugWaveEnabled;
            noiseBufferLeft[sampleCounter] = noiseOutputLeft ? noiseChannel.currentSample * volumeLeft : 0;
            noiseBufferRight[sampleCounter] = noiseOutputRight ? noiseChannel.currentSample * volumeRight : 0;

          //outputFile << std::to_string((float)(square2BufferLeft[sampleCounter] - 8) / 8) << " " << std::to_string((float)(square2BufferRight[sampleCounter] - 8) / 8) << " ";  
            
            sampleCounter++;

            if(sampleCounter == Const::AudioBufferFrames)
            {
                std::copy(square1BufferLeft, square1BufferLeft + Const::AudioBufferFrames, square1DataLeft);
                std::copy(square1BufferRight, square1BufferRight + Const::AudioBufferFrames, square1DataRight);
                std::copy(square2BufferLeft, square2BufferLeft + Const::AudioBufferFrames, square2DataLeft);
                std::copy(square2BufferRight, square2BufferRight + Const::AudioBufferFrames, square2DataRight);
                std::copy(waveBufferLeft, waveBufferLeft + Const::AudioBufferFrames, waveDataLeft);
                std::copy(waveBufferRight, waveBufferRight + Const::AudioBufferFrames, waveDataRight);
                std::copy(noiseBufferLeft, noiseBufferLeft + Const::AudioBufferFrames, noiseDataLeft);
                std::copy(noiseBufferRight, noiseBufferRight + Const::AudioBufferFrames, noiseDataRight);
                sampleCounter = 0;
            }
            cycleCount -= Const::CyclesAudioSample;
        }
    }
}