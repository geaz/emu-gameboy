#pragma once
#ifndef GGBENUMS_H
#define GGBENUMS_H

namespace GGB::Enum
{
    enum class CpuState 
    { 
        STEP, 
        PAUSED, 
        RUNNING,
        INTERRUPT,
        ERROR 
    };

    enum class CpuFlag 
    { 
        Z_ZERO = 7, 
        N_SUBSTRACT = 6, 
        H_HALFCARRY = 5, 
        C_CARRY = 4 
    
    };  

    enum class LcdMode
    {
        HBlank = 0,
        VBlank = 1,
        Oam = 2,
        Transfer = 3
    };

    enum class PadButton
    {
        DOWN = 128,
        UP = 64,
        LEFT = 32,
        RIGHT = 16,
        START = 8,
        SELECT = 4,
        B = 2,
        A = 1,
    };

    enum class ColorShade
    {
        WHITE = 0,
        LIGHT_GRAY = 1,
        DARK_GRAY = 2,
        BLACK = 3,    
        TRANSPARENT = 4
    };

    enum class AudioLevel
    {
        MUTE = 0,
        L100 = 1,
        L50 = 2,
        L25 = 3
    };

    enum class AudioChannel
    {
        Wave
    };
}

#endif // GGBENUMS_H