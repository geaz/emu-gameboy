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
        noiseChannel(mmu) 
    { 
        mmu.registerOnAddrWrite([this](MemoryWriteEvent writeEvent) { onMmuWrite(writeEvent); });
    }

    void Apu::cycle(const uint8_t cycles)
    {
        checkWaveStart();

        cycleLength(cycles);
        cycleEnvelope(cycles);
        cycleSweep(cycles);
        cycleChannels(cycles);
        cycleSamples(cycles);
    }

    void Apu::onMmuWrite(MemoryWriteEvent writeEvent)
    {
        switch(writeEvent.address)
        {
            case Const::AddrRegOutputControl:                
                volumeLeft = 8 - (writeEvent.value & Const::FlagOutputVolume);
                volumeRight = 8 - ((writeEvent.value >> 4) & Const::FlagOutputVolume);
                break;
            case Const::AddrRegChannelControl:
                square1OutputLeft = writeEvent.value & Const::FlagChannel1ToOutput1;
                square1OutputRight = writeEvent.value & Const::FlagChannel1ToOutput2;                
                square2OutputLeft = writeEvent.value & Const::FlagChannel2ToOutput1;
                square2OutputRight = writeEvent.value & Const::FlagChannel2ToOutput2;
                waveOutputLeft = writeEvent.value & Const::FlagChannel3ToOutput1;
                waveOutputRight = writeEvent.value & Const::FlagChannel3ToOutput2;                
                noiseOutputLeft = writeEvent.value & Const::FlagChannel4ToOutput1;
                noiseOutputRight = writeEvent.value & Const::FlagChannel4ToOutput2;
                break;
            case Const::AddrRegChannel1Data:
        	    if(writeEvent.value & Const::FlagChannelRestart) squareChannel1.restart();
                break;
            case Const::AddrRegChannel2Data:
        	    if(writeEvent.value & Const::FlagChannelRestart) squareChannel2.restart();
                break;
            case Const::AddrRegChannel3Data:
        	    if(writeEvent.value & Const::FlagChannelRestart) waveChannel.restart();
                break;
            case Const::AddrRegChannel4Data:
        	    if(writeEvent.value & Const::FlagChannelRestart) noiseChannel.restart();
                break;
        }
    }

    void Apu::checkWaveStart()
    {
        bool channel3On = mmu.readIORegisterBit(Const::AddrRegChannel3On, Const::FlagChannel3On);
        if(channel3On) waveChannel.start();
        else waveChannel.stop();
    }

    void Apu::cycleLength(const uint8_t cycles)
    {        
        cycleCountLength += cycles;
        if(cycleCountLength >= Const::Cycles256Hz)
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
        if(cycleCountEnvelope >= Const::Cycles64Hz)
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
        if(cycleCountSweep >= Const::Cycles128Hz)
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
            sampleData.square1Left[sampleCounter] = square1OutputLeft ? squareChannel1.currentSample / volumeLeft : 0;
            sampleData.square1Right[sampleCounter] = square1OutputRight ? squareChannel1.currentSample / volumeRight : 0;

            sampleData.square2Left[sampleCounter] = square2OutputLeft ? squareChannel2.currentSample / volumeLeft : 0;
            sampleData.square2Right[sampleCounter] = square2OutputRight ? squareChannel2.currentSample / volumeRight : 0;

            sampleData.waveLeft[sampleCounter] = waveOutputLeft ? waveChannel.currentSample / volumeLeft : 0;
            sampleData.waveRight[sampleCounter] = waveOutputRight ? waveChannel.currentSample / volumeRight : 0;

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