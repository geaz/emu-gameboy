#pragma once
#ifndef TILEDATA_H
#define TILEDATA_H

#include <vector>
#include "color_palettes.h"
#include "../memory/mmu.h"

class TileData
{
    public:
        TileData(Mmu& mmu);

        std::vector<std::vector<uint8_t>> getBackgroundTile(const uint8_t number) const;

    private:
        std::vector<std::vector<uint8_t>> getTile(const uint16_t start, const uint8_t number) const;

        Mmu& mmu;

        const uint16_t SB_MAP_START = 0x8000;
        const uint16_t BW_MAP_START = 0x8800;
        const uint16_t SB_MAP_END = 0x8FFF;
        const uint16_t BW_MAP_END = 0x97FF;        
};

#endif // TILEDATA_H