#include <stdexcept>
#include <cstring>
#include "memory.h"

Memory::Memory(Cartridge& cartridge) : cartridge(cartridge)
{ }

void Memory::write(const uint16_t address, const uint8_t value, const bool ppuWrite) 
{
    // If it is not the PPU writing to the LDCY I/O register, it gets a reset.
    if(address == LCD_Y && !ppuWrite)
    {
        memory[address] = 0;
    } 
    else
        memory[address] = value; 
}

uint8_t Memory::read(const uint16_t address, const bool debugAccess) const 
{     
    // VRAM Access through the PPU. CPU is not allowed to access it directly.
    // PPU Mode has to be checked, wether the CPU is currently allowed to access it
    // debugAccess is able to overwrite this behaviour. This way it is possible 
    // for the debugging tools to read memory during each state
    if(!debugAccess)
    {
        uint8_t currentPpuMode = 
            readIORegisterBit(LCD_STATUS, LCD_MODE_HIGH) << 1 
            | readIORegisterBit(LCD_STATUS, LCD_MODE_LOW);
        if(currentPpuMode == MODE_TRANSFER && address >= 0x8000 && address <= 0x9FFF)
            throw std::runtime_error("Illegal VRAM access");
        else if(  (currentPpuMode == MODE_TRANSFER || currentPpuMode == MODE_OAM)
                && address >= 0xFE00 && address <= 0xFE9F)
            throw std::runtime_error("Illegal OAM access");
    }    

    // Cartridge Mapping
    if(address >= 0x000 && address <= 0x3F00)
        return cartridge.read(address);    
    else
        return memory[address];     
}

void Memory::writeIORegisterBit(const IORegister reg, const uint8_t bitNr, const bool value) 
{ 
    if(value) memory[reg] |= (0x1 << bitNr); 
    else memory[reg] &= ~(0x1 << bitNr); 
}

uint8_t Memory::readIORegisterBit(const IORegister reg, const uint8_t bitNr) const { return (memory[reg] >> bitNr) & 0x1; }
uint8_t Memory::readIORegister(const IORegister reg) const { return memory[reg]; }

uint32_t Memory::getSize() const { return memorySize; }
