#pragma once
#ifndef DAC_H
#define DAC_H

#include "rtaudio.h"
#include "hardware/audio/apu.h"

namespace GGB
{
    class Dac
    {
        public:
            Dac(Hardware::Apu& apu);

        private:            
            void populateStream(Enum::AudioChannel audioChannel, float* buffer);

            Hardware::Apu& apu;
            RtAudio dac;
    };   

    // Dac Pointer for RtAudio callbacks
    extern Dac* DacPointer;
}

#endif // DAC_H