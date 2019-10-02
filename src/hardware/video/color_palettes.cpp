#include "color_palettes.h"
#include "../memory/io_register_flags.h"

namespace GGB::Hardware::Video
{
    ColorPalettes::ColorPalettes(Mmu& mmu) : mmu(mmu) { }

    ColorPalette ColorPalettes::getBWPalette()
    {
        uint8_t colorData = mmu.readIORegister(Enums::IO_REGISTER::REG_BG_PALETTE, true);
        return getPalette(colorData, false);
    }

    ColorPalette ColorPalettes::getOBP0Palette()
    {
        uint8_t colorData = mmu.readIORegister(Enums::IO_REGISTER::REG_OB_PALETTE_0, true);
        return getPalette(colorData, true);
    }

    ColorPalette ColorPalettes::getOBP1Palette()
    {
        uint8_t colorData = mmu.readIORegister(Enums::IO_REGISTER::REG_OB_PALETTE_1, true);
        return getPalette(colorData, true);
    }

    ColorPalette ColorPalettes::getPalette(const uint8_t colorData, const bool lowerIsTransparent)
    {
        ColorPalette palette;
        palette.colors[0] = lowerIsTransparent ? Enums::GB_SHADE::TRANSPARENT : (Enums::GB_SHADE) (colorData & 0x3);    
        palette.colors[1] = (Enums::GB_SHADE) ((colorData & 0xC) >> 2);    
        palette.colors[2] = (Enums::GB_SHADE) ((colorData & 0x30) >> 4);
        palette.colors[3] = (Enums::GB_SHADE) ((colorData & 0xC0) >> 6);
        
        return palette;
    }
}