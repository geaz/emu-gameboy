#include "apu.h"
#include <iostream>

namespace GGB::Hardware
{
    Apu* ApuPointer = NULL;

    Apu::Apu(Mmu& mmu) : mmu(mmu), waveChannel(mmu)
    {
        // Store Pointer for RtAudio callbacks
        ApuPointer = this;

        parameters.deviceId = dacWave.getDefaultOutputDevice();
        parameters.nChannels = Constants::AUDIO_OUTPUT_QUANTITY;
        parameters.firstChannel = 0;

        unsigned int bufferFrames = Constants::AUDIO_BUFFER_FRAMES;
        auto waveCallback = [](void *outputBuffer, void * inputBuffer, unsigned int nBufferFrames, 
                double streamTime, RtAudioStreamStatus status, void *data)
        {
            ApuPointer->populateStream(Enums::APU_CHANNEL::WAVE_CHANNEL, (float*)outputBuffer, streamTime);
            return 0;
        };
        dacWave.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                Constants::AUDIO_SAMPLE_RATE, &bufferFrames, waveCallback);
        dacWave.startStream();
    }

    void Apu::cycle(uint8_t cycles)
    {
        cycleCount += cycles;
        cycleCountLength += cycles;
        waveChannel.cycle(cycles);

        while(cycleCountLength >= Constants::AUDIO_LENGTH_CLOCK_CYCLES)
        {
            waveChannel.lengthTick();
            cycleCountLength -= Constants::AUDIO_LENGTH_CLOCK_CYCLES;
        }

        while(cycleCount >= 4194304 / Constants::AUDIO_SAMPLE_RATE)
        {
            waveChannel.updateSample();
            if(sampleCounter == 1024)
            {
                userBuffer2 = !userBuffer2;
                sampleCounter = 0;
            }

            if(userBuffer2) sampleBuffer2[sampleCounter++] = waveChannel.currentSample;
            else sampleBuffer[sampleCounter++] = waveChannel.currentSample;

            cycleCount -= 4194304 / Constants::AUDIO_SAMPLE_RATE;
        }
    }
    static uint8_t oldSample = 8;
    void Apu::populateStream(Enums::APU_CHANNEL audioChannel, float* buffer, double streamTime)
    { 
        bool useBuffer2 = userBuffer2;
        bool output1On = mmu.readIORegisterBit(Enums::APU_REGISTER::OUTPUT_CONTROL, Enums::OUTPUT_CONTROL_FLAG::OUTPUT_1_ON);
        bool output2On = mmu.readIORegisterBit(Enums::APU_REGISTER::OUTPUT_CONTROL, Enums::OUTPUT_CONTROL_FLAG::OUTPUT_2_ON);
        
        bool channel3Ouput1 = mmu.readIORegisterBit(Enums::APU_REGISTER::CHANNEL_OUTPUT, Enums::CHANNEL_OUTPUT_FLAG::CHANNEL_3_TO_OUTPUT_1);
        bool channel3Ouput2 = mmu.readIORegisterBit(Enums::APU_REGISTER::CHANNEL_OUTPUT, Enums::CHANNEL_OUTPUT_FLAG::CHANNEL_3_TO_OUTPUT_2);
        for(int i = 0; i < Constants::AUDIO_BUFFER_FRAMES; i++)
        {
            for(int j = 0; j < Constants::AUDIO_OUTPUT_QUANTITY; j++)
            {
                if(useBuffer2) buffer[i * (j + 1)] = (float)(sampleBuffer[i] - 8) / 8; 
                else buffer[i * (j + 1)] = (float)(sampleBuffer2[i] - 8) / 8; 
                
                if(j == 0 && !output1On) buffer[i * (j + 1)] = -1;
                if(j == 1 && !output2On) buffer[i * (j + 1)] = -1;
                if(j == 0 && !channel3Ouput1) buffer[i * (j + 1)] = -1;
                if(j == 1 && !channel3Ouput2) buffer[i * (j + 1)] = -1;
            }            
        }     
    }
}