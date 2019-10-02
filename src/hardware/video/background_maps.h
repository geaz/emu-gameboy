#pragma once
#ifndef BACKGROUNDMAPS_H
#define BACKGROUNDMAPS_H

#include "color_palettes.h"
#include "../memory/mmu.h"

namespace GGB::Hardware::Video
{
    struct BackgroundMap{
        uint8_t data[32][32];
    };

    class BackgroundMaps
    {
        public:
            BackgroundMaps(Mmu& mmu);

            BackgroundMap getBackgroundMap() const;
            BackgroundMap getWindowMap() const;

        private:
            BackgroundMap getMap(Enums::LCD_CONTROL_FLAG controlFlag) const;

            Mmu& mmu;

            const uint16_t MAP_0_START = 0x9800;
            const uint16_t MAP_1_START = 0x9C00;     
    };
}

#endif // BACKGROUNDMAPS_H