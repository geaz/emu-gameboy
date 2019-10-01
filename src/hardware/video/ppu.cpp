#include "ppu.h"
#include <algorithm>

Ppu::Ppu(Mmu& mmu) : 
    mmu(mmu), 
    tileData(mmu), 
    spriteList(mmu),
    backgroundMaps(mmu),
    colorPalettes(mmu)
{ 
    resetBuffers(); 
}

void Ppu::cycle(const uint8_t cycles)
{
    if(!mmu.readIORegisterBit(REG_LCD_CONTROL, LCD_ENABLE)) return;

    cycleCount += cycles;
    LCDMode currentMode = mmu.readLcdMode();

    bool modeProcessed = false;
    switch (currentMode)
    {
        case MODE_OAM:
            modeProcessed = processOam();
            break;
        case MODE_TRANSFER:
            modeProcessed = processTransfer();
            break;
        case MODE_HBLANK:
            modeProcessed = processHBlank();
            break;
        case MODE_VBLANK:
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
        if(mmu.readIORegisterBit(REG_LCD_STATUS, LCD_OAM_INTERRUPT_ENABLED))
        {
            mmu.writeIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_LCD, true);
        }

        // Check for LCD Y Compare Interrupt, if it is enabled
        if(mmu.readIORegisterBit(REG_LCD_STATUS, LCD_C_INTERRUPT_ENABLED))
        {
            uint8_t lcdy = mmu.readIORegister(REG_LCD_Y);
            uint8_t lcdyc = mmu.readIORegister(REG_LCD_Y_COMPARE);
            bool isLycEqualMode = mmu.readIORegisterBit(REG_LCD_STATUS, LCD_COINCIDENCE_MODE);
            if(    (isLycEqualMode && lcdy == lcdyc)
                || (!isLycEqualMode && lcdy != lcdyc))
            {
                mmu.writeIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_LCD, true);
            }                
        }

        mmu.writeLcdMode(MODE_TRANSFER);
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
        mmu.writeLcdMode(MODE_HBLANK);
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
        if(mmu.readIORegisterBit(REG_LCD_STATUS, LCD_H_BLANK_INTERRUPT_ENABLE))
        {
            mmu.writeIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_LCD, true);
        }
        
        drawBackground();
        drawSprites();

        // Enter V-BLANK on last line 143
        if(mmu.readIORegister(REG_LCD_Y) == 143) mmu.writeLcdMode(MODE_VBLANK);
        // Enter OAM again
        else mmu.writeLcdMode(MODE_OAM);    

        // Increment Line count and update cycles
        mmu.rawWrite(REG_LCD_Y, mmu.read(REG_LCD_Y) + 1); 
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
        if(mmu.read(REG_LCD_Y) == 144)
        {
            mmu.writeIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_V_BLANK, true);

            // Copy buffers to data
            std::copy(&spriteBuffer[0][0], &spriteBuffer[0][0] + 160*144, &spriteData[0][0]);
            std::copy(&backgroundBuffer[0][0], &backgroundBuffer[0][0] + 160*144, &backgroundData[0][0]);
            resetBuffers();
        }

        // Reset on last line 153 and Enter OAM
        if(mmu.read(REG_LCD_Y) == 153)
        {
            mmu.rawWrite(REG_LCD_Y, 0);
            mmu.writeLcdMode(MODE_OAM);
        }
        // Else increment Y and stay in V-Blank Mode
        else mmu.rawWrite(REG_LCD_Y, mmu.read(REG_LCD_Y) + 1);

        cycleCount -= CYCLES_PER_VBLANK; 
        modeProcess = true;
    }    
    return modeProcess;
}

void Ppu::drawBackground()
{
    if(!mmu.readIORegisterBit(REG_LCD_CONTROL, BG_DISPLAY)) return;

    uint8_t lcdY = mmu.readIORegister(REG_LCD_Y);
    uint8_t scrollY = mmu.readIORegister(REG_SCROLL_Y);
    uint8_t scrollX = mmu.readIORegister(REG_SCROLL_X);
    uint8_t windowY = mmu.readIORegister(REG_WINDOW_Y);
    uint8_t windowX = mmu.readIORegister(REG_WINDOW_X);

    // Wrap the Window around Y
    uint8_t startBackgroundTileY = (scrollY + lcdY) / 8 >= 32
        ? (scrollY + lcdY) / 8 % 32
        : (scrollY + lcdY) / 8;
    uint8_t backgroundTileYOffset = (scrollY + lcdY) % 8;

    uint8_t startBackgroundTileX = scrollX / 8;
    uint8_t backgroundTileXOffset = scrollX % 8;
    
    backgroundPalette = colorPalettes.getBWPalette();
    BackgroundMap currentBackgroundMap = backgroundMaps.getBackgroundMap();

    // The Game Boy screen is able to display 20 tiles horizontal (160 pixel / 8 pixel per Tile)
    for(int i = 0; i < 20; i++)
    {
        // Wrap the Window around X
        uint8_t tileNrX = startBackgroundTileX + i >= 32
            ? (startBackgroundTileX + i) % 32
            : startBackgroundTileX + i;
        uint8_t currentTileNr = currentBackgroundMap.data[startBackgroundTileY][tileNrX];
        Tile currentTile = tileData.getBackgroundTile(currentTileNr);
        // each tile is 8 pixels wide
        for(int j = 0; j < 8; j++)
        {
            // Skip the first pixels, if the window start in the middle of the first tile
            // And skip the last few pixels of the end tile
            if(i == 0 && j < backgroundTileXOffset) continue;
            if(i == 19 && backgroundTileXOffset != 0 && j >= backgroundTileXOffset) continue;
            backgroundBuffer[lcdY][(i * 8) + j] = currentTile.data[backgroundTileYOffset][j];
        }
    } 
}

void Ppu::drawSprites()
{
    if(!mmu.readIORegisterBit(REG_LCD_CONTROL, OBJ_ENABLE)) return;

    obj0Palette = colorPalettes.getOBP0Palette();
    obj1Palette = colorPalettes.getOBP1Palette();

    Sprite visibleSprites[TOTAL_SPRITES];
    spriteList.loadSprites();

    uint8_t lcdY = mmu.readIORegister(REG_LCD_Y);
    int vCounter = 0;
    for(int i = 0; i < TOTAL_SPRITES; i++)
    {
        Sprite currentSprite = spriteList.data[i];

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
    uint8_t spriteStart = vCounter > MAX_SPRITES_Y ? MAX_SPRITES_Y : vCounter;
    for(int i = spriteStart - 1; i >= 0; i--)
    {
        Sprite currentSprite = visibleSprites[i];
        if(currentSprite.bgPrio) continue;

        Tile currentTile = currentSprite.bigSprite && lcdY >= currentSprite.posY - 8
            ? tileData.getSpriteTile(currentSprite.upperTileNr)
            : tileData.getSpriteTile(currentSprite.lowerTileNr);    

        for(int j = 0; j < 8; j++)
        {                
            uint8_t xCord = currentSprite.flipX ? (7 - j) : j;
            uint8_t yCord = currentSprite.flipY 
                ? lcdY - ((currentSprite.posY - 16) * -1)
                : lcdY - (currentSprite.posY - 16);
            
            uint8_t pixelData = currentTile.data[yCord][xCord];
            uint8_t color = currentSprite.palette1Selected
                ? obj0Palette.colors[pixelData]
                : obj1Palette.colors[pixelData];                
            if(color != TRANSPARENT) spriteBuffer[lcdY][(currentSprite.posX - 8) + j] = color;                    
        }
    }   
}

void Ppu::resetBuffers()
{
    memset(&backgroundBuffer[0][0], WHITE, 160*144);
    memset(&spriteBuffer[0][0], TRANSPARENT, 160*144);  
}