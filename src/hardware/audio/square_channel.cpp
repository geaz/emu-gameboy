#include "square_channel.h"

namespace GGB::Hardware::Audio
{
    SquareChannel::SquareChannel(Mmu& mmu, SquareChannelParameters channelParams) 
        : mmu(mmu), channelParams(channelParams) { }

    void SquareChannel::restart()
    {        
        isRunning = true;
        mmu.writeIORegisterBit(Const::AddrRegSoundControl, channelParams.ChannelSoundControlFlag, true);
        
        if(length == 0)
            length = Const::AudioDefaultLength - (mmu.read(channelParams.ChannelLengthDutyAddr) & Const::FlagChannelLengthData);
        lengthStop = mmu.readIORegisterBit(channelParams.ChannelDataAddr, Const::FlagChannelLengthStop);
        selectedDuty = (mmu.read(channelParams.ChannelLengthDutyAddr) & Const::FlagChannelDuty) >> 6;

        uint8_t envelopeData = mmu.read(channelParams.ChannelEvenlopeAddr);
        initialEnvelopeVolume = (envelopeData & Const::FlagChannelEnvelopeVolumeInt) >> 4;
        isEnvelopeIncreasing = envelopeData & Const::FlagChannelEnvelopeIncrease;
        envelopeTicks = envelopeData & Const::FlagChannelEnvelopeSweep;
        currentVolume = initialEnvelopeVolume;

        // Nothing magical just the way the hardware calculates the channel frequency
        // see: https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware
        cycleSampleUpdate = (2048 - getFrequency()) * 4;
        cycleCount = 0;
        sampleIndex = 0;

        if(channelParams.hasSweep)
        {
            elaspsedSweepTime = 0;

            uint8_t sweepData = mmu.read(channelParams.ChannelSweepAddr);
            sweepTime = (sweepData & Const::FlagChannelSweepTime) >> 4;
            isSweepIncreasing = sweepData & Const::FlagChannelSweepIncrease;
            sweepShift = sweepData & Const::FlagChannelSweepShift;
        }
    }

    void SquareChannel::cycle(const uint8_t cycles)
    {   
        cycleCount += cycles;
        if(cycleCount >= cycleSampleUpdate)
        {
            sampleIndex++;
            if(sampleIndex > 7) sampleIndex = 0;
            
            updateSample();
            cycleCount -= cycleSampleUpdate;
        } 
    }

    void SquareChannel::lengthTick()
    {
        if(length > 0) length--;
        if(length == 0 && lengthStop)
        {
            isRunning = false;       
            mmu.writeIORegisterBit(Const::AddrRegSoundControl, channelParams.ChannelSoundControlFlag, false);
        }
    }

    void SquareChannel::envelopeTick()
    {
        if(envelopeTicks == 0) return;
        if(elapsedEnvelopeTicks != envelopeTicks) elapsedEnvelopeTicks ++;
        if(elapsedEnvelopeTicks == envelopeTicks)
        {
            if(!isEnvelopeIncreasing && currentVolume != 0)
                currentVolume--;
            else if(isEnvelopeIncreasing && currentVolume != 15)
                currentVolume++;
            elapsedEnvelopeTicks = 0;
        }
    }

    void SquareChannel::sweepTick()
    {
        if(sweepTime != 0)
        {
            if(elaspsedSweepTime != sweepTime) elaspsedSweepTime++;
            if(elaspsedSweepTime != sweepTime)
            {
                int8_t sweepCorrection = isSweepIncreasing ? 1 : -1;
                cycleSampleUpdate += (cycleSampleUpdate >> sweepShift) * sweepCorrection;
                cycleCount = 0;
            }
            if(elaspsedSweepTime == sweepTime || cycleSampleUpdate > 2047) isRunning = false;
        }        
    }

    uint16_t SquareChannel::getFrequency() const
    {
        uint8_t frequencyData = mmu.read(channelParams.ChannelDataAddr);
        uint16_t frequency = mmu.read(channelParams.ChannelFreqLowAddr);
        frequency |= (frequencyData & Const::FlagChannelFreq) << 8;
        return frequency;
    }

    void SquareChannel::updateSample()
    {
        uint8_t dutyValue = Const::AudioWavePatternArray[selectedDuty][sampleIndex];
        currentSample = dutyValue * currentVolume;

        if(!isRunning) currentSample = 0;
    }
}