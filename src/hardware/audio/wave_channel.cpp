#include "wave_channel.hpp"
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
        mmu.writeIORegisterBit(Const::AddrRegSoundControl, Const::FlagSound3On, true);
        
        uint16_t length = Const::AudioWaveLength -  mmu.read(Const::AddrRegChannel3Length);
        bool lengthStop =  mmu.readIORegisterBit(Const::AddrRegChannel3Data, Const::FlagChannelLengthStop);
        lengthComponent.setLength(length, lengthStop);

        // Nothing magical just the way the hardware calculates the channel frequency
        // see: https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware
        cycleSampleUpdate = (2048 - getFrequency()) * 2;
        cycleCount = 0;
        sampleIndex = 0;

        uint8_t levelReg = mmu.read(Const::AddrRegChannel3Level);
        outputLevel = (Enum::AudioLevel) ((levelReg & Const::FlagChannel3Output) >> 5);

        updateSample();
    }

    void WaveChannel::lengthTick()
    {
        isRunning = lengthComponent.tick();
        if(!isRunning)
            mmu.writeIORegisterBit(Const::AddrRegSoundControl, Const::FlagSound3On, false);   
    }

    void WaveChannel::cycle(const uint8_t cycles)
    {   
        cycleCount += cycles;
        if(cycleCount >= cycleSampleUpdate)
        {
            sampleIndex++;
            if(sampleIndex > 31) sampleIndex = 0;
            
            updateSample();
            cycleCount -= cycleSampleUpdate;
        } 
    }

    uint16_t WaveChannel::getFrequency() const
    {
        uint8_t frequencyData = mmu.read(Const::AddrRegChannel3Data);
        uint16_t frequency = mmu.read( Const::AddrRegChannel3FreqLow8Bit);
        frequency |= (frequencyData & Const::FlagChannelFreq) << 8;
        return frequency;
    }

    void WaveChannel::updateSample()
    {
        // Each byte in the Wave RAM holds two 2 4-bit samples
        uint8_t sampleByte = mmu.read(Const::AddrWaveRamStart + (sampleIndex / 2));
        uint8_t newSample = sampleIndex % 2 == 0
            ? (sampleByte & 0xF0) >> 4
            : sampleByte & 0x0F;

        currentSample = newSample;        
        if(outputLevel != Enum::AudioLevel::MUTE)
            currentSample = currentSample >> (static_cast<uint8_t>(outputLevel) - 1);
        if(!isEnabled || !isRunning || outputLevel == Enum::AudioLevel::MUTE)
            currentSample = 0;
    }
}