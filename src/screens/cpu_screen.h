#pragma once
#ifndef CPUSCREEN_H
#define CPUSCREEN_H

#include "../opengl/screen.h"
#include "../hardware/cpu.h"

class CpuScreen : public Screen
{   
    public:
        CpuScreen(Cpu& cpu);

        void handleKeys(const int key, const int scancode, const int action, const int mods) override; 
        void update() override;

        Cpu& cpu;
};

#endif // CPUSCREEN_H