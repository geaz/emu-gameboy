#pragma once
#ifndef SPRITEDATA_H
#define SPRITEDATA_H

#include "color_palettes.hpp"
#include "../memory/mmu.hpp"

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

            Sprite getSprite(uint8_t index);

        private:
            void onMmuWrite(MemoryWriteEvent writeEvent);
            void updateSpriteInfo();

            Mmu& mmu;
            Sprite data[40];
            bool spriteDataMemUpdated = false;
    };
}

#endif // SPRITEDATA_H