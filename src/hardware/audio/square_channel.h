#pragma once
#ifndef SQUARECHANNEL_H
#define SQUARECHANNEL_H

#include "../memory/mmu.h"

namespace GGB::Hardware::Audio
{
    struct SquareChannelParameters
    {
        bool hasSweep;
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
                void updateSample();     

                Mmu& mmu;
                SquareChannelParameters channelParams;

                bool isRunning = false;
                bool lengthStop = false;
                uint8_t length = 0;
            
                uint8_t sweepShift = 0;
                uint8_t sweepTime = 0;
                uint8_t elaspsedSweepTime = 0;
                bool isSweepIncreasing = false;

                uint8_t envelopeTicks = 0;
                uint8_t currentVolume = 0;
                uint8_t initialEnvelopeVolume = 0;
                bool isEnvelopeIncreasing = false;

                uint8_t selectedDuty = 0;    
                uint16_t sampleIndex = 0;
                uint16_t cycleSampleUpdate = 0;
                uint16_t cycleCount = 0;
    };
}

#endif // SQUARECHANNEL_H