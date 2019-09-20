#include "ppu.h"

Ppu::Ppu(Memory& memory) : memory(memory) { }

void Ppu::cycle(long cycles)
{
    if(!memory.readIORegisterBit(LCD_STATUS, LCD_ENABLE)) return;

    cycleCount += cycles;
    uint8_t currentMode = 
          memory.readIORegisterBit(LCD_CONTROL, LCD_MODE_HIGH) << 1 
        & memory.readIORegisterBit(LCD_CONTROL, LCD_MODE_LOW);

    bool modeProcessed = false;
    switch(currentMode)
    {
        case MODE_OAM:
            if(cycleCount < CYCLES_PER_OAMSEARCH) return;

            // Nothing to do in this stage besides switching into the next mode
            memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_HIGH, 1);
            memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_LOW, 1);
            cycleCount = cycleCount % CYCLES_PER_OAMSEARCH;
            modeProcessed = true;
            break;
        case MODE_TRANSFER:
            if(cycleCount < CYCLES_PER_TRANSFER) return;

            // LYC? HBLANK INTERRUPT?

            memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_HIGH, 0);
            memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_LOW, 0);
            cycleCount = cycleCount % CYCLES_PER_TRANSFER;
            modeProcessed = true;
            break;
        case MODE_HBLANK:
            if(cycleCount < CYCLES_PER_HBLANK) return;
            memory.write(LCD_Y, memory.read(LCD_Y) + 1);
            // HBLANK INTERRUPT?
            // DRAW Line on Screen
            // Enter V-BLANK
            if(memory.read(LCD_Y) < 144)
            {
                memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_HIGH, 0);
                memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_LOW, 1);
            }
            // Enter OAM again
            else
            {
                memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_HIGH, 1);
                memory.writeIORegisterBit(LCD_CONTROL, LCD_MODE_LOW, 0);
            }      
            cycleCount = cycleCount % CYCLES_PER_HBLANK;     
            modeProcessed = true; 
            break; 
        case MODE_VBLANK:
            if(cycleCount < CYCLES_PER_VBLANK) return;
            // SET V INTERRUPT

            cycleCount = cycleCount % CYCLES_PER_VBLANK; 
            modeProcessed = true;
            break;
    }
    // Because the CPU maybe processed so many cycles since
    // the last PPU cycle, we will work as much as we can
    // with the cycles we got to catch up
    if(modeProcessed) cycle(0);
}