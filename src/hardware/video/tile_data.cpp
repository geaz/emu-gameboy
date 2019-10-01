#include "tile_data.h"

TileData::TileData(Mmu& mmu) : mmu(mmu) { }

Tile TileData::getBackgroundTile(const uint8_t number) const
{
    // Each tile is 16 bytes long
    return mmu.readIORegisterBit(REG_LCD_CONTROL, BG_TILE_DATA_SELECT)
        ? getTile(TILE_DATA_1, (number * 16))
        : getTile(TILE_DATA_0, ((static_cast<int8_t>(number) + 128) * 16)); 
}

Tile TileData::getSpriteTile(const uint8_t number) const
{
    return getTile(TILE_DATA_1, (number * 16)); 
}

Tile TileData::getTile(const uint16_t start, const int16_t number) const
{
    Tile tile;
    uint16_t memoryStart = start + number;
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