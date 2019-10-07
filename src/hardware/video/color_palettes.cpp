#include "color_palettes.h"

namespace GGB::Hardware::Video
{
    ColorPalettes::ColorPalettes(Mmu& mmu) : mmu(mmu) { }

    ColorPalette ColorPalettes::getBWPalette()
    {
        uint8_t colorData = mmu.read(Const::AddrRegBgPalette, true);
        return getPalette(colorData, false);
    }

    ColorPalette ColorPalettes::getOBP0Palette()
    {
        uint8_t colorData = mmu.read(Const::AddrRegOBPalette0, true);
        return getPalette(colorData, true);
    }

    ColorPalette ColorPalettes::getOBP1Palette()
    {
        uint8_t colorData = mmu.read(Const::AddrRegOBPalette1, true);
        return getPalette(colorData, true);
    }

    ColorPalette ColorPalettes::getPalette(const uint8_t colorData, const bool lowerIsTransparent)
    {
        ColorPalette palette;
        palette.colors[0] = lowerIsTransparent ? Enum::ColorShade::TRANSPARENT : (Enum::ColorShade) (colorData & 0x3);    
        palette.colors[1] = (Enum::ColorShade) ((colorData & 0xC) >> 2);    
        palette.colors[2] = (Enum::ColorShade) ((colorData & 0x30) >> 4);
        palette.colors[3] = (Enum::ColorShade) ((colorData & 0xC0) >> 6);
        
        return palette;
    }
}