#pragma once
#ifndef DAC_H
#define DAC_H

#include "rtaudio.h"
#include "ring_buffer.hpp"
#include "../../ggb_constants.hpp"

namespace GGB::Hardware::Audio
{
    struct SampleData
    {
        uint8_t square1Right[Const::AudioBufferFrames];
        uint8_t square1Left[Const::AudioBufferFrames];
        uint8_t square2Right[Const::AudioBufferFrames];
        uint8_t square2Left[Const::AudioBufferFrames];
        uint8_t waveRight[Const::AudioBufferFrames];
        uint8_t waveLeft[Const::AudioBufferFrames];
        uint8_t noiseRight[Const::AudioBufferFrames];
        uint8_t noiseLeft[Const::AudioBufferFrames];
    };

    class Dac
    {
        public:
            Dac();

            void feedSamples(const SampleData sampleData);

        private:            
            void populateStream(float* buffer);

            RtAudio dac;
            RingBuffer<float> sampleBufferLeft;
            RingBuffer<float> sampleBufferRight;
            unsigned int bufferFrames = Const::AudioBufferFrames;
    };   

    // Dac Pointer for RtAudio callbacks
    extern Dac* DacPointer;
}

#endif // DAC_H