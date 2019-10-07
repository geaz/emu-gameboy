#pragma once
#ifndef COLORPALETTES_H
#define COLORPALETTES_H

#include "../memory/mmu.h"

namespace GGB
{
    namespace Hardware::Video
    {
        struct ColorPalette
        {
            Enum::ColorShade colors[4];
        };

        class ColorPalettes
        {
            public:
                ColorPalettes(Mmu& mmu);

                ColorPalette getBWPalette();
                ColorPalette getOBP0Palette();
                ColorPalette getOBP1Palette();      
            
            private:
                ColorPalette getPalette(const uint8_t colorData, const bool lowerIsTransparent);

                Mmu& mmu;
        };
    }
}

#endif // COLORPALETTES_H