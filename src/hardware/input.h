#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "memory/mmu.h"

namespace GGB
{
    namespace Enums
    {
        enum JOYPAD
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
    }   

    namespace Hardware
    {
        class Input
        {
            public:
                Input(Mmu& mmu);

                void cycle();        
                void toggleButton(const Enums::JOYPAD button, const bool pressed);

            private:
                Mmu& mmu;
                uint8_t padState = 0xFF;
        };
    }
}

#endif // INPUT_H