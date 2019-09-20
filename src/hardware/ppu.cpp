#include "ppu.h"

Ppu::Ppu(Memory& memory) : memory(memory) { }

void Ppu::cycle(long cycles)
{
    if(!memory.readIORegisterBit(LCD_CONTROL, LCD_ENABLE)) return;

    cycleCount += cycles;
    uint8_t currentMode = 
          memory.readIORegisterBit(LCD_STATUS, LCD_MODE_HIGH) << 1 
        | memory.readIORegisterBit(LCD_STATUS, LCD_MODE_LOW);

    bool modeProcessed = false;
    switch(currentMode)
    {
        case MODE_OAM:
            if(cycleCount < CYCLES_PER_OAMSEARCH) return;

            // Check for OAM Interrupt
            if((bool) memory.readIORegisterBit(LCD_STATUS, LCD_OAM_INTERRUPT_ENABLED))
            {
                memory.writeIORegisterBit(INTERRUPT_FLAG, INTERRUPT_LCD, true);
            }

            // Check for LCD Y Compare Interrupt, if it is enabled
            if((bool) memory.readIORegisterBit(LCD_STATUS, LCD_C_INTERRUPT_ENABLED))
            {
                uint8_t lcdy = memory.readIORegister(LCD_Y);
                uint8_t lcdyc = memory.readIORegister(LCD_Y_COMPARE);
                bool isLycEqualMode = (bool) memory.readIORegisterBit(LCD_STATUS, LCD_COINCIDENCE_MODE);
                if(    (isLycEqualMode && lcdy == lcdyc)
                    || (!isLycEqualMode && lcdy != lcdyc))
                {
                    memory.writeIORegisterBit(INTERRUPT_FLAG, INTERRUPT_LCD, true);
                }                
            }

            memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_HIGH, 1);
            memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_LOW, 1);
            cycleCount = cycleCount % CYCLES_PER_OAMSEARCH;
            modeProcessed = true;
            break;
        case MODE_TRANSFER:
            if(cycleCount < CYCLES_PER_TRANSFER) return;

            // Nothing to do in this stage besides switching into the next mode
            memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_HIGH, 0);
            memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_LOW, 0);
            cycleCount = cycleCount % CYCLES_PER_TRANSFER;
            modeProcessed = true;
            break;
        case MODE_HBLANK:
            if(cycleCount < CYCLES_PER_HBLANK) return;

            // Check for H-BLANK Interrupt
            if((bool) memory.readIORegisterBit(LCD_STATUS, LCD_H_BLANK_INTERRUPT_ENABLE))
            {
                memory.writeIORegisterBit(INTERRUPT_FLAG, INTERRUPT_LCD, true);
            }

            // DRAW Line on Screen
            // TODO

            // Enter V-BLANK on last line 143
            if(memory.read(LCD_Y) == 143)
            {
                memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_HIGH, 0);
                memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_LOW, 1);
            }
            // Enter OAM again
            else
            {
                memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_HIGH, 1);
                memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_LOW, 0);
            }     

            // Increment Line count and update cycles
            memory.write(LCD_Y, memory.read(LCD_Y) + 1, true); 
            cycleCount = cycleCount % CYCLES_PER_HBLANK;     
            modeProcessed = true; 
            break; 
        case MODE_VBLANK:
            if(cycleCount < CYCLES_PER_VBLANK) return;

            // Set V_BLANK interrupt on V-Blank mode begin (Line 144)
            if(memory.read(LCD_Y) == 144)
            {
                memory.writeIORegisterBit(INTERRUPT_FLAG, INTERRUPT_V_BLANK, true);
            }
            
            // Reset on last line 153 and Enter OAM
            if(memory.read(LCD_Y) == 153)
            {
                memory.write(LCD_Y, 0, true);
                memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_HIGH, 1);
                memory.writeIORegisterBit(LCD_STATUS, LCD_MODE_LOW, 0);
            }
            // Else increment Y and stay in V-Blank Mode
            else
            {                
                memory.write(LCD_Y, memory.read(LCD_Y) + 1, true);
            }

            cycleCount = cycleCount % CYCLES_PER_VBLANK; 
            modeProcessed = true;
            break;
    }
    // Because the CPU maybe processed so many cycles since
    // the last PPU cycle, we will work as much as we can
    // with the cycles we got to catch up
    if(modeProcessed) cycle(0);
}