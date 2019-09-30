#include "ppu.h"

Ppu::Ppu(Mmu& mmu) : 
    mmu(mmu), 
    tileData(mmu), 
    backgroundMaps(mmu)
{ 
    for(int i = 0; i < 144; i++)
    {
        memset(backgroundBuffer[i], 0, 160);
    }    
}

void Ppu::cycle(uint8_t cycles)
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
        // Nothing to do in this stage besides switching into the next mode
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

        // DRAW Line on Screen
        uint8_t lcdY = mmu.readIORegister(REG_LCD_Y);
        if(lcdY <= 143)
        {
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
                    if(i == 19 && j >= backgroundTileXOffset) continue;
                    backgroundBuffer[lcdY][(i * 8) + j] = currentTile.data[backgroundTileYOffset][j];
                }
            } 
        }               

        // Enter V-BLANK on last line 143
        if(lcdY == 143) mmu.writeLcdMode(MODE_VBLANK);
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