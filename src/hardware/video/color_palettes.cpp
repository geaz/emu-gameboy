#include "color_palettes.h"
#include "../memory/io_register_flags.h"

ColorPalettes::ColorPalettes(Mmu& mmu) : mmu(mmu) { }

ColorPalette ColorPalettes::getBWPalette()
{
    uint8_t colorData = mmu.read(REG_BG_PALETTE);
    return getPalette(colorData, false);
}

ColorPalette ColorPalettes::getOBP0Palette()
{
    uint8_t colorData = mmu.read(REG_OB_PALETTE_0);
    return getPalette(colorData, true);
}

ColorPalette ColorPalettes::getOBP1Palette()
{
    uint8_t colorData = mmu.read(REG_OB_PALETTE_1);
    return getPalette(colorData, true);
}

ColorPalette ColorPalettes::getPalette(const uint8_t colorData, const bool lowerIsTransparent)
{
    ColorPalette palette;
    palette.colors[0] = lowerIsTransparent ? TRANSPARENT : (GBShade) (colorData & 0x3);    
    palette.colors[1] = (GBShade) ((colorData & 0xC) >> 2);    
    palette.colors[2] = (GBShade) ((colorData & 0x30) >> 4);
    palette.colors[3] = (GBShade) ((colorData & 0xC0) >> 6);
    
    return palette;
}