#pragma once
#ifndef PPU_H
#define PPU_H

#include "tile_list.h"
#include "sprite_list.h"
#include "color_palettes.h"
#include "background_maps.h"
#include "../memory/mmu.h"

namespace GGB
{
    namespace Constants
    {
        const uint8_t GAMEBOY_LCD_WIDTH = 160;
        const uint8_t GAMEBOY_LCD_HEIGHT = 144;
    }

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

                Enums::GB_SHADE spriteData[144][160];
                Enums::GB_SHADE backgroundData[144][160];
                Enums::GB_SHADE spriteBuffer[144][160];
                Enums::GB_SHADE backgroundBuffer[144][160];

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

                long cycleCount = 0;

                const uint16_t CYCLES_PER_HBLANK = 207;   // Mode 0 (H-Blank) 207 cycles
                const uint16_t CYCLES_PER_VBLANK = 4560;  // Mode 1 (V-Blank) 4560 cycles
                const uint16_t CYCLES_PER_OAMSEARCH = 83; // Mode 2 (OAM Search) 83 cycles
                const uint16_t CYCLES_PER_TRANSFER = 175; // Mode 3 (Transfer LCD) 175 cycles
        };
    }
}

#endif // PPU_H