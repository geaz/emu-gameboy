#pragma once
#ifndef APUENUMS_H
#define APUENUMS_H

namespace GGB::Enums
{
    enum class APU_CHANNEL
    {
        WAVE_CHANNEL,
    };

    enum APU_REGISTER
    {    
        CHANNEL_3_ON = 0xFF1A,
        CHANNEL_3_LENGTH = 0xFF1B,
        CHANNEL_3_LEVEL = 0xFF1C,
        CHANNEL_3_FREQ_LOW_8BIT = 0xFF1D,
        CHANNEL_3_FREQ_DATA = 0xFF1E,
        OUTPUT_CONTROL = 0xFF24,
        CHANNEL_OUTPUT = 0xFF25,
    };

    enum CHANNEL_3_ON_FLAG
    {
        ON_FLAG = 128, // Bit 7 - Sound Channel 3 Off  (0=Stop, 1=Playback)  (Read/Write)
    };

    enum CHANNEL_3_LEVEL_FLAG
    {       
        OUTPUT_LEVEL_HIGH = 64, // Bit 6-5 - Select output level (Read/Write)
        OUTPUT_LEVEL_LOW = 32
    };

    enum CHANNEL_3_FREQ_DATA_FLAG
    {
        FREQ_RESTART = 128,    // Bit 7   - Initial (1=Restart Sound)     (Write Only)
        FREQ_LENGTH_STOP = 64, // Bit 6   - Counter/consecutive selection (Read/Write)
                               // (1=Stop output when length in NR31 expires)
        FREQ_HIGH = 4,         // Bit 2-0 - Frequency's higher 3 bits (x) (Write Only)
        FREQ_MID = 2,
        FREQ_LOW = 1
    };

    enum OUTPUT_CONTROL_FLAG
    {
        OUTPUT_2_ON = 127, // Bit 7   - Output Vin to SO2 terminal (1=Enable)
        // Bit 6-4 - SO2 output level (volume)  (0-7)
        OUTPUT_1_ON = 8,  // Bit 3   - Output Vin to SO1 terminal (1=Enable)
        // Bit 2-0 - SO1 output level (volume)  (0-7)
    };

    enum CHANNEL_OUTPUT_FLAG
    {
        CHANNEL_4_TO_OUTPUT_2 = 128, // Bit 7 - Output sound 4 to SO2 terminal
        CHANNEL_3_TO_OUTPUT_2 = 64,  // Bit 6 - Output sound 3 to SO2 terminal
        CHANNEL_2_TO_OUTPUT_2 = 32,  // Bit 5 - Output sound 2 to SO2 terminal
        CHANNEL_1_TO_OUTPUT_2 = 16,  // Bit 4 - Output sound 1 to SO2 terminal
        CHANNEL_4_TO_OUTPUT_1 = 8,   // Bit 3 - Output sound 4 to SO1 terminal
        CHANNEL_3_TO_OUTPUT_1 = 4,   // Bit 2 - Output sound 3 to SO1 terminal
        CHANNEL_2_TO_OUTPUT_1 = 2,   // Bit 1 - Output sound 2 to SO1 terminal
        CHANNEL_1_TO_OUTPUT_1 = 1    // Bit 0 - Output sound 1 to SO1 terminal
    };

    enum OUTPUT_LEVEL
    {
        MUTE = 0,
        L100 = 1,
        L50 = 2,
        L25 = 3
    };
}

#endif // APUENUMS_H