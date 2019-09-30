#include "tile_data.h"

TileData::TileData(Mmu& mmu) : mmu(mmu) { }

Tile TileData::getBackgroundTile(const uint8_t number) const
{
    return mmu.readIORegisterBit(REG_LCD_CONTROL, WINDOW_TILE_MAP_SELECT)
        ? getTile(BW_MAP_START, number + 128)
        : getTile(SB_MAP_START, number); 
}

Tile TileData::getTile(const uint16_t start, const uint8_t number) const
{
    uint16_t memoryStart = start + (number * 16); // Each tile is 16 bytes long
    Tile tile;
    for(int i = 0; i < 8; i++)
    {
        uint8_t lineData1 = mmu.read(memoryStart + (i * 2));
        uint8_t lineData2 = mmu.read(memoryStart + (i * 2) + 1);
        for(int j = 7; j >= 0; j--)
        {
            uint8_t lowBit = (lineData1 >> j) & 0x1; 
            uint8_t highBit =  (lineData2 >> j) & 0x1; 
            tile.data[i][std::abs(j - 7)] = (highBit << 1) | lowBit;
        }
    }
    return tile;
}