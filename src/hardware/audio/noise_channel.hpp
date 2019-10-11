#pragma once
#ifndef NOISECHANNEL_H
#define NOISECHANNEL_H

#include "../memory/mmu.hpp"

namespace GGB::Hardware::Audio
{
    class NoiseChannel
    {
        public:
                NoiseChannel(Mmu& mmu);

                void restart();
                void cycle(const uint8_t cycles);    
                void lengthTick();
                void envelopeTick();

                uint8_t currentSample = 0;

            private:
                void updateSample();

                Mmu& mmu;

                bool isRunning = false;
                bool lengthStop = false;
                uint8_t length = 0;

                uint8_t envelopeTicks = 0;
                uint8_t initialEnvelopeVolume = 0;
                int8_t envelopeVolumeCorrection = 0;
                bool isEnvelopeIncreasing = false;
  
                bool isWidth7Bit = false;
                uint8_t divisor = 0;
                uint16_t cycleSampleUpdate = 0;
                uint16_t cycleCount = 0;
    };
}

#endif // NOISECHANNEL_H