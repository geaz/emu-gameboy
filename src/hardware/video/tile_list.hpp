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
            
            Tile getBackgroundTile(const uint8_t tileNr);
            Tile getSpriteTile(const uint8_t tileNr);
            Tile getWindowTile(const uint8_t tileNr);

        private:
            void onMmuWrite(MemoryWriteEvent writeEvent);
            Tile getTile(const uint16_t startAddr, const uint8_t tileNr);
            void updateTiles(Tile* tileData, const uint16_t startAddr);

            Mmu& mmu;  
            Tile tile0Data[256];
            Tile tile1Data[256];
            bool tile0MemUpdated = false;
            bool tile1MemUpdated = false;
    };
}

#endif // TILEDATA_H