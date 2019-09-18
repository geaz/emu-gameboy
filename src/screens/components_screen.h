#pragma once
#ifndef COMPONENTSSCREEN_H
#define COMPONENTSSCREEN_H

#include "../opengl/screen.h"

#include "../hardware/memory.h"

class ComponentsScreen : public Screen
{   
    public:
        ComponentsScreen(Memory& memory);

        void update() override;

        Memory& memory;
};

#endif // COMPONENTSSCREEN_H