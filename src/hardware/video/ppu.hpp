#pragma once
#ifndef PPU_H
#define PPU_H

#include "tile_list.hpp"
#include "sprite_list.hpp"
#include "color_palettes.hpp"
#include "background_maps.hpp"
#include "../memory/mmu.hpp"

namespace GGB
{
    namespace Hardware 
    {
        class Ppu
        {                     
            public:
                Ppu(Mmu& mmu);

                void cycle(const uint8_t cycles);

                Video::ColorPalette obj0Palette;
                Video::ColorPalette obj1Palette;
                Video::ColorPalette backgroundPalette;

                Enum::ColorShade spriteData[144][160];
                Enum::ColorShade backgroundData[144][160];

            private:
                void processOam();
                void processTransfer();
                void processHBlank();
                void processVBlank();

                void drawBackground();
                void drawWindow();
                void drawSprites();
                void resetBuffers(const bool initial);

                Mmu& mmu;
                Video::TileList tileList;
                Video::SpriteList spriteList;   
                Video::ColorPalettes colorPalettes;
                Video::BackgroundMaps backgroundMaps;
                Video::BackgroundMap currentBackgroundMap;
                
                Enum::ColorShade spriteBuffer[144][160];
                Enum::ColorShade backgroundBuffer[144][160];

                long cycleCount = 0;
        };
    }
}

#endif // PPU_H