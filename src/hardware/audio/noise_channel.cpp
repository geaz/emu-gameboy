#include "noise_channel.h"

namespace GGB::Hardware::Audio
{
    NoiseChannel::NoiseChannel(Mmu& mmu) : mmu(mmu) { }

    void NoiseChannel::restart()
    {        
        isRunning = true;
        mmu.writeIORegisterBit(Const::AddrRegSoundControl, Const::FlagSound4On, true);
        
        if(length == 0)
            length = Const::AudioDefaultLength - (mmu.read(Const::AddrRegChannel4Length) & Const::FlagChannelLengthData);
        lengthStop = mmu.readIORegisterBit(Const::AddrRegChannel4Data, Const::FlagChannelLengthStop);

        uint8_t envelopeData = mmu.read(Const::AddrRegChannel4Envelope);
        initialEnvelopeVolume = (envelopeData & Const::FlagChannelEnvelopeVolumeInt) >> 4;
        isEnvelopeIncreasing = envelopeData & Const::FlagChannelEnvelopeIncrease;
        envelopeTicks = envelopeData & Const::FlagChannelEnvelopeSweep;
        envelopeVolumeCorrection = 0;

        uint8_t noiseData = mmu.read(Const::AddrRegChannel4Counter);
        divisor = Const::AudioDivisorArray[noiseData & Const::FlagChannel4DividingRatio]; 
        isWidth7Bit = noiseData & Const::FlagChannel4CounterWidthMode;

        cycleSampleUpdate = divisor << ((noiseData & Const::FlagChannel4ShiftFreq) >> 4);
        cycleCount = 0;
        
        updateSample();
    }

    void NoiseChannel::cycle(const uint8_t cycles)
    {   
        cycleCount += cycles;
        if(cycleCount >= cycleSampleUpdate)
        {
            updateSample();
            cycleCount -= cycleSampleUpdate;
        } 
    }

    void NoiseChannel::lengthTick()
    {
        if(length > 0) length--;
        if(length == 0 && lengthStop)
        {
            isRunning = false;       
            mmu.writeIORegisterBit(Const::AddrRegSoundControl, Const::FlagSound4On, false);
        }    
    }

    void NoiseChannel::envelopeTick()
    {
        if(envelopeTicks != 0) envelopeTicks--;
        if(envelopeTicks != 0) 
        {               
            envelopeVolumeCorrection += isEnvelopeIncreasing ? 1 : -1;
        } 
    }

    void NoiseChannel::updateSample()
    {
        if(!isRunning) currentSample = 0;
    }
}