#include <stdexcept>
#include <cstring>
#include "mmu.h"

Mmu::Mmu(Cartridge& cartridge) : cartridge(cartridge) { }

uint8_t Mmu::read(const uint16_t address, const bool ppuAccess) const 
{     
    // VRAM Access through the PPU. CPU is not allowed to access it directly.
    // PPU Mode has to be checked, wether the CPU is currently allowed to access it
    // ppuAccess is able to overwrite this behaviour. This way it is possible 
    // for the debugging tools and the PPU to read memory during each state
    if(!ppuAccess)
    {
        LCDMode currentPpuMode = readLcdMode();
        if(currentPpuMode == MODE_TRANSFER && address >= 0x8000 && address <= 0x9FFF)
            return 0xFF;
        else if((currentPpuMode == MODE_TRANSFER || currentPpuMode == MODE_OAM)
                && address >= 0xFE00 && address <= 0xFE9F)
            return 0xFF;
    }    

    // Cartridge Bank 0
    if(address >= 0x000 && address <= 0x3FFF)
        return cartridge.read(address);    
    // Cartridge Bank 1..NN
    else if(address >= 0x4000 && address <= 0x7FFF)
        return cartridge.read(address);    
    else
        return memory[address];     
}

void Mmu::write(const uint16_t address, const uint8_t value) 
{
    if(address == 0x9800)
        auto t = "";
    // If writing to LDCY I/O register, it gets a reset.
    if(address == REG_LCD_Y) memory[address] = 0;
    else if(address == REG_DIVIDER) memory[address] = 0;
    // If written to DMA start a DMA transfer to OAM
    else if(address == REG_DMA) executeDmaTransfer(value);    
    else if(address == REG_INTERRUPT_FLAG)
        memory[address] = value;  
    // If written to the pad register for setting bit 4 & 5
    // Preserver Lower Bits (= Button pressed atm)
    // 0x30 = 0011 0000
    else if(address == REG_PAD && (value & 0x30) != 0) 
        memory[REG_PAD] = ((value ^ memory[REG_PAD]) & 0xF0) | (memory[REG_PAD] & 0x0F);
    else memory[address] = value; 
}

void Mmu::rawWrite(const uint16_t address, const uint8_t value) 
{
    if(address == 0x9800)
        auto t = "";
    memory[address] = value;
}

void Mmu::executeDmaTransfer(const uint8_t value)
{
    memory[REG_DMA] = value;
    uint16_t startAddress = value * 0x100;

    for (int i = 0x0; i <= 0x9F; i++) 
    {
        uint16_t copyFrom = startAddress + i;
        uint16_t copyTo = 0xFE00 + i;

        uint8_t copyValue = memory[copyFrom];
        memory[copyTo] = copyValue;
    }
}

uint8_t Mmu::readIORegisterBit(const IORegister reg, const uint8_t bitNr) const 
{ 
    return (memory[reg] >> bitNr) & 0x1; 
}

uint8_t Mmu::readIORegister(const IORegister reg) const 
{
    return memory[reg]; 
}

void Mmu::writeIORegisterBit(const IORegister reg, const uint8_t bitNr, const bool value) 
{ 
    if(value) memory[reg] |= (0x1 << bitNr); 
    else memory[reg] &= ~(0x1 << bitNr); 
}

LCDMode Mmu::readLcdMode() const
{
    return (LCDMode)(readIORegisterBit(REG_LCD_STATUS, LCD_MODE_HIGH) << 1 | readIORegisterBit(REG_LCD_STATUS, LCD_MODE_LOW));
}

void Mmu::writeLcdMode(const LCDMode lcdMode)
{
    writeIORegisterBit(REG_LCD_STATUS, LCD_MODE_HIGH, (lcdMode >> 1) & 0x1);
    writeIORegisterBit(REG_LCD_STATUS, LCD_MODE_LOW, lcdMode & 0x1);
}

uint32_t Mmu::getSize() const 
{ 
    return memorySize; 
}
