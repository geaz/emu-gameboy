#include "tile_list.h"

namespace GGB::Hardware::Video
{
    TileList::TileList(Mmu& mmu) : mmu(mmu) { }

    Tile TileList::loadBackgroundTile(const uint8_t tileNr) const
    {
        // Each tile is 16 bytes long
        return mmu.readIORegisterBit(Const::AddrRegLcdControl, Const::FlagLcdControlBgData, true)
            ? loadTileFromMem(Const::AddrTileData1, tileNr, (tileNr * 16))
            : loadTileFromMem(Const::AddrTileData0, tileNr, ((static_cast<int8_t>(tileNr) + 128) * 16)); 
    }

    Tile TileList::loadWindowTile(const uint8_t tileNr) const
    {
        return loadTileFromMem(Const::AddrTileData0, tileNr, ((static_cast<int8_t>(tileNr) + 128) * 16)); 
    }

    Tile TileList::loadSpriteTile(const uint8_t tileNr) const
    {
        return loadTileFromMem(Const::AddrTileData1, tileNr, (tileNr * 16)); 
    }

    Tile TileList::loadTileFromMem(const uint16_t startAddr, const uint8_t tileNr, const int16_t tileMemStart) const
    {
        Tile tile;
        tile.nr = tileNr;

        uint16_t tileMemoryStart = (uint16_t)startAddr + tileMemStart;
        for(int i = 0; i < 8; i++)
        {
            uint8_t lineData1 = mmu.read(tileMemoryStart + (i * 2), true);
            uint8_t lineData2 = mmu.read(tileMemoryStart + (i * 2) + 1, true);
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