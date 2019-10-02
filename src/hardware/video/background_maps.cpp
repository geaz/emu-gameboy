#include "background_maps.h"

namespace GGB::Hardware::Video
{
    BackgroundMaps::BackgroundMaps(Mmu& mmu) : mmu(mmu) { }

    BackgroundMap BackgroundMaps::getBackgroundMap() const
    {
        return getMap(Enums::LCD_CONTROL_FLAG::BG_TILE_MAP_SELECT);
    }

    BackgroundMap BackgroundMaps::getWindowMap() const
    {
        return getMap(Enums::LCD_CONTROL_FLAG::WINDOW_TILE_MAP_SELECT);
    }

    BackgroundMap BackgroundMaps::getMap(Enums::LCD_CONTROL_FLAG controlFlag) const
    {
        uint16_t startAddress = mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, controlFlag)
            ? MAP_1_START
            : MAP_0_START;
        
        BackgroundMap backgroundMap;
        for(int i = 0; i < 32 * 32; i++)
        {
            backgroundMap.data[i/32][i%32] = mmu.read(startAddress + i);
        }
        return backgroundMap;
    }
}