#include "color_palettes.h"
#include "../memory/memory_flags.h"

ColorPalettes::ColorPalettes(Mmu& mmu) : mmu(mmu) { }

ColorPalette ColorPalettes::getBWPalette()
{
    uint8_t colorData = mmu.read(REG_BG_PALETTE);
    ColorPalette bwPalette;
    bwPalette.colors[0] = (GBShade) (colorData & 0x3);    
    bwPalette.colors[1] = (GBShade) ((colorData & 0xC) >> 2);    
    bwPalette.colors[2] = (GBShade) ((colorData & 0x30) >> 4);
    bwPalette.colors[3] = (GBShade) ((colorData & 0xC0) >> 6);

    return bwPalette;
}

ColorPalette ColorPalettes::getOBP0Palette()
{
    uint8_t colorData = mmu.read(REG_OB_PALETTE_0);
    ColorPalette obPalette;
    obPalette.colors[0] = (GBShade) (colorData & 0x3);    
    obPalette.colors[1] = (GBShade) ((colorData & 0xC) >> 2);    
    obPalette.colors[2] = (GBShade) ((colorData & 0x30) >> 4);
    obPalette.colors[3] = (GBShade) ((colorData & 0xC0) >> 6);

    return obPalette;
}

ColorPalette ColorPalettes::getOBP1Palette()
{
    uint8_t colorData = mmu.read(REG_OB_PALETTE_1);
    ColorPalette obPalette;
    obPalette.colors[0] = (GBShade) (colorData & 0x3);    
    obPalette.colors[1] = (GBShade) ((colorData & 0xC) >> 2);    
    obPalette.colors[2] = (GBShade) ((colorData & 0x30) >> 4);
    obPalette.colors[3] = (GBShade) ((colorData & 0xC0) >> 6);
    
    return obPalette;
}