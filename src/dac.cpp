#include "dac.h"

namespace GGB
{    
    Dac* DacPointer = NULL;

    Dac::Dac(Hardware::Apu& apu) : apu(apu)
    {
        // Store Pointer for RtAudio callbacks
        DacPointer = this;
                
        RtAudio::StreamParameters parameters;
        parameters.deviceId = dac.getDefaultOutputDevice();
        parameters.nChannels = Const::AudioOutputQuantity;
        parameters.firstChannel = 0;

        RtAudio::StreamOptions options;
        options.numberOfBuffers = 2;

        unsigned int bufferFrames = Const::AudioBufferFrames;
        auto waveCallback = [](void *outputBuffer, void * inputBuffer, unsigned int nBufferFrames, 
                double streamTime, RtAudioStreamStatus status, void *data)
        {
            DacPointer->populateStream(Enum::AudioChannel::Wave, (float*)outputBuffer);
            return 0;
        };
        dac.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                Const::AudioSampleRate, &bufferFrames, waveCallback, NULL, &options);
        dac.startStream();
    }    
    
    void Dac::populateStream(Enum::AudioChannel audioChannel, float* buffer)
    { 
        for(int i = 0; i < Const::AudioBufferFrames * Const::AudioOutputQuantity; i += Const::AudioOutputQuantity)
        {
            buffer[i] = getSample(i / Const::AudioOutputQuantity, true);
            buffer[i + 1] = getSample(i / Const::AudioOutputQuantity, false);
        }          
    }

    float Dac::getSample(const uint16_t sampleIndex, const bool left) const
    {
        auto sampleTransform = [](uint8_t sample) -> float {
            return (float)(sample - 8) / 8;
        };

        float sample = 0;
        if(left)
        {
            sample = (sampleTransform(apu.square1DataLeft[sampleIndex])
                + sampleTransform(apu.square2DataLeft[sampleIndex])
                + sampleTransform(apu.waveDataLeft[sampleIndex])
                + sampleTransform(apu.noiseDataLeft[sampleIndex])) / 4;
        }
        else
        {
            sample = (sampleTransform(apu.square1DataRight[sampleIndex])
                + sampleTransform(apu.square2DataRight[sampleIndex])
                + sampleTransform(apu.waveDataRight[sampleIndex])
                + sampleTransform(apu.noiseDataLeft[sampleIndex])) / 4;
        }
        return sample;
    }
}