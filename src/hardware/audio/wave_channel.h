#pragma once
#ifndef WAVECHANNEL_H
#define WAVECHANNEL_H

#include <cstdint>
#include "../memory/mmu.h"

namespace GGB::Hardware::Audio
{
    class WaveChannel
    {
        public:
            WaveChannel(Mmu& mmu);

            void start();
            void stop();
            void restart();
            void cycle(uint8_t cycles);            
            void lengthTick();

            uint8_t currentSample = 0;

        private:
            uint16_t getFrequency();
            void updateSamples();

            Mmu& mmu;
            
            bool isEnabled = false;
            bool isRunning = false;
            bool lengthStop = false;
            uint32_t length = 0;
            uint16_t sampleIndex = 0;
            Enum::AudioLevel outputLevel = Enum::AudioLevel::MUTE;            

            uint16_t cycleSampleUpdate = 0;
            uint16_t cycleCount = 0;
    };
}

#endif // WAVECHANNEL_H