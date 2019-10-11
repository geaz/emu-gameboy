#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "memory/mmu.hpp"
#include "../ggb_enums.hpp"

namespace GGB
{
    namespace Hardware
    {
        class Input
        {
            public:
                Input(Mmu& mmu);

                void cycle();        
                void toggleButton(const Enum::PadButton button, const bool pressed);

            private:
                Mmu& mmu;
                uint8_t padState = 0xFF;
        };
    }
}

#endif // INPUT_H