#include "wave_channel.h"

namespace GGB::Hardware::Audio
{
    WaveChannel::WaveChannel(Mmu& mmu) : mmu(mmu) { }

    void WaveChannel::cycle(uint8_t cycles)
    {
        updateChannelInfo();

        currentSample = 0;
        if(isOn) 
        {
            cycleCount += cycles;
            if(cycleCount >= cyclesPerTick)
            {
                sampleIndex++;
                if(sampleIndex > 31) 
                    sampleIndex = 0;
                cycleCount -= cyclesPerTick;
            }    
            if(restart)
            {
                mmu.writeIORegisterBit(Enums::APU_REGISTER::CHANNEL_3_FREQ_DATA, Enums::CHANNEL_3_FREQ_DATA_FLAG::FREQ_RESTART, false);
                sampleIndex = 0;
                //lengthCounter = length;
            }
        }
    }

    void WaveChannel::lengthTick()
    {
        if(isOn) 
        {
            lengthCounter -= lengthCounter != 0 ? 1 : 0; 
        }
    }

    void WaveChannel::updateSample()
    {
        if(!isOn) currentSample = 0;
        else if(lengthStop && lengthCounter == 0) currentSample = 0;
        else
        {
            // Each byte in the Wave RAM holds two 2 4-bit samples
            // By checking the ramPosition
            uint8_t currentByte = mmu.read(Constants::WAVE_RAM_START + (sampleIndex / 2));
            currentSample = sampleIndex % 2 == 0
                ? (currentByte & 0xF0) >> 4
                : currentByte & 0x0F;

            if(outputLevel == Enums::OUTPUT_LEVEL::MUTE)
                currentSample = 0;
            else
                currentSample = currentSample >> (outputLevel - 1);
        }
    }

    void WaveChannel::updateChannelInfo()
    {
        isOn = mmu.readIORegisterBit(Enums::APU_REGISTER::CHANNEL_3_ON, Enums::CHANNEL_3_ON_FLAG::ON_FLAG);

        uint8_t levelReg = mmu.readIORegister(Enums::APU_REGISTER::CHANNEL_3_LEVEL);
        outputLevel = (Enums::OUTPUT_LEVEL)
            (((levelReg & Enums::CHANNEL_3_LEVEL_FLAG::OUTPUT_LEVEL_HIGH) >> 5)
            |((levelReg & Enums::CHANNEL_3_LEVEL_FLAG::OUTPUT_LEVEL_LOW) >> 5));

        uint8_t freqDataReg = mmu.readIORegister(Enums::APU_REGISTER::CHANNEL_3_FREQ_DATA);

        uint16_t oldFreq = frequency;
        frequency = mmu.readIORegister(Enums::APU_REGISTER::CHANNEL_3_FREQ_LOW_8BIT);
        frequency |= 
            ((freqDataReg & Enums::CHANNEL_3_FREQ_DATA_FLAG::FREQ_HIGH)
            |(freqDataReg & Enums::CHANNEL_3_FREQ_DATA_FLAG::FREQ_MID)
            |(freqDataReg & Enums::CHANNEL_3_FREQ_DATA_FLAG::FREQ_LOW)) << 8;
        if(oldFreq != frequency) cycleCount = 0;

        restart = freqDataReg & Enums::CHANNEL_3_FREQ_DATA_FLAG::FREQ_RESTART;
        lengthStop = freqDataReg & Enums::CHANNEL_3_FREQ_DATA_FLAG::FREQ_LENGTH_STOP;
        length = mmu.readIORegister(Enums::APU_REGISTER::CHANNEL_3_LENGTH);
        if(length != 0) 
        {
            lengthCounter = length;
            mmu.write(Enums::APU_REGISTER::CHANNEL_3_LENGTH, 0);
        }
    
        // Frequency Forumlar taken from https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware
        // Cycles Per Tick = Timer Period
        cyclesPerTick = (2048 - frequency) * 2;
    }
}