#include "sprite_list.h"

SpriteList::SpriteList(Mmu& mmu) : mmu(mmu) { }

void SpriteList::loadSprites()
{    
    bool bigSprite = mmu.readIORegisterBit(REG_LCD_CONTROL, OBJ_SIZE);
    for(int i = 0; i < TOTAL_SPRITES; i++)
    {
        uint8_t posY = mmu.read(OAM_MEM_START + (i * 4) + POSITION_Y);
        uint8_t posX = mmu.read(OAM_MEM_START + (i * 4) + POSITION_X);
        uint8_t tileNr = mmu.read(OAM_MEM_START + (i * 4) + TILE_NR);
        uint8_t attributes = mmu.read(OAM_MEM_START + (i * 4) + ATTRIBUTES);
        
        Sprite sprite;
        sprite.memAdress = OAM_MEM_START + (i * 4);
        sprite.posY = posY;
        sprite.posX = posX;
        sprite.bigSprite = bigSprite;
        sprite.flipX = attributes & FLIP_X;
        sprite.flipY = attributes & FLIP_Y;
        sprite.bgPrio = attributes & OBJ_BG_PRIO;
        sprite.palette1Selected = attributes & PALETTE_NR;

        if(bigSprite)
        {
            sprite.upperTileNr = ((tileNr & 0xFF00) >> 4) & 0xFE;
            sprite.upperTileNr = ((tileNr & 0xFF00) >> 4) | 0x01;
        }
        else sprite.lowerTileNr = tileNr;

        data[i] = sprite;
    }
}