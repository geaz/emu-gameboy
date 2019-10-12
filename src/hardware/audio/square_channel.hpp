#pragma once
#ifndef SQUARECHANNEL_H
#define SQUARECHANNEL_H

#include "../memory/mmu.hpp"
#include "components/length_component.hpp"
#include "components/envelope_component.hpp"

namespace GGB::Hardware::Audio
{
    struct SquareChannelParameters
    {
        bool hasSweep;
        uint8_t ChannelSoundControlFlag;
        uint16_t ChannelDataAddr;
        uint16_t ChannelFreqLowAddr;
        uint16_t ChannelLengthDutyAddr;
        uint16_t ChannelEvenlopeAddr;
        uint16_t ChannelSweepAddr;
    };

    class SquareChannel
    {
        public:
                SquareChannel(Mmu& mmu, SquareChannelParameters channelParams);

                void restart();
                void cycle(const uint8_t cycles);    
                void lengthTick();
                void envelopeTick();
                void sweepTick();  

                uint8_t currentSample = 0;

            private:
                uint16_t getFrequency() const;
                void setFrequency(uint16_t frequency);
                void updateSample();     

                Mmu& mmu;
                SquareChannelParameters channelParams;
                LengthComponent lengthComponent;
                EnvelopeComponent envelopeComponent;

                bool isRunning = false;
            
                uint8_t sweepShift = 0;
                uint8_t sweepTime = 0;
                uint8_t elaspsedSweepTime = 0;
                uint16_t currentFrequency = 0;
                bool isSweepDecreasing = false;

                uint8_t selectedDuty = 0;    
                uint16_t sampleIndex = 0;
                uint16_t cycleSampleUpdate = 0;
                uint16_t cycleCount = 0;
    };
}

#endif // SQUARECHANNEL_H