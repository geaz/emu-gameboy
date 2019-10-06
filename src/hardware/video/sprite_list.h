#pragma once
#ifndef SPRITEDATA_H
#define SPRITEDATA_H

#include "color_palettes.h"
#include "../memory/mmu.h"

namespace GGB::Hardware::Video
{
    struct Sprite { 
        uint16_t memAdress;
        uint8_t posY; 
        uint8_t posX; 
        uint8_t tileNr; 
        bool palette1Selected; 
        bool flipX; 
        bool flipY; 
        bool bgPrio; 
        bool bigSprite; 

        bool operator < (const Sprite& other) const
        {
            return (posX < other.posX) || (posX == other.posX && memAdress < other.memAdress);
        }    
    };

    enum SpriteNumbers { TOTAL_SPRITES = 40, MAX_SPRITES_Y = 10 };
    enum SpriteByte { POSITION_Y = 0, POSITION_X = 1, TILE_NR = 2, ATTRIBUTES = 3 };
    enum SpriteAttributeFlag
    {
        OBJ_BG_PRIO = 128,  // Bit7   OBJ-to-BG Priority (0=OBJ Above BG, 1=OBJ Behind BG color 1-3)
                            // (Used for both BG and Window. BG color 0 is always behind OBJ)
        FLIP_Y = 64,        // Bit6   Y flip          (0=Normal, 1=Vertically mirrored)
        FLIP_X = 32,        // Bit5   X flip          (0=Normal, 1=Horizontally mirrored)
        PALETTE_NR = 16     // Bit4   Palette number  **Non CGB Mode Only** (0=OBP0, 1=OBP1)
    };

    class SpriteList
    {
        public:
            SpriteList(Mmu& mmu);

            void updateSpriteInfo();

            Sprite data[40]; 

        private:
            Mmu& mmu;

            const uint16_t OAM_MEM_START = 0xFE00;  
    };
}

#endif // SPRITEDATA_H