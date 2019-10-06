#include "ppu.h"
#include <algorithm>

namespace GGB::Hardware
{
    Ppu::Ppu(Mmu& mmu) : 
        mmu(mmu), 
        tileList(mmu), 
        spriteList(mmu),
        backgroundMaps(mmu),
        colorPalettes(mmu)
    { 
        resetBuffers(true); 
    }

    void Ppu::cycle(const uint8_t cycles)
    {
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::ENABLE, true)) return;

        cycleCount += cycles;
        Enums::LCD_MODE currentMode = mmu.readLcdMode();

        switch (currentMode)
        {
            case Enums::LCD_MODE::OAM:
                processOam();
                break;
            case Enums::LCD_MODE::TRANSFER:
                processTransfer();
                break;
            case Enums::LCD_MODE::HBLANK:
                processHBlank();
                break;
            case Enums::LCD_MODE::VBLANK:
                processVBlank();
                break;
        }
    }

    void Ppu::processOam()
    {
        if(cycleCount >= CYCLES_PER_OAMSEARCH)
        {
            // Check for OAM Interrupt
            if(mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::OAM_INTERRUPT_ENABLED, true))
            {
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::LCD, true);
            }

            // Check for LCD Y Compare
            uint8_t lcdy = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true);
            uint8_t lcdyc = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y_COMPARE, true);
            if(lcdy == lcdyc)
            {
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::COINCIDENCE_FLAG, true); 
                if(mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::C_INTERRUPT_ENABLED, true))
                {
                    mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::LCD, true);
                }
            }  
            else
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::COINCIDENCE_FLAG, false);
            
            mmu.writeLcdMode(Enums::LCD_MODE::TRANSFER);
            cycleCount -= CYCLES_PER_OAMSEARCH;
        }    
    }

    void Ppu::processTransfer()
    {
        if(cycleCount >= CYCLES_PER_TRANSFER)
        {
            mmu.writeLcdMode(Enums::LCD_MODE::HBLANK);
            cycleCount -= CYCLES_PER_TRANSFER;
        }    
    }
        
    void Ppu::processHBlank()
    {
        if(cycleCount >= CYCLES_PER_HBLANK)
        {
            // Check for H-BLANK Interrupt
            if(mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::H_BLANK_INTERRUPT_ENABLE, true))
            {
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::LCD, true);
            }
            
            drawBackground();
            drawWindow();
            drawSprites();

            // Enter V-BLANK on last line 143
            if(mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true) == 143) mmu.writeLcdMode(Enums::LCD_MODE::VBLANK);
            // Enter OAM again
            else mmu.writeLcdMode(Enums::LCD_MODE::OAM);    

            // Increment Line count and update cycles
            mmu.rawWrite(Enums::IO_REGISTER::REG_LCD_Y, mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true) + 1); 
            cycleCount -= CYCLES_PER_HBLANK;  
        }       
    }
        
    void Ppu::processVBlank()
    {
        if(cycleCount >= CYCLES_PER_VBLANK)
        {
            // Set V_BLANK interrupt on V-Blank mode begin (Line 144)
            if(mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true) == 144)
            {
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::V_BLANK, true);

                // Copy buffers to data
                std::copy(&spriteBuffer[0][0], &spriteBuffer[0][0] + 160*144, &spriteData[0][0]);
                std::copy(&backgroundBuffer[0][0], &backgroundBuffer[0][0] + 160*144, &backgroundData[0][0]);
                resetBuffers(false);
            }

            // Reset on last line 153 and Enter OAM
            if(mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true) == 153)
            {
                mmu.rawWrite(Enums::IO_REGISTER::REG_LCD_Y, 0);
                mmu.writeLcdMode(Enums::LCD_MODE::OAM);
            }
            // Else increment Y and stay in V-Blank Mode
            else mmu.rawWrite(Enums::IO_REGISTER::REG_LCD_Y, mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true) + 1);

            cycleCount -= CYCLES_PER_VBLANK; 
        }    
    }

    void Ppu::drawBackground()
    {
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::BG_ENABLE, true)) return;

        uint8_t lcdY = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true);
        uint8_t scrollY = mmu.readIORegister(Enums::IO_REGISTER::REG_SCROLL_Y, true);
        uint8_t scrollX = mmu.readIORegister(Enums::IO_REGISTER::REG_SCROLL_X, true);

        // Wrap the Window around Y
        uint8_t startBackgroundTileY = (scrollY + lcdY) / 8 >= 32
            ? (scrollY + lcdY) / 8 % 32
            : (scrollY + lcdY) / 8;
        uint8_t backgroundTileYOffset = (scrollY + lcdY) % 8;

        uint8_t startBackgroundTileX = scrollX / 8;
        uint8_t backgroundTileXOffset = scrollX % 8;

        backgroundPalette = colorPalettes.getBWPalette();
        Video::BackgroundMap currentBackgroundMap = backgroundMaps.getBackgroundMap();

        // The Game Boy screen is able to display 20 tiles horizontal (160 pixel / 8 pixel per Tile)
        // We will render 21 tiles to scroll correctly
        for(int i = 0; i < 21; i++)
        {
            // Wrap the Window around X
            uint8_t tileNrX = startBackgroundTileX + i >= 32
                ? (startBackgroundTileX + i) % 32
                : startBackgroundTileX + i;
            uint8_t currentTileNr = currentBackgroundMap.data[startBackgroundTileY][tileNrX];
            Video::Tile currentTile = tileList.loadBackgroundTile(currentTileNr);
            // each tile is 8 pixels wide
            for(int j = 0; j < 8; j++)
            {
                // Skip the first pixels, if the window start in the middle of the first tile
                // And skip the last few pixels of the end tile
                if(i == 0 && j < backgroundTileXOffset) continue;
                if(i == 20 && j >= backgroundTileXOffset) continue;
                
                uint8_t pixelData = currentTile.data[backgroundTileYOffset][j];
                Enums::GB_SHADE color = backgroundPalette.colors[pixelData];
                backgroundBuffer[lcdY][(i * 8) + j - backgroundTileXOffset] = color;
            }
        } 
    }

    void Ppu::drawWindow()
    {
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::WINDOW_ENABLE, true)) return;

        uint8_t lcdY = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true);
        int16_t windowY = mmu.readIORegister(Enums::IO_REGISTER::REG_WINDOW_Y, true);
        int16_t windowX = mmu.readIORegister(Enums::IO_REGISTER::REG_WINDOW_X, true) - 7;

        if(lcdY >= windowY)
        {
            bool stopOffscreen = false;
            Video::BackgroundMap currentWindowMap = backgroundMaps.getWindowMap();
            for(int tileX = 0; tileX < 32; tileX++)
            {
                uint8_t currentTileNr = currentWindowMap.data[(lcdY - windowY) / 8][tileX];            
                Video::Tile currentTile = tileList.loadWindowTile(currentTileNr);
                for(int j = 0; j < 8; j++)
                {
                    // Skip the first pixels, if the window start in the middle of the first tile
                    // And skip the last few pixels of the end tile
                    if((tileX * 8) + j + windowX > 159)
                    {
                        stopOffscreen = true;
                        break;
                    }

                    uint8_t pixelData = currentTile.data[(lcdY - windowY) % 8][j];
                    Enums::GB_SHADE color = backgroundPalette.colors[pixelData];
                    backgroundBuffer[lcdY][(tileX * 8) + j + windowX] = color;
                }            
                if(stopOffscreen) break;
            }
        }
    }

    void Ppu::drawSprites()
    {
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::OBJ_ENABLE, true)) return;

        spriteList.updateSpriteInfo();
        obj0Palette = colorPalettes.getOBP0Palette();
        obj1Palette = colorPalettes.getOBP1Palette();

        uint8_t lcdY = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y, true);

        int vCounter = 0;
        Video::Sprite visibleSprites[Video::TOTAL_SPRITES];
        for(int i = 0; i < Video::TOTAL_SPRITES; i++)
        {
            Video::Sprite currentSprite = spriteList.data[i];

            // Pos Y : Specifies the sprites vertical position on the screen (minus 16).
            // An offscreen value (for example, Y=0 or Y>=160) hides the sprite.
            if(lcdY >= currentSprite.posY - 16 
                && (  (currentSprite.bigSprite && lcdY < currentSprite.posY)
                || (!currentSprite.bigSprite && lcdY < currentSprite.posY - 8)))
            {
                visibleSprites[vCounter] = currentSprite;
                vCounter ++;
            }
        }

        // Sort by Priority and take max 10 sprites from lowest prio to highest
        std::sort(std::begin(visibleSprites), std::end(visibleSprites));
        uint8_t spriteStart = vCounter > Video::MAX_SPRITES_Y ? Video::MAX_SPRITES_Y : vCounter;
        for(int i = spriteStart - 1; i >= 0; i--)
        {
            Video::Sprite currentSprite = visibleSprites[i];
            Video::Tile currentTile = currentSprite.bigSprite && lcdY >= currentSprite.posY - 8
                ? tileList.loadSpriteTile(currentSprite.tileNr + 1)
                : tileList.loadSpriteTile(currentSprite.tileNr);    
            currentTile = currentSprite.flipY && currentSprite.bigSprite && lcdY >= currentSprite.posY - 8
                ? tileList.loadSpriteTile(currentSprite.tileNr - 1)
                : currentTile;

            for(int j = 0; j < 8; j++)
            {                
                // If the numbers are not equal we loaded the 
                // second tile of the  8x16 sprite.
                uint8_t yCorrection = currentSprite.tileNr == currentTile.nr ? 16 : 8; 

                uint8_t xCord = currentSprite.flipX ? (7 - j) : j;
                uint8_t yCord = currentSprite.flipY 
                    ? abs(lcdY - (currentSprite.posY - yCorrection + 7))
                    : lcdY - (currentSprite.posY - yCorrection);
                
                uint8_t pixelData = currentTile.data[yCord][xCord];
                Enums::GB_SHADE color = currentSprite.palette1Selected
                    ? obj1Palette.colors[pixelData]
                    : obj0Palette.colors[pixelData];      

                // If the sprite has bgPrio and the background color is not WHITE, skip rendering of pixel
                // also skip it, if it is a transparent pixel (pixelData = 0) - this way we don't override previous rendered priority sprites
                int16_t backgroundXCord = (currentSprite.posX - 8) + j;
                if(!(currentSprite.bgPrio && backgroundBuffer[lcdY][backgroundXCord] != Enums::GB_SHADE::WHITE) 
                && color != Enums::GB_SHADE::TRANSPARENT && backgroundXCord < 160 && backgroundXCord >= 0)
                    spriteBuffer[lcdY][backgroundXCord] = color;                  
            }
        }   
    }

    void Ppu::resetBuffers(const bool initial)
    {
        for(uint8_t y = 0; y < 144; y++)
        {
            for(uint8_t x = 0; x < 160; x++)
            {
                if(initial)
                {
                    backgroundData[y][x] = Enums::GB_SHADE::WHITE;
                    spriteData[y][x] = Enums::GB_SHADE::TRANSPARENT;
                }
                backgroundBuffer[y][x] = Enums::GB_SHADE::WHITE;
                spriteBuffer[y][x] = Enums::GB_SHADE::TRANSPARENT;
            }
        }
    }
}