#include "noise_channel.hpp"

namespace GGB::Hardware::Audio
{
    NoiseChannel::NoiseChannel(Mmu& mmu) : mmu(mmu) { }

    void NoiseChannel::restart()
    {        
        isRunning = true;
        mmu.writeIORegisterBit(Const::AddrRegSoundControl, Const::FlagSound4On, true);
        
        uint16_t length =  Const::AudioDefaultLength - (mmu.read(Const::AddrRegChannel4Length) & Const::FlagChannelLengthData);
        bool lengthStop =  mmu.readIORegisterBit(Const::AddrRegChannel4Data, Const::FlagChannelLengthStop);
        lengthComponent.setLength(length, lengthStop);

        uint8_t envelopeData = mmu.read(Const::AddrRegChannel4Envelope);
        uint8_t envelopeTicks = envelopeData & Const::FlagChannelEnvelopeSweep;
        uint8_t envelopeVolume = (envelopeData & Const::FlagChannelEnvelopeVolumeInt) >> 4;
        bool increasing = envelopeData & Const::FlagChannelEnvelopeIncrease;
        envelopeComponent.setEnvelope(envelopeTicks, envelopeVolume, increasing);   

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
        isRunning = lengthComponent.tick();
        if(!isRunning)
            mmu.writeIORegisterBit(Const::AddrRegSoundControl, Const::FlagSound4On, false);    
    }

    void NoiseChannel::envelopeTick()
    {
        envelopeComponent.tick();
    }

    void NoiseChannel::updateSample()
    {
        if(!isRunning) currentSample = 0;
    }
}