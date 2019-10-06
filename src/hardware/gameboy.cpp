#include "gameboy.h"

namespace GGB
{
    GameBoy::GameBoy(Hardware::Cartridge& cartridge) : 
        cartridge(cartridge),
        mmu(Hardware::Mmu(cartridge)),
        cpu(Hardware::Cpu(mmu)),
        ppu(mmu),
        apu(mmu),
        input(Hardware::Input(mmu)),
        timer(Hardware::Timer(mmu)),
        debugger(cartridge, mmu, cpu, apu)
    { }

    /**
     * This method always emulate a complete screen refresh per call.
     * One call emulates 70368 cycles (1 frame duration on DMG)
     * After each instruction the processed cycles are given to the remaining components.
     * 
     * In the beginning of the instruction emulation we start a clock.
     * As soon as the application calls this method again, we check, 
     * how long it took from starting the previous call until now.
     * If this time is < ~16.775.708 nano seconds (time a frame takes on the DMG),
     * we will enter a NOP loop (while). 
     * This way we always emulate the "correct" time a frame should take and should get ~59.6 Frames a second.
     **/
    void GameBoy::process()
    {
        using Enums::CPU_STATE;
        
        if(clock.started) while(clock.shouldSleep()) { };

        int64_t cycles = GGB::Constants::FRAME_CYCLES;
        while(cycles > 0 && (cpu.state == CPU_STATE::RUNNING || cpu.state == CPU_STATE::STEP))
        {
            if(!clock.started && cpu.state == CPU_STATE::RUNNING) clock.start();
            int opCycles = cpu.cycle();

            // If the CPU is halted, it won't process any operations
            // In this case we set the cycles to four (NOP) to do 
            // progress on the PPU and Timer
            opCycles = opCycles == 0
                ? 4
                : opCycles;

            ppu.cycle(opCycles);
            timer.cycle(opCycles);
            apu.cycle(opCycles);
            input.cycle();
            debugger.cycle();
            
            cycles -= opCycles;
        }     
    }
}