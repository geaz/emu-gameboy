#pragma once
#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "cartridge.h"

class Gameboy
{
    public:
        Gameboy(Cartridge& cartridge);
        void process();

        Cpu cpu;
        Cartridge& cartridge;
};

#endif // GAMEBOY_H