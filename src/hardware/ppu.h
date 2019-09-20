#pragma once
#ifndef PPU_H
#define PPU_H

#include "memory.h"

enum Mode {
    MODE_HBLANK = 0,
    MODE_VBLANK = 1,
    MODE_OAM = 2,
    MODE_TRANSFER = 3,
};

class Ppu
{
    public:
        Ppu(Memory& memory);

        void cycle(long cycles);

    private:
        Memory& memory;
        long cycleCount = 0;

        const uint16_t CYCLES_PER_HBLANK = 207;   // Mode 0 (H-Blank) 207 cycles
        const uint16_t CYCLES_PER_VBLANK = 4560;  // Mode 1 (V-Blank) 4560 cycles
        const uint16_t CYCLES_PER_OAMSEARCH = 83; // Mode 2 (OAM Search) 83 cycles
        const uint16_t CYCLES_PER_TRANSFER = 175; // Mode 3 (Transfer LCD) 175 cycles
};

#endif // PPU_H