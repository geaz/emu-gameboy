#pragma once
#ifndef APUCONSTS_H
#define APUCONSTS_H

#include <cstdint>

namespace GGB::Constants
{
    const uint8_t AUDIO_OUTPUT_QUANTITY = 2;
    const uint32_t AUDIO_SAMPLE_RATE = 44100;
    const uint16_t AUDIO_BUFFER_FRAMES = 1024;
    const uint16_t AUDIO_LENGTH_CLOCK_CYCLES = 4194304 / 256;

    const uint16_t WAVE_RAM_START = 0xFF30;
    const uint16_t WAVE_RAM_END = 0xFF3F;
}

#endif // APUCONSTS_H