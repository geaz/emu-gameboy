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
            // Convert the 4-bit samples (0-15) to floats ranging from -1.0 to 1.0
            buffer[i] = (float)(apu.waveDataLeft[i / Const::AudioOutputQuantity] - 8) / 8;
            buffer[i + 1] = (float)(apu.waveDataRight[i / Const::AudioOutputQuantity] - 8) / 8; 
        }          
    }
}