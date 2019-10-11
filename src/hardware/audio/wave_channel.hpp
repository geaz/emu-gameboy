#pragma once
#ifndef WAVECHANNEL_H
#define WAVECHANNEL_H

#include <cstdint>
#include "../memory/mmu.hpp"
#include "components/length_component.hpp"

namespace GGB::Hardware::Audio
{
    class WaveChannel
    {
        public:
            WaveChannel(Mmu& mmu);

            void start();
            void stop();
            void restart();
            void lengthTick();
            void cycle(const uint8_t cycles);       

            uint8_t currentSample = 0;

        private:
            uint16_t getFrequency() const;
            void updateSample();
    
            Mmu& mmu;
            LengthComponent lengthComponent;

            bool isEnabled = false;            
            bool isRunning = false;

            uint16_t sampleIndex = 0;
            uint16_t cycleSampleUpdate = 0;
            uint16_t cycleCount = 0;

            Enum::AudioLevel outputLevel = Enum::AudioLevel::MUTE;            
    };
}

#endif // WAVECHANNEL_H