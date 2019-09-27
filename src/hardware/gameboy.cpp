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

void Gameboy::pressButton(Button button)
{
    mmu.write(REG_PAD, 0xCF); //1100 1111 (No Buttons pressed)
}