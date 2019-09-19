#include <cstring>
#include "memory.h"

Memory::Memory(Cartridge& cartridge) : cartridge(cartridge) 
{ 
    // Copy cartridge into memory
    memcpy(&memory[0x100], &cartridge.cartridgeData[0x100], 0x3F00);
}

uint32_t Memory::getSize() { return memorySize; }
uint8_t Memory::read(uint16_t address) { return memory[address]; }
void Memory::write(uint16_t address, uint8_t value) { memory[address] = value; }