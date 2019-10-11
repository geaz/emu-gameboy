#pragma once
#ifndef NOISECHANNEL_H
#define NOISECHANNEL_H

#include "../memory/mmu.hpp"
#include "components/length_component.hpp"
#include "components/envelope_component.hpp"

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
                LengthComponent lengthComponent;
                EnvelopeComponent envelopeComponent;

                bool isRunning = false;
  
                bool isWidth7Bit = false;
                uint8_t divisor = 0;
                uint16_t cycleSampleUpdate = 0;
                uint16_t cycleCount = 0;
    };
}

#endif // NOISECHANNEL_H