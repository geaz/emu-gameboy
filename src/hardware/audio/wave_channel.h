#pragma once
#ifndef WAVECHANNEL_H
#define WAVECHANNEL_H

#include <cstdint>
#include "../memory/mmu.h"
#include "apu_enums.h"
#include "apu_consts.h"

namespace GGB::Hardware::Audio
{
    class WaveChannel
    {
        public:
            WaveChannel(Mmu& mmu);

            void cycle(uint8_t cycles);
            void updateSample();
            void lengthTick();

            uint8_t currentSample = 8;

        private:
            void updateChannelInfo();

            Mmu& mmu;

            uint8_t length = 0, lengthCounter = 0;
            uint16_t frequency = 0;
            bool isOn = false, lengthStop = false, restart = false;
            Enums::OUTPUT_LEVEL outputLevel = Enums::OUTPUT_LEVEL::MUTE;

            uint16_t cycleCount = 0;
            uint32_t cyclesPerTick = 0;
            uint16_t sampleIndex = 0;
    };
}

#endif // WAVECHANNEL_H