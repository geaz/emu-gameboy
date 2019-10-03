#include "tile_list.h"

namespace GGB::Hardware::Video
{
    TileList::TileList(Mmu& mmu) : mmu(mmu) { }

    Tile TileList::loadBackgroundTile(const uint8_t tileNr) const
    {
        // Each tile is 16 bytes long
        return mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::BG_TILE_DATA_SELECT, true)
            ? loadTileFromMem(TILE_DATA_POSITION::TILE_DATA_1, tileNr, (tileNr * 16))
            : loadTileFromMem(TILE_DATA_POSITION::TILE_DATA_0, tileNr, ((static_cast<int8_t>(tileNr) + 128) * 16)); 
    }

    Tile TileList::loadWindowTile(const uint8_t tileNr) const
    {
        return loadTileFromMem(TILE_DATA_POSITION::TILE_DATA_1, tileNr, (tileNr * 16)); 
    }

    Tile TileList::loadSpriteTile(const uint8_t tileNr) const
    {
        return loadTileFromMem(TILE_DATA_POSITION::TILE_DATA_1, tileNr, (tileNr * 16)); 
    }

    Tile TileList::loadTileFromMem(const TILE_DATA_POSITION start, const uint8_t tileNr, const int16_t tileMemStart) const
    {
        Tile tile;
        tile.nr = tileNr;

        uint16_t memoryStart = (uint16_t)start + tileMemStart;
        for(int i = 0; i < 8; i++)
        {
            uint8_t lineData1 = mmu.read(memoryStart + (i * 2), true);
            uint8_t lineData2 = mmu.read(memoryStart + (i * 2) + 1, true);
            for(int j = 7; j >= 0; j--)
            {
                uint8_t lowBit = (lineData1 >> j) & 0x1; 
                uint8_t highBit =  (lineData2 >> j) & 0x1; 
                tile.data[i][std::abs(j - 7)] = (highBit << 1) | lowBit;
            }
        }
        return tile;
    }
}