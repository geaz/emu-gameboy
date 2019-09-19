#include "gameboy.h"

Gameboy::Gameboy(Cartridge& cartridge) : 
    cartridge(cartridge),
    memory(Memory(cartridge)),
    cpu(Cpu(memory))
{ }

void Gameboy::process()
{
    cpu.cycle();
}