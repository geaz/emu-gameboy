#pragma once
#ifndef INSTRUCTIONSCREEN_H
#define INSTRUCTIONSCREEN_H

#include "../opengl/screen.h"
#include "../hardware/cpu.h"

class InstructionScreen : public Screen
{   
    public:
        InstructionScreen(Cpu& cpu);

        void update() override;

        Cpu& cpu;
};

#endif // INSTRUCTIONSCREEN_H