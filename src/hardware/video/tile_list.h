#pragma once
#ifndef TILEDATA_H
#define TILEDATA_H

#include "color_palettes.h"
#include "../memory/mmu.h"

namespace GGB::Hardware::Video
{
    struct Tile {
        uint8_t data[8][8];
    };

    enum class TILE_DATA_POSITION
    {
        TILE_DATA_0 = 0x8800,
        TILE_DATA_1 = 0x8000
    };

    class TileList
    {
        public:
            TileList(Mmu& mmu);
            
            Tile loadBackgroundTile(const uint8_t number) const;
            Tile loadSpriteTile(const uint8_t number) const;
            Tile loadWindowTile(const uint8_t number) const;

        private:
            Tile loadTileFromMem(const TILE_DATA_POSITION start, const int16_t number) const;

            Mmu& mmu;  
            Tile data0Cache[256], data1Cache[256];
    };
}

#endif // TILEDATA_H