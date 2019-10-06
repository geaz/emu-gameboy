#pragma once
#ifndef APU_H
#define APU_H

#include "RtAudio.h"
#include "apu_enums.h"
#include "apu_consts.h"
#include "../clock.h"
#include "../memory/mmu.h"

#include "wave_channel.h"

namespace GGB::Hardware
{
    class Apu
    {
        public:
            Apu(Mmu& mmu);
        
            void cycle(uint8_t cycles);

            Audio::WaveChannel waveChannel;

        private:
            void populateStream(Enums::APU_CHANNEL audioChannel, float* buffer, double streamTime);

            Mmu& mmu;
            uint32_t cycleCount = 0;
            uint32_t cycleCountLength = 0;

            RtAudio dacWave;
            RtAudio::StreamParameters parameters;
            uint8_t sampleBuffer[Constants::AUDIO_BUFFER_FRAMES];
            uint8_t sampleBuffer2[Constants::AUDIO_BUFFER_FRAMES];
            uint16_t sampleCounter = 0;
            bool userBuffer2 = false;
    };

    // Apu Pointer for RtAudio callbacks
    extern Apu* ApuPointer;
}

#endif // APU_H