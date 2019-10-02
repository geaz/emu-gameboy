#include "gameboy.h"

namespace GGB
{
    GameBoy::GameBoy(Hardware::Cartridge& cartridge) : 
        cartridge(cartridge),
        mmu(Hardware::Mmu(cartridge)),
        cpu(Hardware::Cpu(mmu)),
        ppu(mmu),
        input(Hardware::Input(mmu)),
        timer(Hardware::Timer(mmu))
    { }

    void GameBoy::process()
    {
        using Enums::CPU_STATE;

        int cycles = cpu.clock.getCatchUpCycles();
        while(cycles > 0 && (cpu.state == CPU_STATE::RUNNING || cpu.state == CPU_STATE::STEP))
        {
            int opCycles = cpu.cycle();

            // If the CPU is halted, it won't process any operations
            // In this case we set the cycles to four (NOP) to do 
            // progress on the PPU and Timer
            opCycles = opCycles == 0
                ? 4
                : opCycles;

            ppu.cycle(opCycles);
            timer.cycle(opCycles);
            input.cycle();
            
            cycles -= opCycles;
        } 
    }
}