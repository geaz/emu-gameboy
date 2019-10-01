#pragma once
#ifndef TILEDATA_H
#define TILEDATA_H

#include "color_palettes.h"
#include "../memory/mmu.h"

struct Tile {
    uint8_t data[8][8];
};

enum TileDataPosition
{
    TILE_DATA_0 = 0x8800,
    TILE_DATA_1 = 0x8000
};

class TileData
{
    public:
        TileData(Mmu& mmu);

        Tile getBackgroundTile(const uint8_t number) const;
        Tile getSpriteTile(const uint8_t number) const;

    private:
        Tile getTile(const uint16_t start, const int16_t number) const;

        Mmu& mmu;  
};

#endif // TILEDATA_H