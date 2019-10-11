#include <iostream>
#include <algorithm>
#include "apu.hpp"

namespace GGB::Hardware
{
    Apu::Apu(Mmu& mmu) 
        : mmu(mmu), 
        squareChannel1(mmu, square1Parameters),
        squareChannel2(mmu, square2Parameters),
        waveChannel(mmu),
        noiseChannel(mmu) { }

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
        if(cycleCount >= Const::CyclesAudioSample)
        {
            uint8_t volumeReg = mmu.read(Const::AddrRegOutputControl);
            uint8_t volumeLeft = 8 - (volumeReg & Const::FlagOutputVolume);
            uint8_t volumeRight = 8 - ((volumeReg >> 4) & Const::FlagOutputVolume);
            
            uint8_t channelControl = mmu.read(Const::AddrRegChannelControl);
            uint8_t square1OutputLeft = channelControl & Const::FlagChannel1ToOutput1 && debugSquare1Enabled;
            uint8_t square1OutputRight = channelControl & Const::FlagChannel1ToOutput2 && debugSquare1Enabled;
            sampleData.square1Left[sampleCounter] = square1OutputLeft ? squareChannel1.currentSample / volumeLeft : 0;
            sampleData.square1Right[sampleCounter] = square1OutputRight ? squareChannel1.currentSample / volumeRight : 0;

            uint8_t square2OutputLeft = channelControl & Const::FlagChannel2ToOutput1 && debugSquare2Enabled;
            uint8_t square2OutputRight = channelControl & Const::FlagChannel2ToOutput2 && debugSquare2Enabled;
            sampleData.square2Left[sampleCounter] = square2OutputLeft ? squareChannel2.currentSample / volumeLeft : 0;
            sampleData.square2Right[sampleCounter] = square2OutputRight ? squareChannel2.currentSample / volumeRight : 0;

            uint8_t waveOutputLeft = channelControl & Const::FlagChannel3ToOutput1 && debugWaveEnabled;
            uint8_t waveOutputRight = channelControl & Const::FlagChannel3ToOutput2 && debugWaveEnabled;
            sampleData.waveLeft[sampleCounter] = waveOutputLeft ? waveChannel.currentSample / volumeLeft : 0;
            sampleData.waveRight[sampleCounter] = waveOutputRight ? waveChannel.currentSample / volumeRight : 0;

            uint8_t noiseOutputLeft = channelControl & Const::FlagChannel4ToOutput1 && debugWaveEnabled;
            uint8_t noiseOutputRight = channelControl & Const::FlagChannel4ToOutput2 && debugWaveEnabled;
            sampleData.noiseLeft[sampleCounter] = noiseOutputLeft ? noiseChannel.currentSample / volumeLeft : 0;
            sampleData.noiseRight[sampleCounter] = noiseOutputRight ? noiseChannel.currentSample / volumeRight : 0;
            
            sampleCounter++;
            if(sampleCounter == Const::AudioBufferFrames)
            {
                dac.feedSamples(sampleData);
                sampleCounter = 0;
            }
            cycleCount -= Const::CyclesAudioSample;
        }
    }
}