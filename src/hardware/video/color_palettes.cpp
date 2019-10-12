#include "color_palettes.hpp"

namespace GGB::Hardware::Video
{
    ColorPalettes::ColorPalettes(Mmu& mmu) : mmu(mmu) 
    {
        mmu.registerOnAddrWrite([this](MemoryWriteEvent writeEvent) { onMmuWrite(writeEvent); });
    }

    ColorPalette ColorPalettes::getBWPalette()
    {
        return bwPalette;
    }

    ColorPalette ColorPalettes::getOBP0Palette()
    {
        return obj0Palette;
    }

    ColorPalette ColorPalettes::getOBP1Palette()
    {
        return obj1Palette;
    }
    
    void ColorPalettes::onMmuWrite(MemoryWriteEvent writeEvent)
    {
        switch(writeEvent.address)
        {
            case Const::AddrRegBgPalette:
                bwPalette = getPalette(writeEvent.value, false);
                break;
            case Const::AddrRegOBPalette0:
                obj0Palette = getPalette(writeEvent.value, true);
                break;
            case Const::AddrRegOBPalette1:
                obj1Palette = getPalette(writeEvent.value, true);
                break;
        }
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