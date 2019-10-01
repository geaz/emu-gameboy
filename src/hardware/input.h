#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "memory/mmu.h"

enum Button
{
    GB_DOWN = 128,
    GB_UP = 64,
    GB_LEFT = 32,
    GB_RIGHT = 16,
    GB_START = 8,
    GB_SELECT = 4,
    GB_B = 2,
    GB_A = 1,
};

class Input
{
    public:
        Input(Mmu& mmu);

        void cycle(const uint8_t cycles);        
        void toggleButton(const Button button, const bool pressed);

    private:
        Mmu& mmu;

        uint32_t cycleCount = 0;
        uint8_t padState = 0xFF;

        const uint32_t PAD_FREQUENCY = 65536;
};

#endif // INPUT_H