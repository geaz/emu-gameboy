#pragma once
#ifndef APU_H
#define APU_H

#include "../clock.hpp"
#include "../memory/mmu.hpp"
#include "../../ggb_enums.hpp"
#include "../../ggb_constants.hpp"
#include "dac.hpp"
#include "square_channel.hpp"
#include "wave_channel.hpp"
#include "noise_channel.hpp"

namespace GGB::Hardware
{
    const Audio::SquareChannelParameters square1Parameters = {
        true,
        Const::FlagSound1On,
        Const::AddrRegChannel1Data,
        Const::AddrRegChannel1FreqLow8Bit,
        Const::AddrRegChannel1LengthDuty,
        Const::AddrRegChannel1Envelope,
        Const::AddrRegChannel1Sweep
    };

    const Audio::SquareChannelParameters square2Parameters = {
        false,
        Const::FlagSound2On,
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
            Audio::Dac dac;
        
            void cycle(const uint8_t cycles);

            Audio::SquareChannel squareChannel1;
            Audio::SquareChannel squareChannel2;
            Audio::WaveChannel waveChannel;
            Audio::NoiseChannel noiseChannel;

        private:          
            void checkWaveStart();  
            void checkRestartTrigger();
            void cycleLength(const uint8_t cycles);
            void cycleEnvelope(const uint8_t cycles);
            void cycleSweep(const uint8_t cycles);
            void cycleChannels(const uint8_t cycles);
            void cycleSamples(const uint8_t cycles);

            Mmu& mmu;
            uint32_t cycleCount = 0;
            uint32_t cycleCountLength = 0;
            uint32_t cycleCountEnvelope = 0;
            uint32_t cycleCountSweep = 0;
            uint16_t sampleCounter = 0;

            MemoryWriteEvent lastRelevantMemoryEvent;
            Audio::SampleData sampleData;
    };
}

#endif // APU_H