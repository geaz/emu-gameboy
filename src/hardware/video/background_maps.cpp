#include "background_maps.h"

BackgroundMaps::BackgroundMaps(Mmu& mmu) : mmu(mmu) { }

std::vector<std::vector<uint8_t>> BackgroundMaps::getBackgroundMap() const
{
    uint8_t selectedMap = mmu.readIORegisterBit(REG_LCD_CONTROL, WINDOW_TILE_MAP_SELECT);
    uint16_t startAddress = selectedMap == 0
        ? MAP_0_START
        : MAP_1_START;
    
    std::vector<std::vector<uint8_t>> backgroundMap(32, std::vector<uint8_t>(32));
    for(int i = 0; i < 32 * 32; i++)
    {
        backgroundMap[i/32][i%32] = mmu.read(startAddress + i);
    }
    return backgroundMap;
}