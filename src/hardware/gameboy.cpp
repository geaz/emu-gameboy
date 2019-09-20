#include "gameboy.h"

Gameboy::Gameboy(Cartridge& cartridge) : 
    cartridge(cartridge),
    memory(Memory(cartridge)),
    cpu(Cpu(memory)),
    ppu(memory)
{ }

void Gameboy::process()
{
    long cycles = cpu.cycle();
    ppu.cycle(cycles);
}