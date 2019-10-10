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

#include "square_channel.h"
#include "wave_channel.h"
#include "noise_channel.h"

namespace GGB::Hardware
{
    const Audio::SquareChannelParameters square1Parameters = {
        true,
        Const::AddrRegChannel1Data,
        Const::AddrRegChannel1FreqLow8Bit,
        Const::AddrRegChannel1LengthDuty,
        Const::AddrRegChannel1Envelope,
        Const::AddrRegChannel1Sweep
    };

    const Audio::SquareChannelParameters square2Parameters = {
        false,
        Const::AddrRegChannel2Data,
        Const::AddrRegChannel2FreqLow8Bit,
        Const::AddrRegChannel2LengthDuty,
        Const::AddrRegChannel2Envelope,
        0
    };
    
    class Apu
    {
        public:
            Apu(Mmu& mmu);
        
            void cycle(const uint8_t cycles);

            Audio::SquareChannel squareChannel1;
            Audio::SquareChannel squareChannel2;
            Audio::WaveChannel waveChannel;
            Audio::NoiseChannel noiseChannel;

            bool debugSquare1Enabled = true;
            bool debugSquare2Enabled = true;
            bool debugWaveEnabled = true;
            bool debugNoiseEnabled = true;

            uint8_t square1DataRight[Const::AudioBufferFrames];
            uint8_t square1DataLeft[Const::AudioBufferFrames];
            uint8_t square2DataRight[Const::AudioBufferFrames];
            uint8_t square2DataLeft[Const::AudioBufferFrames];
            uint8_t waveDataRight[Const::AudioBufferFrames];
            uint8_t waveDataLeft[Const::AudioBufferFrames];
            uint8_t noiseDataRight[Const::AudioBufferFrames];
            uint8_t noiseDataLeft[Const::AudioBufferFrames];

        private:          
            void checkWaveStart();  
            void checkRestartTrigger();
            void cycleLength(const uint8_t cycles);
            void cycleEnvelope(const uint8_t cycles);
            void cycleSweep(const uint8_t cycles);
            void cycleChannels(const uint8_t cycles);
            void cycleSamples(const uint8_t cycles);

            Mmu& mmu;
            std::ofstream outputFile;
            uint32_t cycleCount = 0;
            uint32_t cycleCountLength = 0;
            uint32_t cycleCountEnvelope = 0;
            uint32_t cycleCountSweep = 0;
            uint16_t sampleCounter = 0;

            MemoryWriteEvent lastRelevantMemoryEvent;

            uint8_t square1BufferRight[Const::AudioBufferFrames];
            uint8_t square1BufferLeft[Const::AudioBufferFrames];
            uint8_t square2BufferRight[Const::AudioBufferFrames];
            uint8_t square2BufferLeft[Const::AudioBufferFrames];
            uint8_t waveBufferRight[Const::AudioBufferFrames];
            uint8_t waveBufferLeft[Const::AudioBufferFrames];
            uint8_t noiseBufferRight[Const::AudioBufferFrames];
            uint8_t noiseBufferLeft[Const::AudioBufferFrames];
    };
}

#endif // APU_H