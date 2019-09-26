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
            throw std::runtime_error("Illegal VRAM access");
        else if(  (currentPpuMode == MODE_TRANSFER || currentPpuMode == MODE_OAM)
                && address >= 0xFE00 && address <= 0xFE9F)
            throw std::runtime_error("Illegal OAM access");
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

void Mmu::write(const uint16_t address, const uint8_t value, const bool ppuAccess) 
{
    // If it is not the PPU writing to the LDCY I/O register, it gets a reset.
    if(address == REG_LCD_Y && !ppuAccess) memory[address] = 0;
    else if(address == REG_DMA) throw std::runtime_error("NOT IMPLEMENTED");        
    else memory[address] = value; 
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
