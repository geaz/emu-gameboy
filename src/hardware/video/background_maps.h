#pragma once
#ifndef BACKGROUNDMAPS_H
#define BACKGROUNDMAPS_H

#include "color_palettes.h"
#include "../memory/mmu.h"

struct BackgroundMap{
    uint8_t data[32][32];
};

class BackgroundMaps
{
    public:
        BackgroundMaps(Mmu& mmu);

        BackgroundMap getBackgroundMap() const;

    private:
        Mmu& mmu;

        const uint16_t MAP_0_START = 0x9800;
        const uint16_t MAP_1_START = 0x9C00;     
};

#endif // BACKGROUNDMAPS_H