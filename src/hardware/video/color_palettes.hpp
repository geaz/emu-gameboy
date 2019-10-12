#pragma once
#ifndef COLORPALETTES_H
#define COLORPALETTES_H

#include "../memory/mmu.hpp"

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
                void onMmuWrite(MemoryWriteEvent writeEvent); 
                ColorPalette getPalette(const uint8_t colorData, const bool lowerIsTransparent);

                Mmu& mmu;
                ColorPalette bwPalette;
                ColorPalette obj0Palette;
                ColorPalette obj1Palette;
        };
    }
}

#endif // COLORPALETTES_H