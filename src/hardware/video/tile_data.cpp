#include "tile_data.h"

TileData::TileData(Mmu& mmu) : mmu(mmu) { }

std::vector<std::vector<uint8_t>> TileData::getBackgroundTile(const uint8_t number) const
{
    uint8_t selectedMap = mmu.readIORegisterBit(REG_LCD_CONTROL, WINDOW_TILE_MAP_SELECT);
    return selectedMap == 0
        ? getTile(SB_MAP_START, number)
        : getTile(BW_MAP_START, number + 128); 
}

std::vector<std::vector<uint8_t>> TileData::getTile(const uint16_t start, const uint8_t number) const
{
    uint16_t memoryStart = start + (number * 16); // Each tile is 16 bytes long
    std::vector<std::vector<uint8_t>> tile(8, std::vector<uint8_t>(8));
        for(int i = 0; i < 8; i++)
        {
            uint8_t lineData1 = mmu.read(memoryStart + (i * 2));
            uint8_t lineData2 = mmu.read(memoryStart + (i * 2) + 1);
            for(int j = 7; j >= 0; j--)
            {
                uint8_t lowBit = (lineData1 >> j) & 0x1; 
                uint8_t highBit =  (lineData2 >> j) & 0x1; 
                tile[i][std::abs(j - 7)] = (highBit << 1) | lowBit;
            }
        }
        return tile;
}