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
        lfsr = 0x7FFF;

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
        uint8_t bit0 = lfsr & 0x1;
        uint8_t bit1 = (lfsr & 0x2) >> 1;
        uint8_t xored = bit0 ^ bit1;

        lfsr = (xored << 14) | (lfsr >> 1);
        if(isWidth7Bit)
            lfsr = (xored << 6) | (lfsr & 0x7FBF);

        currentSample = (lfsr & 0x1) == 0 ? 1 : 0;
        if(!isRunning) currentSample = 0;
    }
}