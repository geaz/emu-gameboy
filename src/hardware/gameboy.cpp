#include "gameboy.h"

Gameboy::Gameboy(Cartridge& cartridge) : 
    cartridge(cartridge),
    mmu(Mmu(cartridge)),
    cpu(Cpu(mmu)),
    ppu(mmu)
{ }

void Gameboy::process()
{
    long cycles = cpu.cycle();
    ppu.cycle(cycles);
}