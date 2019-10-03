#include "sprite_list.h"

namespace GGB::Hardware::Video
{
    SpriteList::SpriteList(Mmu& mmu) : mmu(mmu) { }

    void SpriteList::loadSprites()
    {    
        bool bigSprite = mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::OBJ_SIZE, true);
        for(int i = 0; i < TOTAL_SPRITES; i++)
        {
            uint8_t posY = mmu.read(OAM_MEM_START + (i * 4) + POSITION_Y, true);
            uint8_t posX = mmu.read(OAM_MEM_START + (i * 4) + POSITION_X, true);
            uint8_t tileNr = mmu.read(OAM_MEM_START + (i * 4) + TILE_NR, true);
            uint8_t attributes = mmu.read(OAM_MEM_START + (i * 4) + ATTRIBUTES, true);
            
            Sprite sprite;
            sprite.memAdress = OAM_MEM_START + (i * 4);
            sprite.posY = posY;
            sprite.posX = posX;
            sprite.bigSprite = bigSprite;
            sprite.tileNr = bigSprite ? tileNr & 0xFE : tileNr;
            sprite.flipX = attributes & FLIP_X;
            sprite.flipY = attributes & FLIP_Y;
            sprite.bgPrio = attributes & OBJ_BG_PRIO;
            sprite.palette1Selected = attributes & PALETTE_NR;

            data[i] = sprite;
        }
    }
}