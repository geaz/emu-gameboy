#pragma once
#ifndef DEBUGSCREEN_H
#define DEBUGSCREEN_H

#include "../opengl/screen.h"
#include "../hardware/cpu.h"

class DebugScreen : public Screen
{   
    public:
        DebugScreen(Cpu& cpu);

        void handleKeys(const int key, const int scancode, const int action, const int mods) override; 
        void update() override;

        Cpu& cpu;

        static bool showCpu;
};

#endif // DEBUGSCREEN_H