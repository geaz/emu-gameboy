#include "dac.hpp"

namespace GGB::Hardware::Audio
{    
    Dac* DacPointer = NULL;

    Dac::Dac() :
        sampleBufferLeft(Const::AudioBufferFrames * 4),
        sampleBufferRight(Const::AudioBufferFrames * 4)
    {
        // Store Pointer for RtAudio callbacks
        DacPointer = this;
                
        RtAudio::StreamParameters parameters;
        parameters.deviceId = dac.getDefaultOutputDevice();
        parameters.nChannels = Const::AudioOutputQuantity;
        parameters.firstChannel = 0;

        auto waveCallback = [](void *outputBuffer, void * inputBuffer, unsigned int nBufferFrames, 
                double streamTime, RtAudioStreamStatus status, void *data)
        {
            DacPointer->populateStream((float*)outputBuffer);
            return 0;
        };
        dac.openStream(&parameters, NULL, RTAUDIO_FLOAT32, Const::AudioSampleRate, &bufferFrames, waveCallback);
    }    
    
    void Dac::feedSamples(const SampleData sampleData)
    {
        for(int i = 0; i < Const::AudioBufferFrames; i++)
        {
            float allLeftChannels = 
                (float)(sampleData.square1Left[i]
                + sampleData.square2Left[i]
                + sampleData.waveLeft[i]
                + sampleData.noiseLeft[i]) / 4;
            float allRightChannels = 
                (float)(sampleData.square1Right[i]
                + sampleData.square2Right[i]
                + sampleData.waveRight[i]
                + sampleData.noiseRight[i]) / 4;

            sampleBufferLeft.put((allLeftChannels - 8) / 8);
            sampleBufferRight.put((allRightChannels - 8) / 8);
        }
        // Wait with the start of the dac until we filled the buffer a bit
        if(!dac.isStreamRunning() && sampleBufferLeft.size() >= Const::AudioBufferFrames * 2) 
            dac.startStream();
    }

    void Dac::populateStream(float* buffer)
    { 
        for(int i = 0; i < Const::AudioBufferFrames * Const::AudioOutputQuantity; i += Const::AudioOutputQuantity)
        {
            buffer[i] = sampleBufferLeft.get();
            buffer[i + 1] = sampleBufferRight.get();
        }          
    }
}