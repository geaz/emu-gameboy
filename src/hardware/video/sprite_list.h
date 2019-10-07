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