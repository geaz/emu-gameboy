#pragma once
#ifndef ROMSCREEN_H
#define ROMSCREEN_H

#include "../opengl/screen.h"

#include "../rom.h"

class RomScreen : public Screen
{   
    public:
        RomScreen(const Rom rom);

        void update() override;

        Rom rom;
};

#endif // ROMSCREEN_H