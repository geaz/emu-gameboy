#include "wave_channel.h"
#include <iostream>
namespace GGB::Hardware::Audio
{
    WaveChannel::WaveChannel(Mmu& mmu) : mmu(mmu) { }

    void WaveChannel::start()
    {        
        if(!isEnabled) 
        {
            isEnabled = true;
            restart();
        }
    }

    void WaveChannel::stop()
    {
        isEnabled = false;
        isRunning = false;
    }

    void WaveChannel::restart()
    {        
        isRunning = true;
        
        if(length == 0)
            length = Const::AudioWaveLength -  mmu.read(Const::AddrRegChannel3Length);
        lengthStop = mmu.readIORegisterBit(Const::AddrRegChannel3Data, Const::FlagChannelLengthStop);

        // Nothing magical just the way the hardware calculates the channel frequency
        // see: https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware
        cycleSampleUpdate = (2048 - getFrequency()) * 2;
        cycleCount = 0;
        sampleIndex = 0;

        uint8_t levelReg = mmu.read(Const::AddrRegChannel3Level);
        outputLevel = (Enum::AudioLevel)
            (((levelReg & Const::FlagChannel3OutputHigh) >> 5)
            |((levelReg & Const::FlagChannel3OutputLow) >> 5));
    }

    void WaveChannel::cycle(uint8_t cycles)
    {   
        cycleCount += cycles;
        if(cycleCount >= cycleSampleUpdate)
        {
            sampleIndex++;
            if(sampleIndex > 31) sampleIndex = 0;
            
            updateSamples();
            cycleCount -= cycleSampleUpdate;
        } 
    }

    void WaveChannel::lengthTick()
    {
        if(length == 0 && lengthStop) isRunning = false;
        else if(length > 0) length--;       
    }

    uint16_t WaveChannel::getFrequency()
    {
        uint8_t frequencyData = mmu.read(Const::AddrRegChannel3Data);
        uint16_t frequency = mmu.read(Const::AddrRegChannel3FreqLow8Bit);
        frequency |= 
            ((frequencyData & Const::FlagChannelFreqHigh)
            |(frequencyData & Const::FlagChannelFreqMid)
            |(frequencyData & Const::FlagChannelFreqLow)) << 8;
        return frequency;
    }

    void WaveChannel::updateSamples()
    {
        // Each byte in the Wave RAM holds two 2 4-bit samples
        uint8_t sampleByte = mmu.read(Const::AddrWaveRamStart + (sampleIndex / 2));
        uint8_t newSample = sampleIndex % 2 == 0
            ? (sampleByte & 0xF0) >> 4
            : sampleByte & 0x0F;

        currentSample = newSample;        
        if(outputLevel != Enum::AudioLevel::MUTE)
            currentSample = currentSample >> (static_cast<uint8_t>(outputLevel) - 1);
        if(!isEnabled || !isRunning)
            currentSample = 0;
    }
}