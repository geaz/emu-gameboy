#pragma once
#ifndef COLORPALETTES_H
#define COLORPALETTES_H

#include "../memory/mmu.h"

enum GBShade
{
    WHITE = 0,
    LIGHT_GRAY = 1,
    DARK_GRAY = 2,
    BLACK = 3
};

struct ColorPalette
{
    uint8_t colors[4];
};

class ColorPalettes
{
    public:
        ColorPalettes(Mmu& mmu);

        ColorPalette getBWPalette();
        ColorPalette getOBP0Palette();
        ColorPalette getOBP1Palette();      
    
    private:
        Mmu& mmu;
};

#endif // COLORPALETTES_H