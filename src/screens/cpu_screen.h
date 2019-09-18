#pragma once
#ifndef CPUSCREEN_H
#define CPUSCREEN_H

#include "../opengl/screen.h"

#include "../hardware/cpu.h"

class CpuScreen : public Screen
{   
    public:
        CpuScreen(Cpu& cpu);

        void update() override;

        Cpu& cpu;
};

#endif // CPUSCREEN_H