#pragma once
#ifndef MEMORYSCREEN_H
#define MEMORYSCREEN_H

#include "../opengl/screen.h"

#include "../hardware/memory.h"

class MemoryScreen : public Screen
{   
    public:
        MemoryScreen(Memory& memory);

        void update() override;

        Memory& memory;
};

#endif // MEMORYSCREEN_H