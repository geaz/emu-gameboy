#include "sprite_list.h"

namespace GGB::Hardware::Video
{
    SpriteList::SpriteList(Mmu& mmu) : mmu(mmu) { }

    void SpriteList::updateSpriteInfo()
    {    
        bool bigSprite = mmu.readIORegisterBit(Const::AddrRegLcdControl, Const::FlagLcdControlObjSize, true);
        for(int i = 0; i < Const::TotalSprites; i++)
        {
            uint8_t posY = mmu.read(OAM_MEM_START + (i * 4) + Const::ByteSpritePosY, true);
            uint8_t posX = mmu.read(OAM_MEM_START + (i * 4) + Const::ByteSpritePosX, true);
            uint8_t tileNr = mmu.read(OAM_MEM_START + (i * 4) + Const::ByteSpriteTileNr, true);
            uint8_t attributes = mmu.read(OAM_MEM_START + (i * 4) + Const::ByteSpriteAttributes, true);
            
            Sprite sprite;
            sprite.memAdress = OAM_MEM_START + (i * 4);
            sprite.posY = posY;
            sprite.posX = posX;
            sprite.bigSprite = bigSprite;
            sprite.tileNr = bigSprite ? tileNr & 0xFE : tileNr;
            sprite.flipX = attributes & Const::FlagSpriteAttrFlipX;
            sprite.flipY = attributes & Const::FlagSpriteAttrFlipY;
            sprite.bgPrio = attributes & Const::FlagSpriteAttrObjBgPrio;
            sprite.palette1Selected = attributes & Const::FlagSpriteAttrPaletteNr;

            if(sprite.flipY && sprite.bigSprite)
                sprite.tileNr++;

            data[i] = sprite;
        }
    }
}