#pragma once
#ifndef TILEDATA_H
#define TILEDATA_H

#include "color_palettes.hpp"
#include "../memory/mmu.hpp"

namespace GGB::Hardware::Video
{
    struct Tile {
        uint8_t nr;
        uint8_t data[8][8];
    };

    class TileList
    {
        public:
            TileList(Mmu& mmu);
            
            Tile loadBackgroundTile(const uint8_t tileNr) const;
            Tile loadSpriteTile(const uint8_t tileNr) const;
            Tile loadWindowTile(const uint8_t tileNr) const;

        private:
            Tile loadTileFromMem(const uint16_t startAddr, const uint8_t tileNr, const int16_t tileMemStart) const;

            Mmu& mmu;  
            Tile data0Cache[256], data1Cache[256];
    };
}

#endif // TILEDATA_H