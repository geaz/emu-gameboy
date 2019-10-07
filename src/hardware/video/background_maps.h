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
            BackgroundMap getMap(const uint8_t controlFlag) const;

            Mmu& mmu;    
    };
}

#endif // BACKGROUNDMAPS_H