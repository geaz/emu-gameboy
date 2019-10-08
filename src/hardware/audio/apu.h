#pragma once
#ifndef APU_H
#define APU_H

#include <ostream>
#include <iostream>
#include <fstream>

#include "../clock.h"
#include "../memory/mmu.h"
#include "../../ggb_enums.h"
#include "../../ggb_constants.h"

#include "wave_channel.h"

namespace GGB::Hardware
{
    class Apu
    {
        public:
            Apu(Mmu& mmu);
        
            void cycle(uint8_t cycles);

            Audio::WaveChannel waveChannel;

            bool debugWaveEnabled = true;

            uint8_t waveDataRight[Const::AudioBufferFrames];
            uint8_t waveDataLeft[Const::AudioBufferFrames];

        private:          
            void checkStart();  
            void checkRestartTrigger();

            Mmu& mmu;
            std::ofstream outputFile;
            uint32_t cycleCount = 0;
            uint32_t cycleCountLength = 0;
            uint16_t sampleCounter = 0;

            MemoryWriteEvent lastRelevantMemoryEvent;

            uint8_t waveBufferRight[Const::AudioBufferFrames];
            uint8_t waveBufferLeft[Const::AudioBufferFrames];
    };
}

#endif // APU_H