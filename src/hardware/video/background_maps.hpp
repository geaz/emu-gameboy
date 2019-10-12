#pragma once
#ifndef BACKGROUNDMAPS_H
#define BACKGROUNDMAPS_H

#include "color_palettes.hpp"
#include "../memory/mmu.hpp"

namespace GGB::Hardware::Video
{
    struct BackgroundMap{
        uint8_t data[32][32];
    };

    class BackgroundMaps
    {
        public:
            BackgroundMaps(Mmu& mmu);

            BackgroundMap getBackgroundMap();
            BackgroundMap getWindowMap();

        private:            
            void onMmuWrite(MemoryWriteEvent writeEvent);
            BackgroundMap getMap(const uint8_t controlFlag);
            BackgroundMap loadMap(const uint16_t startAddress) const;

            Mmu& mmu;    
            bool mapData0MemUpdated = false;
            bool mapData1MemUpdated = false;
            BackgroundMap map0;
            BackgroundMap map1;
    };
}

#endif // BACKGROUNDMAPS_H