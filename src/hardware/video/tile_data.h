#pragma once
#ifndef TILEDATA_H
#define TILEDATA_H

#include "color_palettes.h"
#include "../memory/mmu.h"

struct Tile {
    uint8_t data[8][8];
};

class TileData
{
    public:
        TileData(Mmu& mmu);

        Tile getBackgroundTile(const uint8_t number) const;

    private:
        Tile getTile(const uint16_t start, const uint8_t number) const;

        Mmu& mmu;

        const uint16_t TILE_DATA_0 = 0x8800;  
        const uint16_t TILE_DATA_1 = 0x8000;   
};

#endif // TILEDATA_H