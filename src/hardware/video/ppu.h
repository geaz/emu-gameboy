#pragma once
#ifndef PPU_H
#define PPU_H

#include "tile_data.h"
#include "sprite_list.h"
#include "color_palettes.h"
#include "background_maps.h"
#include "../memory/mmu.h"

class Ppu
{
    public:
        Ppu(Mmu& mmu);

        void cycle(const uint8_t cycles);

        ColorPalette obj0Palette;
        ColorPalette obj1Palette;
        ColorPalette backgroundPalette;

        uint8_t spriteData[144][160];
        uint8_t backgroundData[144][160];
        uint8_t spriteBuffer[144][160];
        uint8_t backgroundBuffer[144][160];

    private:
        bool processOam();
        bool processTransfer();
        bool processHBlank();
        bool processVBlank();

        void drawBackground();
        void drawSprites();
        void resetBuffers();

        Mmu& mmu;
        TileData tileData;
        SpriteList spriteList;   
        ColorPalettes colorPalettes;
        BackgroundMaps backgroundMaps;

        long cycleCount = 0;

        const uint16_t CYCLES_PER_HBLANK = 207;   // Mode 0 (H-Blank) 207 cycles
        const uint16_t CYCLES_PER_VBLANK = 4560;  // Mode 1 (V-Blank) 4560 cycles
        const uint16_t CYCLES_PER_OAMSEARCH = 83; // Mode 2 (OAM Search) 83 cycles
        const uint16_t CYCLES_PER_TRANSFER = 175; // Mode 3 (Transfer LCD) 175 cycles
};

#endif // PPU_H