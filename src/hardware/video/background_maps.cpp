#include "background_maps.h"

BackgroundMaps::BackgroundMaps(Mmu& mmu) : mmu(mmu) { }

BackgroundMap BackgroundMaps::getBackgroundMap() const
{
    uint16_t startAddress = mmu.readIORegisterBit(REG_LCD_CONTROL, WINDOW_TILE_MAP_SELECT)
        ? MAP_1_START
        : MAP_0_START;
    
    BackgroundMap backgroundMap;
    for(int i = 0; i < 32 * 32; i++)
    {
        backgroundMap.data[i/32][i%32] = mmu.read(startAddress + i);
    }
    return backgroundMap;
}