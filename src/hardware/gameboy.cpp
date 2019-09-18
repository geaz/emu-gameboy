#include "gameboy.h"

Gameboy::Gameboy(Cartridge& cartridge) : 
    cartridge(cartridge),
    cpu(cartridge)
{ }

void Gameboy::process()
{
    if(cpu.state == RUNNING)
    {
        cpu.cycle();
    }
}