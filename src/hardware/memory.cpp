#include <stdexcept>
#include <cstring>
#include "memory.h"

Memory::Memory(Cartridge& cartridge) : cartridge(cartridge) 
{ 
}

void Memory::write(const uint16_t address, const uint8_t value) { memory[address] = value; }
uint8_t Memory::read(const uint16_t address, const bool debugAccess) const 
{ 
    // Cartridge Mapping
    if(address >= 0x000 && address <= 0x3F00)
        return cartridge.read(address);
    // VRAM Access through the PPU
    // CPU is not allowed to access it directly
    // PPU State has to be checked, wether the CPU is
    // currently allowed to access it
    else if(address >= 0x8000 && address <= 0x9FFF && !debugAccess)
        throw std::runtime_error("Illegal VRAM access");
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
