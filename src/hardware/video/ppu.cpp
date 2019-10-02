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
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::ENABLE)) return;

        cycleCount += cycles;
        Enums::LCD_MODE currentMode = mmu.readLcdMode();

        bool modeProcessed = false;
        switch (currentMode)
        {
            case Enums::LCD_MODE::OAM:
                modeProcessed = processOam();
                break;
            case Enums::LCD_MODE::TRANSFER:
                modeProcessed = processTransfer();
                break;
            case Enums::LCD_MODE::HBLANK:
                modeProcessed = processHBlank();
                break;
            case Enums::LCD_MODE::VBLANK:
                modeProcessed = processVBlank();
                break;
        }

        // Because the CPU maybe processed so many cycles since
        // the last PPU cycle, we will work as much as we can
        // with the cycles we got to catch up
        if(modeProcessed) cycle(0);
    }

    bool Ppu::processOam()
    {
        bool modeProcessed = false;
        if(cycleCount >= CYCLES_PER_OAMSEARCH)
        {
            // Check for OAM Interrupt
            if(mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::OAM_INTERRUPT_ENABLED))
            {
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::LCD, true);
            }

            // Check for LCD Y Compare Interrupt, if it is enabled
            if(mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::C_INTERRUPT_ENABLED))
            {
                uint8_t lcdy = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y);
                uint8_t lcdyc = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y_COMPARE);
                bool isLycEqualMode = mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::COINCIDENCE_MODE);
                if(    (isLycEqualMode && lcdy == lcdyc)
                    || (!isLycEqualMode && lcdy != lcdyc))
                {
                    mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::LCD, true);
                }                
            }

            mmu.writeLcdMode(Enums::LCD_MODE::TRANSFER);
            cycleCount -= CYCLES_PER_OAMSEARCH;
            modeProcessed = true;
        }    
        return modeProcessed;
    }

    bool Ppu::processTransfer()
    {
        bool modeProcessed = false;
        if(cycleCount >= CYCLES_PER_TRANSFER)
        {
            mmu.writeLcdMode(Enums::LCD_MODE::HBLANK);
            cycleCount -= CYCLES_PER_TRANSFER;
            modeProcessed = true;
        }    
        return modeProcessed;
    }
        
    bool Ppu::processHBlank()
    {
        bool modeProcessed = false;
        if(cycleCount >= CYCLES_PER_HBLANK)
        {
            // Check for H-BLANK Interrupt
            if(mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_STATUS, Enums::LCD_STATUS_FLAG::H_BLANK_INTERRUPT_ENABLE))
            {
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::LCD, true);
            }
            
            drawBackground();
            drawWindow();
            drawSprites();

            // Enter V-BLANK on last line 143
            if(mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y) == 143) mmu.writeLcdMode(Enums::LCD_MODE::VBLANK);
            // Enter OAM again
            else mmu.writeLcdMode(Enums::LCD_MODE::OAM);    

            // Increment Line count and update cycles
            mmu.rawWrite(Enums::IO_REGISTER::REG_LCD_Y, mmu.read(Enums::IO_REGISTER::REG_LCD_Y) + 1); 
            cycleCount -= CYCLES_PER_HBLANK;  
            modeProcessed = true;
        }       
        return modeProcessed; 
    }
        
    bool Ppu::processVBlank()
    {
        bool modeProcess = false;
        if(cycleCount >= CYCLES_PER_VBLANK)
        {
            // Set V_BLANK interrupt on V-Blank mode begin (Line 144)
            if(mmu.read(Enums::IO_REGISTER::REG_LCD_Y) == 144)
            {
                mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::V_BLANK, true);

                // Copy buffers to data
                std::copy(&spriteBuffer[0][0], &spriteBuffer[0][0] + 160*144, &spriteData[0][0]);
                std::copy(&backgroundBuffer[0][0], &backgroundBuffer[0][0] + 160*144, &backgroundData[0][0]);
                resetBuffers(false);
            }

            // Reset on last line 153 and Enter OAM
            if(mmu.read(Enums::IO_REGISTER::REG_LCD_Y) == 153)
            {
                mmu.rawWrite(Enums::IO_REGISTER::REG_LCD_Y, 0);
                mmu.writeLcdMode(Enums::LCD_MODE::OAM);
            }
            // Else increment Y and stay in V-Blank Mode
            else mmu.rawWrite(Enums::IO_REGISTER::REG_LCD_Y, mmu.read(Enums::IO_REGISTER::REG_LCD_Y) + 1);

            cycleCount -= CYCLES_PER_VBLANK; 
            modeProcess = true;
        }    
        return modeProcess;
    }

    void Ppu::drawBackground()
    {
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::BG_ENABLE)) return;

        uint8_t lcdY = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y);
        uint8_t scrollY = mmu.readIORegister(Enums::IO_REGISTER::REG_SCROLL_Y);
        uint8_t scrollX = mmu.readIORegister(Enums::IO_REGISTER::REG_SCROLL_X);

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
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::WINDOW_ENABLE)) return;

        uint8_t lcdY = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y);
        uint8_t windowY = mmu.readIORegister(Enums::IO_REGISTER::REG_WINDOW_Y);
        uint8_t windowX = mmu.readIORegister(Enums::IO_REGISTER::REG_WINDOW_X) - 7;

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
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_LCD_CONTROL, Enums::LCD_CONTROL_FLAG::OBJ_ENABLE)) return;

        obj0Palette = colorPalettes.getOBP0Palette();
        obj1Palette = colorPalettes.getOBP1Palette();

        Video::Sprite visibleSprites[Video::TOTAL_SPRITES];
        spriteList.loadSprites();

        uint8_t lcdY = mmu.readIORegister(Enums::IO_REGISTER::REG_LCD_Y);
        int vCounter = 0;
        for(int i = 0; i < Video::TOTAL_SPRITES; i++)
        {
            Video::Sprite currentSprite = spriteList.data[i];

            // Pos Y : Specifies the sprites vertical position on the screen (minus 16).
            // An offscreen value (for example, Y=0 or Y>=160) hides the sprite.
            if(lcdY >= currentSprite.posY - 16 
                && (  (currentSprite.bigSprite && lcdY <= currentSprite.posY)
                || (!currentSprite.bigSprite && lcdY <= currentSprite.posY - 8)))
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
                ? tileList.loadSpriteTile(currentSprite.upperTileNr)
                : tileList.loadSpriteTile(currentSprite.lowerTileNr);    

            for(int j = 0; j < 8; j++)
            {                
                uint8_t xCord = currentSprite.flipX ? (7 - j) : j;
                uint8_t yCord = currentSprite.flipY 
                    ? abs(lcdY - (currentSprite.posY - 16 + 8))
                    : lcdY - (currentSprite.posY - 16);
                
                uint8_t pixelData = currentTile.data[yCord][xCord];
                Enums::GB_SHADE color = currentSprite.palette1Selected
                    ? obj0Palette.colors[pixelData]
                    : obj1Palette.colors[pixelData];      

                // If the sprite has bgPrio and the background color is not WHITE, skip rendering of pixel
                // also skip it, if it is a transparent pixel (pixelData = 0) - this way we don't override previous rendered priority sprites
                if(!(currentSprite.bgPrio && backgroundBuffer[lcdY][(currentSprite.posX - 8) + j] != Enums::GB_SHADE::WHITE) 
                && color != Enums::GB_SHADE::TRANSPARENT && (currentSprite.posX - 8) + j < 160)
                    spriteBuffer[lcdY][(currentSprite.posX - 8) + j] = color;                  
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