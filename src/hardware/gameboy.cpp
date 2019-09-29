#include "gameboy.h"

Gameboy::Gameboy(Cartridge& cartridge) : 
    cartridge(cartridge),
    mmu(Mmu(cartridge)),
    cpu(Cpu(mmu)),
    ppu(mmu),
    timer(Timer(mmu))
{ }

void Gameboy::process()
{
    int cycles = cpu.clock.getCatchUpCycles();
    while(cycles > 0 && (cpu.state == RUNNING || cpu.state == STEP))
    {
        int opCycles = cpu.cycle();

        // If the CPU is halted, it won't process any operations
        // In this case we set the cycles to four to do 
        // progress on the PPU and Timer
        opCycles = opCycles == 0
            ? 4
            : opCycles;

        ppu.cycle(opCycles);
        timer.cycle(opCycles);
        
        cycles -= opCycles;
    }
    cpu.clock.Reset();    
}

void Gameboy::pressButton(Button button)
{
    mmu.write(REG_PAD, 0xCF); //1100 1111 (No Buttons pressed)
}